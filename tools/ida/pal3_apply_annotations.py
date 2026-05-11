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


def build_struct_decl(name, struct_info, all_structs=None):
    """从 known_members + size 生成带 gap 填充的 C struct 声明。支持基类继承和数组类型。"""
    import re as _re
    if all_structs is None:
        all_structs = {}

    members = struct_info.get("known_members", {})
    size = max(struct_info.get("binary_size", 0), struct_info.get("pdb_size", 0), struct_info.get("gen_size", 0))
    base_class = struct_info.get("base_class")
    base_size = struct_info.get("base_size", 0)

    if not members and not size:
        return None

    sorted_members = sorted(
        [(int(off), info) for off, info in members.items() if int(off) >= base_size],
        key=lambda x: x[0]
    )

    def next_member_offset(current_offset):
        for off, _ in sorted_members:
            if off > current_offset:
                return off
        return size if size > 0 else current_offset

    lines = []
    cursor = base_size

    for offset, info in sorted_members:
        mname = info["name"]
        mtype = info["type"].replace("class ", "").replace("struct ", "")

        if offset > cursor:
            lines.append("    char _gap_%03X[%d];" % (cursor, offset - cursor))

        arr_match = _re.search(r'(\[\d+\](?:\[\d+\])*)$', mtype)

        if 'std::' in mtype or '::' in mtype or '<' in mtype:
            span = next_member_offset(offset) - offset
            lines.append("    char %s[%d]; // %s" % (mname, max(span, 4), mtype))
            cursor = offset + max(span, 4)
        elif arr_match:
            base_type = mtype[:arr_match.start()].rstrip()
            lines.append("    %s %s%s;" % (base_type, mname, arr_match.group(1)))
            cursor = next_member_offset(offset)
        else:
            lines.append("    %s %s;" % (mtype, mname))
            if "*" in mtype:        cursor = offset + 4
            elif mtype == "double": cursor = offset + 8
            elif mtype == "float":  cursor = offset + 4
            elif mtype in ("char", "unsigned char", "bool", "BYTE"): cursor = offset + 1
            elif mtype in ("short", "unsigned short", "WORD"):       cursor = offset + 2
            else:
                # Look up type size from all_structs
                clean = mtype.replace("class ", "").replace("struct ", "").strip()
                ref_size = 0
                if clean in all_structs:
                    ref = all_structs[clean]
                    ref_size = max(ref.get("pdb_size", 0), ref.get("binary_size", 0))
                cursor = offset + (ref_size if ref_size > 0 else 4)

    if size > 0 and cursor < size:
        lines.append("    char _tail_%03X[%d];" % (cursor, size - cursor))

    if not lines:
        if size > 0:
            inherit = " : public %s" % base_class if base_class else ""
            data_size = size - base_size if base_class else size
            return "struct %s%s { char _data[%d]; };" % (name, inherit, data_size)
        return None

    inherit = " : public %s" % base_class if base_class else ""
    return "struct %s%s {\n%s\n};" % (name, inherit, "\n".join(lines))


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

    # --- 3. Structs (gap-filling build, base classes first) ---
    structs = data.get("structs", {})
    til = ida_typeinf.get_idati()

    # Topological sort: dependencies (base classes + value-type members) first
    import re as _re2
    all_struct_names = set(structs.keys())

    def get_deps(sinfo):
        deps = set()
        base = sinfo.get("base_class")
        if base and base in all_struct_names:
            deps.add(base)
        for off, m in sinfo.get("known_members", {}).items():
            mtype = m["type"].replace("class ", "").replace("struct ", "")
            if "*" in mtype:
                continue
            base_type = _re2.sub(r'\[.*\]', '', mtype).strip()
            if base_type in all_struct_names:
                deps.add(base_type)
        return deps

    ordered = []
    remaining = dict(structs)
    done = set()
    for _ in range(20):
        batch = []
        for sname, sinfo in list(remaining.items()):
            deps = get_deps(sinfo)
            if deps <= done:
                batch.append(sname)
        if not batch:
            break
        for sname in batch:
            ordered.append((sname, remaining.pop(sname)))
            done.add(sname)
    ordered.extend(remaining.items())

    s_ok = 0
    s_fail = []
    for sname, sinfo in ordered:
        decl = build_struct_decl(sname, sinfo, structs)
        if not decl:
            continue
        tinfo = ida_typeinf.tinfo_t()
        result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
        if result is not None:
            tinfo.set_named_type(til, sname, ida_typeinf.NTF_REPLACE)
            s_ok += 1
        else:
            s_fail.append((sname, sinfo))


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
