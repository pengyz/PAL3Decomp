# T45 迭代台账（2026-10-13 · pal3-converge · 迭代 9 收口）

> **命名注**：`_t6_`（迭代 1）· `_t36_`（迭代 6）· `_t38_`（迭代 7）· `_t41_`（迭代 8）已使用，本迭代 9 收口用 `_t45_iteration_ledger.md`（按复核 task id 命名）避免冲突。

**会话**：pal3-converge · **成员**：diagnoser（T46 收口，T6/T16/T25/T29/T33/T36/T39/T42 等价）
**覆盖**：T43 诊断 → T44 实施 → T45 复核（t45 pass 无需 repair）
**收口态基线**：S2 **127/209** · 总错误 **1337** · L1 **133** · matched **777/952** · partial 552 · L1 率 **133/685 = 19.4%**（仍在 18-19.5% 平台内）

---

## 一、本迭代裁决（Decisions）

### D1 · T43 诊断定位 n_diff=1 四函数簇为最高 L1 ROI
- **背景**：迭代 7-8 L1 停滞在 132，T43 诊断结构性原因
- **裁决**：**n_diff=1 四函数簇**（`AStarPathFinder::FindInOpen/FindInClosed` · `CEffAction::ResetState` · `UITextArea::Destroy`）为最高 L1 ROI（+4 L1 直接转换）
- **诊断结论**：L1 停滞是**结构性**（459/553 = 83% partial n_diff≥20；「差一点就 L1」池仅 19/553 = 3.4%）

### D2 · T44 逐函数裁决（ResetState 修 + FindIn*/Destroy 挂账）
- **裁决**：**逐函数 A 级 objdump 逐字节裁决** —— 1 修（ResetState）+ 3 挂账（FindIn*/Destroy）
- **ResetState 修 ✓**：原始 `0x4c064b c2 10 00` = `ret 0x10`（弹 16 字节 = 4 个 DWORD 实参）vs 编译物 `c2 04 00`（1 实参）⇒ sig `int nVal1` → 4 参 ⇒ **L1 转换 ✓**
- **FindInOpen/FindInClosed 挂账**：byte22 = `8b 41 3c`（原始 `mov eax,[ecx+0x3c]` 经 OPEN）vs `8b 40 3c`（编译物经 i/eax）—— **寄存器分配差**，源形等价改写不够（编译器仍选 eax）⇒ 需更深源形重建（禁猜测）
- **UITextArea::Destroy 挂账**：原始 `83 c1 68; e9 …`（add+**jmp 尾调用**）vs 编译物 `add+call+ret 0x4` ⇒ **尾调用形差**，需签名/返回型对齐使 MSVC6 尾调用优化触发
- **效果**：**L1 132→133（+1，ResetState 转换）** · 总错误 1337 不变 · S2 127/209 不变 · **零翻红**
- **+1 vs T43 预测 +4 归因**：FindIn* 寄存器差 + Destroy 尾调用形 = 2/4 挂账（逐字节证据已备）

### D3 · T45 复核 ResetState 双重坐实 + FindIn*/Destroy 挂账证据完整 + T43 统计可复现（pass 无需 repair）
- **T45 复核**：T44 的声称（L1 +1 · 总错误 0 · S2 0）**当场读实测成立**
- **ResetState 双重坐实**：sig 实参个数错（定义侧 ABI）+ ret 立即数直证
- **FindIn*/Destroy 挂账证据完整**：逐字节 objdump 证据已备（供后续重建源形）
- **T43 统计可复现**：精确命令可复现（s4_baseline.json.rows + s4_diff_detail.json.units 遍历）

### D4 · T45-F1/F2 非阻塞发现
- **F1（low）**：T43 的 n_diff「分布」表**缺 5≤n_diff≤19 桶**（75 函数，表列和 478≠553）—— 须补全桶
- **F2（low）**：T44「2/4 挂账」计数表述按**函数口径**应为 **3/4**（FindInOpen/FindInClosed/Destroy 3 函数挂账）—— **函数数与修复项数混用**

---

## 二、本迭代教训（Lessons）

### L1 · 函数数与修复项数计数口径（T45-F2）
- **症状**：T44 说「2/4 挂账」（修复项口径），但按函数口径是「3/4 挂账」
- **规则**：**计数口径必须明确**（函数数 vs 修复项数 vs 缺陷数），不能混用

### L2 · n_diff 分布表须全桶（T45-F1）
- **症状**：T43 的 n_diff 分布表列和 478≠553（缺 5≤n_diff≤19 桶的 75 函数）
- **规则**：**分布表必须全桶覆盖**（不能省略中间桶）

### L3 · 寄存器分配差需源形重建（T44 FindIn* 挂账）
- **症状**：源形等价改写（`i=i->next`→`i=OPEN->next`）不够，编译器仍选 eax
- **规则**：**寄存器分配差不是源形等价改写能解决的**，需更深源形重建或调用约定调整

### L4 · 尾调用形差需签名对齐（T44 Destroy 挂账）
- **症状**：原始 `add+jmp`（尾调用）vs 编译物 `add+call+ret`
- **规则**：**尾调用优化需签名/返回型对齐**才能让 MSVC6 触发

---

## 三、T45 的 F1/F2 非阻塞发现

