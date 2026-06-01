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


def _resolve_member_type(mtype_str, til):
    """将成员类型字符串解析为 tinfo_t，优先 API 创建，模板/函数指针 fallback parse_decl。"""
    s = mtype_str.strip()
    if not s:
        return None
    s = re.sub(r'\[0x([0-9a-fA-F]+)\]', lambda m: '[%d]' % int(m.group(1), 16), s)

    if '<' in s or '(' in s:
        tinfo = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(tinfo, til, "%s __x;" % s, ida_typeinf.PT_VAR) is None:
            return None
        return tinfo

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

    tinfo = ida_typeinf.tinfo_t()
    resolved = tinfo.get_named_type(til, s)
    if not resolved or tinfo.get_size() in (0, 0xFFFFFFFFFFFFFFFF):
        # get_named_type 不处理基本类型（char/int/float 等），用 parse_decl fallback
        if ida_typeinf.parse_decl(tinfo, til, "%s __x;" % s, ida_typeinf.PT_VAR) is None:
            return None
        resolved = True

    if is_ptr:
        ptr_tinfo = ida_typeinf.tinfo_t()
        if not ptr_tinfo.create_ptr(tinfo):
            return None
        tinfo = ptr_tinfo
    for size in reversed(array_sizes):
        arr_tinfo = ida_typeinf.tinfo_t()
        if not arr_tinfo.create_array(tinfo, size):
            return None
        tinfo = arr_tinfo
    return tinfo


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
    enum_ok = 0
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
        decl = 'enum %s {\n%s\n};' % (name, ',\n'.join(member_strs))
        tinfo = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
            tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
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

    # 批量生成 struct 声明
    _decls = []
    for cls in classes:
        name = cls.get('name', '')
        if not name or name in _SKIP_SYSTEM_TYPES:
            continue
        if '<' in name or '::' in name:
            continue
        # 跳过 gbengine 类型（已在 import_gbengine_types 中导入）
        _skip_ti = ida_typeinf.tinfo_t()
        if _skip_ti.get_named_type(til, name) and _skip_ti.get_size() > 1:
            continue
        data_members = cls.get('data_members', [])
        if not data_members:
            continue

        lines = []
        for m in data_members:
            mname = m.get('name', '')
            mtype_str = m.get('type', 'int')
            if not mname:
                continue
            if mname.startswith('__vftable') or any(v in mtype_str for v in _vftable_types):
                continue
            # 数组后缀移到变量名: char[64] buf → char buf[64]
            _arr = ''
            _base_type = mtype_str
            while True:
                _ma = re.match(r'^(.+?)\[(\d+|0x[0-9a-fA-F]+)\](.*)$', _base_type)
                if not _ma:
                    break
                _base_type = _ma.group(1).strip()
                _arr += '[%s]' % _ma.group(2)
            if _arr:
                lines.append("    %s %s%s;" % (_base_type, mname, _arr))
            else:
                lines.append("    %s %s;" % (mtype_str, mname))

        if not lines:
            continue

        keyword = "union" if cls.get('kind') == 'union' else "struct"
        _decls.append("%s %s {\n%s\n};" % (keyword, name, "\n".join(lines)))

    # PDB struct definitions 暂存，等 gbengine+D3D 导入后再执行
    # (gbengine 类型优先级高于 PDB 类型)
    _pdb_decls = _decls if _decls else None
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
    _errs = idc.parse_decls(_full_decls, 0)
    log("[*] D3D parse_decls: errors=%d" % (_errs if _errs is not None else 0))

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

    # Phase 1c: 导入 PDB struct 定义（D3D + gbengine 类型已就绪）
    if _pdb_decls:
        log("")
        cls_ok = 0
        _fail_list = []
        for _idx, _d in enumerate(_pdb_decls):
            _ti = ida_typeinf.tinfo_t()
            _name_match = re.match(r'(?:struct|union|class)\s+(\w+)', _d)
            _sname = _name_match.group(1) if _name_match else '?'
            if ida_typeinf.parse_decl(_ti, til, _d, ida_typeinf.PT_TYP) is not None:
                try:
                    _ti.set_named_type(til, _sname, ida_typeinf.NTF_REPLACE)
                    cls_ok += 1
                    if (_idx + 1) % 100 == 0:
                        log("  ... %d/%d" % (_idx + 1, len(_pdb_decls)))
                except:
                    pass
            elif _idx < 10:
                _fail_list.append(_sname)
        log("[Phase 1c] PDB struct 导入: %d/%d 成功" % (cls_ok, len(_pdb_decls)))
        if _fail_list:
            log("  首批失败: %s" % ", ".join(_fail_list))
        log("[*] 类导入: %d forward decls + %d full definitions" % (len(classes), cls_ok))


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
