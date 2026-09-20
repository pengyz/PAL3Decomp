# 交付 1 台账（`superpower-subagent-driven-development`）

| 任务 | 状态 | 证据 |
|---|---|---|
| **T1** advisory 挂到写盘路径 | **完成（带条件通过）**（评审者 `49c10b28`）（实现子代理 `cd5dfbbe` 已完成并提交）| commit **`18af81298`**（恰 2 文件 +63 行 ✓）；编排者**独立核实**：测试 **3/3 PASS** ✓、`check` **exit 0** ✓、helper **无 `sys.exit`** ✓、apply/export 各 1 次 ✓、tracked clean ✓、**无符号链接残留** ✓；评审者 `49c10b28` running |
| T2 `??_L/??_M` 抽取器 | **实现已落地，编排者复验发现 1 处缺口**（子代理 `07521f30` 尚未汇报）| 目标：`tools/audit_element_sizes.py` + 测试；**预检**：`original/PAL3.exe.asm` 存在(22.8MB) ✓ 且 `call ??_L@` 计数 **=133** ✓（编排者独立复现三路复核的数字 ✓）|
| T3 133 站点核对 | 未开始 | — |
| T4 三 fixture 裁定 | 未开始 | — |
| T5 Spike 报告 | 未开始 | — |

## 裁决记录（Ruling）
- **R1**：编排者**不得**在实现子代理 running 期间编辑同一文件 ✗ ⇒ 我对 `cmd_export` 的补丁被"已接线，勿重复"断言安全拒绝 ✓，**这是正确行为**（避免双写 ✓）。
  *若错的代价*：重复插入一行调用（可撤销、无害）✓ —— 但并发写同一文件可能互相覆盖 ✗，故坚持等待。
- **R2**：T1 的完成判据以**实现子代理自身提交**为准 ✓；若它结束但未提交，则由编排者按其改动内容补提交并记录 ✓。

## 追加记录
- **T1 实现完成**（commit `18af81298`）✓ —— 编排者**独立复验**通过（不只采信实现者自述 ✓）。
- **实现者主动披露**一起自我失误：做 HEAD 对比时 `ln -s` + `git show HEAD:... > $T/pipeline/cli.py`
  **写穿符号链接**，一度覆盖工作区 `cli.py` ✗；它自行发现、恢复、重做并复核 ✓。
  ⇒ **值得进 `docs/knowledge` 的 gotcha**：`ln -s` 指向受跟踪文件 + shell 重定向 = **写穿符号链接**，
  静默改坏工作区 ✓（应改为"真实复制到 /tmp" ✓）。
- **评审者已分发**（`49c10b28`）：除规格符合度/代码质量外，特别请它裁两条待裁项 ——
  **F1** `cmd_check` 内联块与本任务 helper **重复**（DRY ✗）；**F2** advisory 块以 `=> FAIL` 结尾
  可能被误读为门禁失败（**假红→被习惯性忽略** ✗，是三路复核警告的镜像风险 ✓）。

## Ruling 追加（第 2 轮）
- **R3（并行推进 T2）**：T1 已**提交**（`18af81298` ✓）且其评审只读 ✓；T2 只**新建** `tools/audit_element_sizes.py`
  与其测试 ✓ ⇒ 与 T1 评审**无文件重叠** ⇒ **并行分发 T2 实现子代理** ✓（不让链条空转 ✓）。
  *若错的代价*：T2 的产出若与 T1 评审结论冲突，可在 T2 评审时合并处理（可见、可撤销 ✓）。
- **R4（预检前置）**：在分发 T2 前先核对**输入可用性**（asm 存在 ✓、`??_L` 计数=133 ✓）——
  避免子代理跑到一半才发现输入缺失 ✗（教训：`.asm`/`asm/` 均 gitignore ✓，clean checkout 后不存在 ✓）。

## 第 4 轮追加
- **已作废** `_structural_contradictions.json` ✓（commit `f30779802`）：重命名为
  `_OBSOLETE_structural_contradictions.json` + 附 `_OBSOLETE_structural_contradictions.md` 声明 ✓
  （理由：复核实测其偏移取自 decomp `this+N`，**量纲错 8×** —— 报 2571 vs asm 真值 `[ebp+505Ch]`=20572 ✓）。
