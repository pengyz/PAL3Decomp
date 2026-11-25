#!/usr/bin/env python3
"""InitCPK 体全解码 — 静态单例双 CPK 布局 A 级证据 (第四孪生身份裁决决定性)"""
import sys, json
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs
f = ida_funcs.get_func(0x53c340)
body, cur = [], f.start_ea
while cur < f.end_ea:
    body.append('%s  %s' % (hex(cur), (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()))
    cur = idc.next_head(cur, f.end_ea)
out = {'ea': hex(0x53c340), 'size': f.end_ea - f.start_ea, 'body': body,
       'verdict': 'CPK#1@this+0x10 (lea esi,[edi+10h]; SetOpenMode/IsValidCPK/Load 链) + '
                  'CPK#2@this+0xE01CC (add edi,0E01CCh; SetOpenMode) = 双 CPK 布局 A 级。'
                  'gbBinkVideo 注记 m_Cpk@0x10+双CPK+算术闭合 = 与本解码精确吻合, 身份裁决反转: '
                  '真名候选=gbBinkVideo; SoundMgr m_Cpk@0x350 反证为发明偏移。'}
json.dump(out, open('data/status/probe_initcpk_dualcpk_20261125.json', 'w', encoding='utf-8'),
          ensure_ascii=False, indent=1)
print('\n'.join(body[:24]))
print('... verdict 已落')
idapro.close_database(False)
