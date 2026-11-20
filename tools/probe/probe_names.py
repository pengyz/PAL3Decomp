import sys
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
import idaapi, ida_name, ida_funcs

db = idapro.open_database("/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64", True)
idaapi.auto_wait()
with open('/tmp/names_out.txt', 'w') as f:
    for ea, label in ((0x004c8950, 'cand_CEffgbParticle_1'), (0x004c87a0, 'cand__CEffgbParticle'),
                      (0x004c9540, 'cand_CEffgbParticle_0'), (0x004cb340, 'cand_complete_dtor')):
        raw = ida_name.get_name(ea) or '<noname>'
        dem = ida_name.demangle_name(raw, 0) or ''
        fn = ida_funcs.get_func(ea)
        f.write('%s 0x%08x raw=%r dem=%r func=%s start=%s\n' % (
            label, ea, raw, str(dem)[:60], 'yes' if fn else 'NO',
            hex(fn.start_ea) if fn else '-'))
    # CEffgbParticle_0(0x4c87a0)体内call目标真名
    import ida_ua, idc
    e = 0x004c87a0
    for i in range(12):
        if ida_ua.print_insn_mnem(e) == 'call':
            tgt = idc.get_operand_value(e, 0)
            f.write('CALL@0x%x -> 0x%08x name=%r\n' % (e, tgt, ida_name.get_name(tgt)))
        e = idc.next_head(e)
idapro.close_database(False)
