> ⚠️ **更正（2026-09-25，最后收口轮）**：本报告多处（`:4/:350/:399/:491/:583`）曾称
> "本报告在 `.superpowers/sdd/` 下、该目录被 `.gitignore` 忽略 ⇒ 不入库"。**该说法已过时**：
> 设计与计划、SDD 台账、task-1..8-brief/report **均已入库**（`948fc786d`、`212f53b02`、`4269a5570`）。
> 机制说明：文件早已被跟踪，而 `git add <该路径>` 会暂存改动却因 `.superpowers/sdd/.gitignore` 的 `*`
> 打印 advice 并 **exit 1** ⇒ `git add … && git commit …` 链式静默跳过提交。请以 `git ls-files` 为准。

# Task 8 报告：端到端验证（L1 + `.rdata` 双裁判）

- **状态**：DONE_WITH_CONCERNS
- **提交**：`2eb555f09`（3 files, +3204：`tests/test_vtable_e2e.py` · `data/status/vtable_e2e_report.json` · `data/status/vtable_ratchet_baseline.json`；本报告文件在 `.superpowers/sdd/` 下、该目录被 `.gitignore` 忽略 ⇒ 不入库，与 task-1..7-report.md 同例）
- **一行测试摘要**：新增 `tests/test_vtable_e2e.py` **离线 19 passed / 0 failed / 8 skipped；真机 `PAL3_E2E_LIVE=1` 27 passed / 0 failed / 0 skipped**；前序 8 套全无回退（35 / 38 / 68 / 73 / 88 / 61(+3 skip) / 35 / 19）
- **交付物**：`tests/test_vtable_e2e.py`（harness + 测试）· `data/status/vtable_e2e_report.json`（机读双裁判报告）· `data/status/vtable_ratchet_baseline.json`（当日 Task 5 棘轮基线）

---

## 1. 双裁判与 3 个断裂单元（核心交付）

L1 裁判口径 = **生产 `match` 口径**（`production_l1_flags()` = `data/status/s4_baseline.json.flags`
= `pipeline/cli.py:690` 传给 `compare_pal3.py --flags` 的同一串：`/nologo /TP /c /W3 /O2 /Ob2 /Oi
/Ot /Oy /GF /Gy /GX /GR /MD /Gd`，**含 `/O2` 与 `/GR`**）。
⚠️ **R=3 更正（全分支最终评审 ★Critical）**：本行原文写的是"生产口径 `pipeline/compare_pal3.py:PROBE_FLAGS`
（`/nologo /TP /c /W3`，不含 `/O2`、不含 `/GR`）"—— **失实**。`PROBE_FLAGS` 只是 `compare_pal3` 的
**probe 默认口径**，生产 `match` 唯一调用点 `pipeline/cli.py:690` 传的是上面那串（`s4_baseline.json.flags`
逐字相同）；`HYPOTHESIS_FLAGS` 才含 `/O2`/`/GR` 的探针假设集。原文把 probe 默认值当成生产口径，
连带使 §2 建议①的"移除后 L1 口径不变"与台账 `:322` 的"`.text` 不受直接影响"**双双为假**（见 §2）。
`.rdata` 裁判 = `tools/vtable_verify.py`（`force_emit` 强制发射 + 逐槽归一对比，探针 flags `/Od`，**不带 `/GR`**，理由见 §2）——该侧**不受本更正影响**（评审已复证其证据为真）。

| 单元 | 类 | L1 判词（**生产口径**） | L1 判词（probe 默认口径，仅对照） | `.rdata` 判词 | 分歧分类 |
|---|---|---|---|---|---|
| `pal3/src/Combat/CCBStageShadow.cpp` | `CCBStageShadow` | `l1_partial`：**L1=2 / partial=6**（matched 9/10，unmatched 1，unresolved_synth 1，rate 0.25） | L1=0 / partial=8（rate 0.0） | `rdata_not_applicable` | `l1_broken_rdata_na` |
| `pal3/src/Misc/PalScriptWaitObj.cpp` | `PalScriptWaitObj` | `l1_partial`：**L1=0 / partial=1**（matched 1/1，unmatched 0，rate 0.0） | L1=0 / partial=1（rate 0.0） | `rdata_missing_vtable` | `both_broken` |
| `pal3/src/Misc/UI3DCtrl.cpp` | `UI3DCtrl` | `l1_partial`：**L1=2 / partial=10**（matched 14/16，unmatched 2，unresolved_synth 2，rate ≈0.167） | L1=0 / partial=12（rate 0.0） | `rdata_deviations`：**obj 26 槽 vs bin 8 槽**，9 处偏差 | `both_broken` |

> **口径后果（R=3 实测，同一 harness 双口径并列跑）**：CCBStageShadow `2/6` vs `0/8`、
> UI3DCtrl `2/10` vs `0/12`、PalScriptWaitObj `0/1` vs `0/1`。⇒ 原报告"L1 近乎结构性必为 0
> ⇒ 该维度不具判别力"是**口径错误的产物**：生产口径下前两个单元**各有 2 条函数体逐字节全同**，
> 该维度**有判別力**，只是此前没跑在生产口径上。分歧分类与 `summary` 不变（判词状态未变）。

分歧统计（`vtable_e2e_report.json.summary`）：`both_broken 2 · l1_broken_rdata_na 1 ·` 其余 0。

### 1.1 逐单元归因（每一条都有可复现证据）

**① `CCBStageShadow` —— `.rdata` 维度**不适用**（两侧都非多态），唯一有判词的是 L1**

- 发射头 `pal3/src/Combat/CCBStageShadow.h` **0 条 `virtual`**（`header_facts` 实测）。
- 二进制侧：ctor `0x511EE0` 的**字节级扫描**（`c7 <modrm> <imm32>` 且 imm32 ∈ 189 个 ctor 实写表起始）
  **零命中** ⇒ 二进制不写 vptr；PDB（PAL3A，仅参考）成员自 +0 起、size 1556，无 vfptr 空隙。
- ⇒ 两条独立来源一致：**该类在二进制里就是非多态**。它的"断裂"全在函数体（生产口径下 6 个 partial
  + **2 条已逐字节全同**，逐函数匹配率 6.8% / 30.5% / 12.9% …）⇒ 这正是 L1 裁判负责的面，
  `.rdata` 裁判对它**天然无话可说**。

**② `PalScriptWaitObj` —— `.rdata` **结构性缺失**（二进制要多态、源侧不建模 vptr）**

- 发射头 `Misc/PalScriptWaitObj.h` **0 条 `virtual`**，只声明 1 个非虚 `ReleaseObject`。
- 二进制侧要求 vfptr 的证据（三条独立）：
  1. PDB：`PalScriptWaitObj` size **8**，唯一数据成员 `m_needscriptdel@4`；其派生类 `RoleCameraCtrl`
     size 76 且成员自 **+8** 起 ⇒ `[0,8)` 是 `vfptr(4) + 1 DWORD`；
  2. Task 4 的**编译器裁判**：`sizeof(&RoleCameraCtrl::f) == 8`（PMF 8 ⇒ 最基层载体 `PalScriptWaitObj`
     自身是 vfptr 载体且有直接基）；
  3. 注解 `PalScriptWaitObj.json` 把 +0x0 记成数据成员 `m_nTodo_000`（**vptr 被误建模成数据成员**，
     违反"vptr 由编译器生成"约束）。
- ⇒ 判词 `rdata_missing_vtable`：L1 看不见（它只看函数体）、`.rdata` 裁判看得见（表根本发射不出来）。

**③ `UI3DCtrl` —— 两侧同时破，且 `.rdata` 给出精确槽面**

- 表地址证据（两条独立来源互证）：注解 `vtables[0].addr = 0x0056ACFC`；**字节级** ctor 扫描在
  `0x43D83A` 命中 `c7 06 fc ac 56 00`（`movl $0x56ACFC,(%esi)`）⇒ 注解地址**是真实表地址**（不是错挂）。
- 编译产物侧：`??_7UI3DCtrl@@6B@` **26 槽**。逐槽名证明成因（**R=1 已由断言保护**，见 §8.6）：
  `[0]UI3DCtrl::~UI3DCtrl`（与基类同名 ⇒ **在位覆写**基类槽 0）`[1..20]` 基类块同下标对齐
  （其中 `[2]/[15]/[16]` 为本类 `slot_2`/`slot_3`/`slot_4`——与基类**同名** ⇒ 在位覆写）
  `[12]UIWnd::ShowWindow` `[20]UIWnd::RenderText`
  `[21]UI3DCtrl::slot_0` `[22]Render` `[23]_scalar_dtor` `[24]slot_6` `[25]CreateWithTexture`
  ⇒ 发射器把 **UIWnd 的 21 个 virtual 整体抄进派生头**（基类块同下标对齐），而派生类自家
  `slot_0`（= `ShowWindow`@`0x445E70`）因**占位名不同**没有被识别为覆写 ⇒ 被**追加**到槽 21，
  基类槽 12 的 `UIWnd::ShowWindow` **原样保留** ⇒ 与二进制（槽 0 = `ShowWindow`）整体错位。
  （R=0 报告"从槽 1 起整体错位"表述过粗：基类块 20 槽中有 3 处是**同名在位覆写**，非整体位移。）
- 二进制侧真实表 `0x56ACFC` = **8 槽**（`[0]UIWnd::ShowWindow [1]UI3DCtrl::Render [2]SceneObj::Update
  [3]UIPushButton::Destroy [4]CCBItemWindow::Create [5]UI3DCtrl::_scalar_dtor [6]CGameData::OnMessage
  [7]UI3DCtrl::CreateWithTexture`）。
- ⇒ 偏差 1 条 `slot_count`（26 ≠ 8）+ 8 条 `slot_key`（`identity=mixed`）。
- 该单元的 L1=2 / partial=10（生产口径，共 12 条已比对；2 条逐字节全同）也说明函数体侧
  仍以不匹配为主 ⇒ **`both_broken`**。

---

## 2. 🔴 `/GR` spike：结论与建议（Critical 架构前提）

**探针**：真项目类 `AStarPathFinder`（`Misc/AStarPathFinder.h`，`ctor_declared` 走 `dummy ctor` 强制发射），
同一源两种 flags 编译，再与 `original/PAL3.exe` 的**真实 `.rdata` 表** `0x56A600` 对照。

