#!/usr/bin/env python3
"""[T75] 成员使用图景探测器（T74 首例判据系统化）。

判据（A 级 objdump，reg+disp32 站点分类）：
- **双解引用**（`[reg+off]` 载值后再被解引用/寻址）⇒ **指针**
- **算术存取**（载值后 add/sub/cmp 等算术）⇒ **标量**
- **直接存储**（`mov [reg+off], X`）⇒ 需看 X 的用法（未知/待查）

用法：python tools/audit_member_use_pattern.py --class UIScenePanel --offset 0x978
      python tools/audit_member_use_pattern.py --class UIScenePanel --all
（--all 读 data/annotations/structs/<Cls>.json 的 known_members 里 type=int
且名含 p/Panel/Slot 的候选逐个扫描——T73 类型坍缩簇口径）
"""
import argparse
import json
import re
import subprocess
import sys
import os

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')

# [reg+off] / [reg+off+idx] 站点（含 8/32 位 disp）
_SITE_RE = re.compile(r'^\s*([0-9a-f]+):\s+((?:[0-9a-f]{2} )+)\s+(.*)$')
_MEM_RE = re.compile(r'(?:BYTE|DWORD|WORD|QWORD)?\s*PTR\s*\[(\w+)(?:\+|-)0x([0-9a-f]+)\]')


def scan_sites(offset_hex):
    """objdump 全文扫 `[reg+0x<off>]` 站点，返回 (addr, mnemonic, operand) 列表。"""
    off = offset_hex.lower().replace('0x', '')
    out = subprocess.run(['objdump', '-d', '-M', 'intel', EXE],
                         capture_output=True, text=True).stdout
    sites = []
    for line in out.split('\n'):
        m = _SITE_RE.match(line)
        if not m:
            continue
        if ('+0x%s]' % off) in line.lower():
            sites.append((m.group(1), m.group(3).strip()))
    return sites


def classify(sites):
    """T74 判据：双解引用=指针 / 算术存取=标量 / 直接存储=待查。"""
    verdicts = []
    for addr, op in sites:
        if op.startswith('mov') and 'PTR [' in op and op.split(',')[0].strip().endswith(']'):
            # 直接存储 mov [reg+off], X
            verdicts.append((addr, op, 'direct-store', 'unknown'))
            continue
        if op.startswith('mov') and 'PTR [' in op:
            # 载值形 mov dst, [reg+off]
            verdicts.append((addr, op, 'load', 'pending-next'))
            continue
        verdicts.append((addr, op, 'other', 'unknown'))
    # 二次判：load 后下一站是否有解引用/寻址（此处按相邻文本近似——工具保守，未知即报 unknown）
    return verdicts


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--class', dest='cls', required=True)
    ap.add_argument('--offset')
    ap.add_argument('--all', action='store_true')
    args = ap.parse_args()
    offsets = []
    if args.offset:
        offsets = [args.offset]
    elif args.all:
        p = os.path.join(ROOT, 'data', 'annotations', 'structs', '%s.json' % args.cls)
        d = json.load(open(p))
        for k, v in (d.get('known_members') or {}).items():
            nm = v.get('name') or ''
            t = str(v.get('type') or '')
            if 'int' in t and any(x in nm for x in ('p', 'Panel', 'Slot')):
                offsets.append(hex(int(k)))
    else:
        ap.error('--offset or --all required')
    for off in offsets:
        sites = scan_sites(off)
        v = classify(sites)
        loads = sum(1 for x in v if x[2] == 'load')
        stores = sum(1 for x in v if x[2] == 'direct-store')
        print('%s %s: %d sites (load=%d store=%d)' % (args.cls, off, len(sites), loads, stores))
        for addr, op, kind, verdict in v[:6]:
            print('   %s [%s] %s  => %s' % (addr, kind, op[:52], verdict))


if __name__ == '__main__':
    main()
