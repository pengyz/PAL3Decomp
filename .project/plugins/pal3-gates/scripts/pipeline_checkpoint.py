#!/usr/bin/env python3
"""Notification hook (interval=15): 周期性收集度量，自动更新面板 + 趋势追踪

通过 slot_updates 自动写入 naming_rate 和 progress_trend。
有异常时额外输出 content 注入 system-reminder 提醒 LLM。
"""
import json, subprocess, sys, os, re
from datetime import datetime

project = os.environ.get("AIDE_PROJECT_ROOT", r"D:\workspace\PAL3Decomp")
ann_dir = os.path.join(project, "data", "annotations")

# ═══ 收集度量 ═══

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

# 结构体字段命名率
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

# Annotations 验证
os.chdir(project)
check = subprocess.run([sys.executable, "pipeline/check_annotations.py"],
                       capture_output=True, text=True, timeout=30)
ann_ok = check.returncode == 0

# 最近 commit
try:
    git_log = subprocess.run(["git", "log", "-1", "--format=%ar"],
                             capture_output=True, text=True, cwd=project)
    last_commit = git_log.stdout.strip()
except Exception:
    last_commit = "unknown"

# ═══ 构建输出 ═══

today = datetime.now().strftime("%m-%d %H:%M")
output = {
    "slot_updates": {
        "naming_rate": naming_rate,
        "progress_trend": {
            "_append": {
                "date": today,
                "compile": "0",
                "match": "0",
                "naming": str(naming_rate),
            }
        }
    }
}

# 有问题时注入提醒
issues = []
if not ann_ok:
    issues.append("annotations 验证失败，立即修复")
if "hour" in last_commit or "day" in last_commit:
    issues.append(f"上次 commit 是 {last_commit}，应更频繁提交")

if issues:
    output["content"] = "## 检查点告警\n\n- " + "\n- ".join(issues)

print(json.dumps(output))
sys.exit(0)
