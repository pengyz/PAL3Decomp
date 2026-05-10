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

PROJECT_ROOT = Path(__file__).parent.parent
DECOMP_DIR = PROJECT_ROOT / "asm" / "pal3" / "decomp"
OUTPUT_DIR = PROJECT_ROOT / "src" / "pal3"
HEADER_DIR = PROJECT_ROOT / "include" / "pal3" / "gen"

# Game classes that have headers (from gen_headers.py output)
GAME_CLASSES = set()
for h in HEADER_DIR.glob("*.h"):
    GAME_CLASSES.add(h.stem)

# Classes to skip entirely (CRT, STL, gbengine wrappers)
SKIP_CLASSES = {
    'std', 'stdiobuf', 'exception', 'type_info', 'filebuf',
    'Iostream_init', 'Concurrency',
    'gbGeomNode', 'gbLightObj', 'gbParticleEffect', 'gbRain', 'gbSnow', 'gbVisNode',
}

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
        if f.name.startswith("_"):
            continue
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

        if '::' in name:
            cls = name.split('::')[0]
            if cls in SKIP_CLASSES:
                continue
            by_class[cls].append({
                'name': name,
                'method': name.split('::', 1)[1].split('(')[0],
                'code': code,
                'addr': addr,
                'sig': sig,
            })
        else:
            free_funcs.append({
                'name': name,
                'code': code,
                'addr': addr,
                'sig': sig,
            })

    return by_class, free_funcs


# MEMORY[addr] -> global variable name mapping
MEMORY_MAP = {
    0x00BFDA60: 'g_pGfxManager',
    0x00BFDA64: 'g_pActorMgr',
    0x00BFDA68: 'g_pCamera',
    0x00BFDA6C: 'g_nGameState',
    0x00BFDA70: 'g_pSceneMgr',
    0x00BFDA74: 'g_pCBSystem',
    0x00BFDA78: 'g_pGameData',
    0x00BFDA7C: 'g_pScreenMode',
    0x00BFDA80: 'g_pInput',
    0x00BFDA84: 'g_pRoleSystem',
    0x00BFDA8C: 'g_pUIManager',
    0x00BFDA90: 'g_pEffMgr',
    0x00BFDA94: 'g_pLogger',
    0x00BFDA98: 'g_pPalScript',
    0x00BFDA9C: 'g_pConfig',
    0x00BFDAA0: 'g_pTextureLib',
}


def replace_memory_refs(code):
    """Replace MEMORY[0xADDR] with named globals."""
    def mem_replace(match):
        addr = int(match.group(1), 16)
        if addr in MEMORY_MAP:
            return MEMORY_MAP[addr]
        return match.group(0)
    return re.sub(r'MEMORY\[0x([0-9A-Fa-f]+)\]', mem_replace, code)


