#!/usr/bin/env python3
"""tails: _Tidy/_Split/_Freeze 尾部 retn N + 当前 IDB tinfo + Assign 渲染形佐证"""
import sys, json
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, ida_bytes, ida_nalt, ida_typeinf

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_string_tails_20261125.json'
report = {}
for nm, ea in (('_Tidy', 0x402fb0), ('_Split', 0x407c70), ('_Freeze', 0x407ab0), ('Assign', 0x4326a0)):
    f = ida_funcs.get_func(ea)
    sz = f.end_ea - f.start_ea
    tail = ida_bytes.get_bytes(f.end_ea - 8, 8) or b''
    tif = ida_typeinf.tinfo_t()
    ok = ida_nalt.get_tinfo(tif, ea)
    report[nm] = {'size': sz,
                  'tail_hex': tail.hex(),
                  'tail_disasm': [(idc.generate_disasm_line(h, 0) or '').split(';')[0].strip()
                                  for h in (f.end_ea - 8, f.end_ea - 4) if h > f.start_ea],
                  'tinfo': str(tif) if ok and not tif.empty() else None}
json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print(json.dumps(report, ensure_ascii=False, indent=1))
idapro.close_database(False)
