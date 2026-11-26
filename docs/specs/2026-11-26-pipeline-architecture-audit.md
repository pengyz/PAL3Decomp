# 管线架构审计（只读）

- 任务：#5 `tsk_01M8BWJS6F14BEZY5G6X6C`
- 执行：承宇（架构）
- 日期：2026-11-26
- 性质：**只读审计**。本报告未修改任何代码、数据与基线，未运行 `apply/export/codegen/probe/match`。
- 行号说明：文中 `file:line` 均为本次审计时用 `grep -n` / `sed -n` 实测所得；仓库演进后行号可能漂移，复现命令见 §6。

---

## 0. 结论摘要

1. **五阶段的"阶段边界"在 CLI 层是清晰的，但在实现层不是**：`codegen all` 内部会跑 `probe s2`、`snapshot capture` 与两个 lint + `compile_regression`（`pipeline/cli.py:553-623`）；`match` 的裁判脚本 `compare_pal3.py` 在执行测量的同一趟里**非 scoped 时写 `s4_baseline.json`**（`pipeline/compare_pal3.py:983-1003`）。也就是说"测量"和"记分/落基线"没有分成两个动作。
2. **codegen 侧注解读点是失效的**：CLAUDE.md 写"尚有 3 处直读"并给了三个行号，**这三个行号现在都不是注解直读**（其中一个已改为 `annotation_view` 导入）。用跨行路径扫描 + 逐行核对重数，实测静态直读为 **38 处 / 8 文件**（`emit_headers.py` 18、`stage4_substitution.py` 7、`emit_cpp.py` 4、`type_registry.py` 4、`collect.py` 2、`scoped_targets.py`/`ref_params.py`/`ast_transform.py` 各 1；明细见 §2.3）。此前「12 处 / 3 文件」是单行 grep 的漏计（路径被拆成 `'data' / 'annotations'` 多行），已按独立验收意见改正。
3. **export 同时是"读注解"和"写 IDB"**：读注解有文件头声明（`[t4-DECLARED-EXCEPTION]`），共 **7 个标记点 / 8 份文件读取**（`:457` 一次读 `structs/*.json` + `functions.json` 两份；grep 9 命中含 `:38`/`:42` 两行头注释），属 CLAUDE.md 已声明取舍。**但 `:457-521` 的 mangler pre-pass 会 `ida_name.set_name` 写回 IDB（自注"实测 3276 次"），与文件头 `:2` 的 "Pure export - no modifications to IDB" 自述直接冲突**，CLAUDE.md 未声明——这是本次发现的一个未声明副作用（见 L4b/D14）。
4. **基线不是单写者**：`s4_baseline.json` 由 `compare_pal3.py` 与 `cli.py` 两处写；S2 有两份基线（`compile_baseline.json` / `baselines/latest.json`）再加链接层 `link_census.json`；`preflight.py` 不得不用 `known_red_gates` 专门给它们对账（`pipeline/preflight.py:160`）。
5. **可测试性在本机已破**：默认 `python -m pytest --collect-only -q` **EXIT=2**，1775/1783 收集、4 个收集错误；`tests/test_preflight.py` 整个模块被 `pytestmark = skip` 关掉；仓库**没有 CI**（无 `.github/workflows`、无 `.gitlab-ci.yml`），pre-commit 只跑 `pipeline/cli.py check`。门禁测试存在但大多默认不执行，等于"有测试资产、无回归防线"。
6. **最大的单点体量集中在 `pipeline/gen/stages/emit_headers.py`（5844 行）与 `pipeline/cli.py`（1322 行，命令分发 + 编排 + 棘轮策略 + 报告写出 + 编译全在一处）**。建议按 §3 的"单写者 / 测量与策略分离 / 生成器纯净 / 注解读点唯一 / IDA 层不依赖 gen / 导出幂等"**六条红线**（R-A…R-F）重构，按 §3.3 的 **6 个 PR** 渐进落地，不需要一次性大改。

---

## 1. 五阶段数据流

### 1.1 总图

```
data/annotations/**  ──┐
 (structs/functions/   │  apply: 先跑 cli.py check（闸口），再 IDA 脚本写 IDB
  globals/vtables/     │
  skip_functions ...)  ▼
                 ┌───────────────────────────┐
                 │ work IDB                  │
                 │ original/PAL3.exe.i64     │
                 └───────────┬───────────────┘
                             │ export: IDA 导出（7 个注解直读标记/8 份读取=声明例外；
                             │         另写 IDB mangled 名 set_name=未声明副作用）
                             ▼
        ┌─────────────────────────────────────────────┐
        │ asm/pal3/decomp/**  (Hex-Rays JSON 语料)     │
        │ asm/pal3/ida_structs.json (结构快照)         │
        └───────────┬─────────────────────────────────┘
                    │ codegen: AST 变换 + 发射（另读 data/annotations/**）
                    ▼
        ┌─────────────────────────────────────────────┐
        │ pal3/src/**  (C++ 源 + 头)                   │
        └───────────┬─────────────────────────────────┘
                    │ probe: MSVC 编译（s1 头 / s2 cpp），不链接
                    ▼
        ┌─────────────────────────────────────────────┐
        │ data/status/probe_census.json                │
        │ data/status/compile_baseline.json (快照基线) │
        │ data/status/baselines/latest.json (正式基线) │
        │ data/status/link_census.json (链接层，全量)  │
        └───────────┬─────────────────────────────────┘
                    │ match: 重编 + 逐函数字节比较（compare_pal3.py）
                    ▼
        ┌─────────────────────────────────────────────┐
        │ data/status/s4_baseline.json  (L1 真值)      │
        │ data/status/s4_diff_detail.json              │
        │ data/status/pal3_registry.jsonl              │
        │ data/status/s4_l1_identity_cur.json          │
        └─────────────────────────────────────────────┘
```

### 1.2 逐阶段表

