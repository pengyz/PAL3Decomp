#!/usr/bin/env python3
"""
Generate .cpp implementation files from IDA decomp JSONs.

Groups functions by class, applies hexrays_to_oop post-processing,
and outputs organized .cpp files under src/pal3/.

Usage:
  python tools/gen_cpp.py
"""

import json
import os
import re
import sys
from collections import defaultdict
from pathlib import Path

PIPELINE_ROOT = Path(__file__).parent.parent
PROJECT_ROOT = PIPELINE_ROOT.parent
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
OUTPUT_DIR = PROJECT_ROOT / "src" / "pal3"
HEADER_DIR = PROJECT_ROOT / "include" / "pal3" / "gen"

# Game classes that have headers (from gen_headers.py output)
GAME_CLASSES = set()
for h in HEADER_DIR.glob("*.h"):
    GAME_CLASSES.add(h.stem)

# Globals already declared in globals.h (don't re-declare as extern int)
GLOBALS_H = PROJECT_ROOT / "include" / "pal3" / "globals.h"
_DECLARED_GLOBALS = set()
if GLOBALS_H.exists():
    import re as _re
    for _line in open(GLOBALS_H, encoding='utf-8', errors='replace'):
        _m = _re.search(r'extern\s+\S.*?\b(\w+)\s*(?:\[|;)', _line)
        if _m:
            _DECLARED_GLOBALS.add(_m.group(1))

# Thunk address → target name mapping (for call replacement)
THUNK_MAP = {}  # "sub_XXXXXX" → "TargetFunc"
_skip_file = PIPELINE_ROOT / "data" / "annotations" / "skip_functions.json"
if _skip_file.exists():
    _skip_data = json.load(open(_skip_file))
    for _addr, _info in _skip_data.items():
        if _info.get('reason') == 'thunk' and _info.get('target_name'):
            _hex = _addr[2:].lstrip('0').lower() or '0'
            # IDA 可能用 sub_XXXX 或 j_XXX 引用 thunk
            _target = _info['target_name']
            THUNK_MAP["sub_%s" % _hex] = _target
            THUNK_MAP[_info['name']] = _target
            # Also handle ~ → _ variant (gen_cpp replaces ~ with _)
            THUNK_MAP[_info['name'].replace('~', '_')] = _target.replace('~', '_')

# .rdata literal constants: flt_XXXX → inline value replacement
# Read float literals directly from binary (like thunk transparency)
import struct as _struct
LITERAL_MAP = {}  # "flt_XXXXXX" → "0.5f"
_exe_path = PROJECT_ROOT / "original" / "PAL3.exe"
if _exe_path.exists():
    _exe_data = open(_exe_path, 'rb').read()
    _rdata_start = 0x56A000
    _rdata_end = 0x571000
    for _off in range(_rdata_start - 0x400000, _rdata_end - 0x400000, 4):
        _va = _off + 0x400000
        _val = _struct.unpack_from('<f', _exe_data, _off)[0]
        if abs(_val) < 1e10 and (abs(_val) > 1e-10 or _val == 0.0):
            _hex = '%X' % _va
            _key = 'flt_%s' % _hex
            if _val == int(_val) and abs(_val) < 1000000:
                LITERAL_MAP[_key] = '%d.0f' % int(_val)
            else:
                LITERAL_MAP[_key] = '%.7gf' % _val
    # Also handle some well-known dword constants that are actually floats
    # loaded via integer registers
    del _exe_data


def replace_literals(code):
    """Replace .rdata float literal references with inline values."""
    if not LITERAL_MAP:
        return code
    def _repl(m):
        name = m.group(0)
        return LITERAL_MAP.get(name, name)
    return re.sub(r'\bflt_[0-9A-Fa-f]+\b', _repl, code)


# Globals name map: IDA default name (stru_5D5484) → proper name from globals.json
# Only exact address matches — sub-access replacement requires manual verification
GLOBALS_NAME_MAP = {}  # "stru_5D5484" → "g_EffMgr"
_globals_json = PIPELINE_ROOT / "data" / "annotations" / "globals.json"
if _globals_json.exists():
    _gdata = json.load(open(_globals_json, encoding='utf-8'))
    _ida_prefixes = ('dword', 'byte', 'word', 'stru', 'off', 'unk', 'flt')
    for _addr_str, _ginfo in _gdata.items():
        _gname = _ginfo.get('name', '')
        if not _gname:
            continue
        if any(_gname.startswith(p + '_') for p in _ida_prefixes):
            continue
        _addr_int = int(_addr_str, 16)
        _addr_hex = '%X' % _addr_int
        for _pfx in _ida_prefixes:
            GLOBALS_NAME_MAP['%s_%s' % (_pfx, _addr_hex)] = _gname


