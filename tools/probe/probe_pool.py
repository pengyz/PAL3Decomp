import sys
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
import idaapi, ida_name, ida_ua, idc

db = idapro.open_database("/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64", True)
idaapi.auto_wait()
with open('/tmp/pool_map.txt', 'w') as f:
    # CCBUI 两个 ~CCBUI 地址的函数体反汇编: 提取 call 目标+调用前 lea/add 偏移
    for ea, label in ((0x00525520, 'CCBUI_dtor_A'), (0x00519360, 'CCBUI_dtor_B')):
        fn = ida_funcs.get_func(ea)
        if not fn:
            f.write('%s: no func\n' % label); continue
        f.write('== %s 0x%08x..0x%08x (%d insns)\n' % (label, fn.start_ea, fn.end_ea, (fn.end_ea-fn.start_ea)//4))
        e = fn.start_ea
        n = 0
        while e < fn.end_ea and n < 200:
            mnem = ida_ua.print_insn_mnem(e)
            txt = idaapi.generate_disasm_line(e, 0) or ''
            if mnem == 'call':
                tgt = idc.get_operand_value(e, 0)
                nm = ida_name.get_name(tgt) or ''
                f.write('  call 0x%08x -> 0x%08x %s\n' % (e, tgt, str(nm)[:50]))
            e = idc.next_head(e)
            n += 1
idapro.close_database(False)
