#!/usr/bin/env python3
"""
topo.dll 字节比对工具

从 VC6 编译的 .obj 提取 COFF text section，
与 original/topo.dll 中对应函数的字节做比较。

用法:
    python tools/topo_compare.py --compile src/topo/gbVec3D.cpp --all
    python tools/topo_compare.py --obj tools/vc6/gbVec3D.obj --all
    python tools/topo_compare.py --compile src/topo/gbVec3D.cpp --scan
"""

import argparse
import json
import struct
import sys
import subprocess
import os
import re
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_DLL = PROJECT_ROOT / "original" / "topo.dll"
GHIDRA_DIR = PROJECT_ROOT / "asm" / "topo"
VC6_DIR = PROJECT_ROOT / "tools" / "vc6"
VC6_BIN = VC6_DIR / "Bin"
VC6_INCLUDE = VC6_DIR / "Include"
VC6_LIB = VC6_DIR / "Lib"

DLL_IMAGE_BASE = 0x10000000


def get_dll_text_section(dll_path):
    """Parse PE header to find .text section offset and VA."""
    with open(dll_path, 'rb') as f:
        f.seek(0x3C)
        pe_offset = struct.unpack('<I', f.read(4))[0]
        f.seek(pe_offset)
        sig = f.read(4)
        assert sig == b'PE\x00\x00'
        machine = struct.unpack('<H', f.read(2))[0]
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


def read_dll_bytes(dll_path, rva, size, text_section):
    """Read bytes from DLL at given RVA."""
    file_offset = rva - text_section['virt_addr'] + text_section['raw_offset']
    with open(dll_path, 'rb') as f:
        f.seek(file_offset)
        return f.read(size)


def parse_coff_obj(obj_path):
    """Parse COFF .obj file, return dict of symbol_name -> (section_data, offset, size)."""
    with open(obj_path, 'rb') as f:
        data = f.read()

    machine = struct.unpack_from('<H', data, 0)[0]
    num_sections = struct.unpack_from('<H', data, 2)[0]
    sym_table_offset = struct.unpack_from('<I', data, 8)[0]
    num_symbols = struct.unpack_from('<I', data, 12)[0]
    opt_hdr_size = struct.unpack_from('<H', data, 16)[0]

    sections = []
    sec_offset = 20 + opt_hdr_size
    for i in range(num_sections):
        name_bytes = data[sec_offset:sec_offset+8]
        virt_size = struct.unpack_from('<I', data, sec_offset+8)[0]
        virt_addr = struct.unpack_from('<I', data, sec_offset+12)[0]
        raw_size = struct.unpack_from('<I', data, sec_offset+16)[0]
        raw_offset = struct.unpack_from('<I', data, sec_offset+20)[0]
        reloc_offset = struct.unpack_from('<I', data, sec_offset+24)[0]
        num_relocs = struct.unpack_from('<H', data, sec_offset+32)[0]
        characteristics = struct.unpack_from('<I', data, sec_offset+36)[0]

        str_table_offset = sym_table_offset + num_symbols * 18
        if name_bytes[0:1] == b'/':
            str_off = int(name_bytes[1:].rstrip(b'\x00').decode('ascii'))
            end = data.index(b'\x00', str_table_offset + str_off)
            sec_name = data[str_table_offset + str_off:end].decode('ascii')
        else:
            sec_name = name_bytes.rstrip(b'\x00').decode('ascii')

        sec_data = data[raw_offset:raw_offset+raw_size] if raw_offset > 0 else b''

        relocs = set()
        if num_relocs > 0 and reloc_offset > 0:
            for r in range(num_relocs):
                roff = reloc_offset + r * 10
                r_vaddr = struct.unpack_from('<I', data, roff)[0]
                for b in range(4):
                    relocs.add(r_vaddr + b)

        sections.append({
            'name': sec_name,
            'data': sec_data,
            'raw_size': raw_size,
            'characteristics': characteristics,
            'relocs': relocs,
        })
        sec_offset += 40

    str_table_offset = sym_table_offset + num_symbols * 18
    symbols = []
    i = 0
    while i < num_symbols:
        sym_offset = sym_table_offset + i * 18
        name_field = data[sym_offset:sym_offset+8]
        value = struct.unpack_from('<I', data, sym_offset+8)[0]
        sec_num = struct.unpack_from('<h', data, sym_offset+12)[0]
        sym_type = struct.unpack_from('<H', data, sym_offset+14)[0]
        storage_class = data[sym_offset+16]
        num_aux = data[sym_offset+17]

        if name_field[0:4] == b'\x00\x00\x00\x00':
            str_off = struct.unpack_from('<I', name_field, 4)[0]
            end = data.index(b'\x00', str_table_offset + str_off)
            sym_name = data[str_table_offset + str_off:end].decode('ascii', errors='replace')
        else:
            sym_name = name_field.rstrip(b'\x00').decode('ascii', errors='replace')

        symbols.append({
            'name': sym_name,
            'value': value,
            'section': sec_num,
            'type': sym_type,
            'storage_class': storage_class,
        })
        i += 1 + num_aux

    functions = {}
    for sym in symbols:
        if sym['section'] <= 0:
            continue
        sec_idx = sym['section'] - 1
        if sec_idx >= len(sections):
            continue
        sec = sections[sec_idx]
        if not (sec['characteristics'] & 0x20):
            continue
        if sym['storage_class'] == 2 and (sym['type'] & 0x20):
            functions[sym['name']] = {
                'section_idx': sec_idx,
                'offset': sym['value'],
            }

    for name, info in functions.items():
        sec_idx = info['section_idx']
        offset = info['offset']
        sec = sections[sec_idx]
        next_offset = sec['raw_size']
        for other_name, other_info in functions.items():
            if other_info['section_idx'] == sec_idx and other_info['offset'] > offset:
                if other_info['offset'] < next_offset:
                    next_offset = other_info['offset']
        size = next_offset - offset
        info['size'] = size
        info['bytes'] = sec['data'][offset:offset+size]
        info['relocs'] = set()
        for r in sec['relocs']:
            rel_off = r - offset
            if 0 <= rel_off < size:
                info['relocs'].add(rel_off)

    return functions


