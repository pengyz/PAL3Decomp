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
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
sys.path.insert(0, PROJECT_ROOT)
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "apply_annotations_log.txt")
PDB_EXPORT = os.path.join(PROJECT_ROOT, "data", "pdb", "pdb_export.json")

from pipeline.gen.annotation_view import iter_struct_files, iter_structs, load_struct


def _strict_struct_entries(directory):
    for path in iter_struct_files(directory):
        struct_data = load_struct(path)
        if not isinstance(struct_data, dict):
            raise ValueError('%s: struct annotation must be a JSON object' % path)
    return list(iter_structs(directory))

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
    # 2026-09-27：Hex-Rays 惯用拼写补全（g_pSceneTransitionEnd 'unsigned __int8 *'
    # 过不了 _resolve_member_type ⇒ apply FATAL 阻断全链）
    '__int8': ida_typeinf.BTF_INT8,
    'unsigned __int8': ida_typeinf.BTF_BYTE,
    '__int16': ida_typeinf.BTF_INT16,
    'unsigned __int16': ida_typeinf.BTF_UINT16,
    '__int32': ida_typeinf.BTF_INT32,
    'unsigned __int32': ida_typeinf.BTF_UINT32,
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


def _resolve_type_object(tdef, til):
    """Build tinfo_t from {'union': [...]} or {'struct': [...]} annotation type.
    Recursively resolves nested types.
    """
    if not isinstance(tdef, dict):
        return None
    if "union" in tdef:
        return _build_udt(tdef["union"], til, is_union=True)
    if "struct" in tdef:
        return _build_udt(tdef["struct"], til, is_union=False)
    return None


def _build_udt(members, til, is_union):
    """Build a UDT from member definitions using IDA's UDT API.
    Returns tinfo_t or None on failure.
    """

    def _usz(mtype, til):
        """Estimate size of a member type for union total_size computation."""
        if isinstance(mtype, dict):
            # Recursive: union/struct
            inner = _resolve_type_object(mtype, til)
            return inner.get_size() if inner else 4
        t = _resolve_member_type(mtype, til)
        if t and t.get_size() not in (0, 0xFFFFFFFFFFFFFFFF):
            return t.get_size()
        return 4

    udt = ida_typeinf.udt_type_data_t()
    if is_union:
        udt.is_union = True
    else:
        udt.taudt_bits = 1024

    cursor = 0
    for m in members:
        mname = m.get("name", "")
        mtype = m.get("type", "int")
        moff = m.get("offset")

        if isinstance(mtype, dict):
            tinfo = _resolve_type_object(mtype, til)
        else:
            tinfo = _resolve_member_type(mtype, til)

        if tinfo is None:
            log("[!] _build_udt: cannot resolve type for '%s'" % mname)
            return None

        tsz = tinfo.get_size()
        if tsz in (0, 0xFFFFFFFFFFFFFFFF):
            log("[!] _build_udt: invalid size %d for '%s'" % (tsz, mname))
            return None

        offset = moff if moff is not None else cursor

        um = ida_typeinf.udt_member_t()
        um.name = mname
        um.offset = offset * 8
        um.size = tsz * 8
        um.type = tinfo
        udt.push_back(um)

        if not is_union:
            cursor = max(cursor, offset + tsz)

    if not is_union:
        udt.total_size = cursor
    else:
        _max_usz = 0
        for _um in members:
            _usz_val = _usz(_um.get("type", "int"), til)
            _uoff = _um.get("offset", 0)
            _uend = _uoff + _usz_val
            if _uend > _max_usz:
                _max_usz = _uend
        udt.total_size = _max_usz

    result = ida_typeinf.tinfo_t()
    flag = ida_typeinf.BTF_UNION if is_union else ida_typeinf.BTF_STRUCT
    if not result.create_udt(udt, flag):
        log("[!] _build_udt: create_udt failed")
        return None
    return result


def log(msg):
    log_lines.append(str(msg))
    print(msg)




def _import_gbengine_headers():
    """从 include/gbengine/*.h 直接导入 gbengine 类型到 IDB local types。
    单一真相源：gbengine 类型只在头文件中定义，annotation JSON 不再重复。
    (2026-09-25 消除双数据源同步问题)"""
    import glob
    import ida_typeinf
    root = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    inc_dir = os.path.join(root, 'include', 'gbengine')
    prelude_path = os.path.join(root, 'data', 'annotations', 'gbengine_prelude.h')
    
    if not os.path.isdir(inc_dir):
        log("  [gbengine] include dir not found: %s" % inc_dir)
        return 0
    
    prelude = ''
    if os.path.exists(prelude_path):
        prelude = open(prelude_path, encoding='utf-8').read()
    
    til = ida_typeinf.get_idati()
    imported = 0
    headers = sorted(glob.glob(os.path.join(inc_dir, '*.h')))
    for hdr_path in headers:
        hdr_name = os.path.basename(hdr_path)
        try:
            content = open(hdr_path, encoding='utf-8').read()
            content = re.sub(r'^\s*#include.*$', '', content, flags=re.MULTILINE)
            content = re.sub(r'^\s*#pragma.*$', '', content, flags=re.MULTILINE)
            full = prelude + '\n' + content
            result = ida_typeinf.parse_decls(til, full, None, ida_typeinf.PT_SIL | ida_typeinf.PT_REPLACE)
            imported += 1
            log("  [gbengine] %s (parse=%d)" % (hdr_name, result))
        except Exception as e:
            log("  [gbengine] ERROR %s: %s" % (hdr_name, e))
    
    log("  [gbengine] done: %d/%d headers" % (imported, len(headers)))
    return imported

def _make_vtable_method_type(ann_sig, vm_short, til, cls_name=None):
    """从 annotation 签名创建 vtable 方法类型，纯 API 不用 parse_decl。"""
    if '(' not in ann_sig:
        return None
    open_paren = ann_sig.index('(')
    close_paren = ann_sig.rindex(')')
    prefix = ann_sig[:open_paren].strip()
    params_str = ann_sig[open_paren+1:close_paren].strip()
    # Strip __hidden this (IDA annotation, not valid C++ type)
    params_str = re.sub(r'\w+\s*\*\s*(?:__hidden\s+)?this\s*,?\s*', '', params_str)
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
    # Insert `Cls *__hidden this` as first arg — IDA's official this-argument
    # spelling. Keeps the vtbl slot type consistent with the function's own
    # definite type, so vcall sites decompile as obj->Method(...) and the
    # structs-methods vs decomp-signature projections agree.
    if cls_name and cc == ida_typeinf.CM_CC_THISCALL:
        _cls_tif = _resolve_member_type(cls_name, til)
        if _cls_tif is not None:
            _cls_ptr = ida_typeinf.tinfo_t()
            if _cls_ptr.create_ptr(_cls_tif):
                _this_arg = ida_typeinf.funcarg_t()
                _this_arg.type = _cls_ptr
                _this_arg.name = 'this'
                _this_arg.flags = ida_typeinf.FAI_HIDDEN
                func_data.push_back(_this_arg)
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
    base_size = struct_info.get("base_size", 0)
    base_class = struct_info.get("base_class")
    # Half-configured guard: a base without base_size cannot re-base members
    # safely — applying it declares inheritance while keeping the flattened
    # member list, and every descendant's export shifts (observed 2026-09-13:
    # UIWnd/SceneObj writes without base_size cost 9 S2 units). Configured
    # chains (UIFrameWnd:UIWnd base_size=68 etc.) are unaffected.
    if base_class and not base_size:
        base_class = None
    # Handle multiple inheritance: only use first base (IDA's struct model limitation)
    if isinstance(base_class, list):
        base_class = base_class[0] if base_class else None

    # IDA parse_decl cannot handle C++ template base classes
    if base_class and ('<' in base_class or '>' in base_class):
        base_class = None  # drop template inheritance, use gap instead

    if not members and not size:
        return None

    # 复核 5560c6c5 P1：键可带 N_N 数组后缀 —— int('50814_0',0)=508140（Py 下划线
    # 数字分隔符语义）会把键读成 508140 ⇒ 先 split('_')[0] 再解析（与 :986 同款）。
    sorted_members = sorted(
        [(int(str(off).split('_')[0], 0), info) for off, info in members.items()
         if int(str(off).split('_')[0], 0) >= base_size],
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
        mtype_raw = info.get("type", "int")
        if isinstance(mtype_raw, dict):
            continue
        mtype = mtype_raw.replace("class ", "").replace("struct ", "")

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
        # 复核 75f6709b C3 同批：键可 hex/N_N（键谱系 dec 9745/hex 51/N_N 4）——
        # split('_')[0] 去数组后缀 + base=0 认 hex（旧 int(...)=十进制强制，hex 键 ValueError）
        overrides[int(str(k).split('_')[0], 0)] = v
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

    # --- 统一判据（与 create_fixed_struct 逐条一致，消除旧 :654-656 / :866-877 的行为分叉 ---
    #
    # ⚠️ 可达性说明（2026-09-15 t9 独立验证 D2 指出，captain 已修正）：
    # `create_fixed_struct_diff` 全仓**无调用者**（只有本处定义），当前是死代码。
    # 因此下面的"统一"对本轮判定**没有实际作用**——它只是让这个函数在将来被启用时
    # 行为与主路径一致。不要把它当成"两路径已验证统一"的证据。
    #
    # 【关键时序，与 create_fixed_struct 同理】必须先 set_named_type 再读 UDT 详情：
    # 未在 TIL 中命名的 tinfo 上，get_udt_details() 对一部分 UDT 返回 false，
    # 会让 _layout_end_of_members 返回 (None, ...) → `if _oversized:` 为假 →
    # **末端检查被静默跳过**。原先此处的 set_named_type 在检查之后，正是该缺陷。
    result_tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)

    actual_size = result_tinfo.get_size()
    if actual_size == 0xFFFFFFFFFFFFFFFF:
        # diff-mode 的 -1 不是 union 变体形态（本次是 layout 合并失败），正确拒绝。
        return (False, "create_udt produced invalid type (diff mode, get_size=-1)")

    # 末端口径：diff-mode 此前的「偏移校验」同样的盲区也在这里。
    # 注意 _layout_end_of_members 在布局不可读时返回 oversized=None，
    # 此时 `if _oversized:` 为假 —— 故下面显式区分「无越界」与「布局读不到」。
    _oversized, _culprit, _max_end, _n_oversized, _terminal_overflow = \
        _layout_end_of_members(result_tinfo, binary_size)
    if _oversized is None:
        log("[FATAL] %s (diff mode): layout unreadable (get_udt_details failed "
            "after set_named_type) — cannot verify member bounds." % name)
        return (False, "diff mode: layout unreadable for %s" % name)
    if _oversized:
        _omax = max(_oversized, key=lambda t: t[2])
        log("[FATAL] %s (diff mode): %d member(s) out of declared binary_size %d; "
            "max member end +%d '%s' (declared offset +%d)" % (
                name, _n_oversized, binary_size, _omax[2], _omax[1], _omax[0]))
        return (False, "diff mode: %d member(s) out of bounds (max end +%d > binary_size %d)"
                % (_n_oversized, _omax[2], binary_size))

    # PDB 和 PAL3.exe 版本不同，struct size 可能不一致。
    # annotation binary_size 是 PAL3.exe 实测值，应优先采用。
    # 如果合并后 size 不匹配，说明 PDB layout 差异过大，回退 replace 模式。
    if actual_size != binary_size:
        log("  [i] %s (diff mode): merged layout size %d != annotation binary_size %d "
            "— falling back to TAUDT_FIXED replace mode" % (name, actual_size, binary_size))
        return create_fixed_struct(name, struct_info, {}, {}, til)

    return _verify_named_udt(result_tinfo, name, til, binary_size=binary_size)