def replace_global_names(code):
    """Replace IDA default global names with annotated proper names (exact match only)."""
    if not GLOBALS_NAME_MAP:
        return code
    _pat = re.compile(r'\b((?:dword|byte|word|stru|off|unk|flt)_[0-9A-Fa-f]+)\b')
    def _repl(m):
        name = m.group(0)
        pfx, hexpart = name.split('_', 1)
        key = '%s_%s' % (pfx, hexpart.upper())
        return GLOBALS_NAME_MAP.get(key, name)
    return _pat.sub(_repl, code)


# Thunk class names to skip (these are just jump trampolines)
THUNK_CLASSES = set()
if _skip_file.exists():
    for _info in _skip_data.values():
        if _info.get('reason') == 'thunk':
            _n = _info.get('name', '')
            if '::' in _n:
                THUNK_CLASSES.add(_n.split('::')[0])
    # Also catch j_std from j_?method@class@std@@
    THUNK_CLASSES.add('j_std')
    THUNK_CLASSES.add('j_j_codecvt_base')

# Classes to skip entirely (CRT, STL, gbengine wrappers)
SKIP_CLASSES = {
    'std', 'stdiobuf', 'exception', 'type_info', 'filebuf',
    'Iostream_init', 'Concurrency',
    'gbGeomNode', 'gbLightObj', 'gbParticleEffect', 'gbRain', 'gbSnow', 'gbVisNode',
} | THUNK_CLASSES

# Organize classes into subdirectories by category
CLASS_DIRS = {
    # Combat system
    'CCBSystem': 'Combat', 'CCBRoleState': 'Combat', 'CCBStage': 'Combat',
    'CCBStageCam': 'Combat', 'CCBStageRole': 'Combat', 'CCBStageScene': 'Combat',
    'CCBStageEffect': 'Combat', 'CCBStageShadow': 'Combat',
    'CCBControl': 'Combat', 'CCBAttackSequen': 'Combat',
    'CCBAI': 'Combat', 'CCBUI': 'Combat', 'CCCTData': 'Combat',
    'CCBAIWindow': 'Combat', 'CCBControlWindow': 'Combat',
    'CCBItemWindow': 'Combat', 'CCBLineupWindow': 'Combat',
    'CCBMagicWindow': 'Combat', 'CCBSkillWindow': 'Combat',
    'CCBParabolaWindow': 'Combat', 'CCBProtectWindow': 'Combat',
    'CCBResultWindow': 'Combat', 'CCBCamControl': 'Combat',
    'Combat': 'Combat', 'CUtil': 'Combat',
    # Effects
    'CEffect': 'Effect', 'CEffMgr': 'Effect', 'CEffectSystem': 'Effect',
    'CEffCylinder': 'Effect', 'CEffExplosive': 'Effect', 'CEffGrid': 'Effect',
    'CEffMeteor': 'Effect', 'CEffModel': 'Effect', 'CEffQuad': 'Effect',
    'CEffQuake': 'Effect', 'CEffShock': 'Effect', 'CEffSParticle': 'Effect',
    'CEffgbParticle': 'Effect', 'CMeteorChain': 'Effect',
    'C2DSpark': 'Effect', 'C3DSpark': 'Effect',
    'ScreenEffect': 'Effect', 'ScreenEffectMgr': 'Effect',
    # UI
    'UIWnd': 'UI', 'UIScene': 'UI', 'UIManager': 'UI', 'UISystem': 'UI',
    'UIDialog': 'UI', 'UIBigDialog': 'UI', 'UISelectDialog': 'UI',
    'UIItem': 'UI', 'UIBase': 'UI', 'UICamera': 'UI', 'UICursor': 'UI',
    'UIListBox': 'UI', 'UILBColumn': 'UI', 'UILBItem': 'UI',
    'UINote': 'UI', 'UIQuadManager': 'UI', 'UIRenderObj': 'UI',
    'EquipUI': 'UI', 'MagicUI': 'UI', 'PropUI': 'UI', 'StateUI': 'UI',
    # Render
    'RenderTarget': 'Render', 'RenderTarget2': 'Render',
    'RenderTarget3': 'Render', 'RenderTarget4': 'Render',
    'CRenderTarget': 'Render', 'CRenderTarget2': 'Render',
    'CScreenMode': 'Render', 'TextureLib': 'Render',
    # Game core
    'PAL3': 'GameBase', 'GRPinput': 'GameBase', 'Config': 'GameBase',
    'Logger': 'GameBase', 'InputSystem': 'GameBase',
    'SoundSystem': 'GameBase', 'SoundContext': 'GameBase',
    # Script
    'PalScript': 'Script', 'PalScriptMgr': 'Script',
    'ScriptObj': 'Script', 'ScriptSystem': 'Script',
    # Scene/Role
    'Role': 'Role', 'RoleSystem': 'Role', 'NPC': 'Role',
    'Actor': 'Role', 'Object3D': 'Role', 'ObjectCamera': 'Role',
    'Scene': 'Scene', 'SceneMgr': 'Scene', 'SceneObj': 'Scene',
    'Camera': 'Scene', 'CameraCtrl': 'Scene', 'CameraSystem': 'Scene',
    # Data
    'CGameData': 'Data', 'PAL_GDB': 'Data',
    # Misc
    'MiniGame1': 'MiniGame', 'MiniGame3': 'MiniGame',
    'ParabolaCalculator': 'Misc', 'PtrArray': 'Misc', 'Array': 'Misc',
    'OpenBaseFile': 'Misc', 'OpenNULLFile': 'Misc', 'OpenSceneFile': 'Misc',
    'MvcController': 'Misc', 'MvcViewport': 'Misc',
}


