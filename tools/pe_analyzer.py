#!/usr/bin/env python3
"""
PAL3 PE Binary Analyzer
Analyzes all .exe and .dll files in the PAL3 game directory.
Uses only Python stdlib (struct for PE parsing).
"""

import struct
import os
import glob
import math
import datetime
from collections import OrderedDict

GAME_DIR = "/home/peng/.steam/debian-installation/steamapps/common/PAL3/"

# Rich header compiler ID database (prodid -> description)
RICH_PRODIDS = {
    0x0001: "Import (VC 5.0/6.0)",
    0x0002: "Linker 5.x",
    0x0004: "MSVC 6.0 Linker",
    0x0006: "Resource Compiler (cvtres 5.00)",
    0x000A: "MSVC 6.0 Linker (6.00)",
    0x000B: "MSVC 6.0 Linker (imp)",
    0x000C: "MSVC 6.0 C Compiler",
    0x000D: "MSVC 6.0 C++ Compiler",
    0x000E: "MASM 6.15",
    0x000F: "MASM 6.15",
    0x0013: "MSVC 6.0 SP5 C Compiler",
    0x0014: "MSVC 6.0 SP5 C++ Compiler",
    0x0015: "MSVC 6.0 SP5 Linker",
    0x0016: "MSVC 6.0 SP6 C Compiler",
    0x0019: "VC++ 6.0 SP5",
    0x001C: "MSVC 7.0 Linker (7.00)",
    0x001D: "MSVC 7.0 Import",
    0x003D: "MSVC 7.0 Linker",
    0x003E: "MSVC 7.0 C++ Compiler",
    0x003F: "MSVC 7.0 C Compiler",
    0x0040: "MSVC 7.0 Linker",
    0x005A: "MSVC 7.1 Linker (7.10)",
    0x005B: "MSVC 7.1 Import",
    0x005C: "MSVC 7.1 C Compiler",
    0x005D: "MSVC 7.1 C++ Compiler",
    0x005E: "MSVC 7.1 MASM",
    0x005F: "MSVC 7.1 cvtres",
    0x0060: "MSVC 7.1 Linker",
    0x006D: "MSVC 8.0 C Compiler",
    0x006E: "MSVC 8.0 C++ Compiler",
    0x0078: "MSVC 8.0 Linker (8.00)",
    0x0083: "MSVC 9.0 C Compiler",
    0x0084: "MSVC 9.0 C++ Compiler",
    0x0091: "MSVC 9.0 Linker (9.00)",
    0x0093: "MSVC 9.0 Linker",
    0x0094: "MSVC 9.0 Linker (9.00)",
    0x009D: "MSVC 10.0 C Compiler",
    0x009E: "MSVC 10.0 C++ Compiler",
    0x00AA: "MSVC 10.0 Linker (10.00)",
    0x00AB: "MSVC 10.0 Linker",
    0x00C7: "MSVC 11.0 C Compiler",
    0x00C8: "MSVC 11.0 C++ Compiler",
    0x00D4: "MSVC 11.0 Linker (11.00)",
    0x00D5: "MSVC 11.0 Linker",
    0x00D9: "MSVC 11.0 Linker (11.00)",
    0x00DB: "MSVC 12.0 C Compiler",
    0x00DC: "MSVC 12.0 C++ Compiler",
    0x00E0: "MSVC 12.0 Linker (12.00)",
    0x00EB: "MSVC 14.0 C Compiler",
    0x00EC: "MSVC 14.0 C++ Compiler",
    0x00FF: "MSVC 14.0 Linker (14.00)",
    0x0100: "MSVC 14.0 Linker",
    0x0104: "MSVC 14.0 Linker (14.00) Update 3",
}

PACKER_SECTIONS = {
    '.sforce': 'StarForce protection',
    '.brick': 'StarForce protection',
    'upx0': 'UPX packer',
    'upx1': 'UPX packer',
    'upx2': 'UPX packer',
    '.aspack': 'ASPack packer',
    '.adata': 'ASPack packer',
    '.packed': 'Generic packer',
    '.nsp0': 'NsPack',
    '.nsp1': 'NsPack',
    '.enigma1': 'Enigma Protector',
    '.enigma2': 'Enigma Protector',
    '.themida': 'Themida/WinLicense',
    '.vmp0': 'VMProtect',
    '.vmp1': 'VMProtect',
}

