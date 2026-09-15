# 干净重建暴露的长期被掩盖缺陷：`PlayerMgr::PoisonState` 悬垂类型引用

> **发现时间**：2026-09-15 · **发现方式**：从 `original/PAL3.exe.raw.i64` 干净重建 IDB 后跑 `apply`
> **性质**：**不是本轮任何改动的回归**；是 round 5 迁移的遗漏被增量 IDB 掩盖至今
> **严重度**：**高** —— `ArcLocale` 在导出中退化为空结构，其下游引用面广
> **裁决要求**：需要用户决定类型归属（captain 无 A 级证据，按 CLAUDE.md 不得猜）

---

## 1. 现象

干净重建（`init` → `apply`）后：

```
pipeline/ida/_logs/apply_annotations_log.txt:43:
[FATAL] Struct import failed: ArcLocale → add member +336 'pstate'
        type 'PlayerMgr::PoisonState *' FAILED: _resolve_member_type

[3] Structs: 880/881 imported successfully (fail=1)
```

**对比**：同一份注解、增量 IDB 上为 **881/881**。差异仅来自 IDB 的构建路径。

## 2. 下游影响（实测）

- `asm/pal3/ida_structs.json` → `ArcLocale`：**`size=1, data_members=0`**（16 个成员全丢）
  - 对照正常结构：`SceneInfo: size=132, 7 members`、`RC_ARG: size=28, 5 members`
- `ArcLocale` 被广泛引用：`pal3/src/Data/CGameData.cpp`、`pal3/src/free_functions.h`、
  `pal3/src/free_functions.cpp`、`pal3/src/Combat/CCBUI.cpp`、`pal3/src/Role/Actor.cpp`
- ⇒ **codegen 会基于这个空 `ArcLocale` 生成错误源码**，影响面不止一个文件
- 生成源码 `pal3/src/Misc/ArcLocale.h:22` 仍打印 `PlayerMgr::PoisonState * pstate;`（该头文件是旧产物，
  引用了一个 codegen 不会再声明的类型）

## 3. 根因链（全部可复核）

1. `PlayerMgr` 是**幻影类**，已由 `tools/_migrate_playermgr.py`（提交 `6a8d71924`，round 5）**解散进 `SaleUI`**。
   该脚本的 A 级证据（其 docstring 自载）：
   - vtable `0x56B5CC` 由 `0x45acde`（在 `??0SaleUI` 内）与 `0x45ae81`（在误标为 `?ctor@PlayerMgr` 的函数内）**共同装载** → 同一虚表、同一类
   - `0x45AE60` 的唯一调用者是 `?_scalar_dtor@SaleUI@@`，且按**降序**走成员 → 它是 `~SaleUI`
   - **0 个 PDB-mangled `PlayerMgr` 名**（17 个 IDA 伪名）；PDB 证实的 12 个 `SaleUI` 方法与伪名方法物理交错
   - 抽查 6 个 `PlayerMgr` 命名方法全部访问 ≤ `0x19DB4`，落在 `SaleUI` 的 `0x19DB8` 分配内
2. **但该迁移脚本完全没有处理 `nested_types`**（实测 `grep -n nested tools/_migrate_playermgr.py` → **0 命中**）。
3. 原 `PlayerMgr.json`（`git show 6a8d71924^:…`）有：
   `nested_types = {"PoisonState": {"kind": "struct", "binary_size": 32}}`
   迁移后 `SaleUI.json` 的 `nested_types = []` ⇒ **`PoisonState` 被丢弃**。
4. `ArcLocale.json` 的 `known_members["336"]` = `{"name": "pstate", "type": "PlayerMgr::PoisonState *", "source": "annotation"}`
   该类型由 `b40b49bae`（nested type system）引入。
5. ⇒ `ArcLocale.pstate` 引用了一个**只存在于已解散类**下的类型 → 干净重建时 `_resolve_member_type` 失败。

## 4. `PoisonState` 是什么（重要）

孤儿头 `pal3/src/Misc/PlayerMgr.h`（gitignored 生成物）显示：

```cpp
class PlayerMgr {
public:
    struct PoisonState;
    struct PoisonState {
        _BYTE _tail_000[32];      // ← 32 字节纯填充，无真实成员
    };
```

⇒ `PoisonState` 是**嵌套类型解析的占位产物**（scaffolding），**不是有内容的真实类型**。
它由提交 `892c0999a`「拆分 13 个嵌套类型为独立 struct stubs」时代产生。

