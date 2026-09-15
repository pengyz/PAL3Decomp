# 归属/misattribution 现存产物清单（t3/t6 简报路径纠错，2026-09-15）

**用途**：t1/t3/t6 简报中引用的 `data/annotations/_generated/`、`attribution*.json`（该目录下）、
`docs/knowledge/pattern_misattrib_evidence_unreliable.md` **在当前树中均不存在**
（属同步前的本地线，已随 `git reset --hard origin/master` 消失）。
本文件给出**实证到的现存产物**作为替代引用源，t3/t6 一律以本表为准。

> 证据等级与门槛见 `docs/specs/2026-09-15-cleanup-scan-taxonomy.md`。
> 本清单只做「路径存在性 + 可采信度」勘定，不做条目裁决（裁决在 t5）。

---

## 1. 现存产物总表

| # | 路径 | 存在 | 版本控制 | 生产时间 | 可采信度 |
|---|------|------|----------|----------|----------|
| 1 | `data/status/misattribution_ledger.json` | ✅ 79145 B | **tracked** | 2026-09-15 09:42 | ✅ 可作当前态基线 |
| 2 | `pipeline/ida/_logs/attribution_demoted.json` | ✅ 36881 B | ❌ **git-ignored（untracked）** | 2026-09-04 18:03 | ⚠️ **历史快照，已失配** |
| 3 | `data/status/signature_conflicts.json` | ✅ 759 B | **tracked** | 2026-09-01 11:03 | ️ **历史快照，引用的 decomp 已重生成** |
| 4 | `pipeline/ida/_logs/attribution_this_mismatch.txt` | ✅ 575 B | ❌ **git-ignored（untracked）** | 2026-09-04 18:03 | ❌ **不得作为归属修改证据**（见 §3.3） |
| 5 | `data/annotations/structs/*.json` 的 `methods[addr]._misattrib_evidence` | ✅ 74 文件 / **222** method 条 | tracked | 随时间累积 | ⚠️ 历史记录，非证据（见 §3.2） |

取证命令：
```bash
for f in data/status/misattribution_ledger.json pipeline/ida/_logs/attribution_demoted.json \
         data/status/signature_conflicts.json pipeline/ida/_logs/attribution_this_mismatch.txt; do
  printf "%-52s " "$f"; if [ -f "$f" ]; then
    echo "EXISTS ($(wc -c <"$f") B) $(git ls-files --error-unmatch "$f" >/dev/null 2>&1 && echo TRACKED || echo untracked)"
  else echo MISSING; fi
done
```

---

## 2. 逐份说明

### 2.1 `data/status/misattribution_ledger.json` —— 当前态基线（唯一可当基线者）

```json
{"generated_by": ".../tools/misattribution_ledger.py", "ledger": [ {"callee": "...", "sites": N,
 "callers": {...}, "files": [...], "addrs": [...], "vtable_owners": [...], "struct_owners": [...],
 "full_callers": {...}, "bucket": "A|B|C", "rename_to": "..." | null}, ... ]}
```

**实测**：197 条，**全部 `bucket=C`**，**`rename_to` 全为 `null`**。
分桶语义（`tools/misattribution_ledger.py:115-126`）：
- `B` = 存在唯一 vtable owner 且 ≠ callee → `rename_to` 指向该 owner；
- `A` = 唯一 caller 且无 vtable/struct owner 冲突，且 full_callers ⊆ marker_callers → `rename_to` 指向该 caller；
- `C` = 其余（**需考古**）。

**推论（t5 必须吸收）**：ledger 当前**没有任何一条达到「可直接改名」分桶**。
因此 t6 的「可立即修」批次**不能从 ledger 直接取用**——所有 A/B 级候选必须**新取证**。
（该结论 captain 已在 t5 要求 2(a) 中背书。）

> ⚠️ 该文件 mtime 为 09:42（早于 apply 09:48），故它反映的是**上一次 apply 之前**的生成物代码状态；
> 由于生成物未被跟踪（见 `AR-201`），本文件是当前唯一可跟踪的归属分桶记录。

### 2.2 `pipeline/ida/_logs/attribution_demoted.json` —— 历史快照，已失配

- 结构：`{"<addr>": {"by_misattrib": bool, "by_skip": bool, "method": "<Class>_<Method>", "veto_reason": "<string>"}}`
- **实测 193 条**，而 ledger 为 **197 条** → **两者计数不同源**，不可交叉当一致。
  典型 `veto_reason`：`"functions.json:type=skip:misattributed in struct, removed"`
- 生产时间 **2026-09-04**，而 ledger 为 **2026-09-15** → 相差 11 天，中间经历多次 apply 与标注轮次（round3–round6）。
- **`pipeline/ida/_logs/` 被 `.gitignore:98` 排除**，故它是**机器本地产物**：
  一次 `git reset --hard origin/master`（即本轮)`_generated/` 消失的同一事件）不会删除它，
  但换机/重建 work IDB 后**无法再生出同一份**（无 producer 被跟踪）。
