#!/bin/bash
input=$(cat)
file_path=$(echo "$input" | python3 -c "
import sys, json
d = json.load(sys.stdin)
ti = d.get('tool_input', {})
print(ti.get('file_path', ti.get('path', '')))
" 2>/dev/null)
[ -z "$file_path" ] && exit 0
case "$file_path" in
    */pipeline/data/annotations/*) exit 0 ;;
    */docs/*|*/.project/*) exit 0 ;;
esac
echo "{\"reason\": \"禁止修改管线脚本 ${file_path}。反编译迭代中只允许修改 annotations 数据。\"}"
exit 2
