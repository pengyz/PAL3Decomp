# E3 落地记录：detached nested types 解析载体

> **任务**：`docs/specs/2026-09-15-annotation-tombstone-task.md` 的 J/E1 经独立对抗性复核后**改用 E3**
> **日期**：2026-09-15 · **执行**：captain · **方案来源**：独立对抗性复核子 agent `2c66861a` round 2

---

## 1. 为什么改用 E3（J 与 E1 均被取代）

### J 的前提被推翻（captain 派错方向）

captain 曾派 J 调查「PDB 导入是否丢弃含 `::` 的类名」，怀疑 `PlayerMgr::PoisonState` 未从 PDB 导入。
**复核者实测推翻该前提**：

```
pipeline/ida/master_pipeline.py:196-205
# PDB struct 不再由 master_pipeline 导入。annotation 文件已合并 PDB 所有成员数据
cls_ok = 0
```

⇒ **PDB 不贡献任何 struct 类型**。J 的调查方向不成立，已 interrupt 停止（避免浪费）。

### 完整机制（captain 原报告缺失的一环）

`ArcLocale` 退化为 `size=1/data_members=0` **不是** raw.i64 残留、**不是** PDB 导入，而是 `apply` 自己：

1. `apply_annotations.py:1775` → `fwd_names = set(structs.keys())`
   ⇒ **`ArcLocale` 自己就在 fwd_names 里**
2. step 3a 的 pre-pass 对不在 TIL 的名字做 `create_udt(total_size=0)` + `set_named_type`
   ⇒ 建出**空占位 `ArcLocale`**
3. 导入循环对 `+336 pstate` 解析失败 → 在 `create_udt` **之前**就 `return (False, ...)`
4. ⇒ **真实 484 字节布局从未落地**，TIL 里剩的就是第 2 步的空占位
5. export 导出 `size=1/dm=0`，codegen 产出 `class ArcLocale { char _tail_000[1]; }`

**旁证**：`asm/pal3/ida_structs.json` 里 `size=1 且 0 成员`的条目共 **90 个**，`ArcLocale` 与 `PlayerMgr` 都在其中。

### ️ 推广结论（比 ArcLocale 本身重要）

> **任何 struct 只要一条成员类型解析失败，它在导出里就退化为 1 字节空壳，而不是保留上一版布局。**

这是「一个坏成员类型 → 整个结构体报废」的**放大器**，是 codegen 侧大面积塌方的真正起点。

**同类破坏路径（本轮不修，已登记）**：`apply_annotations.py:1974` 在 `[3a] Vtable structs pre-created`
里**先 `del_named_type`**，而 `_vt_off == 0` 时重建的是空 `total_size=0` UDT
（日志证据：`[vtable] RoleStatePanel: 1 table(s), 0 slots`）。若该 struct 随后导入失败，同样只剩空占位。

### 为什么 E3 优于 A/B/D/E1/E2

| 方案 | 判定 | 理由 |
|---|---|---|
| A（改判归属给 SaleUI） | **REJECT** | 前提被证伪；新增无证据断言；与项目自己 t2b 的裁定（`0x19DB8` 以上不属于 SaleUI）自相矛盾 |
| B（删成员） | **REJECT** | 违反 CLAUDE.md 破坏性 workaround；且此处**无**几何不可能论证可用 |
| E1（恢复只含 nested_types 的 `PlayerMgr.json`） | 可行但次优 | 会新增/复活一个受管 struct 注解文件 |
| E2（放进 `sdk_types.json`） | **走不通** | `apply_annotations.py:1745` 的 SDK 路径有 `if not _st.get("known_members"): continue` —— 空成员条目**直接被跳过**，且只能建顶层名 |
| **E3（detached_nested_types.json + pre-pass）** | **ACCEPT（已落地）** | 不新增受管 struct、不复活 `PlayerMgr` 注解文件、不改 `ArcLocale.json`、不新增任何归属或尺寸断言、属 IDA 层（符合 CLAUDE.md「IDA 层能解决的应在 IDA 层解决」） |

---

## 2. 落地内容

### 数据（新增）

`data/annotations/detached_nested_types.json`：
```json
{
  "_purpose": "已解散/无注解文件的父类所遗留的嵌套类型名载体…",
  "_evidence": { "…" : "…" },
  "_maintenance": "若某父类重新获得真实 struct 注解（含 nested_types），应把条目移回并从此文件删除",
  "PlayerMgr": {
    "PoisonState": { "kind": "struct", "binary_size": 32, "_note": "尺寸 32 取自提交 892c0999a 的 stub，非新断言" }
  }
}
```

**关键：名字与尺寸均取自仓库今日已有记录，不新增任何断言**；
且**不主张** `PoisonState` 位于 `PlayerMgr` 的内存里（该主张已被证伪，见
`data/status/_cleanup_correction_poisonstate_attribution.md`）。

### 代码（`pipeline/ida/apply_annotations.py` 新增 §3c）

在嵌套类型 pre-pass 之后、主导入循环之前，遍历该文件并复用现成的 `_forward_decl_nested()`：

