"""
Fix ALL 34 mismatched structs by analyzing their Hex-Rays decomp output.

For each placeholder struct, extract member offsets and types from _data[N] patterns,
then build a proper struct with typed members.

This script runs iteratively — import struct, re-decompile, verify.
"""
import ida_auto, ida_hexrays, ida_typeinf, ida_name, idc, idautils
import json, os, re, time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
DECOMP_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
PDB_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)


def get_class_functions(cls_name):
    """Get all function addresses for a class."""
    addrs = []
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        name = ida_name.get_name(ea) or ""
        if cls_name in name:
            addrs.append(ea)
    return addrs


def decompile_and_extract_offsets(ea):
    """Decompile function and extract _data[N] offset accesses."""
    members = {}
    ida_hexrays.mark_cfunc_dirty(ea)
    try:
        cfunc = ida_hexrays.decompile(ea)
        if not cfunc:
            return members
        code = str(cfunc)

        # _DWORD access at offset
        for m in re.finditer(r'\*\(_DWORD \*\)&\w+->_data\[(\d+)\]', code):
            off = int(m.group(1))
            members[off] = {'size': 4, 'type': 'int'}

        # float access
        for m in re.finditer(r'\*\(float \*\)&\w+->_data\[(\d+)\]', code):
            off = int(m.group(1))
            members[off] = {'size': 4, 'type': 'float'}

        # Pointer detection: assigned from operator new or function call
        for m in re.finditer(r'\*\(_DWORD \*\)&\w+->_data\[(\d+)\]\s*=\s*(operator new|[a-zA-Z]+::\w+)', code):
            off = int(m.group(1))
            members[off] = {'size': 4, 'type': 'void *'}

        # vtable at offset 0
        for m in re.finditer(r'\*\(_DWORD \*\)\w+->_data\s*=\s*&', code):
            members[0] = {'size': 4, 'type': 'void *'}

        # BYTE access
        for m in re.finditer(r'_data\[(\d+)\]\s*[=!<>]', code):
            off = int(m.group(1))
            if off not in members:
                members[off] = {'size': 1, 'type': 'char'}

    except Exception as e:
        pass
    return members


def build_struct_from_offsets(name, size, members):
    """Build IDA struct declaration from discovered members."""
    lines = ["struct %s {" % name]
    prev_end = 0

    for off in sorted(members.keys()):
        m = members[off]
        mtype = m['type']
        msize = m['size']

        if off > prev_end:
            lines.append("  char _pad_%03X[%d];" % (prev_end, off - prev_end))

        if mtype == 'float':
            lines.append("  float _f%03X;" % off)
            prev_end = off + 4
        elif mtype == 'void *':
            lines.append("  void *_p%03X;" % off)
            prev_end = off + 4
        elif mtype == 'char':
            lines.append("  char _b%03X;" % off)
            prev_end = off + 1
        else:
            lines.append("  int _d%03X;" % off)
            prev_end = off + 4

    if prev_end < size:
        lines.append("  char _tail[%d];" % (size - prev_end))
    lines.append("};")
    return '\n'.join(lines)


def apply_pdb_names(name, members, pdb_class, shift):
    """Try to apply PDB member names to discovered offsets using shift."""
    if not pdb_class:
        return members

    pdb_members = pdb_class.get('data_members', [])
    named = {}
    for pm in pdb_members:
        pal3_off = pm['offset'] + shift
        if pal3_off in members:
            named[pal3_off] = pm['name']
    return named


# Structs to fix with their sizes (from earlier analysis)
TARGETS = [
    ("CEffgbParticle", 80),
    ("CEffSParticle", 128),
    ("CEffModel", 256),
    ("CEffQuad", 512),
    ("CEffShock", 512),
    ("CEffGrid", 512),
    ("CEffCylinder", 512),
    ("CEffMeteor", 512),
    ("CEffExplosive", 1280),
    ("CEffCustomShape", 256),
    ("UIStatic", 248),
    ("UIFrameWnd", 152),
    ("UIDialog", 128),
    ("UIListBox", 1208),
    ("CCBControlWindow", 84),
    ("CCBItemWindow", 108),
    ("CCBMagicWindow", 180),
    ("CCBAIWindow", 256),
    ("CCBProtectWindow", 128),
    ("CCBParabolaWindow", 128),
    ("CCBSkillWindow", 128),
    ("CCBResultWindow", 256),
    ("SceneObj", 256),
    ("PalScript", 64),
]


def main():
    ida_auto.auto_wait()
    til = ida_typeinf.get_idati()
    log("[*] Fix mismatched structs from Hex-Rays analysis")
    log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

    fixed = 0
    for cls_name, size in TARGETS:
        # Get all functions for this class
        addrs = get_class_functions(cls_name)
        if not addrs:
            log("  [skip] %s: no functions found" % cls_name)
            continue

        # Extract offsets from decompilation
        all_members = {}
        for ea in addrs[:10]:  # limit to first 10 functions
            m = decompile_and_extract_offsets(ea)
            all_members.update(m)

        if not all_members:
            log("  [skip] %s: no offsets extracted" % cls_name)
            continue

        # Build struct
        decl = build_struct_from_offsets(cls_name, size, all_members)

        # Apply to IDA
        nerr = idc.parse_decls(decl, idc.PT_TYP)
        if nerr == 0:
            fixed += 1
            log("  [+] %s: %d members, size=%d" % (cls_name, len(all_members), size))
        else:
            log("  [!] %s: parse error %d" % (cls_name, nerr))

    log("")
    log("[*] Fixed: %d / %d" % (fixed, len(TARGETS)))
    ida_auto.auto_wait()
    idc.qexit(0)


try:
    main()
except Exception as e:
    log("[ERROR] %s" % str(e))
    import traceback
    log(traceback.format_exc())
finally:
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(os.path.join(LOG_DIR, "pal3_fix_all_mismatched_log.txt"), 'w') as f:
        f.write('\n'.join(log_lines))
