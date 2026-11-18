#!/usr/bin/env python3
"""[探针 R1 2026-11-18] CCBCamControl 池区定谳——普查该类方法群对池区
[0x24e4, 0x68fb0) 的原始汇编 disp。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_ccbcamcontrol_pool_20261118.py
"""
import sys

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)

import idautils
import ida_funcs
import ida_bytes
import ida_ua
import idc

# CCBCamControl 方法群地址从注解拿
import json
d = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/CCBCamControl.json'))
methods = [(int(k, 16), m.get('name')) for k, m in (d.get('methods') or {}).items()
           if isinstance(m, dict)]
print('CCBCamControl methods: %d' % len(methods))

POOL_LO, POOL_HI = 0x24e4, 0x68fb0

# 对每个方法, 扫描汇编中 disp 落在池区的指令 (this 基: lea/mov [reg+disp])
import re
import io
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
DISP_RE = re.compile(r'\[(?:eax|ebx|ecx|edx|esi|edi|ebp)(?:\+[a-z]{3}\*\d)?\+(?:0x)?([0-9A-Fa-f]+)h?\]')

hits = {}
for ea, name in sorted(methods):
    f = ida_funcs.get_func(ea)
    if not f:
        continue
    found = []
    cur = f.start_ea
    n = 0
    while cur < f.end_ea and n < 4000:
        line = idc.generate_disasm_line(cur, 0)
        # 粗扫: 含大 disp 的指令
        for m in DISP_RE.finditer(line):
            disp = int(m.group(1), 16)
            if POOL_LO <= disp < POOL_HI:
                found.append((cur, line[:80], disp))
                break
        cur = idc.next_head(cur)
        if cur <= 0: break
        n += 1
    if found:
        hits[(ea, name)] = found

print('\n=== 方法 x 池区 disp 命中 (%d 方法) ===' % len(hits))
for (ea, name), rows in sorted(hits.items(), key=lambda kv: -len(kv[1]))[:20]:
    print('0x%08x %-36s hits=%d' % (ea, str(name)[:36], len(rows)))
    for addr, line, disp in rows[:200]:
        print('    0x%08x disp=0x%05x  %s' % (addr, disp, line))

idapro.close_database(False)
print('\n[probe] done')
