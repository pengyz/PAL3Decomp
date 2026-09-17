# 基线（最终，2026-09-15 13:43）—— 取代此前所有基线记录

> 此前记录（`ok=56/198`、`L1=14`）与"回退低点"（`ok=51/203`、`L1=6`）**均已被本文档取代**。

## 实测口径（`export → codegen all → probe all → match`）

```
census (probe_census.json):  ok = **55 / 202**
match  (当次 stdout):        matched **156/180** · **L1 14** · partial 119
                             unmatched 24 · oob 0 · unresolved-synth 23
                             [L1 ratchet] previous 14 -> current 14   ⇒ 无退化，match_exit=0
err = 3703 · C2039 = 1068 · __vftable 族 = 718
错误码 Top: C2039 1068 · C2660 634 · C2664 318 · C2440 285 · C2227 202 · C2059 169
```

## 回退→修复的完整因果（**已闭合**）

| 阶段 | ok | L1 | matched |
|---|---|---|---|
| "良好态"记录 | 56/198 | 14 | 150 |
| **回退低点** | **51/203** | **6** | **114** |
| 修复①`b590e97b1`（codegen 孤立体）| 55/202 | 6 | 147 |
| **修复②`d1445c151`（反引号特名 ×4 处）** | 55/202 | **14** | **156** |

**根因**：Hex-Rays 的**反引号特名** `` `scalar deleting destructor' `` 在**四处**未归一化
（`collect.py` 跳过判据、`emit_headers._get_scalar_dtor_classes`、
`compare_pal3._split_mangled_name`、`compare_pal3.build_mangled_map`）
⇒ 既使 4 个文件编译失败（`ok −4`），又使 8 个 `??_G` 匹配不到（`L1 −8`）。
⇒ 归一化为 `_scalar_dtor`/`_vector_dtor` 后两者同时恢复。

## 失败文件分布（ROI 地图）

```
错误数分布:  1错 13 · 2错 13 · 3错 10 · 4错 3 · 5错 9 · 6错 3 · 7错 4 · 8错 2 · 9错 5 · 10错 1
             ≥11错 **79**（长尾）      总失败 142
★ ≤2 错: **26 个文件** ⇒ 全部修好即 **+26 ok（55 → 81，+47%）**
★ ≤10 错: **63 个文件** ⇒ 理论上限 **+63 ok（55 → 118）**
```

**近失文件的首错码分布**：`C2660 23 · C2664 9 · C2440 8 · C2065 5 · C2100 3 · C2039 2 · C2059 2 · …`
⇒ **前三类共 40 个文件（63%）都是"函数调用与声明不匹配"**。

⚠️ **但 C2660 的 23 个符号【完全不重复】**（`CalcSpeed`/`Read`/`SetData`/`RenderGeomQuad`/…）
⇒ **没有共同的机械根因，每个都需独立诊断**（这是 ROI 的决定性事实）。

## `error_classifier` 分类（147 个失败文件）

```
annotation_fix 63 (42.9%)  ·  codegen_fix 21 (14.3%)  ·  hexrays_limit 57 (38.8%)
manual_idb 1 (0.7%)        ·  unknown 5 (3.4%)
```
（对比旧记录 `annotation_fix 49 (33.6%)` / `codegen_fix 33 (22.6%)`
⇒ **codegen_fix 从 33 降到 21**，说明各修复有效。）

## 遗留

| 项 | 状态 |
|---|---|
| `UICamera.cpp`（7 错）| ❌ 类型/注解类：`C2446/C2040`（`v8 != g_SceneMgr.m_nCurrentRoleSlot` 指针 vs int）+ `C2065`（`unk_C10968` 未声明）|
| `F2`（补 `CEffShock` 的 `vtables`+`methods`）| 注解已保全（`data/status/_cleanup_f2_ceffshock_attempt.json`），**基线现已稳定，可安全测量**；但实测 `C2039` 未动（近失池 0 个 `__vftable` 文件）|
