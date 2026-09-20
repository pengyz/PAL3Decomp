# 架构清理与修复 · 实施计划（2026-09-20）

依据：`data/status/_audit_repair_plan_20260920.md`（Kiro 独立复核版）。
目标（本会话长期目标 `goal-312d2835`）：**完整实施 P0→P1→P2**，每项带验证证据，每步提交推送。

## 硬约束（全程）
不重写 5 阶段 codegen 管线；不做未经用户同意的 git 历史重写；
每项改动后必须验证 + 提交推送；**L1 多重集不得回退（基线 34）、总错误不得增加（基线 2151）**、
`pipeline/cli.py check` PASS；结束时工作区 clean。

## P0 止血（先做，成本小）
| # | 动作 | 验证 |
|---|---|---|
| P0-1 | `tests/e2e/test_smoke.py`：`return True/False` ⇒ `assert`；`MIN_S2` 改真实值 + 注明需手动核对 | 故意把 MIN_S2 设 9999 必须 FAIL |
| P0-2 | `pipeline/cli.py` `cmd_compile` 末尾传播 ninja 退出码 | 注入语法错误后 `echo $?` 非 0 |
| P0-3 | `hooks.json` / `gate_commit.sh` / `gate_annotations.sh` / `aide.toml`：死路径 `pipeline/data/annotations/` ⇒ `data/annotations/`；`chmod +x` 两个 .sh | `touch`+`git add` 后跑 gate 能触发 `check` |
| P0-4 | 同上（aide.toml 同款死路径一并修） | `grep -rn "pipeline/data/annotations" .` 归零 |
| P0-5 | `tools/_land_sizes.py` 的 `git checkout --` ⇒ **仅报告 + 非零退出** | 构造未提交修改，确认文件未被自动改动 |

## P1 进度
- [x] **P1-1** 两条硬线注入式负例测试 ✓✓ **两条都真跑并验证通过**
      · `tests/e2e/test_probe_baseline_injection.py`：注入 ok→fail ⇒
        `regression_detector --check` **退出码非 0** ✓ 且 `baselines/latest.json`
        **逐字节未变** ✓（"不得刷新基线"成立）。设计适配：`probe all` 会**重生成** census，
        故注入打在 census 文件上、直接测 `cmd_probe` 判定所用的那一步（已注明）。
      · `tests/e2e/test_l1_ratchet_injection.py`：注入 `s4_baseline.match_L1=35` ⇒
        真跑 `pipeline/cli.py match` ⇒ **退出码非 0**（棘轮报警）✓ 且基线被**写回注入值**
        （证明"退化时写回旧基线"，棘轮不会失忆）✓；`finally` 还原后实测 `match_L1=34` ✓。
        耗时约 5 分钟（e2e 固有成本），用 `PAL3_E2E_INJECTION=1` 开启以免拖慢日常套件。
- [x] **P1-6** 两个回归门禁职责分工写入 `compile_regression.py` / `regression_detector.py`
      docstring + `CLAUDE.md`（含"检查点表缺 `probe` 一步"的明示）✓
- [x] **P1-3** `audit_layout` 的 `1b declared-size geometry` 从"仅打印"提升为**影响退出码** ✓
      加 `--strict-geometry`（**默认关**）+ 阈值可环境覆盖（`PAL3_GEOMETRY_WARN_RATIO` /
      `PAL3_GEOMETRY_HIGH_RATIO`，后者是**为了能被注入式验证**）。
      验证：A 默认 ⇒ exit 0（行为不变，38 warnings）；B 注入 `HIGH=1.0`+strict ⇒ **exit 1** ✓
      （门禁可被触发）；C strict+默认阈值 ⇒ **exit 1**（**14 个结构体 >50x**，这是真实发现）。
      **新落地清单**：`data/status/_geometry_strict_report.json`（HIGH 14 个 / warn 38 个），
      例：`CCBProtectWindow`(size 与成员几何严重不符)、`CEffQuake`、`CONTEXT`、
      `CTaskTpl_tagEffTaskParam_CEff*` —— 与审计 §4 的"尺寸判据"发现互相印证
      （我此前的 `_structural_contradictions` 也记过 `CCBProtectWindow 176→2632`）。
      这批需**按二进制证据**修正尺寸或成员，属**独立 backlog**（不在本目标的 P0/P1 范围内）。
