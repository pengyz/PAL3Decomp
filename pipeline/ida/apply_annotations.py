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
import ida_funcs
import ida_hexrays
import ida_name
import ida_typeinf
import idautils
import idc
import json
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "pipeline", "data", "annotations")


def build_struct_decl(name, struct_info, all_structs=None, vtables=None):
    """从 known_members + size 生成带 gap 填充的 C struct 声明。支持基类继承、数组类型和虚函数。"""
    import re as _re
    if all_structs is None:
        all_structs = {}
    if vtables is None:
        vtables = {}

    members = struct_info.get("known_members", {})
    size = struct_info.get("binary_size") or struct_info.get("pdb_size") or struct_info.get("gen_size") or 0
    base_class = struct_info.get("base_class")
    base_size = struct_info.get("base_size", 0)

    # IDA parse_decl cannot handle C++ template base classes
    if base_class and ('<' in base_class or '>' in base_class):
        base_class = None  # drop template inheritance, use gap instead

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

    # 查找此类的 vtable（只处理无基类的，有基类时 vtable 由基类定义）
    virtual_methods = None
    if not base_class:
        for vt_name, vt_info in vtables.items():
            if vt_info.get("class") == name:
                virtual_methods = vt_info.get("methods", [])
                break

    lines = []
    cursor = base_size

    for offset, info in sorted_members:
        mname = info["name"]
        mtype = info["type"].replace("class ", "").replace("struct ", "")

        if offset > cursor:
            lines.append("    char _gap_%03X[%d];" % (cursor, offset - cursor))

        # vfptr: 用 vtbl struct 指针（IDA 反编译输出最优）
        if offset == 0 and mname == "vfptr" and virtual_methods:
            vt_struct_name = None
            for vt_name, vt_info in vtables.items():
                if vt_info.get("class") == name:
                    vt_struct_name = "vtbl_%s" % vt_info["address"][2:]
                    break
            if vt_struct_name:
                lines.append("    %s *__vftable;" % vt_struct_name)
            else:
                lines.append("    int vfptr;")
            cursor = offset + 4
            continue

        arr_match = _re.search(r'(\[\d+\](?:\[\d+\])*)$', mtype)

        if 'std::' in mtype or '::' in mtype or '<' in mtype:
            span = next_member_offset(offset) - offset
            lines.append("    char %s[%d]; // %s" % (mname, max(span, 4), mtype))
            cursor = offset + max(span, 4)
        elif arr_match:
            base_type = mtype[:arr_match.start()].rstrip()
            lines.append("    %s %s%s;" % (base_type, mname, arr_match.group(1)))
            elem_size = 0
            if "*" in base_type:
                elem_size = 4
            elif base_type in ("double",):
                elem_size = 8
            elif base_type in ("float", "int", "unsigned int", "DWORD", "LONG", "UINT",
                               "unsigned long"):
                elem_size = 4
            elif base_type in ("short", "unsigned short", "WORD"):
                elem_size = 2
            elif base_type in ("char", "unsigned char", "bool", "BYTE"):
                elem_size = 1
            else:
                clean = base_type.replace("class ", "").replace("struct ", "").strip()
                if clean in all_structs:
                    ref = all_structs[clean]
                    elem_size = ref.get("binary_size") or ref.get("pdb_size") or ref.get("gen_size") or ref.get("size") or 0
            if elem_size > 0:
                dims = [int(d) for d in _re.findall(r'\[(\d+)\]', arr_match.group(1))]
                total_elems = 1
                for d in dims:
                    total_elems *= d
                cursor = offset + total_elems * elem_size
                # FATAL: type size exceeds span — annotations data error
                nmo = next_member_offset(offset)
                if nmo > offset and cursor > nmo:
                    print("[!] LAYOUT ERROR in %s: member '%s %s%s' at +%d has type_size=%d but span=%d (next at +%d)" %
                          (name, base_type, mname, arr_match.group(1), offset, total_elems * elem_size, nmo - offset, nmo))
                    cursor = nmo  # clamp to avoid negative gap, but struct will have wrong member
            else:
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
                    ref_size = ref.get("binary_size") or ref.get("pdb_size") or 0
                cursor = offset + (ref_size if ref_size > 0 else 4)
                # FATAL: type size exceeds span — annotations data error
                nmo = next_member_offset(offset)
                if nmo > offset and cursor > nmo:
                    print("[!] LAYOUT ERROR in %s: member '%s %s' at +%d has type_size=%d but span=%d (next at +%d)" %
                          (name, mtype, mname, offset, ref_size if ref_size > 0 else 4, nmo - offset, nmo))
                    cursor = nmo  # clamp to avoid negative gap

    if size > 0 and cursor < size:
        lines.append("    char _tail_%03X[%d];" % (cursor, size - cursor))

    if not lines:
        if size > 0:
            inherit = " : public %s" % base_class if base_class else ""
            data_size = size - base_size if base_class else size
            return "struct %s%s { char _data[%d]; };" % (name, inherit, data_size)
        return None

    inherit = " : public %s" % base_class if base_class else ""
    # Only use pack(1) for structs explicitly marked (file format headers, etc.)
    pack = struct_info.get("pack")
    if pack == 1:
        return "#pragma pack(push, 1)\nstruct %s%s {\n%s\n};\n#pragma pack(pop)" % (name, inherit, "\n".join(lines))
    return "struct %s%s {\n%s\n};" % (name, inherit, "\n".join(lines))


