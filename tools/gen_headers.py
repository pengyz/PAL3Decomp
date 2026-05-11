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
ANNOTATIONS_FILE = PROJECT_ROOT / "asm" / "pal3" / "annotations.json"
IDA_STRUCTS_FILE = PROJECT_ROOT / "asm" / "pal3" / "ida_structs.json"
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
OUTPUT_DIR = PROJECT_ROOT / "include" / "pal3" / "gen"
OVERRIDES_DIR = PROJECT_ROOT / "include" / "pal3" / "overrides"

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

# Prefix patterns for system/library types that should never be generated
SKIP_PREFIXES = (
    'D3D', '_D3D', 'ID3D', 'IDirect', 'IUnknown',
    'CD3D',  # D3D helper classes from SDK samples
    'D3DX',  # D3DX math types
    'gb',    # gbengine types (all start with gb)
)


def should_skip_class(name):
    """Check if a class name should be skipped (system/library type)."""
    if name in SKIP_CLASSES:
        return True
    if name.startswith(SKIP_PREFIXES):
        return True
    return False

# Type mapping for header output (includes IDA internal type names)
TYPE_REMAP = {
    'unsigned char': 'BYTE',
    'unsigned int': 'UINT',
    'unsigned long': 'DWORD',
    '__int8': 'char',
    '__int16': 'short',
    '__int32': 'int',
    '__int64': '__int64',
    'unsigned __int8': 'unsigned char',
    'unsigned __int16': 'unsigned short',
    'unsigned __int32': 'unsigned int',
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


def demangle_name(mangled):
    """Extract (ClassName, MethodName) from MSVC mangled name.

    Formats:
      ?Method@Class@@...       -> (Class, Method)
      ??0Class@@...            -> (Class, Class)   [ctor]
      ??1Class@@...            -> (Class, ~Class)  [dtor]
    """
    if not mangled.startswith('?'):
        return None

    inner = mangled[1:]  # strip leading ?

    # Ctor/dtor: starts with ?0 or ?1 after the leading ?
    if inner.startswith('?0') or inner.startswith('?1'):
        code = inner[1]
        rest = inner[2:]
        at_pos = rest.find('@')
        if at_pos <= 0:
            return None
        cls = rest[:at_pos]
        if not cls or '$' in cls or '<' in cls or not cls[0].isalpha():
            return None
        if code == '0':
            return cls, cls
        else:
            return cls, '~' + cls

    # Regular method: Method@Class@...
    at_pos = inner.find('@')
    if at_pos <= 0:
        return None
    method = inner[:at_pos]
    rest = inner[at_pos+1:]

    at_pos2 = rest.find('@')
    if at_pos2 <= 0:
        return None
    cls = rest[:at_pos2]

    if not cls or '$' in cls or '<' in cls or not cls[0].isalpha():
        return None
    if not method or '$' in method or '<' in method:
        return None
    if not method[0].isalpha() and method[0] != '~':
        return None

    return cls, method


def collect_methods():
    """Collect all class methods from decomp JSONs."""
    classes = defaultdict(list)
    for f in sorted(DECOMP_DIR.glob("*.json")):
        try:
            with open(f, 'r', encoding='utf-8') as fh:
                d = json.load(fh)
        except:
            continue

        name = d.get('name', '')
        sig = d.get('signature', '')
        addr = d.get('address', '')

        cls = None
        method = None

        # Try demangling first (handles ?Method@Class@@ format)
        if name.startswith('?'):
            result = demangle_name(name)
            if result:
                cls, method = result
        # Then try ClassName::Method format
        elif '::' in name and not name.startswith('sub_'):
            if '`' not in name:
                parts = name.split('::', 1)
                cls = parts[0]
                method = parts[1].split('(')[0] if '(' in parts[1] else parts[1]
                if '?' in method:
                    cls = None  # skip

        if not cls or not method:
            continue
        if should_skip_class(cls):
            continue
        if ' ' in method or '`' in method:
            continue

        classes[cls].append((method, sig, addr))
    return classes


def generate_header(cls_name, pdb_class, methods, known_classes=None):
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
                  'unsigned short', 'unsigned __int64', 'wchar_t',
                  '__int8', '__int16', '__int32', 'unsigned __int8',
                  'unsigned __int16', 'unsigned __int32'}

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
        # Inheritance -> include (simplify template names same as in class declaration)
        for b in pdb_class.get('bases', []) or []:
            bname = b['name']
            if '<' in bname:
                bname = bname.split('<')[0]  # CTaskTpl<...> -> CTaskTpl
            if '::' not in bname:
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

    # Only include types that will have a header file; demote others to fwd_types
    if known_classes is not None:
        existing_includes = set()
        missing_includes = set()
        for t in include_types:
            if t in known_classes:
                existing_includes.add(t)
            else:
                missing_includes.add(t)
        include_types = existing_includes
        fwd_types |= missing_includes

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

    # Class declaration with inheritance
    # Source 1: PDB base_classes
    # Source 2: annotations.json base_class field (fallback when PDB is empty)
    bases_str = ""
    base_names = []
    if pdb_class and pdb_class.get('bases'):
        for b in pdb_class['bases']:
            bname = b['name']
            if '<' in bname:
                bname = bname.split('<')[0]
            base_names.append(bname)

    if not base_names:
        # Fallback: read from annotations.json
        try:
            ann_data = json.load(open(str(ANNOTATIONS_FILE), 'r', encoding='utf-8'))
            ann_struct = ann_data.get('structs', {}).get(cls_name, {})
            base = ann_struct.get('base_class')
            if base:
                base_names.append(base)
        except:
            pass

    if base_names:
        bases_str = " : " + ", ".join("public %s" % b for b in base_names)
        for b in base_names:
            if b not in fwd_types and b not in include_types:
                fwd_types.add(b)

    lines.append("class %s%s {" % (cls_name, bases_str))
    lines.append("public:")

    # Data members
    # Determine base class size to skip inherited members
    base_size = 0
    if base_names:
        try:
            ann_data = json.load(open(str(ANNOTATIONS_FILE), 'r', encoding='utf-8'))
            ann_struct = ann_data.get('structs', {}).get(cls_name, {})
            base_size = ann_struct.get('base_size', 0)
        except:
            pass

    if pdb_class and pdb_class.get('data_members'):
        members = pdb_class['data_members']
        size = pdb_class.get('size', 0)

        for m in members:
            mname = m.get('name', '')
            mtype = m.get('type', 'int')
            moffset = m.get('offset', 0)

            # Skip members that belong to base class
            if base_size > 0 and moffset < base_size:
                continue

            if not mname:
                mname = '_field_%04X' % moffset

            # Skip vtable members (IDA internal, not part of C++ source)
            if '__vftable' in mname or 'vtbl_' in mtype or '_vtbl' in mtype:
                continue

            # Remap IDA internal types to C types
            for ida_type, c_type in TYPE_REMAP.items():
                if ida_type in mtype:
                    mtype = mtype.replace(ida_type, c_type)

            # Fix IDA type misidentification
            mtype = mtype.replace('stdiobuf', 'UIWnd')
            mtype = mtype.replace('std::ios_base', 'UIWnd')

            # Handle nested/template types that can't be directly declared
            if '::' in mtype or '<' in mtype:
                # Calculate member size from next offset
                idx = members.index(m)
                if idx + 1 < len(members):
                    msize = members[idx+1]['offset'] - moffset
                else:
                    msize = size - moffset if size > moffset else 4
                if msize > 0:
                    lines.append("    char %s[%d]; // +0x%X (%s)" % (mname, msize, moffset, mtype))
                else:
                    lines.append("    int %s; // +0x%X (%s)" % (mname, moffset, mtype))
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
            # Also treat as thiscall if params contain '*this' (IDA sometimes omits __thiscall)
            if not is_thiscall and '*this' in params:
                is_thiscall = True
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

            # Skip invalid method names and calling conventions
            if '`' in method_name or ' ' in method_name or '?' in method_name:
                continue
            # Skip methods with vtable types in signature (IDA internal)
            if 'vtbl_' in ret or 'vtbl_' in params or '__vftable' in sig:
                lines.append("    // [IDA_VTABLE] %s; // %s" % (method_name, addr))
                continue
            if '__userpurge' in sig or '__usercall' in sig:
                lines.append("    // [IDA_USERPURGE] %s; // %s" % (method_name, addr))
                continue
            if '@<' in sig:
                lines.append("    // [IDA_REGPARAM] %s; // %s" % (method_name, addr))
                continue
            # Complex signatures (function pointer return types) -> simplify
            if sig.count('(') > 2:
                lines.append("    // [IDA_COMPLEX_RET] original: %s" % sig[:80])
                ret = 'int'
                params = ''

            # Deduplicate: skip if same method name+params already declared
            method_key = "%s(%s)" % (method_name, params)
            if method_key in seen_methods:
                continue
            seen_methods.add(method_key)

            # Fix IDA type misidentification in method declarations
            decl = decl.replace('stdiobuf *', 'UIWnd *')
            decl = decl.replace('stdiobuf', 'UIWnd')
            decl = decl.replace('std::ios_base *', 'UIWnd *')
            lines.append("%s // %s" % (decl, addr))

    lines.append("};")
    lines.append("")
    return '\n'.join(lines)


