# 管线架构债执行路线图（只读汇编）

- 任务：#36 `tsk_01M8CG3ATEY7TTFJ01DDB2`
- 日期：2026-11-27
- 性质：**只读汇编**。本文只从 #5 审计、代码、测试与现有文档摘取事实，给出批次与验收；未修改代码/注解/数据/基线，未跑 `apply` / `export` / `codegen` / `probe` / `loop`，未 `git commit`。
- 主源：`docs/specs/2026-11-26-pipeline-architecture-audit.md`（#5，381 行）。债务编号沿用其 §5.1 的 `D1`–`D14`，**本文不新增债务**。
- 行号口径：#5 的 `file:line` 是审计时实测；本文引用时保留原行号，并在 §1 标“已审计”。仓库继续演进后行号可能漂移，复现命令见 #5 §6。
- 当前写域：截至本文写作，#30 仍 `in_progress`，写域 `include/gbengine/gbVisNode.h`、`data/annotations/structs/gbVisNode.json`、`tests/`；#34 `pending_acceptance`，写域仅 `docs/specs/2026-11-27-screenfade-size-4b-evidence.md`；#35 已 `done`。下文批次的写域按这三个边界避让。

## 0. 一分钟结论

1. #5 债务清单共 **14 条**：P0 4 条（D1–D4）、P1 6 条（D5–D9、D14）、P2 4 条（D10–D13）。其中 D2/D3 是“测试防线本身坏了”，不是普通重构。
2. 建议拆 **6 个批次**，按“先恢复可验证性，再收口测量/基线，再做模块化，最后做 P2 卫生”的顺序推进。批次之间用写域和前置依赖隔开，不并发改同一文件。
3. **如果 Human 只批准一件事，先做 B2（D1：38 处注解直读收敛 + lint）**：它是 P0、与当前 #30 写域不重叠、产物应字节不变，且后面 B4/B5 的注解读点迁移都依赖它先落地。
4. **B1（恢复 pytest/preflight）先等 #30 释放 `tests/`**；#34 只写一份 R4 取证文档，不阻塞任何架构批次。
5. **D13（`emit_headers.py` 5844 行 / `cli.py` 1322 行单体）本轮不拆**：只登记为长期重构观察项，避免把“可验收的小步”做成一次性大改。

本次只读复核（不是 #5 的数字替换，只说明现状）：

- `python3 -m pytest --collect-only -q` 仍 **EXIT=2**，4 个收集错误（`pipeline/ida/test_lvar_apply.py`、`pipeline/ida/test_settype_thiscall.py`、`tools/test_scan_misattribution.py`、`tools/test_t1b.py`）；本次读到 **1794/1802 收集**（#5 审计时为 1775/1783），说明测试资产又增加了，但“默认测试套件不可用”的结论未变。
- `wc -l pipeline/cli.py pipeline/gen/stages/emit_headers.py` = **1322 / 5844**，与 #5 §5.1 D13 一致。
- #5 引用的关键文件均存在：`pipeline/compare_pal3.py`、`pipeline/probe_compile.py`、`pipeline/check_annotations.py`、`pipeline/ida/export_full.py`、`pipeline/gen/annotation_view.py`、`pipeline/gen/codegen.py`、`conftest.py`、`pytest.ini`、`tests/test_preflight.py`。

## 1. 债务索引

编号、级别、问题均来自 #5 §5.1；`证据`列给 #5 章节与 `file:line`，`状态`列说明本次是否复核。

