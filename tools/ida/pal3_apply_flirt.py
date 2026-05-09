"""
IDAPython: Apply FLIRT signatures to identify CRT/STL functions in PAL3.exe

Applies vc32rtf and omvc60 signatures to recognize standard library functions.
Then re-exports all decomp with improved naming.

Usage:
  idat.exe -A -S"pal3_apply_flirt.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_funcs
import ida_name
import ida_hexrays
import idautils
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_apply_flirt_log.txt")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def count_named():
    named = 0
    total = 0
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        total += 1
        name = ida_name.get_name(ea) or ""
        if name and not name.startswith("sub_"):
            named += 1
    return named, total


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe FLIRT signature application")
        log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        before_named, total = count_named()
        log("[*] Before: %d / %d named" % (before_named, total))

        # Apply FLIRT signatures
        sigs = ["vc32rtf", "omvc60"]
        for sig_name in sigs:
            log("[*] Applying: %s" % sig_name)
            result = ida_funcs.plan_to_apply_idasgn(sig_name)
            log("    plan_to_apply_idasgn: %d" % result)

        # Wait for auto-analysis to process
        ida_auto.auto_wait()

        after_named, _ = count_named()
        log("[*] After: %d / %d named (+%d)" % (after_named, total, after_named - before_named))

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
                sig = cfunc.type.dstr()
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
                    'signature': sig,
                    'decompiled_c': code,
                }
                with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                    json.dump(result, f, indent=2, ensure_ascii=False)
                exported += 1
            except:
                errors += 1

        elapsed = time.time() - t0
        log("[*] Exported: %d, errors: %d (%.1fs)" % (exported, errors, elapsed))

        named_final = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] Final named in export: %d" % named_final)
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
