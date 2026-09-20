# P1：第二判据 —— "401 条矛盾到底是 `binary_size` 污染还是归属错"（2026-09-20）

> 方法：**只读**连接两份已有产物，不新造取证 ✓
> `data/status/element_size_adjudication.json`（元素尺寸候选/矛盾层）× `data/status/alloc_sizeof.json`
> （`operator new(N)`+ctor ⇒ **独立于注解**的第二尺寸源 ✓，`{operator_new, rows:[{class,ctor,alloc_size,annotation_size,verdict}]}`）

## 1. 结果（实测）

| 量 | 值 |
|---|---|
| `contradiction=True` 的行 | **401** |
| 其中**能连上第二判据**的（类级） | **155** |
| `alloc(N)` 与**元素字面量**一致 | **3** ✗ |
| `alloc(N)` 与**注解 `binary_size`** 一致 | **0** ✗ |
| **三方互不一致** | **152** ✗✗ |

典型（字面量/注解/`alloc(N)`）：
`UIListBox 84/1208/1760` · `UIStatic 208/152/248` · `UIScenePanel 376/14232/14236` ·
`UISceneMap 584/1012/232` · `Camera …/12956/544`（规格 §2.5 提过的 17 条 MISMATCH 之一 ✓）

## 2. **关键结论：不能据此判定因果** ✗（比"查出谁错"更重要 ✓）

**152/155 三方不一致 ⇒ 第二判据并不能当裁决者** ✗，原因是**三者测的不是同一个对象** ✓：
- `??_L` 的 `size` 是**元素**尺寸（数组/`eh vector` 的**成员元素** ✓），**不等于**该类的**整对象**尺寸 ✗；
- `alloc(N)` 是**整对象**分配尺寸 ✓；
- 注解 `binary_size` 是**整对象**声明尺寸 ✓。
⇒ 把"元素字面量"与"整对象尺寸"直接比，**构造上就会不一致** ✗ —— 这正是 `contradiction` 里那 401 条的大部分成因 ✗✓。

**支持该解释的近匹配证据** ✓：`UIScenePanel` 的 **注解 14232 vs `alloc(N)` 14236，Δ=4** ✓
—— 两者显然是**同一个整对象**（差 4 字节，可能是尾部 padding/一个未标成员 ✓），而"字面量 376"是**其内嵌元素** ✗。

## 3. 因此的正确做法（P1 的产出 = **修正问题的提法** ✓）

**不能问**"401 条矛盾是尺寸错还是归属错" ✗ —— 先要**把测量对象对齐** ✓：
1. **整对象类**：只比较 `alloc(N)` ↔ 注解 `binary_size` ✓（**排除元素字面量** ✗）⇒ 这一类才是"尺寸真伪"问题 ✓
   （17 条 `alloc_sizeof` MISMATCH 就是它的样本 ✓；其中 `UIScenePanel` 的 Δ=4 值得优先看 ✓）
2. **元素尺寸类**：只比较 `??_L` 字面量 ↔ **被构造数组的声明元素类型尺寸** ✓（要求该类的 `binary_size` 与
   `count`/数组声明一致 ✓）⇒ 不一致才是"归属错或数组类型错" ✓
3. **只有第 1 类**能回答"`binary_size` 是否被污染" ✓；**第 2 类**回答"ctor 归属/数组元素类型是否错" ✓

**⇒ 交付 2/3 必须先按"测量对象"分层** ✓，否则 `INCONCLUSIVE` 的定义仍是错的 ✗
（这与总评审的 M2 同一性质：**判据的语义没对齐，就会既漏报又误报** ✓）。

## 4. 与规格 §2.5 的关系（ROI 仍成立 ✓）

本层（元素尺寸）可机判面 **O(10–38)** 个类 ✓；而射程外（(b) 通路错 / (c) codegen 改写错）占当前错误 **≥59%** ✓
⇒ **P1 的产出没有改变 ROI 判断** ✓，但**修正了下一步该"比什么"** ✓。