| 观测 | 无 `/GR`（`/Od`） | 带 `/GR`（`/Od /GR`） | 二进制真实表 `0x56A600` |
|---|---|---|---|
| `??_7AStarPathFinder@@6B@` 符号 value（= address point 在节内偏移） | **0** | **4** | address point 偏移 **0** |
| COL 符号（`??_R4…`，位于 value−4） | `None` | **`??_R4AStarPathFinder@@6B@`** | 无 COL：`base−4 = 0x3F800000`（= 1.0f **float 数据**，不在 `.text`/`.rdata`） |
| `.rdata` COMDAT 长度 | **8**（2 槽） | **12**（COL + 2 槽） | 3 槽（`0x401030` dtor / `0x4014E0` / `0x4014F0`） |
| `.obj` 体积 | 1290 | **2100**（+810 = COL + `.?AV` 类型描述符 + 其它 RTTI 节） | — |
| `compare_tables` 的 COL 判据 | 双侧都无 ⇒ 不报 | obj 有 / bin 无 ⇒ **`address_point_rtti` 偏差** | — |

**结论：`/GR_IS_STRUCTURAL_BLOCKER`（已由纯函数 `gr_spike_analysis` 判定，可在离线夹具上复证）**

1. 带 `/GR` ⇒ 每张 vtable 的 `.rdata` 布局是 `[COL dword][slot0][slot1]…`，符号/address point 落在 **+4**；
   目标二进制**没有** RTTI COL（全库仅 6 条 `.?AV` 串且全是 CRT/STL）⇒ **每表多 4 字节 + 逐槽位移**。
2. 因此 **`.rdata` 维度的 byte-match 结构性不可能**（不是"当前没对齐"，是"编译口径与目标不同构"）。
3. 注意边界：这只杀 **byte-match**。`vtable_verify` 的**归一化槽序列**仍可比（`coff_vtable` 会把 COL
   从槽数里剔除），带 `/GR` 时那条 `address_point_rtti` 偏差就是"目标无 COL"的**确定性信号**，不是噪声。

**建议（按优先级）**

1. **移除管线 `/GR`**（4 处，逐处可 grep）：
   `cmake/MSVCSettings.cmake:89` · `pipeline/compare.py:69` · `pipeline/compare.py:81` · `pipeline/cli.py:690`。
   理由：目标二进制无游戏类 RTTI，加 `/GR` 只会产出目标没有的数据；移除后 `.rdata` 口径与目标同构。
   ⚠️ **R=3 更正（原文此处为假）**：原文写"`.text` 侧 L1 口径本来就不带 `/GR`（`PROBE_FLAGS` 无 `/GR`）
   ⇒ 移除后 L1 口径不变"—— **错**。`/GR` **就在生产 L1 的 flags 串里**（`pipeline/cli.py:690` =
   `s4_baseline.json.flags`）⇒ 移除 `/GR` **会改变生产 L1 编译标志**：`.text` 字节比对**受影响**、
   **L1 基线须重测**（不得假定"口径不变"）。原推理的前提（`PROBE_FLAGS` = 生产口径）正是本轮
   ★Critical 的失实声称。落地时须在同一管线运行中当场读 L1 输出（ratchet 会回写基线，不能事后查文件）。
2. **`tools/vtable_verify.py:161` 的 `DEFAULT_PROBE_FLAGS = ('/Od','/GR')` 与目标不一致**：Task 6 的真机
   数字全部来自测试里显式传的 `flags=['/Od']`（无 `/GR`）；默认值却是带 `/GR` ⇒ 任何走默认值的对比都会
   多报一条 `address_point_rtti`。建议默认改为 `('/Od',)`，或在对比时显式声明"目标无 COL"。
3. 若决策是**保留 `/GR`**（例如为了异常/RTTI 语义的其它收益）：`.rdata` 维度只能声明为
   **归一化对比 + 已知 COL 差异**，并在门禁里把 `address_point_rtti` 定为**预期偏差**，
   **不得**在任何文档/判词里写 "vtable byte-match"。

> 落地范围说明：本任务受"只创建 `tests/test_vtable_e2e.py`"约束，**未改**上述 5 处；spike 的
> 结论、证据与建议已写进本报告 + `vtable_e2e_report.json.gr_spike`，代码改动转出（见 §9 T1）。

---

## 3. 接线 `_layout_asserts.h`（I-3：交付了却无人消费）

### 3.1 方案（`wiring_plan()`，纯数据、可测）

| 项 | 结论 |
|---|---|
| 接入位置 | 生成器自身契约：**必须在全部类声明之后包含**（`sizeof`/`offsetof` 需要完整类型）⇒ 自然接线点是 codegen 发射的 `.cpp` 的 **include 块末尾**（`emit_headers` 追加 `#include "_layout_asserts.h"`），**不是文件头** |
| `/FI` 强包含 | **不可用**。实测 `/FI <asserts.h>` 强包含发生在 TU 自身 include 之前 ⇒ 类类型未声明 ⇒ `C2059/C2143/C2118`（`verify_wiring.force_include_rc=2` 留痕）。即使 VC6 支持 `/FI` 也不能用于本头 |
| 上线方式 | **按类试运行**：`layout_assert_gen --only <Cls> --untrusted-policy consistency-only`，逐类接入 |
| 禁止 | **全量一次性开启**：真实数据 8846 条 consistency-only 断言会产生 **64 假杀 + 71 C2039**（Task 4 评审实测），会让 include 该头的 TU 直接编不过 |
| 门禁 | 每接一类必须同时给**正相**（编过）与**负相**（篡改常量 ⇒ C2118）；缺一即"未生效"（`wiring_decision`） |
| 档位性质 | `consistency-only` 是**漂移探测器**，不是布局真值证据（E-2 同源）：只捕获 codegen 声明相对注解常量的 stage 漂移 |

### 3.2 端到端生效验证（至少一个单元：`CCBStageShadow`）

| 证据 | 结果 |
|---|---|
| 生成（`--only CCBStageShadow --untrusted-policy consistency-only`） | rc=0，**9 条断言**（active 8 / commented 1；`consistency-only 8` + `suspect 1`；by_kind `shape 1 / size 1 / offset 7`）|
| **正相**：`#include "Combat/CCBStageShadow.h"` + 生成头 | **rc=0**（0 错误）⇒ 该类断言不假杀 |
| **负相**：把 `sizeof(CCBStageShadow) == 1556` 改成 `== 1557` | **C2118**（`negative_rc=2`）⇒ 断言**确实在编译中生效**（不是被注释掉的死文本） |
| 判词 | `wired_and_enforced` |

⇒ I-3 的"今天没有一条断言在编译中生效"已被**具体的正相+负相编译证据**闭合：机制可用、按类可用，
唯一缺的是把 include 追进 codegen 的 `.cpp` 发射（转出，见 §9 T2）。

---

## 4. 当日基线刷新（Task 5 锚点问题）

| 项 | 结果 | 命令 / 证据 |
|---|---|---|
| Task 5 **棘轮基线**（当日） | **rc=0**，落盘 `data/status/vtable_ratchet_baseline.json`（**78 类 / 841 槽**） | `vtable_decl_check.py --decls pal3/src --structs data/annotations/structs --baseline <path> --write-baseline`（**显式** `--baseline`） |
| 缺 `--baseline` 的契约 | **rc=2**（Q2 修法生效） | 同一调用去掉 `--baseline` ⇒ rc=2、不落盘、stderr 报错 ⇒ 不会造成"门禁永久静默关闭/永远绿" |
| `data/status/vtable_baseline.json`（mapper 派生快照） | **漂移 = 0**（`total_slots 841 / resolved 539 / pass 20 / fail 72 / order_mismatch 0` 与文件逐字相同）⇒ **今日无需刷新** | `vtable_mapper.check()` + 与文件逐字段比 |
| 该文件为何仍是隐患 | 它由**注解**派生（非 IDB 真值），合法注解瘦身会让它变成**过严锚点**（Task 5 评审 Q4 根因）。本任务给出去重口径：**每日重算并与当日棘轮基线同时落盘**，两者不一致时以重算值为准并显式改文件 | `refresh_baselines()` |

> "完整 codegen 之后取基线"：本任务**没有**跑 `codegen all`（理由见 §9 T5）——当前 `pal3/src/**` 已是
> Task 1–7 之后的生成物，当日 mapper 数字与文件**零漂移**本身就证明基线未陈旧；刷新命令已固定在
> `refresh_baselines()` 里，下次真实 pipeline 运行后重跑即可。

---

## 5. `.rdata` 裁判的已知边界（本节为**留档**；其中 ①② 是本任务新增量化）

