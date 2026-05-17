"""Quick test: try parse_decl for a specific struct and report error."""
import ida_auto, ida_typeinf, idc
import json, os, sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))

sys.path.insert(0, os.path.join(PROJECT_ROOT, "pipeline", "ida"))
from apply_annotations import build_struct_decl, load_annotations

def main():
    ida_auto.auto_wait()
    til = ida_typeinf.get_idati()

    data = load_annotations()
    structs = data.get("structs", {})

    # Forward declare all
    for sname in structs:
        fwd = "struct %s;" % sname
        t = ida_typeinf.tinfo_t()
        if ida_typeinf.parse_decl(t, til, fwd, ida_typeinf.PT_TYP) is not None:
            t.set_named_type(til, sname, ida_typeinf.NTF_REPLACE)

    # Test specific structs
    test_names = ["EquipUI", "CCBStageRole", "PalScriptMgr", "Role", "SwordUI"]
    vtables = data.get("vtables", {})

    test_results = {}
    for sname in test_names:
        if sname not in structs:
            print("[!] %s not found" % sname)
            continue
        decl = build_struct_decl(sname, structs[sname], structs, vtables)
        if not decl:
            print("[!] %s: None decl" % sname)
            continue
        print("[*] %s: decl_len=%d" % (sname, len(decl)))
        t = ida_typeinf.tinfo_t()
        result = ida_typeinf.parse_decl(t, til, decl, ida_typeinf.PT_TYP)
        if result is not None:
            t.set_named_type(til, sname, ida_typeinf.NTF_REPLACE)
            # Verify
            t2 = ida_typeinf.tinfo_t()
            t2.get_named_type(til, sname)
            udt = ida_typeinf.udt_type_data_t()
            if t2.get_udt_details(udt):
                print("  OK: ida_members=%d ida_size=%d" % (udt.size(), t2.get_size()))
            else:
                print("  PARSED but no UDT details")
        else:
            print("  FAILED to parse")
            # Try to find which line fails by binary search
            lines = decl.split("\n")
            # Remove struct wrapper
            body_lines = [l for l in lines if not l.startswith("struct") and l.strip() != "};"]
            lo, hi = 0, len(body_lines)
            while lo < hi:
                mid = (lo + hi) // 2
                test = "struct %s_test {\n%s\n};" % (sname, "\n".join(body_lines[:mid+1]))
                t3 = ida_typeinf.tinfo_t()
                if ida_typeinf.parse_decl(t3, til, test, ida_typeinf.PT_TYP) is not None:
                    lo = mid + 1
                else:
                    hi = mid
            if lo < len(body_lines):
                print("  First failing line [%d]: %s" % (lo, body_lines[lo].strip()))
            else:
                print("  Binary search inconclusive")
            test_results[sname] = {"status": "unknown_fail"}
        test_results[sname] = test_results.get(sname, {"status": "ok"})

    # Save results
    log_path = os.path.join(SCRIPT_DIR, "_logs", "test_single_struct.json")
    os.makedirs(os.path.dirname(log_path), exist_ok=True)
    with open(log_path, "w") as f:
        json.dump(test_results, f, indent=2)
    idc.qexit(0)

if __name__ == "__main__":
    main()
