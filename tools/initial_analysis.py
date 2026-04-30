#!/usr/bin/env python3
"""
Ghidra Initial Analysis Post-Script for PAL3.

Run after importing PAL3.exe into Ghidra to perform reconnaissance:
1. Check for RTTI (Run-Time Type Information)
2. Detect third-party library code via known signatures
3. Classify functions by module (address range heuristics)
4. Identify leaf functions (no calls to other unknown functions)
5. Sort functions by size for prioritization
6. Output a comprehensive analysis report

Usage via Ghidra headless:
    analyzeHeadless /path/to/project PAL3Project \
        -process PAL3.exe \
        -postScript initial_analysis.py --output-dir ./asm

Standalone mode (reads from previously exported _function_list.json):
    python initial_analysis.py --function-list asm/_function_list.json
"""

try:
    from ghidra.app.decompiler import DecompInterface
    from ghidra.program.model.symbol import SourceType
    from ghidra.util.task import ConsoleTaskMonitor
    GHIDRA_ENV = True
except ImportError:
    GHIDRA_ENV = False

import json
import os
import re
import sys
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ASM_DIR = PROJECT_ROOT / "asm"
BUILD_DIR = PROJECT_ROOT / "build"


# ========================================================================
# RTTI Detection
# ========================================================================

def find_rtti_info(program):
    """Search for MSVC RTTI structures in the binary."""
    rtti_classes = []
    memory = program.getMemory()
    listing = program.getListing()

    # MSVC RTTI: look for ".?AV" prefix in type descriptor names
    # These appear as ASCII strings in .rdata section
    rdata_block = None
    for block in memory.getBlocks():
        if block.getName() in ('.rdata', '.data'):
            rdata_block = block
            break

    if not rdata_block:
        return rtti_classes

    # Search for RTTI type descriptor signature ".?AV"
    addr = rdata_block.getStart()
    end = rdata_block.getEnd()

    while addr and addr.compareTo(end) < 0:
        try:
            # Read 4 bytes looking for ".?AV" pattern
            b = bytearray(4)
            memory.getBytes(addr, b)
            if b == bytearray(b'.?AV'):
                # Found RTTI type descriptor, read the class name
                name_bytes = bytearray(256)
                memory.getBytes(addr, name_bytes)
                # Null-terminate
                null_idx = name_bytes.find(0)
                if null_idx > 0:
                    name = name_bytes[:null_idx].decode('ascii', errors='ignore')
                    # Parse mangled name: .?AVClassName@@
                    match = re.match(r'\.?\?AV(.+?)@@', name)
                    if match:
                        class_name = match.group(1)
                        rtti_classes.append({
                            'address': str(addr),
                            'mangled': name,
                            'class_name': class_name,
                        })
            addr = addr.add(1)
        except Exception:
            addr = addr.add(1)
            continue

    return rtti_classes


# ========================================================================
# Third-party Library Detection
# ========================================================================

# Known function signatures for common game middleware
KNOWN_LIBRARY_SIGNATURES = {
    'DirectX 8 (D3D)': [
        'Direct3DCreate8', 'IDirect3D8', 'IDirect3DDevice8',
        'd3d8.dll',
    ],
    'DirectX 9 (D3D)': [
        'Direct3DCreate9', 'IDirect3D9', 'IDirect3DDevice9',
        'd3d9.dll',
    ],
    'DirectInput': [
        'DirectInput8Create', 'dinput8.dll', 'IDirectInput8',
    ],
    'DirectSound': [
        'DirectSoundCreate', 'dsound.dll', 'IDirectSound',
    ],
    'DirectMusic': [
        'CoCreateInstance', 'dmime.dll', 'IDirectMusicPerformance',
    ],
    'DirectShow': [
        'IGraphBuilder', 'IMediaControl', 'quartz.dll',
    ],
    'Bink Video': [
        'BinkOpen', 'BinkDoFrame', 'BinkCopyToBuffer',
        'binkw32.dll', 'BinkNextFrame', 'BinkWait',
    ],
    'Miles Sound System': [
        'AIL_startup', 'AIL_open_digital_driver', 'mss32.dll',
        'AIL_allocate_sample_handle',
    ],
    'Windows Media': [
        'wmvcore.dll', 'IWMReader',
    ],
    'CRT (MSVCRT)': [
        'msvcrt.dll', 'msvcr71.dll', 'msvcp71.dll',
        'msvcr70.dll', 'msvcp70.dll',
    ],
    'MFC': [
        'mfc42.dll', 'mfc71.dll',
    ],
    'Lua': [
        'lua_open', 'lua_pcall', 'lua_pushstring',
        'luaL_loadfile', 'lua_State',
    ],
    'zlib': [
        'inflate', 'deflate', 'uncompress', 'compress',
        'inflateInit_', 'deflateInit_',
    ],
    'STL (MSVC)': [
        'std::basic_string', 'std::vector', 'std::map',
        'std::_Tree', 'std::_Vector_val',
    ],
}


