#!/usr/bin/env python3
"""成员全用法形扫描（P0-6 纪律）——改型前必扫。

## 为什么（2026-10-21 R51 教训）

59 条弱型改型（int→struct 31 · float→struct 16）致 **+617 错误**。
根因：opcode 证据只查一种用法形（lea+call 子对象），未查其他（算术/比较/赋值）。
⇒ **单点 opcode 证据 ≠ 全用法证据**。改型是「改变语义」，须证「语义无歧义」。

## 7 种用法形（全扫）

| 用法形 | opcode 特征 | 推断型 |
|---|---|---|
| arith  | add/sub/imul/idiv | int |
| cmp    | cmp/test | int |
| assign | mov reg,addr / mov addr,reg | 视数据 |
| addr   | lea + push（取址传参）| 结构体指针 |
| float  | fld/fstps/fadd/fmul/fdiv | float/double |
| bitop  | and/or/xor | int/标志 |
| indirect | call *(%reg) | 对象指针 |

## 判据

  **用法单一**（如仅 float）  ⇒ ✅ 可改型（float/double）
  **用法混合**（arith + addr）⇒ ❌ **冻结**（可能 union/位面复用）
  **零特征**                  ⇒ ❌ 冻结

## 用法
    python3 tools/member_usage_scan.py --cls RoleSystem --offset 0x4dc
    python3 tools/member_usage_scan.py --cls RoleSystem --offset 0x4dc --json

R15 单测见 tests/test_member_usage_scan.py
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys
from collections import Counter

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PAL3 = os.path.join(ROOT, 'original', 'PAL3.exe')

_ARITH = re.compile(r'\b(add|sub|imul|idiv|mul|div|inc|dec|neg)\b')
_CMP = re.compile(r'\b(cmp|test|comis[sd]|ucomis[sd])\b')
# [修 2026-10-21] 去 trailing \b —— fstps/flds 的 s 后缀被 \b 拦截
_FLOAT = re.compile(r'\b(fld|fstp|fild|fistp|fadd|fsub|fmul|fdiv|fcom|fucom|fchs|fabs|fsqrt|fsin|fcos)')
_BITOP = re.compile(r'\b(and|or|xor|not|shl|shr|sar|rol|ror)\b')
_LEA = re.compile(r'\blea\b')
_MOV = re.compile(r'\bmov[a-z]*\b')
_CALLIND = re.compile(r'\bcall\b.*\*')


def classify_instruction(ins):
    """单条指令的用法形分类（可多重）。"""
    forms = set()
    if _FLOAT.search(ins): forms.add('float')
    if _ARITH.search(ins): forms.add('arith')
    if _CMP.search(ins): forms.add('cmp')
    if _BITOP.search(ins): forms.add('bitop')
    if _LEA.search(ins): forms.add('addr')
    if _CALLIND.search(ins): forms.add('indirect')
    if _MOV.search(ins): forms.add('assign')
    return forms


def scan_member_usage(cls_name, member_offset, register='esi', objdump_path=PAL3):
    """扫某类方法内对 `0xOFFSET(%reg)` 的全部用法形。

    返回 {'forms': {form: count}, 'samples': {form: [addr,...]}, 'total_hits': int}
    """
    # 找该类方法地址（decomp 反查，IDA 边界可信）
    addrs = []
    for fp in glob.glob(os.path.join(ROOT, 'asm', 'pal3', 'decomp', '*.json')):
        try:
            with open(fp, encoding='utf-8') as fh:
                j = json.load(fh)
        except (OSError, ValueError):
            continue
        if f'{cls_name} *this' in str(j.get('signature', '')):
            a = j.get('address')
            if a:
                addrs.append(int(str(a), 16))
    if not addrs:
        return {'error': f'no methods for {cls_name}', 'forms': {}, 'samples': {}, 'total_hits': 0}
    lo, hi = min(addrs), max(addrs) + 0x2000
    off_hex = f'{member_offset:02x}' if isinstance(member_offset, int) else str(member_offset).lower().replace('0x', '')
    # [修 2026-10-21] register 传 'esi' 时不应再加 %e 前缀（会成 %eesi）
    # [P0-8 2026-10-21] 固定偏移 + 比例变址双支持
    # 固定偏移：0xNN(%esi)  |  比例变址：0xNN(%esi,%eax,4) / (%esi,%eax,8) 形（数组元素）
    pat = re.compile(
        r'0x0*' + re.escape(off_hex) + r'\(%' + re.escape(register)
        + r'(?:,%e[a-z]+,[1248])?\)', re.I)
    # 数组元素型标记（若命中 scaled 形）
    scaled_hit = re.compile(r'\(%' + re.escape(register) + r',%e[a-z]+,[1248]\)', re.I)
    forms = Counter()
    samples = {}
    total = 0
    scaled_count = 0
    try:
        r = subprocess.run(['objdump', '-d', f'--start-address=0x{lo:X}', f'--stop-address=0x{hi:X}', objdump_path],
                           capture_output=True, text=True, timeout=300)
    except Exception as e:
        return {'error': str(e), 'forms': {}, 'samples': {}, 'total_hits': 0}
    for line in r.stdout.split('\n'):
        if not pat.search(line):
            continue
        total += 1
        if scaled_hit.search(line):
            scaled_count += 1
        ins = line.split('\t')[-1] if '\t' in line else line
        addr_m = re.match(r'\s*([0-9a-f]+):', line)
        addr = addr_m.group(1) if addr_m else '?'
        for form in classify_instruction(ins):
            forms[form] += 1
            samples.setdefault(form, []).append(f'0x{addr} {ins.strip()[:50]}')
    return {'forms': dict(forms), 'samples': {k: v[:3] for k, v in samples.items()},
            'total_hits': total, 'scaled_index_hits': scaled_count}


def usage_verdict(forms):
    """按用法形组合判改型安全性。"""
    if not forms:
        return 'NONE'
    keys = set(forms)
    if keys == {'float'}:
        return 'SINGLE_FLOAT'
    if keys == {'arith'} or keys == {'arith', 'cmp'} or keys == {'cmp'}:
        return 'SINGLE_ARITH'
    if keys == {'addr'} or keys == {'addr', 'assign'}:
        return 'SINGLE_ADDR'
    if keys == {'assign'}:
        return 'SINGLE_ASSIGN'
    return 'MIXED'


def safe_type_for(verdict):
    return {
        'SINGLE_FLOAT': 'float',
        'SINGLE_ARITH': 'int',
        'SINGLE_ADDR': 'void *',   # 结构体指针，具体型待补
        'SINGLE_ASSIGN': None,      # 单赋值不足以定型
        'MIXED': None,
        'NONE': None,
    }.get(verdict)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--cls', required=True)
    ap.add_argument('--offset', required=True)
    ap.add_argument('--register', default='esi')
    ap.add_argument('--json', action='store_true')
    args = ap.parse_args()
    try:
        off = int(args.offset, 16) if args.offset.startswith('0x') else int(args.offset)
    except ValueError:
        off = args.offset
    res = scan_member_usage(args.cls, off, args.register)
    v = usage_verdict(res['forms'])
    out = {'cls': args.cls, 'offset': args.offset, 'register': args.register,
           'usage_forms': res['forms'], 'samples': res['samples'],
           'total_hits': res['total_hits'], 'usage_verdict': v,
           'proposed_type': safe_type_for(v),
           'change_kind': 'retype' if safe_type_for(v) else 'freeze'}
    if args.json:
        print(json.dumps(out, ensure_ascii=False, indent=2))
    else:
        print(f'{args.cls}+{args.offset} (%{args.register}): {res["total_hits"]} 命中')
        print(f'  用法形: {res["forms"]}')
        print(f'  判定: {v} → {out["change_kind"]} ({out["proposed_type"]})')
        for f, s in res['samples'].items():
            print(f'  {f}: {s}')
    return 0


if __name__ == '__main__':
    sys.exit(main())
