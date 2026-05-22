"""Verify Batch 1 candidates: check ALL refs for each field to detect multi-view vs single-type.

For each candidate field, collect all xrefs and their access types.
If ALL accesses are same width/type → safe to change.
If MIXED access types → multi-view, skip.

Output: pipeline/ida/_logs/batch1_verification.json
"""
import idaapi
import idc
import ida_xref
import ida_bytes
import ida_funcs
import ida_struct
import json
import os
import struct as _struct

idaapi.auto_wait()

PROJECT_ROOT = r"D:\workspace\PAL3Decomp"
LOGS_DIR = os.path.join(PROJECT_ROOT, "pipeline", "ida", "_logs", "batch1")
os.makedirs(LOGS_DIR, exist_ok=True)

# Candidates to verify (struct, offset, current_type, suggested_type, function VA)
CANDIDATES = [
    ("CScreenMode", 12, "float", "int *", 0x0052ED30),
    ("CScreenMode", 16, "float", "char *", 0x0052ED30),
    ("CScreenMode", 120, "float", "MainEquipUI *", 0x0047BE20),
    ("RenderTarget", 92, "float", "gbParticleEffect *", 0x004BD880),
    ("UIButton", 100, "BYTE", "char *", 0x0043FF70),
    ("RoleSystem", 52, "float", "unsigned char *", 0x004207D0),
    ("RoleSystem", 16, "float", "RoleSystem *", 0x00420940),
    ("CameraCtrl", 32, "float", "int *", 0x0041D5D0),
    ("SceneObj", 88, "float", "unsigned char *", 0x00453200),
    ("UI3DCtrl", 264, "float", "UI3DModelNode *", 0x0052AF20),
    ("UI3DCtrl", 256, "float", "gbGeomNode *", 0x0052B050),
]

results = {}

for cls_name, offset, cur_type, suggested, func_va in CANDIDATES:
    key = f"{cls_name}+{offset}"

    # Read binary around the function VA to find the instruction accessing this offset
    func = ida_funcs.get_func(func_va)
    if not func:
        results[key] = {"status": "no_func", "offset": offset}
        continue

    # Search for instructions with this displacement in the function
    refs_found = []
    ea = func.start_ea
    while ea < func.end_ea and ea != idc.BADADDR:
        disasm = idc.GetDisasm(ea)
        # Check if this instruction references our offset
        disp_hex = "+%Xh" % offset
        disp_hex2 = "+%xh" % offset
        if disp_hex in disasm or disp_hex2 in disasm or ("+%d" % offset) in disasm:
            mnem = idc.print_insn_mnem(ea)
            # Determine access type
            if mnem in ('fld', 'fstp', 'fadd', 'fsub', 'fmul', 'fdiv', 'fcomp', 'fst'):
                access = 'fpu'
            elif mnem in ('movzx',) and 'byte' in disasm.lower():
                access = 'byte'
            elif mnem in ('mov', 'cmp', 'test', 'add', 'sub', 'or', 'and', 'xor'):
                if 'byte' in disasm.lower():
                    access = 'byte'
                elif 'word' in disasm.lower():
                    access = 'word'
                else:
                    access = 'dword'
            elif mnem == 'lea':
                access = 'lea'
            else:
                access = mnem

            refs_found.append({
                "va": hex(ea),
                "disasm": disasm[:60],
                "access": access,
                "mnem": mnem,
            })

        ea = idc.next_head(ea)

    # Also search other functions that reference this class at this offset
    # (simplified: just report what we found in the specified function)

    access_types = set(r['access'] for r in refs_found)

    # Determine if single-type or multi-view
    if 'fpu' in access_types and len(access_types) == 1:
        verdict = "confirmed_float"
    elif 'fpu' in access_types and access_types - {'fpu'}:
        verdict = "mixed_float_and_other"  # multi-view
    elif access_types == {'dword'} or access_types == {'lea'}:
        verdict = "ambiguous_dword"  # could be int or pointer
    elif access_types == {'byte'}:
        verdict = "confirmed_byte"
    else:
        verdict = "needs_manual_review"

    results[key] = {
        "struct": cls_name,
        "offset": offset,
        "current_type": cur_type,
        "suggested_type": suggested,
        "refs_in_func": refs_found,
        "access_types": list(access_types),
        "verdict": verdict,
    }

# Write results
out_path = os.path.join(LOGS_DIR, "batch1_verification.json")
with open(out_path, "w", encoding="utf-8") as f:
    json.dump(results, f, indent=2, ensure_ascii=False)

print(f"[*] Verified {len(results)} candidates")
for key, r in results.items():
    print(f"  {key}: {r['verdict']} (accesses: {r.get('access_types', [])})")

idc.qexit(0)
