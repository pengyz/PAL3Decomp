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
import sys
from collections import defaultdict
from pathlib import Path

PIPELINE_ROOT = Path(__file__).parent.parent.parent  # pipeline/
PROJECT_ROOT = PIPELINE_ROOT.parent
PDB_FILE = PROJECT_ROOT / "data" / "pdb" / "pdb_export.json"
ANNOTATIONS_DIR = PROJECT_ROOT / "data" / "annotations"
IDA_STRUCTS_FILE = PROJECT_ROOT / "asm" / "pal3" / "ida_structs.json"
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
OUTPUT_DIR = PROJECT_ROOT / "include" / "pal3" / "gen"
OVERRIDES_DIR = PROJECT_ROOT / "include" / "pal3" / "overrides"


_annotations_cache = None
_header_errors = []

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
    'std', 'stdiobuf', 'exception', 'type_info', 'filebuf', 'string',
    'strstreambuf', 'ios_base', 'facet', 'codecvt_base',
    '_ThrowInfo', '_CatchableType', '_CatchableTypeArray',
    # C/C++ reserved words that IDA may use as class names
    'float', 'int', 'char', 'void', 'double', 'long', 'short', 'bool',
    # Windows SDK typedefs that clash with IDA struct names
    'DOUBLE', 'FLOAT', 'INT', 'CHAR', 'VOID', 'LONG', 'SHORT', 'BOOL',
    'BYTE', 'WORD', 'DWORD', 'UINT', 'ULONG',
    # Windows types
    'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG', 'RECT', 'POINT', 'SIZE',
    'tagRGBQUAD', 'RGBQUAD',
    'WNDCLASSA', 'tagWNDCLASSA', 'tagOFNA',
    '_FILETIME', '_SYSTEMTIME', '_MEMORYSTATUS', '_SECURITY_ATTRIBUTES',
    '_OSVERSIONINFOA', '_STARTUPINFOA', '_WIN32_FIND_DATAA',
    '_GUID', 'GUID', 'IID',
    'tagNMHDR', 'tagNMITEMACTIVATE', 'tagLVCOLUMNA', 'tagLVITEMA',
    'tagTCITEMA', 'tagCOPYDATASTRUCT', 'tagPALETTEENTRY',
    'tagKBDLLHOOKSTRUCT',
    # Windows handle types (HXXX__)
    'HICON__', 'HWND__', 'HDC__', 'HINSTANCE__', 'HBRUSH__',
    'HHOOK__', 'HKEY__', 'HMONITOR__', 'HWAVEOUT__',
    # COM/OLE enums and types (defined by platform SDK)
    'tagCLSCTX', 'tagCOINIT', 'tagCALLCONV', 'tagCALLTYPE',
    'tagFUNCKIND', 'tagFUNCFLAGS', 'tagINVOKEKIND', 'tagVARKIND',
    'tagVARFLAGS', 'tagTYPEKIND', 'tagTYPEFLAGS', 'tagSYSKIND',
    'tagLIBFLAGS', 'tagDESCKIND', 'tagCHANGEKIND', 'tagTYMED',
    'tagDVASPECT', 'tagSTGTY', 'tagSTGC', 'tagSTGMOVE',
    'tagSTATFLAG', 'tagLOCKTYPE', 'tagSTREAM_SEEK', 'tagBIND_FLAGS',
    'tagMKSYS', 'tagMKREDUCE', 'tagADVF', 'tagSF_TYPE',
    'tagREGCLS', 'tagPENDINGMSG', 'tagPENDINGTYPE', 'tagSERVERCALL',
    'tagMEMCTX', 'tagMSHCTX', 'tagMSHLFLAGS', 'tagSTDMSHLFLAGS',
    'tagEXTCONN', 'tagBINDSPEED', 'tagBINDSTATUS', 'tagBINDSTRING',
    'tagOLERENDER', 'tagOLEUPDATE', 'tagOLEVERBATTRIB', 'tagOLEMISC',
    'tagOLECLOSE', 'tagOLECONTF', 'tagOLEGETMONIKER', 'tagOLEWHICHMK',
    'tagOLELINKBIND', 'tagUSERCLASSTYPE', 'tagDISCARDCACHE',
    'tagURLZONE', 'tagURLTEMPLATE', 'tagCOWAIT_FLAGS',
    'tagDCOM_CALL_STATE', 'tagDATADIR',
    'tagEOLE_AUTHENTICATION_CAPABILITIES', 'tagExtendedErrorParamTypes',
    'tagDOMNodeType', 'tagXMLEMEM_TYPE', 'tagShutdownType',
    'tagApplicationType',
    'HandlerType',
    # CRT / Runtime
    '_iobuf', 'FILE', '_cpinfo', '_EXCEPTION_RECORD', 'EXCEPTION_RECORD',
    'Concurrency',
    # DirectX / DirectInput
    '_DIMOUSESTATE2',
    # IDA template instantiation artifacts
    'primitive', 'uint',
    # gbengine (separate library) — auto-populated below
}

