"""
IDAPython: Export types from PAL3A IDB - try both local types and ida_struct.
"""
import ida_auto, ida_typeinf, idc, os, json

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
OUTPUT_JSON = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pal3a_types_full.json")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3a_export_types_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)


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


def main():
    try:
        ida_auto.auto_wait()
        log("[*] Exporting types from PAL3A IDB")

        til = ida_typeinf.get_idati()
        count = get_ordinal_count(til)
        log("[*] Local types count: %d" % count)

        # Try ida_struct
        try:
            import ida_struct
            struct_count = ida_struct.get_struc_qty()
            log("[*] IDA structs count: %d" % struct_count)

            # Export IDA structs
            structs = []
            for i in range(struct_count):
                sid = ida_struct.get_struc_by_idx(i)
                sname = ida_struct.get_struc_name(sid)
                sptr = ida_struct.get_struc(sid)
                if not sptr:
                    continue

                entry = {
                    "name": sname,
                    "size": ida_struct.get_struc_size(sptr),
                    "is_union": bool(sptr.is_union()),
                    "bases": [],
                    "members": [],
                }

                for j in range(sptr.memqty):
                    mptr = sptr.get_member(j)
                    if not mptr:
                        continue
                    mname = ida_struct.get_member_name(mptr.id)
                    moff = mptr.soff
                    msize = ida_struct.get_member_size(mptr)

                    # Detect base class by name pattern
                    is_base = mname and ("baseclass" in mname.lower())
                    if is_base:
                        entry["bases"].append({"name": mname, "offset": moff})
                    else:
                        entry["members"].append({
                            "name": mname if mname else "_field_%04X" % moff,
                            "type": "char[%d]" % msize if msize > 4 else "int",
                            "offset": moff,
                            "size": msize,
                        })

                structs.append(entry)

            log("[*] Exported %d IDA structs" % len(structs))

            # Show first 30
            for s in structs[:30]:
                bases_str = ""
                if s["bases"]:
                    bases_str = " : " + ", ".join(b["name"] for b in s["bases"])
                log("  %-30s size=%d members=%d%s" % (
                    s["name"], s["size"], len(s["members"]), bases_str))

            # Count with bases
            has_bases = sum(1 for s in structs if s["bases"])
            log("[*] With inheritance: %d" % has_bases)

        except Exception as e:
            log("[!] ida_struct error: %s" % str(e))
            import traceback
            log(traceback.format_exc())
            structs = []

        # Also export local types
        classes = []
        enums = []
        for ordinal in range(1, count + 1):
            tif = ida_typeinf.tinfo_t()
            if not tif.get_numbered_type(til, ordinal):
                continue
            name = tif.get_type_name()
            if not name or '<' in name:
                continue
            if tif.is_struct() or tif.is_union():
                si = ida_typeinf.udt_type_data_t()
                if tif.get_udt_details(si):
                    entry = {"name": name, "size": tif.get_size(),
                             "is_union": bool(tif.is_union()), "bases": [], "members": []}
                    for i in range(si.size()):
                        m = si[i]
                        mname = m.name if m.name else ""
                        moff = m.offset // 8
                        msize = m.size // 8
                        mtype = m.type.dstr() if m.type else ""
                        if m.is_baseclass():
                            entry["bases"].append({"name": mtype or mname, "offset": moff})
                        else:
                            entry["members"].append({"name": mname, "type": mtype,
                                                    "offset": moff, "size": msize})
                    classes.append(entry)
            elif tif.is_enum():
                ei = ida_typeinf.enum_type_data_t()
                if tif.get_enum_details(ei):
                    entry = {"name": name, "values": {}}
                    for i in range(ei.size()):
                        entry["values"][ei[i].name] = int(ei[i].value)
                    enums.append(entry)

        log("[*] Local type classes: %d, enums: %d" % (len(classes), len(enums)))

        # Merge
        local_names = set(c["name"] for c in classes)
        merged = list(classes)
        for s in structs:
            if s["name"] not in local_names:
                merged.append(s)

        log("[*] Total merged: %d" % len(merged))

        # Write
        os.makedirs(os.path.dirname(OUTPUT_JSON), exist_ok=True)
        with open(OUTPUT_JSON, 'w', encoding='utf-8') as f:
            json.dump({"classes": merged, "enums": enums, "ida_structs_count": len(structs)},
                      f, indent=2, ensure_ascii=False)
        log("[*] Output: %s" % OUTPUT_JSON)
        log("[*] Done")

    except Exception as e:
        import traceback
        log("[!] %s" % str(e))
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
