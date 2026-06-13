import ida_typeinf, inspect
f = open('/tmp/print_type_test2.txt','w')
til = ida_typeinf.get_idati()

t = ida_typeinf.tinfo_t()
t.get_named_type(til, 'tagNewItem')

# Check signature of print_tinfo
try:
    sig = inspect.signature(ida_typeinf.print_tinfo)
    f.write(f"print_tinfo sig: {sig}\n")
except Exception as e:
    f.write(f"print_tinfo sig error: {e}\n")

# Check print_type signature
try:
    sig = inspect.signature(ida_typeinf.print_type)
    f.write(f"print_type sig: {sig}\n")
except Exception as e:
    f.write(f"print_type sig error: {e}\n")

# Try print_tinfo with empty cmt
try:
    result = ida_typeinf.print_tinfo("", til, t, 0, 0, 0, "")
    f.write(f"print_tinfo: {repr(result)}\n")
except Exception as e:
    f.write(f"print_tinfo error: {e}\n")

f.close()
