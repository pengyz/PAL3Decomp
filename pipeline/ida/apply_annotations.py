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
   4. enums     — idc.add_enum + add_enum_member (幂等)
"""

import ida_auto
import ida_bytes
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
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "apply_annotations_log.txt")
PDB_EXPORT = os.path.join(PROJECT_ROOT, "data", "pdb", "pdb_export.json")

log_lines = []


# 基本类型到 BTF 常量映射（纯 API，不用 parse_decl）
_PRIMITIVE_BTF = {
    'void': ida_typeinf.BTF_VOID,
    'char': ida_typeinf.BTF_CHAR,
    'signed char': ida_typeinf.BTF_INT8,
    'unsigned char': ida_typeinf.BTF_BYTE,
    'BYTE': ida_typeinf.BTF_BYTE,
    'uchar': ida_typeinf.BTF_BYTE,
    'uint8_t': ida_typeinf.BTF_BYTE,
    'short': ida_typeinf.BTF_INT16,
    'signed short': ida_typeinf.BTF_INT16,
    'unsigned short': ida_typeinf.BTF_UINT16,
    'WORD': ida_typeinf.BTF_UINT16,
    'ushort': ida_typeinf.BTF_UINT16,
    'short int': ida_typeinf.BTF_INT16,
    'int': ida_typeinf.BTF_INT32,
    'signed int': ida_typeinf.BTF_INT32,
    'int32': ida_typeinf.BTF_INT32,
    'unsigned int': ida_typeinf.BTF_UINT32,
    'UINT': ida_typeinf.BTF_UINT32,
    'uint': ida_typeinf.BTF_UINT32,
    'DWORD': ida_typeinf.BTF_UINT32,
    'unsigned': ida_typeinf.BTF_UINT32,
    'long': ida_typeinf.BTF_INT32,
    'signed long': ida_typeinf.BTF_INT32,
    'unsigned long': ida_typeinf.BTF_UINT32,
    'LONG': ida_typeinf.BTF_INT32,
    'long int': ida_typeinf.BTF_INT32,
    'float': ida_typeinf.BTF_FLOAT,
    'double': ida_typeinf.BTF_DOUBLE,
    'bool': ida_typeinf.BTF_BOOL,
    'BOOL': ida_typeinf.BTF_INT32,
    '__int64': ida_typeinf.BTF_INT64,
    'unsigned __int64': ida_typeinf.BTF_UINT64,
    'int64': ida_typeinf.BTF_INT64,
    'UINT64': ida_typeinf.BTF_UINT64,
    'HRESULT': ida_typeinf.BTF_INT32,
    '_DWORD': ida_typeinf.BTF_UINT32,
    '_BYTE': ida_typeinf.BTF_BYTE,
    '_WORD': ida_typeinf.BTF_UINT16,
}


def _create_primitive(name):
    """通过 API 创建基础类型 tinfo_t，不用 parse_decl。"""
    btf = _PRIMITIVE_BTF.get(name)
    if btf is None:
        return None
    t = ida_typeinf.tinfo_t()
    if not t.create_simple_type(btf):
        return None
    return t


def _normalize_type(mtype_str):
    mtype_str = re.sub(r'\bclass\s+|\bstruct\s+', '', mtype_str)
    mtype_str = re.sub(r'\[0x([0-9a-fA-F]+)\]', lambda m: '[%d]' % int(m.group(1), 16), mtype_str)
    return mtype_str


def _resolve_member_type(mtype_str, til):
    """将成员类型字符串解析为 tinfo_t（纯 API，不用 parse_decl）。

    优先级：
    1. 基础类型（int/float/char 等）：_create_primitive
    2. 命名类型（结构体/类）：get_named_type
    3. 指针：create_ptr
    4. 数组：create_array
    5. 模板/函数指针：不支持，返回 None
    """
    s = _normalize_type(mtype_str).strip()
    if not s:
        return None

    if '<' in s or '(' in s:
        # Function pointer type: "int (__thiscall *)(void *, unsigned long)"
        if '(' in s and '*' in s:
            tinfo = ida_typeinf.tinfo_t()
            try:
                # parse_decl is a global function: ida_typeinf.parse_decl(tinfo, til, decl, flags)
                # Build decl with dummy name after *
                _fp = re.search(r'\(([^)]*\*)\)\s*\(', s)
                if _fp:
                    _inner = _fp.group(1)
                    _star_pos = _inner.rfind('*')
                    _decl = s[:_fp.start(1)] + _inner[:_star_pos] + '*__x' + s[_fp.end(1):] + ';'
                    _result = ida_typeinf.parse_decl(tinfo, til, _decl, 0)
                    if _result is not None:
                        return tinfo
            except:
                pass
        base = re.split(r'[<(]', s)[0].strip()
        tinfo = ida_typeinf.tinfo_t()
        if tinfo.get_named_type(til, base):
            return tinfo
        return None

    array_sizes = []
    while True:
        m = re.search(r'\[(\d+)\]$', s)
        if not m:
            break
        array_sizes.insert(0, int(m.group(1)))
        s = s[:m.start()].strip()

    ptr_count = 0
    while s.endswith('*'):
        ptr_count += 1
        s = s.rstrip('*').strip()

    if s.startswith('const '):
        s = s[6:].strip()

    if not s:
        return None

    if s == 'void' and ptr_count > 0:
        void_t = ida_typeinf.tinfo_t()
        if void_t.create_simple_type(ida_typeinf.BTF_VOID):
            ptr_t = ida_typeinf.tinfo_t()
            if ptr_t.create_ptr(void_t):
                return ptr_t
        return None

    tinfo = _create_primitive(s)
    if tinfo is not None:
        for _ in range(ptr_count):
            p = ida_typeinf.tinfo_t()
            if not p.create_ptr(tinfo):
                return None
            tinfo = p
        for size in reversed(array_sizes):
            a = ida_typeinf.tinfo_t()
            if not a.create_array(tinfo, size):
                return None
            tinfo = a
        return tinfo

    tinfo = ida_typeinf.tinfo_t()
    if tinfo.get_named_type(til, s):
        for _ in range(ptr_count):
            p = ida_typeinf.tinfo_t()
            if not p.create_ptr(tinfo):
                return None
            tinfo = p
        for size in reversed(array_sizes):
            a = ida_typeinf.tinfo_t()
            if not a.create_array(tinfo, size):
                return None
            tinfo = a
        return tinfo

    return None


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def _make_vtable_method_type(ann_sig, vm_short, til):
    """从 annotation 签名创建 vtable 方法类型，纯 API 不用 parse_decl。"""
    if '(' not in ann_sig:
        return None
    open_paren = ann_sig.index('(')
    close_paren = ann_sig.rindex(')')
    prefix = ann_sig[:open_paren].strip()
    params_str = ann_sig[open_paren+1:close_paren].strip()
    prefix = re.sub(r'\w+::\w+', '', prefix).strip()
    prefix = re.sub(r'\bvirtual\s+', '', prefix).strip()
    ret_type = prefix
    cc = ida_typeinf.CM_CC_THISCALL
    if '__stdcall' in ret_type:
        cc = ida_typeinf.CM_CC_STDCALL
        ret_type = ret_type.replace('__stdcall', '').strip()
    elif '__cdecl' in ret_type:
        cc = ida_typeinf.CM_CC_CDECL
        ret_type = ret_type.replace('__cdecl', '').strip()
    else:
        ret_type = ret_type.replace('__thiscall', '').strip()
    ret_tinfo = _resolve_member_type(ret_type, til)
    if ret_tinfo is None:
        return None
    func_data = ida_typeinf.func_type_data_t()
    func_data.rettype = ret_tinfo
    func_data.cc = cc
    if params_str:
        depth = 0
        current = []
        for c in params_str:
            if c == '<': depth += 1
            elif c == '>': depth -= 1
            elif c == ',' and depth == 0:
                p = ''.join(current).strip()
                if p:
                    tokens = p.split()
                    if len(tokens) >= 2 and tokens[-1] not in ('const',):
                        ptype = ' '.join(tokens[:-1])
                    else:
                        ptype = p
                    pt_tinfo = _resolve_member_type(ptype, til)
                    if pt_tinfo is not None:
                        arg = ida_typeinf.funcarg_t()
                        arg.type = pt_tinfo
                        func_data.push_back(arg)
                current = []
                continue
            current.append(c)
        if current:
            p = ''.join(current).strip()
            if p:
                tokens = p.split()
                if len(tokens) >= 2 and tokens[-1] not in ('const',):
                    ptype = ' '.join(tokens[:-1])
                else:
                    ptype = p
                pt_tinfo = _resolve_member_type(ptype, til)
                if pt_tinfo is not None:
                    arg = ida_typeinf.funcarg_t()
                    arg.type = pt_tinfo
                    func_data.push_back(arg)
    mtif = ida_typeinf.tinfo_t()
    if not mtif.create_func(func_data):
        return None
    return mtif


def build_struct_decl(name, struct_info, all_structs=None, vtables=None):
    """从 known_members + size 生成带 gap 填充的 C struct 声明。支持基类继承、数组类型和虚函数。"""
    import re as _re
    if all_structs is None:
        all_structs = {}
    if vtables is None:
        vtables = {}

    members = struct_info.get("known_members", {})
    size = struct_info.get("binary_size") or struct_info.get("pdb_size") or 0
    base_class = struct_info.get("base_class")
    # Handle multiple inheritance: only use first base (IDA's struct model limitation)
    if isinstance(base_class, list):
        base_class = base_class[0] if base_class else None
    base_size = struct_info.get("base_size", 0)

    # IDA parse_decl cannot handle C++ template base classes
    if base_class and ('<' in base_class or '>' in base_class):
        base_class = None  # drop template inheritance, use gap instead

    if not members and not size:
        return None

    sorted_members = sorted(
        [(int(off, 0), info) for off, info in members.items() if int(off, 0) >= base_size],
        key=lambda x: x[0]
    )

    def next_member_offset(current_offset):
        for off, _ in sorted_members:
            if off > current_offset:
                return off
        return size if size > 0 else current_offset

    # 查找此类的 vtable（只处理无基类的，有基类时 vtable 由基类定义）
    # 新 schema: vtable 信息内嵌在 struct_info['vtables']
    virtual_methods = None
    own_vtable_addr = None
    if not base_class and struct_info and struct_info.get("vtables"):
        own_vtable_addr = struct_info["vtables"][0].get("addr", "")
        virtual_methods = struct_info["vtables"][0].get("slots", [])

    lines = []
    cursor = base_size

    for offset, info in sorted_members:
        mname = info["name"]
        mtype = info["type"].replace("class ", "").replace("struct ", "")

        if offset > cursor:
            lines.append("    char _gap_%03X[%d];" % (cursor, offset - cursor))

        # __vftable/vfptr: typed vtable pointer（IDA 反编译输出最优）
        if offset == 0 and mname in ("__vftable", "vfptr") and virtual_methods:
            if own_vtable_addr:
                vt_struct_name = "vtbl_%s" % own_vtable_addr[2:]
                lines.append("    %s *__vftable;" % vt_struct_name)
            else:
                lines.append("    int vfptr;")
            cursor = offset + 4
            continue

        arr_match = re.search(r'((?:\[(?:\d+|0x[0-9a-fA-F]+)\])+)$', mtype)

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
                    elem_size = ref.get("binary_size") or ref.get("pdb_size") or ref.get("size") or 0
            if elem_size > 0:
                def _parse_dim(dim_str):
                    return int(dim_str, 0)  # handles 0x hex prefix automatically
                dims = [_parse_dim(d) for d in re.findall(r'\[(0x[0-9a-fA-F]+|\d+)\]', arr_match.group(1))]
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

    def _base_has_vtable(bc):
        return bool(bc and all_structs and all_structs.get(bc, {}).get("vtables"))

    if not lines:
        if size > 0:
            inherit = " : public %s" % base_class if base_class else ""
            data_size = size - base_size if base_class else size
            cpp = " __cppobj" if _base_has_vtable(base_class) else ""
            return "struct%s %s%s { char _data[%d]; };" % (cpp, name, inherit, data_size)
        return None

    inherit = " : public %s" % base_class if base_class else ""
    # Mark as __cppobj if class has a vtable (enables Hex-Rays virtual call resolution)
    has_vtable = any("__vftable" in l for l in lines) or _base_has_vtable(base_class)
    cppobj = " __cppobj" if has_vtable else ""
    # Only use pack(1) for structs explicitly marked (file format headers, etc.)
    pack = struct_info.get("pack")
    if pack == 1:
        return "#pragma pack(push, 1)\nstruct%s %s%s {\n%s\n};\n#pragma pack(pop)" % (cppobj, name, inherit, "\n".join(lines))
    return "struct%s %s%s {\n%s\n};" % (cppobj, name, inherit, "\n".join(lines))


def _type_exists_in_til(name, til):
    """检查 TIL 中是否有命名类型（不论 forward decl 还是完整定义）。"""
    tinfo = ida_typeinf.tinfo_t()
    return tinfo.get_named_type(til, name)


def _has_pdb_definition(name, til):
    """检查 TIL 中是否有 PDB 导入的完整 struct 定义（非 forward decl）。"""
    tinfo = ida_typeinf.tinfo_t()
    if not tinfo.get_named_type(til, name):
        return False
    if tinfo.get_size() in (0, 0xFFFFFFFFFFFFFFFF):
        return False
    udt = ida_typeinf.udt_type_data_t()
    if not tinfo.get_udt_details(udt):
        return True  # TIL has type but can't read UDT — still a valid definition
    for i in range(len(udt)):
        m = udt[i]
        if m.name or m.type.get_size() > 0:
            return True
    return False


def create_fixed_struct_diff(name, struct_info, til):
    """Diff 模式: TIL 中已有 PDB struct（由 master_pipeline 导入），
    annotation 只做 incremental patch: 删除偏移、重命名/改类型、新增成员。"""
    binary_size = struct_info.get("binary_size") or 0
    if not binary_size:
        return (False, "no binary_size")

    deleted = set(struct_info.get("deleted_members", []))
    overrides = {}
    for k, v in struct_info.get("known_members", {}).items():
        overrides[int(k.split('_')[0])] = v
    is_union = struct_info.get("is_union", False)

    # 加载 PDB struct
    existing_tinfo = ida_typeinf.tinfo_t()
    if not existing_tinfo.get_named_type(til, name):
        return (False, "type not found in TIL")
    existing_udt = ida_typeinf.udt_type_data_t()
    if not existing_tinfo.get_udt_details(existing_udt):
        # TIL 有类型但无法读取 UDT 详情（IDB 导入格式差异）。
        # 回退到 replace 模式，从 known_members 重建。
        return create_fixed_struct(name, struct_info, {}, {}, til)

    new_udt = ida_typeinf.udt_type_data_t()
    new_udt.taudt_bits = 1024  # TAUDT_FIXED
    if existing_udt.taudt_bits & 128:
        new_udt.taudt_bits |= 128  # TAUDT_CPPOBJ
    if is_union:
        new_udt.is_union = True
    new_udt.total_size = binary_size

    existing_offsets = set()
    for i in range(len(existing_udt)):
        m = existing_udt[i]
        m_off_bytes = m.offset // 8

        if m_off_bytes in deleted:
            existing_offsets.add(m_off_bytes)
            continue

        if m_off_bytes in overrides:
            m.name = overrides[m_off_bytes]["name"]
            new_type_str = overrides[m_off_bytes].get("type")
            if new_type_str and new_type_str != "int":
                new_tinfo = _resolve_member_type(new_type_str, til)
                if new_tinfo is not None:
                    _nsz = new_tinfo.get_size()
                    if _nsz not in (0, 0xFFFFFFFFFFFFFFFF):
                        m.type = new_tinfo
                        m.size = _nsz * 8

        new_udt.push_back(m)
        existing_offsets.add(m_off_bytes)

    # 新增 annotation 独有的成员
    for off, minfo in sorted(overrides.items()):
        if off in existing_offsets or off in deleted:
            continue
        if off < 0:
            continue

        mname = minfo["name"]
        mtype_str = minfo["type"]

        tinfo = _resolve_member_type(mtype_str, til)
        if tinfo is None:
            return (False, "add member +%d '%s': _resolve_member_type failed on '%s'" % (off, mname, mtype_str))

        m = ida_typeinf.udt_member_t()
        msize = tinfo.get_size()
        if msize in (0, 0xFFFFFFFFFFFFFFFF):
            return (False, "add member +%d '%s': invalid size %d for type '%s'" % (
                off, mname, msize, mtype_str))
        m.name = mname
        m.offset = off * 8
        m.size = msize * 8
        m.type = tinfo
        new_udt.push_back(m)

    # 写回 TIL
    result_tinfo = ida_typeinf.tinfo_t()
    udt_flag = ida_typeinf.BTF_UNION if is_union else ida_typeinf.BTF_STRUCT
    if not result_tinfo.create_udt(new_udt, udt_flag):
        return (False, "create_udt() failed (diff mode)")

    actual_size = result_tinfo.get_size()
    if actual_size == 0xFFFFFFFFFFFFFFFF:
        return (False, "create_udt produced invalid type")
    # PDB 和 PAL3.exe 版本不同，struct size 可能不一致。
    # annotation binary_size 是 PAL3.exe 实测值，应优先采用。
    # 如果合并后 size 不匹配，说明 PDB layout 差异过大，回退 replace 模式。
    if actual_size != binary_size:
        return create_fixed_struct(name, struct_info, {}, {}, til)

    result_tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
    return (True, None)


def create_fixed_struct(name, struct_info, all_structs, vtables, til):
    """用 TAUDT_FIXED 从 annotation 精确创建 IDA struct。

    每个成员逐一添加并验证。任何失败立即返回明确错误信息。
    返回 (True, None) 成功，或 (False, error_msg) 失败。
    """
    binary_size = struct_info.get("binary_size") or 0
    if not binary_size:
        return (False, "no binary_size")

    members = struct_info.get("known_members", {})
    is_union = struct_info.get("is_union", False)
    base_class_raw = struct_info.get("base_class")
    # Unions don't support inheritance
    if is_union:
        base_class = None
        base_size = 0
        base_classes = []
    elif isinstance(base_class_raw, list):
        base_classes = base_class_raw
        base_class = base_classes[0] if base_classes else None
        # Multiple base classes are handled by adding each as an anonymous member
    else:
        base_class = base_class_raw
        base_classes = [base_class] if base_class else []
    if not is_union:
        base_size = struct_info.get("base_size", 0)
        # Filter out template expression names (with <>) that won't resolve in TIL
        _concrete_bases = [bc for bc in base_classes if '<' not in bc and '>' not in bc]
        # For multiple inheritance, compute total base size by looking up each base
        if len(base_classes) > 1:
            total_base = 0
            for bc in _concrete_bases:
                bc_tinfo = ida_typeinf.tinfo_t()
                if bc_tinfo.get_named_type(til, bc):
                    total_base += bc_tinfo.get_size()
            if total_base > 0:
                base_size = total_base

    udt = ida_typeinf.udt_type_data_t()
    is_flexible = struct_info.get("_flexible", False)
    if is_union:
        udt.is_union = True
    else:
        is_flexible = struct_info.get("_flexible", False)
        if base_class:
            # TAUDT_FIXED + TAUDT_CPPOBJ: enforce annotation's exact member
            # layout and types (instead of IDA auto-layout from base class).
            if not is_flexible:
                udt.taudt_bits = 1024  # TAUDT_FIXED
                udt.total_size = binary_size
            udt.taudt_bits |= 128  # TAUDT_CPPOBJ
        else:
            if not is_flexible:
                udt.taudt_bits = 1024  # TAUDT_FIXED: respect explicit offsets
                udt.total_size = binary_size
            udt.taudt_bits |= 128  # TAUDT_CPPOBJ

    # Add base classes as anonymous members (supports multiple inheritance)
    _concrete_bases = [bc for bc in base_classes if '<' not in bc and '>' not in bc]
    _base_offset = 0
    if _concrete_bases and base_size > 0:
        base_offset = 0
        for bc in _concrete_bases:
            bc_tinfo = ida_typeinf.tinfo_t()
            if not bc_tinfo.get_named_type(til, bc):
                continue
            bc_size = bc_tinfo.get_size()
            if bc_size == 0xFFFFFFFFFFFFFFFF or bc_size == 0:
                continue
            mb = ida_typeinf.udt_member_t()
            mb.name = ""
            mb.offset = base_offset * 8  # bits
            mb.size = bc_size * 8  # bits
            mb.type = bc_tinfo
            udt.push_back(mb)
            base_offset += bc_size
        _base_offset = base_offset

    # Add known members at exact annotation offsets
    # Union members use "0", "0_1", "0_2" keys (all at offset 0)
    for off_str, minfo in sorted(members.items(), key=lambda x: int(x[0].split('_')[0], 0)):
        offset = int(off_str.split('_')[0], 0)
        if base_class and offset < base_size and minfo.get("name") not in ("vfptr", "__vftable"):
            continue

        mname = minfo["name"]
        mtype_str = _normalize_type(minfo["type"])

        # STL/template types: flatten to char[span] (TIL API can't handle template syntax)
        _is_stl = 'std::' in mtype_str or '<' in mtype_str
        if _is_stl:
            sorted_offs = sorted(int(o, 0) for o in members if int(o, 0) > offset)
            span = min(sorted_offs) - offset if sorted_offs else binary_size - offset
            if span <= 0:
                span = 4
            mtype_str = "char[%d]" % span

        # Resolve type string to tinfo_t
        tinfo = _resolve_member_type(mtype_str, til)
        if tinfo is None:
            return (False, "add member +%d '%s' type '%s' FAILED: _resolve_member_type" % (
                offset, mname, mtype_str))

        member_size = tinfo.get_size()

        m = ida_typeinf.udt_member_t()
        m.name = mname
        m.offset = offset * 8  # bytes to bits
        m.size = member_size * 8  # bytes to bits
        m.type = tinfo
        udt.push_back(m)

    # When struct has size but no members, IDA creates a blob without named fields.
    # Add a char[N] filler so the struct has proper named members in the IDB.
    if udt.size() == 0 and binary_size > 0:
        _filler_arr = ida_typeinf.tinfo_t()
        _filler_char = _resolve_member_type("unsigned char", til)
        if _filler_char and _filler_arr.create_array(_filler_char, binary_size):
            _filler_m = ida_typeinf.udt_member_t()
            _filler_m.name = "_tail_000"
            _filler_m.offset = 0
            _filler_m.type = _filler_arr
            udt.push_back(_filler_m)

    # For flexible structs, compute total_size from actual member layout
    if is_flexible and not is_union:
        _computed_size = binary_size
        for _i in range(udt.size()):
            _m = udt[_i]
            _m_end = _m.offset // 8 + _m.size // 8
            if _m_end > _computed_size:
                _computed_size = _m_end
        udt.total_size = _computed_size

    # Create the struct/union
    result_tinfo = ida_typeinf.tinfo_t()
    udt_flag = ida_typeinf.BTF_UNION if is_union else ida_typeinf.BTF_STRUCT

    if not result_tinfo.create_udt(udt, udt_flag):
        return (False, "TAUDT_FIXED create_udt() returned False for %s" % name)

    method_udms = ida_typeinf.udtmembervec_t()
    struct_methods = struct_info.get('methods', {}) if struct_info else {}
    vt_slots = resolve_vtable_slots(struct_info, struct_methods)
    if vt_slots:
        total = sum(len(slots) for _, slots in vt_slots)
        log("  [vtable] %s: %d table(s), %d slots" % (name, len(vt_slots), total))
    seen_vm = set()
    for _vt_addr, slots in vt_slots:
        for _slot_addr, vm_short, ann_sig, _from in slots:
            if not vm_short or vm_short in seen_vm or not ann_sig:
                continue
            seen_vm.add(vm_short)
            try:
                mtif = _make_vtable_method_type(ann_sig, vm_short, til)
                if mtif is not None:
                    mudm = ida_typeinf.udm_t()
                    mudm.name = vm_short
                    mudm.type = mtif
                    mudm.set_method(True)
                    method_udms.push_back(mudm)
                else:
                    log("  [!] vtable method FAILED for %s (ann_sig='%s')" % (vm_short, ann_sig))
            except Exception as _e:
                log("  [!] vtable method EXCEPTION for %s: %s (ann_sig='%s')" % (vm_short, _e, ann_sig))
    if len(method_udms) > 0:
        result_tinfo.set_methods(method_udms)

    actual_size = result_tinfo.get_size()
    if actual_size == 0xFFFFFFFFFFFFFFFF:
        # TAUDT_FIXED with union members (same-offset variants) causes IDA to
        # report get_size=-1 even though the UDT was created successfully.
        # Use binary_size as the authoritative size for validation.
        if binary_size > 0:
            actual_size = binary_size
        else:
            log("[FATAL] %s: TAUDT_FIXED struct 'invalid' (get_size=-1). "
                "binary_size=%d, members=%d, base=%s. "
                "Fix member offsets or types in annotation." % (
                    name, binary_size, len(members), base_class or '(none)'))
            return (False, "TAUDT_FIXED invalid for %s (get_size=-1)" % name)
    # When created without base members (_base_offset==0), actual_size may
    # be smaller than binary_size (base class portions are missing). Accept it.
    if is_flexible:
        _size_check = actual_size  # flexible structs: accept whatever IDA computes
    else:
        _size_check = binary_size
    if actual_size > _size_check:
        return (False, "size mismatch: expected <=%d, got %d" % (
            binary_size, actual_size))

    result_tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
    
    # Post-create: fix __vftable type for classes with vtables
    # build_struct_decl creates typed vtbl_ADDR *__vftable, but annotations
    # overwrite it with int. This ensures the vtable pointer has the correct type.
    if struct_info and struct_info.get("vtables"):
        _va0 = struct_info["vtables"][0].get("addr", "")
        if _va0:
            _vtn = "vtbl_%s" % _va0[2:]
            _vtif = ida_typeinf.tinfo_t()
            if _vtif.get_named_type(til, _vtn) and _vtif.get_size() < 10000:
                _vp_tif = ida_typeinf.tinfo_t()
                _vp_tif.create_ptr(_vtif)
                if _vp_tif.is_correct() and _vp_tif.get_size() == 4:
                    _udt2 = ida_typeinf.udt_type_data_t()
                    if result_tinfo.get_udt_details(_udt2):
                        for _i in range(_udt2.size()):
                            try:
                                _um = _udt2[_i]
                                if _um.get_name() == "__vftable":
                                    _um.type = _vp_tif  # set typed vtable pointer
                                    _r2 = ida_typeinf.tinfo_t()
                                    if _r2.create_udt(_udt2, ida_typeinf.BTF_STRUCT):
                                        _r2.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                                    break
                            except: pass

    return (True, None)


def load_annotations():
    """从拆分目录加载标注数据。"""
    if not os.path.isdir(ANNOTATIONS_DIR):
        return None

    log("[*] Loading annotations from: %s" % ANNOTATIONS_DIR)
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
        # Merge struct methods into functions dict (class methods not in functions.json)
        for addr, minfo in sdata.get("methods", {}).items():
            if addr not in functions:
                functions[addr] = minfo
        # Also merge nested type methods (e.g. NODE::FindInOpen)
        for _nt_name, _nt_info in sdata.get("nested_types", {}).items():
            _nt_full = "%s::%s" % (sname, _nt_name)
            for _addr, _minfo in _nt_info.get("methods", {}).items():
                if _addr not in functions:
                    _mn = _minfo.get("name", "")
                    if _mn and "::" not in _mn:
                        _minfo["name"] = "%s::%s" % (_nt_full, _mn)
                    functions[_addr] = _minfo
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
    }


def resolve_vtable_slots(struct_info, functions):
    """从 per-class vtables 重建有序 slot 列表。

    返回 list of (vtable_addr, slots) — slots 是有序 list of
    (slot_addr, short_name, signature, from_class)。
    name/signature 按地址从该类 methods -> functions 解析 (Trust by address)。
    """
    methods = struct_info.get("methods", {}) if struct_info else {}
    out = []
    for vt in struct_info.get("vtables", []) if struct_info else []:
        slots = []
        for slot in vt.get("slots", []):
            addr = slot.get("addr", "")
            entry = methods.get(addr) or functions.get(addr) or {}
            raw_name = entry.get("name", "")
            short = raw_name.split("::")[-1] if "::" in raw_name else raw_name
            slots.append((addr, short, entry.get("signature", ""), slot.get("from")))
        out.append((vt.get("addr", ""), slots))
    return out


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

    # Look up each type — should already exist from PDB import in master_pipeline
    import re as _re_gb
    _gb_missing = set()
    for _m in _re_gb.finditer(r'(?:struct|enum|typedef)\s+(\w+)\s*[{:;]', content):
        _n = _m.group(1)
        if _n not in ('int','char','float','double','short','long','unsigned','void','bool'):
            if not ida_typeinf.tinfo_t().get_named_type(til, _n):
                _gb_missing.add(_n)
    if _gb_missing:
        # Create forward declarations for missing types (opaque)
        for _n in sorted(_gb_missing):
            _u = ida_typeinf.udt_type_data_t()
            _u.total_size = 0
            _t = ida_typeinf.tinfo_t()
            if _t.create_udt(_u, ida_typeinf.BTF_STRUCT):
                _t.set_named_type(til, _n, ida_typeinf.NTF_REPLACE)
    # Verify
    type_names = set(_re_gb.findall(r'(?:struct|enum)\s+(\w+)\s*[{:;]', content))
    type_names = {n for n in type_names if n not in ('int','char','float','double','short','long','unsigned','void','bool')}
    ok = sum(1 for n in type_names if ida_typeinf.tinfo_t().get_named_type(til, n))
    log("[gb] gbengine types: %d/%d present in til (%d stubs cleared, %d forward-declared)"
          % (ok, len(type_names), stubs_removed, len(_gb_missing)))

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


# ============================================================
# VC6 mangled name generator
# ============================================================
_VC6_TC = {
    'void': 'X', 'char': 'D', 'unsigned char': 'E',
    'short': 'F', 'unsigned short': 'G',
    'int': 'H', 'unsigned int': 'I',
    'long': 'J', 'unsigned long': 'K',
    'float': 'M', 'double': 'N', 'bool': '_N',
    'BYTE': 'E', 'WORD': 'G', 'DWORD': 'K', 'BOOL': 'I', 'UINT': 'I',
}
_VC6_CC = {'__thiscall': 'A', '__cdecl': 'C', '__stdcall': 'G', '__fastcall': 'I'}


def _vc6_encode_type(t):
    t = t.strip()
    is_const = t.startswith('const ')
    if is_const: t = t[6:].strip()
    is_ref = t.endswith('&')
    if is_ref: t = t[:-1].strip()
    ptr = 0
    while t.endswith('*'):
        t = t[:-1].strip(); ptr += 1
    tag = None
    if t.startswith('struct '): tag = 'U'; t = t[7:].strip()
    elif t.startswith('class '): tag = 'V'; t = t[6:].strip()
    # Handle nested types (e.g. AStarPathFinder::NODE)
    # IDA keeps :: in mangled names: PAUAStarPathFinder::NODE@@
    if '::' in t and tag is None:
        tag = 'U'
    code = _VC6_TC.get(t)
    if '::' in t and code is None:
        code = (tag if tag else 'U') + t + '@@'
    elif code is None and ptr > 0:
        code = 'U' + t + '@@'
    elif code is None and tag:
        code = tag + t + '@@'
    elif code is None:
        if t.startswith('unsigned '): code = _VC6_TC.get(t[9:].strip())
        if code is None: code = 'H'
    if is_ref: code = 'A' + code
    for _ in range(ptr):
        code = 'P' + ('B' if (is_const and _ == 0) else 'A') + code
    return code


def _vc6_strip_param_name(p):
    m = re.match(r'^(.+\*)\s*\w*$', p)
    if m: return m.group(1).strip()
    m = re.match(r'^(.+?)\s+\w+$', p)
    if m: return m.group(1).strip()
    return p.strip()


def _mangle_vc6_class_chain(cls_name):
    """Convert 'AStarPathFinder::NODE' to 'NODE@AStarPathFinder' (MSVC format)."""
    parts = cls_name.split('::')
    return '@'.join(reversed(parts))

def _mangle_vc6(cls_name, method_name, sig):
    cls_chain = _mangle_vc6_class_chain(cls_name)
    paren = sig.find('(') if sig else -1
    if paren == -1: return '?' + method_name + '@' + cls_chain + '@@QAEXXZ'
    prefix = sig[:paren].strip()
    pstr = sig[paren + 1:sig.rfind(')')] if sig.rfind(')') > paren else ''
    cc = '__thiscall'
    for c in ['__thiscall', '__cdecl', '__stdcall', '__fastcall']:
        if c in prefix: cc = c; break
    ret = prefix.replace(cc, '').strip()
    # Strip trailing ClassName::Method (from signature patterns like
    # "int ClassName::Method()") but NOT nested types in return position
    # (e.g. "AStarPathFinder::NODE *" must keep AStarPathFinder::NODE).
    ret = re.sub(r'\s+\w+::\w+$', '', ret).strip()
    pstr = re.sub(r'\w+\s*\*\s*(?:__hidden\s+)?this\s*,?\s*', '', pstr)
    params = []
    if pstr and pstr.strip() not in ('', 'void'):
        depth = 0; cur = ''
        for ch in pstr:
            if ch in '<([': depth += 1; cur += ch
            elif ch in '>)]': depth -= 1; cur += ch
            elif ch == ',' and depth == 0:
                if cur.strip(): params.append(cur.strip()); cur = ''
            else: cur += ch
        if cur.strip(): params.append(cur.strip())
    r = '?' + method_name + '@' + cls_chain + '@@'
    r += 'Q' + _VC6_CC.get(cc, 'A') + 'E'
    r += _vc6_encode_type(ret)
    for p in params: r += _vc6_encode_type(_vc6_strip_param_name(p))
    r += '@Z'
    return r


def _try_apply_type_tinfo(addr, sig, info, til):
    """Apply function type via tinfo_t API (fallback when SetType fails on :: types)."""
    import re as _re_t
    if '::' not in sig:
        return False
    name = info.get("name", "")
    try:
        sig_clean = sig.strip().rstrip(";")
        # Parse: rettype __thiscall(params) or rettype(params)
        paren = sig_clean.find("(")
        if paren <= 0:
            return False
        prefix = sig_clean[:paren].strip()
        pstr = sig_clean[paren + 1:sig_clean.rfind(")")] if sig_clean.rfind(")") > paren else ""
        # Extract return type
        cc = '__thiscall'
        for c in ['__thiscall', '__cdecl', '__stdcall', '__fastcall']:
            if c in prefix:
                cc = c
                break
        ret_str = prefix.replace(cc, '').strip()
        # Build function type
        ftd = ida_typeinf.func_type_data_t()
        ftd.rettype = _resolve_member_type(ret_str, til)
        if ftd.rettype is None:
            ret_str_try = ret_str.replace('struct ', '').replace('class ', '')
            ftd.rettype = _resolve_member_type(ret_str_try, til)
        if ftd.rettype is None:
            return False
        ftd.cc = {'__thiscall': ida_typeinf.CM_CC_THISCALL,
                  '__cdecl': ida_typeinf.CM_CC_CDECL,
                  '__stdcall': ida_typeinf.CM_CC_STDCALL,
                  '__fastcall': ida_typeinf.CM_CC_FASTCALL}.get(cc, ida_typeinf.CM_CC_THISCALL)
        # Parse params
        if pstr and pstr.strip() not in ('', 'void'):
            depth = 0
            cur = ''
            for ch in pstr:
                if ch in '<([':
                    depth += 1
                    cur += ch
                elif ch in '>)]':
                    depth -= 1
                    cur += ch
                elif ch == ',' and depth == 0:
                    if cur.strip():
                        _pt = _resolve_member_type(cur.strip(), til)
                        if _pt is not None:
                            fa = ida_typeinf.funcarg_t()
                            fa.type = _pt
                            ftd.push_back(fa)
                    cur = ''
                else:
                    cur += ch
            if cur.strip():
                _pt = _resolve_member_type(cur.strip(), til)
                if _pt is not None:
                    fa = ida_typeinf.funcarg_t()
                    fa.type = _pt
                    ftd.push_back(fa)
        ft = ida_typeinf.tinfo_t()
        if not ft.create_func(ftd):
            return False
        return ida_typeinf.apply_type(til, ft, addr)
    except Exception:
        return False


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
    log("[0] Un-named %d stale functions" % _unnamed)

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
            else:
                # add_func without arg failed — try with explicit end (next
                # function boundary). This handles functions without standard
                # prologues (e.g. AStarPathFinder::NODE methods at 0x401500).
                _next_func = _ida_funcs.get_next_func(addr)
                if _next_func:
                    if _ida_funcs.add_func(addr, _next_func.start_ea):
                        created += 1
        if name:
            # Skip functions outside PAL3.exe code range (gbengine imports etc.)
            if addr < 0x00401000 or addr > 0x005695D0:
                continue
            cur = ida_name.get_name(addr) or ""
            if cur == name:
                renamed += 1
                continue

            # Delete existing name first (required for mangled names like ?xxx@yyy@@)
            if cur:
                ida_name.set_name(addr, "", ida_name.SN_NOWARN)

            # Use mangled name for class methods (globally unique, no _N conflict)
            # or simple name for free functions.
            if '::' in name:
                _parts = name.rsplit('::', 1)
                _cls = _parts[0]   # may include :: for nested types
                _method = _parts[1]
                _sig = info.get('signature', '')
                _mangled = _mangle_vc6(_cls, _method, _sig)
                if _mangled and ida_name.set_name(addr, _mangled, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                    renamed += 1
                else:
                    rename_fail.append((addr_str, cur, name))
            else:
                if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                    renamed += 1
                else:
                    rename_fail.append((addr_str, cur, name))

    # Also name skip_functions (not decompiled, but callers need their names)
    skip_path = os.path.join(ANNOTATIONS_DIR, "skip_functions.json")
    skip_named = 0
    skip_funcs = {}
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

    log("[1] Functions: created=%d, renamed=%d/%d, skip_named=%d, rename_fail=%d" %
          (created, renamed, len(funcs), skip_named, len(rename_fail)))
    if rename_fail:
        for _addr, _old, _new in rename_fail[:10]:
            print("    [!] %s: '%s' → '%s' FAILED" % (_addr, _old[:40], _new[:40]))

    # --- 2. Globals (names only; types deferred to step 6b after structs) ---
    globs = data.get("globals", {})
    g_named = 0
    g_typed = 0
    til = ida_typeinf.get_idati()
    for addr_str, info in globs.items():
        addr = int(addr_str, 16)
        name = info.get("name", "")
        gtype = info.get("type", "")
        if name:
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                g_named += 1
        # Set type for globals with explicit type annotations (skip "skip" and empty)
        if name and gtype and gtype != "skip":
            if idc.SetType(addr, gtype):
                g_typed += 1

    log("[2] Globals: named=%d/%d, typed=%d (incl. deferred)" % (g_named, len(globs), g_typed))

    # --- 2b. SDK types (from data/annotations/sdk_types.json) ---
    _sdk_path = os.path.join(ANNOTATIONS_DIR, "sdk_types.json")
    _sdk_ok = 0
    _sdk_total = 0
    if os.path.exists(_sdk_path):
        try:
            with open(_sdk_path, 'r', encoding='utf-8') as _sf:
                _sdk_data = json.load(_sf)
            _sdk_total = len(_sdk_data)
            for _st in _sdk_data:
                _sn = _st.get("name", "")
                if not _sn or not _st.get("known_members"):
                    continue
                try:
                    _r = build_struct_decl(_sn, _st)
                    if _r and _r[0]:
                        _sdk_ok += 1
                except Exception as _e:
                    log("  [!] SDK type %s FAILED: %s" % (_sn, _e))
        except Exception as _e:
            log("  [!] SDK types load FAILED: %s" % _e)
    log("[2b] SDK types: %d/%d" % (_sdk_ok, _sdk_total))

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
                if '::' in base:
                    continue  # nested types — forward decl via parent struct
                fwd_names.add(base)
    fwd_ok = 0
    fwd_skip = 0
    for name in sorted(fwd_names):
        existing = ida_typeinf.tinfo_t()
        if existing.get_named_type(til, name):
            fwd_skip += 1
            continue
        _udt = ida_typeinf.udt_type_data_t()
        _udt.total_size = 0
        _t = ida_typeinf.tinfo_t()
        if _t.create_udt(_udt, ida_typeinf.BTF_STRUCT):
            _t.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
            fwd_ok += 1
    log("[3a] Forward declarations: %d new, %d skipped (already in til)" % (fwd_ok, fwd_skip))

    # --- 3b. Enums (via ida_enum API, 不用 parse_decl) ---
    enums = data.get("enums", {})
    e_ok = 0
    for ename, einfo in enums.items():
        values = einfo.get("values", {})
        if not values:
            continue
        if idc.get_enum(ename) != -1:
            e_ok += 1  # Already exists from PDB import
            continue
        eid = idc.add_enum(-1, ename, 1)
        if eid != -1:
            for k, v in values.items():
                val = int(v, 0) if isinstance(v, str) else v
                idc.add_enum_member(eid, k, val)
            e_ok += 1
    log("[3b] Enums: applied=%d/%d" % (e_ok, len(enums)))

    # Topological sort: dependencies (base classes + value-type members) first
    import re as _re2
    all_struct_names = set(structs.keys())

    def get_deps(sinfo):
        deps = set()
        base = sinfo.get("base_class")
        # Handle both single base (string) and multiple bases (list)
        if isinstance(base, list):
            for b in base:
                if b in all_struct_names:
                    deps.add(b)
        elif base and base in all_struct_names:
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

    functions = data.get("functions", {})

    # Aggregate per-class vtables into (struct_name, ordered_slots) jobs.
    vtable_jobs = []
    for sname, sinfo in structs.items():
        for vt_addr, slots in resolve_vtable_slots(sinfo, functions):
            if vt_addr and slots:
                vtable_jobs.append((vt_addr, slots))

    import re as _re3
    vt_pre = 0
    for vt_addr, slots in vtable_jobs:
        struct_name = "vtbl_%s" % vt_addr[2:]
        lines = []
        seen_names = set()
        for i, (slot_addr, short_name, sig, _from) in enumerate(slots):
            short = short_name or ("method_%d" % i)
            short = _re3.sub(r'[^a-zA-Z0-9_]', '_', short) if short else ("method_%d" % i)
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
        _vt_udt = ida_typeinf.udt_type_data_t()
        _vt_off = 0
        for _line in lines:
            _line = _line.strip().rstrip(';')
            if not _line:
                continue
            _fp_m = re.match(r'(.*?)\((.*?)\*(.*?)\)(\(.*\))$', _line)
            if not _fp_m:
                continue
            _ret_str = _fp_m.group(1).strip()
            _cc_str = _fp_m.group(2).strip()
            _fn_str = _fp_m.group(3).strip()
            _args_str = _fp_m.group(4).strip()
            _ret_ti = _resolve_member_type(_ret_str, til)
            if _ret_ti is None:
                continue
            _cc_map = {'__thiscall': ida_typeinf.CM_CC_THISCALL, '__cdecl': ida_typeinf.CM_CC_CDECL, '__stdcall': ida_typeinf.CM_CC_STDCALL}
            _fd = ida_typeinf.func_type_data_t()
            _fd.rettype = _ret_ti
            _fd.cc = _cc_map.get(_cc_str, ida_typeinf.CM_CC_THISCALL)
            if _args_str.strip('()'):
                _inner = _args_str.strip('()').strip()
                for _ap in re.split(r',\s*(?![^<>]*>)', _inner):
                    _ap = _ap.strip().rstrip(')')
                    _ap_tokens = _ap.rsplit(None, 1)
                    if len(_ap_tokens) > 1 and not _ap_tokens[1].startswith('*'):
                        _ap = _ap_tokens[0]
                    _ap_ti = _resolve_member_type(_ap, til)
                    if _ap_ti is not None:
                        _fa = ida_typeinf.funcarg_t(); _fa.type = _ap_ti; _fd.push_back(_fa)
            _ft = ida_typeinf.tinfo_t()
            if not _ft.create_func(_fd):
                continue
            _fpt = ida_typeinf.tinfo_t()
            if not _fpt.create_ptr(_ft):
                continue
            _vtm = ida_typeinf.udt_member_t()
            _vtm.offset = _vt_off
            _vtm.type = _fpt
            _vtm.name = _fn_str
            _vt_udt.push_back(_vtm)
            _vt_off += 4
        _vt_udt.total_size = _vt_off
        ida_typeinf.del_named_type(til, struct_name, ida_typeinf.NTF_TYPE)
        _t = ida_typeinf.tinfo_t()
        if _vt_off > 0 and _t.create_udt(_vt_udt, ida_typeinf.BTF_STRUCT):
            _t.set_named_type(til, struct_name, ida_typeinf.NTF_REPLACE)
            vt_pre += 1
        elif _vt_off == 0:
            _u = ida_typeinf.udt_type_data_t()
            _u.total_size = 0
            _t2 = ida_typeinf.tinfo_t()
            if _t2.create_udt(_u, ida_typeinf.BTF_STRUCT):
                _t2.set_named_type(til, struct_name, ida_typeinf.NTF_REPLACE)
            vt_pre += 1
            # _vt_off > 0 but create_udt failed — log it
            pass
    log("[3a] Vtable structs pre-created: %d/%d" % (vt_pre, len(vtable_jobs)))
    log("[3a] Starting TAUDT_FIXED struct import...")

    # --- TAUDT_FIXED struct import: precise offsets from annotation ---
    s_ok = 0
    s_fail = []
    s_errors = []

    log("  Structs: %d total (dependency order by topological sort)" % len(ordered))

    # Pre-create forward declarations for ALL nested types (recursive,
    # arbitrary depth) BEFORE the main loop. This ensures any struct
    # referencing Parent::Nested as a member type can resolve it
    # (e.g. CEmitter has CParticleSystem::EmitterAttribute).
    def _forward_decl_nested(parent_name, parent_sinfo, til):
        """Recursively create forward decls for all depths of nested types."""
        for _nt_name, _nt_info in parent_sinfo.get("nested_types", {}).items():
            _nt_full = "%s::%s" % (parent_name, _nt_name)
            _probe = ida_typeinf.tinfo_t()
            if _probe.get_named_type(til, _nt_full):
                continue
            _nt_kind = _nt_info.get("kind", "")
            if _nt_kind in ("struct", "class"):
                _u = ida_typeinf.udt_type_data_t()
                _u.total_size = _nt_info.get("binary_size", 0)
                _t = ida_typeinf.tinfo_t()
                if _t.create_udt(_u, ida_typeinf.BTF_STRUCT):
                    _t.set_named_type(til, _nt_full, ida_typeinf.NTF_REPLACE)
            elif _nt_kind == "enum":
                # Create as enumeration (parent struct forward-declared in step 3a)
                _eid = idc.add_enum(-1, _nt_full, 4)
                if _eid != -1:
                    _nt_values = _nt_info.get("values", {})
                    for _k, _v in _nt_values.items():
                        _val = int(_v, 0) if isinstance(_v, str) else _v
                        idc.add_enum_member(_eid, _k, _val)
            _forward_decl_nested(_nt_full, _nt_info, til)

    for _sname, _sinfo in ordered:
        _forward_decl_nested(_sname, _sinfo, til)
    log("  Nested type forward decls: pre-created (recursive)")

    # 导入所有 struct（严格模式：任何失败直接终止）
    for sname, sinfo in ordered:
        ok, err = create_fixed_struct(sname, sinfo, structs, {}, til)
        if ok:
            s_ok += 1
        else:
            log("[FATAL] Struct import failed: %s → %s" % (sname, err))
            s_fail.append((sname, err))
            continue  # skip nested if parent failed

        # Create nested types recursively (arbitrary depth) — same create_fixed_struct, full args
        def _create_nested_recursive(parent_name, parent_sinfo):
            """Recursively create nested types in TIL (arbitrary depth)."""
            for _nt_name, _nt_info in parent_sinfo.get("nested_types", {}).items():
                _nt_kind = _nt_info.get("kind", "")
                _nt_full = "%s::%s" % (parent_name, _nt_name)
                if _nt_kind in ("struct", "class"):
                    _nt_data = dict(_nt_info)
                    _nt_data.pop("kind", None)
                    _nt_data.setdefault("known_members", {})
                    _nt_mtd = _nt_data.get("methods", {})
                    for _addr, _minfo in _nt_mtd.items():
                        _mn = _minfo.get("name", "")
                        if _mn and "::" not in _mn:
                            _minfo["name"] = "%s::%s" % (_nt_full, _mn)
                    ok_nt, err_nt = create_fixed_struct(_nt_full, _nt_data, structs, {}, til)
                    if not ok_nt:
                        log("  [!] nested struct %s FAILED: %s" % (_nt_full, err_nt))
                elif _nt_kind == "enum":
                    _nt_values = _nt_info.get("values", {})
                    if not _nt_values:
                        continue
                    # Enum should already be created by _forward_decl_nested.
                    # Only add values if the enum exists but has no members.
                    _old_eid = idc.get_enum(_nt_full)
                    if _old_eid == -1 or _old_eid == 0xFFFFFFFF:
                        ida_typeinf.del_named_type(til, _nt_full, ida_typeinf.NTF_TYPE)
                        _eid = idc.add_enum(-1, _nt_full, 4)
                        if _eid != -1 and _eid != 0xFFFFFFFF:
                            for _k, _v in _nt_values.items():
                                _val = int(_v, 0) if isinstance(_v, str) else _v
                                try:
                                    idc.add_enum_member(_eid, _k, _val)
                                except ValueError:
                                    pass  # duplicate member, ignore
                # Recurse deeper (arbitrary depth)
                _create_nested_recursive(_nt_full, _nt_info)

        _create_nested_recursive(sname, sinfo)

    if s_fail:
        log("[FATAL] %d struct imports FAILED — aborting. Fix annotation offsets or types." % len(s_fail))
        for _sn, _se in s_fail:
            log("  [FAIL] %s: %s" % (_sn, _se))
        raise RuntimeError("Struct import failures: %d\nSee [FAIL] entries above for details." % len(s_fail))
    log("[3] Structs: %d/%d imported successfully (fail=%d)" % (s_ok, len(structs), len(s_fail)))

    # (Enums already applied in step 3b, before structs)

    # --- 5. Vtable .rdata typing ---
    vt_applied = 0
    for vt_addr_hex, slots in vtable_jobs:
        if not slots:
            continue
        struct_name = "vtbl_%s" % vt_addr_hex[2:]
        if idc.SetType(int(vt_addr_hex, 16), "%s x;" % struct_name):
            vt_applied += 1

    log("[5] Vtable .rdata typed: %d/%d" % (vt_applied, len(vtable_jobs)))

    # Wait for type system to settle before applying signatures
    ida_auto.auto_wait()

    # --- 6. Function signatures (after structs so types are resolved) ---
    import re as _re_sig
    sig_ok = 0
    sig_fail = []
    sig_skip_placeholder = 0

    # Build a combined list: functions.json + struct/*.json methods
    _sig_entries = list(funcs.items())
    _structs_dir = os.path.join(ANNOTATIONS_DIR, "structs")
    if os.path.isdir(_structs_dir):
        for _sf in sorted(os.listdir(_structs_dir)):
            if not _sf.endswith('.json'):
                continue
            try:
                _sd = json.load(open(os.path.join(_structs_dir, _sf), encoding='utf-8'))
            except:
                continue
            for _addr_str, _minfo in _sd.get('methods', {}).items():
                if _minfo.get('signature') and _addr_str not in funcs:
                    _sig_entries.append((_addr_str, _minfo))

    for addr_str, info in _sig_entries:
        addr = int(addr_str, 16)
        # Skip entries listed in skip_functions.json (compiler-generated, etc.)
        if addr_str in skip_funcs:
            continue
        sig = info.get("signature", "")
        name = info.get("name", "")
        if not sig:
            continue
        # Skip placeholder signatures (IDA-unknown params, no value to apply)
        if '(...)' in sig:
            sig_skip_placeholder += 1
            continue
        sig_raw = sig.strip().rstrip(";")
        # Strip IDA-specific modifiers that SetType doesn't accept
        # (parse_decl PT_TYP is used for final application and handles C++ keywords)
        sig_raw = _re_sig.sub(r'__usercall|__userpurge', '', sig_raw)
        sig_raw = _re_sig.sub(r'@<[\w:]+>', '', sig_raw)  # register annotations
        sig_raw = sig_raw.replace(' __noreturn', '')
        sig_raw = _re_sig.sub(r'\s*__spoils<[^>]*>', '', sig_raw)
        sig_raw = sig_raw.strip()
        # Clean up redundant calling conventions for member functions
        if ("::" in name or "*this" in sig_raw) and "__cdecl" in sig_raw and "__thiscall" in sig_raw:
            # Member function with both __cdecl and __thiscall - remove __cdecl
            sig_raw = sig_raw.replace("__cdecl ", "")
        # Fix common type name issues
        sig_raw = sig_raw.replace("(string *", "(std::string *")  # string → std::string
        sig_raw = sig_raw.replace(", string *", ", std::string *")
        sig_raw = sig_raw.replace(" string *", " std::string *")
        # Fix format issues: int__cdecl → int __cdecl (but NOT Render__ovl → Render __ovl)
        import re as _re_format
        sig_raw = _re_format.sub(r'(\w)__(cdecl|thiscall|stdcall|fastcall)\b', r'\1 __\2', sig_raw)
        paren_idx = sig_raw.find("(")
        if paren_idx > 0:
            # Auto-complete this pointer for class methods.
            # Signatures in annotations no longer redundantly store ClassName *this.
            # Extract class from function name and prepend if missing.
            # Only for __thiscall methods: __cdecl/__stdcall/__fastcall are static and have no this.
            if "::" in name:
                _cls = name.split("::")[0]
                _cc_is_thiscall = '__thiscall' in sig_raw
                _params = sig_raw[paren_idx:]
                if _cc_is_thiscall and not re.search(r'\b' + re.escape(_cls) + r'\s*\*\s*this', _params):
                    _before = sig_raw[:paren_idx].rstrip()
                    # Insert ClassName *this as first param
                    if _params.startswith('(') and _params[1:].strip() and _params[1:].strip()[0] != ')':
                        _new_params = '(%s *this, %s' % (_cls, _params[1:])
                    else:
                        _new_params = '(%s *this)' % _cls
                    sig_raw = _before + _new_params
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
            # Strip own class prefix for __thiscall return type (function type setup
            # handles this implicitly)
            # Apply via idc.SetType — handles virtual, thiscall, etc.
            if idc.SetType(addr, sig_with_name):
                sig_ok += 1
            else:
                stripped = sig_with_name.replace("struct ", "").replace("class ", "")
                if stripped != sig_with_name and idc.SetType(addr, stripped):
                    sig_ok += 1
                else:
                    # Final fallback: apply via tinfo_t API (handles :: in types)
                    if _try_apply_type_tinfo(addr, sig, info, til):
                        sig_ok += 1
                    else:
                        sig_fail.append((addr_str, name, sig_with_name))

    if sig_fail:
        # Write detailed failure log
        sig_fail_log = os.path.join(SCRIPT_DIR, "_logs", "signature_failures.txt")
        with open(sig_fail_log, 'w', encoding='utf-8') as f:
            f.write("SIGNATURE APPLICATION FAILURES (%d total):\n\n" % len(sig_fail))
            for addr_str, fname, sig_str in sig_fail:
                f.write("%s %s\n  → %s\n\n" % (addr_str, fname, sig_str))
        log("[!] Signature failures logged: %s" % sig_fail_log)
        for addr_str, fname, sig_str in sig_fail[:5]:
            log("  [!] %s %s → %s" % (addr_str, fname[:40], sig_str[:60]))
    log("[6] Signatures: %d/%d (fail=%d, placeholder=%d)" % (sig_ok, len([f for f in funcs.values() if f.get("signature")]), len(sig_fail), sig_skip_placeholder))
    if sig_fail:
        for _addr_s, _fname_s, _err_s in sig_fail[:20]:
            log("  [!] %s: %s → %s" % (_addr_s, _fname_s[:40], _err_s[:60]))

    # --- 6b. Global types (after structs so struct types are resolved) ---
    g_typed = 0
    g_type_fail = []
    for addr_str, info in globs.items():
        addr = int(addr_str, 16)
        typ = info.get("type", "")
        if typ:
            if typ.strip() == "skip":
                g_typed += 1
                continue
            type_str = typ.rstrip(";") + ";"
            if idc.SetType(addr, type_str):
                g_typed += 1
            else:
                stripped = type_str.replace("struct ", "").replace("class ", "")
                if stripped != type_str and idc.SetType(addr, stripped):
                    g_typed += 1
                else:
                    g_type_fail.append((addr_str, info.get("name", ""), typ))

    log("[6b] Global types: %d/%d (fail=%d)" % (g_typed, len([g for g in globs.values() if g.get("type")]), len(g_type_fail)))
    if g_type_fail:
        log("[6b] Global type failures: %d" % len(g_type_fail))
        for addr_str, gname, typ in g_type_fail[:20]:
            log("  [!] %s %s → %s" % (addr_str, gname[:40] if gname else "?", typ[:60]))

    # --- 6b2. Create IDA data arrays for array-typed globals ---
    # SetType alone sets type metadata but doesn't create data items in IDA's
    # data segment. Without actual data array creation, Hex-Rays cannot resolve
    # element accesses (e.g., g_fCamRoleParams[5] stays as dword_XXXXXX).
    _ELEM_SIZES = {
        'char': 1, 'unsigned char': 1, 'BYTE': 1, '_BYTE': 1, 'bool': 1,
        'CHAR': 1, 'UCHAR': 1, 'signed char': 1,
        'short': 2, 'unsigned short': 2, 'WORD': 2, '_WORD': 2, 'SHORT': 2,
        'int': 4, 'unsigned int': 4, 'DWORD': 4, '_DWORD': 4,
        'long': 4, 'unsigned long': 4, 'UINT': 4, 'BOOL': 4, 'INT': 4,
        'float': 4, 'double': 8, '__int64': 8,
    }
    arr_created = 0
    arr_fail = []
    _arr_re = re.compile(r'^(.+?)\s*\[(\d+)\]$')
    for addr_str, info in globs.items():
        typ = info.get("type", "")
        m = _arr_re.match(typ)
        if not m:
            continue
        elem_type = m.group(1).strip()
        count = int(m.group(2))
        if count <= 0:
            continue
        addr = int(addr_str, 16)

        # Determine element size
        if '*' in elem_type:
            elem_size = 4  # 32-bit pointers
        elif elem_type in _ELEM_SIZES:
            elem_size = _ELEM_SIZES[elem_type]
        else:
            # Struct/class type — try to get size from IDA's type system
            til = ida_typeinf.get_idati()
            tif = ida_typeinf.tinfo_t()
            if tif.get_named_type(til, elem_type):
                elem_size = tif.get_size()
            else:
                elem_size = 0

        if elem_size <= 0:
            arr_fail.append((addr_str, info.get("name", ""), typ, "unknown elem size"))
            continue

        total_size = elem_size * count
        # Clear existing data items in this range
        ida_bytes.del_items(addr, ida_bytes.DELIT_SIMPLE, total_size)

        # Create first element with correct data type
        if elem_size == 1:
            ok = idc.create_byte(addr)
        elif elem_size == 2:
            ok = idc.create_word(addr)
        elif elem_size == 4:
            ok = idc.create_dword(addr)
        elif elem_size == 8:
            ok = idc.create_qword(addr)
        else:
            # Struct-sized elements: create as bytes, rely on SetType for struct info
            ok = idc.create_byte(addr)

        if ok:
            # Expand the first element into an array of `count` elements
            idc.make_array(addr, count)
            arr_created += 1
        else:
            arr_fail.append((addr_str, info.get("name", ""), typ, "create_data failed"))

    if arr_created:
        log("[6b2] Array globals created: %d" % arr_created)
    if arr_fail:
        log("[6b2] Array creation failures: %d" % len(arr_fail))
        for addr_str, name, typ, reason in arr_fail[:5]:
            log("  [!] %s %s (%s): %s" % (addr_str, name, typ, reason))

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
    log("[8] Signature retry: %d/%d recovered" % (sig_retry, len(sig_fail)))

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
    log("[8b] Global type retry: %d/%d recovered" % (g_type_retry, len(g_type_fail)))

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

        ann_by_name = {}
        ann_by_stkoff = {}
        for lv_ann in lvars_ann:
            fn = lv_ann.get("from_name")
            if fn is not None:
                ann_by_name[fn] = lv_ann
            sk = lv_ann.get("stack_offset")
            if sk is not None:
                ann_by_stkoff[sk] = lv_ann
        if not ann_by_name and not ann_by_stkoff:
            lvar_fail += len(lvars_ann)
            continue

        try:
            cfunc = ida_hexrays.decompile(func)
        except:
            # Force fresh decompilation (clear cache)
            ida_hexrays.del_heap_decomp(addr)
            try:
                cfunc = ida_hexrays.decompile(func)
            except:
                lvar_fail += len(lvars_ann)
                continue
        if not cfunc:
            lvar_fail += len(lvars_ann)
            continue

        modified = False
        for lvar in list(cfunc.lvars):
            is_reg = lvar.is_reg_var()
            ann = ann_by_name.get(lvar.name)
            if ann is None and ann_by_stkoff and not is_reg:
                try:
                    if lvar.is_stk_var():
                        soff = lvar.get_stkoff()
                        ann = ann_by_stkoff.get(soff)
                except:
                    pass
            if ann is None:
                continue
            new_name = ann.get("name")
            if new_name and lvar.name != new_name:
                lvar.name = new_name
                modified = True
            new_type = ann.get("type")
            if new_type and not is_reg:
                tif = _resolve_member_type(new_type, ida_typeinf.get_idati())
                if tif is not None:
                    try:
                        lvar.set_lvar_type(tif)
                        modified = True
                    except:
                        pass
            lvar_ok += 1

        if modified:
            try:
                uvec = ida_hexrays.lvar_uservec_t()
                uvec.lvvec = ida_hexrays.lvar_saved_infos_t()
                for lv in cfunc.lvars:
                    si = ida_hexrays.lvar_saved_info_t()
                    ll = ida_hexrays.lvar_locator_t()
                    ll.defea = cfunc.entry_ea
                    si.ll = ll
                    si.name = lv.name
                    uvec.lvvec.push_back(si)
                ida_hexrays.save_user_lvar_settings(addr, uvec)
            except Exception as e:
                log("[9] lvar save failed: %s" % str(e))

    log("[9] Lvars: %d/%d applied (fail=%d)" % (lvar_ok, lvar_total, lvar_fail))

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
    # Disable auto-analysis to prevent further type propagation from reverting names
    ida_auto.set_auto_state(False)
    log("[11] Step 11 reached, funcs=%d" % len(funcs))
    _force_renamed = 0
    _total = 0
    for addr_str, info in funcs.items():
        addr = int(addr_str, 16)
        desired = info.get("name", "")
        if not desired:
            continue
        # Compute expected name: mangled for class methods, simple for free functions
        if '::' in desired:
            _parts = desired.rsplit('::', 1)
            _cls = _parts[0]
            _method = _parts[1]
            _sig = info.get('signature', '')
            _expected = _mangle_vc6(_cls, _method, _sig)
        else:
            _expected = desired
        if not _expected:
            continue
        cur = ida_name.get_name(addr) or ""
        # Always set expected name (type propagation may have overridden)
        ida_name.set_name(addr, "", ida_name.SN_NOWARN)
        if ida_name.set_name(addr, _expected, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            _force_renamed += 1
    log("[11] Force-renamed %d/%d" % (_force_renamed, len(funcs)))

    idc.save_database(idc.get_idb_path(), 0)
    log("[*] Done. Database saved.")

    # Write log file
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))

    idc.qexit(0)


if __name__ == "__main__":
    try:
        apply_annotations()
    except Exception as e:
        import traceback, os
        err_log = os.path.join(SCRIPT_DIR, "_logs", "apply_exception.txt")
        os.makedirs(os.path.dirname(err_log), exist_ok=True)
        with open(err_log, 'w') as f:
            f.write("EXCEPTION in apply_annotations:\n")
            f.write(str(e) + "\n\n")
            f.write(traceback.format_exc())
        # Also write log_lines before exit
        if log_lines:
            os.makedirs(LOG_DIR, exist_ok=True)
            with open(LOG_FILE, 'w', encoding='utf-8') as f:
                f.write('\n'.join(log_lines))
        print("[FATAL] Exception: %s" % str(e))
        print("[FATAL] See %s for details" % err_log)
        idc.qexit(1)
