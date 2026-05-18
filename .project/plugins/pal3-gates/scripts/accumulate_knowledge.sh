#!/bin/bash
# Notification/10: 经验蒸馏 — 读取已有 → 判断 → 分流写入
# 使用 inject 强制 LLM 执行结构化的知识提炼

PROJECT="${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}"
DISC="$PROJECT/discoveries.md"

# 读取已有 discoveries 内容（供 LLM 去重判断）
existing=""
if [ -f "$DISC" ]; then
    existing=$(cat "$DISC")
fi

# 构造 inject 指令（含已有内容让 LLM 做融合判断）
python3 << PY
import json

existing = """$existing"""

prompt = f"""请执行知识蒸馏（这是自动触发的，不需要确认）：

**第一步：回顾本轮工作，判断是否有新的通用规律发现。**

通用规律的标准：
- 适用于本项目的多个函数/结构体（不是只对一个函数有效的特例）
- 关于编译器行为、调用约定、代码模式、工具使用技巧
- 未来遇到类似情况时可以直接复用

**第二步：分流处理。**

A) 如果发现了**通用规律**且下方已有条目中没有类似内容：
   → 用 Edit 工具将新条目融合到 discoveries.md 的合适位置（按类别分组）
   → 如果已有类似条目但不精确，更新已有条目而非追加新条目

B) 如果发现了**结构化事实**（如某类的继承关系、某函数的确切签名、某结构体的确认大小）：
   → 用 kb_add_entities 写入 Knowledge Base

C) 如果本轮只有**特异性操作**（只对当前函数有效的临时修复）：
   → 不写入任何文件，直接说"本轮无通用规律发现"并继续工作

**已有 discoveries.md 内容（用于去重和融合）：**
```
{existing if existing else '（空文件，首次写入）'}
```

请按上述规则执行。完成后继续正常的反编译工作。"""

print(json.dumps({{"inject": prompt}}))
PY
