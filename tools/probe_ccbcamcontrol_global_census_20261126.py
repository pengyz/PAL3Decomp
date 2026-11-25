#!/usr/bin/env python3
"""probe_ccbcamcontrol_global_census_20261126.py — g_CCBCamControlData 绝对寻址普查。

静态单例对象: 方法内 this-form([ecx+disp]) 已由 probe_ccbcamcontrol_census 普查;
本探针补第四面: 全二进制 .text 扫描 `g_CCBCamControlData+disp` / `offset
g_CCBCamControlData` 形(静态基址绑定+外部访问器), 聚焦四大洞区:
  [0x2598,0x5558) 12224B / [0x555c,0x3cfb8) 227932B / [0x4af58,0x5d9ec) 76436B
  [0x60af8,0x68fb0) 33976B / [0x43c,0x984) 1352B / [0x40,0xec) 172B
输出: 每洞 {访问函数集, disp 列表, 方法内/外分布} → 成员边界从 disp 聚类显形。
"""
import sys, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

SIZE = 0x690B0
BASE = 0x17AAF64
OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_ccbcamcontrol_global_census_20261126.json'
CC = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/CCBCamControl.json',
                    encoding='utf-8'))
METHODS = {int(a, 16) for a in (CC.get('methods') or {})}
HOLES = [(0x14,0x34),(0x40,0xec),(0x1c8,0x260),(0x43c,0x984),
         (0x2598,0x5558),(0x555c,0x3cfb8),(0x4af58,0x5d9ec),
         (0x5e0a4,0x5f360),(0x60af8,0x68fb0),(0x0,0x8)]
# 全局名+disp 形; imm 绝对基址形(offset g_CCBCamControlData)
NAME_RX = re.compile(r'g_CCBCamControlData(?:\+(0[xX][0-9A-Fa-f]+|[0-9A-Fa-f]{1,8}h?))?')
IMMBIND_RX = re.compile(r'\boffset\s+g_CCBCamControlData\b|\b0[xX]?17AAF64\b', re.I)

hits = []            # (caller_ea, caller_name, is_method, disp)
bind_sites = []      # (caller, text) 静态基址绑定(mov reg,offset/immediates)
nfun = 0
for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    if not f:
        continue
    nfun += 1
    cn = idc.get_func_name(f.start_ea)
    is_m = f.start_ea in METHODS
    cur, n = f.start_ea, 0
    fhits = []
    while cur < f.end_ea and n < 4000:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        if 'g_CCBCamControlData' in t or '17AAF64' in t:
            m = NAME_RX.search(t)
            d = None
            if m and m.group(1):
                g = m.group(1)
                d = int(g, 16) if g.lower().startswith('0x') else int(g.rstrip('h'), 16)
            if d is not None and d < SIZE:
                fhits.append((hex(cur), d, t))
                for lo, hi in HOLES:
                    if lo <= d < hi:
                        hits.append((cn, is_m, d))
            if IMMBIND_RX.search(t):
                bind_sites.append((cn, hex(cur), t))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
print('functions scanned: %d, hole-site hits: %d, bind sites: %d' % (nfun, len(hits), len(bind_sites)))

agg = {}
for lo, hi in HOLES:
    rows = [h for h in hits if lo <= h[2] < hi]
    methods = sorted(set(h[0] for h in rows if h[1]))
    exts = sorted(set(h[0] for h in rows if not h[1]))
    disps = sorted(set(h[2] for h in rows))
    agg['%s-%s' % (hex(lo), hex(hi))] = {
        'bytes': hi - lo, 'n_sites': len(rows),
        'methods': methods, 'ext_funcs': exts[:40],
        'n_ext': len(exts), 'disps': [hex(d) for d in disps[:80]],
        'disp_stride_guess': None,
    }
    # 步距探测: 相邻 disp 差公约数
    if len(disps) > 3:
        from math import gcd
        g = 0
        for a, b in zip(disps, disps[1:]):
            g = gcd(g, b - a)
        agg['%s-%s' % (hex(lo), hex(hi))]['disp_stride_guess'] = hex(g) if g else None

report = {'agg': agg, 'bind_sites': bind_sites[:120],
          'n_bind': len(bind_sites)}
json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
for k, v in agg.items():
    print('洞 %s (%dB): %d 站 方法%d 外部%d 步距猜=%s' % (
        k, v['bytes'], v['n_sites'], len(v['methods']), v['n_ext'],
        v['disp_stride_guess']))
    print('   方法:', v['methods'][:10])
    print('   外部:', v['ext_funcs'][:10])
    print('   disp:', v['disps'][:24])
idapro.close_database(False)
