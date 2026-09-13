"""Query struct overlap at CCBStageCam base."""
import idaapi, idautils, idc, ida_bytes, ida_funcs

idaapi.auto_wait()
out_path = r"D:\workspace\PAL3Decomp\pipeline\ida\_logs\_overlap.txt"
f = open(out_path, "w")

# First, list all structs
f.write("=== All structs in IDB ===\n")
for i in range(30):
    sname = idc.get_struc_by_idx(i)
    if sname:
        sid = idc.get_struc_id(sname)
        sz = idc.get_struc_size(sid)
        f.write("  [%d] %s (size=%d, sid=%d)\n" % (i, sname, sz, sid))
f.write("\n")

# Use IDC compatibility functions for struct access
for sname in ["gbCamera", "RoleCamera", "CCBStageCam"]:
    sid = idc.get_struc_id(sname)
    f.write("=== %s: sid=%d ===\n" % (sname, sid))
    if sid == -1:
        continue
    n = idc.get_member_qty(sid)
    for i in range(n):
        mname = idc.get_member_name(sid, i)
        moff = idc.get_member_offset(sid, i)
        msize = idc.get_member_size(sid, i)
        f.write("  [%2d] +0x%04x (%3dB) %s\n" % (i, moff, msize, mname))
    m0_name = idc.get_member_name(sid, 0)
    f.write("  member@0: %s\n" % m0_name)

# Check what's at offset 152 in gbCamera
sid_cam = idc.get_struc_id("gbCamera")
if sid_cam != -1:
    f.write("\n=== gbCamera offset probes ===\n")
    for off in [0, 148, 152, 156]:
        mname = idc.get_member_name(sid_cam, off)
        if mname:
            f.write("  @%d: %s\n" % (off, mname))

# Check CCBStageCam
sid_ccb = idc.get_struc_id("CCBStageCam")
if sid_ccb != -1:
    f.write("\n=== CCBStageCam offset probes ===\n")
    n = idc.get_member_qty(sid_ccb)
    f.write("  total members: %d\n" % n)
    for off in [0, 152, 692, 736]:
        mname = idc.get_member_name(sid_ccb, off)
        if mname:
            msize = idc.get_member_size(sid_ccb, off)
            f.write("  @%d: %s (size=%d)\n" % (off, mname, msize))

f.close()
print("OK")
idc.qexit(0)
