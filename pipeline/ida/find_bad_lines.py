"""IDAPython: Binary-search for the first failing line in each empty struct."""
import ida_auto, ida_typeinf, idc
import json, os, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "pipeline", "data", "annotations")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

def try_parse(decl):
    til = ida_typeinf.get_idati()
    t = ida_typeinf.tinfo_t()
    return ida_typeinf.parse_decl(t, til, decl, ida_typeinf.PT_TYP) is not None

def main():
    ida_auto.auto_wait()

    # Load apply status
    with open(os.path.join(LOG_DIR, "apply_status.json"), "r", encoding="utf-8") as f:
        status = json.load(f)

    # Load struct data
    all_structs = {}
    for fname in os.listdir(os.path.join(ANNOTATIONS_DIR, "structs")):
        if fname.endswith(".json"):
            with open(os.path.join(ANNOTATIONS_DIR, "structs", fname), "r", encoding="utf-8") as f:
                d = json.load(f)
            all_structs[d.get("name", fname.replace(".json", ""))] = d

    # Forward declare everything
    til = ida_typeinf.get_idati()
    primitives = {"char","int","float","double","short","long","unsigned",
                  "unsigned char","unsigned short","unsigned int","unsigned long",
                  "void","bool","BYTE","WORD","DWORD","UINT","LONG","BOOL",
                  "HRESULT","__int64","_DWORD","_BYTE","_WORD"}
    fwd_names = set(all_structs.keys())
    for sinfo in all_structs.values():
        for m in sinfo.get("known_members", {}).values():
            base = re.sub(r'\[.*\]', '', m["type"].replace("class ", "").replace("struct ", "")).replace("*", "").strip()
            if base and base not in primitives:
                fwd_names.add(base)
    for name in fwd_names:
        t = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(t, til, "struct %s;" % name, ida_typeinf.PT_TYP) is not None:
            t.set_named_type(til, name, ida_typeinf.NTF_REPLACE)

    # For each empty struct, build member lines and binary search for failure
    results = {}
    empty_structs = [s for s, v in status.items() if v["status"] == "empty" and s in all_structs]

    for sname in sorted(empty_structs):
        sdata = all_structs[sname]
        members = sdata.get("known_members", {})
        size = max(sdata.get("binary_size", 0) or 0, sdata.get("pdb_size", 0) or 0, sdata.get("gen_size", 0) or 0)
        if not members or size == 0:
            continue

        sorted_m = sorted([(int(o), m) for o, m in members.items()], key=lambda x: x[0])

        # Build individual member lines
        member_lines = []
        cursor = 0
        for offset, minfo in sorted_m:
            mtype = minfo["type"].replace("class ", "").replace("struct ", "")
            mname = minfo["name"]
            if offset > cursor:
                member_lines.append("    char _gap_%03X[%d];" % (cursor, offset - cursor))
            arr = re.search(r'(\[\d+\](?:\[\d+\])*)$', mtype)
            if "std::" in mtype or "::" in mtype or "<" in mtype:
                span = 4
                for o2, _ in sorted_m:
                    if o2 > offset:
                        span = o2 - offset
                        break
                else:
                    span = size - offset if size > offset else 4
                member_lines.append("    char %s[%d];" % (mname, max(span, 4)))
                cursor = offset + max(span, 4)
            elif arr:
                base_type = mtype[:arr.start()].rstrip()
                member_lines.append("    %s %s%s;" % (base_type, mname, arr.group(1)))
                # Estimate cursor
                for o2, _ in sorted_m:
                    if o2 > offset:
                        cursor = o2
                        break
                else:
                    cursor = size
            else:
                member_lines.append("    %s %s;" % (mtype, mname))
                if "*" in mtype: cursor = offset + 4
                elif mtype == "float": cursor = offset + 4
                elif mtype == "double": cursor = offset + 8
                elif mtype in ("char", "unsigned char", "bool", "BYTE"): cursor = offset + 1
                elif mtype in ("short", "unsigned short", "WORD"): cursor = offset + 2
                else: cursor = offset + 4

        if cursor < size:
            member_lines.append("    char _tail_%03X[%d];" % (cursor, size - cursor))

        # Binary search for first failing line
        lo, hi = 0, len(member_lines)
        while lo < hi:
            mid = (lo + hi) // 2
            test = "struct %s_test {\n%s\n};" % (sname, "\n".join(member_lines[:mid + 1]))
            if try_parse(test):
                lo = mid + 1
            else:
                hi = mid

        if lo < len(member_lines):
            results[sname] = {
                "fail_line_idx": lo,
                "fail_line": member_lines[lo].strip(),
                "total_lines": len(member_lines),
            }
        else:
            # All lines pass individually — maybe it's a total size issue
            full = "struct %s {\n%s\n};" % (sname, "\n".join(member_lines))
            if try_parse(full):
                results[sname] = {"status": "ok_now"}
            else:
                results[sname] = {"status": "unknown_fail", "total_lines": len(member_lines)}

    with open(os.path.join(LOG_DIR, "bad_lines.json"), "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    # Summary
    from collections import Counter
    line_issues = Counter()
    for r in results.values():
        if "fail_line" in r:
            line_issues[r["fail_line"]] += 1
        elif "status" in r:
            line_issues[r["status"]] += 1

    print("[*] Results:")
    for issue, count in line_issues.most_common(20):
        print("  %s: %d" % (issue, count))

    idc.qexit(0)

if __name__ == "__main__":
    main()
