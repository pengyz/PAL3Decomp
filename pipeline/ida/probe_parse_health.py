import ida_typeinf, idc
out = []
# ① 当前 til
til = ida_typeinf.get_idati()
tif = ida_typeinf.tinfo_t()
ok = ida_typeinf.parse_decl(tif, til, 'int (int, int);', ida_typeinf.PT_SIL)
out.append('当前til int(int,int): %s' % bool(ok))
# ② 新建独立 til
til2 = ida_typeinf.get_idati()
out.append('get_idati 幂等: %s' % (til2 == til))
# ③ tinfo_t 直接构造函数型(不经 parse_decl)
import ida_idd
out.append('ida_typeinf 有 create_ptr: %s' % hasattr(ida_typeinf.tinfo_t(), 'create_ptr'))
# ④ 零参函数
tif2 = ida_typeinf.tinfo_t()
ok2 = ida_typeinf.parse_decl(tif2, til, 'void f(void);', ida_typeinf.PT_SIL)
out.append('void f(void): %s' % bool(ok2))
# ⑤ 数据型
tif3 = ida_typeinf.tinfo_t()
ok3 = ida_typeinf.parse_decl(tif3, til, 'unsigned long x;', ida_typeinf.PT_SIL)
out.append('数据型 ulong: %s' % bool(ok3))
open(__file__.replace('.py', '_out.txt'), 'w', encoding='utf-8').write('\n'.join(out))
idc.qexit(0)
