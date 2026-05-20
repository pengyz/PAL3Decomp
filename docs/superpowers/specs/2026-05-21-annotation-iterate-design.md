# Design: Annotation Iteration Engine

Date: 2026-05-21
Status: APPROVED
Branch: master

## Problem

PAL3 annotation 迭代当前依赖人工：跑 IDA query → 分析证据 → 修改 annotation → pipeline rebuild → 检查结果。每轮 ~10 分钟人工 + ~3 分钟 pipeline。需要自动化这个循环直到收敛。

## Solution

`pipeline/iterate.py` — 自动化迭代引擎，组合现有 CLI 能力，新增规则引擎做证据分析和 annotation 修正。

## Convergence Criteria

短路退出，满足任一即停：
- errors 连续 3 轮不下降（stale_limit=3）
- errors < 1000 或 pass > 100（target）
- 无候选修正可生成（能力耗尽）
- max_rounds 达到上限（默认 20）

## Evidence Level

接受 B 级及以上（3+ 条 A 级交叉确认）。不接受 C 级（单条 Hex-Rays 推断）。

## Architecture

```
pipeline/iterate.py          — CLI 入口 + 收敛控制循环
pipeline/iterate_rules.py    — 三个规则引擎
pipeline/iterate_apply.py    — fix 应用 + overlap 检查 + rollback
```

依赖已有：
- `pipeline/cli.py` — cmd_init, cmd_export, cmd_codegen, cmd_compile
- `pipeline/snapshots/snapshot.py` — _compile_and_collect()
- `pipeline/check_annotations.py` — 校验
- `pipeline/ida/query_todo_fields.py` — IDA field 扫描
- `pipeline/ida/_query_lea_batch.py` — LEA 目标追踪

## Rules

### Rule 1: Function Signature Unification

```
输入: 编译 errors (C2664) + functions.json
触发: 3+ callers 传同一 type 但 decl 不同
排除: caller_type 是 void*
动作: 修改 functions.json 中的 signature 参数类型
置信度: 80 (B级)
```

### Rule 2: Embedded Type from Constructor

```
输入: lea_batch_analysis.json + structs/*.json
触发: LEA 字段的 call_name 含 ctor/dtor + 可解析类名
验证: new_type.binary_size + offset <= next_field_offset (overlap check)
动作: 修改 structs/Class.json 中的 field type
置信度: 85 (A级 ctor evidence)
```

### Rule 3: Function Attribution from Member Access

```
输入: 编译 errors (C2673) + decomp JSON + functions.json
触发: 函数 F 有 __thiscall 但 class A 不含其 member → class B 含 3+ members
验证: member 在 B 存在且不在 A 存在
动作: 修改 functions.json 中的 name (A::Method → B::Method)
置信度: 80 (B级: 3+ member 交叉)
```

## Apply Strategy

逐个 fix 应用：
1. 写入 annotation
2. 运行 check_annotations
3. 如果 check 失败 → 回退该 fix，继续下一个

整轮 rebuild 后如果 errors 增加 → `git checkout -- data/annotations/` 回退全轮。

## CLI Interface

```bash
python pipeline/iterate.py                          # 默认运行
python pipeline/iterate.py --dry-run                # 只分析不修改
python pipeline/iterate.py --max-rounds 5           # 限制轮次
python pipeline/iterate.py --target-errors 500      # 自定义目标
python pipeline/iterate.py --stale-limit 5          # 放宽收敛判定
```

## Main Loop Pseudocode

```python
prev_errors = get_current_errors()
stale = 0

for round in range(1, max_rounds + 1):
    run_ida_queries()
    fixes = analyze_evidence()
    
    if not fixes:
        break  # 能力耗尽
    
    applied = apply_fixes(fixes)
    cmd_init(force=True)
    cmd_export()
    cmd_codegen(['all'])
    errors, passes = evaluate()

    if errors < target_errors or passes > target_pass:
        commit(); break  # 目标达成
    elif errors < prev_errors:
        commit(); stale = 0; prev_errors = errors
    else:
        rollback(); stale += 1
        if stale >= stale_limit:
            break  # 收敛
```

## Constraints

- 不修改 codegen 代码或头文件，只改 data/annotations/
- 每轮必须 init --force（不可用 apply 替代）
- check_annotations 必须 pass 才能 commit
- rollback 用 git checkout（保证原子性）

## Success Metrics

- errors 从 3073 持续下降
- 脚本可无人值守运行到收敛
- 零误判（所有修正有 B 级以上证据）
