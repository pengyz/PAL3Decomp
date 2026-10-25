import json, collections, os

BS = chr(92)
det = json.load(open(os.path.join('data','status','s4_diff_detail.json'), encoding='utf-8'))
base = json.load(open(os.path.join('data','status','s4_baseline.json'), encoding='utf-8'))

rows_by_key = {}
for r in base['rows']:
    rows_by_key[(r['file'], r.get('name',''), r.get('va',''))] = r

sem_funcs = []
non_sem_funcs = []
for unit, fns in sorted(det['units'].items()):
    u = unit.replace(BS, '/')
    dd = u.split('/')[2] if len(u.split('/'))>2 else '?'
    for f in fns:
        nd = f.get('n_diff', 0)
        size = f.get('size', 0)
        cl = f.get('compiled_len', 0)
        rate = round(100.0*max(size-nd,0)/max(size,1), 1) if size else 0
        is_sem = f.get('semantic_match', False)
        e = {
            'unit': u.split('/')[-1], 'dir': dd, 'name': f.get('name',''),
            'size': size, 'cl': cl, 'n_diff': nd,
            'match_pct': rate, 'byte_rate': rate,
            'is_semantic': is_sem,
        }
        if is_sem:
            sem_funcs.append(e)
        else:
            non_sem_funcs.append(e)

# 分段
tiers = [(0,5),(5,10),(10,20),(20,30),(30,50),(50,70),(70,90),(90,101)]
print('=== 非语义 partial 字节匹配率分布 ===')
for lo,hi in tiers:
    c = sum(1 for f in non_sem_funcs if lo <= f['byte_rate'] < hi)
    print('  %d-%d%%: %d' % (lo,hi,c))

# 目录级
dir_agg = collections.defaultdict(lambda: {'n':0, 'low':0, 'bytes':0, 'low_bytes':0})
for f in non_sem_funcs:
    dir_agg[f['dir']]['n'] += 1
    dir_agg[f['dir']]['bytes'] += f['size']
    dir_agg[f['dir']]['low_bytes'] += f['n_diff']
    if f['byte_rate'] < 30: dir_agg[f['dir']]['low'] += 1

print()
print('=== 目录级平均字节匹配率 ===')
for dd in sorted(dir_agg.keys(), key=lambda d: -dir_agg[d]['n']):
    s = dir_agg[dd]
    rate = round(100.0*(1 - s['low_bytes']/max(s['bytes'],1)), 1)
    print('  %-14s %3d fn  %3d low(<30%%)  rate %.1f%%' % (dd, s['n'], s['low'], rate))

# 最低 30 个
non_sem_funcs.sort(key=lambda x: x['byte_rate'])
print()
print('=== 最低 30 个函数 ===')
for f in non_sem_funcs[:30]:
    print('  %5.1f%% %-45s %s (nd=%d)' % (f['byte_rate'], f['name'][:45], f['unit'], f['n_diff']))

out = {'sem': sem_funcs, 'non_sem': non_sem_funcs}
with open(os.path.join('data','status','_sem_analysis.json'), 'w', encoding='utf-8') as fh:
    json.dump(out, fh, ensure_ascii=False, indent=1)
print('\nsaved')
