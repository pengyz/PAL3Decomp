#!/usr/bin/env python3
"""PostToolUse hook: git commit 成功后自动收集度量写入 DataStore

通过 slot_updates 约定自动更新面板，不依赖 LLM 记得 data_write。
Claude Code 环境下忽略 slot_updates，仅显示 additional_context。
"""
import json, subprocess, sys, os, re

input_data = json.load(sys.stdin)
tool_success = input_data.get("tool_success", False)

if not tool_success:
    sys.exit(0)

project = os.environ.get("AIDE_PROJECT_ROOT", r"D:\workspace\PAL3Decomp")
ann_dir = os.path.join(project, "data", "annotations")

# ═══ 收集度量 ═══

# 字段命名率
member_total = member_named = 0
struct_dir = os.path.join(ann_dir, "structs")
try:
    for f in os.listdir(struct_dir):
        if not f.endswith(".json"):
            continue
        s = json.load(open(os.path.join(struct_dir, f), encoding="utf-8"))
        for mb in s.get("known_members", {}).values():
            member_total += 1
            name = mb.get("name", "")
            if not re.match(r'^_field_|^_todo_', name):
                member_named += 1
except Exception:
    pass

naming_rate = round(member_named / max(member_total, 1) * 100, 1)

# 函数命名率
func_named = func_total = 0
try:
    funcs = json.load(open(os.path.join(ann_dir, "functions.json"), encoding="utf-8"))
    func_total = len(funcs)
    func_named = sum(1 for f in funcs.values()
                     if f.get("name", "").strip()
                     and not f["name"].startswith("sub_")
                     and not f["name"].startswith("nullsub_"))
except Exception:
    pass

func_rate = round(func_named / max(func_total, 1) * 100, 1)

# ═══ 输出（slot_updates 自动写入面板 + additional_context 给 LLM 参考）═══
output = {
    "additional_context": f"字段命名率={naming_rate}% ({member_named}/{member_total}), 函数命名率={func_rate}% ({func_named}/{func_total})",
    "slot_updates": {
        "naming_rate": naming_rate,
    }
}

print(json.dumps(output))
sys.exit(0)
