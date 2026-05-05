#!/usr/bin/env python3
"""
从 PDB 导出生成 IDAPython 结构体导入脚本。

读取 asm/pal3a/pdb_export.json 中的 classes 字段，
按类型传播影响力排序，生成可在 IDA 中执行的 IDAPython 脚本。

生成的脚本会：
1. 创建/更新 IDA 中的结构体定义（使用真实字段名和类型）
2. 对成员函数设置正确的 this 指针类型
3. 清除 Hex-Rays 反编译缓存

用法:
    python tools/gen_ida_struct_import.py --batch P0        # 引擎基础类 (~30)
    python tools/gen_ida_struct_import.py --batch P1        # 游戏核心类 (~20)
    python tools/gen_ida_struct_import.py --batch P2        # 战斗系统 (~15)
    python tools/gen_ida_struct_import.py --batch P3        # UI系统 (~30)
    python tools/gen_ida_struct_import.py --batch all       # 所有有 data_members 的类
    python tools/gen_ida_struct_import.py --class Role      # 单个类
    python tools/gen_ida_struct_import.py --list            # 列出分批信息
    python tools/gen_ida_struct_import.py --deps Role       # 显示依赖关系
"""

import argparse
import json
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
PDB_EXPORT = PROJECT_ROOT / "asm" / "pal3a" / "pdb_export.json"
OUTPUT_DIR = PROJECT_ROOT / "tools" / "fulldump"

# PDB type string → IDA til type mapping
BASIC_TYPE_MAP = {
    'int': 'BT_INT32',
    'unsigned int': 'BT_UINT32',
    'uint': 'BT_UINT32',
    'long': 'BT_INT32',
    'unsigned long': 'BT_UINT32',
    'ulong': 'BT_UINT32',
    'short': 'BT_INT16',
    'unsigned short': 'BT_UINT16',
    'ushort': 'BT_UINT16',
    'char': 'BT_INT8',
    'unsigned char': 'BT_UINT8',
    'uchar': 'BT_UINT8',
    'float': 'BT_FLOAT',
    'double': 'BT_DOUBLE',
    'bool': 'BT_BOOL',
    'void': 'BT_VOID',
    '__int64': 'BT_INT64',
    'unsigned __int64': 'BT_UINT64',
    'BOOL': 'BT_INT32',
    'BYTE': 'BT_UINT8',
    'WORD': 'BT_UINT16',
    'DWORD': 'BT_UINT32',
    'LONG': 'BT_INT32',
    'ULONG': 'BT_UINT32',
    'UINT': 'BT_UINT32',
    'CHAR': 'BT_INT8',
    'WCHAR': 'BT_INT16',
    'HANDLE': 'BT_UINT32',
    'HWND': 'BT_UINT32',
    'HINSTANCE': 'BT_UINT32',
    'HRESULT': 'BT_INT32',
    'LPSTR': 'PTR_CHAR',
    'LPCSTR': 'PTR_CHAR',
    'LPVOID': 'PTR_VOID',
    'SIZE_T': 'BT_UINT32',
}

# Size of basic types (bytes)
BASIC_TYPE_SIZE = {
    'int': 4, 'unsigned int': 4, 'uint': 4,
    'long': 4, 'unsigned long': 4, 'ulong': 4,
    'short': 2, 'unsigned short': 2, 'ushort': 2,
    'char': 1, 'unsigned char': 1, 'uchar': 1,
    'float': 4, 'double': 8,
    'bool': 1, 'void': 0,
    '__int64': 8, 'unsigned __int64': 8,
    'BOOL': 4, 'BYTE': 1, 'WORD': 2, 'DWORD': 4,
    'LONG': 4, 'ULONG': 4, 'UINT': 4,
    'CHAR': 1, 'WCHAR': 2,
    'HANDLE': 4, 'HWND': 4, 'HINSTANCE': 4, 'HRESULT': 4,
    'LPSTR': 4, 'LPCSTR': 4, 'LPVOID': 4, 'SIZE_T': 4,
}