| ID | 级别 | 债务（一句话） | #5 证据 | 影响 | 证据状态 |
|---|---|---|---|---|---|
| D1 | P0 | codegen 注解直读 38 处 / 8 文件，单点读规则失效，CLAUDE.md 的“3 处/行号”已漂移 | #5 §2.3（38 处清单）、§5.1 D1 | 红线失效；schema 变更要改 N 处；lint 落地当天会红 | 已审计；本次抽查 8 个文件存在 |
| D2 | P0 | 默认 `pytest` EXIT=2（4 个收集错误），测试套件不能当门禁 | #5 §4.2 第 1 条、§5.1 D2；`python3 -m pytest --collect-only -q` | 新环境第一次跑测试即红；回归只能靠人工记得 | 已审计；本次复跑仍 EXIT=2 |
| D3 | P0 | `tests/test_preflight.py` 整模块 `pytestmark=skip`，preflight/loop 无活契约测试 | #5 §4.2 第 2 条、§5.1 D3；`tests/test_preflight.py` | 三份基线对账/已知恒红门禁没有活测试 | 已审计；未复跑用例 |
| D4 | P0 | `s4_baseline.json` 双写者：`compare_pal3.py` 非 scoped 时每次测量都写，`cli.py` 棘轮/对齐也写 | #5 §2.2 L1、§5.1 D4；`compare_pal3.py:983-1003`、`cli.py:744/:811/:851` | 单独跑 compare 会静默重锚；“裁判”和“记分员”同一模块 | 已审计；文件存在 |
| D5 | P1 | `codegen all` 内嵌 probe/snapshot/compile_regression，生成器不纯；CLAUDE.md 检查点表与代码分叉 | #5 §2.2 L3、§5.1 D5；`cli.py:553-623` | 生成耗时/退出码被编译结果污染；`--skip-probe` 会让 compile_regression 读陈旧 census | 已审计；文件存在 |
| D6 | P1 | `pipeline/gen/annotation_view.py` 位于 `gen/`，却被 `pipeline/ida/export_full.py` 导入，依赖方向倒置 | #5 §2.2 L8、§5.1 D6；`pipeline/ida/export_full.py:16` | `gen` 目录调整会破坏 export；单点读模块不能被两层公平共享 | 已审计；文件存在 |
| D7 | P1 | `check_annotations.py` 在“检查”中自举写 4 个文件（2 个 baseline、工作清单、依赖图） | #5 §2.2 L12、§5.1 D7；`check_annotations.py:984/:1819/:2171/:2404` | “只读校验”首次运行会改仓库；CI 与本地不一致 | 已审计；文件存在 |
| D8 | P1 | 跨 stage 进程内可变全局 `_ADJUDICATION_QUEUE`（`emit_cpp` ← `emit_headers`） | #5 §2.2 L7、§5.1 D8；`emit_cpp.py:1346-1359`、`codegen.py:105-118` | stage 顺序/进程边界成为隐式契约；单独跑 `codegen cpp` 会丢决策 | 已审计；文件存在 |
| D14 | P1 | `export` 写回 IDB 名称（自注 3276 次），文件头却写 “no modifications to IDB”，导出不幂等 | #5 §2.2 L4b、§5.1 D14；`export_full.py:2` vs `:457-521` | 导出永久改 work IDB 名字；apply/export 顺序可能影响命名；“验证前 apply→export”前提不成立 | 已审计；文件存在 |
| D9 | P1 | `probe` 同一命令测量 + 刷新基线，缺“只测不写”入口 | #5 §2.2 L2、§5.1 D9；`cli.py:937-978` | 回滚要人工 `--rebaseline` 或还原文件；测量与落基线语义混在一起 | 已审计；文件存在 |
| D10 | P2 | `iterate` 空槽 + `apply_scoped_env()` 死代码 | #5 §2.2 L13、§5.1 D10；`cli.py:1285-1297/:1313`、`codegen.py:155-162` | 新人误以为有自动迭代引擎；射程过滤无统一入口 | 已审计；文件存在 |
| D11 | P2 | `pipeline/README.md` 与 `cli.py` 实际命令脱节（仍写手工 IDA 命令） | #5 §5.1 D11；`pipeline/README.md` vs `pipeline/cli.py:296-1051`（命令入口） | 文档误导新人与自动化 | 已审计；未逐行 diff |
| D12 | P2 | advisory 检查无 owner/无到期（export 一致性、MemberExtent、invariants） | #5 §5.1 D12；`cli.py:436-444/:499-512` | “advisory 永不转硬”等于没有 | 已审计；文件存在 |
| D13 | P2 | `emit_headers.py` 5844 行单体；`cli.py` 1322 行多职责 | #5 §5.1 D13；`wc -l pipeline/gen/stages/emit_headers.py pipeline/cli.py` = 5844/1322 | 评审面过大；策略无法单测 | 已审计；本次 `wc -l` 复核 |

