"""
IDAPython: 诊断 PDB 导入后的孤儿 ordinal（前向声明成功，完整定义失败）
"""
import ida_auto, ida_typeinf, json, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))

def main():
    ida_auto.auto_wait()
    print("[*] Diagnosing orphan ordinals from PDB import...")

    til = ida_typeinf.get_idati()
    if not til:
        print("[!] No type library")
        return

    qty = ida_typeinf.get_ordinal_qty(til)
    print(f"[*] Total ordinals in TIL: {qty}")

    # Check top problematic ordinals from grep analysis
    problem_ordinals = [116, 115, 821, 133, 105, 114, 101, 123, 129, 127, 136, 119, 118, 124, 138]

    results = []
    for ordinal in problem_ordinals:
        tif = ida_typeinf.tinfo_t()
        if ida_typeinf.get_numbered_type(til, ordinal, tif):
            name = ida_typeinf.get_numbered_type_name(til, ordinal)
            dstr = tif.dstr()

            info = {
                'ordinal': ordinal,
                'name': name if name else None,
                'dstr': dstr,
                'is_decl_struct': tif.is_decl_struct(),  # Forward declaration only
                'is_struct': tif.is_struct(),
                'is_ptr': tif.is_ptr(),
                'size': tif.get_size(),
            }

            # Check if it's an orphan (forward decl without full definition)
            if tif.is_decl_struct():
                info['status'] = 'ORPHAN_FORWARD_DECL'
                print(f"\n[!] #{ordinal}: ORPHAN - forward declared but no full definition")
                print(f"    Name: {name}")
                print(f"    dstr: {dstr}")
            elif not name:
                info['status'] = 'ANONYMOUS'
                print(f"\n[!] #{ordinal}: ANONYMOUS - no name")
                print(f"    dstr: {dstr}")
            else:
                info['status'] = 'OK'
                print(f"\n[+] #{ordinal}: OK")
                print(f"    Name: {name}")
                print(f"    Size: {tif.get_size()}")

            results.append(info)
        else:
            print(f"\n[!] #{ordinal}: NOT FOUND in TIL")
            results.append({'ordinal': ordinal, 'status': 'NOT_FOUND'})

    # Save results
    output = {
        'total_ordinals': qty,
        'problem_ordinals': results,
        'orphan_count': sum(1 for r in results if r.get('status') == 'ORPHAN_FORWARD_DECL'),
        'anonymous_count': sum(1 for r in results if r.get('status') == 'ANONYMOUS'),
    }

    output_file = os.path.join(SCRIPT_DIR, "_logs", "orphan_ordinals.json")
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    with open(output_file, 'w') as f:
        json.dump(output, f, indent=2)

    print(f"\n[*] Results saved to: {output_file}")
    print(f"[*] Orphans: {output['orphan_count']}, Anonymous: {output['anonymous_count']}")

if __name__ == "__main__":
    main()
    import ida_pro
    ida_pro.qexit(0)