KNOWN_THIRD_PARTY = {
    'binkw32.dll': ('Bink Video', 'RAD Game Tools - Video codec for FMV playback'),
    'mss32.dll': ('Miles Sound System', 'RAD Game Tools - Audio middleware'),
    'ijl15.dll': ('Intel JPEG Library', 'Intel - JPEG compression/decompression v1.5'),
    'steam_api.dll': ('Steamworks API', 'Valve - Steam platform integration'),
    'steamworks.net.dll': ('Steamworks.NET', '.NET/Mono wrapper for Steamworks API'),
}


def read_u8(data, off):
    return struct.unpack_from('<B', data, off)[0]

def read_u16(data, off):
    return struct.unpack_from('<H', data, off)[0]

def read_u32(data, off):
    return struct.unpack_from('<I', data, off)[0]

def read_cstring(data, off, max_len=256):
    end = data.find(b'\x00', off, off + max_len)
    if end == -1:
        end = off + max_len
    try:
        return data[off:end].decode('ascii', errors='replace')
    except:
        return "<unreadable>"


def rva_to_file_offset(rva, sections):
    for s in sections:
        if s['va'] <= rva < s['va'] + max(s['vsize'], s['raw_size']):
            return rva - s['va'] + s['raw_offset']
    return None


def calculate_entropy(data_block):
    if not data_block or len(data_block) == 0:
        return 0.0
    freq = [0] * 256
    for b in data_block:
        freq[b] += 1
    length = len(data_block)
    entropy = 0.0
    for count in freq:
        if count > 0:
            p = count / length
            entropy -= p * math.log2(p)
    return entropy


def parse_rich_header(data):
    rich_pos = data.find(b'Rich')
    if rich_pos == -1 or rich_pos > 0x400:
        return None
    xor_key = read_u32(data, rich_pos + 4)
    dans_sig = struct.pack('<I', 0x536E6144 ^ xor_key)
    dans_pos = data.find(dans_sig, 0x40, rich_pos)
    if dans_pos == -1:
        return None
    entries = []
    pos = dans_pos + 16
    while pos < rich_pos:
        val1 = read_u32(data, pos) ^ xor_key
        val2 = read_u32(data, pos + 4) ^ xor_key
        prodid = (val1 >> 16) & 0xFFFF
        build = val1 & 0xFFFF
        count = val2
        if prodid != 0 or build != 0:
            name = RICH_PRODIDS.get(prodid, f"Unknown (prodid=0x{prodid:04X})")
            entries.append({'prodid': prodid, 'build': build, 'count': count, 'name': name})
        pos += 8
    return entries


def identify_compiler_from_rich(entries):
    if not entries:
        return "Unknown"
    compilers = []
    linkers = []
    for e in entries:
        n = e['name'].lower()
        if 'c++ compiler' in n or 'c compiler' in n:
            compilers.append(e)
        elif 'linker' in n:
            linkers.append(e)
    if compilers:
        best = max(compilers, key=lambda x: x['prodid'])
        return best['name']
    elif linkers:
        best = max(linkers, key=lambda x: x['prodid'])
        return best['name']
    elif entries:
        best = max(entries, key=lambda x: x['prodid'])
        return best['name']
    return "Unknown"


def parse_imports(data, data_dirs, sections):
    if 'Import' not in data_dirs:
        return {}
    import_rva = data_dirs['Import']['rva']
    import_offset = rva_to_file_offset(import_rva, sections)
    if import_offset is None:
        return {}
    imports = OrderedDict()
    pos = import_offset
    while True:
        if pos + 20 > len(data):
            break
        ilt_rva = read_u32(data, pos)
        name_rva = read_u32(data, pos + 12)
        iat_rva = read_u32(data, pos + 16)
        if ilt_rva == 0 and name_rva == 0:
            break
        name_off = rva_to_file_offset(name_rva, sections)
        if name_off is not None:
            dll_name = read_cstring(data, name_off)
        else:
            dll_name = f"<RVA 0x{name_rva:08X}>"
        func_names = []
        lookup_rva = ilt_rva if ilt_rva != 0 else iat_rva
        if lookup_rva != 0:
            lt_off = rva_to_file_offset(lookup_rva, sections)
            if lt_off is not None:
                fpos = lt_off
                while fpos + 4 <= len(data):
                    entry = read_u32(data, fpos)
                    if entry == 0:
                        break
                    if entry & 0x80000000:
                        func_names.append(f"Ordinal#{entry & 0xFFFF}")
                    else:
                        hint_off = rva_to_file_offset(entry & 0x7FFFFFFF, sections)
                        if hint_off is not None and hint_off + 2 < len(data):
                            fname = read_cstring(data, hint_off + 2)
                            func_names.append(fname)
                        else:
                            func_names.append(f"<RVA 0x{entry:08X}>")
                    fpos += 4
        imports[dll_name] = func_names
        pos += 20
    return imports


