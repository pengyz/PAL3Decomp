#!/bin/bash
cat <<'JSON'
{"content": "## 质量门禁提醒\n\n1. **偏移必须有二进制证据** — 绝对地址或 reg+disp32\n2. **置信度 ≥ 80** 才能修改 offset/type\n3. **单字段验证** — 逐个确认，不批量推断\n4. **commit 前必须** `python pipeline/cli.py check`\n5. 用 `data_write` 更新迭代日志和进度面板"}
JSON
exit 0
