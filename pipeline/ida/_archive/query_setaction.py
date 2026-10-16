import json, os, idc, ida_funcs, idautils
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_logs", "setaction.json")
ea = 0x421560
func = ida_funcs.get_func(ea)
result = {}
if func:
    insns = []
    for head in idautils.Heads(func.start_ea, func.end_ea):
        insn = idc.generate_disasm_line(head, 0)
        if insn and ('[esi+' in insn or 'lea' in insn or 'add' in insn):
            insns.append({"addr": f"0x{head:08X}", "insn": insn.strip()})
    result["insns"] = insns
with open(OUT, 'w') as f:
    json.dump(result, f, indent=2)
idc.qexit(0)