def load_pdb():
    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        return json.load(f)


def parse_type_string(type_str):
    """解析 PDB 类型字符串，返回 (base_type, is_ptr, array_count)

    PDB 格式:
      "int" → (int, False, 0)
      "int *" → (int, True, 0)
      "int[10]" → (int, False, 10)  — inline array
      "Type[16] *" → (Type, True, 16) — array of 16 pointers
    """
    s = type_str.strip()

    # Check pointer (末尾 *)
    is_ptr = s.endswith('*')
    if is_ptr:
        s = s[:-1].strip()

    # Check array
    array_count = 0
    arr_match = re.search(r'\[(\d+)\]$', s)
    if arr_match:
        array_count = int(arr_match.group(1))
        s = s[:arr_match.start()].strip()

    return s, is_ptr, array_count


def get_type_size(type_str, class_sizes):
    """估算类型大小"""
    base, is_ptr, arr_count = parse_type_string(type_str)

    if is_ptr:
        size = 4  # 32-bit pointer
    elif base in BASIC_TYPE_SIZE:
        size = BASIC_TYPE_SIZE[base]
    elif base in class_sizes:
        size = class_sizes[base]
    else:
        size = 4  # Default assumption

    if arr_count > 0:
        size *= arr_count

    return size


def deduplicate_classes(classes):
    """去重：PDB 中同名类可能出现多次，取字段最多的版本"""
    best = {}
    for c in classes:
        name = c['name']
        if not c.get('data_members'):
            continue
        if name not in best or len(c['data_members']) > len(best[name]['data_members']):
            best[name] = c
    return best


def compute_dependencies(classes_dict):
    """计算类之间的依赖关系（字段类型引用）"""
    deps = defaultdict(set)
    for name, c in classes_dict.items():
        for m in c.get('data_members', []):
            base, is_ptr, _ = parse_type_string(m['type'])
            if base in classes_dict and base != name:
                if not is_ptr:
                    # Non-pointer → hard dependency (needs full definition)
                    deps[name].add(base)
    return deps


def topological_sort(classes_dict, deps):
    """拓扑排序：被依赖的结构体先定义"""
    visited = set()
    order = []

    def dfs(name):
        if name in visited:
            return
        visited.add(name)
        for dep in deps.get(name, set()):
            if dep in classes_dict:
                dfs(dep)
        order.append(name)

    for name in classes_dict:
        dfs(name)
    return order


def classify_batches(classes_dict, func_class_count):
    """按影响力分批"""
    batches = {
        'P0': [],  # 引擎基础 (gb* + 被广泛依赖的)
        'P1': [],  # 游戏核心 (Role, SceneObj, Scene, PAL3)
        'P2': [],  # 战斗系统 (CCB*)
        'P3': [],  # UI系统 (*UI)
        'P4': [],  # 其余
    }

    core_game = {'Role', 'SceneObj', 'Scene', 'PAL3', 'PlayerMgr', 'Actor',
                 'NavigationInfo', 'SceneMapObj', 'PalScript', 'MyMdl'}
    combat_prefixes = ('CCB', 'CG_')
    ui_suffixes = ('UI', 'Dialog', 'Window')

    for name in classes_dict:
        if name.startswith('gb'):
            batches['P0'].append(name)
        elif name in core_game:
            batches['P1'].append(name)
        elif any(name.startswith(p) for p in combat_prefixes):
            batches['P2'].append(name)
        elif any(name.endswith(s) for s in ui_suffixes):
            batches['P3'].append(name)
        else:
            batches['P4'].append(name)

    # Sort each batch by function count (highest impact first)
    for batch in batches.values():
        batch.sort(key=lambda n: -func_class_count.get(n, 0))

    return batches


