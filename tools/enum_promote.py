#!/usr/bin/env python3
"""Precise PDB-enum verification: full literal scan + structural exhibits.

PDB 非权威源（版本与 PAL3.exe 不匹配，用户裁定 2026-09-14）。本工具不做
统计计数——聚合频率不是证据。它做两件事：

1. 完整扫描反编译语料，无损索引每个 switch 块的 case 值集合（带 file:line）。
2. 对每个候选枚举给出**结构性 exhibits**：
   - switch 匹配：case 值集合与枚举成员集合的关系（相等=完整证据）
   - 求值器函数：同函数内使用 >=3 个枚举成员值的函数（==/case 均计），
     逐处列出 file:line 原文。

每个断言都有地址，人工复核 = 打开对应位置看原文。没有阈值。

分级（由结构关系推导，非数值评分）：
  SWITCH_EXACT   存在 switch 其 case 集合与枚举成员集合完全相等
  SWITCH_PARTIAL 存在 switch 覆盖 >=3 个成员值（子集关系）
  EVALUATORS     无 switch 但存在 >=3 成员值的求值器函数
  UNPROVEN       无结构性证据（不代表否定——小值枚举若无 switch 需人工）

用法:
  python tools/enum_promote.py            # 全量扫描 + 报告
  python tools/enum_promote.py --name CURSOR_TYPE   # 单枚举明细
报告: data/status/enum_promotion_report.json
"""

import argparse
import glob
import json
import os
import re
import sys
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PDB_EXPORT = os.path.join(ROOT, 'data', 'pdb', 'pdb_export.json')
ENUMS_ANNOT = os.path.join(ROOT, 'data', 'annotations', 'enums.json')
DECOMP_DIR = os.path.join(ROOT, 'asm', 'pal3', 'decomp')
REPORT = os.path.join(ROOT, 'data', 'status', 'enum_promotion_report.json')

SWITCH_RE = re.compile(r'\bswitch\s*\(')
CASE_RE = re.compile(r'\bcase\s+(0x[0-9A-Fa-f]+|\d+)\s*:')
CMP_RE = re.compile(r'(==|!=)\s*(0x[0-9A-Fa-f]+|\d+)\b')


def parse_num(tok):
    try:
        if tok.lower().startswith('0x'):
            return int(tok, 16)
        return int(tok)
    except ValueError:
        return None


def scan_corpus():
    """Full scan: extract every switch block's case-value set and every
    function's comparison-value set, each with file:line exhibits.

    Hex-Rays 输出结构良好（一层缩进的花括号），行级括号深度追踪即可。"""
    switches = []          # [{'file','line','values':set}]
    func_cmp = []          # [{'file','func','line','values':set}] per function
    files = sorted(glob.glob(os.path.join(DECOMP_DIR, '*.json')))
    for path in files:
        fname = os.path.basename(path)
        try:
            d = json.loads(open(path, encoding='utf-8').read())
        except Exception:
            continue
        func = d.get('name', fname)
        lines = d.get('decompiled_c', '').split('\n')

        cur_switches = []   # open switches: [start_line, depth, values]
        func_vals = set()   # cmp values anywhere in this function
        for ln, raw in enumerate(lines, 1):
            code = raw.split('//', 1)[0]
            depth = code.count('{') - code.count('}')

            if SWITCH_RE.search(code):
                cur_switches.append([ln, depth, set()])
            # attribute case labels to the innermost open switch
            m = CASE_RE.search(code)
            if m and cur_switches:
                v = parse_num(m.group(1))
                if v is not None:
                    cur_switches[-1][2].add(v)
            for cm in CMP_RE.finditer(code):
                v = parse_num(cm.group(2))
                if v is not None:
                    func_vals.add(v)

            # close switches whose block has ended
            while cur_switches and depth < 0:
                s = cur_switches.pop()
                if s[2]:
                    switches.append({'file': fname, 'line': s[0],
                                     'values': s[2]})
                depth += 1  # consumed one closing level
        for s in cur_switches:
            if s[2]:
                switches.append({'file': fname, 'line': s[0], 'values': s[2]})
        if func_vals:
            func_cmp.append({'file': fname, 'func': func, 'values': func_vals})
    return switches, func_cmp