def parse_exports(data, export_dir, sections):
    export_offset = rva_to_file_offset(export_dir['rva'], sections)
    if export_offset is None or export_offset + 40 > len(data):
        return {'count': 0, 'num_names': 0, 'names': [], 'dll_name': ''}
    num_functions = read_u32(data, export_offset + 20)
    num_names = read_u32(data, export_offset + 24)
    name_rva = read_u32(data, export_offset + 12)
    names_ptr_rva = read_u32(data, export_offset + 32)
    dll_name_off = rva_to_file_offset(name_rva, sections)
    dll_name = read_cstring(data, dll_name_off) if dll_name_off else ''
    export_names = []
    names_ptr_off = rva_to_file_offset(names_ptr_rva, sections)
    if names_ptr_off is not None:
        for i in range(min(num_names, 500)):
            if names_ptr_off + i * 4 + 4 > len(data):
                break
            fn_rva = read_u32(data, names_ptr_off + i * 4)
            fn_off = rva_to_file_offset(fn_rva, sections)
            if fn_off is not None:
                export_names.append(read_cstring(data, fn_off))
    return {'count': num_functions, 'num_names': num_names, 'names': export_names, 'dll_name': dll_name}


def parse_debug_dir(data, debug_dir_info, sections):
    debug_offset = rva_to_file_offset(debug_dir_info['rva'], sections)
    if debug_offset is None:
        return None
    results = []
    num_entries = debug_dir_info['size'] // 28
    for i in range(num_entries):
        entry_off = debug_offset + i * 28
        if entry_off + 28 > len(data):
            break
        debug_type = read_u32(data, entry_off + 12)
        debug_raw = read_u32(data, entry_off + 24)
        type_names = {0: 'Unknown', 1: 'COFF', 2: 'CodeView', 3: 'FPO', 4: 'Misc',
                      5: 'Exception', 6: 'Fixup', 9: 'Borland', 12: 'Feature',
                      13: 'CoffGrp', 14: 'ILTCG', 16: 'Repro', 20: 'ExDllCharacteristics'}
        info = {'type': type_names.get(debug_type, f'Type{debug_type}')}
        if debug_type == 2 and debug_raw + 4 <= len(data):
            sig = data[debug_raw:debug_raw+4]
            if sig == b'RSDS' and debug_raw + 24 < len(data):
                info['pdb_path'] = read_cstring(data, debug_raw + 24, 512)
            elif sig == b'NB10' and debug_raw + 16 < len(data):
                info['pdb_path'] = read_cstring(data, debug_raw + 16, 512)
        results.append(info)
    return results


