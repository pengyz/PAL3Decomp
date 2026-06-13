import ida_typeinf
f = open("/tmp/tagnewitem_check.txt", "w")
til = ida_typeinf.get_idati()

t = ida_typeinf.tinfo_t()
exists = t.get_named_type(til, "tagNewItem")
f.write(f"tagNewItem in TIL: {exists}\n")
if exists:
    f.write(f"  get_size: {t.get_size()}\n")
    f.write(f"  dstr: {t.dstr()}\n")
    udt = ida_typeinf.udt_type_data_t()
    if t.get_udt_details(udt):
        f.write(f"  UDT: {udt.size()} members, total_size={udt.total_size}\n")
        for i in range(udt.size()):
            m = udt[i]
            f.write(f"    +{m.offset//8}: {m.name} size={m.size//8} type={m.type.dstr()}\n")
    else:
        f.write(f"  No UDT details\n")
f.close()
