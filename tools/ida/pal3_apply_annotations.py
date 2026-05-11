"""
IDAPython: 从 annotations.json 批量应用所有标注到当前 IDB。

这是恢复流程的 Layer 4 — 在 master_pipeline (Layer 1-3) 之后执行。
annotations.json 是 PDB base 之上的纯差分层，存储所有人工标注。

用法:
  idat -A -S"tools/ida/pal3_apply_annotations.py" original/PAL3.exe.91.i64

处理:
  1. functions — set_name + SetType (幂等)
  2. globals   — set_name + SetType (幂等)
  3. structs   — build_struct with gap-filling (增量叠加)
  4. enums     — parse_decl (幂等)
"""

import ida_auto
import ida_name
import ida_typeinf
import idautils
import idc
import json
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "annotations.json")


def build_struct_decl(name, struct_info):
    """从 known_members + size 生成带 gap 填充的 C struct 声明。"""
    members = struct_info.get("known_members", {})
    size = struct_info.get("binary_size", 0)

    if not members and not size:
        return None

    # Sort members by offset
    sorted_members = sorted(
        [(int(off), info) for off, info in members.items()],
        key=lambda x: x[0]
    )

    lines = []
    cursor = 0

    for offset, info in sorted_members:
        mname = info["name"]
        mtype = info["type"]

        # Fill gap before this member
        if offset > cursor:
            gap = offset - cursor
            lines.append("    char _gap_%03X[%d];" % (cursor, gap))

        # Emit member
        # Clean type for IDA C parser
        clean_type = mtype.replace("class ", "").replace("struct ", "")
        lines.append("    %s %s;" % (clean_type, mname))

        # Estimate member size (pointers=4, double=8, float=4, int=4, char=1)
        if "*" in mtype:
            msize = 4
        elif mtype == "double":
            msize = 8
        elif mtype == "float":
            msize = 4
        elif mtype in ("char", "unsigned char", "bool"):
            msize = 1
        elif mtype in ("short", "unsigned short"):
            msize = 2
        else:
            msize = 4

        cursor = offset + msize

    # Fill trailing gap to reach target size
    if size > 0 and cursor < size:
        lines.append("    char _tail_%03X[%d];" % (cursor, size - cursor))

    if not lines:
        if size > 0:
            return "struct %s { char _data[%d]; };" % (name, size)
        return None

    return "struct %s {\n%s\n};" % (name, "\n".join(lines))


def apply_annotations():
    ida_auto.auto_wait()

    if not os.path.exists(ANNOTATIONS_FILE):
        print("[!] Not found: %s" % ANNOTATIONS_FILE)
        idc.qexit(1)
        return

    with open(ANNOTATIONS_FILE, "r", encoding="utf-8") as f:
        data = json.load(f)

    # --- 1. Functions ---
    funcs = data.get("functions", {})
    renamed = 0
    sig_ok = 0
    for addr_str, info in funcs.items():
        addr = int(addr_str, 16)
        name = info.get("name", "")
        sig = info.get("signature", "")
        if name:
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                renamed += 1
        if sig:
            if idc.SetType(addr, sig):
                sig_ok += 1

    print("[1] Functions: renamed=%d/%d, signatures=%d" % (renamed, len(funcs), sig_ok))

    # --- 2. Globals ---
    globs = data.get("globals", {})
    g_named = 0
    g_typed = 0
    for addr_str, info in globs.items():
        addr = int(addr_str, 16)
        name = info.get("name", "")
        typ = info.get("type", "")
        if name:
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                g_named += 1
        if typ:
            if idc.SetType(addr, typ + ";"):
                g_typed += 1

    print("[2] Globals: named=%d/%d, typed=%d" % (g_named, len(globs), g_typed))

    # --- 3. Structs (gap-filling build) ---
    structs = data.get("structs", {})
    til = ida_typeinf.get_idati()
    s_ok = 0
    for sname, sinfo in structs.items():
        decl = build_struct_decl(sname, sinfo)
        if not decl:
            continue
        tinfo = ida_typeinf.tinfo_t()
        result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
        if result is not None:
            tinfo.set_named_type(til, sname, ida_typeinf.NTF_REPLACE)
            s_ok += 1
        else:
            print("    [!] struct %s parse failed" % sname)

    print("[3] Structs: applied=%d/%d" % (s_ok, len(structs)))

    # --- 4. Enums ---
    enums = data.get("enums", {})
    e_ok = 0
    for ename, einfo in enums.items():
        values = einfo.get("values", {})
        if not values:
            continue
        member_strs = ["    %s = %s" % (k, v) for k, v in values.items()]
        decl = "enum %s {\n%s\n};" % (ename, ",\n".join(member_strs))
        tinfo = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
            tinfo.set_named_type(til, ename, ida_typeinf.NTF_REPLACE)
            e_ok += 1

    print("[4] Enums: applied=%d/%d" % (e_ok, len(enums)))

    idc.save_database(idc.get_idb_path(), 0)
    print("[*] Done. Database saved.")
    idc.qexit(0)


if __name__ == "__main__":
    apply_annotations()