def _load_incomplete_udt_overrides():
    """读取「已知待修 struct」白名单（逐 struct 留痕覆盖开关）。

    默认**拒绝** apply：白名单文件不存在或为空 dict → 返回空集 → 任何不完整 UDT
    都会让 apply 失败。这是 t3 的硬要求（见 handoff §4 t3 要求 5）：
    覆盖面必须显式、逐 struct、且带登记理由，不允许全局开关。

    文件格式（data/annotations/_incomplete_udt_overrides.json）：
        {
          "StructName": {
            "reason": "为何仍允许 apply（如：已有独立任务跟踪待修）",
            "registered": "2026-09-15",
            "tracking": "t3 / CHANGE_LOG 条目 / issue 链接"
          }
        }
    """
    _ov_path = os.path.join(ANNOTATIONS_DIR, "_incomplete_udt_overrides.json")
    if not os.path.exists(_ov_path):
        return {}
    try:
        with open(_ov_path, "r", encoding="utf-8") as f:
            _ov = json.load(f)
    except Exception as e:
        log("[WARN] %s unreadable (%s) — treating as EMPTY (no overrides)" % (_ov_path, e))
        return {}
    if not isinstance(_ov, dict):
        log("[WARN] %s is not a JSON object — treating as EMPTY" % _ov_path)
        return {}
    return _ov


def _expected_pushed_member_count(struct_info, base_class, base_size):
    """干跑成员循环，算出「应当落入 TIL」的成员数。

    严格复刻 create_fixed_struct 中加入成员时的过滤（基类区域成员被跳过），
    使期望数可与 IDA 实际落入的成员数直接比较。

    注意：union 的同偏移变体（键形如 "12_1"）在 IDA 中可能被合并或重排，
    故该期望数只作为**诊断对照**，不作为硬判据——硬判据是末端口径
    （declared_offset + member_size <= binary_size）。
    """
    expected = 0
    for _off_str in struct_info.get("known_members", {}):
        _off = int(_off_str.split('_')[0], 0)
        if base_class and _off < base_size:
            continue
        expected += 1
    return expected


def _should_authoritative_fallback(reason_codes, binary_size):
    """FATAL 路径权威回退判据（纯函数，R15 单测点）。

    [方案 A 2026-10-16] 两级继承 UDT 读回失败族（41/41 base_class=['UIFrameWnd']）
    ——`get_udt_details()==False` **单因**且 binary_size>0 ⇒ 沿用 [i] 组
    `binary_size` 权威回退（工具已实现该回退，41 只是没走到 FATAL 前）。
    多因/几何越界/计数错 ⇒ 保持 FATAL（不掩盖真几何问题）。
    """
    return (list(reason_codes) == ["get_udt_details()==False (incomplete UDT shell)"]
            and int(binary_size or 0) > 0)


def _layout_end_of_members(result_tinfo, binary_size):
    """按「末端口径」核对已创建 UDT 里每个成员的末端是否越出 binary_size。

    返回 (oversized, culprit, max_end, overflow_count, terminal_overflow)：
      oversized  -- (offset, name, member_end) 列表，逐条越界成员
      culprit    -- 末端最远的成员名（用于报错信息）
      max_end    -- 所有成员的末端最大值（末端口径的观测量）
      overflow_count -- 越界成员数
      terminal_overflow -- 是否存在「末成员撑破边界」形态
                           (= max_end > binary_size，这是 SaleUI 那一类的形态)

    为什么用 member_end 而不是声明偏移：偏移口径会漏掉「成员自身尺寸撑破边界」
    的形态（SaleUI 的 ml_SmeltList@104752 ends 105960 > 105952）。见
    docs/specs/2026-09-15-cleanup-handoff.md §4 t3 要求 2。
    """
    udt_details = ida_typeinf.udt_type_data_t()
    if not result_tinfo.get_udt_details(udt_details):
        # 判据失败：无法读回布局。交由调用方按「不完整 UDT」处置。
        return (None, None, 0, 0, False)

    oversized = []
    max_end = 0
    culprit = None
    for _i in range(udt_details.size()):
        _um = udt_details[_i]
        try:
            if _um.is_bitfield():
                # 位域没有字节粒度的偏移语义，跳过末端检查
                continue
        except Exception:
            pass
        _off = _um.offset // 8
        # 用 udt_member_t.size（原始 bit 宽度）而非 type.get_size()：
        # 后者已含对齐填充，会把末端算大，产生假越界。
        _msize = _um.size // 8
        if _msize <= 0:
            continue
        _end = _off + _msize
        if _end > max_end:
            max_end = _end
            culprit = _um.name
        if _end > binary_size:
            oversized.append((_off, _um.name, _end))

    return (oversized, culprit, max_end, len(oversized), max_end > binary_size)


