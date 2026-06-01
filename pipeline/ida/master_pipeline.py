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

    # Forward declarations — first pass: every class gets a struct X;
    for cls in classes:
        name = cls.get('name', '')
        if name and name not in _SKIP_SYSTEM_TYPES:
            decl = 'struct %s;' % name
            tinfo = ida_typeinf.tinfo_t()
            if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
                tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)

    # Full definitions — 单遍导入，跳过无法解析的成员（gbengine/D3D 等不在 PDB 的类型）。
    # 此类成员在 IDB 中留为 gap，apply_annotations 的 diff 模式会补充。
    cls_ok = 0
    cls_names_ok = set()  # track successfully imported
    skip_member_total = 0
    for cls in classes:
        name = cls.get('name', '')
        if not name or name in _SKIP_SYSTEM_TYPES:
            continue
        if '<' in name or '::' in name:
            continue
        data_members = cls.get('data_members', [])
        if not data_members:
            continue
        try:
            udt = ida_typeinf.udt_type_data_t()
            udt.taudt_bits = 1024
            skip_count = 0

            for m in data_members:
                mname = m.get('name', '')
                mtype_str = m.get('type', 'int')
                moffset = m.get('offset', 0)
                if not mname:
                    continue

                mtinfo = _resolve_member_type(mtype_str, til)
                if mtinfo is None:
                    skip_count += 1
                    continue
                msize = mtinfo.get_size()
                if msize in (0, 0xFFFFFFFFFFFFFFFF):
                    skip_count += 1
                    continue

                mm = ida_typeinf.udt_member_t()
                mm.name = mname
                mm.offset = moffset * 8
                mm.size = msize * 8
                mm.type = mtinfo
                udt.push_back(mm)

            is_union = cls.get('kind') == 'union'
            udt_flag = ida_typeinf.BTF_UNION if is_union else ida_typeinf.BTF_STRUCT
            result_tinfo = ida_typeinf.tinfo_t()
            if result_tinfo.create_udt(udt, udt_flag):
                result_tinfo.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                cls_ok += 1
                cls_names_ok.add(name)
                skip_member_total += skip_count
        except Exception as e:
            log("[!] 无法导入 %s: %s" % (name, e))

    if skip_member_total > 0:
        log("[!] 共 %d 个成员因类型无法解析被跳过（后续可通过 annotation 补充）" % skip_member_total)

    log("[*] 类导入: %d forward decls + %d full definitions" % (len(classes), cls_ok))

    # Phase 1b: 先创建 D3D 值类型（避免被 gbengine import 中的 parse_decls 错误覆盖）
    log("")
    log("=" * 60)
    log("[Phase 1b] 创建 D3D 值类型 + 导入 gbengine 类型")
    log("=" * 60)

    # 先确保 D3D 值类型以纯 struct 形式存在于 TIL
    _d3d_types = [
        ("D3DCOLOR",      4,  "unsigned long"),
        ("D3DVECTOR",     12, "float[3]"),
        ("D3DCOLORVALUE", 16, "float[4]"),
        ("D3DXVECTOR2",   8,  "float[2]"),
        ("D3DXVECTOR3",   12, "float[3]"),
        ("D3DXVECTOR4",   16, "float[4]"),
        ("D3DXCOLOR",     16, "float[4]"),
    ]
    _d3d_ok = 0
    for _tn, _tsize, _trep in _d3d_types:
        _ti = ida_typeinf.tinfo_t()
        if _ti.get_named_type(til, _tn) and _ti.get_size() == _tsize:
            _d3d_ok += 1
            continue
        # 创建不透明类型（正确 size + 字段名）
        _decl = "struct %s { char _data[%d]; }; " % (_tn, _tsize)
        _ti2 = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(_ti2, til, _decl, ida_typeinf.PT_TYP) is not None:
            _ti2.set_named_type(til, _tn, ida_typeinf.NTF_REPLACE)
            _d3d_ok += 1
    # D3DXMATRIX
    _ti = ida_typeinf.tinfo_t()
    if _ti.get_named_type(til, "D3DXMATRIX") and _ti.get_size() == 64:
        _d3d_ok += 1
    else:
        _decl = "struct D3DXMATRIX { float _11,_12,_13,_14; float _21,_22,_23,_24; float _31,_32,_33,_34; float _41,_42,_43,_44; }; "
        _ti2 = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(_ti2, til, _decl, ida_typeinf.PT_TYP) is not None:
            _ti2.set_named_type(til, "D3DXMATRIX", ida_typeinf.NTF_REPLACE)
            _d3d_ok += 1
    log("[*] D3D 值类型: %d/9 存在" % _d3d_ok)

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

    # Retry PDB full definitions — now gbengine/D3D types are available
    log("")
    log("[Phase 1c] 重试 PDB 完整导入（gbengine 类型已就绪）")
    _imported_names = set()
    for cls in classes:
        n = cls.get('name', '')
        if n:
            _imported_names.add(n)
    cls_retry = 0
    for cls in classes:
        name = cls.get('name', '')
        if not name or name in cls_names_ok:
            continue
        existing_ti = ida_typeinf.tinfo_t()
        if existing_ti.get_named_type(til, name) and existing_ti.get_size() > 1:
            continue  # already imported
        try:
            data_members = cls.get('data_members', [])
            if not data_members:
                continue
            udt = ida_typeinf.udt_type_data_t()
            udt.taudt_bits = 1024
            for m in data_members:
                mname = m.get('name', '')
                mtype_str = m.get('type', 'int')
                moffset = m.get('offset', 0)
                if not mname:
                    continue
                mtinfo = _resolve_member_type(mtype_str, til)
                if mtinfo is None:
                    break
                msize = mtinfo.get_size()
                if msize in (0, 0xFFFFFFFFFFFFFFFF):
                    break
                mm = ida_typeinf.udt_member_t()
                mm.name = mname
                mm.offset = moffset * 8
                mm.size = msize * 8
                mm.type = mtinfo
                udt.push_back(mm)
            else:
                is_union = cls.get('kind') == 'union'
                udt_flag = ida_typeinf.BTF_UNION if is_union else ida_typeinf.BTF_STRUCT
                rt = ida_typeinf.tinfo_t()
                if rt.create_udt(udt, udt_flag):
                    rt.set_named_type(til, name, ida_typeinf.NTF_REPLACE)
                    cls_retry += 1
        except Exception:
            pass
    if cls_retry:
        log("[*] retry 追加: %d structs (原跳过成员现可解析)" % cls_retry)


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
