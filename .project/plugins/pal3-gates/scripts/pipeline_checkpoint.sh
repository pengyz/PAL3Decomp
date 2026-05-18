#!/bin/bash
PROJECT="${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}"
TS=$(date '+%Y-%m-%d %H:%M:%S')

# Annotations stats
ann_ok="?"
if cd "$PROJECT" && python3 pipeline/cli.py check >/dev/null 2>&1; then
    ann_ok="PASS"
else
    ann_ok="FAIL"
fi

# Function naming rate
stats=$(cd "$PROJECT" && python3 -c "
import json
f = json.load(open('pipeline/data/annotations/functions.json'))
named = sum(1 for v in f.values() if v.get('name','').strip() and not v['name'].startswith('sub_'))
print(f'{named}/{len(f)}')
" 2>/dev/null || echo "?/?")

# gbengine progress
gb=$(cd "$PROJECT" && python3 -c "
import json, os
p = 'build/gbengine_progress.json'
if os.path.exists(p):
    d = json.load(open(p))
    print(f\"{d.get('done',0)}/{d.get('target_functions',0)} ({round(d.get('done_bytes',0)/max(d.get('target_bytes',1),1)*100,1)}%)\")
else:
    print('N/A')
" 2>/dev/null || echo "N/A")

report="annotations: ${ann_ok} | functions: ${stats} | gbengine: ${gb}"
echo "[$TS] ${report}" >> "$PROJECT/.project/pipeline_milestones.log"

cat <<EOF
{"slot_updates": {"pipeline_status": "## 管线检查点 ($TS)\n\n- Annotations 验证: ${ann_ok}\n- 函数命名: ${stats}\n- gbengine match: ${gb}"}, "content": "管线检查点完成：${report}。请用 data_write 更新 progress_dashboard。"}
