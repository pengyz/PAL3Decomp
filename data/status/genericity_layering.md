# 通用性分层（架构治理 ③——2026-10-07 复核抽样+分类）

> 三分法：**generic**（参数化收编 tools/generic/）/ **project-specific**（批次完归档）/ **evidence**（docs/evidence/ 永不删）。

## generic（逻辑可搬·跨项目可用）——收编候选
| 工具 | 通用面 | 参数化需 |
|---|---|---|
| error_classifier.py | MSVC 错误码规则表 | 输入/输出路径 |
| annotation_diff.py | JSON struct diff+git | 注解目录 |
| compare 族×7 | 字节/函数对比 | 目标二进制 |
| byte_diff_explain.py | 字节 diff 解释 | obj/二进制 |
| type_evidence.py | 类型证据（二进制） | exe 路径 |

## project-specific（PAL3 硬编码）——批次完归档
| 工具 | 硬编码面 | 状态 |
|---|---|---|
| _land_sizes.py（已归档）| 8 类尺寸 | _obsolete |
| adjudicate_*×4 | PAL3 判据 | 批次完→归档 |
| tier_disposition.py | PAL3 分层 | 同上 |
| c2660_classify.py | PAL3 族 | 同上 |
| admission_evidence.py | PAL3 准入 | 同上 |
| migrate_*×4（已归档）| PAL3 迁移 | _obsolete |

## evidence（证据/证物——永不删）| 归 docs/evidence/
| 工具 | 证据性质 | 处置 |
|---|---|---|
| gather_reattribution_evidence.py | 反例记录（docstring 自认）| git add -f ✓ |
| _migrate_playermgr.py | 迁移凭证（活数据引用）| git add -f ✓ |
| audit_layout.py（已废弃）| 同源比较反例 | _obsolete+标注 |

## 半通用（思想通用·裁判耦合）——参数化后可 generic
| 工具 | 耦合 | 解耦 |
|---|---|---|
| audit_type_layout.py | VC6 裁判 | 裁判参数化 |
| verify_fix.py | 数据布局 | 布局配置化 |
| compile_regression.py | 路径写死 | 路径参数化 |

## 待分（~60 件——工具清点的其余）
- audit_*×12·check_*×5·fix_*×10·辅助×39——逐件三分（下批）

## 分层原则（删除保留三问）
1. **为什么删/留**：生命周期（一次性/死）·证据链（引用/无）·可复用（替代/独立）·正确性（证伪/有效）
2. **是否通用**：逻辑可搬（参数化）vs 硬编码（项目专用）
3. **是否区分**：必须三分——generic 收编/project 归档/evidence 保留

## audit_* 族三问分类（2026-10-07·用户三分法）
- **generic**（逻辑可搬）：audit_element_sizes/audit_member_semantics/audit_type_layout
- **project-specific**（PAL3 判据）：audit_attribution/audit_attribution_evidence/audit_method_attribution/
  audit_retn_param_count/audit_signature_consistency/audit_structural_attribution/audit_this_in_free_functions/audit_vftable_offset0

## check_*/fix_* 族三问分类（2026-10-07）
- **generic**：check_annotation_names/check_member_extent/check_member_offsets/check_union_member_triviality
- **project-specific**：check_export_annotation_consistency/fix_all_vtables/fix_annotation_names/fix_vtable_splits
