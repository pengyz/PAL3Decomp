import ida_typeinf
import idc
out = []

def main():
    til = ida_typeinf.get_idati()
    t = ida_typeinf.tinfo_t()
    ok = t.get_named_type(til, 'UIScene')
    out.append('UIScene in til: %s' % bool(ok))
    if not ok:
        return
    out.append('size: %s' % t.get_size())
    try:
        ud = ida_typeinf.udt_type_data_t()
        if t.get_udt_details(ud):
            out.append('members: %d' % ud.size())
            for i in range(ud.size()):
                m = ud[i]
                if 'vf' in m.name.lower():
                    out.append('vft member: %s : %s' % (m.name, str(m.type)[:60]))
    except Exception as e:
        out.append('udt exc: %s' % str(e)[:80])

try:
    main()
except Exception as _e:
    import traceback
    out.append('EXC: %s' % str(_e)[:120])
    out.append(traceback.format_exc()[-400:])
open(__file__.replace('.py', '_out.txt'), 'w', encoding='utf-8').write('\n'.join(out))
idc.qexit(0)