def load_annotations():
    """从拆分目录加载标注数据。"""
    if not os.path.isdir(ANNOTATIONS_DIR):
        return None

    print("[*] Loading annotations from: %s" % ANNOTATIONS_DIR)
    with open(os.path.join(ANNOTATIONS_DIR, "functions.json"), "r", encoding="utf-8") as f:
        functions = json.load(f)
    with open(os.path.join(ANNOTATIONS_DIR, "globals.json"), "r", encoding="utf-8") as f:
        globals_data = json.load(f)
    structs = {}
    structs_dir = os.path.join(ANNOTATIONS_DIR, "structs")
    for fname in os.listdir(structs_dir):
        if not fname.endswith(".json"):
            continue
        with open(os.path.join(structs_dir, fname), "r", encoding="utf-8") as f:
            sdata = json.load(f)
        sname = sdata.pop("name", fname.replace(".json", ""))
        structs[sname] = sdata
    with open(os.path.join(ANNOTATIONS_DIR, "vtables.json"), "r", encoding="utf-8") as f:
        vtables = json.load(f)
    enums = {}
    enums_path = os.path.join(ANNOTATIONS_DIR, "enums.json")
    if os.path.exists(enums_path):
        with open(enums_path, "r", encoding="utf-8") as f:
            enums = json.load(f)
    return {
        "functions": functions,
        "globals": globals_data,
        "structs": structs,
        "enums": enums,
        "vtables": vtables,
    }


