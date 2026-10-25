#!/usr/bin/env python3
"""L1 匹配率多维统计（只读，零管线侵入）。数据源：s4_baseline.json"""
import json, os, collections

base = json.load(open('data/status/s4_baseline.json', encoding='utf-8'))
rows = base['rows']
stats = base['stats']

# ── 函数级 ──
funcs = []
for r in rows:
    f = r['file'].replace('\\','/')
    parts = f.split('/')
    d = parts[2] if len(parts) > 2 else '?'
    funcs.append({'file': f, 'dir': d, 'name': r['name'], 'va': r['va'],
                  'status': r['status'], 'match_pct': r.get('match_pct',0),
                  'size': r.get('size',0)})

l1 = [f for f in funcs if f['status']=='L1']
partial = [f for f in funcs if f['status']=='partial']

# ── cpp 单元级 ──
unit_stats = collections.defaultdict(lambda: {'total':0, 'l1':0, 'partial':0, 'funcs':[]})
for f in funcs:
    u = unit_stats[f['file']]
    u['total'] += 1; u['funcs'].append(f)
    if f['status']=='L1': u['l1'] += 1
    else: u['partial'] += 1

unit_rows = []
for u, s in sorted(unit_stats.items()):
    l1_rate = round(100.0*s['l1']/max(s['total'],1),1)
    avg_match = round(sum(f['match_pct'] for f in s['funcs'])/max(len(s['funcs']),1),1)
    unit_rows.append({'file': u, 'dir': f['dir'], **s, 'l1_rate': l1_rate, 'avg_match_pct': avg_match})

# ── 目录级 ──
dir_stats = collections.defaultdict(lambda: {'total':0,'l1':0,'partial':0,'unit_set':set(),'match_sum':0,'func_count':0})
for ur in unit_rows:
    dd = dir_stats[ur['dir']]
    dd['total'] += ur['total']; dd['l1'] += ur['l1']; dd['partial'] += ur['partial']
    dd['unit_set'].add(ur['file']); dd['match_sum'] += ur['avg_match_pct'] * ur['total']
    dd['func_count'] += ur['total']
dir_rows = []
for dd, s in sorted(dir_stats.items()):
    rate = round(100.0*s['l1']/max(s['total'],1),1)
    avg_m = round(s['match_sum']/max(s['func_count'],1),1)
    dir_rows.append({'dir': dd, 'total': s['total'], 'l1': s['l1'], 'partial': s['partial'], 'l1_rate': rate, 'avg_match_pct': avg_m, 'unit_count': len(s['unit_set'])})

# ── 输出 ──
report = {
    'generated': '2026-10-25',
    'summary': stats,
    'by_directory': sorted(dir_rows, key=lambda x: -x['total']),
    'by_unit': sorted(unit_rows, key=lambda x: (-x['avg_match_pct'], x['file'])),
    'l1_functions': [{'file': f['file'], 'name': f['name'], 'va': f['va']} for f in l1],
    'near_miss': sorted([{'file': f['file'], 'name': f['name'], 'match_pct': f['match_pct'], 'size': f['size']}
                         for f in partial if f['match_pct'] >= 90], key=lambda x: -x['match_pct']),
}
with open('data/status/match_rate_report.json', 'w', encoding='utf-8') as fh:
    json.dump(report, fh, ensure_ascii=False, indent=1)

# ── 控制台 ──
st = stats
print('═══════════════════════════════════════════════')
print('  PAL3 匹配率仪表盘')
print('═══════════════════════════════════════════════')
print('  符号总数: %d' % st.get('symbols',0))
print('  L1 (字节全同): %d (%.1f%%)' % (st.get('match_L1',0), 100.0*st.get('match_L1',0)/max(st.get('symbols',0) or st.get('matched',0)+st.get('unmatched',0),1)))
print('  partial: %d' % st.get('partial',0))
print('  matched 总计: %d / unmatched: %d' % (st.get('matched',0), st.get('unmatched',0)))
print()

print('── 目录级 L1 率 ──')
print('%-14s %5s %5s %6s %7s %8s' % ('目录','单元','L1','partial','L1率','avg%'))
for dr in sorted(dir_rows, key=lambda x:-x['l1_rate']):
    print('%-14s %5d %5d %6d %6.1f%% %7.1f%%' % (
        dr['dir'], dr['unit_count'], dr['l1'], dr['partial'], dr['l1_rate'], dr['avg_match_pct']))
print()

print('── 函数 match 率分布 ──')
buckets = collections.Counter()
for f in partial:
    p = f.get('match_pct',0)
    if p >= 99: buckets['99%+'] += 1
    elif p >= 90: buckets['90-98%'] += 1
    elif p >= 75: buckets['75-89%'] += 1
    elif p >= 50: buckets['50-74%'] += 1
    else: buckets['<50%'] += 1
for b in ['99%+','90-98%','75-89%','50-74%','<50%']:
    print('  %-8s %4d' % (b, buckets.get(b,0)))
print()

print('── 近失 Top 15（partial 中 match 率最高）──')
for f in sorted(partial, key=lambda x: -x.get('match_pct',0))[:15]:
    print('  %5.1f%% %-40s %s' % (f.get('match_pct',0), f['name'][:40], f['file'].split('/')[-1]))

print()
print('saved -> data/status/match_rate_report.json')
