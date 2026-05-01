#!/usr/bin/env python3
"""
Generate gbengine.dll C++ source stubs from Ghidra JSON exports.

Reads asm/gbengine/*.json, groups functions by class, and generates
compilable C++ source files with proper export decorations.
"""

import json
import os
import glob
import re
import subprocess
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
ASM_DIR = PROJECT_ROOT / "asm" / "gbengine"
SRC_DIR = PROJECT_ROOT / "src" / "gbengine"
INCLUDE_DIR = PROJECT_ROOT / "include" / "gbengine"
ORIGINAL_DLL = PROJECT_ROOT / "original" / "gbengine.dll"

# Map class names to source files
CLASS_TO_FILE = {
    'gbCamera': 'gbCamera',
    'gbCamControler': 'gbCamera',
    'gbCamQuakeControl': 'gbCamera',
    'gbCamSpringControl': 'gbCamera',
    'gbGfxManager': 'gbGfxManager',
    'gbGfxManager_D3D': 'gbGfxManager',
    'gbRenderEffect': 'gbRenderEffect',
    'gbSceneGraph': 'gbSceneGraph',
    'gbGeomNode': 'gbGeomNode',
    'gbVisNode': 'gbVisNode',
    'gbActor': 'gbActor',
    'gbActorMgr': 'gbActor',
    'gbAnimNodeGroup': 'gbActor',
    'gbBaseMesh': 'gbMesh',
    'gbStaticMesh': 'gbMesh',
    'gbDynVertBuf': 'gbMesh',
    'gbTexture': 'gbTexture',
    'gbTexture_D3D': 'gbTexture',
    'gbTextureArray': 'gbTexture',
    'gbImage2D': 'gbImage2D',
    'gbImage2DInfo': 'gbImage2D',
    'gbResManager': 'gbResManager',
    'gbResource': 'gbResManager',
    'gbRefObject': 'gbResManager',
    'gbAudioManager': 'gbAudioManager',
    'gbAudioMgrDesc': 'gbAudioManager',
    'gbSound2DNode': 'gbAudioManager',
    'gbSound3DNode': 'gbAudioManager',
    'gbVFileSystem': 'gbVFileSystem',
    'gbVFile': 'gbVFileSystem',
    'gbVFile1': 'gbVFileSystem',
    'gbVTextFile': 'gbVFileSystem',
    'CPK': 'CPK',
    'CPKFile': 'CPK',
    'CIniFile': 'CIniFile',
    'gbMatrix4': 'gbMath',
    'gbMatrixStack': 'gbMath',
    'gbQuaternion': 'gbMath',
    'gbRotMatrix': 'gbMath',
    'gbVec3D': 'gbMath',
    'gbRay': 'gbMath',
    'gbAABBox': 'gbMath',
    'gbOBBox': 'gbMath',
    'gbSphere': 'gbMath',
    'gbPlane': 'gbMath',
    'gbParticleEffect': 'gbParticle',
    'gbParticleGroup': 'gbParticle',
    'gbParticleUnit': 'gbParticle',
    'gbPartEmitter': 'gbParticle',
    'gbPartGroupParam': 'gbParticle',
    'gbPartParamControl': 'gbParticle',
    'gbEmitterData': 'gbParticle',
    'gbEmitterSquare': 'gbParticle',
    'gbEffectMgr': 'gbEffectMgr',
    'gbLightObj': 'gbSceneGraph',
    'gbPrintFont': 'gbPrintFont',
    'gbPrintFontMgr': 'gbPrintFont',
    'gbColorFlt': 'gbMisc',
    'gbColorQuad': 'gbMisc',
    'gbPixelFormat': 'gbMisc',
    'gbUIRect': 'gbMisc',
    'gbTimeCounter': 'gbMisc',
    'gbNameVarBuf': 'gbMisc',
    'gbIndexBubble': 'gbVertPool',
    'gbIndexPool': 'gbVertPool',
    'gbVertexPool': 'gbVertPool',
    'gbVertPoolMgr': 'gbVertPool',
    'gbChain1D': 'gbChain',
    'gbChain1DNode': 'gbChain',
    'gbChain2D': 'gbChain',
    'gbChain2DNode': 'gbChain',
    'gbStaticChain': 'gbChain',
    'gbBinaryTree': 'gbChain',
    'gbBinaryTreeNode': 'gbChain',
    'gbNBTree': 'gbChain',
    'gbNBTreeNode': 'gbChain',
    'gbDropGroup': 'gbWeather',
    'gbDropUnit': 'gbWeather',
    'gbRain': 'gbWeather',
    'gbSnow': 'gbWeather',
    'BEZIER': 'gbMisc',
}