| 编号 | 内容 | 处置 |
|---|---|---|
| **F1（low）** | T43 的 n_diff 分布表缺 5≤n_diff≤19 桶（75 函数）| **挂账**（下轮补全桶）|
| **F2（low）** | T44「2/4 挂账」计数口径混用（函数 vs 修复项）| **挂账**（下轮统一口径）|

---

## 四、挂账交接（下轮）

| 项 | 归属 | 备注 |
|---|---|---|
| **🔥 T44 挂账** | codegen | `FindInOpen`/`FindInClosed`（寄存器分配差，需源形重建）· `UITextArea::Destroy`（尾调用形差）—— **逐字节 objdump 证据已备** |
| **T43 ROI 排序** | annotation/codegen | n_diff=2-4 十五函数（**+15 L1 潜力**）· T34 挂账（+0~+5）· 归属批 E3 122（+0~+5）|
| **T45-F1** | 独立轮 | n_diff 分布表补全桶（5≤n_diff≤19 的 75 函数）|
| **T45-F2** | 独立轮 | 函数数 vs 修复项数计数口径 |
| **T41 low** | tests | `test_base_fallback_recursive` 收紧 |
| **T35-F1/F2** | 独立轮 | 3 单元名单 · 簇枚举口径 |
| **T32-F1/F2 · T22-F3 · T17/T19/T28** | 多层 | E3 量化口径 · 漂移清单 · 三形守卫 · 归属批 · adjudicate_lvar_type · O1/O2 |

---

## 五、迭代 9 效果对照（判据 v2.1 `aeb0adf41`）

| 指标 | 迭代 8 收口 | 迭代 9 收口 | Δ | 判据 |
|---|---|---|---|---|
| **L1 绝对数** ⭐ | 132 | **133** | **+1** | ✅ **主判据增长** |
| **S2 绿单元** | 127/209 | **127/209** | **0** | ✅ |
| **总错误** | 1337 | **1337** | **0** | ✅ |
| **matched** | 777/952 | **777/952** | 0 | — |
| **partial** | 553 | 552 | −1 | ResetState 转 L1 |
| **L1 率**（参考）| 19.3% | **19.4%** | **+0.1pp** | ⚠️ 分母失真 |

**L1 率说明**：
- L1 绝对数 **+1**（132→133，ResetState 转换）—— **主判据增长** ✓
- **L1 率 19.4% 仍在 18-19.5% 平台内**（仅 0.2pp 低于上限）
- **L1 增速 > partial 增速**（0.76% vs −0.18%）—— partial 减少而 L1 增长 ⇒ 字节修复兑现 ✓

**迭代 9 里程碑**：
- **L1 累计 +1**（132→133，T44 ResetState 贡献）
- **n_diff=1 四函数簇**：1 修（ResetState）+ 3 挂账（FindIn*/Destroy 逐字节证据已备）
- **总错误 1337 不变**（S2 127/209 不变）

---

## 六、验证证据（本 T46 收口）

| 项 | 命令 | 结果 |
|---|---|---|
| 全量 loop 端到端（含 export）| `python pipeline/cli.py loop --expect-s2 127/209 --expect-errors 1337 --expect-l1 133` | **apply 0/11.2s · export 0/150.0s · codegen 0/183.4s · probe 0/56.6s · match 0/298.5s**（**全 rc=0**）· **✓ 基线断言全部满足** |
| 三基线刷新 | `regression_detector.py --save-baseline` + `compile_regression.py --update-baseline` + match 自动 | `baselines/20261013_120835.json`（209 文件 127 ok 82 fail）· `compile_baseline.json` 已更新 · `s4_baseline.json` stats: symbols=952 matched=777 L1=133 partial=552 |
| L1 当场读 | `python pipeline/cli.py match` | `matched 777/952 · L1 133 · partial 552 · L1 rate 133/685 = 19.4%` · `[L1 ratchet] previous 133 -> current 133` ✓ |
| CLAUDE.md:150 参数 | 编辑 | `--expect-s2 127/209 --expect-errors 1337 --expect-l1 133`（从 `127/209 · 1337 · 132`）|
| 当场读数（非事后基线）| `probe_census.json generated_at=2026-10-13T12:02:30` | S2 127/209 · 总错误 1337 |

**Confidence: high**（**连续五次全量 loop 全 rc=0**（T33/T36/T39/T42/T46）+ 基线断言全部满足 + A 级 objdump 逐字节证据（ResetState ret 立即数直证）+ T45 pass 复核 + T43 统计可复现）

---

## 七、迭代 9 完成度总结

**T43→T45 三任务全部完成**：
- **T43**：诊断 L1 停滞结构性原因 + 最高 L1 ROI（n_diff=1 四函数簇）
- **T44**：逐函数裁决（ResetState 修 L1 132→133 + FindIn*/Destroy 挂账）
- **T45**：pass 无需 repair（ResetState 双重坐实 + 挂账证据完整 + T43 统计可复现 + F1/F2 非阻塞）

**累计效果**：**L1 +1**（132→133）· **S2 127/209 不变** · **总错误 1337 不变** · **n_diff=1 簇 1/4 修 + 3/4 挂账**

**下轮入口**：按挂账 8 项推进（🔥 T44 FindIn*/Destroy 源形重建 · T43 n_diff=2-4 十五函数 +15 潜力 · T45-F1/F2 口径修正 · T41 low · T35-F1/F2 · T32-F1/F2 · T22-F3 · T17/T19/T28）
