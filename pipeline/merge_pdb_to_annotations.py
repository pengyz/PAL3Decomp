#!/usr/bin/env python3
"""一次性脚本：将 PDB 数据合并到 annotation 文件中。

迁移后 annotation 成为唯一数据源，PDB 不再参与管线。

使用:
  python pipeline/merge_pdb_to_annotations.py
"""

import json
import os
import re

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PDB_FILE = os.path.join(PROJECT_ROOT, "data", "pdb", "pdb_export.json")
ANN_DIR = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")

# 跳过系统类型
_SKIP_TYPES = {
    '_DIMOUSESTATE', '_DIMOUSESTATE2', '_DIJOYSTATE', '_DIJOYSTATE2',
    '_DIDEVCAPS', '_DIDEVICEINSTANCEA', '_DIDEVICEOBJECTINSTANCEA',
    'DIMOUSESTATE', 'DIMOUSESTATE2', 'DIJOYSTATE', 'DIJOYSTATE2',
    'tagRECT', 'tagPOINT', 'tagSIZE', 'tagMSG', 'RECT', 'POINT', 'SIZE',
    'WNDCLASSA', 'tagWNDCLASSA', '_WIN32_FIND_DATAA',
    '_FILETIME', '_SYSTEMTIME', '_MEMORYSTATUS', '_SECURITY_ATTRIBUTES',
    '_OSVERSIONINFOA', '_STARTUPINFOA', '_GUID', 'GUID', 'IID',
    'D3DMATRIX', '_D3DMATRIX', 'D3DVECTOR', '_D3DVECTOR',
    '_iobuf', 'FILE',
}


def load_pdb():
    with open(PDB_FILE) as f:
        return json.load(f)


def load_annotations(name):
    path = os.path.join(ANN_DIR, f"{name}.json")
    if os.path.exists(path):
        with open(path) as f:
            return json.load(f)
    return None


def save_annotation(name, data):
    path = os.path.join(ANN_DIR, f"{name}.json")
    # Ensure known_members keys are strings (JSON requires string keys)
    km = {}
    for k, v in data.get("known_members", {}).items():
        km[str(k)] = v
    data["known_members"] = km

    with open(path, "w") as f:
        json.dump(data, f, indent=2, ensure_ascii=False)
        f.write("\n")
    print(f"  ✓ {name}")


def main():
    pdb = load_pdb()
    classes = pdb.get("classes", [])
    print(f"PDB 类: {len(classes)}")

    updated = 0
    created = 0
    skipped = 0

    for cls in classes:
        name = cls.get("name", "")
        if not name or name in _SKIP_TYPES:
            continue
        if "<" in name or "::" in name:
            continue
        data_members = cls.get("data_members", [])
        if not data_members:
            continue

        # 获取或创建 annotation
        ann = load_annotations(name)
        if ann is None:
            ann = {
                "name": name,
                "binary_size": cls.get("size", 0),
                "known_members": {},
            }
            created += 1
        elif ann.get("members_mode") == "replace":
            # replace 模式的 annotation 保持原样（手动管理）
            skipped += 1
            continue

        # 合并 base_class（PDB 的 bases → annotation 的 base_class）
        pdb_bases = cls.get("bases", [])
        ann.setdefault("base_class", [])
        if isinstance(ann.get("base_class"), str):
            ann["base_class"] = [ann["base_class"]]  # 统一为 list
        for b in pdb_bases:
            bc_name = b.get("name", "")
            if bc_name and bc_name not in ann.get("base_class", []):
                ann.setdefault("base_class", []).append(bc_name)

        # 合并 base_size
        if pdb_bases:
            _bs = 0
            for b in pdb_bases:
                bc_cls = next((c for c in classes if c.get("name") == b.get("name")), None)
                if bc_cls:
                    _bs += bc_cls.get("size", 0)
            if _bs > 0 and not ann.get("base_size"):
                ann["base_size"] = _bs

        # PDB 的偏移 → member 映射
        pdb_by_offset = {}
        for m in data_members:
            off = m["offset"]
            pdb_by_offset[off] = m

        # annotation 已有的偏移
        ann_offsets = set()
        for k in ann.get("known_members", {}):
            try:
                ann_offsets.add(int(k.split("_")[0]))
            except ValueError:
                pass

        # 补充 PDB 有但 annotation 无的成员
        added = 0
        first_offset = min(pdb_by_offset.keys()) if pdb_by_offset else 0
        for off in sorted(pdb_by_offset.keys()):
            if off in ann_offsets:
                continue
            pm = pdb_by_offset[off]
            ann.setdefault("known_members", {})[str(off)] = {
                "name": f"_field_{off:04X}",
                "type": pm["type"],
                "source": "pdb_merge",
            }
            added += 1

        if added > 0 or created:
            ann["binary_size"] = cls.get("size", ann.get("binary_size", 0))
            save_annotation(name, ann)
            updated += 1
        else:
            skipped += 1
        else:
            skipped += 1

    print(f"\n完成: {updated} 更新, {created} 创建, {skipped} 跳过")


if __name__ == "__main__":
    main()
