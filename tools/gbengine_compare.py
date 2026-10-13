#!/usr/bin/env python3
"""
gbengine.dll 字节比对工具

从 VC6 编译的 .obj 提取 COFF text section，
与 original gbengine.dll 中对应函数的字节做比较。

用法:
    python tools/gbengine_compare.py --obj tools/vc6/BEZIER.obj --func "BEZIER::BEZIER(gbVec3D *)"
    python tools/gbengine_compare.py --obj tools/vc6/BEZIER.obj --all
    python tools/gbengine_compare.py --compile src/gbengine/BEZIER.cpp --all
"""

import argparse
import json
import struct
import sys
import subprocess
import os
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ORIGINAL_DLL = PROJECT_ROOT / "original" / "gbengine.dll"
IDA_DIR = PROJECT_ROOT / "asm" / "gbengine_ida"
VC6_DIR = PROJECT_ROOT / "tools" / "vc6"
VC6_BIN = VC6_DIR / "Bin"
VC6_INCLUDE = VC6_DIR / "Include"
VC6_LIB = VC6_DIR / "Lib"

# gbengine.dll base address and .text section info
# Need to parse PE to get actual values
DLL_IMAGE_BASE = 0x10000000


def get_dll_text_section(dll_path):
    """Parse PE header to find .text section offset and VA."""
    with open(dll_path, 'rb') as f:
        # DOS header
        f.seek(0x3C)
        pe_offset = struct.unpack('<I', f.read(4))[0]

        # PE signature
        f.seek(pe_offset)
        sig = f.read(4)
        assert sig == b'PE\x00\x00'

        # COFF header
        machine = struct.unpack('<H', f.read(2))[0]
        num_sections = struct.unpack('<H', f.read(2))[0]
        f.read(12)  # timestamp, symbol table, num symbols
        opt_hdr_size = struct.unpack('<H', f.read(2))[0]
        f.read(2)  # characteristics

        # Skip optional header
        f.seek(pe_offset + 4 + 20 + opt_hdr_size)

        # Section headers
        for i in range(num_sections):
            name = f.read(8).rstrip(b'\x00').decode('ascii', errors='replace')
            virt_size = struct.unpack('<I', f.read(4))[0]
            virt_addr = struct.unpack('<I', f.read(4))[0]
            raw_size = struct.unpack('<I', f.read(4))[0]
            raw_offset = struct.unpack('<I', f.read(4))[0]
            f.read(16)  # relocs, line numbers, characteristics

            if name == '.text':
                return {
        'reloc_target': reloc_target,
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

    # COFF header
    machine = struct.unpack_from('<H', data, 0)[0]
    num_sections = struct.unpack_from('<H', data, 2)[0]
    timestamp = struct.unpack_from('<I', data, 4)[0]
    sym_table_offset = struct.unpack_from('<I', data, 8)[0]
    num_symbols = struct.unpack_from('<I', data, 12)[0]
    opt_hdr_size = struct.unpack_from('<H', data, 16)[0]

    # Parse sections
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

        # Decode section name
        if name_bytes[0:1] == b'/':
            str_offset = int(name_bytes[1:].rstrip(b'\x00').decode('ascii'))
            str_table_offset = sym_table_offset + num_symbols * 18
            end = data.index(b'\x00', str_table_offset + str_offset)
            sec_name = data[str_table_offset + str_offset:end].decode('ascii')
        else:
            sec_name = name_bytes.rstrip(b'\x00').decode('ascii')

        sec_data = data[raw_offset:raw_offset+raw_size] if raw_offset > 0 else b''

        # Parse relocations for this section
        relocs = set()
        if num_relocs > 0 and reloc_offset > 0:
            for r in range(num_relocs):
                roff = reloc_offset + r * 10
                r_vaddr = struct.unpack_from('<I', data, roff)[0]
                # Each relocation covers 4 bytes (32-bit address)
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

    # Parse symbol table
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

        # Decode symbol name
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

    # Build function map: for each EXTERNAL/function symbol in a .text section
    functions = {}
    for sym in symbols:
        if sym['section'] <= 0:
            continue
        sec_idx = sym['section'] - 1
        if sec_idx >= len(sections):
            continue
        sec = sections[sec_idx]
        if not (sec['characteristics'] & 0x20):  # IMAGE_SCN_CNT_CODE
            continue
        # storage class 2 = EXTERNAL, type 0x20 = function
        if sym['storage_class'] == 2 and (sym['type'] & 0x20):
            functions[sym['name']] = {
                'section_idx': sec_idx,
                'offset': sym['value'],
            }

    # Calculate function sizes
    # With /Gy (COMDAT), each function is typically in its own section
    # Use the IDA-reported size as the authoritative size for comparison
    # For now, store all available bytes from offset to end of section
    for name, info in functions.items():
        sec_idx = info['section_idx']
        offset = info['offset']
        sec = sections[sec_idx]

        # Find next function in same section
        next_offset = sec['raw_size']
        for other_name, other_info in functions.items():
            if other_info['section_idx'] == sec_idx and other_info['offset'] > offset:
                if other_info['offset'] < next_offset:
                    next_offset = other_info['offset']

        size = next_offset - offset
        info['size'] = size
        info['bytes'] = sec['data'][offset:offset+size]
        # Collect relocation offsets relative to function start
        info['relocs'] = set()
        for r in sec['relocs']:
            rel_off = r - offset
            if 0 <= rel_off < size:
                info['relocs'].add(rel_off)

    return functions


def demangle_to_ida_name(mangled):
    """Try to convert mangled name to IDA-style demangled name."""
    # This is a simplified approach - we'll match by searching IDA exports
    pass


def build_ida_index():
    """Build mangled_name -> IDA data index."""
    index = {}
    if not IDA_DIR.exists():
        return index

    for json_file in IDA_DIR.glob("*.json"):
        try:
            with open(json_file, 'r', encoding='utf-8') as f:
                d = json.load(f)
            mangled = d.get('mangled_name', '')
            name = d.get('name', '')
            if mangled:
                index[mangled] = d
            if name:
                index[name] = d
        except (json.JSONDecodeError, IOError):
            continue

    return index


def compare_bytes(compiled, original, func_name, verbose=True, relocs=None):
    """Compare compiled bytes against original, return match info."""
    if relocs is None:
        relocs = set()
    min_len = min(len(compiled), len(original))
    matches = 0
    diffs = []
    reloc_diffs = 0

    # [T81/P0c] 重定位目标核对（kiro 口径）：每处重定位的 4 字节值双侧比较——
    # 可解析（双值在 .text 范围内 ⇒ 目标可定位）计入 reloc_ok/total；不可解析
    # （导入/字符串/vtable）计 reloc_unresolved。每处 4 字节跳过+截断比较的判据
    # 不变（完美性判定不被此检查改变——纯计量）。
    reloc_target = {'total': 0, 'ok': 0, 'unresolved': 0}
    for i in sorted(relocs):
        if i + 4 > min_len:
            continue
        reloc_target['total'] += 1
        cv = int.from_bytes(compiled[i:i+4], 'little')
        ov = int.from_bytes(original[i:i+4], 'little')
        if 0x400000 <= cv <= 0x600000 and 0x400000 <= ov <= 0x600000:
            if cv == ov:
                reloc_target['ok'] += 1
            else:
                reloc_target['unresolved'] += 1  # 目标异（计入偏移量后仍异）
        else:
            reloc_target['unresolved'] += 1  # 导入/字符串/vtable 等不可解析
    for i in range(min_len):
        if compiled[i] == original[i]:
            matches += 1
        elif i in relocs:
            matches += 1  # Relocation bytes are "don't care"
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
                print(f"      +{off:04X}: compiled=0x{compiled[off]:02X} original=0x{original[off]:02X}")
        elif diffs:
            print(f"    First 5 diffs: {diffs[:5]}")
            for off in diffs[:5]:
                print(f"      +{off:04X}: compiled=0x{compiled[off]:02X} original=0x{original[off]:02X}")

    return {
        'name': func_name,
        'compiled_size': len(compiled),
        'original_size': len(original),
        'matches': matches,
        'total': total,
        'match_pct': match_pct,
        'perfect': len(compiled) == len(original) and matches == total,
        # ROI-1（2026-09-19，长线计划）：把差异**偏移**返回出去。
        # 原先这里算完 `diffs`/`reloc_diffs` 就丢掉，是"没有任何工具能解释 partial"的根因
        # （`compare_pal3.compare_units` 拿到 res 后只取 match_pct）。**只增字段，不改判据**。
        'diffs': diffs,
        'reloc_diffs': reloc_diffs,
        'reloc_target': reloc_target,
        'first_diff': diffs[0] if diffs else None,
    }


def _is_linux():
    """Check if running on Linux."""
    return sys.platform.startswith('linux')


def _to_winpath(path):
    """Convert Unix path to Wine Z: drive path."""
    return 'Z:' + str(Path(path).resolve()).replace('/', '\\')


def compile_file(src_path, obj_path):
    """Compile a source file with VC6 (supports Linux via Wine)."""
    cl_exe = str(VC6_BIN / "CL.EXE")
    use_wine = _is_linux()

    if use_wine:
        win_include = _to_winpath(VC6_INCLUDE)
        win_proj_include = _to_winpath(PROJECT_ROOT / 'include')
        win_obj = _to_winpath(obj_path)
        win_src = _to_winpath(src_path)

        cmd = [
            'wine', cl_exe,
            '/nologo',
            '/c',        # compile only
            '/O2',       # optimize for speed
            '/Oi',       # enable intrinsic functions
            '/Ob2',      # auto-inline any suitable function
            '/GF',       # string pooling
            '/Gy',       # function-level linking
            '/Zp4',      # 4-byte struct member alignment (matches original)
            '/GX',       # enable C++ exception handling (SEH frames for new)
            '/DWINVER=0x0500',         # target Win2000+ (matches original DEVMODEA size)
            '/D_WIN32_WINNT=0x0400',   # NT4 SP4+ features
            f'/I{win_include}',
            f'/I{win_proj_include}',
            f'/Fo{win_obj}',
            win_src,
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
            '/nologo',
            '/c',        # compile only
            '/O2',       # optimize for speed
            '/Oi',       # enable intrinsic functions
            '/Ob2',      # auto-inline any suitable function
            '/GF',       # string pooling
            '/Gy',       # function-level linking
            '/Zp4',      # 4-byte struct member alignment (matches original)
            '/GX',       # enable C++ exception handling (SEH frames for new)
            '/DWINVER=0x0500',         # target Win2000+ (matches original DEVMODEA size)
            '/D_WIN32_WINNT=0x0400',   # NT4 SP4+ features
            f'/Fo{obj_path}',
            str(src_path),
        ]

    result = subprocess.run(cmd, capture_output=True, text=True, env=env)
    if result.returncode != 0:
        print(f"  Compilation FAILED:")
        print(f"    {result.stderr}")
        if result.stdout:
            print(f"    {result.stdout}")
        return False
    return True


def scan_dll_for_func(text_data, text_sec, compiled_bytes, relocs, min_size=20):
    """Search .text section for a function matching compiled bytes.
    Returns list of (VA, match_ratio) tuples."""
    if len(compiled_bytes) < min_size:
        return []

    results = []
    # Build a non-reloc prefix for fast searching
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
        # Full comparison
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


def main():
    parser = argparse.ArgumentParser(description='gbengine 字节比对')
    parser.add_argument('--obj', help='已编译的 .obj 文件路径')
    parser.add_argument('--compile', help='源文件路径 (自动编译)')
    parser.add_argument('--func', help='比较指定函数 (IDA名称)')
    parser.add_argument('--all', action='store_true', help='比较 .obj 中所有函数')
    parser.add_argument('--scan', action='store_true', help='对未在IDA索引中的函数扫描DLL匹配')
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
    print(f"[*] 解析 original/gbengine.dll ...")
    text_sec = get_dll_text_section(ORIGINAL_DLL)
    if not text_sec:
        print("[!] 找不到 .text section")
        sys.exit(1)
    print(f"    .text: VA=0x{text_sec['virt_addr']:X}, size=0x{text_sec['virt_size']:X}, file_offset=0x{text_sec['raw_offset']:X}")

    # Parse .obj
    print(f"[*] 解析 .obj ...")
    functions = parse_coff_obj(obj_path)
    print(f"    找到 {len(functions)} 个函数符号")

    # Build IDA index
    print(f"[*] 构建 IDA 索引 ...")
    ida_index = build_ida_index()
    print(f"    索引 {len(ida_index)} 个条目")

    # Load .text for scan mode
    text_data = None
    if args.scan:
        with open(ORIGINAL_DLL, 'rb') as f:
            f.seek(text_sec['raw_offset'])
            text_data = f.read(text_sec['raw_size'])

    # Compare
    results = []
    scan_results = []
    skipped = []
    for mangled_name, func_info in sorted(functions.items()):
        # Look up in IDA index by mangled name
        ida_data = ida_index.get(mangled_name)

        if args.func:
            if ida_data and args.func not in ida_data.get('name', '') and args.func not in mangled_name:
                continue
            elif not ida_data and args.func not in mangled_name:
                continue

        if ida_data:
            addr = int(ida_data['address'], 16)
            rva = addr - DLL_IMAGE_BASE
            orig_size = ida_data['size_bytes']

            # Read original bytes
            orig_bytes = read_dll_bytes(ORIGINAL_DLL, rva, orig_size, text_sec)

            # Use IDA size as authoritative - trim compiled bytes to match
            compiled_bytes = func_info['bytes'][:orig_size]

            # Compare (pass relocation info to skip reloc bytes)
            result = compare_bytes(compiled_bytes, orig_bytes, ida_data['name'],
                                   verbose=True, relocs=func_info.get('relocs', set()))
            results.append(result)
        elif args.scan and text_data and func_info['size'] >= 20:
            # Scan DLL .text for this function
            matches = scan_dll_for_func(text_data, text_sec, func_info['bytes'],
                                        func_info.get('relocs', set()))
            if len(matches) == 1:
                va, ratio = matches[0]
                # Do full comparison at this address
                rva = va - DLL_IMAGE_BASE
                orig_bytes = read_dll_bytes(ORIGINAL_DLL, rva, func_info['size'], text_sec)
                result = compare_bytes(func_info['bytes'], orig_bytes, f"{mangled_name} @0x{va:08X}",
                                       verbose=True, relocs=func_info.get('relocs', set()))
                scan_results.append(result)
            elif len(matches) > 1:
                if args.verbose:
                    addrs = [f"0x{m[0]:08X}({m[1]*100:.0f}%)" for m in matches[:3]]
                    print(f"  [AMBIGUOUS] {mangled_name} -> {addrs}")
            else:
                skipped.append(mangled_name)
        else:
            skipped.append(mangled_name)

    # Summary
    all_results = results + scan_results
    if all_results:
        perfect = sum(1 for r in all_results if r['perfect'])
        print(f"\n[*] 总结: {perfect}/{len(all_results)} 函数完全匹配")
        avg_match = sum(r['match_pct'] for r in all_results) / len(all_results)
        print(f"    平均匹配率: {avg_match:.1f}%")
        if scan_results:
            scan_perfect = sum(1 for r in scan_results if r['perfect'])
            print(f"    (其中扫描匹配: {scan_perfect}/{len(scan_results)})")
    if skipped and not args.func:
        if not results and not scan_results:
            print(f"\n[!] 没有匹配的函数。")
        if args.verbose or (not results and not scan_results):
            print(f"    未匹配符号 ({len(skipped)}):")
            for name in skipped[:5]:
                print(f"      {name}")


if __name__ == '__main__':
    main()
