#!/usr/bin/env python3
"""
修复 Windows 不兼容的文件名
将特殊字符替换为安全字符
"""

import os
import subprocess
import re
from pathlib import Path

def get_problematic_files():
    """获取所有有问题的文件"""
    result = subprocess.run(
        ['git', 'ls-files'],
        capture_output=True,
        text=True
    )

    files = result.stdout.strip().split('\n')
    problematic = []

    for file in files:
        # Windows 不允许的字符: < > : " / \ | ? *
        # 以及反引号
        if re.search(r'[<>:"/\\|?*`]', file):
            problematic.append(file)

    return problematic

def safe_filename(filename):
    """生成安全的文件名"""
    # 替换规则
    replacements = {
        '*': '_mul_',
        '+': '_add_',
        '-': '_sub_',
        '=': '_eq_',
        '<': '_lt_',
        '>': '_gt_',
        '!': '_not_',
        ':': '_',
        '`': '',
        "'": '',
        '"': '',
    }

    safe = filename
    for char, replacement in replacements.items():
        safe = safe.replace(char, replacement)

    return safe

def rename_file_in_git(old_path, new_path):
    """在 Git 中重命名文件"""
    # 使用 git mv 重命名
    result = subprocess.run(
        ['git', 'mv', old_path, new_path],
        capture_output=True,
        text=True
    )

    if result.returncode != 0:
        print(f"  Warning: {result.stderr.strip()}")
        return False
    return True

def main():
    print("=" * 70)
    print("修复 Windows 不兼容的文件名")
    print("=" * 70)

    os.chdir(Path(__file__).parent)

    # 获取有问题的文件
    problematic = get_problematic_files()

    if not problematic:
        print("\n[OK] No problematic files found")
        return

    print(f"\n找到 {len(problematic)} 个有问题的文件\n")

    renamed = 0
    failed = 0

    for old_path in problematic:
        # 生成新文件名
        dir_path = os.path.dirname(old_path)
        old_name = os.path.basename(old_path)
        new_name = safe_filename(old_name)
        new_path = os.path.join(dir_path, new_name)

        if old_name == new_name:
            continue

        print(f"重命名:")
        print(f"  旧: {old_name}")
        print(f"  新: {new_name}")

        if rename_file_in_git(old_path, new_path):
            renamed += 1
            print(f"  [OK] Success\n")
        else:
            failed += 1
            print(f"  [FAIL] Failed\n")

    print("=" * 70)
    print(f"完成: {renamed} 个文件已重命名, {failed} 个失败")
    print("=" * 70)

    if renamed > 0:
        print("\n下一步:")
        print("  git status  # 查看改动")
        print("  git commit -m 'Fix Windows incompatible filenames'")

if __name__ == "__main__":
    main()