| # | 边界 | 本任务处置 |
|---|---|---|
| ① | **类族一致性判据过度截断**：`bin_table_from_image` 见到"槽族 ≠ 首槽族"即断表，而派生类槽 0 常是**基类**函数、槽 1 起是自己的覆写 ⇒ 立刻断。实测 **92/189（49%）张真机表被截短**；注解表 **76/94**。交叉核对：**raw 界定 1164 槽 vs 族判据 639 槽 = Task 6 报告的"189 表/639 槽"** ⇒ Task 6 的真机数字是在**被截断**的表上算出来的 | 双裁判**改用 raw 界定**（仅"非代码指针即断"）作槽数分母，并把两者同时记进判词（`bin_slots` vs `bin_slots_family_rule`）；判据本身的修法转出（§9 T3） |
| ② | **表长硬上界截短**（**R=1 更正**）：`bin_table_from_image` / `vtable_compare.bin_table` 取"**下一个 ctor 实写目标**"作表长硬上界；**当该目标落在本表内部时**（相邻/派生子表与本体共享尾部）本表被截短。实测 `CEffectSystem` `0x56F824`：注解 **9 槽且逐槽与镜像 dword 同址、9 个都是代码指针**，而下一个 ctor 目标 `0x56F844` **恰是槽 8 的地址**（`base + 8*4`）⇒ 只读到 **8 槽**。⚠️ **不是**"`nxt[0]` 未排序"：唯一生产者 `bin_vptr_targets()` 返回 `sorted(out)`，所有调用点（`vtable_verify.py:1765`、`vtable_compare.py:244`）都传**有序表** ⇒ `nxt[0] == min(nxt)`，R=0 建议的"改用 `min(nxt)`"是**空操作** | 记录 + 转出（§9 T3 改写为"落在表内部的 ctor 目标"这一**真实边界**）；本任务未改工具 |
| ③ | **残项 146 槽（22.9%）**：bin 侧 idx 无名字（import stub `ff 25 <IAT>` 79 + 未命名函数 67）⇒ VA/名字两判据都不可用，保守报 `slot_key` | 记录（归零需补名字源：idx 覆盖 / PE import 表解析，属新增特性） |
| ④ | `.obj` 侧**占位槽名 `slot_N`** 在 idx 里无 VA 可归约（注释里才有地址）⇒ 该槽退化为名字判据、与 bin 侧真实 VA 不可比 ⇒ 保守报 `slot_key`（UI3DCtrl 8 条 `slot_key` 里多条属此） | 记录；**不得**用注解 `vtables[].slots[].addr` 反填（那是同源比较，零判别力） |
| ⑤ | 残项 **10 例** `_sdtor_*` / `_scalar_dtor` 同签名组参数编码不可区分 ⇒ 静默 | 记录（Task 6 R=2 ruling 已接受为文档化局限） |
| ⑥ | **`identity_mode='va'` 含"包含判据"**（**R=1 补记**）：逐槽身份判定里"一侧**单一 VA**、另一侧**候选集** ⇒ 用**包含判据**（`VA ∈ 候选集`）"，此时 `used_va` 同样置位 ⇒ 汇总出的 `identity_mode='va'` **不能**读作"两侧都有单一 VA"，只能读作"该表全部可比槽都走了 VA 系判据（含包含判据）"；退名字判据才记 `name`/`mixed` | 记录；判词里 `identity_mode` 必须与 `compare_tables` 的候选集注记同读（`vtable_verify.py:_slot_identity_decision` 判据 2） |
| ⑦ | **thunk 归一**：静态/动态 adjustor 归一为元组，动态 delta 用 `(target, kind=dynamic, const)` 三元组 | 记录（Task 6 已交付，本任务 e2e 未新增） |
| ⑧ | **COMDAT 折叠别名**：同体不同 VA 会假报（真机 0 冲突） | 记录 |
| ⑨ | MI 继承槽名归属差异**故意不自动判等**（否则会放过错误基类函数） | 记录（Task 6 顾虑 3） |

---

## 6. 真实归因线索（Task 5 产出）—— 逐条复核并定性

### 6.1 `CEffectSystem`：`Reset@0x4C6260` 被发射到槽 1，二进制在槽 8（8 处错位）—— **已确认，归因到发射器**

| 来源 | 槽序 |
|---|---|
| 二进制注解表 `0x56F824`（9 槽） | `0x4C5D50, 0x4C5D80, 0x4C5DB0, 0x4C5DE0, 0x4C5E70, 0x4C5E80, 0x4C5E20, 0x4C6030, **0x4C6260(Reset)**` |
| 发射头 `Effect/CEffectSystem.h`（9 条 virtual） | `slot_0(0x4C5D50), **Reset(0x4C6260)**, slot_1, slot_2, slot_3, nullsub_79, ProcessEffects, slot_6, UpdateEffectState(0x4C6030)` |

- 注解里 `Reset` **带 `"ordinal": 8`**（= 正确的槽下标），但发射头把它排在**声明第 2 位** ⇒ 8 个槽整体位移。
- 归因：发射器对"补位占位名（`slot_N`，按**表下标**命名）"与"已命名方法（按注解 `methods` 的 **VA/dict 顺序**）"
  **混用了两套排序**，`ordinal` 未被遵循。
- 处置：**记录 + 转出到发射器层**（§9 T4）。这是**代码生成**的缺陷，不是注解或 vtable 工具的问题；
  本任务不改（改 `emit_headers` 属别任务范围），但已给出可复现判据（同一头内比较声明序 vs 注解表槽序）。

### 6.2 `CGameData`：8 条 virtual 声明 vs 7 槽 —— **已确认，归因到发射器的"重复注入"**（**R=1 事实更正**）

- 注解表 `0x56B094` 7 槽 = `[0x445E70, 0x44F5B0, 0x44F4C0, 0x44F430, 0x445B90, 0x44F030, 0x445D10]`；
  **槽 5 = `0x44F030` = `CGameData::'scalar deleting destructor'(uint)`**（idx 实名，机读留痕
  `attribution.CGameData.bin_dtor_name`）⇒ **二进制有析构槽**，且注解 `methods` 已把该槽建模为
  具名方法 `_scalar_dtor`（`"ordinal": 5`）。
- 发射头 `Data/CGameData.h`（`virtuals = 8`）声明 `virtual ~CGameData() {}` **+ 7 条具名 virtual**；
  这 7 条具名与二进制 7 槽 **1:1 对应（含上面那个析构槽）**。
- ⇒ 多出的那条 `virtual ~CGameData() {}` 是**重复注入**同一个析构槽（注解已把该槽建模为具名方法
  `_scalar_dtor`，发射器又注入一条 `virtual ~`）——**不是**"凭空多出来的一个槽"（R=0 报告此处
  表述**事实错误**，R=1 已更正）。后果与 6.1 同类：发射器多产出一个槽位 ⇒ 派生表与二进制错位。
- 处置：**记录 + 转出**（§9 T4，与 6.1 同一层）。

### 6.3 Task 7 顾虑 a："另一契约读法（新形态失败也合成 stub）⇒ ≈460 新 stub" —— **量测（不依赖全量 pipeline）**

- 台账原因分布（Task 7 全语料实测，按函数去重）：`non_class_hint 240` · `self_arg_mismatch 185` ·
  `slot_out_of_range 21` · `no_vtables_declaration 17` · `name_declared_at_other_address 1`，R=1 收口后
  **439 行**（R=0 为 464 行）。
- ⇒ "新形态失败也合成 stub"会新增 **≈439–464 处** stub 调用。
- 判读（同意 Task 7 原读法）：这些间接调用文本**本身即可编译**（stub 机制是为 `__vftable` 成员不存在
  导致的 C2039 而设的**可编译性**兜底）⇒ 合成 stub **没有可编译性收益**，只会**引入新的字节差异**。
- 剩余不确定：**字节影响的确切值**需要一次完整 `loop --expect-*` 才能给（本任务未跑，见 §9 T5）⇒ 记为
  "已给出量级与方向、确切字节影响待真实 pipeline 运行"（§9 T5）。

---

## 7. 其它累积待办的处置

| 待办（来源） | 处置 |
|---|---|
| 6 个 `CEffTrack*` 的 `base_class` 重复间接基 ⇒ C2584 | **记录**（6 类均无 `.cpp` ⇒ 潜伏未阻断；属注解层独立工单） |
| `CCBParabolaWindow` C2555 + `PlayerAtt` `RoleAtt.h:91` C2061 | **记录**（头文件自身编不过，与 Task 4 评审点名的 8 个"发射头自身编不过"集合一致） |
| `stage3_cleanup.py:173-191` legacy 兜底仍直读 `structs/<Cls>.json` | **记录**（CLAUDE.md 已知 3 处直读之一，独立工单） |
| Task 7 台账 `data/status/vtable_transform_failures.md` | **未生成**：该文件是 codegen 运行时产物（`PAL3_VTABLE_FAILURE_LOG` 可注入路径）；本任务未跑 `codegen all`（§9 T5）⇒ 随真实 pipeline 运行入库 |
| Task 7 顾虑 a 的另一契约读法 | 已量测（§6.3） |
| 残项 146 槽 / 10 例 `_sdtor` / 表长**硬上界截短**（R=1 更正，非 `nxt[0]` 未排序）/ COMDAT 折叠 / thunk 归一 | 已留档（§5） |

---

## 8. 实现与测试设计（可复核）

### 8.1 判词是**数据派生**的，不停在"当前缺陷状态"

Task 5 评审 Q4 的教训：把"当前缺陷状态"钉死成必须成立，会在**正确修复**时报红。故：

* 断言全部落在**纯函数 + 夹具**上：`l1_verdict` / `rdata_verdict` / `classify_divergence` /
  `gr_spike_analysis` / `wiring_decision` / `header_facts` / `build_report` / `render_report`；
* 真实数据只用于 ① **报告落盘** ② **不变量**（如 `3` 个单元必须存在且 S2 `ok`、raw 界定 **1164 槽**
  与族判据的**子集关系** `family_rule ≤ raw`、`CEffectSystem` 的 `ordinal=8` vs 声明第 2 位、
  `CGameData` 二进制槽 5 = `0x44F030`（有析构槽）而发射头**重复注入** `virtual ~`）；
* **R=1 更正（I-4）**：此处原文写"`CGameData`/`CEffectSystem` 判据可复现"当时**无据**——
  测试文件对这两个类名 **0 命中**、报告 JSON 中亦 **0 命中**（纯口头断言）。现已补齐
  ① `attribution_evidence()` 的**机读留痕**（`vtable_e2e_report.json.attribution`）
  ② `test_live_dual_judge_report_end_to_end` 里的**逐条断言**（二进制槽 5 / idx 实名 /
  `ordinal` / 声明序 / 硬上界地址）⇒ 该断言自此**有据**；
* **R=1 修复（I-5）**：族判据的当前输出（**639 槽 / 92 张表截断**）是 T3 要修掉的**缺陷态**⇒
  `test_live_bin_table_census_*` **删去 639 硬钉**，改为 raw 界定不变量 + `family_rule ≤ raw`
  关系断言，当前值只**留痕**（打印 + 报告 JSON）；同理 `run_e2e` 侧的
  `truncated_family_rule > 0` 也改为**关系**断言。唯一**故意**钉住的缺陷态是 §1.1③ 的
  发射器归因（I-6：抄基类块 + 追加自家 `slot_0`）——那是本任务的**发现**本身，T4 落地时同步改；
* 分歧分类器对**未知状态抛 `ValueError`**（`test_divergence_rejects_unknown_status`）⇒ 不会把"判不了"
  伪装成"判过了"；`build_report` 对未知分歧同样拒绝。

### 8.2 分歧分类（7 类，全覆盖）

