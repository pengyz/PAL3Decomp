#!/usr/bin/env python3
"""
PAL3.exe 编译对比工具

编译单个源文件，提取对应函数的 .obj COFF text section 字节，
与原始 PAL3.exe 中该函数的字节做对比。

用法:
    python tools/pal3_compare.py --compile src/pal3/WinMain.cpp --func WinMain --addr 0x00541900 --size 824
    python tools/pal3_compare.py --compile src/pal3/WinMain.cpp --all
    python tools/pal3_compare.py --obj build/WinMain.obj --func WinMain --addr 0x00541900 --size 824

编译器: VC6 SP0 (MSVC 12.00.8168) — 与原始 PAL3.exe Rich Header 匹配
"""

import argparse
import json
import struct
import subprocess
import sys
import os
import re
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_EXE = PROJECT_ROOT / "original" / "PAL3.exe"
VC6_ROOT = PROJECT_ROOT / "tools" / "compilers" / "msvc6.0"
VC6_BIN = VC6_ROOT / "Bin"
VC6_INCLUDE = VC6_ROOT / "Include"
VC6_LIB = PROJECT_ROOT / "tools" / "vc6" / "Lib"  # Lib from SP5 (compatible)
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
BUILD_DIR = PROJECT_ROOT / "build" / "pal3"

# PE 解析
EXE_IMAGE_BASE = 0x00400000
EXE_TEXT_VA = 0x00401000
EXE_TEXT_RAW_OFFSET = 0x1000
EXE_TEXT_SIZE = 0x1685D0


def to_winpath(path):
    """Unix 路径转 Wine Z: 盘路径"""
    return "Z:" + str(Path(path).resolve()).replace("/", "\\")


def compile_source(src_path, obj_path=None):
    """用 VC6 SP0 编译源文件到 .obj"""
    src = Path(src_path).resolve()
    if obj_path is None:
        BUILD_DIR.mkdir(parents=True, exist_ok=True)
        obj_path = BUILD_DIR / (src.stem + ".obj")
    obj = Path(obj_path).resolve()

    win_src = to_winpath(src)
    win_obj = to_winpath(obj)
    win_inc = to_winpath(VC6_INCLUDE)
    win_proj_inc = to_winpath(PROJECT_ROOT / "include")

    cmd = [
        "wine", str(VC6_BIN / "CL.EXE"), "/nologo", "/c",
        "/O2", "/Ob2", "/Oi", "/Ot", "/Oy", "/GF", "/Gy",
        "/GX", "/GR", "/MD", "/Gd",
        "/W3",
        "/DNDEBUG", "/DWIN32", "/D_WINDOWS", "/D_MBCS",
        f"/I{win_inc}", f"/I{win_proj_inc}",
        f"/Fo{win_obj}",
        f"/FAcs", f"/Fa{to_winpath(BUILD_DIR)}/",
        win_src
    ]

    env = os.environ.copy()
    env["WINEDEBUG"] = "-all"

    print(f"编译: {src.name} -> {obj.name}")
    result = subprocess.run(cmd, capture_output=True, text=True, env=env)

    if result.returncode != 0:
        print(f"编译失败!")
        print(result.stdout)
        print(result.stderr)
        return None

    if result.stdout.strip():
        # 过滤掉文件名行
        for line in result.stdout.strip().split('\n'):
            if not line.strip().endswith('.cpp') and not line.strip().endswith('.c'):
                print(f"  {line}")

    return obj