def verify_enum(name, members, switches, func_cmp, already):
    """Structural exhibits for one enum. No numeric scoring."""
    mset = set(members)
    exhibits_switch = []
    for s in switches:
        inter = mset & s['values']
        if len(inter) >= 2:
            exhibits_switch.append({
                'file': s['file'], 'line': s['line'],
                'switch_values': sorted(s['values']),
                'members_covered': sorted(inter),
                'exact_match': s['values'] == mset,
                'extras': sorted(s['values'] - mset),
            })
    exact = [e for e in exhibits_switch if e['exact_match']]
    partial = [e for e in exhibits_switch if not e['exact_match']
               and len(e['members_covered']) >= 3]

    evaluators = []
    for fc in func_cmp:
        used = mset & fc['values']
        if len(used) >= 3:
            evaluators.append({'file': fc['file'], 'func': fc['func'],
                               'members_used': sorted(used)})

    if exact:
        grade = 'SWITCH_EXACT'
    elif partial:
        grade = 'SWITCH_PARTIAL'
    elif evaluators:
        grade = 'EVALUATORS'
    else:
        grade = 'UNPROVEN'
    return {'name': name, 'grade': grade,
            'already_in_annotations': already,
            'members': sorted(members),
            'switch_exhibits': (exact + partial)[:8] or exhibits_switch[:8],
            'exact_switch_count': len(exact),
            'evaluators': evaluators[:8]}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--name', help='单枚举明细')
    ap.add_argument('--top', type=int, default=15)
    args = ap.parse_args()

    pdb = json.loads(open(PDB_EXPORT, encoding='utf-8').read())
    enums = [e for e in (pdb.get('enums') or [])
             if e.get('name') and e.get('values')
             and '__unnamed' not in e.get('name', '')
             and '::' not in e.get('name', '')]
    existing = json.loads(open(ENUMS_ANNOT, encoding='utf-8').read())
    print('PDB 候选枚举: %d | 注解层已有: %d' % (len(enums), len(existing)))

    print('完整扫描语料（switch 块 + 比较链，无损）...')
    switches, func_cmp = scan_corpus()
    print('switch 块: %d | 含比较值的函数: %d' % (len(switches), len(func_cmp)))

    report = []
    seen_names = set()
    for e in enums:
        name = e['name']
        if name in seen_names:
            continue
        seen_names.add(name)
        members = set()
        for ms, mv in e['values'].items():
            try:
                members.add(int(mv))
            except (ValueError, TypeError):
                pass
        if not members:
            continue
        if args.name and name != args.name:
            continue
        report.append(verify_enum(name, members, switches, func_cmp,
                                  name in existing))

    from collections import Counter as C
    grades = C(r['grade'] for r in report)
    print('分级: %s' % dict(grades.most_common()))

    order = {'SWITCH_EXACT': 0, 'SWITCH_PARTIAL': 1, 'EVALUATORS': 2,
             'UNPROVEN': 3}
    report.sort(key=lambda r: (order.get(r['grade'], 9), r['name']))
    json.dump({'summary': dict(grades), 'enums': report},
              open(REPORT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('report -> %s' % REPORT)

    shown = 0
    for r in report:
        if r['grade'] in ('SWITCH_EXACT', 'SWITCH_PARTIAL') \
                and shown < args.top:
            print('\n== [%s] %s (exact switches: %d)' % (
                r['grade'], r['name'], r['exact_switch_count']))
            for ex in r['switch_exhibits'][:3]:
                tag = 'EXACT' if ex['exact_match'] else 'partial'
                print('   %s %s:%s cases=%s%s' % (
                    tag, ex['file'], ex['line'], ex['switch_values'],
                    '  extras=%s' % ex['extras'] if ex['extras'] else ''))
            shown += 1


if __name__ == '__main__':
    main()
