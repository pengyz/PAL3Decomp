#!/usr/bin/env python3
"""音频方法调用点 ASM 全窗 — 验证接收者是否 sub-object (lea ecx,[reg+K])"""
import sys, json
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_audio_callsite_asm_20261125.json'
report = {}
for nm, ea in (('GetAudioManager', 0x53e500), ('PlayCPKStream', 0x53ea80)):
    wins = []
    for i, site in enumerate(idautils.CodeRefsTo(ea, 0)):
        if i >= 3:
            break
        seq, cur = [], site
        for _ in range(14):
            p = idc.prev_head(cur, 0)
            if p == idc.BADADDR:
                break
            t = (idc.generate_disasm_line(p, 0) or '').split(';')[0].strip()
            seq.append('%s  %s' % (hex(p), t))
            cur = p
        wins.append({'site': hex(site), 'window': list(reversed(seq))})
    report[nm] = wins
    print('=== %s ===' % nm)
    for w in wins[:2]:
        print('-- site', w['site'])
        for line in w['window']:
            print('   ', line)
json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
idapro.close_database(False)