| 阶段 | 入口（CLI） | 输入（读） | 输出（写） | 关键模块 | 关键 file:line |
|---|---|---|---|---|---|
| apply | `pipeline/cli.py apply` | `data/annotations/**`、work IDB | work IDB（类型/名字/结构体）、`pipeline/ida/_logs/apply_annotations_log.txt` | `ida/apply_annotations.py`、`ida/fix_vtable_types.py` | `cli.py:350`（闸口 `:357-363`、失败 `exit 1 :371-384`、advisory `:390`） |
| export | `pipeline/cli.py export` | work IDB、**`data/annotations/**`（7 个标记点/8 份读取，声明例外）** | `asm/pal3/decomp/**`、`asm/pal3/ida_structs.json`、`pipeline/ida/_logs/pal3_export_only_log.txt`；**并写回 work IDB（`ida_name.set_name` mangled 名，自注 3276 次）** | `ida/export_full.py` | `cli.py:395`（失败 `:427-430`、一致性 advisory `:436-443`）；`export_full.py:2`（"no modifications" 自述）vs `:457-521`（实际写 IDB） |
| codegen | `pipeline/cli.py codegen all` | `asm/pal3/decomp/**`、**`data/annotations/**`（38 处未收敛直读，见 §2.3）**、`asm/pal3/ida_structs.json` | `pal3/src/**` + `data/status/_decomp_derived_header_facts.json`、`data/status/adjudication_queue.json`、`data/status/vtable_transform_failures.md`；**并触发 probe/snapshot/lint** | `gen/codegen.py`、`gen/data.py`、`gen/ast_transform.py`、`gen/stages/*` | `cli.py:516`（内嵌 `probe s2 :553-563`、`snapshot :565-571`、`param_lint :582-590`、`invariant_lint :600-610`、`compile_regression :612-623`） |
| probe | `pipeline/cli.py probe all\|s1\|s2` | `pal3/src/**`（头/cpp）、`build/` 产物 | `data/status/probe_census.json`；无退化时 `data/status/baselines/latest.json`；全量再写 `data/status/link_census.json`；报告目录 `pipeline/_logs/regression_detection/` | `pipeline/probe_compile.py`、`tools/regression_detector.py`、`pipeline/link_probe.py` | `cli.py:911`（check `:940`、不刷新 `:944-970`、save `:974`、link `:988-995`） |
| match | `pipeline/cli.py match` | `data/status/probe_census.json`、`pal3/src/**`、`asm/pal3/decomp/**`、`PAL3.exe .text`、`data/status/expected_symbols.json`、**旧 `s4_baseline.json`** | `s4_baseline.json`、`s4_diff_detail.json`、`pal3_registry.jsonl`、`s4_l1_identity_cur.json`；退化时 `data/status/archive/*` | `pipeline/compare_pal3.py`、`pipeline/s4_pair.py` | `cli.py:704`（读旧基线 `:744`、跑 compare `:757`、棘轮 `:788-798`、`--rebaseline :810-815`、成对恢复 `:890-901`、`exit 1 :904-906`） |

补充事实：

- `init` 是**另一个**入口（不是五阶段之一）：`cli.py:296-319` 先 `master_pipeline.py`，再**两趟** `apply_annotations.py`——单趟无法完成"造 item → 挂类型 → 命名"的依赖链（`:305-314` 注释给出实测读数）。`apply` 命令本身只跑一趟 + `fix_vtable_types.py`（`cli.py:371-375`）。
- `probe` 的 s1/s2 只编译不链接；链接层（LNK2005/LNK2001）仅在全量 `probe` 末尾通过 `link_probe --check` 覆盖（`cli.py:988-995`），`codegen` 链里的 `probe s2` 不触发它（`:984` 注释）。
- `match` 的编译参数固定为 `/nologo /TP /c /W3 /O2 /Ob2 /Oi /Ot /Oy /GF /Gy /GX /GR /MT /Gd`（`cli.py:755-757`），与 `compare_pal3.py` 的口径同源。
- `snapshot capture` 不重编，只把 `probe_census.json` + decomp 语料整理进 `pipeline/snapshots/data/<snap>/` 的 7 个文件（`meta/decomp_summary/compile_result/*.txt`）。

### 1.3 产物归属（谁写什么）

| 产物 | 写者 | 依据 |
|---|---|---|
| `pal3/src/**` | `gen.codegen`（`cmd_clean` 会整目录删除，`gen/codegen.py:85-98`） | 生成器产物 |
| `asm/pal3/decomp/**`、`ida_structs.json` | `ida/export_full.py` | 导出产物 |
| work IDB 函数名（mangled） | `ida/export_full.py:520-521`（`ida_name.set_name`，pre-pass） | 见 L4b |
| `data/status/probe_census.json` | `pipeline/probe_compile.py:279-280` | 测量结果 |
| `data/status/compile_baseline.json` | `tools/compile_regression.py:68-70`（`--update-baseline`） | 快照闸基线 |
| `data/status/baselines/latest.json` | `tools/regression_detector.py:136-189`（`--save-baseline`） | 正式 S2 基线 |
| `data/status/link_census.json` | `pipeline/link_probe.py:239-242`（`--rebaseline`）/ `--check` 通过时刷新 | 链接层基线 |
| `data/status/s4_baseline.json` | **两处**：`compare_pal3.py:983-1003`（非 scoped 时每次测量都写）与 `cli.py:811`（`--rebaseline`）/`:851`（pairing-infra 对齐） | 见 L1 |
| `data/status/s4_diff_detail.json` | `compare_pal3.py`；退化时由 `s4_pair.restore_pair` 回滚 + `archive/` 存档 | 诊断明细 |
| `data/status/_decomp_derived_header_facts.json` | `emit_headers.py:355`（`save_header_facts`） | 见 L6 |
| `data/status/adjudication_queue.json` | `emit_cpp.py:1346-1359` | 见 L6/L7 |
| `data/status/vtable_transform_failures.md` | `stage3_cleanup.py:616/:1017/:1073` | 见 L6 |
| `data/status/canonical_contract_baseline.json`、`n12_grandfathered.json`、`n22_pair_closure.json`、`asm/pal3/annotation_dep_graph.json` | **`check_annotations.py` 在"检查"过程中自举写**（`:1819`、`:2171`、`:2404`、`:984`） | 见 L12 |
| `pipeline/_logs/loop_<stage>.log`、`data/status/_loop_last.json` | `cli.py:1181-1183`、`:1228-1233` | loop 编排 |

---

## 2. 逐阶段职责与错层操作

### 2.1 各阶段"必须做"与副作用

