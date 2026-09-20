#!/usr/bin/env python3
"""归属取证：把函数的 `this` 字节偏移与各注解类的成员边界做**精确匹配**打分。

用途（§49.4 第 (2) 项）：为"归属错"的函数找**宿主类**，产出 CLAUDE.md 要求的那种证据
——"函数引用的成员在**目标类中存在**、且**不在原类中存在**"。

为什么不用 decomp 的 `this + N`：
Hex-Rays 的 `this` 类型来自**注解**；当函数**被错误归属**时，`this` 的类型就是错的，
于是 `this + N` 会按**错误的元素尺寸**缩放（`CIniFile* this + 2522` 实际是 2522×8 字节）。
⇒ 只有 **asm 的 `[reg+imm]`** 才是无歧义的字节偏移。

判据（越严越好，按强度排序）：
  1. **精确命中**：被访问偏移 == 某成员的起始偏移（最强；再配合访问宽度 == 成员尺寸更佳）；
  2. **成员内命中**：落在某**有名字**成员的跨度内；
  3. **空洞命中**：落在无类型空洞里 —— **不算证据**（大类的空洞会覆盖任意偏移，
     2026-09-19 实测"区间覆盖"判据会命中上百个类）。

⚠️ 读表注意（2026-09-19 自查发现的偏差）：**"成员内"一列对"最后一个成员"会被高估** ——
末成员的跨度按 `binary_size` 兜底，于是"落在大类最后一个成员之后"的偏移也会被算成"成员内"。
因此**只有"精确命中"一列可作判据**；"成员内"只用来做同分时的辅助排序。
`--strict` 只保留"全部访问偏移都精确命中"的类（用于打破并列；返回空 = 没有类的成员表覆盖这些偏移）。

⚠️ 另一个已知限制：同一函数里 `this` 寄存器可能被复用去指别的对象，
于是"多个偏移其实不属于同一个对象"。本工具的逐指令跟踪只能缓解、不能根治；
`--strict` 返回空集时，正确解读是"**没有单个注解类的成员模型能覆盖这些偏移**"，
而**不是**"这些函数没有归属"。要根治需要逐访问的对象溯源（dataflow）。

⚠️ 已知漏采形态（2026-09-19 实测，命中即会误报"0 个偏移"）：
  1. **索引寻址** `[reg+reg*scale+disp]`（如 `[ecx+edx*8+0C2F80h]`）—— 正则只认 `[reg±imm]`；
  2. **`this` 中途被重装**（`mov esi,[esp+..]` 之后 esi 不再是 this）—— 覆盖跟踪会把它移出集合，
     于是一个真实访问都不记录（实测 `sub_504130`：真偏移 `-4/0/+4/+8/+0xC/+0x10`）；
  3. **`this` 本身是结构体中间指针**（用 `[esi-4]` 这类负偏移）—— 负偏移已支持，
     但"中间指针"在语义上无法与任何**类基址**对齐，offsets 匹配法对它天然失效。
遇到"0 个偏移"先手工读函数体（本项目多次靠手工读定案），别把 0 当成"没有归属"。

用法：
    python tools/attribution_offset_match.py --func 0x504240
    python tools/attribution_offset_match.py --func 0x504240 --func 0x4EC700 --top 6
    python tools/attribution_offset_match.py --func 0x504240 --strict
    python tools/attribution_offset_match.py --func 0x504240 --src CIniFile   # 打印"不在原类中"的确认
"""
import argparse
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM = os.path.join(ROOT, 'original', 'PAL3.exe.asm')
STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')
PROC_RE = re.compile(r'^(sub_[0-9A-Fa-f]+)\s+proc\s+near')


def _off_int(k):
    k = str(k).strip()
    return int(k, 16) if k.lower().startswith('0x') else int(k)


def _imm(tok):
    t = tok.strip()
    if not t:
        return None
    return int(t[:-1], 16) if t.lower().endswith('h') else int(t)


