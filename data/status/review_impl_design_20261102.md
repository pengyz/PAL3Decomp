# 对抗性复核：ghidra 双轨验证轨·实现设计——完备性专项（2026-11-02）

> 复核人：独立对抗性复核（subagent）· 被复核物：`docs/specs/2026-11-02-ghidra-dual-track-impl-design.md`（9 节）
> 交叉一致性核对：`docs/specs/2026-11-02-ghidra-dual-track-spec.md` · `docs/specs/2026-11-02-e2e-fixture-rules.md` ·
> `data/status/review_persist_arch_20261102.md`（前次定谳 C 案）· `CLAUDE.md`（项目纪律）
> 现场取证：仓库工作树只读巡检（apply_plan.py / run_e2e.py / import_annotation.py / import_via_daemon.py /
> case-01 产物 / ghidra_proj 库态 / thirdparty 两仓 / data/annotations schema）。
> 铁律：不准确=不判定 · 只做等价变换不编造 · 引用带文件路径+行号。**本复核只写本文件，未运行任何会改库/改产物的命令。**

---

## 1. 总裁

**有条件通过。**

一句话根据：**架构骨架（单源双渲染 / 四钉夹具 / 七铁律 / VERIFICATION-ONLY）立得住且全部有实证锚，
但 M1 收官判据本身三方不对齐、D2/D3 两条钉的现行判据一假红一假绿、L-fresh/L-lock 在实现与现场双双失守——
设计文本必须先修订（G1-G5），才允许按 §8 口径收 M1；G6-G8 修完才允许 M2 开工。**

| 维度 | 裁定 | 依据 |
|---|---|---|
| 架构（§2 数据所有权/双通道/四钉） | **通过** | 单源双渲染+派生可弃与 spec 铁律 1-3 一致（spec:73-77）；与 CLAUDE.md「字节匹配第一」无冲突（§1:21「L1 三限定口径不变」） |
| 6 ADR | **4 过 2 有条件** | ADR-1 措辞失准（G15）；ADR-3 与本文 §4.2:83 自相矛盾（G7，病灶层「双副本分叉」同型坑）；ADR-2/5/6 成立（均有实证锚） |
| 七铁律（§4.5） | **内容全对，可执行性 2/7** | L-persist/L-addr 半自动；L-fresh 声明自动实未实现（G4）；L-lock/L-rebuild/L-assert/L-no-self-kill 无检查点（G16） |
| M1 收官口径（§6/§8） | **驳回现状** | 「沿用 spec M1-M4 口径」（§6:141）不实：spec M1=切片双轨差分清单+逐条溯源（spec:86,102-104），本文 M1=case-01 四钉+「D4 挂位」（§6:143, §8:170）——弱化且错位（G1） |
| M2-M4 | **有条件** | 差分器（G1 核心产出的生产者）组件/ schema /对齐键全文缺位（G6）；签名面三分叉（G7）；plan 不可重放（G8） |
| 现场一致性 | **部分失守** | ~index.dat 毒化+残锁现存于 ghidra_proj（G5）；case-01 D2 现读数 FAIL 是判据自损假红（G3） |

**驳回未到**的理由：没有发现「方向性错误」——所有被攻出的缺口都是**完备性/判据精度**问题，
设计的骨架、数据所有权、失败即弃出口（§7:159-164）均可保留。

---

## 2. 缺口表（分级）

### 阻塞 M1（不修不得按 §8 收 M1）

