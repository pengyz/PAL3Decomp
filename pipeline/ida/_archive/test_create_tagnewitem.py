import ida_typeinf, json, os
f = open("/tmp/create_tagnewitem.txt", "w")

til = ida_typeinf.get_idati()

# Load annotation
ann_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../data/annotations/structs/tagNewItem.json')
with open(ann_path) as f2:
    ann = json.load(f2)

binary_size = ann.get('binary_size', 0)
members = ann.get('known_members', {})
f.write(f"binary_size={binary_size}, members={len(members)}\n")

# Simulate create_fixed_struct
udt = ida_typeinf.udt_type_data_t()
udt.taudt_bits = 1024  # TAUDT_FIXED
udt.total_size = binary_size
udt.taudt_bits |= 128  # TAUDT_CPPOBJ

# Add members
for off_str in sorted(members, key=lambda x: int(x.split('_')[0])):
    minfo = members[off_str]
    off = int(off_str.split('_')[0])
    mname = minfo["name"]
    mtype_str = minfo["type"]
    f.write(f"  +{off} {mname}: {mtype_str}")
    
    # Parse type
    tinfo = ida_typeinf.tinfo_t()
    # Try parse_decl for function pointer types
    if '(' in mtype_str and '*' in mtype_str:
        import re
        _fp = re.search(r'\(([^)]*\*)\)\s*\(', mtype_str)
        if _fp:
            _inner = _fp.group(1)
            _star_pos = _inner.rfind('*')
            _decl = mtype_str[:_fp.start(1)] + _inner[:_star_pos] + '*__x' + mtype_str[_fp.end(1):] + ';'
            r = ida_typeinf.parse_decl(tinfo, til, _decl, 0)
            if r is not None:
                f.write(f" -> parse_decl OK, size={tinfo.get_size()}\n")
            else:
                f.write(f" -> parse_decl FAILED, falling back\n")
                # Fallback to int
                tinfo.create_simple_type(ida_typeinf.BTF_INT32)
                f.write(f"  (fallback to int)\n")
        else:
            f.write(f"  (no fp match, using int)\n")
            tinfo.create_simple_type(ida_typeinf.BTF_INT32)
    else:
        # Simple type
        s = mtype_str
        arr_sizes = []
        import re
        while True:
            m = re.search(r'\[(\d+)\]$', s)
            if not m: break
            arr_sizes.insert(0, int(m.group(1)))
            s = s[:m.start()].strip()
        ptr_count = 0
        while s.endswith('*'):
            ptr_count += 1
            s = s.rstrip('*').strip()
        if s == 'int':
            tinfo.create_simple_type(ida_typeinf.BTF_INT32)
        elif s == 'DWORD' or s == 'unsigned long':
            tinfo.create_simple_type(ida_typeinf.BTF_UINT32)
        elif s == 'float':
            tinfo.create_simple_type(ida_typeinf.BTF_FLOAT)
        elif s == 'void' and ptr_count > 0:
            void_t = ida_typeinf.tinfo_t()
            void_t.create_simple_type(ida_typeinf.BTF_VOID)
            tinfo.create_ptr(void_t)
        else:
            tinfo.create_simple_type(ida_typeinf.BTF_INT32)
        f.write(f" -> simple, size={tinfo.get_size()}\n")
    
    member_size = tinfo.get_size()
    
    m = ida_typeinf.udt_member_t()
    m.name = mname
    m.offset = off * 8
    m.size = member_size * 8
    m.type = tinfo
    udt.push_back(m)
    
f.write(f"\nUDT: {udt.size()} members, total_size={udt.total_size}\n")
for i in range(udt.size()):
    m = udt[i]
    f.write(f"  +{m.offset//8}: {m.name} size={m.size//8} type={m.type.dstr()}\n")

# Create struct
result = ida_typeinf.tinfo_t()
udt_flag = ida_typeinf.BTF_STRUCT
ok = result.create_udt(udt, udt_flag)
f.write(f"\ncreate_udt: ok={ok}\n")
if ok:
    f.write(f"  get_size: {result.get_size()}\n")
    f.write(f"  dstr: {result.dstr()}\n")
else:
    f.write(f"  FAILED\n")

f.close()
