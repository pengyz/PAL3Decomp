#!/usr/bin/env python3
"""
Generate C++ stub source files for unresolved gbengine.dll symbols.
Parses MSVC demangled signatures from unresolved.txt, groups by class,
generates minimal stub implementations with correct signatures.
"""
import re
import os
import sys
from collections import defaultdict

UNRESOLVED_FILE = "unresolved.txt"
OUTPUT_DIR = "src/gbengine/stubs"

LINE_RE = re.compile(r'^"(.+)"\s+\(([^)]+)\)$')


def parse_unresolved_line(demangled):
    """Parse a demangled MSVC signature into structured components.
    Returns: (class_name, code_line, kind) or None if vftable/unparseable.
    """
    # vftable: "const ClassName::`vftable'"
    m = re.match(r"^const (\w+)::`vftable'$", demangled)
    if m:
        return (m.group(1), None, 'vftable')

    # Static data: "private: static unsigned long * CPK::CrcTable"
    m = re.match(r'^(public|private|protected):\s+static\s+(.+?)\s+(\w+)::(\w+)$', demangled)
    if m:
        access, dtype, cls, member = m.groups()
        dtype = clean_type(dtype)
        return (cls, f'{dtype} {cls}::{member};', 'static_data')

    # Free function: "RetType __cdecl FuncName(params)"
    m = re.match(r'^(.+?)\s+__cdecl\s+(\w+)\((.+)\)$', demangled)
    if m:
        ret, name, params = m.groups()
        ret = clean_type(ret)
        params_decl = make_params(params)
        ret_stmt = default_return(ret)
        body = f' {ret_stmt} ' if ret_stmt else ' '
        return ('__globals__', f'{ret} {name}({params_decl}) {{{body}}}', 'free_fn')

    # Static member function: "access: static RetType __cdecl Class::Method(params)"
    m = re.match(
        r'^(public|private|protected):\s+static\s+(.+?)\s+__cdecl\s+(\w+)::(\w+)\((.+)\)$',
        demangled
    )
    if m:
        access, ret, cls, func, params_raw = m.groups()
        ret = clean_type(ret)
        params_decl = make_params(params_raw)
        ret_stmt = default_return(ret)
        body = f' {ret_stmt} ' if ret_stmt else ' '
        return (cls, f'{ret} {cls}::{func}({params_decl}) {{{body}}}', 'static_method')

    # Member function patterns
    # "access: [virtual] [RetType] __thiscall Class::Method(params)[const]"
    m = re.match(
        r'^(public|private|protected):\s+'
        r'(.*?)'
        r'__thiscall\s+'
        r'(\w+)::(.*)',
        demangled
    )
    if m:
        access, prefix, cls, rest = m.groups()
        return parse_member(cls, prefix.strip(), rest.strip())

    return ('__unparsed__', f'// UNPARSED: {demangled}', 'unknown')


def parse_member(cls, prefix, rest):
    """Parse member function details.
    prefix: everything between access and __thiscall (e.g., "virtual void ", "int ")
    rest: everything after Class:: (e.g., "SetFov(float)", "~gbCamera(void)")
    """
    # Extract const suffix
    is_const = False
    if rest.endswith('const ') or rest.endswith('const'):
        is_const = True
        rest = rest.rstrip()
        if rest.endswith('const'):
            rest = rest[:-5].rstrip()

    # Extract params
    paren_idx = rest.rfind('(')
    if paren_idx == -1:
        return (cls, f'// UNPARSED MEMBER: {cls}::{rest}', 'unknown')

    func_part = rest[:paren_idx].strip()
    params_raw = rest[paren_idx + 1:]
    if params_raw.endswith(')'):
        params_raw = params_raw[:-1]

    # Determine function type
    is_virtual = 'virtual' in prefix
    prefix_clean = prefix.replace('virtual', '').strip()

    # Constructor
    if func_part == cls:
        params_decl = make_params(params_raw)
        return (cls, f'{cls}::{cls}({params_decl}) {{}}', 'ctor')

    # Destructor
    if func_part == f'~{cls}':
        return (cls, f'{cls}::~{cls}() {{}}', 'dtor')

    # Operator or normal method
    # prefix_clean is the return type (may be empty for ctor/dtor, shouldn't be here)
    ret_type = clean_type(prefix_clean) if prefix_clean else 'void'
    params_decl = make_params(params_raw)
    const_str = ' const' if is_const else ''
    ret_stmt = default_return(ret_type)
    body = f' {ret_stmt} ' if ret_stmt else ' '

    # Handle operator names in func_part
    # func_part could be "operator=" or "operator==" or "operator[]" or "operator float" etc.
    # Or could be "RetType FuncName" if prefix was empty
    if not prefix_clean:
        # prefix was empty but it's not ctor/dtor — try splitting func_part
        parts = func_part.rsplit(' ', 1)
        if len(parts) == 2 and 'operator' not in parts[0]:
            ret_type = clean_type(parts[0])
            func_part = parts[1]
            ret_stmt = default_return(ret_type)
            body = f' {ret_stmt} ' if ret_stmt else ' '

    return (cls, f'{ret_type} {cls}::{func_part}({params_decl}){const_str} {{{body}}}', 'method')


