"""
Simplified: dump struct info + nearby func disasm.
Usage: idat.exe -A -S"pipeline/ida/_query_cam_struct2.py" original/PAL3.exe.i64
"""
import idaapi, idautils, idc, ida_bytes, ida_struct, ida_funcs
import json, os

idaapi.auto_wait()

LOG_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "_logs")
OUTPUT = os.path.join(LOG_DIR, "cam_struct2.json")

out = {}
out["structs"] = {}

for sname in ["CCBStageCam", "RoleCamera", "gbCamera", "CCBStage"]:
    sid = ida_struct.get_struc_id(sname)
    if sid == -1:
        out["structs"][sname] = {"error": "NOT FOUND"}
        continue
    sptr = ida_struct.get_struc(sid)
    members = []
    n = ida_struct.get_member_qty(sid)
    for i in range(min(n, 60)):
        m = ida_struct.get_member_by_idx(sid, i)
        if m:
            mname = ida_struct.get_member_name(m.id) or "???"
            members.append({"idx": i, "name": mname, "offset": m.soff, "size": m.size, "ea": "0x%X" % m.soff})
    out["structs"][sname] = {"size": sptr.size, "member_count": n, "members": members}

out["funcs"] = {}
for faddr in [0x004D4D30, 0x004D4D70]:
    func = ida_funcs.get_func(faddr)
    if not func:
        continue
    fname = idc.get_func_name(faddr) or ("sub_%X" % faddr)
    dasm = []
    for head in idautils.Heads(func.start_ea, func.end_ea):
        if ida_bytes.is_code(ida_bytes.get_flags(head)):
            dasm.append("0x%08X: %s" % (head, idc.GetDisasm(head)))
    out["funcs"][fname] = dasm

with open(OUTPUT, "w") as f:
    json.dump(out, f, indent=2)
print("OK wrote %s" % OUTPUT)
print("CCBStageCam members: %d" % len(out["structs"].get("CCBStageCam", {}).get("members", [])))
print("gbCamera members: %d" % len(out["structs"].get("gbCamera", {}).get("members", [])))
idc.qexit(0)