| 阶段 | 必须做 | 额外副作用 |
|---|---|---|
| apply | 校验注解（`cli.py check`）；把 structs/functions/vtables/globals 写入 IDB；`fix_vtable_types.py` 修 vtable 指针类型 | `fix_vtable_types.py` 非零只 WARN 不阻断（`cli.py:386-390`），可能让后续 export 拿半更新 IDB；`_run_invariants_advisory` 跑不变量但只 advisory |
| export | 从 IDB 导出 decomp JSON 与 `ida_structs.json`；mangler pre-pass 用注解里的 `Class::Method` 名对 IDB 函数 `set_name` | 读 7 个标记点注解（声明例外）；**写 IDB 名称**（`export_full.py:457-521`，与文件头 `:2` 自述冲突）；一致性检查与不变量检查都只是 advisory（`cli.py:436-444`） |
| codegen | 从 decomp + annotations 生成 `pal3/src/**` | 写 3 个 `data/status` 文件；**内嵌 probe/快照/lint/compile_regression**，可能因编译退化而 `exit 1`（与"生成本身"无关的失败） |
| probe | 编译 s1/s2 并写 census；对账后刷新基线 | 在同一命令里**既测量又刷新基线**；全量时再跑链接层检查并可能刷新 `link_census.json` |
| match | 重编 + 逐函数字节比较 + 棘轮判定 | **裁判脚本本人写基线**；退化时由 CLI 再做一次"成对恢复 + 存档"；population 变化仅告警（`:799-802`） |

### 2.2 错层操作清单

| ID | 错层操作 | 证据 | 影响 | CLAUDE.md 已声明例外？ |
|---|---|---|---|---|
| L1 | `compare_pal3.py` 在测量同趟**非 scoped 时写 `s4_baseline.json`** | `pipeline/compare_pal3.py:983-1003`；`cli.py:744` 在调用 compare（`:757`）之前先读旧基线，`:788-798` 再判棘轮 | 手工直接跑 `compare_pal3.py`（诊断场景）会**静默重锚**而不触发棘轮；"裁判"与"记分员"同一模块，任何单独调用它的人都可能改掉真值 | 部分（CLAUDE.md 只警告"棘轮会回写基线"，未声明"裁判自己写基线"） |
| L2 | `probe` 同命令内测量 + 刷新基线 | `cli.py:940-974` | 语义上可接受（先 `--check` 后 `--save-baseline`），但"测量"与"落基线"仍是同一个 verb；回滚需要人工 `--rebaseline` 或还原文件 | 否（检查点表只写"probe 后跑 error_classifier/match"） |
| L3 | `codegen all` 内嵌 `probe s2` + `snapshot` + `compile_regression` | `cli.py:553-623`；`:540-552` 注释自述"CLAUDE.md 的检查点表也缺了这一步" | 生成器不再是纯函数：耗时、退出码、日志都被编译结果污染；`--skip-probe` 会让 `compile_regression` 基于陈旧 census（注释自己承认"结论无意义"，`:544-547`） | 否；且**文档与代码已经分叉**（CLAUDE.md 检查点表仍写"codegen all 后跑 compile_regression"） |
| L4a | `export_full.py` 读 `data/annotations/**`（7 个标记点 / 8 份读取） | `pipeline/ida/export_full.py:277/:408/:457/:568/:994/:1345/:1378`，文件头 `:38-42` 声明；grep `t4-DECLARED-EXCEPTION` 9 命中（`:38`/`:42` 两行头注释 + 7 个标记点） | 导出输入不是"纯 IDB"：改注解但未 apply 时，导出结果可能"看起来新、实际 IDB 旧"，产生双源不一致 | **是**（文件头 + CLAUDE.md 明示） |
| L4b | **`export_full.py` 写回 IDB**（mangler pre-pass 用注解名 `ida_name.set_name` 重命名 3276 个地址） | `export_full.py:457-521`（`:520-521` 为 `set_name` 调用；`:459` 自注"这段写 IDB，与文件头 no modifications to IDB 的自述不符"）；文件头 `:2` 仍写 "Pure export - no modifications to IDB"；`cli.py:311-314` 亦自注"疑与 export 也会改 IDB 有关" | 导出不是幂等只读：export 会永久改 work IDB 的函数名；`apply` 与 `export` 相对顺序可能影响命名结果；"验证前 apply→export" 的前提（export 不改数据）不成立；备份/回滚策略缺失 | 否（CLAUDE.md 只说 export 不读 annotation，未提写 IDB） |
| L5 | **codegen 直读注解 38 处 / 8 文件** | 完整清单见 §2.3。高密度文件：`emit_headers.py` 18 处（structs 全量 glob ×2、templates ×4、structs/&lt;cls&gt; ×3、domain_exclude ×2、type_aliases/sdk_types/template_bases/enums/globals ×5、globals `read_text` ×1）、`stage4_substitution.py` 7 处、`emit_cpp.py` 4 处、`type_registry.py` 4 处、`collect.py` 2 处、`scoped_targets.py`/`ref_params.py`/`ast_transform.py` 各 1 处 | 违反"新增注解直读必须走 `annotation_view`"红线：这些点绕过 `strip_ovl`（`__ovl_` 单点剥离）与坏 JSON 的 fail-visible 处理；schema 变更要改 N 处；C1 若只按 3 个文件改，lint 落地当天就会被打红。CLAUDE.md 的"3 处/三个行号"也已全部漂移（`ast_transform.py:336-342` 现为 `annotation_view` 导入、`stage3_cleanup.py:107-110` 现为 `OwnerPath` 类、`emit_headers.py:3259-3260` 现为 vtable 注释） | 否（无 `[t4-DECLARED-EXCEPTION]` 头，也无 CLAUDE.md 条目；规则本身要求走单点） |
| L6 | codegen 写 `data/status/*` 产物 | `emit_headers.py:355`（`save_header_facts`）；`emit_cpp.py:1346-1359`；`stage3_cleanup.py:616/:1017/:1073` | `data/status` 是"测量/门禁状态"目录，生成器往里写会模糊"谁拥有 status"；清理/重跑语义不明；审计时难以区分"生成产物"与"测量结果" | 否 |
| L7 | `emit_cpp` 导入 `emit_headers` 的**进程内可变全局** `_ADJUDICATION_QUEUE` | `emit_cpp.py:1346-1359`（import + flush）；`gen/codegen.py:105-118` 在**同一进程**先 headers 后 cpp | stage 顺序/进程边界变成隐式契约：单独跑 `codegen cpp` 时队列为空（对应决策丢失），把两个 stage 拆进程或并行会静默改变输出 | 否 |
| L8 | `annotation_view` 位于 `pipeline/gen/`，却被 `pipeline/ida/export_full.py` 导入 | `export_full.py:16` `import pipeline.gen.annotation_view` | 依赖方向倒置：IDA 层反向依赖 codegen 包；`gen` 的目录调整会破坏 export；单点读模块无法被两层公平共享 | 否 |
| L9 | `cli.py` 单文件承担命令分发 + 阶段编排 + 棘轮策略 + 基线写 + 日志/报告 + 编译 | `cli.py` 1322 行；策略段集中在 `:788-906`，编排 `:350-1051`，编译 `:997-1051` | 改任何一条策略都要动 CLI；策略无法单测（只能通过 e2e 真跑 match）；评审面过大 | 否 |
| L10 | 三套 S2/L1 基线 + 三套门禁语义重叠 | `preflight.py:160` 的 `known_red_gates` 专门处理 `compile_baseline` vs `baselines/latest` 不一致；`preflight.py` docstring 记录 76/206 vs 75/205 vs L1 38 的历史矛盾 | 新人无法判断"以哪份为准"；两份 S2 基线不同步时门禁失去判别力；status 需常年背特例 | 部分（CLAUDE.md 承认三份基线曾矛盾，并警告"不能事后查基线文件判断退化"） |
| L11 | 自动化防线缺失 + 默认测试套件当前不可用 | 无 CI 配置；`.git/hooks/pre-commit` 只跑 `cli.py check`；`pytest --collect-only` EXIT=2（4 个收集错误，见 §4.2） | 回归只能靠人工记得跑；pre-commit 只覆盖注解一致性，不覆盖 codegen/probe/match；新环境 `pytest` 直接红 | 否 |
| L12 | `check_annotations.py` 在"检查"中**自举写基线/工作清单** | `:1819` 写 `data/status/canonical_contract_baseline.json`、`:2171` 写 `n12_grandfathered.json`、`:2404` 写 `n22_pair_closure.json`、`:984` 写 `asm/pal3/annotation_dep_graph.json` | 声称"只读校验"的命令在首次运行会改仓库；`git status` 无法区分"我的改动"与"检查器自举"；CI 首次运行与本地不一致 | 否 |
| L13 | 死代码/空槽：`iterate` 命令不可用；`apply_scoped_env()` 定义了但无人调用 | `cli.py:1285-1297`（打印 UNAVAILABLE 并 `exit 2`）；`cli.py:1313`；`gen/codegen.py:155-162` 注释明确"cli.py 的 apply_scoped_env() 写了却没调用" | 认知负担；新人以为存在"自动迭代引擎"；射程过滤靠环境变量裸传，无统一入口 | 否 |