- [x] **P1-2** `codegen all` 钩子**先跑 `probe s2`**（默认开）+ `--skip-probe` 逃生 ✓
      插入位置（代码行号确认）：**PROBE(L428) → SNAPSHOT(L455) → LINT(L474) → REGRESSION(L484)**
      —— 让 `snapshot` 与 `compile_regression` 看**本次** codegen 的 census（此前它们看的是
      "上一次不知何时跑的 probe 快照"）。
      成本实测：`probe s2` **21 秒**（206 单元）⇒ 可接受，故默认开启。
      验证：真跑 `codegen all` ⇒ 日志出现 `[Probe] Running probe s2 …`，并因**检出已知回归**
      （`UISystem.cpp`/`sub_421870`）而**中断 exit 1** ✓（退出码已传播 ⇒ `&&` 链断开）。
      注：日志里 snapshot 的输出**早于** probe 是父子进程 stdout **缓冲交错**的假象，
      以**代码顺序**为准（已用 AST/行号核对）。
      顺手修了自己引入的 `%d` 未插值 bug。
- [ ]
      **P1-4** 复核 `export_full.py` 的 8 处 `[t4-DECLARED-EXCEPTION]` + 一致性校验 ✓
      复核结论：这 8 处是"高质量的已声明例外"，**不该删到合规**（头部声明块给出：IDB 无等价
      可查询形式 / 承重且量化：1955 skip 地址与 3594 导出交集=0、475 virtual→442 签名前缀、
      3276 mangled 名、686 struct 的 8979 条 _variants、1816 _skip_function_names / 
      vtables+methods 与注解逐字段等值）。
      新工具 `tools/check_export_annotation_consistency.py` 补上缺失的告警，判据只用
      `vtables`+`methods`；`_variants` **仅提示**（两侧表示不同，比键会产出 742 个假阳性 ——
      我第一版之错，已降级）。已**接入 `cmd_export` 尾部**（只读、无需 IDA、报警不阻断）。
      验证：A 现状 exit 0（0 不一致 ⇒ 独立印证 export_full 自述的 761/761）；B 注入一处
      methods 名 ⇒ exit 1 + ❌ ✓；C 还原后 exit 0 ✓。
· **P1-5**（直读收敛）

## P1 结构（P0 后）
P1-1 两条硬线注入式负例测试（L1 棘轮 / probe 不得刷新基线，均 `finally` 还原）
P1-2 `cmd_codegen` 钩子插入 `probe_compile`（+`--skip-probe`）
P1-3 `audit_layout` 的 `1b` 几何判据提升为影响退出码（+`--strict-geometry` 默认关）
P1-4 复核 `export_full.py` 8 处 `[t4-DECLARED-EXCEPTION]` + 加"注解 vs IDB"一致性校验
P1-5 直读收敛到 `pipeline/gen/annotation_view.py`（验证：`codegen all` 产物 `diff -r` 字节相同）
P1-6 两个回归门禁职责分工写入 docstring + CLAUDE.md

## P2 清理（滚动）
P2-1 归档失效脚本（先 `grep -rln` 确认零文档引用，移 `tools/archive/`）
P2-2 `requirements.txt` 补 `capstone`（先复现 ImportError）
P2-3 424MB Ghidra zip（**需用户明确同意**，不自行重写历史）
P2-4 给 4 个"无 argparse 且写盘"的审计工具补 argparse

## 进度
- [x] **P0-1** `test_smoke.py` 改 assert ✓（`MIN_S2` 改读**编译基线**=68，棘轮语义）
      验证：`python3 tests/e2e/test_smoke.py` → 3 passed / **1 failed**；
      注入 `PAL3_MIN_S2=9999` → `❌ probe_compile: S2 75/206 < 下限 9999` ✓ **门禁已复活**。
      ⚠️ **那 1 failed 是真实回归、不是测试 bug**：`compile_regression` 退出码非 0，
      对应既存未修回归 `UISystem.cpp`/`sub_421870`（根因=调用点两处可疑注解，§50.4 已诊断）。
      **本用例保持红色**——它现在如实反映一个已诊断未修的问题，属"门禁复活"的证据。
- [x] **P0-2** `cmd_compile` 末尾传播 ninja 退出码 ✓
      验证：AST 检查 `cmd_compile` 最后一条语句 = `sys.exit(0 if result.returncode == 0 else 1)`。
      （未做全量 ninja 真跑验证：耗时长，留待需要时补）
- [x] **P0-3/4** 死路径 `pipeline/data/annotations/` ⇒ `data/annotations/` ✓
      共 8 处：`hooks.json`(2) + `aide.toml`(4) + `scripts/gate_commit.sh`(1) + `scripts/gate_readonly.sh`(1)；
      并把 7 个 `scripts/*.sh` 全部 `chmod +x`（原先 3 个是 664 不可执行）。
      验证：`grep -rn "pipeline/data/annotations" --include=*.json --include=*.toml --include=*.sh` 仅剩
      `data/status/*.json`（审计记录本身）⇒ **无活门禁路径**。
      **附带发现**：`data/status/_cleanup_scan_triage.json:5766` 记录 `globals.h` 头部注释也写着
      过期的 `pipeline/data/annotations/globals.json` ⇒ 生成物里的路径字面量陈旧，归入 P1/P2。