def parse_pe(filepath):
    result = OrderedDict()
    filename = os.path.basename(filepath)
    result['filename'] = filename
    result['filepath'] = filepath
    result['size'] = os.path.getsize(filepath)

    with open(filepath, 'rb') as f:
        data = f.read()

    if len(data) < 64 or data[:2] != b'MZ':
        result['error'] = 'Not a valid PE (no MZ header)'
        return result

    pe_offset = read_u32(data, 0x3C)
    if pe_offset + 4 > len(data) or data[pe_offset:pe_offset+4] != b'PE\x00\x00':
        result['error'] = 'No PE signature found (may be .NET-only assembly or corrupt)'
        return result

    coff_offset = pe_offset + 4
    machine = read_u16(data, coff_offset)
    num_sections = read_u16(data, coff_offset + 2)
    timestamp = read_u32(data, coff_offset + 4)
    characteristics = read_u16(data, coff_offset + 18)
    size_of_opt_header = read_u16(data, coff_offset + 16)

    result['machine'] = 'x86 (i386)' if machine == 0x14C else 'x64 (AMD64)' if machine == 0x8664 else f'0x{machine:04X}'
    result['timestamp'] = timestamp
    result['is_dll'] = bool(characteristics & 0x2000)

    try:
        result['timestamp_str'] = datetime.datetime.utcfromtimestamp(timestamp).strftime('%Y-%m-%d %H:%M:%S UTC')
    except:
        result['timestamp_str'] = 'Invalid'

    opt_offset = coff_offset + 20
    opt_magic = read_u16(data, opt_offset)
    result['pe_type'] = 'PE32' if opt_magic == 0x10B else 'PE32+' if opt_magic == 0x20B else f'Unknown(0x{opt_magic:X})'

    linker_major = read_u8(data, opt_offset + 2)
    linker_minor = read_u8(data, opt_offset + 3)
    result['linker_version'] = f'{linker_major}.{linker_minor:02d}'

    if opt_magic == 0x10B:
        entry_point = read_u32(data, opt_offset + 16)
        image_base = read_u32(data, opt_offset + 28)
        num_data_dirs = read_u32(data, opt_offset + 92)
        data_dir_offset = opt_offset + 96
        subsystem = read_u16(data, opt_offset + 68)
        size_of_image = read_u32(data, opt_offset + 56)
    elif opt_magic == 0x20B:
        entry_point = read_u32(data, opt_offset + 16)
        image_base = struct.unpack_from('<Q', data, opt_offset + 24)[0]
        num_data_dirs = read_u32(data, opt_offset + 108)
        data_dir_offset = opt_offset + 112
        subsystem = read_u16(data, opt_offset + 68)
        size_of_image = read_u32(data, opt_offset + 56)
    else:
        result['error'] = f'Unknown optional header magic: 0x{opt_magic:X}'
        return result

    result['entry_point'] = f'0x{entry_point:08X}'
    result['image_base'] = f'0x{image_base:08X}'
    result['size_of_image'] = size_of_image
    result['subsystem'] = {1: 'Native', 2: 'Windows GUI', 3: 'Windows Console', 9: 'WinCE'}.get(subsystem, f'Unknown({subsystem})')

    data_dirs = {}
    dir_names = ['Export', 'Import', 'Resource', 'Exception', 'Security',
                 'BaseReloc', 'Debug', 'Architecture', 'GlobalPtr', 'TLS',
                 'LoadConfig', 'BoundImport', 'IAT', 'DelayImport',
                 'CLRRuntime', 'Reserved']
    for i in range(min(num_data_dirs, 16)):
        rva = read_u32(data, data_dir_offset + i * 8)
        size = read_u32(data, data_dir_offset + i * 8 + 4)
        if rva != 0 or size != 0:
            name = dir_names[i] if i < len(dir_names) else f'Dir{i}'
            data_dirs[name] = {'rva': rva, 'size': size}

    result['data_dirs'] = data_dirs
    result['has_exports'] = 'Export' in data_dirs
    result['has_clr'] = 'CLRRuntime' in data_dirs
    result['has_tls'] = 'TLS' in data_dirs
    result['has_debug'] = 'Debug' in data_dirs
    result['has_reloc'] = 'BaseReloc' in data_dirs

    section_table_offset = opt_offset + size_of_opt_header
    sections = []
    packer_detected = []
    for i in range(num_sections):
        s_off = section_table_offset + i * 40
        name_bytes = data[s_off:s_off+8]
        name = name_bytes.split(b'\x00')[0].decode('ascii', errors='replace')
        vsize = read_u32(data, s_off + 8)
        va = read_u32(data, s_off + 12)
        raw_size = read_u32(data, s_off + 16)
        raw_offset = read_u32(data, s_off + 20)
        section_chars = read_u32(data, s_off + 36)

        sec_flags = []
        if section_chars & 0x20: sec_flags.append('CODE')
        if section_chars & 0x40: sec_flags.append('IDATA')
        if section_chars & 0x80: sec_flags.append('UDATA')
        if section_chars & 0x20000000: sec_flags.append('X')
        if section_chars & 0x40000000: sec_flags.append('R')
        if section_chars & 0x80000000: sec_flags.append('W')

        entropy = 0.0
        if raw_size > 0 and raw_offset + raw_size <= len(data):
            entropy = calculate_entropy(data[raw_offset:raw_offset+raw_size])

        sec = {
            'name': name, 'vsize': vsize, 'va': va,
            'raw_size': raw_size, 'raw_offset': raw_offset,
            'characteristics': section_chars,
            'flags_str': '|'.join(sec_flags),
            'entropy': entropy,
        }
        sections.append(sec)

        if name.lower() in PACKER_SECTIONS:
            packer_detected.append(f'{name} -> {PACKER_SECTIONS[name.lower()]}')

        if entropy > 7.5 and (section_chars & 0x20000000):
            packer_detected.append(f'{name}: high entropy ({entropy:.2f}) - possibly packed/encrypted')

    result['sections'] = sections
    result['packer_detected'] = packer_detected

    rich_entries = parse_rich_header(data)
    result['rich_header'] = rich_entries
    if rich_entries:
        result['compiler'] = identify_compiler_from_rich(rich_entries)
    else:
        result['compiler'] = f'Unknown (linker {result["linker_version"]})'

    imports = parse_imports(data, data_dirs, sections)
    result['imports'] = imports

    if 'Export' in data_dirs:
        result['exports'] = parse_exports(data, data_dirs['Export'], sections)
    else:
        result['exports'] = None

    if 'Debug' in data_dirs:
        result['debug_info'] = parse_debug_dir(data, data_dirs['Debug'], sections)
    else:
        result['debug_info'] = None

    return result