## 2. 批次计划（6 批，按依赖排序）

### B1 恢复“能跑的测试防线”（P0 D2/D3）

- **目标**：默认 `pytest` 能收集，`tests/test_preflight.py` 的非数据依赖用例恢复运行；不改生产行为。
- **涉及文件**：`conftest.py`、`pytest.ini`、`pipeline/ida/test_lvar_apply.py`、`pipeline/ida/test_settype_thiscall.py`、`tools/test_scan_misattribution.py`、`tools/test_t1b.py`、`tests/ida/`（新，迁移 IDA 专属测试）、`tests/test_preflight.py`、`tests/test_preflight_live.py`（新，拆数据依赖用例）。
- **owner 角色**：engineer（主）+ qa（复跑）。
- **writeScopes**：上述文件；`tests/` 下的新增只落 `tests/ida/` 与两个 preflight 文件，不碰其它测试。
- **blockedBy**：#30（其写域含 `tests/`）。
- **验收**：
  1. `python3 -m pytest --collect-only -q` EXIT=0；
  2. 收集数不低于本次实读的 **1794**（#5 审计基线为 1775，允许因新增测试更多）；
  3. `python3 -m pytest tests/test_preflight.py -q` 全部通过；数据依赖用例在 `tests/test_preflight_live.py` 里单独标记，不默认跑；
  4. `git status` 除测试/夹具外无生产文件改动。
- **风险与回退**：迁测试可能把用例“搬丢”。失败点：收集数下降或 preflight 仍有 skip；回退到迁移前文件，不删原测试。**停止条件**：收集数 < 1794 或出现新的 import 错误。

### B2 注解直读收敛 + 可执行 lint（P0 D1）

- **目标**：把 #5 §2.3 的 38 处直读改为经 `annotation_view`/单点读；新增 AST lint，白名单只允许单点读文件；产物字节不变。
- **涉及文件**：`pipeline/gen/stages/emit_headers.py`、`pipeline/gen/stages/stage4_substitution.py`、`pipeline/gen/stages/emit_cpp.py`、`pipeline/gen/type_registry.py`、`pipeline/gen/stages/collect.py`、`pipeline/gen/stages/scoped_targets.py`、`pipeline/gen/ref_params.py`、`pipeline/gen/ast_transform.py`、`pipeline/gen/annotation_view.py`、`pipeline/gen/test_annotation_read_single_point.py`（新）、`CLAUDE.md`。
- **owner 角色**：engineer。
- **writeScopes**：上述 exact 文件（**不用 `pipeline/gen/**` 整目录**，避免与 B3 的 `pipeline/gen/test_*` 重叠）；不改 `data/annotations`、`pal3/src`。
- **blockedBy**：无（与 #30 的 `tests/` 写域无交集）。
- **验收**：
  1. 新 lint 对 `pipeline/gen/**` 报 **38 → 0** 处直读（排除 `annotation_view.py` 与 `test_*.py`；必须跟随 `annotation_json_path` / `dirname(注解路径变量)` 派生读取）；
  2. `python3 -m pytest pipeline/gen/test_annotation_read_single_point.py -q` 通过；
  3. `python3 pipeline/cli.py codegen all` 前后 `pal3/src` 全树 hash 一致（产物字节不变）；
  4. `python3 pipeline/cli.py check` 对本批产生 **0 new errors**（若基线本身红，以 new errors 0 判，不要求全绿）。
- **风险与回退**：38 处中有 4 处是常量/派生路径（`emit_headers.py:980`、`ast_transform.py:192`、`stage4_substitution.py:2308/:2318`），lint 只扫字面量会漏。失败点：hash 变或 lint 仍 >0；回退本次 8 文件改动，保留 lint 报告。
- **测试落点说明**：为避开 #30 的 `tests/` 写域，lint 单测暂落 `pipeline/gen/`（该目录已有 34 个 `test_*.py` 先例，见 #5 §4.1）；B1 恢复 `tests/` 后可再迁移，不影响验收实质。