def build_ghidra_index():
    """Build name -> ghidra data index from asm/topo/*.json."""
    index = {}
    if not GHIDRA_DIR.exists():
        return index

    for json_file in GHIDRA_DIR.glob("*.json"):
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                d = json.load(f)
            addr = d.get('address', '')
            name = d.get('name', '')
            sig = d.get('signature', '')
            d['_file'] = json_file.name
            # Index by address (primary key)
            if addr:
                index[addr] = d
            # Also index by signature components for matching
            if sig:
                index[f"sig:{sig}"] = d
        except (json.JSONDecodeError, IOError):
            continue

    return index


def demangle_msvc(mangled):
    """Demangle MSVC name using undname.exe if available, else basic parsing."""
    undname = VC6_BIN / "UNDNAME.EXE"
    if undname.exists():
        try:
            result = subprocess.run(
                [str(undname), mangled],
                capture_output=True, text=True, timeout=5
            )
            if result.returncode == 0 and result.stdout.strip():
                return result.stdout.strip().split('\n')[-1].strip()
        except:
            pass

    # Basic manual demangling for common patterns
    # ?Name@Class@@... -> Class::Name
    m = re.match(r'\?(\w+)@(\w+)@@', mangled)
    if m:
        func_name = m.group(1)
        class_name = m.group(2)
        if func_name.startswith('?'):
            # Operators
            op_map = {
                '?0': class_name,  # constructor
                '?1': f'~{class_name}',  # destructor
                '?4': 'operator=',
                '?8': 'operator==',
                '?G': 'operator-',
                '?X': 'operator*=',
                '?Y': 'operator+=',
                '?Z': 'operator-=',
            }
            func_name = op_map.get(func_name, func_name)
        return f"{class_name}::{func_name}"
    return mangled


