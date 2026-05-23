"""
IDAPython: 调试 parse_decl 失败原因。

对每个失败结构体，尝试 parse_decl 并打印错误信息。
对大结构体，二分查找哪些成员导致解析失败。
"""
import ida_auto, ida_typeinf, idc
import json, os, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT_FILE = os.path.join(LOG_DIR, "parse_debug.json")


def load_all_structs():
    structs = {}
    structs_dir = os.path.join(ANNOTATIONS_DIR, "structs")
    for fname in os.listdir(structs_dir):
        if fname.endswith(".json"):
            with open(os.path.join(structs_dir, fname), "r", encoding="utf-8") as f:
                sdata = json.load(f)
            sname = sdata.get("name", fname.replace(".json", ""))
            structs[sname] = sdata
    return structs


def build_minimal_decl(name, size):
    """Build simplest possible struct with just size."""
    return "struct %s { char _data[%d]; };" % (name, size)


def build_member_line(mname, mtype, offset, next_offset, all_structs):
    """Build a single member line for IDA."""
    mtype = mtype.replace("class ", "").replace("struct ", "")

    # Handle arrays
    arr_match = re.search(r'(\[\d+\](?:\[\d+\])*)$', mtype)

    if 'std::' in mtype or '::' in mtype or '<' in mtype:
        span = next_offset - offset if next_offset > offset else 4
        return "    char %s[%d];" % (mname, max(span, 4)), offset + max(span, 4)

    if arr_match:
        base_type = mtype[:arr_match.start()].rstrip()
        line = "    %s %s%s;" % (base_type, mname, arr_match.group(1))
        return line, next_offset

    line = "    %s %s;" % (mtype, mname)
    if '*' in mtype:
        return line, offset + 4
    elif mtype == 'double':
        return line, offset + 8
    elif mtype == 'float':
        return line, offset + 4
    elif mtype in ('char', 'unsigned char', 'bool', 'BYTE'):
        return line, offset + 1
    elif mtype in ('short', 'unsigned short', 'WORD'):
        return line, offset + 2
    else:
        clean = mtype.strip()
        ref_size = 0
        if clean in all_structs:
            ref = all_structs[clean]
            ref_size = max(ref.get("pdb_size", 0), ref.get("binary_size", 0))
        return line, offset + (ref_size if ref_size > 0 else 4)


def try_parse(decl):
    """Try parse_decl and return success."""
    til = ida_typeinf.get_idati()
    tinfo = ida_typeinf.tinfo_t()
    result = ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)
    return result is not None


def main():
    ida_auto.auto_wait()
    print("[*] Debug parse_decl failures")

    all_structs = load_all_structs()

    # Load apply status
    status_file = os.path.join(LOG_DIR, "apply_status.json")
    with open(status_file, "r", encoding="utf-8") as f:
        status = json.load(f)

    # Test each failing struct
    results = {}
    tested = 0

    for sname, sinfo in sorted(status.items()):
        if sinfo["status"] not in ("missing", "empty"):
            continue
        if sname not in all_structs:
            continue

        sdata = all_structs[sname]
        members = sdata.get("known_members", {})
        size = max(sdata.get("binary_size", 0), sdata.get("pdb_size", 0))

        if not members or size == 0:
            continue

        tested += 1

        # Test 1: can we parse minimal struct?
        minimal = build_minimal_decl(sname, size)
        if not try_parse(minimal):
            results[sname] = {"issue": "name_conflict", "detail": "even minimal struct fails"}
            continue

        # Test 2: try adding members one by one, find first failure
        sorted_members = sorted(
            [(int(off), m) for off, m in members.items()],
            key=lambda x: x[0]
        )

        lines = []
        cursor = 0
        bad_member = None

        for i, (offset, minfo) in enumerate(sorted_members):
            mname = minfo["name"]
            mtype = minfo["type"]
            next_offset = sorted_members[i + 1][0] if i + 1 < len(sorted_members) else size

            if offset > cursor:
                lines.append("    char _gap_%03X[%d];" % (cursor, offset - cursor))

            line, new_cursor = build_member_line(mname, mtype, offset, next_offset, all_structs)
            lines.append(line)

            # Test if declaration still parses
            test_lines = list(lines)
            if new_cursor < size:
                test_lines.append("    char _tail_%03X[%d];" % (new_cursor, size - new_cursor))

            test_decl = "struct %s {\n%s\n};" % (sname + "_test", "\n".join(test_lines))
            if not try_parse(test_decl):
                bad_member = {
                    "offset": offset,
                    "name": mname,
                    "type": mtype,
                    "line": line.strip(),
                    "member_index": i,
                }
                # Verify: does it work without this member?
                test_without = list(lines[:-1])
                gap_size = next_offset - cursor if next_offset > cursor else 4
                test_without.append("    char _skip_%03X[%d];" % (offset, gap_size))
                if new_cursor < size:
                    test_without.append("    char _tail_%03X[%d];" % (next_offset, size - next_offset))
                test_decl2 = "struct %s {\n%s\n};" % (sname + "_test", "\n".join(test_without))
                if try_parse(test_decl2):
                    bad_member["confirmed"] = True
                break

            cursor = new_cursor

        if bad_member:
            results[sname] = {"issue": "bad_member", "detail": bad_member}
        else:
            # Full decl should work...
            if size > 0 and cursor < size:
                lines.append("    char _tail_%03X[%d];" % (cursor, size - cursor))
            full_decl = "struct %s {\n%s\n};" % (sname, "\n".join(lines))
            if try_parse(full_decl):
                results[sname] = {"issue": "ok_now", "detail": "rebuilding fixed it"}
            else:
                results[sname] = {"issue": "unknown", "decl_len": len(full_decl), "n_lines": len(lines)}

        if tested % 50 == 0:
            print("  [%d tested]" % tested)

    # Summary
    from collections import Counter
    issues = Counter(v["issue"] for v in results.values())
    print("[*] Results: %s" % dict(issues))

    # Show bad members
    bad_types = Counter()
    for sname, info in results.items():
        if info["issue"] == "bad_member":
            detail = info["detail"]
            print("  %s: offset=%d type='%s' name='%s' line='%s'" % (
                sname, detail["offset"], detail["type"], detail["name"], detail["line"]))
            bad_types[detail["type"]] += 1

    print("\nBad type frequency:")
    for typ, count in bad_types.most_common(20):
        print("  %s: %d" % (typ, count))

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    print("[*] Output: %s" % OUTPUT_FILE)
    idc.qexit(0)


if __name__ == "__main__":
    main()