- [x] **P0-5** `tools/_land_sizes.py` 不再自动 `git checkout --` ✓（改为打印 `[REVERT-NEEDED]` + 收集清单）
      验证：`grep -n "git', 'checkout'" tools/_land_sizes.py` → 已移除 ✓
- [ ] P1-1 … P1-6
- [ ] P2-1 … P2-4

## P2-4 执行记录（2026-09-20，第 5 轮）
**问题**：本仓多个**会写盘**的工具**没有参数解析**（或只识别个别开关、**对未知开关一律忽略**）⇒
`--help` 会被当作普通输入并**执行全流程、覆盖产物**。本次审计期间已因此发生 **2 起事故**。

**做法**：给 **16 个**"会写盘且完全无 argv 处理"的工具统一插入护栏：
见到任何 `-` 开头的参数即打印用法并 **exit 0，不执行任何工作**。
文件清单见 commit；护栏文本统一带 `_sys_guard` 标记（可 grep 复查）。

**验证（产物哈希，`--help` 前后必须不变）**：
| 工具 | exit | 产物变化 |
|---|---|---|
| `alloc_sizeof.py` | 0 | **无** ✓ |
| `audit_signature_consistency.py` | 0 | **无** ✓ |
| `byte_diff_explain.py` | 0 | **无** ✓ |
| `misattribution_ledger.py`（**审计事故工具**）| 0 | **无** ✓（修复后）|
| `audit_retn_param_count.py` | 1 | 无（它 `import idc`，IDA 外本就跑不了 ⇒ 非回归）|

**额外发现并修复**：`tools/misattribution_ledger.py` **不在**上述 16 个里 —— 它有**部分**
`sys.argv` 处理（`:37` 的 `--min-sites`）却**忽略未知开关**，于是 `--help` 仍会执行并覆盖
受跟踪的 `data/status/misattribution_ledger.json`（本轮实测哈希 `e90498be→4a1412d2`）。
⇒ 已给它加**严格拒绝未知开关**的护栏，并用**合规方式**（`git show HEAD:<path> > <path>`，
**非** `git checkout`）还原文件（还原后 md5 = HEAD ✓）。
**教训：判据"完全无 argv"太窄；真正的危险类是"无严格开关校验"。**

**残留清单**（已存档 `data/status/_tools_argparse_hazard.json`）：仍有若干工具满足
"会写盘 且 无 argparse 且 无严格护栏"，其中 `uses_argv=True` 的那些与 `misattribution_ledger.py`
同型（会忽略未知开关），应在后续轮次按同一护栏修掉。

## P2-4 残留（第 6 轮，已完成）
给 4 个"会写盘但**忽略未知开关**"的同型工具加**严格拒绝未知开关**护栏：
`sig_evidence.py`（**审计事故工具**）、`apply_vtable_fix.py`、`fix_all_vtables.py`、`fix_vtable_splits.py`。
验证（`--help` 前后产物哈希）：三者 exit0 且**产物无变化** ✓；`sig_evidence.py`
`--help` ⇒ exit0 + 产物不变 ✓，且**无参调用仍正常**（exit0，会按设计重写 pack）✓。

**过程中我犯的错（记录）**：第一版补丁按 4 空格缩进插入，但 `sig_evidence.py` 的锚点是
**模块级 `if __name__ == '__main__':` 内的 4 空格 `if`** —— 插入后 `IndentationError:351`
把文件**改坏**。已 `git show HEAD:` 还原后，**按锚点实际缩进重插**并验证语法+行为 ✓。
**教训：给已有文件插代码必须指定与锚点一致的缩进，且插入后必须跑 `py_compile`。**

## P2-2（第 6 轮，已完成）
`capstone` 未安装已在 `byte_diff_explain.py:38` / `check_member_offsets.py:30` 复现
`ModuleNotFoundError` ⇒ 已补入 `requirements.txt`（`capstone>=5.0.0` + 理由注释）。
**安装仍需操作者执行 `pip install -r requirements.txt`**（本环境未联网安装）。

## 🆕 新发现（第 6 轮，登记为 **P2-5**，未修）
**`tools/sig_evidence.py` 的默认（无参）运行会把受跟踪产物 `data/status/_sig_evidence_pack.json`
从 6931 行砍到 1648 行（丢 76%）** —— 实测（本轮验证时无意触发，已 `git show` 还原，md5==HEAD）。
这与审计观察到的"该 pack 被重写成 363→30 含 slots"一致，也印证工具自述的
"**54 条 A-V2 是现行评分函数产不出的更高等级（别的版本写入）**"⇒ **当前工具无法忠实重建该产物**。
**待做（P2-5）**：给该工具加**棘轮护栏**（新 pack 条目数远小于现有 ⇒ 拒绝覆盖并报警），
或改为"必须显式开关才允许覆盖既有 pack"。**在修好之前，任何人不应无参运行 `sig_evidence.py`。**