def classify_binary(result):
    fname = result['filename'].lower()
    if fname in KNOWN_THIRD_PARTY:
        return 'THIRD-PARTY', KNOWN_THIRD_PARTY[fname][0], KNOWN_THIRD_PARTY[fname][1]
    if result.get('has_clr'):
        return 'THIRD-PARTY (.NET)', 'Steamworks.NET', '.NET managed assembly - not native game code'
    packer = result.get('packer_detected', [])
    if fname == 'pal3.exe':
        detail = 'Main game executable'
        if packer:
            detail += f' (PACKED: {"; ".join(packer)})'
        return 'GAME CODE (main)', 'PAL3 Main Executable', detail
    if fname == 'config.exe':
        return 'GAME CODE (tool)', 'Configuration Tool', 'Game settings configuration utility'
    if fname == 'pal3works.exe':
        return 'WRAPPER', 'Steam Launcher', 'Launches PAL3.exe through Steam platform'
    if fname == 'gbengine.dll':
        return 'GAME CODE (engine)', 'Game Engine DLL', 'Core game engine - PRIMARY RE target'
    if fname == 'pal3.dll':
        exports = result.get('exports')
        detail = 'Small game module (24 KB)'
        if exports and exports.get('names'):
            detail += f' - {exports["num_names"]} named exports'
        return 'GAME CODE (module)', 'PAL3 Game Module', detail
    if fname == 'topo.dll':
        exports = result.get('exports')
        detail = 'Utility DLL'
        if exports and exports.get('names'):
            detail += f' - {exports["num_names"]} named exports'
        return 'UNCERTAIN', 'Topo DLL', detail
    return 'UNKNOWN', 'Unknown', ''


def format_size(size):
    if size >= 1024 * 1024:
        return f'{size:>10,} ({size/1024/1024:.1f} MB)'
    elif size >= 1024:
        return f'{size:>10,} ({size/1024:.1f} KB)'
    return f'{size:>10,}'


def sep(char='=', width=120):
    return char * width


