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

PIPELINE_ROOT = Path(__file__).parent.parent
PROJECT_ROOT = PIPELINE_ROOT.parent
PDB_FILE = PIPELINE_ROOT / "data" / "pdb" / "pdb_export.json"
ANNOTATIONS_DIR = PIPELINE_ROOT / "data" / "annotations"
IDA_STRUCTS_FILE = PROJECT_ROOT / "asm" / "pal3" / "ida_structs.json"
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
OUTPUT_DIR = PROJECT_ROOT / "include" / "pal3" / "gen"
OVERRIDES_DIR = PROJECT_ROOT / "include" / "pal3" / "overrides"


_annotations_cache = None

def load_annotations_data():
    """从拆分目录加载标注数据（带缓存）。"""
    global _annotations_cache
    if _annotations_cache is not None:
        return _annotations_cache
    ann_dir = ANNOTATIONS_DIR
    structs = {}
    structs_dir = ann_dir / "structs"
    if structs_dir.exists():
        for f in structs_dir.glob("*.json"):
            sdata = json.load(open(f, encoding='utf-8'))
            sname = sdata.pop('name', f.stem)
            structs[sname] = sdata
    vtables = {}
    vt_file = ann_dir / "vtables.json"
    if vt_file.exists():
        vtables = json.load(open(vt_file, encoding='utf-8'))
    _annotations_cache = {'structs': structs, 'vtables': vtables}
    return _annotations_cache


