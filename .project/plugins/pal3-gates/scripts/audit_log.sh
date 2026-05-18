#!/bin/bash
# PostToolUse: 审计日志 + slot_updates 写入面板
PROJECT="${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}"
LOG="$PROJECT/.project/audit.log"

python3 << 'PY'
import sys, json, datetime, os

stdin_data = sys.stdin.read()
try:
    d = json.loads(stdin_data)
except:
    d = {}

tool = d.get('tool_name', '?')
ti = d.get('tool_input', {})
success = d.get('tool_success', True)
path = ti.get('file_path', ti.get('path', ''))
cmd = ti.get('command', ti.get('cmd', ''))
summary = (path or cmd[:80] or json.dumps(ti)[:80]).replace('"', '')

ts = datetime.datetime.now().strftime('%H:%M:%S')
status = 'OK' if success else 'FAIL'
line = f'{ts} | {tool} | {status} | {summary}'

log_path = os.environ.get('AIDE_PROJECT_ROOT', '/home/peng/workspace/PAL3Decomp') + '/.project/audit.log'
with open(log_path, 'a') as f:
    f.write(line + '\n')

try:
    with open(log_path) as f:
        lines = f.readlines()[-15:]
    panel = ''.join(lines)
except:
    panel = line + '\n'

print(json.dumps({'slot_updates': {'audit_trail': panel}}))
PY
