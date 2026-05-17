#!/usr/bin/env python3
"""Stop hook: v4.0 自主循环模式的停止控制。

策略：
- 报错/异常停止 → 允许（exit 0）
- 用户明确要求停止 → 允许（exit 0）
- 正常结束（AI 认为做完了）→ 检查是否还有工作，有则阻止（exit 2）
"""
import json
import sys
import os
import re

input_data = json.load(sys.stdin)
turn = input_data.get("turn", 0)
last_msg = input_data.get("last_assistant_message", "")[:1000]

# ════════════════════════════════════════
# 1. 无条件允许停止的情况
# ════════════════════════════════════════

# 用户明确要求
user_stop = ["根据你的要求", "按照你的指示停止", "用户要求停止", "按你说的"]
for kw in user_stop:
    if kw in last_msg:
        sys.exit(0)

# 致命错误（无法自行恢复）
fatal = ["IDA 崩溃", "无法启动", "permission denied", "disk full",
         "编译环境损坏", "i64 文件损坏", "raw.i64 不存在", "磁盘空间不足"]
for kw in fatal:
    if kw in last_msg.lower() or kw in last_msg:
        sys.exit(0)

# 检测错误/异常模式 — 如果 AI 因为反复出错而停止，允许
error_patterns = [
    r"连续\d+次.*失败",
    r"无法.*恢复",
    r"回退.*修改",
    r"error.*无法解决",
    r"check_annotations.*报错.*回退",
]
for pat in error_patterns:
    if re.search(pat, last_msg):
        sys.exit(0)

# ════════════════════════════════════════
# 2. 检查是否还有工作可做
# ════════════════════════════════════════

project = os.environ.get("AIDE_PROJECT_ROOT", r"D:\workspace\PAL3Decomp")
ann_dir = os.path.join(project, "pipeline", "data", "annotations")
struct_dir = os.path.join(ann_dir, "structs")

has_work = False
work_hints = []

try:
    # 检查未命名字段数
    todo_count = 0
    total_members = 0
    for f in os.listdir(struct_dir):
        if not f.endswith(".json"):
            continue
        with open(os.path.join(struct_dir, f), encoding="utf-8") as fh:
            d = json.load(fh)
        for m in d.get("known_members", {}).values():
            total_members += 1
            if re.match(r"^(_todo_|_field_)", m.get("name", "")):
                todo_count += 1

    if todo_count > 0:
        has_work = True
        naming_pct = round((total_members - todo_count) / max(total_members, 1) * 100, 1)
        work_hints.append(f"还有 {todo_count} 个未命名字段（命名率 {naming_pct}%）")

    # 检查未命名函数数
    funcs_file = os.path.join(ann_dir, "functions.json")
    if os.path.exists(funcs_file):
        with open(funcs_file, encoding="utf-8") as fh:
            funcs = json.load(fh)
        sub_count = sum(1 for f in funcs.values()
                       if f.get("name", "").startswith("sub_"))
        if sub_count > 0:
            has_work = True
            work_hints.append(f"还有 {sub_count} 个 sub_ 函数待命名")

except Exception:
    # 无法检查状态时，保守策略：允许停止
    sys.exit(0)

# ════════════════════════════════════════
# 3. 决策
# ���═══════════════════════════════════════

if not has_work:
    # 真的没工作了，允许停止
    sys.exit(0)

# 还有工作，阻止停止并给出具体建议
hints_text = "\n".join(f"  - {h}" for h in work_hints)
reason = f"""反编译工作尚未完成：
{hints_text}

请继续工作循环：
1. 运行 `python pipeline/check_annotations.py` 确认当前状态
2. 选择下一个高 ROI 目标（编译错误 > 高引用未命名字段 > 接近完成的类）
3. 收集证据 → 修改 → 验证 → 记录 → commit
4. 更新面板（data_write）"""

print(json.dumps({"reason": reason}))
sys.exit(2)