| L1 \ `.rdata` | clean | deviations / missing_vtable | not_applicable | probe_failed / no_evidence |
|---|---|---|---|---|
| green | `agree_clean` | **`l1_blind_rdata_broken`**（L1 结构性失明的直接证据） | `agree_nonpolymorphic` | `rdata_unavailable` |
| partial / skip / no_symbols | `rdata_clean_l1_broken` | `both_broken` | `l1_broken_rdata_na` | `rdata_unavailable` |

### 8.3 测试清单（27 条）

- **离线 19 条**：判词三态、`compile_skip` 不是绿、覆盖缺口（`unmatched`/`unresolved_synth`）留痕、
  `.rdata` 六态、分歧矩阵 10 组、未知状态拒绝、`/GR` spike 三态、接线判词四态、接线方案文案断言、
  `header_facts` 真头、报告 JSON 可序列化 + 统计、花名册与现实一致、3 个单元钉死。
- **真机 8 条**（`PAL3_E2E_LIVE=1`）：3 单元 L1 判词、3 单元 `.rdata` 判词（**+ I-6 的
  UI3DCtrl×UIWnd 逐槽归因断言**）、ctor 字节扫描定位
  `0x56ACFC`（+ `CCBStageShadow` 负相零命中）、表长普查（raw 1164 不变 + `family_rule ≤ raw`；
  当前值 639 / 92 / 76 **只留痕**）、`/GR` spike、
  接线（正相 0 + 负相 C2118 + `/FI` 不可行）、基线（rc=0 / 78 类 841 槽 / 缺 `--baseline` rc=2）、
  端到端报告回读（**写临时目录，不动入库 JSON**）+ **I-4 的 CGameData/CEffectSystem 归因断言**。

### 8.4 TDD 红绿

| 阶段 | 结果 |
|---|---|
| 红（9 个纯分析函数 `raise NotImplementedError`） | **2 passed / 16 failed / 7 skipped** |
| 绿（实现纯分析层 + 真机层） | 离线 **19 passed / 0 failed / 8 skipped**；真机 **27 passed / 0 failed / 0 skipped** |
| 前序回归 | 35 / 38 / 68 / 73 / 88 / 61(+3 skip) / 35 **逐套与基线相同** |
| **R=1 红**（I-6 按评审**字面**建议先写：`obj[1:21] == base[1:21]`） | **AssertionError**（实测 3 处不相等：`[2]/[15]/[16]` 是**同名在位覆写**）⇒ 字面断言不成立，按实测形态收敛 |
| **R=1 绿**（I-5 去 639 硬钉 + I-6 归因断言 + I-4 归因断言/留痕） | 离线 **19 passed / 0 failed / 8 skipped**；真机 **27 passed / 0 failed / 0 skipped**（R=1 实测；断言加在**既有**用例内 ⇒ 条数契约不变） |

### 8.5 复现命令

```bash
python3 tests/test_vtable_e2e.py                                             # 离线 19 条
PAL3_E2E_LIVE=1 python3 tests/test_vtable_e2e.py                             # 真机 27 条（不写入库报告）
PAL3_E2E_LIVE=1 python3 tests/test_vtable_e2e.py --e2e --no-write            # 只打印报告
PAL3_E2E_LIVE=1 python3 tests/test_vtable_e2e.py --e2e \
    --out data/status/vtable_e2e_report.json                                 # 显式刷新入库报告
```

### 8.6 R=1 新增/修正的断言（逐条对应评审发现）

| 发现 | 断言位置 | 形态 |
|---|---|---|
| **I-5** 硬钉缺陷态 | `test_live_bin_table_census_*` | 删 `family_rule == 639`；改 `raw == 1164`（不变量）+ `family_rule ≤ raw` + 例证 `family_rule < raw`；当前值 `print` 留痕 + 报告 `bin_census` |
| **I-6** 最强归因无断言 | `test_live_rdata_judge_three_units` 尾段 | `_emit_obj_table('UIWnd')` 现取 `??_7UIWnd@@6B@`，与本类表**逐槽**比：基类块同下标对齐、差异恰为 `[2,15,16]`（同名在位覆写）、`obj[12] == UIWnd::ShowWindow` 未被覆盖、`UI3DCtrl::slot_0` 落在 `len(base)`（追加）+ 追加块 5 条 |
| **I-4** §8.1 无据断言 | `test_live_dual_judge_report_end_to_end` 尾段 + `attribution_evidence()` | CGameData：二进制 7 槽 / 槽 5 = `0x44F030` / idx 实名含 `scalar deleting destructor` / 注解 `_scalar_dtor` `ordinal=5` / 头 8 virtual 且**具名 7 条与二进制 7 槽逐槽同序**；CEffectSystem：注解 9 槽逐槽与镜像同址、`Reset` `ordinal=8` vs 声明位 1、硬上界 `0x56F844` = 槽 8 地址且该 dword 仍是代码指针 |
| **Minor** 数字矛盾 | 文件头 / `judge_rdata` docstring / 普查 docstring | 统一 **92/189** |
| **Minor** 真机套件改写入库 JSON | `run_e2e(write=False)` 默认 + `--no-write` + 用例写 `tempfile.mkdtemp()` 后回读并清理 | 真机套件跑完工作树**不再变脏**（实测 `git status` 干净） |

---

## 9. 转出工单（本任务**未改**代码，逐条给出理由与落点）

| # | 工单 | 落点 | 理由 |
|---|---|---|---|
| **T1** | 移除管线 `/GR`（`cmake/MSVCSettings.cmake:89`、`pipeline/compare.py:69/81`、`pipeline/cli.py:690`）+ `vtable_verify.py:161` 默认探针 flags 去 `/GR` | 管线/工具层 | 属管线级改动，会同时影响 L1/编译口径与所有 vtable 探针；本任务范围限于 `tests/test_vtable_e2e.py`（spike 证据已足够决策）。⚠️ **落地必读（R=3 补）**：**移除 `/GR` 会改变生产 L1 编译标志**（`/GR` 在该 flags 串里，`pipeline/cli.py:690` = `s4_baseline.json.flags`）⇒ 与 `.rdata` 一并，**L1 基线须重测**，**不得**假定"L1 口径不变 / `.text` 比对不受直接影响"；落地须在同一 `loop`/`match` 运行中当场读 L1（ratchet 会回写基线，事后查文件不可判退化） |
| **T2** | `_layout_asserts.h` 落地接线：`emit_headers` 在发射 `.cpp` 的 include 块末尾追加 `#include "_layout_asserts.h"`（按类 `--only` 灰度） | codegen | 需改 `pipeline/gen/stages/emit_headers.py`；本任务已给出方案 + 逐类正/负相证据 |
| **T3** | `bin_table_from_image` 类族判据过度截断（92/189 张表）+ **表长硬上界截短**——下一个 ctor 实写目标**落在本表内部**时本表被截短（实测 `CEffectSystem` `0x56F824`：注解 9 槽、逐槽与镜像同址，截点 `0x56F844` = 槽 8 地址 ⇒ 只读到 8 槽） | `tools/vtable_verify.py` + `tools/vtable_compare.py` | 改工具需同时改其单测与跨实现一致性测试；本任务只做量化与"用 raw 界定绕过"。⚠️ **R=1 更正**：**不要把修法写成 `min(nxt)`**——`bin_vptr_targets()` 已返回 `sorted(out)`，所有调用点都传有序表 ⇒ `nxt[0] == min(nxt)`，"改用 `min(nxt)`"是**空操作**（I-2） |
| **T4** | 发射器槽序/槽数：① `ordinal` 未被遵循（`CEffectSystem` `Reset` `ordinal=8` 排在声明第 2 位 ⇒ 8 处错位）；② **重复注入**虚析构槽（`CGameData`：二进制槽 5 已是 `_scalar_dtor`，发射器又注入 `virtual ~` ⇒ 头 8 声明 vs 二进制 7 槽） | `pipeline/gen/stages/emit_headers.py`（发射层） | 代码生成缺陷，影响所有多态类的头；需单独评审 + 全量回归。**R=1 更正**：`CGameData` 的表述是"**重复注入**"而非 R=0 的"凭空多一槽"（二进制**有**析构槽，I-3） |
| **T5** | 跑一次完整 `loop --expect-*`：落地 Task 7 台账 `data/status/vtable_transform_failures.md`、量测"另一契约读法"的确切字节影响、刷新当日基线 | 管线运行 | 跑 `codegen all` 会把 Task 7 的 **113 处虚调用转换**首次写进 `pal3/src/**`（真实源码级 diff），超出 Task 8 "只创建测试文件"的范围，且会与并发的 Task 6 R=2 只读评审产生 diff 干扰。**本任务只报告，不执行** |
| **T6** | 6 个 `CEffTrack*` 去重间接基（C2584）· `CCBParabolaWindow` C2555 · `PlayerAtt` C2061 · `stage3_cleanup.py:173-191` 注解直读 | 注解 / stage3 层 | 均潜伏或独立，非本任务引入 |

---

## 10. 顾虑（诚实披露）

1. **3 个"断裂单元"的选择口径**：简报只给了 3 个文件名，未给选择依据。本任务以"文件存在 + S2 `ok` +
   判词由数据派生"落地，并用两条独立证据（字节级 ctor 扫描 / PDB / 注解）解释每个单元的断裂形态。
   若控制器原意是"另 3 个单元"（例如按 L1=0 的 49 个单元采样），本 harness 只需改 `TARGETS` 一行即可复用
   ——判词与报告机制与具体单元解耦。
2. **`PalScriptWaitObj` 的"二进制要多态"含 1 条参考级证据**：PDB 来自 PAL3A（偏移可能与 PAL3 不同），
   仅作参考。但 PMF=8（Task 4 编译器裁判，真编译产物）与"注解把 +0 建模成数据成员"是本地证据；
   三者一致才判定 `rdata_missing_vtable`。若只采信本地证据，结论仍成立（PMF 8 + 头 0 virtual）。
3. **`UI3DCtrl` 的 8 条 `slot_key` 偏差里混有两种成因**：① 真结构性错位（槽 1 起整体位移）② `.obj` 侧
   占位名 `slot_N` 无 VA 可归约（§5④）。本报告以 `slot_count 26≠8` 作为**可靠的主判据**，`slot_key` 作辅证；
   不把 8 条都算作"独立发现"。