def get_class_dir(cls_name):
    """Get subdirectory for a class."""
    return CLASS_DIRS.get(cls_name, 'Misc')


def collect_functions():
    """Collect all functions from decomp, grouped by class and free functions."""
    by_class = defaultdict(list)
    free_funcs = []

    for f in sorted(DECOMP_DIR.glob("*.json")):
        try:
            with open(f, 'r', encoding='utf-8') as fh:
                d = json.load(fh)
        except:
            continue

        name = d.get('name', '')
        code = d.get('decompiled_c', '')
        addr = d.get('address', '')
        sig = d.get('signature', '')

        if not code or not name:
            continue
        if name.startswith('sub_'):
            continue

        # Demangle MSVC names: ?Method@Class@@... -> Class::Method
        cls = None
        method = None
        if name.startswith('?'):
            inner = name[1:]
            if inner.startswith('?0') or inner.startswith('?1'):
                code_ch = inner[1]
                rest = inner[2:]
                at_pos = rest.find('@')
                if at_pos > 0:
                    cls = rest[:at_pos]
                    method = cls if code_ch == '0' else '~' + cls
            else:
                at_pos = inner.find('@')
                if at_pos > 0:
                    method = inner[:at_pos]
                    rest = inner[at_pos+1:]
                    at_pos2 = rest.find('@')
                    if at_pos2 > 0:
                        cls = rest[:at_pos2]
            if cls and ('$' in cls or '<' in cls or not (cls[0].isalpha() or cls[0] == '_')):
                cls = None
        elif '::' in name:
            cls = name.split('::')[0]
            method = name.split('::', 1)[1].split('(')[0]

        if cls and method:
            if cls in SKIP_CLASSES:
                continue
            by_class[cls].append({
                'name': '%s::%s' % (cls, method),
                'method': method,
                'code': code,
                'addr': addr,
                'sig': sig,
                '_source_file': str(f),
            })
        else:
            free_funcs.append({
                'name': name,
                'code': code,
                'addr': addr,
                'sig': sig,
            })

    return by_class, free_funcs



