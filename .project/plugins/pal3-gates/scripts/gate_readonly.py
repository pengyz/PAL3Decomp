#!/usr/bin/env python3
"""PreToolUse gate: 保护管线脚本不被 LLM 修改"""
import json, sys, os, fnmatch

input_data = json.load(sys.stdin)
tool_input = input_data.get("tool_input", {})
file_path = tool_input.get("file_path", tool_input.get("path", ""))

if not file_path:
    sys.exit(0)

# 规范化路径
file_path = file_path.replace("\\", "/")

# 白名单
whitelist = ["*/data/annotations/*", "*/docs/*", "*/.project/*"]
for pattern in whitelist:
    if fnmatch.fnmatch(file_path, pattern):
        sys.exit(0)

# 阻止管线脚本修改
blocked = ["*/pipeline/*.py", "*/pipeline/ida/*.py", "*/pipeline/gen/*.py", "*/pipeline/hooks/*"]
for pattern in blocked:
    if fnmatch.fnmatch(file_path, pattern):
        print(json.dumps({"reason": f"禁止修改管线脚本 {file_path}。反编译迭代中只允许修改 annotations 数据。如需修改脚本，请先告知用户获得确认。"}))
        sys.exit(2)

sys.exit(0)
