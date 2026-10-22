# 增量正确性 TDD 复核

对象 `tests/test_incremental_correctness.py`（实跑 5/5 绿）。零产品改动；自构造 case `/tmp/tdd_review_selfcase.py`（7/7）

## 5 用例复核

1. **dependency_closure** ✓ 断言对。但喂合成 dict，测的是 `decide` 决策表，非真实依赖闭包。
2. **dependency_closure_partial** ⚠ 断言不全：docstring 承诺「跑 codegen+probe」，只断言 codegen。**变异证据**：decide 改坏（decomp 变时误跳过 probe），5 用例仍全绿。
3. **no_unnecessary_generation** ⚠ 判据不符：docstring 写「未变⇒文件不修改（mtime/diff）」，实际只断言 decide 判全跳过，从未验证文件未改。
4. **incremental_equals_full_golden_hash** ✗ **核心判据空转**：L87-97 仅测 temp 目录 hash 确定性，随即 `assert True, '待差分测试实施后激活'`。commit 885d7f895 的「逐字节相同」是**一次性手工实测**未进测试 ⇒ 管线一变即失保护。
5. **pipeline_script_change_forces_all** ⚠ 同义反复：只遍历 compute_inputs 已有 3 键，不验键集合完备。实测 **13 项影响生成的输入不在 hash 内**：`pipeline/{cli,compare_pal3,link_probe,config,probe_compile,check_annotations,preflight}.py`、`pipeline/{tools,hooks}`、`phase2/{overlay,manifest.json}`、`cmake/toolchain-vc6.cmake`、`pal3/CMakeLists.txt`。改 `cli.py` 或 phase2 overlay ⇒ decide 实测判 4 阶段全跳过，**直接违反「管线脚本变⇒强制全跑」纪律**。

## 自构造 case

- **A（golden hash 差分，真实 decide+迷你管线）**：改未覆盖输入（phase2）⇒ 增量 stale，hash `a7da002a…`≠全量 `a30914d5…`（判据有效但覆盖有洞）；正向对照改有覆盖输入 ⇒ 增量==全量 `177406cf…`。即「增量==全量」**恰在未覆盖输入处断裂**。
- **B（hash 健全性）**：产品 `_hash_dir` 是 **mtime+size 非内容 hash** —— 同 size 改内容且 mtime 还原（cp -p 形）⇒ hash 未变 = **假跳过类**；touch 反之假重跑（成本类）。
- **C（测试 helper）**：用例自带 `_hash_dir` 把绝对路径喂进 hash（`h.update(fp.encode())`）⇒ 同内容两目录 hash 不同，差分跨目录比对会假报警。
- **D**：单独跑用例 #4，0.0s 通过、未跑管线（空转实证）。

## 挑刺（缺什么测试）

1. **真·golden hash 差分**（增量 vs 全量逐字节）——唯一判据现为 stub。
2. **hash 键完备性守卫**：扫描 cli.py 各阶段实读路径，断言 ⊆ compute_inputs（13 项漏项实锤）。
3. **输入检测健全性**：同 size 改写漏检类；或改内容 hash。
4. **probe 跳过条件**断言（变异实证）。
5. **「无不必要」实效判据**：跑前后全树 mtime/哈希快照断言零修改。
6. **失败路径**：export rc≠0 不 `--save`、state 不污染、重跑收敛。
7. **state 卫生**：`incremental_state.json` 被 git 跟踪且 worktree 已 M（14:50:51 vs 提交 14:40:46）；`test_run_pipeline_incremental.py` 的 `save_state` 直写**真实 STATE 路径** ⇒ 测试可覆盖生产基线，缺可注入隔离。
8. **IDB（.i64）不在输入 hash**：manual_idb 手改后全跳过 ⇒ stale codegen，缺测试。
9. **match 门禁缺失**：CLAUDE.md 规定 probe 后强制 `cli.py match`，增量执行器无 match 亦无测试。
10. 小项：`test_run_pipeline_incremental.py` docstring 所列用例名与实际函数名不符。

## verdict

**驳回（补 3 项 must-fix 后重审）**：①用例 #4 空转，「golden hash 逐字节相同」只存在于 commit 一次性实测；②输入覆盖 13 项漏项使「管线脚本变⇒全跑」失守；③hash 非内容级存在假跳过类。叠加 ⇒ **「增量生成==全量生成」当前不成立**（A2 实证断裂）。决策表（用例 1/2）基本正确，但「测试全绿」≠正确性证明——恰是 docstring 自己的洞察，核心判据却未落地。