def print_analysis(result):
    fname = result['filename']
    classification, short_desc, detail = classify_binary(result)

    print(sep('='))
    print(f"  {fname}")
    print(f"  Size: {format_size(result['size'])}    |    Classification: [{classification}] {short_desc}")
    if detail:
        print(f"  Detail: {detail}")
    print(sep('-'))

    if 'error' in result:
        print(f"  ERROR: {result['error']}")
        print()
        return classification

    print(f"  PE Type: {result['pe_type']}  |  Machine: {result['machine']}  |  "
          f"Subsystem: {result['subsystem']}  |  Linker: {result['linker_version']}")
    print(f"  Entry Point: {result['entry_point']}  |  Image Base: {result['image_base']}  |  "
          f"Timestamp: {result['timestamp_str']}")

    if result['rich_header']:
        print(f"  Rich Header: YES  |  Primary Compiler: {result['compiler']}")
        tools = set()
        for e in result['rich_header']:
            if 'Unknown' not in e['name']:
                tools.add(e['name'])
        if tools:
            tool_list = sorted(tools)
            print(f"    Tools: {', '.join(tool_list[:8])}")
            if len(tool_list) > 8:
                print(f"           {', '.join(tool_list[8:])}")
    else:
        print(f"  Rich Header: NO  |  Compiler: {result['compiler']}")

    if result.get('has_clr'):
        print(f"  ** .NET ASSEMBLY (CLR Runtime header detected) **")

    if result.get('debug_info'):
        for d in result['debug_info']:
            if 'pdb_path' in d:
                print(f"  PDB Path: {d['pdb_path']}")

    if result.get('packer_detected'):
        print(f"  !! PACKING/PROTECTION DETECTED:")
        for p in result['packer_detected']:
            print(f"     - {p}")

    # Sections
    print(f"\n  Sections ({len(result['sections'])}):")
    print(f"    {'Name':<12} {'VirtSize':>10} {'RawSize':>10} {'RVA':>10} {'Flags':<22} {'Entropy':>8}")
    print(f"    {'-'*12} {'-'*10} {'-'*10} {'-'*10} {'-'*22} {'-'*8}")
    for s in result['sections']:
        emark = ' << HIGH' if s['entropy'] > 7.0 else ''
        print(f"    {s['name']:<12} {s['vsize']:>10,} {s['raw_size']:>10,} 0x{s['va']:06X}  {s['flags_str']:<22} {s['entropy']:>7.3f}{emark}")

    # Exports
    if result.get('exports'):
        exp = result['exports']
        print(f"\n  Exports: {exp['count']} functions ({exp['num_names']} named)  [internal name: {exp['dll_name']}]")
        if exp['names']:
            shown = exp['names'][:40]
            for i in range(0, len(shown), 5):
                chunk = shown[i:i+5]
                print(f"    {', '.join(chunk)}")
            if len(exp['names']) > 40:
                print(f"    ... and {len(exp['names']) - 40} more")

    # Imports
    imports = result.get('imports', {})
    if imports:
        total_funcs = sum(len(v) for v in imports.values())
        print(f"\n  Imports: {len(imports)} DLLs, {total_funcs} functions total")

        system_dlls = []
        dx_dlls = []
        game_dlls = []
        other_dlls = []
        known_sys = {'kernel32.dll', 'user32.dll', 'gdi32.dll', 'advapi32.dll',
                     'ntdll.dll', 'shell32.dll', 'ole32.dll', 'oleaut32.dll',
                     'comctl32.dll', 'comdlg32.dll', 'msvcrt.dll', 'msvcr70.dll',
                     'msvcr71.dll', 'msvcp60.dll', 'ws2_32.dll', 'winmm.dll',
                     'shlwapi.dll', 'version.dll', 'imm32.dll', 'psapi.dll',
                     'wininet.dll', 'crypt32.dll', 'wintrust.dll', 'rpcrt4.dll',
                     'setupapi.dll', 'iphlpapi.dll', 'netapi32.dll', 'mpr.dll',
                     'userenv.dll', 'winspool.drv', 'mscoree.dll', 'wsock32.dll',
                     'msvcp70.dll', 'oledlg.dll', 'urlmon.dll', 'secur32.dll'}

        for dll, funcs in imports.items():
            dl = dll.lower()
            if dl in known_sys:
                system_dlls.append((dll, len(funcs)))
            elif dl.startswith('d3d') or dl.startswith('ddraw') or dl.startswith('dinput') or dl.startswith('dsound'):
                dx_dlls.append((dll, funcs))
            elif dl in ('gbengine.dll', 'pal3.dll', 'topo.dll', 'binkw32.dll',
                         'mss32.dll', 'ijl15.dll'):
                game_dlls.append((dll, funcs))
            else:
                other_dlls.append((dll, funcs))

        if system_dlls:
            sys_sorted = sorted(system_dlls, key=lambda x: -x[1])
            sys_summary = ', '.join(f'{d}({n})' for d, n in sys_sorted)
            print(f"    System: {sys_summary}")

        if dx_dlls:
            for dll, funcs in dx_dlls:
                sample = funcs[:10]
                extra = f' +{len(funcs)-10} more' if len(funcs) > 10 else ''
                print(f"    DirectX: {dll} ({len(funcs)} funcs): {', '.join(sample)}{extra}")

        if game_dlls:
            for dll, funcs in game_dlls:
                sample = funcs[:10]
                extra = f' +{len(funcs)-10} more' if len(funcs) > 10 else ''
                print(f"    Game/Middleware: {dll} ({len(funcs)} funcs): {', '.join(sample)}{extra}")

        if other_dlls:
            for dll, funcs in other_dlls:
                sample = funcs[:8]
                extra = f' +{len(funcs)-8} more' if len(funcs) > 8 else ''
                print(f"    Other: {dll} ({len(funcs)} funcs): {', '.join(sample)}{extra}")

    print()
    return classification


