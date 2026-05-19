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
import re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")


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
            # Advance cursor: use annotation offset gap as ground truth.
            # Type size estimation is only a fallback for the last member.
            nmo = next_member_offset(offset)
            has_next_member = any(off > offset for off, _ in sorted_members)
            if has_next_member and nmo > offset:
                # Verify type size doesn't exceed span (annotation data error detection)
                type_size = 4  # default
                if "*" in mtype:        type_size = 4
                elif mtype == "double": type_size = 8
                elif mtype == "float":  type_size = 4
                elif mtype in ("char", "unsigned char", "bool", "BYTE"): type_size = 1
                elif mtype in ("short", "unsigned short", "WORD"):       type_size = 2
                else:
                    clean = mtype.replace("class ", "").replace("struct ", "").strip()
                    if clean in all_structs:
                        ref = all_structs[clean]
                        type_size = ref.get("binary_size") or ref.get("pdb_size") or 4
                if type_size > (nmo - offset):
                    print("[!] LAYOUT ERROR in %s: member '%s %s' at +%d has type_size=%d but span=%d (next at +%d)" %
                          (name, mtype, mname, offset, type_size, nmo - offset, nmo))
                cursor = nmo
            else:
                # Last member: estimate type size
                if "*" in mtype:        cursor = offset + 4
                elif mtype == "double": cursor = offset + 8
                elif mtype == "float":  cursor = offset + 4
                elif mtype in ("char", "unsigned char", "bool", "BYTE"): cursor = offset + 1
                elif mtype in ("short", "unsigned short", "WORD"):       cursor = offset + 2
                else:
                    clean = mtype.replace("class ", "").replace("struct ", "").strip()
                    ref_size = 0
                    if clean in all_structs:
                        ref = all_structs[clean]
                        ref_size = ref.get("binary_size") or ref.get("pdb_size") or 0
                    cursor = offset + (ref_size if ref_size > 0 else 4)

    if size > 0 and cursor < size:
        lines.append("    char _tail_%03X[%d];" % (cursor, size - cursor))

    if not lines:
        if size > 0:
            inherit = " : public %s" % base_class if base_class else ""
            data_size = size - base_size if base_class else size
            has_vt = base_class and any(vt_info.get("class") == base_class for vt_info in vtables.values())
            cpp = " __cppobj" if has_vt else ""
            return "struct%s %s%s { char _data[%d]; };" % (cpp, name, inherit, data_size)
        return None

    inherit = " : public %s" % base_class if base_class else ""
    # Mark as __cppobj if class has a vtable (enables Hex-Rays virtual call resolution)
    has_vtable = any("__vftable" in l for l in lines) or (base_class and any(
        vt_info.get("class") == base_class for vt_info in vtables.values()
    ))
    cppobj = " __cppobj" if has_vtable else ""
    # Only use pack(1) for structs explicitly marked (file format headers, etc.)
    pack = struct_info.get("pack")
    if pack == 1:
        return "#pragma pack(push, 1)\nstruct%s %s%s {\n%s\n};\n#pragma pack(pop)" % (cppobj, name, inherit, "\n".join(lines))
    return "struct%s %s%s {\n%s\n};" % (cppobj, name, inherit, "\n".join(lines))


