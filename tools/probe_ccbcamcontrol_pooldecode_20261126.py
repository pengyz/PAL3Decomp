#!/usr/bin/env python3
"""probe_ccbcamcontrol_pooldecode_20261126.py — CCT 任务池本体解码 v5。

m_Pool tagCCT[2000]@0x0 止于 m_bPoolInUse@0x639c0, 但 409280/2000=204.64
非整数 stride = 注解池模型存疑。全量反汇编池方法 + INI 装载器:
  InsertTaskToList@0x5075e0 / SwapTask@0x507b20 / ClearList@0x508190
  IsTaskValid@0x5081a0 / GetTaskNumInList@0x5081b0 / GetFreeSpaceInPool@0x5081c0
  InitEntries@0x44d780 / Create_8770@0x4a8770 / CCCTData_6F10@0x4a6f10
  CIniFile::LoadStructuredConfig(读 head 域装载形)
产出: 池基址/步距/元素结构/in-use 索引形态。
"""
import sys, json
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_ccbcamcontrol_pooldecode_20261126.json'
TARGETS = [
    (0x5075e0, 'InsertTaskToList', 3000),
    (0x507b20, 'SwapTask', 3000),
    (0x508190, 'ClearList', 200),
    (0x5081a0, 'IsTaskValid', 200),
    (0x5081b0, 'GetTaskNumInList', 200),
    (0x5081c0, 'GetFreeSpaceInPool', 200),
    (0x44d780, 'InitEntries', 3000),
    (0x4a8770, 'Create_8770', 2000),
    (0x4a6f10, 'CCCTData_6F10', 1500),
]
# CIniFile::LoadStructuredConfig — 找地址
import idautils
ini_ea = None
for fea in idautils.Functions():
    n = idc.get_func_name(fea)
    if 'LoadStructuredConfig' in (n or ''):
        ini_ea = fea
        break

report = {}
for ea, nm, cap in TARGETS:
    f = ida_funcs.get_func(ea)
    if not f:
        report[nm] = {'missing': True}
        continue
    lines = []
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < cap:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        lines.append('%s %s' % (hex(cur), t))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    report[nm] = {'ea': hex(ea), 'size': f.end_ea - f.start_ea, 'body': lines}
if ini_ea:
    f = ida_funcs.get_func(ini_ea)
    lines = []
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 2500:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        lines.append('%s %s' % (hex(cur), t))
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    report['LoadStructuredConfig'] = {'ea': hex(ini_ea), 'size': f.end_ea - f.start_ea, 'body': lines}

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
for nm in ('IsTaskValid', 'GetTaskNumInList', 'GetFreeSpaceInPool', 'ClearList'):
    r = report.get(nm) or {}
    if r.get('missing'): continue
    print('== %s (%s B) ==' % (nm, r['size']))
    for ln in r['body']:
        print('  ', ln)
idapro.close_database(False)