# Auto-detect classes defined in gbengine headers
_GBENGINE_DIR = Path(__file__).parent.parent.parent.parent / "include" / "gbengine"
if _GBENGINE_DIR.exists():
    for _hf in _GBENGINE_DIR.glob("*.h"):
        with open(_hf, 'r', encoding='utf-8', errors='replace') as _fh:
            for _line in _fh:
                _m = re.match(r'^(?:class|struct)\s+(\w+)', _line)
                if _m:
                    SKIP_CLASSES.add(_m.group(1))

# Prefix patterns for system/library types that should never be generated
SKIP_PREFIXES = (
    'D3D', '_D3D', 'ID3D', 'IDirect', 'IUnknown',
    'CD3D',  # D3D helper classes from SDK samples
    'D3DX',  # D3DX math types
    'gb',    # gbengine types (all start with gb)
    'vtbl_', # IDA vtable structs (not real C++ types)
    '_DI',   # DirectInput internal structs (defined by dinput.h)
    '_IMAGE',# PE header structs (defined by winnt.h)
    '_Crt',  # CRT debug internals
)


def should_skip_class(name):
    """Check if a class name should be skipped (system/library type)."""
    if not name or len(name) <= 1:
        return True
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
    """Parse IDA signature into (return_type, calling_conv, params_str, ret_right).

    For normal functions: ret_right is ''.
    For functions returning function pointers (e.g.
      "int (__thiscall *__thiscall(Class *this, int a2))(char *, int)"),
    ret_right contains the trailing parameter list of the returned fp type.
    """
    if not sig:
        return 'int', '', '', ''

    # Detect function-pointer return type: "... *CC(params)(fp_params)"
    fp_match = re.search(r'\*\s*(__thiscall|__cdecl|__stdcall|__fastcall)\s*\(', sig)
    if fp_match:
        cc = fp_match.group(1)
        ret_left = sig[:fp_match.start()+1]  # up to and including '*'
        # Find matching ')' for the '(' at end of fp_match
        paren_start = fp_match.end() - 1
        depth = 0
        paren_end = paren_start
        for i in range(paren_start, len(sig)):
            if sig[i] == '(':
                depth += 1
            elif sig[i] == ')':
                depth -= 1
                if depth == 0:
                    paren_end = i
                    break
        params = sig[paren_start+1:paren_end]
        ret_right = sig[paren_end+1:]
        return ret_left, cc, params, ret_right

    cc_match = re.search(r'(__thiscall|__cdecl|__stdcall|__fastcall)', sig)
    paren_match = re.search(r'\(', sig)

    if cc_match and paren_match:
        cc = cc_match.group(1)
        ret = sig[:cc_match.start()].rstrip()
        if not ret:
            ret = 'int'
        params = sig[paren_match.start()+1:sig.rfind(')')]
        return ret, cc, params, ''

    if paren_match:
        ret = sig[:paren_match.start()].rstrip()
        if not ret:
            ret = 'int'
        params = sig[paren_match.start()+1:sig.rfind(')')]
        return ret, '__cdecl', params, ''

    return 'int', '', '', ''


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
    """Collect all class methods from decomp JSONs + functions.json (fallback)."""
    classes = defaultdict(list)
    seen_addrs = set()

    # Primary source: decomp JSONs
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
        seen_addrs.add(addr)

    # Secondary source: functions.json (for functions not exported by IDA)
    funcs_json = ANNOTATIONS_DIR / "functions.json"
    if funcs_json.exists():
        funcs_data = json.load(open(funcs_json, encoding='utf-8'))
        for addr_str, info in funcs_data.items():
            if addr_str in seen_addrs:
                continue
            name = info.get('name', '')
            sig = info.get('signature', '')
            if '::' not in name or name.startswith('sub_'):
                continue
            parts = name.split('::', 1)
            cls = parts[0]
            method = parts[1]
            if should_skip_class(cls) or '`' in method or ' ' in method or '?' in method:
                continue
            addr = addr_str
            classes[cls].append((method, sig, addr))

    return classes


