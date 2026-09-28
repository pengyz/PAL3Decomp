import traceback, json, os
LOG = r'D:\workspace\PAL3Decomp\pipeline\_logs\fpu_probe2_result.txt'
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
    # 复现 export_full 的装载逻辑
    PROJECT_ROOT = r'D:\workspace\PAL3Decomp'
    _lvar_ann_path = os.path.join(PROJECT_ROOT, 'data', 'annotations', 'lvars.json')
    _LVAR_ANN = json.load(open(_lvar_ann_path, encoding='utf-8'))
    log('[load] keys=%s' % list(_LVAR_ANN.keys()))
    EA = 0x40C7D0
    log('[key] 0x%08X in ann: %s' % (EA, ('0x%08X' % EA) in _LVAR_ANN))
    ida_hexrays.mark_cfunc_dirty(EA)
    cf = ida_hexrays.decompile(EA)
    _ann_lvars = _LVAR_ANN.get('0x%08X' % EA)
    if _ann_lvars:
        for _spec in _ann_lvars:
            try:
                for _lv in cf.lvars:
                    _hit = False
                    if 'stkoff' in _spec and _lv.location.is_stkoff():
                        _hit = (_lv.location.stkoff() == int(_spec['stkoff']))
                    elif 'reg' in _spec and _lv.location.is_reg():
                        _hit = (str(_lv.location.reg1()) == str(_spec['reg']))
                    log('[match] spec=%s lv=%s is_reg=%s reg1=%s hit=%s' % (
                        _spec, _lv.name, _lv.location.is_reg(),
                        _lv.location.reg1() if _lv.location.is_reg() else '-', _hit))
                    if _hit:
                        import ida_typeinf
                        _tif = ida_typeinf.tinfo_t()
                        if ida_typeinf.parse_decl(_tif, ida_typeinf.get_idati(),
                                                  '%s __lv_ann;' % _spec['type'], ida_typeinf.PT_SIL):
                            ok = _lv.set_lvar_type(_tif)
                            log('[set] %s -> %s' % (_lv.name, ok))
                    if _hit:
                        break
            except Exception:
                log('[EXC-spec] ' + traceback.format_exc())
        # 渲染
        for ln in str(cf).split('\n'):
            if 'v2' in ln or '32.0' in ln or 'Scale' in ln:
                log('  R: ' + ln)
    else:
        log('[!] no ann for Render2')
except Exception:
    log('[EXC] ' + traceback.format_exc())
flush()
ida_pro.qexit(0)
