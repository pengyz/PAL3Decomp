# 架构债路线图可执行性复核（#41）

- 复核对象：`docs/specs/2026-11-27-architecture-debt-roadmap.md`（#36，230 行）
- 复核时间：2026-11-27 02:5x（所有读数见 §9 命令，均为当场执行）
- 模式：只读复核，只新增本文件；未改代码/注解/数据/基线，未跑 apply/export/codegen/probe/loop/match

## §0 结论摘要（8 条）

1. **文件与行号基本成立**：路线图引用的 26 个已存在文件全部存在（§2.1）；#5 审计的 20 个关键行号锚点本轮逐个 `sed -n` 复核，**全部仍对得上**（§9-C2）。没有整段失效、需要重写的文件。
2. **计数类数字已漂移**：`tests/*.py` 顶层 158→**159**、递归 177→**178**（新增 `tests/test_stage5_this_alias_reassign.py`，mtime 02:32，属 #30 的 `tests/` 写域）；`pytest --collect-only` 1794/1802→**1799/1807**，EXIT 仍 2、4 个收集错文件不变。而 `pipeline/cli.py` 1322 行、`emit_headers.py` 5844 行、`pipeline/gen/test_*.py` 34 个未变。
3. **两个「新建目标」的前提有误**：`tests/ida/` 不是新目录（已存在，含 `tests/ida/test_export_scoped.py`，mtime Oct 10）；`pipeline/stages/` 目录**整个不存在**，B4 要先建包（¶ 目录 + `__init__.py` 约定需在卡面写明）。
4. **B1 阻塞正确**：#30 仍在 in_progress 且写域含 `tests/`，B1 的 `blockedBy: [#30]` 正确，**不能现在开**。另：B1 验收「`pytest tests/test_preflight.py -q` 全部通过」当前会**空转通过**（模块级 `pytestmark = pytest.mark.skip`，0 passed/全 skipped），必须补「非 skip 用例数 > 0」断言。
5. **B2「可立即开」要打折**：其验收第 3 条「codegen 前后 `pal3/src` hash 一致」与 #30 正在改 `data/annotations/structs/gbVisNode.json` 直接冲突——注解一变，同一进程前后两次 codegen 的产物就会变，hash 必不相等，属**假失败**。要么等 #30 收口，要么把该验收标注为「需独占窗口且注解静止」。
6. **B4 有一处硬缺口（阻断级）**：`pipeline/check_annotations.py:29` 也是 `from pipeline.gen.annotation_view import ...`，但 B4 的 writeScopes 没列这个文件；`annotation_view` 一旦迁到 `pipeline/annotations.py`，check 侧直接 ImportError。且 ida→gen 实际 **6 处**引用（5 处 import：`export_full.py:16/:198/:503/:627`、`apply_annotations.py:38`；外加 `export_full.py:210` 的 `sys.modules['pipeline.gen.stages.emit_headers']` 动态取模块），路线图只写了 `export_full.py:16` 一处，验收范围不足。
7. **「38 处」不是字面量口径**：`grep -rn "data/annotations" pipeline/gen --include=*.py`（排除 `annotation_view.py` 与 `test_*`）实测 **31 处 / 9 文件**，且多出 #5 清单外的 `data.py`、`stage3_cleanup.py`、`transform.py`。B2 验收应写「lint 报 0」，而不是「38→0」这个不可复现的固定数；lint 规则须先按 #5 §2.3 的口径（含常量/变量/派生路径 4 处）写成测试，再谈阈值。
8. **最小首批推荐 B3 而不是 B2**：B3 与 #30 零耦合、写域无交集、验收全是新增单测 + 一次 match；B2 虽然也是 P0，但其 hash 验收依赖注解静止。**只批一件时选 B3，B2 在 #30 收口后立刻开**（§6）。

## §1 逐批核对总表

