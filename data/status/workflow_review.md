# 工作流梳理（诉求 4——2026-10-07）

## 现行工作流（主链）
```
annotations → apply → IDB → Hex-Rays → decomp JSON → codegen → C++ → Phase2: 手工fix
                                                              ↕ 字节比对（match）
```

## 支撑工具链（现行——有效）
| 阶段 | 工具 | 三分法 |
|---|---|---|
| 注解 | check_annotations·annotation_diff | generic |
| 应用 | apply_annotations（pipeline/ida） | project |
| 导出 | export_full（pipeline/ida） | project |
| 生成 | pipeline/gen（stage1-5+emit） | project |
| 验证 | error_classifier·audit_*·verify_fix | generic/project |
| 比对 | match（compare_pal3）·bin_oracle | generic |
| 门禁 | compile_regression·regression_detector | generic |

## 过时/需清理（诉求 4 的清理面）
| 类 | 件 | 处置 |
|---|---|---|
| 已废弃 | audit_layout（已下架 ✓）| _obsolete |
| 一次性 | 8 件批次工具（已归档 ✓）| _obsolete |
| 死闸 | check_annotation_names（零引用）| 退役/接线 |
| 双真相源 | pre-commit 内嵌扫描器（与 check_annotations 不一致）| 统一为 cli.py check |

## 工作流支撑的过时面
1. **R1-R16 异质编号**（CLAUDE.md 自认）——文档债
2. **python3 命令**（本机无 python3——文档漂移）——python 统一
3. **三方基线权威**（s4/compile/latest——无单一权威）——权威单一化

## 清理原则（用户三分法）
- **通用反编译工具**：参数化收编（tools/generic/）
- **项目相关工具**：留 tools/（批次完归档）
- **特定任务工具**：不保留（_obsolete/归档）