def main():
    print()
    print(sep('#'))
    print("  PAL3 PE BINARY ANALYZER")
    print(f"  Game Directory: {GAME_DIR}")
    print(f"  Date: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print(sep('#'))

    pe_files = sorted(
        glob.glob(os.path.join(GAME_DIR, '*.exe')) +
        glob.glob(os.path.join(GAME_DIR, '*.dll')),
        key=lambda x: os.path.basename(x).lower()
    )

    print(f"\n  Found {len(pe_files)} PE binaries\n")

    results = []
    for pf in pe_files:
        r = parse_pe(pf)
        results.append(r)
        print_analysis(r)

    # =========================================================================
    # SUMMARY TABLE
    # =========================================================================
    print(sep('#'))
    print("  SUMMARY TABLE")
    print(sep('#'))
    print()
    header = f"  {'File':<22} {'Size':>10}  {'Type':<6} {'Compiler/Toolchain':<28} {'Sections':<35} {'Classification'}"
    print(header)
    print(f"  {'-'*22} {'-'*10}  {'-'*6} {'-'*28} {'-'*35} {'-'*30}")

    for r in results:
        fname = r['filename']
        size_kb = f"{r['size']/1024:.0f} KB"
        pe_type = r.get('pe_type', 'N/A')
        compiler = r.get('compiler', 'N/A')
        if r.get('has_clr'):
            compiler = '.NET CLR Assembly'
        compiler = compiler[:27]
        secs = ', '.join(s['name'] for s in r.get('sections', []))
        secs = secs[:34]
        cls, short, _ = classify_binary(r)
        print(f"  {fname:<22} {size_kb:>10}  {pe_type:<6} {compiler:<28} {secs:<35} {cls}")

    # =========================================================================
    # KEY DLLs DEEP DIVE
    # =========================================================================
    print()
    print(sep('#'))
    print("  DEEP DIVE: KEY GAME DLLs (gbengine.dll, pal3.dll, topo.dll)")
    print(sep('#'))

    for r in results:
        fname = r['filename'].lower()
        if fname not in ('gbengine.dll', 'pal3.dll', 'topo.dll'):
            continue

        print()
        print(f"  {'='*60}")
        print(f"  {r['filename']}")
        print(f"  {'='*60}")

        cls, short, detail = classify_binary(r)
        print(f"  Classification: [{cls}] {detail}")
        print(f"  Size: {format_size(r['size'])}")

        if r.get('rich_header'):
            print(f"  Compiler: {r['compiler']}")
            # Show all Rich entries for detail
            print(f"  Rich Header Entries:")
            for e in r['rich_header']:
                print(f"    prodid=0x{e['prodid']:04X} build={e['build']:>5} count={e['count']:>3}  {e['name']}")
        else:
            print(f"  Compiler: {r.get('compiler', 'Unknown')} (no Rich header)")

        if r.get('packer_detected'):
            print(f"  PACKED: YES")
            for p in r['packer_detected']:
                print(f"    - {p}")
        else:
            print(f"  Packed: No (sections look normal)")

        if r.get('debug_info'):
            for d in r['debug_info']:
                if 'pdb_path' in d:
                    print(f"  PDB Path: {d['pdb_path']}")
                else:
                    print(f"  Debug Entry: {d['type']} (no PDB path)")

        exports = r.get('exports')
        if exports:
            print(f"  Exports: {exports['count']} functions, {exports['num_names']} named")
            if exports['names']:
                cpp_mangled = [n for n in exports['names'] if n.startswith('?')]
                c_style = [n for n in exports['names'] if not n.startswith('?') and not n.startswith('_')]
                underscore = [n for n in exports['names'] if n.startswith('_') and not n.startswith('__')]
                dunder = [n for n in exports['names'] if n.startswith('__')]

                if cpp_mangled:
                    print(f"    C++ mangled names: {len(cpp_mangled)}")
                    for n in cpp_mangled[:15]:
                        print(f"      {n}")
                    if len(cpp_mangled) > 15:
                        print(f"      ... and {len(cpp_mangled)-15} more")
                if c_style:
                    print(f"    C-style names ({len(c_style)}): {', '.join(c_style[:20])}")
                    if len(c_style) > 20:
                        print(f"      ... and {len(c_style)-20} more")
                if underscore:
                    print(f"    _prefixed names ({len(underscore)}): {', '.join(underscore[:15])}")
                if dunder:
                    print(f"    __prefixed names ({len(dunder)}): {', '.join(dunder[:10])}")

                ordinal_only = exports['count'] - exports['num_names']
                if ordinal_only > 0:
                    print(f"    Ordinal-only (unnamed) exports: {ordinal_only}")
        else:
            print(f"  Exports: NONE")

        imports = r.get('imports', {})
        if imports:
            print(f"  Imports: {len(imports)} DLLs")
            for dll, funcs in imports.items():
                if len(funcs) <= 15:
                    print(f"    {dll} ({len(funcs)}): {', '.join(funcs)}")
                else:
                    print(f"    {dll} ({len(funcs)}): {', '.join(funcs[:12])}")
                    print(f"      +{len(funcs)-12} more")

        # Assessment
        print()
        if r.get('packer_detected'):
            print(f"  >> RE ASSESSMENT: DIFFICULT - Binary is packed/protected.")
            print(f"     Must unpack first. Use process dump at runtime.")
        elif r.get('has_clr'):
            print(f"  >> RE ASSESSMENT: EASY - .NET assembly, use dnSpy/ILSpy.")
        elif exports and exports['num_names'] > 20:
            print(f"  >> RE ASSESSMENT: MODERATE - Many named exports help structure analysis.")
            print(f"     Load in IDA/Ghidra, exports provide good starting points.")
        elif exports and exports['count'] > 0:
            print(f"  >> RE ASSESSMENT: MODERATE - Has exports but some are ordinal-only.")
        else:
            print(f"  >> RE ASSESSMENT: MODERATE - Standard native binary.")

    # =========================================================================
    # DEPENDENCY MAP
    # =========================================================================
    print()
    print(sep('#'))
    print("  DEPENDENCY MAP (game binaries only)")
    print(sep('#'))
    print()

    game_dlls_set = {'gbengine.dll', 'pal3.dll', 'topo.dll', 'binkw32.dll', 'mss32.dll', 'ijl15.dll'}

    for r in results:
        imports = r.get('imports', {})
        deps = []
        for dll in imports:
            if dll.lower() in game_dlls_set:
                deps.append((dll, len(imports[dll])))
        if deps:
            for dll, count in deps:
                print(f"  {r['filename']:<22} --({count:>3} funcs)--> {dll}")

    # =========================================================================
    # RECOMMENDATIONS
    # =========================================================================
    print()
    print(sep('#'))
    print("  FINAL RECOMMENDATIONS FOR REVERSE ENGINEERING")
    print(sep('#'))
    print("""
  PRIORITY 1: gbengine.dll (1.2 MB)
    - This is the core game engine DLL, the PRIMARY reverse engineering target.
    - Contains DirectX rendering, scene graph, physics, resource management.
    - PAL3patch project references it as "gboffset" - meaning RE work has
      already been done to identify key offsets/functions.
    - Start with: exported functions, DirectX vtable hooks, string references.

  PRIORITY 2: PAL3.exe (1.8 MB) -- BUT PACKED
    - Main game executable with game logic, scripting, UI.
    - PACKED with StarForce (.sforce/.brick sections detected).
    - Must dump from memory at runtime to get unpacked version.
    - After unpacking, this becomes a high-priority target.

  PRIORITY 3: pal3.dll (24 KB)
    - Very small module - likely a thin wrapper or plugin interface.
    - Analyze exports to understand its role.
    - Quick to reverse due to small size.

  PRIORITY 4: topo.dll (104 KB)
    - Unknown purpose. "Topo" could relate to topology/terrain/map data.
    - Analyze exports and imports to determine if it's game code
      or a third-party library.
    - Medium priority - reverse if exports suggest game functionality.

  SKIP (third-party, do not reverse):
    - binkw32.dll   -> RAD Game Tools Bink Video (use known API)
    - Mss32.dll     -> RAD Game Tools Miles Sound System (use known API)
    - ijl15.dll     -> Intel JPEG Library (use known API)
    - steam_api.dll -> Valve Steamworks (use known API)
    - Steamworks.NET.dll -> .NET wrapper (use known API)
    - config.exe    -> Settings tool (low priority)
    - Pal3Works.exe -> Steam launcher wrapper (low priority)
""")


if __name__ == '__main__':
    main()
