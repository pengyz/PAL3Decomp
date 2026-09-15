# PAL3 清理工作 — 上下文交接文档

> **用途**：本文档用于**上下文切换**。前一个会话的被作废，接手者只需读本文档 + 下列"产物索引"里的文件即可继续，无需重读历史对话。
> **生成时间**：2026-09-15 15:20 (+08:00) · **仓库**：`/home/peng/workspace/PAL3Decomp` · **HEAD**：`9cb436305`
> **校验**：本文档中所有数字均为生成时刻的实测值（来源命令写在括号里）。

---

## 1. 目标与背景

**项目**：PAL3 匹配反编译。目标是用 MSVC 6.0 SP0 编译出与 `original/PAL3.exe` **字节匹配**的源码。第一优先级是**字节匹配**，不是代码优雅。

**本轮目标（用户原话）**：整体性扫描是否存在架构问题、现存待清理问题（**特别是已明确标记 misattribute 的历史残留**），逐条**明确并修复**。

**工作分两阶段**：
- **扫描阶段（已完成，队伍已归档）**：三路并行扫描 codegen 标记/残留、misattribution 历史残留、架构与基建，产出分级清单。
- **执行阶段（进行中）**：按裁决批次逐条修复 → 独立验证 → 独立复核 → 整合落地。

---

## 2. 当前状态快照（生成时刻实测）

### 2.1 仓库与三层一致性

| 项 | 值 |
|---|---|
| HEAD | `9cb436305`（未提交任何修复；全部改动仍在工作区） |
| 受管文件已修改 | **8** 个（3 个注解 struct + `CHANGE_LOG.md` + `baselines/latest.json` + `pal3_registry.jsonl` + `s4_baseline.json` + `.agent-teams/retired-members.json`） |
| 未跟踪文件 | **23** 个（扫描/修复产物，见 §6） |
| 三层一致性 | **现已一致**：工作区注解 → IDB（`.i64` 15:14:42）→ decomp（15:08:35）→ `pal3/src`（15:10:13）。**这意味着当前基线数字可信、可比。**（此前有过"工作区未修复 / IDB 修复态 / pal3/src 由修复态 IDB 生成"的三层分叉，已通过后续 apply/export/codegen 消除。） |

### 2.2 基线数字（权威）

| 指标 | 值 | 来源 |
|---|---|---|
| S2 编译 | **ok = 53 / 198**（fail 145） | `data/status/baselines/latest.json`（name `20260915_151121`） |
| 字节匹配 L1 | **5**（棘轮 `previous 5 -> current 5`） | `data/status/s4_baseline.json` → `stats.match_L1` |
| matched / partial / unmatched | **123 / 118 / 52**（symbols 175） | 同上 |
| oob（越界成员导致的尺寸错误） | **0**（本轮修复前未清零） | 同上 → `stats.oob` |
| apply struct 导入 | **881/881 (fail=0)** | `pipeline/ida/_logs/apply_annotations_log.txt` → `[3]` 行 |
| 错误总数 | **3089** | `baselines/latest.json` results 汇总 |
| 错误码 top | C2660 **706** · C2664 498 · C2440 291 · C2039 236 · C2059 205 · C2227 143 · C2100 106 · C2065 82 | 同上 |

> **验收硬线（不得回退）**：`L1 ≥ 5`、`ok ≥ 53/198`。**分母 198 变化即判不可比**。

### 2.3 标记计数（当前 `pal3/src` 树，供修复前后对照）

```
[VFTABLE] 1935   [VFTABLE-STUB] 614   [AUTO-COMMENTED] 233   [MISATTRIBUTED] 344（343 行）
[ROWTABLE] 576   [IDA_MISID] 84       [IDA_VTABLE] 1（仅在 .h）   [IDA_VFTABLE] 0（死发射分支）
```
四种拼写**不可合并计数**。注意 `[VFTABLE]` 在 10:39 那次未授权重生成前是 1643、之后是 1935 → **引用旧数字一律作废**。

---

## 3. 已完成（DONE）

### 3.1 扫描阶段（队伍 `cleanup-arch-scan` 已归档）

| 任务 | 产物 | 内容 |
|---|---|---|
| 分类学/证据门槛/验收口径 | `docs/specs/2026-09-15-cleanup-scan-taxonomy.md`（353 行） | 四类 C1–C4 + G1–G4 判定闸门；证据分级 **A–E**（A=指令级 reg+disp32/绝对地址）；14 字段清单契约 |
| codegen/管线残渣扫描 | `data/status/_cleanup_scan_codegen.json` | 25 条目 + 9 缺口（前缀 CG-） |
| misattribution 历史残留扫描 | `data/status/_cleanup_scan_attribution.json` | 212 条目 + 12 缺口（前缀 AT-） |
| 架构层扫描 | `data/status/_cleanup_scan_architecture.json` | 27 条目 + 10 缺口（前缀 AR-） |
| 架构裁决书 / 产物清单 | `docs/specs/2026-09-15-cleanup-scan-architecture-rulings.md`、`…-attribution-artifact-inventory.md` | 红线裁决 (a)(b)(c)(d)(e)、四份产物可采信度 |
| **t5 汇总裁决** | `data/status/_cleanup_scan_triage.json` + `docs/specs/2026-09-15-cleanup-scan-triage.md` | **268 条目 + 31 缺口**，四批次，规则化裁决，**自洽校验全过**（C3 226==226、C4 4==4、`FIX_*`@C/D/E=0、`NEED_EVIDENCE` 缺 proof=0） |
| 独立复核（t3 三条承重结论） | `data/status/_cleanup_verify_scan_claims.json` | 空集/108-159/AT-022 字节三条 **CONFIRMED**，无反例 |