- **采信结论**：只能作「2026-09-04 时刻的降级记录」引用，**不得**当作当前态的 demotion 全集。

### 2.3 `data/status/signature_conflicts.json` —— 历史快照，交叉引用已被重生成

- 结构：数组，每元素 `[kind, addr, class, method, A, B, decomp_file]`，`kind ∈ {RET, NARGS}`。实测 **5 条**：
  `RET 0x0042C920 CG_Entry::GetCGEntry`、`NARGS 0x0043DDF0 CCBControlWindow::Render`、
  `NARGS 0x00456FC0 Scene::GetNumObj`、`RET 0x004C5B90 _Texture_uv::operator=`、`RET 0x004D33A0 CEffQuake::ResetFlags`。
- 生产时间 **2026-09-01 11:03**，而 `asm/pal3/decomp/**` 于 **2026-09-15 09:49** 重生成。
- **交叉引用实测（5 条中 4 条仍在、1 条失配）**：
  | 引用的 decomp 文件 | 现状 |
  |---|---|
  | `GetCGEntry_CG_Entry_QAEPAU[thunk]:class_GetCGEntry_public:_class_GetCGEntry_XZ_0042c920.json` | ✅ 存在 |
  | `CCBControlWindow_Rendervoid_0043ddf0.json` | ✅ 存在 |
  | `ReadRegistryString_00456fc0.json` | ✅ 存在（**注意**：文件名与同条目的 `Scene::GetNumObj` 不匹配，命名本身可疑） |
  | `CEffSParticle_sub_4D33A0_004d33a0.json` | ✅ 存在（文件名写 `CEffSParticle`，条目却是 `CEffQuake::ResetFlags`，同样可疑） |
  | `Texture_uv_operator_004c5b90.json` | ❌ **不存在**；该地址现导出为 `...operator_004c5b90.json` → **条目已失配** |
- **另有实时相关性**：`0x0042C920` 正是**当前 apply 仍报的签名失败**（`apply_annotations_log.txt`：
  `[!] 0x0042C920 GetCGEntry → [thunk]:class GetCGEntry \`public: static class GetCGEntry *`），
  故本条**仍然有效**，可作当前问题的入口；其余 4 条须先按 §3.4 复验。

### 2.4 `pipeline/ida/_logs/attribution_this_mismatch.txt` —— 不得作为归属证据

- 格式（10 行）：`0x<addr> owner=<Class>::<method>  sig this=<TYPE>`
- 生产时间 **2026-09-04**，且同属 **git-ignored**（`.gitignore:98`）。
- **为什么不能当证据**：它只记录 **signature 的 `this` 类型**，而 CLAUDE.md 明令
  「**禁止仅凭 signature this 修正归属** —— 必须有 decomp member access evidence
  （函数内 `this->member` 引用的成员在目标类中存在且不在原类中存在）」。
  本文件正好是**被禁止的那一类证据的唯一形态**。
- **采信结论**：可作为**待复核工单列表**（"这 10 处签名 this 与 owner 不符，值得取证"），
  **不可**作为修改依据。10 条 addr 见文件原文；其中 `0x0051B5D0 CCBControlWindow::OnMessage sig this=CCBItemWindow`
  是本团队 `[MISATTRIBUTED]` 形态（`CCBItemWindow on CCBControlWindow::this`）的同类，优先取证。

---

## 3. 引用纪律（t3/t6 必须遵守）

### 3.1 三份产物的时间戳分级
- **当前态**（09-15）：`misattribution_ledger.json`
- **历史快照**（09-01 / 09-04）：`signature_conflicts.json`、`attribution_demoted.json`、`attribution_this_mismatch.txt`

引用历史快照时**必须**写明其生产时间，并说明"该结论基于 MM-DD 状态"。

### 3.2 `_misattrib_evidence` 是历史记录，不是证据（captain 已备书）
- 位置：`data/annotations/structs/*.json` → `methods["0x<addr>"]._misattrib_evidence`（**74 文件 / 222 条**）
- 形态：字符串，如 `"max_offset=383296>class_size=111488"`、`"saleui-slider: accesses +0x1795C(96,604) > PAL3 size; SaleUI ctor inits same layout"`
- **量化锚点（替代不存在的 `pattern_misattrib_evidence_unreliable.md`）**：
  222 条中 **182 条**可解析出 `class_size`，其中 **141 条 ≠ 当前 `binary_size`（77.5%）**。
- **纪律**：`class_size != binary_size` 的条目**一律降级重取证**（需 live TIL/IDB 复核）；
  数值相等的仅作**方向性**参考，仍不得据以动偏移。
  `class_size` 语义未定（存在与 `binary_size` 相等的情形，如 `CUtil` 一处 48 vs 1772），
  **不得**仅凭"数值不等"判定证据失效。

