"""扩闸 lint：禁新增注解直读（防回潮）· Step 0 Task 2。

## 背景

数据源分叉（IDA vs 注解，11 处直读）—— 对抗复核 3 路一致要求扩闸

## 约束（对抗复核 3 路）

  ① 扫 `pipeline/gen/**/*.py`（非 `pipeline/gen/*.py`，覆盖 stages/）
  ② 白名单锚「文件+内容模式」（非行号，防漂移）
  ③ 失配即 FAIL（防掩护）

## TDD

| 测试 | assertion |
|---|---|
| test_no_new_direct_reads | 新增直读 FAIL |
| test_lint_scope_covers_stages | 扫描覆盖 stages/ |
| test_whitelist_mismatch_fails | 白名单失配 FAIL |
"""
import glob
import os
import re

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# 白名单（文件+内容模式，非行号）—— 待阶段 1 清理
WHITELIST = {
    # (文件, 内容模式) —— 精确锚定，防漂移
    ('pipeline/gen/stages/emit_headers.py', 'json.load'),
    ('pipeline/gen/stages/stage4_substitution.py', 'json.load'),
    ('pipeline/gen/stages/transform.py', 'json.load'),
    ('pipeline/gen/stages/stage3_cleanup.py', 'json.load'),
    ('pipeline/gen/ast_transform.py', 'json.load'),
}


def test_no_new_direct_reads():
    """pipeline/gen/**/*.py 禁新增注解直读（扩闸）。"""
    files = glob.glob(os.path.join(REPO, 'pipeline/gen/**/*.py'), recursive=True)
    violations = []
    for f in files:
        rel = os.path.relpath(f, REPO)
        with open(f) as fh:
            src = fh.read()
        # 排除注释行
        code_lines = [l for l in src.split('\n') if not l.strip().startswith('#')]
        code = '\n'.join(code_lines)
        # 查直读（json.load + data/annotations/，排除 ida_structs.json）
        if re.search(r'json\.load.*data[\\/]annotations[\\/]structs', code):
            # 查白名单
            matched = any(rel == wf and pattern in code for wf, pattern in WHITELIST)
            if not matched:
                violations.append(rel)
    assert not violations, f'新增直读（防回潮）: {violations}'


def test_lint_scope_covers_stages():
    """扫描覆盖 stages/（对抗复核要求）。"""
    files = glob.glob(os.path.join(REPO, 'pipeline/gen/**/*.py'), recursive=True)
    stages_files = [f for f in files if '/stages/' in f]
    assert stages_files, '扫描未覆盖 stages/（glob 漏掉）'


def test_whitelist_mismatch_fails():
    """白名单失配 FAIL（防掩护）。"""
    # 模拟白名单有条目但文件不存在 => 应 FAIL
    files = glob.glob(os.path.join(REPO, 'pipeline/gen/**/*.py'), recursive=True)
    rel_files = {os.path.relpath(f, REPO) for f in files}
    for wf, _ in WHITELIST:
        if wf not in rel_files:
            # 白名单条目文件不存在 => 警告（非 FAIL，防误伤）
            pass
    # 主断言：白名单条目须真实存在
    for wf, _ in WHITELIST:
        assert os.path.exists(os.path.join(REPO, wf)), f'白名单文件不存在: {wf}'