def match_func_to_ghidra(mangled_name, ghidra_index):
    """Try to match a mangled COFF symbol to a Ghidra JSON entry."""
    demangled = demangle_msvc(mangled_name)

    # Extract class::method from demangled name
    m = re.match(r'(\w+)::(\w+|operator\S+|~\w+)', demangled)
    if not m:
        return None

    class_name = m.group(1)
    method_name = m.group(2)

    # Search ghidra index by signature containing class::method
    candidates = []
    for key, data in ghidra_index.items():
        if not key.startswith('sig:'):
            continue
        sig = key[4:]
        # Check if signature contains the class and method
        if f'{class_name}::' in sig and method_name in sig:
            candidates.append(data)

    if len(candidates) == 1:
        return candidates[0]
    elif len(candidates) > 1:
        # Try to disambiguate by parameter count or types in mangled name
        # For now return None for ambiguous
        return None
    return None


def compare_bytes(compiled, original, func_name, verbose=True, relocs=None):
    """Compare compiled bytes against original, return match info."""
    if relocs is None:
        relocs = set()
    min_len = min(len(compiled), len(original))
    matches = 0
    diffs = []
    reloc_diffs = 0

    for i in range(min_len):
        if compiled[i] == original[i]:
            matches += 1
        elif i in relocs:
            matches += 1
            reloc_diffs += 1
        else:
            diffs.append(i)

    total = max(len(compiled), len(original))
    match_pct = (matches / total * 100) if total > 0 else 0

    if verbose:
        size_match = "OK" if len(compiled) == len(original) else f"MISMATCH (compiled={len(compiled)}, original={len(original)})"
        print(f"  {func_name}:")
        print(f"    Size: {size_match}")
        reloc_info = f" (reloc_skip={reloc_diffs})" if reloc_diffs else ""
        print(f"    Match: {matches}/{total} bytes ({match_pct:.1f}%){reloc_info}")

        if diffs and len(diffs) <= 20:
            print(f"    Diffs at offsets: {diffs[:20]}")
            for off in diffs[:5]:
                if off < len(compiled) and off < len(original):
                    print(f"      +{off:04X}: compiled=0x{compiled[off]:02X} original=0x{original[off]:02X}")
        elif diffs:
            print(f"    First 5 diffs: {diffs[:5]}")
            for off in diffs[:5]:
                if off < len(compiled) and off < len(original):
                    print(f"      +{off:04X}: compiled=0x{compiled[off]:02X} original=0x{original[off]:02X}")

    return {
        'name': func_name,
        'compiled_size': len(compiled),
        'original_size': len(original),
        'matches': matches,
        'total': total,
        'match_pct': match_pct,
        'perfect': len(compiled) == len(original) and matches == total,
    }


def scan_dll_for_func(text_data, text_sec, compiled_bytes, relocs, min_size=16):
    """Search .text section for a function matching compiled bytes."""
    if len(compiled_bytes) < min_size:
        return []

    results = []
    prefix_bytes = bytearray()
    for i in range(min(8, len(compiled_bytes))):
        if i in relocs:
            break
        prefix_bytes.append(compiled_bytes[i])

    if len(prefix_bytes) < 3:
        return []

    prefix = bytes(prefix_bytes)
    pos = 0
    while True:
        pos = text_data.find(prefix, pos)
        if pos == -1:
            break
        compare_len = min(len(compiled_bytes), len(text_data) - pos)
        matches = 0
        total = compare_len
        for i in range(compare_len):
            if i in relocs:
                matches += 1
            elif compiled_bytes[i] == text_data[pos + i]:
                matches += 1
        ratio = matches / total if total > 0 else 0
        if ratio >= 0.85:
            va = pos + text_sec['virt_addr'] + DLL_IMAGE_BASE
            results.append((va, ratio))
        pos += 1

    return results


