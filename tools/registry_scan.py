#!/usr/bin/env python3
"""
gbengine 函数注册表 - 字节扫描匹配工具

对于 IDA 中的 sub_XXXXXXXX (unknown) 函数，通过字节比对找到对应的编译符号。

原理:
  1. 从原始 gbengine.dll 读取每个 sub_ 函数的字节
  2. 从我们编译的 .obj 文件中提取每个函数的字节 (跳过重定位)
  3. 比对字节，匹配率 >= 90% 视为同一个函数
  4. 根据 obj 来源确定状态:
     - d3dx9:*.obj → not_needed (D3DX9 静态库)
     - LIBCMT:*.obj → not_needed (CRT)
     - *.cpp.obj → done (我们的实现)

这是一次性的高成本操作，结果写入 registry。

用法:
    python tools/registry_scan.py                  # 扫描并更新 registry
    python tools/registry_scan.py --dry-run        # 不写入，仅报告匹配结果
    python tools/registry_scan.py --threshold 0.95 # 设置匹配阈值 (默认 0.90)
"""

import json
import struct
import re
import sys
import os
import glob
from pathlib import Path
from collections import defaultdict

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_DLL = PROJECT_ROOT / "original" / "gbengine.dll"
IDA_DIR = PROJECT_ROOT / "asm" / "gbengine_ida"
SRC_DIR = PROJECT_ROOT / "src" / "gbengine"
MAP_FILE = PROJECT_ROOT / "build" / "gbengine.map"
REGISTRY_FILE = PROJECT_ROOT / "data" / "gbengine_registry.jsonl"
BUILD_DIR = PROJECT_ROOT / "build"

# obj 文件可能的位置 (编译产物)
OBJ_DIRS = [
    PROJECT_ROOT / "tools" / "vc6",
    BUILD_DIR,
]


def get_dll_text_section(dll_path):
    """Parse PE header to find .text section."""
    with open(dll_path, 'rb') as f:
        f.seek(0x3C)
        pe_offset = struct.unpack('<I', f.read(4))[0]
        f.seek(pe_offset + 4)  # skip PE sig
        f.read(2)  # machine
        num_sections = struct.unpack('<H', f.read(2))[0]
        f.read(12)
        opt_hdr_size = struct.unpack('<H', f.read(2))[0]
        f.read(2)
        f.seek(pe_offset + 4 + 20 + opt_hdr_size)

        for i in range(num_sections):
            name = f.read(8).rstrip(b'\x00').decode('ascii', errors='replace')
            virt_size = struct.unpack('<I', f.read(4))[0]
            virt_addr = struct.unpack('<I', f.read(4))[0]
            raw_size = struct.unpack('<I', f.read(4))[0]
            raw_offset = struct.unpack('<I', f.read(4))[0]
            f.read(16)
            if name == '.text':
                return {
                    'virt_addr': virt_addr,
                    'virt_size': virt_size,
                    'raw_offset': raw_offset,
                    'raw_size': raw_size,
                }
    return None


def read_dll_function(dll_path, text_section, rva, size):
    """Read function bytes from DLL at RVA."""
    file_offset = rva - text_section['virt_addr'] + text_section['raw_offset']
    with open(dll_path, 'rb') as f:
        f.seek(file_offset)
        return f.read(size)


