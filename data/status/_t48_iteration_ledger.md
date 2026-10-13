# T48 迭代台账（2026-10-13 · pal3-converge · 迭代 10 收口）

> **命名注**：`_t6_`（迭代 1）· `_t36_`（迭代 6）· `_t38_`（迭代 7）· `_t41_`（迭代 8）· `_t45_`（迭代 9）已使用，本迭代 10 收口用 `_t48_iteration_ledger.md`（按复核 task id 命名）避免冲突。

**会话**：pal3-converge · **成员**：diagnoser（T49 收口，T6/T16/T25/T29/T33/T36/T39/T42/T46 等价）
**覆盖**：T43 诊断（迭代 9）→ T47 实施 → T48 复核（t48 pass 无需 repair）
**收口态基线**：S2 **127/209** · 总错误 **1337** · L1 **134** · matched **777/952** · partial 551 · L1 率 **134/685 = 19.56%** ⭐ **首次突破 19.5% 平台上限**

---

## 一、本迭代裁决（Decisions）

### D1 · T47 n_diff=2-4 十五函数簇逐函数裁决（OnTest 修 + 14 挂账）
- **背景**：T43 预测 n_diff=2-4 十五函数有 +15 L1 潜力
- **裁决**：**逐函数 A 级 objdump 逐字节裁决** —— 1 修（OnTest）+ 14 挂账（三分类）
- **OnTest 修 ✓**：原始 `0x4c0500 32 c0 c3`（`xor al,al`+`ret` 仅清 AL ⇒ **1 字节返型**）vs 我方 int 返型栈临时体 ⇒ sig `int()`→`bool()`（bool/char 对编译字节等价）⇒ **L1 转换 ✓**
- **三分类定性准确**：
  - **指令移位族 ×10**（GetGfxManager / sub_445FA0 / CheckCurRV / SetNewRole / OnMessage / Object3D ctor / AllocEffect / AllocRenderTarget / ProcessAllCmds / ScriptPoolPage_Manage）—— byte13 编码长度差向尾部传播
  - **COMDAT 别名 thunk ×3**（PreLoadEffGroup / RunValueAutomation / RefreshFacePos）—— 原始 `e9 0b 00 00 00` jmp 形
  - **删除析构形 ×1**（scalar deleting destructor）—— 尾调用/删除析构形
- **效果**：**L1 133→134（+1，OnTest 转换）** · 总错误 1337 不变 · S2 127/209 不变 · **零翻红**
- **+1 vs T43「+15 潜力」归因**：14/15 需源形重建（逐字节证据已备）—— T44 教训（源形等价改写可能不够）

### D2 · T48 复核 OnTest 双重坐实 + 三分类定性准确 + +1 vs +15 归因成立（pass 无需 repair）
- **T48 复核**：T47 的声称（L1 +1 · 总错误 0 · S2 0）**当场读实测成立**
- **OnTest 双重坐实**：1 字节返型（xor al,al 仅清 AL）+ bool/char 编译字节等价
- **三分类定性准确**：指令移位族 / COMDAT 别名 thunk / 删除析构形 —— 14 函数全枚举
- **+1 vs +15 归因成立**：14/15 需源形重建，逐字节证据已备

### D3 · T48-F1 非阻塞发现
- **F1（low）**：汇总「移位族 ×9」与 commit 自己的枚举不符 —— 枚举实含 **10 个**（`GetGfxManager`/`sub_445FA0`/`CheckCurRV`/`SetNewRole`/`OnMessage`/`Object3D ctor`/`AllocEffect`/`AllocRenderTarget`/`ProcessAllCmds`/`ScriptPoolPage_Manage`）；9+3+1=13≠14，按枚举 **10+3+1=14** ✓
- **建议**：汇总改 ×10 或附逐函数分类表

---

## 二、本迭代教训（Lessons）

### L1 · 分类汇总计数须与枚举一致（T48-F1）
- **症状**：汇总「移位族 ×9」与枚举 10 个不符
- **规则**：**分类汇总的计数必须与逐项枚举的和一致**（9+3+1=13≠14 ⇒ 10+3+1=14 ✓）

### L2 · T45-F2 同型计数口径（续）
- **T45-F2**：函数数 vs 修复项数混用
- **T48-F1**：分类汇总 vs 枚举计数不一致
- **规则**：**任何计数必须明确口径**（函数数 / 修复项数 / 缺陷数 / 分类族数），不能混用

### L3 · 返型宽度差是独立机制（T47 OnTest）
- **症状**：OnTest 原始 `xor al,al`（1 字节返型）vs 我方 int 返型栈临时体
- **规则**：**返型宽度差**（bool/char/short vs int）是独立的 byte 级差异机制，需按谓词语义选正确返型

### L4 · 指令移位差需源形重建（T44/T47 续）
- **T44 FindIn***：寄存器分配差，源形等价改写不够
- **T47 移位族 ×10**：byte13 编码长度差向尾部传播
- **规则**：**指令移位/寄存器分配差不是源形等价改写能解决的**，需更深源形重建或调用约定调整

---

## 三、T48 的 F1 非阻塞发现

