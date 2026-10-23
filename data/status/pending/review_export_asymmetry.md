# export 不对称根因复核

## 根因验证
✓ 属实。L713-715 注释原文：「annotation 具名实体与已有具名替身的 `_inline_`/`$` 合成名**不再导出**——消除「具名实体 + 合成名」双源并存发射（C2011 型重定义 921 根因：ida_structs ∩ annotation 具名 = 858 同名交集双发射）」。gate 落点 `export_structs` L998 `_named_supersede_decision` ⇒ `continue`。但 lead 因果链少一环（见 verdict）。

## 不对称验证
✓ 实证（自跑扫描 `asm/pal3/ida_structs.json`）：`data_members` 引用 `_inline_`/`::$` 共 **18 处**，其中 **7 处悬空**（定义被 gate、引用仍在）：`_inline_PalScript_m_RoleSlotArray`(PalScript.m_RoleSlotArray@396) · `_inline_FightItem_desc`@96 · `_inline_PalScript_m_szDialog1`@1300 · `_inline_RoleAtt_Remark`@6 · `_inline_RoleSystem_m_teamSlotOverlay`@1684 · `_inline_tagRoleTask_vec1`@16 · gbNodeMsgObj 内层 `::$`。另 11 处定义尚在 ⇒ **逐名不一致**，非全删全留。下游：`census_after1-4` 各 4 条 `'_inline_...' : undeclared identifier`（C2065）✓。

## 修法评估
对称二选一**都不完整**：
- **都删**（引用也删/改写）：断 decomp 成员访问（`PalScript_SetActionint_00421560.json`：`_inline_PalScript_m_RoleSlotArray *pSlots`）；替身 size 不合——`PalScriptRoleSlotOverlay` 896 ≠ 基 union 864 ⇒ 无脑 rewrite 改后续成员偏移。
- **都留**：对**无具名替身**的悬空名是正解（无双源 ⇒ 无 C2011）；有替身者仍须跳过。

推荐**按替身存在性分派 + 引用闭包对称**：有替身 ⇒ 跳过定义 + 成员改写（**size 对齐校验**）或发 `typedef 替身 _inline_X;`（typedef 不与 struct 同名冲突，MSVC6 安全，引用不断）；无替身 ⇒ 保留导出。

## verdict
根因注释属实 ✓、不对称属实 ✓，但真机制是**定义侧 gate 与 `data_members` 透传不同步** ＋ **prefix 容错过宽误顶替**：`_k.startswith(_tn)` 使内层变体替身键（`_inline_PalScript_m_RoleSlotArray::$C73B…`→`PalScriptSlotStateOverlay`）把**基 union** `_inline_PalScript_m_RoleSlotArray`（864）也顶替掉；名形推导 L749 只认 `__\$hash` 尾形，基名不命中 ⇒ 布局无人承载。⇒ 修序：①收紧匹配（基名须**精确同名替身**才 skip；前缀匹配仅限 `__\$hash` 后缀形）②引用侧对称化（改写/typedef + size 校验）。单纯「都删/都留」分别引入断引用/残留双源。
