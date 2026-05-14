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


def flatten_gbengine_headers(header_dir):
    """Read gbengine headers and produce IDA-compatible C declarations."""
    parse_order = [
        "gbengine_types.h", "gbengine_export.h", "gbengine_internal.h",
        "gbMisc.h", "gbChain.h",
        "gbTexture.h", "gbMesh.h", "gbResManager.h",
        "gbRenderEffect.h", "gbGeomNode.h",
        "gbSceneGraph.h", "gbCamera.h", "gbActor.h", "gbActorMgr.h",
        "gbAudio.h", "gbGfxManager.h", "gbParticle.h", "gbPrintFont.h",
        "gbVFileSystem.h", "gbVisNode.h",
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

    # IDA parse_decls only handles data layout — strip all methods/functions.
    # Strategy: remove lines containing '(' that are NOT function-pointer members.
    # Then clean up any empty struct bodies and ensure proper closing braces.
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
            if is_func_ptr or is_typedef_fp:
                output.append(line)  # function pointer member — keep
            else:
                # It's a method — skip it
                # If it has an opening brace, track until closing
                if '{' in s:
                    brace_depth = s.count('{') - s.count('}')
                    if brace_depth > 0:
                        in_method = True
                continue
        else:
            # Remove keywords IDA C parser doesn't handle
            s2 = line
            for kw in ('static ', 'extern ', 'inline ', 'virtual ', 'explicit '):
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

    # Nested enum inside struct: IDA can't handle. Pull them out before the struct.
    # Pattern: "enum NAME { ... };" inside a struct body
    # For now, just remove nested enums (they're defined elsewhere)
    full = re.sub(r'\s*enum\s+\w+\s*\{[^}]*\}\s*;', '', full)

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
        idc.qexit(1)
        return

    log("[*] Flattening gbengine headers for IDA...")
    try:
        content = flatten_gbengine_headers(header_dir)
    except Exception as e:
        log("[!] flatten_gbengine_headers failed: %s" % str(e))
        import traceback
        log(traceback.format_exc())
        log_path = os.path.join(log_dir, "import_gbengine_log.txt")
        with open(log_path, 'w') as f:
            f.write('\n'.join(log_lines))
        idc.qexit(1)
        return

    flat_path = os.path.join(log_dir, "gbengine_flat_ida.h")
    with open(flat_path, 'w') as f:
        f.write(content)

    til = ida_typeinf.get_idati()

    # Step 0: Remove forward-declaration stubs that block full definitions
    # (IDA keeps forward decls with size=-1 that prevent inheritance parsing)
    type_names_in_content = set(re.findall(r'(?:struct|enum)\s+(\w+)\s*[{:]', content))
    stubs_removed = 0
    for tname in type_names_in_content:
        tinfo = ida_typeinf.tinfo_t()
        if tinfo.get_named_type(til, tname):
            sz = tinfo.get_size()
            if sz == 0xFFFFFFFFFFFFFFFF or sz == 0:
                ida_typeinf.del_named_type(til, tname, ida_typeinf.NTF_TYPE)
                stubs_removed += 1
    if stubs_removed:
        log("[*] Step 0: removed %d forward-decl stubs from TIL" % stubs_removed)

    # Step 1: Bulk parse (two passes — second catches ordering-dependent failures)
    errs = idc.parse_decls(content, 0)
    log("[*] Step 1 idc.parse_decls pass 1: %d errors" % errs)
    if errs > 0:
        errs2 = idc.parse_decls(content, 0)
        log("[*] Step 1 idc.parse_decls pass 2: %d errors" % errs2)

    # Step 1b: Identify which declarations fail by testing each block
    if errs > 0:
        # Split content into logical blocks (each struct/enum/typedef)
        blocks = re.split(r'(?<=;\n)', content)
        cum_errors = 0
        error_blocks = []
        for i, block in enumerate(blocks):
            block_s = block.strip()
            if not block_s:
                continue
            e = idc.parse_decls(block_s, 0)
            if e > 0:
                # Extract name from block
                nm = re.search(r'(?:struct|enum|typedef\s+\S+\s+)(\w+)', block_s)
                name = nm.group(1) if nm else "block_%d" % i
                error_blocks.append((name, block_s[:150]))
                cum_errors += e
        if error_blocks:
            log("[!] Step 1b: %d blocks with errors:" % len(error_blocks))
            for name, preview in error_blocks:
                log("    FAIL: %s — %s" % (name, preview.replace('\n', ' ')[:100]))

    # Step 2: Recover individually-parseable types missed by bulk parse
    decl_pattern = re.compile(
        r'((?:struct|enum)\s+(\w+)\s*(?::\s*[^{]*?)?\s*\{[^}]*(?:\{[^}]*\}[^}]*)*\}\s*;)',
        re.DOTALL
    )
    recovered = 0
    failed_individual = []
    for m in decl_pattern.finditer(content):
        name = m.group(2)
        decl = m.group(1)
        tinfo = ida_typeinf.tinfo_t()
        if not tinfo.get_named_type(til, name):
            tinfo2 = ida_typeinf.tinfo_t()
            result = ida_typeinf.parse_decl(tinfo2, til, decl, ida_typeinf.PT_TYP)
            if result is not None:
                tinfo2.set_named_type(til, name)
                recovered += 1
            else:
                failed_individual.append(name)
    log("[*] Step 2 recovered: %d types, failed: %d" % (recovered, len(failed_individual)))
    if failed_individual:
        log("[!] Step 2 failures: %s" % ', '.join(failed_individual))

    # Verify
    type_names = set()
    for mm in re.finditer(r'(?:struct|enum)\s+(\w+)\s*[{:;]', content):
        type_names.add(mm.group(1))

    ok = fail = 0
    fail_list = []
    for name in sorted(type_names):
        # Try multiple verification methods
        tinfo = ida_typeinf.tinfo_t()
        found = tinfo.get_named_type(til, name)
        if not found:
            found = bool(ida_typeinf.get_named_type(til, name, ida_typeinf.NTF_TYPE))
        if found:
            ok += 1
        else:
            fail += 1
            fail_list.append(name)

    log("[*] gbengine types: %d found in TIL, %d missing" % (ok, fail))
    if fail_list:
        log("[!] Missing: %s" % ', '.join(fail_list))

    log_path = os.path.join(log_dir, "import_gbengine_log.txt")
    with open(log_path, 'w') as f:
        f.write('\n'.join(log_lines))

    idc.qexit(0)

if __name__ == '__main__':
    main()