def get_exports():
    """Get demangled export list from the DLL."""
    import pefile
    pe = pefile.PE(str(ORIGINAL_DLL))
    exports = []
    for e in pe.DIRECTORY_ENTRY_EXPORT.symbols:
        if e.name:
            exports.append(e.name.decode())
    return exports


def parse_mangled_name(mangled):
    """Extract class name and method name from a mangled symbol."""
    if mangled.startswith('??0'):
        cls = mangled[3:].split('@')[0]
        return cls, 'ctor', mangled
    elif mangled.startswith('??1'):
        cls = mangled[3:].split('@')[0]
        return cls, 'dtor', mangled
    elif mangled.startswith('??4'):
        cls = mangled[3:].split('@')[0]
        return cls, 'operator=', mangled
    elif mangled.startswith('??B'):
        cls = mangled[3:].split('@')[0]
        return cls, 'operator_cast', mangled
    elif mangled.startswith('??H'):
        cls = mangled[3:].split('@')[0]
        return cls, 'operator+', mangled
    elif mangled.startswith('??R'):
        cls = mangled[3:].split('@')[0]
        return cls, 'operator()', mangled
    elif mangled.startswith('??_7'):
        cls = mangled[4:].split('@')[0]
        return cls, 'vftable', mangled
    elif mangled.startswith('?'):
        parts = mangled[1:].split('@')
        method = parts[0]
        cls = parts[1] if len(parts) >= 2 and parts[1] != '' else None
        if cls and '@@Y' not in mangled:
            return cls, method, mangled
        else:
            return None, method, mangled
    return None, mangled, mangled


def load_ghidra_functions():
    """Load all Ghidra JSON function data."""
    functions = []
    for fpath in glob.glob(str(ASM_DIR / "*.json")):
        try:
            with open(fpath, 'r', encoding='utf-8') as f:
                data = json.load(f)
            functions.append(data)
        except (json.JSONDecodeError, IOError):
            continue
    return functions


def classify_function(func_data):
    """Determine which source file a function belongs to."""
    name = func_data.get('name', '')
    sig = func_data.get('signature', '')

    # Try to extract class from signature's :: notation
    if '::' in sig:
        cls = sig.split('::')[0].split()[-1]
        if cls in CLASS_TO_FILE:
            return CLASS_TO_FILE[cls], cls

    # Try from function name's :: notation
    if '::' in name:
        cls = name.split('::')[0]
        if cls in CLASS_TO_FILE:
            return CLASS_TO_FILE[cls], cls

    # Extract class from __thiscall signature: "ret __thiscall FuncName(ClassName * this, ...)"
    thiscall_match = re.search(r'__thiscall\s+\w+\s*\(\s*(\w+)\s*\*\s*this', sig)
    if thiscall_match:
        cls = thiscall_match.group(1)
        if cls in CLASS_TO_FILE:
            return CLASS_TO_FILE[cls], cls

    # Try matching name patterns against known classes
    for cls in CLASS_TO_FILE:
        if name.startswith(cls + '_') or name.startswith(cls):
            return CLASS_TO_FILE[cls], cls

    # Global functions with gb prefix
    if name.startswith('gb') or name.startswith('Profile'):
        return 'gbengine', None

    return 'gbengine_internal', None


def parse_signature(sig):
    """Parse Ghidra signature into components.

    Example: "void __thiscall gbCamera::SetFov(gbCamera *this, float param_1)"
    Returns: (return_type, calling_conv, class_name, func_name, params_without_this)
    """
    if not sig:
        return None

    # Match: return_type calling_conv [class::]name(params)
    m = re.match(
        r'([\w\s\*]+?)\s+(__\w+)\s+'  # return_type + calling_conv
        r'(?:(\w+)::)?'                # optional class::
        r'(\w+)\s*'                    # function name
        r'\((.*)\)',                    # params
        sig.strip()
    )
    if not m:
        # Try without calling convention
        m = re.match(
            r'([\w\s\*]+?)\s+'
            r'(?:(\w+)::)?'
            r'(\w+)\s*'
            r'\((.*)\)',
            sig.strip()
        )
        if m:
            ret = m.group(1).strip()
            cls = m.group(2)
            fname = m.group(3)
            params = m.group(4).strip()
            return ret, '', cls, fname, params
        return None

    ret = m.group(1).strip()
    cc = m.group(2)
    cls = m.group(3)
    fname = m.group(4)
    params = m.group(5).strip()

    # For __thiscall, extract class from first param if not in name
    if cc == '__thiscall' and not cls:
        this_m = re.match(r'(\w+)\s*\*\s*this', params)
        if this_m:
            cls = this_m.group(1)

    # Remove 'this' parameter for member functions
    if cls and params:
        # Remove "ClassName * this" or "ClassName *this" from params
        params = re.sub(r'^\w+\s*\*\s*this\s*,?\s*', '', params).strip()
        if params.startswith(','):
            params = params[1:].strip()

    return ret, cc, cls, fname, params


