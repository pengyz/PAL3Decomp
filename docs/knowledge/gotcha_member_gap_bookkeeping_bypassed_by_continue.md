---
name: gotcha-member-gap-bookkeeping-bypassed-by-continue
description: emit_headers 的"补白 gap"逻辑位于循环中部、且在三条 continue 分支之后 ⇒ 走那些分支的成员（inline union/struct、_variants、自引用类型）全部跳过补白 ⇒ 生成头实际布局比注解少若干字节、其后全部成员静默漂移；F63/F65 两次"在分支里补 gap"均失败（按下葫芦浮起瓢，因各分支 start_off 记账口径不一致）
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：成员补白被 `continue` 绕过 + 记账口径不一致（**两次修复失败史**）

## 现象

`pipeline/gen/stages/emit_headers.py` 的成员发射循环里，补白逻辑在**循环中部**：

```
1897/1883  (inline UDT 分支内的内部 gap)
1910  continue        ← 分支①
1921  start_off = off + member_size ; 1922 continue   ← 分支②
1925  start_off = off + 4            ; 1926 continue   ← 分支③
1927  # Insert gap padding before this member if needed
1928  if off > start_off:  emit char _gap_XXX[...]
```
⇒ **走①②③任一的成员都跳过了补白** ✗，而它们的 `start_off` 推进口径**互不一致**
（`off + member_size` / `off + 4` / 内联体的 `max(_union_sizes)`）⇒ 记账与实际发射末端脱节 ✓

**实测（2026-09-21，编译器裁判）**：`RoleSystem` 的 `m_StaticSlotArray`（按值 `UIWnd`）之后
**没有补 pad** ⇒ `union { tagTeamSlotsBOverlay combat; }` 注释写 `+0xC00`、实际落在 **0xBF0**
⇒ 该类型其后**全部成员 −16** ✗；`SceneMgr` 因**按值内嵌 `RoleSystem`** 继承 −16，尾部再叠加一个 −24 ⇒ **−40** ✗

## **为什么**前两次修复失败（必须避免第 4 次重蹈）

| 轮次 | 做法 | 结果 |
|---|---|---|
| **F63**（111轮）| 在 `_variants` 分支里补 gap | **未生效/已回退**：`m_nRoleCount` 仍 −20 |
| **F65**（113轮）| 在 **inline UDT 分支**里补 gap | **已回退**：**修掉了 −26**（出现 `_gap_C664[26]`），但 deltas 由 `{−22,−20,+4}` 变成 `{4,20,22,24}`、`sizeof` 0xE55C vs 注解 0xE544（**+24**）✗ |

F65 自己的结论：*"本分支的**尺寸记账另有问题**（内联体的 `member_size`/`start_off` 推进方式），必须与 gap 一起解决，否则**按下葫芦浮起瓢**"* ✓

⇒ **分支局部修补注定失败**：那些分支的 `start_off` 本就不是真实发射末端 ✗

## 正确的修法（结构性，第 4 次）

1. **单一记账路径**：每个成员发射后，`start_off` 必须是**真实发射末端**
   （内联体的末端 = 其内部布局的实际末端；不要用"估算尺寸"与"off+4"两套口径）；
2. **把补白提到循环顶部**（在任何 `continue` 之前）：`if off > start_off: emit _gap_` ✓
   ⇒ 这样 inline union/struct、`_variants`、自引用类型**都不会再绕过补白** ✓
3. **两个独立裁判验收**（这也是与前三次的关键差别 —— 前几轮没有独立裁判，只能靠试）：
   * `tools/audit_type_layout.py`（编译器裁判）⇒ 该类**成员偏移全对齐** ✓
   * `loop --stages codegen,probe,match` ⇒ **逐函数字节**改善（`SceneMgr::ClearInactiveRoles` 预期 **L1**）✓

## **何时使用**

* 看到"某类成员偏移整体差一个常数（−4/−16/−20/−24/−40…）"⇒ **先查补白是否被 `continue` 绕过** ✓
* 看到"按值内嵌的成员类型"（如 `RoleSystem`/`UIWnd` 按值）⇒ 该类漂移会**沿 DAG 传播**到所有依赖者 ⇒
  **先修叶子类型**（DAG 序）✓
* 任何"在某个分支里补一句"的修法：**先问该分支的 `start_off` 是否等于真实末端**，否则必然按下葫芦浮起瓢 ✗
