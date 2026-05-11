"""
IDAPython: Apply class names to functions confirmed via xref analysis.
Sets function names to Class::sub_XXXX format.

Usage:
  idat.exe -A -S"pal3_xref_annotate.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_name
import ida_funcs
import ida_hexrays
import idautils
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_xref_annotate_log.txt")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Xref-confirmed class attributions
XREF_CONFIRMED = [
    (0x004022E0, "C2DSpark"),
    (0x004014F0, "CCBAI"),
    (0x004ED010, "CCBAI"),
    (0x004ED060, "CCBAI"),
    (0x004EF980, "CCBAI"),
    (0x004F2BB0, "CCBAI"),
    (0x004F3570, "CCBAI"),
    (0x004F36D0, "CCBAI"),
    (0x004F3A50, "CCBAI"),
    (0x004F3BC0, "CCBAI"),
    (0x004F3C00, "CCBAI"),
    (0x004F3D90, "CCBAI"),
    (0x004F4DA0, "CCBAI"),
    (0x004F5070, "CCBAI"),
    (0x004F55D0, "CCBAI"),
    (0x004F57A0, "CCBAI"),
    (0x004F5970, "CCBAI"),
    (0x004F5B70, "CCBAI"),
    (0x004DB6C0, "CCBRoleState"),
    (0x004DB6E0, "CCBRoleState"),
    (0x004DB750, "CCBRoleState"),
    (0x004F05A0, "CCBRoleState"),
    (0x004F2910, "CCBRoleState"),
    (0x004F3430, "CCBRoleState"),
    (0x004F3B90, "CCBRoleState"),
    (0x004F3E20, "CCBRoleState"),
    (0x004F98B0, "CCBRoleState"),
    (0x004FA540, "CCBRoleState"),
    (0x004FA6A0, "CCBRoleState"),
    (0x004FA8B0, "CCBRoleState"),
    (0x004DFAA0, "CCBStage"),
    (0x004DFED0, "CCBStage"),
    (0x00503020, "CCBStage"),
    (0x0050A980, "CCBStage"),
    (0x0050D440, "CCBStage"),
    (0x0050E0D0, "CCBStage"),
    (0x004ED040, "CCBStageRole"),
    (0x0050A560, "CCBStageRole"),
    (0x0050B330, "CCBStageRole"),
    (0x0050B530, "CCBStageRole"),
    (0x00536CE0, "CCBStageRole"),
    (0x00536D20, "CCBStageRole"),
    (0x005371B0, "CCBStageRole"),
    (0x0053E2E0, "CCBStageRole"),
    (0x0053E310, "CCBStageRole"),
    (0x0050FE50, "CCBStageScene"),
    (0x004DB6A0, "CCBSystem"),
    (0x004DB710, "CCBSystem"),
    (0x004DB730, "CCBSystem"),
    (0x004DB780, "CCBSystem"),
    (0x004DB910, "CCBSystem"),
    (0x004DB920, "CCBSystem"),
    (0x004DC560, "CCBSystem"),
    (0x004DC5B0, "CCBSystem"),
    (0x004ED100, "CCBSystem"),
    (0x004FC8F0, "CCBSystem"),
    (0x004FC940, "CCBSystem"),
    (0x00500170, "CCBSystem"),
    (0x00513840, "CCBSystem"),
    (0x00515C50, "CCBSystem"),
    (0x00446010, "CCBUI"),
    (0x004DC5C0, "CCBUI"),
    (0x0041C900, "CCCTData"),
    (0x005044C0, "CCCTData"),
    (0x004D58A0, "CEffMgr"),
    (0x00402310, "GRPinput"),
    (0x00402380, "GRPinput"),
    (0x0047D9D0, "Object3D"),
    (0x00536C50, "Object3D"),
    (0x00536FD0, "Object3D"),
    (0x004118D0, "PAL3"),
    (0x0041EE40, "PAL3"),
    (0x00420F30, "PAL3"),
    (0x0042FDA0, "PAL3"),
    (0x0042FDC0, "PAL3"),
    (0x0042FDE0, "PAL3"),
    (0x0044F8A0, "PAL3"),
]


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe xref-based class annotation")
        log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        renamed = 0
        for addr, cls in XREF_CONFIRMED:
            cur = ida_name.get_name(addr) or ""
            if cur.startswith("sub_"):
                # Set name to Class::sub_XXXX
                new_name = "%s::%s" % (cls, cur)
                if ida_name.set_name(addr, new_name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                    renamed += 1
                else:
                    # :: not allowed in some contexts, try underscore
                    new_name2 = "%s_%s" % (cls, cur.replace("sub_",""))
                    ida_name.set_name(addr, new_name2, ida_name.SN_NOWARN | ida_name.SN_FORCE)
                    renamed += 1

        log("[*] Renamed: %d / %d" % (renamed, len(XREF_CONFIRMED)))

        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB saved")

        # Re-export
        log("[*] Re-exporting...")
        os.makedirs(OUTPUT_DIR, exist_ok=True)
        import glob
        for f in glob.glob(os.path.join(OUTPUT_DIR, "*.json")):
            if not os.path.basename(f).startswith('_'):
                os.remove(f)

        targets = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if not name or name.startswith("nullsub_") or name.startswith("j_"):
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() <= 1:
                continue
            targets.append((ea, name, func.size()))

        targets.sort()
        exported = 0
        errors = 0
        t0 = time.time()
        for i, (ea, name, size) in enumerate(targets):
            if (i+1) % 1000 == 0:
                log("  [%d/%d]" % (i+1, len(targets)))
            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    continue
                code = str(cfunc)
                sig_str = cfunc.type.dstr()
                demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else name
                safe = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
                safe = safe.replace('*', '_').replace(' ', '_').replace('?', '_')
                safe = safe.replace('@', '_').replace('$', '_').replace(',', '_')
                safe = safe.replace('(', '').replace(')', '').replace('/', '_')
                safe = safe.replace('"', '').replace("'", '').replace('\\', '_')
                while '__' in safe:
                    safe = safe.replace('__', '_')
                safe = safe.strip('_')
                if len(safe) > 100:
                    safe = safe[:100]
                filename = '%s_%08x.json' % (safe, ea)
                result = {
                    'name': display_name,
                    'address': '0x%08X' % ea,
                    'size_bytes': size,
                    'signature': sig_str,
                    'decompiled_c': code,
                }
                with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                    json.dump(result, f, indent=2, ensure_ascii=False)
                exported += 1
            except:
                errors += 1

        elapsed = time.time() - t0
        named_count = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] Exported: %d, errors: %d (%.1fs)" % (exported, errors, elapsed))
        log("[*] Named functions: %d" % named_count)
        log("[*] Done!")

    except Exception as e:
        log("[!] Error: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)


if __name__ == '__main__':
    main()