def transform_method_code(cls_name, method_name, code, sig):
    """Post-process Hex-Rays output into cleaner C++."""
    lines = code.split('\n')

    # 0. Filter IDA header comments (before function definition line)
    lines = [l for l in lines if not l.strip().startswith('// between_std_methods')]

    # Find the actual function definition line (may not be lines[0] if IDA comments precede it)
    func_line_idx = 0
    for idx, l in enumerate(lines):
        if '(' in l and (cls_name + '::' in l or 'sub_' in l):
            func_line_idx = idx
            break

    # Fix function definition line: replace sub_XXXXX with ClassName::MethodName
    if lines and method_name:
        first_line = lines[func_line_idx]
        full_method = '%s::%s' % (cls_name, method_name)
        first_line = re.sub(r'\bsub_[0-9A-Fa-f]+\b', full_method, first_line, count=1)

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

    # 5. Replace MEMORY[0xADDR] with named globals
    code = replace_memory_refs(code)

    # 6b. Fix IDA type misidentification: stdiobuf/ios_base -> UIWnd in game code
    code = code.replace('stdiobuf *', 'UIWnd *')
    code = code.replace('stdiobuf::', 'UIWnd::')
    code = code.replace('(stdiobuf *)', '(UIWnd *)')
    code = code.replace('std::ios_base *', 'UIWnd *')
    code = code.replace('(std::ios_base *)', '(UIWnd *)')

    # 6d. Remove __thiscall from function pointer casts (VC6 doesn't support explicit __thiscall)
    code = re.sub(r'__thiscall\s+', '', code)
    code = re.sub(r'__userpurge\s+', '', code)
    code = re.sub(r'__usercall\s+', '', code)

    # 6. Fix *(this + N) -> *((_DWORD *)this + N) for pointer arithmetic on typed this
    code = re.sub(r'\*\(\s*this\s*\+\s*(\d+)\s*\)', r'*((_DWORD *)this + \1)', code)
    code = re.sub(r'\*\(\s*this\s*-\s*(\d+)\s*\)', r'*((_DWORD *)this - \1)', code)

    # 6c. If 'this' appears as a non-pointer parameter (e.g. "int this"), rename to _this
    # This handles cases where IDA named a parameter 'this' but it's not a real C++ this
    code = re.sub(r'\bint\s+this\b', 'int _this', code)
    code = re.sub(r'\bchar\s+this\b', 'char _this', code)
    code = re.sub(r'\b_DWORD\s+this\b', '_DWORD _this', code)
    # Also: &this[N] -> &((_DWORD *)this)[N]  and  this[N] -> ((_DWORD *)this)[N]
    # But be careful not to break this->member access

    # 7. Fix void* implicit conversion
    # VC6 also doesn't allow void* -> typed pointer without cast
    # Pattern 1: "Type *var = expr;" where var is assigned from a void* expression
    # Pattern 2: "var = expr;" where var is already declared as typed pointer
    # We add cast for common patterns
    # Simple approach: any assignment to a _DWORD*, _BYTE* etc from a function call gets a cast
    def fix_ptr_assign(line):
        # Match: "  TypePtr *varname = funcall(...);"
        m = re.match(r'(\s*)([\w ]+\*)\s*(\w+)\s*=\s*(.+);', line)
        if m:
            indent, ptype, var, expr = m.group(1), m.group(2), m.group(3), m.group(4)
            # Don't cast if already has a cast, or if RHS is just a variable/number
            if expr.startswith('(') and ')' in expr.split('(')[1]:
                return line  # already has cast
            if re.match(r'^[\w.>\-]+$', expr):
                return line  # simple variable, might be same type
            if re.match(r'^\d+$', expr) or expr in ('0', 'NULL', 'nullptr'):
                return line
            # Add cast
            return '%s%s %s = (%s)%s;' % (indent, ptype, var, ptype.strip(), expr)
        return line

    # Also handle standalone assignments: "var = expr;" where var was declared as Type*
    # Simple tracking: find all "Type *var;" declarations, then cast assignments to those vars
    ptr_vars = {}  # var_name -> type string
    for m in re.finditer(r'^\s*([\w ]+\*)\s*(\w+)\s*;', code, re.MULTILINE):
        ptr_vars[m.group(2)] = m.group(1).strip()

    new_lines = []
    for line in code.split('\n'):
        line = fix_ptr_assign(line)
        # Check standalone assignment: "  var = expr;"
        m2 = re.match(r'(\s*)(\w+)\s*=\s*(.+);', line)
        if m2 and m2.group(2) in ptr_vars:
            var = m2.group(2)
            expr = m2.group(3)
            ptype = ptr_vars[var]
            # Don't cast if already cast or simple var or 0/NULL
            if not (expr.startswith('(') or re.match(r'^[\d\w]+$', expr) or expr in ('0','NULL')):
                line = '%s%s = (%s)%s;' % (m2.group(1), var, ptype, expr)
        new_lines.append(line)
    code = '\n'.join(new_lines)

    return code


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


def collect_sub_refs(code):
    """Find all sub_XXXXX and named function references needing forward declaration."""
    refs = set(re.findall(r'\b(sub_[0-9A-Fa-f]+)\b', code))
    # Also find named functions called as standalone (not Class::Method)
    # Pattern: identifier( where it's not preceded by . or -> or ::
    for m in re.finditer(r'(?<![.>:])\b([A-Z][a-zA-Z]+(?:Update|Init|Create|Destroy|Render|Sort|Check|Process))\s*\(', code):
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
    refs.update(re.findall(r'\b(flt_[0-9A-Fa-f]+)\b', code))
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
    """Generate forward declarations for sub_ and unnamed globals."""
    lines = []
    subs = collect_sub_refs(all_code)
    if subs:
        lines.append("// Forward declarations for unnamed functions")
        for s in sorted(subs):
            lines.append("int %s(...);" % s)
        lines.append("")

    undef = collect_undefined_refs(all_code)
    if undef:
        lines.append("// Unnamed globals (extern)")
        for u in sorted(undef):
            if u.startswith('flt_'):
                lines.append("extern float %s;" % u)
            elif u.startswith('byte_'):
                lines.append("extern unsigned char %s;" % u)
            elif u.startswith('off_'):
                lines.append("extern void *%s;" % u)
            elif u.startswith('a') and u[1].isupper():
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
    # Look for ClassName:: or ClassName * patterns that need the class definition
    all_code_preview = '\n'.join(m['code'] for m in methods)
    needed_classes = set()
    for match in re.finditer(r'\b([A-Z]\w+)::', all_code_preview):
        c = match.group(1)
        if c != cls_name and (HEADER_DIR / ("%s.h" % c)).exists():
            needed_classes.add(c)
    # Also detect "this->m_pXXX->" patterns where m_pXXX is a typed pointer member
    for match in re.finditer(r'->(\w+)\(', all_code_preview):
        pass  # method calls already handled by Class:: detection
    for c in sorted(needed_classes):
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
        code = replace_memory_refs(code)
        # In free functions, 'this' is not a valid parameter name in C++
        # Rename to '_this' to avoid syntax errors
        code = re.sub(r'\bthis\b', '_this', code)
        # Fix stdiobuf/ios_base
        code = code.replace('stdiobuf *', 'UIWnd *')
        code = code.replace('stdiobuf::', 'UIWnd::')
        code = code.replace('std::ios_base *', 'UIWnd *')
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

        # Skip if file exists and not forced
        if out_path.exists() and not force_all and cls_name not in force_files:
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