def clean_type(t):
    """Clean a type string for use in C++ code."""
    t = t.strip()
    t = t.replace('class ', '')
    t = t.replace('struct ', '')
    t = re.sub(r'\s+', ' ', t)
    # Handle "enum X" -> "X"
    t = t.replace('enum ', '')
    return t


def make_params(params_raw):
    """Convert parameter type list to C++ parameter declarations."""
    params_raw = params_raw.strip()
    if params_raw == 'void' or params_raw == '':
        return ''

    params = split_params(params_raw)
    result = []
    for i, p in enumerate(params):
        p = clean_type(p)
        result.append(f'{p} p{i + 1}')
    return ', '.join(result)


def split_params(s):
    """Split comma-separated parameter list respecting nesting."""
    params = []
    depth = 0
    current = ''
    for ch in s:
        if ch in ('(', '<', '['):
            depth += 1
            current += ch
        elif ch in (')', '>', ']'):
            depth -= 1
            current += ch
        elif ch == ',' and depth == 0:
            params.append(current.strip())
            current = ''
        else:
            current += ch
    if current.strip():
        params.append(current.strip())
    return params


def default_return(ret_type):
    """Generate a default return statement for a type."""
    rt = ret_type.strip()
    if not rt or rt == 'void':
        return ''
    if '*' in rt:
        return 'return 0;'
    if '&' in rt:
        # Reference return — need static dummy
        base = rt.replace('&', '').replace('const', '').strip()
        if base == '':
            return ''
        return f'static {base} _d; return _d;'
    if rt in ('int', 'long', 'unsigned int', 'unsigned long',
              'short', 'unsigned short', 'char', 'unsigned char'):
        return 'return 0;'
    if rt in ('bool', 'bool const'):
        return 'return false;'
    if rt == 'float':
        return 'return 0.0f;'
    if rt == 'double':
        return 'return 0.0;'
    # Unknown — assume int-like
    return 'return 0;'