---

# ⚠️ 复核后的更正（2026-09-20，复核者 `12f09f9e` 全程只读）

## A. 本文档的错误（均已证实 ✗）
1. **§2 的机制结论 C4 是错的** ✗：`??_L(ptr,size,count,ctor,dtor)` 清的是 **count 个各 size 字节、
   元素 ctor 即该地址**的数组元素 ⇒ **元素尺寸就是该元素类的整对象 `sizeof`** ✓ —— **与 `binary_size` 可比** ✓。
   **真正不可比的原因不是"元素 vs 整对象"，而是"连接本身无效"** ✗：155 对里
   **110 对锚在"dtor 名"** ✗、**42 对锚在任意方法名** ✗、**只有 3 对锚在真 ctor（name==类名）** ✓。
   （row 级：**306 任意方法名 + 140 dtor 名 + 13 真 ctor** ✓）
   ⇒ **401 条矛盾的主导成因是"注解类名合并 / 方法（含 ctor）错挂"** ✗，"元素 vs 整对象"只是表象 ✗。
2. **§1 的"与注解 size 一致 = 0"是同义反复** ✗：155 这个集合本身就是按 `alloc != annotation` 切出来的 ✓；
   **不切 = 3**（`UILoadingFrm 332/332` ✓）。
3. **§1 的 C1 口径未写明** ✗：155 来自"(行, 主张类) 去重对 ∩ 28 个 alloc 类，且过滤掉 `alloc==annotation`" ✓；
   不过滤 = **158**、按行数 = **128** ✓。
4. **§1 的抽样掩盖了决定性事实** ✗：`UIStatic` 实际有 **{208:3, 248:3}** ✓ —— 只写 208 **恰好把唯一可裁决的 248 藏掉** ✗；
   `UIListBox` 是 **{84:3, 584:30}** ✓；**`Camera` 根本不在 155 里** ✗（它与任何 `??_L` 站点无 ctor/dtor 地址连接 ✓）
   —— 把它当"典型三元组"是**集合混淆** ✗。
5. **§1 的"17 条 MISMATCH"是 11:30 的快照** ✗：直接读当前 structs JSON ⇒ 6 行已漂移
   （`CCBUIPanel→22112`、`UISceneFrm→3288`、`UITitle_ArcSave→4004`、`JusticeBookUI→56192`、
   `UIRoleSelectDialog→2204`、`CScreenMode→5496` ✓），**当前 OK=14 / MISMATCH=11** ✓；
   漂移来自 `f87db02f0`（"8 vtable-proven size corrections"）与 `1c2234d06` ✓。
6. **`alloc_sizeof` 的类标签是注解派生的** ✓（`methods` 里 `name==类名` 或伪名 `'ctor'` ✓）；
   `UISceneMap`/`UILoadingFrm`/`UITitle_ArcSave`/`JusticeBookUI`/`UICoverFrm`/`UIListBox`/`CCBRoleState`/
   `CCBUI`/`UISceneFrm` 的 alloc 行锚的都是**伪 `'ctor'`** ✓。
7. **C6 的分层 ② 当前不可实现** ✗：缺"地址 → 元素类"解析器 ✓，且"被构造数组的声明元素类型尺寸"
   在注解里**根本不存在** ✗（分层 ① 可实现，且 `f87db02f0` 已在做 ✓）。