### 3.3 消费方现状（captain 要求 3 定性）
- **`_misattrib_evidence` 目前无任何 pipeline 脚本消费**，仅 4 个一次性脚本写入：
  `tools/_migrate_playermgr.py`、`tools/_migrate_saleui_slider.py`、`tools/_migrate_round3.py`、
  `tools/_migrate_rolestatepanel.py`。
  取证：`grep -rln "_misattrib_evidence" --include=*.py .`
- **定性（供 t5）**：它是**写入-only 的僵尸字段**（当前），**但**其中 `max_offset=` 字段
  是**唯一现成的指令级下界来源**，而本轮 `AR-009/AR-010` 的"撑大检测"正需要这样的消费方。
  故建议 t5 定性为 **「待接入证据（潜在消费方明确）」** 而非纯僵尸：
  僵尸部分 = 其余自由文本叙事（无消费、无 schema）；可接入部分 = 结构化 `max_offset=` / `class_size=` 数值。
  **但**：`max_offset` 是**下界**，只能用于"发现撑大"，**不能**用于确定 `binary_size` 精确值（见 `AR-009`）。

### 3.4 引用历史快照前的最小复验
对 §3.1 的历史快照条目，引用前至少做一步独立复验，否则一律判 `evidence_grade=E + NEED_EVIDENCE`：
1. `signature_conflicts.json` 条目 → 确认其 `decomp_file` 字段指向的文件**当前存在**（本条已实测 4/5）。
2. `attribution_this_mismatch.txt` 条目 → 按 CLAUDE.md 补 **decomp member access** 证据（signature this 不够）。
3. `attribution_demoted.json` 条目 → 与 `misattribution_ledger.json` 交叉核对（注意 193 vs 197 计数不同源）。

### 3.5 `[IDA_MISID]` 的语义处理（captain 要求 3 第二项）
`[IDA_MISID]` 84 处由 `pipeline/gen/stages/stage3_cleanup.py:752-759` **整体注释掉**，模式表为
`Concurrency`、`details::VirtualProcessor`、`NtTib`、`ExceptionList`、`std::_Xlen`、`std::_Xran`。
**t5 必须区分两类**（不得统一判"有意保留"）：
- **(i) 事实正确但丢了语义**：被注释的行确实是 FLIRT/TIL 误识别（如 `NtTib`/`ExceptionList` 属 CRT 内部），
  注释掉是正确的——但**注释同时抹掉了 IDA 误名的"真实目标"信息**，使后继读者无法知道原行意图。
  → 建议动作 `DOCUMENT`（在注释中补真实目标）或 `KEEP_AS_SIGNAL`。
- **(ii) 应重命名保留**：被注释的行含**真实游戏语义**（FLIRT 把真实函数误判成某个库符号名），
  此时注释掉等于**丢弃真实调用**。→ 建议动作 `FIX_ATTRIBUTION` / `DOCUMENT`，**不得**静默注释。
判定依据：逐行核对被注释行引用的符号是否为 PAL3 真实使用的库/CRT 符号（对 (i)）或
是否为 `.text` 内真实函数（对 (ii)）。

---

## 4. 本清单与 t4 扫描产物的关系

| 本清单条目 | 对应 t4 JSON |
|---|---|
| `attribution_demoted.json` / `attribution_this_mismatch.txt` 属 git-ignored 机器本地产物 | `AR-201`（验收产物未入库）、`AR-205`（过期路径引用） |
| `signature_conflicts.json` 的 1/5 条目失配 | `AR-205` |
| `_misattrib_evidence` 无消费方 | `AR-009`（撑大检测缺消费方）、`GAP-AR-06` |
| `binary_size` 无真实尺寸来源 | `AR-009`、`AR-010`；裁决书 `docs/specs/2026-09-15-cleanup-scan-architecture-rulings.md` |

**未确认缺口（计数维度映射）**：`misattribution_ledger.json` 的 **197 条**与生成物中 `[MISATTRIBUTED]`
**344 站点**不是同一计数维度——ledger 每条是按 `(callee_class, callee_method)` 的**聚合**，
`sites` 字段记录该聚合的站点数。两者差额来源**未经核实**，可能包含：
(a) marker 文本与 ledger 解析正则的差异（ledger 需从 `/* ... */` 注释中提取类名与方法名）；
(b) `--min-sites` 过滤——注意其**默认值为 1**（`tools/misattribution_ledger.py:36`，
`:103` 为 `if c['sites'] < min_sites: continue`），**默认不过滤任何条目**，故此项**不**构成差额来源；
(c) `[ROWTABLE]` 与 `[MISATTRIBUTED]` 同源分支（`ast_transform.py:421` vs `:353/:436`）是否被混计。

**该映射关系由 t3 建立**，本清单不作断言。