def transform_method_code(cls_name, method_name, code, sig):
    """Post-process Hex-Rays output into cleaner C++."""
    lines = code.split('\n')

    # 0. Filter IDA header comments (before function definition line)
    lines = [l for l in lines if not l.strip().startswith('// between_std_methods')]

    # Find the actual function definition line (may not be lines[0] if IDA comments precede it)
    # IDA may strip leading underscores from class names in decompiled output
    cls_variants = [cls_name]
    if cls_name.startswith('_'):
        cls_variants.append(cls_name[1:])
    func_line_idx = 0
    for idx, l in enumerate(lines):
        if '(' in l and (any(cv + '::' in l for cv in cls_variants) or 'sub_' in l):
            func_line_idx = idx
            break

    # Fix function definition line: replace sub_XXXXX or IDA-mangled class name with correct name
    if lines and method_name:
        first_line = lines[func_line_idx]
        full_method = '%s::%s' % (cls_name, method_name)
        first_line = re.sub(r'\bsub_[0-9A-Fa-f]+\b', full_method, first_line, count=1)
        # Fix IDA stripping leading underscore from class name
        for cv in cls_variants:
            if cv != cls_name and cv + '::' in first_line:
                first_line = first_line.replace(cv + '::', cls_name + '::')

        # If this is a constructor or destructor, remove the return type
        is_ctor = (method_name == cls_name)
        is_dtor = (method_name == '~%s' % cls_name)
        if is_ctor or is_dtor:
            first_line = re.sub(r'^.*?\b(%s::%s)' % (re.escape(cls_name), re.escape(method_name)),
                               r'\1', first_line)

        lines[func_line_idx] = first_line

    # 1b. For constructors/destructors, remove 'return expr;' (they can't return values)
    if method_name and (method_name == cls_name or method_name == '~%s' % cls_name):
        for i in range(len(lines)):
            # "return expr;" -> "expr;" (keep the expression as a statement)
            lines[i] = re.sub(r'^\s*return\s+(.+);', r'  \1;', lines[i])

    # 2. Transform function signature: remove ClassName *this param, fix return
    if lines:
        first = lines[func_line_idx]
        # Remove calling conventions from definition (not valid in VC6 function defs)
        first = re.sub(r'\s*__thiscall\s*', ' ', first)
        first = re.sub(r'\s*__cdecl\s*', ' ', first)
        first = re.sub(r'\s*__stdcall\s*', ' ', first)
        first = re.sub(r'\s*__fastcall\s*', ' ', first)
        first = re.sub(r'\s*__userpurge\s*', ' ', first)
        first = re.sub(r'\s*__usercall\s*', ' ', first)
        # Remove "ClassName *this" or any "*this" variant from params
        # Handles: Type *this, Type **this, _DWORD *this, etc.
        first = re.sub(r'\(\s*\w[\w\s]*\*+\s*this\s*,\s*', '(', first)
        first = re.sub(r'\(\s*\w[\w\s]*\*+\s*this\s*\)', '()', first)
        # Destructors cannot have parameters — strip all params
        if is_dtor:
            first = re.sub(r'\([^)]*\)', '()', first)
        # Clean double spaces
        first = re.sub(r'  +', ' ', first).strip()
        lines[func_line_idx] = first

    code = '\n'.join(lines)

    # 3. Convert Class::Method(this, ...) -> this->Method(...)
    #    and Class::Method(obj, ...) -> obj->Method(...)
    # Pattern: ClassName::MethodName(expr, ...)
    # Only for thiscall methods (where first arg is this or a pointer)
    # 3. AST-based OOP conversion: Class::Method(obj, ...) -> obj->Method(...)
    import sys, os
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from ast_transform import transform_oop_calls
    code = transform_oop_calls(code)

    # 4. Remove variable declarations for 'this' pointer
    code = re.sub(r'^\s*%s\s*\*\s*this\s*;.*$' % re.escape(cls_name), '', code, flags=re.MULTILINE)

    # 6c. Fix broken operator new: ((operator *)0xNNu)->new() -> operator new(0xNN)
    code = re.sub(r'\(\(operator \*\)(0x[0-9A-Fa-f]+u?)\)->new\(\)',
                  r'operator new(\1)', code)

    # 6d. Remove __thiscall from function pointer casts (VC6 doesn't support explicit __thiscall)
    code = re.sub(r'__thiscall\s+', '', code)
    code = re.sub(r'__userpurge\s+', '', code)
    code = re.sub(r'__usercall\s+', '', code)

    # Final: replace thunk references (after OOP transform may have created j_Class casts)
    code = replace_thunks(code)
    code = replace_literals(code)
    code = replace_global_names(code)

    # Replace IDA vtable struct types with void (not real C++ types)
    code = re.sub(r'\bvtbl_[0-9A-Fa-f]+\b', 'void', code)

    # Fix IDA exception type name: _ThrowInfo → _s__ThrowInfo (MSVC6 CRT)
    code = code.replace('(_ThrowInfo *)', '(_s__ThrowInfo *)')

    # VC6 compatibility: LL suffix → i64, uLL → ui64
    code = re.sub(r'(\b0x[0-9A-Fa-f]+)uLL\b', r'\1ui64', code)
    code = re.sub(r'(\b0x[0-9A-Fa-f]+)LL\b', r'\1i64', code)
    code = re.sub(r'(\b\d+)LL\b', r'\1i64', code)

    # Fix Hex-Rays broken dereference: (*)var → (*var)
    code = re.sub(r'\(\*\)(\w+)', r'(*\1)', code)

    # Replace ctor return pattern: "return &this->__vftable;" → "return this;"
    code = re.sub(r'return\s+&this->__vftable\s*;', 'return this;', code)
    # Also: "return (Type *)&this->__vftable;" → "return this;"
    code = re.sub(r'return\s+\([^)]+\)\s*&this->__vftable\s*;', 'return this;', code)

    # VC6: explicit constructor calls via ->ClassName() are illegal in C++.
    # IDA emits these for placement-like ctor calls. Comment them out.
    # Pattern: ((Type *)expr)->ClassName()  where ClassName is a known class
    code = _comment_out_explicit_ctor_calls(code)

    # VC6: LODWORD(x) = &symbol  -- assigning pointer to unsigned long
    # Add (unsigned long) cast for LODWORD/HIDWORD assignments from address-of expressions
    code = re.sub(
        r'((?:LODWORD|HIDWORD)\s*\([^)]+\))\s*=\s*(&\w+)',
        r'\1 = (unsigned long)\2',
        code
    )

    # VC6: (int)Class::Method -- casting member function pointer to int is illegal
    # Use union-based cast helper to extract function address as int
    def _fix_mfp_cast(m):
        cls_method = m.group(1)
        # Extract hex address from method name if available (e.g., Method_4DF2F0 → 0x4DF2F0)
        addr_m = re.search(r'_([0-9A-Fa-f]{5,})$', cls_method.split('::')[-1])
        if addr_m:
            return '0x%s' % addr_m.group(1)
        # Fallback: use 0 as placeholder
        return '0 /* TODO: (int)%s */' % cls_method
    code = re.sub(
        r'\(int\)\s*(\w+::(?:~?\w+))\b(?!\s*\()',
        _fix_mfp_cast,
        code
    )

    # Remove compiler-internal calls and vtable init
    code = _replace_ida_internals(code)

    return code


