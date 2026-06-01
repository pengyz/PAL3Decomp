"""Dump lvars for CEffMgr::CreateEffect"""
import ida_hexrays, ida_funcs, ida_auto, ida_ida, ida_typeinf
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

ida_auto.auto_wait()
ea = 0x004CDCA0
func = ida_funcs.get_func(ea)
cfunc = ida_hexrays.decompile(func)

lines = ["LVAR DUMP for CEffMgr::CreateEffect (0x004CDCA0)\n"]
lines.append("=============================================\n")
for lv in cfunc.lvars:
    loc = lv.location
    stkoff = loc.stkoff() if loc.is_stkoff() else -1
    tname = lv.type.dstr() if lv.type else '?'
    lines.append("  name=%-12s stack=%-6s type=%s\n" % (lv.name, str(stkoff), tname))

# Also dump the decompiled code
code = str(cfunc)
lines.append("\n--- Decompiled code (first 2000 chars) ---\n")
lines.append(code[:2000])

with open(os.path.join(LOG_DIR, "lvar_dump.txt"), 'w') as f:
    f.writelines(lines)
print("[*] Dumped to lvar_dump.txt")

ida_hexrays.term_hexrays()
ida_ida.qexit(0)
