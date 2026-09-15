# Correction: `PlayerMgr::PoisonState` 的归属 —— captain 的论证被独立复核证伪

> **时间**：2026-09-15 · **纠正人**：captain（原主张者）· **证伪者**：独立对抗性复核子 agent `2c66861a`
> **交付物**：`data/status/_cleanup_review_arc_locale_dangling.json`
> **被纠正的文档**：`data/status/_cleanup_finding_dangling_nested_type.md` §7 方案 A

---

## 1. captain 的错误主张（作废）

captain 主张：`PlayerMgr::PoisonState` 是幻影类 `PlayerMgr` 的 nested type；round 5 迁移
（`tools/_migrate_playermgr.py`，提交 `6a8d71924`）把 `PlayerMgr` 解散进 `SaleUI` 时漏搬了
`nested_types`，故 `ArcLocale.pstate: PlayerMgr::PoisonState *` 成为悬垂引用。

**推荐方案 A**：把 `nested_types.PoisonState` 恢复进 `SaleUI.json`，并把类型改为 `SaleUI::PoisonState *`，
理由是"`PlayerMgr` 内存已确证并入 `SaleUI`，所以 `PoisonState` 随之归属 `SaleUI`，属恢复迁移遗漏而非猜测"。

## 2. 实际为真（复核者实测，captain 已复核确认）

### 2.1 决定性反证：`PoisonState` 从来不是 PlayerMgr 的内容

```bash
git show 892c0999a:data/annotations/structs/PlayerMgr.json | grep -i poison   # → 无命中, exit=1
git show 892c0999a:data/annotations/structs/PlayerMgr_PoisonState.json
# → {"name":"PlayerMgr_PoisonState","binary_size":32,"known_members":{},
#    "note":"Nested struct from PlayerMgr::PoisonState. Size=32 from member stride."}
```

在 `PoisonState` stub 被创建的那一刻，`PlayerMgr.json` 里**既没有 `nested_types`，也没有任何该类型的成员**。
它是**顶层扁平名** `PlayerMgr_PoisonState`。
`PlayerMgr.json` 直到 `b40b49bae` 才出现 `nested_types`，而**同一条 commit** 把 `ArcLocale.pstate`
由扁平名 `PlayerMgr_PoisonState` 改成限定名 `PlayerMgr::PoisonState *`。

⇒ **`nested_types` 只是为支撑该限定名而补的「名字解析条目」，不是「PlayerMgr 的内容」。**

### 2.2 captain 混合了两条独立且都无据的证据链

| 要素 | 来源 | 问题 |
|---|---|---|
| 名字 `PlayerMgr::PoisonState` | PDB（`pdb_export.json:184106`） | 项目已于 **2026-09-14** 裁定 PDB 非权威（`_pdb_nonauthority_notice.json`：「全部 mangled 名、类定义、方法签名不得作为归属或命名的权威证据」） |
| 尺寸 32 | 注解自身的成员边界（ArcLocale 336 → 368 的下一成员 `g_bYouDi`） | 与 PDB 无关 |

⇒ 用**非权威名**去改判归属 = **双重无据**。

### 2.3 硬反证：项目自己最近裁定 0x19DB8 以上的区域**不属于 SaleUI**

- round 5 把 PlayerMgr 的 22 个成员并进 SaleUI（`6a8d71924^` 81 → `6a8d71924` 101 成员，max `0x1B2AC`）
- 但**本轮 t2b 又删掉了它们**，判据原文（`_cleanup_fix_saleui.json`）：
  「成员偏移 ≥ `binary_size`(105912)（几何不可能）… 约 10 条源自已解散的旧 `PlayerMgr.json`(107056)」
- ⇒ 「PlayerMgr 内存确证并入 SaleUI」**只在 < 0x19DB8 成立**（含 `m_pstate @0x19F34` 的区域已判不属于 SaleUI）

**范畴错误**：nested type 是**类型系统条目**，不是对象内存字段。用内存归属论证类型归属不成立。

### 2.4 更精确的真根因（修正 captain 的表述）

`apply` **从不删除「注解里已删掉」的结构**（无 tombstone / GC）。增量 IDB 因此永久累积遗留物
（`PlayerMgr` 107056 + 其 nested `PoisonState`）。
⇒ 这才是「增量 881/881 掩盖悬垂、干净重建 880/881 暴露」的**可操作根因**。

### 2.5 captain 引用的 `PlayerMgr.h` 内容是错的

captain 引用 `struct PoisonState { _BYTE _tail_000[32]; }`。那是 **16:55 之前的旧产物**；
17:38 之后该文件已无 `PoisonState`（全文 `char _tail_000[1]`、total `0x1`）。

## 3. 门禁方案（captain 的方案 C）—— 已落地并实测

captain 原推荐"通用版悬垂检测"。复核者指出通用版会喷 **148** 个假阳性（`tagRECT`×145、`tagPOINT`×22、
`_D3DFORMAT`×11、`std::…`、`HWND`、`FILE`、函数指针形态等）。
captain 独立复测：通用版未知类型名 **96** 个（口径不同但同量级）。

**captain 进一步收敛出精确规则并实测**（这是本轮 captain 唯一做对的部分）：

> 规则：**非模板展开**（类型串不含 `std::` 且不含 `<`）时，成员类型里的 `X::Y` 限定名
> **必须**在某注解的 `nested_types` 里存在。
>
> 该过滤**镜像 `apply` 自己的 flatten 逻辑**——`create_fixed_struct` 对含 `std::` 或 `<` 的类型
> 一律展平成 `char[span]`、**从不解析**，故这些 `::` 名不可能是悬垂引用。

实测结果（captain 独立复算）：

