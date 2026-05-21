#!/usr/bin/env python3
"""
同步 PDB 的 kind 字段到 annotations/structs/*.json

从 data/pdb/pdb_export.json 读取每个类的 kind (struct/union/class),
更新到对应的 data/annotations/structs/ClassName.json 文件中。
"""

import json
import os

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PDB_EXPORT = os.path.join(PROJECT_ROOT, "data", "pdb", "pdb_export.json")
STRUCTS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")

def main():
    # Load PDB
    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        pdb = json.load(f)

    # Build name->kind map
    kind_map = {}
    for cls in pdb.get('classes', []):
        name = cls.get('name')
        kind = cls.get('kind', 'struct')
        if name:
            kind_map[name] = kind

    print(f"[*] PDB contains {len(kind_map)} types")

    # Update annotations
    updated = 0
    added_kind = 0
    changed_kind = 0

    for fname in os.listdir(STRUCTS_DIR):
        if not fname.endswith('.json'):
            continue

        path = os.path.join(STRUCTS_DIR, fname)
        with open(path, 'r', encoding='utf-8') as f:
            data = json.load(f)

        name = data.get('name')
        if not name:
            continue

        pdb_kind = kind_map.get(name)
        if not pdb_kind:
            # Not in PDB, skip
            continue

        existing_kind = data.get('kind')
        if existing_kind == pdb_kind:
            # Already correct
            continue

        if existing_kind:
            print(f"[~] {name}: {existing_kind} -> {pdb_kind}")
            changed_kind += 1
        else:
            print(f"[+] {name}: (none) -> {pdb_kind}")
            added_kind += 1

        data['kind'] = pdb_kind

        with open(path, 'w', encoding='utf-8') as f:
            json.dump(data, f, indent=2, ensure_ascii=False)

        updated += 1

    print(f"\n[*] Updated {updated} files")
    print(f"    Added kind: {added_kind}")
    print(f"    Changed kind: {changed_kind}")

    # Report kind distribution
    kind_stats = {}
    for fname in os.listdir(STRUCTS_DIR):
        if not fname.endswith('.json'):
            continue
        with open(os.path.join(STRUCTS_DIR, fname), 'r', encoding='utf-8') as f:
            data = json.load(f)
        k = data.get('kind', 'struct')
        kind_stats[k] = kind_stats.get(k, 0) + 1

    print(f"\n[*] Kind distribution in annotations:")
    for k, count in sorted(kind_stats.items()):
        print(f"    {k}: {count}")

if __name__ == '__main__':
    main()
