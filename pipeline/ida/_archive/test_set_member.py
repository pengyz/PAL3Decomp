import ida_typeinf, ida_struct
f = open('/tmp/set_member_test.txt', 'w')

til = ida_typeinf.get_idati()
t = ida_typeinf.tinfo_t()
t.get_named_type(til, 'tagNewItem')

# Try get_member_by_name
f.write("get_member_by_name:\n")
for mname in ['fnHP', 'nHP', 'fnGP', 'nGP', 'fnMP', 'fMP', 'nMP']:
    mtype = t.get_member_by_name(mname)
    if mtype is not None:
        f.write(f"  {mname}: {mtype.dstr()}\n")
    else:
        f.write(f"  {mname}: None\n")

# Check if ida_struct has the struct
sid = ida_struct.get_struc_id('tagNewItem')
f.write(f"\nget_struc_id('tagNewItem') = {sid}\n")
if sid != -1:
    s = ida_struct.get_struc(sid)
    f.write(f"struc: {s}\n")
    f.write(f"members: {s.member_qty()}\n")

f.close()
