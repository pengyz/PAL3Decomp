"""
IDAPython: Apply batch 2 xref annotations (323 functions).
Reads from asm/pal3/_xref_batch6.json

Usage:
  idat.exe -A -S"pal3_xref_batch2.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, ida_funcs, ida_hexrays, idautils, idc
import json, os, time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_xref_batch6_log.txt")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
DATA_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "_xref_batch6.json")
TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Batch 2 xref annotation")

        with open(DATA_FILE, 'r') as f:
            annotations = json.load(f)
        log("[*] Loaded %d annotations" % len(annotations))

        renamed = 0
        for addr, cls in annotations:
            cur = ida_name.get_name(addr) or ""
            if cur.startswith("sub_"):
                new_name = "%s_%s" % (cls, cur.replace("sub_",""))
                if ida_name.set_name(addr, new_name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                    renamed += 1

        log("[*] Renamed: %d" % renamed)
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)

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
        for i, (ea, name, size) in enumerate(targets):
            if (i+1) % 1000 == 0:
                log("  [%d/%d]" % (i+1, len(targets)))
            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc: continue
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
                if len(safe) > 100: safe = safe[:100]
                filename = '%s_%08x.json' % (safe, ea)
                with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                    json.dump({'name': display_name, 'address': '0x%08X' % ea,
                               'size_bytes': size, 'signature': sig,
                               'decompiled_c': code}, f, indent=2, ensure_ascii=False)
                exported += 1
            except: pass

        named_count = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] Exported: %d, Named: %d" % (exported, named_count))
        log("[*] Done!")
    except Exception as e:
        log("[!] %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
