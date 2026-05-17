#!/usr/bin/env python3
"""PostToolUse: 每次工具调用后记录审计日志"""
import json, sys, os
from datetime import datetime

input_data = json.load(sys.stdin)
tool_name = input_data.get("tool_name", "")
tool_success = input_data.get("tool_success", True)
tool_input = input_data.get("tool_input", {})

# 摘要
path = tool_input.get("file_path", tool_input.get("path", ""))
cmd = tool_input.get("command", tool_input.get("cmd", ""))
summary = path or cmd[:80] or json.dumps(tool_input)[:80]

project = os.environ.get("AIDE_PROJECT_ROOT", r"D:\workspace\PAL3Decomp")
log_file = os.path.join(project, ".project", "audit.log")
os.makedirs(os.path.dirname(log_file), exist_ok=True)

ts = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
status = "OK" if tool_success else "FAIL"

with open(log_file, "a", encoding="utf-8") as f:
    f.write(f"{ts} | {tool_name} | {status} | {summary}\n")

sys.exit(0)
