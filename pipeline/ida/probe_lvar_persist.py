"""[L-VAR 探针v2] fresh decompile 打印 v7 全部相关行(声明+赋值)。"""
import ida_funcs
import ida_hexrays
import idc

func = ida_funcs.get_func(0x41CC50)
cfunc = ida_hexrays.decompile(func)
lines = [l.strip() for l in str(cfunc).split('\n') if 'v7' in l]
out = open(__file__.replace('.py', '_out.txt'), 'w', encoding='utf-8')
out.write('\n'.join(lines))
out.close()
idc.qexit(0)
