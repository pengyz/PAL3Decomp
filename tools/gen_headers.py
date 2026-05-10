#!/usr/bin/env python3
"""
Generate C++ header files from PDB class data + IDA function signatures.

For each class, generates include/pal3/gen/<ClassName>.h containing:
  - Base class inheritance
  - Data members with correct types and offsets (as comments)
  - Method declarations from IDA decomp signatures

Sources:
  - asm/pal3a/pdb_export.json: class layout (members, inheritance, size)
  - asm/pal3/decomp/*.json: method signatures

Usage:
  python tools/gen_headers.py
"""

import json
import os
import re
from collections import defaultdict
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.parent
PDB_FILE = PROJECT_ROOT / "asm" / "pal3a" / "pdb_export.json"
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
OUTPUT_DIR = PROJECT_ROOT / "include" / "pal3" / "gen"

# Skip STL/CRT/Windows types (already defined by system headers)
SKIP_CLASSES = {
    'std', 'stdiobuf', 'exception', 'type_info', 'filebuf',
    # Windows types
    'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG', 'RECT', 'POINT', 'SIZE',
    'WNDCLASSA', 'tagWNDCLASSA', 'tagOFNA',
    '_FILETIME', '_SYSTEMTIME', '_MEMORYSTATUS', '_SECURITY_ATTRIBUTES',
    '_OSVERSIONINFOA', '_STARTUPINFOA', '_WIN32_FIND_DATAA',
    '_GUID', 'GUID', 'IID',
    # CRT
    '_iobuf', 'FILE', '_cpinfo', '_EXCEPTION_RECORD', 'EXCEPTION_RECORD',
    # DirectX / DirectInput
    '_DIMOUSESTATE2',
    # gbengine (separate library)
    'gbGfxManager', 'gbActorMgr', 'gbCamera', 'gbActor', 'gbVFileSystem',
    'gbRenderEffect', 'gbSceneGraph', 'gbTexture', 'gbGeomNode',
    'gbPrintFont', 'gbPrintFontMgr', 'gbMatrixStack', 'gbRefObject',
    'gbAudioManager', 'gbBinkVideo', 'gbDynVertBuf', 'gbVertPoolMgr',
    'gbSoundData', 'gbResManager', 'gbImage2D', 'gbCursorRes',
    'gbTexture_D3D', 'gbIndexPool', 'gbVertexPool',
}

# Type mapping for header output
TYPE_REMAP = {
    'unsigned char': 'BYTE',
    'unsigned int': 'UINT',
    'unsigned long': 'DWORD',
    'unsigned short': 'WORD',
    '_iobuf *': 'FILE *',
}


def parse_signature(sig):
    """Parse IDA signature into (return_type, calling_conv, params_str)."""
    if not sig:
        return 'int', '', ''

    cc_match = re.search(r'(__thiscall|__cdecl|__stdcall|__fastcall)', sig)
    paren_match = re.search(r'\(', sig)

    if cc_match and paren_match:
        cc = cc_match.group(1)
        ret = sig[:cc_match.start()].rstrip()
        if not ret:
            ret = 'int'
        params = sig[paren_match.start()+1:sig.rfind(')')]
        return ret, cc, params

    if paren_match:
        ret = sig[:paren_match.start()].rstrip()
        if not ret:
            ret = 'int'
        params = sig[paren_match.start()+1:sig.rfind(')')]
        return ret, '__cdecl', params

    return 'int', '', ''


def split_params(params_str):
    """Split comma-separated params respecting nested parens/templates."""
    result = []
    depth = 0
    current = ''
    for ch in params_str:
        if ch == ',' and depth == 0:
            result.append(current.strip())
            current = ''
        else:
            if ch in '(<':
                depth += 1
            elif ch in ')>':
                depth -= 1
            current += ch
    if current.strip():
        result.append(current.strip())
    return result


def collect_methods():
    """Collect all class methods from decomp JSONs."""
    classes = defaultdict(list)
    for f in sorted(DECOMP_DIR.glob("*.json")):
        if f.name.startswith("_"):
            continue
        try:
            with open(f, 'r', encoding='utf-8') as fh:
                d = json.load(fh)
        except:
            continue

        name = d.get('name', '')
        sig = d.get('signature', '')
        addr = d.get('address', '')

        if '::' not in name or name.startswith('sub_'):
            continue
        # Skip mangled/special names
        if '`' in name or '?' in name.split('::')[-1]:
            continue

        parts = name.split('::', 1)
        cls = parts[0]
        method = parts[1].split('(')[0] if '(' in parts[1] else parts[1]

        if cls in SKIP_CLASSES:
            continue
        # Skip invalid method names
        if ' ' in method or '`' in method:
            continue

        classes[cls].append((method, sig, addr))
    return classes


