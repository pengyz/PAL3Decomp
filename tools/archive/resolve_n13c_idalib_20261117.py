#!/usr/bin/env python3
"""[N13c按名解析器 2026-11-17] IDB名字表反查缺失函数地址 → 注解条目生成。

运行: /home/peng/.local/ida-mcp-venv/bin/python tools/resolve_n13c_idalib_20261117.py
数据流: n13c清单(类::方法) → idautils.Names()全表+mangled双向反查 → 地址
  → idaapi.get_tinfo取签名初值 → 注解methods条目(evidence_level=unverified,
  sig_model pending) → check重跑N13c收敛。
"""
import sys
import os
import json

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)
print('[resolver] db opened:', db)

os.chdir('/home/peng/workspace/PAL3Decomp')
sys.path.insert(0, '/home/peng/workspace/PAL3Decomp/pipeline')
sys.path.insert(0, '/home/peng/workspace/PAL3Decomp/pipeline/ida')
import idc
idc.qexit = lambda *a, **k: None

import idautils
import ida_name
import ida_funcs
import idaapi

# N13c清单: 从check输出解析(或硬编码清单)
import re
manifest = []
log_path = None
for cand in ('/tmp/chk79.out', '/tmp/chk77.out'):
    if os.path.exists(cand):
        log_path = cand
        break
if log_path:
    for ln in open(log_path, encoding='utf-8', errors='ignore'):
        m = re.search(r'DATA:N13c:(\S+) 限定调用契约断', ln)
        if m:
            cls, meth = m.group(1).split('::', 1)
            manifest.append((cls, meth))
manifest = sorted(set(manifest))
print('[resolver] N13c清单: %d条' % len(manifest))

# 名字表: demangled+raw双向
name_map = {}
for ea, name in idautils.Names():
    name_map[name] = ea
    dm = ida_name.demangle_name(name, 0) or ''
    if dm:
        # 'Cls::M(...)' 剥参数取 'Cls::M'
        base = dm.split('(')[0].strip()
        name_map.setdefault(base, ea)

resolved, unresolved = [], []
for cls, meth in manifest:
    full = '%s::%s' % (cls, meth)
    ea = name_map.get(full) or name_map.get(meth)
    if ea is None:
        unresolved.append(full)
        print('[miss] %s' % full)
        continue
    fn = ida_funcs.get_func(ea)
    sig = ''
    if fn:
        tf = idaapi.tinfo_t()
        if tf.get_func_type(fn.start_ea) if hasattr(tf, 'get_func_type') else False:
            try:
                sig = str(tf)[:120]
            except Exception:
                pass
    resolved.append({'cls': cls, 'meth': meth, 'ea': '0x%08x' % ea, 'sig': sig})
    print('[hit] %s → 0x%08x %s' % (full, ea, sig[:40]))

print('[resolver] resolved=%d unresolved=%d' % (len(resolved), len(unresolved)))
json.dump({'resolved': resolved, 'unresolved': unresolved},
          open('data/status/n13c_resolved_20261117.json', 'w', encoding='utf-8'),
          ensure_ascii=False, indent=1)

import json as _json
# 落注解条目(unverified, sig_model pending)
added = 0
for r in resolved:
    fp = 'data/annotations/structs/%s.json' % r['cls']
    if not os.path.exists(fp):
        print('[skip] %s 无注解文件' % r['cls'])
        continue
    d = _json.load(open(fp, encoding='utf-8'))
    ms = d.setdefault('methods', {})
    if r['ea'] in ms:
        continue
    sig = r['sig'] or ''
    sm = {'return': None, 'cc': None, 'params': None, 'varargs': False, 'pending': True}
    if sig:
        m = re.match(r'^(\w[\w\s:*&]*?)\s*(?:__\w+\s*)*\(', sig)
        if m:
            sm['return'] = m.group(1).strip()
            sm['pending'] = False
    ms[r['ea']] = {
        'name': r['meth'], 'evidence_level': 'unverified',
        'source': 'idb_name_evidence 2026-11-17(N13c按名解析)',
        'sig_model': sm,
        'signature': (r['sig'] or '') if r['sig'] else '%s __thiscall()' % r['meth'],
        'name_note': 'N13c按名解析20261117: IDB名字表反查命中(语料限定调用契约断修复)'}
    _json.dump(d, open(fp, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    added += 1
print('注解条目 +%d' % added)

idapro.close_database(False)
print('[resolver] done')
