#!/usr/bin/env python3
"""[探针 2026-11-24 #12] PAL3A PDB SceneMgr 方法族 → PAL3 地址映射(跨版本指纹匹配)。

背景: data/pdb/pdb_export.json(PAL3A PDB)有真 SceneMgr 符号族 26 个
(SceneMgr.cpp 源文件索引), PAL3A 地址已知, PAL3 地址未知。
指纹: 前 30 条指令的助记符序列(mnemonic-only, 抗重定位) + 前 8 条含寄存器形状。
匹配: PAL3 函数库全索引 → 唯一命中 = 地址映射。
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_pal3a_scenemgr_match_20261124.py
"""
import sys
import re
import json
import collections

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db_path = sys.argv[1] if len(sys.argv) > 1 else \
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64'
import idapro as _ida
db = _ida.open_database(db_path, run_auto_analysis=False)

import idc
import ida_bytes
import ida_funcs
import ida_name
import idautils


def fingerprint(fstart, n=30):
    f = ida_funcs.get_func(fstart)
    if not f:
        return None
    mnems = []
    cur = f.start_ea
    cnt = 0
    while cur < f.end_ea and cnt < n:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        mn = idc.print_insn_mnem(cur)
        if mn:
            mnems.append(mn)
            cnt += 1
        cur = idc.next_head(cur, f.end_ea)
    return tuple(mnems)


def head_shape(fstart, n=8):
    f = ida_funcs.get_func(fstart)
    out = []
    cur = f.start_ea
    cnt = 0
    while cur < f.end_ea and cnt < n:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        t = (idc.generate_disasm_line(cur, 0) or '')
        t = re.sub(r'0x?[0-9A-Fa-f]+h?', '#', t)
        t = re.sub(r'\s+', ' ', t).strip()
        out.append(t)
        cnt += 1
        cur = idc.next_head(cur, f.end_ea)
    return tuple(out)


MODE = sys.argv[2] if len(sys.argv) > 2 else 'index'

if MODE == 'index':
    # PAL3: 全函数指纹索引
    idx = collections.defaultdict(list)
    total = 0
    for ea in idautils.Functions():
        fp = fingerprint(ea)
        if fp:
            idx['|'.join(fp)].append(ea)
            total += 1
    hs = {'%x' % ea: list(head_shape(ea)) for ea in idautils.Functions()}
    json_out = {'idx': idx, 'hs': hs}
    import json as _j
    _j.dump(json_out, open('/tmp/pal3_fp_index.json', 'w'))
    print('PAL3 functions:', total, 'unique fingerprints:', len(idx))
else:
    # PAL3A: SceneMgr 方法指纹 → 与 /tmp/pal3_fp_index.json 匹配
    import json as _j
    idxd = _j.load(open('/tmp/pal3_fp_index.json'))
    idx = {tuple(k.split('|')): v for k, v in idxd['idx'].items()}
    hs = {int(k, 16): tuple(v) for k, v in idxd['hs'].items()}

    d = _j.load(open('/home/peng/workspace/PAL3Decomp/data/pdb/pdb_export.json'))
    sfi = d['source_file_index']
    scenesyms = []
    for fkey in sfi:
        if 'SceneMgr' in fkey:
            scenesyms.extend(sfi[fkey])
    seen = set()
    print('PAL3A SceneMgr 符号 → PAL3 匹配:')
    for s in scenesyms:
        nm = s['name']
        a = int(s['address'], 16)
        if nm in seen or nm.startswith('$E'):
            continue
        seen.add(nm)
        fp = fingerprint(a)
        hs_a = head_shape(a)
        if fp is None:
            print('  %-28s PAL3A 0x%06X: NO-FUNC' % (nm, a))
            continue
        hits = idx.get(fp, [])
        ver = ''
        if len(hits) == 1:
            ver = 'PAL3 0x%X %s' % (hits[0], (ida_name.get_name(hits[0]) or '')[:30])
        elif len(hits) > 1:
            # head_shape 消歧
            refined = [h for h in hits if hs.get(h) == hs_a]
            ver = 'PAL3 multi(%d) refined=%s' % (len(hits), ['0x%X' % x for x in refined[:3]])
        else:
            ver = 'NO-MATCH'
        print('  %-28s PAL3A 0x%06X fp=%3d → %s' % (nm, a, len(fp), ver))

_ida.close_database(False)