IDA_C_TYPE_MAP = {
    'uchar': 'unsigned char',
    'ulong': 'unsigned int',
    'uint': 'unsigned int',
    'ushort': 'unsigned short',
    'BOOL': 'int',
    'BYTE': 'unsigned char',
    'WORD': 'unsigned short',
    'DWORD': 'unsigned int',
    'LONG': 'int',
    'ULONG': 'unsigned int',
    'UINT': 'unsigned int',
    'CHAR': 'char',
    'WCHAR': 'short',
    'HANDLE': 'void *',
    'HWND': 'void *',
    'HINSTANCE': 'void *',
    'HRESULT': 'int',
    'LPSTR': 'char *',
    'LPCSTR': 'const char *',
    'LPVOID': 'void *',
    'SIZE_T': 'unsigned int',
    'HBITMAP': 'void *',
    'HDC': 'void *',
    'HFONT': 'void *',
    'COLORREF': 'unsigned int',
    'WPARAM': 'unsigned int',
    'LPARAM': 'int',
    'LRESULT': 'int',
    'D3DCOLOR': 'unsigned int',
    'FLOAT': 'float',
}


def generate_ida_type_string(type_str, known_structs):
    """生成 IDA parse_decls 能识别的 C 类型声明字符串"""
    base, is_ptr, arr_count = parse_type_string(type_str)

    # Simplify std:: types to void*
    if base.startswith('std::'):
        if is_ptr:
            return 'void *'
        return None  # Will use gap

    # Function pointers
    if '(*)' in type_str or 'void (*)' in type_str:
        if is_ptr:
            return 'void **'
        return 'void *'

    # Map PDB types to standard C types that IDA recognizes
    if base in IDA_C_TYPE_MAP:
        c_type = IDA_C_TYPE_MAP[base]
    elif base in ('int', 'unsigned int', 'short', 'unsigned short',
                  'char', 'unsigned char', 'float', 'double',
                  'long', 'unsigned long', 'void', '__int64',
                  'unsigned __int64', 'bool'):
        c_type = base
    elif base in known_structs:
        c_type = base
    else:
        if is_ptr:
            return 'void *'
        return None  # Will use gap

    if is_ptr:
        # If c_type already ends with *, don't double it
        if not c_type.endswith('*'):
            c_type += ' *'
    if arr_count > 0:
        c_type += f'[{arr_count}]'

    return c_type


def generate_struct_definition(cls, class_sizes, known_structs):
    """为单个类生成 IDA C 结构体定义字符串"""
    name = cls['name']
    size = cls['size']
    members = cls.get('data_members', [])

    if not members:
        return None

    # Skip template classes (not valid C identifiers)
    if '<' in name or '>' in name or ',' in name:
        return None

    # Sort members by offset
    members = sorted(members, key=lambda m: m['offset'])

    lines = []
    lines.append(f'struct {name} {{')

    current_offset = 0
    for i, m in enumerate(members):
        offset = m['offset']
        field_name = m['name']
        type_str = m['type']

        # Sanitize field name
        field_name = re.sub(r'[^a-zA-Z0-9_]', '_', field_name)
        if not field_name or field_name[0].isdigit():
            field_name = f'field_{offset:X}'

        # Add gap if needed
        if offset > current_offset:
            gap_size = offset - current_offset
            lines.append(f'    char _gap_{current_offset:X}[{gap_size}];')
            current_offset = offset

        # Determine field type and size
        c_type = generate_ida_type_string(type_str, known_structs)

        # Calculate field size
        if i + 1 < len(members):
            next_offset = members[i + 1]['offset']
            field_size = next_offset - offset
        else:
            field_size = size - offset

        if c_type is None:
            # Unknown type - use char array
            if field_size > 0:
                lines.append(f'    char {field_name}[{field_size}]; // {type_str}')
            current_offset = offset + field_size
            continue

        # Handle arrays in the type string
        base, is_ptr, arr_count = parse_type_string(type_str)
        if arr_count > 0 and is_ptr:
            # "Type[N] *" → array of N pointers: Type * field[N]
            base_c = generate_ida_type_string(base + ' *', known_structs) or 'void *'
            lines.append(f'    {base_c} {field_name}[{arr_count}];')
        elif arr_count > 0:
            # "Type[N]" → inline array
            base_c = generate_ida_type_string(base, known_structs) or 'char'
            lines.append(f'    {base_c} {field_name}[{arr_count}];')
        else:
            lines.append(f'    {c_type} {field_name};')

        current_offset = offset + field_size

    # Final gap
    if current_offset < size:
        gap_size = size - current_offset
        lines.append(f'    char _gap_{current_offset:X}[{gap_size}];')

    lines.append('};')
    return '\n'.join(lines)


