"""[L-VAR 探针] 新进程 fresh decompile 验证 user lvar 跨进程持久化。"""
import ida_funcs
import ida_hexrays
import idc

func = ida_funcs.get_func(0x41CC50)
cfunc = ida_hexrays.decompile(func)
decl = None
for ln in str(cfunc).split('\n'):
    if ' v7' in ln and ';' in ln:
        decl = ln.strip()
        break
print('[probe] v7 声明: %r' % decl)
out = open(__file__.replace('.py', '_out.txt'), 'w')
out.write(repr(decl))
out.close()
idc.qexit(0)