4. **ctor 扫描的窗口与噪声**：窗口取 decomp `size_bytes`（下限 0x40、上限 0x800）。UI3DCtrl 的注解
   `methods` 含**继承来的** UIWnd 方法（`0x445E70` 等），扫描它们会额外命中 `0x56A66C`（一个与本类无关的
   ctor 实写）⇒ 证据生产者的输出**可能有无关命中**，本任务只用它做"注解地址与 ctor 写是否互证"，
   不据此自动改注解。
5. **`/GR` 建议未落地**：见 T1。若控制器选择保留 `/GR`，则本报告的 `.rdata` 判词需追加"COL 差异是预期"
   的口径说明（`render_report` 的 spike 段落已给出两种决策的措辞）。
6. **`data/status/vtable_e2e_report.json` 是运行时产物**（含时间戳与编译路径），两次运行会有时间戳差异；
   本次入库的是最后一次真机运行的结果。
7. **本任务未使用子代理**（遵守无子代理契约）。
---

# 11. R=1 修复轮记录（1 项必修 + 5 项文档/事实更正 + 2 Minor）

- **状态**：DONE
- **提交**：`37888beed`（2 files, +470/−32：`tests/test_vtable_e2e.py` · `data/status/vtable_e2e_report.json`；
  本报告在 `.superpowers/sdd/` 下、该目录被 `.gitignore` 忽略 ⇒ 不入库，与 task-1..7 同例）
- **约束遵守**：**只**改上述 2 个文件 + 本报告；**未**跑 `pipeline/cli.py apply` / `export`（**未碰 IDB**）；
  未改任何 `tools/` / `pipeline/` 代码；`git add` 只加了这 2 个文件。
- **一行测试摘要**：离线 **19 passed / 0 failed / 8 skipped**；真机 `PAL3_E2E_LIVE=1`
  **27 passed / 0 failed / 0 skipped**；前序 7 套逐套同基线（35 / 38 / 68 / 73 / 88 / 61(+3 skip) / 35）。

## 11.1 逐项处置

| # | 发现 | 处置 | 证据 |
|---|---|---|---|
| **I-5**（必修·质量隐患） | 普查用例硬钉 `targets_slots_family_rule == 639`（族判据**缺陷态**输出）⇒ 与 §8.1"不停在当前缺陷状态"自相矛盾，**T3 修好后该测试必红（尽管一切变好）** | **已删硬钉**，改 3 类不因修好而报错的断言：① **raw 界定不变量** `targets_slots_raw == 1164`；② **关系** `0 < family_rule ≤ raw`、`0 ≤ truncated ≤ targets`、`0 ≤ annotated_truncated ≤ annotated_tables`；③ 例证自洽 `family_rule < raw`。当前值 639 / 76 **只留痕**（`print` + 报告 `bin_census`）。`run_e2e` 侧原有的 `truncated_family_rule > 0`（同类硬钉）一并改为**关系**断言 | `grep -n "== 639" tests/test_vtable_e2e.py` ⇒ **0 命中**（余下 639 仅出现在文档/留痕文案里）；LIVE 实测 PASS，留痕打印 `族判据当前输出 639 槽（raw 1164）⇒ 截断 92/189 张真机表；注解表 76/94` |
| **I-2** ★ | §5②/T3 的 `nxt[0]`"未排序 bug"表述**不成立** | 已独立复核并**改写**：唯一生产者 `bin_vptr_targets()`（`tools/vtable_compare.py:81`）返回 **`sorted(out)`**；两个生产调用点（`tools/vtable_verify.py:1765`、`tools/vtable_compare.py:244`）都传**有序表** ⇒ `nxt[0] == min(nxt)`，R=0 建议的"改用 `min(nxt)`"是**空操作**。真实边界改写为"**ctor 实写目标落在当前表内部 ⇒ 硬上界截短**"（§5② + §9 T3 + 文件头/§7 同步） | 实测 `CEffectSystem 0x56F824`：注解 **9 槽**、逐槽与镜像 dword **同址且 9 个都是代码指针**；下一个 ctor 实写目标 `0x56F844` **恰是槽 8 的地址**（`base + 8*4`）⇒ `bin_table_from_image`（`family_of=None`）只读到 **8 槽**。机读留痕 `attribution.CEffectSystem`（`annotation_slots=9`、`annotation_slots_match_bytes=true`、`hard_end=0x0056F844`、`dword_at_hard_end=0x004C6260` 仍是代码指针、`raw_slots=8`）+ 断言 |
| **I-3** ★ | §6.2 称"`virtual ~CGameData(){}` 是凭空多出来的一个槽（二进制没有对应槽）"**事实错误** | 已改正：二进制 `0x56B094` **槽 5 = `0x44F030` = `CGameData::'scalar deleting destructor'(uint)`**（idx 实名）⇒ **二进制有析构槽**；头里 **7 条具名 virtual 与二进制 7 槽逐槽同序 1:1 对应**（含该析构）；多出的 `virtual ~CGameData() {}` 是**重复注入**（注解已把该槽建模为具名方法 `_scalar_dtor`，`ordinal=5`；发射器又注入一条 `virtual ~`）。归因到发射器层的大方向不变 | `attribution.CGameData`：`bin_dtor_slot_index=5`、`bin_dtor_name` 含 `scalar deleting destructor`、`annotation_scalar_dtor_ordinal=5`、`header_named_matches_binary_order=true`（`header_named_vas == bin_slots_list` 逐槽相同）；编译产物 `??_7CGameData@@6B@` **8 槽**（= 7 + 重复注入 1，**只留痕不硬钉**） |
| **I-1** | `identity_mode='va'` **含包含判据**（一侧单一 VA、另一侧候选集 ⇒ `used_va` 置位）⇒ §5 边界表**零处置** | §5 **补第 ⑥ 条**（原 ⑥⑦⑧ 顺延 ⑦⑧⑨，既有引用 `§5①`/`§5④` 仍有效）：`identity_mode='va'` 只能读作"该表全部可比槽都走了 **VA 系**判据（含包含判据）"，**不可**读作"两侧都有单一 VA"；退名字判据才记 `name`/`mixed` | `tools/vtable_verify.py:_slot_identity_decision` 判据 2（`o.va in b.va_candidates` ⇒ `used_va=True`）与 `compare_tables` 的 `votes.add('va' if used_va else 'name')` |
| **I-4** | §8.1"不变量…`CGameData`/`CEffectSystem` 判据**可复现**"**无据**（测试文件对二者 **0 命中**、报告 JSON 亦 0 命中） | 采推荐方案①：新增 `attribution_evidence()` **机读留痕**（写入报告新增的 `attribution` 段，`render_report` 也打印一行）+ 在 `test_live_dual_judge_report_end_to_end` 里对两条归因**逐条断言**；§8.1 已改写为"有据"，并显式记录 R=0 此处为无据断言 | 报告 JSON 顶层新增 `attribution.{CGameData,CEffectSystem}`（见上两行字段）；报告 §8.6 汇总表 |
| **I-6** | UI3DCtrl"抄基类块 + 自家 `slot_0` 被追加到 21"**只断状态、无断言保护** | **加断言**（写在既有 LIVE 用例内 ⇒ 条数契约 27/0 不变）：`_emit_obj_table('UIWnd')` 现取 `??_7UIWnd@@6B@`（**21 槽**），与 `??_7UI3DCtrl@@6B@`（26 槽）逐槽比 ⇒ ① 基类块同下标对齐、差异**恰为 `[2,15,16]`**（`slot_2`/`slot_3`/`slot_4` 与基类**同名 ⇒ 在位覆写**）；② `obj[12] == 'UIWnd::ShowWindow'`（**未被覆盖**）而 `UI3DCtrl::slot_0` 落在 `index == len(base) == 21`（**追加**）；③ 追加块 = 5 条本类新 virtual。`judge_rdata` 同时留痕 `obj_slot_keys`/`obj_slot_vas`/`bin_slot_keys` | **TDD 红**：按评审**字面**建议先写 `obj[1:21] == base[1:21]` ⇒ 实测 **AssertionError**（`[2]/[15]/[16]` 三处不相等）⇒ 字面形态不成立，按实测收敛；**绿**：实测 PASS。⚠️ 该断言**故意**钉住发射器当前形态（它是本任务的**发现**，T4 落地时应同步改），与 I-5"不得钉缺陷规则输出"的区别已写进代码注释与 §8.6 |
| **Minor** 同文件数字矛盾 | `:533` / `:1117` 写 `87/189`，文件头与报告/实测均 `92/189` | 统一为 **92/189**（`judge_rdata` docstring、普查 docstring；文件头原已 92） | `grep -n "87/189" tests/test_vtable_e2e.py` ⇒ **0 命中** |
| **Minor** 真机套件改写已入库 JSON | `test_live_dual_judge_report_end_to_end` 原写 `REPORT_OUT` ⇒ 时间戳 + workdir 让工作树变脏 | ① `run_e2e(write=False)` 改为**默认不写**并新增 `out_path`；② 该用例写 `tempfile.mkdtemp()` 后回读、`shutil.rmtree` 清理；③ CLI 新增 `--no-write`（`--e2e` 仅在显式 `--out`/默认路径时落盘） | 实测：跑完完整 `PAL3_E2E_LIVE=1 python3 tests/test_vtable_e2e.py` 与单跑该用例后 `data/status/vtable_e2e_report.json` 的 **sha256 前后不变**（`29fa63a5…` ⇒ `29fa63a5…`） |

## 11.2 实测数字（R=1）

| 命令 | 结果 |
|---|---|
| `python3 tests/test_vtable_e2e.py` | **19 passed / 0 failed / 8 skipped** |
| `PAL3_E2E_LIVE=1 python3 tests/test_vtable_e2e.py` | **27 passed / 0 failed / 0 skipped** |
| `PAL3_E2E_LIVE=1 python3 tests/test_vtable_e2e.py --e2e`（刷新入库报告） | 落盘含 `attribution` 段；表长界定仍留痕 **639 / 92 / 76**（raw 1164） |
| 前序 7 套 | 35 / 38 / 68 / 73 / 88 / 61(+3 skip) / 35 **逐套同基线** |