def _comment_out_explicit_ctor_calls(code):
    """Comment out illegal explicit constructor calls: ((Type*)expr)->ClassName().

    In C++, you cannot explicitly call a constructor via ->. IDA Hex-Rays
    emits these for placement-like initialization. We comment them out since
    the compiler generates these automatically.
    """
    # Match patterns like:
    #   ((ClassName *)expr)->ClassName();
    #   ((ClassName *)expr)->ClassName(args);
    # where ClassName matches a known header file (indicating a real class)
    def _repl(m):
        indent = m.group(1)
        full = m.group(0)
        return indent + '// [AUTO-COMMENTED] ' + full.strip()

    # Build pattern: ->ClassName( where ClassName is in GAME_CLASSES
    # We do line-by-line to handle this properly
    lines = code.split('\n')
    out = []
    for line in lines:
        stripped = line.strip()
        # Check for ->ClassName() or ->ClassName(args) where ClassName is a known class
        m = re.search(r'->\s*([A-Z_]\w+)\s*\(', stripped)
        if m:
            called_name = m.group(1)
            # Only comment out if it's a constructor call (name matches a class)
            # and the line is a standalone statement (not part of assignment or condition)
            if called_name in GAME_CLASSES:
                # Check it's a statement, not part of a larger expression
                # Heuristic: line ends with ; and doesn't have = or return before the call
                if stripped.endswith(';') and '=' not in stripped and not stripped.startswith('return') \
                        and not stripped.startswith('if') and not stripped.startswith('while'):
                    indent = line[:len(line) - len(line.lstrip())]
                    out.append(indent + '// [AUTO-COMMENTED] ' + stripped)
                    continue
        out.append(line)
    return '\n'.join(out)


def _replace_ida_internals(code):
    """Remove IDA backtick-quoted compiler-internal calls (compiler auto-generates these)."""
    _BACKTICK_PATTERNS = (
        "`eh vector constructor iterator'",
        "`eh vector destructor iterator'",
        "`default constructor closure'",
        "`scalar deleting destructor'",
        "`vftable'",
    )
    lines = code.split('\n')
    out = []
    skip_until_semicolon = False
    for line in lines:
        s = line.strip()
        if skip_until_semicolon:
            if ';' in s:
                skip_until_semicolon = False
            continue
        if any(p in s for p in _BACKTICK_PATTERNS):
            if ';' not in s:
                skip_until_semicolon = True
            continue
        # Delete vtable pointer init (compiler-generated in ctor/dtor)
        if re.match(r'\s*\w.*->__vftable\s*=\s*', s) or re.match(r'\s*this->__vftable\s*=', s):
            continue
        if re.match(r'\s*this\[\d+\]\.__vftable\s*=\s*', s):
            continue
        if re.match(r'\s*LOBYTE\s*\(\s*\w.*->__vftable\s*\)\s*=', s) or \
           re.match(r'\s*LOBYTE\s*\(\s*this->__vftable\s*\)\s*=', s):
            continue
        # Comment out __vftable-based virtual calls (IDA artifact, not valid C++)
        # Pattern: ((cast)obj->__vftable->Method)(args);  or  ((cast)obj->__vftable)(args);
        if ('->__vftable->' in s or '->__vftable)' in s) and s.endswith(';') \
                and not s.startswith('//'):
            indent = line[:len(line) - len(line.lstrip())]
            out.append(indent + '// [IDA_VFTABLE] ' + s)
            continue
        # Delete compiler-generated ctor/dtor calls:
        #   ((Type *)expr)->Type(args);  or  ((Type *)expr)->~Type();
        # Key: method name must match the cast type name (ctor = ClassName())
        _ctor_m = re.match(r'\s*\(\((\w+)\s*\*\)\s*[^)]*\)\s*->\s*~?(\w+)\s*\([^)]*\)\s*;', s)
        if _ctor_m and _ctor_m.group(1) == _ctor_m.group(2):
            continue
        # Double-cast variant: ((Type *)(Type *)expr)->Type(args);
        _ctor_m2 = re.match(r'\s*\(\((\w+)\s*\*\)\s*\(\w+\s*\*\)\s*[^)]*\)\s*->\s*~?(\w+)\s*\([^)]*\)\s*;', s)
        if _ctor_m2 and _ctor_m2.group(1) == _ctor_m2.group(2):
            continue
        out.append(line)
    return '\n'.join(out)


