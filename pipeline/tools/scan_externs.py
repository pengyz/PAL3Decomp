"""
Extern Declaration Scanner — systematic analysis of all forward-declared
functions and global variables across generated .cpp files.

Usage:
    python pipeline/tools/scan_externs.py        # scan + print report
    python pipeline/tools/scan_externs.py --fix   # scan + apply batch fixes
"""
import json, glob, re, os, sys
from collections import defaultdict
from pathlib import Path

SRC_DIR = Path('src/pal3/gen')
FUNC_JSON = Path('data/annotations/functions.json')
GLOB_JSON = Path('data/annotations/globals.json')
IDA_STRUCTS = Path('asm/pal3/ida_structs.json')
DECOMP_DIR = Path('asm/pal3/decomp')

def load_json(path):
    try:
        return json.load(open(str(path)))
    except:
        return {}

def addr_key(addr):
    """Normalize address to lowercase hex string."""
    if isinstance(addr, int):
        return '0x' + format(addr, '08x')
    return addr.replace('0X', '0x').lower() if addr.startswith('0x') else addr

def scan_externs():
    """Scan all .cpp files for extern forward declarations."""
    functions = load_json(FUNC_JSON)
    globals_data = load_json(GLOB_JSON)
    ida = load_json(IDA_STRUCTS)
    _globals = ida.get('_globals', {})
    
    # Build normalized _globals lookup
    norm_globals = {}
    for k, v in _globals.items():
        norm_globals[addr_key(k)] = v
    
    results = {
        'files_with_externs': 0,
        'total_sub_funcs': 0,
        'total_globals': 0,
        'funcs_in_fjson': 0,     # in functions.json
        'funcs_not_in_fjson': 0,  # NOT in functions.json
        'funcs_thiscall_mismatch': 0,  # __cdecl in fjson but __thiscall in decomp
        'globals_in_gjson': 0,
        'globals_not_in_gjson': 0,
        'globals_with_type': 0,
        'globals_without_type': 0,
        'func_details': [],
        'global_details': [],
        'files': {},
    }
    
    cpp_files = sorted(SRC_DIR.rglob('*.cpp'))
    
    for fpath in cpp_files:
        rel = fpath.relative_to(SRC_DIR.parent.parent).as_posix()
        try:
            content = fpath.read_text(encoding='utf-8', errors='replace')
        except:
            continue
        
        # Extract forward declaration sections
        func_section = re.search(r'// Forward declarations for unnamed functions\n(.*?)(?=\n//|\Z)', content, re.DOTALL)
        global_section = re.search(r'// Unnamed globals \(extern\)\n(.*?)(?=\n//|\Z)', content, re.DOTALL)
        
        funcs = []
        globs = []
        
        if func_section:
            for line in func_section.group(1).strip().split('\n'):
                line = line.strip()
                if not line:
                    continue
                m = re.match(r'(?:void|int|char|float|double|\w+\s*\*?)\s+(\w+)\(.*?\)', line)
                if m:
                    funcs.append(m.group(1))
        
        if global_section:
            for line in global_section.group(1).strip().split('\n'):
                line = line.strip()
                if not line:
                    continue
                m = re.match(r'extern\s+(?:\w+\s+)+\*?\s*(\w+);', line)
                if m:
                    globs.append(m.group(1))
        
        if not funcs and not globs:
            continue
        
        results['files_with_externs'] += 1
        results['total_sub_funcs'] += len(funcs)
        results['total_globals'] += len(globs)
        results['files'][rel] = {'funcs': funcs, 'globs': globs}
        
        # Analyze each function
        for fn in funcs:
            info = analyze_function(fn, functions, DECOMP_DIR)
            results['func_details'].append(info)
            if info['in_functions_json']:
                results['funcs_in_fjson'] += 1
            else:
                results['funcs_not_in_fjson'] += 1
            if info['thiscall_mismatch']:
                results['funcs_thiscall_mismatch'] += 1
        
        # Analyze each global
        for gn in globs:
            info = analyze_global(gn, globals_data, norm_globals)
            results['global_details'].append(info)
            if info['in_globals_json']:
                results['globals_in_gjson'] += 1
            else:
                results['globals_not_in_gjson'] += 1
            if info['has_type']:
                results['globals_with_type'] += 1
            else:
                results['globals_without_type'] += 1
    
    return results