def apply_annotations():
    ida_auto.auto_wait()

    data = load_annotations()
    if data is None:
        print("[!] No annotations found")
        idc.qexit(1)
        return

    # --- 0. Un-name functions no longer in annotations (revert to sub_XXXXXX) ---
    import ida_funcs as _ida_funcs
    _ann_addrs = set()
    for _k in data.get("functions", {}):
        _ann_addrs.add(int(_k, 16))
    _skip_path = os.path.join(ANNOTATIONS_DIR, "skip_functions.json")
    if os.path.exists(_skip_path):
        for _k in json.load(open(_skip_path, encoding="utf-8")):
            _ann_addrs.add(int(_k, 16))
    _unnamed = 0
    for ea in idautils.Functions(0x00401000, 0x00560000):
        cur = ida_name.get_name(ea) or ""
        if cur.startswith("sub_") or not cur:
            continue
        if ea not in _ann_addrs:
            ida_name.set_name(ea, "", ida_name.SN_NOWARN)
            _unnamed += 1
    print("[0] Un-named %d stale functions" % _unnamed)

    # --- 1. Functions (ensure exist + rename, signatures deferred to step 6) ---
    import re as _re_fn
    funcs = data.get("functions", {})
    created = 0
    renamed = 0
    for addr_str, info in funcs.items():
        addr = int(addr_str, 16)
        name = info.get("name", "")
        if not _ida_funcs.get_func(addr):
            if _ida_funcs.add_func(addr):
                created += 1
        if name:
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                renamed += 1

    # Also name skip_functions (not decompiled, but callers need their names)
    skip_path = os.path.join(ANNOTATIONS_DIR, "skip_functions.json")
    skip_named = 0
    if os.path.exists(skip_path):
        with open(skip_path, "r", encoding="utf-8") as f:
            skip_funcs = json.load(f)
        for addr_str, info in skip_funcs.items():
            name = info.get("name", "")
            if name and not name.startswith("sub_"):
                addr = int(addr_str, 16)
                if not _ida_funcs.get_func(addr):
                    _ida_funcs.add_func(addr)
                if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                    skip_named += 1

    print("[1] Functions: created=%d, renamed=%d/%d, skip_named=%d" % (created, renamed, len(funcs), skip_named))

    # --- 2. Globals (names only; types deferred to step 6b after structs) ---
    globs = data.get("globals", {})
    g_named = 0
    for addr_str, info in globs.items():
        addr = int(addr_str, 16)
        name = info.get("name", "")
        if name:
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                g_named += 1

    print("[2] Globals: named=%d/%d (types deferred)" % (g_named, len(globs)))

    # --- 3. Structs (gap-filling build, base classes first) ---
    structs = data.get("structs", {})
    til = ida_typeinf.get_idati()

    # Forward-declare ALL type names referenced in struct members
    import re as _re_fwd
    _primitives = {
        "char", "int", "float", "double", "short", "long", "unsigned",
        "unsigned char", "unsigned short", "unsigned int", "unsigned long",
        "void", "bool", "BYTE", "WORD", "DWORD", "UINT", "LONG", "BOOL",
        "HRESULT", "__int64", "_DWORD", "_BYTE", "_WORD",
    }
    fwd_names = set(structs.keys())
    for sinfo in structs.values():
        for m in sinfo.get("known_members", {}).values():
            mtype = m["type"].replace("class ", "").replace("struct ", "")
            # Extract base type (strip pointers and arrays)
            base = _re_fwd.sub(r'\[.*\]', '', mtype).replace("*", "").strip()
            if base and base not in _primitives:
                fwd_names.add(base)
    fwd_ok = 0
    fwd_skip = 0
    for name in sorted(fwd_names):
        # Skip if type already exists in til (could be enum, typedef, or PDB-imported struct)
        existing = ida_typeinf.tinfo_t()
        if existing.get_named_type(til, name):
            fwd_skip += 1
            continue
        fwd_decl = "struct %s;" % name
        tinfo = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(tinfo, til, fwd_decl, ida_typeinf.PT_TYP) is not None:
            tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
            fwd_ok += 1
    print("[3a] Forward declarations: %d new, %d skipped (already in til)" % (fwd_ok, fwd_skip))

    # --- 3b. Enums (BEFORE structs — struct members may reference enum types) ---
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
    print("[3b] Enums: applied=%d/%d" % (e_ok, len(enums)))

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

    vtables = data.get("vtables", {})

    # Pre-create vtable structs so class structs can reference them
    import re as _re3
    vt_pre = 0
    for vt_name, vt_info in vtables.items():
        methods = vt_info.get("methods", [])
        if not methods:
            continue
        struct_name = "vtbl_%s" % vt_info["address"][2:]
        lines = []
        seen_names = set()
        for i, m in enumerate(methods):
            sig = m.get("signature", "")
            mname = m.get("name", "")
            short = "method_%d" % i
            if "::" in mname:
                short = mname.split("::")[-1]
                short = _re3.sub(r'[^a-zA-Z0-9_]', '_', short)
            elif mname.startswith("sub_"):
                short = mname
            if short in seen_names:
                short = "%s_%d" % (short, i)
            seen_names.add(short)
            if sig:
                sig_clean = sig.strip().rstrip(";")
                fp_match = _re3.match(r'^(.+?)(\s+__\w+)?\s+\w+\s*(\(.*\))$', sig_clean)
                if fp_match:
                    ret = fp_match.group(1).strip()
                    cc = fp_match.group(2) or ""
                    args = fp_match.group(3)
                    lines.append("    %s (%s*%s)%s;" % (ret, cc.strip() + " " if cc.strip() else "", short, args))
                else:
                    lines.append("    int (*%s)();" % short)
            else:
                lines.append("    int (*%s)();" % short)
        decl = "struct %s {\n%s\n};" % (struct_name, "\n".join(lines))
        tinfo = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
            tinfo.set_named_type(til, struct_name, ida_typeinf.NTF_REPLACE)
            vt_pre += 1
    print("[3a] Vtable structs pre-created: %d/%d" % (vt_pre, len(vtables)))

    s_ok = 0
    s_fail = []
    for sname, sinfo in ordered:
        decl = build_struct_decl(sname, sinfo, structs, vtables)
        if not decl:
            continue
        tinfo = ida_typeinf.tinfo_t()
        result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
        if result is not None:
            tinfo.set_named_type(til, sname, ida_typeinf.NTF_REPLACE)
            s_ok += 1
        else:
            s_fail.append((sname, sinfo))

    # Retry failed structs until no more progress
    for retry in range(50):
        if not s_fail:
            break
        still_fail = []
        resolved = 0
        for sname, sinfo in s_fail:
            decl = build_struct_decl(sname, sinfo, structs, vtables)
            if not decl:
                continue
            tinfo = ida_typeinf.tinfo_t()
            result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
            if result is not None:
                tinfo.set_named_type(til, sname, ida_typeinf.NTF_REPLACE)
                s_ok += 1
                resolved += 1
            else:
                still_fail.append((sname, sinfo))
        s_fail = still_fail
        if resolved == 0:
            break  # no progress, stop retrying

    if s_fail:
        for sname, sinfo in s_fail:
            decl = build_struct_decl(sname, sinfo, structs, vtables)
            decl_preview = (decl[:200] + '...') if decl and len(decl) > 200 else decl
            print("[!] Struct failed: %s (decl_len=%d, members=%d)" % (
                sname, len(decl) if decl else 0, len(sinfo.get('known_members', {}))))
            if decl:
                print("    preview: %s" % decl_preview)

    print("[3] Structs: applied=%d/%d" % (s_ok, len(structs)))

    # (Enums already applied in step 3b, before structs)

    # --- 5. Vtable .rdata typing ---
    vt_applied = 0
    for vt_name, vt_info in vtables.items():
        methods = vt_info.get("methods", [])
        if not methods:
            continue
        vt_addr = int(vt_info["address"], 16)
        struct_name = "vtbl_%s" % vt_info["address"][2:]
        if idc.SetType(vt_addr, "%s x;" % struct_name):
            vt_applied += 1

    print("[5] Vtable .rdata typed: %d/%d" % (vt_applied, len(vtables)))

    # Wait for type system to settle before applying signatures
    ida_auto.auto_wait()

    # --- 6. Function signatures (after structs so types are resolved) ---
    import re as _re_sig
    sig_ok = 0
    sig_fail = []
    for addr_str, info in funcs.items():
        addr = int(addr_str, 16)
        sig = info.get("signature", "")
        name = info.get("name", "")
        if not sig:
            continue
        sig_raw = sig.strip().rstrip(";")
        if sig_raw.count("(") > 1:
            continue
        # Strip IDA-specific modifiers that SetType doesn't accept
        sig_raw = _re_sig.sub(r'__usercall|__userpurge', '', sig_raw)
        sig_raw = _re_sig.sub(r'@<[\w:]+>', '', sig_raw)  # register annotations
        sig_raw = sig_raw.replace(' __noreturn', '')
        sig_raw = _re_sig.sub(r'\s*__spoils<[^>]*>', '', sig_raw)
        sig_raw = sig_raw.strip()
        paren_idx = sig_raw.find("(")
        if paren_idx > 0:
            # Extract a valid C identifier for the function name
            if "::" in name:
                short_name = name.split("::")[-1]
            else:
                short_name = name
            # Demangle: ?Name@Class@@... → Name, ??1Class@@... → dtor_Class
            if short_name.startswith("??1"):
                m = _re_sig.match(r'\?\?1(\w+)@@', short_name)
                short_name = ("dtor_" + m.group(1)) if m else "dtor"
            elif short_name.startswith("??0"):
                m = _re_sig.match(r'\?\?0(\w+)@@', short_name)
                short_name = ("ctor_" + m.group(1)) if m else "ctor"
            elif short_name.startswith("?"):
                m = _re_sig.match(r'\?(\w+)@', short_name)
                if m:
                    short_name = m.group(1)
                else:
                    short_name = _re_sig.sub(r'[^a-zA-Z0-9_]', '_', short_name)
            short_name = short_name.replace("~", "_dtor_").replace(" ", "_")
            # Sanitize: only keep valid C identifier chars
            short_name = _re_sig.sub(r'[^a-zA-Z0-9_]', '_', short_name)
            if not short_name or short_name[0].isdigit():
                short_name = "fn_" + short_name
            before = sig_raw[:paren_idx].rstrip()
            after = sig_raw[paren_idx:]
            # 检测 ( 前是否已有函数名
            before_normalized = before.replace("*", "* ")
            tokens = before_normalized.split()
            _type_and_cc = {
                "__thiscall", "__cdecl", "__stdcall", "__fastcall",
                "int", "void", "char", "float", "double", "short", "long",
                "unsigned", "signed", "bool", "BOOL", "BYTE", "WORD", "DWORD",
                "HRESULT", "UINT", "__int64", "_DWORD", "_BYTE", "_WORD", "*",
            }
            last_meaningful = tokens[-1] if tokens else ""
            needs_name = last_meaningful in _type_and_cc
            if needs_name:
                sig_with_name = before + " " + short_name + after
            else:
                sig_with_name = before + after
            # Try original (with struct/class keywords), fallback to stripped
            if idc.SetType(addr, sig_with_name):
                sig_ok += 1
            else:
                stripped = sig_with_name.replace("struct ", "").replace("class ", "")
                if stripped != sig_with_name and idc.SetType(addr, stripped):
                    sig_ok += 1
                else:
                    sig_fail.append((addr_str, name, sig_with_name))

    if sig_fail:
        for addr_str, fname, sig_str in sig_fail[:10]:
            print("[!] Sig failed: %s %s → %s" % (addr_str, fname, sig_str[:60]))
    print("[6] Signatures: %d/%d (fail=%d)" % (sig_ok, len([f for f in funcs.values() if f.get("signature")]), len(sig_fail)))

    # --- 6b. Global types (after structs so struct types are resolved) ---
    g_typed = 0
    g_type_fail = []
    for addr_str, info in globs.items():
        addr = int(addr_str, 16)
        typ = info.get("type", "")
        if typ:
            type_str = typ.rstrip(";") + ";"
            if idc.SetType(addr, type_str):
                g_typed += 1
            else:
                stripped = type_str.replace("struct ", "").replace("class ", "")
                if stripped != type_str and idc.SetType(addr, stripped):
                    g_typed += 1
                else:
                    g_type_fail.append((addr_str, info.get("name", ""), typ))

    print("[6b] Global types: %d/%d (fail=%d)" % (g_typed, len([g for g in globs.values() if g.get("type")]), len(g_type_fail)))

    # --- 7. Trigger full reanalysis for type propagation ---
    ida_auto.plan_and_wait(0x00401000, 0x00560000)
    ida_auto.auto_wait()

    # --- 8. Re-apply failed signatures (types may now be resolved after propagation) ---
    sig_retry = 0
    for addr_str, fname, sig_str in sig_fail:
        addr = int(addr_str, 16)
        if idc.SetType(addr, sig_str):
            sig_retry += 1
        else:
            stripped = sig_str.replace("struct ", "").replace("class ", "")
            if idc.SetType(addr, stripped):
                sig_retry += 1
    print("[8] Signature retry: %d/%d recovered" % (sig_retry, len(sig_fail)))

    # --- 8b. Re-apply failed global types ---
    g_type_retry = 0
    for addr_str, gname, typ in g_type_fail:
        addr = int(addr_str, 16)
        type_str = typ.rstrip(";") + ";"
        if idc.SetType(addr, type_str):
            g_type_retry += 1
        else:
            stripped = type_str.replace("struct ", "").replace("class ", "")
            if idc.SetType(addr, stripped):
                g_type_retry += 1
    print("[8b] Global type retry: %d/%d recovered" % (g_type_retry, len(g_type_fail)))

    # --- 9. Local variable names/types (requires Hex-Rays) ---
    lvar_ok = 0
    lvar_fail = 0
    lvar_total = 0
    for addr_str, info in funcs.items():
        lvars_ann = info.get("local_vars")
        if not lvars_ann:
            continue
        addr = int(addr_str, 16)
        lvar_total += len(lvars_ann)

        func = ida_funcs.get_func(addr)
        if not func:
            lvar_fail += len(lvars_ann)
            continue

        try:
            cfunc = ida_hexrays.decompile(func)
        except:
            lvar_fail += len(lvars_ann)
            continue

        if not cfunc:
            lvar_fail += len(lvars_ann)
            continue

        ann_by_stkoff = {}
        for lv_ann in lvars_ann:
            stkoff = lv_ann.get("stack_offset")
            if stkoff is not None:
                ann_by_stkoff[stkoff] = lv_ann

        modified = False
        lvars = cfunc.lvars
        for lvar in lvars:
            loc = lvar.location
            if not loc.is_stkoff():
                continue
            soff = loc.stkoff()
            if soff not in ann_by_stkoff:
                continue

            ann = ann_by_stkoff[soff]
            new_name = ann.get("name")
            new_type = ann.get("type")

            if new_name and lvar.name != new_name:
                lvar.name = new_name
                modified = True

            if new_type:
                tif = ida_typeinf.tinfo_t()
                if ida_typeinf.parse_decl(tif, None, new_type + ";", 0):
                    lvar.set_lvar_type(tif)
                    modified = True

            lvar_ok += 1

        if modified:
            cfunc.save_user_lvars()

    print("[9] Lvars: %d/%d applied (fail=%d)" % (lvar_ok, lvar_total, lvar_fail))

    # --- 10. Final un-name pass (type propagation in step 7 may re-name functions) ---
    _unnamed2 = 0
    for ea in idautils.Functions(0x00401000, 0x00560000):
        cur = ida_name.get_name(ea) or ""
        if cur.startswith("sub_") or not cur:
            continue
        if ea not in _ann_addrs:
            ida_name.set_name(ea, "", ida_name.SN_NOWARN)
            _unnamed2 += 1
    if _unnamed2:
        print("[10] Final un-name: %d stale functions (post-propagation)" % _unnamed2)

    idc.save_database(idc.get_idb_path(), 0)
    print("[*] Done. Database saved.")
    idc.qexit(0)


if __name__ == "__main__":
    apply_annotations()
