#!/usr/bin/env python3
"""probe_ccbcamcontrol_census_20261126.py — CCBCamControl 430KB 成员普查(W2 P0 首战)。

CEffMgr 模式三证:
  1. ctor/工厂体解码: Create@0x508230(operator new 尺寸字面量) + Init@0x5054b0
     写序 + dtor@0x5081d0/0x5081e0 释放面(delete → 指针成员+池结构显形)
  2. 全 33 方法 this-form disp 普查: [base+idx*scale+disp] 全形态,
     聚类落洞区 [0x14,0x34)[0x40,0xec)[0x1c8,0x260)[0x43c,0x984)
     [0x2598,0x5558)[0x555c,0x3cfb8)[0x4af58,0x5d9ec)[0x5e0a4,0x5f360)
     [0x60af8,0x68fb0)
  3. 洞区访问形: 每洞列出访问方法×disp×读写形态 → 成员边界从 disp 聚类显形
"""
import sys, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, ida_bytes

SIZE = 0x690B0
OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_ccbcamcontrol_census_20261126.json'
HOLES = [(0x14,0x34),(0x40,0xec),(0x1c8,0x260),(0x43c,0x984),
         (0x2598,0x5558),(0x555c,0x3cfb8),(0x4af58,0x5d9ec),
         (0x5e0a4,0x5f360),(0x60af8,0x68fb0),(0x0,0x8)]
CC = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/CCBCamControl.json',
                    encoding='utf-8'))
METHODS = {int(a,16): str(m.get('name') or a) for a, m in (CC.get('methods') or {}).items()}

# 内存操作全形态: [base] [base+disp] [base+idx] [base+idx*scale+disp]
MEM_RX = re.compile(r'\[(e[a-z]{2}|cx|si|di)(?:\+(e[a-z]{2}|cx|si|di)(?:\*([1248]))?)?'
                    r'(\+(0[xX][0-9A-Fa-f]+|[0-9A-Fa-f]{1,8}h?))?\]')
IMM_RX = re.compile(r'\+([0-9A-Fa-f]{1,8})h?(\]|$)')

def disasm_range(f, cap=6000):
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < cap:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        yield cur, t
        cur = idc.next_head(cur, f.end_ea)
        n += 1

report = {}

# ---- 1. Create 工厂: new 尺寸 + 调用链 ----
create_ea = 0x508230
f = ida_funcs.get_func(create_ea)
seq = []
if f:
    for cur, t in disasm_range(f, 200):
        seq.append((hex(cur), t))
report['create_body'] = seq

# ---- 2. dtor 释放面 ----
for dea, tag in ((0x5081d0, 'dtor_d0'), (0x5081e0, 'dtor_e0')):
    f = ida_funcs.get_func(dea)
    if not f: continue
    hits = []
    for cur, t in disasm_range(f, 1500):
        if re.search(r'(call|jmp)', t) and re.search(r'(delete|free|Mem|mem)', t):
            hits.append((hex(cur), t))
        mm = MEM_RX.search(t)
        if mm and mm.group(4):
            d = int(mm.group(5).rstrip('h]'), 16) if mm.group(5) else 0
            if d < SIZE and d > 0x1000:
                hits.append((hex(cur), t))
    report[tag] = hits[:80]

# ---- 3. Init 写序 ----
f = ida_funcs.get_func(0x5054b0)
init_writes = []
if f:
    for cur, t in disasm_range(f, 4000):
        mm = MEM_RX.search(t)
        if mm and re.match(r'\s*(mov|add|sub|or|and)', t):
            d = 0
            if mm.group(4):
                g = mm.group(5)
                d = int(g.rstrip('h]'), 16) if not g.startswith('0x') else int(g, 16)
            init_writes.append((hex(cur), d, t))
report['init_writes'] = init_writes[:400]

# ---- 4. 全方法 disp 普查 ----
census = {}
hole_hits = collections.defaultdict(list)
for ea, nm in sorted(METHODS.items()):
    f = ida_funcs.get_func(ea)
    if not f:
        continue
    disps = collections.Counter()
    scaled = collections.Counter()
    for cur, t in disasm_range(f):
        mm = MEM_RX.search(t)
        if not mm:
            continue
        d = 0
        if mm.group(4):
            g = mm.group(5)
            d = int(g.rstrip('h]'), 16) if not g.startswith('0x') else int(g, 16)
        if d < SIZE:
            disps[d] += 1
            if mm.group(2):                      # [base+idx*..+disp] 数组形
                scaled[d] += 1
    mx = max(disps) if disps else None
    census[nm] = {'ea': hex(ea), 'n_disp': sum(disps.values()),
                  'max_disp': hex(mx) if mx is not None else None,
                  'scaled_disps': {hex(k): v for k, v in sorted(scaled.items())[:24]},
                  'top_disps': [hex(o) for o, _ in disps.most_common(40)]}
    for d in disps:
        for lo, hi in HOLES:
            if lo <= d < hi:
                hole_hits[(lo, hi)].append((nm, hex(d), disps[d]))
report['census'] = census
report['hole_hits'] = {
    '%s-%s' % (hex(lo), hex(hi)): {
        'bytes': hi - lo,
        'n_sites': len(v),
        'n_methods': len(set(x[0] for x in v)),
        'by_method': sorted(collections.Counter(x[0] for x in v).items(), key=lambda x:-x[1]),
        'disps': sorted(set(x[1] for x in v))[:60],
    } for (lo, hi), v in sorted(hole_hits.items())}

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
print('== Create 体 ==')
for a, t in report['create_body'][:26]:
    print(' ', a, t)
print('== 洞区命中 ==')
for k, v in report['hole_hits'].items():
    print('  洞 %s (%dB): %d 站 / %d 方法' % (k, v['bytes'], v['n_sites'], v['n_methods']),
          dict(v['by_method'][:6]))
print('== max_disp per method ==')
for nm, c in sorted(census.items(), key=lambda x: -int(x[1]['max_disp'] or '0', 16))[:12]:
    print('  %-24s max=%s n=%d' % (nm, c['max_disp'], c['n_disp']))
idapro.close_database(False)
