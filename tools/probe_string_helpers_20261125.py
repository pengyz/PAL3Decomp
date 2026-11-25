#!/usr/bin/env python3
"""probe_string_helpers_20261125.py — string helper 函数体布局指纹 → 类身份裁决。
F1: _Eos/_Grow/max_size/_Tidy/_Split/_Freeze 全地址 + 函数体 (布局指纹)
F2: String::Assign 0x4326a0 体 (游戏自有类布局对照)
F3: 各 helper 的调用者计数
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils, ida_bytes

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_string_helpers_20261125.json'
report = {}

pats = {
    '_Eos':   r'\?_Eos@',
    '_Grow':  r'\?_Grow@',
    'max_size': r'\?max_size@\$?basic_string',
    '_Tidy':  r'\?_Tidy@',
    '_Split': r'\?_Split@',
    '_Freeze': r'\?_Freeze@',
    '_Copy':  r'\?_Copy@',
    'String.Assign': r'\?Assign@String@@',
}

def body(ea, max_ins=10):
    f = ida_funcs.get_func(ea)
    sz = (f.end_ea - f.start_ea) if f else 16
    out, cur = [], ea
    for _ in range(max_ins):
        if cur == idc.BADADDR or cur >= ea + sz:
            break
        out.append((idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip())
        cur = idc.next_head(cur, ea + sz + 16)
    return {'size': sz, 'bytes': (ida_bytes.get_bytes(ea, min(sz, 40)) or b'').hex(),
            'disasm': out}

for key, pat in pats.items():
    hits = []
    for ea, name in idautils.Names():
        if re.search(pat, name):
            f = ida_funcs.get_func(ea)
            ncalls = 0
            if f:
                ncalls = sum(1 for _ in idautils.CodeRefsTo(f.start_ea, 0))
            hits.append({'ea': hex(ea), 'name': name[:70], 'callers': ncalls,
                         'body': body(ea, 9)})
        if len(hits) >= 4:
            break
    report[key] = hits

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
for key, hits in report.items():
    print('=== %s ===' % key)
    for h in hits:
        print('  %s %s callers=%d size=%d' % (h['ea'], h['name'][:60], h['callers'], h['body']['size']))
        for t in h['body']['disasm'][:7]:
            print('    %s' % t)
idapro.close_database(False)