def parse_coff_obj(obj_path):
    """从 COFF .obj 文件提取函数 (section name -> bytes)"""
    with open(obj_path, 'rb') as f:
        data = f.read()

    # COFF header
    machine = struct.unpack_from('<H', data, 0)[0]
    num_sections = struct.unpack_from('<H', data, 2)[0]
    sym_table_off = struct.unpack_from('<I', data, 8)[0]
    num_symbols = struct.unpack_from('<I', data, 12)[0]
    opt_header_size = struct.unpack_from('<H', data, 16)[0]

    sec_start = 20 + opt_header_size
    sections = []
    for i in range(num_sections):
        off = sec_start + i * 40
        name_bytes = data[off:off + 8]
        if name_bytes[0:1] == b'/':
            # 长名称 - 从字符串表获取
            strtab_off = sym_table_off + num_symbols * 18
            name_off = int(name_bytes[1:8].rstrip(b'\x00').decode())
            end = data.find(b'\x00', strtab_off + name_off)
            name = data[strtab_off + name_off:end].decode()
        else:
            name = name_bytes.rstrip(b'\x00').decode()

        vsize = struct.unpack_from('<I', data, off + 8)[0]
        raw_off = struct.unpack_from('<I', data, off + 20)[0]
        raw_size = struct.unpack_from('<I', data, off + 16)[0]
        nrelocs = struct.unpack_from('<H', data, off + 32)[0]
        chars = struct.unpack_from('<I', data, off + 36)[0]

        sec_data = data[raw_off:raw_off + raw_size] if raw_off > 0 and raw_size > 0 else b''
        sections.append({
            'index': i + 1,
            'name': name,
            'vsize': vsize,
            'raw_size': raw_size,
            'data': sec_data,
            'nrelocs': nrelocs,
            'chars': chars
        })

    # 解析符号表找到函数和它们所在的 section
    functions = {}
    strtab_off = sym_table_off + num_symbols * 18

    i = 0
    while i < num_symbols:
        sym_off = sym_table_off + i * 18
        name_field = data[sym_off:sym_off + 8]
        if struct.unpack_from('<I', name_field, 0)[0] == 0:
            # 长名称
            str_off = struct.unpack_from('<I', name_field, 4)[0]
            end = data.find(b'\x00', strtab_off + str_off)
            sym_name = data[strtab_off + str_off:end].decode('ascii', errors='replace')
        else:
            sym_name = name_field.rstrip(b'\x00').decode('ascii', errors='replace')

        value = struct.unpack_from('<I', data, sym_off + 8)[0]
        sec_num = struct.unpack_from('<h', data, sym_off + 12)[0]
        sym_type = struct.unpack_from('<H', data, sym_off + 14)[0]
        storage_class = data[sym_off + 16]
        aux_count = data[sym_off + 17]

        # 外部函数定义 (storage_class==2, sec_num>0, type==0x20 表示函数)
        if storage_class == 2 and sec_num > 0 and (sym_type & 0x20):
            sec = sections[sec_num - 1]
            if sec['chars'] & 0x20:  # IMAGE_SCN_CNT_CODE
                functions[sym_name] = {
                    'section': sec_num,
                    'offset': value,
                    'section_name': sec['name']
                }

        i += 1 + aux_count

    return sections, functions


def get_function_bytes_from_obj(obj_path, func_name=None):
    """从 .obj 提取函数字节。如果 func_name 为 None，返回所有 .text 字节"""
    sections, functions = parse_coff_obj(obj_path)

    # 找到所有 code section
    code_sections = [s for s in sections if s['chars'] & 0x20]

    if func_name:
        # 查找特定函数 (支持部分匹配)
        matches = []
        for name, info in functions.items():
            if func_name in name or func_name == name:
                matches.append((name, info))

        if not matches:
            print(f"  未找到函数 '{func_name}'")
            print(f"  可用函数:")
            for name in sorted(functions.keys()):
                print(f"    {name}")
            return None, None

        if len(matches) > 1:
            print(f"  多个匹配 '{func_name}':")
            for name, _ in matches:
                print(f"    {name}")
            # 用最短的
            matches.sort(key=lambda x: len(x[0]))

        name, info = matches[0]
        sec = sections[info['section'] - 1]
        # 对于 /Gy (函数级链接)，每个函数在独立 section
        return name, sec['data']
    else:
        # 返回所有 code sections
        result = {}
        for name, info in functions.items():
            sec = sections[info['section'] - 1]
            result[name] = sec['data']
        return None, result


def get_original_bytes(address, size):
    """从原始 PAL3.exe 提取指定地址的字节"""
    file_offset = address - EXE_IMAGE_BASE - (EXE_TEXT_VA - EXE_IMAGE_BASE) + EXE_TEXT_RAW_OFFSET
    with open(ORIGINAL_EXE, 'rb') as f:
        f.seek(file_offset)
        return f.read(size)


def compare_bytes(original, compiled, func_name="", verbose=True):
    """字节对比，返回匹配率"""
    if original is None or compiled is None:
        return 0.0

    min_len = min(len(original), len(compiled))
    max_len = max(len(original), len(compiled))

    matches = 0
    diffs = []
    for i in range(min_len):
        if original[i] == compiled[i]:
            matches += 1
        else:
            diffs.append(i)

    match_rate = matches / max_len * 100 if max_len > 0 else 0

    if verbose:
        size_note = ""
        if len(original) != len(compiled):
            size_note = f" (大小不匹配: 原始={len(original)}, 编译={len(compiled)})"

        if match_rate == 100.0:
            print(f"  ✓ {func_name}: 完全匹配! ({len(original)} bytes){size_note}")
        else:
            print(f"  ✗ {func_name}: {match_rate:.1f}% ({matches}/{max_len} bytes){size_note}")
            if len(diffs) <= 20:
                for off in diffs[:10]:
                    print(f"      offset 0x{off:04X}: 原始=0x{original[off]:02X} 编译=0x{compiled[off]:02X}")
                if len(diffs) > 10:
                    print(f"      ... 还有 {len(diffs)-10} 处差异")

    return match_rate


