import ida_typeinf
import re

f = open("/tmp/dstr_fnptr.txt", "w")
til = ida_typeinf.get_idati()

# Test dstr for function pointer types
test_types = [
    "int (__thiscall *)(void *, unsigned long)",
    "int (*)(void *, unsigned long)",
    "int (__cdecl *)(void *, unsigned long)",
]

for s in test_types:
    t = ida_typeinf.tinfo_t()
    _fp = re.search(r'\(([^)]*\*)\)\s*\(', s)
    if _fp:
        _inner = _fp.group(1)
        _star_pos = _inner.rfind('*')
        _decl = s[:_fp.start(1)] + _inner[:_star_pos] + '*__x' + s[_fp.end(1):] + ';'
        r = ida_typeinf.parse_decl(t, til, _decl, 0)
        if r is not None:
            dstr = t.dstr()
            f.write(f"  '{s}' -> dstr='{dstr}' size={t.get_size()}\n")
        else:
            f.write(f"  '{s}' -> parse failed\n")

f.close()
