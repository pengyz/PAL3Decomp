"""Decompile unlisted functions to categorize them."""
import ida_auto, ida_hexrays, ida_name, ida_funcs, idc
import json, os

ida_auto.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

# Load unlisted functions
with open(os.path.join(LOG_DIR, "unlisted_functions.json"), 'r') as f:
    data = json.load(f)

# Focus on medium+large game-area functions (>50B, <0x540000)
targets = [f for f in data['unnamed'] 
           if f['size'] > 50 and int(f['address'], 16) < 0x540000]
targets.sort(key=lambda x: -x['size'])

results = []
for entry in targets[:30]:  # Analyze top 30 by size
    ea = int(entry['address'], 16)
    try:
        ida_hexrays.mark_cfunc_dirty(ea)
        cfunc = ida_hexrays.decompile(ea)
        if cfunc:
            code = str(cfunc)
            sig = cfunc.type.dstr()
        else:
            code = "FAILED"
            sig = ""
    except:
        code = "EXCEPTION"
        sig = ""
    
    results.append({
        "address": entry['address'],
        "size": entry['size'],
        "ida_name": entry['name'],
        "signature": sig,
        "code": code[:500],  # First 500 chars only
    })

output_path = os.path.join(LOG_DIR, "unlisted_decompiled.json")
with open(output_path, 'w', encoding='utf-8') as f:
    json.dump(results, f, indent=2, ensure_ascii=False)
print("[*] Decompiled %d unlisted functions" % len(results))
idc.qexit(0)