## 11.3 顾虑（诚实披露）

1. **I-6 与 I-5 的原则存在表面张力**：I-6 按评审要求钉住了发射器**当前**形态（追加而非覆写）。
   代码注释 + §8.6 已写明"这是**发现**的钉子，T4 落地时同步改"；其中
   "7 条具名与二进制 7 槽逐槽同序"等断言**不**依赖缺陷是否修好（修好后仍应成立）。
2. **`0x56F844` 在字节层面本身歧义**：它既是 `0x56F824` 的槽 8 地址，**也是**另一张 ctor 实写表的
   槽 0（两表共享同一 dword）⇒ "8 槽还是 9 槽"不是纯字节可判的问题。本任务只**量化 + 留痕 +
   断言判据**，不裁定谁对（裁定属 T3）。
3. **raw 不变量 `== 1164` 仍是对"观察口径"的硬断言**：它不钉缺陷值，但若 T3 改变表长语义
   （例如把落在表内部的 ctor 目标并入本表），raw 会变 ⇒ 该断言需同步更新（它钉的是**观察口径**）。
4. **`data/status/vtable_e2e_report.json` 已按新契约重生成**（含 `attribution` 段与
   `units.*.rdata.compare.obj_slot_keys` 留痕），时间戳为最后一次显式 `--e2e` 运行时刻。
5. **本任务未使用子代理**（遵守无子代理契约）。

---

# 12. R=2 修复轮记录（I-5 **二次**收口：一行条件式断言 + 1 Minor 降级留痕）

- **状态**：DONE
- **提交**：`9479c3a7e91b9c52ab8900d2011456867bb4c93e`（**1 file**：`tests/test_vtable_e2e.py`，+110/−88；
  `data/status/vtable_e2e_report.json` **未改**，sha256 前后同为 `29fa63a5…`；本报告在 `.superpowers/sdd/` 下、
  该目录被 `.gitignore` 忽略 ⇒ 不入库，与 task-1..7 / R=1 同例）
- **约束遵守**：**只**改 `tests/test_vtable_e2e.py` + 本报告；**未**跑 `pipeline/cli.py apply` / `export`
  （**未碰 IDB**）；未改任何 `tools/` / `pipeline/` 代码；`git add` 只加了这 1 个文件
  （`git status` 里其余 `??` 均为与本任务无关的既有未跟踪项，未被加入）。
- **一行测试摘要**：离线 **19 passed / 0 failed / 8 skipped**；真机 `PAL3_E2E_LIVE=1`
  **27 passed / 0 failed / 0 skipped**；前序 7 套逐套同基线（35 / 38 / 68 / 73 / 88 / 61(+3 skip) / 35）。

## 12.1 I-5 二次收口（必修）

**问题**：R=1 删掉了 `assert c['truncated_family_rule'] > 0`（硬钉"族判据截断缺陷存在"），但**同一提交**
在 `tests/test_vtable_e2e.py:1372` 新增的 `assert c['examples']`（非空断言）**等价地重新引入了同一危害**：

* `examples` 只在族判据**确实截断**时才非空 ⇒ 非空断言 = 要求"截断缺陷继续存在"；
* 与文件头 `:40` docstring"T3 修好族判据后两者应相等"**自相矛盾**；
* **T3 落地后**：族判据修好 ⇒ `examples == []` ⇒ 该断言**必红，尽管一切变好**。

**修法（控制器裁定，逐字落地）**：去掉非空断言，**只保留条件式关系断言**：

```python
# examples 非空时逐例自洽；为空（族判据已修好）时同样合法
for e in c['examples']:
    assert e['family_rule'] < e['raw'], e
```

`grep -n "assert c\['examples'\]" tests/test_vtable_e2e.py` ⇒ 2 命中，但**两处都在注释/docstring 里**
（`:1376` docstring、`:1390` `#` 注释，均作为反面引用），**可执行断言 0 处**；该用例对该键的可执行引用
只剩 `:1395` 的 `for e in c['examples']:`。docstring 的第 ③ 条同步改写为
"**条件式**：若 `examples` 非空…；为空同样合法"，使文档与断言不再互相矛盾。

**TDD 红/绿双向（实测输出，非口头）**：

| 场景 | 改前 | 改后 |
|---|---|---|
| 模拟 `examples == []`（族判据已修好：`family_rule == raw == 1164`、`trunc=0`、`annotated_truncated=0`） | **RED** — `AssertionError: {'targets': 189, …, 'examples': []}` | **GREEN** |
| 当前真实 `examples` 非空（实测 **8 条**；639 / raw 1164；截断 92/189 表；注解表 76/94） | GREEN | GREEN |

（驱动脚本 `/tmp/t8r2_tdd.py`：按路径加载被测模块 → 取真实 `bin_table_census()` 后把 `examples` 换成 `[]`、
`family_rule` 置为 `raw`，再直接调用该用例函数；两组各跑一次。）

## 12.2 Minor（成本低则做）：`_base_raw()` 降级留痕

**问题**：`attribution_evidence()` 的 `_base_raw()` 未包 try/except ⇒ 注解文件缺失 / JSON 坏 /
`vtables[0].addr` 非 hex 时，`run_e2e()`（含 `--e2e` 报告路径）**直接抛异常**，而非像同函数
`_emit_obj_table` 段那样"记 `error` 后继续"。

**修法**：把两段记录构建体提取为内部函数 `_cg_record()` / `_ce_record()`，统一由新增的
`_degraded_or(cls, fn)` 包裹；失败时返回 `{'cls': …, 'degraded': True, 'error': '…'}`（形状与健康路径同构，
缺哪个键由 `error` 指明），`run_e2e` 因此不再崩、报告仍能落盘并留痕。

**TDD 红/绿（实测输出；把 `STRUCTS` 指向不存在目录以模拟文件缺失）**：

| 版本 | 结果 |
|---|---|
| HEAD（改前，对照） | **RAISED** `FileNotFoundError: …/structs/CGameData.json` ⇒ `run_e2e` 崩 |
| 改后 | **DEGRADED** `CGameData.degraded=True` / `CEffectSystem.degraded=True`，各自带 `FileNotFoundError` 留痕 |

**重构等价性（可证）**：把新 `attribution_evidence()` 的输出与**入库报告 JSON 的 `attribution` 段**
逐键比对（两类的全部键：`bin_slots` / `bin_dtor_slot_index` / `header_named_vas` / `hard_end` /
`annotation_slots_match_bytes` / **编译路径产生的 `obj_slots=8` 与 `obj_slot_keys`** 等）⇒
**0 差异 / RESULT: EQUIVALENT** ⇒ 本次"提取内部函数 + 缩进变换"**无语义变化**。

## 12.3 实测数字（R=2）

| 命令 | 结果 |
|---|---|
| `python3 tests/test_vtable_e2e.py` | **19 passed / 0 failed / 8 skipped** |
| `PAL3_E2E_LIVE=1 python3 tests/test_vtable_e2e.py` | **27 passed / 0 failed / 0 skipped**（`grep -c "^  FAIL"` = **0**，EXIT=0） |
| 前序 7 套 | 35 / 38 / 68 / 73 / 88 / 61(+3 skip) / 35 **逐套同基线** |
| 入库报告 sha256 | `29fa63a59c77fd1b94649844f1b7b743c49bb7f55c7925b6626fb314f0a0c4b7` ⇒ **不变** |
| 工作树 | 跑完全部套件后仅 ` M tests/test_vtable_e2e.py`（无 JSON 脏化、无残留临时文件） |

## 12.4 顾虑（诚实披露）

1. **`assert c['targets_slots_raw'] == 1164` 仍是"观察口径"硬断言**（R=1 遗留，本轮未动）：它不钉缺陷值，
   但若 T3 改变表长语义（例如把"落在表内部的 ctor 目标"并入本表），raw 会变 ⇒ 该断言需同步更新。
2. **降级路径对 LIVE 用例仍然失败**：`_degraded_or` 的降级记录**不含** `bin_slots` 等硬键 ⇒
   `test_live_dual_judge_report_end_to_end` 会以 `KeyError`（而非 `FileNotFoundError`）/断言失败收场。
   本轮只按 Minor 要求把"崩溃"改为"降级 + 留痕"（**报告可落盘并说明原因**），**未**把该用例的断言改成
   "缺文件也算通过"——那会制造新的静默假通过。
3. **两层降级粒度未合并**：`_cg_record()` 内层原有的 `obj` 发射 try/except（`obj_emit_error`）保留不动，
   与新增外层 `_degraded_or` 是不同粒度的留痕；有意不合并以收窄改动面（本轮为"极小修复"）。
4. **88 行缩进变换由脚本执行后人工复核 diff**（`git diff` 全文过目 + `ast.parse` 通过 + 上述逐键等价性比对），
   `tests/test_vtable_e2e.py` 的**行为契约未变**（用例条数 19 / 27 不变、前序 7 套不变）。
5. **本任务未使用子代理**（遵守无子代理契约）。

---

# 13. 全分支最终评审收口修复轮（R=3）—— Critical + Important + 4 Minor

- **状态**：DONE
- **提交**：`244f0ea12`（4 files：`tests/test_vtable_e2e.py` · `tests/test_vtable_sig_infer.py` · `tools/vtable_sig_infer.py` · `data/status/vtable_e2e_report.json`）
- **一行测试摘要**：离线 **22 passed / 0 failed / 8 skipped**；LIVE **30 passed / 0 failed / 0 skipped**；前序 8 套 **35 / 38 / 71 / 73 / 88 / 61(+3 skip) / 35 / 22(+8 skip) 全 0 failed**（71 与 22 为本轮新增测试后的数：sig_infer 68→71、e2e 19→22）；跑完工作树**仅 4 个 tracked 文件 M**（无 JSON 脏化、无残留）
- **本报告文件在 `.superpowers/sdd/` 下（被 `.gitignore` 忽略）⇒ 不入库**；入库的是上述 4 个文件

## 13.1 ★Critical：L1 判词不在生产口径上运行却声称"与生产 L1 同一口径" —— 已收口

**失实声称（原 `tests/test_vtable_e2e.py:454-455` 与 §1）**：口径 = `compare_pal3.PROBE_FLAGS`
（`/nologo /TP /c /W3`，不含 `/O2`、不含 `/GR`），并称"与生产 L1 同一口径"。

