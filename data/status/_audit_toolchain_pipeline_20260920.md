# 工具链与管线整体审计（2026-09-20）—— 4 维度多 agent 分析 + 交叉复核

**方法**：4 个只读子 agent 分别审「工具集清单/重叠/失效」「管线阶段与架构」「工作流闭环完备性」
「证据与判据体系」；主 agent 对其**后果最重的论断逐条独立复核**（逐字节比对、命令复算），
并**自行验证了两次事故的回滚**。基线：`git rev-parse HEAD` = 8d6db0048（审计期间）。

## 0. 审计期间的两起操作事故（均已回滚，主 agent 已验证）

两个 agent 都用 `--help` 探测工具可运行性，而**这些工具没有 argparse、把 `--help` 当普通参数执行并写盘**：

| 工具 | 被改写的受跟踪文件 | 改动幅度 | 回滚验证 |
|---|---|---|---|
| `tools/sig_evidence.py` | `data/status/_sig_evidence_pack.json` | 删过 6020 行 | 与 HEAD 逐字节一致 ✓ |
| （同批） | `alloc_sizeof.json`、`signature_conflicts.json` | — | 一致 ✓ |
| `tools/misattribution_ledger.py:160` | `data/status/misattribution_ledger.json` | 197 cluster → 3 | 与 HEAD 逐字节一致 ✓ |

**这本身是第一等发现**：「只读审计」在本仓**无法机械保证**——至少 4 个审计工具具备
"无 argparse + 无条件写受跟踪产物"的组合；且 `audit_retn_param_count.py:37-38` 用 `%TEMP%`，
Linux 下 `TEMP` 未设 ⇒ 产物落到**仓库根**（本次已产生 `retn_param_audit.json`）。

## 1. 工具集（报告 A）

**规模**：208 个项目脚本（`tools/` 65 + `tools/ida/` 95 + `ida/archive/` 42 + `ghidra/` 6）。

**诊断：需要结构性清理，而非新增工具。**

* **应删/归档 ≈137（66%）**：46 个硬编码 `asm/pal3a/`（该目录**已不存在**，主 agent 核实 ✓）；
  `tools/ida/` 的 **59 个 `pal3_*.py` 中 0 个**引用现代 `data/annotations/structs`（旧单文件模型已删）；
  `tools/run.py` **15 个调用中 13 个指向不存在的脚本**；`tools/ghidra/*` 硬编码 `D:/workspace/project-x`。
* **10 组重叠**，最严重：**同一条管线里两个回归门禁** —— `compile_regression.py`(`cli.py:455`)
  与 `regression_detector.py`(`cli.py:614`)，读**同一输入** `probe_census.json` 却用**两套基线**
  （`compile_baseline.json` vs `baselines/latest.json`）。
* **唯一必须"新增"的不是工具，而是 `requirements.txt` 里的 `capstone`** ——
  缺它使 Phase2 主力 `byte_diff_explain.py` 与 `check_member_offsets.py` **完全不可运行**（主 agent 核实 ✓）。
* **45 处文档引用了不存在的工具路径**（如 `tools/check_annotations.py` 真身在 `pipeline/`）；
  但**运行时无断链**（`cli.py` 真正 subprocess 调用的只有 3 个，均存在）。

## 2. 管线阶段与架构（报告 B）

**阶段建议命名 7 段**：0 输入真源 / 1 注入 `apply` / 2 导出 `export` / 3 生成 `codegen` /
4 编译普查 `probe` / 5 字节裁判 `match` / 6 门禁与基线。
其中 **codegen 内部实为 7 个变换**（5 stage + `_thunk_keep_tailjump` + `_jumpout_to_tailcall`），
而 `transform.py` docstring 只写 5。

**判定：分层意图正确，但边界已失守、门禁名义化。需要重构（最小必要），但不要重写 5 阶段管线。**

已复核的关键缺陷：

