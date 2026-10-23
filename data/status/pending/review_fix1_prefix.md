# 修① 复核

## 正确性
方向对、实现错，带回归。
- **声称机制未修**：注释称「基名须精确同名替身才 skip」，但 `hash-suffix-rev`（`_k.startswith(_tn)`+余下`__$`）与旧前缀匹配对真实语料等价——6 个基名仍被跳过（14:33 export 日志 6× `(hash-suffix-rev)`）。
- **真实改动=打断 P0-B 截断容错**（回归）：`_origin` 键为截断 hash（余下 hex 尾≠`__$`）⇒ 6 个内层变体 old-skip→export（纯函数对比 delta 仅这 6 个变 outcome），纯修①产物中无引用=**死定义**，与具名替身双源并存。
- 基名报的替身任意且 size 不合（RoleSlotArray 896 vs 报告 PalScriptSlotStateOverlay 864）。

## 效果验证
**「7→6」不成立，真实进展 0**（自跑 pytest+export）：
- 口径混淆：7=6 基名+1 gbNodeMsgObj `::$`（`struct ` 异形，测试不数）；测试口径本就 6。
- 实测纯修①产物（14:33 json）：`_inline_` 悬空 **6→6**、全口径 **7→7**、+6 死定义。今悬空 0 系未提交修向② `[inline-supplement]` 之功。
- 自跑 `cli.py export` 产物与 14:47 字节全同；pytest 7 passed。

## 修②准备
1. 决策层正解：基名仅精确同名+size 校验才 skip（删 `hash-suffix-rev`）+ 恢复截断前缀命中 ⇒ supplement 可退役。
2. 引用侧去 `struct `/`class ` 前缀（残余悬空 `struct gbNodeMsgObj::$…`、`Misc/class.h` 假 include 同族）。
3. size 实测：512=512✓·298=298✓·164=164✓·12=12✓；**RoleSlotArray 896≠864 ✗、teamSlotOverlay 1228≠873 ✗** ⇒ 该 2 处禁 rewrite（移位+丢 script_state/m_state 致 C2039），须 typedef/hoist。

## 挑刺
1. P0-B 回归实证；注释与实现不符，后人误信基名已处理。
2. 7→6 跨口径；台账「剩悬空」列 5 名（漏 `_inline_tagRoleTask_vec1`，实 6）。
3. 测试盲区：只数 `_inline_`，漏 `::$`/`struct ` 异形 ⇒ 7/7 绿仍 1 悬空。
4. ⚠️ 挡修②：15:05 census **S2 ok 0/214**（基线 135/209）：C1083 `Misc/class.h` 无此文件 + C2079 `_inline_RoleAttRemarkSkills_skillCount` 未定义，root `_ns_udts.h`/`RoleAttRemarkSkills.h`（emit/hoist 待定谳）——当前组合勿提交。
5. R1：复核中 lead 两改 export_full.py 并连跑管线；本复核锚定 132944759+14:33 产物。

## verdict
**不通过（修①应重做）**：机制未修（6 基名仍误顶替）、实效 0 悬空+6 死定义（P0-B 回归）、7→6 假进展，commit/台账数字须更正。修②走 1+2+3 决策层正解，先解 S2 0/214。
