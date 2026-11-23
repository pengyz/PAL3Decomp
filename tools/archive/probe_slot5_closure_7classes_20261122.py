#!/usr/bin/env python3
"""[槽5闭环探针 2026-11-22] 7类删除式dtor的表归属闭环验证(三律工具化)。

三律之一(vtable-writer-evidence-law 闭环要求): "删除式地址∈表slot5"只证关联,
必须反向验"表∈类注解vtables"——未闭环=欠账(本探针产出欠账清单+落地评估)。

方法:
  ①.rdata 扫 DWORD==删除式地址 → 候选表基(H-0x14)
  ②槽域校验(邻域代码址≥6/9) → 确认表基
  ③闭环判定: 表基 ∈ 类注解 vtables? → CLOSED / OPEN(欠账)
  ④OPEN 类的表基归属交叉: 其他类 vtables 含此表? → 跨类误挂检测
  ⑤全槽读出+IDB名(落地工作量评估)

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_slot5_closure_7classes_20261122.py
"""
import sys
import json
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
idapro = __import__('idapro')
idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                     run_auto_analysis=False)
import idc
import ida_bytes
import ida_name
import ida_segment
import ida_funcs

REPO = '/home/peng/workspace/PAL3Decomp'

# 类注解 vtables 表地址集(闭环判定基准)
import glob as _g
ann_tables = {}   # table_addr → [cls...]
for fp in _g.glob(REPO + '/data/annotations/structs/*.json'):
    try:
        d = json.load(open(fp, encoding='utf-8'))
    except Exception:
        continue
    cls = d.get('name') or fp.split('/')[-1][:-5]
    for vt in (d.get('vtables') or []):
        try:
            ta = int(str(vt.get('addr')), 16)
            ann_tables.setdefault(ta, []).append(cls)
        except (ValueError, TypeError):
            pass

TARGETS = [
    ('ArraySlots',      0x0044AB40),
    ('CCBSystem',       0x00515DD0),
    ('EffBinkNode',     0x004C20B0),
    ('EffCallBackNode', 0x004C34B0),
    ('ParticleEffect',  0x004BD850),
    ('RenderTarget2',   0x004C3C80),
    ('SceneMgr',        0x004CD930),
]

seg = ida_segment.get_segm_by_name('.rdata')
RD_START, RD_END = seg.start_ea, seg.end_ea
rd = ida_bytes.get_bytes(RD_START, RD_END - RD_START)

report = {}
for cls, dtor in TARGETS:
    pat = dtor.to_bytes(4, 'little')
    hits = []
    off = 0
    while True:
        i = rd.find(pat, off)
        if i < 0:
            break
        hits.append(RD_START + i)
        off = i + 1
    confirmed = None
    for h in hits:
        base = h - 0x14
        ok = 0
        for k in range(-1, 8):
            va = int.from_bytes(ida_bytes.get_bytes(base + 4 * k, 4), 'little')
            if 0x00401000 <= va < 0x00570000 and ida_funcs.get_func(va):
                ok += 1
        if ok >= 6 and base % 4 == 0 and confirmed is None:
            confirmed = base
    st = report.setdefault(cls, {'dtor': hex(dtor), 'hits': len(hits), 'tables': []})
    if confirmed is None:
        st['verdict'] = 'OPEN(表基未确认)'
        print('== %-14s 0x%X: 命中%d, 无确认表基' % (cls, dtor, len(hits)))
        continue
    owners = ann_tables.get(confirmed, [])
    closed = cls in owners
    st['verdict'] = 'CLOSED' if closed else 'OPEN(表未入注解)'
    st['table'] = hex(confirmed)
    st['owners'] = owners
    slots = []
    for k in range(0, 9):
        va = int.from_bytes(ida_bytes.get_bytes(confirmed + 4 * k, 4), 'little')
        nm = ida_name.get_name(va) or ''
        sem = '语义' if nm and not nm.startswith(('sub_', 'nullsub')) else '无名'
        slots.append((k, va, nm[:44], sem))
        if va == dtor:
            st['slot5_hit'] = True
    st['slots'] = slots
    print('== %-14s 0x%X: 表0x%X [%s] %s' % (
        cls, dtor, confirmed, ','.join(owners) or '无主', st['verdict']))
    for k, va, nm, sem in slots:
        mark = ' <== 删除式' if va == dtor else ''
        print('   slot%-2d 0x%X %-46s %s%s' % (k, va, nm[:44], sem, mark))

out = REPO + '/data/status/slot5_closure_7classes_20261122.json'
json.dump(report, open(out, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('\n报告 →', out)
idapro.close_database(False)
