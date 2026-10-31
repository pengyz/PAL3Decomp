import json
import struct
import sys

sys.path.insert(0, 'tools')
from diff_byteform_cluster import Exe

d = json.load(open('data/status/s4_diff_detail.json', encoding='utf-8'))
ents = [(u, e) for u, us in d['units'].items() for e in us
        if e['compiled_len'] < e['size']]
exe = Exe('original/PAL3.exe')
pat_start = 0      # 6A FF 68 at start
pat_deep = 0       # 6A FF 68 within first 12B (EBP-SEH variant)
ebp_no_seh = 0     # 55 8B EC start but no SEH marker
other = 0
samples = {'deep': [], 'ebp': []}
for u, e in ents:
    b = exe.head(int(e['va'], 16), 24)
    if b[:3] == b'\x6a\xff\x68' or b[:2] == b'\x6a\xff':
        pat_start += 1
    elif b'\x6a\xff\x68' in b[:12]:
        pat_deep += 1
        if len(samples['deep']) < 5:
            samples['deep'].append((e['name'][:40], e['va'], b[:16].hex()))
    elif b[:3] == b'\x55\x8b\xec':
        ebp_no_seh += 1
        if len(samples['ebp']) < 5:
            samples['ebp'].append((e['name'][:40], e['va'], b[:16].hex()))
    else:
        other += 1
print('len-delta 246 序言形细分:')
print('  首字节 SEH 形:      ', pat_start)
print('  深位 SEH 变体(EBP): ', pat_deep)
print('  EBP 序言无 SEH:     ', ebp_no_seh)
print('  其它:               ', other)
for k, vs in samples.items():
    for s in vs:
        print('  [%s] %s %s | %s' % (k, s[0], s[1], s[2]))
