"""
Export all local struct/type definitions from PAL3 IDA database.
Output: asm/pal3/ida_structs.json

This captures structs we've manually created/imported in IDA (like SceneMgr)
that are NOT in the PAL3A PDB. gen_headers.py can use this as override data.
"""
import ida_auto
import ida_typeinf
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
OUTPUT_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "ida_structs.json")

def main():
    ida_auto.auto_wait()
    til = ida_typeinf.get_idati()

    print("[*] Exporting struct definitions from IDA TIL...")
    t0 = time.time()

    structs = []

    # Get ordinal count (IDA version compatible)
    def get_ordinal_count(til):
        if hasattr(til, 'get_ordinal_qty'):
            return til.get_ordinal_qty()
        if hasattr(ida_typeinf, 'get_ordinal_qty'):
            return ida_typeinf.get_ordinal_qty(til)
        n = 1
        while True:
            tif = ida_typeinf.tinfo_t()
            if not tif.get_numbered_type(til, n):
                break
            n += 1
            if n > 100000:
                break
        return n - 1

    count = get_ordinal_count(til)
    print("[*] TIL ordinals: %d" % count)

    for ordinal in range(1, count + 1):
        tif = ida_typeinf.tinfo_t()
        if not tif.get_numbered_type(til, ordinal):
            continue

        name = tif.get_type_name()
        if not name:
            continue

        # Only export struct/union types
        if not tif.is_struct() and not tif.is_union():
            continue

        size = tif.get_size()
        if size <= 0:
            continue

        # Get members
        udt = ida_typeinf.udt_type_data_t()
        if not tif.get_udt_details(udt):
            continue

        members = []
        for i in range(udt.size()):
            m = udt[i]
            members.append({
                'name': m.name,
                'offset': m.offset // 8,  # bits to bytes
                'size': m.size // 8,
                'type': m.type.dstr() if m.type else 'int',
            })

        structs.append({
            'name': name,
            'size': size,
            'data_members': members,
        })

    elapsed = time.time() - t0
    print("[*] Exported %d structs in %.1fs" % (len(structs), elapsed))

    # Write output
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        json.dump({'structs': structs}, f, indent=2, ensure_ascii=False)

    print("[+] Saved to %s" % OUTPUT_FILE)
    idc.qexit(0)

try:
    main()
except Exception as e:
    print("[ERROR] %s" % str(e))
    import traceback
    traceback.print_exc()
    idc.qexit(1)