def simplify_stl_type(t, cls_name=None):
    """Simplify IDA-exported full STL type to short compilable form.

    std::vector<T,std::allocator<T>> → vector<T>
    std::queue<T,std::deque<T,std::allocator<T>>> → queue<T>
    std::basic_string<char,std::char_traits<char>,std::allocator<char>> → string
    """
    # Iteratively simplify until stable
    for _ in range(5):
        prev = t
        # Remove std::allocator<...> parameter (always default)
        t = re.sub(r',\s*std::allocator<[^<>]*(?:<[^<>]*>)?[^<>]*>\s*', '', t)
        # Remove std::deque<T> second param in queue/stack (default container)
        t = re.sub(r',\s*std::deque<([^<>]+)>\s*', '', t)
        # std::basic_string<char,std::char_traits<char>> → std::string
        t = re.sub(r'std::basic_string<char,\s*std::char_traits<char>\s*>', 'std::string', t)
        t = re.sub(r'std::basic_string<char>', 'std::string', t)
        if t == prev:
            break
    # Strip std:: prefix (pal3_stl.h has 'using namespace std')
    t = t.replace('std::', '')
    # Strip own class prefix for nested types inside class body
    if cls_name:
        t = re.sub(r'\b%s::' % re.escape(cls_name), '', t)
    # Clean up extra spaces
    t = re.sub(r'\s+', ' ', t).strip()
    # Remove trailing space before >
    t = re.sub(r'\s+>', '>', t)
    return t


def _estimate_member_size(mtype):
    """Estimate size of a member from its type string."""
    # Pointer types
    if '*' in mtype:
        return 4
    # Array types: "Type[N]" or "Type[N][M]"
    arr_match = re.search(r'\[(\d+)\](?:\[(\d+)\])?$', mtype)
    if arr_match:
        base = mtype[:arr_match.start()].strip()
        count = int(arr_match.group(1))
        count2 = int(arr_match.group(2)) if arr_match.group(2) else 1
        return _estimate_member_size(base) * count * count2
    # Known sizes
    t = mtype.strip()
    if t in ('char', 'unsigned char', 'BYTE', '_BYTE', 'bool'):
        return 1
    if t in ('short', 'unsigned short', 'WORD', '_WORD', 'wchar_t'):
        return 2
    if t in ('int', 'unsigned int', 'long', 'unsigned long', 'DWORD',
             '_DWORD', 'UINT', 'LONG', 'BOOL', 'HRESULT', 'float', 'HWND',
             'HANDLE', 'HINSTANCE', 'HDC', 'LPVOID'):
        return 4
    if t in ('double', '__int64', 'LONGLONG', 'ULONGLONG'):
        return 8
    # Strip nested class prefix: C2DSpark::tagSpark -> tagSpark
    if '::' in t:
        t = t.rsplit('::', 1)[-1]
    # Struct/class - check annotation cache first, then file
    try:
        ann = load_annotations_data()
        ann_s = ann.get('structs', {}).get(t, {})
        sz = ann_s.get('binary_size') or ann_s.get('gen_size')
        if sz and sz != '?':
            return int(sz)
    except:
        pass
    # Default: assume 4 bytes (int-sized)
    return 4


