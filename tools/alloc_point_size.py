#!/usr/bin/env python3
"""分配点分析：从指令级 asm 取"对象真实尺寸"的二进制证据（A 级）。

判据（MSVC 6 惯用法，逐条可在 asm 里核对）::

    push    <N>              ; Size
    call    ??2@YAPAXI@Z     ; operator new(uint)
    add     esp, 4
    ...                      ; 判空 / 存栈槽
    mov     ecx, eax         ; this = 刚分配的对象
    call    <ctor>           ; ⇒ sizeof(ctor 所属类) == N

为什么不是"扫一遍 operator new 的实参就完事"：`operator new(N)` 的 N 是
**被分配对象**的尺寸，不是"调用它的那个函数所属类"的尺寸（2026-09-19 §49.1
的失败尝试就栽在这里：`MiniGame3` 里的 `operator new(0x118)` 分配的是别的对象）。
唯一可靠的挂钩是 **紧随其后的 ctor 调用**。

用法::

    python tools/alloc_point_size.py --scan                 # 全部 (size, ctor) 对
    python tools/alloc_point_size.py --ctor 0x51D6E0        # 指定 ctor 的分配点
    python tools/alloc_point_size.py --callers 0x52FC60     # 函数调用点 + ecx 来源
    python tools/alloc_point_size.py --class MatrixStack    # 用注解里的 ctor 反查
    python tools/alloc_point_size.py --scan --json out.json
"""
import argparse
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM = os.path.join(ROOT, 'original', 'PAL3.exe.asm')

OPERATOR_NEW = ('??2@YAPAXI@Z', '??_U@YAPAXI@Z')
PROC_RE = re.compile(r'^([A-Za-z_?$@][\w?$@]*)\s+proc\s+near')


def _imm(token):
    """把 IDA 立即数写成 int。多位十六进制带 `h` 后缀（项目已实测），也接受 0x。"""
    t = token.strip().rstrip(',')
    if not t:
        return None
    neg = t.startswith('-')
    if neg:
        t = t[1:]
    low = t.lower()
    if low.endswith('u'):
        t = t[:-1]
        low = t.lower()
    val = None
    if low.endswith('h') and len(t) > 1 and re.fullmatch(r'[0-9][0-9a-fA-F]*h', t):
        val = int(t[:-1], 16)
    elif low.startswith('0x'):
        val = int(t, 16)
    elif re.fullmatch(r'\d+', t):
        val = int(t)
    if val is None:
        return None
    return -val if neg else val


def _instr(line):
    """返回 (mnemonic, operands) 或 None（跳过空行/纯注释/标签）。"""
    s = line.split(';')[0].strip()
    if not s or s.endswith(':'):
        return None
    parts = s.split(None, 1)
    if not parts:
        return None
    return parts[0], (parts[1].strip() if len(parts) > 1 else '')


def load_functions(path=ASM):
    """→ [(name, start_line_idx, end_line_idx)]"""
    with open(path, encoding='utf-8', errors='replace') as fh:
        lines = fh.read().split('\n')
    funcs = []
    for i, ln in enumerate(lines):
        m = PROC_RE.match(ln)
        if m:
            if funcs:
                funcs[-1][2] = i
            funcs.append([m.group(1), i, len(lines)])
    return lines, funcs


def _slot_from_eax(operand):
    """`[ebp+var_4]` / `[esp+34h+var_20]` 这类栈槽文本（用于 eax 中转识别）。"""
    m = re.search(r'\[([^\]]+)\]', operand)
    return m.group(1).strip() if m else None


def find_allocs(lines, funcs, max_back=8, max_fwd=16):
    """全量扫描分配点 → [{size, ctor, func, line, ctor_call_line, via_slot}]"""
    out = []
    for name, s, e in funcs:
        for i in range(s, e):
            ins = _instr(lines[i])
            if not ins:
                continue
            mn, ops = ins
            if mn != 'call' or not any(t in ops for t in OPERATOR_NEW):
                continue
            # 1) 往回找 push <imm>
            size = None
            for j in range(i - 1, max(0, i - max_back) - 1, -1):
                ins2 = _instr(lines[j])
                if not ins2:
                    continue
                if ins2[0] == 'push':
                    cand = _imm(ins2[1].split()[0])
                    if cand is not None:
                        size = cand
                    break
                if ins2[0] in ('call', 'retn', 'ret'):
                    break
            if size is None:
                continue
            # 2) 往后找 `mov ecx, eax`（或经栈槽中转）再找第一个 call
            slot = None
            ecx_from_eax = False
            ctor = None
            ctor_line = None
            for j in range(i + 1, min(len(lines), i + max_fwd)):
                ins2 = _instr(lines[j])
                if not ins2:
                    continue
                mn2, ops2 = ins2
                if mn2 == 'mov' and ops2.replace(' ', '').startswith('[') is False:
                    dst, _, src = ops2.partition(',')
                    dst, src = dst.strip(), src.strip()
                    if dst == 'ecx' and src == 'eax':
                        ecx_from_eax = True
                    elif src == 'eax' and _slot_from_eax(dst):
                        slot = _slot_from_eax(dst)
                    elif dst == 'ecx' and slot and _slot_from_eax(src) == slot:
                        ecx_from_eax = True
                elif mn2 == 'call':
                    if any(t in ops2 for t in OPERATOR_NEW):
                        continue
                    if ecx_from_eax:
                        ctor = ops2.split()[0]
                        ctor_line = j
                    break
            out.append({
                'size': size,
                'ctor': ctor,
                'via_slot': bool(ecx_from_eax and slot),
                'func': name,
                'line': i + 1,
                'ctor_call_line': (ctor_line + 1) if ctor_line else None,
                'raw': lines[i].strip()[:90],
                'push_raw': lines[i - 1].strip()[:60] if i else '',
            })
    return out


