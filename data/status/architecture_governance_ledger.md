# 架构治理进展+后续方案（落账 2026-10-08）

## 当前进展（架构治理 52 轮+技术债主身）
| 面 | 状态 | 产出 |
|---|---|---|
| 架构梳理 | ✅ | workflow_review.md（现行链+支撑工具+过时面）|
| 技术债清理 | ⚠️ P0✓P1✓P2（测试 triage+根治）·主身（管线/门禁债）进行 | gate_registry/genericity_layering |
| 工具清理分类 | ✅ | genericity_layering.md（三分法全工具：generic 27/project 53/特定 8/test 5）|
| 历史清理 | ✅ | docs/evidence/（归档）+workflow_review |
| 门禁债 | ✅ check 真双注清（0 errors）·pre-commit 统一（→cli.py check）| 5d6dcd7c6 |
| 管线债 | ✅ 绝对路径→PROJECT_ROOT（stage4/transform 5 处）| 5ef173cbf |

## 测试态（真态）
- 512 绿·29 红·37 skip（P0 纠偏后真态——9 module skip 撤）
- 29 红分类：env 9·编码 1·期望 2·契约 4·悬空 4·隔离 1（复核分类）

## 后续方案（技术债主身——非测试）
### 门禁债
- [ ] pre-commit 安装（.git/hooks——机器强制 3→4）
- [ ] 表外 10 门禁归位（登记表四栏补全）
- [ ] [D] vtables 告警清（5 类——GlowObj 族）

### 工具债
- [ ] tools/test_health.py（红/skip 分类器+棘轮）——挂 cli.py status
- [ ] generic 参数化（4 件先行：error_classifier/compile_regression/audit_type_layout/bin_oracle）
- [ ] tools/README 重写（乱码+死链）

### 管线债
- [ ] 注解直读收敛（annotation_view 单一读点——≥6 处待）
- [ ] check_annotations 5 读点深修（P0-4 残留）

### 文档债
- [ ] tests/README 更新（15/15 过时→578 collected）
- [ ] CLAUDE.md 检查点表补 probe 步骤

## 纪律（每轮强制）
- 复核→测试→提交推送·删除保留三问·三分法·禁"落地后不 grep 核实"
- **停测试逐件**（测试=债的子类非主身——用户纠偏）