| # | 缺口 | 锚点 |
|---|---|---|
| G1 | **M1 判据三方不对齐**：§6:141 声称「沿用 spec M1-M4 口径」，但 spec M1=「切片函数集双轨编译错误清单落档 + 每条差异可溯源（错误码/单元/行级锚点）」（spec:86,102-104），本文 M1=case-01 四钉全绿+「D4 挂位或出首表」（§6:143, §8:170）——「挂位」弱于 spec:103 的可溯源硬要求；且 `dual_track_m1_diff.json` 无产出工具、无 schema（§5:119-135 目录里没有差分器） | impl:141,143,170-171 / spec:86,102-104 |
| G2 | **D3 `this->m_flags` 达成路径缺失 + 判据弱于规则**：M1 ④ 要求「D3 5/5 含 this->m_flags」（§6:143），但 (a) render.json 判据是裸成员名正则 `m_complex\|m_flags`（`expected/render.json:2`），`param_1->m_flags` 会**假绿**——而 e2e rules:34 明文要求「`this->member` 出现」；(b) 现场实证 fresh-session 渲染为 `param_1->` ×4、this->m_flags 尾钉未收，同会话渲染更退化为 `*(int *)(this + 0x38)`（`ghidra_track/out/case-01-struct-union-overload/slice/update.c:9`，apply 同进程 emit，apply_plan.py:166-179）；(c) setThis 已死（§9:184/L9），ghidra_sig_params 命名 'this'（import_annotation.py:97-98）但 fresh 会话丢名——设计未给任何达成机制，也未裁定等价形归一（`param_N->`≡`this->`） | impl:143 / e2e-rules:34 / render.json:2 / update.c:9 |
| G3 | **D2 判据自损——现读数 FAIL 不可信**：`slice/ghidra_isms.h` 从未被任何代码生成（全仓仅 run_e2e.py:72,80 引用，生成者缺位），all_units.cc `#include "ghidra_isms.h"`（run_e2e.py:80）→ 编译报 `fatal error: ghidra_isms.h: No such file or directory` → 落入 catch-all `else: transform-broken`（run_e2e.py:94）⇒ **当前「transform-broken 1」（report.json D2=FAIL）就是判据自身缺件**（前次复核 U5 悬案定谳）。另：桶分类正则顺序缺陷——`constructor\|code\*\|template\|::`（run_e2e.py:90）先于 `no member\|has no member`（run_e2e.py:92），带 `::` 的 annotation-signal 会被吞进 transform-broken；catch-all 强行入桶违反「不准确=不判定」（应设未分类桶=fail） | run_e2e.py:80,87-94 |
| G4 | **D2/D3 读数污染 + L-fresh 未实现**：slice 目录从不清场（apply_plan.py:170 makedirs 不清旧件；run_e2e.py:69-70 全量收 `.c`），实测 35 文件**双代同堂**（16:50 PIE 时代 `FUN_00101020.c` 与 18:48 `-no-pie` 时代 `FUN_00401020.c` 并存）；D3 把全量拼串判读（run_e2e.py:104）⇒ 跨代假绿/假红双向风险。且 D3 读的是 apply 同进程产出（ADR-5/L-fresh 明文禁同会话读数，§3:63, §4.5:109），run_e2e 内**没有** fresh-session 重渲染步骤 ⇒ §8:173「L-persist/L-lock/L-fresh 在 run_e2e 内自动执行」为不实陈述 | run_e2e.py:69-70,104 / apply_plan.py:166-179 / impl:63,109,173 |
| G5 | **L-persist/L-lock 现场活失守 + 探针收尾纪律缺位**：`ghidra_proj/PAL3_FX.rep/{idata,user,versioned}/~index.dat` 三份毒化清单 + `PAL3_FX.lock`/`PAL3_FX.lock~` 残锁**现存**（现场实证=daemon「Program not loaded: fixture」根因）；而 run_e2e.py:60-68 的 T1 持久化探针是 `pyghidra.start()→openProject→openProgram('/','fixture',**False**)→print` **无 proj.close()**——它本身就是毒化源，且 rw 开库违反 ADR-2「旁路只许做只读探针」字面（§3:60）。L-persist 只管「写入」（§4.5:107），探针退出收尾纪律（close 与否、毒化清扫）无一条文；L-rebuild「库损坏=全重建」（§4.5:110）无**触发判据**（谁判损坏、Program not loaded 是否触发） | run_e2e.py:60-68 / impl:60,107,110 / ghidra_proj 实况 |

### 阻塞 M2（不修不得开 M2 全量）

