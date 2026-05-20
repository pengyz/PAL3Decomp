"""Query: For fields accessed with LEA, trace what function the address is passed to.

This helps determine embedded object types by finding constructor calls
or typed function parameters that receive the field address.

Output: pipeline/ida/_logs/lea_target_analysis.json
"""
import idaapi
import idautils
import idc
import ida_bytes
import ida_funcs
import ida_name
import ida_typeinf
import json
import os

idaapi.auto_wait()

# Target: fields with LEA access from query_todo_fields
TARGETS = [
    # (class, offset_hex, VA_of_lea_instruction)
    ("Actor", 0x200, 0x0044CB5A),   # Actor+512
    ("Actor", 0x188, 0x00539476),   # Actor+392
    ("Actor", 0x134, 0x004119C3),   # Actor+308
    ("Actor", 0x98, 0x0044CC0E),    # Actor+152
    ("CCBStage", 0x1F8, 0x005046D7),  # CCBStage+504 (int, fld)
    ("CCBStage", 0x248, 0x0050411D),  # CCBStage+584
    ("CCBStage", 0x128, 0x004DF72C),  # CCBStage+296
    ("RoleSystem", 0x5A8, 0x00412257),  # RoleSystem+1448
    ("RoleSystem", 0x194, 0x0041C0F5),  # RoleSystem+404
]

results = {}

for cls_name, field_offset, lea_va in TARGETS:
    # Get the function containing the LEA
    func = ida_funcs.get_func(lea_va)
    if not func:
        continue

    key = f"{cls_name}+{field_offset}"
    results[key] = {
        "class": cls_name,
        "offset": field_offset,
        "offset_hex": hex(field_offset),
        "lea_va": hex(lea_va),
        "analysis": []
    }

    # Disassemble from LEA forward to find what happens with the register
    # Look for: push reg, call func (the LEA result passed as argument)
    # or: mov ecx, reg; call func (thiscall on the object)
    ea = lea_va
    lea_disasm = idc.GetDisasm(ea)
    # Extract destination register from LEA
    lea_op0 = idc.print_operand(ea, 0)  # destination register

    results[key]["lea_disasm"] = lea_disasm
    results[key]["lea_dest_reg"] = lea_op0

    # Scan forward up to 20 instructions looking for calls that use this register
    scan_ea = idc.next_head(ea)
    for i in range(20):
        if scan_ea == idc.BADADDR:
            break
        mnem = idc.print_insn_mnem(scan_ea)

        if mnem == "call":
            # Found a call - check what's being called
            call_target = idc.get_operand_value(scan_ea, 0)
            call_name = ida_name.get_name(call_target) if call_target != idc.BADADDR else "indirect"

            # Get the function's type info if available
            tinfo = ida_typeinf.tinfo_t()
            if ida_typeinf.guess_tinfo(tinfo, call_target):
                func_type = str(tinfo)
            else:
                func_type = "unknown"

            results[key]["analysis"].append({
                "instruction": idc.GetDisasm(scan_ea),
                "call_target": hex(call_target) if call_target != idc.BADADDR else "indirect",
                "call_name": call_name,
                "func_type": func_type,
                "distance_from_lea": i
            })
            break

        # Check if the LEA register is used as ECX (thiscall pattern)
        if mnem == "mov" and idc.print_operand(scan_ea, 0) == "ecx" and lea_op0 in idc.GetDisasm(scan_ea):
            # mov ecx, <lea_reg> → next call is thiscall on this object
            next_ea = idc.next_head(scan_ea)
            for j in range(5):
                if next_ea == idc.BADADDR:
                    break
                if idc.print_insn_mnem(next_ea) == "call":
                    call_target = idc.get_operand_value(next_ea, 0)
                    call_name = ida_name.get_name(call_target) if call_target != idc.BADADDR else "indirect"
                    results[key]["analysis"].append({
                        "pattern": "thiscall",
                        "mov_ecx": idc.GetDisasm(scan_ea),
                        "call": idc.GetDisasm(next_ea),
                        "call_target": hex(call_target) if call_target != idc.BADADDR else "indirect",
                        "call_name": call_name,
                        "distance_from_lea": i
                    })
                    break
                next_ea = idc.next_head(next_ea)
            break

        # If the register is overwritten, stop
        if lea_op0 in idc.print_operand(scan_ea, 0) and mnem not in ("push", "test", "cmp"):
            if mnem != "lea":  # another LEA is OK (might be building on it)
                break

        scan_ea = idc.next_head(scan_ea)

# Write output
out_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_logs")
os.makedirs(out_dir, exist_ok=True)
out_path = os.path.join(out_dir, "lea_target_analysis.json")
with open(out_path, "w", encoding="utf-8") as f:
    json.dump(results, f, indent=2, ensure_ascii=False)

print(f"[*] LEA target analysis written to {out_path}")
print(f"[*] Analyzed {len(results)} fields")

idc.qexit(0)