### B3 基线单写者 + 纯测量 + 棘轮纯函数（P0 D4、P1 D9）

- **目标**：`compare_pal3.py` 提供纯测量入口（`--no-write-baseline` 或默认不写，卡内定死）；四份基线只由 `baselines.py` 写；棘轮决策从 `cli.py` 抽成纯函数并用表驱动测试锁住。
- **涉及文件**：`pipeline/baselines.py`（新）、`pipeline/ratchet.py`（新）、`pipeline/compare_pal3.py`、`pipeline/cli.py`、`pipeline/probe_compile.py`、`pipeline/gen/test_ratchet_policy.py`（新）、`pipeline/gen/test_baselines_single_writer.py`（新）。
- **owner 角色**：engineer。
- **writeScopes**：上述文件；不写 `data/status/*` 基线（测试用 `tmp_path`）。
- **blockedBy**：无（与 B2 的 exact 文件不重叠）。
- **验收**：
  1. 两个新单测通过（棘轮 6 个用例：accept / L1 退化 / semantic 豁免 / pairing-infra 对齐 / population 变化 / rebaseline；基线单写者用 tmp_path 断言只有 `baselines.py` 写）；
  2. 用纯测量入口跑 `compare_pal3.py`（诊断场景）不再改任何基线文件；`match` 全链决策与改前一致；
  3. `python3 pipeline/cli.py match` 在同输入下 L1/exit code 不变；未 `--rebaseline` 时 `s4_baseline.json` 内容不变。
- **风险与回退**：`cli.py` 策略段被搬动可能改变棘轮分支。失败点：6 个用例任一与旧行为不一致，或 match 结果变化；回退 `cli.py`/`compare_pal3.py`，保留 `ratchet.py` 草案。
- **说明**：D9 的“只测不写”入口由 `compare_pal3.py --no-write-baseline`（默认仍兼容写一版，或直接默认不写并由 `match` 显式落基线）实现；两种取一，批次卡里定死，不用“看情况”。

### B4 codegen 去门禁化 + 单点读上移（P1 D5/D6）

- **目标**：`codegen all` 只生成、退出码只反映生成；probe/snapshot/lint/compile_regression 由显式 `gate`/`loop` 调；`annotation_view` 上移为 `pipeline/annotations.py`，`ida` 不再 import `gen`。
- **涉及文件**：`pipeline/stages/codegen.py`（新）、`pipeline/gen/codegen.py`、`pipeline/cli.py`、`pipeline/annotations.py`（新，从 `pipeline/gen/annotation_view.py` 迁）、`pipeline/gen/annotation_view.py`、`pipeline/ida/export_full.py`、`pipeline/gen/**` 的 import 更新（只改导入，不改生成逻辑）、`pipeline/gen/test_codegen_purity.py`（新）、`pipeline/gen/test_import_direction.py`（新）。
- **owner 角色**：engineer（主）+ architect（边界复核）。
- **writeScopes**：上述文件；`pipeline/gen/**` 的改动仅限 import 行，逐文件列出，不整目录重写。
- **blockedBy**：B2（注解读点已收敛）、B3（`cli.py` 已改过一轮，避免同文件并发）。
- **验收**：
  1. `python3 pipeline/cli.py codegen all` 不再触发 probe/snapshot/compile_regression，退出码只反映生成；`--with-probe` 兼容一版（若保留）；
  2. `loop` 显式调 `gate`，`loop --expect-*` 断言语义不变；
  3. `pipeline/ida/**` 不再 import `pipeline/gen/**`（新 import-direction 测试通过）；
  4. `codegen all` 前后 `pal3/src` hash 不变（纯生成等价）。
- **风险与回退**：`cli.py` 再动一次编排，可能把 loop 的顺序改错。失败点：`codegen all` 退出码被编译污染仍存在，或 loop 门禁少跑一步；回退 `cli.py` 编排，保留 `gate` 子命令草案。
- **注意**：R-C 与 CLAUDE.md 检查点表冲突（#5 §3.2），本批必须同步改文档；否则文档继续误导“codegen 后跑 compile_regression”。

