"""按**二进制访问**重建一个类的成员布局（只读）。

## 为什么需要它
逐案核对时反复出现同一类问题：类注解的 `binary_size` / `known_members` 与二进制
实际访问不符（实例：`UIProgressBar` 声明 244 字节、成员只到 +220，而它的 ctor
初始化到 +304，`FindChildByName` 在注解声明"指针"的 +152/+156 上做 `flds`/`fstps`）。
盯着编译错误或伪代码修是治标；正确路径是**先按真实访问把布局画出来**。

## 做法
对类（含其主基类）的每个方法：
  1. 反汇编**整个函数体**（用 decomp JSON 的 `size_bytes` 界定，遇 `ret` 停）；
  2. 做 `this` 指针的数据流跟踪：`%ecx` 入口为 `this+0`；`mov %r,%s` 传播、
     `lea X(%r),%s` 记 `this+X`（≠0 的后续访问**不属于本对象**，跳过）、
     写寄存器即失效、`call` 后 `%eax/%ecx/%edx` 失效（callee-saved 保留）；
  3. 收集 `X(%r)` 且 `%r == this+0` 的访问，按助记符判**宽度**；
  4. 按偏移聚合，并与注解里同偏移的成员对照。

宽度来自 AT&T 助记符后缀（x87 的 `flds/fsts`=4、`fldl/fstpl`=8、`fildl/fistpl`=4、
`filds/fistps`=2；`movb`=1、`movw`=2、其余 32 位=4）。这是**启发式**，
输出里保留原始助记符以便人工复核。

## 用法（只读，不改任何东西）
    python3 tools/access_map.py UIProgressBar [--no-base]
"""
import argparse
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools.scan_misattribution import (  # noqa: E402
    _objdump, _find_member, load_decomp, load_structs, norm_va, sizeof_type,
)

FLOAT4 = re.compile(r'^f(ld|st|stp|add|sub|mul|div|com|comp)s$')
FLOAT8 = re.compile(r'^f(ld|st|stp|add|sub|mul|div|com|compl|comp)l$')
FILD4 = ('fildl', 'fistpl', 'fistl', 'fisttpl')
FILD2 = ('filds', 'fistps', 'fists')
BYTE_M = re.compile(r'^(mov[bzsw]|add|sub|or|and|xor|cmp|test|inc|dec|neg|not|shl|shr|sar|set)'
                    r'(b|zbl|sbl|zbl)$|^movb$|^movzbl$|^movsbl$|^set')
WORD_M = re.compile(r'^(mov|add|sub|or|and|xor|cmp|test|inc|dec)w$|^movzwl$')


REG8 = re.compile(r'^%(a|b|c|d)[lh]$|^%(s|d|b|spl|sil|dil|bpl)l$|^%r\d+b$')
REG16 = re.compile(r'^%(ax|bx|cx|dx|si|di|bp|sp)$|^%r\d+w$')


def _reg_width(r):
    if REG8.match(r):
        return 1
    if REG16.match(r):
        return 2
    return 4


def mem_width(mnem, ops=''):
    """(宽度, 说明)；宽度 None = 未知（调用方应人工复核）。

    ️ 不能只看助记符：`88 91 ee 00 00 00  mov %dl,0xee(%ecx)` 里 objdump 打印的是
    裸 `mov`，宽度由**源寄存器**（`%dl`=1B）决定，不是 4B。
    """
    m = mnem.lower()
    if m in ('mov', 'movl'):
        mm = re.match(r'(%[a-z0-9]+)\s*,', ops)
        if mm:
            return _reg_width(mm.group(1)), 'reg-implied' 
    if FLOAT8.match(m):
        return 8, 'x87 double'
    if FLOAT4.match(m):
        return 4, 'x87 float'
    if m in FILD4:
        return 4, 'x87 int32'
    if m in FILD2:
        return 2, 'x87 int16'
    if WORD_M.match(m):
        return 2, 'word'
    if BYTE_M.match(m):
        return 1, 'byte'
    return 4, 'dword'


_CALLED = ('%eax', '%ecx', '%edx')


