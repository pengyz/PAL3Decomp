"""
IDAPython: Pure export - no modifications to IDB. Just export all functions.

Usage:
  idat.exe -A -S"pal3_export_only.py" original/PAL3.exe.i64
"""
import ida_auto, ida_funcs, ida_hexrays, ida_name, ida_typeinf, idautils, idc
import json, os, time, glob

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
LOG_FILE = os.path.join(SCRIPT_DIR, "_logs", "pal3_export_only_log.txt")
TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Pure export (no IDB modifications)")

        os.makedirs(OUTPUT_DIR, exist_ok=True)
        for f in glob.glob(os.path.join(OUTPUT_DIR, "*.json")):
            if not os.path.basename(f).startswith('_'):
                os.remove(f)

        # Load skip list
        skip_addrs = set()
        skip_file = os.path.join(PROJECT_ROOT, "pipeline", "data", "annotations", "skip_functions.json")
        if os.path.exists(skip_file):
            import json as _json
            skip_data = _json.load(open(skip_file))
            skip_addrs = set(int(a, 16) for a in skip_data.keys())

        targets = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if not name or name.startswith("nullsub_") or name.startswith("j_"):
                continue
            if ea in skip_addrs:
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() <= 1:
                continue
            targets.append((ea, name, func.size()))
        targets.sort()

        named = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] Targets: %d (named: %d, sub_: %d)" % (len(targets), named, len(targets)-named))

        exported = 0
        t0 = time.time()
        for i, (ea, name, size) in enumerate(targets):
            if (i+1) % 1000 == 0:
                log("  [%d/%d]" % (i+1, len(targets)))
            try:
                # Clear Hex-Rays cache to force fresh decompilation with latest type info
                try:
                    ida_hexrays.mark_cfunc_dirty(ea)
                except:
                    pass
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
                while '__' in safe: safe = safe.replace('__', '_')
                safe = safe.strip('_')
                if len(safe) > 100: safe = safe[:100]
                filename = '%s_%08x.json' % (safe, ea)
                with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                    json.dump({'name': display_name, 'address': '0x%08X' % ea,
                               'size_bytes': size, 'signature': sig,
                               'decompiled_c': code}, f, indent=2, ensure_ascii=False)
                exported += 1
            except: pass

        log("[*] Exported: %d (%.1fs)" % (exported, time.time()-t0))

        # Export struct definitions from IDB (authoritative source for gen_headers)
        export_structs(log)

        log("[*] Done")
    except Exception as e:
        log("[!] %s" % str(e))

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)


def export_structs(log):
    """Export all struct definitions from IDB to ida_structs.json."""
    import idautils
    structs_path = os.path.join(PROJECT_ROOT, "asm", "pal3", "ida_structs.json")
    result = {}
    count = 0

    for idx, sid, name in idautils.Structs():
        size = idc.get_struc_size(sid)
        if size <= 0:
            continue

        members = []
        for offset, mname, msize in idautils.StructMembers(sid):
            mtype_str = 'int'
            stinfo = ida_typeinf.tinfo_t()
            if stinfo.get_named_type(ida_typeinf.get_idati(), name):
                udt = ida_typeinf.udt_type_data_t()
                if stinfo.get_udt_details(udt):
                    for mi in range(udt.size()):
                        um = udt[mi]
                        if um.offset // 8 == offset:
                            mtype_str = um.type.dstr() if um.type else 'int'
                            break
                    else:
                        mtype_str = 'char[%d]' % msize if msize > 4 else 'int'

            members.append({'name': mname, 'type': mtype_str, 'offset': offset})

        # Detect base class
        bases = []
        stinfo = ida_typeinf.tinfo_t()
        if stinfo.get_named_type(ida_typeinf.get_idati(), name):
            udt = ida_typeinf.udt_type_data_t()
            if stinfo.get_udt_details(udt):
                for mi in range(udt.size()):
                    um = udt[mi]
                    umname = um.name
                    if umname and ('baseclass' in umname.lower() or umname.startswith('__parent')):
                        base_type = um.type.dstr() if um.type else ''
                        for prefix in ('struct ', 'class '):
                            if base_type.startswith(prefix):
                                base_type = base_type[len(prefix):]
                        if base_type:
                            bases.append({'name': base_type, 'offset': um.offset // 8})

        # Filter out baseclass/vtable from members
        filtered = [m for m in members
                    if not any(x in m['name'].lower() for x in ('baseclass', '__parent', '__vftable', 'vtbl'))]

        result[name] = {
            'size': size,
            'kind': 'struct',
            'data_members': filtered,
            'bases': bases,
        }
        count += 1

    with open(structs_path, 'w', encoding='utf-8') as f:
        json.dump(result, f, indent=2, ensure_ascii=False)
    log("[*] Structs exported: %d → ida_structs.json" % count)

if __name__ == '__main__':
    main()
