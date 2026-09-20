#!/bin/bash
# 你自己复核用：进程 + 运行时长 + 日志末尾 + 指标（只读 ✓）
cd "$(dirname "$0")/../.."
echo "=== 现在 $(date '+%H:%M:%S') ==="
echo "--- 进程（PID / 已运行秒 / 命令）:"
ps -eo pid,etimes,args --no-headers | awk '$0 ~ /land[0-9]\.sh|recover[0-9]\.sh|cli\.py|apply_annotation/ && $0 !~ /awk/ {print "  "$1"  "$2"s  "substr($0,index($0,$3),80)}'
echo "--- 日志末尾:"
for f in /tmp/recover4.log /tmp/land5.log; do [ -f "$f" ] && echo "  [$f] 最后写 $(stat -c '%y' "$f" | cut -d. -f1)" && tail -2 "$f" | sed 's/^/      /'; done
echo "--- 指标:"
python3 -c "
import json
n=json.load(open('data/status/probe_census.json'))['s2']['results']; s=json.load(open('data/status/s4_baseline.json'))['stats']
print('  census ok=%d errors=%d | L1=%d | matched=%d/%d' % (sum(1 for r in n if r['status']=='ok'), sum(len(r.get('errors',[])) for r in n), s['match_L1'], s['matched'], s['symbols']))"
echo "--- 注解改动数: $(cd /home/peng/workspace/PAL3Decomp && git status --porcelain -- data/annotations | wc -l)"