def analyze_function(fn, functions, decomp_dir):
    """Analyze a function extern."""
    info = {
        'name': fn,
        'in_functions_json': False,
        'fjson_sig': '',
        'has_decomp': False,
        'decomp_sig': '',
        'decomp_class': '',
        'thiscall_mismatch': False,
        'action': '',
    }
    
    # Check functions.json by searching name in values
    for addr, entry in functions.items():
        if entry.get('name') == fn or entry.get('name') == fn.split('(')[0]:
            info['in_functions_json'] = True
            info['fjson_sig'] = entry.get('signature', '')
            info['fjson_addr'] = addr
            break
    
    # Search decomp JSON
    decomp_files = list(decomp_dir.glob('*' + fn + '*.json'))
    if decomp_files:
        try:
            d = json.load(open(str(decomp_files[0])))
            info['has_decomp'] = True
            info['decomp_sig'] = d.get('signature', '')
            dname = d.get('name', '')
            if '::' in dname:
                info['decomp_class'] = dname.split('::')[0]
            # Check __thiscall mismatch
            if '__thiscall' in info['decomp_sig'] and '__cdecl' in info['fjson_sig']:
                info['thiscall_mismatch'] = True
                info['action'] = 'FIX_SIGNATURE'
        except:
            pass
    
    if not info['in_functions_json'] and info['has_decomp']:
        if info['decomp_class']:
            info['action'] = 'ADD_TO_STRUCT'  # belongs to a class
        elif '__thiscall' in info['decomp_sig']:
            info['action'] = 'ADD_TO_FJSON_THISCALL'
        else:
            info['action'] = 'ADD_TO_FJSON'
    elif not info['in_functions_json']:
        info['action'] = 'NO_DECOMP'
    
    return info

def analyze_global(gname, globals_data, norm_globals):
    """Analyze a global variable extern."""
    info = {
        'name': gname,
        'address': '',
        'in_globals_json': False,
        'has_type': False,
        'known_type': '',
        'action': '',
    }
    
    # Derive address from name: dword_5D4DAC -> 0x005d4dac
    prefix = gname.split('_')[0]
    addr_str = gname[len(prefix)+1:]
    try:
        addr_int = int(addr_str, 16)
        # Format address: for 0x005D4DAC, it could be 0x5D4DAC or 0x005D4DAC
        addr_8 = '0x' + format(addr_int, '08x').lower()
        addr_short = '0x' + format(addr_int, 'x').lower()
        info['address'] = addr_8
    except:
        info['action'] = 'INVALID_ADDRESS'
        return info
    
    # Check globals.json
    if addr_8 in globals_data:
        info['in_globals_json'] = True
        entry = globals_data[addr_8]
        info['known_type'] = entry.get('type', '')
        info['has_type'] = bool(info['known_type'])
        if entry.get('type') == 'skip':
            info['action'] = 'ALREADY_SKIPPED'
        elif info['has_type']:
            info['action'] = 'ALREADY_NAMED'
        return info
    
    # Check _globals in ida_structs
    if addr_8 in norm_globals:
        g = norm_globals[addr_8]
        info['known_type'] = g.get('type', '')
        info['has_type'] = bool(info['known_type'])
        info['in_globals_json'] = False
        info['action'] = 'ADD_TO_GJSON' if info['has_type'] else 'ADD_TO_GJSON_UNKNOWN'
        return info
    elif addr_short in norm_globals:
        g = norm_globals[addr_short]
        info['known_type'] = g.get('type', '')
        info['has_type'] = bool(info['known_type'])
        info['action'] = 'ADD_TO_GJSON' if info['has_type'] else 'ADD_TO_GJSON_UNKNOWN'
        return info
    
    info['action'] = 'ADD_TO_GJSON_UNKNOWN'
    return info

