# S2 衰退修复 Spec（2026-11-01）

## 背景

S2 从基线 135/214 降至 127/214（-8），错误净改善 7 条（28 消失 vs 21 新增）但分布变化。
本 spec 定位根因、明确修复路径、给出验证面。

## 根因分层

### 层 1：codegen 表达式翻译（C2784，+36）
- **病灶**：decomp `*(gbVec3D*)(X+N)` → codegen `*(gbVec3D*)X + N`（括号丢失）
- **效果**：`gbVec3D + int` 无 `operator+` → C2676 → C2784（std::operator+ 回退）
- **修法**：在 stage4 表达式翻译处保括号/优先级（修生产者）
- **验证**：C2784 降 0，S2 +4~6

### 层 2：annotation 改名声明同步（C2065，+10）
- **病灶**：批 15-16 改名（`UIFrameWnd__deleting`/`UIFrameWnd_BBB0`）后 header 声明未同步
- **修法**：改名必须同步 header 声明（改名后 codegen 重生成 header）
- **验证**：C2065 中 `UIFrameWnd_*` 降 0

### 层 3：annotation 类型标注（C2440，+15）
- **病灶**：`CCBPanelSlot → int`（27 条）等类型标注错误
- **修法**：逐条修正 annotation 类型（需二进制证据）
- **验证**：C2440 降 15+

### 层 4：annotation 归属（C2039/C2227，+18）
- **病灶**：`RoleAtt* → SaleUI_SortData`（归属错误）等
- **修法**：逐条修正归属（vtable/偏移证据）
- **验证**：C2039/C2227 降 18+

## 修复优先级

| P | 修复 | 预期 S2 增量 | 工作量 |
|---|---|---|---|
| **P0** | 层 1：codegen 表达式括号修 | +4~6 | 中 |
| **P1** | 层 2：改名声明同步 | +2~3 | 低 |
| **P2** | 层 3：annotation 类型修 | +1~2 | 高（逐条） |
| **P3** | 层 4：annotation 归属修 | +1~2 | 高（逐条） |

## 验证面

1. `cli.py loop` S2 读数当场读
2. `regression_detector --check` 逐码净增减
3. `cli.py check` 0 errors
4. TDD 测试锁（24 测绿）
5. C1003 截断单元最大行号不降

## 约束

- 只改管线（annotation + codegen），不手改源码
- 每处 annotation 修改需二进制证据
- 禁止批量修改未验证字段
- 修生产者不修症状