| 批次 | 目标（路线图） | 引用文件 | 行号/符号 | 写域与在跑卡 | blockedBy 是否正确 | 验收命令可跑 | 结论 |
|---|---|---|---|---|---|---|---|
| **B1** | D2/D3：pytest 收集清零、preflight 复活 | 9 个路径全存在（§2.1）；`tests/ida/` 已存在非新建（§2.3） | 无行号锚点；`tests/test_preflight.py:4` 模块级 skip 仍在 | `tests/` 与 #30 重叠 | ✅ 正确（#30 in_progress） | collect-only 现 RC=2（本批目标）；`pytest tests/test_preflight.py` 全 skip ⇒ 验收需补「非 skip>0」 | **不能开**（等 #30）+ 验收补断言 |
| **B2** | D1：38 处注解直读收敛 + lint | 8 个 gen 文件全存在；`pipeline/gen/test_annotation_read_single_point.py` 待建 | 派生 4 处仍在（§2.1）；字面量实测 31/9 文件（§2.4） | 仅 `pipeline/gen/**` 精确文件，与 #30 无交集 | ⚠️ 标「无」，但 hash 验收与 #30 的注解写冲突（§4.2） | lint 文件未建（先建后跑）；`codegen all` 可跑但慢；前后 hash 需独占窗口 | **可开，建议 #30 收口后** |
| **B3** | D4/D9：基线单写者 + 棘轮策略 | `cli.py`/`compare_pal3.py`/`probe_compile.py` 存在；4 个新文件待建 | `cli.py:744/811/851`、`compare_pal3.py:983/1003` 全成立 | 与 #30 无交集 | ✅ 无阻塞正确 | `match` 可跑（需独占窗口，~2–3 分钟） | **可立即开（推荐首批）** |
| **B4** | D5/D6：codegen 阶段上收 + 层向不倒置 | `pipeline/stages/` 目录不存在（§2.3）；目标 2 个新文件待建 | ida→gen 实际 **6 处**（5 import + 1 `sys.modules`），非 1 处；`check_annotations.py:29` 漏列（§2.2） | 与 B2/B3 文件重叠 | ✅ 依赖 B2+B3 正确 | import 方向测试待建；范围须覆盖 5+1 处 | **不能开**（依赖 + 硬缺口） |
| **B5** | D14/D7/D8：export 幂等、check 自举写、跨 stage 全局 | 6 个改文件存在；3 个新测试待建 | `export_full.py:2/457`、`check_annotations.py:984/1819/2171/2404`、`emit_cpp.py:1346`、`codegen.py:105` 全成立 | 依赖 B4 | ✅ 正确 | 两次 export 可跑（各 ~155s，需 6 分钟窗口） | **不能开**（依赖 B4） |
| **B6** | P2：iterate 死代码、README 漂移、D10 行号 | `cli.py`/`README.md`/`codegen.py` 存在 | `cli.py:1285/:1313` 成立；D10 引用的 `codegen.py:155-162` 是注释块，实际 env 读取在 `:165-166`（§2.2） | 依赖 B5 | ✅ 正确 | `cli.py --help` RC=0（§9-C6） | **不能开**（依赖 B5） |

## §2 文件与行号明细

### 2.1 仍然成立的引用（逐条实测）

