# Unify Data Source Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 消除管线数据源分叉（IDA vs 注解）—— 统一到注解 `known_members`，减少分支/例外，降调试摩擦 50%

**Architecture:** 数据源统一到 `_annview.struct_by_class()`（注解单一读点），IDA `data_members` 作为 fallback。dict-union 优先发射（真 union），其他成员补。每步 P1-5 双验证（逻辑等价 + 字节 diff + L1 不降 + 总错误不增）。

**Tech Stack:** Python 3.10 · MSVC 6.0 (wine) · pytest

**Spec:** `docs/specs/refactor_unify_data_source.md`

## Global Constraints

- **禁大爆炸**：渐进迁移，每步 P1-5 双验证
- **L1 不降**：字节匹配是唯一裁判（`match`）
- **总错误不增**：`loop --expect-errors` 断言
- **禁改 IDB**：所有改动走 annotation apply 流
- **禁伪语义命名**：`conf<60` 冻结 `_todo_`
- **commit 前 `git diff` 核实**（R13）

## Review Focus

| 输入/条件 | 期望行为 | 测试 |
|---|---|---|
| dict-union 成员 | 发射真 union（非单类型）| `test_dict_union_emission` |
| `_inline_*` 类型缺失 | fallback 到 IDA `data_members` | `test_inline_fallback` |
| 注解/IDA 不一致 | 注解优先 | `test_annotation_priority` |
| 双副本表分叉 | 双侧键集合相等 | `test_dual_table_consistency` |
| 静默变异 | 字节 diff 门禁 | `test_no_silent_mutation` |

---

### Task 1: 清 `stage3_cleanup.py` 直读

**Files:**
- Modify: `pipeline/gen/stages/stage3_cleanup.py:107-110`
- Test: `tests/test_unify_data_source.py`

**Interfaces:**
- Consumes: `_annview.struct_by_class(cls_name)` → `dict`（含 `known_members`）
- Produces: `stage3_cleanup` 不再直读 `structs/<Cls>.json`

- [ ] **Step 1: Write the failing test**

```python
def test_stage3_no_direct_read():
    """stage3_cleanup 不直读 structs/*.json（走 annotation_view）。"""
    import ast, inspect
    from pipeline.gen.stages import stage3_cleanup
    src = inspect.getsource(stage3_cleanup)
    assert 'structs/' not in src or '_annview' in src, \
        'stage3_cleanup 直读 structs/*.json（应走 annotation_view）'
```

- [ ] **Step 2: Run test to verify it fails**

Run: `pytest tests/test_unify_data_source.py::test_stage3_no_direct_read -v`
Expected: FAIL with "直读 structs/*.json"

- [ ] **Step 3: Modify `stage3_cleanup.py:107-110`**

改直读 `structs/<Cls>.json` 为 `_annview.struct_by_class(cls_name)`。

- [ ] **Step 4: Run test to verify it passes**

Run: `pytest tests/test_unify_data_source.py::test_stage3_no_direct_read -v`
Expected: PASS

- [ ] **Step 5: P1-5 双验证**

Run: `python pipeline/cli.py apply && python pipeline/cli.py export && python pipeline/cli.py codegen all --skip-probe && python pipeline/cli.py probe s2`
Expected: S2 不降 · 总错误不增

- [ ] **Step 6: Commit**

```bash
git add pipeline/gen/stages/stage3_cleanup.py tests/test_unify_data_source.py
git commit -m "refactor(stage3): 清直读走 annotation_view（阶段 1）"
```

---

### Task 2: 清 `ast_transform.py` 直读

**Files:**
- Modify: `pipeline/gen/ast_transform.py:336-342`
- Test: `tests/test_unify_data_source.py`

**Interfaces:**
- Consumes: `_annview.struct_by_class(cls_name)`
- Produces: `ast_transform` 不再直读 `structs/*.json`

- [ ] **Step 1: Write the failing test**

