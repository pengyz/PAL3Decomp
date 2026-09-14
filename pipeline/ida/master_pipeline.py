"""
IDAPython: PAL3.exe 完整分析管线

在新建的 PAL3.exe IDB 上一次性执行:
1. 导入 PAL3A.PDB 类型 (structs, enums)
2. 应用 FLIRT 签名 (pal3a_text.sig)
3. 应用全局变量名
4. 导出 Hex-Rays 反编译

用法 (新建 IDB 并执行管线):
  idat.exe -A -S"pal3_master_pipeline.py" original/PAL3.exe

或在已有 IDB 上执行:
  idat.exe -A -S"pal3_master_pipeline.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_funcs
import ida_name
import ida_bytes
import ida_hexrays
import ida_typeinf
import ida_fixup
import idautils
import idc
import json
import os
import re
import time
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
os.makedirs(LOG_DIR, exist_ok=True)

PDB_EXPORT = os.path.join(PROJECT_ROOT, "data", "pdb", "pdb_export.json")
GLOBALS_FILE = os.path.join(PROJECT_ROOT, "data", "pdb", "globals_export.json")
# PDB 非权威源（版本与 PAL3.exe 不匹配，用户裁定 2026-09-14）：
# 枚举默认不再导入 IDB。数据保留在 pdb_export.json 作为假设库，
# 晋升走 tools/enum_promote.py 的二进制证据验证 → data/annotations/enums.json。
PDB_ENUM_IMPORT = False
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3")
SIG_NAME = "pal3a_text"

LOG_FILE = os.path.join(LOG_DIR, "pal3_master_pipeline_log.txt")
try:
    open(LOG_FILE, 'w').close()
except:
    pass

TEXT_START = 0x00401000
TEXT_END = 0x005695D0
RDATA_START = 0x0056A000
RDATA_END = 0x0057F178
DATA_START = 0x00580000
DATA_END = 0x0060C000

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)
    try:
        with open(LOG_FILE, 'a') as _lf:
            _lf.write(str(msg) + '\n')
    except:
        pass


_PRIMITIVE_BTF = {
    'void': ida_typeinf.BTF_VOID, 'char': ida_typeinf.BTF_CHAR, 'signed char': ida_typeinf.BTF_INT8,
    'unsigned char': ida_typeinf.BTF_BYTE, 'BYTE': ida_typeinf.BTF_BYTE, 'uchar': ida_typeinf.BTF_BYTE,
    'short': ida_typeinf.BTF_INT16, 'unsigned short': ida_typeinf.BTF_UINT16, 'WORD': ida_typeinf.BTF_UINT16,
    'int': ida_typeinf.BTF_INT32, 'signed int': ida_typeinf.BTF_INT32, 'unsigned int': ida_typeinf.BTF_UINT32,
    'UINT': ida_typeinf.BTF_UINT32, 'DWORD': ida_typeinf.BTF_UINT32, 'unsigned': ida_typeinf.BTF_UINT32,
    'long': ida_typeinf.BTF_INT32, 'unsigned long': ida_typeinf.BTF_UINT32, 'LONG': ida_typeinf.BTF_INT32,
    'float': ida_typeinf.BTF_FLOAT, 'double': ida_typeinf.BTF_DOUBLE,
    'bool': ida_typeinf.BTF_BOOL, 'BOOL': ida_typeinf.BTF_INT32,
    '__int64': ida_typeinf.BTF_INT64, 'unsigned __int64': ida_typeinf.BTF_UINT64,
    '_DWORD': ida_typeinf.BTF_UINT32, '_BYTE': ida_typeinf.BTF_BYTE, '_WORD': ida_typeinf.BTF_UINT16,
}

def _resolve_member_type(mtype_str, til):
    s = mtype_str.strip()
    if not s:
        return None
    s = re.sub(r'\[0x([0-9a-fA-F]+)\]', lambda m: '[%d]' % int(m.group(1), 16), s)
    if '<' in s or '(' in s:
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
    is_ptr = s.endswith('*')
    if is_ptr:
        s = s.rstrip('*').strip()
    if s.startswith('const '):
        s = s[6:].strip()
    if not s:
        return None
    if s == 'void' and is_ptr:
        void_t = ida_typeinf.tinfo_t()
        if void_t.create_simple_type(ida_typeinf.BTF_VOID):
            ptr_t = ida_typeinf.tinfo_t()
            if ptr_t.create_ptr(void_t): return ptr_t
        return None
    btf = _PRIMITIVE_BTF.get(s)
    if btf is not None:
        tinfo = ida_typeinf.tinfo_t()
        if tinfo.create_simple_type(btf):
            if is_ptr: p = ida_typeinf.tinfo_t(); p.create_ptr(tinfo); tinfo = p
            for sz in reversed(array_sizes): a = ida_typeinf.tinfo_t(); a.create_array(tinfo, sz); tinfo = a
            return tinfo
    tinfo = ida_typeinf.tinfo_t()
    if tinfo.get_named_type(til, s) and tinfo.get_size() not in (0, 0xFFFFFFFFFFFFFFFF):
        if is_ptr: p = ida_typeinf.tinfo_t(); p.create_ptr(tinfo); tinfo = p
        for sz in reversed(array_sizes): a = ida_typeinf.tinfo_t(); a.create_array(tinfo, sz); tinfo = a
        return tinfo
    return None


# ========================================================================
# Phase 1: Import Types
# ========================================================================
def phase1_import_types():
    log("")
    log("=" * 60)
    log("[Phase 1] 导入 PAL3A.PDB 类型")
    log("=" * 60)

    # SDK TIL disabled: causes more harm than benefit.
    # Concurrency/NtTib/stdiobuf misidentifications outweigh D3D type availability.
    # D3D types are handled via gbengine headers instead.
    # til = ida_typeinf.get_idati()
    # for til_name in ('mssdk_win7', 'mssdk_win10'):
    #     rc = ida_typeinf.add_til(til_name, ida_typeinf.ADDTIL_SILENT)
    #     if rc:
    #         log("[*] Loaded TIL: %s" % til_name)
    #         break
    # else:
    #     log("[!] No mssdk TIL found (D3D types may be unavailable)")
    log("[*] SDK TIL: DISABLED (causes type misidentification)")

    if not os.path.exists(PDB_EXPORT):
        log("[!] PDB 文件不存在: %s" % PDB_EXPORT)
        return

    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        pdb_data = json.load(f)

    classes = pdb_data.get('classes', [])
    enums = pdb_data.get('enums', [])
    log("[*] 类: %d, 枚举: %d" % (len(classes), len(enums)))

    til = ida_typeinf.get_idati()

    # Enums - format: {name, values: {NAME: "value_str"}}
    # PDB 非权威（见 PDB_ENUM_IMPORT 注释）：默认跳过；晋升需经
    # tools/enum_promote.py 的二进制证据验证后写入 annotations/enums.json。
    enum_ok = 0
    if not PDB_ENUM_IMPORT:
        log("[*] PDB 枚举导入: 已跳过（PDB 非权威源，走 enum_promote 晋升通道）")
    else:
        for enum_info in enums:
            name = enum_info.get('name', '')
            values = enum_info.get('values', {})
            if not name or not values:
                continue
            # Skip anonymous enums (contain "::" with __unnamed)
            if '__unnamed' in name or '::' in name:
                continue
            member_strs = []
            for mname, mval_str in values.items():
                try:
                    mval = int(mval_str)
                except (ValueError, TypeError):
                    mval = 0
                member_strs.append('    %s = %d' % (mname, mval))
            if not member_strs:
                continue
            eid = idc.get_enum(name)
            if eid == -1:
                eid = idc.add_enum(-1, name, 1)
            if eid != -1:
                for mname, mval_str in values.items():
                    try:
                        mval = int(mval_str)
                    except (ValueError, TypeError):
                        mval = 0
                    idc.add_enum_member(eid, mname, mval)
            enum_ok += 1

    log("[*] 枚举导入: %d / %d" % (enum_ok, len(enums)))

    # System types provided by SDK headers — do NOT import from PDB (creates blobs)
    _SKIP_SYSTEM_TYPES = {
        '_DIMOUSESTATE', '_DIMOUSESTATE2', '_DIJOYSTATE', '_DIJOYSTATE2',
        '_DIDEVCAPS', '_DIDEVICEINSTANCEA', '_DIDEVICEOBJECTINSTANCEA',
        'DIMOUSESTATE', 'DIMOUSESTATE2', 'DIJOYSTATE', 'DIJOYSTATE2',
        'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG', 'RECT', 'POINT', 'SIZE',
        'WNDCLASSA', 'tagWNDCLASSA', '_WIN32_FIND_DATAA',
        '_FILETIME', '_SYSTEMTIME', '_MEMORYSTATUS', '_SECURITY_ATTRIBUTES',
        '_OSVERSIONINFOA', '_STARTUPINFOA', '_GUID', 'GUID', 'IID',
        'D3DMATRIX', '_D3DMATRIX', 'D3DVECTOR', '_D3DVECTOR',
        '_iobuf', 'FILE',
    }

    # Full definitions — 生成单一 C header 字符串，用 idc.parse_decls 批量解析。
    # 此方式让 IDA 内部处理前向引用和依赖顺序，和 gbengine 类型导入同样机制。
    cls_ok = 0
    _vftable_types = {'__vftable', 'vtbl_'}

    # PDB struct 不再由 master_pipeline 导入。
    # annotation 文件已合并 PDB 所有成员数据，由 apply_annotations 一次性导入。
    cls_ok = 0

    # Phase 1b: 从 VC6 DirectX 9 头文件导入 D3D 值类型 + gbengine 类型
    log("")
    log("=" * 60)
    log("[Phase 1b] 导入 D3D 值类型 + gbengine 类型")
    log("=" * 60)

    _vc6_dir = os.path.join(PROJECT_ROOT, "tools", "vc6", "Include")
    _d3d_content = []
    _hp = os.path.join(_vc6_dir, 'd3d9types.h')
    if os.path.exists(_hp):
        _txt = open(_hp, encoding='utf-8', errors='replace').read()
        _txt = _txt.replace('\r\n', '\n')
        _txt = re.sub(r'//[^\n]*', '', _txt)
        _txt = re.sub(r'/\*.*?\*/', '', _txt, flags=re.DOTALL)
        _txt = re.sub(r'\\\n', ' ', _txt)
        _txt = re.sub(r'#\s*(?:include|define|undef|if|ifdef|ifndef|else|elif|endif|pragma|error|warning|line)[^\n]*', '', _txt, flags=re.MULTILINE)
        _txt = re.sub(r'DECLARE_INTERFACE[^}]*}\s*;', '', _txt, flags=re.DOTALL)
        _txt = re.sub(r'\n{3,}', '\n\n', _txt)
        _d3d_content.append(_txt)

    # d3dx9math.h 是 C++ class 语法，idc.parse_decls 不支持。
    # D3DX 值类型用手动纯 struct 定义（无继承、无方法）。
    _d3dx_stubs = """
