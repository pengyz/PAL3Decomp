#!/usr/bin/env python3
"""round3: _Eos 函数体+xref / Init 5 站 push 常量 / legacy 枚举成员 / codecvt 站窗"""
import sys, json
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, ida_bytes, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_crt_round3_20261125.json'
report = {}

def heads(ea, n):
    out, cur = [], ea
    for _ in range(n):
        out.append(cur)
        cur = idc.next_head(cur, ea + 64)
        if cur == idc.BADADDR:
            break
    return out

def body(ea, n=6):
    f = ida_funcs.get_func(ea)
    sz = (f.end_ea - f.start_ea) if f else 16
    return {'size': sz,
            'bytes': (ida_bytes.get_bytes(ea, min(sz, 24)) or b'').hex(),
            'disasm': [(idc.generate_disasm_line(h, 0) or '').split(';')[0].strip() for h in heads(ea, n)]}

def win(site_ea, back=6, fwd=2):
    cur = site_ea
    starts = [cur]
    for _ in range(back):
        p = idc.prev_head(cur, 0)
        if p == idc.BADADDR:
            break
        starts.append(p)
        cur = p
    seq = []
    for h in reversed(starts):
        seq.append('%s  %s' % (hex(h), (idc.generate_disasm_line(h, 0) or '').split(';')[0].strip()))
    cur = site_ea
    for _ in range(fwd):
        cur = idc.next_head(cur, 0)
        if cur == idc.BADADDR:
            break
        seq.append('%s  %s' % (hex(cur), (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()))
    return seq

# E1 _Eos 0x407b30
report['eos_body'] = body(0x407b30, 8)
xr = []
for xa in idautils.XrefsTo(0x407b30, 0):
    cf = ida_funcs.get_func(xa.frm)
    xr.append({'site': hex(xa.frm), 'caller': idc.get_func_name(cf.start_ea) if cf else '?',
               'win': win(xa.frm, 4, 1)})
report['eos_xrefs'] = xr

# E2 Init 5 站 push 常量
report['init_sites'] = {}
for site in (0x405243, 0x508541, 0x508714, 0x52f147, 0x53089d):
    report['init_sites'][hex(site)] = win(site, 5, 2)

# E4 codecvt 站窗 + thunk 链体
report['codecvt_sites'] = {}
for site in (0x512678, 0x4fbd20, 0x505400):
    report['codecvt_sites'][hex(site)] = win(site, 6, 2)
report['thunks'] = {}
for t in (0x504e20, 0x505400):
    report['thunks'][hex(t)] = body(t, 2)

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print(json.dumps(report, ensure_ascii=False, indent=1)[:5200])
idapro.close_database(False)
