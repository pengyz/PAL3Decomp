"""
IDAPython: Diagnose why Hex-Rays outputs #ordinal instead of type names.

Usage:
  idat.exe -A -S"diagnose_type_ordinals.py" original/PAL3.exe.i64
"""
import ida_auto, ida_hexrays, ida_typeinf, idautils, ida_funcs, json, os, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))

def check_type_ordinal(ordinal):
    """Check what a specific type ordinal represents."""
    print(f"\n=== Checking ordinal #{ordinal} ===")

    # Method 1: get_numbered_type
    tif = ida_typeinf.tinfo_t()
    if ida_typeinf.get_numbered_type(None, ordinal, tif):
        print(f"  get_numbered_type: SUCCESS")
        print(f"    dstr(): {tif.dstr()}")
        print(f"    size: {tif.get_size()}")
        print(f"    is_ptr: {tif.is_ptr()}")
        print(f"    is_struct: {tif.is_struct()}")
        print(f"    is_decl_struct: {tif.is_decl_struct()}")
        if tif.is_ptr():
            pointed = tif.get_pointed_object()
            print(f"    pointed_to: {pointed.dstr()}")
    else:
        print(f"  get_numbered_type: FAILED")

    # Method 2: get_numbered_type_name
    name = ida_typeinf.get_numbered_type_name(None, ordinal)
    if name:
        print(f"  get_numbered_type_name: {name}")
    else:
        print(f"  get_numbered_type_name: None")

    return tif if ida_typeinf.get_numbered_type(None, ordinal, tif) else None

def scan_decompilation_for_ordinals(ea):
    """Decompile a function and find all #ordinal patterns."""
    cfunc = ida_hexrays.decompile(ea)
    if not cfunc:
        return None, []

    code = str(cfunc)
    # Find all #ordinal patterns
    ordinals = set()
    for m in re.finditer(r'#(\d+)', code):
        ordinals.add(int(m.group(1)))

    return code, ordinals

def main():
    ida_auto.auto_wait()
    print("[*] Diagnosing type ordinal issues...")

    # Find functions with #ordinal patterns in their decompilation
    TEXT_START = 0x00401000
    TEXT_END = 0x005695D0

    functions_with_ordinals = []
    ordinal_counts = {}

    print("[*] Scanning first 100 functions for #ordinal patterns...")
    count = 0
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        if count >= 100:
            break
        count += 1

        code, ordinals = scan_decompilation_for_ordinals(ea)
        if ordinals:
            func = ida_funcs.get_func(ea)
            functions_with_ordinals.append({
                'ea': ea,
                'name': ida_funcs.get_func_name(ea),
                'ordinals': sorted(ordinals),
                'code_snippet': code[:200] if code else ""
            })
            for ord_num in ordinals:
                ordinal_counts[ord_num] = ordinal_counts.get(ord_num, 0) + 1

    print(f"\n[*] Found {len(functions_with_ordinals)} functions with #ordinal patterns")
    print(f"[*] Most common ordinals:")
    for ord_num, count in sorted(ordinal_counts.items(), key=lambda x: -x[1])[:10]:
        print(f"    #{ord_num}: {count} occurrences")

    # Deep dive into the most common ordinals
    print("\n" + "="*80)
    print("[*] Analyzing most common ordinals:")
    for ord_num, _ in sorted(ordinal_counts.items(), key=lambda x: -x[1])[:5]:
        tif = check_type_ordinal(ord_num)

    # Show example functions
    print("\n" + "="*80)
    print("[*] Example functions with #ordinal:")
    for func_info in functions_with_ordinals[:3]:
        print(f"\n0x{func_info['ea']:08X} {func_info['name']}")
        print(f"  Ordinals: {func_info['ordinals']}")
        print(f"  Code snippet: {func_info['code_snippet'][:150]}...")

    # Check if types are in the local type library
    print("\n" + "="*80)
    print("[*] Checking local type library:")
    til = ida_typeinf.get_idati()
    if til:
        qty = ida_typeinf.get_ordinal_qty(til)
        print(f"  Total ordinals in local type library: {qty}")

        # List some types
        print("  Sample types (first 20):")
        for i in range(1, min(21, qty)):
            name = ida_typeinf.get_numbered_type_name(til, i)
            if name:
                print(f"    #{i}: {name}")

    # Save results
    output_file = os.path.join(SCRIPT_DIR, "_logs", "type_ordinal_diagnosis.json")
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    with open(output_file, 'w') as f:
        json.dump({
            'functions_with_ordinals': functions_with_ordinals,
            'ordinal_counts': ordinal_counts,
            'total_ordinal_qty': ida_typeinf.get_ordinal_qty(ida_typeinf.get_idati())
        }, f, indent=2)

    print(f"\n[*] Results saved to: {output_file}")
    print("[*] Diagnosis complete")

if __name__ == "__main__":
    main()
    import ida_pro
    ida_pro.qexit(0)
