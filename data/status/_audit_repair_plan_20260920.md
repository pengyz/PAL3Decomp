# 审计复核（Kiro 独立对抗性复核）+ 修复方案

**复核者**：`subagent_kiro`（独立只读）；**被复核对象**：`data/status/_audit_toolchain_pipeline_20260920.md`；
**主 agent 对复核结论的再验证**：见 §1 末列。

## 1. 复核结论：10 条断言无一"不成立"，但**发现我方 3 处过度断言 + 1 处不完整**

| # | 原断言 | Kiro 判定 | 核实结果（主 agent 亲验） |
|---|---|---|---|
| 1 | 同一管线两个回归门禁 | **成立**（但二者触发时机不同，可视为两道防线） | 真问题是**文档/命名未讲清**，易误删其一 |
| 2 | `compile_regression` 只读缓存 census ⇒ 不能起门禁作用 | **部分成立** | **退出码传播早已修复**（`cli.py:661-666`）；真正问题是 `cmd_codegen` 的钩子**不调用 `probe`** ⇒ 验的是**可能过期的快照** |
| 3 | `audit_layout` 恒真门禁 | **成立**（自述 NON-DISCRIMINATING） | **但不完整**：它**已有** `1b. Declared-size geometry (IDB-independent)`（`:9-10,68,445-446`）⇒ 只需**提升为退出码判据** |
| 4 | `compile` 恒 exit 0 | **成立** | `cli.py:710-721` 只打印，无 `sys.exit` |
| 5 | **L1 棘轮活跃洞** | **部分成立，且已部分修复** | **已在 `cli.py:554-586` 缓解**（`prev_text`/`prev_l1` + 退化写回）。**残留窄边界**：`compare_pal3.py` 写完 `OUT_JSON` 后、自然结束前抛未捕获异常（如 registry/diff 写盘失败）⇒ `rc≠0` 命中"未完成"分支，**不还原**。触发法：让 `data/status/pal3_registry.jsonl` 只读。**严重性：低但非零** |
| 6 | `test_smoke.py` pytest 下恒通过 | **成立** | 4 个 `test_*` 全 `return`、0 `assert`；pytest 只在**异常**时失败（返回非 None 仅告警）；`MIN_S2=58` 而实际 75 |
| 7 | `export_full.py` blanket except + 恒 `qexit(0)` | **成立，但有例外** | 我方**遗漏**：文件内已有局部硬失败 `_os._exit(1)`（critical struct 0-member）；但主循环崩溃时它不会被调用 |
| 8 | codegen 违反"不读 annotation"红线 5 文件 19+ 处 | **成立，但实况比报告更透明** | `export_full.py` 的 8 处是**显式 `[t4-DECLARED-EXCEPTION]`**（带理由+量化数据）⇒ 性质是"**已声明的例外**"，不是隐蔽违规 ⇒ 修复应从"抓违规"改为"**审查已声明例外 + 加 IDB/注解一致性校验**" |
| 9 | 工具集 137/208 应删/归档 | **成立**（3 处抽查全中） | 数字略有差异（14 调用/7 种缺失 vs 13/15）；**我方遗漏**：`tools/ghidra/` 里有 **424MB Ghidra 发行包 zip**（仓库卫生，且清理历史需用户同意） |
| 10 | A 级证据门槛无执行者 | **成立** | `grade` 在 `apply_annotations.py` **0 命中**；`ast_transform.py:238-246` 只判 `'slots' in _c` |

**复核发现的我方报告缺陷（必须接受）**：

1. **基线断层未标注**：审计基线 `8d6db0048` **已含大量修复**（`cli.py:387/440/565/581/618` 的
   R1/R2/R5/M1/M2/M3 注释，日期 2026-09-15）。审计提交 `2c3467912` **只加 md、未改代码**（已核实）
   ⇒ 报告**未区分"现存缺陷"与"历史缺陷+已加固但残留"**，易让人从零重修已修过的东西。
2. `error_classifier.py` **逻辑健全**（真 `sys.exit(1)`），问题纯是"未接线"——报告混在一起讲易被误读。
3. `hooks.json` 死路径是**系统性复制粘贴模式**（不是一次性意外）⇒ 应加**通用检查**
   （"grep 所有 hook/matcher 路径并验证存在"），而非逐个修。
4. **"先写产物、后判断"是系统性模式**（`compare_pal3.py`/`compile_regression.py`/`regression_detector.py` 同构），
   不是 `match` 独有 ⇒ 应作为**结构性风险类**处理。
5. **424MB Ghidra zip** 未覆盖。
6. **优先级倒置**：`test_smoke.py` 恒真应是 **P0 最高**（最像"标准测试"的死门禁，最易被信任）；
   **`land` 单命令价值被低估**（它是唯一能一次堵住"4 个未接线检查点 + 被绕过钩子 + 缺席 L1"的单点杠杆）。

**Kiro 明确同意"不要重写 5 阶段管线"**（理由：`cli.py` 里大量 R1/R2/M1/M2 式历史修复注释说明
该结构已在实战中反复暴露并修补，重写会丢掉已验证的边界处理，如 init 的"两趟 apply"）。

