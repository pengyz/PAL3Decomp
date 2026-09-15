# 任务书：注解层 tombstone/GC + 悬垂类型引用治理（J + E1）

> **状态**：**J 调查中 / E1 待落地** · **立档**：2026-09-15 · **HEAD**：`aacdf69c5`（工作区另有未提交改动）
> **缘起**：从 `original/PAL3.exe.raw.i64` 干净重建 IDB 暴露了 `ArcLocale.pstate: PlayerMgr::PoisonState *` 悬垂类型引用。
> **前置证据**：`data/status/_cleanup_finding_dangling_nested_type.md`（§1–§5 有效，§7 方案 A 已作废）、
> `data/status/_cleanup_correction_poisonstate_attribution.md`（纠错）、
> `data/status/_cleanup_review_arc_locale_dangling.json`（独立对抗性复核）

---

## 1. 问题陈述

`apply` 报 `880/881 (fail=1)`：
```
[FATAL] Struct import failed: ArcLocale → add member +336 'pstate'
        type 'PlayerMgr::PoisonState *' FAILED: _resolve_member_type
```
后果：`ArcLocale` 在导出中退化为 **`size=1, data_members=0`**（16 个成员全丢），
而它被 `CGameData.cpp` / `free_functions.h` / `free_functions.cpp` / `CCBUI.cpp` / `Actor.cpp` 引用。

**判据影响**：`struct import 880/881`（未达标）、`ok 52/198`（未达标，硬线 53）。
`L1 = 5` **未退**（5 个 L1 函数不受影响）。

---

## 2. 真根因（已定谳）

**`apply` 从不删除「注解里已删掉」的结构（无 tombstone / GC）。**

增量 IDB 因此永久累积历史遗留物：`PlayerMgr`（107056）及其 nested `PoisonState`。
于是 `ArcLocale.pstate` 能靠**残留的 forward declaration** 解析成功 → 增量态 `881/881`。
干净重建没有这条历史血统 → 悬垂暴露 → `880/881`。

⇒ **`881/881`（增量）是被掩盖的假读数；`880/881`（干净）才是诚实读数。**

---

## 3. 为什么不能靠注解打补丁了事（架构判断）

`PlayerMgr::PoisonState` 的**名字来自 PDB**，而项目已于 **2026-09-14** 裁定 PDB 非权威
（`_pdb_nonauthority_notice.json`：「全部 mangled 名、类定义、方法签名不得作为归属或命名的权威证据」）。
所以：

- 在注解层"恢复一个名字载体"（E1）**能解悬垂，但保留了以非权威名为依据的类型**；
- 它在**干净 IDB 里本就应该存在**——干净 IDB 的 `PlayerMgr size=1` 与 PDB 的 `PlayerMgr(union,size=1)` 一致，
  说明 `PlayerMgr` **来自 init 的 PDB 导入**；但**同一 PDB 里的 `PlayerMgr::PoisonState`（size 32）没被导入**
  （`ida_structs.json` 里 13 个含 `::` 的条目中没有它）。

⇒ **J（先查）**：若 PDB 导入器**丢弃含 `::` 的类名**，那是一个 **IDA 层缺陷**。
   CLAUDE.md 明令「**IDA 层能解决的问题在 IDA 层解决**」。
   修 J 可能**一举消除本悬垂**，且比在注解层加补丁正确得多。

---

## 4. 行动顺序

### J（先做）：核查 PDB 导入是否丢弃含 `::` 的类名

**要回答的问题**：
1. init / `master_pipeline` 的 PDB 导入路径是哪个脚本？它如何遍历 PDB 的类/结构？
2. `PlayerMgr::PoisonState` 在 `data/pdb/pdb_export.json` 里的**确切记录形态**是什么（是否含 `::`、size、kind）？
3. 导入器是否对含 `::` 的名字做了**跳过/归一化/改名**？在哪一行？
4. 若确实丢弃：**能否修复**使 PDB 的嵌套类名正确导入？修复后 `ArcLocale.pstate` 是否自动解析成功（即 `881/881`）？
5. 若不能修（有合理理由）：记录"为何不可迁移"，转 E1。

**判据**：修复后干净重建应达 **`881/881`**，且 `ArcLocale` 的 `data_members` 恢复为 **16**。

### E1（J 不行才做，或与 J 并存作为保险）：注解层保留名字载体

恢复一份**只含 `nested_types`、无任何成员/方法**的 `data/annotations/structs/PlayerMgr.json`：
```json
{
  "name": "PlayerMgr",
  "binary_size": 1,
  "_naming_note": "仅作为已记录嵌套类型名的解析载体。PlayerMgr 是幻影类，已于 round 5（6a8d71924）解散进 SaleUI；本条目不主张任何成员/内存归属。",
  "nested_types": { "PoisonState": { "kind": "struct", "binary_size": 32 } }
}
```
**注意**：这**不**主张 `PoisonState` 属于 `PlayerMgr` 的内存（那是被证伪的错误主张），
只提供 `ArcLocale.pstate` 那个 `::` 限定名的解析目标。

**`*` 与 32 字节的判定标「待窗口」**：注解写 `*`（指针）是**类型错误**——
`create_fixed_struct` 会把它建成 4 字节指针 + 28 字节未覆盖洞（布局靠 codegen 的显式 gap 兜住，
故不破坏布局，但语义错）。改它需二进制证据。

---

## 5. 已完成的独立项（不在本任务内，但相关）

| 项 | 状态 | 产出 |
|---|---|---|
| **门禁**：`check_annotations.py` 新增悬垂 `::` 限定类型检测（精确规则：`::` ∧ 非模板展开） | ✅ 已完成并实测 | 真阳性 1（`ArcLocale.pstate`）/ 假阳性 0；正确排除 3 个模板假阳性（`CParticleSystem::TexCoordQuad`/`Role::ScriptCmd`/`SceneObj::Common_State`） |

## 6. 另立的独立缺陷（不在本任务内）

| id | 缺陷 | 证据 |
|---|---|---|
| **H** | codegen **丢失 scalar-dtor 的 `char a2` 形参** → `AStarPathFinder.cpp` `C2296` | `emit_headers.py:1975-1979` 的 `decl = "    ~%s();" % cls_name` 无条件丢弃形参表；decomp signature 含 `char a2`。**长期存在**（09-01 基线同一行是 `C2065 'a2'`） |
| **K** | t7 删 `_IDA_MISID_PATTERNS` 导致 `ExternalStatistics.cpp` ok→fail，属**半成品恢复** | 扫描清单 `_cleanup_scan_attribution.json:9297` 原建议是「**应重命名保留**」而非解除注释；该文件不在 t7 自报变更集 |

---

## 7. 记账守则（本轮踩过的坑，必须继承）

1. **判据分母**：`s4_baseline` 的 `symbols` 分母会随代次变化（175 → 135）。**分母变即判不可比**，
   不得用 `matched` 绝对值跨代比较（captain 本轮因此误报"退化"，实际比率 70.3% → 74.8% 上升）。
2. **换代变量**：`diff -rq` 显示 146 个文件差异，而单任务自报常只有 54 个
   ⇒ 任何单点归因必须先排除「整代重生成」。
3. **增量 vs 干净重建不等价**：不得再用增量 IDB 的读数证明"注解正确"。
4. **PDB 非权威**：不得用 PDB 名称/尺寸作为归属或命名的证据。

## 8. 交付物

- `data/status/_cleanup_fix_tombstone_gc.json`（J 与 E1 的结论、命令、实测数字、`pending_window`）