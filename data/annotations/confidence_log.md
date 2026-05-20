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

## 下一步

- 剩余高价值 _todo_ 字段需二进制 query 或 IDA 深度分析
- Rotation 参数等需完整逻辑理解才能语义命名
