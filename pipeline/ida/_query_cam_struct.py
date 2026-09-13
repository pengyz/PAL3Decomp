"""
Query camera struct layout and check overlap at offset 0.
Usage: idat.exe -A -S"pipeline/ida/_query_cam_struct.py" original/PAL3.exe.i64
"""
import idaapi, idautils, idc, ida_bytes, ida_struct
import json, os

idaapi.auto_wait()

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT = os.path.join(LOG_DIR, "cam_struct_query.json")

STRUCTS = ["CCBStageCam", "RoleCamera", "gbCamera", "CCBStage"]
FUNCS = [0x004D4D30, 0x004D4D70]  # GetTaskParam, SetTaskState

result = {}

# 1) Query struct layouts
for sname in STRUCTS:
    sid = ida_struct.get_struc_id(sname)
    if sid == -1:
        result[sname] = {"error": "struct not found"}
        continue
    struc = ida_struct.get_struc(sid)
    members = []
    for i in range(ida_struct.get_member_qty(sid)):
        m = ida_struct.get_member_by_idx(sid, i)
        if m:
            mname = ida_struct.get_member_name(m.id)
            moff = m.soff  # start offset
            msize = m.size
            members.append({"name": mname, "offset": moff, "size": msize})
    result[sname] = {
        "size": struc.size if struc else -1,
        "members": members,
    }

# 2) For each function, disasm and show how m_pCam is used
for faddr in FUNCS:
    func = ida_funcs.get_func(faddr)
    if not func:
        continue
    fname = idc.get_func_name(faddr)
    disasm_lines = []
    for head in idautils.Heads(func.start_ea, func.end_ea):
        if ida_bytes.is_code(ida_bytes.get_flags(head)):
            disasm_lines.append("0x%08X: %s" % (head, idc.GetDisasm(head)))
    # Also get Hex-Rays decomp
    try:
        import ida_hexrays
        cfunc = ida_hexrays.decompile(faddr)
        decomp = str(cfunc)
    except:
        decomp = "(failed)"
    result[fname] = {
        "disasm": disasm_lines,
        "decomp": decomp,
    }

with open(OUTPUT, "w", encoding="utf-8") as f:
    json.dump(result, f, indent=2, ensure_ascii=False)

print("[OK] Wrote %s" % OUTPUT)

# Print struct member summary for camera types
for sname in ["CCBStageCam", "gbCamera"]:
    if sname in result and "members" in result[sname]:
        print("\n=== %s (size=%d) ===" % (sname, result[sname]["size"]))
        for m in result[sname]["members"][:30]:
            print("  +0x%04X (%3d): %s" % (m["offset"], m["size"], m["name"]))
        if len(result[sname]["members"]) > 30:
            print("  ... (%d more)" % (len(result[sname]["members"]) - 30))

idc.qexit(0)
