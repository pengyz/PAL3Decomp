"""Query raw IDB for all memory accesses with displacement in a specific function.
Run on raw IDB: idat -A -S"pipeline/ida/_query_method.py" original/PAL3.exe.raw.i64
"""
import idaapi
import idautils
import idc
import json
import os

idaapi.auto_wait()

# Functions to analyze
FUNCTIONS = [
    ("CCBStageScene::_method_52b2a0", 0x0052B2A0),
    ("CCBStageScene::CCBStageScene", 0x0050F900),
    ("CCBStageScene::_sub_50FD00", 0x0050FD00),
    ("CCBStageScene::Init", 0x005107A0),
]

results = {}

for func_name, func_va in FUNCTIONS:
    func = idaapi.get_func(func_va)
    if not func:
        results[func_name] = {"error": f"no function at {hex(func_va)}"}
        continue

    accesses = []
    ea = func.start_ea
    while ea < func.end_ea:
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
                if disp > 0 and disp < 0x10000:
                    reg_names = {0:'eax',1:'ecx',2:'edx',3:'ebx',4:'esp',5:'ebp',6:'esi',7:'edi'}
                    base_reg = reg_names.get(op.reg, f'r{op.reg}')
                    mnem = idc.print_insn_mnem(ea)
                    disasm = idc.generate_disasm_line(ea, 0)
                    dtype_sizes = {0:1, 1:2, 2:4, 3:8, 4:10, 5:16}
                    width = dtype_sizes.get(op.dtype, 4)
                    accesses.append({
                        "va": f"0x{ea:08X}",
                        "disp": f"0x{disp:X}",
                        "base_reg": base_reg,
                        "mnem": mnem,
                        "width": width,
                        "disasm": disasm,
                        "op_idx": op_idx,
                    })
        ea += length

    results[func_name] = accesses

out_path = os.path.join(os.path.dirname(__file__), "_logs", "method_accesses.json")
os.makedirs(os.path.dirname(out_path), exist_ok=True)
with open(out_path, "w", encoding="utf-8") as f:
    json.dump(results, f, indent=2, ensure_ascii=False)

print(f"Saved to {out_path}")
for name, data in results.items():
    if isinstance(data, list):
        print(f"  {name}: {len(data)} accesses")
    else:
        print(f"  {name}: {data}")

idc.qexit(0)