def parse_coff_obj(obj_path):
    """Parse COFF .obj, return functions with bytes and relocs."""
    with open(obj_path, 'rb') as f:
        data = f.read()

    if len(data) < 20:
        return {}

    machine = struct.unpack_from('<H', data, 0)[0]
    if machine not in (0x14c, 0):  # i386 or unknown
        return {}

    num_sections = struct.unpack_from('<H', data, 2)[0]
    sym_table_offset = struct.unpack_from('<I', data, 8)[0]
    num_symbols = struct.unpack_from('<I', data, 12)[0]
    opt_hdr_size = struct.unpack_from('<H', data, 16)[0]

    # Parse sections
    sections = []
    sec_offset = 20 + opt_hdr_size
    for i in range(num_sections):
        if sec_offset + 40 > len(data):
            break
        name_bytes = data[sec_offset:sec_offset+8]
        raw_size = struct.unpack_from('<I', data, sec_offset+16)[0]
        raw_offset = struct.unpack_from('<I', data, sec_offset+20)[0]
        reloc_offset = struct.unpack_from('<I', data, sec_offset+24)[0]
        num_relocs = struct.unpack_from('<H', data, sec_offset+32)[0]
        characteristics = struct.unpack_from('<I', data, sec_offset+36)[0]

        sec_data = data[raw_offset:raw_offset+raw_size] if raw_offset > 0 else b''

        # Parse relocations
        relocs = set()
        if num_relocs > 0 and reloc_offset > 0:
            for r in range(num_relocs):
                roff = reloc_offset + r * 10
                if roff + 10 > len(data):
                    break
                r_vaddr = struct.unpack_from('<I', data, roff)[0]
                for b in range(4):
                    relocs.add(r_vaddr + b)

        sections.append({
            'data': sec_data,
            'raw_size': raw_size,
            'characteristics': characteristics,
            'relocs': relocs,
        })
        sec_offset += 40

    # Parse symbols
    if sym_table_offset == 0:
        return {}

    str_table_offset = sym_table_offset + num_symbols * 18
    functions = {}

    i = 0
    while i < num_symbols:
        sym_offset = sym_table_offset + i * 18
        if sym_offset + 18 > len(data):
            break

        name_field = data[sym_offset:sym_offset+8]
        value = struct.unpack_from('<I', data, sym_offset+8)[0]
        sec_num = struct.unpack_from('<h', data, sym_offset+12)[0]
        sym_type = struct.unpack_from('<H', data, sym_offset+14)[0]
        storage_class = data[sym_offset+16]
        num_aux = data[sym_offset+17]

        # Decode name
        if name_field[0:4] == b'\x00\x00\x00\x00':
            str_off = struct.unpack_from('<I', name_field, 4)[0]
            end = data.index(b'\x00', str_table_offset + str_off)
            sym_name = data[str_table_offset + str_off:end].decode('ascii', errors='replace')
        else:
            sym_name = name_field.rstrip(b'\x00').decode('ascii', errors='replace')

        # EXTERNAL function in code section
        if (sec_num > 0 and sec_num <= len(sections) and
            storage_class == 2 and (sym_type & 0x20)):
            sec_idx = sec_num - 1
            sec = sections[sec_idx]
            if sec['characteristics'] & 0x20:  # IMAGE_SCN_CNT_CODE
                # Get function size (to end of section for COMDAT)
                func_size = sec['raw_size'] - value
                func_bytes = sec['data'][value:value+func_size]
                # Adjust relocs relative to function start
                func_relocs = set()
                for r in sec['relocs']:
                    rel_off = r - value
                    if 0 <= rel_off < func_size:
                        func_relocs.add(rel_off)

                functions[sym_name] = {
                    'bytes': func_bytes,
                    'size': func_size,
                    'relocs': func_relocs,
                }

        i += 1 + num_aux

    return functions


def compare_bytes_fuzzy(original, compiled, threshold=0.90):
    """Compare bytes, skipping likely relocation positions (4-byte address-like values).

    Strategy: when bytes differ at position i, check if positions i..i+3 all differ
    and look like an absolute address (0x10xxxxxx pattern). If so, skip as relocation.

    Returns match ratio (0.0 - 1.0).
    """
    if not original or not compiled:
        return 0.0

    # Must be same size
    if len(original) != len(compiled):
        return 0.0

    size = len(original)
    if size == 0:
        return 0.0

    matches = 0
    i = 0
    while i < size:
        if original[i] == compiled[i]:
            matches += 1
            i += 1
        else:
            # Check if this is a 4-byte relocation (address difference)
            if i + 3 < size:
                # Both look like absolute addresses (0x10xxxxxx range)?
                orig_val = struct.unpack_from('<I', original, i)[0] if i + 4 <= size else 0
                comp_val = struct.unpack_from('<I', compiled, i)[0] if i + 4 <= size else 0
                if (0x10000000 <= orig_val <= 0x10200000 and
                    0x10000000 <= comp_val <= 0x10200000):
                    matches += 4  # skip as relocation
                    i += 4
                    continue
            i += 1

    return matches / size


def load_registry():
    """Load registry."""
    entries = []
    with open(REGISTRY_FILE) as f:
        for line in f:
            if line.strip():
                entries.append(json.loads(line))
    return entries


def save_registry(entries):
    """Save registry."""
    with open(REGISTRY_FILE, 'w') as f:
        for entry in entries:
            clean = {k: v for k, v in entry.items() if v is not None}
            f.write(json.dumps(clean, ensure_ascii=False) + "\n")


