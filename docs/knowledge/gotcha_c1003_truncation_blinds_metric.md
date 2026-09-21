---
name: gotcha-c1003-truncation-blinds-the-error-metric
description: MSVC 在单单元 ~100 条错误处 C1003 停住 ⇒ 在截断单元里修掉早期错误会被隐藏的后续错误填满，总错误与 (code,msg) 多重集都可能完全不变；必须改看"列表内最大错误行号"
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：C1003 截断让"总错误"指标对真实进展失明

## 现象

一个**验证正确**的修复可以做到"总错误完全不变"，从而被发布门禁误判为中性：

| 指标 | 修复 `::ShowWindow` 补限定前 | 后 |
|---|---|---|
| 总错误 | **2150** | **2150** |
| `(code,msg)` 多重集（`regression_detector`）| — | **新错误 0 / 收敛 0** |
| 消失的条目 | — | **9 × `C2660 'ShowWindow' : does not take 2 parameters`** ✓ |
| 新增的条目 | — | **9 条无关族**（`C2296`/`C2440` 成员函数指针、`C2039 __vftable`、`C2227`）|

原因：`Combat/CCBStage.cpp` · `Combat/CCBUI.cpp` · `free_functions.cpp`
在 **~102 条错误**处被 MSVC 的 **C1003**（`error count exceeds 100; stopping compilation`）停住。
在这些单元里修掉早期错误 ⇒ 列表**立刻被原本隐藏的后续错误填满** ⇒ 聚合指标不动 ✗。

## **为什么**必须换度量

* C1003 的上限**不是可配的编译选项**（VC6 固定 ~100），所以"多给点数"修不了；
* 该单元的**错误列表是"前 N 条"**，因此可用的替代信号是**列表推进到哪里**：
  修好早期错误后，第 102 条错误会出现在**更靠后的行** ✓

| 单元 | BEFORE 列表内最大行号 | AFTER | 判定 |
|---|---|---|---|
| `Combat/CCBUI.cpp` | 3389 | **3787** | ✓ 前进 398 行 |
| `Combat/CCBStage.cpp` | 3823 | **3855** | ✓ 前进 32 行 |
| `free_functions.cpp` | 2879 | 2879 | 未触及（对照 ✓）|

**如何证明"新增的 9 条不是本次改动造成的"**：本次改动只在 `ShowWindow(` 调用上插 `::`
⇒ 它**不可能**产生"成员函数指针"类错误（`C2296 '*' : illegal, left operand has type 'class CCBStage *(__thiscall CCBStage::*)'`）
⇒ 这些必是**旧有的、此前被截断隐藏的**错误 ✓。**"新增错误是否与改动同族"是最实用的判据。**

## 工具落地（2026-09-21）

* `python3 pipeline/cli.py status` 现在打印 **C1003 截断单元表**（`errors` + **列表内最大行号**）；
* 判据：**最大行号变大 = 有真实进展** ✓；
* 发布门禁"改善 ≥ 新增"在截断单元上**会误判为中性** ⇒ 此时改用
  「新增错误是否同族」+「截断进度是否前进」，并在 commit message 写明理由 ✓；
* 单测：`tests/test_preflight.py` 的 `test_truncated_units_reported_with_max_line` /
  `test_non_capped_units_not_reported` / `test_truncation_progress_is_visible_in_render` ✓

## **何时使用**

* 任何"改完发现错误数没变"的情况：**先看改动是否落在截断单元里** ✓，不要立刻判为无效；
* 评估改动时：同时看 `总错误`、**逐码净增减**、`status` 的截断表 —— 只看其中一个都会骗人 ✗；
* 引用"总错误 2150"作为基线时：记住它是**下界**（3 个单元的计数被封顶）✓。