def generate_header(cls_name, pdb_class, methods, known_classes=None, enum_names=None,
                    colliding_enums=None):
    """Generate a complete header for one class."""
    lines = []
    lines.append("#pragma once")
    lines.append("// Auto-generated: %s" % cls_name)
    lines.append("")

    # Embed colliding enums (case-insensitive FS collision) before class definition
    if colliding_enums:
        for ename, edata in colliding_enums:
            values = edata.get('values', {})
            lines.append('enum %s {' % ename)
            for vname, vval in sorted(values.items(), key=lambda x: int(x[1])):
                lines.append('    %s = %s,' % (vname, vval))
            lines.append('};')
            lines.append('')

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
                        name = m.group(1)
                        header_path = "gbengine/%s" % hf.name
                        is_definition = ('{' in line or ':' in line)
                        # Prefer headers with full definitions over forward declarations
                        if name not in _gbengine_type_to_header or is_definition:
                            _gbengine_type_to_header[name] = header_path

    if pdb_class:
        # Inheritance -> include (simplify template names same as in class declaration)
        for b in pdb_class.get('bases', []) or []:
            bname = b['name']
            if '<' in bname:
                bname = bname.split('<')[0]  # CTaskTpl<...> -> CTaskTpl
            if '::' not in bname:
                include_types.add(bname)

    # Annotation base_class also needs include (inheritance requires full definition)
    try:
        _ann_for_base = load_annotations_data()
        _ann_base_cls = _ann_for_base.get('structs', {}).get(cls_name, {}).get('base_class')
        if _ann_base_cls and '<' not in _ann_base_cls and '::' not in _ann_base_cls:
            include_types.add(_ann_base_cls)
    except:
        pass

    if pdb_class:
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
    needs_stl = False
    try:
        ann_data_ref = load_annotations_data()
        ann_struct_ref = ann_data_ref.get('structs', {}).get(cls_name, {})
        for m in ann_struct_ref.get('known_members', {}).values():
            mtype = m.get('type', '')
            is_ptr = '*' in mtype
            # Detect STL template usage → need pal3_stl.h
            if '<' in mtype and ('std::' in mtype or any(
                    kw in mtype for kw in ('vector<', 'queue<', 'deque<', 'list<',
                                           'stack<', 'map<', 'string<', 'bitset<'))):
                needs_stl = True
                # Extract template argument types for include/fwd-declare
                # e.g. std::vector<ArcScene,...> → ArcScene needs include
                arg_types = re.findall(r'<\s*([A-Za-z_]\w*)', mtype)
                for at in arg_types:
                    if at == cls_name or at in PRIMITIVES or at in SYSTEM_TYPES:
                        continue
                    if at in ('std', 'char', 'float', 'int', 'unsigned'):
                        continue
                    # Template args used by value inside container → need full def
                    if at + ' *' not in mtype:
                        include_types.add(at)
                    else:
                        fwd_types.add(at)
                continue
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
    if needs_stl:
        lines.append('#include "pal3/pal3_stl.h"')
    for t in sorted(include_types):
        if t in _gbengine_type_to_header:
            lines.append('#include "%s"' % _gbengine_type_to_header[t])
        else:
            lines.append('#include "%s.h"' % t)
    if include_types or needs_stl:
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

    # Emit forward declarations for class types (skip IDA vtable structs)
    fwd_types = {t for t in fwd_types if not t.startswith('vtbl_')}
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
            # Inheritance requires full definition → include (not just fwd-declare)
            include_types.add(b)
            fwd_types.discard(b)

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
                lines.append("    // vtable (%s, %d methods) — signatures from IDA vtable, not authoritative" % (vt_name, len(vt_methods)))
                seen_vnames = set()
                for vm in vt_methods:
                    vm_name = vm.get('name', '')
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

    # Annotation known_members are authoritative over IDB/PDB struct layouts.
    # IDA's struct layout engine may compute different alignment/padding than MSVC 6.0,
    # causing offset drift in derived classes. Use annotation path when available.
    use_pdb_members = False
    try:
        _ann_d = load_annotations_data()
        _ann_s = _ann_d.get('structs', {}).get(cls_name, {})
    except:
        _ann_s = {}
    if _ann_s.get('known_members'):
        use_pdb_members = False
    elif pdb_class and pdb_class.get('data_members'):
        use_pdb_members = True

    if use_pdb_members:
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

            # Full type restoration for templates and nested types
            if '<' in mtype or 'std::' in mtype:
                mtype = simplify_stl_type(mtype, cls_name)
            elif '::' in mtype:
                mtype = re.sub(r'^%s::' % re.escape(cls_name), '', mtype)

            # Fix C99 flexible array "Type[]" -> "Type[1]" (VC6 workaround)
            mtype = re.sub(r'\[\]', '[1]', mtype)

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
    if not use_pdb_members:
        # Fallback: generate from annotation known_members with gap filling
        try:
            ann_data_fb = load_annotations_data()
            ann_struct_fb = ann_data_fb.get('structs', {}).get(cls_name, {})
            ann_members = ann_struct_fb.get('known_members', {})
            ann_size = ann_struct_fb.get('binary_size') or ann_struct_fb.get('gen_size')
            if ann_members or ann_size:
                sorted_members = sorted(ann_members.items(), key=lambda x: int(x[0])) if ann_members else []
                start_off = base_size
                for off_str, m in sorted_members:
                    mname = m.get('name', '_field_%04X' % int(off_str))
                    mtype = m.get('type', 'int')
                    off = int(off_str)
                    if off < start_off:
                        continue
                    # Insert gap padding before this member if needed
                    if off > start_off:
                        gap_size = off - start_off
                        lines.append("    char _gap_%03X[%d]; // +0x%X" % (start_off, gap_size, start_off))
                    # Fix C99 flexible array
                    mtype = re.sub(r'\[\]', '[1]', mtype)
                    # Full type restoration: annotation stores real C++ types,
                    # codegen outputs them directly (no flatten for IDA limitations)
                    if '<' in mtype or 'std::' in mtype:
                        simplified = simplify_stl_type(mtype, cls_name)
                        # Self-referencing nested types (e.g. queue<Common_State> inside
                        # SceneObj where Common_State = SceneObj::Common_State) need the
                        # nested type declared first. Since we don't have its layout,
                        # fall back to char[N] for these cases only.
                        original_has_self_ref = (cls_name + '::') in mtype
                        if original_has_self_ref:
                            idx_m = sorted_members.index((off_str, m))
                            if idx_m + 1 < len(sorted_members):
                                next_off = int(sorted_members[idx_m + 1][0])
                            else:
                                next_off = int(ann_size) if ann_size and ann_size != '?' else off + 4
                            msize = next_off - off
                            if msize > 0:
                                lines.append("    char %s[%d]; // +0x%X %s" % (mname, msize, off, simplified))
                            else:
                                lines.append("    int %s; // +0x%X %s" % (mname, off, simplified))
                            member_size = msize if msize > 0 else 4
                            start_off = off + member_size
                            continue
                        mtype = simplified
                    elif '::' in mtype:
                        # Strip own class prefix for nested types
                        mtype = re.sub(r'^%s::' % re.escape(cls_name), '', mtype)
                    # Emit member with real type
                    arr_match = re.search(r'(\[\d+\](?:\[\d+\])*)$', mtype)
                    if arr_match:
                        arr_part = arr_match.group(1)
                        base_type = mtype[:arr_match.start()].rstrip()
                        lines.append("    %s %s%s; // +0x%X" % (base_type, mname, arr_part, off))
                    else:
                        lines.append("    %s %s; // +0x%X" % (mtype, mname, off))
                    # Estimate member size to compute next start_off
                    member_size = _estimate_member_size(mtype)
                    start_off = off + member_size
                # Tail padding to reach total size
                if ann_size and ann_size != '?' and int(ann_size) > start_off:
                    tail_size = int(ann_size) - start_off
                    lines.append("    char _tail_%03X[%d]; // +0x%X" % (start_off, tail_size, start_off))
                if ann_size and ann_size != '?':
                    lines.append("    // total size: 0x%X (%d)" % (int(ann_size), int(ann_size)))
                lines.append("")
        except Exception as e:
            import traceback; traceback.print_exc()

    # Methods (deduplicate by name+params to avoid C2535)
    if methods:
        seen_methods = set()  # track "name(params)" to deduplicate
        for method_name, sig, addr in sorted(methods, key=lambda x: x[2]):
            ret, cc, params, ret_right = parse_signature(sig)

            # Remap IDA internal types to C types in signatures
            for ida_type, c_type in TYPE_REMAP.items():
                if ida_type in ret:
                    ret = ret.replace(ida_type, c_type)
                if ida_type in params:
                    params = params.replace(ida_type, c_type)

            is_ctor = (method_name == cls_name)
            is_dtor = (method_name.startswith('~') or method_name == '~%s' % cls_name)
            is_thiscall = '__thiscall' in cc
            # Also treat as thiscall if params contain '*this' (IDA sometimes omits __thiscall)
            if not is_thiscall and '*this' in params:
                is_thiscall = True
            is_static = not is_thiscall and not is_ctor and not is_dtor

            # Strip register annotations
            params = re.sub(r'@<\w+>', '', params)

            # Remove this pointer from params (always first param for __thiscall)
            if is_thiscall and params:
                param_list = split_params(params)
                if param_list:
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
                param_list = [_fix_param(p) for p in param_list]
                # Deduplicate parameter names (IDA sometimes gives same name to different params)
                seen_names = {}
                for idx, p in enumerate(param_list):
                    m = re.match(r'^(.+[\s\*])(\w+)$', p.strip())
                    if m:
                        pname = m.group(2)
                        if pname in seen_names:
                            param_list[idx] = '%s%s%d' % (m.group(1), pname, idx)
                        seen_names[pname] = idx
                params = ', '.join(param_list)

            # Skip invalid method names and calling conventions
            if '`' in method_name or ' ' in method_name or '?' in method_name:
                continue
            if 'vtbl_' in ret or 'vtbl_' in params or '__vftable' in sig:
                lines.append("    // [IDA_VTABLE] %s; // %s" % (method_name, addr))
                continue
            if '__userpurge' in sig or '__usercall' in sig:
                lines.append("    // [IDA_USERPURGE] %s; // %s" % (method_name, addr))
                continue
            if '@<' in sig:
                lines.append("    // [IDA_REGPARAM] %s; // %s" % (method_name, addr))
                continue

            # Function pointer parameters: VC6 doesn't support __thiscall in fp type decls.
            # Strip calling conventions from nested function pointer types and rename 'this'.
            if sig.count('(') > 2:
                params = re.sub(r'__thiscall\s*\*', '*', params)
                params = re.sub(r'__cdecl\s*\*', '*', params)
                params = re.sub(r'__stdcall\s*\*', '*', params)
                ret_right = re.sub(r'__thiscall\s*\*', '*', ret_right)
                ret_right = re.sub(r'__cdecl\s*\*', '*', ret_right)
                ret_right = re.sub(r'__stdcall\s*\*', '*', ret_right)
                def _fix_nested_this(m):
                    return m.group(0).replace(' this', ' _this').replace('*this', '*_this')
                params = re.sub(r'\([^)]*\bthis\b[^)]*\)', _fix_nested_this, params)

            # Strip calling conventions from function-pointer return type
            if ret_right:
                ret = re.sub(r'__thiscall\s*\*', '*', ret)
                ret = re.sub(r'__cdecl\s*\*', '*', ret)
                ret = re.sub(r'__stdcall\s*\*', '*', ret)

            # Build declaration
            if is_ctor:
                decl = "    %s(%s);" % (cls_name, params)
            elif is_dtor:
                decl = "    ~%s();" % cls_name
            elif ret_right:
                # Function-pointer return: "ret_left method(params) ret_right;"
                if is_static:
                    decl = "    static %s %s(%s)%s;" % (ret, method_name, params, ret_right)
                else:
                    decl = "    %s %s(%s)%s;" % (ret, method_name, params, ret_right)
            elif is_static:
                decl = "    static %s %s(%s);" % (ret, method_name, params)
            else:
                decl = "    %s %s(%s);" % (ret, method_name, params)

            # Virtual override: method inherited from base vtable but this class has its own impl.
            # Declare it normally (not as VTABLE_DUP) — the .cpp has the implementation.
            if method_name in vtable_method_names:
                pass  # fall through to normal declaration below

            # Detect duplicate declarations
            def _strip_param_names(p_str):
                parts = split_params(p_str)
                stripped = []
                for p in parts:
                    p = p.strip()
                    m2 = re.match(r'^(.+[\s\*])(\w+)$', p)
                    stripped.append(m2.group(1).strip() if m2 else p)
                return ', '.join(stripped)

            # Dtor with address suffix (e.g. ~UIWnd_ef50): compiler-generated sdtor thunk, skip
            if is_dtor and method_name != '~%s' % cls_name:
                continue

            if is_dtor:
                method_key = "~%s()" % cls_name
            elif is_ctor:
                method_key = "%s(%s)" % (cls_name, _strip_param_names(params))
            else:
                method_key = "%s(%s)" % (method_name, _strip_param_names(params))
            if method_key in seen_methods:
                _header_errors.append(
                    "DUPLICATE METHOD: %s::%s (addr=%s)" % (cls_name, method_key, addr))
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

    # IDB is the sole authoritative source for struct layout.
    # PDB data is already in IDB (imported by master_pipeline), annotation is the diff on top.
    # IDB export = PDB + annotation merged. Always use IDB data over raw PDB.
    ida_override_count = 0
    if IDA_STRUCTS_FILE.exists():
        ida_data = json.load(open(IDA_STRUCTS_FILE, encoding='utf-8'))
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

            # IDB always overrides PDB — IDB = PDB + annotation + gbengine merged
            pdb_classes[sname] = s
            ida_override_count += 1

        print("  IDA struct overrides: %d (IDB is authoritative)" % ida_override_count)

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
        has_ann_sz = bool(ann_s.get('binary_size') or ann_s.get('gen_size'))
        if has_members or has_methods or has_ann or has_ann_sz:
            classes_with_headers.add(cls_name)
    # Also include template stubs and enums
    for base_name in template_classes:
        if not should_skip_class(base_name):
            classes_with_headers.add(base_name)
    enum_names = set()
    enum_by_name = {}  # name -> {values: {name: val}}
    for e in pdb.get('enums', []):
        ename = e.get('name', '')
        if ename and (ename[0].isalpha() or ename[0] == '_') and '<' not in ename and '::' not in ename:
            classes_with_headers.add(ename)
            enum_names.add(ename)
            enum_by_name[ename] = e

    # Build case-insensitive enum lookup for collision detection
    enum_by_lower = {}
    for ename, edata in enum_by_name.items():
        enum_by_lower.setdefault(ename.lower(), []).append((ename, edata))

    embedded_enums = set()  # enum names already embedded in a class header

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
        has_ann_size = bool(ann_struct.get('binary_size') or ann_struct.get('gen_size'))
        if not has_members and not has_methods and not has_vtable and not has_ann_members and not has_ann_size:
            continue

        # Skip class generation if name conflicts with a PDB enum and class is just an enum wrapper
        # (size <= 4, no meaningful members beyond padding)
        if cls_name in enum_names:
            pdb_size = pdb_class.get('size', 0) if pdb_class else 0
            if pdb_size <= 4 and not has_ann_members:
                continue

        # Embed enums that would collide with this class header on disk:
        # - case-insensitive match (UIEMOTE vs UIEmote) — Windows FS collision
        # - exact same name but class has real content (ECBRoleSpecState)
        colliding_enums = []
        for ename, edata in enum_by_lower.get(cls_name.lower(), []):
            if ename == cls_name:
                # Same name: only embed if class has methods (otherwise let enum win)
                if has_methods:
                    colliding_enums.append((ename, edata))
                    embedded_enums.add(ename)
            else:
                # Case-insensitive collision: always embed
                colliding_enums.append((ename, edata))
                embedded_enums.add(ename)

        content = generate_header(cls_name, pdb_class, methods, classes_with_headers, enum_names,
                                  colliding_enums=colliding_enums)
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
        # Skip if already embedded in a class header during class generation
        if name in embedded_enums:
            enum_count += 1
            continue
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

    # Clean stale headers: remove .h files for classes now in SKIP_CLASSES
    stale_removed = 0
    for hf in OUTPUT_DIR.glob("*.h"):
        stem = hf.stem
        if should_skip_class(stem) and stem not in enum_names:
            hf.unlink()
            stale_removed += 1

    print("Generated %d header files in %s" % (generated, OUTPUT_DIR))
    print("  With PDB layout: %d" % sum(1 for c in all_classes
          if c in pdb_classes and pdb_classes[c].get('data_members') and pdb_classes[c].get('size', 0) > 1))
    print("  With methods: %d" % sum(1 for c in all_classes if c in methods_by_class and methods_by_class[c]))
    print("  Enums: %d" % enum_count)
    print("  Template stubs: %d" % tmpl_count)
    if stale_removed:
        print("  Cleaned %d stale headers" % stale_removed)

    # --- Generate globals.h from annotations ---
    generate_globals()


def generate_globals():
    """Generate include/pal3/globals.h from globals.json + binary initial values."""
    import struct as _st

    globals_json = ANNOTATIONS_DIR / "globals.json"
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
        has_struct = (ANNOTATIONS_DIR / "structs" / ("%s.json" % base_typ)).exists()

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

    if _header_errors:
        print("\n[ERROR] Header generation found %d annotation conflicts:" % len(_header_errors))
        for e in _header_errors:
            print("  %s" % e)
        print("\nFix these in data/annotations/functions.json, then re-run.")
        sys.exit(1)


def run_header_generation():
    main()

if __name__ == '__main__':
    main()