### B5 export 幂等 + check 显式初始化 + 队列显式化（P1 D14/D7/D8）

- **目标**：`export` 不再静默改 IDB 名称：首选不改名；若迁移成本高，则文件头与 `cli export` 显式声明会改，并输出连续两次名称 diff（卡内定死，推荐前者）；`check_annotations` 无基线时只报错、不写文件；`_ADJUDICATION_QUEUE` 不再靠进程内全局传递。
- **涉及文件**：`pipeline/ida/export_full.py`、`pipeline/ida/apply_annotations.py`、`pipeline/check_annotations.py`、`pipeline/cli.py`、`pipeline/gen/stages/emit_cpp.py`、`pipeline/gen/codegen.py`、`pipeline/gen/test_export_idempotence.py`（新）、`pipeline/gen/test_check_no_bootstrap.py`（新）、`pipeline/gen/test_adjudication_queue.py`（新）、`CLAUDE.md`。
- **owner 角色**：engineer（主）+ architect（export 语义）。
- **writeScopes**：上述文件；不写 `data/status` 基线/清单（测试用 tmp_path）。
- **blockedBy**：B4（`cli.py`/`export_full.py` 已稳定）。
- **验收**：
  1. 按卡内选定口径验收：不改名 → 同一 IDB 连续两次 `export`，第二次名称 diff 为空；显式声明 → 文件头/CLAUDE.md 有声明，且 `cli export` 输出连续两次名称 diff（diff 允许非空，但必须可见，不得静默）；
  2. 无基线时 `check` 只报错，`git status --porcelain -- data/status` 前后 diff 为空；显式 `baseline init` 才自举；
  3. `codegen cpp` 单独跑不再依赖 headers stage 的进程内队列（新测试用两个进程/两次调用验证）；
  4. 三个新单测通过。
- **风险与回退**：export 命名迁移到 apply 可能改变 IDB 状态；失败点：第二次 export 名称 diff 非空，或 check 仍写文件；回退 export/check 改动，保留“名称 diff 记录”作为最小替代。

### B6 P2 卫生与文档对齐（P2 D10/D11/D12）

- **目标**：清理死代码/空槽，`pipeline/README.md` 与 `cli.py --help` 一致，advisory 有 owner/到期。
- **涉及文件**：`pipeline/cli.py`、`pipeline/README.md`、`pipeline/gen/codegen.py`、`CLAUDE.md`。
- **owner 角色**：architect（主）+ writer（文档）。
- **writeScopes**：上述文件；不碰 `data/annotations`、`pal3/src`、基线。
- **blockedBy**：B5（`cli.py` 最后一次改）。
- **验收**：
  1. `python3 pipeline/cli.py iterate` 删除或接上；`apply_scoped_env()` 删除或接入唯一入口（二选一，卡内定死）；
  2. `pipeline/README.md` 的命令与 `python3 pipeline/cli.py --help` 对齐（逐条 diff 为空）；
  3. advisory 每项有 owner 与到期策略（不再“永不转硬”）。
- **风险与回退**：低；只动入口/文档。失败点：删了仍被引用的入口；回退该文件。
- **D13 不在本批**：单体拆分（`emit_headers.py` 5844 行 / `cli.py` 1322 行）只登记，另立长期重构，不在本轮 6 批内硬做。

## 3. 分层纠偏清单

