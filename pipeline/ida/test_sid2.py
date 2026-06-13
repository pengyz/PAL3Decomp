import sys, traceback as tb
try:
    import ida_typeinf
except Exception as e:
    open('/tmp/sid2_err.txt','a').write(f"ida_typeinf import error: {e}\n{tb.format_exc()}\n")

try:
    import ida_struct
except Exception as e:
    open('/tmp/sid2_err.txt','a').write(f"ida_struct import error: {e}\n{tb.format_exc()}\n")

open('/tmp/sid2_err.txt','a').write("imports done\n")

try:
    til = ida_typeinf.get_idati()
    t = ida_typeinf.tinfo_t()
    t.get_named_type(til, 'tagNewItem')
    open('/tmp/sid2_err.txt','a').write(f"got tagNewItem: {t.dstr()}\n")
    
    for mname in ['fnHP', 'nHP']:
        try:
            mtype = t.get_member_by_name(mname)
            if mtype is not None:
                open('/tmp/sid2_err.txt','a').write(f"  {mname}: {mtype.dstr()}\n")
            else:
                open('/tmp/sid2_err.txt','a').write(f"  {mname}: None\n")
        except Exception as e:
            open('/tmp/sid2_err.txt','a').write(f"  {mname} error: {e}\n")
except Exception as e:
    open('/tmp/sid2_err.txt','a').write(f"error: {e}\n{tb.format_exc()}\n")

open('/tmp/sid2_err.txt','a').write("DONE\n")