def addr_of(sym):
    m = re.match(r'^(?:sub|loc|unknown_libname)?_?([0-9A-Fa-f]{6,8})$', sym or '')
    return int(m.group(1), 16) if m else None


def ctor_addrs_of_class(cls):
    """从注解里取"构造该类的函数"地址集合。"""
    p = os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % cls)
    if not os.path.exists(p):
        return {}
    j = json.load(open(p, encoding='utf-8'))
    found = {}
    for a, m in (j.get('methods') or {}).items():
        nm = (m or {}).get('name') or ''
        if nm == cls or nm.startswith('~' + cls):
            found[int(a, 16)] = nm
    return found


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--scan', action='store_true')
    ap.add_argument('--ctor', action='append', default=[])
    ap.add_argument('--class', dest='classes', action='append', default=[])
    ap.add_argument('--callers', action='append', default=[])
    ap.add_argument('--near', action='append', default=[],
                    help='对调用该地址的函数，列出同函数内的分配点（用于没有 ctor 注解的类）')
    ap.add_argument('--json')
    args = ap.parse_args()

    lines, funcs = load_functions()
    print('[asm] %d 行 / %d 个函数' % (len(lines), len(funcs)), file=sys.stderr)

    if args.near:
        want = {}
        for c in args.near:
            want[int(c, 16) if c.lower().startswith('0x') else int(c)] = c
        allocs = find_allocs(lines, funcs)
        for a in sorted(want):
            sites = []
            for name, s, e in funcs:
                for i in range(s, e):
                    ins = _instr(lines[i])
                    if ins and ins[0] == 'call' and addr_of(ins[1].split()[0]) == a:
                        sites.append((name, i + 1))
            print('== 0x%X：%d 个调用点' % (a, len(sites)))
            for name, ln in sites:
                # 该调用点所在函数的分配点
                same = [x for x in allocs if x['func'] == name]
                print('   调用点 %s(行 %d)  →  同函数分配点 %d 个' % (name, ln, len(same)))
                for x in same:
                    print('       size=0x%-6X (%d)  行 %d  ctor=%s  %s'
                          % (x['size'], x['size'], x['line'], x['ctor'], x['push_raw']))
            print()
        return

    if args.callers:
        want = set()
        for c in args.callers:
            want.add(int(c, 16) if c.lower().startswith('0x') else int(c))
        for name, s, e in funcs:
            for i in range(s, e):
                ins = _instr(lines[i])
                if not ins or ins[0] != 'call':
                    continue
                tgt = addr_of(ins[1].split()[0])
                if tgt in want:
                    ctx = [lines[k].rstrip()[:96] for k in range(max(0, i - 6), i + 1)
                           if _instr(lines[k])]
                    print('=== 调用 0x%X @ %s(行 %d) ===' % (tgt, name, i + 1))
                    for c in ctx:
                        print('   ', c)
        return

    allocs = find_allocs(lines, funcs)
    print('[asm] 分配点 %d 个（有 ctor 挂钩的 %d 个）'
          % (len(allocs), sum(1 for a in allocs if a['ctor'])), file=sys.stderr)

    targets = {}
    for c in args.ctor:
        targets[int(c, 16) if c.lower().startswith('0x') else int(c)] = c
    for cls in args.classes:
        for a, nm in ctor_addrs_of_class(cls).items():
            targets[a] = '%s::%s' % (cls, nm)

    if targets:
        for a in sorted(targets):
            hits = [x for x in allocs if addr_of(x['ctor']) == a]
            print('== %s (0x%X): %d 个分配点' % (targets[a], a, len(hits)))
            for h in hits:
                print('   size=%-8d 0x%-6X  %s  (行 %d → ctor 行 %s)'
                      % (h['size'], h['size'], h['func'], h['line'], h['ctor_call_line']))
                print('       %s' % h['push_raw'])
        if not args.scan:
            return

    if args.scan:
        from collections import Counter
        cnt = Counter((a['size'], a['ctor']) for a in allocs if a['ctor'])
        print('\n== 全部 (size, ctor) 对，按 size 排序 ==')
        for (size, ctor), n in sorted(cnt.items()):
            print('  size=%-8d 0x%-6X ctor=%-22s x%d' % (size, size, ctor, n))

    if args.json:
        json.dump(allocs, open(args.json, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
        print('[out] %s' % args.json, file=sys.stderr)


if __name__ == '__main__':
    main()