- **遗留引用（须后续清理）** ✗：实测仍有 **8 个文件**引用旧名 ——
  `docs/specs/2026-09-20-evidence-layer-design.md`（本次规格自己 ✓）、`data/annotations/CHANGE_LOG.md`、
  `data/status/{_cleanup_vtable_class_reconcile,_knowledge_process_diagnosis_20260920,_attribution_evidence_20260919,
  _audit_toolchain_pipeline_20260920,_size_evidence_20260919,_architecture_cleanup_plan_20260920}.md`。
  三路复核要求"把引用改指 asm 重算产物" ✗ ⇒ 列为**独立后续任务**（不宜在本轮批量改写历史 status 文档 ✗）。
- **`_attribution_evidence_20260919.md` / `_size_evidence_20260919.md` 的 `max_offset` 数字同源失效** ✗（3/20 已过期）。

## 第 4 轮：T2 **编排者独立复验结果**（不采信自述 ✓）
| 项 | 结果 |
|---|---|
| 单元测试 | **3/3 PASS** ✓（含 `--help` 被护栏拒绝并打印用法 ✓）|
| 真实 asm 全量抽取 | 站点 **466**（完整 460 / 不完整 **6**）|
| **`ehl` 计数** | **133** ✓✓ —— **三路复核的数字由本工具精确复现** ✓ |
| **成功判据①（133/133 ehl 参数完整）** | **FAIL ✗** —— `ehl` 有 **1** 个不完整：`sub_498820:223790` ✗（另 5 个不完整在 `ehm`）|
| 语义抽查（强证据）| `sub_408740` → `size=8704,count=5,ctor=0x411900,dtor=0x411CA0` ✓（= 复核的 Role 证据）；`sub_41F6F0` → `size=896,count=64,ctor=0x4236D0,dtor=0x423880` ✓（= tagRoleSlot/BINK fixture）|
**⇒ T2 待处理项（交 T2 完成汇报或评审）** ✗：
1. `sub_498820:223790` 的 `ehl` 参数为何抽不全（疑：调用前 push 不足 5 个 / 中间夹了非 push 指令 / 跨 proc 边界）；
2. 5 个 `ehm` 不完整是否同类原因（`??_M` 只需 4 参，本应更易 ✓）；
3. 处置取向：**修抽取器** ✓ 还是**显式记录为已知漏采** ✓（若属"push 被 `mov`/`lea` 拆开"，则应按"已知漏采"记录并让下游只当 candidate/signal ✓ —— 与复核对本工具"只能给候选"的定性一致 ✓）。

## T1 评审结论（`49c10b28`）：**带条件通过 ⇒ 可记为完成** ✓
**规格符合度**：计划任务1 **逐项 ✅**，无硬缺陷 —— 恰 2 文件(20+43=63 插入/0 删除 ✓)、接口 ✅
（helper `cli.py:414-429`，`return int`；两处调用 365/409 **裸调用丢弃返回值**；**评审者自建行为级验证**：
monkeypatch `_check_ida`/`_run_ida`/`subprocess.run`，advisory rc=1 时 apply/export **仍不抛 SystemExit**
且各调用恰 1 次 ⇒ "调用方不得据返回值改退出码"**实测成立** ✓）、位置 ✅（在失败分支 `sys.exit(1)` 之后、
`print("Next:...")` 之前 ✓）、`cmd_check` 未被动 ✅、5 个 TDD 步骤 ✅、全局约束 ✅。
**零残留核实 ✅**：`git hash-object pipeline/cli.py` == `HEAD:` == `18af81298:` ✓；tracked 干净 ✓；
`find . -type l -name '*.py'` = **0** ✓；普通文件权限 ✓ ⇒ **`ln -s` 写穿事故确无残留** ✓。

### 3 条后续项（**登记，非阻塞** —— 评审者明确"不算 T1 缺陷"）
1. **F1（DRY，属实但不是 T1 的修复项）**：helper(`cli.py:420-428`) 与 `cmd_check` inline(`cli.py:440-447`)
   同一逻辑两份；inline 版由 `f74edaa7b` 引入，**早于** T1；T1 计划明写"`cmd_check` 勿动" ⇒ 改动即越界 ✓。
   最小修法：`cmd_check` 内换成 `_run_invariants_advisory()  # 返回值刻意丢弃`；风险低 ✓。