def this_offsets(lines, addr):
    """→ (offset→行号, this 寄存器集合, 函数行范围)"""
    name = 'sub_%X' % addr
    s = None
    for i, l in enumerate(lines):
        m = PROC_RE.match(l)
        if m and m.group(1).lower() == name.lower():
            s = i
            break
    if s is None:
        return None
    e = s
    for j in range(s, len(lines)):
        if lines[j].strip().endswith('endp'):
            e = j
            break
    # 逐指令前向跟踪「哪个寄存器此刻装的是 this」：函数中途寄存器会被复用于别的局部，
    # 所以必须在**每条指令处**判定，而不是整函数取一个寄存器集合。
    is_this = {'ecx': True}
    offs = {}
    for j in range(s, e + 1):
        code = lines[j].split(';')[0].rstrip()
        if not code.strip():
            continue
        # 1) 记录本指令里对 this 寄存器的访问（**含负偏移**）
        #    2026-09-19 补：原实现只匹配 `[reg+IMM]`，把 `[esi-4]` 这类**负偏移**整个漏掉，
        #    于是 `this` 实际是"结构体中间指针"的函数会被报成"0 个偏移"
        #    （实测 sub_504130：真偏移是 -4/0/+4/+8/+0xC/+0x10，全在 ReadLine 的输出缓冲上）。
        for m in re.finditer(r'\[(\w+)([+-])([0-9A-Fa-f]+h|\d+)\]', code):
            r = m.group(1)
            if is_this.get(r):
                v = _imm(m.group(3))
                if v is not None:
                    if m.group(2) == '-':
                        v = -v
                    if v not in offs:
                        offs[v] = j + 1
        # 2) 更新寄存器状态（写操作）
        m = re.search(r'\bmov\s+(\w+),\s*(\w+)\s*$', code)
        if m:
            dst, src = m.group(1), m.group(2)
            is_this[dst] = bool(is_this.get(src)) if src in is_this else False
            continue
        m = re.match(r'\s*mov\s+(\w+)\s*,', code)
        if m:
            is_this[m.group(1)] = False        # mov A, <mem|imm>
            continue
        m = re.match(r'\s*lea\s+(\w+)\s*,\s*\[(\w+)(?:\+0)?\]\s*$', code)
        if m:
            is_this[m.group(1)] = bool(is_this.get(m.group(2)))
            continue
        m = re.match(r'\s*(?:lea|xor|sub|add|and|or|pop|imul|shl|shr|neg|not)\s+(\w+)', code)
        if m and m.group(1) != 'ecx':
            is_this[m.group(1)] = False
    regs = {r for r, v in is_this.items() if v}
    return offs, regs, (s + 1, e + 1)


def load_classes():
    out = {}
    for fn in os.listdir(STRUCTS):
        if not fn.endswith('.json'):
            continue
        cls = fn[:-5]
        j = json.load(open(os.path.join(STRUCTS, fn), encoding='utf-8'))
        ms = []
        for k, v in (j.get('known_members') or {}).items():
            try:
                o = _off_int(k)
            except Exception:
                continue
            ms.append((o, str(v.get('name')), str(v.get('type'))))
        ms.sort()
        out[cls] = (j.get('binary_size') or 0, ms)
    return out


def score(off_map, classes, top, strict=False):
    offs = sorted(off_map)
    rows = []
    for cls, (size, ms) in classes.items():
        starts = {m[0] for m in ms}
        exact = [o for o in offs if o in starts]
        if strict and len(exact) != len(offs):
            continue
        named = []
        for o in offs:
            for i, (mo, n, t) in enumerate(ms):
                nxt = ms[i + 1][0] if i + 1 < len(ms) else size
                if mo <= o < (nxt or 0):
                    named.append(o)
                    break
        rows.append((len(exact), len(named), size, cls, exact))
    rows.sort(key=lambda r: (-r[0], -r[1]))
    return rows[:top]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--func', action='append', default=[], required=True)
    ap.add_argument('--top', type=int, default=5)
    ap.add_argument('--src', default=None, help='原类名，用于打印"不在原类中"的确认')
    ap.add_argument('--strict', action='store_true',
                    help='只保留"全部访问偏移都精确命中成员起始"的类（用于打破并列）')
    args = ap.parse_args()

    with open(ASM, encoding='utf-8', errors='replace') as fh:
        lines = fh.read().split('\n')
    classes = load_classes()
    print('[asm] %d 行 / 注解类 %d 个' % (len(lines), len(classes)), file=sys.stderr)

    for a in args.func:
        addr = int(a, 16) if a.lower().startswith('0x') else int(a)
        r = this_offsets(lines, addr)
        if r is None:
            print('== %s NOT FOUND' % a)
            continue
        off_map, regs, (s, e) = r
        print('== sub_%X (asm 行 %d-%d)  this 寄存器=%s  访问 %d 个字节偏移: %s'
              % (addr, s, e, sorted(regs), len(off_map),
                 ' '.join('0x%X' % o for o in sorted(off_map))))
        for ex, na, size, cls, exact in score(off_map, classes, args.top, args.strict):
            print('   %-22s size=%-9s 精确命中 %2d/%-2d  成员内 %2d/%-2d   %s'
                  % (cls, size, ex, len(off_map), na, len(off_map),
                     ' '.join('0x%X' % o for o in exact[:10])))
        if args.src:
            size, ms = classes.get(args.src, (None, []))
            names = {n for _, n, _ in ms}
            print('   [原类 %s] size=%s 成员=%s' % (args.src, size, sorted(names)))
        print()


if __name__ == '__main__':
    main()