def split_params_simple(s):
    """Split by comma respecting parens."""
    result = []
    depth = 0
    current = ''
    for ch in s:
        if ch == ',' and depth == 0:
            result.append(current)
            current = ''
        else:
            if ch in '(':
                depth += 1
            elif ch in ')':
                depth -= 1
            current += ch
    if current.strip():
        result.append(current)
    return result


def replace_thunks(code):
    """Replace thunk calls and type casts with direct target equivalents."""
    for thunk_name, target_name in THUNK_MAP.items():
        if thunk_name in code:
            code = code.replace(thunk_name, target_name)
    # Also replace thunk class type casts: (j_ClassName *) → (ClassName *)
    for cls in THUNK_CLASSES:
        if cls in code:
            real_cls = cls[2:] if cls.startswith('j_') else cls  # j_UIWnd → UIWnd
            code = code.replace(cls + ' *', real_cls + ' *')
            code = code.replace(cls + ' **', real_cls + ' **')
    return code


def collect_sub_refs(code):
    """Find all sub_XXXXX and named function references needing forward declaration."""
    refs = set(re.findall(r'\b(sub_[0-9A-Fa-f]+)\b', code))
    # Also find named functions called as standalone (not Class::Method)
    # Pattern: identifier( where it's not preceded by . or -> or ::
    # Broadened to catch any PascalCase or underscore-prefixed game function call
    for m in re.finditer(r'(?<![.>:])\b([A-Z][a-zA-Z0-9_]*(?:Update|Init|Create|Destroy|Render|Sort|Check|Process|SetState|GetState|Reset|Load|Save|Release|Free|Manager|Info))\s*\(', code):
        refs.add(m.group(1))
    # Also catch specific patterns: UIObj_XXX, GetXxxManager_N, Texture_Info_XXXX
    for m in re.finditer(r'(?<![.>:])(?<!\w)\b((?:UIObj_\w+|Get\w+Manager(?:_\d+)?|Texture_Info_\w+|GetGfxManager_\d+))\s*\(', code):
        refs.add(m.group(1))
    return refs


def collect_undefined_refs(code):
    """Find likely undefined identifiers that need extern/forward decl."""
    refs = set()
    # IDA string constants: aXxxxx
    refs.update(re.findall(r'\b(a[A-Z]\w{3,})\b', code))
    # IDA unnamed globals: dword_XXX, byte_XXX, etc (only as identifiers, not types)
    refs.update(re.findall(r'\b(dword_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(byte_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(word_[0-9A-Fa-f]+)\b', code))
    refs.update(r for r in re.findall(r'\b(flt_[0-9A-Fa-f]+)\b', code) if r not in LITERAL_MAP)
    refs.update(re.findall(r'\b(off_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(unk_[0-9A-Fa-f]+)\b', code))
    refs.update(re.findall(r'\b(stru_[0-9A-Fa-f]+)\b', code))
    # IDA named but unresolved: nullsub_N, unknown_libname_N
    refs.update(re.findall(r'\b(nullsub_\d+)\b', code))
    refs.update(re.findall(r'\b(unknown_libname_\d+)\b', code))
    refs.update(re.findall(r'\b(nullsub_\d+)\b', code))
    refs.update(re.findall(r'\b(unknown_libname_\d+)\b', code))
    return refs


