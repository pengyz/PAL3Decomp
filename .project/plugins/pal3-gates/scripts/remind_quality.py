#!/usr/bin/env python3
"""Notification hook (interval=5): 行为审计 — 检查 AI 是否遵守规则

v4 适配：不再空洞提醒"保持质量"，而是检查具体违规：
1. AI 是否在更新 activity 面板（通过检查 .project/data/ 文件）
2. 是否有连续修改无 commit
3. 是否有未验证就修改的迹象
"""
import json, subprocess, sys, os
from datetime import datetime

project = os.environ.get("AIDE_PROJECT_ROOT", r"D:\workspace\PAL3Decomp")
os.chdir(project)

issues = []

# 检查是否有未 commit 的 annotations 变更
try:
    result = subprocess.run(
        ["git", "status", "--porcelain", "--", "data/annotations/"],
        capture_output=True, text=True, cwd=project
    )
    dirty_files = [l for l in result.stdout.strip().split("\n") if l.strip()]
    if len(dirty_files) > 3:
        issues.append(
            f"你有 {len(dirty_files)} 个未提交的 annotations 文件。"
            "请验证后尽快 commit，避免大量未保存的修改丢失。"
        )
except Exception:
    pass

# 检查 check_annotations 是否通过（快速验证）
try:
    check = subprocess.run(
        [sys.executable, "pipeline/check_annotations.py"],
        capture_output=True, text=True, timeout=15, cwd=project
    )
    if check.returncode != 0:
        issues.append(
            "⚠️ annotations 当前有验证错误！在继续新修改前，请先修复现有错误。"
        )
except Exception:
    pass

if issues:
    print(json.dumps({"message": "\n".join(issues)}))

sys.exit(0)
