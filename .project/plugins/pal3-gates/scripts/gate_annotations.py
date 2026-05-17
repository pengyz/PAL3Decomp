#!/usr/bin/env python3
"""PreToolUse gate: 写入 annotations 前必须通过验证。exit 0=允许, exit 2=阻止"""
import json, subprocess, sys, os

project = os.environ.get("AIDE_PROJECT_ROOT", r"D:\workspace\PAL3Decomp")
os.chdir(project)

result = subprocess.run([sys.executable, "pipeline/check_annotations.py"], capture_output=True, text=True)
if result.returncode != 0:
    output = result.stdout + result.stderr
    print(json.dumps({"reason": f"Annotations 验证失败，禁止写入。请先修复：\n\n{output}"}))
    sys.exit(2)
sys.exit(0)