def main():
    # Load PDB class data
    with open(PDB_FILE, 'r', encoding='utf-8') as f:
        pdb = json.load(f)

    pdb_classes = {}
    template_classes = {}  # template instances: "BaseName<...>" -> class data
    for c in pdb.get('classes', []):
        name = c.get('name', '')
        if not name:
            continue
        if '<' in name:
            # Template instance - store by simplified base name
            base_name = name.split('<')[0]
            if base_name and '::' not in base_name and c.get('size', 0) > 1:
                template_classes[base_name] = c
        elif '::' not in name:
            pdb_classes[name] = c

    # Override PDB data with IDA struct exports
    # Strategy: Use IDA struct when PDB is broken (size<=1) OR when IDA has
    # typed pointer members that PDB doesn't have (higher quality).
    # Do NOT override if PDB has good data and IDA just has primitives.
    ida_override_count = 0
    if IDA_STRUCTS_FILE.exists():
        ida_data = json.load(open(IDA_STRUCTS_FILE, encoding='utf-8'))
        for s in ida_data.get('structs', []):
            sname = s.get('name', '')
            ssize = s.get('size', 0)
            if not sname or ssize <= 1 or should_skip_class(sname):
                continue
            if '$' in sname or ':' in sname or '?' in sname or '<' in sname:
                continue
            if not sname[0].isalpha() and sname[0] != '_':
                continue

            pdb_entry = pdb_classes.get(sname)
            pdb_size = pdb_entry.get('size', 0) if pdb_entry else 0

            # Override if PDB is broken (forward-declared, size<=1)
            if pdb_size <= 1:
                pdb_classes[sname] = s
                ida_override_count += 1
            # Don't override PDB with IDA if PDB already has layout
            # (PDB types are from source code, IDA types may have wrong offsets for PAL3)

        print("  IDA struct overrides: %d (PDB broken only)" % ida_override_count)

    # Collect methods from decomp
    methods_by_class = collect_methods()

    # Generate headers for all classes that have either members or methods
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    generated = 0
    all_classes = set(pdb_classes.keys()) | set(methods_by_class.keys())

    # Pre-compute set of all class names that will have headers generated
    classes_with_headers = set()
    for cls_name in all_classes:
        if should_skip_class(cls_name):
            continue
        pdb_class = pdb_classes.get(cls_name)
        methods_list = methods_by_class.get(cls_name, [])
        has_members = pdb_class and pdb_class.get('data_members') and pdb_class.get('size', 0) > 1
        has_methods = len(methods_list) >= 1
        if has_members or has_methods:
            classes_with_headers.add(cls_name)
    # Also include template stubs and enums
    for base_name in template_classes:
        if not should_skip_class(base_name):
            classes_with_headers.add(base_name)
    for e in pdb.get('enums', []):
        ename = e.get('name', '')
        if ename and ename[0].isalpha() and '<' not in ename and '::' not in ename:
            classes_with_headers.add(ename)

    for cls_name in sorted(all_classes):
        if should_skip_class(cls_name):
            continue

        pdb_class = pdb_classes.get(cls_name)
        methods = methods_by_class.get(cls_name, [])

        # Skip if no useful content
        has_members = pdb_class and pdb_class.get('data_members') and pdb_class.get('size', 0) > 1
        has_methods = len(methods) >= 1
        if not has_members and not has_methods:
            continue

        content = generate_header(cls_name, pdb_class, methods, classes_with_headers)
        output_path = OUTPUT_DIR / ("%s.h" % cls_name)
        with open(output_path, 'w', encoding='utf-8') as f:
            f.write(content)
        generated += 1

    # Generate enum headers
    enum_count = 0
    for e in pdb.get('enums', []):
        name = e.get('name', '')
        values = e.get('values', {})
        if not name or '<' in name or '::' in name:
            continue
        if not name[0].isalpha():
            continue

        lines = ['#pragma once', '// Auto-generated: %s enum' % name, '']
        lines.append('enum %s {' % name)
        sorted_vals = sorted(values.items(), key=lambda x: int(x[1]))
        for vname, vval in sorted_vals:
            lines.append('    %s = %s,' % (vname, vval))
        lines.append('};')
        lines.append('')

        out_path = OUTPUT_DIR / ('%s.h' % name)
        with open(out_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))
        enum_count += 1

    # Generate template class stubs (simplified, non-template version)
    tmpl_count = 0
    for base_name, tc in sorted(template_classes.items()):
        if should_skip_class(base_name):
            continue
        # Skip if already generated as a normal class
        out_path = OUTPUT_DIR / ('%s.h' % base_name)
        if out_path.exists():
            continue

        members = tc.get('data_members', [])
        size = tc.get('size', 0)
        if not members or size <= 1:
            continue

        lines = ['#pragma once']
        lines.append('// Auto-generated: %s (template class, simplified)' % base_name)
        lines.append('// Original: %s' % tc.get('name', base_name))
        lines.append('// Size: 0x%X (%d bytes) from PAL3A PDB' % (size, size))
        lines.append('')
        lines.append('class %s {' % base_name)
        lines.append('public:')
        for m in members:
            mname = m.get('name', '_unk_%04X' % m.get('offset', 0))
            mtype = m.get('type', 'int')
            moffset = m.get('offset', 0)
            # Simplify template types in members
            if '<' in mtype:
                mtype = 'void *'
            lines.append('    %s %s; // +0x%X' % (mtype, mname, moffset))
        lines.append('    // total size: 0x%X (%d)' % (size, size))
        lines.append('};')
        lines.append('')

        with open(out_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))
        tmpl_count += 1

    print("Generated %d header files in %s" % (generated, OUTPUT_DIR))
    print("  With PDB layout: %d" % sum(1 for c in all_classes
          if c in pdb_classes and pdb_classes[c].get('data_members') and pdb_classes[c].get('size', 0) > 1))
    print("  With methods: %d" % sum(1 for c in all_classes if c in methods_by_class and methods_by_class[c]))
    print("  Enums: %d" % enum_count)
    print("  Template stubs: %d" % tmpl_count)


if __name__ == '__main__':
    main()