KNOWN_TYPES = {
    'void', 'int', 'unsigned int', 'char', 'unsigned char',
    'short', 'unsigned short', 'long', 'unsigned long',
    'float', 'double', '__int64', 'unsigned __int64',
    'DWORD', 'WORD', 'BYTE', 'BOOL', 'LONG', 'ULONG',
    'HRESULT', 'HWND', 'HDC', 'HANDLE', 'LPVOID',
    'LPCSTR', 'LPSTR', 'LPCWSTR', 'LPWSTR',
    'SIZE_T', 'UINT', 'INT',
    'IDirect3DDevice9', 'IDirect3DTexture9', 'IDirect3DSurface9',
    'IDirect3DVertexBuffer9', 'IDirect3DIndexBuffer9',
    'D3DFORMAT', 'D3DPOOL', 'D3DPRIMITIVETYPE',
    'D3DXMATRIX', 'D3DXVECTOR3', 'D3DXVECTOR4', 'D3DXQUATERNION',
    'D3DXPLANE', 'D3DCOLOR', 'D3DVIEWPORT9',
    'gbVec3D', 'gbVec2D', 'gbVec4D', 'gbMatrix4', 'gbRotMatrix',
    'gbQuaternion', 'gbRay', 'gbAABBox', 'gbOBBox', 'gbSphere',
    'gbPlane', 'gbColorQuad', 'gbColorFlt', 'gbUIRect', 'gbPixelFormat',
}


def simplify_type(t):
    """Simplify Ghidra types to C++ compilable types."""
    t = t.strip()
    # Ghidra undefined types
    t = re.sub(r'\bundefined[1248]?\b', 'int', t)
    t = re.sub(r'\buint\b', 'unsigned int', t)
    t = re.sub(r'\bulong\b', 'unsigned long', t)
    t = re.sub(r'\bbyte\b', 'unsigned char', t)
    t = re.sub(r'\bword\b', 'unsigned short', t)
    t = re.sub(r'\bdword\b', 'unsigned int', t)
    t = re.sub(r'\bbool\b', 'int', t)
    t = re.sub(r'\blonglong\b', '__int64', t)
    t = re.sub(r'\bulonglong\b', 'unsigned __int64', t)
    return t


def resolve_param_type(param_str):
    """Resolve a single parameter type, replacing unknown types with void*."""
    param_str = param_str.strip()
    if not param_str:
        return param_str

    # Extract type and name
    # Common forms: "Type * name", "Type name", "Type"
    param_str = simplify_type(param_str)

    # Check if it's a pointer to unknown type
    ptr_match = re.match(r'^(\w+)\s*\*\s*(\w*)$', param_str)
    if ptr_match:
        base_type = ptr_match.group(1)
        name = ptr_match.group(2)
        if base_type not in KNOWN_TYPES and base_type not in CLASS_TO_FILE:
            return f'void * {name}' if name else 'void *'

    # Check if it's an unknown non-pointer type used as value
    words = param_str.split()
    if len(words) >= 1:
        base = words[0]
        if base not in KNOWN_TYPES and base not in CLASS_TO_FILE and '*' not in param_str:
            # Unknown value type - use int
            if len(words) >= 2:
                return f'int {words[-1]}'
            else:
                return 'int'

    return param_str


def format_params(params_str):
    """Format parameter list for C++ output."""
    if not params_str:
        return 'void'

    # Split by comma, simplify each
    parts = []
    depth = 0
    current = ''
    for ch in params_str:
        if ch == '(' or ch == '<':
            depth += 1
            current += ch
        elif ch == ')' or ch == '>':
            depth -= 1
            current += ch
        elif ch == ',' and depth == 0:
            parts.append(current.strip())
            current = ''
        else:
            current += ch
    if current.strip():
        parts.append(current.strip())

    result = []
    for i, p in enumerate(parts):
        p = simplify_type(p)
        # Rename param_N to more standard names
        p = re.sub(r'\bparam_(\d+)\b', lambda m: f'p{m.group(1)}', p)
        p = resolve_param_type(p)
        result.append(p)

    return ', '.join(result) if result else 'void'