**t5 四批次**：**B1 可立即修注解 = 4**（→ 已完成）· **B2 可立即修管线/codegen = 23**（→ 待办）· **B3 需补证 = 200** · **B4 应删除 = 14** · **B5 有意保留 = 27**。

### 3.2 B1 批次（3 个 UDT）——**已全部修完并验证** ✅

| struct | 改动 | 证据 | 验证（实测） |
|---|---|---|---|
| **SceneObj** | 删偏移 **18804/18808**（`m_nSpringTargetX/Y`）；`binary_size` 保持 1784 | P1 `check_annotations` 自报 `extend to +18812 > 1784`；P2 两条 `source` 自证来自 `CCBRoleState::UpdateEffects`；P3 `CCBRoleState` 已有同名同偏移（零信息损失）；**P4 A 级** `fst dword ptr [esi+4974h]`（`CCBRoleState::CalcSpringForce` 0x449F00，`mov esi,ecx`=this） | `apply_status`: 47 成员 / 1784 / `ok`；`CG_Scene`+`Scene` 两条 FATAL 消失 |
| **UICursor** | `binary_size` **32 → 64** | **A 级**：`UICursor::Update` 中 `esi=this` 访问到 **+0x3E** | `apply_status`: 6 成员 / 64 / `ok` |
| **SaleUI** | 删 **35** 个结构性不可能成员（101→66）；`binary_size` 保持 **105912** | 批A 34 条：偏移 ≥105912（几何不可能）+ 约 10 条源自已解散的旧 `PlayerMgr.json`(107056)；批B 1 条 `ml_SmeltList@104752`：末端 105960 > 105912，且其位移 `+19930h` 的 3 处 asm 访问**全在 LineupUI 方法内**（`0x477BB0 LineupUI::OnMessage`、`0x471590 LineupUI::InitListView`）→ 不属 SaleUI | `check_annotations` 对 SaleUI **零错误**；`apply_status`: 66 成员 / 105912 / `ok`；两条 overlap 一并消解 |

**判据核对**：`[3] Structs 881/881 (fail=0)` ✓ · **L1=5 ≥5** ✓ · **oob=0** ✓ · **ok=53/198** ✓。

**产出**：`data/annotations/CHANGE_LOG.md`（新增两条完整条目：证据→改动→验证）· `data/status/_cleanup_fix_attribution.json` · `data/status/_cleanup_fix_saleui.json`。

**重要方法学留痕（必须继承）**：
- "位移在 asm 出现 0 次"这条**负证据判别力很弱**：界内成员中也有 **50/67** 位移为 0 次（基础发生率≈75%）。**决定性依据是几何不可能 + 出处可追**。
- "`binary_size` 偏小"假设（对 SaleUI）**无正证据**：若成员真属该类，其位移应被该类的 this 访问；实测为 0 或归于他类 → **未采用放大尺寸的做法**。

### 3.3 本轮新登记的遗留发现（**未修**，转"需补证"）

1. **`LineupUI.binary_size = 1208` 疑小约 100 倍**（高）：其方法访问到 **+124248**（`~LineupUI` 自标 `_misattrib_evidence: max_offset=124248>class_size=1208`；`OnMessage` 0x477BB0 / `InitListView` 0x471590），与 `0x1E56C`=124268 分配点线索同量级。**此前未被发现。**
2. **`UIListBox.binary_size = 1208`** 与 LineupUI 同值、疑同源（中）。
3. **`SaleUI` `ann_members=66` vs `ida_members=63`**（3 条未被 IDA 建入，疑 union variant 键/重复偏移）（低）。
4. **`g_RoleSlotBuf ⊂ g_SceneMgr`** globals overlap —— 需加 `overlaps_with` 声明（低）。

---

## 4. 待办队列（TODO）

**执行顺序**（串行窗口，由依赖强制；每步一个执行单元）：

```
t3 导入器显式失败 → t4 export 红线 → t5 门禁与基建 → t6 codegen 双轨
   → t7 破坏性注释恢复 → t8 死门禁与吞错 → t9 独立验证
   → t10/t11 两路复核 → t12 整合落地
```

> **窗口规则**：`apply`/`export`/`codegen`/`probe`/`match` 会写共享产物（`pal3/src`、`asm/pal3/decomp`、`data/status/probe_census.json`、`baselines/`）→ **同一时刻只允许一个执行单元跑，开始与结束都要通报**；读者在窗口内先 `cp -r` 快照到 `/tmp` 再分析。

