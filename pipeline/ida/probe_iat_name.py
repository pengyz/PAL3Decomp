import ida_name, ida_typeinf, idc
ea = 0x57C068
out = []
out.append('name: %s' % (ida_name.get_name(ea) or '?'))
t = ida_typeinf.tinfo_t()
if ida_nalt_ok := True:
    import ida_nalt
    if ida_nalt.get_tinfo(t, ea):
        out.append('type: %s' % str(t)[:80])
    else:
        out.append('type: (无)')
open(__file__.replace('.py', '_out.txt'), 'w', encoding='utf-8').write('\n'.join(out))
idc.qexit(0)
