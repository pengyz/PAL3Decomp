# 作废声明：`_structural_contradictions.json`（2026-09-20）

**状态：已作废 ✗ —— 不得再引用其任何数字。**

## 为什么作废（独立复核实测）

该产物的偏移取自 **Hex-Rays 反编译的 `this+N`** 文本 ✗，而该口径**量纲错**：
它按**错误的元素尺寸**缩放，实测差 **8×**：
- 该产物报告：**2571**
- asm 真值（`[ebp+505Ch]`）：**20572**

同类问题也存在于 `_attribution_evidence_20260919.md` / `_size_evidence_20260919.md` 的 `max_offset` 数字
（其中 3/20 已过期 ✗）。

## 正确的替代（已有实现，勿重造）

- **偏移/归属取证**用 `tools/attribution_offset_match.py` —— 它**早已**用 asm `[reg+imm]`，
  头注就举了 CIniFile×8 这个例子 ✓，实跑 `--func 0x4EC700` 得正确字节偏移 `0x204 0x4ED0 0x505C` ✓。
  **它只缺一个 `--scan`**（全库扫描需先建 proc index，否则 4752 proc × 579k 行不可接受 ✗）。
- 若需"矛盾清单"，须**从 asm 重算**，并把**输入参数与生成时刻**写进产物 ✓
  （反例：`_geometry_strict_report.json` 的 `warn_count: 6` 因未记录 `PAL3_GEOMETRY_WARN_RATIO` 而不可复现 ✗）。

## 相关（本次三路复核的共同结论）

"尺寸/归属"判据的**参照物被污染**（以注解自述的 `binary_size` 为界）✗ ⇒ 真正缺的是
**独立于注解的证据源** ✓；本作废动作是该方向收尾的一部分 ✓。
