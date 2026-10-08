# 下一步修复方案（2026-10-08，基于实测 + kiro 独立复核）

**状态**：待执行 · **依据**：kior 独立复核 + 本会话实测（A/B 实验）
**当前 HEAD**：`f16b7daef`（+ 未提交的 `pal3/src`/decomp 重生成，两者均 gitignored）

---

## 0. 事故与恢复（已了结）

| 项 | 状态 |
|---|---|
| 我的 `timeout 60` 截断 `export` | ✅ **已恢复**（decomp 1373→**3649**；`.text` 覆盖 `0x401000..0x5694f0`；真实 export 耗时 **154.6s > 60s**）|
| IDB / git / 基线文件 | ✅ **未被污染**（`apply` 显式 `save_database`；基线写入点有回归保护，事故时**拒绝刷新**）|
| `subagent_kiro` 复核 | ✅ 确认诊断 1-5 全部成立；机制更精确（日志是**全量原子写**，被 SIGTERM 时**整份冻结**而非截断）|

---

## 1. 当前真实问题

| 指标 | 基线（10-06） | 现在 | 差 |
|---|---|---|---|
| S2 | **108/209** | **86/210** | **−22** |
| 总错误 | 1515 | **2074** | **+559** |
| 退化单元 | — | **23**（改善 1）| — |

### 1.1 A/B 归因实验（决定性）
| 组 | `stage3_cleanup.py` | S2 | 退化 |
|---|---|---|---|
| **A** | remote + **我的 Task 7** | **86**/210 | 23 |
| **B** | `origin/master`（**无 Task 7**）| **88**/210 | 21 |

⇒ **我的 Task 7 只贡献 2 个单元**（86 vs 88）；**主因在我之外**。

### 1.2 🎯 单点根因（大爆炸半径）
| 事实 | 证据 |
|---|---|
| `0x00445D10` 的真实所有者是 **`UIWnd::OnMessage`** | `pal3/src/UI/UIWnd.h:45` `virtual int OnMessage(int,int,int); // 0x00445D10` |
| 但 IDB/decomp 把它命名为 **`CGameData::OnMessage`** | decomp 文件名 `CGameData_OnMessageint_int_int_00445d10.json`；`name: CGameData::OnMessage(int,int,int)` |
| **15 个类**的注解都声明了该地址（各记录继承来的虚函数）| `grep -l 0x00445D10 data/annotations/structs/*.json` = 15 |
| ⇒ `[MISATTRIBUTED]` 站点 **44 文件**，callee=`CGameData` **41 次** | `grep -rho 'MISATTRIBUTED] [A-Za-z_0-9]*::'` |
| ⇒ 发射 `CGameData::OnMessage(this, …)` = **4 参 < 声明 3 参** | `ast_transform.py:1455-1481` 的 MISATTRIBUTED 路径 |
| ⇒ **C2660/C2661 主导**（`OnMessage` 8 单元 + `Create` 5 单元）| 退化单元首个错误码分布 |

**机制**：`ast_transform.py:1455-1481` 检测到"**无关类在我们自己的 `this` 上被调用**"（`CCBItemWindow::this` 调 `CGameData::OnMessage` —— 源码不可能这样写）⇒ **拒绝洗白成合法语法**，保留静态调用形并打 `[MISATTRIBUTED]` 标记，**故意让它编译失败作为"修 callee IDB 名"的精确信号**。
⚠️ 但**注释声称报 C2352，实测报 C2660**（MSVC6 按成员调用解析 ⇒ 显式 `this` 变成多余参数）——**注释与实测不符**（次要缺陷）。

### 1.3 未解问题（需一次调查）
**为什么 10-06 基线（远端，108/209）没有这些失败？**
候选：① 远端 IDB 里 `0x00445D10` 命名不同（IDB **被 gitignore、不随 git 共享**）；② 远端 10-06 的 `pal3/src` 来自不同 decomp 状态；③ 基线比较**跨 IDB**，本无可比性。
⇒ **这是归因的最后一块拼图，必须先解**（否则无法判断是"真退化"还是"跨 IDB 比较失真"）。

---

## 2. 修复方案

