import ida_auto, idc, ida_typeinf, ida_name
ida_auto.auto_wait()
_tif = ida_typeinf.tinfo_t()
def get_tinfo_str(ea):
    _t = ida_typeinf.tinfo_t()
    if ida_nalt.get_tinfo(_t, ea):
        return str(_t)
    return '(无类型)'
import json
ea = 0x00445cd0
print('TEST: ea=0x%x 当前名=%s' % (ea, idc.get_name(ea)))
print('TEST: 当前tinfo=%s' % get_tinfo_str(ea)[:100])
# 尝试1: void __thiscall()
r1 = idc.SetType(ea, 'void __thiscall()')
print('TEST: SetType rc=%s tinfo=%s' % (r1, get_tinfo_str(ea)[:80]))
# 尝试2: 不带cc的void()
r2 = idc.SetType(ea, 'void()')
print('TEST: SetType rc=%s tinfo=%s' % (r2, get_tinfo_str(ea)[:80]))
# 尝试3: 声明带函数名
r3 = idc.SetType(ea, 'void __thiscall Render()')
print('TEST: SetType rc=%s tinfo=%s' % (r3, get_tinfo_str(ea)[:80]))
print('TEST-DONE')
