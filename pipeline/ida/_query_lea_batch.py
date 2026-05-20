"""Batch LEA target analysis: trace all int-typed fields with LEA access
to determine their true type (embedded object, array, etc.)

Reads from query_todo_fields output, finds all LEA refs, traces forward
to constructor calls or typed function parameters.

Output: pipeline/ida/_logs/lea_batch_analysis.json
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

# Load query_todo_fields output
logs_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_logs")
todo_path = os.path.join(logs_dir, "todo_field_context.json")

with open(todo_path, "r", encoding="utf-8") as f:
    todo_data = json.load(f)

# Collect all LEA targets
lea_targets = []
for cls, fields in todo_data.items():
    for offset_str, info in fields.items():
        refs = info.get("refs", [])
        for r in refs:
            if isinstance(r, dict) and r.get("access") == "lea":
                va_str = r.get("va", "")
                if va_str:
                    try:
                        va = int(va_str, 16)
                        lea_targets.append({
                            "class": cls,
                            "offset": int(offset_str),
                            "offset_hex": hex(int(offset_str)),
                            "cur_type": info.get("type", "?"),
                            "lea_va": va,
                            "method": r.get("method", ""),
                        })
                    except ValueError:
                        pass

print(f"[*] Found {len(lea_targets)} LEA targets to analyze")

results = {}

for target in lea_targets:
    ea = target["lea_va"]
    key = f"{target['class']}+{target['offset']}"

    if key in results:
        # Already analyzed from another ref
        continue

    results[key] = {
        "class": target["class"],
        "offset": target["offset"],
        "offset_hex": target["offset_hex"],
        "cur_type": target["cur_type"],
        "lea_va": hex(ea),
        "method": target["method"],
        "calls_found": []
    }

    # Get LEA destination register
    lea_dest = idc.print_operand(ea, 0)

    # Scan forward looking for how the LEA result is used
    scan_ea = idc.next_head(ea)
    for i in range(30):
        if scan_ea == idc.BADADDR:
            break

        mnem = idc.print_insn_mnem(scan_ea)
        disasm = idc.GetDisasm(scan_ea)

        # Pattern 1: mov ecx, <lea_reg>; call X (thiscall on embedded object)
        if mnem == "mov" and idc.print_operand(scan_ea, 0) == "ecx":
            if lea_dest in disasm:
                # Found thiscall setup - look for next call
                next_ea = idc.next_head(scan_ea)
                for j in range(5):
                    if next_ea == idc.BADADDR:
                        break
                    if idc.print_insn_mnem(next_ea) == "call":
                        call_target = idc.get_operand_value(next_ea, 0)
                        call_name = ida_name.get_name(call_target) if call_target and call_target != idc.BADADDR else ""
                        if not call_name:
                            call_name = idc.GetDisasm(next_ea)
                        results[key]["calls_found"].append({
                            "pattern": "thiscall",
                            "call_name": call_name,
                            "call_va": hex(call_target) if call_target and call_target != idc.BADADDR else "indirect",
                        })
                        break
                    next_ea = idc.next_head(next_ea)
                break

        # Pattern 2: push <lea_reg>; ... call X (cdecl/stdcall param)
        if mnem == "push" and lea_dest in disasm:
            # LEA result pushed as argument - find the call
            next_ea = idc.next_head(scan_ea)
            for j in range(10):
                if next_ea == idc.BADADDR:
                    break
                if idc.print_insn_mnem(next_ea) == "call":
                    call_target = idc.get_operand_value(next_ea, 0)
                    call_name = ida_name.get_name(call_target) if call_target and call_target != idc.BADADDR else ""
                    if not call_name:
                        call_name = idc.GetDisasm(next_ea)
                    results[key]["calls_found"].append({
                        "pattern": "push_arg",
                        "call_name": call_name,
                        "call_va": hex(call_target) if call_target and call_target != idc.BADADDR else "indirect",
                    })
                    break
                next_ea = idc.next_head(next_ea)
            break

        # Pattern 3: direct call with lea_reg (already in position)
        if mnem == "call":
            call_target = idc.get_operand_value(scan_ea, 0)
            call_name = ida_name.get_name(call_target) if call_target and call_target != idc.BADADDR else ""
            if not call_name:
                call_name = idc.GetDisasm(scan_ea)
            results[key]["calls_found"].append({
                "pattern": "direct_call_after_lea",
                "call_name": call_name,
                "call_va": hex(call_target) if call_target and call_target != idc.BADADDR else "indirect",
            })
            break

        # If register is overwritten by non-trivial instruction, stop
        if lea_dest in idc.print_operand(scan_ea, 0) and mnem not in ("push", "test", "cmp", "add", "sub"):
            break

        scan_ea = idc.next_head(scan_ea)

# Write output
out_path = os.path.join(logs_dir, "lea_batch_analysis.json")
with open(out_path, "w", encoding="utf-8") as f:
    json.dump(results, f, indent=2, ensure_ascii=False)

# Summary
ctor_found = sum(1 for r in results.values() if any("ctor" in c.get("call_name","").lower() or "gbVec3D" in c.get("call_name","") for c in r["calls_found"]))
any_call = sum(1 for r in results.values() if r["calls_found"])
print(f"[*] Results: {len(results)} fields analyzed")
print(f"[*] Found calls for {any_call} fields, {ctor_found} with constructor evidence")
print(f"[*] Output: {out_path}")

idc.qexit(0)
