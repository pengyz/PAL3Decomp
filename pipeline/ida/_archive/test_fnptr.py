import ida_typeinf
import re
import sys

f = open("/tmp/fnptr_test.txt", "w")

til = ida_typeinf.get_idati()

f.write("ida_typeinf members with decl/parse:\n")
for x in dir(ida_typeinf):
    if 'decl' in x.lower() or 'parse' in x.lower() or 'import' in x.lower():
        f.write(f"  {x}\n")

# Build decl
s = 'int (__thiscall *)(void *, unsigned long)'
_fp = re.search(r'\(([^)]*\*)\)\s*\(', s)
if _fp:
    _inner = _fp.group(1)
    _star_pos = _inner.rfind('*')
    _decl = s[:_fp.start(1)] + _inner[:_star_pos] + '*__x' + s[_fp.end(1):] + ';'
    f.write(f"decl: {_decl}\n")

# Try tinfo.parse_decl
t = ida_typeinf.tinfo_t()
try:
    ok = t.parse_decl(til, _decl, 0)
    f.write(f"t.parse_decl(til, decl, 0) = {ok}, size={t.get_size()}\n")
except AttributeError as e:
    f.write(f"t.parse_decl not available: {e}\n")

# Try global parse_decl
if hasattr(ida_typeinf, 'parse_decl'):
    t2 = ida_typeinf.tinfo_t()
    try:
        ok2 = ida_typeinf.parse_decl(t2, til, _decl, 0)
        f.write(f"ida_typeinf.parse_decl(t, til, decl, 0) = {ok2}\n")
    except Exception as e:
        f.write(f"ida_typeinf.parse_decl error: {e}\n")

# Try simpler: create function pointer manually
ft = ida_typeinf.tinfo_t()
ft.create_simple_type(ida_typeinf.BTF_INT32)
f.write(f"int type created: ok\n")

# Try parse_decl on simple types
for test_decl in ["int __x;", "void *__x;", "int (*__x)(void);"]:
    t3 = ida_typeinf.tinfo_t()
    try:
        ok3 = t3.parse_decl(til, test_decl, 0)
        f.write(f"  '{test_decl}' -> ok={ok3} size={t3.get_size()}\n")
    except Exception as e:
        f.write(f"  '{test_decl}' -> error: {e}\n")

f.write("Done\n")
f.close()
