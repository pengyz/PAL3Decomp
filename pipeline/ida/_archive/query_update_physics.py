import json, os, idc, ida_funcs, idautils
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_logs", "update_physics.json")

def build_field_map(sid):
    m = {}
    for i in range(idc.get_member_qty(sid)):
        mid = idc.get_member_by_idx(sid, i)
        if mid:
            soff = idc.get_member_offset(mid)
            if soff is not None:
                sz = idc.get_member_size(mid) or 4
                m[soff] = (idc.get_member_name(mid) or '?', sz)
    return m

ea = 0x419690
func = ida_funcs.get_func(ea)
if not func:
    with open(OUT, 'w') as f: f.write('{"error":"func not found"}')
    idc.qexit(1)

ac_map = build_field_map(idc.get_struc_id('Actor'))
rs_map = build_field_map(idc.get_struc_id('RoleSystem'))

accesses = []
for head in idautils.Heads(func.start_ea, func.end_ea):
    insn = idc.generate_disasm_line(head, 0)
    if not insn or '[esi+' not in insn: continue
    p = insn.find('[esi+'); rest = insn[p+5:]
    h = ''
    for c in rest:
        if c in '0123456789abcdefABCDEF': h += c
        elif c in 'hH]': break
        else: h = ''; break
    if not h: continue
    disp = int(h, 16)
    a = {"addr": f"0x{head:08X}", "disp": f"0x{disp:X}", "in_actor": disp < 820}
    # Actor field
    for base, (name, sz) in ac_map.items():
        if base <= disp < base + sz:
            a["actor_field"] = name
            break
    # RS field
    rs_off = disp + 0x1A8
    a["rs_off"] = f"0x{rs_off:X}"
    for base, (name, sz) in rs_map.items():
        if base <= rs_off < base + sz:
            a["rs_field"] = name
            break
    accesses.append(a)

with open(OUT, 'w') as f:
    json.dump({"accesses": accesses}, f, indent=2)
idc.qexit(0)