def access_map_for_method(va, this_map=None):
    """返回 [(offset, width, mnemo, addr)]，只含对**本对象**（this+0）的访问。"""
    out = _objdump(va, va + 0x10000)   # 由调用方保证 size 正确；这里再截到 ret
    lines = []
    for l in out.splitlines():
        m = re.match(r'\s+([0-9a-f]+):\s+((?:[0-9a-f]{2} )+)\s*(\S+)\s*(.*)$', l)
        if m:
            lines.append((m.group(1), m.group(3), m.group(4)))
    res = []
    tmap = {'%ecx': 0}          # 寄存器 -> 相对 this 的偏移；None = 未知
    for addr, mnem, ops in lines:
        if mnem.startswith('ret'):
            break
        if mnem == 'call' or mnem == 'jmp':
            if mnem == 'call':
                for r in _CALLED:
                    if r in tmap:
                        del tmap[r]
            continue
        # 收集本指令对 this+0 的访问（**先读后写**）
        for mm in re.finditer(r'0x([0-9a-f]+)\((%[a-z0-9]+)(?:,[^)]*)?\)', ops):
            off, reg = int(mm.group(1), 16), mm.group(2)
            if tmap.get(reg) == 0:
                w, _ = mem_width(mnem, ops)
                res.append((off, w, mnem, addr))
        # 更新数据流：**只有存在目标寄存器时**才算写。
        # ⚠️ 曾错把"操作数里最后一个寄存器"当目标，于是 `flds 0x7c(%ecx)`
        # 这类**纯读**也被判成写 `%ecx`，指针跟踪立刻断掉（真值校验抓出）。
        mm = re.match(r'%[a-z0-9]+,\s*(%[a-z0-9]+)$', ops)
        if mm and mnem in ('mov', 'movl'):
            tmap[mm.group(1)] = tmap.get(re.match(r'(%[a-z0-9]+)', ops).group(1))
            continue
        mm = re.match(r'0x([0-9a-f]+)\((%[a-z0-9]+)(?:,[^)]*)?\),\s*(%[a-z0-9]+)$', ops)
        if mm and mnem == 'lea':
            base = tmap.get(mm.group(2))
            tmap[mm.group(3)] = None if base is None else base + int(mm.group(1), 16)
            continue
        mm = re.search(r',\s*(%[a-z0-9]+)$', ops)
        if mm and mm.group(1) in tmap:      # 目标寄存器被覆盖
            tmap[mm.group(1)] = None
    return res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('cls')
    ap.add_argument('--no-base', action='store_true', help='不扫基类方法')
    ap.add_argument('--out', default=None)
    args = ap.parse_args()

    S = load_structs()
    load_decomp()
    info = S.get(args.cls)
    if not info:
        print('无此类的 annotation: %s' % args.cls)
        return 1

    classes = [args.cls]
    if not args.no_base:
        c = args.cls
        for _ in range(8):
            bs = (S.get(c) or {}).get('bases') or []
            if not bs:
                break
            classes.append(bs[0])
            c = bs[0]

    from tools.scan_misattribution import FUNC_SIZE
    agg = {}
    for cls in classes:
        for k, v in sorted((S[cls]['methods'] or {}).items()):
            a = norm_va(k)
            sz = FUNC_SIZE.get(a, 0)
            if sz <= 0:
                continue
            for off, w, mnem, addr in access_map_for_method(a):
                agg.setdefault(off, []).append((w, mnem, cls, v.get('name'), addr))

    print('=== %s  size=%s  base=%s  扫描类=%s ==='
          % (args.cls, info['size'], info['bases'], classes))
    declared = {}
    for cls in classes:
        for mn, (off, ty) in (S[cls]['members'] or {}).items():
            declared.setdefault(off, []).append((mn, ty, cls, sizeof_type(S, ty)))
    print('--- 按偏移的真实访问 vs 注解 ---')
    for off in sorted(set(agg) | set(declared)):
        acc = agg.get(off, [])
        dec = declared.get(off, [])
        widths = sorted({w for w, _, _, _, _ in acc})
        dtxt = '; '.join('%s:%s(%s)' % (mn, ty, sz if sz is not None else '?')
                         for mn, ty, _, sz in dec) or '(无成员)'
        flag = ''
        if dec and widths and all(w != (sz or -1) for w in widths for _, _, _, sz in dec):
            flag = '  <== 宽度与声明不符'
        if not dec and acc:
            flag = '  <== 未登记成员'
        print('  +%-5d 访问=%-14s %-30s %s%s'
              % (off, widths or '-',
                 ','.join(sorted({m for _, m, _, _, _ in acc}))[:30], dtxt, flag))
    print()
    print('--- 注解里声明的偏移，二进制中**从未访问** ---')
    for off in sorted(declared):
        if off not in agg:
            print('  +%-5d %s' % (off, declared[off][0][0]))

    if args.out:
        json.dump({str(k): v for k, v in agg.items()},
                  open(os.path.join('data', 'status', args.out), 'w', encoding='utf-8'),
                  ensure_ascii=False, indent=1)
        print('\n访问图 -> data/status/%s' % args.out)
    return 0


if __name__ == '__main__':
    sys.exit(main())