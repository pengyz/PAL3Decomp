import ida_typeinf
f = open('/tmp/print_type_test3.txt','w')

t = ida_typeinf.tinfo_t()
t.get_named_type(None, 'tagNewItem')  # Try with None til

# Correct parameter order: prefix, indent, cmtindent, flags, tif, name, cmt
try:
    result = ida_typeinf.print_tinfo("", 0, 0, 0, t, "tagNewItem", "")
    f.write(f"print_tinfo: {repr(result)}\n")
except Exception as e:
    f.write(f"error: {e}\n")
    # Try different combos
    try:
        result = ida_typeinf.print_tinfo("", 0, 0, 0, t, "", "")
        f.write(f"print_tinfo (empty name): {repr(result)}\n")
    except Exception as e2:
        f.write(f"error2: {e2}\n")

f.close()
