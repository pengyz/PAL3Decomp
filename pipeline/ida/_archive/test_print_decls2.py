import ida_typeinf
f = open('/tmp/print_decls2.txt','w')
til = ida_typeinf.get_idati()

# print_decls: need ordinals and flags
try:
    # til, ordinals which is a list of type names, flags
    result = ida_typeinf.print_decls(til, ['tagNewItem'], 0)
    f.write(f"print_decls: {repr(result)}\n")
except Exception as e:
    f.write(f"print_decls error: {e}\n")
    # Try without ordinals
    try:
        result = ida_typeinf.print_decls(til, [], 0)
        f.write(f"print_decls (empty): {repr(result)[:500]}\n")
    except Exception as e2:
        f.write(f"print_decls2 error: {e2}\n")

f.close()
