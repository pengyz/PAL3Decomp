"""Decompile the remaining 175 small unlisted functions (11-50B)."""
import ida_auto, ida_hexrays, ida_name, ida_funcs, idc
import json, os

ida_auto.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

# Load what's NOT covered
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
with open(os.path.join(PROJECT_ROOT, "data/annotations/functions.json"), 'r', encoding='utf-8') as f:
    ann = json.load(f)
with open(os.path.join(PROJECT_ROOT, "data/annotations/skip_functions.json"), 'r', encoding='utf-8') as f:
    skip = json.load(f)

ann_addrs = set(int(a,16) for a in ann.keys())
skip_addrs = set(int(a,16) for a in skip.keys())

results = []
import idautils
for ea in idautils.Functions(0x401000, 0x540000):
    if ea in ann_addrs or ea in skip_addrs:
        continue
    func = ida_funcs.get_func(ea)
    if not func or func.size() <= 10 or func.size() > 50:
        continue
    
    name = ida_name.get_name(ea) or ""
    try:
        cfunc = ida_hexrays.decompile(ea)
        code = str(cfunc)[:300] if cfunc else "FAILED"
        sig = cfunc.type.dstr() if cfunc else ""
    except:
        code = "EXCEPTION"
        sig = ""
    
    results.append({
        "address": "0x%08X" % ea,
        "size": func.size(),
        "name": name,
        "sig": sig,
        "code": code,
    })

output_path = os.path.join(LOG_DIR, "unlisted_small_decompiled.json")
with open(output_path, 'w', encoding='utf-8') as f:
    json.dump(results, f, indent=2, ensure_ascii=False)
print("[*] Decompiled %d small unlisted functions" % len(results))
idc.qexit(0)
