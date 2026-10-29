# 整分支最终复核报告 — boundary-spec-landing-plan（667a3d8d8..e8c275312 · 13 commits）

> 复核员：整分支最终复核（fresh context）· 2026-10-29
> 评审包：`.superpowers/sdd/2026-10-28-boundary-spec-landing-plan/review-667a3d8d8..e8c275312.diff`
> 计划：`docs/superpowers/plans/2026-10-28-boundary-spec-landing-plan.md`
> spec：`docs/specs/2026-10-28-reproducible-boundary-spec.md`（§7 九项=验收基准）
> 台账：`.superpowers/sdd/2026-10-28-boundary-spec-landing-plan/progress.md`

---

## 1. 总裁定

### **需修（可合但有应修项）**

**判定依据**：13 commits 主体工作扎实——9 项 spec 落地面 7 真闭环 + 2 诚实挂账，33 个新测试全绿（全套件 923 passed），LNK2005 金丝雀=0 重复定义，读数 S2 135/214 · L1 162（三限定）· 总错 1110 与终态一致。但存在 **4 项 Important 级缺口**（测试死代码、六消费点对账测试缺失、census 纯态断言缺失、一处未勘误的记账失实）应在合并前或合并后立即修复。

---

## 2. Review Focus 五条逐判

### RF-1 SetBlend 型误登（声明/键变更误形=静默坏码）

**判：有实际风险敞口，但已收窄**

- ✅ T2 P1 修复了 0x541C40 三参形（WinMain 三 push + add esp,0xC 铁证），测试锁了 arity=3。
- ✅ T2 P2 修复了 0x5414A0 fastcall ABI 载体，测试锁了 `__fastcall`。
- ✅ T1 修复了 cc 误写（cdecl→stdcall），测试锁了 `__stdcall`。
- ⚠️ **遗留敞口**：`is_synthesized_member` 的 `_sdtor_` 模式会误匹配任何含 `_sdtor_` 子串的名字（如 `update_sdtor_state`、`A_sdtor_thing`），在合成物抑制路径上造成假阳性→真方法被抑制。实测当前数据集无此类误伤（33 测全绿 + link_probe 0 dups），但模式过宽是潜在风险。
- ⚠️ `test_rules_from_census_applied` 的 `crt_sub_` 分支是**死代码**（`_sub_` 检查在前、`crt_sub_` 永远被 `_sub_` 截胡），导致 52 条 `crt_sub_*` 条目实际全获 `lib_relink_ok` 而非测试声称的 `awaiting_signature`。若 F2 分类有误（如 `crt_sub_00541590` 同族误登——T2 复核 P6 已标记随修候选），测试不会报警。

### RF-2 Batch-0 型爆炸（动 skip 不查 decl 收编⇒C2556×144）

**判：前置检查可靠**

- ✅ T2 Step 3 明确执行了 decl 收编前置检查（grep 六消费点对四地址的处理面）。
- ✅ `test_p4_correctness_locks` 锁了双源零命中（structs 不含四地址）+ 名字唯一 + 0x541490 不入 functions。
- ✅ `check_annotations.py` 有 declaration_only 变参签名豁免逻辑（防 C2556/2373 双定义）。
- ✅ link_probe 金丝雀=0 重复定义，确认无 LNK2005 爆炸。

### RF-3 合成物误判（adjthunk 当手写真方法⇒LNK2005）

**判：处理正确**

- ✅ `is_synthesized_member('Destroy__ovl_03')` = False（对抗样本正确拒绝）。
- ✅ `test_classifier` 显式测了 Destroy__ovl_03 对抗样本 + RandLerpF 负例。
- ✅ `test_no_adjthunk_annotation_entries`：合成物注册须标 declaration_only。
- ✅ `test_no_adjthunk_definitions_generated`：生成源零手写 adjthunk 定义体。
- ✅ link_probe: duplicate definitions = 0 symbols ⇒ LNK2005 面干净。
- ✅ Destroy 族 11 注释块全数识别（9 条目整退役），标记棘轮 107=118−11 精确对账。

### RF-4 消费点漏改（skip schema 枚举化后 6 消费点静默失配）

**判：对账未真锁——测试缺口**