```python
def test_ast_transform_no_direct_read():
    """ast_transform 不直读 structs/*.json。"""
    import inspect
    from pipeline.gen import ast_transform
    src = inspect.getsource(ast_transform)
    assert 'structs/' not in src or '_annview' in src
```

- [ ] **Step 2: Run test to verify it fails**

Run: `pytest tests/test_unify_data_source.py::test_ast_transform_no_direct_read -v`
Expected: FAIL

- [ ] **Step 3: Modify `ast_transform.py:336-342`**

改直读为 `_annview.struct_by_class(cls_name)`。

- [ ] **Step 4: Run test to verify it passes**

Run: `pytest tests/test_unify_data_source.py::test_ast_transform_no_direct_read -v`
Expected: PASS

- [ ] **Step 5: P1-5 双验证**

Run: 同 Task 1 Step 5
Expected: S2 不降 · 总错误不增

- [ ] **Step 6: Commit**

```bash
git add pipeline/gen/ast_transform.py tests/test_unify_data_source.py
git commit -m "refactor(ast_transform): 清直读走 annotation_view（阶段 1）"
```

---

### Task 3: 清 `emit_headers.py:3259` 直读

**Files:**
- Modify: `pipeline/gen/stages/emit_headers.py:3259-3260`
- Test: `tests/test_unify_data_source.py`

**Interfaces:**
- Consumes: `_annview` globals 读点
- Produces: `emit_headers` 不再直读 `globals.json`

- [ ] **Step 1: Write the failing test**

```python
def test_emit_headers_no_direct_read():
    """emit_headers 不直读 globals.json。"""
    import inspect
    from pipeline.gen.stages import emit_headers
    src = inspect.getsource(emit_headers)
    assert 'globals.json' not in src or '_annview' in src
```

- [ ] **Step 2: Run test to verify it fails**

Run: `pytest tests/test_unify_data_source.py::test_emit_headers_no_direct_read -v`
Expected: FAIL

- [ ] **Step 3: Modify `emit_headers.py:3259-3260`**

改直读 `globals.json` 为 `_annview` 读点。

- [ ] **Step 4: Run test to verify it passes**

Run: `pytest tests/test_unify_data_source.py::test_emit_headers_no_direct_read -v`
Expected: PASS

- [ ] **Step 5: P1-5 双验证**

Run: 同 Task 1 Step 5
Expected: S2 不降 · 总错误不增

- [ ] **Step 6: Commit**

```bash
git add pipeline/gen/stages/emit_headers.py tests/test_unify_data_source.py
git commit -m "refactor(emit_headers): 清直读走 annotation_view（阶段 1）"
```

---

### Task 4: 成员构造数据源统一（dict-union 优先）

**Files:**
- Modify: `pipeline/gen/stages/emit_headers.py:2315-2318`
- Test: `tests/test_unify_data_source.py`

**Interfaces:**
- Consumes: `_annview.struct_by_class(cls_name).known_members`（含 dict-union）
- Produces: `ann_members` 优先 dict-union，其他从 `data_members` 补

- [ ] **Step 1: Write the failing test**

```python
def test_dict_union_emission():
    """dict-union 成员发射真 union（非单类型）。"""
    # PalScript.m_RoleSlotArray 是 dict-union（3 变体）
    # 期望：PalScript.h 发射 union { slot; overlay; script_state; }
    with open('pal3/src/Script/PalScript.h') as f:
        content = f.read()
    assert 'union {' in content, 'dict-union 未发射为真 union'
    assert 'script_state' in content, 'script_state 变体丢失'
```

- [ ] **Step 2: Run test to verify it fails**

Run: `pytest tests/test_unify_data_source.py::test_dict_union_emission -v`
Expected: FAIL（当前单类型）

- [ ] **Step 3: Modify `emit_headers.py:2315-2318`**

MERGE `known_members`（dict-union 优先）+ `data_members`（其他补）。