### 步骤 0：解 1.3 的未解问题（**只读，无副作用**）
```bash
# 该地址在 IDB 里的历史命名（用备份 IDB 或 .91/.92 对照）
ls -la original/*.i64*
# 检查命名来源：apply 是否写函数名
grep -nE "set_name|SetName|force_name" pipeline/apply_annotations.py pipeline/ida/export_full.py | head
```
**判据**：若能证明"远端 IDB 里该地址名为 `UIWnd::OnMessage`" ⇒ 主因是**IDB 状态差异** ⇒ 步骤 1 改为"重建 IDB 命名"；
若能证明"两 IDB 命名相同" ⇒ 主因是**注解变更** ⇒ 步骤 1 改为"注解修复"。

### 步骤 1：修 `0x00445D10` 的命名（**病灶层：IDB/注解命名**）
**目标**：让它归属真实所有者 `UIWnd::OnMessage`。

**候选动作**（按步骤 0 结论择一）：
1. **注解侧**：确认 `UIWnd.json` 是该地址的"定义者"，其余 14 个类只应作为**继承记录**（不参与命名仲裁）；
   若命名仲裁取"声明该地址的任意类"，改为取**继承链最基类的定义者**。
2. **IDB 侧**：修正 IDB 中该地址的函数名（需 IDA 操作或 `apply` 侧支持）。
3. **最小验证**：`grep -c 'MISATTRIBUTED] CGameData::OnMessage' pal3/src/` 应从 **41 → 0**。

⚠️ **禁止**：把 MISATTRIBUTED 路径"洗白"成合法语法（会掩盖真实归属错误——代码注释明确禁止）。

### 步骤 2：修 `[MISATTRIBUTED]` 注释与实测不符（**次要，但影响后续排查**）
`ast_transform.py:1455-1481` 注释称报 **C2352**，实测报 **C2660**。
⇒ 更正注释（或明确记录 MSVC6 的实际行为），避免后续会话按错误码找错方向。

### 步骤 3：处理我的 Task 7 的 2 单元贡献（**86 → 88**）
A/B 已证明 Task 7 净损 **2 单元**。需定位是哪 2 个，并判断：
- 若是 Task 7 **违反自身失败契约**（"保留 stub + 记账，不降级"）⇒ **修 Task 7**；
- 若只是 vtable 名称/签名推断偏差 ⇒ 按 Task 7 契约**记账并降级**，不得发射不编译的代码。

**判据**：`A/B 差集` = `{A 退化} - {B 退化}` 的 2 个单元，逐条看是否含 Task 7 的 `->Method(` 转换。

### 步骤 4：重跑验证（**无副作用**，但耗时长 ~6 分钟）
```bash
python3 pipeline/cli.py loop --stages codegen,probe,match   # 不加任何 timeout！
```
**验收**：
| # | 判据 |
|---|---|
| 1 | S2 ≥ 基线（**108**/209）或至少 ≥ 88（B 组水平）+ 解释差额 |
| 2 | `grep -c 'MISATTRIBUTED' pal3/src/` 显著下降（目标 0）|
| 3 | 总错误 ≤ 1515（且 C1003 两单元最大行号 ≥ 3838/2849）|
| 4 | `match` 的 L1 ≥ 94（棘轮不倒退）|
| 5 | `git status` 干净 |

### 步骤 5：基线刷新（**高副作用，需显式确认**）
仅在步骤 4 验收通过后：
```bash
python3 tools/regression_detector.py --save-baseline
```
⚠️ 会**永久覆盖** `data/status/baselines/latest.json`。历史快照（`20260914_*` … ）可回退。

---

## 3. 回退路径

| 级别 | 动作 |
|---|---|
| **零级** | `pal3/src`、`asm/pal3/decomp`、`probe_census.json`、`_loop_last.json` **均为可再生的派生物**，无需回退 |
| **一级** | 基线文件：用 `data/status/baselines/` 下的历史快照手工恢复 `latest.json` |
| **二级** | IDB：`original/PAL3.exe.i64.bak`（05-22）· `.polluted.bak`（08-29）· `.91.i64`/`.92.i64` 为现成备份 |
| **不可回退** | 若 `apply` 已把错误命名写进 IDB 且无备份 ⇒ 需重建（代价高）|