**定量小结**：14 项错层中（L4 拆为 L4a/L4b），**明确声明例外的只有 L4a（export 读注解）**；L4b/L5/L6/L7/L8/L12 属于未声明的规则违反、自述冲突或隐式耦合；L1/L2/L3/L10 属于"设计取舍未显式化"，危害是**改变行为的入口比人以为的多**（单独跑 `compare_pal3.py` 会改基线、`codegen all` 会编译、`check` 会写文件、`export` 会改 IDB）。

### 2.3 codegen 注解直读清单（38 处 / 8 文件）

统计口径：`pipeline/gen/**` 中**直接** `open()` / `json.load()` / `read_text()` / `glob()` 读 `data/annotations/**` 的位置；排除单一读点 `annotation_view.py` 与 `test_*.py`；`glob` 与其后的 `load` 合并为 1 处（同一次读取动作）。跨行路径（`'data' / 'annotations'`）用 §6 的脚本扫描，再逐行核对、去掉 exe/evidence pack/gbengine 头/写文件/`ida_structs.json` 等非注解目标。

| 文件 | 处数 | 行号（读的文件 / 用途） |
|---|---|---|
| `emit_headers.py` | 18 | `:55` structs 全量 glob（vtable slot 地址缓存）· `:89` structs 全量 glob（imported_dll）· `:419` domain_exclude · `:475` type_aliases · `:508` sdk_types（路径经 `annotation_json_path`，open 直读）· `:838` template_bases · `:861` templates · `:917` structs/&lt;cls&gt;（declaration_only）· `:980` enums（`_ANNOTATION_ENUMS_PATH`）· `:1107` domain_exclude · `:1132` templates · `:1821` structs/&lt;cls&gt;（vfptr_slot 标记）· `:1897` templates · `:4101` structs/&lt;cls&gt;（G1b methods）· `:4821` globals（强制类型）· `:5030` globals（skip 过滤）· `:5387` templates · `:5634` globals（`read_text`） |
| `stage4_substitution.py` | 7 | `:2288` mrect_allowlist · `:2297` fcg_tail_allowlist · `:2308` ac_family_cast_allowlist（`_al4 = dirname(_al_path)/…`）· `:2318` type_leak_allowlist（同款派生）· `:2355` structs 全量 glob（sig cache）· `:2394` structs 全量 glob（base names）· `:2427` structs 全量 glob |
| `emit_cpp.py` | 4 | `:49` structs/&lt;cls&gt;（调用约定查询）· `:91` fold_carrier_aliases · `:111` structs/&lt;qual&gt;（折叠别名地址校验）· `:921` structs/&lt;cls&gt;（declaration_only） |
| `type_registry.py` | 4 | `:83` enums · `:107` type_aliases · `:141` structs 全量 glob（类属枚举）· `:171` sdk_types |
| `collect.py` | 2 | `:95` domain_exclude · `:454` structs/&lt;cls&gt; |
| `scoped_targets.py` | 1 | `:30` structs/&lt;cls&gt; |
| `ref_params.py` | 1 | `:245` structs 全量 glob |
| `ast_transform.py` | 1 | `:192` structs/*.json（路径枚举已走 `iter_struct_files`，但 `json.load` 仍自读） |

说明：① 扫描脚本原始命中 53 行，其中自动识别 34 处（其余为 exe/pack/gbengine/写文件/ida_structs 等非注解目标或 glob+load 同一处），另 **4 处需人工补记**——`emit_headers.py:980`（路径是常量 `_ANNOTATION_ENUMS_PATH`，字面量距读点 18 行）、`ast_transform.py:192`（路径来自 `annotation_view.iter_struct_files`，读点窗口内无 `annotations` 字面量）、`stage4_substitution.py:2308` 与 `:2318`（路径是 `dirname(_al_path)` 派生，`_al_path` 定义在 `:2285`、距读点 23 行，超出 ±15 行窗口）；② 本报告第 1 版写的「12 处 / 3 文件」是单行 grep 漏计（绝大多数路径被拆成多行），不成立；③ **lint 必须跟随 `annotation_json_path` / `dirname(注解路径变量)` 的派生读取**，只扫字面量会漏掉上面 4 处，无法自证清零；④ 两处边界已排除并说明：`stage4_substitution.py:2329-2331` 的 `sig3_allowlist.json` 读取**整段被注释**（`:2327` 注明清单/库/测试保留但接线回退），不计入；`ast_transform.py:346-354` 用 `os.listdir(data/annotations/structs)` 只枚举类名、内容经 `annotation_view.struct_by_class` 读取，按「直接读文件内容」口径不计入，若 lint 目标升级为「零目录布局依赖」需一并覆盖。⑤ 这 38 处是 C1/PR1 的真实改动面，缺一个都会让「零直读 lint」在落地当天打红。

---

## 3. 模块化边界提案

### 3.1 目标边界（职责 → 模块）

```
pipeline/
├── cli.py                 # 只做参数解析 + 调用例；不含策略、不含 IDA 细节（目标 <300 行）
├── config.py              # 保留
├── annotations.py         # 由 gen/annotation_view.py 上移：唯一注解读点
│                          #   strip_ovl / structs_dir / iter_structs / load_annotation_json / template_bases
├── stages/                # 每个阶段一个"用例"，只编排不实现细节
│   ├── apply.py
│   ├── export.py
│   ├── codegen.py         # 纯生成：不 probe、不 snapshot、不写 status
│   ├── probe.py           # 只测量：写 census
│   └── match.py           # 只测量：调 measurement.byte_compare
├── measurement/
│   ├── compile_census.py  # 由 probe_compile.py 迁入（纯：给定源树 → census）
│   └── byte_compare.py    # compare_pal3.py 的测量部分（纯：给定 census/源/exe → stats+rows+diff）
├── baselines.py           # 唯一基线读写：compile / latest / s4 / link
│                          #   每个基线带 producer、generated_at、schema_version
├── ratchet.py             # 纯函数策略：prev + cur + policy → decision
│                          #   {accept, rebaseline, restore_pair, align_pairing_infra, reason}
├── artifacts.py           # 唯一 data/status 写点（报告/清单/队列/失败表）
├── preflight.py           # 只读读模型（保留，继续只读）
├── s4_pair.py             # 保留（成对恢复工具）
└── snapshots/             # 保留
```

`pipeline/ida/*` 只允许依赖 `pipeline/annotations.py` 与 IDB API；**不允许** import `pipeline.gen.*`。
`pipeline/gen/*` 只允许依赖 `pipeline/annotations.py`、`pipeline.artifacts.py`；**不允许**写 `data/status` 基线。

### 3.2 依赖方向与红线

目标依赖方向（箭头 = 依赖）：

```
cli ──> stages ──> { measurement, gen, baselines, ratchet, artifacts } ──> annotations
ida ──> annotations
preflight ──> baselines (只读)
```

六条可检查红线：

- **R-A 单写者**：`data/status/*baseline*.json`、`link_census.json`、`s4_baseline.json` 只能由 `baselines.py` 写；stage 只产出测量对象。
- **R-B 测量与策略分离**：`measurement/*` 返回纯数据；`ratchet.py` 用纯函数决定 `accept/restore/align/rebaseline`；CLI 只执行决策。
- **R-C 生成器纯净**：`codegen` 不编译、不探测、不写 status；`probe`/`snapshot`/`compile_regression` 由 `loop` 或显式 `gate` 步骤调用（保留一个版本周期的 `--with-probe` 兼容开关）。
- **R-D 注解读点唯一**：所有注解 JSON 读取经 `annotations.py`；用 AST lint 禁止 `pipeline/gen/**` 与 `pipeline/ida/**` 出现 `data/annotations` 字面路径直读（白名单仅 `annotations.py` 与 export 的已声明例外，且例外须带标记）。
- **R-E 层向不倒置**：`pipeline/ida/**` 不得 import `pipeline/gen/**`。
- **R-F 导出幂等**：`export` 要么只读（命名统一由 apply 完成），要么在文件头与 CLAUDE.md 显式声明"export 会写 IDB 名称"，并在 `cli.py export` 前后记录名称 diff（连续两次 export 的第二次 diff 必须为空）。

**与现状/既有红线的冲突点（必须显式处理）**：

- R-C 与 CLAUDE.md 检查点表冲突：表里写"`codegen all` 后跑 `compile_regression`"，但代码已经把 probe 内嵌。落地 R-C 时**同时更新 CLAUDE.md 检查点表**，否则文档继续误导。
- R-A 与 `compare_pal3.py` 的独立可用性冲突：诊断时需要"只测量不落基线"，因此 `byte_compare` 必须提供"纯测量"入口（默认不写文件），落基线由 `stages/match.py` 调 `baselines.py` 完成。
- R-D 与 export 的已声明例外冲突：export 的 8 份读取（7 个标记点）保留，但要求在文件内集中到一个 `_load_annotation()` 帮助函数（**不改变行为**），并让 lint 只对 `pipeline/gen/**` 强制。
- R-B 与 `s4_pair` 的存档语义：`restore_pair` 已是纯工具（接受文本参数），继续由决策层调用，不进 measurement。

### 3.3 最小改动路径（按风险从低到高，6 个 PR）

| PR | 内容 | 改动面 | 行为变化 | 验证方式 |
|---|---|---|---|---|
| PR1 | **注解直读收敛 + lint**：把 §2.3 的 38 处改为经 `annotations.py`；新增 `tests/test_annotation_read_single_point.py`（AST 扫描 `pipeline/gen/**`，白名单 `annotations.py`） | `pipeline/gen/**`、`tests/` | **产物字节应完全不变** | codegen 前后 `pal3/src` 全树 hash 对比 + `pytest tests/test_annotation_read_single_point.py` |
| PR2 | **抽出 `ratchet.py` + 表驱动单测**：把 `cli.py:788-906` 的判据迁为纯函数；`compare_pal3.py` 增加 `--no-write-baseline`（默认仍写，兼容期） | `cli.py`、`compare_pal3.py`、新增 `pipeline/ratchet.py`、`tests/test_ratchet_policy.py` | 同一输入决策不变（表驱动对齐旧输出） | 用当前 `s4_baseline.json` + `s4_diff_detail.json` 构造 6 个用例（accept / L1 退化 / semantic 豁免 / pairing-infra 对齐 / population 变化 / rebaseline） |
| PR3 | **基线单写者**：`baselines.py` 统一读写四份基线；`probe`/`match` 停止直接写 | `pipeline/baselines.py`（新）、`cli.py`、`compare_pal3.py`、`probe_compile.py` 调用点 | 文件格式不变；写点收敛 | `pytest tests/test_baselines_single_writer.py`（tmp_path 断言只有 baselines 模块写）+ 一次真实 `probe s2` 后 diff 基线内容 |
| PR4 | **编排拆出 codegen 内嵌门禁**：新增 `cli.py gate`（probe s2 + snapshot + compile_regression + lint），`codegen all` 默认只生成，`--with-probe` 保留一版 | `cli.py`、`pipeline/stages/codegen.py` | `codegen all` 变快且退出码只反映生成；`loop` 显式调 gate | `loop --expect-*` 断言 + `codegen all` 前后 `pal3/src` hash 不变 |
| PR5 | **`annotation_view` 上移** + export 导入更新 + 文件内 `_load_annotation()` 集中 | `pipeline/annotations.py`（新，从 gen 迁）、`export_full.py:16`、`gen/**` 导入 | 无 | 全量 `pytest`（修好收集后）+ 一次 `apply→export` 产物 diff |
| PR6 | **export 幂等化**（R-F）：把 mangled 命名迁到 apply，或声明并记录 IDB 名称 diff | `pipeline/ida/export_full.py`、`pipeline/ida/apply_annotations.py`（命名容量核对）、`pipeline/cli.py`、`CLAUDE.md` | 连续两次 export 的 IDB 名称 diff 为空；导出可重复执行 | 同一 IDB 连跑两次 `export`，比较 `ida_name` 快照（名称→地址）差异为空；`apply→export` 产物 hash 不变 |

PR1/PR2 可以并行（改动面不重叠）；PR3 依赖 PR2 的决策边界；PR4/PR5 独立。

### 3.4 与 `annotation_view` 单点读规则的关系

- 现状：规则**只写在 CLAUDE.md**，没有机器检查；38 处直读（§2.3）就是规则失效的直接证据。
- PR1 把规则变成**可执行的 lint**（R-D），并顺带修正 CLAUDE.md 里已漂移的"3 处/三个行号"表述。
- PR5 解决 L8：单点读模块从 `gen/` 上移到 `pipeline/` 顶层，IDA 层与 codegen 层共享同一读点，依赖方向恢复单向（`ida → annotations`，而非 `ida → gen`）。
- 已声明例外（export 的 7 个标记点 / 8 份读取）**不迁**，但集中为文件内帮助函数并保留 `[t4-DECLARED-EXCEPTION]` 标记；lint 的例外清单直接读该标记，避免"例外又长出口头传统"。

---

## 4. 可测试性

### 4.1 现有资产（实测）

| 资产 | 数量/内容 | 依据 |
|---|---|---|
| `tests/**` | 顶层 154 个 `*.py`；递归 173 个（含子目录） | `ls tests/*.py \| wc -l` → 154；`find tests -name '*.py' \| wc -l` → 173 |
| `pipeline/gen/test_*.py` | 34 个 | `ls pipeline/gen/test_*.py` |
| `pipeline/test_*.py` | 2 个 | — |
| `tools/test_*.py` | 3 个 | — |
| pytest 收集 | 1775/1783 收集、8 deselected（`-m "not slow"`） | `python -m pytest --collect-only -q`，**EXIT=2** |
| CI | **无**（无 `.github/workflows`、无 `.gitlab-ci.yml`） | `ls -a` / `find . -name '*.yml'` |
| pre-commit | 只跑 `PYTHONUTF8=1 python pipeline/cli.py check`；另对 `experiments/ghidra_track` 特定文件跑 `gate.sh` | `.git/hooks/pre-commit` |
| 有效的门禁单测 | `tests/test_s4_pair.py`（`restore_pair` 成对恢复）；`tests/e2e/test_probe_baseline_injection.py`（默认运行，注入假退化，断言不刷新基线，finally 还原）；`tests/test_annotation_view_fail_visible.py`（坏 JSON fail-visible） | 文件内容 |
| 默认不跑的门禁单测 | `tests/e2e/test_l1_ratchet_injection.py`（需 `PAL3_E2E_INJECTION=1`，真跑完整 match，数分钟）；`tests/test_preflight.py`（整模块 `pytestmark = skip`） | 文件内容 |

### 4.2 实测缺陷

1. **默认测试命令直接失败**：`python -m pytest --collect-only -q` → **EXIT=2**，4 个收集错误：
   - `pipeline/ida/test_lvar_apply.py`：`ModuleNotFoundError: No module named 'ida_funcs'`
   - `pipeline/ida/test_settype_thiscall.py`：`ModuleNotFoundError: No module named 'ida_auto'`
   - `tools/test_scan_misattribution.py`：`ModuleNotFoundError: No module named 'tools.scan_misattribution'`
   - `tools/test_t1b.py`：`ModuleNotFoundError: No module named 'tools.t1b'`
   ⇒ 本地/新环境第一次跑测试就是红的，等于全仓测试套件不可作为门禁。
2. **preflight/loop 契约测试整体关闭**：`tests/test_preflight.py` 模块级 `pytestmark = pytest.mark.skip(reason="数据依赖（match stage 可选） —— 待夹具更新")`。而 `preflight.py` 正是"三份基线对账 + 已知恒红门禁"的唯一读模型——它没有活测试。
3. **L1 棘轮负例默认不跑**：`tests/e2e/test_l1_ratchet_injection.py` 仅当 `PAL3_E2E_INJECTION=1` 才执行，否则函数体直接 `return`（不是 skip，CI 里看起来是"通过"）。棘轮是 match 阶段最关键的防线（ADR 要求"必须能被人为降低的 partial 触发"），却默认不验证。
4. **无 CI**：以上三条只靠开发者记得，且没有"每次 push 跑哪些检查"的定义；pre-commit 只覆盖 `check`。
5. **既有覆盖缺口（未被任何测试固定）**：
   - `compare_pal3.py` 的 ratchet / `pairing-infra` 自动对齐 / population 告警分支（只有被 env 关掉的 e2e 间接覆盖）；
   - `codegen` 的 38 处注解直读（§2.3，无 lint）；
   - `codegen all` 内嵌 probe/snapshot 的编排契约（无测试）；
   - 基线的"单写者/格式/版本"契约；
   - `check_annotations.py` 自举写基线的行为（首次运行 vs 已有基线）。

### 4.3 高价值低成本缺口（按性价比排序）

| 编号 | 缺口 | 成本 | 价值 | 建议 |
|---|---|---|---|---|
| T1 | 默认 pytest 不可用（4 收集错） | 低（1 个 `conftest.py` 让 `tools/` 可导入；IDA 专属测试移到 `tests/ida/` 并在缺 `ida_*` 时 `pytest.importorskip`） | 极高：恢复整套测试作为门禁的前提 | P0 |
| T2 | `tests/test_preflight.py` 被整体 skip | 中（它已有合成状态构造器 `_state()`，把"数据依赖"的少数用例拆到 `test_preflight_live.py`，其余恢复） | 高：preflight/loop 读模型有活契约 | P0 |
| T3 | 棘轮策略无纯函数测试 | 中（需先做 PR2 的 `ratchet.py`） | 高：match 防线可表驱动验证 | P1 |
| T4 | 注解直读无 lint | 低（AST 扫描 + 白名单，PR1 附带） | 高：把 CLAUDE.md 红线变成可执行 | P1 |
| T5 | 基线单写者无契约测试 | 中（需先做 PR3） | 中：防"三份基线再分叉" | P2 |
| T6 | e2e 注入测试默认不跑 | 低（加 `pytest.ini` 的 `slow` 标记与 CI nightly 任务） | 中：需配合 CI 才有意义 | P2（依赖 CI） |

---

## 5. 债务清单与拆卡建议

### 5.1 债务清单

| 级别 | ID | 债务 | 关联错层 | 证据 |
|---|---|---|---|---|
| **P0** | D1 | codegen 注解直读 38 处 / 8 文件，规则失效且 CLAUDE.md 描述漂移 | L5 | 见 §2.3 |
| **P0** | D2 | 默认 `pytest` EXIT=2（4 收集错），测试套件不可作为门禁 | L11 | §4.2 第 1 条 |
| **P0** | D3 | `tests/test_preflight.py` 整模块 skip，preflight/loop 无活测试 | L11 | §4.2 第 2 条 |
| **P0** | D4 | `s4_baseline.json` 双写者（compare_pal3 非 scoped 时每次写 + cli 棘轮写），独立跑 compare 会静默重锚 | L1 | `compare_pal3.py:983-1003`、`cli.py:744/:811` |
| **P1** | D5 | `codegen all` 内嵌 probe/snapshot/compile_regression，生成器不纯；CLAUDE.md 检查点表与代码分叉 | L3 | `cli.py:553-623` |
| **P1** | D6 | `annotation_view` 层位倒置（`ida/export_full.py:16` 依赖 `gen`） | L8 | `export_full.py:16` |
| **P1** | D7 | `check_annotations.py` 在检查中自举写 4 个文件（含 2 个 baseline + 1 个工作清单 + 依赖图） | L12 | `check_annotations.py:984/:1819/:2171/:2404` |
| **P1** | D8 | 跨 stage 进程内可变全局 `_ADJUDICATION_QUEUE`（emit_cpp ← emit_headers） | L7 | `emit_cpp.py:1346-1359`、`codegen.py:105-118` |
| **P1** | D14 | export 写回 IDB 名称（自注 3276 次），文件头自称 "no modifications to IDB"，导出不幂等 | L4b | `export_full.py:2` vs `:457-521` |
| **P1** | D9 | probe 同命令测量+刷新基线（语义可接受，但缺"只测不写"入口） | L2 | `cli.py:937-978` |
| **P2** | D10 | `iterate` 空槽 + `apply_scoped_env` 死代码 | L13 | `cli.py:1285-1297`、`:1313`、`codegen.py:155-162` |
| **P2** | D11 | `pipeline/README.md` 与 `cli.py` 实际命令脱节（仍写手工 IDA 命令，未反映 apply/export/probe/match/status/loop 包装） | — | 读 `pipeline/README.md` 全文 vs `cli.py` docstring |
| **P2** | D12 | advisory 检查无 owner/无到期（export 一致性、MemberExtent、invariants）——"advisory 永不转硬"等于没有 | L4a 邻域 | `cli.py:436-444`、`:499-512` |
| **P2** | D13 | `emit_headers.py` 5844 行单体；`cli.py` 1322 行多职责 | L9 | `wc -l`（见 §6） |

### 5.2 拆卡建议（可直接建 Task）

| 卡 | 标题 | writeScopes | 验收（resultDefinition 摘要） |
|---|---|---|---|
| C1 | 注解直读收敛到单点 + 可执行 lint | `pipeline/gen/**`、`tests/test_annotation_read_single_point.py` | §2.3 的 38 处直读清零（lint 通过）；`pal3/src` 全树 hash 前后一致；CLAUDE.md 的"3 处/行号"表述同步修正 |
| C2 | 修复默认 pytest 收集（4 错） | `conftest.py`、`pytest.ini`、`pipeline/ida/test_*.py` 迁移到 `tests/ida/`、`tools/test_*.py` 的导入方式 | `python -m pytest --collect-only -q` EXIT=0；收集数不少于 1775 |
| C3 | 恢复 preflight/loop 契约测试 | `tests/test_preflight.py`、新增 live/integration 用例 | 非数据依赖用例全部运行并通过；数据依赖用例单独标记 |
| C4 | 基线单写者 + 纯测量入口 | `pipeline/baselines.py`（新）、`pipeline/compare_pal3.py`、`pipeline/cli.py`、`tests/test_baselines_single_writer.py` | 手工跑 compare 不再改基线（默认 `--no-write` 或纯测量 API）；`match` 全链行为不变；tmp_path 单测证明唯一写点 |
| C5 | 抽出棘轮纯函数 + 表驱动测试 | `pipeline/ratchet.py`（新）、`pipeline/cli.py`、`tests/test_ratchet_policy.py` | 6 个策略用例与旧行为逐项对齐；`cli.py` 策略段行数下降 |
| C6 | codegen 去门禁化（`gate` 命令） | `pipeline/cli.py`、`pipeline/stages/codegen.py`（或 `gen/codegen.py` 调用层） | `codegen all` 只生成且退出码只反映生成；`loop` 显式调 gate；`--with-probe` 兼容一版 |
| C7 | `check_annotations` 自举改为显式 `baseline init` | `pipeline/check_annotations.py`、`pipeline/cli.py`、`data/status/*` 相关初始化路径 | 无基线时 check 只报错（不再写文件）；显式 `baseline init` 才自举；首次运行 `git status` 不出现意外新增 |
| C8 | 清理死代码与文档脱节 | `pipeline/cli.py`、`pipeline/README.md` | `iterate` 与 `apply_scoped_env` 删除或接上；README 与 `cli.py --help` 一致 |
| C9 | export 幂等化（或显式声明写 IDB） | `pipeline/ida/export_full.py`、`pipeline/ida/apply_annotations.py`、`pipeline/cli.py`、`CLAUDE.md` | 二选一：(a) mangled 命名移到 apply，export 只读；(b) 保留但在文件头/CLAUDE.md 声明，并在 `cli export` 前后记录名称 diff。验收：同一 IDB 连续两次 export，第二次名称 diff 为空 |

建议顺序：C2（先把测试跑起来）→ C1 → C4/C5 → C3 → C6 → C7 → C8。C1 与 C2 可并行（改动面不重叠）。

---

## 6. 本次审计未覆盖与复现命令

**未覆盖**：

- 未实际运行五阶段（只读审计），因此"产物归属表"基于代码路径静态判定，未对运行期文件时间戳做交叉验证。
- 未逐条审计 `tools/` 下 186 个脚本（只审了门禁链：`compile_regression.py`、`regression_detector.py`、`link_probe.py`、`s4_pair` 相关）。
- 未审计 `pipeline/gen/test_*.py` 34 个文件的逐项覆盖面（只统计数量与失败收集）。
- 未审计 `ida/apply_annotations.py`、`ida/fix_vtable_types.py` 内部实现（只确认为什么被调、失败如何传播）。

**复现命令**（全部只读）：

```bash
# 阶段编排与行号
grep -n "def cmd_apply\|def cmd_export\|def cmd_codegen\|def cmd_probe\|def cmd_match\|def cmd_loop\|LOOP_ORDER" pipeline/cli.py
sed -n '350,394p;540,575p;960,996p;1280,1300p' pipeline/cli.py

# codegen 注解直读（跨行路径扫描；原始命中 53 行，人工核对后有效 38 处/8 文件，见 §2.3）
python3 - <<'PY'
import re, pathlib
READ = re.compile(r"(open\(|json\.load|read_text\(|glob\()")
ANN  = re.compile(r"('data'\s*[/,]\s*'annotations'|\"data\"\s*[/,]\s*\"annotations\"|annotation_json_path|ann_dir)")
for f in sorted(pathlib.Path('pipeline/gen').rglob('*.py')):
    if f.name == 'annotation_view.py' or f.name.startswith('test_'):
        continue
    L = f.read_text(encoding='utf-8', errors='replace').splitlines()
    for i, ln in enumerate(L):
        if READ.search(ln) and ANN.search("\n".join(L[max(0, i-15):i+3])):
            print('%s:%d' % (f, i+1))
PY
# 说明：路径含变量/常量/派生的 4 处（emit_headers.py:980、ast_transform.py:192、stage4_substitution.py:2308/:2318）扫描不到，需人工补记；其余命中里还需剔除 exe/evidence pack/gbengine/写文件/ida_structs 等非注解目标。

# export 声明例外
grep -n "t4-DECLARED-EXCEPTION" pipeline/ida/export_full.py
grep -n "no modifications to IDB\|ida_name.set_name" pipeline/ida/export_full.py

# 基线写点
grep -n "s4_baseline\|write_text\|json.dump" pipeline/compare_pal3.py | head -30
grep -n "base_path *=\|_n12_base *=\|_gpath *=\|n22_pair_closure" pipeline/check_annotations.py

# 测试资产与失败
find tests -name '*.py' | wc -l
ls pipeline/gen/test_*.py | wc -l
python -m pytest --collect-only -q   # EXIT=2（4 收集错）
head -5 tests/test_preflight.py
head -35 tests/e2e/test_l1_ratchet_injection.py

# 代码体量
wc -l pipeline/cli.py pipeline/compare_pal3.py pipeline/gen/stages/emit_headers.py
```

---

## 7. QA 自检（对照 #5 验收面）

| 验收项 | 状态 | 位置 |
|---|---|---|
| 五部分齐全（数据流/错层/模块化/可测试性/债务） | ✅ | §1–§5 |
| 每条结论有命令/路径/行号证据 | ✅ | 各行内 `file:line`；复现命令 §6 |
| `git status` 仅新增报告 | ⚠️ 措辞不成立（已说明） | 本会话只写本文件；`git status` 里其余改动（loop 日志、`evidence_ledger.json` 的 ev_0003/ev_0004、thirdparty 子模块、他人未跟踪产物）时间戳早于/独立于本报告，非本次审计产生；四份基线（`compile_baseline.json`/`baselines/latest.json`/`s4_baseline.json`/`link_census.json`）`git status` 为空、未重锚；未跑任何写管线命令 |
| 模块化提案含依赖方向与红线冲突 | ✅ | §3.2（R-A…R-F + 与 CLAUDE.md 检查点表/export 例外的冲突处理） |
| 补测/债务有优先级 | ✅ | §4.3 T1–T6、§5.1 P0/P1/P2、§5.2 卡序 |