| 引用点 | 实测内容（截断） |
|---|---|
| `pipeline/cli.py:744` | `prev_text = s4.read_text(encoding='utf-8')`（match 读旧基线） |
| `pipeline/cli.py:811` | `s4.write_text(...)`（--rebaseline 写基线） |
| `pipeline/cli.py:851` | `s4.write_text(...)`（pairing-infra 自动对齐写基线） |
| `pipeline/cli.py:553` | `print("[Probe] Running probe s2 ...")`（codegen 内嵌 probe） |
| `pipeline/cli.py:567` | `snap = subprocess.run([... , 'capture'])`（codegen 内快照） |
| `pipeline/cli.py:612` | `regression_script = os.path.join(tools_dir, 'compile_regression.py')` |
| `pipeline/cli.py:937` | `if has_baseline:`（probe 后 regression_detector --check） |
| `pipeline/cli.py:974` | `save_rc = subprocess.run([... , '--save-baseline'])` |
| `pipeline/cli.py:1285` | `elif command == 'iterate':`（UNAVAILABLE exit 2） |
| `pipeline/cli.py:1313` | `def apply_scoped_env():`（定义但无调用者） |
| `pipeline/cli.py:436` | `checker = os.path.join(_PROJECT_DIR, 'tools', ...)`（export 后一致性 advisory） |
| `pipeline/cli.py:499` | `_me = os.path.join(_PROJECT_DIR, 'tools', 'check_member_extent.py')` |
| `pipeline/compare_pal3.py:983` | `_base_p.write_text(json.dumps(...))`（裁判自己写 s4_baseline） |
| `pipeline/compare_pal3.py:1003` | `_detail_out.write_text(...)`（写 s4_diff_detail） |
| `pipeline/ida/export_full.py:2` | `IDAPython: Pure export - no modifications to IDB`（与 :457 写名矛盾） |
| `pipeline/ida/export_full.py:16` | `from pipeline.gen.annotation_view import iter_struct_files, iter_structs, load_struct` |
| `pipeline/ida/export_full.py:457` | `# [t4-DECLARED-EXCEPTION] structs/*.json + functions.json → VC6 mangled 名` |
| `pipeline/check_annotations.py:984/1819/2171/2404` | 四处 `open(...,'w')`（dep_graph / canonical baseline / n12 / n22 派生写） |
| `pipeline/gen/stages/emit_cpp.py:1346` | `def _flush_adjudication_queue():`（跨 stage 可变全局） |
| `pipeline/gen/codegen.py:105` | `from stages.emit_headers import run_header_generation`（进程内共享全局） |
| 派生读取 4 处 | `emit_headers.py:980 with open(_ANNOTATION_ENUMS_PATH,...)`、`ast_transform.py:192 for _path in _av.iter_struct_files(_structs_dir)`、`stage4_substitution.py:2308 with open(_al4, ...)`、`:2318 with open(_al5, ...)` |

### 2.2 失效或偏移（需修订）

| 位置 | 路线图写法 | 实测 | 处理建议 |
|---|---|---|---|
| B4「ida 不再 import gen」 | 只列 `export_full.py:16` | ida 内实际 6 处引用：`export_full.py:16/:198/:503/:627`、`apply_annotations.py:38`，以及 `export_full.py:210` 的 `sys.modules['pipeline.gen.stages.emit_headers']` | 验收改为「`pipeline/ida/**` 中 `pipeline.gen` 引用为 0，覆盖上述 5 处 import + 1 处 `sys.modules` 动态取模块」 |
| B4 writeScopes | 未列 `check_annotations.py` | `check_annotations.py:29` import `gen.annotation_view` | **必须加进 B4 写域**，否则移动单点读后 check 直接红（阻断级） |
| B6 / D10 | `codegen.py:155-162` | `:155` 起是注释块；实际 `CODEGEN_CLASS`/`CODEGEN_FUNC` 读取在 `:165`/`:166`，判断函数在 `:171-175` | 引用改为 `:165-166`（或 `:155-175` 区间） |
| B1 `tests/ida/` | 「（新，迁移 IDA 专属测试）」 | 目录已存在，含 `tests/ida/test_export_scoped.py`（Oct 10） | 改为「已存在，追加迁移文件」 |
| B2「38 处」 | 固定数 38→0 | 字面量实测 31 处/9 文件，且含 `data.py`/`stage3_cleanup.py`/`transform.py` 三个 #5 清单外文件 | 验收改「lint 0」；lint 规则按 #5 §2.3 口径实现（含 4 处派生路径） |

### 2.3 新建目标实况

- **已存在**：`tests/ida/`（含 `test_export_scoped.py`）。
- **不存在**（13 项）：`tests/test_preflight_live.py`、`pipeline/gen/test_annotation_read_single_point.py`、`pipeline/baselines.py`、`pipeline/ratchet.py`、`pipeline/gen/test_ratchet_policy.py`、`pipeline/gen/test_baselines_single_writer.py`、`pipeline/stages/codegen.py`、`pipeline/annotations.py`、`pipeline/gen/test_codegen_purity.py`、`pipeline/gen/test_import_direction.py`、`pipeline/gen/test_export_idempotence.py`、`pipeline/gen/test_check_no_bootstrap.py`、`pipeline/gen/test_adjudication_queue.py`。
- **目录不存在**：`pipeline/stages/`（B4 需建包；`pipeline/gen/codegen.py:105` 现用 `from stages.emit_headers ...` 说明 sys.path 依赖，迁包时要一并改）。

