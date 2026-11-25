#!/usr/bin/env python3
"""GetInstance 体解码 + 442 调用点前向扫真方法全集"""
import sys, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_getinstance_members_20261125.json'
GI = 0x53df70
report = {}
# ① GetInstance 体
f = ida_funcs.get_func(GI)
body = []
cur = f.start_ea
while cur < f.end_ea:
    body.append('%s  %s' % (hex(cur), (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()))
    cur = idc.next_head(cur, f.end_ea)
report['gi_body'] = body

# ② 调用点前向扫: GetInstance 后第一个 call
member_calls = collections.Counter()
sites = list(idautils.CodeRefsTo(GI, 0))
for site in sites:
    cur = site
    for _ in range(12):
        cur = idc.next_head(cur, site + 0x100)
        if cur == idc.BADADDR:
            break
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        m = re.match(r'call\s+(.+)$', t)
        if m:
            tgt = m.group(1)
            member_calls[tgt[:70]] += 1
            break
        if re.match(r'mov\s+ecx,\s*e[a-z]{2}', t) is None and t.startswith('mov') and 'p' not in t.split(' ')[0]:
            pass
report['total_gi_sites'] = len(sites)
report['forward_members'] = dict(member_calls.most_common(40))

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('GetInstance 体:')
for b in body[:8]:
    print(' ', b)
print('调用点 %d, 前向真方法 %d 个:' % (len(sites), len(member_calls)))
for k, v in member_calls.most_common(25):
    print('   %3d  %s' % (v, k))
idapro.close_database(False)
