#!/usr/bin/env python3
"""[S2 槽5探针 2026-11-21] 5类 ctor写表→slot5归属→vtables落地评估。

目标: ParticleEffect/UIWnd/CPK/CCBPanelSlot/UIScene 的 ??_G 载体恢复前置——
  virtual 声明证据 = dtor地址 ∈ 类 vtables 槽地址(virtual证据律)。
方法: .rdata 扫描 DWORD==删除式地址 → 候选表基(H-0x14) → 槽序校验(邻域全为.text代码址)
  → 读槽0..8 + IDB名/型 → 落地工作量评估。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_slot5_5classes_20261121.py
"""
import sys
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc
import ida_bytes
import ida_funcs
import ida_name
import ida_segment
import ida_typeinf

TARGETS = [
    ('ParticleEffect', 0x004BD850),
    ('UIWnd',          0x00445B20),
    ('CPK',            0x0053C2B0),
    ('CCBPanelSlot',   0x004431B0),
    ('UIScene',        0x0043BE10),
]

# .rdata 段范围
seg = ida_segment.get_segm_by_name('.rdata')
RD_START, RD_END = seg.start_ea, seg.end_ea
print('[probe] .rdata 0x%X-0x%X (%d bytes)' % (RD_START, RD_END, RD_END - RD_START))
rd = ida_bytes.get_bytes(RD_START, RD_END - RD_START)

def is_text_code(va):
    return 0x00401000 <= va < 0x00570000 and ida_funcs.get_func(va) is not None

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
    print('\n== %s 删除式 0x%X: .rdata 引用 %d 处 ==' % (cls, dtor, len(hits)))
    confirmed = None
    for h in hits:
        base = h - 0x14          # slot5 = 基+0x14
        # 槽域校验: 基-4..基+36 的 9 个 dword 全为 .text 代码址(或表头对齐)
        ok = 0
        for k in range(-1, 8):
            va = int.from_bytes(ida_bytes.get_bytes(base + 4 * k, 4), 'little')
            if 0x00401000 <= va < 0x00570000:
                ok += 1
        tag = ''
        if ok >= 7 and base % 4 == 0:
            tag = ' <== 候选表基(slot5)'
            if confirmed is None:
                confirmed = base
        print('  引用@0x%X (slot%+d from 0x%X) 邻域代码址%d/9%s' % (
            h, (h - base) // 4 if ok else 0, base, ok, tag))
    if confirmed:
        print('  -- 表基 0x%X 全槽读出 --' % confirmed)
        for k in range(0, 9):
            va = int.from_bytes(ida_bytes.get_bytes(confirmed + 4 * k, 4), 'little')
            nm = ida_name.get_name(va) or ''
            f = ida_funcs.get_func(va)
            sz = f.size() if f else 0
            mark = ' <== 删除式' if va == dtor else ''
            sem = '' if (nm.startswith('sub_') or nm.startswith('nullsub') or not nm) else '语义'
            print('   slot%-2d 0x%X %-46s size=%-4d %s%s' % (k, va, nm[:46], sz, sem, mark))

idapro.close_database(False)