def detect_libraries_from_imports(program):
    """Detect third-party libraries from the import table."""
    detected = defaultdict(list)
    ext_mgr = program.getExternalManager()

    # Get all imported library names
    import_libs = set()
    for lib_name in ext_mgr.getExternalLibraryNames():
        import_libs.add(lib_name.lower())
        # Check each import against known signatures
        for category, signatures in KNOWN_LIBRARY_SIGNATURES.items():
            for sig in signatures:
                if sig.lower() in lib_name.lower():
                    detected[category].append(lib_name)
                    break

        # Also check individual function imports
        ext_locs = ext_mgr.getExternalLocations(lib_name)
        for loc in ext_locs:
            func_name = loc.getLabel()
            for category, signatures in KNOWN_LIBRARY_SIGNATURES.items():
                for sig in signatures:
                    if sig.lower() in func_name.lower():
                        if func_name not in detected[category]:
                            detected[category].append(func_name)

    return dict(detected), list(import_libs)


def detect_libraries_from_strings(program):
    """Detect libraries by searching for known string patterns."""
    detected = {}
    # This would search .rdata for known strings
    # Simplified version - full implementation would scan data sections
    return detected


# ========================================================================
# Function Classification
# ========================================================================

def classify_functions(program):
    """Classify all functions and gather statistics."""
    func_mgr = program.getFunctionManager()
    listing = program.getListing()
    ref_mgr = program.getReferenceManager()

    functions = []
    total_code_bytes = 0

    for func in func_mgr.getFunctions(True):
        if func.isExternal():
            continue

        entry = func.getEntryPoint()
        size = func.getBody().getNumAddresses()
        total_code_bytes += size

        # Determine if leaf function (doesn't call other internal functions)
        is_leaf = True
        callees_internal = []
        callees_external = []

        refs = ref_mgr.getReferenceIterator(func.getBody().getMinAddress())
        while refs.hasNext():
            ref = refs.next()
            if not func.getBody().contains(ref.getFromAddress()):
                continue
            if ref.getReferenceType().isCall():
                to_addr = ref.getToAddress()
                called_func = func_mgr.getFunctionAt(to_addr)
                if called_func:
                    if called_func.isExternal() or called_func.isThunk():
                        callees_external.append(called_func.getName())
                    else:
                        callees_internal.append(str(to_addr))
                        is_leaf = False

        # Count callers
        caller_count = 0
        refs_to = ref_mgr.getReferencesTo(entry)
        for ref in refs_to:
            if ref.getReferenceType().isCall():
                caller_count += 1

        # Check for string references (helps with naming)
        string_refs = []
        for addr in func.getBody().getAddresses(True):
            data_refs = ref_mgr.getReferencesFrom(addr)
            for dref in data_refs:
                if dref.getReferenceType().isData():
                    data = listing.getDefinedDataAt(dref.getToAddress())
                    if data and 'string' in str(data.getDataType()).lower():
                        try:
                            val = str(data.getValue())
                            if len(val) > 2:
                                string_refs.append(val[:100])
                        except Exception:
                            pass

        func_info = {
            'address': "0x{:08x}".format(entry.getOffset()),
            'name': func.getName(),
            'size_bytes': size,
            'is_thunk': func.isThunk(),
            'is_leaf': is_leaf,
            'has_custom_name': func.getSymbol().getSource() != SourceType.DEFAULT,
            'calling_convention': str(func.getCallingConventionName()),
            'callees_internal_count': len(callees_internal),
            'callees_external': callees_external[:10],
            'caller_count': caller_count,
            'string_refs': string_refs[:5],
        }
        functions.append(func_info)

    return functions, total_code_bytes


