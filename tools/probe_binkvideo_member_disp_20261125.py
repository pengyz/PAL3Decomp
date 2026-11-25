#!/usr/bin/env python3
"""W2 成员调和: gbBinkVideo 27 迁移方法体 this-form disp 普查 → 音频/视频域真偏移"""
import sys, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs

gb = json.load(open('data/annotations/structs/gbBinkVideo.json', encoding='utf-8'))
CPK1_LO, CPK1_HI = 0x10, 0x10 + 0xE01BC
CPK2_LO, CPK2_HI = 0xE01CC, 0xE01CC + 0xE01BC
OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_binkvideo_member_disp_20261125.json'

result = {}
for a, m in (gb.get('methods') or {}).items():
    ea = int(a, 16)
    nm = str(m.get('name') or '?')
    f = ida_funcs.get_func(ea)
    if not f:
        continue
    disp = collections.Counter()
    cur = f.start_ea
    n = 0
    while cur < f.end_ea and n < 2500:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        mm = re.search(r'\[(?:e[a-z]{2})\+([0-9A-Fa-f]{1,8})h?\]', t)
        if mm:
            off = int(mm.group(1), 16)
            if off < 0x400000:
                disp[off] += 1
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    # 分类: 头域(<0x10) / CPK1区内 / CPK2区内 / CPK后(>=0x1C0388)
    head = sorted(o for o in disp if o < 0x10)
    in_cpk1 = sorted(o for o in disp if CPK1_LO <= o < CPK1_HI)
    in_cpk2 = sorted(o for o in disp if CPK2_LO <= o < CPK2_HI)
    after = sorted(o for o in disp if o >= CPK2_HI)
    result[nm] = {'ea': hex(ea), 'head': [hex(o) for o in head][:8],
                  'in_cpk1_n': len(in_cpk1), 'in_cpk1_max': hex(max(in_cpk1)) if in_cpk1 else None,
                  'in_cpk2_n': len(in_cpk2), 'after': [hex(o) for o in after][:10],
                  'disp_all_sample': [hex(o) for o in sorted(disp)[:20]]}

json.dump(result, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
for nm, r in result.items():
    print('%-22s head=%s cpk1=%d(max %s) cpk2=%d after=%s' % (
        nm, r['head'][:4], r['in_cpk1_n'], r['in_cpk1_max'], r['in_cpk2_n'], r['after'][:5]))
idapro.close_database(False)
