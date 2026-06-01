#!/usr/bin/env python3
"""从 PDB 生成完整 annotation，用旧 annotation 的语义命名覆盖。

流程:
1. 备份 data/annotations/ 到 data/annotations.bak/
2. 对每个有 data_members 的 PDB struct，生成 annotation 文件
3. 旧 annotation 的 known_members（按偏移）覆盖 PDB 生成的名字和类型
4. PDB 有但旧 annotation 无的成员，保留 PDB 原名
5. PDB 有 bases 的，写入 base_class
"""

import json
import os
import re
import shutil

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PDB_FILE = os.path.join(PROJECT_ROOT, "data", "pdb", "pdb_export.json")
ANN_DIR = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")
BACKUP_DIR = os.path.join(PROJECT_ROOT, "data", "annotations.bak")

_SKIP_TYPES = {
    '_DIMOUSESTATE','_DIMOUSESTATE2','_DIJOYSTATE','_DIJOYSTATE2',
    '_DIDEVCAPS','_DIDEVICEINSTANCEA','_DIDEVICEOBJECTINSTANCEA',
    'DIMOUSESTATE','DIMOUSESTATE2','DIJOYSTATE','DIJOYSTATE2',
    'tagRECT','tagPOINT','tagSIZE','tagMSG','RECT','POINT','SIZE',
    'WNDCLASSA','tagWNDCLASSA','_WIN32_FIND_DATAA',
    '_FILETIME','_SYSTEMTIME','_MEMORYSTATUS','_SECURITY_ATTRIBUTES',
    '_OSVERSIONINFOA','_STARTUPINFOA','_GUID','_iobuf','FILE',
}


def main():
    pdb = json.load(open(PDB_FILE))
    classes = pdb.get("classes", [])

    # Step 1: 备份旧 annotation
    if os.path.exists(ANN_DIR):
        if os.path.exists(BACKUP_DIR):
            shutil.rmtree(BACKUP_DIR)
        shutil.copytree(ANN_DIR, BACKUP_DIR)
        print(f"备份旧 annotation → {BACKUP_DIR}/")
    else:
        os.makedirs(ANN_DIR, exist_ok=True)

    # 加载旧 annotation
    old_ann = {}
    if os.path.exists(BACKUP_DIR):
        for fname in os.listdir(BACKUP_DIR):
            if not fname.endswith(".json"):
                continue
            with open(os.path.join(BACKUP_DIR, fname)) as f:
                s = json.load(f)
            old_ann[s.get("name", fname.replace(".json", ""))] = s

    # 构建 className → size 映射（用于 base_size 计算）
    pdb_size_map = {c["name"]: c.get("size", 0) for c in classes if c.get("name")}

    created = 0
    updated = 0
    skipped = 0

    for cls in classes:
        name = cls.get("name", "")
        if not name or name in _SKIP_TYPES:
            continue
        if "<" in name or "::" in name:
            continue
        pdb_members = cls.get("data_members", [])
        if not pdb_members:
            continue

        # 新 annotation：从 PDB 数据生成
        new_ann = {
            "name": name,
            "binary_size": cls.get("size", 0),
            "known_members": {},
        }

        # 合并 base_class
        pdb_bases = cls.get("bases", [])
        if pdb_bases:
            new_ann["base_class"] = [b["name"] for b in pdb_bases]

        # 所有 PDB 成员写入新 annotation
        for m in pdb_members:
            off = str(m["offset"])
            new_ann["known_members"][off] = {
                "name": m["name"],
                "type": m["type"],
                "source": "pdb_merge",
            }

        # 冲突检测：同名字段在不同偏移 → 保留旧 annotation 偏移（PAL3 二进制分析更可信）
        if name in old_ann:
            old = old_ann[name]
            old_km = old.get("known_members", {})
            name_to_old_off = {}
            for k, v in old_km.items():
                try:
                    name_to_old_off[v.get("name", "")] = str(int(k.split("_")[0]))
                except:
                    pass
            # 删除 PDB 中与旧 annotation 同名但不同偏移的成员
            to_remove = []
            for off, m in new_ann["known_members"].items():
                if m["name"] in name_to_old_off and off != name_to_old_off[m["name"]]:
                    to_remove.append(off)
            for off in to_remove:
                del new_ann["known_members"][off]

        # 旧 annotation 覆盖：按偏移匹配，语义命名优先
        if name in old_ann:
            old = old_ann[name]
            old_km = old.get("known_members", {})
            for k, v in old_km.items():
                try:
                    off = str(int(k.split("_")[0]))
                except ValueError:
                    continue
                if off in new_ann["known_members"]:
                    # 旧 annotation 有更好的名字 → 覆盖
                    if v.get("name") and not v["name"].startswith(("_field_", "_todo_", "_gap_")):
                        new_ann["known_members"][off]["name"] = v["name"]
                        new_ann["known_members"][off]["source"] = "annotation"
                    # 旧 annotation 有明确的类型 → 覆盖（跳过 int）
                    vt = v.get("type", "")
                    if vt and vt != "int":
                        new_ann["known_members"][off]["type"] = vt
                        new_ann["known_members"][off]["source"] = "annotation"

            # 旧 annotation 中 PDB 没有的偏移 → 保留（如 vfptr）
            for k, v in old_km.items():
                try:
                    off = str(int(k.split("_")[0]))
                except ValueError:
                    continue
                if off not in new_ann["known_members"]:
                    new_ann["known_members"][off] = v

            # 旧 annotation 的 base_class 补充（不是替换——PDB 可能有多继承）
            old_bc = old.get("base_class")
            if old_bc:
                if isinstance(old_bc, str):
                    old_bc = [old_bc]
                for _bc in old_bc:
                    if _bc not in new_ann.get("base_class", []):
                        new_ann.setdefault("base_class", []).append(_bc)

            # 旧 annotation 的 binary_size 覆盖
            old_bs = old.get("binary_size")
            if old_bs and old_bs != cls.get("size"):
                new_ann["binary_size"] = old_bs

        # 写回
        out_path = os.path.join(ANN_DIR, f"{name}.json")
        # 确保 known_members key 是字符串
        km = {}
        for k, v in new_ann["known_members"].items():
            km[str(k)] = v
        new_ann["known_members"] = km

        with open(out_path, "w") as f:
            json.dump(new_ann, f, indent=2, ensure_ascii=False)
            f.write("\n")

        if name in old_ann:
            updated += 1
        else:
            created += 1

    # 验证
    ann_files = [f for f in os.listdir(ANN_DIR) if f.endswith(".json")]
    pdb_with_members = sum(1 for c in classes if c.get("data_members")
                          and c.get("name") and c["name"] not in _SKIP_TYPES
                          and "<" not in c["name"] and "::" not in c["name"])

    print(f"\n结果:")
    print(f"  PDB 应有 struct（有 data_members）: {pdb_with_members}")
    print(f"  生成 annotation 文件: {len(ann_files)}")
    print(f"  创建: {created}, 更新: {updated}")
    print(f"  覆盖率: {len(ann_files)}/{pdb_with_members}")
    print(f"  备份旧 annotation 在: {BACKUP_DIR}/")


if __name__ == "__main__":
    main()
