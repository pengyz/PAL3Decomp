import json, ida_auto, ida_funcs, ida_hexrays, idautils, idc, ida_typeinf
ida_auto.auto_wait()

r = {}
addr = 0x43DE40

# Check which class this function belongs to via PDB
func_name = idc.get_func_name(addr)
r['func_name'] = func_name
r['type'] = idc.get_type(addr)

# Check xrefs — which functions call this?
xrefs = []
for xref in idautils.XrefsTo(addr):
    caller = idc.get_func_name(xref.frm)
    xrefs.append((hex(xref.frm), caller, xref.type))
r['xrefs'] = xrefs[:10]

# Check what type is at this+0x44
# mov ecx, [esi+44h] — read gbRefObject* from this+0x44
# Get the full disassembly to understand this usage
insns = []
for head in idautils.FuncItems(addr):
    insn = idc.generate_disasm_line(head, 0)
    if head < addr + 0x40:  # first 64 bytes
        insns.append(f'0x{head:X}: {insn}')
r['disasm'] = insns[:20]

# Decompile
try:
    c = ida_hexrays.decompile(addr)
    r['decomp'] = str(c)
except Exception as e:
    r['decomp_err'] = str(e)

json.dump(r, open('/tmp/destroy_analysis.json', 'w'), indent=2, default=str)
idc.qexit(0)