| 口径 | 真阳性 | 假阳性 |
|---|---|---|
| 通用版（所有成员类型名都要存在） | 1 | **96** |
| 只按 `::` 限定名（无模板过滤） | 4 | 3 |
| **精确规则（`::` + 非模板展开）** | **1** | **0** |

被模板过滤正确排除的 3 个：

```
CParticleSystem +192  _TexCoordData = std::vector<CParticleSystem::TexCoordQuad, std::allocator<...>>
Role            +96   m_cmdqueue    = std::queue<Role::ScriptCmd, std::deque<...>>
SceneObj        +1708 m_common      = std::queue<SceneObj::Common_State, std::deque<...>>
```

**已落地**：`pipeline/check_annotations.py` 新增 §4f 检查（放在 struct 循环**内**，修正了初版的作用域 bug）。
实测输出：

```
errors=2 warnings=9
悬垂命中 = 1
  structs[ArcLocale]: member 'pstate' at +336 type 'PlayerMgr::PoisonState *'
  references undefined nested type 'PlayerMgr::PoisonState' — no annotation declares
  struct PlayerMgr → nested_types['PoisonState']. apply will fail with _resolve_member_type
  and the struct will degrade to size=1/data_members=0. ...
假阳性 = 0
```

## 4. 复核者发现的、captain 未报告的问题（必须记账）

### 4.1 `AStarPathFinder.cpp` 的 ok→fail **与 ArcLocale 无关**

- `diff /tmp/t7/pre/src/Misc/AStarPathFinder.cpp pal3/src/Misc/AStarPathFinder.cpp` → **空**（该文件从未变过）
- 16:55 的 `globals.h`：`extern int a2; // 0x586194`（`a2 & 1` 合法 → ok）
- 干净重建后：`extern CHAR a2[]; // 0x590638`（IDA 自动名搬家）→ `L19 C2296 '&' : illegal, left operand has type 'char []'`
- **真根因**：codegen **丢失 scalar-dtor 的 `char a2` 形参**
  （`asm/pal3/decomp/AStarPathFinder_~AStarPathFinderchar_00401030.json` 的 signature 含 `char a2`，
  但 `emit_headers.py:1975-1979` 的 `decl = "    ~%s();" % cls_name` 无条件丢弃形参表）
- **长期存在**：09-01 基线里同一行就是 `C2065 'a2' : undeclared identifier`（同根因，当时无同名全局）
- ⇒ 属**被偶然掩盖的旧缺陷暴露**，**不属于 t7 判据豁免范围**

### 4.2 `ExternalStatistics.cpp` 的 ok→fail **未被 captain 归因**

- t7 删除了 `_IDA_MISID_PATTERNS`（`grep -c IDA_MISID`：ORIG=3 → 改后=0）
- `grep -rh "\[IDA_MISID\]" /tmp/t7/pre/src | wc -l` → **84（29 文件）**；当前树 → **0**
- `ExternalStatistics.cpp` **不在** t7 自报的 `changed_files.txt`、也不在影响表里
- 恢复的是 `Concurrency::details::ExternalStatistics::MarkInactive(...)`；
  扫描清单 `_cleanup_scan_attribution.json:9297` 对该类（ii）的建议原文是「**应重命名保留**」，
  **不是原样解除注释** ⇒ 属**半成品恢复**，不满足豁免的「恢复的真实代码」

### 4.3 ⚠️ captain 的 `matched 123→101` 是**不可比**读数（captain 的严重错误）

| 来源 | symbols 分母 | matched |
|---|---|---|
| `_cleanup_verify_fixes.json`（旧代） | **175** | 123 |
| `s4_baseline.json`（当前代） | **135** | 101 |

⇒ **分母不同**，按 captain 自己定的规则「分母变化即判不可比」——**captain 却拿它当退化读了**。
而且**比率反而上升**：123/175 = **70.3%** → 101/135 = **74.8%**。
另有反证：两代 L1 名单已漂移（旧代含 `AStarPathFinder::IsInBounds`，当代含 `UISceneFace::ResetAllSlots`）。

### 4.4 结构性混淆（记账）

`diff -rq /tmp/t7/pre/src pal3/src` → **146 个文件不同**，而 t7 自报只有 **54** 个
⇒ 至少 92 个差异来自**换代 export**。15:57→17:41 窗口里**同时**有 t7/t6 codegen 改动**和**整代重生成，
**任何单点归因都必须先排除"换代"这一变量**。

t7 影响表预测 `53-2+1=52` 数字对上了，但**成员构成不对** ⇒ **52 是巧合**。
（且表里预期 `ArcLocaleRole` fail→ok 在真实树**没发生**，仍是 fail 11 错。）

## 5. 判据现状（复核者独立核对）

| 判据 | 现状 | 达标 |
|---|---|---|
| `L1 ≥ 5` | **5**（5 个名单 captain 与复核者独立核对一致） | ✅ |
| `ok ≥ 53/198` | **52/198**（`baselines/20260915_174124`，分母未变） | ❌ **未达标** |
| struct import `881/881` | **880/881** | ❌ **未达标** |
| `oob == 0` | 0 | ✅ |

## 6. 作废声明

- **不得再引用**「`PoisonState` 是 `PlayerMgr` 的内容 / 应归属 `SaleUI`」这一说法。
- `data/status/_cleanup_finding_dangling_nested_type.md` 的 **§7 方案 A 及其论证作废**；
  该文件的 §1–§5（现象、根因链、影响面、`PoisonState` 是占位脚手架）**仍然有效**。
- **不得再引用**「`matched 123→101` 显示退化」这一说法——两者分母不同、不可比，且比率上升。