def assign_modules(functions):
    """
    Heuristic module assignment based on function characteristics.

    This is a rough initial classification that should be refined manually.
    """
    for func in functions:
        ext_calls = [c.lower() for c in func.get('callees_external', [])]
        strings = ' '.join(func.get('string_refs', [])).lower()
        addr = int(func['address'], 16)

        module = 'unknown'

        # Heuristic classification based on API calls and strings
        if any('d3d' in c or 'direct3d' in c for c in ext_calls):
            module = 'core/render'
        elif any('dinput' in c for c in ext_calls):
            module = 'core/input'
        elif any('dsound' in c or 'directsound' in c or 'ail_' in c for c in ext_calls):
            module = 'core/audio'
        elif any('bink' in c for c in ext_calls):
            module = 'core/video'
        elif any('createfile' in c or 'readfile' in c or 'writefile' in c for c in ext_calls):
            module = 'core/io'
        elif any(s in strings for s in ['battle', 'attack', 'damage', 'hp', 'mp']):
            module = 'game/battle'
        elif any(s in strings for s in ['script', 'sce', 'command', 'opcode']):
            module = 'game/script'
        elif any(s in strings for s in ['dialog', 'menu', 'button', 'ui_']):
            module = 'game/ui'
        elif any(s in strings for s in ['save', 'load', 'slot']):
            module = 'game/save'
        elif any('malloc' in c or 'free' in c or 'realloc' in c for c in ext_calls):
            if func['size_bytes'] < 100:
                module = 'core/memory'

        func['module'] = module

    return functions


# ========================================================================
# Report Generation
# ========================================================================