### t3 — 导入器显式失败（`pipeline/ida/apply_annotations.py`）
**根因链（已定谳，勿重新调研）**：成员偏移/末端越界 → `create_udt()` 仍返回 true 但产出**不完整 UDT**（`get_size()==-1`、`get_udt_details()==false`）→ `:866-877`（TAUDT_FIXED）**无条件**把 -1 降级成 `actual_size=binary_size` → `:888` `set_named_type` 静默失败留下空壳 → `SceneObj[256]` 取元素尺寸得 -1 → `:797-800` 报 `invalid member_size` FATAL。
**要求**：
1. 判据用 **`get_udt_details()` 成功 + 实际落入成员数 == 期望推入成员数**（**不要**"见 `get_size()==-1` 即 fail"——`:867-868` 注释承认 union 同偏移变体时 -1 属正常现象）；
2. 保留独立前置检查 **`member_end = 声明偏移 + 成员解析尺寸` > `binary_size`**（**末端口径**；偏移口径会漏掉 SaleUI 那类"末成员尺寸撑破边界"）；
3. **统一 `:654-656`（diff-mode，正确拒绝 -1）与 `:866-877`（无条件降级）** 的行为；
4. 报错同时打印 **`offset / member_end / binary_size`** 三元组 + 输出**可操作不完整清单**；
5. 提供**逐 struct 留痕覆盖**开关（**默认拒绝 apply**），每次覆盖都要记录"该 struct 已登记为已知待修"。
**判据**：现在 3 个 UDT 都已完整 → **本改动不应改变任何计数**（881/881 保持）；`L1 ≥ 5`、`ok ≥ 53/198`；`.i64` mtime 必须刷新。
**注意**：`pipeline/ida/_logs/apply_status.json` **不是 `apply` 写的**，由独立 IDAPython 脚本 `pipeline/ida/check_apply_status.py` 生成（`idat -A -S"pipeline/ida/check_apply_status.py" original/PAL3.exe.i64`，用完确认无残留 idat）。
**交付**：`data/status/_cleanup_fix_struct_import.json`。

### t4 — export 红线（`pipeline/ida/export_full.py`）
`export_full.py` **9 处**直接读 `data/annotations/`（`:150/:159/:200/:213/:216/:281/:485/:688/:718`；`:148` 注释自称 "authoritative source for signatures"），违反 CLAUDE.md「**export 不读 annotation**」，且 `docs/knowledge/MEMORY.md` 的 `## Decisions` 段**为空**（无取舍记载）。
**出口二选一**：(a) 等价重构（只从 IDB/apply 产物取数）+ 导出结果**等价性证明**（计数对照/diff）+ 全链不回退；(b) 证据充分的"有意取舍" → 决策页交 t12 落盘到 `docs/knowledge/`。
**边界**：不改注解；不做与红线无关的重构；若必然连带其它模块，先回报。
**交付**：`data/status/_cleanup_fix_export_redline.json`。

### t5 — 门禁与基建（含发行阻断项）
1. **坏符号链接（发行阻断）**：`data/status/baselines/latest.json` 索引 mode **120000** 但其 blob 是 **462044 字节的完整 JSON**（非路径串）→ `git -c core.symlinks=true clone` **exit 128**（`文件名过长`）、克隆后**该路径不存在**；它指向的 `20260915_100946.json` **未入库**（dangling）。**修法**：改成 **100644 普通文件**，正文用真实 baseline JSON（坏 blob 与已跟踪的 `20260915_075701.json` **逐字节相同**，sha256 `37c360fc…`，零信息损失）；并修产生路径 `tools/regression_detector.py:120-128`（把符号链接分支改为一律写普通文件）。
   **判据（合取式，四项全过）**：① `git ls-files -s`=**100644** ② `git -c core.symlinks=true checkout-index -f --prefix=/tmp/x/ -- <path>` **exit 0** ③ `git -c core.symlinks=true clone -q --no-hardlinks . /tmp/c` **exit 0 ∧ 该路径落成普通文件（`stat -c %F` 非 symbolic link）∧ `json.load` 成功** ④ `git archive HEAD | tar -x` 无错解出。**防复发**：修完跑一次 `probe s2` 再确认仍为 100644；收尾**撤销本检出为绕过该缺陷所设的 `git config core.symlinks false`**，用默认配置复验（**靠本地配置兜住的"通过"不算通过**）。
