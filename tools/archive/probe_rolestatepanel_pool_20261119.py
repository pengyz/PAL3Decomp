#!/usr/bin/env python3
"""[R2 探针 2026-11-19] RoleStatePanel 池区 [0x169,0x25E04) disp 普查 + ParticleEffect
头部区 [0x0,0x763C) 消费普查——真实汇编 disp 对齐 (R1 教训: 语料借位渲染不可当偏移证据)。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_rolestatepanel_pool_20261119.py
输出: data/annotations/archive/probe_rolestatepanel_output_20261119.txt (R1-T4 教训: 必存档)
"""
import io
import json
import re
import sys

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8', errors='replace')
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)

import idautils
import ida_funcs
import idc

# 变址兼容 regex (R1 教训)
DISP_RE = re.compile(
    r'\[(?:eax|ebx|ecx|edx|esi|edi|ebp)(?:\+[a-z]{3}\*[\dxa-fh]+)*\+(?:0x)?([0-9A-Fa-f]+)h?\]')

def scan_methods(methods, lo, hi, tag, cap=6000):
    hits = {}
    for ea, name in sorted(methods):
        f = ida_funcs.get_func(ea)
        if not f:
            continue
        found = []
        cur = f.start_ea
        while cur < f.end_ea and (f.end_ea - f.start_ea) < cap * 10:
            line = idc.generate_disasm_line(cur, 0)
            if line:
                for m in DISP_RE.finditer(line):
                    disp = int(m.group(1), 16)
                    if lo <= disp < hi:
                        found.append((cur, disp, line[:90]))
                        break
            nxt = idc.next_head(cur)
            if nxt <= cur:
                break
            cur = nxt
        if found:
            hits[(ea, name)] = found
    print('\n=== %s: %d 方法命中池区 disp ===' % (tag, len(hits)))
    for (ea, name), rows in sorted(hits.items(), key=lambda kv: -len(kv[1]))[:18]:
        print('0x%08x %-38s hits=%d' % (ea, str(name)[:38], len(rows)))
        disp_cnt = {}
        for addr, disp, line in rows:
            disp_cnt[disp] = disp_cnt.get(disp, 0) + 1
        for disp, cnt in sorted(disp_cnt.items())[:14]:
            print('    disp=0x%05x x%d' % (disp, cnt))
    return hits

# RoleStatePanel: 注解 10 成员
rsp = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/RoleStatePanel.json'))
m1 = [(int(k, 16), m.get('name')) for k, m in (rsp.get('methods') or {}).items() if isinstance(m, dict)]
scan_methods(m1, 0x169, 0x25E04, 'RoleStatePanel 池区[0x169,0x25E04)')

# ParticleEffect: 头部区
pe = json.load(open('/home/peng/workspace/PAL3Decomp/data/annotations/structs/ParticleEffect.json'))
m2 = [(int(k, 16), m.get('name')) for k, m in (pe.get('methods') or {}).items() if isinstance(m, dict)]
scan_methods(m2, 0x0, 0x763C, 'ParticleEffect 头部[0x0,0x763C)')

idapro.close_database(False)
print('\n[probe] done')
