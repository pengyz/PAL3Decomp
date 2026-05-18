#!/bin/bash
# Notification/10: 多维度统计 → 结构化 slot_updates
PROJECT="${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}"

python3 << 'PY'
import json, os, subprocess, datetime

project = os.environ.get('AIDE_PROJECT_ROOT', '/home/peng/workspace/PAL3Decomp')
ts = datetime.datetime.now().strftime('%Y-%m-%d %H:%M')

# ── 编译率 ──
total_cpp = 0
compile_pass = 0
fail_files = []
try:
    r = subprocess.run(['cmake', '--build', 'build/pal3'],
                       capture_output=True, text=True, timeout=180, cwd=project)
    output = r.stdout + r.stderr
    error_files = set()
    for line in output.split('\n'):
        if ': error C' in line and '(' in line:
            fname = line.split('(')[0].split('\\')[-1].split('/')[-1]
            error_files.add(fname)
    
    src_dir = f'{project}/src/pal3'
    if os.path.isdir(src_dir):
        for root, _, files in os.walk(src_dir):
            for f in files:
                if f.endswith('.cpp'):
                    total_cpp += 1
                    if f not in error_files:
                        compile_pass += 1
                    else:
                        fail_files.append(f)
except:
    src_dir = f'{project}/src/pal3'
    if os.path.isdir(src_dir):
        for root, _, files in os.walk(src_dir):
            total_cpp += sum(1 for f in files if f.endswith('.cpp'))

compile_rate = compile_pass / max(total_cpp, 1)

# ── 命名率 ──
try:
    funcs = json.load(open(f'{project}/data/annotations/functions.json'))
    named = sum(1 for v in funcs.values()
                if v.get('name','').strip() and not v['name'].startswith('sub_'))
    total_funcs = len(funcs)
    naming_rate = named / max(total_funcs, 1)
except:
    named = total_funcs = 0
    naming_rate = 0

# ── match 率（gbengine）──
try:
    p = json.load(open(f'{project}/data/gbengine_progress.json'))
    match_rate = p.get('done', 0) / max(p.get('target_functions', 1), 1)
except:
    match_rate = 0

# ── 里程碑 ──
phase1_done = (compile_pass == total_cpp and total_cpp > 0)
if phase1_done:
    milestone = f"""## Phase 2: 质量提升 ← 当前

Phase 1 ✅ 全部编译通过

- byte-match: {round(match_rate*100,1)}%
- 命名率: {round(naming_rate*100,1)}%
- 目标: match ≥ 95%, _todo_ → 0
"""
else:
    milestone = f"""## Phase 1: 通过编译 ← 当前

- 编译: **{compile_pass}/{total_cpp}** ({round(compile_rate*100,1)}%)
- 命名: {named}/{total_funcs} ({round(naming_rate*100,1)}%)

Phase 2: 质量提升（待 Phase 1 完成）
"""

# ── 文件明细 ──
if fail_files:
    file_lines = '\n'.join(f'- ❌ {f}' for f in fail_files[:15])
    if len(fail_files) > 15:
        file_lines += f'\n- ...+{len(fail_files)-15} more'
    file_detail = f"## 编译失败文件 ({len(fail_files)})\n\n{file_lines}"
else:
    file_detail = "## 全部通过 ✅" if total_cpp > 0 else "## 等待编译..."

# ── 命名趋势数据点（追加到 list）──
trend_point = {"time": ts, "rate": str(round(naming_rate * 100, 1))}

# ── 迭代记录数据点 ──
iter_point = {
    "time": ts,
    "event": f"检查点: 编译 {compile_pass}/{total_cpp}, 命名 {round(naming_rate*100,1)}%",
    "detail": f"match {round(match_rate*100,1)}%"
}

# ── 输出 ──
output = {
    'slot_updates': {
        'compile_rate': compile_rate,
        'naming_rate': naming_rate,
        'match_rate': match_rate,
        'milestone_status': milestone,
        'file_detail': file_detail,
        'naming_trend': {'$append': trend_point},
        'iterations': {'$append': iter_point},
    },
    'content': f'检查点 ({ts}): 编译 {compile_pass}/{total_cpp}, 命名 {round(naming_rate*100,1)}%, match {round(match_rate*100,1)}%'
}
print(json.dumps(output))
PY
