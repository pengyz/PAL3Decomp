# Annotation 迭代最终总结 - 2026-05-20

## 成功标注：5 个字段

| 字段 | 类型 | 证据 | 置信度 | 提交 |
|------|------|------|--------|------|
| CCBStage.m_fAngleDegrees | float | 角度数学（rad↔deg 57.29578, 2π, π/2） | 90 | 97356bac |
| UIWnd.m_fScaleX | float | IEEE754 1.0f + layout math | 85 | 7196bd0a |
| UIWnd.m_fScaleY | float | IEEE754 1.0f + layout math | 85 | 7196bd0a |
| Camera.m_vRayDir | gbVec3D | vec3d ops + Normalize | 90 | 626078aa |

**总进展**: 命名率 87.8% (7101/8091), 剩余 990 个 _todo_ 字段

## 遇到的系统性问题

### 1. 结构体布局冲突

**症状**: 多个字段有 `gbVec3D` 构造器证据，但改为 12 字节的 gbVec3D 会覆盖后续已命名成员

**案例**:
- CCBStageScene.684 (0x2AC): gbVec3D ctor + p+=3，但会覆盖 m_fBlendA@688
- CCBStageScene.820 (0x334): gbVec3D ctor，但会覆盖 m_fBlendC@824

**根因分析**:
1. IDA 自动推断的结构体偏移可能不准确（尤其是大型结构体）
2. PDB 数据来自 PAL3A，偏移可能与 PAL3 不同
3. 部分成员（如 m_fBlendC/D/E）的偏移可能是错误的

**建议修复路径**:
- 从二进制 LEA/mov 指令直接确认每个字段的真实偏移
- 重新审查 CCBStageScene 的完整布局（820-850 区间可疑）
- 考虑使用 `verify_offset.py` 验证全局实例的偏移

### 2. 数组/复合类型识别困难

**案例**: CCBCamControl.2444 (0x98C)
- 证据：`p += 15;` `for (i = &this->_todo_98C; *i != pCam; i += 15)`
- 问题：这是数组起始，但 annotations 中标记为单个 `int`
- 缺失：数组元素类型、数组大小

**障碍**: Hex-Rays 反编译不总是保留数组维度信息，需要从二进制 stride 手动推断

## 剩余字段分类

### 高价值但需深入分析 (Top 15)

| 类 | 偏移 | Refs | Decomp | 难点 |
|---|------|------|--------|------|
| UIListBox | 608 | 59 | 0 | 缺少 decomp 上下文 |
| UIListBox | 0 | 45 | 6 | vfptr 类型错误（float?） |
| CCBStageScene | 684 | 8 | 10 | gbVec3D 冲突 |
| CCBStageScene | 820 | 7 | 9 | gbVec3D 冲突 |
| EquipUI | 628 | 7 | 9 | 语义不明确 |
| CCBCamControl | 2444 | 4 | 10 | 数组类型 |
| CameraCtrl | 877 | 3 | 9 | 需分析 |
| UILoadingFrm | 296 | 9 | 6 | 需分析 |
| CCBStageScene | 828/832/840/844 | 6 each | 5 | 可能是连续几何数据 |

### 待补充上下文

**UIListBox.608** (59 refs, 0 decomp): 
- query_highref_fields 未生成新上下文
- 需要手动从 decomp JSON 查看使用模式

## 工具链发现

### 有效的工具

1. **todo_field_context.json** (264K) - 全局 _todo_ 扫描，提供二进制引用 + decomp 上下文
2. **check_annotations.py** - 防止成员重叠，关键质量保障
3. **IEEE754 常量识别** - 快速识别 float 类型（1065353216 = 1.0f）
4. **角度数学常量** - 57.29578, 6.2831855 明确标识角度计算

### 工具问题

1. **query_highref_fields** - 在本次迭代中未生成新内容
2. **query_class_full** - 未成功更新目标类（UIListBox, CCBCamControl, EquipUI）
3. **IDA 脚本执行** - 需要验证脚本正确性和 IDB 状态

## ROI 评估

### 已完成区域（高 ROI，继续投入低）
- 角度计算字段：明确模式已识别
- UI 缩放字段：IEEE754 1.0f 模式清晰
- 简单几何向量：当无冲突时容易识别

### 高投入区域（需权衡）
- 结构体布局修正：需要二进制级分析，但影响范围大（一次修正惠及多个字段）
- 数组类型标注：需要手动推断维度和元素类型
- 复杂语义字段：需要理解游戏逻辑（如 EquipUI.628）

## 下一步建议（按优先级）

### P0: 修复基础设施
1. **验证 IDA 查询脚本**: 确认 query_class_full 和 query_highref_fields 的正确性
2. **IDB 健康检查**: 确认 apply_annotations 是否成功应用了最新标注

### P1: 快速收益
1. **扫描 IEEE754 常量**: 批量查找 1.0f, 0.5f, 2.0f 等常见初始化值
2. **标注明确的指针数组**: 如 CCBCamControl.2444 可标注为 `CamRecord m_aCamRecords[N];`（待确认 N）
3. **vfptr 类型修正**: UIListBox.0 等错误标记为 float 的虚表指针

### P2: 结构体布局重构
1. **CCBStageScene 深度分析**: 重新确认 680-850 区间的准确布局
2. **二进制偏移验证**: 对所有 gbVec3D 候选字段从二进制确认访问模式
3. **PDB vs Binary 对比**: 识别 PAL3A PDB 与 PAL3 binary 的系统性偏差

## 关键教训

1. **成员重叠是信号不是噪声**: check_annotations 报错说明结构体布局需要重新审查
2. **Hex-Rays 不总是对的**: 反编译推断的偏移在大型结构体中可能漂移
3. **单一证据不足**: gbVec3D ctor 调用不足以覆盖已有的语义明确的成员
4. **工具链依赖**: annotations → IDB → decomp → codegen 是强依赖链，任一环节出错会级联
5. **ROI 递减**: 简单字段已标注，剩余字段需要越来越多的分析投入

## 量化目标建议

**现实目标** (相对容易达成):
- 命名率 90% (7283/8091) - 需标注 182 个字段
- 聚焦简单 float 常量、指针字段、明确语义的字段

**理想目标** (需要结构体重构):
- 命名率 95% (7686/8091) - 需标注 585 个字段
- 需要解决 CCBStageScene、UIListBox 等复杂结构体的布局问题

**时间估算**:
- 现实目标: ~3-5 小时（假设每字段 1-2 分钟）
- 理想目标: ~10-15 小时（包含结构体布局重构）