| ID | 当前层/动作 | 应放层 | 迁移动作 | 关联债务/批次 | 是否阻塞字节匹配 |
|---|---|---|---|---|---|
| L1 | `compare_pal3.py` 测量同趟写 `s4_baseline.json` | measurement + ratchet + baselines | 纯测量入口只返回 stats/rows；`match` 显式落基线；诊断不写 | D4 / B3 | **间接阻塞**：基线真值可被静默改，所有 L1 验收失真 |
| L2 | `probe` 测量 + 刷新基线同一 verb | measurement/probe stage + baselines | 测量写 census；`--save-baseline` 或 `match` 显式落基线 | D9 / B3 | 否（语义可接受，但入口要分清） |
| L3 | `codegen all` 内嵌 probe/snapshot/lint/compile_regression | stages/codegen + gate | `codegen all` 只生成；`gate`/`loop` 显式跑门禁；保留一版 `--with-probe` | D5 / B4 | 否（但退出码/耗时被污染） |
| L4a | export 读 annotation（7 标记/8 读取） | 保持声明例外，文件内 `_load_annotation()` 集中 | 不迁移；lint 只对 `pipeline/gen/**` 强制，例外读标记 | 无独立债务 / B4 | 否（已声明） |
| L4b | export 写回 IDB 名称（3276 次） | apply 命名，或 export 显式声明 + diff | 命名迁 apply，或保留写名但记录连续两次 diff | D14 / B5 | **间接阻塞**：导出不幂等，apply/export 顺序影响命名 |
| L5 | codegen 直读注解 38 处/8 文件 | `annotations.py` 单点读 | 8 文件改经单点；AST lint 38→0；跟随派生路径 | D1 / B2 | 否（应字节等价；但绕过 `strip_ovl` 会藏 bug） |
| L6 | codegen 写 `data/status/*` 产物 | artifacts.py（唯一 status 写点） | 生成器只返回数据；status 由 artifacts 写 | 无独立债务；本轮不新建模块，登记为后续 | 否（所有权/清理语义问题） |
| L7 | `_ADJUDICATION_QUEUE` 进程内全局 | 显式 artifact（文件/参数） | headers 写、cpp 读同一显式产物；不靠 import 全局 | D8 / B5 | 否（但 stage 顺序变隐式契约） |
| L8 | `pipeline/ida/export_full.py` import `pipeline/gen/annotation_view.py` | `pipeline/annotations.py` 顶层 | 单点读上移；ida 只依赖 annotations | D6 / B4 | 否（依赖方向/可维护性） |
| L9 | `cli.py` 分发+编排+策略+编译 1322 行 | cli 只解析；stages/ratchet/baselines 分层 | 先抽 ratchet/baselines（B3），再 gate（B4） | D13 / 长期 | 否（评审/单测问题） |
| L10 | 三套 S2/L1 基线 + 三套门禁语义 | baselines.py 单写 + preflight 只读 | 统一四份基线写点；preflight 继续只读 | D4 / B3 | **间接阻塞**：基线不同步时门禁失去判别力 |
| L11 | 无 CI；pre-commit 只跑 check；默认 pytest 红 | tests/CI 门禁 | 先修收集（B1），再谈 CI/nightly | D2/D3 / B1 | 否（但回归无防线） |
| L12 | `check_annotations.py` 检查中自举写 4 文件 | 显式 `baseline init` | 无基线只报错；显式 init 才写；首跑 git status 不变 | D7 / B5 | 否（git 状态污染/CI 不一致） |
| L13 | `iterate` 空槽、`apply_scoped_env` 死代码 | 删除或接上唯一入口 | 二选一，不保留“看起来能用”的空槽 | D10 / B6 | 否 |

**P0 的判据**：只有“让验证/测量本身失真”或“红线完全失效”的债务进 P0（D1–D4）。纯风格、文档、死代码不升 P0。

## 4. 可测试性与补测试

### 4.1 现有资产（#5 §4.1，本次复核）

| 资产 | #5 审计时 | 本次只读复核 |
|---|---|---|
| `tests/**` 顶层 `*.py` | 154 | 158 |
| `tests/**` 递归 `*.py` | 173 | 177 |
| `pipeline/gen/test_*.py` | 34 | 34 |
| `pytest --collect-only` | 1775/1783，EXIT=2，4 收集错 | 1794/1802，EXIT=2，同 4 个收集错 |
| CI | 无 | 无（`.github/workflows`、`.gitlab-ci.yml` 均无） |
| pre-commit | 只跑 `cli.py check` | 同 |