| # | 缺口 | 锚点 |
|---|---|---|
| G6 | **差分器缺位 + B−A 方向三处自相矛盾**：spec:61 列「差分器=本仓新件 ⬜」，本文 §4/§5 全文无此组件、无 `dual_track_m1_diff.json` schema、无对齐键（B 轨 per-fn 单元 vs A 轨 pal3/src 大单元，spec:103 的「行级锚点」跨轨不可对齐）。方向矛盾：spec:47「差分（B−A）=Hex-Rays 约束清单」vs spec:104「**仅 A 有**簇=Hex-Rays 约束」（集合差方向相反）；本文内部 :144「B−A 差分=Hex-Rays 约束清单」vs :171「仅 A 有=Hex-Rays 约束归因」同反；且 §1:15「（transform-broken 桶=约束证据）」与 e2e-rules:42「transform-broken=变换应消（B 轨噪声）」**定性直接对立**——归因方向错则 G1 核心产出定性反 | spec:47-48,61,103-104 / impl:15,144,171 / e2e-rules:42 |
| G7 | **签名面三分叉（ADR-3 漏判+自相矛盾）**：约定归一映射现存**三份**——`thirdparty/ghidra-mcp/ghidra-worker/src/main/java/com/ghidramcp/operations/DataTypeOps.java:1125-1138`（`_thiscall→__thiscall` 归一表，=ADR-3 的权威）· `ghidra_track/apply_plan.py:126`（`cls+conv` 条件，其余全落 `__cdecl`——`__fastcall` 被吞）· `ghidra_track/import_via_daemon.py:71`（dict 默认 `'cdecl'`，`__fastcall` 同吞）。更重：**同一 set_func_sig op 两通道产不同签名**——apply_plan 经 ghidra_sig_params 注入 `('this','Cls *')` 首参（import_annotation.py:97-98 → apply_plan.py:107-111），import_via_daemon 直接拼 `op['params']`（无 this）（import_via_daemon.py:72-75）⇒ 同注解经批量/增量通道灌库结果不同，D3/D4 差分混入管线噪声。§4.2:83「签名（经 4.3 的代理或本地 ArrayList 形）」与 ADR-3「不自造」（§3:61）自相矛盾（且「4.3 的代理」交叉引用指错——4.3 是消费面）。=CLAUDE.md `gotcha_dual_copy_table_divergence` 同型坑（stage3/stage5 30/34/交集 29/分叉 6 实证） | impl:61,83 / apply_plan.py:126 / import_via_daemon.py:71-75 / import_annotation.py:97-98 / DataTypeOps.java:1125-1138 |
| G8 | **plan 不可重放 + 无版本化**：§2:50「plan=派生（可重放）」不成立——(a) build_import_plan 只消费 `known_members`，**不吃 structs/*.json 的 `methods`**（import_annotation.py:52-75），而正式 schema 的方法签名在 methods（`data/annotations/structs/C3DSpark.json` 等实证；case-01 的 update/render/calc 全在 methods），case 的 plan 里 8 个 sig 是**会话期临时脚本人工并入**的（全仓 grep 无 plan 生成器/无 methods 合并代码）⇒ M2 的 3935 认领方法签名进不了 plan；(b) plan.json 无 schema 版本号，apply_plan 对未知 op kind 静默跳过（apply_plan.py:89-134 if/elif 无 else 报错）——§4.1:77 承诺的位域/枚举新 op 会被静默丢弃（假绿），违反「不准确=不判定」 | impl:50,77 / import_annotation.py:52-75 / apply_plan.py:89-134 |
| G9 | **多 case 隔离缺位**：全部 case 共用单项目单程序——run_e2e.py:50-53（`PAL3_FX` 项目 `-import …/fixture`，apply 目标 `/fixture`）、import_via_daemon.py:48（`programPath` 硬编码 `'fixture'`）。run_e2e.py:49 注释「幂等：已存在跳过」**无出处**：若真跳过，case-02 的新 fixture 二进制不会入库（地址轴错位=违 L-addr）；若重导，会抹写入（前次 U4 同型疑案）。nm 真址入注解（L-addr，§4.5:111）无自动对账（fixture 重编译后注解 addr 静默陈旧）。多 case 并发/串行均撞库；L-lock 无 run_e2e 级锁检查 | run_e2e.py:49-53 / import_via_daemon.py:48 / impl:111 |
| G10 | **M2 成本判据缺位（迭代支撑性）**：§6:150「改注解→plan 重放（**秒级**）→四钉回归=单轮闭环」在全量规模不成立。量级估计（分析估，未实测，见 §5）：apply_plan 全函数**双遍** decompile（apply_plan.py:172-180 出码遍 + 183-192 member_hits 遍，每函数 decompileFunction(30s) 上限）×2000 函数 ≈ 7-70 min；analyzeHeadless 重导入+自动分析 PAL3.exe ≈ 5-20 min；签名 3935 ops ≈ 0.5-3 min；四钉含两次 g++ 与全量拼编译 ⇒ **批量通道单轮闭环 15-90 min 量级**，「秒级」只在 case 切片成立。增量通道（daemon）M2 起才有（§4.2:86），M1 期间改一个注解=全量重放。deleteAll+重灌（§4.2:84）vs 增量的**分界判据**（多大改动走哪条）未写 | impl:84,86,150 / apply_plan.py:172-192 |

### 改进项（不阻塞，应排期）

| # | 缺口 | 锚点 |
|---|---|---|
| G11 | **D1 口径漂移**：e2e-rules:32 D1 三件=①layout 机测 ②**注解 size=layout** ③库内 sizeof；设计 §4.4:99 与实现（report.json：layout/sizeof_reconcile/persistence）把②丢了、加了持久化——注解 size 错、Ghidra 按错 size 建型时③两边同错=假绿通道。②无任何落点（run_e2e 不比 annotations size vs layout.json） | e2e-rules:32 / impl:99 / run_e2e.py:42,57-58 |
| G12 | **report.json 无 schema/无总判定/无趋势**：report.json 字段由 run_e2e.py:11,42,57-58,99-112 顺手拼出，无 schema 文档；「全绿判据=四钉全过」（§4.4:100）无人计算（report 无 case verdict 字段）；D2 只计数不记条文（U5 同源）；e2e-rules:18「report.json 每次 run 覆写」与 §6:153「每轮 report.json 落盘=趋势可查」矛盾（覆写≠趋势，除非逐轮 commit）；「每 case 四钉绿入 CI 快照」（§6:147）的快照形态（基线文件/棘轮/回退判据）全无定义——对照 CLAUDE.md 的 regression_detector/L1 棘轮纪律，D2 计数应「单调降」（e2e-rules:41）但 run_e2e.py:97 只有 `v<=allowed`，可涨回天花板 | impl:100,147,153 / e2e-rules:18,41 / run_e2e.py:97,99 |
| G13 | **错误桶白名单维护流程缺**：e2e-rules:42「逐个转白名单需附理由」无理由字段/无台账/无准入裁定人；与 §4.4:101「禁改期望迁就实现」的边界未裁（transform-broken 转白名单=改期望还是合法豁免？） | e2e-rules:42 / impl:101 |
| G14 | **D3 判据精度**：regex 对全量拼串匹配（run_e2e.py:104-107）与 render.json:2 desc 的作用域（「Derived::render 内」）不符=跨单元假绿通道；`count_min` 断言硬编码 `\bcalc\b`（run_e2e.py:109）——judge 不是 case 通用的，L2/L3 新 case 的重载钉会静默失效 | run_e2e.py:104-109 / render.json:2-4 |
| G15 | **ADR 漏判三件**：ADR-2「只读探针」边界无执法（无 grep 闸/无探针必须 readOnly=True 的规则——现 run_e2e.py:63 开 rw）；ADR-4「唯一验收口径」（§3:62）与 M2「全量差分表」/M3「登记册」两种非四钉验收不兼容；ADR-1「同一 IR 双渲染=D4 对拍公平性前提」（§3:59）措辞失准——A 轨不经 plan 渲染（apply_annotations 直读注解），公平前提是**同一注解源**，且转换层 bug 必须显式归入 D4「管线」桶（e2e-rules:35） | impl:59-62 / run_e2e.py:63 |
| G16 | **七铁律自动化检查点逐条缺位**（§8:173 声明「不靠人记」，实际 2/7）：见 §3.4 逐条表 | impl:103-113,173 |
| G17 | **quick 预设开关位置未写**：实证开关在 cpp-parser 的 `transformGhidraCode({preset:'quick'\|'full'\|'custom'})` API 选项（`thirdparty/ghidra-reconstruct/packages/cpp-parser/src/ghidra.ts:144-145,302-315,544-546`），**run.ts CLI 无 preset flag**（run.ts:75-119 只有 --codegen-only/--extract-only/--no-snapshot 等），config/project.json 也无 ⇒ §4.3:94「预设 quick/full」的切换点在设计里是悬空的，且「npx tsx run.ts」运行形（§4.3:93）根本不透传 full 对照档 | impl:93-94 / ghidra.ts:144-145 / run.ts:75-119 |
| G18 | **M1 四步顺序依赖/工程形未写**：①「apply 迁回 postScript 形」（§6:143）的脚本形未写——现 apply_plan.py 是 pyghidra `main(argv)` 形+模块级 `pyghidra.start()`（apply_plan.py:9-10,148-153），postScript 需 GhidraScript/run(currentProgram)+scriptArgs 收 plan，不是平移；「analyzer 已分析 vs 未分析差异」（必攻 5）未评估——postScript 在自动分析后跑 vs 现独立进程跑，fm.getFunctionAt 的 nofunc 集（apply_plan.py:97-101）可能不同，且 `-import` 已存在程序的跳过/重导语义未定（G9）。②daemon 消费被 G5 毒化阻塞（现场已中）；④依赖①持久化+②③出码，且④本身被 G2 卡住 | impl:143 / apply_plan.py:9-10,97-101,148-153 |
| G19 | **Ghidra 版本双钉**：spec:58「Ghidra 11.2.1（本仓既有）」vs §5:134「ghidra_12.1.2_PUBLIC（GHIDRA_HOME 钉 12.1.2）」；`tools/ghidra/` 两版并存（11.2.1+12.1.2，ls 实证）——前次复核 U6「钉死单一版本入 spec」未执行 | spec:58 / impl:134 |
| G20 | **L2/L3 面漂移 + PAL3 难点映射缺**：§6:147「L2：函数指针/位域/虚继承/静态成员」漏「枚举/模板实例」、「L3：-O2/内联/switch」漏「尾合并」（对照 e2e-rules:51-52）；L2/L3 清单未映射 CLAUDE.md「影响字节匹配的核心困难」——COMDAT 折叠/调整 thunk（vtable 布局细部）、CRT 边界（case 里已混入 __libc_start_main/_ITM_* 等 CRT 符号恰是现成考题但无判定）、模板特化桥接（template_bases）、成员函数指针（C2296/C2440 族）、`__usercall` 面（D6 fp 约定，commit 37895ea1b）均无 case 规划 | impl:147 / e2e-rules:51-52 |
| G21 | **测试三层缺口**：单测=转换层纯函数 8 测（test_annotation_import.py 5 + test_apply_plan_logic.py 3）✓；apply_plan 的 Ghidra 侧（两遍建型/replaceAtOffset/签名施加）无单测（可用 pyghidra 探针测）；双签名通道（G7）**无 parity 测试**；集成=四钉 ✓（判据缺陷见 G2/G3/G11/G14）；回归=无形态（G12）。且 spec:95 风险缓解「M1 前转换层测试**≥覆盖率硬门槛**」在 §4.1:76 被降级为「5 测」计数——覆盖率硬门槛丢失 | impl:76 / spec:95 |
| G22 | **杂项**：①§1:22「2b 暂缓，三险见 spec」悬空——spec 无「三险」清单（spec:29-32 非目标只有 grep 续账 A-D）；②e2e-rules:56 的 `run_e2e.sh` 不存在（只有 run_e2e.py）；③`ghidra_track/fixture/annotations/` 与 `cases/case-01…/annotations/` **双副本已分叉**（diff 实证：fixture 版是 0x0/0x1000 占位地址，case 版是 nm 真址）——又一处双副本（G7 同族）；④ghidra_proj2/proj3 实验残留项目+三份 ~index.dat（卫生+G5 物证）；⑤apply_plan.py:183 report dict 里 `verify_comps` 键重复书写 | impl:22 / e2e-rules:56 |

**已核对一致（无需改）**：零字节轨变更三方一致（§8:172 = spec:105 = CLAUDE.md 纪律 3；现场 git status 确认 pal3/src 与 data/annotations 无变更）；VERIFICATION-ONLY/可弃件（§1:23, §2:50）与 spec:73 一致；L1 三限定口径不变（§1:21）与 CLAUDE.md 度量盲区条款一致；§4.1:77「先 TDD 再实现」与 R15（CLAUDE.md 纪律现状表）一致；ADR-6/L-assert 与 R13 同型 ✓。

---

## 3. 逐条必攻发现

### 3.1 完备性缺口（必攻 1）
- **plan 版本化** → G8：无版本字段、无校验、未知 op 静默丢。
- **多 case 并发/隔离** → G9：单项目单程序 `fixture`，import 幂等语义无出处。
- **库重建判据触发** → G5/G10：L-rebuild 无触发器（「Program not loaded」是否触发重建未裁）；重建成本无量级。
- **错误桶白名单维护流程** → G13：无理由字段/台账/棘轮。
- **D4 A 轨接入** → G1/G6：IDA 轨怎么产同源 C 全文未写（e2e-rules:59,64 只说「同一份 annotations/ 灌 IDB」——但 codegen 是 PAL3 耦合的，fixture 案的 C₁ 产出路径、以及 M2 全量对拍时 A 语料取自哪次 probe 快照均未定义）；差分器无组件。
- **report.json schema / CI 快照** → G12。
- 另发现计划外缺口：G2（D3 判据精度）、G3（判据自损）、G5（探针收尾）——完备性审查顺手抓到的判据级实弹。

### 3.2 与 spec / e2e 规则 / CLAUDE.md 的一致性矛盾（必攻 2）
| 矛盾 | 两侧 | 判定 |
|---|---|---|
| M1 口径 | impl:141「沿用 spec 口径」vs spec:86,102-104 | **矛盾（G1）**，且 impl:170「D4 挂位」弱化 spec:103 溯源要求 |
| B−A 方向 | spec:47-48 vs spec:104 vs impl:15,144,171 | **三处互斥（G6）**；transform-broken 定性 impl:15 vs e2e-rules:42 对立 |
| D3 判据 | e2e-rules:34「`this->member` 出现」vs render.json:2 裸成员名 | **矛盾（G2）** |
| D1 三件 | e2e-rules:32 vs impl:99 | **漂移（G11）** |
| L2/L3 面 | e2e-rules:51-52 vs impl:147 | **漂移（G20）** |
| report 覆写 vs 趋势 | e2e-rules:18 vs impl:153 | **矛盾（G12）** |
| Ghidra 版本 | spec:58 vs impl:134 | **双钉（G19）** |
| 覆盖率硬门槛 | spec:95 vs impl:76 | **降级（G21）** |
| 零字节轨 / 验证轨可弃 / L1 三限定 | 三方 | **一致 ✓** |
| R7（确定性下游重跑）→ L-fresh 同型 | CLAUDE.md vs §4.5:109 | 精神一致，但实现缺位（G4） |
| 病灶层/双副本 gotcha | CLAUDE.md `gotcha_dual_copy_table_divergence` vs G7/G22③ | **设计自身引入同型坑（G7）** |
| 衰退纪律（棘轮） | CLAUDE.md L1 棘轮 vs run_e2e.py:97 `<=` | 无棘轮（G12） |

### 3.3 ADR 漏判（必攻 3）
- **ADR-2**：方向正确（pyghidra 旁路两真 bug 实证成立），但「只读探针」边界**不可执法**——run_e2e.py:63 现即开 rw 且无收尾；「探针退出也须收尾（否则 ~index.dat 毒化）」是铁律级遗漏（G5/G15）。
- **ADR-3**：「不自造」与本文 §4.2:83「本地 ArrayList 形」自相矛盾；批量通道签名面用什么没有裁定——若 set_prototype 批量慢（2000 函数未实测），退回 ArrayList 形则归一表双副本（apply_plan.py:126 vs DataTypeOps.java:1125-1138），**必须**指定单一归一层+parity 测试，否则 D4 差分混入管线噪声（G7）。
- **ADR-4**：「唯一验收口径」过宽——M2 全量差分表/M3 登记册不是 fixture 四钉能判的（G15）。
- **ADR-1**：决策（plan IR 载体无关）成立，但理由「同一 IR 双渲染=D4 公平性前提」不准——A 轨不经 plan；公平前提=同一注解源+转换层 bug 归桶（G15）。
- **ADR-5/ADR-6**：成立（emit 缓存假阴/空打补丁均有实证锚）。

### 3.4 生命周期七铁律可执行性（必攻 4）——逐条检查点

| 铁律 | 设计声明 | 自动检查点在哪 | 缺口 |
|---|---|---|---|
| L-persist（§4.5:107） | 写入走完整收尾；pyghidra 只读 | 半：run_e2e.py:60-68 T1 探针（读回断言）✓ | 探针自身无收尾+开 rw（G5）；「pyghidra 禁写」无 grep 闸（G15） |
| L-lock（:108） | 互斥持库；跑管线前清会话 | **无**——run_e2e 入口不查 `.gpr.lock`、不清 daemon 会话 | 缺；现场已有残锁物证（G5） |
| L-fresh（:109） | 渲染判据只认 fresh | **无**——D3 读同会话 slice（run_e2e.py:104） | 缺；§8:173 声明不实（G4） |
| L-rebuild（:110） | 损坏/换 bin=清重建 | **无**——无损坏检测、无触发器、run_e2e 无重建分支 | 缺（G5） |
| L-addr（:111） | -no-pie + nm 真址入注解 | 半：-no-pie ✓（run_e2e.py:15） | nm↔注解 addr 对账缺（G9）；layout_dump 编译步无 -no-pie（无害，仅备注） |
| L-assert（:112） | patch 必带锚点 assert | **无工具化**——无 safe_patch helper，靠人写 assert | 缺（可给 10 行工具收编） |
| L-no-self-kill（:113） | python 排己法清进程 | **无工具化** | 缺（同上） |

⇒ §8:173「L-persist/L-lock/L-fresh 在 run_e2e 内自动执行（不靠人记）」当前为**不实陈述**，验收 4 不可过。

### 3.5 M1 收官四步的顺序依赖/风险（必攻 5）
```
①apply 迁 postScript ──┬─→ ④case-01 四钉（D3 5/5 含 this->m_flags）
②daemon 消费跑通 ──────┤        ↑ 还依赖 G2 达成机制 + G3 判据修复 + G4 fresh 步
③reconstruct quick ───┘
⑤D2 红绿对照表 ──→ 依赖 G3（现读数假红）+「红绿对照」形态本身未定义（G12 同族）
```
- ②现被 ~index.dat 毒化阻塞（现场「Program not loaded: fixture」）——**顺序上 G5 清扫是 ②③ 的前置**，不在四步清单里（缺步）。
- ①postScript 迁移非平移：apply_plan.py:9-10 模块级 `pyghidra.start()` + `main(argv)`（:148-153）需改 GhidraScript 形；plan 经 scriptArgs 传入。**analyzer 已分析 vs 未分析差异**：postScript 跑在自动分析完成后（函数发现齐全，nofunc 集应更小），与现「import 分析→独立进程 apply」读数可能不同（apply_plan.py:97-101 nofunc 记账可作对照探针）——建议迁移后用 nofunc 集 diff 验证。
- **quick 预设开关**：不在 run.ts、不在 project.json，在 `transformGhidraCode({preset})` API（ghidra.ts:144-145）——设计未写清（G17），③「reconstruct quick 跑」的可复现命令行给不出。

### 3.6 迭代支撑性实测视角（必攻 6）
- **单轮闭环（改一个注解）**：M1 期=批量通道全量重放+四钉，**15-90 min 量级**（G10 分析估：decompile 双遍×2000 主导）；「秒级」仅 plan 生成本身（纯函数）成立。M2 起增量通道（set_prototype 单点）才是秒-十秒级，但受 G7 双通道不一致之累。
- **plan 重放后 Ghidra 库怎么增量**：设计=deleteAll+重灌（§4.2:84）——对结构体是 O(成员) 重建，对签名是全量 replaceParameters 重放，**没有**「只重放变更 op」的 plan diff 机制（plan 可重放≠plan 可增量）。2000 函数规模下 deleteAll+重灌本身可接受（分钟内），**贵的是配套的全函数双遍 decompile**（apply_plan.py:172-192）——它应移出批量通道职责（§4.2 本就没列它），改由消费面按需抽样。
- **建议判据**：M2 前给「单注解改动闭环」立时间盒（如 ≤10 min 走批量、≤30 s 走增量），超时即触发通道优化，否则「可迭代性」（§1:17 目标 4）只是宣称。

### 3.7 测试策略完备性（必攻 7）
- 三层落点：单测 ✓（8 测纯函数）/ 集成 ✓（四钉，但判据带 G2/G3/G11/G14 缺陷）/ 回归 ✗（无快照形态、无棘轮，G12）。
- 缺：apply_plan Ghidra 侧单测、双签名通道 parity 测试（G7）、覆盖率硬门槛（spec:95 在 impl:76 丢失，G21）。
- **fixture L2/L3 ↔ PAL3 难点映射**（G20）：L1 覆盖 vtable/inline-union/重载 ✓；L2「模板实例」≠ 模板特化桥接（template_bases）；**COMDAT 折叠/调整 thunk**（vtable 布局三难点）无 case；**CRT 边界**（CLAUDE.md 困难 #1）无 case（case-01 的 CRT 符号混入恰好是素材）；成员函数指针、`__usercall`（D6 fp 约定）无 case。L3 少尾合并。建议在 e2e-rules §4 表加「PAL3 难点映射」列逐项挂 case。

---

## 4. 修正建议（段落级）

| # | 位置 | 改法 |
|---|---|---|
| R1 | §1:15 | 删「（transform-broken 桶=约束证据）」→「（仅 A 有簇=Hex-Rays 约束证据；transform-broken=B 轨变换缺陷，见 e2e-rules §3）」 |
| R2 | §3 ADR-1 行:59 | 理由列改「同一**注解源**双渲染（A 轨经 apply_annotations 直读、不经 plan）；转换层 bug 显式归 D4『管线』桶」 |
| R3 | §3 ADR-3 行:61 | 增补裁定句：「签名归一**单一权威=DataTypeOps 归一表**；批量/增量两通道必须共用同一归一层（或 apply_plan ArrayList 形显式标注为过渡实现+parity 测试钉住两通道读回一致）；`__fastcall` 不得静默落 `__cdecl`」 |
| R4 | §3 ADR-4 行:62 | 「唯一验收口径」→「fixture 四钉=用例层唯一验收口径；M2 全量差分/M3 登记册另行定义验收」 |
| R5 | §3 ADR-2 行:60 | 附则补「探针纪律：pyghidra 探针只开 readOnly=True 或必须 `proj.close()` 收尾后退出；无收尾退出=毒化 `~index.dat`（现场实证）」 |
| R6 | §4.1:71-77 | (a) 语义清单补「structs.`methods` 消费（方法签名并入 set_func_sig）」；(b) plan op 增 `schema_version` 字段；(c) 测试锚补「覆盖率硬门槛（spec:95）」与「apply/daemon 双通道签名 parity 测试」 |
| R7 | §4.2:83 | 「签名（经 4.3 的代理或本地 ArrayList 形）」→「签名（经 ADR-3 单一归一层）」（修正交叉引用）；职责末补「未知 op kind **fail-loud**」；「验证合体 decompile 抽样」移出批量通道职责（→消费面按需） |
| R8 | §4.2:84 | 补增量/重建分界判据（例：单 plan ≤N op 走增量、结构签名批改/换 bin/损坏走重建）与 plan diff（只重放变更 op）为 M2 优化项 |
| R9 | §4.3:93-94 | 预设句补：「preset 由 `transformGhidraCode({preset})` 选择（`packages/cpp-parser/src/ghidra.ts:144`），run.ts 现不透传 ⇒ M1 补 `--preset` flag 或 GHIDRA_PRESET env，命令行示例带 quick/full 两条」 |
| R10 | §4.4:99-101 | (a) D1 恢复 rules 三件+持久化=四件（补「注解 size=layout」检查）；(b) D3 补机制句「fresh-session 重渲染：apply 落盘→**新进程** re-decompile→以 fresh 侧供判（ADR-5）；`this->` 达成=形参命名强制+读回归一（`param_N->`≡`this->` 须显式声明为等价形并入 render.json 归一）」；(c) D2 补「桶分类=白名单式精确匹配+**未分类桶=FAIL**+错误条文入 report；白名单准入附理由字段（台账）」 |
| R11 | §4.5 表 | L-persist 行补探针收尾（见 R5）；L-lock 行补检查点「run_e2e 入口：`.gpr.lock` 存在⇒ 清会话/报 FAIL」；L-rebuild 行补触发判据「create_session 报 Program not loaded / `~index.dat` 残留 / 残锁 ⇒ 清 `.gpr`+`.rep` 全重建」；L-assert/L-no-self-kill 行补工具化（safe_patch/proc_cleanup helper） |
| R12 | §5 目录 | 补三件：`ghidra_track/make_plan.py`（plan 生成器，吃 methods）· `ghidra_track/diff_tracks.py`（差分器+`dual_track_m1_diff.json` schema）· report.json schema 一行注；ghidra_proj 注明「按 case 分 program 名或分项目」；清理 ghidra_proj2/3 残留 |
| R13 | §6:141-143 | M1 行头部改「M1 重定义（相对 spec:86 修订：切片差分→case-01 四钉+切片差分双收口）」或补回「切片双轨差分清单落档+逐条溯源」；四步改五步：**⓪~index.dat/残锁清扫（L-rebuild 触发）**→①→②→③→④⑤ |
| R14 | §6:147 | L2/L3 补回「枚举/模板实例/尾合并」；加「PAL3 难点映射」注（COMDAT 折叠/调整 thunk/CRT 边界/模板特化桥接/成员函数指针/__usercall 各挂 case 计划） |
| R15 | §6:150 | 「plan 重放（秒级）」→「plan 生成（秒级）；批量重放分钟级（M2 规模估 15-90 min/轮，见风险表）；增量通道秒级（M2 起）」 |
| R16 | §8:170-173 | ①判据补 D1②与 D2 未分类桶=FAIL；②补回 spec:103「每条差异可溯源（错误码/单元/**函数级**锚点——行级跨轨不可对齐须改口径）」；④改为可检验陈述（逐条列检查点命令） |
| R17 | §7 风险表 | 增行「D2/D3 判据自损（缺件/陈旧件）」止损=判据修先行；增行「批量通道单轮闭环超时盒」 |
| R18 | §9 表 | 补三行：`~index.dat` 毒化清单→L-persist 附则/L-rebuild 触发 · `ghidra_isms.h` 缺件致 D2 假红→D2 判据自检 · slice 陈旧件混判→run_e2e 清场 |

---

## 5. 未复验（本复核未覆盖/未重跑项）

| # | 项 | 状态 | 说明/建议 |
|---|---|---|---|
| V1 | case-01 全链重跑 | **未跑**（跑链会写 report.json/ghidra_proj，超出「只写本文件」授权） | 盘上 `report.json`（18:06）显示 D1 sizeof=BLIND/persistence=FAIL、D2 FAIL、D3 2 红——与转述「D1 三件绿」**不一致**；`apply_report.json`（较新）示 `sizeof_mismatch={}` 但 member_hits `this_hits` 全 0。转述的绿可能产自 18:48 修复后未落档的手工读数。按「不准确=不判定」：D1 三件绿**待重跑落档后才算数** |
| V2 | fresh-session `param_1->` ×4 / `this->m_flags` 尾钉未收 | 转述现场，未复跑 | 同会话 slice/update.c:9 显示 `*(int *)(this + 0x38)`（更差）——两种会话态的差异机理（形参名丢失 vs 类型传播）未定谳，建议列入 G2 修法的前置实验 |
| V3 | daemon「Program not loaded: fixture」 | 未起 daemon 复现 | 与盘上 `~index.dat`×3+残锁并存互证，机理采信现场定谳；清扫后应复测 create_session |
| V4 | M2 量级估计（15-90 min/轮） | 分析估，未实测 | 建议 M2 前用 plan_m1_slice.json 真切片计时一轮（decompile 双遍是主要变量） |
| V5 | set_prototype 批量 2000 函数性能 | 未实测（ADR-3 问题前半是假设性） | 实测结果决定 G7 修法选「统一走归一层」还是「批量通道=显式过渡实现+parity 钉」 |
| V6 | `analyzeHeadless -import` 对已存在程序的跳过/重导语义 | 未实测 | G9 的关键分支；一次实验可定谳（决定多 case 隔离形态） |
| V7 | Ghidra thiscall 首参命名保留/丢失的确切机理 | 未实测 | `replaceParameters(DYNAMIC_STORAGE_FORMAL_PARAMS)`（apply_plan.py:124）与 `setCallingConvention`（:126）时序嫌疑；影响 G2 修法 |
| V8 | 前次复核 U1-U8 | 多数仍未收（U5 本复核已定谳=G3；U6 未执行=G19） | 建议随 M1 修订批一并清账 |

---

*复核方法：全文逐行读 + 现场只读取证（git/文件系统/grep/diff/盘上产物核对）+ 交叉三方文档一致性核对。
全部结论带锚点；无锚点的推断（V4 量级）已显式标注为估计。*