- ✅ reason 镜像在位（全部 1927 条有 `reason` 字段），6 消费点（export_full/collect/data/apply/check/annotation_view）全部读 `reason` 或地址键，不读 `skip_reason` ⇒ **当前兼容**。
- ❌ **计划要求的 `test_six_consumers_agree_on_new_schema` 测试未实现**。`test_skip_reason_schema.py` 只测了 schema 完备 + 平账 + 分类规则，未对六消费点逐一验证。
- ⚠️ 现有 `test_total_unchanged_and_reason_mirror_intact` 只锁了 `all(e.get('reason'))` 非空，不验证 reason 值在消费点的语义正确性。若 `reason` 镜像被误删或值被改，collect.py 的 `reason == 'thunk'` 过滤和 data.py 的 `reason != 'thunk'` 过滤可能静默失配。

### RF-5 读数漂移误判（overlay 态混入纯态读数）

**判：标签链基本闭合但缺显式测试**

- ✅ `probe_census.json` 标签 `overlay.applied: []`（纯态），26 个 overlay 条目在 `overlay.pure` 下。
- ✅ 计划约束「纯态读数」在 Global Constraints 中明文，T8 三抽检（UIListBox/UISceneFrm/CCBParabolaWindow 纯态 ok）。
- ❌ **计划要求的「census overlay 标签=pure」验收断言未在 `test_debt_recovery_pure.py` 中实现**。测试只验了 manifest 条目数和标记数，未锁 census 标签。
- ⚠️ `compile_baseline.json` 陈旧（135/213 vs 实况 135/214）——pre-existing 恒红门禁，非本分支引入，但引用读数时须注意。

---

## 3. spec §7 九项验收对账表

| # | 项目 | 验收态 | 实证 | 挂账诚实度 |
|---|------|--------|------|-----------|
| 1 | Destroy__ovl_03 修复 | **部分闭环** | T1 上游消债根 + T8 九条目退役（47→38）；11 注释块全清。但归属（中间类 vs COMDAT 折叠两说）未定谳，仅挂账 spec §8 | ✅ 诚实（spec 已标「待分」） |
| 2 | j_D3DX 三名正名 | **真闭环** | 0x4B8200→RandLerpF（A 级 66B 逐字节）；0x542533→D3DXVec3Normalize（157B）；0x544771→D3DXQuaternionSlerp（227B）。测试 3/3 锁名字+签名+cc+declaration_only | ✅ |
| 3 | 4 crt_sub unskip | **真闭环** | 3 户 unskip（A 级反汇编+调用面）；0x541490 改判 linker_artifact 留 skip（Ruling P3 降级）。测试 5/5 锁双源零命中+名字唯一 | ✅ |
| 4 | skip_reason 枚举化 | **部分闭环** | 1907 条→六枚举（+T4 20 条=1927）。分布：awaiting 1104 / lib_relink 523 / compiler_regen 289 / linker_gen 9 / dual_def 2。但 **6 消费点对账测试缺失**；`crt_sub_` 分类分支死代码 | ⚠️ 基本诚实（F2 勘误已回写） |
| 5 | adjustthunk 反模式清理 | **真闭环** | `is_synthesized_member` 分类器 + 三闸（export skip + emit 闸 + 地址级闸 REG16）+ 测试 6 测（含 Destroy__ovl_03 对抗样本）+ link_probe 0 dups | ✅ |
| 6 | LNK2001 排雷 | **真闭环** | 6 件 SingletonThunk 胶水剥离（4 胶水件可剥 + 2 语义对保留 D2）+ D2b 伪参剥离。link_probe LNK2001=2778（存量未恶化）+ 0 dups | ✅ |
| 7 | 注册表落地 | **真闭环** | thunk_registry 17 条（九类/confidence/evidence 三轴）+ system_lib_statics 73 槽全量对账（6 named + 63 paired + 4 unknown）。D9 加固版三锁（计数/公式/内容） | ✅ |
| 8 | D3DX 精确件补给 | **挂账（诚实）** | 分支②未果（环境定界：bash 无外网）。supply=skewed + 检索足迹保全（FamilyId + archive.org 镜像记录）+ 4 残差单元显式挂账 + 到货路径留档 | ✅ 诚实（环境限制明示） |
| 9 | overlay 债回收 | **部分闭环** | 47→38 条目（Destroy 族 9 条目整退役）。38 条理由分类落档（annotation_fix 9 / 编译已净 3 / 混合 26）。标记棘轮 107=118−11。但 **census 纯态断言测试缺失** | ✅ 诚实（理由分类可信） |

