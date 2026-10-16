import ida_typeinf
import re

f = open("/tmp/fnptr2_test.txt", "w")
til = ida_typeinf.get_idati()

test_cases = [
    "int (__thiscall *__x)(void *, unsigned long);",
    "int (*__x)(void *, unsigned long);",
    "int (__cdecl *__x)(void *, unsigned long);",
    "int (__stdcall *__x)(void *, unsigned long);",
]

for decl in test_cases:
    t = ida_typeinf.tinfo_t()
    try:
        r = ida_typeinf.parse_decl(t, til, decl, 0)
        sz = t.get_size()
        f.write(f"  '{decl}': ok={r is not None}, size={sz}\n")
    except Exception as e:
        f.write(f"  '{decl}': EXCEPTION {e}\n")

# Test creating struct with function pointer member
udt = ida_typeinf.udt_type_data_t()
t_int = ida_typeinf.tinfo_t()
t_int.create_simple_type(ida_typeinf.BTF_INT32)

t_fn = ida_typeinf.tinfo_t()
ida_typeinf.parse_decl(t_fn, til, "int (*__x)(void *, unsigned long);", 0)
f.write(f"\nfnptr type size = {t_fn.get_size()}\n")

m1 = ida_typeinf.udt_member_t()
m1.name = "a"
m1.offset = 0
m1.size = 32
m1.type = t_int
udt.push_back(m1)

m2 = ida_typeinf.udt_member_t()
m2.name = "b"
m2.offset = 32
m2.size = 32
m2.type = t_int
udt.push_back(m2)

m3 = ida_typeinf.udt_member_t()
m3.name = "fn"
m3.offset = 64
m3.size = 32
m3.type = t_fn
udt.push_back(m3)

udt.taudt_bits = 1024
udt.total_size = 12

result = ida_typeinf.tinfo_t()
udt_flag = ida_typeinf.BTF_STRUCT
ok = result.create_udt(udt, udt_flag)
f.write(f"struct create_udt: ok={ok}, size={result.get_size()}\n")

f.close()
