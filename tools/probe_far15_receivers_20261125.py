#!/usr/bin/env python3
"""probe_far15_receivers_20261125.py — CScreenMode far 15 方法接收者回溯定谳。
每方法全调用点 → 回溯 12 条找 mov ecx,<src> → 分类:
  singleton(0xa3a7d8) / GetInstance链(call GetInstance→eax→ecx) / reg(寄存器不可判)
"""
import sys, json, re
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_far15_receivers_20261125.json'
SINGLETON = 0x00a3a7d8
GI_EA = 0x53df70  # GetInstance

cm = json.load(open('data/annotations/structs/CScreenMode.json', encoding='utf-8'))
targets = {}
for a, m in (cm.get('methods') or {}).items():
    targets[int(a, 16)] = str(m.get('name') or '?')

report = {}
for ea, nm in sorted(targets.items()):
    f = ida_funcs.get_func(ea)
    if not f:
        report[nm] = {'ea': hex(ea), 'error': 'no_func'}
        continue
    rec = {'ea': hex(ea), 'name': nm, 'singleton': 0, 'gi_chain': 0, 'reg': 0, 'total': 0, 'sites': []}
    for site in idautils.CodeRefsTo(f.start_ea, 0):
        rec['total'] += 1
        # 回溯 12 条
        got = None
        cur = site
        for _ in range(12):
            p = idc.prev_head(cur, 0)
            if p == idc.BADADDR:
                break
            t = (idc.generate_disasm_line(p, 0) or '').split(';')[0].strip()
            # mov ecx, 0a3a7d8h → singleton direct
            m1 = re.match(r'mov\s+ecx,\s*0a3a7d8h$', t.replace(' ', ' '))
            if m1:
                got = 'singleton'; break
            # call GetInstance → eax → ecx 链
            if 'GetInstance' in t and t.startswith('call'):
                got = 'gi_chain'; break
            # mov ecx, eax (紧跟 GetInstance 或其他)
            if re.match(r'mov\s+ecx,\s*eax$', t):
                # 看更早是否 call GetInstance
                cur2 = p
                for _2 in range(5):
                    p2 = idc.prev_head(cur2, 0)
                    if p2 == idc.BADADDR: break
                    t2 = (idc.generate_disasm_line(p2, 0) or '').split(';')[0].strip()
                    if 'GetInstance' in t2:
                        got = 'gi_chain'; break
                    cur2 = p2
                if got: break
                got = 'reg_eax'; break
            # mov ecx, imm (其他 imm = 其他对象)
            m3 = re.match(r'mov\s+ecx,\s*([0-9A-Fa-f]+)h?$', t.replace(' ', ' '))
            if m3:
                got = 'imm_' + m3.group(1); break
            if t.startswith('call') and '__thiscall' not in t:
                break
            cur = p
        if got == 'singleton':
            rec['singleton'] += 1
        elif got == 'gi_chain':
            rec['gi_chain'] += 1
        elif got and got.startswith('imm_'):
            rec.setdefault('other_imm', []).append(got)
        else:
            rec['reg'] += 1
    report[nm] = rec

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('=== far 15 接收者分类 ===')
for nm, r in sorted(report.items()):
    if 'error' in r:
        print('%-24s %s' % (nm, r['error'])); continue
    tags = []
    if r['singleton']: tags.append('singleton×%d' % r['singleton'])
    if r['gi_chain']: tags.append('gi_chain×%d' % r['gi_chain'])
    if r.get('other_imm'): tags.append('other_imm=%s' % r['other_imm'][:2])
    if r['reg']: tags.append('reg×%d' % r['reg'])
    print('%-24s total=%-3d %s' % (nm, r['total'], ' '.join(tags)))
idapro.close_database(False)
