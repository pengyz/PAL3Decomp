import json, os, idc, ida_funcs, idautils
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_logs", "setpause_calls.json")

# Find all CALLs to SetPause (0x4DB910)
target = 0x4DB910
results = []
for ea in idautils.Heads():
    if idc.print_insn_mnem(ea) == 'call':
        op = idc.get_operand_value(ea, 0)
        if op == target:
            # Show instructions before the call
            before = []
            prev = ea
            for i in range(3):
                prev = idc.get_prev_head(prev)
                if prev == idc.BADADDR: break
                before.insert(0, idc.generate_disasm_line(prev, 0))
            results.append({"call_addr": f"0x{ea:X}", "before": before})

with open(OUT, 'w') as f:
    json.dump({"calls": results}, f, indent=2)
idc.qexit(0)