2. **F2（假红框定）**：(a) 不算 T1 缺陷（`=> FAIL` 来自工具自身 `tools/codegen_invariants.py:311-314`，
   父提交即如此）；**但 T1 把同一份"FAIL 字样 + exit 0"搬到了 apply/export** ⇒ 记独立发现项 ✓。
   (b) 最优改点**在工具自身**（单点受益三处）：advisory 时在计数**之前**打印
   `[ADVISORY] 非门禁报告：以下计数不影响任何退出码`，并把 `=>` 的判定词在 advisory 下改为
   `ADVISORY-ONLY（不阻断）` ✓；caller 侧加 `flush=True`（**实测**：stdout 重定向时框定行会**排到 FAIL 计数之后** ✗
   ⇒ 日志里"假红失去前置框定"真实发生 ✓）。
3. **测试补强（major，测试覆盖级别）**：现行 3 个测试是**源码子串检查**，评审者**实测变异**证明其可被绕过 ✗ ——
   把 `cli.py:365` 改成 `sys.exit(_run_invariants_advisory())`（真违反接口条款）后 **3/3 仍全 PASS** ✗；
   且第 3 个测试与第 1 个的 apply 半边同义 ⇒ **零判别力** ✗。
   修法：改用**进程内 monkeypatch 行为测试**（评审者已跑通，约 25 行，无需 IDA/IDB ✓）；
   **不可**用 `cli.py apply --dry-run` ✗（apply/export 无 dry-run，多余参数被静默忽略 ⇒ 会真跑 apply，
   而本机 `cfg.ida_path` 与 work IDB **都存在** ⇒ 破坏性 ✓）。

## 循环纪律（编排者自纠，第 5 轮）
**背景**：我在 T2 实现子代理 running 期间说了"我自己收口"并开始查 asm 准备动手 ✗ —— 这违反了我自己记下的
**R1**（"编排者不得在实现子代理 running 期间编辑同一文件"）✗。**损伤核对**：T2 两文件 mtime 仍为子代理的
17:13/17:11 ✓、我的写入与其**完全不相交** ✓ ⇒ **零损伤** ✓（我只做了只读验证 ✓）。
**⇒ R5（新裁决）**：while 某实现子代理 running，编排者**只允许** (a) 只读验证 ✓ (b) **不相交**文件/主题的工作 ✓
(c) 准备下一任务简报 ✓；**禁止**编辑其文件 ✗、**禁止**抢跑其任务 ✗。判定其**停滞**时，必须走
**显式 interrupt + reassign** ✓，**不得**静默并行 ✗。
（"做裁决，不停摆"的真义是**不要停下来问人类** ✓，不是**替代正在跑的 agent** ✗。）

## 编排纪律（第 8 轮）：**不要用 goal 编排"等子代理"的工作** ✗
**bug 现象**（用户发现）：goal `goal-b6db64de` 的 round 是**强制唤醒** ✗，而当时唯一的待办是
"等 T2 实现子代理汇报" ✓ ⇒ goal 把"等待"变成了"**反复轮询**" ✗（连烧 8 轮，每轮都无真实进展 ✗）。
**处置**：用户已 **pause** 该 goal（`phase: paused` / `activation: disarmed` / roundsStarted 8 ✓）。
**⇒ R6（新裁决）**：
1. **goal 不适合编排"进度由长时间子代理决定"的工作** ✗ —— 它的轮次粒度与子代理**完成事件**不同步 ✓；
   此类工作应以"**子代理汇报驱动**"为主 ✓。
2. **暂停后真正的等待是可行的** ✓ —— 本会话已实证：`cd5dfbbe`（T1 实现）与 `49c10b28`（T1 评审）
   都**主动发消息**唤醒了我 ✓ ⇒ **编排者不需要轮询** ✓。
3. 若某子代理**长时间静默**（可机械核对：其文件 mtime 不动 >15 分钟 ✓），才走
   **显式 interrupt + reassign** ✓（R5 ✓），**不自己接手** ✗、**不压轮询** ✗。
**⇒ 运行模式（此后）**：编排者只在 (a) **子代理汇报** ✓ (b) **用户消息** ✓ (c) **需要裁决** ✓ 时动作 ✓；
其余时间**静默等待** ✓。
