#!/usr/bin/env python3
"""[S2 2026-11-16 TDD] 注解文件级 sig 结构化迁移。幂等。用法: 单文件路径参数, 无参=报告模式。"""
import json, sys, os
sys.path.insert(0, os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')))
from pipeline.sigmodel import migrate_entry


def migrate_file(path):
    d = json.load(open(path, encoding='utf-8'))
    ms = d.get('methods') or {}
    n_migrated = 0
    report = {'file': path, 'migrated': 0, 'pending': 0, 'noop': 0, 'pending_items': []}
    for k, v in ms.items():
        r = migrate_entry(v)
        if r['status'] == 'migrated':
            n_migrated += 1
        report[r['status']] += 1
        if r['status'] == 'pending':
            report['pending_items'].append({'key': k, 'name': v.get('name')})
    # 槽级契约结构化(折叠载体各槽独立契约, C6多槽豁免配套)
    from pipeline.sigmodel import parse_signature
    n_slot = 0
    for vt in (d.get('vtables') or []):
        for sl in (vt.get('slots') or []):
            if sl.get('sig') and not sl.get('sig_model'):
                _n = parse_signature(sl['sig'])
                if _n:
                    sl['sig_model'] = _n
                    n_slot += 1
    if n_slot:
        report['slot_contracts'] = n_slot
    json.dump(d, open(path, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    return n_migrated, report


def main():
    if len(sys.argv) > 1:
        n, r = migrate_file(sys.argv[1])
        print(json.dumps(r, ensure_ascii=False)[:300])
        return 0
    return 0


if __name__ == '__main__':
    sys.exit(main())
