#!/bin/bash
# Notification/10: 管线检查点 — 验证 + 统计 + slot_updates 写入面板
PROJECT="${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}"

python3 << 'PY'
import json, os, subprocess, datetime

project = os.environ.get('AIDE_PROJECT_ROOT', '/home/peng/workspace/PAL3Decomp')
ts = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')

# 1. Annotations 验证
try:
    r = subprocess.run(['python3', 'pipeline/cli.py', 'check'],
                       capture_output=True, text=True, timeout=30, cwd=project)
    ann_ok = 'PASS' if r.returncode == 0 else 'FAIL'
except:
    ann_ok = '?'

# 2. Function naming rate
try:
    funcs = json.load(open(f'{project}/pipeline/data/annotations/functions.json'))
    named = sum(1 for v in funcs.values() if v.get('name','').strip() and not v['name'].startswith('sub_'))
    func_stats = f'{named}/{len(funcs)}'
except:
    func_stats = '?/?'

# 3. gbengine progress
try:
    p = json.load(open(f'{project}/build/gbengine_progress.json'))
    done = p.get('done', 0)
    target = p.get('target_functions', 0)
    done_bytes = p.get('done_bytes', 0)
    target_bytes = max(p.get('target_bytes', 1), 1)
    gb_stats = f'{done}/{target} ({round(done_bytes/target_bytes*100,1)}%)'
except:
    gb_stats = 'N/A'

# 4. Write milestone log
milestone = f'[{ts}] ann={ann_ok} funcs={func_stats} gb={gb_stats}'
log_path = f'{project}/.project/pipeline_milestones.log'
with open(log_path, 'a') as f:
    f.write(milestone + '\n')

# 5. Build status panel content
status = f"""## 管线检查点 ({ts})

| 指标 | 状态 |
|------|------|
| Annotations 验证 | {ann_ok} |
| 函数命名 | {func_stats} |
| gbengine match | {gb_stats} |
"""

# 6. Build progress dashboard
try:
    total_funcs = len(funcs)
    pct = round(named / max(total_funcs, 1) * 100, 1)
    bar_len = int(pct / 5)
    bar = '#' * bar_len + '.' * (20 - bar_len)
    progress = f"""## 进度总览

### 函数命名
`[{bar}]` **{pct}%** ({named}/{total_funcs})

### gbengine Binary Match
{gb_stats}

### 最近检查点
{milestone}
"""
except:
    progress = f"## 进度总览\n\n{milestone}"

# Output: slot_updates + content for system-reminder
output = {
    'slot_updates': {
        'pipeline_status': status,
        'progress_dashboard': progress,
    },
    'content': f'管线检查点完成：{milestone}。请用 data_write 更新 iteration_log 记录本轮工作摘要。'
}
print(json.dumps(output))
PY