def _verify_named_udt(result_tinfo, name, til, binary_size=0, has_methods=False):
    """确认 set_named_type 真的把 UDT 落进了 TIL。

    旧代码在此静默放行（set_named_type 无返回值），正是 SceneObj 事故的收口处：
    空壳类型被当成成功。返回 (ok, err_msg)。

    【本函数的 -1 与判据无关，别混淆】这里**只**拒绝一种 -1：
    **不带成员函数**却报 get_size()==-1 —— 那是空壳（UDT 存在但无体）。
    带成员函数的 UDT 报 -1 属已知正常形态（见 create_fixed_struct 的【关键时序】），
    用 has_methods 放行。
    另注：**不要在这里用 get_udt_details()**，它对带成员函数的 UDT 会合法失败。
    """
    _verify_tinfo = ida_typeinf.tinfo_t()
    if not _verify_tinfo.get_named_type(til, name):
        log("[FATAL] %s: set_named_type(NTF_REPLACE) did not land — "
            "type is absent from TIL after import." % name)
        return (False, "set_named_type failed to land %s in TIL" % name)
    _vs = _verify_tinfo.get_size()
    if _vs == 0xFFFFFFFFFFFFFFFF:
        if has_methods:
            # 带成员函数的 UDT 会报 -1：属已知正常形态，放行。
            return (True, None)
        log("[FATAL] %s: TIL entry landed but reports get_size()==-1 **without** "
            "member functions — empty shell (NOT the union-variant -1 form)." % name)
        return (False, "TIL entry for %s is a shell (get_size=-1, no methods)" % name)
    if binary_size > 0 and _vs > binary_size:
        log("[FATAL] %s: TIL entry landed with size %d > binary_size %d." % (
            name, _vs, binary_size))
        return (False, "TIL entry for %s oversized (%d > %d)" % (name, _vs, binary_size))
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
    # [真相源迁移 2026-10-20] 只读 `bases`（含 MI 偏移）——
    # `base_class` 已废弃删除（与 bases 名字信息完全冗余，bases 是超集）。
    # 此处只取名字列表，后续 list/str 形处理逻辑不变。
    _bs_entries = struct_info.get("bases") or []
    base_class_raw = [str(b.get('name')) for b in _bs_entries
                      if isinstance(b, dict) and b.get('name')] or None
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
    # 诊断对照：期望落入的成员数（union 变体可能被 IDA 合并，故只作对照不作硬判据）
    _expected_pushed = _expected_pushed_member_count(struct_info, base_class, base_size)
    if is_union:
        udt.is_union = True
    else:
        is_flexible = struct_info.get("_flexible", False)
        # TAUDT_FIXED + total_size required for non-union structs
        # Without TAUDT_FIXED, IDA ignores explicit member offsets and total_size.
        udt.taudt_bits = 1024
        udt.total_size = binary_size
    # TAUDT_CPPOBJ omitted: its unnamed-member→DAG conversion
    # leaves _BYTE[] placeholders that corrupt base-class export.

    # Add base classes as anonymous members (supports multiple inheritance)
    #
    # ROOT CAUSE (fixed 2026-08-29): IDA's UDT model does natively support
    # multiple base classes — ida_typeinf.udm_t has an is_baseclass()/
    # set_baseclass() flag (backed by TAFLD_BASECLASS) that is independent
    # of member count or offset. Earlier code (see git blame / commit
    # 236a324c0) assumed "IDA's struct model limitation" restricted structs
    # to a single base and only ever wired up base_classes[0]; when support
    # for the remaining bases was added, the anonymous member was created
    # without ever calling set_baseclass(), so IDA silently treated bases
    # 2+ as ordinary unnamed data members. export_full.py then re-derives
    # "is this a base class?" from udm_t.offset == 0 instead of asking
    # is_baseclass() directly, so every base beyond the first (non-zero
    # offset) was exported as a plain (nameless) data member and rendered
    # by emit_headers.py as an untyped struct field — the direct cause of
    # the C2208 "no members defined using this type" cascade across the
    # ~38 multi-base classes (CEff* task templates, Role/UICaption/
    # MUIDialog/SceneObj, etc.). See docs/knowledge/gotcha_codegen_multi_inheritance_anon_member.md.
    _concrete_bases = [bc for bc in base_classes if '<' not in bc and '>' not in bc]
    _base_offset = 0
    # 完整性判据的两个计数器**必须在基类循环之前**初始化：
    # 基类子对象成员在下面的 `udt.push_back(mb)` 里就已经落入 UDT，
    # 而 `get_udt_details()` 的 size() **包含**它们。先前 `_pushed_count = 0`
    # 被放在基类循环**之后**（原 :926），导致**带 base_class 的 struct 系统性欠计数**，
    # 使 `returned != pushed` 恒成立——M3 的死判据之外还叠加了这个错位。
    # 实证：SaleUI(ann 66 − 4 落 base 内 = own 62) + 1 基类 = 63 = returned；
    #        UIChatRest(38 − 0 = 38) + 1 = 39 = returned。
    # 全仓有 176 个带 base_class 且 base_size>0 的非 union struct。
    _pushed_count = 0      # 落入 UDT 的成员总数（含基类子对象）
    _pushed_own = 0        # 其中来自 known_members 的部分（不含基类）
    _n_bases = 0           # 基类子对象个数
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
            mb.set_baseclass()  # mark every base (not just bases[0]) as a real base class
            udt.push_back(mb)
            _pushed_count += 1
            _n_bases += 1
            base_offset += bc_size
        _base_offset = base_offset

    # Add known members at exact annotation offsets
    # Union members use "0", "0_1", "0_2" keys (all at offset 0)
    # （计数器已在基类循环之前初始化，见上。）
    for off_str, minfo in sorted(members.items(), key=lambda x: int(x[0].split('_')[0], 0)):
        offset = int(off_str.split('_')[0], 0)
        if base_class and offset < base_size:
            # vfptr/__vftable included: unnamed base class member at offset 0
            # already covers the vtable pointer within the base subobject.
            continue

        mname = minfo["name"]
        mtype_raw = minfo.get("type", "int")

        # Handle object-typed member (inline union/struct)
        if isinstance(mtype_raw, dict):
            tinfo = _resolve_type_object(mtype_raw, til)
            if tinfo is None:
                return (False, "add member +%d '%s': _resolve_type_object failed" % (
                    offset, mname))
            # Register inline type with a meaningful name to avoid IDA hash names
            _inline_name = "_inline_%s_%s" % (name, mname)
            tinfo.set_named_type(til, _inline_name, ida_typeinf.NTF_REPLACE)
        else:
            mtype_str = _normalize_type(mtype_raw)

            # STL/template types: flatten to char[span] (TIL API can't handle template syntax)
            _is_stl = 'std::' in mtype_str or '<' in mtype_str
            if _is_stl:
                # 复核 75f6709b C3 同批：N_N 键去后缀（int('50814_0',0)=508140 坑）
                sorted_offs = sorted(int(str(o).split('_')[0], 0) for o in members
                                     if int(str(o).split('_')[0], 0) > offset)
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
        if member_size in (0, 0xFFFFFFFFFFFFFFFF):
            return (False, "add member +%d '%s' type '%s' FAILED: invalid member_size=%d" % (
                offset, mname, mtype_str, member_size))

        m = ida_typeinf.udt_member_t()
        m.name = mname
        m.offset = offset * 8  # bytes to bits
        m.size = member_size * 8  # bytes to bits
        m.type = tinfo
        udt.push_back(m)
        _pushed_count += 1
        _pushed_own += 1

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
            _pushed_count += 1
            _pushed_own += 1

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

    # 记录导入前的 TIL 状态：仅当 UDT 此前不存在时才是「净新建」，
    # 净新建的 UDT 必须能读回详情，否则就是空壳假成功。
    _preexisting_udt = ida_typeinf.tinfo_t()
    _was_preexisting = bool(_preexisting_udt.get_named_type(til, name))

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
                mtif = _make_vtable_method_type(ann_sig, vm_short, til, name)
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
    # 注意：set_methods() 必须推迟到下面的完整性判据与 __vftable 修正之后
    # （见下方【关键时序】）。理由：set_methods() 之后 get_udt_details() 会
    # 合法失败，两处依赖它的后处理都会静默跳过。
    # ---------------------------------------------------------------------------
    # 完整性判据（2026-09-15 清理工作 t3，见 docs/specs/2026-09-15-cleanup-handoff.md §4 t3）
    #
    # 历史缺陷：本处（原 :866-877）曾对 get_size()==-1 **无条件**降级成
    # actual_size = binary_size，并把 set_named_type 的失败结果照单收下。
    # 后果链：成员偏移/末端越界时 create_udt() 仍返回 true 但产出**不完整 UDT**
    # （get_udt_details()==false）→ 被降级掩盖 → set_named_type 静默失败留下空壳
    # → 下游 `SceneObj[256]` 取元素尺寸得 -1 → 原 :797-800 报
    # "invalid member_size" FATAL。真正的病根在此，不在下游报错点。
    #
    # 【关键时序】必须在 set_methods() **之前**判定：
    # `get_udt_details()` 对「带成员函数的 UDT」会合法失败（方法列表使 UDT 不再是
    # 纯数据聚合）。若在 set_methods() 之后判定，所有带虚表的类（本仓 ~93 个
    # vtable struct 覆盖的类）都会被误判为「空壳」——实测该误判命中 10 个结构
    # （tagNewItem/C2DSpark_tagSpark/CEffMgr/UIChatRest/SaleUI 等），而
    # SaleUI 的布局在 set_methods() 前是可读的（上一轮记录 66 members / ok）。
    #
    # 判据（两个独立维度，不靠 get_size()==-1 单点）：
    #   ① get_udt_details() 成功 + 实际落入成员数 == 期望推入成员数
    #   ② 末端口径：declared_offset + member_size <= binary_size
    #      （偏移口径会漏掉「末成员自身尺寸撑破边界」，如 SaleUI 的
    #       ml_SmeltList@104752 ends 105960 > binary_size 105952）
    # ---------------------------------------------------------------------------
    _pre_size = result_tinfo.get_size()   # set_methods() 之前的尺寸（权威）
    _size_is_dash_one = (_pre_size == 0xFFFFFFFFFFFFFFFF)

    # 【关键时序 2】set_named_type() 必须**先于** get_udt_details()：
    # 未在 TIL 中命名的 tinfo 上，get_udt_details() 对一部分 UDT 会返回 false
    # （实测：tagNewItem/C2DSpark_tagSpark/CEffMgr/UIChatRest/SaleUI 五个结构，
    #  命名前全部不可读、命名后可读——15:08 的导出证明它们各有 5/15/38/38/62 个
    #  成员、是**完整** UDT）。因此判定顺序为：
    #      create_udt → set_named_type → 完整性判据/__vftable 修正 → set_methods
    # set_named_type 无返回值，落地是否成功由下面的 _verify_named_udt 复核。
    result_tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)

    # --- 判据 ①-a：读回 UDT 详情（必须在 set_methods() 之前） ---
    _udt_probe = ida_typeinf.udt_type_data_t()
    _udt_ok = bool(result_tinfo.get_udt_details(_udt_probe))
    _returned_members = _udt_probe.size() if _udt_ok else 0

    # --- 判据 ①-b：成员数一致性（非 union） ---
    #
    # 【M3，2026-09-15 独立复核修正】原判据带 `not _was_preexisting` 门控，
    # 但 step 3a 的 fwd 声明与 vtable 结构预建**先于**导入，已把全部 struct 名建入 TIL
    # ⇒ `_was_preexisting` **恒真** ⇒ 本判据对所有非 union struct **恒为 False**
    # （实证：`grep -c "member count mismatch"` = 0；`[3] Structs: 881/881` 对成员数是同义反复）。
    # 现去掉该门控，使判据真正生效。
    #
    # 同时修正计数：`_pushed_count` 现已包含基类子对象（见上），故 `!=` 才是正确比较。
    # 先前 counter 置于基类循环之后 ⇒ 176 个带 base_class 的非 union struct 会**欠计数 1**，
    # 那正是 SaleUI(63 vs 62)、UIChatRest(39 vs 38) 的真实成因
    # ——**不是** captain 曾误称的「union 变体被 IDA 展开」（两结构 `union=no`、无同偏移键组）。
    # union 的同偏移变体确可能被 IDA 合并/重排，故 union 仍豁免本判据。
    _count_mismatch = (_udt_ok and not is_union
                       and _returned_members != _pushed_count)

    # --- 判据 ②：末端口径（按已创建 UDT 的真实布局核对，同样在 set_methods() 之前） ---
    _oversized, _culprit, _max_end, _n_oversized, _terminal_overflow = \
        _layout_end_of_members(result_tinfo, binary_size)

    # --- __vftable 类型修正：也必须在 set_methods() 之前 ---
    # build_struct_decl 造出的是 typed vtbl_ADDR *__vftable，而注解把它覆盖成 int。
    # 历史实现（原 :893-909）位于 set_methods() 之后，对带成员函数的 UDT 会因
    # get_udt_details() 失败而**静默跳过**整类 __vftable 修正 —— 移到此处一并修好。
    _post_udt = ida_typeinf.udt_type_data_t()
    _post_readable = bool(result_tinfo.get_udt_details(_post_udt))
    if _post_readable and struct_info and struct_info.get("vtables"):
        _va0 = struct_info["vtables"][0].get("addr", "")
        if _va0:
            _vtn = "vtbl_%s" % _va0[2:]
            _vtif = ida_typeinf.tinfo_t()
            if _vtif.get_named_type(til, _vtn) and _vtif.get_size() < 10000:
                _vp_tif = ida_typeinf.tinfo_t()
                _vp_tif.create_ptr(_vtif)
                if _vp_tif.is_correct() and _vp_tif.get_size() == 4:
                    _vt_fixed = False
                    for _i in range(_post_udt.size()):
                        try:
                            _um = _post_udt[_i]
                            if _um.get_name() == "__vftable":
                                _um.type = _vp_tif  # set typed vtable pointer
                                _vt_fixed = True
                                break
                        except Exception:
                            pass
                    if _vt_fixed:
                        _r2 = ida_typeinf.tinfo_t()
                        if _r2.create_udt(_post_udt, ida_typeinf.BTF_STRUCT):
                            # 重新落回；随后的 set_methods() 在 fresh 对象上执行
                            result_tinfo = _r2
                            result_tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                        else:
                            log("  [!] %s: __vftable retype create_udt failed" % name)
    elif not _post_readable:
        log("  [!] %s: get_udt_details() unreadable — __vftable not retyped" % name)

    # 越界/空壳判定完成后，才挂成员函数（挂完 get_udt_details 不再可用）。
    if len(method_udms) > 0:
        result_tinfo.set_methods(method_udms)

    actual_size = result_tinfo.get_size()
    # 注：此处 actual_size 是 set_methods() 之后的读数；带方法的 UDT 会合法地
    # 报 -1，故尺寸断言一律用 set_methods() 之前的 _pre_size（权威）。
    if _pre_size != 0xFFFFFFFFFFFFFFFF:
        actual_size = _pre_size

    if (not _udt_ok) or _count_mismatch or _n_oversized:
        if _oversized:
            _omax = max(_oversized, key=lambda t: t[2])
            _detail = ("max member end: +%d '%s' (declared offset +%d, "
                       "end %d > binary_size %d) — %d member(s) out of bounds: %s" % (
                           _omax[2], _omax[1], _omax[0], _omax[2], binary_size,
                           _n_oversized,
                           ", ".join("+%d '%s'(end %d)" % (o, n, e)
                                     for o, n, e in _oversized[:5])) +
                       (" …" if _n_oversized > 5 else ""))
        elif not _udt_ok:
            # 布局根本读不回来 → 没有任何几何观测量可报。这正是「空壳」形态。
            _detail = ("layout unreadable (get_udt_details() failed) — no geometric "
                       "bounds available; this is the empty-shell form")
        elif _terminal_overflow:
            _detail = ("terminal overflow: max member end +%d ('%s') > binary_size %d" % (
                _max_end, _culprit or '?', binary_size))
        else:
            _detail = "no member exceeds binary_size (overflow is structural, not geometric)"

        _count_detail = ("returned_members=%d vs pushed=%d (own=%d + bases=%d; expected=%d)%s" % (
            _returned_members, _pushed_count, _pushed_own, _n_bases, _expected_pushed,
            " — MISMATCH" if _count_mismatch else ""))

        _reason_codes = []
        if not _udt_ok:
            _reason_codes.append("get_udt_details()==False (incomplete UDT shell)")
        if _count_mismatch:
            _reason_codes.append("member count mismatch")
        if _n_oversized:
            _reason_codes.append("%d member(s) out of declared binary_size" % _n_oversized)

        log("[FATAL] %s: TAUDT_FIXED produced INCOMPLETE UDT." % name)
        log("        binary_size=%d, base=%s" % (binary_size, base_class or '(none)'))
        log("        member count : %s" % _count_detail)
        log("        bounds       : %s" % _detail)
        log("        reasons      : %s" % ("; ".join(_reason_codes) or "unknown"))
        log("        get_size()   : %s%s" % (
            "-1" if _size_is_dash_one else str(_pre_size),
            "   (NOTE: -1 is NOT the failure cause here — see the ordering comment above)"
            if _size_is_dash_one else ""))

        # [方案 A 2026-10-16] FATAL 路径沿用权威回退：get_udt_details==False **单因**
        # （空壳形=两级继承 UDT 读回失败族）⇒ 沿用 [i] 组 binary_size 权威回退，
        # 并**保留 last-mile 核**（_verify_named_udt——SceneObj 事故收口处不跳过）。
        if _should_authoritative_fallback(_reason_codes, binary_size):
            log("  [i] %s: get_udt_details()==False (empty-shell / two-level-inheritance "
                "readback family) — FATAL 路径沿用权威回退: using binary_size=%d as "
                "authoritative size; 保留 last-mile _verify_named_udt" % (name, binary_size))
            return _verify_named_udt(result_tinfo, name, til, binary_size=binary_size,
                                     has_methods=bool(len(method_udms) > 0))

        # 逐 struct 留痕覆盖开关（默认拒绝）。覆盖面必须显式登记，见
        # data/annotations/_incomplete_udt_overrides.json。
        _ov = _load_incomplete_udt_overrides().get(name)
        if _ov:
            log("[OVERRIDE] %s is registered as a KNOWN-INCOMPLETE struct — "
                "apply allowed for this struct ONLY." % name)
            log("           reason     : %s" % _ov.get("reason", "(not stated)"))
            log("           registered : %s" % _ov.get("registered", "(not stated)"))
            log("           tracking   : %s" % _ov.get("tracking", "(not stated)"))
            # 覆盖后仍需尽力落地，但不能掩盖：返回成功并让下游按 binary_size 处理。
            # （-1 不是失败原因，无需在此处理。）
            if _n_oversized:
                # 越界形态即使登记也不能落地（会污染下游布局计算）——保持失败。
                log("[OVERRIDE-REJECTED] %s: override does NOT cover geometry overflow "
                    "(%d member(s) out of bounds); keeping FATAL." % (name, _n_oversized))
                return (False, "TAUDT_FIXED incomplete for %s (override does not cover "
                               "geometry overflow; %s)" % (name, _detail))
        else:
            return (False, "TAUDT_FIXED incomplete for %s (%s; %s)" % (
                name, "; ".join(_reason_codes) or "unknown", _detail))

    # get_size()==-1 属**正常形态**，不是判据（见上【关键时序】注释）：
    # 仅记录诊断，不参与成败。措辞按实测区分两种成因，不要一律说成 union variant
    # （t9 独立验证 D6 指出：原先 5/5 条都自报 union=no 却写成 union-variant，失实）。
    if _size_is_dash_one:
        if is_union:
            _dash_one_kind = "union same-offset variants"
        else:
            _dash_one_kind = ("incomplete coalesced layout of union-flagged members "
                              "(struct itself is not a union)")
        log("  [i] %s: get_size()==-1 (readable layout, members=%d, union=%s, "
            "pushed=%d, oversized=0) — attributed to %s; using binary_size=%d "
            "as authoritative size" % (
                name, _returned_members, "yes" if is_union else "no",
                _pushed_count, _dash_one_kind, binary_size))
        actual_size = binary_size

    # When created without base members (_base_offset==0), actual_size may
    # be smaller than binary_size (base class portions are missing). Accept it.
    if is_flexible:
        _size_check = actual_size  # flexible structs: accept whatever IDA computes
    else:
        _size_check = binary_size
    if actual_size > _size_check:
        return (False, "size mismatch: expected <=%d, got %d" % (
            binary_size, actual_size))

    # set_named_type 已在上面（判定之前）调用；此处只做落地复核。
    # 这是空壳 last-mile：旧代码在此静默放行，正是 SceneObj 事故的收口处。
    _land_ok, _land_err = _verify_named_udt(
        result_tinfo, name, til, binary_size=binary_size,
        has_methods=bool(len(method_udms) > 0))
    if not _land_ok:
        return (False, _land_err)
    
    return (True, None)


