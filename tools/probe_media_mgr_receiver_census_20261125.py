#!/usr/bin/env python3
"""probe_media_mgr_receiver_census_20261125.py — 第四孪生定谳: 三名字全方法接收者台账。
每方法全部调用点 → 回溯 mov ecx,imm32 → 分类:
  singleton(0xa3a7d8) / other-imm(其他静态实例!) / reg(寄存器/堆, 不可判)
输出: data/status/media_mgr_receiver_census_20261125.json
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/media_mgr_receiver_census_20261125.json'
SINGLETON = 0x00a3a7d8

ledger = []
for cls in ('CScreenMode', 'SoundMgr'):
    d = json.load(open('data/annotations/structs/%s.json' % cls, encoding='utf-8'))
    for a, m in (d.get('methods') or {}).items():
        ea = int(a, 16)
        nm = str(m.get('name') or '?')
        rec = {'cls': cls, 'addr': hex(ea), 'name': nm,
               'singleton': 0, 'other_imm': [], 'reg': 0, 'total': 0}
        f = ida_funcs.get_func(ea)
        if not f:
            rec['no_func'] = True
            ledger.append(rec)
            continue
        for site in idautils.CodeRefsTo(f.start_ea, 0):
            rec['total'] += 1
            # 回溯找最近的 mov ecx, imm32
            got = None
            cur = site
            for _ in range(10):
                p = idc.prev_head(cur, 0)
                if p == idc.BADADDR:
                    break
                t = (idc.generate_disasm_line(p, 0) or '').split(';')[0].strip()
                m2 = re.match(r'mov\s+ecx,\s*([0-9A-Fa-f]+)h?$', t)
                if m2:
                    got = int(m2.group(1), 16)
                    break
                if t.startswith('call'):
                    break
                cur = p
            if got == SINGLETON:
                rec['singleton'] += 1
            elif got is not None:
                rec['other_imm'].append(hex(got))
            else:
                rec['reg'] += 1
        ledger.append(rec)

json.dump(ledger, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
# 汇总
sing_all = [r for r in ledger if r['singleton'] > 0]
other_all = [r for r in ledger if r['other_imm']]
print('方法总数: %d, 收单例者 %d, 收其他imm者 %d' % (len(ledger), len(sing_all), len(other_all)))
print()
print('=== 收 0xa3a7d8 单例的方法 (真媒体管理器成员候选) ===')
for r in sing_all:
    print('  %-11s %s %-24s singleton=%d reg=%d' % (r['cls'], r['addr'], r['name'], r['singleton'], r['reg']))
print()
print('=== 收其他 imm 的方法 (误归属候选, 看 imm 判真主) ===')
for r in other_all[:25]:
    print('  %-11s %s %-24s other=%s reg=%d' % (r['cls'], r['addr'], r['name'], ','.join(r['other_imm'][:2]), r['reg']))
idapro.close_database(False)