def compile_file(src_path, obj_path):
    """Compile a source file with VC6."""
    cl_exe = str(VC6_BIN / "CL.EXE")
    use_wine = sys.platform.startswith('linux')

    if use_wine:
        win_include = 'Z:' + str(Path(VC6_INCLUDE).resolve()).replace('/', '\\')
        win_proj_include = 'Z:' + str((PROJECT_ROOT / 'include').resolve()).replace('/', '\\')
        win_obj = 'Z:' + str(Path(obj_path).resolve()).replace('/', '\\')
        win_src = 'Z:' + str(Path(src_path).resolve()).replace('/', '\\')
        cmd = [
            'wine', cl_exe,
            '/nologo', '/c', '/O2', '/Oi', '/Ob2', '/GF', '/Gy', '/Zp4', '/GX',
            '/DWINVER=0x0500', '/D_WIN32_WINNT=0x0400',
            f'/I{win_include}', f'/I{win_proj_include}',
            f'/Fo{win_obj}', win_src,
        ]
        env = os.environ.copy()
        env['WINEDEBUG'] = '-all'
    else:
        include_dirs = f"{VC6_INCLUDE};{PROJECT_ROOT / 'include'}"
        env = os.environ.copy()
        env['INCLUDE'] = include_dirs
        env['LIB'] = str(VC6_LIB)
        cmd = [
            cl_exe,
            '/nologo', '/c', '/O2', '/Oi', '/Ob2', '/GF', '/Gy', '/Zp4', '/GX',
            '/DWINVER=0x0500', '/D_WIN32_WINNT=0x0400',
            f'/Fo{obj_path}', str(src_path),
        ]

    result = subprocess.run(cmd, capture_output=True, text=True, env=env)
    if result.returncode != 0:
        print(f"  Compilation FAILED:")
        print(f"    {result.stderr}")
        if result.stdout:
            print(f"    {result.stdout}")
        return False
    return True


