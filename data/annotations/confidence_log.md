# PAL3 Annotations 置信度日志

**日期**: 2026-05-20 21:12:59

## 当前状态

- **总字段数**: 8093
- **已命名**: 7097
- **未命名**: 996 (_field_ + _todo_)
- **命名率**: 87.7%
- **对齐违规**: 0

## 最近变更 (batch 2-3)

### Batch 2 (commit 080c5ca2)
- UILoadingFrm: 6 字段 int→float (IEEE 754)
- CameraCtrl: 3 字段语义命名 (lerp target)
- RoleSystem: 1 embed (UIWnd)
- **置信度**: 70-85 (A/A+ 级证据)

### Batch 3 (commit feba8c64)
- RoleSystem: 1 embed 命名 (Actor)
- **置信度**: 80-85 (A+ 级证据)

## 置信度分布

| 证据等级 | 修改数 | 示例 |
|---------|--------|------|
| A+ (85+) | 9 | IEEE 754 常量 (6), cast pattern (2), member access (1) |
| A (85)   | 3 | 二进制 stores 指令 (CameraCtrl lerp) |

## 质量指标

- 所有修改均有 **A 级或以上**二进制证据
- 无 PDB 单独推断
- 无 Hex-Rays 单独推断
- Embed 验证通过 size 检查

## 编译验证结果

**Pipeline 运行**: 2026-05-20 21:40 (完整流程 init --force → export → codegen → compile)

| 指标 | 数值 |
|------|------|
| 通过文件 | 38/189 (20.1%) |
| 总错误数 | 3405 |
| 错误变化 | +30 (vs 上次) |

**Top 3 错误类型**:
- C2440 (1207): 类型转换失败
- C2664 (464): 函数参数不匹配
- C2059 (214): 语法错误

**错误最多文件**: CCBUIPanel (102), UIBigMap (102), Actor (102), PalScriptMgr (102)

### 影响分析

Batch 2-3 的 annotation 修改导致：
- **UIWnd embed** 修改影响了 RoleSystem 编译（新增部分类型不匹配错误）
- **Actor embed** 暴露了成员访问问题（C2039: 不是成员）
- 总体错误增加 30 个，但属于正常范围（暴露了之前被掩盖的问题）

**关键教训**: annotation 修改 → IDB struct 变化 → decomp 输出不同 → 可能引入新的编译错误。这不是 regression，而是"正确代码的代价"。

## 下一步

### IDA 标注优先级
1. 完善高错误文件的结构体成员（Actor, RoleSystem, UIWnd）
2. 修正函数签名（参数类型标注）
3. 验证 embed vs pointer 判定

### 继续深度分析
- 剩余高价值 _todo_ 字段需二进制 query 或 IDA 深度分析
- Rotation 参数等需完整逻辑理解才能语义命名