def create_fixed_struct(name, struct_info, all_structs, vtables, til):
    """用 TAUDT_FIXED 从 annotation 精确创建 IDA struct。

    每个成员逐一添加并验证。任何失败立即返回明确错误信息。
    返回 (True, None) 成功，或 (False, error_msg) 失败。
    """
    binary_size = struct_info.get("binary_size") or struct_info.get("gen_size") or 0
    if not binary_size:
        return (False, "no binary_size")

    members = struct_info.get("known_members", {})
    base_class = struct_info.get("base_class")
    base_size = struct_info.get("base_size", 0)

    udt = ida_typeinf.udt_type_data_t()
    udt.taudt_bits = 1024  # TAUDT_FIXED: respect explicit offsets
    if base_class:
        udt.taudt_bits |= 128  # TAUDT_CPPOBJ
    udt.total_size = binary_size

    # Add base class as anonymous member at offset 0
    if base_class and base_size > 0:
        base_tinfo = ida_typeinf.tinfo_t()
        if not base_tinfo.get_named_type(til, base_class):
            return (False, "base_class '%s' not found in TIL" % base_class)
        base_actual = base_tinfo.get_size()
        if base_actual == 0xFFFFFFFFFFFFFFFF or base_actual == 0:
            return (False, "base_class '%s' has invalid size" % base_class)
        mb = ida_typeinf.udt_member_t()
        mb.name = ""  # anonymous = base class
        mb.offset = 0
        mb.size = base_actual * 8
        mb.type = base_tinfo
        udt.push_back(mb)

    # Add known members at exact annotation offsets
    for off_str, minfo in sorted(members.items(), key=lambda x: int(x[0])):
        offset = int(off_str)
        if base_class and offset < base_size:
            continue

        mname = minfo["name"]
        mtype_str = minfo["type"].replace("class ", "").replace("struct ", "")

        # STL/template types → flatten to char[span]
        if 'std::' in mtype_str or '<' in mtype_str or '::' in mtype_str:
            sorted_offs = sorted(int(o) for o in members if int(o) > offset)
            span = min(sorted_offs) - offset if sorted_offs else binary_size - offset
            if span <= 0:
                span = 4
            mtype_str = "char[%d]" % span

        # Resolve type string to tinfo_t
        tinfo = ida_typeinf.tinfo_t()
        arr_match = re.match(r'^(.+?)(\[\d+\](?:\[\d+\])*)$', mtype_str)
        if arr_match:
            decl = "%s __x%s;" % (arr_match.group(1).strip(), arr_match.group(2))
        else:
            decl = "%s __x;" % mtype_str

        result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_VAR)
        if result is None:
            return (False, "add member +%d '%s' type '%s' FAILED: parse_decl returned None" % (
                offset, mname, mtype_str))

        member_size = tinfo.get_size()
        if member_size == 0 or member_size == 0xFFFFFFFFFFFFFFFF:
            return (False, "add member +%d '%s' type '%s' FAILED: resolved size=%d invalid" % (
                offset, mname, mtype_str, member_size))

        m = ida_typeinf.udt_member_t()
        m.name = mname
        m.offset = offset * 8  # bytes to bits
        m.size = member_size * 8  # bytes to bits
        m.type = tinfo
        udt.push_back(m)

    # Create the struct
    result_tinfo = ida_typeinf.tinfo_t()
    if not result_tinfo.create_udt(udt, ida_typeinf.BTF_STRUCT):
        return (False, "create_udt() returned False")

    actual_size = result_tinfo.get_size()
    if actual_size == 0xFFFFFFFFFFFFFFFF:
        # Diagnostic: find which members overlap
        overlap_info = []
        for i in range(udt.size()):
            mi = udt[i]
            end_bit = mi.offset + mi.size
            for j in range(i + 1, min(i + 2, udt.size())):
                mj = udt[j]
                if end_bit > mj.offset:
                    overlap_info.append("+%d %s(size=%d) ends@%d > next +%d %s" % (
                        mi.offset // 8, mi.name, mi.size // 8,
                        end_bit // 8, mj.offset // 8, mj.name))
        detail = "; ".join(overlap_info[:3]) if overlap_info else "no overlap detected in UDT"
        return (False, "INVALID struct after create_udt (%s)" % detail)
    if actual_size != binary_size:
        return (False, "size mismatch: expected %d, got %d (member type size wrong?)" % (
            binary_size, actual_size))

    result_tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
    return (True, None)


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


def import_gbengine_types():
    """Import gbengine struct/enum definitions into IDA TIL.

    Integrated from pipeline/ida/import_gbengine_types.py so the full pipeline
    runs in a single apply_annotations invocation.
    """
    from import_gbengine_types import flatten_gbengine_headers

    header_dir = os.path.join(PROJECT_ROOT, "include", "gbengine")
    if not os.path.isdir(header_dir):
        print("[gb] SKIP — gbengine header dir not found: %s" % header_dir)
        return

    content = flatten_gbengine_headers(header_dir)

    # Write flattened header for debugging
    log_dir = os.path.join(SCRIPT_DIR, "_logs")
    os.makedirs(log_dir, exist_ok=True)
    with open(os.path.join(log_dir, "gbengine_flat_ida.h"), 'w') as f:
        f.write(content)

    til = ida_typeinf.get_idati()

    # Remove forward-declaration stubs (size=-1) that block full definitions
    type_names_in_content = set(re.findall(r'(?:struct|enum)\s+(\w+)\s*[{:]', content))
    stubs_removed = 0
    for tname in type_names_in_content:
        tinfo = ida_typeinf.tinfo_t()
        if tinfo.get_named_type(til, tname):
            sz = tinfo.get_size()
            if sz == 0xFFFFFFFFFFFFFFFF or sz == 0:
                ida_typeinf.del_named_type(til, tname, ida_typeinf.NTF_TYPE)
                stubs_removed += 1

    # Bulk parse (multiple passes for ordering-dependent types)
    errs = idc.parse_decls(content, 0)
    for pass_num in range(2, 6):
        if errs == 0:
            break
        errs = idc.parse_decls(content, 0)

    # Recover individually-parseable types missed by bulk parse
    decl_pattern = re.compile(
        r'((?:struct|enum)\s+(\w+)\s*(?::\s*[^{]*?)?\s*\{[^}]*(?:\{[^}]*\}[^}]*)*\}\s*;)',
        re.DOTALL
    )
    recovered = 0
    for m in decl_pattern.finditer(content):
        name = m.group(2)
        decl = m.group(1)
        tinfo = ida_typeinf.tinfo_t()
        if not tinfo.get_named_type(til, name):
            tinfo2 = ida_typeinf.tinfo_t()
            result = ida_typeinf.parse_decl(tinfo2, til, decl, ida_typeinf.PT_TYP)
            if result is not None:
                tinfo2.set_named_type(til, name)
                recovered += 1

    # Verify
    type_names = set(re.findall(r'(?:struct|enum)\s+(\w+)\s*[{:;]', content))
    ok = sum(1 for n in type_names if ida_typeinf.tinfo_t().get_named_type(til, n))
    print("[gb] gbengine types: %d imported (%d stubs cleared, %d recovered, %d errors)"
          % (ok, stubs_removed, recovered, errs))

    # Set correct function types on gbengine IAT entries (data pointers in .idata).
    # Hex-Rays reads the type from the IAT address when decompiling indirect calls.
    # Without this, reference params (gbVec3D &) appear as pointer-pass (&var).
    _GB_IMPORT_SIGS = {
        "?Rotate@gbMatrixStack@@QAEXMAAUgbVec3D@@@Z":
            "void __thiscall(gbMatrixStack *, float, gbVec3D &);",
        "?Rotate@gbMatrixStack@@QAEXAAUgbQuaternion@@@Z":
            "void __thiscall(gbMatrixStack *, gbQuaternion &);",
        "?Translate@gbMatrixStack@@QAEXAAUgbVec3D@@@Z":
            "void __thiscall(gbMatrixStack *, gbVec3D &);",
        "?Scale@gbMatrixStack@@QAEXAAUgbVec3D@@@Z":
            "void __thiscall(gbMatrixStack *, gbVec3D &);",
        "?RightMultiply@gbMatrix4@@QAEXABUgbMatrix4@@@Z":
            "void __thiscall(gbMatrix4 *, const gbMatrix4 &);",
        "?RightMultiply@gbMatrix4@@QAEXABUgbQuaternion@@@Z":
            "void __thiscall(gbMatrix4 *, const gbQuaternion &);",
        "?LeftMultiply@gbMatrix4@@QAEXABUgbMatrix4@@@Z":
            "void __thiscall(gbMatrix4 *, const gbMatrix4 &);",
        "?LeftMultiply@gbMatrix4@@QAEXABUgbQuaternion@@@Z":
            "void __thiscall(gbMatrix4 *, const gbQuaternion &);",
        "?RightTranslate@gbMatrix4@@QAEXAAUgbVec3D@@@Z":
            "void __thiscall(gbMatrix4 *, gbVec3D &);",
        "?LeftTranslate@gbMatrix4@@QAEXAAUgbVec3D@@@Z":
            "void __thiscall(gbMatrix4 *, gbVec3D &);",
        "?MakeMatrix@gbMatrix4@@QAEXAAUgbVec3D@@00@Z":
            "void __thiscall(gbMatrix4 *, gbVec3D &, gbVec3D &, gbVec3D &);",
        "?IsColTriangle@gbRay@@QAEHAAUgbVec3D@@000@Z":
            "int __thiscall(gbRay *, gbVec3D &, gbVec3D &, gbVec3D &, gbVec3D &);",
        "?IntersectPlane@gbRay@@QAEMAAUgbVec3D@@0@Z":
            "float __thiscall(gbRay *, gbVec3D &, gbVec3D &);",
        "?IsColOBB@gbRay@@QAEHAAUgbOBBox@@@Z":
            "int __thiscall(gbRay *, gbOBBox &);",
        "?IsColOBB_H@gbRay@@QAEHAAUgbOBBox@@@Z":
            "int __thiscall(gbRay *, gbOBBox &);",
        "?IsColAABB@gbRay@@QAEHAAUgbAABBox@@@Z":
            "int __thiscall(gbRay *, gbAABBox &);",
        # gbDynVertBuf render functions (fixes struct #136 = gbRenderEffect)
        "?RenderGeomQuadViaStrip@gbDynVertBuf@@QAEXPAUgbGeomQuad@@HPAVgbRenderEffect@@PAUgbTextureArray@@K@Z":
            "void __thiscall(gbDynVertBuf *, gbGeomQuad *, int, gbRenderEffect *, gbTextureArray *, unsigned long);",
    }
    import ida_nalt
    gb_sig_ok = 0
    nimps = ida_nalt.get_import_module_qty()
    for i in range(nimps):
        mod = ida_nalt.get_import_module_name(i)
        if not mod or 'gbengine' not in mod.lower():
            continue
        def _set_import_type(ea, name, ordinal):
            nonlocal gb_sig_ok
            if name and name in _GB_IMPORT_SIGS:
                if idc.SetType(ea, _GB_IMPORT_SIGS[name]):
                    gb_sig_ok += 1
            return True
        ida_nalt.enum_import_names(i, _set_import_type)
    if gb_sig_ok:
        print("[gb] gbengine import function types set: %d" % gb_sig_ok)


def apply_annotations():
    ida_auto.auto_wait()

    # Disable auto-analysis during bulk modifications.
    # IDA's type propagation can override user-set names with mangled names
    # when SetType matches a TIL method declaration. Freezing prevents this.
    ida_auto.set_auto_state(False)

    # --- Import gbengine types FIRST (structs depend on gb* types) ---
    import_gbengine_types()

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
    rename_fail = []
    for addr_str, info in funcs.items():
        addr = int(addr_str, 16)
        name = info.get("name", "")
        if not _ida_funcs.get_func(addr):
            if _ida_funcs.add_func(addr):
                created += 1
        if name:
            cur = ida_name.get_name(addr) or ""
            if cur == name:
                renamed += 1
                continue
            # Delete existing name first (required for mangled names like ?xxx@yyy@@)
            if cur and cur != name:
                ida_name.set_name(addr, "", ida_name.SN_NOWARN)
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                renamed += 1
            else:
                rename_fail.append((addr_str, cur, name))

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

    print("[1] Functions: created=%d, renamed=%d/%d, skip_named=%d, rename_fail=%d" %
          (created, renamed, len(funcs), skip_named, len(rename_fail)))
    if rename_fail:
        for _addr, _old, _new in rename_fail[:10]:
            print("    [!] %s: '%s' → '%s' FAILED" % (_addr, _old[:40], _new[:40]))

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

    # --- 2b. Define essential Windows/SDK types that mssdk TIL would provide ---
    # (mssdk TIL disabled due to excessive misidentification, but we still need basic types)
    _ESSENTIAL_TYPES = [
        "struct tagRECT { long left; long top; long right; long bottom; };",
        "struct tagPOINT { long x; long y; };",
        "struct tagSIZE { long cx; long cy; };",
        "struct tagMSG { void *hwnd; unsigned int message; unsigned int wParam; long lParam; unsigned long time; tagPOINT pt; };",
        "struct _GUID { unsigned long Data1; unsigned short Data2; unsigned short Data3; unsigned char Data4[8]; };",
    ]
    til = ida_typeinf.get_idati()
    ess_ok = 0
    for decl in _ESSENTIAL_TYPES:
        tinfo = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
            # Extract name from "struct NAME {"
            import re as _re_ess
            m = _re_ess.match(r'struct\s+(\w+)', decl)
            if m:
                tinfo.set_named_type(til, m.group(1), ida_typeinf.NTF_REPLACE)
                ess_ok += 1
    print("[2b] Essential SDK types: %d/%d" % (ess_ok, len(_ESSENTIAL_TYPES)))

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
    functions = data.get("functions", {})

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
            # Look up signature from functions.json if not in vtable method
            if not sig and m.get("address"):
                func_entry = functions.get(m["address"], {})
                sig = func_entry.get("signature", "")
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
                # IDA sig format: "ret CC(params)" or "ret CC ClassName::Method(params)"
                # Try with function name first, then without
                fp_match = _re3.match(r'^(.+?\*?\s*)(\s*__\w+)\s+\w+(?:::\w+)?\s*(\(.*\))$', sig_clean)
                if not fp_match:
                    # No function name: "ret CC(params)" — common IDA format
                    fp_match = _re3.match(r'^(.+?\*?\s*)(\s*__\w+)\s*(\(.*\))$', sig_clean)
                if not fp_match:
                    # No CC: "ret(params)" or "ret funcname(params)"
                    fp_match = _re3.match(r'^(.+?)\s*(\(.*\))$', sig_clean)
                    if fp_match:
                        ret = fp_match.group(1).strip()
                        # Remove trailing word (function name) from ret if present
                        ret_parts = ret.rsplit(None, 1)
                        if len(ret_parts) > 1 and ret_parts[-1][0].isalpha():
                            ret = ret_parts[0]
                        args = fp_match.group(2)
                        lines.append("    %s (*%s)%s;" % (ret, short, args))
                        fp_match = None  # handled
                if fp_match:
                    ret = fp_match.group(1).strip()
                    cc = fp_match.group(2).strip() if fp_match.lastindex >= 3 else ""
                    args = fp_match.group(3) if fp_match.lastindex >= 3 else fp_match.group(2)
                    # For __thiscall vtable entries: strip 'this' param so IDA keeps __thiscall CC
                    # (IDA converts __thiscall with explicit this → __stdcall, breaking devirtualization)
                    if cc == "__thiscall":
                        args = _re3.sub(r'\(\s*\w[\w\s]*\*\s*\w+\s*,\s*', '(', args)
                        args = _re3.sub(r'\(\s*\w[\w\s]*\*\s*\w+\s*\)', '()', args)
                    lines.append("    %s (%s*%s)%s;" % (ret, cc + " " if cc else "", short, args))
                elif not any(short in l for l in lines):
                    lines.append("    int (*%s)();" % short)
            else:
                lines.append("    int (*%s)();" % short)
        decl = "struct %s {\n%s\n};" % (struct_name, "\n".join(lines))
        tinfo = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
            tinfo.set_named_type(til, struct_name, ida_typeinf.NTF_REPLACE)
            vt_pre += 1
    print("[3a] Vtable structs pre-created: %d/%d" % (vt_pre, len(vtables)))

    # --- TAUDT_FIXED struct import: precise offsets from annotation ---
    s_ok = 0
    s_fail = []
    s_errors = []

    # First pass: create all structs (dependency order already handled by 'ordered')
    for sname, sinfo in ordered:
        ok, err = create_fixed_struct(sname, sinfo, structs, vtables, til)
        if ok:
            s_ok += 1
        else:
            s_fail.append((sname, sinfo, err))

    # Retry failed structs (dependency on other structs now resolved)
    for retry in range(5):
        if not s_fail:
            break
        still_fail = []
        resolved = 0
        for sname, sinfo, prev_err in s_fail:
            ok, err = create_fixed_struct(sname, sinfo, structs, vtables, til)
            if ok:
                s_ok += 1
                resolved += 1
            else:
                still_fail.append((sname, sinfo, err))
        s_fail = still_fail
        if resolved == 0:
            break

    # Report errors and write to log file
    log_path = os.path.join(SCRIPT_DIR, "_logs", "struct_import_errors.txt")
    os.makedirs(os.path.dirname(log_path), exist_ok=True)

    print("[3] Structs: applied=%d/%d (TAUDT_FIXED)" % (s_ok, len(structs)))

    if s_fail:
        error_lines = []
        error_lines.append("STRUCT IMPORT ERRORS (%d failures):" % len(s_fail))
        for sname, sinfo, err in s_fail:
            line = "  struct %s: %s" % (sname, err)
            error_lines.append(line)
            print("[!] " + line)

        with open(log_path, 'w') as f:
            f.write('\n'.join(error_lines))
        print("[!] Error log: %s" % log_path)

        # ABORT: struct import errors must be fixed before continuing
        print("\n" + "=" * 60)
        print("[FATAL] %d structs failed to import. Fix annotations and retry." % len(s_fail))
        print("=" * 60)
        idc.qexit(1)
    else:
        # Clean: no errors
        if os.path.exists(log_path):
            os.remove(log_path)

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

    # --- 6c. CRT function signatures (operator new/delete) ---
    _CRT_SIGS = {
        '??2@YAPAXI@Z': 'void * __cdecl operator new(unsigned int);',
        '??3@YAXPAX@Z': 'void __cdecl operator delete(void *);',
        'j_??2@YAPAXI@Z': 'void * __cdecl operator new(unsigned int);',
        'j_??3@YAXPAX@Z': 'void __cdecl operator delete(void *);',
    }
    crt_ok = 0
    for ea in idautils.Functions(0x00401000, 0x00560000):
        name = ida_name.get_name(ea) or ""
        if name in _CRT_SIGS:
            if idc.SetType(ea, _CRT_SIGS[name]):
                crt_ok += 1
    if crt_ok:
        print("[6c] CRT function types set: %d" % crt_ok)

    # --- 7. Re-enable auto-analysis + trigger full type propagation ---
    # All modifications are done. Now let IDA propagate types.
    # This may override some function names with mangled versions (IDA C++ resolution).
    # Step 11 will fix those after propagation completes.
    ida_auto.set_auto_state(True)
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

    # --- 11. Force-rename: type propagation may override our names with mangled versions ---
    _force_renamed = 0
    for addr_str, info in funcs.items():
        addr = int(addr_str, 16)
        desired = info.get("name", "")
        if not desired:
            continue
        cur = ida_name.get_name(addr) or ""
        if cur != desired:
            ida_name.set_name(addr, "", ida_name.SN_NOWARN)
            if ida_name.set_name(addr, desired, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                _force_renamed += 1
    if _force_renamed:
        print("[11] Force-renamed %d functions (type propagation override)" % _force_renamed)

    idc.save_database(idc.get_idb_path(), 0)
    print("[*] Done. Database saved.")
    idc.qexit(0)


if __name__ == "__main__":
    apply_annotations()