def generate_report(functions, total_code_bytes, rtti_classes,
                    libraries, import_libs, output_dir):
    """Generate the analysis report."""
    output_dir = Path(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    # Summary statistics
    total_funcs = len(functions)
    leaf_funcs = sum(1 for f in functions if f.get('is_leaf'))
    thunk_funcs = sum(1 for f in functions if f.get('is_thunk'))
    named_funcs = sum(1 for f in functions if f.get('has_custom_name'))
    non_thunk = [f for f in functions if not f.get('is_thunk')]

    # Size distribution
    size_buckets = {
        '1-20 bytes': 0,
        '21-50 bytes': 0,
        '51-100 bytes': 0,
        '101-500 bytes': 0,
        '501-1000 bytes': 0,
        '1001-5000 bytes': 0,
        '5000+ bytes': 0,
    }
    for f in non_thunk:
        s = f['size_bytes']
        if s <= 20:
            size_buckets['1-20 bytes'] += 1
        elif s <= 50:
            size_buckets['21-50 bytes'] += 1
        elif s <= 100:
            size_buckets['51-100 bytes'] += 1
        elif s <= 500:
            size_buckets['101-500 bytes'] += 1
        elif s <= 1000:
            size_buckets['501-1000 bytes'] += 1
        elif s <= 5000:
            size_buckets['1001-5000 bytes'] += 1
        else:
            size_buckets['5000+ bytes'] += 1

    # Module distribution
    module_counts = defaultdict(int)
    for f in non_thunk:
        module_counts[f.get('module', 'unknown')] += 1

    report = {
        'summary': {
            'total_functions': total_funcs,
            'non_thunk_functions': len(non_thunk),
            'thunk_functions': thunk_funcs,
            'leaf_functions': leaf_funcs,
            'named_functions': named_funcs,
            'total_code_bytes': total_code_bytes,
            'avg_function_size': total_code_bytes // max(1, len(non_thunk)),
        },
        'size_distribution': size_buckets,
        'module_distribution': dict(module_counts),
        'rtti_classes': rtti_classes,
        'detected_libraries': libraries,
        'imported_dlls': import_libs,
    }

    # Write full report
    report_path = output_dir / '_analysis_report.json'
    with open(report_path, 'w', encoding='utf-8') as f:
        json.dump(report, f, indent=2, ensure_ascii=False)

    # Write function list sorted by size (smallest first)
    sorted_funcs = sorted(non_thunk, key=lambda x: x['size_bytes'])
    func_list_path = output_dir / '_function_list.json'
    with open(func_list_path, 'w', encoding='utf-8') as f:
        json.dump(sorted_funcs, f, indent=2, ensure_ascii=False)

    # Write leaf function list
    leaf_list = [f for f in sorted_funcs if f.get('is_leaf')]
    leaf_path = output_dir / '_leaf_functions.json'
    with open(leaf_path, 'w', encoding='utf-8') as f:
        json.dump(leaf_list, f, indent=2, ensure_ascii=False)

    # Print summary
    print("\n" + "=" * 60)
    print("  PAL3 Initial Analysis Report")
    print("=" * 60)
    print()
    print("  Functions:")
    print("    Total:            {}".format(total_funcs))
    print("    Non-thunk:        {}".format(len(non_thunk)))
    print("    Thunks:           {}".format(thunk_funcs))
    print("    Leaf functions:   {}".format(leaf_funcs))
    print("    With names:       {}".format(named_funcs))
    print()
    print("  Code Size:          {:,} bytes ({:.1f} KB)".format(
        total_code_bytes, total_code_bytes / 1024))
    print("  Avg function size:  {} bytes".format(
        total_code_bytes // max(1, len(non_thunk))))
    print()
    print("  Size Distribution:")
    for bucket, count in size_buckets.items():
        bar = '#' * min(count // 5, 30)
        print("    {:20s} {:>5d}  {}".format(bucket, count, bar))
    print()

    if rtti_classes:
        print("  RTTI Classes Found: {}".format(len(rtti_classes)))
        for cls in rtti_classes[:20]:
            print("    - {}".format(cls['class_name']))
        if len(rtti_classes) > 20:
            print("    ... ({} more)".format(len(rtti_classes) - 20))
        print()

    if libraries:
        print("  Detected Libraries:")
        for lib, funcs in libraries.items():
            print("    - {} ({} references)".format(lib, len(funcs)))
        print()

    if import_libs:
        print("  Imported DLLs:")
        for dll in sorted(import_libs):
            print("    - {}".format(dll))
        print()

    print("  Module Classification (heuristic):")
    for module, count in sorted(module_counts.items()):
        print("    {:25s} {:>5d} functions".format(module, count))
    print()
    print("  Reports saved to: {}".format(output_dir))
    print("=" * 60)

    return report


# ========================================================================
# Ghidra Entry Point
# ========================================================================

def run_ghidra():
    """Main entry point when running inside Ghidra."""
    # Parse args
    script_args = getScriptArgs()  # noqa: F821
    output_dir = str(ASM_DIR)
    for i, arg in enumerate(script_args):
        if arg == '--output-dir' and i + 1 < len(script_args):
            output_dir = script_args[i + 1]

    program = currentProgram  # noqa: F821

    print("[*] Starting initial analysis of {}...".format(program.getName()))

    # Step 1: RTTI
    print("[*] Searching for RTTI information...")
    rtti_classes = find_rtti_info(program)
    print("    Found {} RTTI classes".format(len(rtti_classes)))

    # Step 2: Library detection
    print("[*] Detecting third-party libraries...")
    libraries, import_libs = detect_libraries_from_imports(program)
    print("    Found {} library categories".format(len(libraries)))

    # Step 3: Function classification
    print("[*] Classifying functions...")
    functions, total_code_bytes = classify_functions(program)
    functions = assign_modules(functions)
    print("    Classified {} functions".format(len(functions)))

    # Step 4: Generate report
    generate_report(functions, total_code_bytes, rtti_classes,
                    libraries, import_libs, output_dir)


# ========================================================================
# Standalone Mode (works with previously exported data)
# ========================================================================

def run_standalone(function_list_path):
    """Run analysis on previously exported function list."""
    print("[*] Loading function list from: {}".format(function_list_path))

    with open(function_list_path, 'r') as f:
        functions = json.load(f)

    total_code_bytes = sum(f.get('size_bytes', 0) for f in functions)

    # Module assignment
    functions = assign_modules(functions)

    # Generate report (without RTTI/imports which need the binary)
    output_dir = str(Path(function_list_path).parent)
    generate_report(functions, total_code_bytes, [], {}, [], output_dir)


# Entry point
if GHIDRA_ENV:
    run_ghidra()
elif __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser(
        description="PAL3 Initial Analysis (standalone mode)")
    parser.add_argument('--function-list', '-f',
                        help='Path to _function_list.json from Ghidra export')
    args = parser.parse_args()

    if args.function_list:
        run_standalone(args.function_list)
    else:
        print("Standalone mode: requires --function-list <path>")
        print("Full mode: run inside Ghidra headless analyzer")
        print()
        print("Usage:")
        print("  Ghidra:      analyzeHeadless ... -postScript initial_analysis.py")
        print("  Standalone:  python initial_analysis.py -f asm/_function_list.json")
