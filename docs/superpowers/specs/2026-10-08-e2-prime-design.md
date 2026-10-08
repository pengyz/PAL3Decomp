# E2′ 设计（纠错而非补全）— base_class 继承链

**日期**：2026-10-08
**状态**：v1 · **经两路对抗复核修订**（可行性/成本 + 风险/爆炸半径）
**性质**：**纠错**（纠正已有错 `base_class`），**不是补全**（不填空 `base_class`）

---

## 0. 前提已被实测证伪（两路复核收敛）

| # | 发现 | 证据 |
|---|---|---|
| **1** | **KB 链方向和根都错** | **objdump 实证**（复核 #2）：<br>· `0x445aa0` UIWnd ctor：先 `lea ecx,[esi+0x24]; call 0x432660`（**成员子对象** ctor）后 `mov [esi],0x56AEC8` ⇒ **UIWnd 是根**（size 68）<br>· `0x452fd0` SceneObj ctor：`call 0x445aa0`（UIWnd ctor）**之后**才 `mov [esi],0x56B200`，自有成员从 +0x44=68 起 ⇒ **`SceneObj : public UIWnd @0`**（**与 KB 方向相反**）<br>· `0x44f065` CGameData ctor：先 `mov [esi],0x56b094`、**无基类 ctor 调用** ⇒ **CGameData 也是根**（size 28268）<br>· 尺寸算术：68 ≥ 1784 ≥ 28268 **不成立** |
| **2** | **预期收益不存在** | MISATTRIBUTED 当前 **9 处**（非 83）；"83" 出自 `_cleanup_review_c2660_independent.md:147`（是历史 347 的子集）<br>**ROWTABLE 形 `(((X*)this))->X::M()` 已编译通过、base@0 时与 `this->X::M()` 字节等价**（`UIProgressBar.cpp` 16 处 ROWTABLE 且 S2 ok）⇒ 转换**零字节收益、零 S2 收益** |
| **3** | **仓库已有正面否决** | `docs/knowledge/decision_sceneobj_composition_not_inheritance.md`（**v4 终裁**，四轮对抗修订）明文「**不是 base_class（行表不是继承）**」；v3 已用 `base_size` 否决同一条链；现行 `[ROWTABLE]` 分支 + `_rowtable_family.json`（63 类）就是它的落地<br>⇒ `arch_gbui_…md` ≈ **被否决的 v2 读法**<br>⚠️ **`MEMORY.md` Decision 段漏收 decision 文**（索引缺口）|
| **4** | **"this 调整验证"零覆盖** | 35 个 vtable 槽 thunk 检查 **0 个 `sub ecx,N`/`add ecx,N`/`lea ecx,[ecx+N]`** ⇒ 所有基类偏移 0 ⇒ **MI/offset 类错误是空集**<br>**反例**：`UIWnd : CGameData` 与 `SceneObj : UIWnd` **都偏移 0、都无 thunk** ⇒ 检查全绿但继承边是错的 |
| **5** | **同类写入有事故记录** | `apply_annotations.py:440-446` 原文："observed 2026-09-13: UIWnd/SceneObj writes without base_size **cost 9 S2 units**" ⇒ **E2 要写的边已写过一次、净损 9 个 S2 单元** |

---

## 1. 真正的问题：**已有错 `base_class` 正在造成损害**

| 错误 | 损害 | 证据 |
|---|---|---|
| `SceneObj : public PalScriptWaitObj, GlowObj, TaskMgr_...`（3 基=80B）| **静默吃掉**注解成员 `+0x44 m_fTimerLimit`、`+0x4C _SaveTaskInfo` | 生成头 `pal3/src/Scene/SceneObj.h` 46→44 |
| `MUIDialog : UIDialog, MUIDialogMgr, UIFrameWnd` | **32 处 C2385 ambiguity** | `probe_census` |

**1759 条错误里继承相关的只有 `C2385(34)` + 少量 `C2039`**，与 `C2440(391)`/`C2664(252)`/`C2273(138)`/`C2227(127)`/`C2228(93)` 无关。

---

## 2. 范围（实测收窄）

| 原范围 | **真实范围** |
|---|---|
| 719 个空 `base_class` | **61 个**（有 vtable ∪ 有派生，**8.5%**）|

