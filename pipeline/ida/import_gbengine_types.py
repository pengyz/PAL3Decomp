"""
IDAPython: Import gbengine struct/enum definitions from flattened header.
Run BEFORE apply_annotations.py so gb* types are available for struct references.

Usage:
  idat -A -S"pipeline/ida/import_gbengine_types.py" original/PAL3.exe.i64
"""
import ida_auto, ida_typeinf, idc
import os, re

def flatten_gbengine_headers(header_dir):
    """Read all gbengine headers and produce IDA-compatible type declarations."""
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

    # Remove preprocessor directives
    full = re.sub(r'#[^\n]*\n', '\n', full)

    # Remove method declarations and inline implementations
    lines = full.split('\n')
    output = []
    for line in lines:
        stripped = line.strip()
        if '(' in stripped and ')' in stripped:
            if re.search(r'\(\s*\*\s*\w+\s*\)', stripped):
                output.append(line)  # function pointer member
            else:
                continue  # method declaration
        elif stripped.startswith('inline '):
            continue
        elif stripped in ('public:', 'private:', 'protected:'):
            continue
        elif stripped.startswith('static ') and '(' not in stripped and '=' not in stripped:
            output.append(line)  # static member variable
        elif stripped.startswith('static '):
            continue  # static method or init
        else:
            output.append(line)

    result = '\n'.join(output)
    result = re.sub(r'\s*// Methods \(auto-generated\)\s*', '\n', result)
    result = re.sub(r'\s*// legacy source name aliases\s*', '', result)
    result = re.sub(r'\n{3,}', '\n\n', result)
    return result


def main():
    ida_auto.auto_wait()

    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(os.path.dirname(script_dir))
    header_dir = os.path.join(project_root, "include", "gbengine")

    if not os.path.isdir(header_dir):
        print("[!] gbengine header dir not found: %s" % header_dir)
        idc.qexit(1)
        return

    print("[*] Flattening gbengine headers...")
    content = flatten_gbengine_headers(header_dir)

    til = ida_typeinf.get_idati()

    # Parse declarations one struct/enum at a time
    # Split on struct/class/enum boundaries
    ok = 0
    fail = 0
    fail_names = []

    # Extract individual type declarations
    # Pattern: (struct|class|enum) Name { ... };
    decl_pattern = re.compile(
        r'((?:struct|class|enum)\s+\w+\s*(?::\s*\w+\s*(?:,\s*\w+\s*)*)?'  # type Name [: base]
        r'\s*\{[^}]*(?:\{[^}]*\}[^}]*)*\}\s*;)',  # { body };
        re.DOTALL
    )

    for m in decl_pattern.finditer(content):
        decl = m.group(0)
        # Extract name
        name_match = re.match(r'(?:struct|class|enum)\s+(\w+)', decl)
        if not name_match:
            continue
        name = name_match.group(1)

        tinfo = ida_typeinf.tinfo_t()
        result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
        if result is not None:
            ok += 1
        else:
            fail += 1
            fail_names.append(name)

    # Also parse forward declarations
    for m in re.finditer(r'(class\s+\w+)\s*;', content):
        decl = m.group(0)
        tinfo = ida_typeinf.tinfo_t()
        ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)

    print("[*] gbengine types: %d parsed, %d failed" % (ok, fail))
    if fail_names:
        print("[!] Failed: %s" % ', '.join(fail_names[:20]))

    idc.save_database(idc.get_idb_path(), 0)
    idc.qexit(0)

if __name__ == '__main__':
    main()
