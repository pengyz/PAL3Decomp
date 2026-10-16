"""
IDAPython: 检查 apply_annotations 后哪些结构体的成员在 IDA 中正确解析。

对每个 annotation struct，检查 IDA 的 til 中是否有对应 struct，
以及成员数量是否匹配。

输出: pipeline/ida/_logs/apply_status.json
"""
import ida_auto, ida_typeinf, idc
import json, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
ANNOTATIONS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
OUTPUT_FILE = os.path.join(LOG_DIR, "apply_status.json")


def main():
    ida_auto.auto_wait()
    print("[*] Check apply status")

    til = ida_typeinf.get_idati()

    structs_dir = os.path.join(ANNOTATIONS_DIR, "structs")
    results = {}

    for fname in sorted(os.listdir(structs_dir)):
        if not fname.endswith(".json"):
            continue
        with open(os.path.join(structs_dir, fname), "r", encoding="utf-8") as f:
            sdata = json.load(f)
        sname = sdata.get("name", fname.replace(".json", ""))
        n_members = len(sdata.get("known_members", {}))

        # Check if struct exists in IDA til
        tinfo = ida_typeinf.tinfo_t()
        found = tinfo.get_named_type(til, sname)

        if found:
            # Get IDA's struct size and member count
            ida_size = tinfo.get_size()
            # Try to count members
            udt = ida_typeinf.udt_type_data_t()
            if tinfo.get_udt_details(udt):
                ida_members = udt.size()
            else:
                ida_members = -1

            ann_size = max(sdata.get("binary_size", 0), sdata.get("pdb_size", 0))
            results[sname] = {
                "status": "ok" if ida_members > 0 else "empty",
                "ann_members": n_members,
                "ida_members": ida_members,
                "ann_size": ann_size,
                "ida_size": ida_size,
                "size_match": ida_size == ann_size if ann_size > 0 else None,
            }
        else:
            results[sname] = {
                "status": "missing",
                "ann_members": n_members,
            }

    # Summary
    ok = sum(1 for v in results.values() if v["status"] == "ok")
    empty = sum(1 for v in results.values() if v["status"] == "empty")
    missing = sum(1 for v in results.values() if v["status"] == "missing")
    size_mismatch = sum(1 for v in results.values() if v.get("size_match") == False)

    print("[*] Results: ok=%d, empty=%d, missing=%d, size_mismatch=%d" % (ok, empty, missing, size_mismatch))

    # Show problems
    for sname, info in sorted(results.items()):
        if info["status"] != "ok":
            print("  [%s] %s: ann_members=%d" % (info["status"], sname, info["ann_members"]))
        elif info.get("size_match") == False:
            print("  [size_mismatch] %s: ann=%d ida=%d" % (sname, info["ann_size"], info["ida_size"]))
        elif info["ida_members"] < info["ann_members"] // 2:
            print("  [low_members] %s: ann=%d ida=%d" % (sname, info["ann_members"], info["ida_members"]))

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    print("[*] Output: %s" % OUTPUT_FILE)
    idc.qexit(0)


if __name__ == "__main__":
    main()
