#!/usr/bin/env python3
"""从 PDB 提取类函数定义合并到 annotation struct 文件中。

流程:
1. 对每个有 class 的 PDB 函数，添加到 struct/*.json 的 methods 字段
2. 用 functions.json 覆盖（functions.json 的签名更准确）
"""

import json
import os
import re

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PDB_FILE = os.path.join(PROJECT_ROOT, "data", "pdb", "pdb_export.json")
ANN_FUNCS_FILE = os.path.join(PROJECT_ROOT, "data", "annotations", "functions.json")
ANN_STRUCTS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")


def pdb_sig_to_str(return_type, params):
    """Convert PDB signature components to signature string."""
    ret = return_type or "int"
    param_strs = []
    for p in params:
        param_strs.append(p.get("type", "int"))
    return "%s (%s)" % (ret, ", ".join(param_strs))


def main():
    pdb = json.load(open(PDB_FILE))
    ann_funcs = json.load(open(ANN_FUNCS_FILE))

    pdb_functions = pdb.get("functions", [])
    funcs_by_addr = {}
    for f in pdb_functions:
        cls = f.get("class", "")
        if not cls or cls == ">" or "std::" in cls:
            continue
        name = f.get("name", "")
        addr_str = f.get("address", "")
        if not addr_str:
            continue
        addr = int(addr_str, 16)
        # Extract simple method name: "ClassName::Method" -> "Method"
        if "::" in name:
            simple_name = name.split("::", 1)[1]
        else:
            simple_name = name
        # Skip adjustor thunks
        if "`adjustor" in simple_name or "`vcall" in simple_name:
            continue

        sig = pdb_sig_to_str(f.get("return_type"), f.get("parameters", []))
        funcs_by_addr.setdefault(cls, {})[addr] = {
            "name": simple_name,
            "signature": sig,
            "source": "pdb",
        }

    # Apply functions.json overlay (more accurate signatures)
    for addr_str, finfo in ann_funcs.items():
        addr = int(addr_str, 16)
        ann_name = finfo.get("name", "")
        ann_sig = finfo.get("signature", "")
        if not ann_name:
            continue
        if "::" in ann_name:
            cls = ann_name.split("::")[0]
            simple_name = ann_name.split("::", 1)[1]
            if cls in funcs_by_addr and addr in funcs_by_addr[cls]:
                funcs_by_addr[cls][addr]["name"] = simple_name
                funcs_by_addr[cls][addr]["signature"] = ann_sig
                funcs_by_addr[cls][addr]["source"] = "annotation"
            elif cls in funcs_by_addr:
                funcs_by_addr[cls][addr] = {
                    "name": simple_name,
                    "signature": ann_sig,
                    "source": "annotation",
                }

    # 写入 struct annotation 文件
    updated = 0
    created = 0
    for cls, methods in funcs_by_addr.items():
        path = os.path.join(ANN_STRUCTS_DIR, f"{cls}.json")
        if os.path.exists(path):
            with open(path) as f:
                ann = json.load(f)
        else:
            ann = {"name": cls, "known_members": {}}
            created += 1

        # 转 methods dict: address -> {name, signature, source}
        methods_dict = {}
        for addr, minfo in methods.items():
            methods_dict["0x%08X" % addr] = minfo

        ann["methods"] = methods_dict
        with open(path, "w") as f:
            json.dump(ann, f, indent=2, ensure_ascii=False)
            f.write("\n")
        updated += 1

    print(f"更新: {updated} struct files (含 methods)")
    print(f"创建: {created} 新 struct files")


if __name__ == "__main__":
    main()
