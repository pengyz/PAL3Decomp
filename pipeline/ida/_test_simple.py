import idaapi, ida_struct, idc, ida_funcs
idaapi.auto_wait()

path = r"D:\workspace\PAL3Decomp\pipeline\ida\_logs\_test_out.txt"
with open(path, "w") as f:
    # Check structs
    for sn in ["gbCamera", "CCBStageCam", "RoleCamera"]:
        sid = ida_struct.get_struc_id(sn)
        f.write("%s: sid=%d\n" % (sn, sid))
        if sid != -1:
            sptr = ida_struct.get_struc(sid)
            f.write("  size=%d\n" % sptr.size)
            for i in range(ida_struct.get_member_qty(sid)):
                m = ida_struct.get_member_by_idx(sid, i)
                if m:
                    mn = ida_struct.get_member_name(m.id) or "?"
                    f.write("  [%d] %s @+0x%X size=%d\n" % (i, mn, m.soff, m.size))
    # Check function
    func = ida_funcs.get_func(0x004D4D30)
    fn = idc.get_func_name(0x004D4D30)
    f.write("\n0x004D4D30: func=%s exists=%s\n" % (fn, "yes" if func else "no"))
    
import sys
sys.stdout.flush()
idc.qexit(0)
