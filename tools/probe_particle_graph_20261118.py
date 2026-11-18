#!/usr/bin/env python3
"""[探针 2026-11-18] particle_graph 家族定谳——找出 sg_emitter/sg_particle 类型
的消费者函数 + graph 区间(5300B)内部访问的原始汇编 disp。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_particle_graph_20261118.py
"""
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)
print('[probe] db opened:', db)

import ida_typeinf
import ida_funcs
import ida_name
import ida_xref
import ida_ua
import idc

# 1) 查全局结构名 sg_emitter/sg_particle/graph 家族的 tid
til = ida_typeinf.get_idati()
for tname in ('sg_emitter', 'sg_particle', 'direction_emitter_graph', 'size_particle_graph'):
    tid = ida_typeinf.get_tid_name if False else None
    import ida_typeinf as ti
    t = ti.tinfo_t()
    ok = t.get_named_type(til, tname)
    print('%-28s found=%s size=%s' % (tname, ok, t.get_size() if ok else '-'))

# 2) 遍历所有函数, 检查局部类型字符串是否含 sg_emitter/sg_particle
import idautils
hits = []
for fea in idautils.Functions():
    f = ida_funcs.get_func(fea)
    if not f:
        continue
    try:
        ti2 = ida_typeinf.tinfo_t()
        if not ida_typeinf.guess_tinfo(ti2, fea):
            continue
        s = str(ti2)
        if 'sg_emitter' in s or 'sg_particle' in s:
            hits.append((fea, ida_name.get_name(fea), s[:120]))
    except Exception:
        continue
print('\n=== 类型签名含 sg_emitter/sg_particle 的函数 (%d) ===' % len(hits))
for ea, name, sig in hits[:40]:
    print('  0x%08x %-40s %s' % (ea, name[:40], sig[:80]))

idapro.close_database(False)
print('\n[probe] done')