def load_annotations():
    """从拆分目录加载标注数据。"""
    if not os.path.isdir(ANNOTATIONS_DIR):
        return None

    log("[*] Loading annotations from: %s" % ANNOTATIONS_DIR)
    with open(os.path.join(ANNOTATIONS_DIR, "functions.json"), "r", encoding="utf-8") as f:
        functions = json.load(f)
    # Tag functions.json entries that have ClassName:: prefix with their class
    # (legacy entries not yet moved to struct JSONs)
    for _addr, _info in functions.items():
        _n = _info.get("name", "")
        if "::" in _n and "class" not in _info:
            _info["class"] = _n.split("::", 1)[0]
            _info["name"] = _n.split("::", 1)[1]
    with open(os.path.join(ANNOTATIONS_DIR, "globals.json"), "r", encoding="utf-8") as f:
        globals_data = json.load(f)
    structs = {}
    # [T5-F5]（2026-10-12 T4 复核）归属可靠性告警——**只报不改行为**：
    #   ①双认领无 owner：同址 ≥2 个来源（functions.json/各 struct methods）认领且无人声明
    #     owner ⇒ 静默覆盖（归属债，升级为 attribution audit 输入）
    #   ②多 struct 争 owner：同址 ≥2 个 struct 声明 owner==sname ⇒ 静默 last-wins（需人工裁定）
    _claims = {addr: ["functions.json"] for addr in functions}
    _owner_claims = {}
    for fname, sdata in _strict_struct_entries(os.path.join(ANNOTATIONS_DIR, "structs")):
        fname = os.path.basename(fname)
        sname = sdata.pop("name", fname.replace(".json", ""))
        structs[sname] = sdata
        # Merge struct methods into functions dict (class methods not in functions.json)
        # Class name derived from file name; name field stores short method name only.
        for addr, minfo in sdata.get("methods", {}).items():
            _claims.setdefault(addr, []).append(sname)
            if minfo.get("owner") == sname:
                _owner_claims.setdefault(addr, []).append(sname)
            if addr not in functions or minfo.get("owner") == sname:
                # Strip any lingering ClassName:: prefix (safety for old-format entries)
                _raw = minfo.get("name", "")
                if "::" in _raw:
                    minfo["name"] = _raw.split("::", 1)[1]
                # Tag with owning class for mangling / signature resolution
                minfo["class"] = sname
                functions[addr] = minfo
        # Also merge nested type methods (e.g. NODE::FindInOpen)
        # Use nested type as class field (ClassName::NestedType)
        for _nt_name, _nt_info in sdata.get("nested_types", {}).items():
            _nt_full = "%s::%s" % (sname, _nt_name)
            for _addr, _minfo in _nt_info.get("methods", {}).items():
                if _addr not in functions:
                    _mn = _minfo.get("name", "")
                    if _mn and "::" in _mn:
                        _mn = _mn.split("::", 1)[1]  # strip prefix from legacy format
                    _minfo["name"] = _mn
                    _minfo["class"] = _nt_full
                    functions[_addr] = _minfo
    # [T5-F5] 归属告警输出（不改行为，只报）
    _dual_no_owner = sorted(a for a, srcs in _claims.items()
                           if len(srcs) > 1 and a not in _owner_claims)
    if _dual_no_owner:
        log("[attribution][WARN] 双认领且无 owner：%d 条（静默覆盖=归属债）例：%s"
            % (len(_dual_no_owner), ", ".join(_dual_no_owner[:5])))
    for _a in sorted(_owner_claims):
        if len(_owner_claims[_a]) > 1:
            log("[attribution][WARN] 多 struct 争 owner %s：%s（当前 last-wins 取后者，需人工裁定）"
                % (_a, " vs ".join(_owner_claims[_a])))
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


def _split_param_list(text):
    """按顶层逗号切分参数表（不切嵌套括号/尖括号内的逗号）。"""
    out, depth, cur = [], 0, ''
    for ch in text:
        if ch in '(<[':
            depth += 1
        elif ch in ')>]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur)
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return [p.strip() for p in out if p.strip()]


def _slot_param_count(t):
    """槽类型里"显式写出的参数个数"；判断不了返回 None。

    函数指针类型（含 `*`）的参数表在**最后一个**括号组；
    IDA 给导入槽打印的裸函数类型（如 `void __thiscall(Class *__hidden this)`）
    参数表在第一个括号组。
    """
    groups = re.findall(r'\(([^()]*)\)', t or '')
    if not groups:
        return None
    inner = (groups[-1] if '*' in (t or '') else groups[0]).strip()
    if not inner or inner == 'void':
        return 0
    return len(_split_param_list(inner))


def _split_demangled_member(dem):
    """把 IDA 的长解算串拆成 (ret, qual, params)；拆不开返回 None。

    IDA 的长形态会带 `public: virtual __thiscall` 前缀，返回类型里又可能有空格
    （`unsigned char *`），因此不能用一个正则一把梭：
      1. 去掉访问修饰/`virtual` 前缀；
      2. 参数表取**末尾那对括号**（含嵌套括号）之前的部分；
      3. 限定名取"最后一个含 `::` 的 token"（`gbVec3D::operator+=` 也能匹配）。
    """
    if not dem:
        return None
    s = re.sub(r'^(?:public|protected|private):\s*', '', dem.strip())
    s = re.sub(r'^virtual\s+', '', s)
    depth, end = 0, -1
    for i in range(len(s) - 1, -1, -1):
        if s[i] == ')':
            if depth == 0:
                end = i
            depth += 1
        elif s[i] == '(':
            depth -= 1
            if depth == 0 and end != -1:
                start = i
                head, params = s[:start].strip(), s[start + 1:end].strip()
                m = re.search(r'([A-Za-z_]\w*(?:::\w+)*::[^\s(]+)\s*$', head)
                if not m:
                    return None
                ret = head[:m.start()].strip()
                ret = re.sub(r'__(?:thiscall|cdecl|stdcall|fastcall)\s*$', '', ret).strip()
                return (ret or 'void', m.group(1), params)
    return None


def _slot_param_text(t):
    """槽类型里"显式写出的参数表文本"（与 `_slot_param_count` 同一取法）。"""
    groups = re.findall(r'\(([^()]*)\)', t or '')
    if not groups:
        return ''
    return (groups[-1] if '*' in (t or '') else groups[0]).strip()


# ============================================================
# 任务 3（2026-10-09）：VC6 修饰名 → 形参类型（纯函数，无 IDA 依赖）
#
# 证据等级 = **A 级**：修饰名直接编码形参类型（`W4gbAxis` ⇒ enum gbAxis、
# `PAUgbVec3D@@` ⇒ struct gbVec3D *），见 data/gbengine_registry.jsonl:911-913/1044。
# 解析规则对 registry 全量 3742 行做过机械校验（形参个数 vs 解码形参个数）；
# 校验数字与残余例外见 .superpowers/sdd/2026-10-09-restore-10-green-units/task-3-report.md。
#
#   name part = `?名@类@@`（首 `@@` 收尾）；成员前缀 3 字符（访问+cv+约定，
#   如 QAE/QBE/UAE/AAE），静态/自由函数 2 字符（SA/YA/YG/CA）；
#   ctor/dtor 无返回类型，用 `@` 占位；返回类型前可有 `?A` 修饰；
#   空形参表 = `XZ`；非空 = <type>+ `@Z`；变参 = <type>+ `ZZ`；
#   UDT 名 = (字面段 `@` | 反引用数字)* `@`。
# 反引用（0-9）与指向函数（P6…）**不解析**，占位 `?` 占一格 —— 宁可不注入，
# 也不允许写错形参（fail-safe）。
# ============================================================

