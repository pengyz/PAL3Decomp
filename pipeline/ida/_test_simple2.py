import idaapi, idautils, ida_funcs, idc, ida_ua, ida_bytes
idaapi.auto_wait()

path = r"D:\workspace\PAL3Decomp\pipeline\ida\_logs\_test2.txt"
f = open(path, "w")
# Just disasm GetTaskParam
func = ida_funcs.get_func(0x004D4D30)
f.write("func at 0x4D4D30: %s\n" % ("OK" if func else "NULL"))
if func:
    f.write("start=0x%X end=0x%X size=%d\n" % (func.start_ea, func.end_ea, func.end_ea - func.start_ea))
    for head in idautils.Heads(func.start_ea, func.end_ea):
        if ida_bytes.is_code(ida_bytes.get_flags(head)):
            f.write("0x%08X: %s\n" % (head, idc.GetDisasm(head)))
f.close()
import sys; sys.stdout.flush()
idc.qexit(0)