**反证（三处独立可复跑，本轮逐条复核为真）**：
1. 生产 `match` 唯一调用点 `pipeline/cli.py:690` 传
   `--flags "/nologo /TP /c /W3 /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MD /Gd"`；
2. 生产 L1 基线 `data/status/s4_baseline.json.flags` **恰含 `/O2` 与 `/GR`**；
3. 入库报告三单元 `l1.flags` 实为 `['/nologo','/TP','/c','/W3']`。
⇒ `PROBE_FLAGS` 只是 probe 默认口径（`HYPOTHESIS_FLAGS` 才是含 `/O2`/`/GR` 的探针假设集）。

**修法（逐条落地）**
1. `judge_l1(unit, ctx=None, flags=None)`：默认走 `l1_flags(None)` = `production_l1_flags()`
   （读 `s4_baseline.json.flags`；缺失时退回与 `cli.py:690` 逐字相同的兜底常量，**不退 probe 口径**）；
   判词新增 `caliber`（`production-match`/`probe-default`/`explicit`）与 `flags_source` 留痕。
2. 措辞更正：`judge_l1` docstring、文件头表与"口径"节不再声称"与生产 L1 同一口径"，
   改为准确描述（probe 默认口径 **非** 生产 `match` 口径；生产口径见 `s4_baseline.json.flags`）。
3. **按生产口径重跑 3 单元**：`run_e2e` 并列跑两套口径 ⇒ 主判词 `l1` = 生产口径，
   `l1_probe_default` = probe 默认口径（对照）；`meta` 同时记录两套 flags + 来源 + 不可混读注。
4. 刷新 `data/status/vtable_e2e_report.json`（sha256 `29fa63a5…` → `e67d1278af21…`）。
5. 同步更正：本报告 §1/§2 建议①（原"移除后 L1 口径不变" **为假**）、台账 `:322`（原 `:308`）、
   T1 工单（写明"移除 `/GR` 会改变生产 L1 编译标志 ⇒ **L1 基线须重测**"）、
   `gr_spike_analysis` 的建议文本（同一条警告）。

**实测口径后果（同一 harness、同一单元、两套 flags 并列）**

| 单元 | 生产 `match` 口径 | probe 默认口径（原报告数字） |
|---|---|---|
| `CCBStageShadow` | **L1=2 / partial=6**（matched 9/10，unmatched 1，synth 1，rate 0.25） | L1=0 / partial=8（matched 9/13，unmatched 4，rate 0.0） |
| `PalScriptWaitObj` | L1=0 / partial=1（matched 1/1，unmatched 0，rate 0.0） | L1=0 / partial=1（matched 1/3，unmatched 2，rate 0.0） |
| `UI3DCtrl` | **L1=2 / partial=10**（matched 14/16，unmatched 2，synth 2，rate ≈0.167） | L1=0 / partial=12（matched 14/21，unmatched 7，rate 0.0） |

⇒ 原结论"L1 近乎结构性必为 0 ⇒ **该维度不具判别力**"是**口径错误的产物**：生产口径下
CCBStageShadow 与 UI3DCtrl **各有 2 条函数体逐字节全同**（UI3DCtrl 的 2 条即
`??_GUIWnd@@UAEPAXI@Z` / `??_GUI3DCtrl@@UAEPAXI@Z`）⇒ 该维度**有判别力**。
⚠️ 另注意：`symbols` / `unmatched` 也随口径变（`/O2` 下内联与 COMDAT 折叠不同）——
旧报告的"matched 9/13"与"matched 9/10"**不可混读**。分歧分类与 `summary` 不变（判词状态未变）。

**TDD（红→绿，可复跑）**：对 HEAD 副本三轴 RED ——
① `'/O2' in flags` False、`'/GR' in flags` False、`flags != PROBE_FLAGS` False（HEAD `judge_l1` 用的就是 `PROBE_FLAGS`）；
② `judge_l1` docstring 不含 `s4_baseline.json`，且仍含失实短语"同一口径：`compare_pal3.PROBE_FLAGS`"；
③ `production_l1_flags` / `l1_flags` 在 HEAD 模块不存在。
⇒ 改后三条离线测试 + 两条 LIVE 断言 GREEN（新增离线测试 3 条：19 → 22）。

**边界（不夸大）**：`.rdata` 裁判（真正的 vtable 裁判）走独立 `/Od` 探针，**不受本更正影响**，
其证据（UI3DCtrl ctor `c7 06 fc ac 56 00`@`0x43D83A`、二进制表 `0x56ACFC` 8 槽、obj 26 槽、
`0x56A600−4 = 0x3F800000` 非 COL）本轮未改动、评审已复证为真。

## 13.2 Important I-2：Task 6 评审 I3「报告 §2.1 输出删减」—— 已收口

`task-6-report.md §2.1` 原先只贴 `--list`（实为 **4 张表**）与 `--cls D --list`（实为 **3 张表**）
各自的**最后 1 张**，其余表的解析正确性无从核对。本轮**实跑复现并补全完整输出**（4 张 / 3 张，
含 `--cls D` 三视图各自 `vbtable = [-4, 24]`、`??_7D@@6B@` 的 `deleting_dtor` 与
`??_7D@@6BV@@@` 的 `composite` 互为对照），并加更正注说明原输出为删减版。

## 13.3 4 Minor —— 全部收口

1. **无端到端驱动器**（规格 §5 数据流未实例化）：**显式声明**（不补脚本，按评审给出的第二选项）——
   落点写入 `tests/test_vtable_e2e.py` 文件头（**已入库**）与台账：
   * 无独立驱动器脚本（`tools/`/`pipeline/`/Makefile/CI grep 0 命中）；
   * 串联 = ①**库级 import 链**（T1/T2/T3 → T5；T2 → T6、T2 → T3，逐条给行号）
     ②本文件 `run_e2e()`（T4/T5/T6 + L1 裁判）；
   * **T7 不由本 harness 驱动**（它是 codegen stage，由管线与 `test_vtable_call_transform.py` 覆盖）
     ⇒ **不得**把本 harness 说成"8 工具全链"。
2. **飞行前扫描 2 条假边**：台账扫描表已更正（`Task2→Task1`、`Task7→Task1` 划除 + 表注 M-1 给实测证据：
   `vtable_slot_order.py:47-48` 只 import `re`/`dataclasses`（`:33-34` 明写槽内容分类属 T2）；
   `stage3_cleanup.py:7-17` 只 import stdlib + `tree_sitter_cpp` + `data.store`，其名称解析读**注解**
   `vtables[0].slots` + `methods`（`:184-187`））；并补记更正时发现的**两条真实边**（T2→T5 `:122`、T2→T6 `:119`）。
3. **`--struct` 静默伪候选**：`tools/vtable_sig_infer.py` 新增 `_slot_evidence_kind()` 门 ——
   输入无槽证据（注解 JSON 形状）⇒ `SystemExit` **rc=1** 并说明原因；不再产出键为 `""` 的
   `? unknown _slot()` 伪候选。TDD：HEAD 静默 exit 0 且 stdout 含 `"methods_pending": {"": …`
   ⇒ RED；改后 GREEN。`--struct` 输入确实含 `slots` 时行为不变（不误伤）。
4. **CLI 前缀拒写误拒兄弟目录**：`startswith` → `_is_under_truth_source()`（`os.path.commonpath`
   路径分量级判定）⇒ `data/annotations/**` 仍**拒写**、兄弟目录 `data/annotations_bak_probe/**`
   **放行落盘**。TDD 双向（拒写真源 + 放行兄弟目录）。
5. **台账撤销标注**：`Ruling: 顾虑d…已补提交` 与 `Controller: … 入库` 两行加注
   "已被下文 `:401`（评审引用编号 `:381`）的『更正 M5』撤销"，并说明编号位移原因。

## 13.4 顾虑（诚实披露）

1. **`production_l1_flags()` 以文件为权威来源**：`s4_baseline.json` 是生产运行会**回写**的文件
   （ratchet）。若某次 `compare_pal3.py` 被不带 `--flags` 直接调用，基线 `flags` 会变成 probe 口径，
   本 harness 会**随之改变主判词口径**（已有断言 ②③ 会在该情形下报红：`/O2`/`/GR` 不在 ⇒ 测试失败，
   属于"响亮失败"而非静默降级）。⇒ 这是**故意**的选择：口径以生产基线为准，不硬编码副本。
2. **双口径使 LIVE 编译次数翻倍**（3 单元 × 2 口径 + 其余探针，实测总时长仍在分钟级）：
   换来的是可对照的历史数字，且 `run_e2e` 默认**不落盘**（R=1 约定保持）。
3. **文件头"L1=2/6"等数字是运行产物**（`/O2` 口径下的当前观测），不是缺陷态钉子；
   若后续修复改变它们，只有 `test_live_*` 的状态类断言（`l1_partial`）与口径断言会生效，
   数字本身不硬断言（与 I-5 原则一致）。
4. **本报告与台账在 `.superpowers/sdd/`（gitignore）⇒ 本轮对 §1/§2/T1/台账的更正不入库**，
   仅本地可查；这与 task-1..8-report 的既有约定一致（评审已记录为 deferred minor）。

## 13.5 提交后复核（可复跑）

* **入库报告可复现**：`PAL3_E2E_LIVE=1 python3 tests/test_vtable_e2e.py --e2e --out /tmp/repro_report.json`
  产出与入库 `data/status/vtable_e2e_report.json` 逐键比对 ⇒ **除 `generated_at` 外完全相同**
  （`REPRODUCIBLE: True`）⇒ 提交的 JSON 不是手改产物。
* **sha256**：入库前 `29fa63a59c77fd1b94649844f1b7b743c49bb7f55c7925b6626fb314f0a0c4b7`（`HEAD~1` 实测）
  → 入库后 `e67d1278af21bbfbad6db86197ccad3fd56b18fe61ee90ed6bf43b737f93230e`（实测）。
* **工作树**：`LIVE 套件`、`--e2e`、`--e2e --out /tmp/…` 三种运行后 `git status --porcelain` 均**无 modified tracked 文件**
  （棘轮基线重写字节相同）；`data/annotations_bak_probe/` 测试后**无残留**。
