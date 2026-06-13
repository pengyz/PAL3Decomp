import sys
try:
    import ida_typeinf
    f = open('/tmp/print_decls_test.txt','w')
    til = ida_typeinf.get_idati()
    
    # Method 1: print_decls
    f.write("=== print_decls ===\n")
    try:
        result = ida_typeinf.print_decls(til, 0)
        f.write(f"type: {type(result)}\n")
        f.write(f"first 1000 chars: {str(result)[:1000]}\n")
    except Exception as e:
        f.write(f"print_decls error: {e}\n")
    
    # Method 2: Get declaration via ida_typeinf
    f.write("\n=== ida_typeinf attributes ===\n")
    for x in dir(ida_typeinf):
        if 'decl' in x.lower() or 'dstr' in x.lower() or 'print' in x.lower():
            f.write(f"  {x}\n")
    
    f.close()
except Exception as e:
    open('/tmp/print_decls_test.txt','w').write(f"FATAL: {e}\n")