### 4.2 盲区与批次测试集

| 盲区 | 现状证据 | 对应批次 | 最小测试集 |
|---|---|---|---|
| 默认 pytest 不可用、preflight 整模块 skip | #5 §4.2 第 1/2 条；本次复跑仍 EXIT=2 | B1 | 收集 EXIT=0 + `test_preflight.py` 非数据用例 |
| 38 处注解直读无 lint | #5 §2.3/§4.2 第 5 条 | B2 | `pipeline/gen/test_annotation_read_single_point.py`（AST 白名单 + 38→0） |
| 棘轮/基线单写者无契约测试 | #5 §4.2 第 5 条 | B3 | `test_ratchet_policy.py` 6 用例 + `test_baselines_single_writer.py` tmp_path |
| `codegen all` 内嵌门禁无编排契约 | #5 §4.2 第 5 条 | B4 | `test_codegen_purity.py`（只生成、不 probe）+ `test_import_direction.py` |
| export 写 IDB/check 自举/队列全局无测试 | #5 §4.2 第 5 条 | B5 | 连续两次 export 名称 diff + check 首跑 git status + 两进程队列 |
| 默认不跑的 e2e（棘轮注入） | #5 §4.2 第 3 条 | 待 CI | 加 `slow` 标记，nightly；不塞进 B1 的默认套件 |

**fixture/生产通路边界**：上表测试全部用 `tmp_path`/假 IDB/假 census；不得把 fixture 升格为生产输入（#5 §6 与项目复用纪律）。`pipeline/gen/test_*.py` 位置是现有约定，不是新生产通路。

## 5. 门槛与顺序

### 5.1 三类门槛

- **现在就能做**：B2（D1）、B3（D4/D9）。两者写域不重叠：B2 只动 8 个 gen 文件 + lint 测试 + `CLAUDE.md`；B3 动 `cli.py`/`compare_pal3.py`/`probe_compile.py` + 两个 `pipeline/gen/test_*` 新文件，不碰 B2 的 8 个文件。
- **等 #30 释放 `tests/`**：B1（D2/D3）。#30 的写域含 `tests/`，B1 必须等它验收/释放，否则同一文件并发写。
- **等 R6 Human 拍板后**：R6 的注解重铸执行卡（①③⑤④②⑥）不在本路线图内；架构批次本身不依赖 R6 决策，但 R6 执行卡落地时不要与 B2/B3 同时改 `pal3/src` 或 `data/annotations`（B2 用 hash 等价验收，R6 会改产物，二者会互相污染读数）。
- **等 R4 #30/#34 收口后**：R4 最终收口需要 #30（C2039）与 #34（四个 fade 各多 4B）都完成；但架构批次只与 #30 的 `tests/` 写域冲突（B1），#34 只写文档、不阻塞任何批次。不要把“R4 全绿”当作 B2/B3 的前置。

### 5.2 依赖顺序

```
B2 (D1) ─┐
         ├─> B4 (D5/D6) ─> B5 (D14/D7/D8) ─> B6 (D10/D11/D12)
B3 (D4/D9) ┘
B1 (D2/D3) 等 #30 释放 tests/ 后可并行（不碰上述写域）
```

- B4 依赖 B2（注解读点已收敛）和 B3（`cli.py` 已改过一轮，避免同文件并发）。
- B5 依赖 B4（`cli.py`/`export_full.py` 稳定）。
- B6 依赖 B5（`cli.py` 最后一次改）。
- B1 只动测试/夹具，可与 B2/B3 并行，但必须等 #30。

### 5.3 只批准一件事时的选择

**B2（D1）**。理由：

1. 它是 P0，且是“红线失效”的直接证据；不做，后面 B4/B5 的读点迁移没有 lint 兜底。
2. 与 #30 写域不重叠，可立即开卡；B3 也可立即开，但 B2 的验收（hash 等价）更独立、回退更小。
3. 它的 lint 是后续 B4（annotations 上移）和 B5（export 例外集中）的前置检查器；先做能减少后面两次返工。

## 6. 下一张卡草案（给 PMO，不建卡）