# Skip STL/CRT/Windows types (already defined by system headers)
SKIP_CLASSES = {
    'std', 'stdiobuf', 'exception', 'type_info', 'filebuf',
    # Windows types
    'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG', 'RECT', 'POINT', 'SIZE',
    'WNDCLASSA', 'tagWNDCLASSA', 'tagOFNA',
    '_FILETIME', '_SYSTEMTIME', '_MEMORYSTATUS', '_SECURITY_ATTRIBUTES',
    '_OSVERSIONINFOA', '_STARTUPINFOA', '_WIN32_FIND_DATAA',
    '_GUID', 'GUID', 'IID',
    # CRT / Runtime
    '_iobuf', 'FILE', '_cpinfo', '_EXCEPTION_RECORD', 'EXCEPTION_RECORD',
    'Concurrency',
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


def generate_header(cls_name, pdb_class, methods, known_classes=None, enum_names=None):
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
                  'unsigned __int16', 'unsigned __int32',
                  '_BYTE', '_WORD', '_DWORD', '_QWORD', '_UNKNOWN',
                  'CHAR', 'WCHAR', 'LONG', 'ULONG', 'INT', 'UINT',
                  'BOOL', 'SIZE_T', 'size_t', 'LPCSTR', 'LPSTR',
                  'LPCWSTR', 'LPWSTR', 'LPVOID',
                  'const', 'signed', 'unsigned __int8',
                  'struct', 'class', 'enum', 'union', 'static', 'extern',
                  'virtual', 'inline', 'register', 'volatile', 'mutable',
                  '__thiscall', '__cdecl', '__stdcall', '__fastcall'}

    # Types provided by windows.h / CRT — already available, no include/fwd needed
    # NOTE: Do NOT include gbengine types here — they need include/fwd-declare
    WINDOWS_CRT_TYPES = {
        'std', 'stdiobuf', 'exception', 'type_info', 'filebuf',
        'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG', 'RECT', 'POINT', 'SIZE',
        'HWND', 'HINSTANCE', 'HICON', 'HBRUSH', 'HDC', 'HANDLE', 'LPVOID',
        'WNDCLASSA', 'tagWNDCLASSA', 'tagOFNA', '_GUID', 'GUID', 'IID',
        '_iobuf', 'FILE', '_cpinfo', '_EXCEPTION_RECORD', 'EXCEPTION_RECORD',
        '_DIMOUSESTATE2', '_FILETIME', '_SYSTEMTIME', '_MEMORYSTATUS',
        '_SECURITY_ATTRIBUTES', '_OSVERSIONINFOA', '_STARTUPINFOA',
        '_WIN32_FIND_DATAA',
        'CRITICAL_SECTION', 'HRESULT', 'BOOL', 'LPCSTR', 'LPSTR',
        'HICON__', 'LRESULT', 'HCURSOR', 'LPARAM', 'WPARAM', 'LCID',
        'IDirectInput8A', 'IDirectInputDevice8A',
    }
    SYSTEM_TYPES = WINDOWS_CRT_TYPES

    # gbengine types — have headers in include/gbengine/, need include or fwd-declare
    # Build mapping: type_name -> header file path (relative to include/)
    GBENGINE_HEADER_DIR = PROJECT_ROOT / "include" / "gbengine"
    _gbengine_type_to_header = {}
    if GBENGINE_HEADER_DIR.exists():
        for hf in GBENGINE_HEADER_DIR.glob("*.h"):
            with open(hf, 'r', encoding='utf-8', errors='replace') as fh:
                for line in fh:
                    m = re.match(r'^(?:class|struct|enum)\s+(\w+)', line)
                    if m:
                        _gbengine_type_to_header.setdefault(m.group(1), "gbengine/%s" % hf.name)

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

    # Also scan annotation known_members for type references
    try:
        ann_data_ref = load_annotations_data()
        ann_struct_ref = ann_data_ref.get('structs', {}).get(cls_name, {})
        for m in ann_struct_ref.get('known_members', {}).values():
            mtype = m.get('type', '')
            is_ptr = '*' in mtype
            base = re.sub(r'\[\d+\]', '', mtype).replace('*', '').strip()
            if not base or base == cls_name or base in PRIMITIVES or base in SYSTEM_TYPES:
                continue
            if '::' in base or '<' in base:
                continue
            if is_ptr:
                fwd_types.add(base)
            else:
                include_types.add(base)
    except:
        pass

    # Also scan method signatures for type references (all pointer/ref -> fwd_types)
    if methods:
        for method_name, sig, addr in methods:
            # Extract all type names from signature
            all_types_in_sig = re.findall(r'\b([A-Za-z_][A-Za-z0-9_]*)\b\s*\*', sig)
            for t in all_types_in_sig:
                if t == cls_name or t in PRIMITIVES or t in SYSTEM_TYPES:
                    continue
                if '::' in t or '<' in t:
                    continue
                fwd_types.add(t)
            # Also check return type and value params (non-pointer custom types)
            ret_match = re.match(r'^(?:static\s+)?(\w+)\s', sig)
            if ret_match:
                rt = ret_match.group(1)
                if rt not in PRIMITIVES and rt not in SYSTEM_TYPES and rt != cls_name and rt != 'void':
                    fwd_types.add(rt)

    # Don't forward-declare what we're including
    fwd_types -= include_types
    # Remove system types from both sets
    include_types -= SYSTEM_TYPES
    fwd_types -= SYSTEM_TYPES
    # Remove invalid identifiers (anonymous PDB types like $S28, keywords, etc.)
    def _valid_type_name(t):
        return bool(re.match(r'^[A-Za-z_][A-Za-z0-9_]*$', t)) and '$' not in t
    include_types = {t for t in include_types if _valid_type_name(t)}
    fwd_types = {t for t in fwd_types if _valid_type_name(t)}

    # Resolve include paths: gbengine types -> "gbengine/xxx.h", pal3 gen types -> "xxx.h"
    # Types needing full definition but no header -> demote to fwd_types
    if known_classes is not None:
        resolved_includes = set()
        for t in include_types:
            if t in _gbengine_type_to_header:
                resolved_includes.add(t)
            elif t in known_classes:
                resolved_includes.add(t)
            else:
                fwd_types.add(t)
        include_types = resolved_includes

    # Also resolve gbengine fwd types — if they have a header, we can fwd-declare
    # (pointer-only usage doesn't need the header)

    # Emit includes
    for t in sorted(include_types):
        if t in _gbengine_type_to_header:
            lines.append('#include "%s"' % _gbengine_type_to_header[t])
        else:
            lines.append('#include "%s.h"' % t)
    if include_types:
        lines.append("")

    # Enums can't be forward-declared in VC6 — promote to include
    if enum_names:
        enum_fwd = fwd_types & enum_names
        for t in sorted(enum_fwd):
            if t in _gbengine_type_to_header:
                lines.append('#include "%s"' % _gbengine_type_to_header[t])
            else:
                lines.append('#include "%s.h"' % t)
        fwd_types -= enum_fwd

    # Emit forward declarations for class types
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
            ann_data = load_annotations_data()
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

    # Virtual methods from vtable (must be first, order matches vtable layout)
    vtable_method_names = set()  # track names declared via vtable (including inherited)
    try:
        ann_data_vt = load_annotations_data()
        vtables_data = ann_data_vt.get('vtables', {})

        # Collect inherited vtable method names from base classes
        def _collect_base_vtable_names(class_name, visited=None):
            if visited is None:
                visited = set()
            if class_name in visited:
                return set()
            visited.add(class_name)
            names = set()
            for vt_name, vt_info in vtables_data.items():
                if vt_info.get('class') == class_name:
                    for vm in vt_info.get('methods', []):
                        vm_name = vm.get('name', '')
                        if '::' in vm_name:
                            names.add(vm_name.split('::')[-1])
                        elif vm_name.startswith('sub_'):
                            names.add(vm_name)
            # Recurse into base classes
            ann_s = ann_data_vt.get('structs', {}).get(class_name, {})
            base = ann_s.get('base_class')
            if base:
                names |= _collect_base_vtable_names(base, visited)
            return names

        for bn in base_names:
            vtable_method_names |= _collect_base_vtable_names(bn)

        # Find the vtable for this class (smallest = base class vtable)
        cls_vtables = [(name, info) for name, info in vtables_data.items()
                       if info.get('class') == cls_name]
        if cls_vtables:
            cls_vtables.sort(key=lambda x: len(x[1].get('methods', [])))
            vt_name, vt_info = cls_vtables[0]
            vt_methods = vt_info.get('methods', [])
            if vt_methods and not base_names:
                lines.append("    // vtable (%s, %d methods)" % (vt_name, len(vt_methods)))
                seen_vnames = set()
                for vm in vt_methods:
                    vm_name = vm.get('name', '')
                    vm_sig = vm.get('signature', '')
                    short = 'unknown'
                    if '::' in vm_name:
                        short = vm_name.split('::')[-1]
                        short = re.sub(r'[^a-zA-Z0-9_]', '_', short)
                    elif vm_name.startswith('sub_'):
                        short = vm_name
                    if short in seen_vnames:
                        short = '%s_%s' % (short, vm.get('address', '0')[-4:])
                    seen_vnames.add(short)
                    vtable_method_names.add(short)
                    # Parse signature to extract return type and params
                    if vm_sig:
                        sig_clean = vm_sig.strip().rstrip(';')
                        # Match "rettype [__cc] funcname(args)"
                        fp_match = re.match(r'^(.+?)(?:\s+__\w+)?\s+\w+\s*(\(.*\))$', sig_clean)
                        if fp_match:
                            ret = fp_match.group(1).strip()
                            args = fp_match.group(2)
                            # Remove this pointer from args
                            arg_str = args.strip('()')
                            arg_list = [a.strip() for a in arg_str.split(',') if a.strip()]
                            if arg_list and ('this' in arg_list[0] or '*this' in arg_list[0]):
                                arg_list = arg_list[1:]
                            lines.append("    virtual %s %s(%s);" % (ret, short, ', '.join(arg_list)))
                        else:
                            lines.append("    virtual int %s();" % short)
                    else:
                        lines.append("    virtual int %s();" % short)
                lines.append("")
    except:
        pass

    # Data members
    # Determine base class size to skip inherited members
    base_size = 0
    if base_names:
        try:
            ann_data = load_annotations_data()
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
    elif not pdb_class or not pdb_class.get('data_members'):
        # Fallback: generate from annotation known_members
        try:
            ann_data_fb = load_annotations_data()
            ann_struct_fb = ann_data_fb.get('structs', {}).get(cls_name, {})
            ann_members = ann_struct_fb.get('known_members', {})
            ann_size = ann_struct_fb.get('binary_size')
            if ann_members:
                sorted_members = sorted(ann_members.items(), key=lambda x: int(x[0]))
                for off_str, m in sorted_members:
                    mname = m.get('name', '_field_%04X' % int(off_str))
                    mtype = m.get('type', 'int')
                    off = int(off_str)
                    if base_size > 0 and off < base_size:
                        continue
                    arr_match = re.search(r'(\[\d+\](?:\[\d+\])*)$', mtype)
                    if arr_match:
                        arr_part = arr_match.group(1)
                        base_type = mtype[:arr_match.start()].rstrip()
                        lines.append("    %s %s%s; // +0x%X" % (base_type, mname, arr_part, off))
                    else:
                        lines.append("    %s %s; // +0x%X" % (mtype, mname, off))
                if ann_size and ann_size != '?':
                    lines.append("    // total size: 0x%X (%d)" % (int(ann_size), int(ann_size)))
                lines.append("")
        except:
            pass

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

            # Fix invalid parameter names (starting with digit like "int 14C")
            if params:
                def _fix_param(p):
                    p = p.strip()
                    # Match: "type [*] name" where name starts with digit
                    m = re.match(r'^(.+?[\s\*])(\d\w*)$', p)
                    if m:
                        return '%s a_%s' % (m.group(1), m.group(2))
                    return p
                param_list = split_params(params)
                params = ', '.join(_fix_param(p) for p in param_list)

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
            # Complex signatures (function pointer return types) -> skip
            if sig.count('(') > 2:
                lines.append("    // [IDA_COMPLEX_RET] original: %s" % sig[:80])
                continue

            # Skip methods already declared in vtable (avoids signature conflicts)
            if method_name in vtable_method_names:
                lines.append("    // [VTABLE_DUP] %s; // %s" % (decl.strip(), addr))
                continue

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
    # IDB is the authoritative source: PDB (PAL3A) + gbengine headers + annotations
    # IDA structs always take priority over PDB when they have more/better data
    ida_override_count = 0
    if IDA_STRUCTS_FILE.exists():
        ida_data = json.load(open(IDA_STRUCTS_FILE, encoding='utf-8'))
        # Support both formats: dict {name: {...}} or list [{name, ...}]
        if isinstance(ida_data, dict):
            ida_items = [(k, v) for k, v in ida_data.items() if isinstance(v, dict)]
        else:
            ida_items = [(s.get('name', ''), s) for s in ida_data.get('structs', [])]

        for sname, s in ida_items:
            ssize = s.get('size', 0)
            if not sname or ssize <= 1 or should_skip_class(sname):
                continue
            if '$' in sname or ':' in sname or '?' in sname or '<' in sname:
                continue
            if not sname[0].isalpha() and sname[0] != '_':
                continue

            pdb_entry = pdb_classes.get(sname)
            pdb_size = pdb_entry.get('size', 0) if pdb_entry else 0
            ida_members = len(s.get('data_members', []))

            # IDA struct overrides PDB when:
            # 1. PDB has no data (size<=1)
            # 2. IDA has larger size (binary_size > pdb_size)
            # 3. IDA has more members (annotation filled gaps)
            pdb_members = len(pdb_entry.get('data_members', [])) if pdb_entry else 0
            if pdb_size <= 1 or ssize > pdb_size or ida_members > pdb_members:
                pdb_classes[sname] = s
                ida_override_count += 1

        print("  IDA struct overrides: %d" % ida_override_count)

    # Collect methods from decomp
    methods_by_class = collect_methods()

    # Generate headers for all classes that have either members or methods
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    # Load annotations for vtable info
    ann_data_all = load_annotations_data()
    vtable_classes = set(v.get('class', '') for v in ann_data_all.get('vtables', {}).values())
    vtable_classes.discard('')
    vtable_classes -= {'crt_internal', 'std_locale_facet'}

    generated = 0
    ann_structs = set(ann_data_all.get('structs', {}).keys())
    all_classes = set(pdb_classes.keys()) | set(methods_by_class.keys()) | vtable_classes | ann_structs

    # Pre-compute set of all class names that will have headers generated
    classes_with_headers = set()
    for cls_name in all_classes:
        if should_skip_class(cls_name):
            continue
        pdb_class = pdb_classes.get(cls_name)
        methods_list = methods_by_class.get(cls_name, [])
        has_members = pdb_class and pdb_class.get('data_members') and pdb_class.get('size', 0) > 1
        has_methods = len(methods_list) >= 1
        ann_s = ann_data_all.get('structs', {}).get(cls_name, {})
        has_ann = bool(ann_s.get('known_members'))
        if has_members or has_methods or has_ann:
            classes_with_headers.add(cls_name)
    # Also include template stubs and enums
    for base_name in template_classes:
        if not should_skip_class(base_name):
            classes_with_headers.add(base_name)
    enum_names = set()
    for e in pdb.get('enums', []):
        ename = e.get('name', '')
        if ename and (ename[0].isalpha() or ename[0] == '_') and '<' not in ename and '::' not in ename:
            classes_with_headers.add(ename)
            enum_names.add(ename)

    for cls_name in sorted(all_classes):
        if should_skip_class(cls_name):
            continue

        pdb_class = pdb_classes.get(cls_name)
        methods = methods_by_class.get(cls_name, [])

        # Skip if no useful content (but keep if has vtable or annotation members)
        has_members = pdb_class and pdb_class.get('data_members') and pdb_class.get('size', 0) > 1
        has_methods = len(methods) >= 1
        has_vtable = any(v.get('class') == cls_name for v in ann_data_all.get('vtables', {}).values())
        ann_struct = ann_data_all.get('structs', {}).get(cls_name, {})
        has_ann_members = bool(ann_struct.get('known_members'))
        if not has_members and not has_methods and not has_vtable and not has_ann_members:
            continue

        content = generate_header(cls_name, pdb_class, methods, classes_with_headers, enum_names)
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
        # Allow _-prefixed game enums, skip system _-prefixed ones
        GAME_ENUMS_UNDERSCORE = {'_BGM', '_FLIP', '_BIGMAP_ELEMENT', '_MU_R_STATE'}
        if not name[0].isalpha() and name not in GAME_ENUMS_UNDERSCORE:
            continue
        if should_skip_class(name):
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

    # --- Generate globals.h from annotations ---
    generate_globals()