## B. 复核者独立得出的**可裁决清单**（第三判据 = 该类 ctor ±0x2000 邻域方法的 `[reg+imm]` 最大位移 + 4，只读 ✓）
| 类 | 注解 size | 独立读数 | 裁决 |
|---|---|---|---|
| **`UIStatic`** | **152** ✗ | 248（3×`new(248)` + 3×`??_L size=248` + `sub_440740` 写 UIStatic 自己的 vtable `0x56AD88` + 类内成员位移上界 ≥200）| **注解过小，真值 248** ✓ —— **且 `f87db02f0` 曾落地 152→248，被 `1c2234d06`「synced to IDB」改回 152 ⇒ 这是一次回退** ✗✗ |
| **`Camera`** | **12956** ✗ | 544（`push544→new→call 0x41BE80`（`name=='Camera'` 的真 ctor，写 `off_56AA84`）；邻域上界 **544 = alloc**）| **注解被吹大，真值≈544** ✓（12953 的位移来自**错挂方法** `0x52BEB0 'InitUIElements'`（`0x52Bxxx` 区）✗）|
| `CCBRoleState` | 22224 ✗ | 20568（其 ctor `sub_456AB0` 访问 `[esi+5054h]` ⇒ 恰好 20568 ✓）| 注解过大 ✓（22224 来自错挂 `0x46F390` ✗）|
| `CCBStageScene` | 1012 ✗ | 972（邻域上界）| 注解过大 ✓（1040 来自错挂 `0x52B1E0` ✗）|
| `UICoverFrm` | 14952 ✗ | ~12956（邻域上界 12957≈alloc）| 注解过大 ✓（此前"alloc 可能不是整对象"的怀疑**被推翻** ✓）|
| **`UIListBox`** | 1208 ✗ | **1760**（邻域上界）| **注解过小，真值 1760** ✓ ⇒ **`1c2234d06` 的"family split"结论需重审** ✗ |
| `UIScenePanel` | 14232 | 14236（= 本文 C5 的 Δ=4 ✓，**是尾成员少标**，非无法解释的 padding ✓）| 注解少 4 ✓ |
| `ScreenEffectNode` | 220 ✗ | 1060（<244 必错；1060 未证实但更可信）| 注解必错 ✓ |
| 不可裁决 | — | `UISceneMap`(232/1012/上界 1108 三方互斥 ✓)、`CCBUI 116`(伪 `ctor` + 邻域上界 2632 ⇒ 配对错 ✓)、`UIScenePanel` 的 376 侧（需 vtable 反查 ✓）| — |

**其它实测**：复核者**逐字节读 exe 校验 `alloc_sizeof` 的 28 条 exhibits** ⇒ **28/28 OK、0 FAIL** ✓
（`push imm==alloc_size`、`call new→0x55353B`、`call ctor→该行 ctor` ✓）⇒ **该产物的数字可信** ✓。
`UIStatic 0x44BE60`（字面量 208）**不是同一对象** ✗：它是某 208B 类的 ctor（只 `call sub_4422E0`，
dtor thunk `0x44BE70`），而 `UIStatic.json` 把"208B 类 ctor"记成了方法 `DestroyChainToBase` ⇒ **方法错挂** ✗。

## C. 结论修正
- **本文档 §2 的"第二判据不能当裁决者"应限定为**："**在未证实 ctor 归属之前**不能" ✓；
  一旦用**真 ctor**（`name==类名`）连接，**它就能裁决** ✓（见 §B 表 ✓）。
- **最强判据（复核者排序）**：① **`tools/alloc_point_size.py`**（有 `mov ecx,eax; call ctor` 的 this 挂钩，
  比 `alloc_sizeof` 的 96B 窗口更严 ✓）＝最合适的**整对象裁决者** ✓；② **ctor 的 vtable-store 反查**（定归属最有效 ✓）；
  ③ `attribution_offset_match.py`（`[reg+imm]` 精确命中 ✓）；④ **`_geometry_strict_report.json` 不建议当裁决者** ✗
  （只管膨胀且阈值粗 ✓：`Camera` 仅 warn(31.8) ✓，`UIStatic` 这种**少标**完全不可见 ✗）。
- **下一步（复核者建议，我采纳 ✓）**：用 `alloc_point_size.py --scan` + **ctor 的 vtable-store 反查**
  重建"**真 ctor → 类**"映射 ✓（补齐 C6 ② 的元素类解析器 ✓），再对**整对象类**只比 `alloc(N)` ↔ `binary_size` ✓；
  **首批落地：`UIStatic 152→248`（回退回归 ✓）与 `Camera 12956→544`** ✓。
