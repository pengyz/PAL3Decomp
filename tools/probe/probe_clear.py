import sys
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
import idaapi, ida_name, ida_ua, idc

db = idapro.open_database("/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64", True)
idaapi.auto_wait()
with open('/tmp/pool_map.txt', 'w') as f:
    # ClearAttackSequence (0x5193d0) — 池遍历主嫌疑
    for start, end, label in ((0x005193d0, 0x005193d0 + 0x300, 'ClearAttackSequence'),
                              (0x0044bda0, 0x0044bda0 + 0x200, 'UICaption_DestroyAll(对照)')):
        fn = ida_funcs.get_func(start)
        end2 = fn.end_ea if fn else end
        f.write('== %s 0x%08x..0x%08x\n' % (label, start, end2))
        e = start
        n = 0
        while e < end2 and n < 300:
            mnem = ida_ua.print_insn_mnem(e)
            if mnem == 'call':
                tgt = idc.get_operand_value(e, 0)
                nm = ida_name.get_name(tgt) or ''
                f.write('  call 0x%08x -> 0x%08x %s\n' % (e, tgt, str(nm)[:56]))
            e = idc.next_head(e)
            n += 1
idapro.close_database(False)
