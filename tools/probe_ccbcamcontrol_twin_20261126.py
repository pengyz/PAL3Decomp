#!/usr/bin/env python3
"""probe_ccbcamcontrol_twin_20261126.py — CCCTData vs CCBCamControl 孪生身份裁决。

疑点: 两注解 binary_size 同为 430256(0x690B0); CCCTData 方法出现在
CCBCamControl 洞区访问者里(GetFreeSpaceInPool/IsTaskValid)。
裁决三查:
  1. 静态绑定面: 谁的 mov ecx,offset <g_XXX> 绑定到 g_CCBCamControlData?
     CCCTData 22 方法 × CCBCamControl 33 方法各自静态基址绑定形态
  2. this-form disp 域: 两类方法各自 max disp / 洞区命中分布
  3. 锚区内独立符号: idautils.Names 枚举 [0x17AAF64, +0x690B0) 内全部
     IDA 名 → 独立对象重叠显形(W1 查一模式)
"""
import sys, json, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs, idautils

SIZE = 0x690B0
BASE = 0x17AAF64
OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_ccbcamcontrol_twin_20261126.json'
CCB = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/CCBCamControl.json', encoding='utf-8'))
CCT = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/CCCTData.json', encoding='utf-8'))
MB_CCB = {int(a,16): str(m.get('name') or a) for a, m in (CCB.get('methods') or {}).items()}
MB_CCT = {int(a,16): str(m.get('name') or a) for a, m in (CCT.get('methods') or {}).items()}

MEM_RX = re.compile(r'\[(e[a-z]{2}|cx|si|di)(?:\+(e[a-z]{2}|cx|si|di)(?:\*([1248]))?)?'
                    r'(\+(0[xX][0-9A-Fa-f]+|[0-9A-Fa-f]{1,8}h?))?\]')

def disps_of(ea):
    f = ida_funcs.get_func(ea)
    if not f:
        return None, []
    out = []
    cur, n = f.start_ea, 0
    while cur < f.end_ea and n < 5000:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        m = MEM_RX.search(t)
        if m and m.group(4):
            g = m.group(5)
            d = int(g, 16) if g.lower().startswith('0x') else int(g.rstrip('h]'), 16)
            if d < SIZE:
                out.append(d)
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    return f, out

report = {}
for tag, mmap in (('CCBCamControl', MB_CCB), ('CCCTData', MB_CCT)):
    rows = {}
    static_bind = []
    for ea, nm in sorted(mmap.items()):
        f, ds = disps_of(ea)
        # 静态绑定: 体首 offset g_CCBCamControlData / mov ecx, 0x17AAF64
        if f:
            cur, n = f.start_ea, 0
            while cur < min(f.start_ea + 0x80, f.end_ea) and n < 40:
                t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
                if 'g_CCBCamControlData' in t or '17AAF64' in t.lower():
                    static_bind.append((nm, hex(cur), t))
                cur = idc.next_head(cur, f.end_ea)
                n += 1
        if ds:
            rows[nm] = {'n': len(ds), 'max': hex(max(ds)),
                        'uniq': len(set(ds))}
    report[tag] = {'rows': rows, 'static_bind': static_bind[:40],
                   'max_all': hex(max(max(int(r['max'],16) for r in rows.values()), 0)) if rows else None,
                   'n_methods_with_disp': len(rows)}

# 3. 锚区内独立符号
names_in_span = []
for ea, nm in idautils.Names():
    if BASE <= ea < BASE + SIZE:
        names_in_span.append((hex(ea), nm, ea - BASE))
names_in_span.sort()
report['names_in_span'] = names_in_span[:200]
report['names_in_span_n'] = len(names_in_span)

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
for tag in ('CCBCamControl', 'CCCTData'):
    r = report[tag]
    print('== %s == max_all=%s 有disp方法=%d 静态绑定=%d' % (
        tag, r['max_all'], r['n_methods_with_disp'], len(r['static_bind'])))
    for nm, a, t in r['static_bind'][:8]:
        print('   绑定:', nm, a, t[:60])
    tops = sorted(r['rows'].items(), key=lambda x: -int(x[1]['max'], 16))[:8]
    for nm, rr in tops:
        print('   %-30s max=%s n=%d uniq=%d' % (nm, rr['max'], rr['n'], rr['uniq']))
print('== 锚区内独立符号 %d 个 ==' % report['names_in_span_n'])
for a, nm, off in report['names_in_span'][:40]:
    print('   %s +0x%x %s' % (a, off, nm))
idapro.close_database(False)