def print_report(results):
    """Print structured report."""
    print('=' * 60)
    print('EXTERN DECLARATION SCAN RESULTS')
    print('=' * 60)
    print(f'\nFiles with externs: {results["files_with_externs"]}')
    print(f'Total function externs: {results["total_sub_funcs"]}')
    print(f'Total global externs: {results["total_globals"]}')
    print()
    
    print('--- FUNCTIONS ---')
    print(f'  In functions.json:           {results["funcs_in_fjson"]}')
    print(f'  NOT in functions.json:       {results["funcs_not_in_fjson"]}')
    print(f'  __thiscall mismatch:         {results["funcs_thiscall_mismatch"]}')
    print()
    
    print('--- GLOBALS ---')
    print(f'  In globals.json:             {results["globals_in_gjson"]}')
    print(f'  NOT in globals.json:         {results["globals_not_in_gjson"]}')
    print(f'  With known type:             {results["globals_with_type"]}')
    print(f'  Without type:                {results["globals_without_type"]}')
    print()
    
    # Print actionable items
    print('--- ACTIONABLE: __thiscall mismatches (FIX SIGNATURE) ---')
    for d in results['func_details']:
        if d['thiscall_mismatch']:
            print(f'  {d["name"]}: fjson={d["fjson_sig"]} -> decomp={d["decomp_sig"]}')
    
    print(f'\n--- ACTIONABLE: Functions NOT in functions.json with class ---')
    for d in results['func_details']:
        if d['action'] == 'ADD_TO_STRUCT':
            print(f'  {d["name"]}: class={d["decomp_class"]}, sig={d["decomp_sig"]}')
    
    print(f'\n--- ACTIONABLE: Globals not in globals.json (with known type) ---')
    for d in results['global_details']:
        if d['action'] == 'ADD_TO_GJSON' and d['has_type']:
            print(f'  {d["name"]} ({d["address"]}): type={d["known_type"]}')
    
    print(f'\n--- ACTIONABLE: Globals not in globals.json (no type) ---')
    for d in results['global_details']:
        if d['action'] == 'ADD_TO_GJSON_UNKNOWN':
            print(f'  {d["name"]} ({d["address"]})')
    
    # Print per-file summary (top 10)
    print(f'\n--- PER-FILE SUMMARY (top files) ---')
    file_func_counts = [(f, len(v['funcs']), len(v['globs'])) 
                        for f, v in sorted(results['files'].items(),
                        key=lambda x: len(x[1]['funcs']) + len(x[1]['globs']), reverse=True)[:10]]
    for f, fc, gc in file_func_counts:
        print(f'  {f}: {fc} funcs, {gc} globals')

def apply_fixes(results):
    """Apply batch fixes for annotation-repairable issues."""
    functions = load_json(FUNC_JSON)
    globals_data = load_json(GLOB_JSON)
    
    fix_count = 0
    
    # Fix 1: __thiscall mismatches — update functions.json signatures
    for d in results['func_details']:
        if d['thiscall_mismatch'] and 'fjson_addr' in d:
            addr = d['fjson_addr']
            decomp_sig = d['decomp_sig']
            # Replace __cdecl with __thiscall but keep parameters
            new_sig = decomp_sig  # Use decomp signature as-is
            old_sig = functions[addr]['signature']
            if old_sig != new_sig:
                print(f'  FIX: {d["name"]}: {old_sig} -> {new_sig}')
                functions[addr]['signature'] = new_sig
                fix_count += 1
    
    if fix_count:
        with open(str(FUNC_JSON), 'w') as fh:
            json.dump(functions, fh, indent=2)
        print(f'\nFixed {fix_count} function signatures.')
    
    # Fix 2: Globals not in globals.json — add with type
    fix_count2 = 0
    for d in results['global_details']:
        if d['action'].startswith('ADD_TO_GJSON') and d['address']:
            if d['address'] not in globals_data:
                name = d['name']
                gtype = d['known_type'] if d['has_type'] else 'int'
                entry = {
                    'name': name,
                    'type': gtype,
                    'reason': 'auto-scanned extern global'
                }
                globals_data[d['address']] = entry
                print(f'  ADD: {d["address"]} -> {name} ({gtype})')
                fix_count2 += 1
    
    if fix_count2:
        with open(str(GLOB_JSON), 'w') as fh:
            json.dump(globals_data, fh, indent=2)
        print(f'\nAdded {fix_count2} globals to globals.json.')
    
    print(f'\nTotal fixes applied: {fix_count + fix_count2}')

if __name__ == '__main__':
    apply_fix = '--fix' in sys.argv
    results = scan_externs()
    print_report(results)
    if apply_fix:
        print('\n' + '=' * 60)
        print('APPLYING FIXES')
        print('=' * 60)
        apply_fixes(results)
    else:
        print('\n' + '=' * 60)
        print('DRY RUN — no changes made. Use --fix to apply fixes.')
        print('=' * 60)