* **提交内容**：`244f0ea12` 仅 4 文件（`git diff --cached --name-only` 核对），无 JSON 脏化、无临时文件入库。

---

# 14. R=4 收口修复轮（本项目**最后一个修复轮**）：M-3 + 新增破环（拒写守卫符号链接）

- **范围**：`tools/vtable_sig_infer.py` + `tests/test_vtable_sig_infer.py`（唯一改动面）
- **状态**：M-3 **ADDRESSED**（含 2 条评审反例）+ 符号链接破环 **ADDRESSED**
- **一行测试摘要**：`python3 tests/test_vtable_sig_infer.py` → **77 passed / 0 failed / 0 skipped**（71 → 77，**+6**）；前序 8 套 **73 / 35 / 38 / 77 / 88 / 61(+3 skip) / 35 / 22(+8 skip)** 全 exit 0 / 0 failed

## 14.1 病灶层检查（动手前，逐问作答）

| 问 | 答（可复核） |
|---|---|
| 病灶在哪一层？ | **工具自身的输入校验层**（`_slot_evidence_kind` 只判顶层形状），不在 T2 分类器 / 推断器。顶层 `list` 放行后，`_slots_from_json`（`vtable_sig_infer.py:1484` 分支 `elif isinstance(data, list): slots = data`）把 `{"methods":{}}` 当**单槽** ⇒ `SigEvidence(addr='')` ⇒ 键 `""` |
| 消费者实际读哪个文件/哪份声明？ | `_slot_evidence_kind()` 的**唯一调用点**是 `main()`（grep 全仓 1 命中）；下游链 `main()` → `_slots_from_json` → `infer_address_record` → `build_methods_pending`。无第二消费者，故门只需在 `main()` 收紧 |
| 报错还缺什么信息？ | 旧 `SystemExit` 只说"顶层形状不含槽证据"，**不指出哪个条目**坏 —— 逐项门给出 1-based 条目序号（`_slot_items_without_evidence`），调用方可直接改 |

### ⚠️ 简报复现命令的**字面**形态是 `open()` 失败（事实更正，不影响修法）

简报给的是 `python3 tools/vtable_sig_infer.py --struct '[{"methods":{}}]'`。实测该形态把 JSON 文本
当**文件路径**（`main()` 只有 `open(src)`，无内联 JSON 形态）：

```
$ python3 tools/vtable_sig_infer.py --struct '[{"methods":{}}]'
FileNotFoundError: [Errno 2] No such file or directory: '[{"methods":{}}]'      # exit 1（traceback）
```

⇒ "静默 exit 0 + 空地址伪候选"的**实质**复现是**文件内容**为该 JSON（本轮按此复现，`/tmp/r4/a.json`、
`/tmp/r4/b.json`，改前 exit 0 + `"methods_pending": {"": … "? unknown _slot()"}`）。缺陷本身为真，
仅命令写法需要落到文件上；本轮**未**新增"内联 JSON"入口（超出工单范围）。

## 14.2 M-3：`--struct` 门的**逐项**缺口（ADDRESSED）

**根因**（与评审一致）：`_slot_evidence_kind()` 只判**顶层形状**（任意 `list` ⇒ `'list'` 即放行），
**无逐项校验**；其 docstring 又把"裸列表"列为合法输入 ⇒ 门有缺口。

**修法**（`tools/vtable_sig_infer.py`，新增 2 个私有判据 + `main()` 一处门）：

* `_slot_entry_lacks_evidence(item)`：条目**自身**必须带槽证据才放行 ——
  `str` 非空白（Ruling 1 原始反汇编文本，即"裸列表"形态）**或** `dict` 的 `addr`（str/int）
  **或** `disasm`（str）之一非空；其他类型一律无证据。
  `name`/`symbol`/`signature` **不单独**构成证据 —— 注解 `known_members` 条目就带 `name`
  （`{"offset":0,"name":"m_x","type":"int"}`），若算证据会重新打开空地址伪候选通道。
* `_slot_items_without_evidence(data)`：返回无证据条目的 **1-based 序号**列表。
* `main()`：顶层门（M-2a）之后**再**逐项校验，非空 ⇒ `SystemExit`（**rc=1**），消息含条目序号 +
  合法形态说明；**fail-closed**：混入坏条目时**整体拒收**，不"悄悄跳过坏的、只出好的"。

**TDD（可复跑）**：先写 4 条测试 ⇒ HEAD RED **3 条**（`[{"methods":{}}]` / `{"slots":[{"methods":{}}]}`
均 stdout 含 `"methods_pending": {\n  "": {` 且 exit 0；混入坏条目亦 rc=0）⇒ 改后 GREEN。

**"含 `slots` 不误伤"的双向证据**：`test_r4_slot_evidence_positive_cases_still_processed` 钉三种合法形态
仍 rc=0（① `slots` 列表 ② 裸列表 dict 条目 ③ 裸列表**字符串**条目）；③ 的键仍是 `""`，但它产出的是
**真推断**（实测 `? __thiscall _slot(?,?)`，B 级）而非 `? unknown _slot()` ⇒ 断言显式排除伪候选
（"键为 `""`"本身不是缺陷判据，"无证据却被当成槽"才是）。

**边界（不夸大）**：单槽对象只给 `addr`（无 `disasm`）仍放行 ⇒ 产出**真实地址**上的
`? unknown _slot()` / C 级 + `insufficient_evidence` 痕迹 —— 这是 Ruling 2 的**契约**
（证据不足 ⇒ C + 留痕，不得当安全默认），**非**本次空地址伪候选缺陷态。

## 14.3 新增破环：拒写守卫经**符号链接**绕过（ADDRESSED）

**复现**（改前实测，`data/annotations_link -> data/annotations`）：

| 路径 | 期望 | 改前（纯词法 `commonpath`） | 改后 |
|---|---|---|---|
| `data/annotations/x.json` | 拒 | True | True |
| `data/annotations_bak_probe/o.json` | 放行 | False | **False**（M-2b 保持） |
| `data/annotations_link/x.json` | 拒 | **False ✗** | **True ✓** |

**修法**（`_is_under_truth_source`）：`os.path.abspath` + **`os.path.realpath`**（解析符号链接）后各自
`commonpath`，两条判据取**或**（任一为真即拒）：① 词法在真源内（覆盖"链接**位于**真源树内、指向外部"
的树内挂载点，纯 realpath 会放行）；② 解析后在真源内（覆盖本次破环）。兄弟目录两条均为假 ⇒ 仍放行。

**测试**（2 条）：`test_r4_truth_source_refusal_resolves_symlinks`（符号链接 ⇒ 拒 + **目标文件不落盘** +
兄弟目录仍放行**并真的落盘**）· `test_r4_truth_source_internal_symlink_pointing_out_is_still_refused`
（树内链接指向外部 ⇒ 仍拒且不落盘）。清理用 `try/finally` + `os.path.islink` 判定。

**独立 shell 复证**（非单测口径，改后实测）：A) `--out data/annotations_link/…` ⇒ exit 1 且目标文件不存在 ·
B) 直写真源 ⇒ 拒 · C) 兄弟目录 ⇒ `[vtable_sig_infer] 1 地址 / 1 候选 → …` exit 0 · D) **多级链**
`/tmp/link2 -> data/annotations_link -> data/annotations` ⇒ 拒。

## 14.4 仓库卫生与事实更正

* **无残留**：测试跑两遍结果逐字相同（77/0/0）；`ls -d data/annotations*` 只有 `data/annotations`，
  `data/annotations_link` / `data/annotations_bak_probe` / `data/annotations/__r4_*` 均**不存在**。
* **事实更正（本轮实测）**：历轮报告/台账写的"`.superpowers/sdd/` 被 gitignore ⇒ 不入库"**为假**，
  且**假的具体机制已定位**（这正是它骗过人两轮的原因）：

  ```
  $ git ls-files .superpowers | wc -l                # 17 —— 本计划文件早已入库
  $ git add .superpowers/sdd/…/progress.md           # 已跟踪文件，改动**确实进了索引**
  $ echo $?                                          # 1  ← 因 .superpowers/sdd/.gitignore 的 `*` 打 advice 并 exit 1
  $ git status --short .superpowers                  # M  …/progress.md  ← 已在索引里
  ```

  ⇒ `git add <该目录> && git commit …` 这种**链式**命令会因 `add` 退出码 1 而**静默跳过提交**
  （R=3 轮即如此，随后才由 `212f53b02` 单独补入库 R=3 台账段）——"不入库"是**提交没跑**的现象，
  不是 gitignore 的效果。本轮按 R=3 先例**分两个提交**：①代码+测试 ②报告/台账（docs，用
  `git commit` 直接提交**已暂存**内容，不再链式 `&&`）。**未**修改任何管线 / annotation / 其他工具。

## 14.5 顾虑（诚实披露）

1. **两条判据取"或"是超出简报的加严**（简报只说 realpath 后再 commonpath）：额外拒掉"真源树内挂载点
   指向外部"这一形态。理由是拒写守卫应保守（该形态仍会往真源树写文件），且它与 M-2b 无冲突
   （分量级比较不受影响，兄弟目录两条判据均为假）——有专门测试钉住该分支。
2. **`signature` 不单独构成证据**是新增判据（原 `_slots_from_json` 接受 `signature` 字段）：单独给
   `signature` 而无 `addr`/`disasm` 的条目现在被拒（旧行为会产出**空地址**记录）。这是收紧而非放宽，
   与"输入契约要求原始指令字节"一致；若将来需要"只给签名"的旁路入口，应显式加 `addr`。
3. **未新增内联 JSON 入口**：简报字面命令（`--struct '<json>'`）在本工具是文件路径参数（见 §14.1）。
   本轮只修"文件内容为坏 JSON"的实质缺陷，不改 CLI 参数语义 —— 若评审希望支持内联 JSON，属新功能。
4. **`data/annotations_link` 这类临时符号链接由测试自建自清**：测试在仓库 `data/` 下建链接（复刻评审
   现场），若进程被强杀可能残留一个**符号链接**（非文件、不影响真源内容）；已用 `islink` 前置清理 +
   `finally` 兜底，实测两遍无残留。