def resolve_return_type(ret_type):
    """Resolve return type, replacing unknown types."""
    ret_type = simplify_type(ret_type).strip()
    if '*' in ret_type:
        # Pointer return - check base type
        base = ret_type.replace('*', '').strip()
        if base not in KNOWN_TYPES and base not in CLASS_TO_FILE:
            return 'void *'
        return ret_type
    if ret_type not in KNOWN_TYPES and ret_type not in CLASS_TO_FILE:
        return 'int'
    return ret_type


STRUCT_TYPES = {
    'gbVec2D', 'gbVec3D', 'gbVec4D', 'gbColorQuad', 'gbColorFlt',
    'gbMatrix4', 'gbRotMatrix', 'gbQuaternion', 'gbRay', 'gbAABBox',
    'gbOBBox', 'gbSphere', 'gbPlane', 'gbUIRect', 'gbPixelFormat',
}


def get_default_return(ret_type):
    """Get default return statement for a type."""
    ret_type = ret_type.strip()
    if ret_type == 'void':
        return ''
    elif '*' in ret_type:
        return '    return NULL;\n'
    elif ret_type == 'float' or ret_type == 'double':
        return '    return 0.0f;\n'
    elif ret_type in STRUCT_TYPES:
        return f'    {ret_type} r = {{0}}; return r;\n'
    else:
        return '    return 0;\n'


def generate_method_stub(func_data, cls_name):
    """Generate an inline class method stub."""
    name = func_data.get('name', 'unknown')
    addr = func_data.get('address', '0x0')
    size = func_data.get('size_bytes', 0)
    sig = func_data.get('signature', '')

    if name.startswith('Catch@') or name.startswith('Unwind@'):
        return None
    if name.startswith('_') and 'CRT' in name:
        return None

    parsed = parse_signature(sig)
    if not parsed:
        return f'    // TODO: {addr} ({size}B) - {name}'

    ret_type, cc, cls, fname, params = parsed
    ret_type = resolve_return_type(ret_type)
    params_fmt = format_params(params)
    default_ret = get_default_return(ret_type)

    # Handle constructors/destructors
    if fname == cls_name:
        lines = []
        lines.append(f'    // {addr} ({size}B)')
        lines.append(f'    {cls_name}({params_fmt}) {{}}')
        return '\n'.join(lines)
    elif fname == '~' + cls_name or fname.startswith('~'):
        lines = []
        lines.append(f'    // {addr} ({size}B)')
        lines.append(f'    ~{cls_name}() {{}}')
        return '\n'.join(lines)

    # Regular method
    lines = []
    lines.append(f'    // {addr} ({size}B)')
    if default_ret:
        lines.append(f'    {ret_type} {fname}({params_fmt}) {{ {default_ret.strip()} }}')
    else:
        lines.append(f'    void {fname}({params_fmt}) {{}}')

    return '\n'.join(lines)


def generate_stub(func_data):
    """Generate a compilable C++ stub from Ghidra function data."""
    name = func_data.get('name', 'unknown')
    addr = func_data.get('address', '0x0')
    size = func_data.get('size_bytes', 0)
    sig = func_data.get('signature', '')

    # Skip catch/unwind handlers and thunks
    if name.startswith('Catch@') or name.startswith('Unwind@'):
        return None
    if name.startswith('_') and 'CRT' in name:
        return None

    parsed = parse_signature(sig)
    if not parsed:
        # Can't parse - emit as comment only
        return f'// TODO: {addr} ({size}B) - {name}\n// sig: {sig}'

    ret_type, cc, cls, fname, params = parsed
    ret_type = resolve_return_type(ret_type)
    params_fmt = format_params(params)
    default_ret = get_default_return(ret_type)

    # Build function definition (global functions only - class methods use generate_method_stub)
    func_sig = f'{ret_type} {fname}({params_fmt})'

    lines = []
    lines.append(f'// {addr} ({size}B)')
    lines.append(f'{func_sig}')
    lines.append('{')
    if default_ret:
        lines.append(default_ret.rstrip())
    lines.append('}')

    return '\n'.join(lines)


