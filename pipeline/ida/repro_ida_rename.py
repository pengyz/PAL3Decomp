import ida_auto, idc, ida_name, ida_segment, ida_bytes
ida_auto.auto_wait()

# 找一个 dword_ 自动名数据地址(.data段)
seg = ida_segment.get_segm_by_name('.data')
ea = None
for a in range(seg.start_ea, seg.end_ea, 4):
    n = ida_name.get_name(a)
    if n and n.startswith('dword_'):
        ea = a
        break
name0 = ida_name.get_name(ea)
print('REPRO: 测试地址 0x%x 当前名=%r' % (ea, name0))

# 1. SetType 类型名(无变量名)
idc.SetType(ea, 'HANDLE')
n1 = ida_name.get_name(ea)
print('REPRO: SetType("HANDLE") 后名=%r (机制1=改名为类型名?)' % n1)

# 2. 同址 SetType 带变量名声明
idc.SetType(ea, 'HANDLE myTestVar')
n2 = ida_name.get_name(ea)
print('REPRO: SetType("HANDLE myTestVar") 后名=%r (机制2=声明名生效)' % n2)

# 3. 还原(清类型+还原名)
idc.SetType(ea, '')
ida_name.set_name(ea, name0, ida_name.SN_AUTO | ida_name.SN_NOCHECK)
print('REPRO: 还原完成')
print('REPRO-DONE')
