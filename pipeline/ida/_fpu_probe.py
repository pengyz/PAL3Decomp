import traceback
LOG = r'D:\workspace\PAL3Decomp\pipeline\_logs\fpu_probe_result.txt'
_out = []
def flush():
    try: open(LOG, 'w', encoding='utf-8').write('\n'.join(_out))
    except Exception: pass
def log(s):
    _out.append(str(s)); flush()
try:
    import ida_auto, ida_hexrays, ida_pro
    ida_auto.auto_wait()
    ida_hexrays.init_hexrays_plugin()
    EA = 0x40C7D0
    cf = ida_hexrays.decompile(EA)
    log('=== vdloc_t attributes ===')
    lv0 = cf.lvars[0]
    log('  ' + ', '.join(a for a in dir(lv0.location) if not a.startswith('_')))
    log('=== Q1 lvars ===')
    target = None
    for lv in cf.lvars:
        loc = lv.location
        if loc.is_stkoff():
            desc = 'stkoff=%s' % loc.stkoff()
        elif loc.is_reg():
            r1 = None
            try: r1 = loc.reg1()
            except Exception as e: r1 = 'err:%s' % e
            desc = 'reg1=%s' % r1
        else:
            desc = 'other'
        log('  %-10s %-30s %s w=%s' % (lv.name, lv.type().dstr() if lv.type() else '?', desc, lv.width))
        if lv.name == 'v2':
            target = lv
    if target is None:
        log('v2 NOT FOUND')
    else:
        import ida_typeinf
        tif = ida_typeinf.tinfo_t()
        okp = ida_typeinf.parse_decl(tif, ida_typeinf.get_idati(), 'float __lv;', ida_typeinf.PT_SIL)
        oks = target.set_lvar_type(tif) if okp else False
        log('=== Q2 set_lvar_type(float): parse=%s set=%s ===' % (bool(okp), oks))
        if oks:
            cf2 = ida_hexrays.decompile(EA)
            log('=== Q3 re-render ===')
            for ln in str(cf2).split('\n'):
                if 'v2' in ln or '32.0' in ln or 'Scale' in ln or 'height' in ln:
                    log('  ' + ln)
except Exception:
    log('[EXC] ' + traceback.format_exc())
flush()
ida_pro.qexit(0)
