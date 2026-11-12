import ida_name, idautils, idc
out = []
# 全局搜名为 a2Pol* 的地址
for seg_start in (0x56A000, 0x580000, 0xBF0000):
    pass
ea = ida_name.get_name_ea(0xFFFFFFFF if False else 0xBFF00000, 'a2Pol')
# 直接遍历 .data/.rdata 名字
import ida_segment
for i in range(ida_segment.get_segm_qty()):
    seg = ida_segment.getnseg(i)
    s = ida_segment.get_segm_name(seg)
    if s not in ('.rdata', '.data'): continue
    cur = seg.start_ea
    found = []
    while cur < seg.end_ea and len(found) < 3:
        n = ida_name.get_name(cur)
        if n and '2Pol' in n:
            found.append((hex(cur), n))
        cur += 1
    out.append('%s: %s' % (s, found))
open(__file__.replace('.py', '_out.txt'), 'w', encoding='utf-8').write('\n'.join(out))
idc.qexit(0)
