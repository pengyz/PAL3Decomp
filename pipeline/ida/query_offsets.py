"""Query raw IDB for access patterns at specific struct offsets.
Run on raw IDB to verify field types (value vs pointer) without annotations bias.

Usage: idat -A -S"pipeline/ida/_query_offsets.py" original/PAL3.exe.raw.i64
"""
import idaapi
import idautils
import idc
import json
import os

idaapi.auto_wait()

# CCBStageScene method VAs (from annotations/functions.json)
# We need to find methods that access offsets 0x29C, 0x2A0, 0x2A4, 0x2A8, 0x2AC, 0x2CC
# Init is the main one: look around 0x510800

# Query: for each target offset, find all [reg+disp32] accesses in a range of functions
TARGET_OFFSETS = [0x29C, 0x2A0, 0x2A4, 0x2A8, 0x2AC, 0x2B0, 0x2CC, 0x2D0, 0x2D8,
                  0x310, 0x334, 0x354, 0x398, 0x3A4]

# Known CCBStageScene methods from functions.json
METHOD_RANGES = [
    ("Init", 0x005107A0, 0x00510C00),
    ("Reset", 0x005100C0, 0x00510400),
    ("Render", 0x0050FE00, 0x005100C0),
    ("LoadPointer", 0x00510E00, 0x00511000),
    ("_sub_50FD00", 0x0050FD00, 0x0050FE00),
    ("ShowAxis", 0x00511300, 0x00511600),
    ("CCBStageScene_ctor", 0x0050F900, 0x0050FD00),
]

results = {}

for method_name, start_va, end_va in METHOD_RANGES:
    for offset in TARGET_OFFSETS:
        key = f"0x{offset:X}"
        if key not in results:
            results[key] = []

        ea = start_va
        while ea < end_va:
            insn = idaapi.insn_t()
            length = idaapi.decode_insn(insn, ea)
            if length <= 0:
                ea += 1
                continue

            # Check each operand for [reg+disp] matching our offset
            for op_idx in range(min(insn.ops.__len__() if hasattr(insn.ops, '__len__') else 6, 6)):
                op = insn.ops[op_idx]
                if op.type == 0:  # o_void
                    break
                # o_displ (phrase + displacement)
                if op.type in (idaapi.o_displ, idaapi.o_phrase):
                    disp = op.addr if hasattr(op, 'addr') else 0
                    if disp == offset:
                        disasm = idc.generate_disasm_line(ea, 0)
                        reg_names = {0:'eax',1:'ecx',2:'edx',3:'ebx',4:'esp',5:'ebp',6:'esi',7:'edi'}
                        base_reg = reg_names.get(op.reg, f'r{op.reg}')

                        # Determine access width
                        dtype_sizes = {0:1, 1:2, 2:4, 3:8, 4:10, 5:16}
                        width = dtype_sizes.get(op.dtype, 4)

                        # Determine if FPU
                        mnem = idc.print_insn_mnem(ea)
                        is_fpu = mnem.startswith('f') or mnem.startswith('F')

                        results[key].append({
                            "method": method_name,
                            "va": f"0x{ea:08X}",
                            "disasm": disasm,
                            "base_reg": base_reg,
                            "width": width,
                            "is_fpu": is_fpu,
                            "mnemonic": mnem,
                            "op_idx": op_idx,
                        })
            ea += length

# Save results
out_path = os.path.join(os.path.dirname(__file__), "_logs", "offset_query.json")
os.makedirs(os.path.dirname(out_path), exist_ok=True)
with open(out_path, "w", encoding="utf-8") as f:
    json.dump(results, f, indent=2, ensure_ascii=False)

print(f"Saved to {out_path}")
for key, hits in sorted(results.items()):
    print(f"  offset {key}: {len(hits)} hits")

idc.qexit(0)
