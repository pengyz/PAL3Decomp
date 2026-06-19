import json, os, idc, ida_funcs, idautils
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_logs", "actor_exec.json")
ea = 0x41BCA0
func = ida_funcs.get_func(ea)

# Simplified: just get offsets, no member loops
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
    if h: accesses.append({"addr": f"0x{head:08X}", "disp": int(h, 16)})

# Get RS members (simpler approach)
sid_rs = idc.get_struc_id('RoleSystem')
near = []
for i in range(idc.get_member_qty(sid_rs)):
    mid = idc.get_member_by_idx(sid_rs, i)
    if mid:
        soff = idc.get_member_offset(mid)
        if soff and 0x680 <= soff < 0x6C0:
            near.append({"off": soff, "name": idc.get_member_name(mid) or '?'})

with open(OUT, 'w') as f:
    json.dump({"accesses": accesses, "near_69C": near}, f)
idc.qexit(0)
