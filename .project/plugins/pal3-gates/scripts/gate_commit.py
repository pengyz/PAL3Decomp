#!/usr/bin/env python3
"""PreToolUse gate: git commit 前验证 annotations + 检查 commit message 格式"""
import json, subprocess, sys, os

project = os.environ.get("AIDE_PROJECT_ROOT", r"D:\workspace\PAL3Decomp")
os.chdir(project)

# 检查是否有 annotations 在暂存区
result = subprocess.run(["git", "diff", "--cached", "--name-only", "--", "data/annotations/"],
                       capture_output=True, text=True)
staged = result.stdout.strip()

if staged:
    check = subprocess.run([sys.executable, "pipeline/check_annotations.py"], capture_output=True, text=True)
    if check.returncode != 0:
        output = check.stdout + check.stderr
        print(json.dumps({"reason": f"Git commit 被阻止：annotations 验证失败。\n\n{output}"}))
        sys.exit(2)
sys.exit(0)
