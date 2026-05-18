#!/bin/bash
input=$(cat)
last_msg=$(echo "$input" | python3 -c "import sys,json; print(json.load(sys.stdin).get('last_assistant_message','')[:500])" 2>/dev/null || echo "")
case "$last_msg" in
    *"IDA 崩溃"*|*"无法启动"*|*"编译环境"*|*"permission denied"*|*"disk full"*) exit 0 ;;
    *"根据你的要求"*|*"按照你的指示停止"*|*"用户要求停止"*|*"as you requested"*) exit 0 ;;
esac
cat <<'REASON'
{"reason": "反编译是长程任务，不应自行决定停止。请继续：\n1. 检查 .claude/pal3_cursor.json 确认当前目标\n2. 选择下一个 BFS frontier 函数或 alignment 目标\n3. 执行标注/对齐迭代\n\n质量提醒：偏移必须有二进制证据，禁止从 Hex-Rays 推断"}
REASON
exit 2