def main():
    print("Loading Ghidra function data...")
    functions = load_ghidra_functions()
    print(f"  Loaded {len(functions)} functions")

    print("Loading export symbols...")
    exports = get_exports()
    export_set = set(exports)
    print(f"  {len(exports)} exports")

    # Group functions by target file
    file_groups = defaultdict(list)
    for func in functions:
        target_file, cls_name = classify_function(func)
        file_groups[target_file].append((cls_name, func))

    print(f"\nFile distribution:")
    for fname, funcs in sorted(file_groups.items(), key=lambda x: -len(x[1])):
        print(f"  {fname}.cpp: {len(funcs)} functions")

    # Generate source files
    SRC_DIR.mkdir(parents=True, exist_ok=True)

    for fname, funcs in file_groups.items():
        # Skip internal/D3DX library functions
        if fname == 'gbengine_internal':
            print(f"  Skipped: {fname}.cpp ({len(funcs)} D3DX/internal functions)")
            continue

        output_path = SRC_DIR / f"{fname}.cpp"

        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(f'/**\n')
            f.write(f' * gbengine.dll - {fname}\n')
            f.write(f' * Auto-generated from Ghidra decompilation\n')
            f.write(f' * Functions: {len(funcs)}\n')
            f.write(f' */\n\n')
            f.write(f'#include "gbengine/gbengine_types.h"\n\n')

            # Group by class within file
            by_class = defaultdict(list)
            for cls_name, func_data in funcs:
                by_class[cls_name or '(global)'].append(func_data)

            # Types already defined as struct in gbengine_types.h - don't redeclare
            types_in_header = {
                'gbVec2D', 'gbVec3D', 'gbVec4D', 'gbColorQuad', 'gbColorFlt',
                'gbMatrix4', 'gbRotMatrix', 'gbQuaternion', 'gbRay', 'gbAABBox',
                'gbOBBox', 'gbSphere', 'gbPlane', 'gbUIRect', 'gbPixelFormat',
            }
            # Forward declare ALL known classes (including those defined later in this file)
            f.write('// Forward declarations\n')
            for cls in sorted(CLASS_TO_FILE.keys()):
                if cls not in types_in_header:
                    f.write(f'class {cls};\n')
            f.write('\n')

            # Generate class definitions with inline methods
            for cls_name, cls_funcs in sorted(by_class.items()):
                cls_funcs.sort(key=lambda x: x.get('address', ''))

                if cls_name != '(global)':
                    # Skip classes that are already defined as structs in header
                    if cls_name in types_in_header:
                        f.write(f'\n/* ======== {cls_name} (defined in header) ======== */\n\n')
                        continue

                    f.write(f'\n/* ======== {cls_name} ======== */\n\n')
                    f.write(f'class {cls_name} {{\n')
                    f.write(f'public:\n')

                    seen_sigs = set()
                    for func_data in cls_funcs:
                        stub = generate_method_stub(func_data, cls_name)
                        if stub:
                            # Deduplicate by signature line (2nd line)
                            sig_line = stub.split('\n')[-1].strip()
                            if sig_line in seen_sigs:
                                # Emit as comment to avoid duplicate
                                addr = func_data.get('address', '?')
                                f.write(f'    // {addr} (duplicate signature skipped)\n')
                            else:
                                seen_sigs.add(sig_line)
                                f.write(stub + '\n')

                    f.write(f'}};\n\n')
                else:
                    f.write(f'\n/* ======== Global Functions ======== */\n\n')
                    seen_global = set()
                    for func_data in cls_funcs:
                        stub = generate_stub(func_data)
                        if stub:
                            sig_line = stub.split('\n')[1] if '\n' in stub else stub
                            if sig_line in seen_global:
                                addr = func_data.get('address', '?')
                                f.write(f'// {addr} (duplicate skipped)\n\n')
                            else:
                                seen_global.add(sig_line)
                                f.write(stub + '\n\n')

        print(f"  Generated: {output_path.name} ({len(funcs)} functions)")

    # Don't overwrite header if it already exists (manually maintained)
    header_path = INCLUDE_DIR / "gbengine_types.h"
    if not header_path.exists():
        INCLUDE_DIR.mkdir(parents=True, exist_ok=True)
        with open(header_path, 'w', encoding='utf-8') as f:
            f.write('#pragma once\n\n')
            f.write('#include <windows.h>\n')
            f.write('#include <d3d9.h>\n\n')
            f.write('#ifdef GBENGINE_EXPORTS\n')
            f.write('#define GBAPI __declspec(dllexport)\n')
            f.write('#else\n')
            f.write('#define GBAPI __declspec(dllimport)\n')
            f.write('#endif\n\n')
        print(f"\n  Generated header: {header_path}")
    else:
        print(f"\n  Header exists (not overwritten): {header_path}")

    print(f"\nDone! Source files: {len(file_groups) - 1}")


if __name__ == '__main__':
    main()
