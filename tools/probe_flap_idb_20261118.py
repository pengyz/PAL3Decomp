#!/usr/bin/env python3
"""[flap 定谳 2026-11-18] apply 幂等性实验: 同一 IDB 连续两次 apply+export, diff 输出。

背景: 同日快照间语料错误数剧烈抖动(Array 7↔51/CCBUI 29↔79), 疑似根因=
apply_annotations 原地反复改同一 .i64 的路径依赖(非幂等)。本实验在**同一个
数据库副本**上跑两轮 apply+export, 比对两轮输出:
  - 逐字节一致 → apply 幂等, flap 根因在管线别处(codegen/环境)
  - 不一致 → 非幂等实锤, diff 内容定性漂移面

用法:
  /home/peng/.local/ida-mcp-venv/bin/python tools/probe_flap_idb_20261118.py <db_path>
输出: /tmp/flap_r1/ /tmp/flap_r2/ + stdout diff 摘要
"""
import json
import os
import shutil
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

DB = sys.argv[1]
if not DB or not os.path.exists(DB):
    print('usage: probe_flap_idb_20261118.py <db_path>'); sys.exit(2)

db = idapro.open_database(DB, run_auto_analysis=False)
print('[flap] db opened:', db)

os.chdir('/home/peng/workspace/PAL3Decomp')
sys.path.insert(0, '/home/peng/workspace/PAL3Decomp/pipeline')
sys.path.insert(0, '/home/peng/workspace/PAL3Decomp/pipeline/ida')
import idc
idc.qexit = lambda *a, **k: None

import apply_annotations as AA
import export_full as EF

REPO = '/home/peng/workspace/PAL3Decomp'
SRC_DECOMP = os.path.join(REPO, 'asm', 'pal3', 'decomp')
SRC_STRUCTS = os.path.join(REPO, 'asm', 'pal3', 'ida_structs.json')

for rnd in (1, 2):
    print('\n[flap] ===== round %d: apply =====' % rnd)
    AA.apply_annotations()
    print('[flap] ===== round %d: export =====' % rnd)
    EF.main()
    out = '/tmp/flap_r%d' % rnd
    shutil.rmtree(out, ignore_errors=True)
    os.makedirs(out)
    shutil.copytree(SRC_DECOMP, os.path.join(out, 'decomp'))
    shutil.copy2(SRC_STRUCTS, os.path.join(out, 'ida_structs.json'))
    print('[flap] round %d snapshot -> %s' % (rnd, out))

idapro.close_database(False)

# ── diff ──
import filecmp
r1, r2 = '/tmp/flap_r1', '/tmp/flap_r2'
d1 = set(os.listdir(r1 + '/decomp'))
d2 = set(os.listdir(r2 + '/decomp'))
same, diff, only1, only2 = filecmp.dircmp(r1 + '/decomp', r2 + '/decomp').same_files, \
    filecmp.dircmp(r1 + '/decomp', r2 + '/decomp').diff_files, \
    d1 - d2, d2 - d1
print('\n[flap] decomp: same=%d diff=%d only_r1=%d only_r2=%d' % (
    len(same), len(diff), len(only1), len(only2)))
if only1: print('  only r1:', sorted(only1)[:10])
if only2: print('  only r2:', sorted(only2)[:10])
if diff:
    print('  CHANGED files (%d), 首批 20:' % len(diff))
    for f in sorted(diff)[:20]:
        print('    ', f)
st_same = filecmp.cmp(r1 + '/ida_structs.json', r2 + '/ida_structs.json', shallow=False)
print('[flap] ida_structs.json identical:', st_same)
print('[flap] VERDICT:', '幂等 ✓ (flap 根因在管线别处)' if (not diff and not only1 and not only2 and st_same) else '非幂等 ✗ 实锤')