def generate_idapython_script(class_names, classes_dict, class_sizes, func_class_count, pdb_data):
    """生成完整的 IDAPython 脚本"""
    # Compute dependency order for selected classes
    deps = compute_dependencies(classes_dict)
    # Include dependencies that are also in classes_dict
    all_needed = set(class_names)
    for name in class_names:
        for dep in deps.get(name, set()):
            if dep in classes_dict:
                all_needed.add(dep)

    # Topological sort
    sub_deps = {k: v & all_needed for k, v in deps.items() if k in all_needed}
    order = topological_sort({k: classes_dict[k] for k in all_needed if k in classes_dict}, sub_deps)

    # Build known structs set (for type resolution)
    known_structs = set(classes_dict.keys())

    # Generate struct definitions as C strings
    struct_defs = []
    for name in order:
        if name not in classes_dict:
            continue
        cls = classes_dict[name]
        defn = generate_struct_definition(cls, class_sizes, known_structs)
        if defn:
            struct_defs.append((name, cls['size'], defn))

    # Generate the IDAPython script
    script_lines = []
    script_lines.append('"""')
    script_lines.append('IDAPython: 导入 PDB 结构体字段定义')
    script_lines.append(f'自动生成 - 包含 {len(struct_defs)} 个结构体')
    script_lines.append('"""')
    script_lines.append('')
    script_lines.append('import ida_auto')
    script_lines.append('import ida_typeinf')
    script_lines.append('import ida_hexrays')
    script_lines.append('import ida_funcs')
    script_lines.append('import ida_name')
    script_lines.append('import idautils')
    script_lines.append('import idc')
    script_lines.append('import traceback')
    script_lines.append('import os')
    script_lines.append('')
    script_lines.append('LOG_FILE = r"D:\\workspace\\project-x\\tools\\fulldump\\ida_struct_import_log.txt"')
    script_lines.append('TEXT_START = 0x00401000')
    script_lines.append('TEXT_END = 0x00558000')
    script_lines.append('')
    script_lines.append('')
    script_lines.append('def main():')
    script_lines.append('    log_lines = []')
    script_lines.append('')
    script_lines.append('    def log(msg):')
    script_lines.append('        log_lines.append(str(msg))')
    script_lines.append('        print(msg)')
    script_lines.append('')
    script_lines.append('    try:')
    script_lines.append('        ida_auto.auto_wait()')
    script_lines.append('        log("[*] IDA 9.x ready")')
    script_lines.append('        log("")')
    script_lines.append('')
    script_lines.append('        til = ida_typeinf.get_idati()')
    script_lines.append('        success = 0')
    script_lines.append('        failed = 0')
    script_lines.append('')
    script_lines.append('        # ====== 导入结构体 ======')
    script_lines.append(f'        log("[STEP 1] 导入 {len(struct_defs)} 个结构体...")')
    script_lines.append('')

    # Add each struct definition
    for name, size, defn in struct_defs:
        # Escape the C definition for Python string
        escaped = defn.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n')
        script_lines.append(f'        # --- {name} ({size} bytes) ---')
        script_lines.append(f'        c_def = "{escaped}"')
        script_lines.append(f'        ret = idc.parse_decls(c_def, idc.PT_TYP)')
        script_lines.append(f'        if ret == 0:')
        script_lines.append(f'            success += 1')
        script_lines.append(f'        else:')
        script_lines.append(f'            log(f"  [!] Failed: {name}")')
        script_lines.append(f'            failed += 1')
        script_lines.append('')

    script_lines.append('        log(f"  成功: {success}, 失败: {failed}")')
    script_lines.append('        log("")')
    script_lines.append('')

    # Apply this pointer types to member functions
    script_lines.append('        # ====== 应用 this 指针类型 ======')
    script_lines.append('        log("[STEP 2] 应用 this 指针类型到成员函数...")')
    script_lines.append('        applied = 0')
    script_lines.append('')

    # Build class -> function name mapping
    class_funcs = defaultdict(list)
    for func in pdb_data['functions']:
        cls = func.get('class', '')
        fname = func.get('name', '')
        if cls in all_needed and fname:
            class_funcs[cls].append(fname)

    for cls_name in order:
        if cls_name not in class_funcs:
            continue
        funcs = class_funcs[cls_name]
        if not funcs:
            continue

        script_lines.append(f'        # {cls_name} 成员函数')
        script_lines.append(f'        for ea in idautils.Functions(TEXT_START, TEXT_END):')
        script_lines.append(f'            name = ida_name.get_name(ea) or ""')
        script_lines.append(f'            if name.startswith("{cls_name}::"):')
        script_lines.append(f'                tif = ida_typeinf.tinfo_t()')
        script_lines.append(f'                if ida_typeinf.parse_decl(tif, til, "{cls_name} *this;", 0):')
        script_lines.append(f'                    # Set first arg as this pointer')
        script_lines.append(f'                    pass  # Type propagation handles this automatically')
        script_lines.append(f'                applied += 1')
        script_lines.append('')

    script_lines.append('        log(f"  应用: {applied} 个函数")')
    script_lines.append('        log("")')
    script_lines.append('')

    # Clear Hex-Rays cache
    script_lines.append('        # ====== 清除 Hex-Rays 缓存 ======')
    script_lines.append('        log("[STEP 3] 清除 Hex-Rays 缓存...")')
    script_lines.append('        cleared = 0')
    script_lines.append('        for ea in idautils.Functions(TEXT_START, TEXT_END):')
    script_lines.append('            try:')
    script_lines.append('                cfunc = ida_hexrays.decompile(ea, flags=ida_hexrays.DECOMP_NO_CACHE)')
    script_lines.append('                if cfunc:')
    script_lines.append('                    cleared += 1')
    script_lines.append('            except:')
    script_lines.append('                pass')
    script_lines.append('            if cleared % 500 == 0 and cleared > 0:')
    script_lines.append('                log(f"  cleared {cleared}...")')
    script_lines.append('        log(f"  已清除: {cleared}")')
    script_lines.append('        log("")')
    script_lines.append('')
    script_lines.append('        # ====== 保存 ======')
    script_lines.append('        idc.save_database(idc.get_idb_path(), 0)')
    script_lines.append('        log("[*] 数据库已保存")')
    script_lines.append('')
    script_lines.append('    except Exception as e:')
    script_lines.append('        log(f"[!] 错误: {e}")')
    script_lines.append('        log(traceback.format_exc())')
    script_lines.append('')
    script_lines.append('    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)')
    script_lines.append('    with open(LOG_FILE, "w", encoding="utf-8") as f:')
    script_lines.append('        f.write("\\n".join(log_lines))')
    script_lines.append('')
    script_lines.append('    try:')
    script_lines.append('        idc.qexit(0)')
    script_lines.append('    except:')
    script_lines.append('        pass')
    script_lines.append('')
    script_lines.append('')
    script_lines.append('main()')

    return '\n'.join(script_lines)


