#!/usr/bin/env python3
"""
Function Rename Helper for PAL3 Decompilation.

Analyzes Ghidra-exported function data to suggest meaningful names for
FUN_XXXXXXXX functions based on:
- String references within the function
- API calls made by the function
- Pattern matching against known function signatures
- Relationship with already-named functions

Outputs a Ghidra-compatible rename script (.py) that can be run to apply names.

Usage:
    python rename_helper.py                        # Suggest names for all
    python rename_helper.py --address 0x00401000   # Single function
    python rename_helper.py --apply                # Generate Ghidra rename script
    python rename_helper.py --interactive          # Review one-by-one
"""

import argparse
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ASM_DIR = PROJECT_ROOT / "asm"
BUILD_DIR = PROJECT_ROOT / "build"


# Pattern recognition rules
# Maps API call patterns to likely function purpose
API_PATTERNS = {
    # Rendering
    'render': {
        'calls': ['CreateDevice', 'SetRenderState', 'DrawPrimitive', 'DrawIndexedPrimitive',
                  'SetTexture', 'SetTransform', 'BeginScene', 'EndScene', 'Present',
                  'CreateVertexBuffer', 'CreateIndexBuffer'],
        'prefix': 'Render_',
    },
    'texture': {
        'calls': ['CreateTexture', 'D3DXCreateTextureFromFile', 'SetTexture',
                  'LockRect', 'UnlockRect'],
        'prefix': 'Texture_',
    },
    # Input
    'input': {
        'calls': ['GetDeviceState', 'GetDeviceData', 'Acquire', 'Unacquire',
                  'DirectInput8Create', 'CreateDevice'],
        'prefix': 'Input_',
    },
    # Audio
    'audio': {
        'calls': ['DirectSoundCreate', 'CreateSoundBuffer', 'Play', 'Stop',
                  'SetVolume', 'AIL_', 'BinkOpen'],
        'prefix': 'Audio_',
    },
    # File I/O
    'file_io': {
        'calls': ['CreateFileA', 'CreateFileW', 'ReadFile', 'WriteFile',
                  'CloseHandle', 'SetFilePointer', 'GetFileSize',
                  'fopen', 'fread', 'fwrite', 'fclose', 'fseek'],
        'prefix': 'File_',
    },
    # Memory
    'memory': {
        'calls': ['malloc', 'free', 'realloc', 'calloc',
                  'HeapAlloc', 'HeapFree', 'VirtualAlloc', 'VirtualFree',
                  'new', 'delete'],
        'prefix': 'Mem_',
    },
    # String
    'string': {
        'calls': ['strlen', 'strcpy', 'strcat', 'strcmp', 'strncpy',
                  'sprintf', 'sscanf', 'atoi', 'atof',
                  'wcslen', 'wcscpy', 'MultiByteToWideChar'],
        'prefix': 'Str_',
    },
    # Window/UI
    'window': {
        'calls': ['CreateWindowEx', 'ShowWindow', 'UpdateWindow',
                  'GetMessage', 'DispatchMessage', 'DefWindowProc',
                  'RegisterClass', 'SetWindowPos'],
        'prefix': 'Win_',
    },
    # Math
    'math': {
        'calls': ['sin', 'cos', 'sqrt', 'atan2', 'pow', 'fabs',
                  'D3DXMatrixMultiply', 'D3DXVec3Transform',
                  'D3DXMatrixRotation', 'D3DXMatrixTranslation'],
        'prefix': 'Math_',
    },
}

# String-based naming patterns
STRING_PATTERNS = [
    # (regex_pattern, name_template)
    (r'(?:error|err|fail|assert)',        'HandleError'),
    (r'(?:init|initialize|startup)',       'Initialize'),
    (r'(?:shutdown|cleanup|destroy|term)', 'Shutdown'),
    (r'(?:update|tick|step)',              'Update'),
    (r'(?:draw|paint|blit)',              'Draw'),
    (r'(?:load|read|open|import)',        'Load'),
    (r'(?:save|write|export)',            'Save'),
    (r'(?:create|alloc|new)',             'Create'),
    (r'(?:delete|free|release|destroy)',  'Destroy'),
    (r'(?:battle|combat|fight)',          'Battle'),
    (r'(?:script|sce|command)',           'Script'),
    (r'(?:dialog|dialogue|talk)',         'Dialog'),
    (r'(?:menu|ui|gui|interface)',        'UI'),
    (r'(?:sound|music|audio|sfx)',        'Sound'),
    (r'(?:video|movie|cutscene|bink)',    'Video'),
    (r'(?:save|slot|checkpoint)',         'SaveLoad'),
    (r'(?:map|scene|level|area)',         'Scene'),
    (r'(?:camera|view|frustum)',          'Camera'),
    (r'(?:anim|animation|skeleton)',      'Anim'),
    (r'(?:particle|effect|fx)',           'Particle'),
    (r'(?:collision|collide|hitbox)',     'Collision'),
    (r'(?:path|waypoint|navigate)',       'Pathfind'),
    (r'(?:inventory|item|equip)',         'Inventory'),
    (r'(?:quest|mission|task)',           'Quest'),
    (r'(?:npc|character|actor)',          'Character'),
]