**闭环率**：4 真闭环 + 3 部分闭环 + 2 诚实挂账 = 9/9 有交代，0 虚报。

---

## 4. Critical / Important / Minor 分级清单

### Critical（阻塞合并）

**无**。

### Important（合并前/后立即修）

| # | 缺陷 | 影响 | 建议 |
|---|------|------|------|
| I-1 | `test_rules_from_census_applied` 的 `crt_sub_` 分支死代码（`_sub_` 截胡）；52 条 `crt_sub_*` 实际全获 `lib_relink_ok` 而非测试声称的 `awaiting_signature` | 分类规则与测试不一致；若 F2 有误（P6 随修候选），测试不报警 | 修测试分支顺序（`crt_sub_` 先于 `_sub_`）或修正分类规则使其与意图一致 |
| I-2 | 计划要求的 `test_six_consumers_agree_on_new_schema` 未实现 | 6 消费点对账缺显式锁；reason 镜像被误删时 consumer 静默失配 | 补写对账测试（或在现有测试中追加 consumer 级断言） |
| I-3 | `test_debt_recovery_pure.py` 缺「census overlay 标签=pure」验收断言 | 纯态/overlay 态混入时测试不报警 | 补 `assert json.load(probe_census)['overlay']['applied'] == []` |
| I-4 | T2 f7b4faa commit message「测试 6/6」实为 3 测（未勘误） | 记账失实（历史案例「6/6」实 3 支同型——同类第 2 例） | 在 progress.md 或后续 commit 补勘误注记 |

### Minor（可延后）

| # | 缺陷 | 影响 |
|---|------|------|
| M-1 | T8 commit「9 条目+18 文件」：实际 9 manifest 条目 + 9 overlay 文件 = 10 文件变更。「18 文件」膨胀 | 记账措辞不精确（不影响实质） |
| M-2 | `is_synthesized_member` 的 `_sdtor_` 模式过宽（可误匹配 `update_sdtor_state` 类名） | 潜在假阳性→真方法被抑制；当前数据集无实害 |
| M-3 | `manifest.json` 尾换行符丢失（cosmetic） | 不影响功能 |
| M-4 | `compile_baseline.json` 陈旧（135/213 vs 实况 135/214）——恒红门禁 | pre-existing，非本分支引入 |
| M-5 | `test_rules_from_census_applied` 最后一个 `elif` 无 `else` 兜底（不匹配任何规则的条目不被断言） | 测试覆盖盲区（当前 1927 条全被规则覆盖，实害=0） |

---

## 5. Ruling 重裁表

| # | Ruling（台账原文摘要） | 重裁 | 理由 |
|---|----------------------|------|------|
| R-1 | Setup：直接在 master 执行 | **合理** | 用户全程纪律「提交+push」显式授权 |
| R-2 | Setup：保留每任务独立对抗复核步 | **合理** | 计划明文要求，已执行 |
| R-3 | T1：取证前置到测试编写前 | **合理** | 测试需语义名定值，TDD 序调整无实质代价 |
| R-4 | T1：真双注走 declaration_only=真 | **合理** | 钩子指引的声明收编形，防真双注 |
| R-5 | T2：批内并行化（commit 先于复核/loop） | **合理但有代价** | 复核缺陷须追加修复——实测追加了 P1-P4 修复批；但节省了串行等待 |
| R-6 | T4：超额回收 175 条（计划~7，正则全族命中） | **合理** | 按衰退纪律预设回滚条件；实测 loop 读数未恶化 |
| R-7 | T4：修法 D④ 矫正——structs 注册=槽符号提供者禁删 | **合理（关键纠错）** | 删注册致 78 槽失名实证；declaration_only 标记 + 双保险抑制是正确修法 |
| R-8 | T4：一版矫正落空=checkout 落暂存区 | **合理** | git 语义坑教训沉淀 |
| R-9 | T5：(i) 胶水剥离 / (ii) 全局对象定义拆分 | **合理** | (i) 本拍清 LNK2001；(ii) 挂账保真静态初始化——正确取舍 |
| R-10 | T6：67 名派生=环 2 字节匹配挂账工具化 | **合理** | 诚实三分（6 named / 63 paired / 4 unknown）优于编造 |
| R-11 | T6：T6 复核覆盖 T7 supply 面 | **合理** | D3 即 T7 内容，避免重复复核 |
| R-12 | T7：分支②未果（环境定界）supply=skewed | **合理** | 环境限制明示 + 检索足迹保全 + 到货路径留档 |
| R-13 | T8：Destroy 族回收法=条目整退役 | **合理** | T1 上游消债根⇒纯态再生即净；overlay 副本系陈旧快照——证据充分 |