## 5. 为什么被掩盖至今（本发现的核心价值）

`apply` 的 `_forward_decl_nested()`（`apply_annotations.py:1786+`）会在主循环前为所有 `nested_types`
建 forward declaration。**增量 IDB 的历史血统里曾成功处理过 `PlayerMgr.json`**，使 `PlayerMgr::PoisonState`
的 TIL 条目残留在库中，于是 `ArcLocale` 能解析成功。

干净重建没有这条历史血统 ⇒ 悬垂引用暴露。

⇒ **这直接证伪了交接文档「IDB 可从 raw 复现」的隐含假设**：
reproducibility ≠ 两组状态等价。`880/881`（干净）与 `881/881`（增量）**不是同一状态**。

## 6. 与 t3 判据的关系（重要澄清）

t3 的判据原文是「本改动不应改变任何计数（881/881 保持）」。**该判据的前提（881/881 是诚实读数）不成立**：

- 增量 IDB 的 `881/881` 是**历史掩盖的产物**，不诚实；
- 干净重建的 `880/881` **才是诚实读数**——但它暴露的是**另一个缺陷**，不是 t3 的过错。

**结论：t3 本身没有引入回归；t3 的显式失败判据正确地捕获了一个长期被掩盖的真实缺陷。**
这是 t3 的价值体现，不是它的失败。

## 7. 我（captain）为什么没有直接修

`data/annotations/structs/ArcLocale.json` 要修，等于要决定 `pstate` 的正确类型。候选：

| 候选 | 依据 | 问题 |
|---|---|---|
| 删掉该成员 | `ArcLocale.cpp` **从不访问 `pstate`**；其唯一存在理由是引用已解散的幻影类 | 丢失 +0x150 的偏移记录（但该记录本身无法编译） |
| 改 `SaleUI::PoisonState *` | `PlayerMgr` 内存已并入 `SaleUI`（A 级证据）→ `PoisonState` 应随之归属 `SaleUI` | 需同时把 `nested_types.PoisonState` 搬进 `SaleUI.json`；且 `PoisonState` 是 32 字节占位、无真实成员 |
| 建独立 struct `PoisonState` | 提交 `892c0999a` 曾把嵌套类型拆为**独立 stubs** | 与「归属已解散类」的证据冲突 |

**CLAUDE.md 明令**：「每一处 annotation 修改必须有二进制直接证据」「禁止猜测性修改」。
我在注解层**没有 A 级证据**判定 `pstate` 的正确类型 ⇒ **不得自行修改**，转用户裁决。

## 8. 建议（captain）

1. **立即修的门禁缺口**（不涉及注解，可做）：`pipeline/check_annotations.py` **无悬垂类型引用检测**
   （实测 `grep -n "resolve|dangling" pipeline/check_annotations.py` → 0 命中）→ 应在 `check` 阶段
   就报出「成员类型引用了不存在的 struct」，而不是等到 `apply` 才 FATAL。
2. **修迁移遗漏**：把 `nested_types.PoisonState` 从已删除的 `PlayerMgr.json` 恢复进 `SaleUI.json`
   （**这在注解层有依据**：PlayerMgr 的内存已确证并入 SaleUI），并把 `ArcLocale.pstate` 的类型改为
   `SaleUI::PoisonState *`。**待用户批准**（因为涉及注解语义）。
3. **复核 round 5 迁移是否还有其它遗漏**：该脚本只搬了 `methods`/`members`，未搬 `nested_types`；
   需检查是否还有别的类引用了 `PlayerMgr::` 下的其它嵌套类型。
4. **修正交接文档**：`§2.1`「三层一致性」与「IDB 可复现」的表述需补上「增量 vs 干净重建不等价」这一事实。

## 9. 待办清单

- [ ] 用户裁决 `pstate` 的类型归属（§7 三选一）
- [ ] `check_annotations.py` 补悬垂类型引用检测
- [ ] 扫查 `data/annotations/` 里是否还有其它 `PlayerMgr::` 悬垂引用（captain 已确认 `PoisonState` 是本例，
      但未做全量扫描）
- [ ] 迁移脚本 `tools/_migrate_playermgr.py` 的 `nested_types` 遗漏修正（若再次运行）
- [ ] 交接文档 §2.1 更正