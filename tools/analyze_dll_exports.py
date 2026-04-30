#!/usr/bin/env python3
"""
分析 gbengine.dll / topo.dll 的导出表。

这些 DLL 没有加壳，导出函数名是 C++ mangled names，
可以还原为类名、方法名和参数类型——这是极有价值的逆向信息。

用法：
    python analyze_dll_exports.py                # 分析所有目标 DLL
    python analyze_dll_exports.py gbengine.dll   # 分析指定 DLL
    python analyze_dll_exports.py --demangle     # 尝试 demangle C++ 名称
"""

import argparse
import json
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
sys.path.insert(0, str(Path(__file__).parent))
from project_config import get_game_dir, get_dll_path

# 我们的反编译目标 DLL
TARGET_DLLS = ['gbengine.dll', 'topo.dll']


def parse_pe_exports(data):
    """解析 PE 文件的导出表，返回导出函数列表"""
    # DOS header
    pe_offset = struct.unpack_from('<I', data, 0x3C)[0]
    sig = data[pe_offset:pe_offset+4]
    if sig != b'PE\x00\x00':
        return None, "Not a valid PE file"

    # COFF header
    num_sections = struct.unpack_from('<H', data, pe_offset + 6)[0]
    opt_header_size = struct.unpack_from('<H', data, pe_offset + 20)[0]

    # Optional header
    opt_start = pe_offset + 24
    opt_magic = struct.unpack_from('<H', data, opt_start)[0]
    image_base = struct.unpack_from('<I', data, opt_start + 28)[0]

    # Data directories - Export table is the first entry
    # In PE32, data directories start at offset 96 from optional header start
    num_data_dirs = struct.unpack_from('<I', data, opt_start + 92)[0]
    export_rva = struct.unpack_from('<I', data, opt_start + 96)[0]
    export_size = struct.unpack_from('<I', data, opt_start + 100)[0]

    if export_rva == 0:
        return None, "No export table"

    # Read section headers to build RVA -> file offset mapping
    sections_start = opt_start + opt_header_size
    sections = []
    for i in range(num_sections):
        offset = sections_start + i * 40
        name = data[offset:offset+8].rstrip(b'\x00').decode('ascii', errors='ignore')
        vsize = struct.unpack_from('<I', data, offset + 8)[0]
        va = struct.unpack_from('<I', data, offset + 12)[0]
        raw_size = struct.unpack_from('<I', data, offset + 16)[0]
        raw_ptr = struct.unpack_from('<I', data, offset + 20)[0]
        sections.append({
            'name': name, 'va': va, 'vsize': vsize,
            'raw_ptr': raw_ptr, 'raw_size': raw_size
        })

    def rva_to_offset(rva):
        for sec in sections:
            if sec['va'] <= rva < sec['va'] + sec['raw_size']:
                return sec['raw_ptr'] + (rva - sec['va'])
        return None

    def read_string(rva):
        off = rva_to_offset(rva)
        if off is None:
            return ""
        end = data.index(b'\x00', off)
        return data[off:end].decode('ascii', errors='replace')

    # Parse IMAGE_EXPORT_DIRECTORY
    exp_off = rva_to_offset(export_rva)
    if exp_off is None:
        return None, "Cannot resolve export table RVA"

    # IMAGE_EXPORT_DIRECTORY fields
    characteristics = struct.unpack_from('<I', data, exp_off)[0]
    timestamp = struct.unpack_from('<I', data, exp_off + 4)[0]
    major_ver = struct.unpack_from('<H', data, exp_off + 8)[0]
    minor_ver = struct.unpack_from('<H', data, exp_off + 10)[0]
    name_rva = struct.unpack_from('<I', data, exp_off + 12)[0]
    ordinal_base = struct.unpack_from('<I', data, exp_off + 16)[0]
    num_functions = struct.unpack_from('<I', data, exp_off + 20)[0]
    num_names = struct.unpack_from('<I', data, exp_off + 24)[0]
    addr_table_rva = struct.unpack_from('<I', data, exp_off + 28)[0]
    name_table_rva = struct.unpack_from('<I', data, exp_off + 32)[0]
    ordinal_table_rva = struct.unpack_from('<I', data, exp_off + 36)[0]

    dll_name = read_string(name_rva)

    # Read name pointer table
    name_table_off = rva_to_offset(name_table_rva)
    ordinal_table_off = rva_to_offset(ordinal_table_rva)
    addr_table_off = rva_to_offset(addr_table_rva)

    exports = []
    for i in range(num_names):
        # Name RVA
        name_ptr_rva = struct.unpack_from('<I', data, name_table_off + i * 4)[0]
        func_name = read_string(name_ptr_rva)

        # Ordinal (index into address table)
        ordinal_idx = struct.unpack_from('<H', data, ordinal_table_off + i * 2)[0]
        ordinal = ordinal_base + ordinal_idx

        # Function RVA
        func_rva = struct.unpack_from('<I', data, addr_table_off + ordinal_idx * 4)[0]

        exports.append({
            'name': func_name,
            'ordinal': ordinal,
            'rva': func_rva,
            'va': image_base + func_rva,
        })

    info = {
        'dll_name': dll_name,
        'image_base': image_base,
        'num_functions': num_functions,
        'num_names': num_names,
        'ordinal_base': ordinal_base,
        'sections': sections,
        'exports': exports,
    }

    return info, None