def generate_forward_decls(all_code):
    """Generate minimal forward declarations: only what this file actually references."""
    lines = []
    subs = collect_sub_refs(all_code)
    if subs:
        lines.append("// Forward declarations for unnamed functions")
        for s in sorted(subs):
            lines.append("int %s(...);" % s)
        lines.append("")

    undef = collect_undefined_refs(all_code)
    undef -= _DECLARED_GLOBALS
    # Detect off_ variables used as arrays (subscripted or address-taken with subscript)
    off_as_array = set()
    for u in undef:
        if u.startswith('off_'):
            # Check if used as: off_XXX[, (&off_XXX)[, or compared with (int) cast
            if re.search(r'\b' + re.escape(u) + r'\s*\[', all_code) or \
               re.search(r'&' + re.escape(u) + r'\s*\)\s*\[', all_code) or \
               re.search(r'&' + re.escape(u) + r'\s*\)\s*[<>]', all_code):
                off_as_array.add(u)
    if undef:
        lines.append("// Unnamed globals (extern)")
        for u in sorted(undef):
            if u.startswith('flt_'):
                lines.append("extern float %s;" % u)
            elif u.startswith('byte_'):
                lines.append("extern unsigned char %s;" % u)
            elif u.startswith('off_') and u in off_as_array:
                lines.append("extern void *%s[];" % u)
            elif u.startswith('off_'):
                lines.append("extern void *%s;" % u)
            elif u.startswith('a') and len(u) > 1 and u[1].isupper():
                lines.append('extern char %s[];' % u)
            else:
                lines.append("extern int %s;" % u)
        lines.append("")

    return '\n'.join(lines)


def generate_class_cpp(cls_name, methods):
    """Generate .cpp content for a class."""
    lines = []

    # Standard includes
    lines.append('#include "pal3/ida_defs.h"')
    lines.append('#include "pal3/globals.h"')
    header_path = HEADER_DIR / ("%s.h" % cls_name)
    if header_path.exists():
        lines.append('#include "pal3/gen/%s.h"' % cls_name)

    # Auto-detect additional includes needed from code content
    all_code_preview = '\n'.join(m['code'] for m in methods)
    needed_classes = set()
    # ClassName:: static calls
    for match in re.finditer(r'\b([A-Z]\w+)::', all_code_preview):
        c = match.group(1)
        if c != cls_name and (HEADER_DIR / ("%s.h" % c)).exists():
            needed_classes.add(c)
    # (ClassName *) casts — accessing members requires full definition
    for match in re.finditer(r'\((\w+)\s*\*+\s*\)', all_code_preview):
        c = match.group(1)
        if c != cls_name and (HEADER_DIR / ("%s.h" % c)).exists():
            needed_classes.add(c)
    # Any word that matches a known header file name in the code
    known_headers = {f.stem for f in HEADER_DIR.glob("*.h")}
    for match in re.finditer(r'\b([A-Za-z_]\w+)\b', all_code_preview):
        c = match.group(1)
        if c != cls_name and c in known_headers and c not in needed_classes:
            needed_classes.add(c)
    # Resolve indirect dependencies: if code dereferences a forward-declared
    # pointer member (ptr->field), include that type's header too.
    indirect = set()
    all_included = needed_classes | {cls_name}
    for inc_cls in list(all_included):
        hpath = HEADER_DIR / ("%s.h" % inc_cls)
        if not hpath.exists():
            continue
        with open(hpath, 'r', encoding='utf-8', errors='replace') as hf:
            for hline in hf:
                m = re.match(r'\s+(\w+)\s*\*\s*(\w+)\s*;', hline)
                if m:
                    ptr_type, ptr_name = m.group(1), m.group(2)
                    if ptr_type in known_headers and ptr_type not in all_included:
                        if re.search(r'\b' + re.escape(ptr_name) + r'\s*->', all_code_preview):
                            indirect.add(ptr_type)
    needed_classes |= indirect

    for c in sorted(needed_classes):
        if c.startswith('vtbl_'):
            continue
        lines.append('#include "pal3/gen/%s.h"' % c)

    lines.append("")

    # Sort methods by address
    methods.sort(key=lambda m: m['addr'])

    # Transform all method code first
    transformed = []
    for m in methods:
        code = transform_method_code(cls_name, m['method'], m['code'].strip(), m['sig'])
        transformed.append((m['addr'], code))

    # Generate forward declarations based on all code in this file
    all_code = '\n'.join(code for _, code in transformed)
    fwd = generate_forward_decls(all_code)
    if fwd:
        lines.append(fwd)

    # Emit transformed code
    for addr, code in transformed:
        lines.append("// %s" % addr)
        lines.append(code)
        lines.append("")

    return '\n'.join(lines)