def suggest_name_from_apis(func_data):
    """Suggest a name based on API calls made by the function."""
    callees = func_data.get('callees', [])
    if not callees:
        callees_ext = func_data.get('callees_external', [])
        callee_names = [c for c in callees_ext if isinstance(c, str)]
    else:
        callee_names = [c.get('name', '') for c in callees if isinstance(c, dict)]

    if not callee_names:
        return None, 0

    # Score each category
    scores = defaultdict(int)
    for category, info in API_PATTERNS.items():
        for callee in callee_names:
            for pattern in info['calls']:
                if pattern.lower() in callee.lower():
                    scores[category] += 1

    if not scores:
        return None, 0

    best_category = max(scores.items(), key=lambda x: x[1])
    prefix = API_PATTERNS[best_category[0]]['prefix']

    return prefix, best_category[1]


def suggest_name_from_strings(func_data):
    """Suggest a name based on string references."""
    strings = func_data.get('string_refs', [])
    if not strings:
        return None, 0

    all_strings = ' '.join(str(s).lower() for s in strings)

    for pattern, name in STRING_PATTERNS:
        if re.search(pattern, all_strings, re.IGNORECASE):
            return name, 2

    # Use the first meaningful string as part of the name
    for s in strings:
        s = str(s).strip()
        if len(s) > 3 and len(s) < 30 and s.isascii():
            # Clean up for use as identifier
            clean = re.sub(r'[^a-zA-Z0-9_]', '_', s)
            clean = re.sub(r'_+', '_', clean).strip('_')
            if clean and not clean[0].isdigit():
                return clean[:30], 1

    return None, 0


def suggest_name_from_signature(func_data):
    """Suggest based on function signature patterns."""
    decompiled = func_data.get('decompiled_c', '')
    if not decompiled:
        return None, 0

    # Check for common patterns in the decompiled code
    patterns = [
        (r'return\s+this\s*->', 'method', 1),
        (r'switch\s*\(', 'dispatch', 1),
        (r'for\s*\(\s*\w+\s*=\s*0', 'process_array', 1),
        (r'GetProcAddress', 'load_library_func', 3),
        (r'WndProc|DefWindowProc', 'window_proc', 3),
        (r'virtual\s*~|destructor', 'destructor', 2),
    ]

    for pattern, name, confidence in patterns:
        if re.search(pattern, decompiled, re.IGNORECASE):
            return name, confidence

    return None, 0


def generate_suggestion(func_data):
    """Generate a name suggestion for a function."""
    address = func_data.get('address', '')
    current_name = func_data.get('name', '')
    size = func_data.get('size_bytes', 0)

    # Skip already-named functions
    if func_data.get('has_custom_name', False):
        return None

    # Skip tiny thunks
    if func_data.get('is_thunk', False):
        return None

    suggestions = []

    # Method 1: API patterns
    api_name, api_conf = suggest_name_from_apis(func_data)
    if api_name:
        suggestions.append((api_name, api_conf, 'api_pattern'))

    # Method 2: String references
    str_name, str_conf = suggest_name_from_strings(func_data)
    if str_name:
        suggestions.append((str_name, str_conf, 'string_ref'))

    # Method 3: Code signature
    sig_name, sig_conf = suggest_name_from_signature(func_data)
    if sig_name:
        suggestions.append((sig_name, sig_conf, 'code_pattern'))

    if not suggestions:
        return None

    # Pick best suggestion
    best = max(suggestions, key=lambda x: x[1])

    # Compose final name
    addr_suffix = address.replace('0x', '')[-4:]
    if best[2] == 'api_pattern':
        suggested_name = "{}func_{}".format(best[0], addr_suffix)
    elif best[2] == 'string_ref':
        suggested_name = "{}_{}".format(best[0], addr_suffix)
    else:
        suggested_name = "{}_{}".format(best[0], addr_suffix)

    return {
        'address': address,
        'current_name': current_name,
        'suggested_name': suggested_name,
        'confidence': best[1],
        'method': best[2],
        'all_suggestions': [
            {'name': s[0], 'confidence': s[1], 'method': s[2]}
            for s in suggestions
        ],
    }


