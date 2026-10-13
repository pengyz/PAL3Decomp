#!/usr/bin/env python3
"""[T75/T76] 成员使用图景探测器（T74 判据 + T76 判定层 + F3 路复核修正）。

判据（A 级 objdump，站点分类 + **载值寄存器 dataflow + ≥2 条窗口**）：
- **指针**：载值寄存器在窗口内被二次解引用/寻址，或指针判空（test r,r）
- **标量**：载值寄存器参与算术（add/sub/imul/cmp 等）
- **浮点**：fld/fstp/fmul 等 FP 指令站点
- **内嵌对象**：`lea r,[r+off]` 取址形
- **终判**：多证冲突（pointer 与 scalar 并存）⇒ **undetermined**（禁一票定案）

⚠️ F3 路复核（bfd87ca0）反例教训：(a) 不追踪载值寄存器 (b) 只看紧邻一条
(c) 指针判空 test r,r 落 scalar (d) 一票定案——本版均修。
⚠️ 站点收集（F2-e）：同 disp 无关寄存器会混收——判读层已按寄存器 dataflow 过滤。
"""
import argparse
import json
import re
import subprocess
import os

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')

_SITE_RE = re.compile(r'^\s*([0-9a-f]+):\s+((?:[0-9a-f]{2} )+)\s+(.*)$')
_MEM_RE = re.compile(r'PTR\s*\[(\w+)(?:\+|-)?0x([0-9a-f]+)\]')


def scan_stream(offset_hex):
    """objdump 全文收集指令流，标记含 `[reg+0x<off>]` 站点（3 窗口）。"""
    off = offset_hex.lower().replace('0x', '')
    needle = ('+0x%s]' % off)
    out = subprocess.run(['objdump', '-d', '-M', 'intel', EXE],
                         capture_output=True, text=True).stdout
    stream = []
    for line in out.split('\n'):
        m = _SITE_RE.match(line)
        if m:
            stream.append((m.group(1), m.group(3).strip()))
    sites = []
    for i, (addr, op) in enumerate(stream):
        if needle in op.lower():
            window = [stream[i + j][1] for j in range(1, 4) if i + j < len(stream)]
            sites.append((addr, op, window))
    return sites


def judge(op, window):
    """T76 判定层（F3 修正版）：站点形 + 载值寄存器 dataflow（3 窗口）。"""
    o = op.strip()
    low = o.lower()
    if low.startswith('lea'):
        return 'embedded-object'
    if low.split()[0] in ('fld', 'fst', 'fstp', 'fmul', 'fadd', 'fdiv', 'fsub', 'fild', 'fistp'):
        return 'float'
    dst = o.split(',', 1)[0] if ',' in o else ''
    if low.startswith('mov') and 'PTR [' in dst:
        return 'store'
    if not (low.startswith('mov') and 'PTR [' in o):
        return 'other'
    # 载值形：取载值寄存器，窗口内 dataflow（F2-a/b/c 修正）
    parts = o.split(',', 1)
    reg = parts[0].split()[-1].strip().lower()
    ev = set()
    for w in window:
        wl = w.lower()
        # 指针判空（F2-c）
        if wl.startswith('test') and reg in wl:
            ev.add('pointer')
        # 二次解引用（载值寄存器出现在 [reg] 形）
        if re.search(r'ptr\s*\[\s*' + re.escape(reg) + r'\s*\]', wl):
            ev.add('pointer')
        if wl.startswith('lea') and ('[' + reg) in wl:
            ev.add('embedded-object')
        if wl.startswith(('add', 'sub', 'imul', 'and', 'or ', 'xor', 'cmp')) and reg in wl:
            ev.add('scalar')
    # 多证终判（F2-d：冲突 ⇒ undetermined）
    if ev == {'pointer'}:
        return 'pointer'
    if ev == {'scalar'}:
        return 'scalar'
    if ev == {'embedded-object'}:
        return 'embedded-object'
    if not ev:
        return 'pending'
    return 'undetermined'


def classify(sites):
    return [(a, o, w, judge(o, w)) for a, o, w in sites]


def member_verdicts(cls):
    p = os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % cls)
    d = json.load(open(p))
    out = {}
    for k, v in (d.get('known_members') or {}).items():
        nm = v.get('name') or ''
        t = str(v.get('type') or '')
        if 'int' in t and any(x in nm for x in ('p', 'Panel', 'Slot')):
            off = hex(int(k))
            sites = classify(scan_stream(off))
            counts = {}
            for a, o, w, vd in sites:
                counts[vd] = counts.get(vd, 0) + 1
            if counts.get('pointer') and not counts.get('scalar') and not counts.get('undetermined'):
                final = 'pointer'
            elif counts.get('float'):
                final = 'float'
            elif counts.get('embedded-object') and not counts.get('pointer'):
                final = 'embedded-object'
            elif counts.get('scalar') and not counts.get('pointer') and not counts.get('pending'):
                final = 'scalar'
            else:
                final = 'undetermined'
            out[off] = (nm, final, counts)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--class', dest='cls', required=True)
    ap.add_argument('--offset')
    ap.add_argument('--all', action='store_true')
    ap.add_argument('--only', dest='only')
    args = ap.parse_args()
    if args.offset:
        sites = classify(scan_stream(args.offset))
        counts = {}
        for a, o, w, vd in sites:
            counts[vd] = counts.get(vd, 0) + 1
        print('%s %s: %d sites %s' % (args.cls, args.offset, len(sites), counts))
        for a, o, w, vd in sites[:8]:
            print('   %s [%s] %s | next: %s' % (a, vd, o[:46], (w[0] if w else '')[:30]))
    else:
        for off, (nm, final, counts) in member_verdicts(args.cls).items():
            print('%s %s (%s): %s => **%s**' % (args.cls, off, nm, counts, final))


if __name__ == '__main__':
    main()
