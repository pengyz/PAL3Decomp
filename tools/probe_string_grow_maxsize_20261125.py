#!/usr/bin/env python3
"""_Grow@0x4317d0 与 max_size@0x407d40 函数体 → sig 定谳"""
import sys, json
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_string_grow_maxsize_20261125.json'
report = {}
for nm, ea in (('_Grow', 0x4317d0), ('max_size', 0x407d40)):
    f = ida_funcs.get_func(ea)
    out, cur, n = [], f.start_ea, 0
    while cur < f.end_ea and n < 40:
        out.append('%s  %s' % (hex(cur), (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    callers = []
    for site in idautils.CodeRefsTo(ea, 0):
        cf = ida_funcs.get_func(site)
        callers.append(idc.get_func_name(cf.start_ea) if cf else '?')
    report[nm] = {'ea': hex(ea), 'size': f.end_ea - f.start_ea,
                  'body': out, 'callers_n': len(callers), 'callers': callers[:8]}
json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print(json.dumps(report, ensure_ascii=False, indent=1)[:5000])
idapro.close_database(False)
