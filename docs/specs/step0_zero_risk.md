# Step 0：零风险降摩擦方案

**created**: 2026-10-23（根治方案前置）

## 目标

**零风险降摩擦**（1-2 天）—— 只读报表 + 扩闸 + 口径对齐

## 3 个动作

### ① 双源 diff 报表（只读）

**目的**：看清 IDA vs 注解的差异（不改任何代码）

**实施**：
```python
# tools/dual_source_diff.py
"""双源 diff 报表（只读）。

对比：
  IDA 侧: asm/pal3/ida_structs.json 的 data_members
  注解侧: data/annotations/structs/*.json 的 known_members

输出：
  - 每类差异（成员数/偏移/类型）
  - _inline_* 引用 vs 定义对称性
  - 量化统计（多少类不一致？多少成员缺失？）
"""
```

**输出**：`data/status/dual_source_report.md`

**验证**：
- 报表生成成功
- 差异数字可复现（同输入 ⇒ 同输出）

### ② 扩闸 lint（禁新增直读）

**目的**：防回潮（清完 8 处后不再新增）

**实施**：
```python
# tests/test_no_new_direct_read.py
def test_no_new_direct_reads():
    """pipeline/gen 禁新增注解直读（扩闸）。

    扫描 pipeline/gen/*.py，断言无新增：
      json.load(...structs...)
      os.path.join(...annotations...)
    已有 8 处白名单（待阶段 1 清理）。
    """
```

**白名单**（待清）：
- `emit_headers.py:563/781/1427/4322`
- `stage4_substitution.py:2445/2513/2552/2585`
- `transform.py:67`
- `stage3_cleanup.py:177`
- `ast_transform.py:337`

**验证**：
- 测试通过（当前 8 处白名单）
- 新增直读时 FAIL（防回潮）

### ③ 口径对齐（基线归一）

**目的**：消除 3 份互斥基线（裁判未校准）

**现状**：
| 基线 | S2 | L1 |
|---|---|---|
| `compile_baseline.json` | 120/214 | — |
| `baselines/latest.json` | 140/205 | — |
| `s4_baseline.json` | — | 194 |

**目标**：统一为「当前实测」口径

**实施**：
```bash
python3 tools/align_baselines.py
# 读当前 probe_census.json / s4_baseline.json
# 统一数字到 3 份基线
```

**验证**：
- 3 份基线数字一致
- P1-5 验证有唯一裁判

## 成本/收益

| 项 | 值 |
|---|---|
| **成本** | 1-2 天 |
| **风险** | **0**（只读 + 加测试 + 改基线数字）|
| **收益** | 差异清单可见 + 防回潮 + 裁判校准 |

## 完备性检查

- [ ] 双源 diff 报表（量化差异）
- [ ] 扩闸 lint（8 处白名单 + 禁新增）
- [ ] 口径对齐（3 基线归一）
- [ ] P1-5 验证（同树 A/B）
- [ ] 对抗复核（方案 + 修复）

## 与后续阶段关系

```
step 0（零风险）→ 阶段 1（清直读）→ 阶段 2（数据源统一）→ 阶段 3（逻辑表收敛）→ 阶段 4（基线归一）
```

**step 0 是后续阶段的基础**（差异清单 + 防回潮 + 裁判校准）
