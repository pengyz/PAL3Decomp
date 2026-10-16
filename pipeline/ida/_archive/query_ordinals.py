"""
IDAPython: Query specific type ordinals to understand why they don't resolve.
"""
import ida_auto, ida_typeinf, json, os, sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

# Ordinals to query (from grep analysis)
ORDINALS_TO_CHECK = [116, 115, 821, 133, 105, 114, 101, 123, 129, 127]

def query_ordinal(ordinal):
    """Get all available info about a type ordinal."""
    result = {'ordinal': ordinal}

    # Try to get type info
    tif = ida_typeinf.tinfo_t()
    if ida_typeinf.get_numbered_type(None, ordinal, tif):
        result['get_numbered_type'] = 'SUCCESS'
        result['dstr'] = tif.dstr()
        result['size'] = tif.get_size()
        result['is_ptr'] = tif.is_ptr()
        result['is_struct'] = tif.is_struct()
        result['is_decl_struct'] = tif.is_decl_struct()
        result['is_union'] = tif.is_union()
        result['is_enum'] = tif.is_enum()
        result['is_array'] = tif.is_array()

        # If it's a pointer, get what it points to
        if tif.is_ptr():
            pointed = tif.get_pointed_object()
            result['pointed_to_dstr'] = pointed.dstr()
            result['pointed_to_size'] = pointed.get_size()
    else:
        result['get_numbered_type'] = 'FAILED'

    # Try to get name
    name = ida_typeinf.get_numbered_type_name(None, ordinal)
    result['name'] = name if name else None

    return result

def main():
    ida_auto.auto_wait()
    print("[*] Querying type ordinals...")

    results = {}
    for ordinal in ORDINALS_TO_CHECK:
        print(f"  Checking #{ordinal}...")
        results[ordinal] = query_ordinal(ordinal)

    # Check total ordinals in local type library
    til = ida_typeinf.get_idati()
    qty = ida_typeinf.get_ordinal_qty(til) if til else 0

    output = {
        'ordinals': results,
        'total_ordinals_in_til': qty,
        'til_name': ida_typeinf.get_til_name(til) if til else None
    }

    output_file = os.path.join(SCRIPT_DIR, "_logs", "ordinal_query_results.json")
    os.makedirs(os.path.dirname(output_file), exist_ok=True)

    with open(output_file, 'w') as f:
        json.dump(output, f, indent=2)

    print(f"\n[*] Results saved to: {output_file}")

    # Print summary
    print("\n=== Summary ===")
    for ordinal, info in results.items():
        print(f"\n#{ordinal}:")
        if info.get('name'):
            print(f"  Name: {info['name']}")
        if info.get('dstr'):
            print(f"  Type: {info['dstr']}")
        else:
            print(f"  Type: UNRESOLVED")

if __name__ == "__main__":
    main()
    import ida_pro
    ida_pro.qexit(0)
