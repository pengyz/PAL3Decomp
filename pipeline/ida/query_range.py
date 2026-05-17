"""Query all accesses to [reg+disp] where disp is in a specific range, across all CCBStageScene functions.
Run on raw IDB.
"""
import idaapi
import idautils
import idc
import json
import os

idaapi.auto_wait()

# Search range: 0x290 to 0x2CC (area between known fields and Quad start)
DISP_MIN = 0x290
DISP_MAX = 0x2CC

# Also include 0x2EC-0x340 (Quad boundaries)
DISP_RANGES = [(0x290, 0x2CC), (0x2EC, 0x340), (0x370, 0x3C0)]

# All known CCBStageScene methods (approximate VAs)
# We'll scan a large range: 0x50F000-0x512000 + 0x52B000-0x52C000
SCAN_RANGES = [
    (0x0050F000, 0x00512000),
    (0x0052B000, 0x0052C000),
]

results = []

for scan_start, scan_end in SCAN_RANGES:
    ea = scan_start
    while ea < scan_end:
        insn = idaapi.insn_t()
        length = idaapi.decode_insn(insn, ea)
        if length <= 0:
            ea += 1
            continue

        for op_idx in range(6):
            op = insn.ops[op_idx]
            if op.type == 0:
                break
            if op.type in (idaapi.o_displ, idaapi.o_phrase):
                disp = op.addr if hasattr(op, 'addr') else 0
                for dmin, dmax in DISP_RANGES:
                    if dmin <= disp <= dmax:
                        reg_names = {0:'eax',1:'ecx',2:'edx',3:'ebx',4:'esp',5:'ebp',6:'esi',7:'edi'}
                        base_reg = reg_names.get(op.reg, f'r{op.reg}')
                        if base_reg in ('esp', 'ebp'):
                            break  # skip stack
                        mnem = idc.print_insn_mnem(ea)
                        disasm = idc.generate_disasm_line(ea, 0)
                        dtype_sizes = {0:1, 1:2, 2:4, 3:8, 4:10, 5:16}
                        width = dtype_sizes.get(op.dtype, 4)
                        func = idaapi.get_func(ea)
                        func_name = idc.get_func_name(ea) if func else "?"
                        results.append({
                            "va": f"0x{ea:08X}",
                            "disp": f"0x{disp:X}",
                            "base_reg": base_reg,
                            "mnem": mnem,
                            "width": width,
                            "disasm": disasm,
                            "func": func_name,
                        })
                        break
        ea += length

# Sort by disp
results.sort(key=lambda x: int(x['disp'], 16))

out_path = os.path.join(os.path.dirname(__file__), "_logs", "range_query.json")
os.makedirs(os.path.dirname(out_path), exist_ok=True)
with open(out_path, "w", encoding="utf-8") as f:
    json.dump(results, f, indent=2, ensure_ascii=False)

print(f"Found {len(results)} accesses")
# Group by disp
from collections import defaultdict
by_disp = defaultdict(list)
for r in results:
    by_disp[r['disp']].append(r)
for disp in sorted(by_disp.keys(), key=lambda x: int(x, 16)):
    hits = by_disp[disp]
    print(f"  {disp}: {len(hits)} hits")
    for h in hits[:3]:
        print(f"    [{h['func']}] {h['disasm']}")

idc.qexit(0)