_VC6_TYPE_DEC = {
    'X': 'void', 'C': 'signed char', 'D': 'char', 'E': 'unsigned char',
    'F': 'short', 'G': 'unsigned short', 'H': 'int', 'I': 'unsigned int',
    'J': 'long', 'K': 'unsigned long', 'M': 'float', 'N': 'double',
}
_VC6_TYPE_DEC2 = {
    '_N': 'bool', '_W': 'wchar_t', '_J': '__int64', '_K': 'unsigned __int64',
}
_VC6_CV_DEC = {'A': '', 'B': 'const ', 'C': 'volatile ', 'D': 'const volatile '}
_VC6_UDT_TAG = {'U': 'struct ', 'V': 'class ', 'T': 'union '}
_VC6_ENUM_RE = re.compile(r'^enum [A-Za-z_]\w*$')
# 槽里 IDA 打印的整型占位（= 无类型信息的 4 字节）
_SLOT_INT_PLACEHOLDERS = (
    'int', '_DWORD', '_UNKNOWN', '_WORD', '_BYTE', '_QWORD',
    'long', 'unsigned int', 'unsigned long',
)


class _MangledParseFail(Exception):
    pass


def _mangled_name(s, i):
    """UDT 名 := (字面段 '@' | 反引用数字)* '@'。反引用不解析，占位 '?'。

    反引用数字是**裸**的（不带段尾 '@'），随后的 '@' 才是整名收尾：
    `ECPKMode@@` = 字面段 + 收尾；`LIGHT_TYPE@1@` = 字面段 + 反引用 1 + 收尾。
    """
    items = []
    while True:
        if i >= len(s):
            raise _MangledParseFail('name eof')
        if s[i] == '@':
            return '::'.join(items), i + 1
        if s[i].isdigit():
            nxt = s[i + 1:i + 2]
            if nxt in ('', '@') or nxt.isdigit():
                items.append('?')      # 名字反引用（如 ??4gbVec3D@@…ABU0@@ 的 0）
                i += 1
                continue
        j = s.find('@', i)
        if j < 0:
            raise _MangledParseFail('unterminated name')
        seg = s[i:j]
        if not seg:
            raise _MangledParseFail('empty name segment')
        items.append(seg)
        i = j + 1


def _mangled_type(s, i):
    """一个类型 → (C 声明串, 新 i)。反引用/指向函数返回 '?'（只占位，不注入）。"""
    if i >= len(s):
        raise _MangledParseFail('type eof')
    ch = s[i]
    if ch.isdigit():
        return '?', i + 1               # 类型反引用：回指不解析（fail-safe）
    if s.startswith('P6', i):
        # 指向函数：P6 + 调用约定(1) + 返回类型 + 形参表
        _ret, j = _mangled_type(s, i + 3)
        _args, j = _mangled_args(s, j)
        return '?', j
    if ch in ('P', 'A'):
        cv = _VC6_CV_DEC.get(s[i + 1:i + 2])
        if cv is None:
            raise _MangledParseFail('bad cv %r' % s[i + 1:i + 2])
        base, j = _mangled_type(s, i + 2)
        if base == '?':
            return '?', j
        return cv + base + (' *' if ch == 'P' else ' &'), j
    if s.startswith('?A', i):
        return _mangled_type(s, i + 2)  # 返回类型修饰（enum/UDT 返回）
    if s.startswith('W4', i):
        name, j = _mangled_name(s, i + 2)
        return 'enum ' + name, j
    if ch in _VC6_UDT_TAG:
        name, j = _mangled_name(s, i + 1)
        return _VC6_UDT_TAG[ch] + name, j
    if s[i:i + 2] in _VC6_TYPE_DEC2:
        return _VC6_TYPE_DEC2[s[i:i + 2]], i + 2
    if ch in _VC6_TYPE_DEC:
        return _VC6_TYPE_DEC[ch], i + 1
    raise _MangledParseFail('bad type %r' % ch)


def _mangled_args(s, i):
    """形参表 := 'XZ'（空） | <type>+ '@Z' | <type>+ 'ZZ'（变参）。"""
    if s.startswith('XZ', i):
        return [], i + 2
    out = []
    while True:
        if s.startswith('@Z', i):
            return out, i + 2
        if s.startswith('ZZ', i):
            return out, i + 2
        t, i = _mangled_type(s, i)
        out.append(t)


def _mangled_param_types(mangled):
    """VC6 修饰名 → 逐形参 C 声明类型列表（不含 this）；解析不出返回 None。

    A 级证据来源：修饰名本身（`W4<Enum>` 直接编码 enum 形参）。IDA 自造的
    `::` 名、模板名、未支持编码一律返回 None —— 调用方保持原行为，不猜。
    """
    try:
        i = mangled.find('@@')
        if i < 0:
            return None
        suf = mangled[i + 2:]
        if not suf:
            return None
        j = 2 if suf[0] in 'SYC' else 3   # 静态/自由函数 2 字符（S/Y/C + 约定），成员 3 字符
        if j > len(suf):
            return None
        if suf[j] == '@':
            j += 1                       # ctor/dtor 无返回类型，'@' 占位
        else:
            _ret, j = _mangled_type(suf, j)
        args, j = _mangled_args(suf, j)
        if suf[j:] and not re.match(r'^_\d+$', suf[j:]):
            return None                  # 模板固定实参尾巴（`_0`）之外的残留
        return args
    except (_MangledParseFail, IndexError):
        return None


def _enum_upgrade_needed(stored_params, mangled_params):
    """槽形参表里该是 enum 的位置现在是整型占位 ⇒ 需要升级改写（int→enum）。

    只在**位置对齐**（长度相等）且 mangled 解出具体 enum 名时判定；解析失败、
    名字反引用、长度漂移一律不动（fail-safe，杜绝写错形参）。
    """
    if not mangled_params or len(stored_params) != len(mangled_params):
        return False
    for _sp, _mp in zip(stored_params, mangled_params):
        if _VC6_ENUM_RE.match(_mp) and _sp.strip() in _SLOT_INT_PLACEHOLDERS:
            return True
    return False


def _enum_merge_plan(existing, declared):
    """enums.json 已声明值 vs IDB enum 现有成员 → 逐项处置表（绝不整体短路）。

    返回 [(action, name, value)]（declared 顺序；值统一 int）：
      'add'      名字空缺且值空缺 ⇒ 可写入
      'keep'     名值一致 ⇒ 已满足（旧代码正是在这里整体 `continue` 丢声明）
      'alias'    名字空缺但值已被别的成员占用 ⇒ IDA 不收同值异名，显式记录
      'conflict' 名字已被占用但值不同 ⇒ 不覆盖既有信息，显式记录
    每个已声明 (name, value) **必**出现在表里 ⇒ 不存在静默丢失。
    """
    out = []
    existing = existing or {}
    taken = {}
    for _n, _v in existing.items():
        taken[int(_v)] = _n
    for name, raw in (declared or {}).items():
        val = int(raw, 0) if isinstance(raw, str) else int(raw)
        if name in existing:
            out.append(('keep' if int(existing[name]) == val else 'conflict', name, val))
        elif val in taken:
            out.append(('alias', name, val))
        else:
            out.append(('add', name, val))
            taken[val] = name
    return out


def _enum_merge_apply(plan, add_member):
    """执行处置表：'add' 逐个落 add_member(name, value)；其余只出显式记录。

    返回 (added, notes)。notes 非空即"没有静默"——调用方必须把 notes 打进日志。
    """
    added, notes = 0, []
    for action, name, value in plan:
        if action == 'add':
            if add_member(name, value):
                added += 1
            else:
                notes.append('add-failed %s=%d' % (name, value))
        else:
            notes.append('%s %s=%d' % (action, name, value))
    return added, notes


def _idb_enum_members(eid):
    """IDB enum 现有成员 {name: value}；读不到返回 {}。

    IDA 9.1 实测：`idc.get_enum_member_name` 只收 const_id（旧签名 id/value/serial
    会 TypeError），故主路径走 `ida_typeinf.enum_type_data_t` 直读。
    fail-safe：枚举失败时处置表会把已声明项判成 'add'，而 add_enum_member 对
    名字/值冲突会失败 ⇒ 记 'add-failed' 显式留痕，**不会**覆盖既有成员。
    """
    existing = {}
    try:
        tif = ida_typeinf.tinfo_t()
        if tif.get_type_by_tid(eid):
            ei = ida_typeinf.enum_type_data_t()
            if tif.get_enum_details(ei):
                for _k in range(len(ei)):
                    _edm = ei[_k]
                    existing[str(_edm.name)] = int(_edm.value)
        if existing:
            return existing
    except Exception:
        existing = {}
    try:
        val = idc.get_first_enum_member(eid)
        seen = 0
        while val not in (None, -1) and seen < 4096:
            cid = idc.get_enum_member(eid, val, 0, -1)
            if cid not in (None, -1):
                nm = idc.get_enum_member_name(cid)
                if nm:
                    existing[str(nm)] = int(val)
            val = idc.get_next_enum_member(eid, val)
            seen += 1
    except Exception:
        pass
    return existing


