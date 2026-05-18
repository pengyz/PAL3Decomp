#!/bin/bash
# Stop hook: 轻量 stats 刷新 + 蒸馏经验 + 强制继续
PROJECT="${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}"

python3 << 'PY'
import json, sys, os

project = os.environ.get('AIDE_PROJECT_ROOT', '/home/peng/workspace/PAL3Decomp')

def quick_stats():
    """只读文件收集统计，不跑管线。"""
    result = {}
    try:
        funcs = json.load(open(f'{project}/data/annotations/functions.json'))
        named = sum(1 for v in funcs.values()
                    if v.get('name','').strip() and not v['name'].startswith('sub_'))
        total = len(funcs)
        pct = round(named / max(total, 1) * 100, 1)
        result['func_stats'] = f"## 函数维度\n\n命名率: **{pct}%** ({named}/{total})"
    except:
        pass
    try:
        struct_dir = f'{project}/data/annotations/structs'
        sc = sum(1 for f in os.listdir(struct_dir) if f.endswith('.json'))
        result['func_stats'] = result.get('func_stats', '## 函数维度\n') + f"\n结构体: {sc}"
    except:
        pass
    return result

# 读取 stdin
stdin_data = sys.stdin.read()
try:
    d = json.loads(stdin_data)
except:
    d = {}

last_msg = d.get('last_assistant_message', '')[:500]

# ── 合法停止检查 ──
fatal = ['IDA 崩溃', '无法启动', '编译环境', 'permission denied', 'disk full']
user_req = ['根据你的要求', '按照你的指示停止', '用户要求停止', 'as you requested']

for s in fatal + user_req:
    if s in last_msg:
        stats = quick_stats()
        if stats:
            print(json.dumps({'slot_updates': stats}))
        sys.exit(0)

# ── 不允许停止：轻量刷新 + 蒸馏 + 继续 ──
stats = quick_stats()

disc_path = f'{project}/discoveries.md'
existing = ''
try:
    with open(disc_path) as f:
        existing = f.read()
except:
    pass

reason = """本轮工作结束，执行经验蒸馏后继续。

**经验蒸馏：**
回顾本轮试错和最终方案，判断：

A) 通用规律（编译器行为/调用约定/代码模式，适用多个函数）：
   → Edit 融合到 discoveries.md（去重，按类别分组）

B) 结构化事实（类继承/函数签名/结构体大小确认）：
   → kb_add_entities 写入 Knowledge Base

C) 仅本次有效的特异操作：
   → 不写入

已有 discoveries.md：
```
""" + (existing[:1500] if existing else '（空文件）') + """
```

蒸馏完成后继续下一轮工作。"""

output = {'reason': reason}
if stats:
    output['slot_updates'] = stats
print(json.dumps(output))
sys.exit(2)
PY