def demangle_msvc(name):
    """
    简单的 MSVC C++ name demangling。

    完整的 demangle 需要 undname.exe 或 c++filt，
    这里做基本的模式识别。
    """
    if not name.startswith('?'):
        return name  # 不是 mangled name

    # 基本格式: ?method@class@@access_type...
    parts = name.split('@')
    if len(parts) < 3:
        return name

    method = parts[0][1:]  # 去掉 '?'
    class_name = parts[1]

    # 特殊名称
    special_names = {
        '?0': '(constructor)',
        '?1': '(destructor)',
        '?4': 'operator=',
        '?H': 'operator+',
        '?G': 'operator-',
        '?D': 'operator*',
        '?K': 'operator/',
    }

    if parts[0] in special_names:
        method = special_names[parts[0]]

    return "{}::{}".format(class_name, method)


def try_system_demangle(names):
    """尝试使用系统的 c++filt 进行 demangle"""
    import subprocess
    try:
        # c++filt 默认用 itanium ABI，但用 -n 可以处理部分 MSVC 名称
        # 实际上对 MSVC 的 mangled names 不太管用，但值得尝试
        input_text = '\n'.join(names)
        result = subprocess.run(
            ['c++filt', '-n'], input=input_text,
            capture_output=True, text=True, timeout=10)
        if result.returncode == 0:
            return result.stdout.strip().split('\n')
    except (FileNotFoundError, subprocess.TimeoutExpired):
        pass
    return None


def analyse_dll(dll_path, do_demangle=False):
    """分析单个 DLL 的导出表"""
    print("分析: {}".format(dll_path))
    print("=" * 60)

    with open(dll_path, 'rb') as f:
        data = f.read()

    print("文件大小: {:,} bytes".format(len(data)))

    info, error = parse_pe_exports(data)
    if error:
        print("[!] {}".format(error))
        return None

    print("DLL 名称: {}".format(info['dll_name']))
    print("Image Base: 0x{:08X}".format(info['image_base']))
    print("导出函数: {} 个 (named: {})".format(
        info['num_functions'], info['num_names']))
    print("Ordinal Base: {}".format(info['ordinal_base']))
    print()

    # 分析命名模式
    cpp_names = []
    c_names = []
    for exp in info['exports']:
        if exp['name'].startswith('?'):
            cpp_names.append(exp)
        else:
            c_names.append(exp)

    print("命名统计:")
    print("  C++ mangled: {} 个".format(len(cpp_names)))
    print("  C/plain:     {} 个".format(len(c_names)))

    # 提取类名
    classes = {}
    for exp in cpp_names:
        parts = exp['name'].split('@')
        if len(parts) >= 3:
            class_name = parts[1]
            if class_name not in classes:
                classes[class_name] = []
            classes[class_name].append(exp['name'])

    print("  识别的类: {} 个".format(len(classes)))
    print()

    # 按类统计并打印前 20 个最大的类
    class_sizes = sorted(classes.items(), key=lambda x: -len(x[1]))
    print("Top 20 类（按方法数）:")
    for class_name, methods in class_sizes[:20]:
        print("  {:30s}  {} 个方法".format(class_name, len(methods)))

    if c_names:
        print()
        print("C/plain 导出函数:")
        for exp in c_names[:20]:
            print("  {:50s}  RVA=0x{:08X}".format(exp['name'], exp['rva']))
        if len(c_names) > 20:
            print("  ... 还有 {} 个".format(len(c_names) - 20))

    # Demangle
    if do_demangle:
        print()
        print("--- Demangled 名称（基本解析）---")
        for exp in info['exports'][:50]:
            demangled = demangle_msvc(exp['name'])
            if demangled != exp['name']:
                print("  {} → {}".format(exp['name'][:60], demangled))

    return info


def save_exports(info, output_name):
    """保存导出表为 JSON"""
    output_dir = PROJECT_ROOT / "build"
    output_dir.mkdir(parents=True, exist_ok=True)

    # 提取类信息
    classes = {}
    for exp in info['exports']:
        if exp['name'].startswith('?'):
            parts = exp['name'].split('@')
            if len(parts) >= 3:
                class_name = parts[1]
                if class_name not in classes:
                    classes[class_name] = {
                        'methods': [],
                        'method_count': 0,
                    }
                classes[class_name]['methods'].append({
                    'mangled': exp['name'],
                    'rva': exp['rva'],
                    'ordinal': exp['ordinal'],
                })
                classes[class_name]['method_count'] = len(classes[class_name]['methods'])

    result = {
        'dll_name': info['dll_name'],
        'image_base': info['image_base'],
        'num_exports': info['num_names'],
        'classes': classes,
        'plain_exports': [
            e for e in info['exports'] if not e['name'].startswith('?')
        ],
    }

    output_path = output_dir / "{}_exports.json".format(output_name)
    with open(output_path, 'w') as f:
        json.dump(result, f, indent=2, default=str)
    print()
    print("导出表已保存: {}".format(output_path))
    return output_path


def main():
    parser = argparse.ArgumentParser(
        description="分析 DLL 导出表（gbengine.dll, topo.dll）")
    parser.add_argument('dll_name', nargs='?',
                        help='要分析的 DLL 名称（默认分析所有目标 DLL）')
    parser.add_argument('--demangle', action='store_true',
                        help='尝试 demangle C++ 名称')
    parser.add_argument('--save', action='store_true', default=True,
                        help='保存结果为 JSON（默认开启）')
    args = parser.parse_args()

    if args.dll_name:
        dlls = [args.dll_name]
    else:
        dlls = TARGET_DLLS

    game_dir = get_game_dir()
    if game_dir is None:
        print("[!] 未配置游戏目录，请编辑 local_config.json")
        sys.exit(1)

    for dll_name in dlls:
        dll_path = get_dll_path(dll_name)
        if dll_path is None:
            print("[!] 未找到: {}".format(dll_name))
            continue

        info = analyse_dll(dll_path, do_demangle=args.demangle)
        if info and args.save:
            save_exports(info, dll_name.replace('.dll', ''))

        print()


if __name__ == '__main__':
    main()
