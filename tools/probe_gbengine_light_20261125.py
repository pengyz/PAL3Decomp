#!/usr/bin/env python3
"""probe_gbengine_light_20261125.py — gbengine.dll 里裁决 LIGHT_TYPE 真值域。
D1: gbLightObj::Init 函数定位 + 体反汇编 (switch/if 域 → 真合法值集)
D2: til/名称空间里 LIGHT_TYPE / LGT_TYPE 枚举定义与成员
D3: gbLightObj ctor 对 Init 的引用值
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/gbengine.dll.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, ida_typeinf, ida_nalt, idautils, ida_bytes

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_gbengine_light_20261125.json'
report = {}

# D1 Init 函数
inits = []
for ea, name in idautils.Names():
    if re.search(r'\?Init@gbLightObj@@', name):
        inits.append((ea, name))
report['init_fns'] = []
for ea, n in inits:
    f = ida_funcs.get_func(ea)
    body = []
    if f:
        cur = f.start_ea
        for _ in range(min(120, (f.end_ea - f.start_ea))):
            body.append('%s  %s' % (hex(cur), (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()))
            cur = idc.next_head(cur, f.end_ea)
            if cur == idc.BADADDR:
                break
    report['init_fns'].append({'ea': hex(ea), 'name': n, 'size': (f.end_ea - f.start_ea) if f else 0,
                               'body': body})

# D2 枚举定义
til = ida_typeinf.get_idati()
report['enums'] = {}
for ename in ('LIGHT_TYPE', 'LGT_TYPE', 'enum_LIGHT_TYPE'):
    tid = ida_typeinf.get_type_ordinal(til, ename)
    info = {'ordinal': tid}
    if tid:
        tif = ida_typeinf.tinfo_t()
        if tif.get_numbered_type(til, tid):
            info['decl'] = tif._print(None, ida_typeinf.PRTYPE_MULTI)
    report['enums'][ename] = info
# 名字含 LIGHT 的枚举全搜
light_names = [n for _, n in idautils.Names() if 'LIGHT' in n.upper() and '::' not in n]
report['light_name_hits'] = light_names[:20]

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print(json.dumps(report, ensure_ascii=False, indent=1)[:6000])
idapro.close_database(False)