2. `tools/audit_layout.py:59-63`：缺 `asm/pal3/ida_structs.json` 时 `WARN`+`return {}` → 比对**静默跳过** → **exit 0 假通过**（改为显式失败，区分"缺前置产物"与"真零问题"）；`:200-205` 的 `binary_size != ida_size` 与**同源 TIL** 比对属**循环**（恒等通过）→ 修其循环性。
3. `tools/compile_regression.py`：棘轮基线 `data/status/compile_baseline.json` 冻结在 **2026-09-01（204 文件/58 ok）** vs 当前 **198/53** → 恒定 REGRESSIONS/exit 1（**已失去探测能力**）→ 刷新或加棘轮。
4. `pipeline/decomp_quality.py:110`：判据 `max(offsets) > cls_size * 2` 与注释语义不一致 → **收紧到 `> cls_size`**（实测 7→**17** 个函数；**属恢复探测能力、不算回退**，须给"修复前静默通过 / 修复后被标记"对照，至少覆盖 `gbVFileSystem`、`SoundMgr`）。
5. `pipeline/cli.py`：`:315-320` apply 失败**无 `sys.exit`**（破坏 `&&` 链）→ 非零退出；`:375-386` 后置钩子**不检查 returncode** → 检查并传出（不吞错）；`:607-610` `iterate` 指向**不存在的模块** → 修或标注不可用。
6. `pipeline.toml` 缺失时（设计上 gitignored）顶层 import 未捕获 → 裸 traceback（`config.py` 已有合格 ConfigError）；`pipeline/compare_pal3.py:243` census 读取无守卫；`tools/annotation_diff.py` 无法区分"无变更"与"读不到 git"（git 不可用时把 **898** 个结构体全报为新增且 exit 0）。
7. **85MB** `original/PAL3.exe.i64.polluted.bak`：**已跟踪**（`git cat-file -s`=85833047，来自提交 `0d1294b0e`）→ **仅 `git rm --cached` + 补 `.gitignore`**（**工作区文件保留**、**不重写历史**、提交留 t12），并产出**已跟踪 >10MB blob 清单**（只报告）。仓库根空文件 **`__vftable`**（tracked/0B/无活跃产生路径）删除。
8. `tools/vc6` 的 **1258 条小写 shim** 是刻意的 Linux 大小写适配（**保留**），但**无存在性门禁** → 加前置检查（指向 `tools/setup_wine_vc6.sh`，响亮失败、不静默兜底）。
9. **IDB 可复现性**：写入 `docs/decompilation_workflow.md`（从 raw IDB 重建的最小路径 + "apply 真成功"的观测点）。
**判据**：`L1 ≥ 5`、`ok ≥ 53/198`（门禁变严导致的指标下降不算回退）。
**交付**：`data/status/_cleanup_fix_infra.json` + `docs/decompilation_workflow.md`。

