"""
Analyze remaining mismatched structs by:
1. Reset to char[] placeholder
2. Re-decompile functions (forces offset-based output)
3. Extract offsets from _data[N] pattern
4. Build typed struct

Targets: classes that were skipped in previous passes.
"""
import ida_auto, ida_hexrays, ida_typeinf, ida_name, idc, idautils
import json, os, re, time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)


TARGETS = [
    ("PalScript", 64),
    ("CEffMgr", 2304),
    ("CCBStageScene", 1024),
    ("CCBStageCam", 2048),
    ("CCBResultWindow", 256),
    ("CCBProtectWindow", 128),
    ("CCBParabolaWindow", 128),
    ("CCBSkillWindow", 128),
    ("ParabolaCalculator", 512),
    ("PAL_GDB", 8192),
    ("CCCTData", 4096),
]


def main():
    ida_auto.auto_wait()
    til = ida_typeinf.get_idati()
    log("[*] Analyze remaining structs (clear → decompile → extract)")
    log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

    fixed = 0
    for cls_name, size in TARGETS:
        # Step 1: Reset to placeholder
        decl = "struct %s { char _data[%d]; };" % (cls_name, size)
        idc.parse_decls(decl, idc.PT_TYP)

        # Step 2: Find class functions and decompile
        addrs = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if cls_name in name:
                addrs.append(ea)

        if not addrs:
            log("  [skip] %s: no functions" % cls_name)
            continue

        # Step 3: Decompile and extract offsets
        members = {}
        for ea in addrs[:15]:
            ida_hexrays.mark_cfunc_dirty(ea)
            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    continue
                code = str(cfunc)

                # _data[N] patterns
                for m in re.finditer(r'\*\(_DWORD \*\)&\w+->_data\[(\d+)\]', code):
                    off = int(m.group(1))
                    if off < size:
                        members[off] = {'size': 4, 'type': 'int'}
                for m in re.finditer(r'\*\(float \*\)&\w+->_data\[(\d+)\]', code):
                    off = int(m.group(1))
                    if off < size:
                        members[off] = {'size': 4, 'type': 'float'}
                for m in re.finditer(r'\*\(_DWORD \*\)&\w+->_data\[(\d+)\]\s*=\s*(operator new|\w+::\w+)', code):
                    off = int(m.group(1))
                    if off < size:
                        members[off] = {'size': 4, 'type': 'void *'}
                for m in re.finditer(r'\*?\(?_BYTE\s*\*?\)?\w+->_data\[(\d+)\]', code):
                    off = int(m.group(1))
                    if off < size and off not in members:
                        members[off] = {'size': 1, 'type': 'char'}
            except:
                pass

        if not members:
            log("  [skip] %s: no offsets after decompile (%d funcs)" % (cls_name, len(addrs)))
            continue

        # Step 4: Build and apply struct
        lines = ["struct %s {" % cls_name]
        prev_end = 0
        for off in sorted(members.keys()):
            m = members[off]
            if off > prev_end:
                lines.append("  char _pad_%03X[%d];" % (prev_end, off - prev_end))
            if m['type'] == 'float':
                lines.append("  float _f%03X;" % off)
            elif m['type'] == 'void *':
                lines.append("  void *_p%03X;" % off)
            elif m['type'] == 'char':
                lines.append("  char _b%03X;" % off)
            else:
                lines.append("  int _d%03X;" % off)
            prev_end = off + m['size']
        if prev_end < size:
            lines.append("  char _tail[%d];" % (size - prev_end))
        lines.append("};")

        decl = '\n'.join(lines)
        nerr = idc.parse_decls(decl, idc.PT_TYP)
        if nerr == 0:
            fixed += 1
            log("  [+] %s: %d members, size=%d" % (cls_name, len(members), size))
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
    with open(os.path.join(LOG_DIR, "pal3_analyze_remaining_log.txt"), 'w') as f:
        f.write('\n'.join(log_lines))