typedef struct D3DXVECTOR2 { float x; float y; } D3DXVECTOR2;
typedef struct D3DXVECTOR3 { float x; float y; float z; } D3DXVECTOR3;
typedef struct D3DXVECTOR4 { float x; float y; float z; float w; } D3DXVECTOR4;
typedef struct D3DXCOLOR { float r; float g; float b; float a; } D3DXCOLOR;
typedef struct D3DXMATRIX {
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
} D3DXMATRIX;
"""
    _d3d_content.append(_d3dx_stubs)
    _full_decls = '\n'.join(_d3d_content)
    log("[*] D3D 头文件: %d chars" % len(_full_decls))
    # D3D types: extract struct names, create empty forward decls
    _d3d_til = ida_typeinf.get_idati()
    _d3d_ok = 0
    for _m in re.finditer(r'(?:struct|typedef struct)\s+(\w+)', _full_decls):
        _n = _m.group(1)
        if ida_typeinf.tinfo_t().get_named_type(_d3d_til, _n): continue
        _u = ida_typeinf.udt_type_data_t(); _u.total_size = 0
        _t = ida_typeinf.tinfo_t()
        if _t.create_udt(_u, ida_typeinf.BTF_STRUCT) and _t.set_named_type(_d3d_til, _n, ida_typeinf.NTF_REPLACE):
            _d3d_ok += 1
    log("[*] D3D types: %d forward-declared" % _d3d_ok)

    # 导入 gbengine 类型
    try:
        sys.path.insert(0, os.path.join(PROJECT_ROOT, "pipeline", "ida"))
        import import_gbengine_types as _gb
        _gb.main()
        log("[*] gbengine 导入完成")
    except SystemExit:
        log("[!] gbengine import 调用 qexit")
    except Exception as e:
        log("[!] gbengine import EXCEPTION: %s" % e)

    # Phase 1c: PDB struct 已合并到 annotation，由 apply_annotations 导入。
    # master_pipeline 仅负责 PDB forward decl + D3D + gbengine 类型。
    log("[*] PDB struct: 已合并到 annotation，由 apply_annotations 导入")


# ========================================================================
# Phase 2: Apply FLIRT Signatures
# ========================================================================
def phase2_apply_flirt():
    log("")
    log("=" * 60)
    log("[Phase 2] 应用 FLIRT 签名")
    log("=" * 60)

    # Count functions before
    before_named = 0
    before_total = 0
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        if ea < TEXT_START or ea >= TEXT_END:
            continue
        before_total += 1
        name = ida_name.get_name(ea) or ""
        if name and not name.startswith("sub_"):
            before_named += 1

    log("[*] 签名应用前: %d 命名 / %d 总函数" % (before_named, before_total))

    # Apply FLIRT signature file using ida_funcs API
    import ida_funcs as _ida_funcs
    result = _ida_funcs.apply_idasgn_to(SIG_NAME, TEXT_START, False)
    log("[*] apply_idasgn_to('%s', 0x%X) 返回: %d" % (SIG_NAME, TEXT_START, result))
    if result >= 0:
        log("[*] FLIRT 签名应用成功")
    else:
        log("[!] FLIRT 签名应用失败 (返回 %d)" % result)
        log("    请确认 %s.sig 在 IDA sig/pc/ 目录中" % SIG_NAME)

    # Wait for auto-analysis
    ida_auto.auto_wait()

    # Count after
    after_named = 0
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        if ea < TEXT_START or ea >= TEXT_END:
            continue
        name = ida_name.get_name(ea) or ""
        if name and not name.startswith("sub_"):
            after_named += 1

    log("[*] 签名应用后: %d 命名 (+%d)" % (after_named, after_named - before_named))


def main():
    """完整管线入口"""
    phase1_import_types()
    phase2_apply_flirt()
    idc.qexit(0)


if __name__ == '__main__':
    main()