### 2.4 直读计数的两套口径

| 口径 | 命令 | 结果 |
|---|---|---|
| 字面量（本轮实测） | `grep -rn "data/annotations" pipeline/gen --include=*.py \| grep -v annotation_view \| grep -v /test_` | **31 处 / 9 文件**：emit_headers 12、ast_transform 5、emit_cpp 4、stage3_cleanup 3、collect 2、data.py 2、transform 1、stage4_substitution 1、scoped_targets 1 |
| 语义读点（#5 §2.3） | #5 §6 的跨行窗口扫描 + 人工补 4 处派生路径 | **38 处 / 8 文件** |

⇒ 两者不可互证。B2 的 lint 必须先定义规则（建议直接以 #5 §2.3 清单为准），再以「lint 输出 0 条」作验收；不要写「38→0」。

## §3 写域重叠矩阵

|  | B1 | B2 | B3 | B4 | B5 | B6 | #30（在跑） | #41（本卡） | #42 |
|---|---|---|---|---|---|---|---|---|---|
| B1 | — | 无 | 无 | 无 | 无 | 无 | **重叠 `tests/`** | 无 | 无 |
| B2 | 无 | — | 同目录不同文件 | B4 依赖 B2 | 无 | 无 | 无（#30 不写 `pipeline/gen`） | 无 | 无 |
| B3 | 无 | 同目录不同文件 | — | B4 依赖 B3 | 无 | 无 | 无 | 无 | 无 |
| B4 | 无 | 依赖 | 依赖 | — | B5 依赖 B4 | 无 | 无 | 无 | 无 |
| B5 | 无 | 无 | 无 | 依赖 | — | B6 依赖 B5 | 无 | 无 | 无 |
| B6 | 无 | 无 | 无 | 无 | 依赖 | — | 无 | 无 | 无 |

- B2/B3 都在 `pipeline/gen/` 下但**文件不相交**（B3 的新测试名与 B2 的 8 个改动文件无交集），可以并行；前提是写域按**精确文件**登记（路线图 B2 已明确不用整目录）。
- #42 写 `docs/knowledge/**`，与所有批次无交集，可与任一批并行。
- #40 已 done（`data/status/evidence_ledger.json`），当前该文件为 `M`，但没有任何批次写它（B3/B5 的测试用 `tmp_path`）。

## §4 阻塞关系检查

### 4.1 阻塞正确的

- B1 ← #30：`tests/` 直接重叠，且 #30 仍在写（最新 `tests/test_stage5_this_alias_reassign.py` 02:32）⇒ 正确。
- B4 ← B2+B3、B5 ← B4、B6 ← B5：文件级重叠（`cli.py`、`export_full.py`、`codegen.py` 等）⇒ 正确。
- R6 类批次（#37 已交付施工图）需 Human 拍板的三件事，路线图未把它们写成 blockedBy，而是写在正文「需 Human 拍板」——可接受，但**落地卡创建时必须带 blockedBy 或显式「等 Human」**，否则会被自动认为可开。

### 4.2 需要补充的约束（非 blockedBy 但影响可执行性）

| 批次 | 约束 | 依据 |
|---|---|---|
| B2 | hash 验收要求注解静止；#30 正在改 `data/annotations/structs/gbVisNode.json` ⇒ 需独占窗口或在 #30 后开 | §0.5 |
| B2 | `codegen all` 默认内嵌 `probe s2` + snapshot + compile_regression（`cli.py:553/567/612`），一次 ~3 分钟；hash 窗口要把这段时间算进去 | 实测管线行为 |
| B3 | `match` 会读/写 `s4_baseline.json`/`s4_diff_detail.json`（`compare_pal3.py:983/1003`），验收「诊断不改基线」必须在临时副本上做，不能碰仓库文件 | 路线图 §B3 已写，此处提醒实现细节 |
| B5 | 两次 export 各 ~155s（含 IDB 加载），窗口 ≥6 分钟；且 export 会写 IDB 名（`export_full.py:457`），两次跑之间不能有他人 apply/export 插入 | 实测 + §2.1 |
| B1 | `tests/test_preflight.py` 现整模块 skip；「全过」需改为「exit 0 且 collected>0 且 skipped==0」 | `tests/test_preflight.py:4` |

