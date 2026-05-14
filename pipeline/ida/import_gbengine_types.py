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
        "gbengine_types.h", "gbengine_export.h", "gbMisc.h", "gbChain.h",
        "gbTexture.h", "gbMesh.h", "gbResManager.h",
        "gbRenderEffect.h", "gbGeomNode.h",
        "gbSceneGraph.h", "gbCamera.h", "gbActor.h", "gbActorMgr.h",
        "gbAudio.h", "gbGfxManager.h", "gbParticle.h", "gbPrintFont.h",
        "gbResManager.h", "gbVFileSystem.h", "gbVisNode.h",
    ]

    all_content = []
    for hname in parse_order:
        hpath = os.path.join(header_dir, hname)
        if os.path.exists(hpath):
            all_content.append(open(hpath).read())
    full = '\n'.join(all_content)

    # Strip preprocessor
    full = re.sub(r'#[^\n]*\n', '\n', full)
    # Strip C++ comments
    full = re.sub(r'//[^\n]*', '', full)

    # Strip methods, friend, static, inline, access specifiers, extern
    lines = full.split('\n')
    output = []
    for line in lines:
        s = line.strip()
        if not s:
            output.append(line)
            continue
        if s.startswith(('friend ', 'static ', 'inline ', 'extern ')):
            continue
        if s in ('public:', 'private:', 'protected:'):
            continue
        if '(' in s and ')' in s:
            if re.search(r'\(\s*\*\s*\w+\s*\)', s):
                output.append(line)  # function pointer member
            else:
                continue  # method
        else:
            output.append(line)

    full = '\n'.join(output)

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
        'struct RECT { int left; int top; int right; int bottom; };\n'
        # CONFIRMDEVICECALLBACK: function pointer (D3DCAPS9* simplified to void*)
        'typedef unsigned char (__cdecl *CONFIRMDEVICECALLBACK)(void* pCaps, int vertexProcessingType, int adapterFormat, int backBufferFormat);\n'
        # Forward declarations for COM interfaces (only used as pointers)
        'struct IDirect3D9;\n'
        'struct ID3DXEffect;\n'
        'struct IDirect3DVertexDeclaration9;\n'
        # Forward declare for pointer-only usage
        'struct CArrayList;\n'
        'struct gbCursorRes;\n'
        # gbengine internal enum defined inside gbLightObj class
        'enum LIGHT_TYPE { LIGHT_POINT = 0, LIGHT_SPOT = 1, LIGHT_DIRECTIONAL = 2 };\n'
    )
    full = preamble + full

    # Expand macros that #define can't handle in parse_decls
    full = full.replace('CPK_MAX_TABLE_NUM', '0x8000')
    full = full.replace('CPK_MAX_OPEN_FILES', '8')

    # Replace C++ bool with unsigned char (IDA C parser compatibility)
    full = re.sub(r'\bbool\b', 'unsigned char', full)

    full = re.sub(r'\n{3,}', '\n\n', full)
    return full


def main():
    ida_auto.auto_wait()

    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(os.path.dirname(script_dir))
    header_dir = os.path.join(project_root, "include", "gbengine")
    log_dir = os.path.join(script_dir, "_logs")
    os.makedirs(log_dir, exist_ok=True)

    log_lines = []
    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    if not os.path.isdir(header_dir):
        log("[!] gbengine header dir not found: %s" % header_dir)
        idc.qexit(1)
        return

    log("[*] Flattening gbengine headers for IDA...")
    content = flatten_gbengine_headers(header_dir)

    flat_path = os.path.join(log_dir, "gbengine_flat_ida.h")
    with open(flat_path, 'w') as f:
        f.write(content)

    til = ida_typeinf.get_idati()

    # Step 1: Bulk parse with idc.parse_decls (handles inheritance + auto-registers)
    errs = idc.parse_decls(content, 0)
    log("[*] Step 1 idc.parse_decls: %d errors" % errs)

    # Step 2: Recover individually-parseable types missed by bulk parse
    decl_pattern = re.compile(
        r'((?:struct|enum)\s+(\w+)\s*(?::\s*[^{]*?)?\s*\{[^}]*(?:\{[^}]*\}[^}]*)*\}\s*;)',
        re.DOTALL
    )
    recovered = 0
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
    log("[*] Step 2 recovered: %d types" % recovered)

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
