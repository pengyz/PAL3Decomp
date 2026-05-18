#!/bin/bash
# 每 10 轮强制 LLM 总结经验
cat <<'JSON'
{"inject": "请总结本阶段工作中发现的新规律或技巧，追加到项目根目录的 discoveries.md 文件末尾。\n\n格式：每条一行，`- [类别] 描述`\n类别可选：compiler/struct/calling-convention/codegen/ida/pattern\n\n只输出新发现的条目，不重复已有内容。如果本轮没有新发现，写入 `- [none] 本轮无新发现` 并继续工作。"}
JSON
exit 0