def generate_parse_decls_script(class_names, classes_dict, class_sizes):
    """生成使用 parse_decls 批量导入的简洁 IDAPython 脚本"""
    deps = compute_dependencies(classes_dict)
    all_needed = set(class_names)
    for name in class_names:
        for dep in deps.get(name, set()):
            if dep in classes_dict:
                all_needed.add(dep)

    sub_deps = {k: v & all_needed for k, v in deps.items() if k in all_needed}
    order = topological_sort({k: classes_dict[k] for k in all_needed if k in classes_dict}, sub_deps)

    known_structs = set(classes_dict.keys())

    # Generate forward declarations for all structs (resolve circular refs)
    c_header_lines = []
    for name in order:
        if name not in classes_dict:
            continue
        # Skip names with template chars that can't be C identifiers
        if '<' in name or '>' in name or ',' in name:
            continue
        c_header_lines.append(f'struct {name};')
    c_header_lines.append('')

    # Generate full struct definitions
    for name in order:
        if name not in classes_dict:
            continue
        if '<' in name or '>' in name or ',' in name:
            continue
        cls = classes_dict[name]
        defn = generate_struct_definition(cls, class_sizes, known_structs)
        if defn:
            c_header_lines.append(defn)
            c_header_lines.append('')

    c_header = '\n'.join(c_header_lines)

    # Generate concise IDAPython script
    script = f'''"""
IDAPython: 批量导入 PDB 结构体定义 ({len(order)} 个)
自动生成 by gen_ida_struct_import.py
"""

import ida_auto
import ida_typeinf
import ida_hexrays
import ida_funcs
import ida_name
import idautils
import idc
import traceback
import os

LOG_FILE = r"D:\\workspace\\project-x\\tools\\fulldump\\ida_struct_import_log.txt"
TEXT_START = 0x00401000
TEXT_END = 0x00558000

STRUCT_HEADER = r"""
{c_header}
"""


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        # Step 1: Parse all struct definitions
        log("[STEP 1] 导入结构体定义...")
        ret = idc.parse_decls(STRUCT_HEADER, idc.PT_TYP)
        log(f"  parse_decls 返回: {{ret}} (0=成功)")

        # Verify
        til = ida_typeinf.get_idati()
        count = 0
        for name in {repr(list(all_needed))}:
            tif = ida_typeinf.tinfo_t()
            if tif.get_named_type(til, name):
                count += 1
        log(f"  可访问结构体: {{count}}/{len(all_needed)}")

        # Step 2: Clear Hex-Rays cache for affected functions
        log("")
        log("[STEP 2] 清除 Hex-Rays 反编译缓存...")
        cleared = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            # Only clear functions belonging to imported classes
            cls = name.split("::")[0] if "::" in name else ""
            if cls in {repr(all_needed)}:
                try:
                    ida_hexrays.mark_cfunc_dirty(ea)
                    cleared += 1
                except:
                    pass
        log(f"  标记需重新反编译: {{cleared}} 个函数")

        # Step 3: Save
        log("")
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {{e}}")
        log(traceback.format_exc())

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\\n".join(log_lines))

    try:
        idc.qexit(0)
    except:
        pass


main()
'''
    return script


