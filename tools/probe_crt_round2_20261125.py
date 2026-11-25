#!/usr/bin/env python3
"""probe_crt_round2_20261125.py — 二轮取证:
  R1 0x4d70b0 函数体字节 + 大小 (CRT 撞名/Icf 折叠鉴别)
  R2 til 枚举 LIGHT_TYPE/LGT_TYPE 成员全量 (PRTYPE_BODY)
  R3 _Eos 全名搜索 (mangle 修正) + callee 类型
  R4 gbLightObj::Init 0x56a5a0 全 xref (code+data)
  R5 ProcFling 调用窗 0x512cb8 前后 12 条 (接收者取证)
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, ida_typeinf, ida_nalt, idautils, ida_bytes

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_crt_round2_20261125.json'
report = {}

# R1 函数体
ea = 0x4d70b0
f = ida_funcs.get_func(ea)
sz = f.end_ea - f.start_ea if f else 0
report['r1_body'] = {
    'ea': hex(ea), 'size': sz,
    'bytes': ida_bytes.get_bytes(ea, min(sz, 32)).hex() if sz else None,
    'disasm': [(idc.generate_disasm_line(ea + i * 4, 0) or '') for i in range(min(sz // 4 + 2, 8))],
}
# 找没有 _0 的同名函数
for a, n in idautils.Names():
    if 'do_always_noconv' in n and not n.endswith('_0'):
        report.setdefault('r1_plain_names', []).append({'ea': hex(a), 'name': n})

# R2 枚举成员
til = ida_typeinf.get_idati()
report['r2_enums'] = {}
for ename in ('LIGHT_TYPE', 'LGT_TYPE'):
    tid = ida_typeinf.get_type_ordinal(til, ename)
    info = {'ordinal': tid}
    if tid:
        tif = ida_typeinf.tinfo_t()
        if tif.get_numbered_type(til, tid):
            info['decl'] = tif._print(None, ida_typeinf.PRTYPE_MULTI)
    report['r2_enums'][ename] = info

# R3 _Eos 搜索
eos = []
for a, n in idautils.Names():
    if '_Eos' in n:
        tif = ida_typeinf.tinfo_t()
        ok = ida_nalt.get_tinfo(tif, a)
        eos.append({'ea': hex(a), 'name': n[:90], 'type': str(tif) if ok and not tif.empty() else None})
report['r3_eos'] = eos

# R4 Init 全 xref
init_ea = 0x56a5a0
xr = []
for xa in idautils.XrefsTo(init_ea, 0):
    cf = ida_funcs.get_func(xa.frm)
    xr.append({'from': hex(xa.frm), 'type': xa.type,
               'caller': idc.get_func_name(cf.start_ea) if cf else '?'})
report['r4_init_xrefs'] = xr

# R5 ProcFling 调用窗
def win(ea, back=6, fwd=6):
    seq = []
    cur = ea
    for _ in range(back):
        cur = idc.prev_head(cur, 0)
        if cur == idc.BADADDR:
            break
    start = cur
    cur = start
    for _ in range(back + fwd):
        if cur == idc.BADADDR:
            break
        seq.append('%s  %s' % (hex(cur), (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()))
        cur = idc.next_head(cur, 0)
    return seq
report['r5_procfling_site'] = win(0x512cb8)
report['r5_procnormal_site'] = win(0x512678)

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print(json.dumps(report, ensure_ascii=False, indent=1)[:4000])
idapro.close_database(False)