**719 的真实构成**（复核 #1 实测）：

| 层 | 数量 | 占比 | 对 8 个消费者的影响 |
|---|---|---|---|
| **纯 POD**（无 vtable·无派生·无 methods）| **566** | **79%** | **永不生效** |
| 叶子类带 methods | 92 | 13% | 仅 caller 侧 |
| 有派生类（无 vtable）| 32 | 4% | 有 |
| 有 vtable | 24 | 3% | 有 |
| 其余交叉项 | 5 | 1% | 有 |

**全仓仅 65 个类被当基类引用**。

**E2′ 的目标范围**（纠错，非补全）：**25 个多基类 + 5-10 个已实证 UI 家族**。

---

## 3. 三步走

### Step 0：裁决两文冲突（**写入流程在此之前不得启动**）

| 动作 | 产出 |
|---|---|
| 勘误 `arch_gbui_seven_slot_vtables_inheritance_chain.md` | 标注 v2 读法已被 v4 终裁否决；链方向错误（实为 `SceneObj : UIWnd`，非 `UIWnd : SceneObj`）|
| `MEMORY.md` Decision 段补收 `decision_sceneobj_composition_not_inheritance.md` | 修索引缺口 |
| E2 清单收益估计 **~500 → 0** | 修正收益口径 |

**证据已齐**：尺寸格 · objdump ctor 顺序 · 88/510 churn · 0-9 收益 · 2026-09-13 事故

### Step 1：纠正错 `base_class`（真正该做的）

| 项 | 动作 | 验收 |
|---|---|---|
| `SceneObj` 3 基类 | 纠正为 `['UIWnd']`（objdump 实证）| **成员零丢失**（`+0x44`/`+0x4C` 回到生成头，44→46）|
| `MUIDialog` 3 基类 | 纠正 | **C2385 消除** |
| 25 个多基类 + 5-10 实证 UI 家族 | 逐个裁决 | `tools/audit_type_layout.py` 通过 |
| 顺带修 | `CEff*` 3 条真单调违规（4<36）| `base_size` 自洽 |

### Step 2（可选）：清 9 处 MISATTRIBUTED 真实根因

| 形态 | 数量 | 修法 |
|---|---|---|
| `AStarPathFinder` 函数名带括号伪影 | 7 | 修两个单元的函数名 |
| callee 命名错位 | 2 | `misattribution_ledger` bucket + `audit_attribution_evidence` 裁决 |

⇒ 验收：**MISATTRIBUTED → 0**

---

## 4. 风险闸（替代无效的"this 调整验证"）

| 闸 | 命令 | 抓什么 |
|---|---|---|
| **① 成员零丢失** | 生成头 `+0xNN` 集合 == 注解 `known_members` 偏移集合（逐类 diff）| **静默吃成员**（S2 查不出的那类；今天 `SceneObj` 是 44/46）|
| **② 编译器裁判** | `tools/audit_type_layout.py --only <Cls>`（含自校验探针）| 布局错误 |
| **③ 尺寸格门** | 20 行脚本：派生尺寸 ≥ 每基尺寸 + `base_size==首基尺寸` | **假链**（零假阴性，本次即用它否决 KB 链）|
| **④ 当场读数** | `loop` 的 `L1≥94` / `S2≥99` / `own_unresolved=0`（棘轮回写基线，**不可事后查文件**）| 回归 |
| **⑤ C2385 单调降** | `is ambiguous` **34 → 0** | 菱形歧义 |
| **⑥ 越界读不增** | `tools/scan_misattribution.py` 的 `min_required_span(callee) > sizeof(声明类型)` | 归属/类型错 |

**⚠️ 不做**："this 调整验证"（**零覆盖**，见 §0.4）· **不设覆盖率棘轮**（违反 `decision_goal_metric_over_proxy_metric.md`）