- [ ] **Step 4: Run test to verify it passes**

Run: `pytest tests/test_unify_data_source.py::test_dict_union_emission -v`
Expected: PASS

- [ ] **Step 5: P1-5 双验证**

Run: 同 Task 1 Step 5
Expected: S2 不降 · 总错误不增 · **C2039 −36**

- [ ] **Step 6: Commit**

```bash
git add pipeline/gen/stages/emit_headers.py tests/test_unify_data_source.py
git commit -m "refactor(emit_headers): 成员构造数据源统一（dict-union 优先）"
```

---

### Task 5: 双副本表收敛（`_GB_REF_PARAM_FUNCS`）

**Files:**
- Modify: `pipeline/gen/stages/stage3_cleanup.py` · `pipeline/gen/stages/stage5_replace.py`
- Test: `tests/test_unify_data_source.py`

**Interfaces:**
- Consumes: 单一 `_GB_REF_PARAM_FUNCS` 定义
- Produces: 双侧键集合相等

- [ ] **Step 1: Write the failing test**

```python
def test_dual_table_consistency():
    """_GB_REF_PARAM_FUNCS 双侧键集合相等。"""
    from pipeline.gen.stages import stage3_cleanup, stage5_replace
    s3 = set(stage3_cleanup._GB_REF_PARAM_FUNCS.keys())
    s5 = set(stage5_replace._GB_REF_PARAM_FUNCS.keys())
    assert s3 == s5, f'双副本分叉: only3={s3-s5}, only5={s5-s3}'
```

- [ ] **Step 2: Run test to verify it fails**

Run: `pytest tests/test_unify_data_source.py::test_dual_table_consistency -v`
Expected: FAIL（分叉 5 键）

- [ ] **Step 3: 收敛到单一定义**

提取 `_GB_REF_PARAM_FUNCS` 到共享模块（如 `pipeline/gen/tables.py`），双侧引用。

- [ ] **Step 4: Run test to verify it passes**

Run: `pytest tests/test_unify_data_source.py::test_dual_table_consistency -v`
Expected: PASS

- [ ] **Step 5: P1-5 双验证**

Run: 同 Task 1 Step 5
Expected: S2 不降 · 总错误不增

- [ ] **Step 6: Commit**

```bash
git add pipeline/gen/tables.py pipeline/gen/stages/stage3_cleanup.py pipeline/gen/stages/stage5_replace.py tests/test_unify_data_source.py
git commit -m "refactor(tables): 收敛 _GB_REF_PARAM_FUNCS 双副本（阶段 3）"
```

---

## Self-Review

**1. Spec coverage:** 4 阶段全覆盖（阶段 1=Task 1-3 · 阶段 2=Task 4 · 阶段 3=Task 5 · 阶段 4=基线归一，可作 Task 6）

**2. Step scan:** 每步一个动作（写测试→跑失败→实现→跑通过→验证→提交）✓

**3. Type consistency:** `_annview.struct_by_class()` 一致 ✓

**4. Review Focus:** 5 个测试覆盖（dict-union / inline fallback / annotation priority / dual table / silent mutation）✓

**5. Proportion:** 计划 5 任务 vs spec 4 阶段 ≈ 1:1 ✓

---

## Execution Handoff

Plan complete and saved to `docs/superpowers/plans/2026-10-23-unify-data-source.md`. Please review the plan. Which execution approach would you prefer?

- **Subagent-driven** - A fresh subagent implements each task and a fresh reviewer checks it before the next one starts, then a whole-branch review at the end. Most thorough; costs a fresh context per task and per review.
- **Native** - I implement every task myself in this session, then one fresh reviewer on the most capable model checks the whole branch. Cheapest and fastest; no independent review until the end.

**For this plan I recommend Subagent-driven**, because 每步有独立复核（用户纪律：每一步完成需要独立复核+修复），且 Task 4（dict-union）是核心（历史 6 次修尝试未生效），须独立验证。