def main():
    if not os.path.exists(UNRESOLVED_FILE):
        print(f"Error: {UNRESOLVED_FILE} not found (run from project root)")
        sys.exit(1)

    entries = defaultdict(list)
    vftable_classes = set()
    parse_errors = []

    with open(UNRESOLVED_FILE, 'r', encoding='utf-8') as f:
        for lineno, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue
            m = LINE_RE.match(line)
            if not m:
                parse_errors.append((lineno, line))
                continue

            demangled, mangled = m.groups()
            cls, code, kind = parse_unresolved_line(demangled)

            if kind == 'vftable':
                vftable_classes.add(cls)
            elif code:
                entries[cls].append(code)

    # Map class names to their header files
    CLASS_TO_HEADER = {
        'gbCamera': 'gbengine/gbCamera.h',
        'gbCamControler': 'gbengine/gbCamera.h',
        'gbCamQuakeControl': 'gbengine/gbCamera.h',
        'gbCamSpringControl': 'gbengine/gbCamera.h',
        'gbGfxManager': 'gbengine/gbGfxManager.h',
        'gbGfxManager_D3D': 'gbengine/gbGfxManager.h',
        'gbEffectMgr': 'gbengine/gbGfxManager.h',
        'gbRenderEffect': 'gbengine/gbRenderEffect.h',
        'gbImage2D': 'gbengine/gbGfxManager.h',
        'gbImage2DInfo': 'gbengine/gbGfxManager.h',
        'gbGeomNode': 'gbengine/gbGeomNode.h',
        'gbBaseMesh': 'gbengine/gbMesh.h',
        'gbStaticMesh': 'gbengine/gbMesh.h',
        'gbDynVertBuf': 'gbengine/gbMesh.h',
        'gbVertPoolMgr': 'gbengine/gbMesh.h',
        'gbIndexBubble': 'gbengine/gbMesh.h',
        'gbTexture': 'gbengine/gbTexture.h',
        'gbTexture_D3D': 'gbengine/gbTexture.h',
        'gbTextureArray': 'gbengine/gbTexture.h',
        'gbVisNode': 'gbengine/gbVisNode.h',
        'gbVolModNode': 'gbengine/gbVisNode.h',
        'gbVolumeModifier': 'gbengine/gbVisNode.h',
        'gbSceneGraph': 'gbengine/gbSceneGraph.h',
        'gbLightObj': 'gbengine/gbSceneGraph.h',
        'gbActor': 'gbengine/gbActor.h',
        'gbActorMgr': 'gbengine/gbActor.h',
        'gbAnimNodeGroup': 'gbengine/gbParticle.h',
        'gbParticleEffect': 'gbengine/gbParticle.h',
        'gbParticleGroup': 'gbengine/gbParticle.h',
        'gbParticleUnit': 'gbengine/gbParticle.h',
        'gbEmitterData': 'gbengine/gbParticle.h',
        'gbEmitterSquare': 'gbengine/gbParticle.h',
        'gbPartGroupParam': 'gbengine/gbParticle.h',
        'gbPartEmitter': 'gbengine/gbParticle.h',
        'gbPartParamControl': 'gbengine/gbParticle.h',
        'gbVTextFile': 'gbengine/gbVFileSystem.h',
        'gbVFileSystem': 'gbengine/gbVFileSystem.h',
        'gbVFile1': 'gbengine/gbVFileSystem.h',
        'gbChain1D': 'gbengine/gbChain.h',
        'gbChain1DNode': 'gbengine/gbChain.h',
        'gbChain2D': 'gbengine/gbChain.h',
        'gbChain2DNode': 'gbengine/gbChain.h',
        'gbNBTree': 'gbengine/gbChain.h',
        'gbNBTreeNode': 'gbengine/gbChain.h',
        'gbBinaryTree': 'gbengine/gbChain.h',
        'gbBinaryTreeNode': 'gbengine/gbChain.h',
        'gbStaticChain': 'gbengine/gbChain.h',
        'gbAudioManager': 'gbengine/gbAudio.h',
        'gbAudioMgrDesc': 'gbengine/gbAudio.h',
        'gbSound2DNode': 'gbengine/gbAudio.h',
        'gbSound3DNode': 'gbengine/gbAudio.h',
        'gbPrintFont': 'gbengine/gbPrintFont.h',
        'gbPrintFontMgr': 'gbengine/gbPrintFont.h',
        'gbColorFlt': 'gbengine/gbengine_types.h',
        'gbColorQuad': 'gbengine/gbengine_types.h',
        'gbMatrix4': 'gbengine/gbengine_types.h',
        'gbVec3D': 'gbengine/gbengine_types.h',
        'gbQuaternion': 'gbengine/gbengine_types.h',
        'gbRotMatrix': 'gbengine/gbengine_types.h',
        'gbRay': 'gbengine/gbengine_types.h',
        'gbAABBox': 'gbengine/gbengine_types.h',
        'gbOBBox': 'gbengine/gbengine_types.h',
        'gbSphere': 'gbengine/gbengine_types.h',
        'gbPlane': 'gbengine/gbengine_types.h',
        'gbPixelFormat': 'gbengine/gbengine_types.h',
        'gbUIRect': 'gbengine/gbengine_types.h',
        'gbMatrixStack': 'gbengine/gbMisc.h',
        'gbNameVarBuf': 'gbengine/gbMisc.h',
        'gbTimeCounter': 'gbengine/gbMisc.h',
        'CPK': 'gbengine/gbVFileSystem.h',
        'CPKFile': 'gbengine/gbVFileSystem.h',
        'gbResManager': 'gbengine/gbGfxManager.h',
        'BEZIER': 'gbengine/gbengine_types.h',
        'gbDropGroup': 'gbengine/gbParticle.h',
        'gbRain': 'gbengine/gbParticle.h',
        'gbSnow': 'gbengine/gbParticle.h',
    }

    # Create output directory
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    files_written = 0
    total_stubs = 0

    for cls in sorted(entries.keys()):
        stubs = entries[cls]
        if cls == '__globals__':
            fname = 'stub_globals.cpp'
        elif cls == '__unparsed__':
            fname = 'stub_unparsed.cpp'
        else:
            fname = f'stub_{cls}.cpp'

        filepath = os.path.join(OUTPUT_DIR, fname)
        with open(filepath, 'w', encoding='utf-8') as f:
            # Determine correct include
            header = CLASS_TO_HEADER.get(cls)
            if header:
                f.write(f'#include "{header}"\n')
            else:
                f.write('#include "pal3.h"\n')
            # Also include common types that params might reference
            if header and header != 'gbengine/gbengine_types.h':
                f.write('#include "gbengine/gbengine_types.h"\n')
            f.write('#pragma optimize("", off)\n\n')

            for stub in stubs:
                f.write(stub + '\n\n')

        files_written += 1
        total_stubs += len(stubs)
        print(f'  {fname}: {len(stubs)} stubs')

    print(f'\n--- Summary ---')
    print(f'Files generated: {files_written}')
    print(f'Total stubs: {total_stubs}')
    print(f'Vtable classes: {len(vftable_classes)} ({", ".join(sorted(vftable_classes))})')
    if parse_errors:
        print(f'Parse errors: {len(parse_errors)}')
        for ln, txt in parse_errors[:5]:
            print(f'  Line {ln}: {txt[:80]}')
    print(f'Output: {OUTPUT_DIR}/')


if __name__ == '__main__':
    main()
