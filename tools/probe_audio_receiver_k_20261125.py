#!/usr/bin/env python3
"""音频方法接收者 K-offset 解码: 调用点回溯 lea/add ecx 形 → 子对象基址判定"""
import sys, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_audio_receiver_k_20261125.json'
targets = {'GetAudioManager': 0x53e500, 'AudioUpdate': 0x53e490, 'PlayCPKStream': 0x53ea80,
           'InitCPK': 0x53c340, 'PlaySceneMusic': None}
# PlaySceneMusic 地址从注解取
import json as _j
gb = _j.load(open('data/annotations/structs/gbBinkVideo.json', encoding='utf-8'))
for a, m in (gb.get('methods') or {}).items():
    if m.get('name') == 'PlaySceneMusic':
        targets['PlaySceneMusic'] = int(a, 16)

report = {}
for nm, ea in targets.items():
    if ea is None:
        continue
    ks = collections.Counter()
    forms = collections.Counter()
    for site in idautils.CodeRefsTo(ea, 0):
        cur = site
        got = None
        for _ in range(12):
            p = idc.prev_head(cur, 0)
            if p == idc.BADADDR:
                break
            t = (idc.generate_disasm_line(p, 0) or '').split(';')[0].strip()
            m1 = re.match(r'mov\s+ecx,\s*(\w+)$', t)
            m2 = re.match(r'lea\s+ecx,\s*\[e[a-z]{2}\+([0-9A-Fa-f]+)h?\]', t)
            m3 = re.match(r'add\s+ecx,\s*([0-9A-Fa-f]+)h?$', t)
            if m1 and m1.group(1).startswith('0'):
                got = ('imm', int(m1.group(1), 16)); break
            if m2:
                got = ('lea+K', int(m2.group(1), 16)); break
            if m3:
                got = ('add+K', int(m3.group(1), 16)); break
            if m1:
                got = ('reg', m1.group(1)); break
            if t.startswith('call'):
                break
            cur = p
        if got:
            forms[got[0]] += 1
            if got[0] in ('lea+K', 'add+K'):
                ks[got[1]] += 1
            elif got[0] == 'imm':
                ks[('imm', hex(got[1]))] += 1
    report[nm] = {'forms': dict(forms), 'k_values': {str(k): v for k, v in ks.most_common(6)}}
    print('%-16s forms=%s K=%s' % (nm, dict(forms), dict(ks.most_common(4))))

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
idapro.close_database(False)
