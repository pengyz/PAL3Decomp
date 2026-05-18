#!/bin/bash
# Stop hook: 蒸馏本轮经验 → 然后决定是否允许停止
#
# 逻辑：
# 1. 检查是否有合法停止理由（致命错误/用户要求）→ 允许停止
# 2. 否则：inject 蒸馏指令 + 强制继续
#    LLM 完成蒸馏后继续下一轮工作

PROJECT="${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}"
DISC="$PROJECT/discoveries.md"

input=$(cat)

python3 << PY
import json, sys, os

input_data = '''$(echo "$input" | sed "s/'/'\\\\''/g")'''
try:
    d = json.loads(input_data)
except:
    d = {}

last_msg = d.get('last_assistant_message', '')[:500]

# 检查合法停止理由
fatal_signals = ['IDA 崩溃', '无法启动', '编译环境', 'permission denied', 'disk full']
user_signals = ['根据你的要求', '按照你的指示停止', '用户要求停止', 'as you requested']

for s in fatal_signals:
    if s in last_msg:
        print('{}')  # 空输出 = exit 0 = 允许停止
        sys.exit(0)

for s in user_signals:
    if s in last_msg:
        print('{}')
        sys.exit(0)

# 不允许停止 — 先蒸馏经验，再继续工作
disc_path = os.environ.get('AIDE_PROJECT_ROOT', '/home/peng/workspace/PAL3Decomp') + '/discoveries.md'
existing = ''
try:
    with open(disc_path) as f:
        existing = f.read()
except:
    pass

reason = f"""本轮工作结束，执行经验蒸馏后继续下一轮。

**经验蒸馏（必须执行）：**

回顾本轮工作过程（包括试错和最终方案），判断：

A) **通用规律**（适用于多个函数/结构体的编译器行为、调用约定、代码模式）：
   → 读取 discoveries.md，用 Edit 融合新条目（去重，按类别分组，更新不精确的旧条目）

B) **结构化事实**（确认的类继承关系、函数签名、结构体大小）：
   → 用 kb_add_entities 写入 Knowledge Base

C) **仅本次有效的特异操作**：
   → 不写入，直接进入下一轮

已有 discoveries.md：
```
{existing[:2000] if existing else '（空文件）'}
```

**蒸馏完成后，继续选择下一个目标函数进行反编译工作。**"""

print(json.dumps({"reason": reason}))
sys.exit(2)  # exit 2 = 强制继续
PY