def generate_globals():
    """Generate include/pal3/globals.h from globals.json + binary initial values."""
    import struct as _st

    globals_json = PIPELINE_ROOT / "data" / "annotations" / "globals.json"
    if not globals_json.exists():
        return

    exe_path = PROJECT_ROOT / "original" / "PAL3.exe"
    exe_data = open(exe_path, 'rb').read() if exe_path.exists() else None

    globs = json.load(open(globals_json, 'r', encoding='utf-8'))

    # PE section info for reading initial values
    DATA_VA = 0x580000
    RDATA_VA = 0x56A000
    RDATA_END = 0x57F178
    BSS_START = 0xBF0000  # approximate: .bss starts around here (uninitialized)

    def read_init_value(addr, typ):
        """Read initial value from .data section of binary."""
        if exe_data is None:
            return None
        foff = addr - 0x400000
        if foff < 0 or foff + 8 > len(exe_data):
            return None
        # .rdata and .data have file backing; .bss does not
        if addr >= BSS_START:
            return None  # uninitialized, default 0
        if 'float' in typ:
            val = _st.unpack_from('<f', exe_data, foff)[0]
            if val == 0.0:
                return None  # skip zero-init (default)
            if val == int(val) and abs(val) < 1e6:
                return '%d.0f' % int(val)
            return '%.7gf' % val
        if 'double' in typ:
            val = _st.unpack_from('<d', exe_data, foff)[0]
            if val == 0.0:
                return None
            return '%.15g' % val
        if any(t in typ for t in ['int', 'DWORD', 'LONG', 'UINT', 'BOOL', 'unsigned long']):
            val = _st.unpack_from('<I', exe_data, foff)[0]
            if val == 0:
                return None
            if val > 0x7FFFFFFF:
                return '0x%X' % val
            return str(val)
        return None

    # Sort by address
    sorted_globs = sorted(globs.items(), key=lambda x: int(x[0], 16))

    # Generate globals.h (extern declarations)
    h_lines = [
        '#pragma once',
        '// PAL3 global variables with known types',
        '// Auto-generated from pipeline/data/annotations/globals.json',
        '',
        '#include <windows.h>',
        '',
        '// %d typed globals' % len(sorted_globs),
        '',
    ]

    # includes_needed: types that need full definition (#include header)
    # fwd_classes: types that only need forward declaration (pointers only)
    includes_needed = set()
    fwd_classes = set()
    gen_header_dir = PROJECT_ROOT / "include" / "pal3" / "gen"

    def extract_base_type(t):
        """Extract base type name from a type string."""
        b = t.replace('const ', '').replace('*', '').replace('[]', '').strip()
        return re.sub(r'\[\d+\]', '', b).strip()

    for addr_str, g in sorted_globs:
        name = g.get('name', '')
        typ = g.get('type', 'int')
        if not name:
            continue
        # Skip IDA default names (they go in per-file forward decls)
        if re.match(r'^(dword|byte|flt|word|off|stru|unk|asc)_', name):
            continue

        base_typ = extract_base_type(typ)
        is_pointer_only = '*' in typ and '[' not in typ
        has_header = (gen_header_dir / ("%s.h" % base_typ)).exists()
        has_struct = (PIPELINE_ROOT / "data" / "annotations" / "structs" / ("%s.json" % base_typ)).exists()

        # Track types needing full definition vs forward declaration
        if has_struct and not is_pointer_only:
            if has_header:
                includes_needed.add(base_typ)
            else:
                fwd_classes.add(base_typ)
        elif has_struct and is_pointer_only:
            if base_typ not in includes_needed:
                fwd_classes.add(base_typ)

        # Emit extern declaration with correct C syntax
        arr_match = re.match(r'^(.+?)(\[\d*\])$', typ)
        ptr_arr_match = re.match(r'^(.+\*)\s*(\[\d+\])$', typ)

        if ptr_arr_match:
            base, arr = ptr_arr_match.group(1).strip(), ptr_arr_match.group(2)
            h_lines.append('extern %s %s%s; // %s' % (base, name, arr, addr_str))
        elif arr_match and '*' not in typ:
            base, arr = arr_match.group(1).strip(), arr_match.group(2)
            h_lines.append('extern %s %s%s; // %s' % (base, name, arr, addr_str))
        elif '[]' in typ:
            base = typ.replace('[]', '').strip()
            h_lines.append('extern %s %s[]; // %s' % (base, name, addr_str))
        elif '*' in typ:
            h_lines.append('extern %s %s; // %s' % (typ, name, addr_str))
        else:
            h_lines.append('extern %s %s; // %s' % (typ, name, addr_str))

    # Remove from fwd_classes anything already in includes_needed
    fwd_classes -= includes_needed

    # Insert #include for types needing full definition
    insert_pos = 8  # after #include <windows.h> and blank line
    if includes_needed:
        for cls in sorted(includes_needed):
            h_lines.insert(insert_pos, '#include "pal3/gen/%s.h"' % cls)
            insert_pos += 1
        h_lines.insert(insert_pos, '')
        insert_pos += 1
    # Insert forward declarations for pointer-only types
    if fwd_classes:
        for cls in sorted(fwd_classes):
            h_lines.insert(insert_pos, 'class %s;' % cls)
            insert_pos += 1
        h_lines.insert(insert_pos, '')

    globals_h = PROJECT_ROOT / "include" / "pal3" / "globals.h"
    with open(globals_h, 'w', encoding='utf-8') as f:
        f.write('\n'.join(h_lines) + '\n')

    print("  Globals: %d in globals.h" % (len(h_lines) - 6))


if __name__ == '__main__':
    main()