| 编号 | 内容 | 处置 |
|---|---|---|
| **F1（low）** | 汇总「移位族 ×9」与枚举不符（实 10 个）| **挂账**（下轮汇总改 ×10 或附逐函数分类表）|

---

## 四、挂账交接（下轮）

| 项 | 归属 | 备注 |
|---|---|---|
| **🔥 T44+T47 源形重建批** | codegen | `FindInOpen`/`FindInClosed`（寄存器分配差）· `UITextArea::Destroy`（尾调用形）· 移位族 ×10（编码长度差传播）· COMDAT 别名 thunk ×3 · 删除析构形 ×1 —— **逐字节 objdump 证据已备** |
| **T48-F1** | 独立轮 | 分类汇总计数口径（×9 → ×10）|
| **T45-F1/F2** | 独立轮 | n_diff 分布表补全桶 · 函数数 vs 修复项数 |
| **T41 low** | tests | `test_base_fallback_recursive` 收紧 |
| **T35-F1/F2 · T32-F1/F2 · T22-F3 · T17/T19/T28** | 多层 | 挂账 |

---

## 五、迭代 10 效果对照（判据 v2.1 `aeb0adf41`）

| 指标 | 迭代 9 收口 | 迭代 10 收口 | Δ | 判据 |
|---|---|---|---|---|
| **L1 绝对数** ⭐ | 133 | **134** | **+1** | ✅ **主判据增长** |
| **S2 绿单元** | 127/209 | **127/209** | **0** | ✅ |
| **总错误** | 1337 | **1337** | **0** | ✅ |
| **matched** | 777/952 | **777/952** | 0 | — |
| **partial** | 552 | **551** | **−1**（OnTest 转 L1）| ✅ |
| **L1 率**（参考）| 19.4% | **19.56%** | **+0.16pp** | ⭐ **首次突破 19.5% 平台上限** |

**L1 率说明**：
- L1 绝对数 **+1**（133→134，OnTest 转换）—— **主判据增长** ✓
- **L1 率 19.56% 首次突破 19.5% 平台上限**（离开平台需 ≥ 19.6%，尚差 0.04pp）
- **L1 增速 > partial 增速**（0.75% vs −0.18%）—— partial 减少而 L1 增长 ⇒ 字节修复兑现 ✓

**迭代 10 里程碑**：
- **L1 累计 +1**（133→134，T47 OnTest 贡献）
- **n_diff=2-4 十五函数簇**：1 修（OnTest）+ 14 挂账（三分类定性准确，逐字节证据已备）
- ⭐ **L1 率 19.56% 首次突破 19.5% 平台上限**（尚差 0.04pp 到 19.6%）

---

## 六、验证证据（本 T49 收口）

| 项 | 命令 | 结果 |
|---|---|---|
| 全量 loop 端到端（含 export）| `python pipeline/cli.py loop --expect-s2 127/209 --expect-errors 1337 --expect-l1 134` | **apply 0/12.8s · export 0/188.0s · codegen 0/260.4s · probe 0/74.6s · match 0/296.3s**（**全 rc=0**）· **✓ 基线断言全部满足** |
| 三基线刷新 | `regression_detector.py --save-baseline` + `compile_regression.py --update-baseline` + match 自动 | `baselines/20261013_125049.json`（209 文件 127 ok 82 fail）· `compile_baseline.json` 已更新 · `s4_baseline.json` stats: symbols=952 matched=777 L1=134 partial=551 |
| L1 当场读 | `python pipeline/cli.py match` | `matched 777/952 · L1 134 · partial 551 · L1 rate 134/685 = 19.56%` · `[L1 ratchet] previous 134 -> current 134` ✓ |
| CLAUDE.md:150 参数 | 编辑 | `--expect-s2 127/209 --expect-errors 1337 --expect-l1 134`（从 `127/209 · 1337 · 133`）|
| 当场读数（非事后基线）| `probe_census.json generated_at=2026-10-13T12:44:21` | S2 127/209 · 总错误 1337 |

**Confidence: high**（**连续六次全量 loop 全 rc=0**（T33/T36/T39/T42/T46/T49）+ 基线断言全部满足 + A 级 objdump 逐字节证据（OnTest xor al,al 直证）+ T48 pass 复核 + 三分类定性准确）

---

## 七、迭代 10 完成度总结

**T47→T48 两任务全部完成**：
- **T47**：n_diff=2-4 十五函数簇逐函数裁决（OnTest 修 L1 133→134 + 14 挂账三分类）
- **T48**：pass 无需 repair（OnTest 双重坐实 + 三分类定性准确 + +1 vs +15 归因成立 + F1 非阻塞）

**累计效果**：**L1 +1**（133→134）· **S2 127/209 不变** · **总错误 1337 不变** · **n_diff=2-4 簇 1/15 修 + 14/15 挂账** · ⭐ **L1 率 19.56% 首次突破 19.5% 平台上限**

**下轮入口**：按挂账 6 项推进（🔥 T44+T47 源形重建批 17 函数逐字节证据已备 · T48-F1 口径修正 · T45-F1/F2 · T41 low · T35-F1/F2 · T32-F1/F2 · T22-F3 · T17/T19/T28）
