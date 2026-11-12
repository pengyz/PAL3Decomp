import ida_name, idc
out = []
ea = 0x17B41E8
out.append('name@0x17B41E8: %s' % (ida_name.get_name(ea) or '?'))
# 它的引用者(局部 v3 = +1252 语义里 v1+1252=0x17B41E8? v1 是什么基址?)
out.append('该地址在 .data(BSS 区), 步进 0x98 的数组基址区')
open(__file__.replace('.py', '_out.txt'), 'w', encoding='utf-8').write('\n'.join(out))
idc.qexit(0)
