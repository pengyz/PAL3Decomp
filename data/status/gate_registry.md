# 门禁登记表（架构治理 ①——2026-10-07 复核实测）

> 四栏分类：机器强制（cli.py 接线）/CLI 手动（纪律跑）/hook 内嵌（pre-commit）/检查点表外（自述门禁未登记）。

## 机器强制（3——cli.py 自动接线）
| 门禁 | 位置 | 时机 | 失败处理 |
|---|---|---|---|
| check_annotations | pipeline/check_annotations.py | cli.py cmd_check | 硬失败 |
| compile_regression | tools/compile_regression.py | cli.py codegen 后 | 报警 |
| regression_detector | tools/regression_detector.py | cli.py probe 后 | 报警 |

## CLI 手动（6——CLAUDE.md 纪律）
| 门禁 | 位置 | 时机 |
|---|---|---|
| annotation_diff | tools/annotation_diff.py | apply 后 |
| error_classifier | tools/error_classifier.py | probe 后 |
| audit_type_layout | tools/audit_type_layout.py | struct 改后 |
| audit_member_semantics | tools/audit_member_semantics.py | 否定结论 |
| audit_attribution_evidence | tools/audit_attribution_evidence.py | 归属改 |
| verify_fix | tools/verify_fix.py | 修复提交前 |

## hook 内嵌（1——未安装）
| 门禁 | 位置 | 状态 |
|---|---|---|
| pre-commit 对齐/重叠扫描 | pipeline/hooks/pre-commit | 未安装（.git/hooks 仅 git-lfs）|

## 检查点表外（≥10——自述门禁未登记）
| 门禁 | 位置 | 备注 |
|---|---|---|
| check_member_offsets | tools/ | 成员偏移 |
| check_member_extent | tools/ | 成员范围 |
| check_union_member_triviality | tools/ | union 平凡性 |
| codegen_invariants | pipeline/gen/ | codegen 不变式（advisory）|
| codegen_param_lint | pipeline/gen/ | 参数 lint |
| member_existence_gate | pipeline/gen/ | 成员存在性 |
| vtable_mapper | tools/ | vtable 映射 |
| check_export_annotation_consistency | tools/ | 导出-注解一致 |
| check_annotation_names | tools/ | 注解命名 |
| codegen_invariants(2) | pipeline/gen/ | 双份? 待核 |

## 登记完备性
- 总计 **≥20**（机器 3+CLI 6+hook 1+表外 10+）
- 待办：①pre-commit 安装或退役 ②表外 10 件的四栏归位 ③CLAUDE.md 检查点表补 probe 步骤
