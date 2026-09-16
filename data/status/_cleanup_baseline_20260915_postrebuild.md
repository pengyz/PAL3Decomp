# 基线登记：干净重建后（2026-09-15 23:54）

> **背景**：本会话记录的「`ok=56/198`、`L1=14`」在**污染态与干净重建下都无法复现**。
> 本文档登记**当前实测口径**的基线，供后续测量使用。

## 实测口径

```
操作：cli.py init --force（从 original/PAL3.exe.raw.i64 重建）
      → export → codegen all → probe all → match

census (probe_census.json, 当次写出):  ok = **51 / 203**
match  (当次 stdout):                  matched 114/128 · **L1 6** · partial 95 · unmatched 14
其它:  decomp = 3598 · ida_structs structs = 1031 · oob = 0
```

## ⚠️ 与旧记录的差异（**未查明原因**）

| 指标 | 旧记录（23:23）| 现在（干净重建）| Δ |
|---|---|---|---|
| `ok` | 56 / 198 | **51 / 203** | **−5** |
| `L1` | 14 | **6** | **−8** |
| 单元总数 | 198 | **203** | +5 |

**已排除的 4 个原因（逐条实测）**：
1. F2 注解 —— 回退注解后跑完整管线，读数完全相同
2. `apply` 累积污染 —— `init --force` 干净重建后回退依旧
3. 我的 `emit_headers`（S0）改动 —— 回退到 `9cb436305` 版并重跑 codegen，错误数不变
4. `mangled_map` 键冲突 —— 离线 diff 键集合完全相同（9700）

**未查明**：剩余候选为 `t3`（`apply_annotations.py` 改动）、`t5/t6`（export/mangler）或环境因素。
**⚠️ 且无法验证"这 5 个文件在会话起点是否通过"** —— `probe_census.json` **不被 git 跟踪**，无历史。

## 跌出 passing 的 5 个文件（**0 个新进入**）

```
pal3/src/Misc/JusticeBookUI.cpp     pal3/src/Misc/UIStatic.cpp
pal3/src/Misc/UITitle_BBTY.cpp      pal3/src/Misc/scScriptInstance.cpp
pal3/src/UI/UICamera.cpp
```

**⚠️ 它们不是"被 C1003 截断"，而是小错误数失败**：
```
UICamera.cpp: 7 错（C2446/C2040 ×2、C2065 'unk_C10968'、C2228 …）
UIStatic.cpp: 6 错（C2143 syntax ×4、C2447 missing function header）
```

## ⇒ 结论与用法

1. **后续测量一律以本口径为准**（`ok=51/203`、`L1=6`）；
   引用 56/198 或 L1=14 时必须注明"旧记录、当前不可复现"。
2. **验收硬线（`ok≥56`、`L1≥14`）当前不成立** —— 需先解决上述 5 个文件的失败
   （它们错误少、可逐个修，**修好即 +5 `ok`**），并查明"为何从通过变失败"。
3. **切勿**在基线未稳定时测量单点改动的效果（本会话已因此浪费两轮）。
