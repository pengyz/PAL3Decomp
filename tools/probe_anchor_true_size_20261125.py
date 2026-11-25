#!/usr/bin/env python3
"""probe_anchor_true_size_20261125.py — Wave1: 可疑尺寸锚真值三证。
查法: ①??0Type@@ ctor 在册? ②工厂调用点 push size + operator new (A 级分配尺寸)
      ③ctor 体 max write offset (写界下证)  ④ehvec/数组字面量 (??_L@ push size)
对照: annotation binary_size → 裁决 真实/虚胖/捏造。
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils, ida_bytes

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_anchor_true_size_20261125.json'
TARGETS = ['gbBinkVideo', 'SoundMgr', 'DealData', 'PAL_GDB', 'CCCTData', 'ARC_PAL_GDB']
report = {}

for cls in TARGETS:
    info = {'ctors': [], 'factory_sites': [], 'ehvec': []}
    # ① ctor
    ctors = []
    for ea, name in idautils.Names():
        if re.search(r'\?\?0%s@@' % cls, name):
            f = ida_funcs.get_func(ea)
            ctors.append({'ea': hex(ea), 'name': name[:60], 'size': (f.end_ea - f.start_ea) if f else 0})
    info['ctors'] = ctors
    # ② ctor 调用点回溯 push size (工厂形: push N; call new; mov ecx,eax; call ctor)
    for c in ctors:
        cea = int(c['ea'], 16)
        for site in idautils.CodeRefsTo(cea, 0):
            seq, cur = [], site
            for _ in range(10):
                p = idc.prev_head(cur, 0)
                if p == idc.BADADDR: break
                t = (idc.generate_disasm_line(p, 0) or '').split(';')[0].strip()
                seq.append(t)
                cur = p
            info['factory_sites'].append({'site': hex(site), 'ctor': c['ea'], 'window': seq[:8]})
    # ③ ctor 体 max write (粗扫: [reg+disp] 写的最大 disp)
    for c in ctors:
        cea = int(c['ea'], 16)
        f = ida_funcs.get_func(cea)
        if not f: continue
        maxw = 0
        cur = f.start_ea
        n = 0
        while cur < f.end_ea and n < 400:
            t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
            m = re.match(r'mov\s+(?:(?:byte|word|dword) ptr\s+)?\[e[a-z]{2}\+([0-9A-Fa-f]+)h?\]', t)
            if m:
                off = int(m.group(1), 16)
                sz = 4
                if 'byte ptr' in t: sz = 1
                elif 'word ptr' in t: sz = 2
                maxw = max(maxw, off + sz)
            m2 = re.match(r'mov\s+e[a-z]{2},\s*\[e[a-z]{2}\+([0-9A-Fa-f]+)h?\]', t)
            if m2:
                maxw = max(maxw, int(m2.group(1), 16) + 4)
            cur = idc.next_head(cur, f.end_ea)
            n += 1
        c['max_write'] = hex(maxw)
    report[cls] = info

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
for cls, info in report.items():
    print('%-12s ctors=%d factory=%d' % (cls, len(info['ctors']), len(info['factory_sites'])))
    for c in info['ctors'][:2]:
        print('    ctor %s size=%d max_write=%s' % (c['ea'], c['size'], c.get('max_write')))
    for s in info['factory_sites'][:2]:
        print('    site %s: %s' % (s['site'], [x for x in s['window'] if 'push' in x][:2]))
idapro.close_database(False)