| 草案 | 标题 | owner 角色 | writeScopes | 验收摘要 |
|---|---|---|---|---|
| K1 | 恢复 pytest 收集与 preflight 契约测试 | engineer | `conftest.py`、`pytest.ini`、`tests/ida/`、`tests/test_preflight*.py`、`pipeline/ida/test_lvar_apply.py`、`pipeline/ida/test_settype_thiscall.py`、`tools/test_*.py` | collect EXIT=0、≥1794、preflight 非数据用例通过；等 #30 释放 `tests/` |
| K2 | 注解直读 38→0 + AST lint | engineer | 8 个 `pipeline/gen` 文件 + `pipeline/gen/annotation_view.py` + `pipeline/gen/test_annotation_read_single_point.py` + `CLAUDE.md` | lint 0、`codegen all` 前后 `pal3/src` hash 一致、check 0 new errors |
| K3 | 基线单写者 + 纯测量 + 棘轮纯函数 | engineer | `pipeline/baselines.py`、`pipeline/ratchet.py`、`pipeline/compare_pal3.py`、`pipeline/cli.py`、`pipeline/probe_compile.py`、两个 `pipeline/gen/test_*` | 6 棘轮用例 + tmp_path 单写者；compare 诊断不改基线；match 决策不变 |
| K4 | codegen 去门禁化 + annotations 上移 | engineer/architect | `pipeline/stages/codegen.py`、`pipeline/annotations.py`、`pipeline/gen/annotation_view.py`、`pipeline/gen/**` 导入、`pipeline/cli.py`、`pipeline/ida/export_full.py` | codegen all 只生成；loop 显式 gate；ida 不 import gen；hash 不变 |
| K5 | export 幂等 + check 显式初始化 + 队列显式化 | engineer | `pipeline/ida/export_full.py`、`pipeline/ida/apply_annotations.py`、`pipeline/check_annotations.py`、`pipeline/cli.py`、`pipeline/gen/stages/emit_cpp.py`、`pipeline/gen/codegen.py`、3 个 `pipeline/gen/test_*`、`CLAUDE.md` | 按卡内口径（不改名→第二次名称 diff 空；显式声明→有可见 diff）；check 首跑不改 `data/status`；队列两进程测试 |
| K6 | P2 清理与文档对齐 | architect/writer | `pipeline/cli.py`、`pipeline/README.md`、`pipeline/gen/codegen.py`、`CLAUDE.md` | iterate/apply_scoped_env 处理完；README 与 help 一致；advisory 有 owner/到期 |

**不要建**：D13 的单体拆分卡（`emit_headers.py`/`cli.py` 大重构）。它没有独立验收面，容易和 B2/B3/B4 的改动撞车；等前 6 批稳定后再单独立项。

## 7. 引用与边界

- 主源：#5 `docs/specs/2026-11-26-pipeline-architecture-audit.md` §0–§7；本文所有债务/错层/测试缺口均可回溯到该文件。
- 关键文件：`pipeline/cli.py`、`pipeline/compare_pal3.py`、`pipeline/probe_compile.py`、`pipeline/check_annotations.py`、`pipeline/ida/export_full.py`、`pipeline/gen/annotation_view.py`、`pipeline/gen/stages/emit_headers.py`、`pipeline/gen/stages/stage4_substitution.py`、`pipeline/gen/codegen.py`。
- 当前写域：#30 `include/gbengine/gbVisNode.h`、`data/annotations/structs/gbVisNode.json`、`tests/`；#34 `docs/specs/2026-11-27-screenfade-size-4b-evidence.md`；#35 已 done。
- 本文只读：未改代码/注解/数据/基线，未跑 `apply` / `export` / `codegen` / `probe` / `loop`，未 `git commit`；批次中的命令是未来执行卡的验收，不代表已执行。
- 数字边界：#5 的 38 处/1775 收集/3276 次命名等是审计时读数；本次只读复核的 1794/1802 与 EXIT=2 已单列，不把两者混写。后续行号漂移时以 #5 §6 复现命令重取，不凭记忆改数字。
