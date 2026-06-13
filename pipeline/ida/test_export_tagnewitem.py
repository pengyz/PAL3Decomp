import ida_typeinf, json
f = open("/tmp/export_test.txt", "w")

til = ida_typeinf.get_idati()
t = ida_typeinf.tinfo_t()
t.get_named_type(til, "tagNewItem")

f.write(f"size={t.get_size()}, dstr={t.dstr()}\n")

udt = ida_typeinf.udt_type_data_t()
if t.get_udt_details(udt):
    f.write(f"UDT: {udt.size()} members, total_size={udt.total_size}, flags={udt.taudt_bits}\n")
    for i in range(udt.size()):
        um = udt[i]
        mtype_str = um.type.dstr() if um.type else 'None'
        f.write(f"  +{um.offset//8}: '{um.name}' type='{mtype_str}' size={um.size//8}\n")
else:
    f.write("No UDT details\n")

f.close()
