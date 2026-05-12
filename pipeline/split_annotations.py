#!/usr/bin/env python3
"""
将 annotations.json 拆分为多文件结构。

输入: asm/pal3/annotations.json (单文件，1.8MB)
输出: asm/pal3/annotations/ 目录
  ├── manifest.json
  ├── functions.json
  ├── globals.json
  ├── structs/
  │   ├── CCBSystem.json
  │   └── ...
  ├── vtables.json
  └── enums.json

用法: python3 tools/split_annotations.py
"""

import json
import os
import sys

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OLD_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "annotations.json")
OUT_DIR = os.path.join(PROJECT_ROOT, "pipeline", "data", "annotations")


def split():
    if not os.path.exists(OLD_FILE):
        print(f"[!] Not found: {OLD_FILE}")
        sys.exit(1)

    with open(OLD_FILE, "r", encoding="utf-8") as f:
        data = json.load(f)

    os.makedirs(OUT_DIR, exist_ok=True)
    structs_dir = os.path.join(OUT_DIR, "structs")
    os.makedirs(structs_dir, exist_ok=True)

    # 1. functions.json
    funcs = data.get("functions", {})
    with open(os.path.join(OUT_DIR, "functions.json"), "w", encoding="utf-8") as f:
        json.dump(funcs, f, ensure_ascii=False, indent=2)
        f.write("\n")
    print(f"  functions.json: {len(funcs)} entries")

    # 2. globals.json
    globs = data.get("globals", {})
    with open(os.path.join(OUT_DIR, "globals.json"), "w", encoding="utf-8") as f:
        json.dump(globs, f, ensure_ascii=False, indent=2)
        f.write("\n")
    print(f"  globals.json: {len(globs)} entries")

    # 3. structs/ (每个 struct 一个文件)
    structs = data.get("structs", {})
    struct_files = []
    for sname, sinfo in sorted(structs.items()):
        safe_name = sname.replace("::", "_").replace("<", "_").replace(">", "_")
        fname = f"{safe_name}.json"
        struct_files.append(fname)
        with open(os.path.join(structs_dir, fname), "w", encoding="utf-8") as f:
            json.dump({"name": sname, **sinfo}, f, ensure_ascii=False, indent=2)
            f.write("\n")
    print(f"  structs/: {len(struct_files)} files")

    # 4. vtables.json
    vtables = data.get("vtables", {})
    with open(os.path.join(OUT_DIR, "vtables.json"), "w", encoding="utf-8") as f:
        json.dump(vtables, f, ensure_ascii=False, indent=2)
        f.write("\n")
    print(f"  vtables.json: {len(vtables)} entries")

    # 5. enums.json
    enums = data.get("enums", {})
    with open(os.path.join(OUT_DIR, "enums.json"), "w", encoding="utf-8") as f:
        json.dump(enums, f, ensure_ascii=False, indent=2)
        f.write("\n")
    print(f"  enums.json: {len(enums)} entries")

    # 6. manifest.json
    manifest = {
        "version": 3,
        "description": "PAL3.exe annotations (split format)",
        "stats": {
            "functions": len(funcs),
            "globals": len(globs),
            "structs": len(structs),
            "vtables": len(vtables),
            "enums": len(enums),
        },
        "struct_files": struct_files,
    }
    with open(os.path.join(OUT_DIR, "manifest.json"), "w", encoding="utf-8") as f:
        json.dump(manifest, f, ensure_ascii=False, indent=2)
        f.write("\n")

    print(f"\n[*] Split complete: {OUT_DIR}")


if __name__ == "__main__":
    split()