def generate_header(cls_name, pdb_class, methods):
    """Generate a complete header for one class."""
    lines = []
    lines.append("#pragma once")
    lines.append("// Auto-generated: %s" % cls_name)
    lines.append("")

    # Analyze references: include vs forward declare
    include_types = set()  # need full definition (value members, inheritance)
    fwd_types = set()      # pointer only, forward declare suffices

    PRIMITIVES = {'int', 'char', 'float', 'double', 'unsigned', 'void', 'long',
                  'short', 'bool', 'BYTE', 'WORD', 'DWORD', 'UINT', 'HRESULT',
                  '__int64', 'unsigned char', 'unsigned int', 'unsigned long',
                  'unsigned short', 'unsigned __int64', 'wchar_t'}

    # Types provided by system headers (windows.h, CRT, gbengine) - never include/fwd-declare
    SYSTEM_TYPES = SKIP_CLASSES | {
        'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG', 'RECT', 'POINT', 'SIZE',
        'HWND', 'HINSTANCE', 'HICON', 'HBRUSH', 'HDC', 'HANDLE', 'LPVOID',
        'WNDCLASSA', 'tagWNDCLASSA', 'tagOFNA', '_GUID', 'GUID', 'IID',
        '_iobuf', 'FILE', '_DIMOUSESTATE2', '_FILETIME', '_SYSTEMTIME',
        'CRITICAL_SECTION', 'HRESULT', 'BOOL', 'LPCSTR', 'LPSTR',
        'gbVec3D', 'gbMatrix4', 'gbColorQuad', 'gbOBBox', 'gbSphere',
        'gbGeomQuad', 'gbUIQuad', 'gbColorFlt', 'gbAABBox',
        'gbGfxManager', 'gbActorMgr', 'gbCamera', 'gbActor',
        'gbVFileSystem', 'gbRenderEffect', 'gbSceneGraph', 'gbTexture',
        'gbGeomNode', 'gbPrintFont', 'gbPrintFontMgr', 'gbMatrixStack',
        'gbRefObject', 'gbAudioManager', 'gbBinkVideo', 'gbImage2D',
        'gbTexture_D3D', 'gbDynVertBuf', 'gbVertPoolMgr', 'gbCursorRes',
        'gbIndexPool', 'gbVertexPool', 'gbSoundData', 'gbResManager',
        'gbLight', 'gbMaterial', 'gbPixelFormat', 'gbRay',
        'IDirectInput8A', 'IDirectInputDevice8A',
    }

    if pdb_class:
        # Inheritance -> include
        for b in pdb_class.get('bases', []) or []:
            bname = b['name']
            if '::' not in bname and '<' not in bname:
                include_types.add(bname)

        # Data members
        for m in pdb_class.get('data_members', []):
            mtype = m.get('type', '')
            # Check if pointer or value
            is_ptr = '*' in mtype
            # Strip array/pointer to get base type name
            base = re.sub(r'\[\d+\]', '', mtype).replace('*', '').strip()
            if not base or base == cls_name:
                continue
            if base in PRIMITIVES or base in SYSTEM_TYPES:
                continue
            if '::' in base or '<' in base:
                continue

            if is_ptr:
                fwd_types.add(base)
            else:
                include_types.add(base)

    # Don't forward-declare what we're including
    fwd_types -= include_types
    # Remove system types from both sets
    include_types -= SYSTEM_TYPES
    fwd_types -= SYSTEM_TYPES

    # Emit includes
    for t in sorted(include_types):
        lines.append('#include "%s.h"' % t)
    if include_types:
        lines.append("")

    # Emit forward declarations
    for t in sorted(fwd_types):
        lines.append("class %s;" % t)
    if fwd_types:
        lines.append("")

    # Class declaration
    bases_str = ""
    if pdb_class and pdb_class.get('bases'):
        base_names = [b['name'] for b in pdb_class['bases']]
        bases_str = " : " + ", ".join("public %s" % b for b in base_names)

    lines.append("class %s%s {" % (cls_name, bases_str))
    lines.append("public:")

    # Data members
    if pdb_class and pdb_class.get('data_members'):
        members = pdb_class['data_members']
        size = pdb_class.get('size', 0)

        for m in members:
            mname = m.get('name', '')
            mtype = m.get('type', 'int')
            moffset = m.get('offset', 0)

            if not mname:
                mname = '_field_%04X' % moffset

            # Handle nested class types: ClassName::NestedType
            if '::' in mtype:
                # Extract the nested type name, declare as inner struct
                parts = mtype.split('::')
                nested_name = parts[-1]
                # Strip array suffix for the struct name
                nested_base = re.sub(r'\[.*', '', nested_name).strip()
                arr_in_nested = re.search(r'(\[\d+\](?:\[\d+\])*)$', mtype)
                if arr_in_nested:
                    lines.append("    struct %s {}; // nested type stub" % nested_base)
                    arr_part = arr_in_nested.group(1)
                    lines.append("    %s %s%s; // +0x%X" % (nested_base, mname, arr_part, moffset))
                else:
                    lines.append("    struct %s {}; // nested type stub" % nested_base)
                    lines.append("    %s %s; // +0x%X" % (nested_base, mname, moffset))
                continue

            # Handle arrays in type: "Type[N]" or "Type *[N]" -> "Type name[N]" / "Type * name[N]"
            arr_match = re.search(r'(\[\d+\](?:\[\d+\])*)$', mtype)
            if arr_match:
                arr_part = arr_match.group(1)
                base_type = mtype[:arr_match.start()].rstrip()
                lines.append("    %s %s%s; // +0x%X" % (base_type, mname, arr_part, moffset))
            else:
                lines.append("    %s %s; // +0x%X" % (mtype, mname, moffset))

        if size > 0:
            lines.append("    // total size: 0x%X (%d)" % (size, size))
        lines.append("")

    # Methods (deduplicate by name+params to avoid C2535)
    if methods:
        seen_methods = set()  # track "name(params)" to deduplicate
        for method_name, sig, addr in sorted(methods, key=lambda x: x[2]):
            ret, cc, params = parse_signature(sig)

            is_ctor = (method_name == cls_name)
            is_dtor = (method_name.startswith('~') or method_name == '~%s' % cls_name)
            is_thiscall = '__thiscall' in cc
            is_static = not is_thiscall and not is_ctor and not is_dtor

            # Strip register annotations
            params = re.sub(r'@<\w+>', '', params)

            # Remove this pointer from params
            if is_thiscall and params:
                param_list = split_params(params)
                if param_list and ('this' in param_list[0] or '*this' in param_list[0]):
                    param_list = param_list[1:]
                params = ', '.join(param_list)

            # Build declaration
            if is_ctor:
                decl = "    %s(%s);" % (cls_name, params)
            elif is_dtor:
                decl = "    ~%s();" % cls_name
            elif is_static:
                decl = "    static %s %s(%s);" % (ret, method_name, params)
            else:
                decl = "    %s %s(%s);" % (ret, method_name, params)

            # Skip invalid method names (IDA special names with backticks, etc.)
            if '`' in method_name or ' ' in method_name or '?' in method_name:
                continue

            # Deduplicate: skip if same method name+params already declared
            method_key = "%s(%s)" % (method_name, params)
            if method_key in seen_methods:
                continue
            seen_methods.add(method_key)

            lines.append("%s // %s" % (decl, addr))

    lines.append("};")
    lines.append("")
    return '\n'.join(lines)


