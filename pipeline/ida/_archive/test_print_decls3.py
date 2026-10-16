import ida_typeinf
f = open('/tmp/print_decls3.txt','w')
til = ida_typeinf.get_idati()

try:
    result = ida_typeinf.print_decls(til, ['tagNewItem'], 0, 0)
    f.write(f"print_decls: {repr(result)}\n")
except Exception as e:
    f.write(f"error: {e}\n")
    # Try with different flag values
    for flags in [1, 2, 4, 8]:
        try:
            result = ida_typeinf.print_decls(til, ['tagNewItem'], 0, flags)
            f.write(f"print_decls(flags={flags}): {repr(result)[:500]}\n")
        except Exception as e2:
            f.write(f"  flags={flags} error: {e2}\n")

f.close()