| 缺陷 | 证据 |
|---|---|
| **「codegen 不读 annotation」被违反 5 文件 19+ 处** | `emit_headers.py`(sdk_types/known_methods/template_bases/base_class/globals…)、`ast_transform.py:146,327`、`data.py`(skip_functions/vtables/bases/globals/functions)、`collect.py:97`、`stage4:334` ⇒ `data.py:229` 自称"the ONLY place"**已不成立**；而 `emit_headers.py:236` 的哨兵 `load_annotations_data()` **无人调用**（给人"已封死"的错觉） |
| **`export_full.py` blanket except + 恒 `qexit(0)`** | 中途崩溃会**留下部分 decomp 被 codegen 消费**，而 `cmd_codegen` 只检查目录里 ≥1 个 json ⇒ **静默的半成品** |
| **`compile` 恒 exit 0**（主 agent 核实 ✓） | `cli.py:710-721` 只打印，不传播退出码 ⇒ 无法断链 |
| **`apply` 盲区** | 日志有 `[6] Signatures fail=1`、`[6b] Global types fail=2`，**退出码仍 0** |
| **L1 棘轮残留洞** | `s4_baseline.json` 由 `compare_pal3.py:546` **先写**、棘轮判断在其后；若其后非零退出，`cli.py:569-573` 直接 exit，**不恢复旧基线** ⇒ 基线可静默下滑（L1 是全局硬线） |
| **门禁自身崩溃被读成"有退化"** | `regression_detector` 的 UnicodeEncodeError → exit 1 → `cli.py:633` 判成退化 → **拒绝刷新基线 + 把假退化写进报告**；`codegen_param_lint` 崩溃 → 被报成"生成源码有形参名为数字" |
| **死代码** | `stage5_fixup.py:990` `... if re.match(...) and False else False` **恒 False ⇒ 983-998 整块死**（主 agent 核实 ✓）；`stage3._fix_ref_params` 已被 stage5 超集取代**仍先跑**，且**绕过 stage5 的 F1a 证据门** |
| **docstring 与实现相反** | `stage3` 头称"No regex is used for pattern recognition" 而实际有 3 个 legacy 正则解析器；`transform.py:6-7` 称 stage4 "(no text hacks)" |
| **输出路径三套解析** | `config.py:107` vs `emit_headers.py:124` vs `emit_cpp.py:491`；且 `store.project_root` 由**注解路径反推**；tracked 模板 `pipeline.toml.example` 写的是 `include/pal3/gen` ⇒ **按 CLAUDE.md 指引新建配置即错位** |
| **悬空契约** | `pipeline/ida/_logs/ida_astring_names.json` **全仓无写入者**；`include/pal3/globals.h` 被 `stage4:844` 读但**未跟踪且过期**（468 extern vs 活体 2684） |
| **`globals.cpp` 行序非确定残留根因** | `emit_headers.py:2740/2747/2768` 从 **set 迭代**产生 |

## 3. 工作流闭环（报告 C）

**判定：不完备。** 5 个"强制检查点"里 **4 个从未接线**（`annotation_diff`、`error_classifier`、
`match`、`audit_layout`），唯一接线的 `compile_regression` **读缓存 census**；
而**唯一的主落地通道** `apply_annotation_batch.py --run-pipeline` **同时绕过它并跳过 L1**。

* **三套并行且互相矛盾的门禁配置**：`.claude/settings.json`（有效，只管结构）；
  `aide.toml` 与 `.project/plugins/pal3-gates/hooks.json` 的 matcher 指向**不存在的
  `pipeline/data/annotations/**`** ⇒ **恒不触发**，`gate_commit.sh:3` 的路径永远为空，且 `gate_*.sh` 是 664 非可执行
  —— 与 `gotcha_annotation_hook_never_wired` **完全同型**。
* **三套"官方工作流"互相矛盾**：`CLAUDE.md:125-133` / `_longterm_plan.md:12` /
  `.claude/commands/pal3-pipeline.md:380`（后者称"标注迭代中不运行 codegen 与 compile"）。
* **`tests/e2e/test_smoke.py` 恒通过**（主 agent 核实 ✓：**4 个 `test_*` 用 `return`、0 个用 `assert`**；
  `MIN_S2 = 58` 而已是 75）。
* **L1 棘轮无注入式负例测试**（`grep -rn ratchet tests/` 零命中），而设计文档明文要求"棘轮必须能被触发，否则是死门禁"。
* **无回退 SOP**：只有一份设计稿；`tools/_land_sizes.py:64` 用的恰是被纪律**明文禁止**的 `git checkout --`。
* **记账无强制**：最近 12 个改 `data/annotations/structs` 的提交**只有 1 个**带 CHANGE_LOG；
  2026-09-20 的 4 个落地提交在 CHANGE_LOG 中**无对应段落**；知识库 32 条中 **5 条未进 `MEMORY.md` 索引**、7 条缺 `created`。

## 4. 证据与判据体系（报告 D）

**判定：部分自洽；"可复核"当前不成立。**

* **等级门槛没有执行者**：`apply_annotations.py` 中 `grade` 出现 **0 次**；
  `ast_transform.py:240-246` 只判 `'slots' in entry` ⇒ **A / A-V2 / B-SLOTMISMATCH 完全等价**；
  而注解里已有 **33 处 `A:decomp_*` 自标 A**（按 taxonomy 定义应属 **C**）。
* **6 套等级词汇互不映射**（skill 的 A/B/C/D、taxonomy 的 A–E、`sig_evidence.py` 的 11 种机器级、
  `enum_promote` 的 4 种、PDB 的 4 层、以及注解 `source` 里**无任何文档定义**的 `A:/B:/C:` 前缀 223/102/3 处）。
