"""
IDAPython: Import gbengine struct/enum definitions into IDA type system.
Run BEFORE apply_annotations.py so gb* types are available.

Preprocessing: strips C++ features IDA can't parse (methods, friend,
static, inline, comments) while preserving data layout.

Usage:
  idat -A -S"pipeline/ida/import_gbengine_types.py" original/PAL3.exe.i64
"""
import ida_auto, ida_typeinf, idc
import os, re


def flatten_gbengine_headers(header_dir, vc6_include_dir=None):
    """Read gbengine headers (+ optional VC6 D3D headers) and produce IDA-compatible C declarations."""
    parse_order = [
        "gbengine_types.h", "gbengine_export.h", "gbengine_internal.h",
        "gbMisc.h", "gbChain.h",
        "gbTexture.h", "gbMesh.h", "gbResManager.h",
        "gbRenderEffect.h", "gbGeomNode.h",
        "gbSceneGraph.h", "gbCamera.h", "gbActor.h", "gbActorMgr.h",
        "gbAudio.h", "gbGfxManager.h", "gbParticle.h", "gbPrintFont.h",
        "gbVFileSystem.h", "gbVisNode.h",
    ]

    # VC6 DirectX 9 SDK headers (value types + enums for PDB struct resolution)
    d3d_headers = [
        "d3d9types.h", "d3d9caps.h", "d3d9.h",
        "d3dx9math.h", "d3dx9core.h", "d3dx9.h",
    ]

    all_content = []
    for hname in parse_order:
        hpath = os.path.join(header_dir, hname)
        if os.path.exists(hpath):
            all_content.append(open(hpath, encoding='utf-8', errors='replace').read())
    full = '\n'.join(all_content)

    # Strip preprocessor
    full = re.sub(r'#[^\n]*\n', '\n', full)
    # Strip C++ comments
    full = re.sub(r'//[^\n]*', '', full)

    # Prepend external SDK type stubs (D3DX types — VC6 DirectX 9 SDK).
    # Provide full definitions for value types, forward decl for interface pointers.
    sdk_stubs = """
struct D3DCOLOR { unsigned long c; };
struct D3DVECTOR { float x; float y; float z; };
struct D3DCOLORVALUE { float r; float g; float b; float a; };
struct D3DXVECTOR2 { float x; float y; };
struct D3DXVECTOR3 { float x; float y; float z; };
struct D3DXVECTOR4 { float x; float y; float z; float w; };
struct D3DXCOLOR { float r; float g; float b; float a; };
struct D3DXMATRIX { float _11,_12,_13,_14; float _21,_22,_23,_24; float _31,_32,_33,_34; float _41,_42,_43,_44; };
struct ID3DXEffect;
struct ID3DXEffectPool;
struct IDirect3DVertexDeclaration9;
struct IDirect3DTexture9;
struct IDirect3DSurface9;
struct IDirect3DDevice9;
"""
    full = sdk_stubs + full

    # IDA parse_decls supports C++ method declarations with reference params,
    # but large classes with many methods can cause parse failures.
    # Strategy: strip all methods EXCEPT those with reference parameters (&).
    # This preserves the critical reference type info for Hex-Rays while
    # avoiding parse issues with complex method signatures.
    lines = full.split('\n')
    output = []
    in_method = False
    brace_depth = 0
    for line in lines:
        s = line.strip()
        # Skip access specifiers
        if s in ('public:', 'private:', 'protected:'):
            continue
        # Skip friend declarations
        if s.startswith('friend '):
            continue
        # Track inline function bodies: skip everything between { and }
        if in_method:
            brace_depth += s.count('{') - s.count('}')
            if brace_depth <= 0:
                in_method = False
                brace_depth = 0
            continue
        # Detect method declarations/definitions (has parens, not a function-pointer member)
        if '(' in s:
            is_func_ptr = bool(re.search(r'\(\s*\*\s*\w+\s*\)', s))
            is_typedef_fp = 'typedef' in s and '(*)' in s.replace(' ', '')
            has_reference = '&' in s and not is_func_ptr
            if is_func_ptr or is_typedef_fp:
                output.append(line)  # function pointer member — keep
            elif has_reference and 'operator' not in s:
                # Method with reference param — KEEP (critical for Hex-Rays)
                # Strip 'const' qualifier on method (IDA parse_decls doesn't support it)
                decl = s
                if '{' in decl:
                    decl = decl[:decl.index('{')].rstrip()
                # Remove trailing 'const' before ';'
                decl = re.sub(r'\)\s*const\s*;', ');', decl)
                decl = re.sub(r'\)\s*const\s*$', ')', decl)
                if not decl.endswith(';'):
                    decl += ';'
                output.append('    ' + decl)
                if '{' in s:
                    brace_depth = s.count('{') - s.count('}')
                    if brace_depth > 0:
                        in_method = True
            else:
                # Regular method without references or operator — skip
                if '{' in s:
                    brace_depth = s.count('{') - s.count('}')
                    if brace_depth > 0:
                        in_method = True
                continue
        else:
            # Skip static/extern member declarations (they don't occupy instance space)
            if s.lstrip().startswith('static ') or s.lstrip().startswith('extern '):
                continue
            # Remove other keywords IDA C parser doesn't handle
            s2 = line
            for kw in ('inline ', 'virtual ', 'explicit '):
                s2 = s2.replace(kw, '')
            output.append(s2)
    full = '\n'.join(output)

    # Remove orphaned method parameter fragments (leftover from multi-line method strip)
    # Pattern: lines outside struct bodies that look like stray params ending with );
    full = re.sub(r'^\s*[\w\s,*&]*\)\s*;\s*$', '', full, flags=re.MULTILINE)
    # Also catch lines with just comma-separated params (no leading struct context)
    full = re.sub(r'^\s+\w+\s+\w+,\s*\w+\s+\w+\)\s*;\s*$', '', full, flags=re.MULTILINE)

    # Fix empty struct bodies: ensure they have at least a dummy member
    # Pattern: "struct X { <only whitespace> };" where body has no members
    def _fix_empty_structs(text):
        def _repl(m):
            body = m.group(2)
            if body.strip():
                return m.group(0)
            return m.group(1) + ' char __vtbl; ' + m.group(3)
        return re.sub(
            r'(struct\s+\w+(?:\s*:\s*(?:public\s+)?\w+)?\s*\{)([\s]*)(};)',
            _repl, text)
    full = _fix_empty_structs(full)

    # Replace 'class' with 'struct'
    full = re.sub(r'\bclass\b', 'struct', full)

    # Reorder struct definitions by dependency DAG (topological sort).
    # Value members require the referenced type to be fully defined first.
    # Pointer/reference members only need a forward declaration.
    #
    # NOTE: The old regex approach could not handle nested braces (struct→union→struct),
    # which caused gbColorQuad and similar types to be truncated. Use brace-counting instead.
    _struct_start_re = re.compile(r'(struct\s+(\w+)(?:\s*:\s*(?:public\s+)?(\w+))?\s*\{)')
    _structs = {}  # name → (full_text, base_class, set_of_value_deps)
    _non_struct_parts = []  # (position, text) for non-struct content
    _last_end = 0

    def _find_struct_end(text, start):
        """Find the matching '};' for a struct definition starting at 'start'."""
        depth = 0
        i = start
        in_char = False
        while i < len(text):
            c = text[i]
            if c == '\\' and not in_char:
                i += 2
                continue
            if c == "'" and not in_char:
                in_char = True
            elif c == "'" and in_char:
                in_char = False
            elif c == '"' and not in_char:
                # skip string literal
                i += 1
                while i < len(text) and text[i] != '"':
                    if text[i] == '\\':
                        i += 1
                    i += 1
            elif not in_char:
                if c == '{':
                    depth += 1
                elif c == '}':
                    depth -= 1
                    if depth == 0:
                        # Check for trailing ';' (with optional whitespace)
                        j = i + 1
                        while j < len(text) and text[j] in ' \t\n\r':
                            j += 1
                        if j < len(text) and text[j] == ';':
                            return j + 1  # position after ';'
                        else:
                            # Not a valid struct end (e.g., function body), continue
                            pass
            i += 1
        return start  # no match found

    for sm in _struct_start_re.finditer(full):
        sm_start = sm.start()
        if sm_start > _last_end:
            _non_struct_parts.append(full[_last_end:sm_start])
        sname = sm.group(2)
        base = sm.group(3)
        end = _find_struct_end(full, sm.end() - 1)  # start from the '{'
        if end > sm.end():
            body = full[sm.start():end]
            _last_end = end
        else:
            # No matching '};' found, treat as non-struct
            _non_struct_parts.append(full[sm_start:sm.end()])
            _last_end = sm.end()
            continue
        # Find value-type dependencies: member declarations like "TypeName fieldname;"
        # (not pointers "TypeName *fieldname;")
        deps = set()
        if base:
            deps.add(base)
        for dm in re.finditer(r'(\w+)\s+\w+\s*(?:\[[^\]]*\])?\s*;', body):
            dep_type = dm.group(1)
            # Check it's not a pointer line and not a primitive
            line_ctx = body[max(0, dm.start()-5):dm.end()]
            if '*' not in line_ctx and dep_type not in (
                'int', 'float', 'double', 'char', 'short', 'long', 'void',
                'unsigned', 'signed', 'bool', 'BYTE', 'WORD', 'DWORD',
                'BOOL', 'UINT', 'ULONG', 'LONG', 'CHAR', 'LPSTR', 'LPCSTR',
                sname  # self-reference in methods
            ):
                deps.add(dep_type)
        _structs[sname] = (body, deps)
    if _last_end < len(full):
        _non_struct_parts.append(full[_last_end:])

    # Topological sort (Kahn's algorithm)
    _all_names = set(_structs.keys())
    _in_degree = {n: 0 for n in _all_names}
    _adj = {n: [] for n in _all_names}
    for sname, (_, deps) in _structs.items():
        for dep in deps:
            if dep in _all_names and dep != sname:
                _adj[dep].append(sname)
                _in_degree[sname] += 1
    _queue = [n for n in _all_names if _in_degree[n] == 0]
    _sorted = []
    while _queue:
        _queue.sort()  # deterministic order
        n = _queue.pop(0)
        _sorted.append(n)
        for m2 in _adj[n]:
            _in_degree[m2] -= 1
            if _in_degree[m2] == 0:
                _queue.append(m2)
    # Append any remaining (circular deps — shouldn't happen for data types)
    for n in _all_names:
        if n not in _sorted:
            _sorted.append(n)

    # Rebuild: non-struct preamble + sorted structs
    _preamble_text = ''.join(_non_struct_parts)
    _sorted_structs = '\n\n'.join(_structs[n][0] for n in _sorted if n in _structs)
    full = _preamble_text + '\n' + _sorted_structs + '\n'

    # Remove forward declarations for structs that have full definitions.
    # IDA may assign different ordinals to forward decl vs full def, causing
    # Hex-Rays to output "struct #NNN" instead of the named type.
    defined_structs = set(_structs.keys())
    full = re.sub(
        r'^struct\s+(\w+)\s*;\s*$',
        lambda m: '' if m.group(1) in defined_structs else m.group(0),
        full, flags=re.MULTILINE
    )

    # Add correct typedefs and forward declarations for external types
    preamble = (
        # DirectX enums (IDA doesn't have SDK headers — use int-sized typedefs)
        'typedef int D3DDEVTYPE;\n'
        'typedef int D3DFORMAT;\n'
        'typedef int D3DSWAPEFFECT;\n'
        'typedef int D3DMULTISAMPLE_TYPE;\n'
        # D3DXHANDLE is LPCSTR per d3dx9shader.h
        'typedef const char * D3DXHANDLE;\n'
        'typedef unsigned int UINT;\n'
        # Windows types
        'struct tagPOINT { int x; int y; };\n'
        'struct tagRECT { int left; int top; int right; int bottom; };\n'
        'struct RECT { int left; int top; int right; int bottom; };\n'
        # CONFIRMDEVICECALLBACK: function pointer (D3DCAPS9* simplified to void*)
        'typedef unsigned char (__cdecl *CONFIRMDEVICECALLBACK)(void* pCaps, int vertexProcessingType, int adapterFormat, int backBufferFormat);\n'
        # Forward declarations for COM interfaces and DirectX types
        'struct IDirect3D9;\n'
        'struct ID3DXEffect;\n'
        'struct IDirect3DVertexDeclaration9;\n'
        'struct IDirect3DBaseTexture9;\n'
        'struct IDirect3DDevice9;\n'
        'struct IDirect3DIndexBuffer9;\n'
        'struct IDirect3DVertexBuffer9;\n'
        'struct IDirect3DSurface9;\n'
        # DirectX structs (opaque to gbengine — only used by value in gbGfxManager_D3D)
        'struct D3DCAPS9 { char _data[0x130]; };\n'
        'struct D3DPRESENT_PARAMETERS { char _data[0x38]; };\n'
        'struct D3DSURFACE_DESC { char _data[0x20]; };\n'
        'struct D3DDISPLAYMODE { int Width; int Height; int RefreshRate; int Format; };\n'
        'struct D3DADAPTER_IDENTIFIER9 { char _data[0x210]; };\n'
        # Windows types
        'typedef void * HWND;\n'
        'typedef void * HANDLE;\n'
        'typedef void * HINSTANCE;\n'
        'typedef void * HDC;\n'
        'typedef unsigned long ULONG;\n'
        'typedef void * FILE;\n'
        'struct LARGE_INTEGER { unsigned int LowPart; int HighPart; };\n'
        # Forward declare for pointer-only usage
        'struct CArrayList;\n'
        'struct gbCursorRes;\n'
        # LIGHT_TYPE comes from gbengine headers (gbMisc.h), no need to predefine
    )
    full = preamble + full

    # Expand macros that #define can't handle in parse_decls
    full = full.replace('CPK_MAX_TABLE_NUM', '0x8000')
    full = full.replace('CPK_MAX_OPEN_FILES', '8')
    full = full.replace('MAX_STREAMS', '4')
    full = full.replace('MAX_2D_SAMPLES', '64')
    full = full.replace('MAX_3D_SAMPLES', '32')

    # Replace C++ bool with unsigned char (IDA C parser compatibility)
    full = re.sub(r'\bbool\b', 'unsigned char', full)

    # Strip GBAPI/GBENGINE_API macro (dllexport attribute, not needed for type defs)
    full = re.sub(r'\bGBAPI\b', '', full)
    full = re.sub(r'\bGBENGINE_API\b', '', full)

    # IDA's parse_decls supports C++ inheritance syntax natively

    # Remove known duplicate nested enum (LIGHT_TYPE is defined globally in gbMisc.h
    # AND nested inside gbLightObj — the nested copy causes parse errors)
    full = re.sub(r'enum\s+LIGHT_TYPE\s*\{[^}]*\}\s*;', '', full)

    full = re.sub(r'\n{3,}', '\n\n', full)
    return full