```python
_dnt_path = os.path.join(ANNOTATIONS_DIR, "detached_nested_types.json")
if os.path.exists(_dnt_path):
    with open(_dnt_path, 'r', encoding='utf-8') as _df:
        _dnt_data = json.load(_df)
    for _dn_par, _dn_info in _dnt_data.items():
        if _dn_par.startswith("_"):          # 跳过元数据键
            continue
        _forward_decl_nested(_dn_par, {"nested_types": _dn_info}, til)
    log("[3c] Detached nested types: %d parent(s) processed" % _dnt_ok)
```

**加载失败时显式 `raise`**（A 级必须可见）——因为加载失败会让悬垂限定名无法解析，
进而使整个 struct 报废，不可静默。

---

## 3. 实测验证（决定性读数）

```
[3c] Detached nested types: 1 parent(s) processed
[3] Structs: 881/881 imported successfully (fail=0)
FATAL: 0
decomp JSON: 3594
```

| 读数 | E3 前 | E3 后 | 期望 |
|---|---|---|---|
| `[3] Structs` | 880/881 (fail=1) | **881/881 (fail=0)** | ✓ |
| `ArcLocale` | `size=1, data_members=0` | **`size=484, data_members=16`** | ✓ |
| FATAL 数 | 1 | **0** | ✓ |
| 是否新增第 882 个 struct | — | **否**（`PlayerMgr` 仍为 size=1 空占位） | ✓ |
| `ArcLocale.json` / `pstate` | — | **一字未改** | ✓ |

**判据（由随后全链 probe/match 取）**：见本目录 `baselines/latest.json` 与 `s4_baseline.json`。

---

## 4. 复核者主动撤回的两处错误推断（记账）

独立复核者对自己的 round1 报告做了自我更正，captain 采纳：

1. ~~「干净 IDB 的 `PlayerMgr size=1` 来自 init 的 PDB 导入」~~ → **错**。
   `master_pipeline.py` 明写「PDB struct 不再由 master_pipeline 导入」，`cls_ok = 0`。
   `PlayerMgr` 来自 step 3a。
2. ~~「raw.i64 可能自带已填充 TIL」~~ → **错**。
   `strings -n 5 original/PAL3.exe.raw.i64` → 91,074 条字符串、`sub_` 143 条（名字确实可见），
   但 `BindToRoleSlot / ResetAllSlots / GetCGEntry / PlayerMgr / ArcLocale / SaleUI / PoisonState / g_RoleSlotBuf`
   **全为 0**；同一探针在当前 i64 上全部命中（`ArcLocale` 68、`PlayerMgr` 22 等）。
   ⇒ **raw.i64 不含任何游戏名。**

E3 不受这两处影响——它依赖的是「`PlayerMgr` 必定已在 TIL 中」这一**逻辑必然**
（`tagRoleTask.json` 的 bare `PlayerMgr *` 是入口，只能由 step 3a 建出），而非被推翻的顺序推断。

---

## 5. 新登记的独立缺陷（本轮不修）

| id | 缺陷 | 证据 |
|---|---|---|
| **第二处 PlayerMgr 引用** | `tagRoleTask.json` 的 `vec1.slots.pToggle`（@+20）类型是 **`PlayerMgr *`** | 它**不 dangling**（bare 名被 step 3a 建成 1 字节空占位），但是**类型质量缺陷**——指向空壳 |
| **`_vt_off == 0` 先删后建** | `apply_annotations.py:1974` 先 `del_named_type`，`_vt_off==0` 时重建空 `total_size=0` UDT | `[vtable] RoleStatePanel: 1 table(s), 0 slots`；若该 struct 随后导入失败则只剩空占位 |
| **round-5 迁移未改 signature** | `_migrate_playermgr.py` 只改 `name`，**从未重写 `signature`** | `grep -rc 'PlayerMgr::' data/annotations/` → `SaleUI.json` **9 处**、`functions.json` 1 处、`vtable_ownership_evidence.json` 2 处。涉及 10 个方法（`LoadState/InitMode/SetSelectionFlags/SetupPlayerDisplay/ToggleSlot0..4/InitSkillUI/InitShopUI`）。非 FATAL（日志 `[6] Signatures: 3655/3656`），但是与归属不一致的陈旧数据，会误导后续轮次 |
| **可复现性缺口** | 17:31 的 apply **不是裸库上的第一次**：`2 new, 965 skipped` + `skip_named=1596`，而 raw.i64 无游戏名 | ⇒「干净 vs 增量」的对立必须**在一条被记录的 init→apply 链上**重建。**待窗口** |

---

## 6. 相关文件

- 任务书：`docs/specs/2026-09-15-annotation-tombstone-task.md`
- 纠错：`data/status/_cleanup_correction_poisonstate_attribution.md`
- 现象与原始根因：`data/status/_cleanup_finding_dangling_nested_type.md`（§7 方案 A 已作废）
- 独立复核（含 round2）：`data/status/_cleanup_review_arc_locale_dangling.json`
- 门禁：`pipeline/check_annotations.py` §4f（悬垂 `::` 限定类型检测，真阳性 1 / 假阳性 0）