* **`CLAUDE.md:72` 引用的"置信度规则表"不存在**。
* **318 个成员以 PDB 为唯一 source** ⇒ 直接违反 `CLAUDE.md:73` 与 `_pdb_nonauthority_notice.json`。
* **`_cleanup_scan_triage.json` 的 268 条等级不可审计**：taxonomy 规定 14 个必填字段，
  实测 `evidence` 仅 **4/268**，`root_cause_fixed`/`recommended_action`/`consistency` **0/268**；
  而 `cleanup-handoff.md:67` 称其"自洽校验全过"。
* **78 个 `data/status/*.json` 中 44 个（56%）无任何生成元数据** ⇒ 无法区分"审计结论"与"某次快照"。
* **恒真式门禁（与本报告 §2 同型）**：`tools/audit_layout.py:14-27` **自标 NON-DISCRIMINATING**
  （annotation→apply→IDB→export 一条数据链 ⇒ `binary_size == ida_size` **由构造必然相等**，
  818/881 恒等）⇒ **PASS 证明不了任何尺寸正确性**，却被 `CLAUDE.md` 列为强制检查点（主 agent 核实原文 ✓）。
* **10 处一致性冲突**（同一机制在不同产物中被判相反动作），其中最危险：
  C1 `arch_gbui_seven_slot_vtables_inheritance_chain.md`（"补 `base_class` 继承链"）vs
  `decision_sceneobj_composition_not_inheritance.md`（v4 终裁"**不是继承，是行表注册制**"）
  —— 按前者行动**会写错 `base_class`**（该文自述"写错 → 运行时崩溃，S2 探针查不出"）。

## 5. 主 agent 对本会话自身工作的更正（诚实交代）

* 我的 `tools/audit_structural_attribution.py` 产出的 `_structural_contradictions.json`，
  **偏移数字取自 decomp `this+N`**（语义错误：`2522` 的真值是 `20176`），且 **3/20 已过期**
  （`CCBProtectWindow` 176→2632、`UIRenderObj` 4→32 —— 主 agent 核实 ✓）。
  **该产物不应被引用，需按 asm `[reg+imm]` 重算。**
* `tools/audit_vftable_offset0.py` 的 `ctor_disp0` 判据本身是二进制的 ✓，但"多态"补充判据依赖注解方法，
  可能与实际不符（已知曾有 9 个类被护栏拦下）。

## 6. 最终诊断：**需要重构，但只做"最小必要重构"，不重写 5 阶段管线**

**分层意图正确（AST/文本分工本身合理、顺序有实证）；问题不在 pass 内部，而在"输入来源"与"门禁接线"。**

### 必做（按 ROI 排序，全部有现成积木）

1. **把"落地一次"固化为单命令 `pipeline/cli.py land`**（并让 `apply_annotation_batch.py` 改调它）：
   `check → apply → annotation_diff → export → codegen all(含 lint+invariants) → probe all →
   error_classifier --summary → match(L1) → audit_layout`，**每步 returncode 硬门禁**，
   跑前快照 census 作为 `--before`，**L1 回退即非零退出并打印回滚指引**。
   *理由*：一次补齐"4 个未接线检查点 + 被绕过的钩子 + 缺席的 L1"。
2. **给两条硬线加注入式负例测试**（L1 棘轮被人为降低必须触发退出码；`probe` 退化时不得刷新基线），
   修 `tests/e2e/test_smoke.py`（改断言、更新 `MIN_S2`），加最小 CI 入口。
3. **唯一出口层**：`export` 产出一个 `ida_export.json`（structs/globals/methods/vtables/skip/template 全量），
   codegen 只读它 —— 把 19+9 处越界收敛成 1 个读点，同时消掉两个悬空契约；
   *止血版* = 把散落直读集中到单一 loader。
4. **回退 SOP + `cli.py rollback`**（annotation / IDB / 产物重建链），并**修 `_land_sizes.py`** 停用被禁的 `git checkout --`。
5. **门禁 truthful 化**：删 `aide.toml` / `pal3-gates/hooks.json` 的死路径与不可执行权限，只留一处权威门禁；
   `audit_layout` 补 IDB 无关尺寸判据或**降级并写明替代**；`CLAUDE.md` 检查点表**补上 `probe all` 这一步**，
   并把 export/codegen 的 `[t4-DECLARED-EXCEPTION]` 写进红线措辞。
6. **记账强制化**（CHANGE_LOG 段落 + knowledge 索引覆盖 + `created` 必填），加校验器。
7. **工具清理**：删/归档 ≈137 个死脚本；`requirements.txt` 补 `capstone`；给 4 个"无 argparse 且写盘"的工具补 argparse。

### 不建议
重写 5 阶段管线；大规模迁移 `tools/` 与 `pipeline/` 的分工（先写清分工文档即可）。