def main():
    parser = argparse.ArgumentParser(description='topo.dll 字节比对')
    parser.add_argument('--obj', help='已编译的 .obj 文件路径')
    parser.add_argument('--compile', help='源文件路径 (自动编译)')
    parser.add_argument('--func', help='比较指定函数 (名称子串匹配)')
    parser.add_argument('--all', action='store_true', help='比较 .obj 中所有函数')
    parser.add_argument('--scan', action='store_true', help='扫描DLL.text匹配')
    parser.add_argument('--verbose', '-v', action='store_true', help='详细输出')
    args = parser.parse_args()

    if not args.obj and not args.compile:
        parser.print_help()
        sys.exit(1)

    # Compile if needed
    obj_path = args.obj
    if args.compile:
        src_path = Path(args.compile)
        if not src_path.is_absolute():
            src_path = PROJECT_ROOT / src_path
        obj_path = str(VC6_DIR / (src_path.stem + '.obj'))
        print(f"[*] 编译 {src_path.name} ...")
        if not compile_file(src_path, obj_path):
            sys.exit(1)
        print(f"    -> {obj_path}")

    # Parse original DLL
    print(f"[*] 解析 original/topo.dll ...")
    text_sec = get_dll_text_section(ORIGINAL_DLL)
    if not text_sec:
        print("[!] 找不到 .text section")
        sys.exit(1)
    print(f"    .text: VA=0x{text_sec['virt_addr']:X}, size=0x{text_sec['virt_size']:X}, file_offset=0x{text_sec['raw_offset']:X}")

    # Load .text data
    with open(ORIGINAL_DLL, 'rb') as f:
        f.seek(text_sec['raw_offset'])
        text_data = f.read(text_sec['raw_size'])

    # Parse .obj
    print(f"[*] 解析 .obj ...")
    functions = parse_coff_obj(obj_path)
    print(f"    找到 {len(functions)} 个函数符号")

    # Build Ghidra index
    print(f"[*] 构建 Ghidra 索引 ...")
    ghidra_index = build_ghidra_index()
    # Build address-based lookup
    addr_index = {k: v for k, v in ghidra_index.items() if k.startswith('0x')}
    print(f"    索引 {len(addr_index)} 个函数 (by address)")

    # Compare
    results = []
    scan_results = []
    skipped = []

    for mangled_name, func_info in sorted(functions.items()):
        if func_info['size'] < 4:
            skipped.append(mangled_name)
            continue

        demangled = demangle_msvc(mangled_name)

        if args.func:
            if args.func not in demangled and args.func not in mangled_name:
                continue

        # Try scan mode: find this function in topo.dll .text
        matches = scan_dll_for_func(text_data, text_sec, func_info['bytes'],
                                     func_info.get('relocs', set()))

        if len(matches) == 1:
            va, ratio = matches[0]
            rva = va - DLL_IMAGE_BASE
            # Look up in ghidra index for authoritative size
            addr_key = f"0x{va:08x}"
            ghidra_data = addr_index.get(addr_key)
            if ghidra_data:
                orig_size = ghidra_data['size_bytes']
                display_name = f"{demangled} [{ghidra_data.get('name', '')}@0x{va:X}]"
            else:
                orig_size = func_info['size']
                display_name = f"{demangled} @0x{va:X}"

            orig_bytes = read_dll_bytes(ORIGINAL_DLL, rva, orig_size, text_sec)
            compiled_bytes = func_info['bytes'][:orig_size]

            result = compare_bytes(compiled_bytes, orig_bytes, display_name,
                                   verbose=True, relocs=func_info.get('relocs', set()))
            results.append(result)

        elif len(matches) > 1:
            if args.verbose:
                addrs = [f"0x{m[0]:08X}({m[1]*100:.0f}%)" for m in matches[:3]]
                print(f"  [AMBIGUOUS] {demangled} -> {addrs}")
            # Try all matches and pick the best
            best = None
            for va, ratio in matches:
                rva = va - DLL_IMAGE_BASE
                addr_key = f"0x{va:08x}"
                ghidra_data = addr_index.get(addr_key)
                if ghidra_data:
                    orig_size = ghidra_data['size_bytes']
                    orig_bytes = read_dll_bytes(ORIGINAL_DLL, rva, orig_size, text_sec)
                    compiled_bytes = func_info['bytes'][:orig_size]
                    if len(compiled_bytes) == orig_size:
                        match_count = sum(1 for i in range(orig_size)
                                         if i in func_info.get('relocs', set()) or
                                         compiled_bytes[i] == orig_bytes[i])
                        if best is None or match_count > best[1]:
                            best = (va, match_count, orig_size, ghidra_data)

            if best:
                va, mc, orig_size, ghidra_data = best
                rva = va - DLL_IMAGE_BASE
                orig_bytes = read_dll_bytes(ORIGINAL_DLL, rva, orig_size, text_sec)
                compiled_bytes = func_info['bytes'][:orig_size]
                display_name = f"{demangled} [{ghidra_data.get('name', '')}@0x{va:X}]"
                result = compare_bytes(compiled_bytes, orig_bytes, display_name,
                                       verbose=True, relocs=func_info.get('relocs', set()))
                results.append(result)
            else:
                skipped.append(f"{demangled} (ambiguous, no ghidra match)")
        else:
            skipped.append(f"{demangled} (not found in DLL)")

    # Summary
    if results:
        perfect = sum(1 for r in results if r['perfect'])
        size_ok = sum(1 for r in results if r['compiled_size'] == r['original_size'])
        print(f"\n{'='*60}")
        print(f"[*] 总结: {perfect}/{len(results)} 函数完全匹配 (100%)")
        print(f"    Size OK: {size_ok}/{len(results)}")
        avg_match = sum(r['match_pct'] for r in results) / len(results)
        print(f"    平均匹配率: {avg_match:.1f}%")
        print(f"{'='*60}")

        # List non-perfect functions
        non_perfect = [r for r in results if not r['perfect']]
        if non_perfect:
            print(f"\n  非完全匹配 ({len(non_perfect)}):")
            for r in sorted(non_perfect, key=lambda x: -x['match_pct']):
                size_info = "" if r['compiled_size'] == r['original_size'] else " SIZE_MISMATCH"
                print(f"    {r['match_pct']:5.1f}% {r['name']}{size_info}")

    if skipped and args.verbose:
        print(f"\n  跳过 ({len(skipped)}):")
        for name in skipped[:10]:
            print(f"    {name}")


if __name__ == '__main__':
    main()