## §5 批次可开性矩阵

| 批次 | 能否立即开 | 阻塞项 | 写域 | 建议 owner | 验收命令当前可跑 | 备注 |
|---|---|---|---|---|---|---|
| B1 | ❌ | #30（in_progress，写 `tests/`） | `tests/`、`pytest.ini`、`conftest.py`、4 个收集错文件 | coder | 可跑（RC=2 即目标态未达成） | 需补「非 skip>0」断言 |
| B2 | ⚠️ 有条件 | 无硬阻塞；hash 验收需独占窗口 | 8 个 gen 文件 + 1 新测试 + `CLAUDE.md` | coder | 可跑（`codegen all` 慢） | 建议 #30 收口后开 |
| B3 | ✅ | 无 | `cli.py`、`compare_pal3.py`、`probe_compile.py` + 4 新文件 | coder | 可跑（`match` 需窗口） | **推荐首批** |
| B4 | ❌ | B2、B3 + 自身硬缺口 | `pipeline/stages/`（新）、`pipeline/annotations.py`(新)、`gen/**` import、`ida/**` 6 处、`check_annotations.py:29` | coder | import 测试待建 | 先把 `check_annotations.py` 加进写域 |
| B5 | ❌ | B4 | 6 文件 + 3 新测试 | coder | 可跑（6 分钟窗口） | export 写 IDB，需独占 |
| B6 | ❌ | B5 | `cli.py`、`README.md`、`codegen.py`、`CLAUDE.md` | coder | `--help` RC=0 | 纯文档/死代码，最后做 |

## §6 最小首批建议

**只批一件：B3。**

理由（按证据排序）：

1. **零耦合**：B3 的写域（`cli.py`、`compare_pal3.py`、`probe_compile.py` + 4 个新文件）与 #30（`include/`、`gbVisNode.json`、`tests/`）无交集；B2 的 hash 验收则直接受 #30 影响（§0.5）。
2. **验收可当场判定**：6 个棘轮用例 + tmp_path 单写者 + 诊断不改基线 + 一次 match 决策不变；不需要等外部条件。
3. **是 B4 的前置**（B4 依赖 B2+B3），先做 B3 不会浪费，且它把「测量」与「策略」拆开，后续 B5 的 export 幂等测试也要用它的单写者约定。
4. **风险低**：改动集中在测量链的三个文件，不碰 codegen 产物；回退就是 `git checkout` 这三文件 + 删四个新测试。

**B2 紧随其后**（#30 收口后立即开）：它是 P0 红线债（注解直读），且是 B4 的另一半前置。开卡时须把验收第 3 条改为「独占窗口内 codegen 前后 hash 一致（注解静止）」，并把 lint 规则写成测试先行。

## §7 路线图需修订点（8 条）

1. B1 的 `tests/ida/` 改为「已存在，追加迁移」，删除「（新）」。
2. B1 验收补「非 skip 用例数 > 0」；collect 目标从固定 1794 改为「执行时实测值」（当前 1799/1807）。
3. B2 验收「38→0」改为「lint 0」；lint 规则按 #5 §2.3 口径（38 处语义读点 + 4 处派生路径）实现；并注明字面量口径当前是 31 处/9 文件。
4. B2 加约束：「hash 验收需独占窗口、注解静止；#30 在跑期间不得判定」。
5. B4 写域补 `pipeline/check_annotations.py`（`:29` 跨层 import）；验收覆盖 ida 6 处（5 import + `export_full.py:210` 的 `sys.modules`）+ check 1 处。
6. B4 注明 `pipeline/stages/` 目录需新建（含包结构），并把 `gen/codegen.py:105` 的 `from stages.emit_headers ...` 路径依赖列入改动面。
7. B6/D10 行号改 `:165-166`（`CODEGEN_CLASS`/`CODEGEN_FUNC` 读取），非 `:155-162`。
8. §4.1 资产表与 §0 的计数（158/177/1794/1802）全部标注「执行时重取」，避免下一张卡把漂移当退化。

**硬缺口（阻断级，仅 1 条）**：B4 漏 `pipeline/check_annotations.py`。不补则 B4 落地后 `check` 直接 ImportError，`pre-commit` 钩子（`pipeline/cli.py check`）会把所有提交卡死。

