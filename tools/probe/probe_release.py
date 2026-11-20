import sys
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
import idaapi, ida_name, ida_ua, idc

db = idapro.open_database("/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64", True)
idaapi.auto_wait()
with open('/tmp/pool_map.txt', 'w') as f:
    e = 0x00519380
    fn = ida_funcs.get_func(e)
    end = fn.end_ea if fn else e + 0x400
    f.write('== Release 0x%08x..0x%08x\n' % (e, end))
    n = 0
    while e < end and n < 400:
        mnem = ida_ua.print_insn_mnem(e)
        txt = (idaapi.generate_disasm_line(e, 0) or '')
        if mnem == 'call':
            tgt = idc.get_operand_value(e, 0)
            nm = ida_name.get_name(tgt) or ''
            f.write('  call 0x%08x -> 0x%08x %s\n' % (e, tgt, str(nm)[:56]))
        e = idc.next_head(e)
        n += 1
idapro.close_database(False)