def load_function_map():
    """加载 decomp 目录中的函数信息 (地址 -> 函数名+大小)"""
    func_map = {}
    if not DECOMP_DIR.exists():
        return func_map

    for f in DECOMP_DIR.iterdir():
        if not f.suffix == '.json':
            continue
        try:
            with open(f) as fp:
                data = json.load(fp)
            addr = int(data['address'], 16)
            func_map[data['name']] = {
                'address': addr,
                'size': data['size_bytes'],
                'file': f.name
            }
        except (json.JSONDecodeError, KeyError, ValueError):
            pass

    return func_map


def main():
    parser = argparse.ArgumentParser(description='PAL3.exe 编译对比工具')
    parser.add_argument('--compile', help='要编译的源文件')
    parser.add_argument('--obj', help='已编译的 .obj 文件')
    parser.add_argument('--func', help='要对比的函数名 (支持部分匹配)')
    parser.add_argument('--addr', help='函数在原始 EXE 中的地址 (如 0x00541900)')
    parser.add_argument('--size', type=int, help='函数大小 (字节)')
    parser.add_argument('--all', action='store_true', help='对比 obj 中所有函数')
    parser.add_argument('--list', action='store_true', help='列出 obj 中的函数')
    args = parser.parse_args()

    # 编译
    obj_path = None
    if args.compile:
        obj_path = compile_source(args.compile)
        if obj_path is None:
            sys.exit(1)
    elif args.obj:
        obj_path = Path(args.obj)
        if not obj_path.exists():
            print(f"错误: 文件不存在: {obj_path}")
            sys.exit(1)
    else:
        parser.print_help()
        sys.exit(1)

    # 列出函数
    if args.list:
        sections, functions = parse_coff_obj(obj_path)
        print(f"\n{obj_path.name} 中的函数:")
        for name, info in sorted(functions.items()):
            sec = sections[info['section'] - 1]
            print(f"  {name} ({sec['raw_size']} bytes)")
        return

    # 加载函数映射
    func_map = load_function_map()

    if args.all:
        # 对比所有函数
        sections, functions = parse_coff_obj(obj_path)
        total = 0
        matched = 0
        results = []

        for sym_name, info in functions.items():
            sec = sections[info['section'] - 1]
            compiled_bytes = sec['data']

            # 从 decomp 数据中查找对应地址和大小
            # 尝试去掉前导下划线和@后缀匹配
            found = None
            for map_name, map_info in func_map.items():
                # 简单匹配: mangled name 包含函数名
                clean = sym_name.lstrip('_').split('@')[0]
                if clean and clean in map_name:
                    found = map_info
                    break

            if found:
                orig_bytes = get_original_bytes(found['address'], found['size'])
                rate = compare_bytes(orig_bytes, compiled_bytes, sym_name, verbose=True)
                results.append((sym_name, rate))
                total += 1
                if rate == 100.0:
                    matched += 1
            else:
                print(f"  ? {sym_name}: 未找到原始地址映射")

        if total > 0:
            print(f"\n总计: {matched}/{total} 函数完全匹配")
    elif args.func and args.addr and args.size:
        # 对比指定函数
        addr = int(args.addr, 16) if isinstance(args.addr, str) else args.addr
        name, compiled_bytes = get_function_bytes_from_obj(obj_path, args.func)
        if compiled_bytes is None:
            sys.exit(1)

        orig_bytes = get_original_bytes(addr, args.size)
        compare_bytes(orig_bytes, compiled_bytes, name or args.func)
    elif args.func:
        # 从 func_map 查找地址
        name, compiled_bytes = get_function_bytes_from_obj(obj_path, args.func)
        if compiled_bytes is None:
            sys.exit(1)

        # 尝试从 func_map 找地址
        found = None
        for map_name, map_info in func_map.items():
            if args.func in map_name:
                found = map_info
                break

        if found:
            orig_bytes = get_original_bytes(found['address'], found['size'])
            compare_bytes(orig_bytes, compiled_bytes, name or args.func)
        else:
            print(f"  未找到 '{args.func}' 的原始地址，请用 --addr --size 指定")
            sys.exit(1)
    else:
        print("请指定 --func 或 --all")
        sys.exit(1)


if __name__ == '__main__':
    main()