## §8 下一张实现卡草案（B3）

- 标题：B3 基线单写者 + 棘轮策略下沉（D4/D9）
- writeScopes：`pipeline/baselines.py`（新）、`pipeline/ratchet.py`（新）、`pipeline/gen/test_ratchet_policy.py`（新）、`pipeline/gen/test_baselines_single_writer.py`（新）、`pipeline/compare_pal3.py`、`pipeline/cli.py`、`pipeline/probe_compile.py`
- blockedBy：无
- 验收：
  1. 6 个棘轮用例全过（rebaseline / pairing-infra 自动对齐 / L1+semantic 豁免 / 真退步成对恢复 / scoped 不碰基线 / 诊断不写基线）；
  2. `pytest pipeline/gen/test_baselines_single_writer.py -q` 在 `tmp_path` 下验证：同一进程内两次「测量→写基线」只有一个写点；
  3. 诊断模式（`--check` 失败路径）不修改任何基线文件（用 `tmp_path` + 文件 mtime/hash 断言）；
  4. `python3 pipeline/cli.py match` 在同一分解上决策不变（`[metric]` 行 L1 不降；与开卡前当场读数对比，读数写进提交说明）；
  5. `git status` 仅新增/改动上述 7 个文件，四份基线无 diff。
- 停止条件：若第 4 条出现 L1 下降，停止并按「衰退纪律」先定位（不改基线判定逻辑）；若 `match` 因并发管线占用 IDB 失败，等窗口重跑，不得改 `--rebaseline`。

## §9 复现命令与实测输出

### C1 引用文件存在性（26/26）

```bash
cd /home/peng/workspace/PAL3Decomp
for f in conftest.py pytest.ini pipeline/ida/test_lvar_apply.py pipeline/ida/test_settype_thiscall.py \
         tools/test_scan_misattribution.py tools/test_t1b.py tests/test_preflight.py pipeline/cli.py \
         pipeline/compare_pal3.py pipeline/probe_compile.py pipeline/check_annotations.py \
         pipeline/ida/export_full.py pipeline/ida/apply_annotations.py pipeline/gen/annotation_view.py \
         pipeline/gen/codegen.py pipeline/gen/stages/emit_headers.py pipeline/gen/stages/stage4_substitution.py \
         pipeline/gen/stages/emit_cpp.py pipeline/gen/type_registry.py pipeline/gen/stages/collect.py \
         pipeline/gen/stages/scoped_targets.py pipeline/gen/ref_params.py pipeline/gen/ast_transform.py \
         pipeline/README.md CLAUDE.md data/status/evidence_ledger.json; do [ -e "$f" ] || echo "MISSING $f"; done
echo "missing-check done"
```

输出：`missing-check done`（无 MISSING 行）。

### C2 行号锚点（逐个打印）

```bash
cd /home/peng/workspace/PAL3Decomp
for x in pipeline/cli.py:744 pipeline/cli.py:811 pipeline/cli.py:851 pipeline/cli.py:553 \
         pipeline/cli.py:567 pipeline/cli.py:612 pipeline/cli.py:937 pipeline/cli.py:974 \
         pipeline/cli.py:1285 pipeline/cli.py:1313 pipeline/compare_pal3.py:983 pipeline/compare_pal3.py:1003 \
         pipeline/ida/export_full.py:2 pipeline/ida/export_full.py:16 pipeline/ida/export_full.py:457 \
         pipeline/check_annotations.py:29 pipeline/gen/stages/emit_cpp.py:1346 pipeline/gen/codegen.py:105 \
         pipeline/gen/stages/emit_headers.py:980 pipeline/gen/ast_transform.py:192; do
  f=${x%:*}; n=${x##*:}; printf "%-58s | " "$x"; sed -n "${n}p" "$f" | cut -c1-90
done
```

输出（逐行，见 §2.1 表；全部非空且语义匹配）。

### C3 新建目标存在性