def main():
    # Load PDB class data
    with open(PDB_FILE, 'r', encoding='utf-8') as f:
        pdb = json.load(f)

    pdb_classes = {}
    for c in pdb.get('classes', []):
        name = c.get('name', '')
        if name and '<' not in name and '::' not in name:
            pdb_classes[name] = c

    # Collect methods from decomp
    methods_by_class = collect_methods()

    # Generate headers for all classes that have either members or methods
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    generated = 0
    all_classes = set(pdb_classes.keys()) | set(methods_by_class.keys())

    for cls_name in sorted(all_classes):
        if cls_name in SKIP_CLASSES:
            continue

        pdb_class = pdb_classes.get(cls_name)
        methods = methods_by_class.get(cls_name, [])

        # Skip if no useful content
        has_members = pdb_class and pdb_class.get('data_members') and pdb_class.get('size', 0) > 1
        has_methods = len(methods) >= 1
        if not has_members and not has_methods:
            continue

        content = generate_header(cls_name, pdb_class, methods)
        output_path = OUTPUT_DIR / ("%s.h" % cls_name)
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(content)
        generated += 1

    print("Generated %d header files in %s" % (generated, OUTPUT_DIR))
    print("  With PDB layout: %d" % sum(1 for c in all_classes
          if c in pdb_classes and pdb_classes[c].get('data_members') and pdb_classes[c].get('size', 0) > 1))
    print("  With methods: %d" % sum(1 for c in all_classes if c in methods_by_class and methods_by_class[c]))


if __name__ == '__main__':
    main()
