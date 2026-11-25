#!/usr/bin/env python3
"""probe_crt_leak_and_light_20261125.py — RC4-CRT 泄漏 + RC2-light-enum 双族取证。

三问:
  Q1 codecvt 族: 谁在调 do_always_noconv(thunk 链)? IDB 类型从哪来(函数签名 this 型)?
  Q2 _Eos 族: IDB callee 函数类型(nargs)? 调用点 push 形态?
  Q3 light 族: gbLightObj::Init IDB 签名参数型 + til 枚举 LIGHT_TYPE/LGT_TYPE 成员值
              + 5 调用点 raw push 常量。
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, ida_typeinf, ida_nalt, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_crt_leak_and_light_20261125.json'
report = {}

def fn_type_dump(ea):
    tif = ida_typeinf.tinfo_t()
    ok = ida_nalt.get_tinfo(tif, ea)
    return str(tif) if ok and not tif.empty() else None

def callers_of(name_pat):
    hits = []
    for ea, name in idautils.Names():
        if re.search(name_pat, name):
            f = ida_funcs.get_func(ea)
            crefs = []
            if f:
                for xr in idautils.CodeRefsTo(f.start_ea, 1):
                    cf = ida_funcs.get_func(xr)
                    cn = idc.get_func_name(cf.start_ea) if cf else '?'
                    crefs.append((hex(xr), cn))
            hits.append({'ea': hex(ea), 'name': name, 'type': fn_type_dump(ea),
                         'callers': crefs[:24], 'caller_n': len(crefs)})
    return hits

# ---- Q1 codecvt 族 ----
report['codecvt'] = callers_of(r'do_always_noconv')

# ---- Q2 _Eos 族 ----
report['eos'] = callers_of(r'_Eos@basic_string|_Eos@string')

# ---- Q3 light 族 ----
init_eas = []
for ea, name in idautils.Names():
    if re.search(r'\?Init@gbLightObj@@', name):
        init_eas.append((ea, name))
report['init_fns'] = [{'ea': hex(ea), 'name': n, 'type': fn_type_dump(ea)} for ea, n in init_eas]

# til 枚举成员: 枚举 LIGHT_TYPE / LGT_TYPE
til = ida_typeinf.get_idati()
report['enums'] = {}
for ename in ('LIGHT_TYPE', 'LGT_TYPE'):
    tid = ida_typeinf.get_type_ordinal(til, ename)
    info = {'ordinal': tid}
    if tid:
        tif = ida_typeinf.tinfo_t()
        if tif.get_numbered_type(til, tid) and tif.is_enum():
            info['decl'] = tif._print(None, ida_typeinf.PRTYPE_MULTI | ida_typeinf.PRTYPE_TYPE)
            info['size'] = tif.get_size()
    report['enums'][ename] = info

# 5 调用点: gbLightObj::Init 的调用者 + 回溯 push 常量
def backtrack_push(call_ea):
    seq = []
    cur = call_ea
    for _ in range(8):
        cur = idc.prev_head(cur, 0)
        if cur == idc.BADADDR:
            break
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        t = t.split(';')[0].strip()
        seq.append(t)
        if t.startswith('call'):
            break
    return seq

init_callers = []
for ea, n in init_eas:
    f = ida_funcs.get_func(ea)
    if not f:
        continue
    for xr in idautils.CodeRefsTo(f.start_ea, 1):
        init_callers.append({'site': hex(xr), 'caller': idc.get_func_name(ida_funcs.get_func(xr).start_ea),
                             'seq': backtrack_push(xr)})
report['init_callers'] = init_callers

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
print('codecvt fn 数: %d' % len(report['codecvt']))
for h in report['codecvt']:
    print('  %s %s type=%s callers=%d' % (h['ea'], h['name'][:50], h['type'], h['caller_n']))
print('eos fn 数: %d' % len(report['eos']))
for h in report['eos'][:6]:
    print('  %s %s type=%s callers=%d' % (h['ea'], h['name'][:44], h['type'], h['caller_n']))
print('Init: %s' % json.dumps(report['init_fns'], ensure_ascii=False))
print('til 枚举: %s' % json.dumps(report['enums'], ensure_ascii=False)[:600])
for c in report['init_callers']:
    print('  caller %s @ %s seq=%s' % (c['caller'], c['site'], c['seq'][-4:]))
idapro.close_database(False)