```bash
cd /home/peng/workspace/PAL3Decomp
for f in tests/test_preflight_live.py pipeline/gen/test_annotation_read_single_point.py pipeline/baselines.py \
         pipeline/ratchet.py pipeline/gen/test_ratchet_policy.py pipeline/gen/test_baselines_single_writer.py \
         pipeline/stages/codegen.py pipeline/annotations.py pipeline/gen/test_codegen_purity.py \
         pipeline/gen/test_import_direction.py pipeline/gen/test_export_idempotence.py \
         pipeline/gen/test_check_no_bootstrap.py pipeline/gen/test_adjudication_queue.py; do
  [ -e "$f" ] && echo "EXISTS $f" || echo "absent $f"
done
[ -d pipeline/stages ] && echo "pipeline/stages EXISTS" || echo "pipeline/stages absent"
[ -d tests/ida ] && echo "tests/ida EXISTS" || echo "tests/ida absent"
```

输出：13 行 `absent`、`pipeline/stages absent`、`tests/ida EXISTS`。

### C4 计数

```bash
cd /home/peng/workspace/PAL3Decomp
wc -l pipeline/cli.py pipeline/gen/stages/emit_headers.py
ls tests/*.py | wc -l
find tests -name '*.py' | wc -l
ls pipeline/gen/test_*.py | wc -l
```

输出：`1322 pipeline/cli.py`、`5844 pipeline/gen/stages/emit_headers.py`、`159`、`178`、`34`。

### C5 pytest 收集

```bash
cd /home/peng/workspace/PAL3Decomp
python3 -m pytest --collect-only -q > /tmp/collect.txt 2>&1; echo "RC=$?"; tail -3 /tmp/collect.txt
grep -E "^ERROR " /tmp/collect.txt
```

输出：`RC=2`、`1799/1807 tests collected (8 deselected), 4 errors`、四个 `ERROR` 文件（`pipeline/ida/test_lvar_apply.py`、`pipeline/ida/test_settype_thiscall.py`、`tools/test_scan_misattribution.py`、`tools/test_t1b.py`）。

### C6 CLI 可执行

```bash
cd /home/peng/workspace/PAL3Decomp
python3 pipeline/cli.py --help | head -8; echo "RC=${PIPESTATUS[0]}"
```

输出：命令表首 8 行 + `RC=0`。

### C7 ida → gen 跨层引用（6 处 + check 1 处）

```bash
cd /home/peng/workspace/PAL3Decomp
grep -rn "pipeline\.gen\|annotation_view\|scoped_targets" pipeline/ida/*.py pipeline/check_annotations.py
```

输出：7 行——`apply_annotations.py:38`、`export_full.py:16`、`export_full.py:198`、`export_full.py:210`（`sys.modules['pipeline.gen.stages.emit_headers']` 动态引用）、`export_full.py:503`、`export_full.py:627`、`check_annotations.py:29`。

### C8 注解字面量读点

```bash
cd /home/peng/workspace/PAL3Decomp
grep -rc "data/annotations" pipeline/gen --include=*.py | grep -v ":0" | grep -v annotation_view | grep -v "/test_" | sort -t: -k2 -nr
```

输出（9 行）：emit_headers 12、ast_transform 5、emit_cpp 4、stage3_cleanup 3、collect 2、data.py 2、transform 1、stage4_substitution 1、scoped_targets 1 ⇒ `awk` 求和 **31**（若不过滤 `/test_`，会多出 `pipeline/gen/test_hang3_nails.py:2`）。

## §10 边界与自检

- 本文件 `wc -l` = **273** 行（§9 命令实测）。

- 只读边界：本卡只运行了 `grep`/`sed`/`ls`/`wc`/`pytest --collect-only`/`pipeline/cli.py --help`，未运行任何会写产物的管线命令；未改 `data/annotations`、`pal3/src`、`pipeline`、`tests`、四份基线。
- 唯一新增文件：本报告。`git status --porcelain docs/specs/2026-11-27-architecture-debt-batch1-check.md` 应为 `??`。
- 并发读数：`data/status/probe_census.json`、`s4_baseline.json`、`struct_holes_20261125.json` 等派生文件会被并发管线重写；本报告涉及的计数（159/178/1799/1807）均带「执行时点」语义，落地卡须重取。
- 未覆盖：B6 的完整正文（只读到 B5 段）、#36 §5 之外的「验收门槛」推导过程；若 QA 要求，可补读并追加。
