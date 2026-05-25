"""Decompile specific addresses and output results."""
import ida_auto, ida_hexrays, ida_name, ida_funcs, idc
import json, os

ida_auto.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

ADDRS = [0x0053DF70]

results = {}
for ea in ADDRS:
    func = ida_funcs.get_func(ea)
    if not func:
        results[hex(ea)] = {"error": "no function"}
        continue
    name = ida_name.get_name(ea)
    try:
        cfunc = ida_hexrays.decompile(ea)
        code = str(cfunc) if cfunc else "decompile failed"
        sig = cfunc.type.dstr() if cfunc else ""
    except:
        code = "exception"
        sig = ""
    results[hex(ea)] = {"name": name, "size": func.size(), "sig": sig, "code": code}
    print("0x%08X (%s, %d bytes):" % (ea, name, func.size()))
    print(code)

with open(os.path.join(LOG_DIR, "decompile_addr.json"), 'w') as f:
    json.dump(results, f, indent=2, ensure_ascii=False)
idc.qexit(0)