**「this 调整验证」的 5 个反例**（复核 #2，明确给）：
1. **base@0 反例（致命）**：`UIWnd : CGameData` 与 `SceneObj : UIWnd` **都偏移 0、都无 thunk** ⇒ 调用点字节完全相同，**检查全绿但继承边是错的**（本族 100% 落在此）
2. **共享槽反例**：`0x445E70`/`0x445B90`/`0x445D10` 各出现在 7–8 张表、this 全不调整 ⇒ "无调整"证明不了归属
3. **非虚直调反例**：本就无 thunk；callee 用同一 this 不代表属于该类（成员对象/全局单例/IDB 命名错位同样字节）
4. **字节流没有类信息** ⇒ 只能验偏移，验不了归属；E2 的核心风险恰恰是归属
5. **完全绕开主风险**：`apply` 的 `base_size` 重定基、`emit_headers` 的成员丢弃，在任何调用点都看不到

---

## 5. 爆炸半径（复核 #2 实测，"8 个"低估了）

### 🔴 高危（直接改字节）
| # | 位置 | 补全后会变什么 |
|---|---|---|
| 1 | `pipeline/ida/apply_annotations.py:439-600`/`895-1015` | **写进 IDB**：`inherit=" : public %s"%base_class[0]`、`data_size=size-base_size`、**`if offset<base_size: continue`（丢成员）**、MI 时 `base_offset += bc_size` 推基类偏移 ⇒ IDB 布局变 ⇒ Hex-Rays 文本变 |
| 2 | `pipeline/gen/stages/emit_headers.py:1395`/`1625-1725`/`1900-1965` | 生成头靠**自然 C++ 布局 + `_gap_`**，基类块一变全部成员偏移错位；`_collect_base_vtable_names` 沿 base_class 上溯 ⇒ **vtable 布局变** |

### 🟡 中（改生成码文本）
| # | 位置 | 说明 |
|---|---|---|
| 3 | `pipeline/gen/ast_transform.py:350`/`1380-1530` | `_is_derived_from()` 决定发 `this->Base::M()` 还是 `[MISATTRIBUTED]`/`[ROWTABLE]` |
| 4 | `pipeline/gen/data.py:312-325` | **硬编码主基在偏移 0、只取 `[0]`、丢弃基类 2+**（`Role` 第二基 @+0x40 永不生效）|
| 5 | `pipeline/gen/stages/stage2_semantic.py:65-80` | `_base_names`（只取 `[0]`）|
| 6 | `pipeline/gen/stages/stage3_cleanup.py:1482-1530` | `_qualified_vftable_offset` 三态；`'strip'` 误判会**静默错址写** |
| 7 | `pipeline/gen/stages/stage4_substitution.py:1580-1640` | `base_sizes` **硬编码 4** |

### 🟢 低
8. `pipeline/check_annotations.py:279-300`（唯一会"发现矛盾"的地方）· 9. `import_gbengine_types.py:159` · 10. `annotation_view.py`

### ⚠️ 未列但同样读 `base_class` 的工具
`tools/vtable_mapper.py:78`（只取 `[0]`）· `vtable_class_reconcile.py:124` · **`layout_assert_gen.py:982-1019`（虚基静默丢弃、零 warning）** · `mi_base_offsets.py:154,213` · **`cascade_scan.py:40-66`+`cascade_plan.py`（改继承会改变 apply 的越界拒绝范围）** · `fix_vtable_splits.py` · `annotation_diff.py:308` · `test_multi_inheritance_regression.py:77` · **`test_pipeline.py:66,105-221`（有断言会翻）** · `tests/test_qualified_vftable_tristate.py` 等

### ⚠️ 类型不统一陷阱（必须防）
898 struct 里 179 个非空 = **159 个 `list` + 20 个 `str`**。各消费者归一化不一致：
- `data.py` 取 `[0]`
- `stage4` 里 `for _b in (_d.get('base_class') or [])` 对 **`str` 会逐字符迭代**

⇒ **补全时写成 str/list 混用会静默产生垃圾边**。**统一写 `list`**。

### 0x44A7F9 双写入已判（复核 #2）
`mov [ecx],0x56AFB0; lea edx,[ecx+0x44]; mov [edx],0x56AFA4; jmp 0x445B40`（UIWnd dtor）
⇒ **`+0x44`(=68) 的是成员对象，不是第二基**（成员对象自己有基类表链 `0x56A9C0→0x56AFA4`）

