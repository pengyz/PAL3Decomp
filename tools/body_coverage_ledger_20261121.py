#!/usr/bin/env python3
"""[体覆盖账本 2026-11-21] 第一性度量: 字节一致要求每个真函数最终有体。

S2 编译普查绿 ≠ 字节一致进度——declaration_only 越多单元越绿越不完整。
本台账对全部注册方法/自由函数按发射意图五分类:

  body            真函数有体(默认发射)
  compiler_regen  编译器再生成形态(伴生dtor/adjustor/compiler_init)——源模型正确即免费再生
  dll_import      导入DLL桩(声明+链接期外部符号, 字节属gbengine.dll)
  debt_pending    挂账真函数(declaration_only且无编译器/DLL豁免证据)——真债, 需逐条清偿
  out_of_domain   skip(非函数目标: CRT/thunk/幻影, 不在语义域)

输出: data/status/body_coverage_ledger.json + 控制台报告
"""
import json
import glob
import re
from collections import defaultdict
from pathlib import Path

REPO = Path(__file__).parent.parent
S = REPO / 'data' / 'annotations'

DLL_HINT = re.compile(r'imported|dll|gbengine|D3DX|链接期', re.I)
COMPILER_HINT = re.compile(r'compiler_init|compiler_generated|静态初始化|编译器', re.I)


def classify_method(m):
    """(类, 地址, 方法) → 五分类"""
    nm = m.get('name') or ''
    flags = str(m.get('flags') or '')
    note = (m.get('name_note') or '') + (m.get('source') or '') + (m.get('sig_note') or '')
    if m.get('type') == 'skip':
        return 'out_of_domain'
    if not m.get('declaration_only'):
        return 'body'
    # declaration_only → 三分
    if nm.startswith('~') or 'dtor' in flags or 'deleting' in flags:
        return 'compiler_regen'
    if 'adjthunk' in nm.lower() or 'thunk' in nm.lower():
        return 'compiler_regen'
    if COMPILER_HINT.search(note):
        return 'compiler_regen'
    if DLL_HINT.search(note):
        return 'dll_import'
    return 'debt_pending'


def classify_fn(v):
    nm = v.get('name') or ''
    note = (v.get('source') or '') + json.dumps(v.get('note') or '', ensure_ascii=False)
    if v.get('type') == 'skip':
        return 'out_of_domain'
    if not v.get('declaration_only'):
        return 'body'
    if re.match(r'compiler_init|compiler_generated', nm) or COMPILER_HINT.search(note + nm):
        return 'compiler_regen'
    if DLL_HINT.search(note + nm) or re.match(r'D3DX', nm):
        return 'dll_import'
    return 'debt_pending'


ledger = {'_doc': '体覆盖账本 2026-11-21 (第一性度量: 每个真函数最终必须有体)',
          'by_class': {}, 'totals': defaultdict(int), 'debt_detail': []}

# 类方法
for fp in sorted(glob.glob(str(S / 'structs' / '*.json'))):
    d = json.loads(Path(fp).read_text(encoding='utf-8'))
    cls = d.get('name') or Path(fp).stem
    row = defaultdict(int)
    for a, m in (d.get('methods') or {}).items():
        k = classify_method(m)
        row[k] += 1
        if k == 'debt_pending':
            ledger['debt_detail'].append(
                {'kind': 'method', 'class': cls, 'addr': a, 'name': m.get('name'),
                 'hint': ((m.get('name_note') or '')[:80])})
    for k in ('body', 'compiler_regen', 'dll_import', 'debt_pending', 'out_of_domain'):
        row[k] = row.get(k, 0)
    row['total'] = sum(row[k] for k in ('body', 'compiler_regen', 'dll_import', 'debt_pending', 'out_of_domain'))
    ledger['by_class'][cls] = row
    for k in ('body', 'compiler_regen', 'dll_import', 'debt_pending', 'out_of_domain'):
        ledger['totals'][k] += row[k]

# 自由函数
fns = json.loads((S / 'functions.json').read_text(encoding='utf-8'))
frow = defaultdict(int)
for a, v in fns.items():
    if not isinstance(v, dict):
        continue
    k = classify_fn(v)
    frow[k] += 1
    if k == 'debt_pending':
        ledger['debt_detail'].append(
            {'kind': 'free', 'class': '<free>', 'addr': a, 'name': v.get('name'),
             'hint': (v.get('source') or '')[:80]})
for k in ('body', 'compiler_regen', 'dll_import', 'debt_pending', 'out_of_domain'):
    frow[k] = frow.get(k, 0)
frow['total'] = sum(frow.values())
ledger['by_class']['<free_functions>'] = frow
for k in ('body', 'compiler_regen', 'dll_import', 'debt_pending', 'out_of_domain'):
    ledger['totals'][k] += frow[k]

# skip_functions.json 目录(非函数目标, 独立计)
sf = json.loads((S / 'skip_functions.json').read_text(encoding='utf-8'))
ledger['skip_catalog'] = len(sf)

T = ledger['totals']
real = T['body'] + T['compiler_regen'] + T['dll_import'] + T['debt_pending']
print('== 体覆盖账本 ==')
print('注册函数总数(语义域): %d' % real)
print('  真函数有体        body           %5d (%.1f%%)' % (T['body'], 100.0 * T['body'] / real))
print('  编译器再生成      compiler_regen %5d (%.1f%%)' % (T['compiler_regen'], 100.0 * T['compiler_regen'] / real))
print('  导入DLL           dll_import     %5d (%.1f%%)' % (T['dll_import'], 100.0 * T['dll_import'] / real))
print('  挂账真函数(债)    debt_pending   %5d (%.1f%%)' % (T['debt_pending'], 100.0 * T['debt_pending'] / real))
print('  非函数目标        out_of_domain  %5d' % T['out_of_domain'])
print('  skip_functions.json 目录(域外): %d' % ledger['skip_catalog'])
print('\n字节一致覆盖进度 = (body+compiler_regen+dll_import)/real = %.1f%%'
      % (100.0 * (T['body'] + T['compiler_regen'] + T['dll_import']) / real))
print('\n挂账 top15:')
for x in ledger['debt_detail'][:15]:
    print('  [%s] %s %s %s | %s' % (x['kind'], x['class'], x['addr'], x['name'], x['hint']))

outp = REPO / 'data' / 'status' / 'body_coverage_ledger.json'
outp.write_text(json.dumps(ledger, ensure_ascii=False, indent=1), encoding='utf-8')
print('\n账本 ->', outp)
