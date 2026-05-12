#!/usr/bin/env python3
"""
将拆分后的 annotations 目录合并回单个 JSON。

用途:
  1. 兼容旧工具（apply_annotations.py 等）
  2. 验证拆分/合并一致性

用法: python3 tools/merge_annotations.py [--output FILE]
"""

import json
import os
import sys
import argparse

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN_DIR = os.path.join(PROJECT_ROOT, "pipeline", "data", "annotations")
DEFAULT_OUTPUT = os.path.join(PROJECT_ROOT, "asm", "pal3", "annotations.json")


def merge(output_path=None):
    if output_path is None:
        output_path = DEFAULT_OUTPUT

    if not os.path.isdir(ANN_DIR):
        print(f"[!] Not found: {ANN_DIR}")
        sys.exit(1)

    manifest_path = os.path.join(ANN_DIR, "manifest.json")
    if not os.path.exists(manifest_path):
        print(f"[!] No manifest.json in {ANN_DIR}")
        sys.exit(1)

    with open(manifest_path, "r", encoding="utf-8") as f:
        manifest = json.load(f)

    # Load functions
    with open(os.path.join(ANN_DIR, "functions.json"), "r", encoding="utf-8") as f:
        functions = json.load(f)

    # Load globals
    with open(os.path.join(ANN_DIR, "globals.json"), "r", encoding="utf-8") as f:
        globals_data = json.load(f)

    # Load structs (from individual files)
    structs = {}
    structs_dir = os.path.join(ANN_DIR, "structs")
    for fname in sorted(os.listdir(structs_dir)):
        if not fname.endswith(".json"):
            continue
        with open(os.path.join(structs_dir, fname), "r", encoding="utf-8") as f:
            sdata = json.load(f)
        sname = sdata.pop("name", fname.replace(".json", ""))
        structs[sname] = sdata

    # Load vtables
    with open(os.path.join(ANN_DIR, "vtables.json"), "r", encoding="utf-8") as f:
        vtables = json.load(f)

    # Load enums
    enums_path = os.path.join(ANN_DIR, "enums.json")
    enums = {}
    if os.path.exists(enums_path):
        with open(enums_path, "r", encoding="utf-8") as f:
            enums = json.load(f)

    # Assemble
    result = {
        "version": manifest.get("version", 3),
        "description": manifest.get("description", ""),
        "functions": functions,
        "globals": globals_data,
        "structs": structs,
        "enums": enums,
        "vtables": vtables,
    }

    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(result, f, ensure_ascii=False, indent=2)
        f.write("\n")

    print(f"[*] Merged: {len(functions)} funcs, {len(globals_data)} globals, "
          f"{len(structs)} structs, {len(vtables)} vtables → {output_path}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", "-o", default=None)
    args = parser.parse_args()
    merge(args.output)