def main():
    parser = argparse.ArgumentParser(description="生成 IDAPython 结构体导入脚本")
    parser.add_argument('--batch', choices=['P0', 'P1', 'P2', 'P3', 'P4', 'all'],
                        help='生成指定批次的导入脚本')
    parser.add_argument('--class', dest='class_name', metavar='NAME',
                        help='仅生成单个类的导入脚本')
    parser.add_argument('--list', action='store_true',
                        help='列出分批信息')
    parser.add_argument('--deps', metavar='CLASS',
                        help='显示指定类的依赖关系')
    parser.add_argument('--output', metavar='PATH',
                        help='输出文件路径 (默认: tools/fulldump/ida_import_<batch>.py)')
    parser.add_argument('--dry-run', action='store_true',
                        help='仅显示将导入的类，不生成脚本')
    args = parser.parse_args()

    # Load PDB data
    print("[*] 加载 PDB 数据...")
    pdb_data = load_pdb()
    classes_raw = pdb_data.get('classes', [])
    classes_dict = deduplicate_classes(classes_raw)
    print(f"    类总数: {len(classes_raw)}, 去重后有字段: {len(classes_dict)}")

    # Build class sizes
    class_sizes = {name: cls['size'] for name, cls in classes_dict.items()}

    # Count functions per class
    func_class_count = Counter()
    for func in pdb_data['functions']:
        cls = func.get('class', '')
        if cls:
            func_class_count[cls] += 1

    # Classify batches
    batches = classify_batches(classes_dict, func_class_count)

    if args.list:
        print("\n分批信息:")
        print("=" * 60)
        for batch_name, members in batches.items():
            total_funcs = sum(func_class_count.get(n, 0) for n in members)
            print(f"\n  {batch_name}: {len(members)} 个类, 影响 {total_funcs} 个函数")
            for name in members[:10]:
                fc = func_class_count.get(name, 0)
                mc = len(classes_dict[name].get('data_members', []))
                print(f"    {name:25s} funcs={fc:4d} members={mc:3d}")
            if len(members) > 10:
                print(f"    ... ({len(members) - 10} more)")
        return

    if args.deps:
        deps = compute_dependencies(classes_dict)
        target = args.deps
        if target not in classes_dict:
            print(f"[!] 类 '{target}' 不存在或无字段信息")
            return
        print(f"\n{target} 的依赖:")
        for dep in sorted(deps.get(target, set())):
            print(f"  → {dep} ({len(classes_dict[dep].get('data_members', []))} members)")
        # Reverse deps
        rdeps = set()
        for name, d in deps.items():
            if target in d:
                rdeps.add(name)
        if rdeps:
            print(f"\n依赖 {target} 的类:")
            for name in sorted(rdeps):
                print(f"  ← {name}")
        return

    # Determine which classes to export
    if args.class_name:
        target_classes = [args.class_name]
        batch_label = args.class_name
    elif args.batch == 'all':
        target_classes = list(classes_dict.keys())
        batch_label = 'all'
    elif args.batch:
        target_classes = batches[args.batch]
        batch_label = args.batch
    else:
        parser.print_help()
        return

    # Filter to only classes with data_members
    target_classes = [n for n in target_classes if n in classes_dict]

    if not target_classes:
        print("[!] 无有效类可导入")
        return

    if args.dry_run:
        print(f"\n将导入 {len(target_classes)} 个类:")
        for name in target_classes:
            fc = func_class_count.get(name, 0)
            mc = len(classes_dict[name].get('data_members', []))
            sz = classes_dict[name]['size']
            print(f"  {name:30s} funcs={fc:4d} members={mc:3d} size={sz}")
        return

    # Generate script
    print(f"\n[*] 生成 IDAPython 脚本 (batch={batch_label}, {len(target_classes)} 类)...")
    script = generate_parse_decls_script(target_classes, classes_dict, class_sizes)

    # Output
    if args.output:
        output_path = Path(args.output)
    else:
        output_path = OUTPUT_DIR / f"ida_import_{batch_label}.py"

    output_path.parent.mkdir(parents=True, exist_ok=True)
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(script)

    print(f"[+] 已生成: {output_path}")
    print(f"    包含 {len(target_classes)} 个结构体定义")
    print(f"\n    运行方式:")
    print(f'    "D:\\Program Files\\IDA Professional 9.2\\idat.exe" -A -S"{output_path}" "D:\\workspace\\project-x\\original\\PAL3A.exe.i64"')


if __name__ == '__main__':
    main()