def _fix_gbengine_import_slots():
    """F73（第 132 轮）：按修饰名纠正 gbengine 导入槽上的**退化原型**。

    实测（A 级）：`?Read@gbVFileSystem@@QAEXPAXIPAVgbVFile@@@Z` 的 IAT 槽类型是
    `void __thiscall(gbVFileSystem *__hidden this)` —— **零栈参**。Hex-Rays 对
    `call ds:<slot>` 优先采用槽上的类型，于是该函数 33 处调用点的三个实参**全部丢失**：
        gbVFileSystem::Read(g_pVFileSys);          # 生成 C++ 报 C2660，语义也丢了
    对照证据：同类 `Seek`/`TellPos`/`Write`/`OpenFile` 的槽类型为空 ⇒ Hex-Rays 回退到
    修饰名给出的签名 ⇒ 参数完整；而且 IDA 的反汇编注释里本来就写着
    `gbVFileSystem::Read(void *,uint,gbVFile *)`，即槽类型才是那个错的东西。

    签名来源 = **修饰名本身**（VC6 mangling 含完整参数表 + 调用约定），无任何猜测；
    只改"显式参数个数少于修饰名"的成员槽，其余一律不碰（幂等、可重跑）。
    """
    import ida_nalt
    til = ida_typeinf.get_idati()
    fixed, seen, failed = 0, 0, 0
    n_all, n_member, n_dem, n_regex = 0, 0, 0, 0
    samples = []

    def _cb(ea, name, ordinal):
        nonlocal fixed, seen, failed, n_all, n_member, n_dem, n_regex
        n_all += 1
        # 注意：这里拿到的是**修饰名**（`?Read@gbVFileSystem@@QAEX...@Z`），
        # 它本身不含括号；括号只出现在解算后的 C++ 串里。
        if not name or '@@' not in name:
            return True
        grp = name.split('@@', 1)[1][:3]
        # 只处理非静态成员（Q/U/I + ... + E=__thiscall）
        if len(grp) < 3 or grp[0] not in 'QUI' or grp[2] != 'E':
            return True
        n_member += 1
        try:
            dem = idc.demangle_name(name, idc.get_inf_attr(idc.INF_LONG_DN)) or ''
        except Exception as _e_dem:
            if len(samples) < 3:
                samples.append('demangle raised for %s: %s' % (name, _e_dem))
            return True
        if not dem:
            if len(samples) < 3:
                samples.append('demangle empty for %s' % name)
            return True
        n_dem += 1
        parsed = _split_demangled_member(dem)
        if not parsed:
            if len(samples) < 3:
                samples.append('split miss: %r' % dem)
            return True
        n_regex += 1
        ret, qual, params = parsed
        cls = qual.rsplit('::', 1)[0]
        decl_params = _split_param_list(params)
        if len(decl_params) == 1 and decl_params[0] == 'void':
            decl_params = []
        cur = idc.get_type(ea) or ''
        n_cur = _slot_param_count(cur)
        if n_cur is None:
            # F73b（2026-09-25 拆解实证）：空槽**不再跳过**。实证链：fresh init 的槽
            # 全空 ⇒ export/Hex-Rays 用调用点推断的**退化原型回写**（Read 被写成
            # `void __thiscall(__hidden this)`、RenderGeomQuad 被写成 __stdcall 丢
            # this）⇒ Hex-Rays 下一轮导出采用坏型丢参；修复要拖到**下一轮 apply**，
            # plain init 永远一次不成型。修饰名含完整签名（零猜测），空槽直接写全。
            decl = '%s __thiscall __sigfix(%s);' % (
                ret, ', '.join([cls + ' *'] + decl_params))
            ftif = ida_typeinf.tinfo_t()
            if not ida_typeinf.parse_decl(ftif, til, decl, ida_typeinf.PT_SIL):
                failed += 1
                log("  [!] import slot sig parse failed: %s -> %s" % (name, decl))
                return True
            ptr = ida_typeinf.tinfo_t()
            ptr.create_ptr(ftif)
            if ida_nalt.set_tinfo(ea, ptr):
                fixed += 1
                log("  [gb] empty slot sig set @%08X %s" % (ea, name))
            else:
                failed += 1
                log("  [!] import slot set_tinfo failed (empty): %s" % name)
            return True
        # 裸函数类型里 IDA 把 this 打印成 `__hidden this` ⇒ 参数个数要减 1
        n_stack = n_cur - (1 if '__hidden this' in cur else 0)
        # 另一种退化：参数个数碰巧够，但**调用约定写错**（如
        # `?RenderGeomQuadViaStrip@gbDynVertBuf@@` 的槽被写成 `__stdcall`，
        #  this 指针从参数表里消失）。修饰名 `@@QAE` 已确定是 __thiscall 成员。
        conv_wrong = bool(cur) and '__thiscall' not in cur
        # F77（第 137 轮）：第三种退化——**参数个数够，但形参类型是占位符**。
        # 实例：`??4gbVec3D@@QAEXABU0@@Z`（`gbVec3D::operator=(gbVec3D const &)`）的槽是
        # `int __thiscall(_DWORD, _DWORD)`。Hex-Rays 因此认为形参是个整数/指针，
        # 于是把调用点写成 `gbVec3D::operator=(&v21.Direction, ViewTarget)`（直接传 `float *`），
        # 而生成头里的声明是 `operator=(const gbVec3D &)` ⇒ 一整族 C2664（实测 48 条）。
        # 判据仍是修饰名：槽里该位置是 `_DWORD`/`_UNKNOWN`，而修饰名在该位置是**指针或引用**。
        _stored_params = [p for p in _split_param_list(
            (_slot_param_text(cur) or '').replace('__hidden this', '')) if p.strip()]
        # 槽里显式列出 this 时参数个数会比修饰名多 1（两种排版都见过：裸函数类型
        # `int __thiscall(_DWORD, _DWORD)` 与函数指针类型 `void (__thiscall *)(Cls *, T&)`）
        if len(_stored_params) == len(decl_params) + 1:
            _stored_params = _stored_params[1:]
        elif len(_stored_params) != len(decl_params):
            _stored_params = []
        ph_wrong = False
        for _i, _p in enumerate(decl_params):
            if _i >= len(_stored_params):
                break
            _sp = _stored_params[_i].strip()
            if _sp in ('_DWORD', '_UNKNOWN', '_QWORD', 'int') and ('*' in _p or '&' in _p):
                ph_wrong = True
                break
        # 任务 3（2026-10-09）：第四种退化——**参数个数够、约定对、非指针占位，
        # 但 enum 形参被存成整型占位**，于是这里 early return、int 永远升不成 enum。
        # 实测：`?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@M@Z` 的槽是
        # `void __thiscall(gbMatrix4 *, int, float)` ⇒ Hex-Rays 不补 cast ⇒ 生成码
        # `SetAxisAngle(2, …)` 裸整型 ⇒ Object3D.cpp L26/L31/L89 三条 C2664。
        # 判据仍是修饰名（A 级）：该位置是 `W4<Enum>` 而槽里是整型占位。
        _mangled_params = _mangled_param_types(name) or []
        enum_wrong = _enum_upgrade_needed(_stored_params, _mangled_params)
        seen += 1
        if n_stack >= len(decl_params) and not conv_wrong and not ph_wrong and not enum_wrong:
            return True
        decl = '%s __thiscall __sigfix(%s);' % (
            ret, ', '.join([cls + ' *'] + decl_params))
        ftif = ida_typeinf.tinfo_t()
        if not ida_typeinf.parse_decl(ftif, til, decl, ida_typeinf.PT_SIL):
            failed += 1
            log("  [!] import slot sig parse failed: %s -> %s" % (name, decl))
            return True
        ptr = ida_typeinf.tinfo_t()
        ptr.create_ptr(ftif)
        if ida_nalt.set_tinfo(ea, ptr):
            fixed += 1
            log("  [gb] slot sig fixed @%08X %s" % (ea, name))
            log("       %s  ->  %s" % (cur, idc.get_type(ea)))
        else:
            failed += 1
            log("  [!] import slot set_tinfo failed: %s" % name)
        return True

    for i in range(ida_nalt.get_import_module_qty()):
        mod = ida_nalt.get_import_module_name(i)
        if mod and 'gbengine' in mod.lower():
            ida_nalt.enum_import_names(i, _cb)
    # 计数全打出来：否则"0 个"无法区分"没有候选"和"过滤条件写错"
    log("[gb] import slots: names=%d member=%d demangled=%d parsed=%d typed=%d "
        "-> corrected=%d failed=%d"
        % (n_all, n_member, n_dem, n_regex, seen, fixed, failed))
    for s in samples:
        log("     sample-reject: %s" % s)
    return fixed


# gbengine IAT 槽数函数类型白名单（模块级：测试直接对它断言）。
# 每条值 = 写到 IAT 槽上的函数指针声明（`ret __thiscall(this, ...)`）。
# 任务 3（2026-10-09）：此前全表**零 enum 形参（零 `W4` 修饰）**且无
# `SetAxisAngle`/`SetOpenMode` 条目 ⇒ 槽形参退化 int ⇒ Hex-Rays 不补 cast ⇒
# C2664（Object3D.cpp L26/L31/L89；SoundMgr.cpp L21/L23）。新增四条按修饰名
# （A 级，data/gbengine_registry.jsonl:911-913/1044）注入 enum 形参。
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
    # 缺参簇补齐（签名权威 = include/gbengine_api.h；无类型导入会让 Hex-Rays
    # 丢参/丢解引用，如 C3DSpark RenderGeomQuad 3/4 参、CCBStageShadow operator= float*）
    "?RenderGeomQuad@gbDynVertBuf@@QAEXPAUgbGeomQuad@@HPAVgbRenderEffect@@PAUgbTextureArray@@@Z":
        "void __thiscall(gbDynVertBuf *, gbGeomQuad *, int, gbRenderEffect *, gbTextureArray *);",
    "??4gbMatrix4@@QAEXABU0@@Z":
        "void __thiscall(gbMatrix4 *, const gbMatrix4 &);",
    "?LoadFromFile@gbGeomNode@@QAEHPBD0P6AXHH@Z@Z":
        "int __thiscall(gbGeomNode *, const char *, const char *, void (__cdecl *)(int, int));",
    "?GetTotalOBBox@gbGeomNode@@QAEPAUgbOBBox@@PAU2@@Z":
        "gbOBBox *__thiscall(gbGeomNode *, gbOBBox *);",
    "?Read@gbVFileSystem@@QAEXPAXIPAVgbVFile@@@Z":
        "void __thiscall(gbVFileSystem *, void *, unsigned int, gbVFile *);",
    # ── 任务 3（2026-10-09）enum 形参注入（A 级：`W4<Enum>` 直接编码 enum 形参）──
    "?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@M@Z":
        "void __thiscall(gbMatrix4 *, enum gbAxis, float);",
    "?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@MM@Z":
        "void __thiscall(gbMatrix4 *, enum gbAxis, float, float);",
    "?SetAxisAngle@gbMatrix4@@QAEXPAUgbVec3D@@M@Z":
        "void __thiscall(gbMatrix4 *, gbVec3D *, float);",
    "?SetOpenMode@CPK@@QAEXW4ECPKMode@@@Z":
        "void __thiscall(CPK *, enum ECPKMode);",
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
    # 签名表 = 模块级 `_GB_IMPORT_SIGS`（任务 3 起含 enum 形参；测试直接对它断言）。
    import ida_nalt
    gb_sig_ok = 0
    gb_sig_try = 0
    nimps = ida_nalt.get_import_module_qty()
    for i in range(nimps):
        mod = ida_nalt.get_import_module_name(i)
        if not mod or 'gbengine' not in mod.lower():
            continue
        def _set_import_type(ea, name, ordinal):
            nonlocal gb_sig_ok, gb_sig_try
            if name and name in _GB_IMPORT_SIGS:
                gb_sig_try += 1
                # IAT 槽是**数据地址**（非函数）：SetType 写裸函数类型会被拒。
                # 必须写"函数指针类型"到槽上（与 F73 同款）——Hex-Rays 反编译
                # `call ds:<slot>` 时从槽读指向类型。实证（2026-09-25 拆解）：
                # 裸 SetType 21 条只成 1 条；槽空着时 export 会用调用点推断的
                # 退化原型回写（RenderGeomQuad 被写成 stdcall ⇒ 丢 this ⇒ 少参）。
                sig = _GB_IMPORT_SIGS[name]
                decl = sig.rstrip(';') + ';'
                ftif = ida_typeinf.tinfo_t()
                if not ida_typeinf.parse_decl(ftif, til, decl, ida_typeinf.PT_SIL):
                    log("  [!] gb import sig parse failed: %s -> %s" % (name, decl))
                    return True
                ptr = ida_typeinf.tinfo_t()
                ptr.create_ptr(ftif)
                if ida_nalt.set_tinfo(ea, ptr):
                    gb_sig_ok += 1
                else:
                    log("  [!] gb import slot set_tinfo failed: %s" % name)
            return True
        ida_nalt.enum_import_names(i, _set_import_type)
    log("[gb] import sig types set: %d/%d" % (gb_sig_ok, gb_sig_try))


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