---

## 4. 管线脆弱点修复（来自 kiro 复核，**防复发**）

| # | 问题 | 建议（可落地）|
|---|---|---|
| **F1** | `cmd_loop` **静默吞掉未知参数**（`--help` 落入正常路径启动全链路）| 遍历 `argv`，凡不属于 `{--dry-run,--stages,--stages=*,--expect-*}` 的 token ⇒ 打印"未知参数 X；查帮助用 `cli.py --help`（**不能加在 loop 之后**）"并 `sys.exit(2)` |
| **F2** | `export` 无**产出完整性自检** | export 后比对 decomp 文件名解析出的最大地址 vs `pipeline/callgraph.py:TEXT_END(0x5695D0)`；差距 > 10% ⇒ 判不完整并 `sys.exit(1)` |
| **F3** | 外部 `timeout` 破坏性（阶段中途状态不一致）| 文档明确"**loop 绝不可加外部 timeout**"；export 单次需 **≥300s** |
| **F4** | 无进度心跳（事后只能靠 mtime 推断）| 每阶段开始时先写 `_loop_last.json` 的 `IN_PROGRESS` 标记 |

---

## 5. 待裁定的决策（D1-D4，v2 方案遗留）

### D1（**前提已被证伪**）：`vtable_decl_check` vs `vtable_mapper`
**"二选一"不成立**——两者**不在同一阶段**：
| 工具 | 输入 | 阶段 | 接线 |
|---|---|---|---|
| `vtable_mapper` | 注解 + IDB 导出 | `cli.py check`（进管线前秒级闸）| ✅ 已接线 |
| `vtable_decl_check` | **生成头 `**/*.h`** + 注解 + pending | **必须 codegen 后** | ❌ 零消费者 |

**mapper 实测能力**：`unresolved` ✓ · `order_mismatch` 活但判据弱（仅"前一槽未解析"）· **`signature_mismatch` 完全死**（`+=` 0 次、print 0 次）⇒ **无签名校验、无真槽序**。

**建议**：`decl_check` 注册为 **codegen 后门禁**（与 `compile_regression` 同级，进 `gate_registry.md` 机器强制栏）⇒ 需同时改 `pipeline/cli.py` + `data/status/gate_registry.md`。

### D2 重复实现收敛
| 对 | 判定 | 建议 |
|---|---|---|
| `vtable_verify` ↔ `vtable_compare` | 重复（自认同规则 + 有 parity 测试）| 提为单一实现 |
| `vtable_sig_infer` ↔ `vtable_slot_audit` | 口径冲突（raw 字节 vs 提交缓存），**无 parity 测试** | 定 `sig_infer` 为唯一证据源 |
| `vtable_scanner` ↔ 两份 `bin_table` | 冲突（终止判据被 docstring 自认失效）| 退役或复用同一界定 |

### D3 立即清理（低成本高收益）
1. **`tools/vtable_call_transform.py` 废弃** —— `--dry-run` = **0 transforms**；在自己 docstring 的形状上产出**非法 C++**（括号不平衡）；**默认写盘**
2. **`tests/test_vtable_call_transform.py` 改名** —— 它测 `stage3_cleanup`，与同名死工具无关（撞名藏了死工具）
3. **修 `vtable_slot_audit.py:107`** —— `rets.get(addr)` 无归一（`:55-62` methods 却用 4 变体）⇒ **4 个有证据的槽被误报 `evidence-none`**

### D4 SDD 文件位置
17 个 force-add 的 SDD 文件偏离远端惯例（`.superpowers/` 不入库、durable 台账放 `data/status/`）⇒ 建议**移到 `data/status/`**。

---

## 6. 诚实的不确定性

- **1.3 未解**：无法排除"跨 IDB 比较失真"⇒ 步骤 0 必须先做
- **21 vs 23 的差额**只在同一 IDB 内可比（A/B 已控制）
- **全库覆盖仍是外推**：125/204 TU 今天编译不过
- **`/GR`、T3、T2、T4 等 v2 待办**（见 `_vtable_next_step_plan_v2_20261008.md`）仍在队列