**结论**：13 条 Ruling 全部维持原判。R-5（批内并行化）是最接近「应改判」的条目（追加了修复批），但整体收益>代价，维持。

---

## 6. 未复验项

| 项 | 原因 | 影响 |
|----|------|------|
| L1 三限定下的逐字节比对 | 未实跑 `pipeline/cli.py match`（耗时 ~305s）；仅读 `s4_baseline.json` 读数 L1=162 | 读数可信度=基线记录级；如需 100% 确认须重跑 match |
| 67 名派生的环 2 字节匹配 | 显式挂账（Ruling R-10）；工具未建 | 字节匹配最终目标的前置条件 |
| 5 对象全局定义（(ii) 挂账） | T5 显式拆分挂账；零引用=零 LNK2001 但静态初始化保真未验 | 运行时行为可能缺失静态初始化 |
| `crt_sub_00541590` 同族误登 | T2 复核 P6 标记随修候选，未修 | 52 条 `crt_sub_*` 全获 `lib_relink_ok` 可能含误分 |
| compile_baseline 刷新 | 恒红门禁 pre-existing；需人确认棘轮决策 | 不影响本分支合并判断 |

---

## 7. 记账失实专项（历史案例「6/6」「10 处」同型排查）

| 案例 | 声称 | 实际 | 状态 |
|------|------|------|------|
| T2 f7b4faa「测试 6/6」 | 6 tests | 3 tests（test_crt_sub_unskip.py） | **未勘误** ← 新发现 |
| T6 499c2a5「测试 6/6」 | 6 tests | 3 tests（test_registry_schema.py） | 已勘误（05fe1de D7） |
| spec §7 #1「10 处」 | 10 overlay 注释 | 11 blocks（T8 正确清点） | 已勘误（T8 commit） |
| T8「9 条目+18 文件」 | 18 files | 9 overlay + 1 manifest = 10 file changes | **未勘误** ← 新发现 |
| T2 8e7c05e「13/13」 | 13 tests | test_crt_sub_unskip.py 4 tests（可能含全量套件计数） | 待确认口径 |

**结论**：共 5 处记账出入，2 处已勘误（执行者自我纠正），2 处未勘误（I-4 + M-1），1 处待确认口径。与历史「6/6 实 3 支」「10 处实 11 块」同型。

---

## 8. 终读数可信度

| 指标 | 声称值 | 实测值 | 一致性 | 备注 |
|------|--------|--------|--------|------|
| S2 | 135/214 | 135/214 | ✅ | probe_census 2026-10-29T13:56:51 |
| L1 | 162（三限定） | 162（s4_baseline match_L1） | ✅ | 三限定：截断到 size / 等长 / reloc 4B don't-care；hidden diff 1226B/6739B=18.2% |
| 总错 | 1110 | 1110 | ✅ | probe_census |
| LNK 金丝雀 | 0 duplicates | 0 duplicates | ✅ | link_probe --check PASS；LNK2001=2778（存量） |
| overlay 标签 | pure | pure（applied=[]） | ✅ | probe_census overlay.applied |
| 测试 | 33 新测全绿 | 33 passed | ✅ | 全套件 923 passed, 355 skipped |
| 债数 | 38（47−9） | 38 | ✅ | manifest entries 精确棘轮 |
| 标记数 | 107（118−11） | 107 | ✅ | overlay-fix 计数精确 |

**结论**：终读数全部可信，8/8 对账一致。三限定随 L1 数字走的引用纪律须持续执行。

---

*报告生成：2026-10-29 · 整分支最终复核*