def generate_free_funcs_cpp(funcs):
    """Generate .cpp for free functions."""
    lines = []
    lines.append('#include "pal3/ida_defs.h"')
    lines.append('#include "pal3/globals.h"')
    lines.append("")
    lines.append("// Free functions (not belonging to any class)")
    lines.append("")

    funcs.sort(key=lambda f: f['addr'])

    # Transform all
    transformed = []
    for f in funcs:
        code = f['code'].strip()
        code = replace_thunks(code)
        code = replace_literals(code)
        code = replace_global_names(code)

        # In free functions, 'this' is not a valid parameter name in C++
        # Rename to '_this' to avoid syntax errors
        code = re.sub(r'\bthis\b', '_this', code)
        # Fix stdiobuf/ios_base
        code = code.replace('stdiobuf *', 'UIWnd *')
        code = code.replace('stdiobuf::', 'UIWnd::')
        code = code.replace('std::ios_base *', 'UIWnd *')
        # Replace IDA vtable struct types
        code = re.sub(r'\bvtbl_[0-9A-Fa-f]+\b', 'void', code)
        # VC6 compatibility
        code = re.sub(r'(\b0x[0-9A-Fa-f]+)uLL\b', r'\1ui64', code)
        code = re.sub(r'(\b0x[0-9A-Fa-f]+)LL\b', r'\1i64', code)
        code = re.sub(r'(\b\d+)LL\b', r'\1i64', code)
        code = re.sub(r'\(\*\)(\w+)', r'(*\1)', code)
        code = _replace_ida_internals(code)
        transformed.append((f['addr'], code))

    # Forward declarations
    all_code = '\n'.join(code for _, code in transformed)
    fwd = generate_forward_decls(all_code)
    if fwd:
        lines.append(fwd)

    for addr, code in transformed:
        lines.append("// %s" % addr)
        lines.append(code)
        lines.append("")

    return '\n'.join(lines)


def main():
    import sys

    # Parse arguments
    force_all = '--force-all' in sys.argv
    force_files = set()
    for arg in sys.argv[1:]:
        if arg.startswith('--force'):
            if '=' in arg:
                force_files.add(arg.split('=', 1)[1])
            elif arg == '--force-all':
                pass
            else:
                # Next arg is the filename
                idx = sys.argv.index(arg)
                if idx + 1 < len(sys.argv):
                    force_files.add(sys.argv[idx + 1])
        elif not arg.startswith('-'):
            force_files.add(arg)

    print("Collecting functions from decomp...")
    by_class, free_funcs = collect_functions()

    print("  Classes with methods: %d" % len(by_class))
    print("  Free functions: %d" % len(free_funcs))

    # Generate .cpp files
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    generated = 0
    skipped = 0
    total_funcs = 0

    for cls_name, methods in sorted(by_class.items()):
        subdir = get_class_dir(cls_name)
        out_dir = OUTPUT_DIR / subdir
        out_dir.mkdir(parents=True, exist_ok=True)

        out_path = out_dir / ("%s.cpp" % cls_name)

        # Skip if output is newer than all source decomp files
        if out_path.exists() and not force_all and cls_name not in force_files:
            out_mtime = out_path.stat().st_mtime
            source_newer = any(
                os.path.getmtime(m['_source_file']) > out_mtime
                for m in methods if '_source_file' in m
            )
            if not source_newer:
                skipped += 1
                total_funcs += len(methods)
                continue

        content = generate_class_cpp(cls_name, methods)
        try:
            with open(out_path, 'w', encoding='utf-8') as f:
                f.write(content)
            generated += 1
        except PermissionError:
            print("  [SKIP] %s (file locked)" % out_path.name)
            skipped += 1
        total_funcs += len(methods)

    # Free functions
    if free_funcs:
        out_path = OUTPUT_DIR / "free_functions.cpp"
        if not out_path.exists() or force_all or 'free_functions' in force_files:
            content = generate_free_funcs_cpp(free_funcs)
            with open(out_path, 'w', encoding='utf-8') as f:
                f.write(content)
            generated += 1
        else:
            skipped += 1
        total_funcs += len(free_funcs)

    print("\nGenerated %d .cpp files (%d skipped, %d functions) in %s" % (
        generated, skipped, total_funcs, OUTPUT_DIR))
    if skipped > 0:
        print("  (use --force-all to overwrite, or pass class names to update specific files)")

    # Summary by directory
    for subdir in sorted(set(CLASS_DIRS.values()) | {'Misc'}):
        d = OUTPUT_DIR / subdir
        if d.exists():
            count = len(list(d.glob("*.cpp")))
            if count > 0:
                print("  %s/: %d files" % (subdir, count))


if __name__ == '__main__':
    main()