### t6 — codegen 证据门控双轨（`pipeline/gen/ast_transform.py`）
**轨道 1 = 严格 3 个站点**：`pal3/src/Combat/CCBAI.cpp:246/444/646` → `AStarPathFinder::GetHeuristicIdx`（VA **0x4014F0**）。**实现口径必须是 `(ret-N 闸门通过) ∧ (callee 占 vtable 槽)`**——实测**只加 ret-N 闸门会放行 234 个站点**（违反"其余不动"），加该条件后恰 **3 个**（预期 `[MISATTRIBUTED]` **−3**，`[ROWTABLE]` **不变**）。
**根因是分支覆盖缺口**：`_ret_param_slots()` 只在 `pointer_expression` 分支被调用（`:477-487`），`(T*)this` 走 Branch B **从不查阅逐被调方二进制证据**。
**3 站点的证据**：`0x4014F0` 原字节 `32 C0 C2 08 00`（`xor al,al; retn 8`，3 字节桩）；真实指令序列**恰 2 个参数**（`push edi / push ebx / mov ecx,esi / call sub_4014F0 / test al,al / jnz`）与 `retn 8` 一致，生成源码渲染成 3 参 → **C2660 是 decomp/IDB 侧渲染产物**；**`C2352 = 0`**（该形态自称的"精确信号"从不出现）；`CCBAI.bases=[]` 且 `CCBAI.vtables=[]`（无继承）；vtable `0x56A600` = `[0x401030, 0x4014E0, 0x4014F0]`。
**轨道 2**：其余约 335 个站点**一律不动**；**文件级 blanket 反转未经用户授权不得实施**（AR-016 保持 DOCUMENT）。
**同任务内还要做**：① **判定顺序翻转**：逐站点证据门控（口径：该 VA 被 **≥2 个类**的虚表 slots 持有才走行表形态；实测 6 支持/3 不支持 → 后者保持现状记 `GAP-ROWTABLE-PRECEDENCE-01`），**必须显式排除 ctor/dtor**（否则凭空造 **17** 个假 `[ROWTABLE]`）；② **AR-002 只声明不迁移**：`:52`(ret-N 证据源)、`:148`(类层次) 加显式声明注释（写明读什么/为何必须读/**为何当前不可迁移**）+ 用 harness（驱动真实 `transform_oop_calls` 跑全部 **3594** 个 decomp JSON，纯内存）证明**零输出差异**；③ **CG-023**：`_rowtable_family()` 读不到文件时返回空集 → **588 站点 / 328 文件静默改判** → 改 `RuntimeError`；④ 该文件 5 个带类型 except（`:58/:83/:90` 保留+stderr 告警；`:117` **不删**、记 C3b 冗余）；⑤ 测试断言同步（`test_pipeline.py:99`↔`:353`+场景`:98`；**补 `:421` ROWTABLE 断言**；`:322/333`↔`:589-596`；`:260`↔`:562-563`；`__main__` L543-603；新增 3 站点断言）。
**AR-002 不可迁移的实测依据**（写进注释）：换 export 源 → `15/3594` 文件漂移（含"**静默放行**"危险方向）；pack-only → `169`；类层次源 → `1`；两者都换 → `16`；`84` 个 (cls,method) 闸门判据变化；pack-only 丢 **89.8%** 证据；`ida_structs.json.bases` 仅 `172/179` 且 7 条为空。
**判据**：`L1 ≥ 5`、`ok ≥ 53/198`。
**交付**：`data/status/_cleanup_fix_codegen_policy.json`。

### t7 — 破坏性注释与硬编码模式表（`pipeline/gen/stages/stage3_cleanup.py`）
- `[VFTABLE]` 发射在 `:722-749`（`:722-743` 按括号深度整段注释、`:745-749` 正则注释残留单行）；**仅约 2.5% 是真 vptr 存根**；其余形状：控制流头（if/while）约 168、真实数据访问约 546、`__vftable` 当数据值 163、cast 44。
- **铁证锚点**：`CCBCamControl.cpp:972-975` 是**未注释**的 float 写入（`-1098907648`=0xBE800000、`1065353216`=0x3F800000=1.0f），而 `:983-986` **同类模式**经 `__vftable` 访问后被注释；`CCBParabolaWindow.cpp:45-46` 整条 `if (v5->__vftable) { Release(); }` 被注释。
- `[AUTO-COMMENTED]`（233）中 **89 处丢弃被使用的赋值**（例 `CCBStage.cpp:868` 的 `Color = v22.gbColorQuad(...)->Color;`，其后仍在用该值）。
- `[IDA_MISID]` 84 处靠 **6 个硬编码模式表**（`:752-759`）绕开 IDA 层，抽到的是真实代码（`std::_Xlen();`、`ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;`）；子类 (i) 15 处（NtTib/ExceptionList，注释后留**悬垂引用**）、子类 (ii) 69 处（`_Xlen`/`_Xran`/Concurrency，decomp 无对应函数记录）。
- 死分支：`:287-290` 的 `'insert'`/`'comment_vft'` 无产生者（`[IDA_VFTABLE]` 实测 0）→ 删除或标注；该文件裸 except 逐处处置。
- **判据豁免（captain 特别裁决）**：本任务**不以 S2 ok 为判据**（恢复被误注释的真实代码必然暴露新错误）→ ① **`L1 ≥ 5` 不回退** ② 不得再有真实语义被注释 ③ 若 ok 下降，须逐条证明新错误来自**恢复的真实代码**。
**交付**：`data/status/_cleanup_fix_vftable_comment.md`。

### t8 — 死门禁/死发射分支/吞错（`emit_headers.py` + `data.py` + `stage5_fixup.py`）
- **恒假门禁**：`emit_headers.py:1948-1950`（`[IDA_USERPURGE]`）与 `:1951-1953`（`[IDA_REGPARAM]`）因 `:1882-1884` 先行剥离 `@<\w+>`/`__userpurge`/`__usercall`（`:1901` 还重复剥离）而**永不触发**（实测 0/0；溯源提交 `c37802092`）→ 删除死分支**或**修正判据使可达，并说明原意（"签名无法表达时不发射声明"）→ **不得以放宽检查方式"修好"**。
- `[IDA_VFTABLE]` 死发射在 `stage3_cleanup.py:289-290`（**属 t7 文件 → 只报判定，不越界改**）；`emit_headers.py:1945-1946` 的 `[IDA_VTABLE]` 是**活**的（.h 中 1 处，由 `vtbl_` signature 恰好 1 个 1:1 触发）。两者拼写/语义不同，**不得合并计数**。
- `data.py:218`：`except` 包住 `json.load` **加整个 for 循环**（`:193-218`）→ **一条坏条目即丢全部 139 条 thunk 映射**（10 个 thunk 名真的出现在生成 .cpp；S4 matched 命中 0/175）→ 改不静默。
- 失实断言：`data.py:226` 的 "ONLY place codegen reads from annotations"（另有 `:191 skip_functions.json`、`:262 globals.json`、`:374 functions.json`）与 `data.py:94` 的 "NOT from annotations" → 改为**如实的例外清单**。
- 死代码：`stage5_fixup.py:71/:101/:98`（dead-on-arrival，自引入提交 `28c00559` 起无引用；真正在用的是 `:108`）删除并写明重建理由；`emit_headers.py:110 OVERRIDES_DIR` 过期常量；4 个无引用 import。
- **裸 except 分级处置**（不放宽、不删检查）：**A 级必须可见**=`data.py:105`（吞 `ida_structs.json` 失败 → 整个 data store 静默退化为空）、`data.py:218`、`emit_headers.py:77`、`data.py:76`；**B 级逐对象吞+计数上报**=`data.py:235/267/295/309/378`、`emit_headers.py:43/547/651/1518/1532/2125`；**C 级收窄异常类型**=`emit_headers.py:743/985/1068/1080/1222/1419/1500/1559/1570`；**D 级**=`emit_headers.py:2993`（gb2312 best-effort，保留+理由注释）、`:3050`（**非吞错**，是有意义回退，保留但收窄）。
- **主证据法**（已批准）：monkeypatch `emit_headers.OUTPUT_DIR` → `/tmp` 并预置当前头文件做前后 diff，证明**逐字节中性**（已审计：全部写/删路径均派生自 `OUTPUT_DIR`；`data.py` 零写操作）→ 不写 `pal3/src`、不跑 probe。
**判据**：`L1 ≥ 5`、`ok ≥ 53/198`。
**交付**：`data/status/_cleanup_fix_dead_gates.md`。

### t9 — 独立验证（全部修复落地后）
- **判据**：`L1 ≥ 5`、`ok ≥ 53/198`（分母 198 变化即判不可比）。
- **apply 诚实读数**：现阶段 3 个 UDT 已完整 → **t3 落地不应改变计数**；历史口径备查：只改导入器（注解未修）时期望 `879→876`/fail 2→5（**876/881 诚实**），注解+导入器同时落地 → **881/881 且诚实**。**盘上任何来自已不存在文件状态的 `apply_status` 不得当当前状态。**
- **必做**：逐条核验各修复声明的二进制证据 ↔ 最终代码/decomp 现象（不一致即失败+反例）；`git status` 变更须全在声明 inScope 内（声明外点名）；**退出码一律 `PIPESTATUS[0]`**；apply 前后核对 `.i64` mtime（**注意：`.til/.nam/.id0-2` 边车只在 IDA 非正常退出时残留，"边车存在=上次崩过"，不是常规指纹**）；开工前记录被改文件 mtime+sha256；**门禁变严不算回退**（`decomp_quality ×2→×1`：7→17；`audit_layout` 假通过→显式失败；`compile_regression` 基线刷新）但须给正向对照；t7 适用其**判据豁免**。
- **发行判据合取式**：同 t5 的四项（修复前实测 clone exit **128**、路径不存在）。
- **窗口**：必须独占（不得与其他 export/codegen/probe 并发）；等 t8 通报"IDB 已释放 + 语料已重建"后开始；开始与结束都通报。
**交付**：`data/status/_cleanup_verify_fixes.json`。

### t10 / t11 — 两路独立复核
- **t10 复核注解路**（SceneObj/UICursor/SaleUI）：证据充分性（A 级门槛）、是否引入新矛盾（`check_annotations` 新增错误/布局越界/overlap/伪语义命名/破坏性 workaround）、**零信息损失**（SaleUI 删除是否逐条有据、是否**显式回应**"尺寸偏小"竞争假设；SceneObj 是否**未**放大尺寸；UICursor 是否走改尺寸而非删成员）、针对**最新实现状态**裁决、`needs_revision` 须给结构化 findings。
- **t11 复核管线/codegen 路**（t3–t8）：t3 是否用 `get_udt_details()`+成员数、末端口径、两路径真正统一、留痕覆盖默认拒绝；t4 的等价性或取舍证据；t5 合取式四项 + `git archive`、门禁**只加强未放宽**、85MB **仅去跟踪**（未删工作区文件/未重写历史）、`backup` 分支与 stash **未被删除**；t6 轨道 1 **严格只有 3 站点**、虚 callee 保留 `Cls::`、**排除 ctor/dtor**、`data.py` 断言已改；t7 只允许真 vptr 存根走注释路径且豁免被正确适用；t8 恒假门禁**删除或修正为可达**（严禁放宽"修好"）；**AR-016 检查**：是否有未授权的文件级 blanket 反转。
**手段限制**：只读 + `/tmp` 副本；**不得**启动 IDA、不得跑会写共享产物的命令（需这些读数的结论标"待 verifier 窗口"）。
**交付**：`data/status/_cleanup_review_attribution.json`、`_cleanup_review_pipeline_codegen.json`。

### t12 — 整合落地与总账
1. **基线更新**：`data/status/baselines/*`、`s4_baseline.json`、`pal3_registry.jsonl`、`error_classification.json` 与权威实况对齐并**纳入版本控制**；写清 apply 两种诚实读数；标注**旧树计数作废**（`[VFTABLE]` 1643 等）与权威计数已重取。
2. **冻结/证据类入版本控制**（当前多 untracked，`git clean -fd` 会清掉）：`baselines/verifier_prefix_s2.json`、三份 `_cleanup_scan_*.json`、`_cleanup_scan_triage.json`、`_cleanup_verify_scan_claims.json`、`_cleanup_evidence_stub_call_4014F0.json`、`_cleanup_fix_*`、`docs/specs/2026-09-15-*.md`。总账**分区段列示**「冻结/基线类」vs「修复类」。
3. **执行 B4 删除批次（14 条）**：死路径/裸 except/仓库根 `__vftable`/`build_output.txt`+一次性 `.obj`（untracked，删除不产生 git 改动 → **不计入"已修复"计数**）；**85MB 仅 `git rm --cached`** + 补 `.gitignore`（**不重写历史**）+ 产出 >10MB 已跟踪 blob 清单。
4. **禁止删除**：`backup/local-line-20260904` 分支与 **10 条 stash**（同步前本地线 29 提交 + 会话工作的**唯一保存点**，远端任何分支都不含它；stash drop 不可逆）→ 列「有意保留」，删除须用户显式决策。
5. **知识沉淀**（≥5 条，写 `docs/knowledge/` 并更新 `MEMORY.md` 索引）：见 §5 的规律清单。
6. **export 红线决策页**（若 t4 判"有意取舍"）→ 落盘到 `docs/knowledge/`。
7. 产出 `data/status/_cleanup_scan_ledger.json`：按 已修/已删/有意保留/需补证 四类计数，且与 `_cleanup_scan_triage.json`（**268 条目/31 缺口**）**自洽**。

---

## 5. 硬纪律与已知陷阱（**必须继承**）

1. **证据门槛**：偏移/类型修改最低需 **A 级证据**（指令级 reg+disp32 / 绝对地址）；归属修正需 **decomp member access evidence**（成员在目标类存在且不在原类）；**禁止猜测性修改**；**禁止批量未验证修改**；**禁止伪语义命名**；**禁止破坏性 workaround**（不用 `void*`/`int` 掩盖真实类型）。
2. **退出码**：一律 `PIPESTATUS[0]` 或紧跟命令取 `$?`。**`cmd | tail` 会让 `$?` 变成 tail 的退出码**——本会话已因此误判两次（一次把 clone 128 读成 0）。
3. **破坏性 git 操作**：**不得**对受管文件执行 `git checkout --` / `git restore` / `git stash`（须先经用户批准）——本会话已因此**两次销毁未提交的工作**（一次是 captain 回退未 claim 的编辑，一次是子 agent 脚本事故后自恢复）。需要"干净基线"时用 `git show HEAD:<path>` 或副本目录。
4. **IDB 单写者**：同一时刻只允许一个执行单元触碰 `original/PAL3.exe.i64`；**边车 `.til/.nam/.id0/.id1/.id2` 只在 IDA 非正常退出时残留**（"边车存在=上次崩过"），干净退出会删除；只核 `.i64` mtime 不足以证明"没人开过库"。
5. **窗口串行**：共享产物（`pal3/src`、`asm/pal3/decomp`、`probe_census.json`、`baselines/`）的写入必须排队；**生产者开始/结束都要通报**；读者先快照。**一次未通报的重生成（10:39）把全队计数基线全部作废过。**
6. **union variant 成员没有 `offset` 字段**：`known_members` 的键形如 `12_1` = `偏移_变体`，真实偏移是**前缀**；**绝不要 `int(key)`**——Python 3 把 `_` 当千位分隔符，`int('12_1')` = **121**（本会话据此产生过一次"6 个越界 struct"的假结论，真值 3 个）。
7. **`asm/` 整树被 `.gitignore` 忽略**（`:119`）→ 基于 `asm/pal3/decomp`、`ida_structs.json` 的结论**只在本工作副本可复现**；干净检出须先跑 IDA 导出。
8. **不得 `git clean -fd`**（会清掉未跟踪的冻结证据）；**不得删除 `backup/local-line-20260904` 与 10 条 stash**。
9. **`apply_status.json` 不是 `apply` 写的**，由 `pipeline/ida/check_apply_status.py` 单独生成 → 判断 apply 是否真实生效要看 `.i64` mtime + `apply_annotations_log.txt` 的 `[3] Structs` 行，不要只看这个文件（它有可能是上一轮的陈旧值）。
10. **负证据（"位移在 asm 出现 0 次"）判别力弱**：界内成员中也有 50/67 为 0（基础发生率≈75%）→ 只能作支持证据，决定性依据是几何不可能 + 出处可追。
11. **`binary_size` 有两个方向相反的缺陷族**：**A 族（撑大）** `>3×`=**52** 个、`>50×`=**10** 个（含 `gbVFileSystem` 917972/24、`SoundMgr` 918796/848）——测法是 `binary_size > N×max(member_offset)`，可用分母 **819**（898 个 struct 中 79 个无分母：77 个空 `known_members` + 2 个无可解析偏移）；**B 族（越界）**=3 个（SceneObj/SaleUI/UICursor，**已修完**）。两者不可混谈。
12. **AgentTeams 机制在本运行时是坏的**：成员派发只累加 attempt 而不 spawn（旧队 8 个会话 `[diagnostic: corrupt]`；新队 `cleanup-arch-fix` 已批准但 6 名成员始终 `idle/unspawned`、t1 attempt 累到 12）。**改用普通子 agent**（`subagent_kiro` 可用），并且**必须审计子 agent 的产出**——有一个子 agent（`subagent-3`）**实际跑完并改了注解，却既没注册成 job 也没有报告**。

---

## 6. 产物索引

| 路径 | 内容 |
|---|---|
| `docs/specs/2026-09-15-cleanup-scan-taxonomy.md` | 分类学（C1–C4 + G1–G4 闸门）、A–E 证据分级、14 字段契约 |
| `docs/specs/2026-09-15-cleanup-scan-triage.md` | t5 裁决摘要（129 行） |
| `docs/specs/2026-09-15-cleanup-scan-architecture-rulings.md` | 架构裁决 (a)–(e)：codegen/export 读红线的判定、"有意取舍"要求 |
| `docs/specs/2026-09-15-attribution-artifact-inventory.md` | 归属产物清单与可采信度 |
| `docs/specs/2026-09-15-cleanup-scan-t5-rules.md`、`…-t5-rules-addendum.md` | t5 消费侧强制规则（最小合格清单 10 项） |
| **`data/status/_cleanup_scan_triage.json`** | **t5 汇总裁决主产物**：268 条目 + 31 缺口、四批次、`rules` 字段记录规则、自洽校验、全局 caveat |
| `data/status/_cleanup_scan_codegen.json` | codegen 扫描 25 条 + 9 缺口（CG-） |
| `data/status/_cleanup_scan_attribution.json` | 归属扫描 212 条 + 12 缺口（AT-） |
| `data/status/_cleanup_scan_architecture.json` | 架构扫描 27 条 + 10 缺口（AR-） |
| `data/status/_cleanup_verify_scan_claims.json` | 扫描阶段独立复核记录（含哈希钉、VF-1..4 措辞修正） |
| `data/status/_cleanup_evidence_stub_call_4014F0.json` | 桩槽案证据包（0x4014F0 四项 A 级证据 + repro 命令） |
| `data/status/_cleanup_fix_attribution.json` | SceneObj + UICursor 修复记录 |
| **`data/status/_cleanup_fix_saleui.json`** | SaleUI 逐条裁定表 + 4 条遗留发现 + 判据核对 |
| `data/annotations/CHANGE_LOG.md` | 逐条变更记录（证据→改动→验证）；本会话新增 SceneObj/UICursor/SaleUI 三条 |
| `data/status/baselines/latest.json` | 当前 S2 基线（`20260915_151121`，ok 53/198）——**注意它是索引里的坏符号链接条目，t5 要修** |
| `data/status/s4_baseline.json` | 字节匹配基线（L1=5、oob=0、matched 123/175） |
| `data/status/baselines/verifier_prefix_s2.json` | **冻结的修复前证据**（不得删除） |
| `pipeline/ida/_logs/apply_annotations_log.txt` / `apply_status.json` | apply 日志（`[3] Structs` 行）与逐 struct 状态（后者由 `check_apply_status.py` 生成） |

---

## 7. 恢复执行的具体步骤

```bash
cd /home/peng/workspace/PAL3Decomp
git log --oneline -1                      # 应为 9cb436305
git status --short | head -20             # 8 个受管改动 + 23 个未跟踪（见 §2.1）
python3 -c "import json;d=json.load(open('data/status/_cleanup_scan_triage.json'));print(d['counts']['by_batch'])"
                                          # 确认四批次计数与批次规则仍可用
```
然后**从 t3 开始**（§4），一个执行单元一步，**每步都跑完验证链并记录真实数字**：

```bash
python3 pipeline/cli.py check;      echo "check=$?"
python3 tools/audit_layout.py;      echo "audit=$?"
python3 pipeline/cli.py apply;      echo "apply=$?"
python3 pipeline/cli.py export;     echo "export=$?"
python3 pipeline/cli.py codegen all; echo "codegen=$?"
python3 pipeline/cli.py probe all;  echo "probe=$?"
python3 tools/error_classifier.py --summary; echo "cls=$?"
python3 pipeline/cli.py match;      echo "match=$?"
```
`apply` 后**必须**核对：`original/PAL3.exe.i64` mtime 刷新 + `pipeline/ida/_logs/apply_annotations_log.txt` 的 `[3] Structs: N/881` 行。

---

## 8. 未验证 / 不确定项（诚实清单）

1. **`LineupUI`/`UIListBox` 的 `binary_size=1208`** 是否真错（疑小约 100 倍）——需独立尺寸锚点（分配点 / 嵌入 span / 数组元素尺寸），**未验证**。
2. **`SaleUI` 的 `ann_members=66` vs `ida_members=63`** 差异原因未定（疑 union variant 键 / 重复偏移）——**未验证**，不影响 `size_match`。
3. **B3 批次 200 条 + 31 缺口**（需补证）**全部未处理**——逐条需要 IDA/MCP 取证（xref、干扰、真实类尺寸）。
4. **扫描阶段的三份清单计数基于 10:39 之前的树**（`[VFTABLE]` 1643 等），当前树为 1935；**部分清单内的站点级计数可能已漂移**，t5 已在 `caveats` 中声明作废，但**逐条重取尚未做**。
5. **`_cleanup_scan_attribution.json` 的 `subclass` 复合值**（如 `C3a/M1_callee_name`）违反 spec 单一取值契约，需在消费时**归一化**（新增 `m_code` 承载 M1/M4），并重跑 §5 计数自洽校验——**未做**。
6. **`C2352=0` 的口径**：本会话门禁跑动中从 1 掉到 0；修复落地后需**再次确认仍为 0**。
7. **B5（有意保留）27 条的解除条件**未跟踪（如 VC6 shim 的解锁条件、`_rowtable_family.json` 白名单的 provenance 缺口）。
8. **`git archive HEAD | tar -x` 与干净克隆目前仍失败**（t5 未做）——任何"干净检出可用"的结论在 t5 落地前都不成立。