## 2. 修复方案（Kiro 给出，主 agent 采纳并排序）

### P0 立即止血（成本小，1-2 天）

| 项 | 动作 | 理由/风险 | 验证 |
|---|---|---|---|
| **P0-1** | 重写 `tests/e2e/test_smoke.py`：`return True/False` ⇒ `assert`；`MIN_S2` 改为真实值并注明需手动核对 | 最易被信任的**死门禁** | 故意把 `MIN_S2` 设为 9999 验证 FAIL |
| **P0-2** | `cmd_compile()` 末尾加 `sys.exit(0 if rc==0 else 1)` | `compile` 是唯一恒 0 命令 | 塞语法错误后 `echo $?` 应非 0 |
| **P0-3/4** | `hooks.json`/`gate_commit.sh`/`gate_annotations.sh`/`aide.toml` 的 `pipeline/data/annotations/` ⇒ `data/annotations/`；`chmod +x` 两个 `.sh` | 死路径 hook + 非可执行 = 双重失效 | `touch` 一个 struct 后 `git add`，跑 `gate_commit.sh` 应触发 `check` |
| **P0-5** | `tools/_land_sizes.py:65` 的 `git checkout --` ⇒ **仅报告 + 非零退出**（不自动执行） | **唯一有真实数据丢失风险**的一条（会静默丢弃未提交标注） | 构造未提交修改，确认文件未被自动改动 |

### P1 结构性（成本中，1-2 周）

| 项 | 动作 | 关键点 |
|---|---|---|
| **P1-1** | **两条硬线的注入式负例测试** | Kiro 给出完整代码：①把 `s4_baseline.json` 的 `match_L1` 人为 +1 ⇒ `match` 必须非零退出**且基线被还原成注入值**；②伪造一个 ok→fail 的 census ⇒ `probe` 必须非零退出**且 `baselines/latest.json` 的 mtime 不变**。两条都用 `finally` 还原 |
| **P1-2** | `cmd_codegen` 的 codegen-后钩子**插入 `probe_compile`**（snapshot 之后、lint/regression 之前） | 让 `compile_regression` 验的是**本次**产出；风险：拖慢 `codegen all` ⇒ 加 `--skip-probe` 逃生口 |
| **P1-3** | 把 `audit_layout` **已有的** `1b` 几何判据从"仅打印"提升为**影响退出码** | 单独加 `--strict-geometry`，先默认关闭观察一轮 |
| **P1-4** | 逐一复核 `export_full.py` 的 **8 处已声明例外**；export 完成后 diff"注解值 vs IDB 实际值"，不一致即报警 | 性质是"审查已声明例外"，**不是删除到红线合规**；已有 `_cleanup_fix_export_redline.json` 可复用 |
| **P1-5** | 把散落的 annotation 直读集中到 `pipeline/gen/annotation_view.py` | **不追求"彻底不读"**；验证=收敛前后 `codegen all` 产物 `diff -r` 字节相同 |
| **P1-6** | 两个回归门禁的**职责分工写进各自 docstring + CLAUDE.md** | 防未来误删其一 |

### P2 清理（成本大但风险低，滚动推进）

`P2-1` 归档失效脚本（**先 `grep -rln` 确认零文档引用**，移到 `tools/archive/` 而非直接删）；
`P2-2` `requirements.txt` 补 `capstone`（先复现 ImportError 再改）；`P2-3` 424MB Ghidra zip
（**若需重写历史必须用户明确同意**，不得自行执行）；`P2-4` 给 4 个"无 argparse 且写盘"的审计工具补 argparse。

### 不要做（Kiro 与我一致）

不要重写 5 阶段管线；不要现在大规模删 `tools/`（清理不解决任何门禁失效）；
不要为"红线合规"砍掉已声明例外；不要未经用户同意做 `git filter-repo` 类历史重写；
不要直接删掉 `_land_sizes.py` 的自动回退（先降级为仅报告观察）。

## 3. `pipeline/cli.py land` 单命令设计（Kiro 强化版）

9 步硬门禁：`check → apply → annotation_diff → export → codegen all → probe all →
error_classifier --summary → match → audit_layout(非阻断)`
* 每步 `subprocess.run(...).returncode`，**非零立即 `sys.exit(step_rc)`** 并打印"失败在第 N 步 + 回滚建议"；
* 跑前把 `s4_baseline.json`/`compile_baseline.json`/`baselines/latest.json` 快照到临时目录，失败时打印还原命令；
* **`apply_annotation_batch.py --run-pipeline` 改为直接调 `cli.py land`** —— 消灭"主落地通道绕过门禁并跳过 L1"；
* **加 `land --dry-run`**：只打印 9 步不执行 ⇒ 直接回应本次审计"只读探测会写盘"的教训。

## 4. 一句话总评（Kiro）

审计**基本可信**、方法论扎实（多维分维 + 逐条独立复核 + 自曝两起事故并逐字节验证回滚）；
**但基线粒度不够细**（把"历史缺陷+已加固"当"现存缺陷"）；修复优先级基本正确，
但 `test_smoke.py` 应提到 P0 最高，且 `land` 单命令应是**第一个交付、第二个验证**的项。
