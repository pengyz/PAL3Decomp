#!/usr/bin/env python3
"""probe_anchor_receiver_bound_20261125.py — W1 查二: 锚类方法体 this-form disp 上界。
判据: 每锚全部注解方法体中 [reg+disp] / [this+disp] 访问 disp 全集 → max disp
对照 binary_size: max_disp ≈ size → 真实; max_disp << size → 尺寸虚胖(查一补放置证据)。
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_anchor_receiver_bound_20261125.json'
TARGETS = {
    'PAL_GDB': 814524, 'ARC_PAL_GDB': 804888, 'DealData': 833340,
    'CCCTData': 430256, 'SoundMgr': 918796, 'gbBinkVideo': 1835912,
}
report = {}

for cls, ann_size in TARGETS.items():
    # 注解方法的地址: 从 annotation json 拿 (比 mangle 搜索可靠)
    import os
    aj = 'data/annotations/structs/%s.json' % cls
    methods = []
    if os.path.exists(aj):
        d = json.load(open(aj, encoding='utf-8'))
        for a, m in (d.get('methods') or {}).items():
            methods.append((int(a, 16), str(m.get('name') or '?')))
    max_disp = 0
    max_site = None
    scanned = 0
    for ea, nm in methods:
        f = ida_funcs.get_func(ea)
        if not f:
            continue
        scanned += 1
        cur = f.start_ea
        n = 0
        while cur < f.end_ea and n < 3000:
            t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
            # this-form 访问: [e??+disp] 任意指令 (粗上界, 含读)
            m = re.search(r'\[(?:e[a-z]{2})\+([0-9A-Fa-f]{3,8})h?\]', t)
            if m:
                off = int(m.group(1), 16)
                if off < 0x200000 and off > max_disp:  # 过滤 rip/绝对值噪声
                    max_disp = off
                    max_site = '%s@%s' % (nm, hex(cur))
            cur = idc.next_head(cur, f.end_ea)
            n += 1
    ratio = (100.0 * max_disp / ann_size) if ann_size else 0
    report[cls] = {'ann_size': ann_size, 'max_disp': hex(max_disp),
                   'ratio_pct': round(ratio, 1), 'methods_scanned': scanned,
                   'max_site': max_site}
    print('%-12s ann=%-8d max_disp=%-8x (%5.1f%%) 方法=%d  %s' % (
        cls, ann_size, max_disp, ratio, scanned, max_site))

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
idapro.close_database(False)
