import ida_hexrays, ida_funcs, ida_auto
import os
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
ida_auto.auto_wait()
ea = 0x004CDCA0
func = ida_funcs.get_func(ea)
cfunc = ida_hexrays.decompile(func)
lines = []
for lv in cfunc.lvars:
    lines.append("name=%s type=%s\n" % (lv.name, lv.type.dstr() if lv.type else '?'))
open(os.path.join(SCRIPT_DIR, "_logs", "lvars_simple.txt"), 'w').writelines(lines)
ida_hexrays.term_hexrays()
import ida_ida; ida_ida.qexit(0)
