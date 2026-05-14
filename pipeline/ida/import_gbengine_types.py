"""
IDAPython: Import gbengine struct/enum definitions into IDA type system.
Run BEFORE apply_annotations.py so gb* types are available.

Preprocessing: strips C++ features IDA can't parse (methods, union, friend,
static, inline, comments) while preserving data layout.

Usage:
  idat -A -S"pipeline/ida/import_gbengine_types.py" original/PAL3.exe.i64
"""
import ida_auto, ida_typeinf, idc
import os, re

LOG_PATH = None  # set in main()


def flatten_gbengine_headers(header_dir):
    """Read gbengine headers and produce IDA-compatible C declarations."""
    parse_order = [
        "gbengine_types.h", "gbengine_export.h", "gbMisc.h", "gbChain.h",
        "gbTexture.h", "gbMesh.h", "gbRenderEffect.h", "gbGeomNode.h",
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

    # Step 1: Remove preprocessor
    full = re.sub(r'#[^\n]*\n', '\n', full)

    # Step 2: Remove C++ comments (// ...)
    full = re.sub(r'//[^\n]*', '', full)

    # Step 3: Remove method declarations (lines with () not being function pointers)
    lines = full.split('\n')
    output = []
    for line in lines:
        stripped = line.strip()
        if not stripped:
            output.append(line)
            continue

        # Skip friend declarations
        if stripped.startswith('friend '):
            continue
        # Skip static members and methods
        if stripped.startswith('static '):
            continue
        # Skip inline
        if stripped.startswith('inline '):
            continue
        # Skip public/private/protected
        if stripped in ('public:', 'private:', 'protected:'):
            continue
        # Skip extern
        if stripped.startswith('extern '):
            continue

        # Lines with () — methods unless function pointer member
        if '(' in stripped and ')' in stripped:
            # Keep: type (*name)(...); — function pointer member
            if re.search(r'\(\s*\*\s*\w+\s*\)', stripped):
                output.append(line)
            # Skip everything else with parens (methods, constructors, operators)
            else:
                continue
        else:
            output.append(line)

    full = '\n'.join(output)

    # Step 4: Flatten anonymous unions/structs for IDA
    # Pattern: union { struct { members }; struct { members }; scalar; };
    # Replace with just the scalar or first struct's members

    # gbColorQuad: union { struct{BGRA}; struct{bgra}; uint Color; }; → uint Color;
    full = re.sub(
        r'union\s*\{\s*struct\s*\{[^}]*\}\s*;\s*struct\s*\{[^}]*\}\s*;\s*([\w\s]+\w+\s*;)\s*\}',
        r'\1',
        full
    )

    # gbColorFlt: union { struct{RGBA floats}; struct{rgba floats}; }; → individual floats
    full = re.sub(
        r'union\s*\{\s*struct\s*\{\s*float\s+Red\s*,\s*Green\s*,\s*Blue\s*,\s*Alpha\s*;\s*\}\s*;\s*'
        r'struct\s*\{\s*float\s+r\s*,\s*g\s*,\s*b\s*,\s*a\s*;\s*\}\s*;\s*\}',
        'float r; float g; float b; float a;',
        full
    )

    # gbMatrix4: union { float m[4][4]; struct{16 named floats}; }; → float m[4][4];
    full = re.sub(
        r'union\s*\{\s*float\s+m\[4\]\[4\]\s*;\s*struct\s*\{[^}]*\}\s*;\s*\}',
        'float m[4][4];',
        full
    )

    # gbUIQuad: union { struct { float sx,sy,ex,ey; }; float rect[4]; }; → 4 floats
    full = re.sub(
        r'union\s*\{\s*struct\s*\{\s*float\s+sx\s*,\s*sy\s*,\s*ex\s*,\s*ey\s*;\s*\}\s*;\s*'
        r'float\s+rect\[4\]\s*;\s*\}',
        'float sx; float sy; float ex; float ey;',
        full
    )

    # Step 5: Add typedefs for unknown external types
    preamble = (
        'typedef int D3DDEVTYPE;\n'
        'typedef int D3DFORMAT;\n'
        'typedef int D3DSWAPEFFECT;\n'
        'typedef int D3DMULTISAMPLE_TYPE;\n'
        'typedef int CONFIRMDEVICECALLBACK;\n'
        'typedef unsigned int UINT;\n'
    )
    full = preamble + full

    # Step 6: Replace remaining unknown types with void*
    full = re.sub(r'\bCArrayList\s*\*', 'void *', full)
    full = re.sub(r'\bIDirect3D9\s*\*', 'void *', full)

    # Clean up multiple blank lines
    full = re.sub(r'\n{3,}', '\n\n', full)
    return full


def main():
    global LOG_PATH
    ida_auto.auto_wait()

    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(os.path.dirname(script_dir))
    header_dir = os.path.join(project_root, "include", "gbengine")
    LOG_PATH = os.path.join(script_dir, "_logs", "import_gbengine_log.txt")
    os.makedirs(os.path.dirname(LOG_PATH), exist_ok=True)

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

    # Save flattened content for debugging
    flat_path = os.path.join(os.path.dirname(LOG_PATH), "gbengine_flat_ida.h")
    with open(flat_path, 'w') as f:
        f.write(content)
    log("[*] Flattened header saved: %s" % flat_path)

    til = ida_typeinf.get_idati()

    # Parse all declarations at once
    errs = ida_typeinf.idc_parse_types(content, 0)
    log("[*] idc_parse_types returned: %s" % str(errs))

    # Verify which types are now in TIL
    ok = 0
    fail = 0
    fail_names = []
    type_names = set()
    for m in re.finditer(r'(?:struct|class|enum)\s+(\w+)\s*[{:;]', content):
        type_names.add(m.group(1))

    for name in sorted(type_names):
        tinfo = ida_typeinf.tinfo_t()
        if ida_typeinf.get_named_type(til, name, ida_typeinf.NTF_TYPE):
            ok += 1
        else:
            fail += 1
            fail_names.append(name)

    log("[*] gbengine types verified: %d found in TIL, %d missing" % (ok, fail))
    if fail_names:
        log("[!] Missing types: %s" % ', '.join(fail_names[:30]))

    with open(LOG_PATH, 'w') as f:
        f.write('\n'.join(log_lines))

    idc.qexit(0)

if __name__ == '__main__':
    main()
