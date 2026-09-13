"""
IDAPython: Query GetTaskParam binary evidence (disp32 offsets, strides).
Usage: idat.exe -A -S"pipeline/ida/_query_gettaskparam.py" original/PAL3.exe.i64
"""
import idaapi, idautils, idc, ida_ua, ida_bytes
import json, os, struct

idaapi.auto_wait()

FUNC_ADDR = 0x004D4D30
FUNC_NAME = "CCBStage::GetTaskParam"

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT = os.path.join(LOG_DIR, "gettaskparam_analysis.json")

# Decompile with Hex-Rays
try:
    import ida_hexrays
    cfunc = ida_hexrays.decompile(FUNC_ADDR)
    decompiled = str(cfunc)
except Exception:
    decompiled = "(Hex-Rays decompile failed)"

# Get raw assembly instructions in the function
func = ida_funcs.get_func(FUNC_ADDR)
if not func:
    print("[ERROR] Function not found")
    idc.qexit(1)

instructions = []
disasm_lines = []

for head in idautils.Heads(func.start_ea, func.end_ea):
    if ida_bytes.is_code(ida_bytes.get_flags(head)):
        insn = ida_ua.insn_t()
        ida_ua.decode_insn(insn, head)
        disasm = idc.GetDisasm(head)
        disasm_lines.append({
            "addr": "0x%08X" % head,
            "bytes": ida_bytes.get_bytes(head, insn.size).hex() if insn.size else "",
            "disasm": disasm,
            "size": insn.size,
        })

        # Record disp32 memory accesses
        for i in range(8):
            op = insn.ops[i]
            if op.type == ida_ua.o_mem and op.addr > 0x00401000:
                instructions.append({
                    "addr": "0x%08X" % head,
                    "type": "mem_disp32",
                    "target": "0x%08X" % op.addr,
                    "disasm": disasm,
                })
            elif op.type == ida_ua.o_phrase and op.addr != 0:
                # Register+displacement access
                instructions.append({
                    "addr": "0x%08X" % head,
                    "type": "reg_disp",
                    "disp": "0x%X" % op.addr,
                    "disasm": disasm,
                })

# Collect all unique disp32 offsets used in reg+disp addressing
disps = sorted(set(
    instr["disp"] for instr in instructions
    if instr["type"] == "reg_disp"
), key=lambda x: int(x, 16))

result = {
    "function": FUNC_NAME,
    "address": "0x%08X" % FUNC_ADDR,
    "size_bytes": func.end_ea - func.start_ea if func else 0,
    "decompiled": decompiled,
    "instructions": disasm_lines,
    "unique_disps": disps,
}

with open(OUTPUT, "w", encoding="utf-8") as f:
    json.dump(result, f, indent=2, ensure_ascii=False)

print("[OK] Output written to %s" % OUTPUT)
print("Instructions: %d" % len(disasm_lines))
print("Unique disp32: %s" % disps)
idc.qexit(0)