def generate_ghidra_rename_script(renames, output_path):
    """Generate a Ghidra Python script to apply renames."""
    lines = [
        '# Auto-generated rename script for PAL3 decompilation',
        '# Run in Ghidra: Script Manager -> Run',
        '#',
        '# Generated by rename_helper.py',
        '',
        'from ghidra.program.model.symbol import SourceType',
        '',
        'program = currentProgram',
        'func_mgr = program.getFunctionManager()',
        'addr_factory = program.getAddressFactory()',
        '',
        'renames = [',
    ]

    for r in renames:
        lines.append('    ("{}", "{}"),  # was: {} (confidence: {}, method: {})'.format(
            r['address'], r['suggested_name'],
            r['current_name'], r['confidence'], r['method']))

    lines.extend([
        ']',
        '',
        'count = 0',
        'for addr_str, new_name in renames:',
        '    addr = addr_factory.getAddress(addr_str)',
        '    func = func_mgr.getFunctionAt(addr)',
        '    if func:',
        '        func.setName(new_name, SourceType.USER_DEFINED)',
        '        count += 1',
        '',
        'print("Renamed {} functions".format(count))',
    ])

    with open(output_path, 'w') as f:
        f.write('\n'.join(lines))


def main():
    parser = argparse.ArgumentParser(
        description="Suggest meaningful names for PAL3 functions"
    )
    parser.add_argument('--address', '-a',
                        help='Analyze specific function address')
    parser.add_argument('--apply', action='store_true',
                        help='Generate Ghidra rename script')
    parser.add_argument('--min-confidence', '-c', type=int, default=1,
                        help='Minimum confidence level (default: 1)')
    parser.add_argument('--output', '-o',
                        help='Output path for rename script')

    args = parser.parse_args()

    # Load functions
    functions = []
    if args.address:
        # Find specific function
        addr_str = args.address.replace('0x', '')
        for jf in ASM_DIR.glob("*_{}.json".format(addr_str)):
            with open(jf) as f:
                functions.append(json.load(f))
    else:
        # Load all
        func_list = ASM_DIR / "_function_list.json"
        if func_list.exists():
            with open(func_list) as f:
                functions = json.load(f)
        else:
            for jf in ASM_DIR.glob("*.json"):
                if jf.name.startswith('_'):
                    continue
                try:
                    with open(jf) as f:
                        functions.append(json.load(f))
                except (json.JSONDecodeError, IOError):
                    continue

    if not functions:
        print("No function data found in {}/".format(ASM_DIR))
        sys.exit(1)

    # Generate suggestions
    renames = []
    for func in functions:
        suggestion = generate_suggestion(func)
        if suggestion and suggestion['confidence'] >= args.min_confidence:
            renames.append(suggestion)

    if not renames:
        print("No rename suggestions generated.")
        sys.exit(0)

    # Sort by confidence
    renames.sort(key=lambda x: -x['confidence'])

    # Print suggestions
    print()
    print("=" * 70)
    print("  Function Rename Suggestions ({} found)".format(len(renames)))
    print("=" * 70)
    print()
    print("  {:<12s} {:<25s} {:<25s} {:>4s} {:<10s}".format(
        "Address", "Current", "Suggested", "Conf", "Method"))
    print("  " + "-" * 65)

    for r in renames[:50]:
        print("  {:<12s} {:<25s} {:<25s} {:>4d} {:<10s}".format(
            r['address'][:12],
            r['current_name'][:25],
            r['suggested_name'][:25],
            r['confidence'],
            r['method'][:10],
        ))

    if len(renames) > 50:
        print("  ... ({} more)".format(len(renames) - 50))

    print()

    # Generate Ghidra script
    if args.apply:
        output = args.output or str(BUILD_DIR / "ghidra_rename.py")
        BUILD_DIR.mkdir(parents=True, exist_ok=True)
        generate_ghidra_rename_script(renames, output)
        print("Ghidra rename script: {}".format(output))
        print("Run in Ghidra Script Manager to apply renames.")

    # Save suggestions
    suggestions_path = BUILD_DIR / "rename_suggestions.json"
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    with open(suggestions_path, 'w') as f:
        json.dump(renames, f, indent=2)
    print("Suggestions saved: {}".format(suggestions_path))


if __name__ == '__main__':
    main()
