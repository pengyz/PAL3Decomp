#!/usr/bin/env python3
"""
批量删除 annotations/structs/*.json 中的 kind 字段

原因：PDB 的 kind 字段来自 PAL3A，与 PAL3.exe 实际布局不匹配。
强制使用这些 kind 值导致 IDA 导入错误类型定义，最终编译结果大幅退步。
"""
import json
import os
import sys

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STRUCTS_DIR = os.path.join(PROJECT_ROOT, "data", "annotations", "structs")

def main():
    if not os.path.isdir(STRUCTS_DIR):
        print(f"[!] Structs directory not found: {STRUCTS_DIR}")
        return 1

    modified = 0
    skipped = 0

    for filename in os.listdir(STRUCTS_DIR):
        if not filename.endswith('.json'):
            continue

        filepath = os.path.join(STRUCTS_DIR, filename)
        with open(filepath, 'r', encoding='utf-8') as f:
            data = json.load(f)

        if 'kind' in data:
            del data['kind']
            with open(filepath, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=2, ensure_ascii=False)
                f.write('\n')
            modified += 1
        else:
            skipped += 1

    print(f"[*] Modified: {modified}, Skipped: {skipped}")
    return 0

if __name__ == '__main__':
    sys.exit(main())