def main():
    ida_auto.auto_wait()

    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(os.path.dirname(script_dir))
    header_dir = os.path.join(project_root, "include", "gbengine")
    log_dir = os.path.join(script_dir, "_logs")
    os.makedirs(log_dir, exist_ok=True)
    # Debug: write path info immediately
    with open(os.path.join(log_dir, "import_gbengine_debug.txt"), 'w') as _dbg:
        _dbg.write("script_dir: %s\nproject_root: %s\nheader_dir: %s\nexists: %s\n" %
                   (script_dir, project_root, header_dir, os.path.isdir(header_dir)))

    log_lines = []
    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    if not os.path.isdir(header_dir):
        log("[!] gbengine header dir not found: %s" % header_dir)
        return

    log("[*] Flattening gbengine headers + VC6 D3D headers for IDA...")
    vc6_include_dir = os.path.join(project_root, "tools", "vc6", "Include")
    try:
        content = flatten_gbengine_headers(header_dir, vc6_include_dir)
    except Exception as e:
        log("[!] flatten_gbengine_headers failed: %s" % str(e))
        import traceback
        log(traceback.format_exc())
    
    # ── Post-processing: fix member names to match gbengine header ──
    # PDB imports may use different naming conventions (PascalCase vs camelCase).
    # gbengine headers are the source of truth — override any PDB-derived names.
    log("[*] Fixing gbengine struct member names to match headers...")
    fix_count = 0
    rename_map = {
        # (struct_name, pdb_name) → header_name
        # gbRefObject/gbResource naming (PascalCase in PDB vs camelCase in header)
        ("gbRefObject", "RefCount"): "refCount",
        ("gbResource", "pName"): "name",
        ("gbResource", "NameCrc32"): "nameCrc",
        ("gbResource", "IsLoaded"): "isLoaded",
        ("gbResource", "pMgr"): "manager",
        # gbChain1D naming
        ("gbChain1D", "m_Head"): "pHead",
        ("gbChain1D", "m_Tail"): "pTail",
        ("gbChain1D", "m_Cur"): "pIterator",
        # gbChain1DNode
        ("gbChain1DNode", "next"): "pNext",
        # gbNBTreeNode
        ("gbNBTreeNode", "pFather"): "pParent",
        # gbVisNode naming
        ("gbVisNode", "pSceneGraph"): "pSceneGraph",  # same
        ("gbVisNode", "Priority"): "renderPriority",
        ("gbVisNode", "TimeScale"): "timeScale",
        ("gbVisNode", "bShow"): "visible",
        ("gbVisNode", "bDoShadow"): "enableShadow",
        ("gbVisNode", "pCullPrev"): "cullPrev",
        ("gbVisNode", "pCullNext"): "cullNext",
        ("gbVisNode", "BlendParam"): "blendValue",
        ("gbVisNode", "BlendFlag"): "blendMode",
    }
    for (cls, old_name), new_name in rename_map.items():
        sid = idc.get_struc_id(cls)
        if sid == -1:
            log("  [SKIP] struct %s not found" % cls)
            continue
        # Find member by name
        mptr = idc.get_member_by_name(sid, old_name)
        if not mptr:
            # Maybe it was already renamed in a previous run
            mptr = idc.get_member_by_name(sid, new_name)
            if mptr:
                log("  [OK] %s.%s already renamed to %s" % (cls, old_name, new_name))
                continue
            log("  [SKIP] %s.%s not found in struct" % (cls, old_name))
            continue
        if idc.set_member_name(mptr, new_name):
            fix_count += 1
            log("  [FIX] %s.%s → %s" % (cls, old_name, new_name))
        else:
            log("  [FAIL] %s.%s → %s (set_member_name failed)" % (cls, old_name, new_name))
    log("[*] Renamed %d struct members" % fix_count)
    
    log_path = os.path.join(log_dir, "import_gbengine_log.txt")
    with open(log_path, 'w') as f:
        f.write('\n'.join(log_lines))

if __name__ == '__main__':
    main()