### ⚠️ `UIWnd.vtables` 分组存疑
`0x443190`（装 `0x56AE2C`）`call 0x442e10`（装 `0x56AE10`）；`0x44A7F0`（装 `0x56AFB0`）`jmp 0x445B40`（UIWnd dtor）
⇒ **`0x56AE2C`/`0x56AFB0` 更像派生类的表被误并进 UIWnd**（KB 说的 vtable 分割问题）⇒ **待逐表裁决**（不影响主结论）

---

## 5. 复用现成工具（不新建绿野工具）

| 需求 | 现成工具 |
|---|---|
| thunk 检查 | `tools/coff_vtable.py` |
| vptr 安装顺序 + 槽 + 祖先矛盾 | `tools/audit_attribution_evidence.py` |
| 表↔类归属（stride）| `tools/vtable_class_reconcile.py --stride` |
| MI 基偏移 | `tools/mi_base_offsets.py` |
| 布局（编译器裁判）| `tools/audit_type_layout.py` |

⇒ **编排 ≈ 1 天**，不新建工具。

---

## 6. 验收

| 判据 | 命令 | 门槛 |
|---|---|---|
| 成员零丢失 | 生成头成员数对比 | `SceneObj.h` 44→46 |
| 尺寸格门 | 自建 20 行脚本 | 派生 ≥ 每基 + `base_size==首基` |
| 布局 | `tools/audit_type_layout.py` | 通过 |
| S2 | `loop` 当场读 | **≥99**（不降）|
| L1 | `loop` 当场读 | **≥94**（不降）|
| MISATTRIBUTED | `grep -r` | 单调不升（目标 0）|
| C2385 | `probe_census` | **消除**（当前 34）|

---

## 7. 回退（**非干净回退**，复核 #2 实测）

| 状态 | 可回退？ | 说明 |
|---|---|---|
| `data/annotations/structs/*.json` | ✅ git | **但非无损**（见下）|
| **IDB（命名+布局）** | ⚠️ 需重跑 `apply` | **`apply_annotations` 只增不删**（`gotcha_apply_single_pass_leaves_globals_untyped`）⇒ **回退后要手工清残留基类子对象**，否则 IDB 留**幽灵 base** |
| `asm/`（decomp + `ida_structs.json`）| ❌ gitignore | 必须重跑 `export`（~161s）；`export_full` 不读注解 ⇒ 残留只在 IDB 侧 |
| `pal3/src` | ✅ 重新 `codegen` | 但 **L1 棘轮回写基线**（CLAUDE.md 明示）⇒ **退化不可事后从基线文件查出，必须当场读** |
| `probe_census`/`baselines/latest.json` | ⚠️ 三方互不相干 | `compile_regression` 读**缓存** census（没跑 probe 就无意义）⇒ 回退后必须重跑 probe |

**⇒ 最小可回退单元 =「注解 + apply + export + codegen + 当场读 L1」，实测 ~6 分钟。**
**⇒ 每批 ≤3 类**，且**每批前先固化 `pal3/src` 的成员清单快照**（否则丢成员发现不了）。

---

## 8. 禁止

- ❌ **不可按 KB 链写入**（方向和根都错，见 §0.1）
- ❌ **不可批量写入**（每类独立裁决 + 验证）
- ❌ **不可设覆盖率棘轮**（违反 `decision_goal_metric_over_proxy_metric.md`）
- ❌ **不可新建裁决工具**（复用现成，见 §5）
- ⚠️ **`tools/misattribution_ledger.py` 会写 `data/status`**（历史事故：`--help` 覆盖受跟踪产物）⇒ 用前复制到 `/tmp` 跑

---

## 9. 与原 E2 的差异

| 项 | 原 E2 | **E2′** |
|---|---|---|
| 性质 | 补全 | **纠错** |
| 范围 | 719 空 `base_class` | **25 多基类 + 5-10 UI 家族** |
| 目标 | 消化 ~500 MISATTRIBUTED | **消除成员丢失 + C2385 ambiguity** |
| 风险闸 | this 调整验证 | **成员零丢失 + 尺寸格门 + 编译器裁判** |
| 收益估计 | ~500 | **~0**（MISATTRIBUTED 仅 9 处，0 处可被链消化）|
| 前提 | KB 链正确 | **KB 链方向和根都错**（objdump 实证）|
| 启动顺序 | 写入先行 | **Step 0 裁决冲突，写入暂停** |