def main():
    import argparse
    parser = argparse.ArgumentParser(description="字节扫描匹配 sub_ 函数")
    parser.add_argument("--dry-run", action="store_true", help="不写入，仅报告")
    parser.add_argument("--threshold", type=float, default=0.90, help="匹配阈值 (默认 0.90)")
    parser.add_argument("--limit", type=int, help="最多处理 N 个 unknown 函数")
    args = parser.parse_args()

    # Check prerequisites
    if not ORIGINAL_DLL.exists():
        print(f"错误: 原始 DLL 不存在: {ORIGINAL_DLL}", file=sys.stderr)
        sys.exit(1)
    if not REGISTRY_FILE.exists():
        print(f"错误: 注册表不存在，请先运行 registry_init.py", file=sys.stderr)
        sys.exit(1)

    # Load DLL .text section
    print("加载原始 DLL...", file=sys.stderr)
    text_section = get_dll_text_section(ORIGINAL_DLL)
    if not text_section:
        print("错误: 无法找到 .text 段", file=sys.stderr)
        sys.exit(1)
    print(f"  .text: VA=0x{text_section['virt_addr']:X}, "
          f"size={text_section['virt_size']} bytes", file=sys.stderr)

    # Parse map file to know obj -> category
    print("解析 map 文件...", file=sys.stderr)
    map_obj_for_symbol = {}  # mangled -> obj_name
    with open(MAP_FILE) as f:
        in_publics = False
        for line in f:
            if "Publics by Value" in line:
                in_publics = True
                continue
            if in_publics and line.strip():
                m = re.match(r"\s+\w+:\w+\s+(\S+)\s+([\da-fA-F]+)\s+f\s+(\S+)", line)
                if m:
                    map_obj_for_symbol[m.group(1)] = m.group(3)

    # Collect compiled function bytes from OUR built DLL + map file
    # Strategy: map gives us (mangled, our_addr, obj), read bytes from our DLL at our_addr
    print("从编译产物 DLL 收集函数字节...", file=sys.stderr)
    OUR_DLL = BUILD_DIR / "gbengine.dll"
    if not OUR_DLL.exists():
        print(f"错误: 编译产物不存在: {OUR_DLL}", file=sys.stderr)
        sys.exit(1)

    our_text = get_dll_text_section(OUR_DLL)
    if not our_text:
        print("错误: 无法解析编译产物 .text 段", file=sys.stderr)
        sys.exit(1)

    # Sort map symbols by address to calculate sizes
    map_entries = []  # (addr, mangled, obj)
    for mangled, obj in map_obj_for_symbol.items():
        # Re-parse to get address
        pass

    # Re-parse map file with addresses
    map_funcs = []  # (addr_int, mangled, obj)
    with open(MAP_FILE) as f:
        in_publics = False
        for line in f:
            if "Publics by Value" in line:
                in_publics = True
                continue
            if in_publics and line.strip():
                m = re.match(r"\s+\w+:\w+\s+(\S+)\s+([\da-fA-F]+)\s+f\s+(\S+)", line)
                if m:
                    mangled = m.group(1)
                    addr = int(m.group(2), 16)
                    obj = m.group(3)
                    map_funcs.append((addr, mangled, obj))

    map_funcs.sort(key=lambda x: x[0])

    # Calculate function sizes from adjacent addresses
    compiled_funcs = {}  # mangled -> {bytes, size, obj}
    OUR_BASE = 0x10000000

    with open(OUR_DLL, 'rb') as dll_f:
        for i, (addr, mangled, obj) in enumerate(map_funcs):
            # Calculate size from next function
            if i + 1 < len(map_funcs):
                next_addr = map_funcs[i + 1][0]
                size = next_addr - addr
            else:
                size = 64  # last function, guess

            if size <= 0 or size > 50000:
                continue

            rva = addr - OUR_BASE
            if rva < our_text['virt_addr'] or rva >= our_text['virt_addr'] + our_text['virt_size']:
                continue

            file_offset = rva - our_text['virt_addr'] + our_text['raw_offset']
            dll_f.seek(file_offset)
            func_bytes = dll_f.read(size)

            compiled_funcs[mangled] = {
                'bytes': func_bytes,
                'size': size,
                'obj': obj,
            }

    print(f"  {len(compiled_funcs)} 个已编译函数 (有字节数据)", file=sys.stderr)

    # Build size index for quick lookup (exact size match required for efficiency)
    by_size = defaultdict(list)
    for mangled, info in compiled_funcs.items():
        by_size[info['size']].append(mangled)
    print(f"  大小索引: {len(by_size)} 个不同大小值", file=sys.stderr)

    # Load registry, find unknown functions
    entries = load_registry()
    unknowns = [e for e in entries if e.get("status") == "unknown"]
    print(f"  {len(unknowns)} 个 unknown 函数待扫描", file=sys.stderr)

    if args.limit:
        unknowns = unknowns[:args.limit]

    # Scan each unknown function
    matched_count = 0
    d3dx_count = 0
    crt_count = 0
    our_count = 0
    results = {}  # addr -> (mangled, obj, ratio)

    DLL_BASE = 0x10000000

    print(f"\n开始字节扫描 (阈值={args.threshold:.0%})...", file=sys.stderr)
    for i, entry in enumerate(unknowns):
        addr = int(entry["addr"], 16)
        size = entry["size"]
        if size <= 0 or size > 50000:
            continue

        # Read original bytes
        rva = addr - DLL_BASE
        if rva < text_section['virt_addr'] or rva >= text_section['virt_addr'] + text_section['virt_size']:
            continue

        try:
            orig_bytes = read_dll_function(ORIGINAL_DLL, text_section, rva, size)
        except Exception:
            continue

        # Find candidates with same size (±4 bytes)
        candidates = []
        for s in range(size - 4, size + 5):
            if s in by_size:
                candidates.extend(by_size[s])

        # Compare with each candidate
        best_match = None
        best_ratio = 0.0

        for mangled in candidates:
            info = compiled_funcs[mangled]
            ratio = compare_bytes_fuzzy(orig_bytes, info['bytes'], args.threshold)
            if ratio > best_ratio:
                best_ratio = ratio
                best_match = mangled

        if best_ratio >= args.threshold and best_match:
            obj = compiled_funcs[best_match]['obj']
            results[entry["addr"]] = (best_match, obj, best_ratio)
            matched_count += 1

            if obj.startswith('d3dx9:'):
                d3dx_count += 1
            elif obj.startswith('LIBCMT:'):
                crt_count += 1
            elif obj.endswith('.cpp.obj'):
                our_count += 1

        if (i + 1) % 200 == 0:
            print(f"  进度: {i+1}/{len(unknowns)}, 匹配: {matched_count}", file=sys.stderr)

    print(f"\n扫描完成:", file=sys.stderr)
    print(f"  总扫描: {len(unknowns)}", file=sys.stderr)
    print(f"  匹配成功: {matched_count}", file=sys.stderr)
    print(f"    D3DX9: {d3dx_count}", file=sys.stderr)
    print(f"    LIBCMT: {crt_count}", file=sys.stderr)
    print(f"    我们的代码: {our_count}", file=sys.stderr)
    print(f"    其他: {matched_count - d3dx_count - crt_count - our_count}", file=sys.stderr)

    if args.dry_run:
        print("\n(dry-run 模式, 未写入)")
        # Show some matches
        print("\n示例匹配 (前20):")
        shown = 0
        for addr_str, (mangled, obj, ratio) in sorted(results.items()):
            print(f"  {addr_str} → {mangled[:50]} [{obj}] ({ratio:.1%})")
            shown += 1
            if shown >= 20:
                break
        return

    # Update registry
    addr_map = {e["addr"]: e for e in entries}
    for addr_str, (mangled, obj, ratio) in results.items():
        entry = addr_map.get(addr_str)
        if not entry:
            continue

        if obj.startswith('d3dx9:'):
            entry["status"] = "not_needed"
            entry["note"] = f"D3DX9 静态库 ({obj}, {ratio:.0%} match)"
        elif obj.startswith('LIBCMT:'):
            entry["status"] = "not_needed"
            entry["note"] = f"MSVC CRT ({obj}, {ratio:.0%} match)"
        elif obj.endswith('.cpp.obj'):
            source_file = obj[:-4] if obj.endswith('.cpp.obj') else obj
            entry["status"] = "done"
            entry["file"] = source_file
            entry["note"] = f"字节匹配 {ratio:.0%} (from {mangled[:40]})"
        else:
            entry["status"] = "not_needed"
            entry["note"] = f"第三方库 ({obj}, {ratio:.0%} match)"

    save_registry(entries)
    print(f"\n已更新注册表: {matched_count} 个函数")


if __name__ == "__main__":
    main()
