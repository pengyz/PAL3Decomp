import ida_typeinf, idc
out = []
til = ida_typeinf.get_idati()
variants = [
    'void __thiscall(gbVec3D *, float, float, float);',
    'void (__thiscall *)(gbVec3D *, float, float, float);',
    'void (gbVec3D *)(float, float, float);',
    'void (__stdcall *)(void *, float, float, float);',
    'int (int, int);',
]
for v in variants:
    tif = ida_typeinf.tinfo_t()
    try:
        ok = ida_typeinf.parse_decl(tif, til, v, ida_typeinf.PT_SIL)
        out.append('%r -> %s' % (v, bool(ok)))
    except Exception as e:
        out.append('%r EXC %s' % (v, str(e)[:60]))
open(__file__.replace('.py', '_out.txt'), 'w', encoding='utf-8').write('\n'.join(out))
idc.qexit(0)