def _apply_func_type_parse(addr, decl, til):
    """Primary function-type application: parse_decl + apply_tinfo (TINFO_DEFINITE).

    Verified path (2026-08-29): Hex-Rays adopts the type as definite. idc.SetType
    silently fails on `ret __thiscall name(Cls *__hidden this, ...)` forms, which
    left Hex-Rays running on its own inference — the root cause of decomp-signature
    divergence from annotations (~231 member/free conflicts in the export audit).
    The `__hidden this` spelling is IDA's official representation for the C++
    this argument (docs.hex-rays.com: Set item type / C++ type details).
    """
    try:
        tif = ida_typeinf.tinfo_t()
        # parse_decl requires a complete declaration — trailing semicolon needed
        if not decl.rstrip().endswith(';'):
            decl = decl + ';'
        if not ida_typeinf.parse_decl(tif, til, decl, ida_typeinf.PT_SIL):
            return False
        return bool(ida_typeinf.apply_tinfo(addr, tif, ida_typeinf.TINFO_DEFINITE))
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
    # 键必须是地址。畸形键（非地址字符串）**不得**让整个 apply 崩溃——
    # 历史事故（源自 **2026-09-01**，非本轮）：`int(_k, 16)` 抛 ValueError 使 apply 整体
    # 失败并写出 `_logs/apply_exception.txt`，内容 "invalid literal for int() with base 16:
    # 'CCBUI::CountAttackSequences'"。该文件的**原始 mtime 实测为 2026-09-01 17:47:04**
    # （419 B）；2026-09-15 19:37:42 复现时被新异常覆盖——captain 曾误把日期读成
    # "2026-09-15 17:47"，由独立复核者纠正，特此留痕。
    # 本守卫已于 2026-09-15 用**注入该键**的方式实测：apply 不崩、逐条 skip 并汇总上报，
    # 且 `[3] Structs: 881/881`。
    # 与 t8 的 `data.py:218`（一条坏条目丢全部 thunk 映射）、
    # `compare_pal3.py` census 守卫同类：**逐条跳过 + 计数上报，不静默、不整体崩**。
    _bad_addr_keys = []
    for _k in data.get("functions", {}):
        try:
            _ann_addrs.add(int(_k, 16))
        except (ValueError, TypeError):
            _bad_addr_keys.append(("functions.json", _k))
    _skip_path = os.path.join(ANNOTATIONS_DIR, "skip_functions.json")
    if os.path.exists(_skip_path):
        for _k in json.load(open(_skip_path, encoding="utf-8")):
            try:
                _ann_addrs.add(int(_k, 16))
            except (ValueError, TypeError):
                _bad_addr_keys.append(("skip_functions.json", _k))
    if _bad_addr_keys:
        # 响亮但非致命：这些键会被忽略，可能让"stale function 清理"漏掉真实地址。
        log("[WARN] %d malformed address key(s) ignored (not valid hex addresses):" %
            len(_bad_addr_keys))
        for _src, _k in _bad_addr_keys[:20]:
            log("       %s: %r" % (_src, _k))
        if len(_bad_addr_keys) > 20:
            log("       ... and %d more" % (len(_bad_addr_keys) - 20))
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
            # class field is set by _load_annotations for ALL class methods.
            if 'class' in info:
                _cls = info['class']
                _method = name
                _sig = info.get('signature', '')
                _mangled = _mangle_vc6(_cls, _method, _sig)
                if _mangled and ida_name.set_name(addr, _mangled, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                    renamed += 1
                else:
                    rename_fail.append((addr_str, cur, name))
            else:
                if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                    renamed += 1

    # Also name skip_functions (not decompiled, but callers need their names)
    skip_path = os.path.join(ANNOTATIONS_DIR, "skip_functions.json")
    skip_named = 0
    _skip_bad_keys = []
    skip_funcs = {}
    if os.path.exists(skip_path):
        with open(skip_path, "r", encoding="utf-8") as f:
            skip_funcs = json.load(f)
        for addr_str, info in skip_funcs.items():
            name = info.get("name", "")
            # 畸形键不得让整个 apply 崩溃（同 1635/1643 处的守卫）。
            # 实测 2026-09-15 19:37：注入一个非地址键
            # 'CCBUI::CountAttackSequences' 后本行 `int(addr_str, 16)` 抛 ValueError，
            # 使 apply 整体失败（cli.py 正确报 exit 1）。逐条跳过 + 汇总上报。
            try:
                addr = int(addr_str, 16)
            except (ValueError, TypeError):
                _skip_bad_keys.append(addr_str)
                continue
            if name and not name.startswith("sub_"):
                if not _ida_funcs.get_func(addr):
                    _ida_funcs.add_func(addr)
                if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                    skip_named += 1

    if _skip_bad_keys:
        log("[WARN] skip_functions.json: %d malformed key(s) ignored: %s" % (
            len(_skip_bad_keys), ", ".join(repr(k) for k in _skip_bad_keys[:10])))

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
            mtype = m["type"]
            if isinstance(mtype, dict):
                # inline union/struct: recursively extract type references
                def _extract_types(tdef, out):
                    if isinstance(tdef, str):
                        base = _re_fwd.sub(r'\[.*\]', '', tdef).replace("*", "").strip()
                        if base and base not in _primitives and '::' not in base:
                            out.add(base)
                    elif isinstance(tdef, dict):
                        for val in tdef.values():
                            if isinstance(val, list):
                                for item in val:
                                    if isinstance(item, dict):
                                        _extract_types(item.get("type"), out)
                _extract_types(mtype, fwd_names)
                continue
            mtype = mtype.replace("class ", "").replace("struct ", "")
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
    #
    # 任务 3（2026-10-09）修复第三个失效点：旧代码
    #   `if idc.get_enum(ename) != -1: e_ok += 1; continue`
    # 对**已存在 enum 整体短路**，把 enums.json 的已声明值静默丢弃。注释写
    # "Already exists from PDB import" 名实不符——实际来源是 include/gbengine/*.h
    # 的 parse_decls（任务 4 §1 实证：gbAxis 早在 TIL，成员是 GB_AXIS_X/Y/Z）。
    # 新语义：逐项处置（add/keep/alias/conflict），每个已声明 (name,value) 都
    # 显式记录，绝不静默丢；不覆盖任何既有信息（conflict 只记录不改）。
    enums = data.get("enums", {})
    e_ok = 0
    e_merged = 0
    enum_notes = []
    for ename, einfo in enums.items():
        values = einfo.get("values", {})
        if not values:
            continue
        eid = idc.get_enum(ename)
        if eid == -1:
            eid = idc.add_enum(-1, ename, 1)
            if eid != -1:
                for k, v in values.items():
                    val = int(v, 0) if isinstance(v, str) else v
                    idc.add_enum_member(eid, k, val)
                e_ok += 1
            continue
        if idc.get_enum_name(eid) is None:
            # IDA 9.1 实测：`idc.get_enum` 对**不存在**的 enum 返回 BADADDR（≠ -1）
            # ⇒ 旧代码 `!= -1` 把"不存在"也当"已存在"整体短路 —— 这才是 3b 创建
            # 路径从未生效的真根因（61 个 enums.json enum 从未进 IDB，export 的
            # `_enums` 只有 13 个可证）。本轮**不**启用创建路径（61 个 PDB 族
            # enum 进 IDB 会触发大面积 decomp cast，生成码侧声明可见性未经验证，
            # 属任务 3 范围外）；只显式记录，不再假装 merge。
            enum_notes.append('%s: not-an-idb-enum (get_enum=BADADDR; '
                              'create path out of scope)' % ename)
            continue
        existing = _idb_enum_members(eid)
        plan = _enum_merge_plan(existing, values)

        def _add_member(_n, _v, _eid=eid):
            # IDA 9.1 的 add_enum_member 对重复名/值**抛 ValueError**（不是返回
            # 错误码）⇒ 必须吞掉转 False，让处置表记 'add-failed' 而不是崩 apply。
            try:
                return idc.add_enum_member(_eid, _n, _v) == 0
            except Exception:
                return False

        added, notes = _enum_merge_apply(plan, _add_member)
        e_ok += 1
        e_merged += 1
        enum_notes.extend('%s: %s' % (ename, n) for n in notes)
        log("  [3b] enum %s merged: +%d added, %d noted (was: whole-enum short-circuit)"
            % (ename, added, len(notes)))
    log("[3b] Enums: applied=%d/%d (existing merged=%d, notes=%d)"
        % (e_ok, len(enums), e_merged, len(enum_notes)))
    for _n in enum_notes[:40]:
        log("     enum-note: %s" % _n)

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
            mtype = m["type"]
            if isinstance(mtype, dict):
                continue  # inline union/struct deps resolved via referenced types
            mtype = mtype.replace("class ", "").replace("struct ", "")
            if "*" in mtype:
                continue
            base_type = _re2.sub(r'\[.*\]', '', mtype).strip()
            if base_type in all_struct_names:
                deps.add(base_type)
        return deps

    ordered = []
    remaining = dict(structs)
    done = set()
    while True:
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
                # [外部 vtable 槽名表 2026-10-16] external/unknown 痕 = **地址不认领**
                # （gbengine.dll 外部库类，vtable 表在 DLL 内）⇒ 不写 IDB（PAL3 .rdata
                # 无此表）。此前 addr='external' 走到 [5] 阶段 `int(vt_addr_hex, 16)`
                # ValueError 崩掉整个 apply（exit 1，实测 2026-10-16 00:05）。
                # 槽序/槽名数据只服务 codegen 渲染链（stage3._load_vtbl_index 的
                # `external:<cls>` 索引）✓ 治理正确性保持（不回填编造址）。
                if not str(vt_addr).lower().startswith('0x'):
                    continue
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
    log("[3] Importing gbengine headers (single source of truth)...")
    _import_gbengine_headers()
    
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

    # --- 3c. detached nested types（2026-09-15 新增，方案 E3） ---
    #
    # 有些**限定名**必须在 TIL 里可解析，但它们的父类**没有也不应有** struct 注解文件：
    #   - 已解散的幻影类（`PlayerMgr`，提交 6a8d71924 并入 SaleUI；当时的临时迁移
    #     脚本只搬了 methods/members，**完全没搬 nested_types**，导致 `PoisonState`
    #     被丢弃——该脚本已随 2026-10-16 归档定谳删除，史实留档于此）
    #   - 只被引用而无成员数据的类型
    #
    # 症状：`data/annotations/structs/ArcLocale.json` 的 `+336 pstate: PlayerMgr::PoisonState *`
    # 解析失败 → `create_fixed_struct` 在 `create_udt` **之前**就返回失败 →
    # ArcLocale 的真实 484 字节布局从未落地，TIL 里只剩 step 3a 建的空占位 →
    # 导出里 ArcLocale 变成 **size=1 / data_members=0**（16 个成员全丢），
    # 并向下游 CGameData.cpp / free_functions.h / CCBUI.cpp / Actor.cpp 传播。
    #
    # 为什么用独立文件而不是新建 struct 注解：为这些父类新建受管 struct 会制造
    # 「第 882 个 struct」并复活已解散的类名，属无证据扩张。E3 只提供**名称解析目标**，
    # 不主张任何成员/内存归属（详见 data/annotations/detached_nested_types.json 的 _evidence）。
    #
    # 注：与 SDK 路径（上面的 2b）不同，这里**不能**要求条目有 known_members ——
    # `PoisonState` 本就是无成员的类型；SDK 路径的 `if not _st.get("known_members"): continue`
    # 会把它整个跳过（复核者实测 E2 方案因此走不通）。
    _dnt_path = os.path.join(ANNOTATIONS_DIR, "detached_nested_types.json")
    _dnt_ok = 0
    if os.path.exists(_dnt_path):
        try:
            with open(_dnt_path, 'r', encoding='utf-8') as _df:
                _dnt_data = json.load(_df)
            for _dn_par, _dn_info in _dnt_data.items():
                if _dn_par.startswith("_"):          # 跳过 _purpose/_evidence/_maintenance 等元数据键
                    continue
                if not isinstance(_dn_info, dict):
                    continue
                _forward_decl_nested(_dn_par, {"nested_types": _dn_info}, til)
                _dnt_ok += 1
            log("[3c] Detached nested types: %d parent(s) processed" % _dnt_ok)
        except Exception as _de:
            # A 级必须可见：加载失败会让悬垂限定名无法解析，进而使整个 struct 报废。
            log("[FATAL] detached_nested_types.json load FAILED: %s" % _de)
            raise

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
        log("[WARN] %d struct imports FAILED — continuing. Fix annotation offsets or types for these:" % len(s_fail))
        for _sn, _se in s_fail:
            log("  [WARN] %s: %s" % (_sn, _se))
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

    # Wait for type system to settle then clear Hex-Rays caches
    # so next export uses corrected struct definitions.
    ida_auto.auto_wait()
    ida_hexrays.clear_cached_cfuncs()

    # --- 6. Function signatures (after structs so types are resolved) ---
    import re as _re_sig
    sig_ok = 0
    sig_fail = []
    sig_skip_placeholder = 0
    sig_parse_ok = 0

    # Build a combined list: functions.json only (struct methods are for codegen headers,
    # NOT for setting IDB function types — sharing same address across classes corrupts SetType)
    _sig_entries = list(funcs.items())

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
        if ("class" in info or "*this" in sig_raw) and "__cdecl" in sig_raw and "__thiscall" in sig_raw:
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
            # Class name from info['class'] field (set by _load_annotations).
            # Only for __thiscall methods: __cdecl/__stdcall/__fastcall are static and have no this.
            _cls = info.get('class')
            if _cls:
                _cc_is_thiscall = '__thiscall' in sig_raw
                _params = sig_raw[paren_idx:]
                if (_cc_is_thiscall
                        and '__hidden' not in _params
                        and not re.search(r'\b' + re.escape(_cls) + r'\s*\*\s*this', _params)):
                    _before = sig_raw[:paren_idx].rstrip()
                    # Insert ClassName *__hidden this as first param.
                    # __hidden is IDA's official spelling for the C++ this argument —
                    # with it Hex-Rays adopts the type as definite instead of
                    # re-inferring (which produced divergent signatures at export).
                    if _params.startswith('(') and _params[1:].strip() and _params[1:].strip()[0] != ')':
                        _new_params = '(%s *__hidden this, %s' % (_cls, _params[1:])
                    else:
                        _new_params = '(%s *__hidden this)' % _cls
                    sig_raw = _before + _new_params
                    # 类限定成员原型优先路径（2026-09-14 MCP set_function_prototype
                    # 验证形态）：'RET __thiscall Cls::Method(Cls *this, params)' —
                    # Hex-Rays 对该形态采纳为确定类型；短名 + __hidden 形式在部分
                    # 成员函数上不生效（HandleMessage 案例：SetType 报成功但
                    # 反编译仍为无参形态）。
                    if _cc_is_thiscall and re.match(r'^\w+$', name):
                        # E-3（e1472de2）：签名自带类限定的条目（`RET __thiscall Cls::M(...)`
                        # 形）_before 已含限定名与 cc——直接拼 _qsig 双拼
                        # （`Cls::M __thiscall Cls::M(...)`）⇒ _before 先剥限定名与调用约定。
                        _b2 = _before
                        _b2 = re.sub(r'\b(?:__thiscall|__cdecl|__stdcall|__fastcall)\s*', ' ', _b2)
                        _b2 = re.sub(r'\s*\w+\s*::\s*\w+\s*$', '', _b2).strip()
                        _qsig = '%s __thiscall %s::%s%s' % (
                            _b2, _cls, name,
                            _new_params.replace('__hidden ', ''))
                        if _apply_func_type_parse(addr, _qsig, til):
                            sig_ok += 1
                            sig_parse_ok += 1
                            continue
            # Extract a valid C identifier for the function name
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
            # Build a parse_decl-friendly declaration for the primary path:
            # qualified names break parse_decl; virtual/static are type-level
            # modifiers (virtuality is restored by vtable placement at export).
            _pb = before.replace("virtual ", " ").replace("static ", " ")
            # Normalize glued '*cc' ('UIFrameWnd *__thiscall') so '*' and the
            # calling convention tokenize separately. Otherwise '*__thiscall'
            # is one unknown token, gets treated as the function-name token
            # and dropped — the return type silently loses BOTH its '*' and
            # the cc (parsed as by-value struct return = ctor form → Hex-Rays
            # invents __return_ptr; root cause of the 86-function sret queue).
            _pb = _pb.replace("*", "* ")
            _pb = _pb.replace("struct ", "").replace("class ", "")
            _pb = _re_format.sub(r'\s+', ' ', _pb).strip()
            _ptoks = _pb.split()
            if _ptoks and _ptoks[-1] not in _type_and_cc:
                _ptoks = _ptoks[:-1]  # drop function-name token (possibly qualified)
            _decl_parse = ' '.join(_ptoks) + ' ' + short_name + after
            # Primary: parse_decl + apply_tinfo — Hex-Rays adopts as definite
            if _apply_func_type_parse(addr, _decl_parse, til):
                sig_ok += 1
                sig_parse_ok += 1
            # Apply via idc.SetType — handles virtual, thiscall, etc.
            elif idc.SetType(addr, sig_with_name):
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
    log("[6] Signatures: %d/%d (parse_tinfo=%d, fail=%d, placeholder=%d)" % (sig_ok, len([f for f in funcs.values() if f.get("signature")]), sig_parse_ok, len(sig_fail), sig_skip_placeholder))
    if sig_fail:
        for _addr_s, _fname_s, _err_s in sig_fail[:20]:
            log("  [!] %s: %s → %s" % (_addr_s, _fname_s[:40], _err_s[:60]))

    # --- 6b. Global types (after structs so struct types are resolved) ---
    g_typed = 0
    g_type_fail = []
    _til_g = ida_typeinf.get_idati()
    for addr_str, info in globs.items():
        addr = int(addr_str, 16)
        typ = info.get("type", "")
        if typ:
            if typ.strip() == "skip":
                g_typed += 1
                continue
            type_str = typ.rstrip(";") + ";"
            _base = typ.rstrip(";").replace("struct ", "").replace("class ", "").strip()
            # Named UDT instances must become REAL data items. Hex-Rays only
            # renders member chains through actual items — a type merely
            # attached to mid-item bytes (tail type) yields unk_XXXX + bogus
            # callee casts (g_palScript symptom). If the address is not a head
            # of the right size, clear the range, force a head, then SetType
            # (which resizes a real head to the UDT size).
            _tif = ida_typeinf.tinfo_t()
            if '[' not in _base and '*' not in _base and _tif.get_named_type(_til_g, _base):
                _need = _tif.get_size()
                if _need and _need != 0xFFFFFFFFFFFFFFFF and _need > 1:
                    _cursz = ida_bytes.get_item_size(addr) if ida_bytes.is_head(ida_bytes.get_flags(addr)) else 0
                    if _cursz != _need:
                        # DELIT_EXPAND (not SIMPLE): SIMPLE refuses to undefine
                        # neighboring typed/named bytes, leaving the address a
                        # 1-byte tail and SetType unable to resize the item.
                        ida_bytes.del_items(addr, ida_bytes.DELIT_EXPAND, _need)
                    if idc.SetType(addr, type_str):
                        g_typed += 1
                        continue
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

    # --- 6b3. Re-apply global names (idempotent) ---
    # Step [2] names globals BEFORE structs/items exist; names targeting
    # addresses that were mid-item at that time fail (set_name on a non-head
    # is rejected). After [6b]/[6b2] created real item heads, re-run the
    # rename so embedded-instance globals (g_palScript etc.) get their names.
    _renamed2 = 0
    for addr_str, info in globs.items():
        _name = info.get("name", "")
        if not _name:
            continue
        _a = int(addr_str, 16)
        if ida_name.get_name(_a) != _name:
            if ida_name.set_name(_a, _name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                _renamed2 += 1
    log("[6b3] Global names (re)applied: %d" % _renamed2)

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
                # ordinal 支持 2026-10-07（复核 R4）：同址多 lvar——列表化
                ann_by_stkoff.setdefault(sk, []).append(lv_ann)
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
        _stk_ordinal = {}
        for lvar in list(cfunc.lvars):
            is_reg = lvar.is_reg_var()
            ann = ann_by_name.get(lvar.name)
            if ann is None and ann_by_stkoff and not is_reg:
                try:
                    if lvar.is_stk_var():
                        soff = lvar.get_stkoff()
                        lst = ann_by_stkoff.get(soff) or []
                        if lst:
                            _i = _stk_ordinal.get(soff, 0)
                            ann = lst[_i] if _i < len(lst) else lst[-1]
                            _stk_ordinal[soff] = _i + 1
                except:
                    pass
            if ann is None:
                continue
            new_name = ann.get("name")
            if new_name and lvar.name != new_name:
                lvar.name = new_name
                modified = True
            new_type = ann.get("type")
            if new_type:
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
                    try:
                        _t = lv.type
                        if _t is not None and hasattr(_t, 'is_correct') and _t.is_correct():
                            si.type = _t
                    except:
                        pass
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
        if 'class' in info:
            _cls = info['class']
            _method = desired
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

    # --- F73（第 132 轮）：gbengine 导入槽的"退化原型"按修饰名纠正 ---
    # 必须放在**最后**（其它所有类型写入之后）：这些槽上的错误类型会被 Hex-Rays
    # 优先采用，从而吞掉真实参数（实测 33 处 `gbVFileSystem::Read`）。
    try:
        _fix_gbengine_import_slots()
    except Exception as _e_slot:
        log("[!] import slot signature pass raised: %s" % _e_slot)

    idc.save_database(idc.get_idb_path(), 0)
    log("[*] Done. Database saved.")

    # Write log file
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))

    # --- R4（2026-09-15 独立复核）：逐 struct 失败必须反映到退出码 ---
    #
    # 原先此处**无条件** `qexit(0)`，而 struct 导入失败只在上面 `[WARN]`+continue
    # ⇒ `cmd_apply` 照样打印 "OK: annotations applied"，整条 `apply && export && codegen`
    # 链对"导入失败"完全失效。这使 t3/M3 的证据门槛**永远只是日志信号，不是门禁**。
    #
    # 退出码取 **4**（避开 IDA 自身语义：`qexit(1)` 用于顶层异常，`2`/`3` 留给 IDA 内部）。
    # 注意 `cli.py:cmd_apply` 已检查本脚本的 returncode 并以之退出（t5 修复），
    # 故此处非零即可让 `&&` 链停下。
    if s_fail:
        log("[FATAL] %d struct(s) failed to import — exiting non-zero so the "
            "`apply && export && codegen` chain stops here." % len(s_fail))
        with open(LOG_FILE, 'w', encoding='utf-8') as f:
            f.write('\n'.join(log_lines))
        idc.qexit(4)

    idc.qexit(0)


if __name__ == "__main__":
    try:
        apply_annotations()
    except Exception as e:
        import traceback, os
        err_log = os.path.join(SCRIPT_DIR, "_logs", "apply_exception.txt")
        os.makedirs(os.path.dirname(err_log), exist_ok=True)
        with open(err_log, 'w') as f:
            # 首行带时间戳：本文件**从不自动清理**，陈旧内容会被误读成"当前状态"
            # （与 apply_status.json 同一类坑——那份也不是 apply 写的）。
            # 带时间戳后，读者可立即判断该异常属于哪一次运行。
            import datetime as _dt
            f.write("EXCEPTION in apply_annotations at %s\n" %
                    _dt.datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
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
