"""程序化构造函数型探针（绕 parse_decl）。"""
import ida_typeinf, idc
out = []
til = ida_typeinf.get_idati()
# gbVec3D ret + 3 float args
ret = ida_typeinf.tinfo_t()
ok_ret = ret.get_named_type(til, 'gbVec3D')
out.append('gbVec3D named: %s' % bool(ok_ret))
fdata = ida_typeinf.func_type_data_t()
fdata.rettype = ida_typeinf.tinfo_t()  # void
fdata.cc = ida_typeinf.CM_CC_THISCALL if hasattr(ida_typeinf, 'CM_CC_THISCALL') else ida_typeinf.CT_PRIV
args = []
for tname in ('gbVec3D *', 'float', 'float', 'float'):
    t = ida_typeinf.tinfo_t()
    if tname.endswith('*'):
        base = ida_typeinf.tinfo_t()
        okb = base.get_named_type(til, tname[:-2])
        t.create_ptr(base)
        out.append('ptr %s: base=%s' % (tname, bool(okb)))
    else:
        ok = t.get_named_type(til, tname)
        out.append('prim %s: %s' % (tname, bool(ok)))
    args.append(t)
fdata.push_back(ida_typeinf.funcarg_t()) if hasattr(ida_typeinf, 'funcarg_t') else None
# 逐参构造
fdata = ida_typeinf.func_type_data_t()
fdata.cc = 4  # CM_CC_THISCALL
for t in args:
    fa = ida_typeinf.funcarg_t()
    fa.type = t
    fdata.push_back(fa)
ftif = ida_typeinf.tinfo_t()
okf = ftif.create_func(fdata)
out.append('create_func: %s (%s)' % (bool(okf), str(ftif)[:60]))
ptr = ida_typeinf.tinfo_t()
ptr.create_ptr(ftif)
out.append('fn-ptr: %s (%s)' % (True, str(ptr)[:70]))
open(__file__.replace('.py', '_out.txt'), 'w', encoding='utf-8').write('\n'.join(out))
idc.qexit(0)
