# Git 冲突数据问题挂账记录（2026-10-17）

## 冲突根因
**git stash pop LIFO 冲突**（stash@{0} 与 HEAD 设计分歧）
- stash@{0}: `_load_annotations()` → `_load_exported_data()`（从 exported JSONs 加载）
- HEAD: `_load_annotations()`（从 annotations 加载）
- **两种不同设计**，非简单冲突

## 我的错误处理（诚实自认）
| # | 错误 | 风险 |
|---|---|---|
| 1 | **机械删除冲突标记**（不看两侧内容）| 丢失 Stashed changes 侧工作 |
| 2 | **机械补回属性**（从使用推断）| 可能引入错误语义 |
| 3 | **正要推断实现 `_prefix_type`** | 可能与原始实现不同 |

## 已回退（git checkout HEAD）
- `data/annotations/globals.json` ✓
- `pipeline/gen/data.py` ✓
- `pipeline/gen/stages/emit_headers.py` ✓
- `pipeline/gen/stages/stage4_substitution.py` ✓

## stash@{0} 丢失内容（待裁决）
- **215 行新增 / 225 行删除**
- **annotation 数据改动**：仅 `globals.json` 4 行（移除 `overlaps_with`）
- **管线代码改动**：`data.py` 重构 + `emit_headers.py` + `export_full.py`

## 待裁决问题
| # | 问题 | 优先级 |
|---|---|---|
| 1 | **stash@{0} 设计分歧**：从 exported JSONs vs 从 annotations 加载 | 🔴 高 |
| 2 | **`globals.json` overlaps_with 字段**：是否需要移除？ | 🔴 高 |
| 3 | **`_prefix_type` 函数**：丢失，需从测试推断或从 stash 恢复 | 🟡 中 |
| 4 | **`DataStore` 属性**：`scalar_dtor_classes` 等 8 个属性丢失 | 🟡 中 |

## 核心资产原则
> **数据是核心资产** —— 不可机械处理，必须逐条核实
> **不引入猜测语义** —— 无 A 级证据不改名/改型

## 状态
- [x] 回退错误修复
- [x] 核查 stash 内容
- [ ] 人工裁决冲突（待子 agent 复核）
- [ ] 标记数据问题（本文件）
