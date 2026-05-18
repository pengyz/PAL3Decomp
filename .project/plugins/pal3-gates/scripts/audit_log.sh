#!/bin/bash
input=$(cat)
eval "$(echo "$input" | python3 -c "
import sys, json
d = json.load(sys.stdin)
print(f'TOOL={json.dumps(d.get(\"tool_name\",\"\"))}')
ti = d.get('tool_input', {})
path = ti.get('file_path', ti.get('path', ''))
cmd = ti.get('command', ti.get('cmd', ''))
summary = path or cmd[:80] or json.dumps(ti)[:80]
print(f'SUMMARY={json.dumps(summary)}')
print(f'SUCCESS={json.dumps(d.get(\"tool_success\",True))}')
" 2>/dev/null)"
PROJECT="${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}"
TS=$(date '+%Y-%m-%d %H:%M:%S')
STATUS="OK"; [ "$SUCCESS" = '"false"' ] && STATUS="FAIL"
TOOL=$(echo "$TOOL" | tr -d '"'); SUMMARY=$(echo "$SUMMARY" | tr -d '"')
echo "${TS} | ${TOOL} | ${STATUS} | ${SUMMARY}" >> "$PROJECT/.project/audit.log"
# slot_updates for UI panel
echo "{\"slot_updates\": {\"audit_trail\": \"$(tail -15 "$PROJECT/.project/audit.log" 2>/dev/null | sed 's/$/\\n/g' | tr -d '\n')\"}}"
exit 0
