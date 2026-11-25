#!/usr/bin/env python3
"""probe_string_class_20261125.py — 游戏 String 类全息取证。
G1: String::Assign 0x4326a0 全体 (调 _Eos/_Tidy/_Split? → 公开方法与 helper 关系)
G2: String ctor ??0String@@ 全清单 + 体 (布局定谳)
G3: _Eos 13 调用者全清单 (含类内方法 vs 游戏函数)
G4: _Tidy/_Split/_Freeze 调用者计数与代表
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_string_class_20261125.json'
report = {}

def full_body(ea):
    f = ida_funcs.get_func(ea)
    if not f:
        return None
    out, cur = [], f.start_ea
    n = 0
    while cur < f.end_ea and n < 90:
        out.append('%s  %s' % (hex(cur), (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()))
        cur = idc.next_head(cur, f.end_ea)
        if cur == idc.BADADDR:
            break
        n += 1
    return out

# G1 Assign 体
report['assign_body'] = full_body(0x4326a0)

# G2 String ctor
ctors = []
for ea, name in idautils.Names():
    if re.search(r'\?\?0String@@', name):
        ctors.append({'ea': hex(ea), 'name': name[:60], 'body': full_body(ea)[:14]})
report['string_ctors'] = ctors

# G3 _Eos 全调用者
calls = []
for site in idautils.CodeRefsTo(0x407b30, 0):
    cf = ida_funcs.get_func(site)
    calls.append({'site': hex(site),
                  'caller': idc.get_func_name(cf.start_ea) if cf else '?'})
report['eos_callers'] = calls

# G4 其他 helper 计数
for nm, ea in (('_Tidy', 0x402fb0), ('_Split', 0x407c70), ('_Freeze', 0x407ab0)):
    cs = []
    for site in idautils.CodeRefsTo(ea, 0):
        cf = ida_funcs.get_func(site)
        cs.append(idc.get_func_name(cf.start_ea) if cf else '?')
    report['callers_' + nm] = {'n': len(cs), 'sample': cs[:8]}

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print(json.dumps(report, ensure_ascii=False, indent=1)[:7000])
idapro.close_database(False)
