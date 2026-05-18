#!/bin/bash
# Notification/10: 多维度统计 → slot_updates 写入 4 个面板
PROJECT="${AIDE_PROJECT_ROOT:-/home/peng/workspace/PAL3Decomp}"

python3 << 'PY'
import json, os, subprocess, datetime

project = os.environ.get('AIDE_PROJECT_ROOT', '/home/peng/workspace/PAL3Decomp')
ts = datetime.datetime.now().strftime('%Y-%m-%d %H:%M')

# ── 文件维度 ──
file_stats_lines = []
src_dir = os.path.join(project, 'src/pal3')
total_cpp = 0
compile_pass = 0
compile_fail_list = []

# 尝试编译获取结果
try:
    r = subprocess.run(['cmake', '--build', 'build/pal3'],
                       capture_output=True, text=True, timeout=180, cwd=project)
    output = r.stdout + r.stderr
    # 统计错误文件
    error_files = set()
    for line in output.split('\n'):
        if ': error C' in line and '(' in line:
            fname = line.split('(')[0].split('\\')[-1].split('/')[-1]
            error_files.add(fname)
    
    if os.path.isdir(src_dir):
        for root, _, files in os.walk(src_dir):
            for f in files:
                if f.endswith('.cpp'):
                    total_cpp += 1
                    if f not in error_files:
                        compile_pass += 1
                    else:
                        compile_fail_list.append(f)
except:
    if os.path.isdir(src_dir):
        for root, _, files in os.walk(src_dir):
            total_cpp += sum(1 for f in files if f.endswith('.cpp'))

compile_pct = round(compile_pass / max(total_cpp, 1) * 100, 1)
bar_len = int(compile_pct / 5)
compile_bar = '#' * bar_len + '.' * (20 - bar_len)

file_stats = f"""## 文件维度 ({ts})

### 编译状态
`[{compile_bar}]` **{compile_pct}%** ({compile_pass}/{total_cpp} 通过)
"""
if compile_fail_list[:5]:
    file_stats += "\n失败:\n" + "\n".join(f"  - {f}" for f in compile_fail_list[:5])
    if len(compile_fail_list) > 5:
        file_stats += f"\n  ...+{len(compile_fail_list)-5} more"

# ── 函数维度 ──
try:
    funcs = json.load(open(f'{project}/pipeline/data/annotations/functions.json'))
    total_funcs = len(funcs)
    named = sum(1 for v in funcs.values() 
                if v.get('name','').strip() and not v['name'].startswith('sub_'))
    named_pct = round(named / max(total_funcs, 1) * 100, 1)
    bar2 = '#' * int(named_pct / 5) + '.' * (20 - int(named_pct / 5))
except:
    total_funcs = named = 0
    named_pct = 0
    bar2 = '.' * 20

# 结构体统计
try:
    struct_dir = f'{project}/pipeline/data/annotations/structs'
    struct_count = sum(1 for f in os.listdir(struct_dir) if f.endswith('.json'))
except:
    struct_count = 0

# 全局变量
try:
    globs = json.load(open(f'{project}/pipeline/data/annotations/globals.json'))
    total_globals = len(globs)
    typed_globals = sum(1 for v in globs.values() if v.get('type','').strip())
except:
    total_globals = typed_globals = 0

func_stats = f"""## 函数维度 ({ts})

### 命名率
`[{bar2}]` **{named_pct}%** ({named}/{total_funcs})

### 结构体
定义数: **{struct_count}**

### 全局变量
有类型: {typed_globals}/{total_globals}
"""

# ── 里程碑状态 ──
phase1_done = (compile_pass == total_cpp and total_cpp > 0)
if phase1_done:
    milestone = f"""## 里程碑 ({ts})

**Phase 1: 通过编译** ✅ 完成

**Phase 2: 质量提升** ← 当前
- byte-match 目标: ≥ 95%
- 命名率: {named_pct}%
- _todo_ 清零中
"""
else:
    milestone = f"""## 里程碑 ({ts})

**Phase 1: 通过编译** ← 当前
- 编译通过率: {compile_pct}% ({compile_pass}/{total_cpp})
- 函数命名率: {named_pct}%
- 结构体: {struct_count}

Phase 2: 质量提升（待 Phase 1 完成）
"""

# ── 输出 ──
output = {
    'slot_updates': {
        'milestone_status': milestone,
        'file_stats': file_stats,
        'func_stats': func_stats,
    },
    'content': f'检查点 ({ts}): 编译 {compile_pass}/{total_cpp}, 函数命名 {named}/{total_funcs}'
}
print(json.dumps(output))
PY
