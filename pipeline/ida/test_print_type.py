import ida_typeinf
f = open('/tmp/print_type_test.txt','w')
til = ida_typeinf.get_idati()

t = ida_typeinf.tinfo_t()
t.get_named_type(til, 'tagNewItem')

# Try print_type
try:
    result = ida_typeinf.print_type(til, t, 0, 0, ida_typeinf.PRINT_TYPE)
    f.write(f"print_type: {result}\n")
except Exception as e:
    f.write(f"print_type error: {e}\n")

# Try print_tinfo
try:
    result = ida_typeinf.print_tinfo("", til, t, 0, 0, 0)
    f.write(f"print_tinfo: {result}\n")
except Exception as e:
    f.write(f"print_tinfo error: {e}\n")

f.close()
