"""Query PlayerMgr function at address where dwWeaponWU+3264 appears.
Check the actual assembly to verify if Hex-Rays interpreted it correctly."""
import json, ida_auto, ida_funcs, ida_hexrays, idaapi, idautils, idc

ida_auto.auto_wait()

# The specific function with PlayerMgr C2440 errors
# From the errors, the pattern appears in functions accessing this->dwWeaponWU + 3264
# Let's find which PlayerMgr functions access offset +14272 from struct base

# Read PlayerMgr struct size from IDA
til = ida_typeinf.get_idati()
t = ida_typeinf.tinfo_t()
if t.get_named_type(til, 'PlayerMgr'):
    pm_size = t.get_size()
else:
    pm_size = 0

result = {
    'pm_size': pm_size,
    'dwWeaponWU_offset': None,
    'functions_accessing_offset': []
}

# Get dwWeaponWU offset from struct
if t.get_named_type(til, 'PlayerMgr'):
    u = ida_typeinf.udt_type_data_t()
    if t.get_udt_details(u):
        for i in range(u.size()):
            m = u[i]
            nm = (m.name or '').strip()
            if 'dwWeaponWU' in nm:
                result['dwWeaponWU_offset'] = m.offset // 8
                break

# Search for functions that reference PlayerMgr::dwWeaponWU-like patterns
target_ea = 0x400000 + result.get('dwWeaponWU_offset', 0) if result.get('dwWeaponWU_offset') else 0

import os

# Find relevant decompilation files
decomp_dir = '/home/peng/workspace/PAL3Decomp/asm/pal3/decomp'
player_mgr_funcs = []
for fn in os.listdir(decomp_dir):
    if 'PlayerMgr' in fn and fn.endswith('.json'):
        with open(os.path.join(decomp_dir, fn)) as f:
            try:
                data = json.load(f)
                code = data.get('code', '')
                if 'dwWeaponWU' in code:
                    player_mgr_funcs.append(fn)
            except: pass

result['player_mgr_decomp_funcs'] = player_mgr_funcs[:10]

path = '/home/peng/workspace/PAL3Decomp/pipeline/ida/_logs/player_mgr_query.json'
with open(path, 'w') as f:
    json.dump(result, f, indent=2, default=str)
print('OK')
idc.qexit(0)
