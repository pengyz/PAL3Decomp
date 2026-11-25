#!/usr/bin/env python3
"""probe_old_idb_types_20261125.py — 从旧 IDB 提取全局类型定型（fresh IDB 缺失的修复参考）。
对比新旧 IDB 的全局类型 → 差集 = fresh init 丢失的类型注解。
"""
import sys, json
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')

def dump_globals_types(path, label):
    import idapro
    db = idapro.open_database(path, run_auto_analysis=False)
    import idc, idautils, ida_typeinf, ida_nalt
    out = {}
    for ea, name in idautils.Names():
        if not name or name.startswith(('sub_', 'loc_', 'j_', '??', 'nullsub', '__')):
            continue
        tif = ida_typeinf.tinfo_t()
        ok = ida_nalt.get_tinfo(tif, ea)
        if ok and not tif.empty():
            out[hex(ea)] = {'name': name, 'type': str(tif)}
    idapro.close_database(False)
    print('%s: %d globals with types' % (label, len(out)))
    return out

old = dump_globals_types('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64.bak-20261125-retire', '旧 IDB')
new = dump_globals_types('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64', '新 IDB')

# 差集: 旧 IDB 有类型但新 IDB 没有（或类型不同）
delta = {}
for ea, old_info in old.items():
    new_info = new.get(ea)
    if new_info is None:
        delta[ea] = {'old': old_info, 'new': None, 'reason': '新 IDB 无类型'}
    elif old_info['type'] != new_info['type']:
        delta[ea] = {'old': old_info, 'new': new_info, 'reason': '类型不一致'}

print('\n差集 %d 条 (旧有型/新缺失或不一致):' % len(delta))
for ea, d in sorted(delta.items())[:20]:
    print('  %s %s: old=%s new=%s [%s]' % (ea, d['old']['name'][:30],
        d['old']['type'][:40], (d.get('new') or {}).get('type', '无')[:40], d['reason']))

json.dump(delta, open('data/status/idb_type_delta_20261125.json', 'w', encoding='utf-8'),
          ensure_ascii=False, indent=1)
print('-> data/status/idb_type_delta_20261125.json')
