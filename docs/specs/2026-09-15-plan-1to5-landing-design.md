# 方案 1–5 落地设计（申请人：captain）

> **状态**：**待用户复核**（本文档只是设计，不含代码改动）
> **日期**：2026-09-15 · **仓库**：`/home/peng/workspace/PAL3Decomp` · **HEAD**：`17a4d2de0`
> **分类**：**architectural**（改 `match` 验收裁判、新增产物、改 codegen 布局表示、定表达路线、落地 AR-016）
> **来源**：第 4 任独立对抗性复核 `data/status/_cleanup_review_strategy_next.json`（子 agent `ad32c455`）
> 经 captain 独立复核的数据见 §1
> **Hindsight**：本会话 `hindsight_*` 全部 401（`API key required`）⇒ 知识沉淀只落文件

---

## 1. 前提事实（全部独立实测，非引用）

| 事实 | 值 | 来源 |
|---|---|---|
| 验收判据 | `ok = 56/198`、`L1 = 6`、`oob = 0` | `data/status/baselines/latest.json`、`s4_baseline.json` |
| **`ok` 是 `L1` 的入口闸门** | `compare_pal3.py:277` `passing = [r['unit'] for r in census['s2']['results'] if r['status']=='ok']` ⇒ **只有编译通过的单元进入比对** | captain 实读 |
| 匹配池 | `symbols=189`、`matched=129`、`partial=123`、`unmatched=60` | `s4_baseline.json` |
| **129 个符号全部住在 `ok` 文件里** | `(partial,ok)=123`、`(match_L1,ok)=6`、**fail 文件里 0 个** | captain 实测 |
| `partial` 中位数 | **24.1%**（最高 95.0%） | captain 实测 |
| **近 L1 果实** | `≥85%`：`ClearName 95.0%/20B`、`FindInOpen 94.1%/34B`、`FindInClosed 94.1%/34B`、`UINote::GetEntryPtr 88.2%/17B`；`≥80%` 加 `_Console::SetActive 84.4%/32B`。**所在文件全部 `err=0`** | captain 实测（复核者称 9 个，captain 核到 4 个 ≥85%） |
| `C2039` 规模 | **1068 条 = 全部错误的 28.8%**（最大族） | 实测 |
| `err` 总数 | 3703，但 **16 个文件被 `C1003` 截断在 102** ⇒ **是下界** | 实测 |
| **`match` 门禁盲区** | `cli.py cmd_match` **只棘轮 `match_L1`**（`:520-575` 实读）；`partial` 大幅退化**不报警**；`compare_pal3` **只写 `match_pct`，不写字节 diff** | captain 实读 |
| 布局炸弹 | 59 多态头 + 145 多继承头 `sizeof` 与二进制不符；**59/145 出自另一复核者的统计，captain 只独立验证过 2 个类** | `docs/specs/2026-09-15-cv-layout-design.md` §4 |
| **C-V 前提已实测通过** | VC6 合成表槽序/override 原位替换/thunk `83 e9 08; e9 rel32` 与二进制 **43 处同款 thunk** 结构同构 | 复核 `ad32c455`（captain 核对 `CEffCylinder` 4 张表一致） |

**本会话基线漂移的自纠**：captain 此前报的 `err 3089 → +614` **口径错**（3089 属提出交接文档那一轮）。
本会话清洁起点是 **18:40 的 `err = 3504`，增量 +199**。已记录。

---

## 2. 已确认的三项决策

| 项 | 决策 | 内容 |
|---|---|---|
| **问题 1** | **A + 分级棘轮** | diff 落**独立文件** `data/status/s4_diffs.json`；`s4_baseline.json` 保持精简；棘轮分级：`L1` 不得降 + `partial` 中位数不得降 + `partial_pct` 总和不得显著降 |
| **问题 2** | **Z 排序** | `1 → 2 → 4 → 3 → 5`（先拿便宜果实、再小规模验路线、最后动最大最脏的一步） |
| **问题 3** | **乙（判据豁免）** | 方案 3 不以 `ok` 为判据，改三条：① `L1` 不回退 ② **`partial` 中位数不回退**（依赖方案 1 已生效）③ 若 `ok` 降须**逐条证明新错误来自被修正的布局** |

---

## 3. 逐步设计

### 方案 1 — partial 棘轮 + per-function diff 落盘

**为什么必须先做**：没有它，方案 3 的"先降后升"窗口**完全静默**（`match` 只看 `L1`）；
且方案 3 的判据乙第②条**依赖它已生效**。

**改动**：

| 文件 | 改动 |
|---|---|
| `pipeline/compare_pal3.py` | ① `compare_units` 的 `rows` 增字段：`first_diff_off`（首个差异字节在函数内的偏移）、`diff_bytes`（差异字节数）、`ctx_hex`（首个差异处 ±8 字节的十六进制，供人工判读）；② 写**新产物** `data/status/s4_diffs.json`：`{generated_by, flags, exe_sha, rows:[...]}`；③ `s4_baseline.json` 的 `rows` **保持现字段不变**（不膨胀） |
| `pipeline/cli.py` `cmd_match` | 棘轮**分级**：现有 `L1` 逻辑保留；**新增** partial 判据 —— 读旧 `s4_baseline.json` 的 `rows` 算 `partial` 的**中位数**与 `partial_pct` 总和，与新值比：中位数下降 → 失败；总和下降超过 2% → 失败。失败时**同样把旧基线写回**再 `sys.exit(1)`（复用现有机制） |

**判据（本步验收）**：
1. `s4_diffs.json` 生成且可 `json.load`；抽样验证 `first_diff_off` 与真实字节差异一致（对 1 个 partial 函数手工比对）
2. `s4_baseline.json` 的字段集**与改动前逐字段相同**（不膨胀）
3. 用**注入式负例**验证棘轮真会失败：临时把某 partial 的 `match_pct` 改低 → `match` 必须 `exit≠0` 且基线被写回
4. 既有硬线不回退：`L1 ≥ 6`、`ok ≥ 56`

**风险**：`cmd_match` 的棘轮失败会在**任何 partial 退化时**让 `match` 非零——这正是目的，
但**可能立刻触发**（当前 partial 中位数 24.1%，若上一轮基线也是 24.1% 则无差异）。

---

### 方案 2 — L1 通道（4 个 near-L1 → 100%）

**为什么便宜**：4 个函数 17–34 字节，**所在文件 `err=0`**（`SceneMapPlayer`/`AStarPathFinder`/`UINote`），
且 `AStarPathFinder` 已是本会话修过的文件。

| 目标 | 当前 | 大小 |
|---|---|---|
| `SceneMapPlayer::ClearName` | 95.0% | 20B |
| `AStarPathFinder::FindInOpen` | 94.1% | 34B |
| `AStarPathFinder::FindInClosed` | 94.1% | 34B |
| `UINote::GetEntryPtr` | 88.2% | 17B |
| （次优先）`_Console::SetActive` | 84.4% | 32B |

**方法**：用方案 1 的 `s4_diffs.json` 取每个函数的 `first_diff_off` + `ctx_hex` ⇒
与 `asm/pal3/decomp/<fn>.json` 的 Hex-Rays 输出**逐指令比对** ⇒ 定位差异（典型成因：
编译器 flag 差异 / 局部变量分配 / 常量折叠 / 调用形式）⇒ 在**允许范围内**（codegen 等价变换 or annotation 修正）收敛。

**判据（本步验收）**：`L1` 从 **6 → ≥10**；且 `ok` 不回退（这些文件 `err=0`，预期无影响）。
**每修一个函数记一条 CHANGE_LOG 级证据**（哪条指令、原字节 vs 生成字节）。

**风险**：可能遇到 `hexrays_limit` 类差异（**不可修**）⇒ 那就**如实记为 NO_FIX 并转下一个**，
不得为凑数做非等价变换。

---

### 方案 4 — C-V 单类试点（定表达路线）

**为什么在 3 之前**：在动 **59+145 个头**之前，先用**一个类**证明路线。

**试点对象**：`CEffCylinder`（**已被扫描器完整取证**：ctor 存 4 张表 `0x56F62C/0x56F7BC/0x56F7C8/0x56F804`，
`vtables[0]=0x56F7C8` 15 槽；且复核者已用它证明 thunk 同构）。

**A/B 两条路线**（复核者已预答前提，本步是**落地验证**）：

| | 路线 ①（手工表） | 路线 ②（C-V，编译器合成） |
|---|---|---|
| 做法 | 删 `virtual` + 保留显式 `void *__vftable` 成员 + ctor 显式赋表 + const 表发射 | vtable 表示收口到 C++ `virtual`，由编译器合成表 |
| VC6 实测 | `A{void*__vftable;int;int}` `sizeof=12`、`__vftable@0` ✅ | 合成表槽序/override/thunk **结构同构** ✅ |

**判据（本步验收）**：
1. 该类 `sizeof` == 注解 `binary_size`（**P1**）
2. `.h` 里每个成员 `// +0xNN` 注释 == 注解偏移（**P2**）
3. **`tools/vtable_scanner.py` 取到该类的表槽位序列 == 二进制真实表槽位序列**（逐槽地址比对）
4. 该类 `.cpp` 单 TU 编译 `exit=0`
5. **不破坏全局硬线**：`L1 ≥ 6`、`ok ≥ 56`

**产出**：路线定案记录（含两条路线的实测对比），供方案 3 使用。

---

### 方案 3 — 布局炸弹（59 多态头 + 145 多继承头）

**前置**：方案 1 已生效（提供 partial 棘轮与 diff）；方案 4 已定路线。

**第 0 步（必做）：复跑清单**。59/145 出自另一复核者的统计，**captain 只独立验证过 2 个类**
⇒ 先写一个**可复跑的门禁**产出精确清单（判据：VC6 编译该类的 `.h` 取 `sizeof` vs 注解 `binary_size`），
**不得直接沿用 59/145**。

**改动**（按方案 4 定案路线）：

| 文件 | 改动 |
|---|---|
| `pipeline/gen/stages/emit_headers.py` | ① 修 `vfptr`/`__vftable` **双重认领**（`emit_headers.py:1728` 的跳过判据与注解实际用名对齐 + 推进 `start_off`）② 修**基类区双重认领**（`public Base` 与 `_gap_000` 并存 ⇒ 基类区宽度用 `sum(sizeof(base))`，**不用注解 `base_size`**——实测 `SceneObj` 的 `base_size=44` 而基类和为 80）③ `__vftable` 引用（**606 处限定形态 + 总 1047 处**）按定案路线处理 |
| `data/annotations/structs/*.json` | 仅为 `sizeof` 不符的类修正 `base_size`（**逐类取证，禁批量**）；`SceneObj` 的 `44` 是 `0x44` 十六进制误写 |
| 新增门禁 `tools/layout_sizeof_check.py` | 判据 **P1**：受影响类 VC6 `sizeof` == `binary_size`。接入 `codegen all` ∧ 链 |

**判据（乙）**：
1. **`L1 ≥ 6` 不回退**
2. **`partial` 中位数不回退**（方案 1 提供）
3. 若 `ok` 降：**逐条证明**新错误来自被修正的布局（给 文件:行号 + 错误码 + 该行引用的成员偏移）
4. P1 清单**收敛**（受影响类数下降至 0，或明确登记为 NO_FIX）

---

### 方案 5 — `MISATTRIBUTED` 26 处定谳（AR-016 落地）

**定性已修正**（复核者证伪 captain）：这 26 处报的是 **C2660 签名不匹配**，
**不是** `CG-005` 定性的 344 个 **C2352** 形态站点；`AR-016` 明文「须用户裁决后才可改 policy」= **未决区**。
抽查 `Array::Insert` 显示：`Array` 注解 `methods` 为空、声明与调用参数数真不匹配 ⇒ **是可修的 annotation_fix**。

**做法**：逐条读该行 + 注解签名 + decomp 签名 ⇒ 三分类：
| 分类 | 动作 |
|---|---|
| **签名缺口**（注解缺形参/归属错） | 修 annotation（**带 decomp 证据**） |
| **真 MISATTRIBUTED**（callee 归属错） | 按 A 级证据改归属，或登记 `NEED_EVIDENCE` |
| **NO_FIX**（如桩体/编译器生成） | 登记 NO_FIX + 理由，**从 `ok` 分母的可归因天花板中剔除** |

**判据**：26 条**每条有定论**（修 / `NEED_EVIDENCE` / `NO_FIX`）；`ok` 不回退。

---

## 4. 错误处理与回滚

| 情形 | 处置 |
|---|---|
| 方案 1 的棘轮**立刻触发**（partial 已退化） | **先查原因再前进**——不得为了通过而放宽棘轮（放宽即回到盲区） |
| 方案 2 遇 `hexrays_limit` | 记为 `NO_FIX` 并**转下一个**，不凑数 |
| 方案 4 两条路线**都不满足 P1/P2/P3** | **停下回报**——这推翻复核者的"结构同构"结论，需重新设计 |
| 方案 3 导致 `ok` 降且**无法逐条归因** | **回滚该步**（用 `git show HEAD:<path>` 恢复，**不做破坏性 git 操作**） |
| 任何一步 `L1` 回退 | **判该步失败并回滚**（项目全局否决规则，无例外） |

**全程硬纪律**（沿用本会话已被证明必要的）：
1. 退出码一律 `cmd; echo "exit=$?"` 或 `${PIPESTATUS[0]}`（**`cmd | tail` 会吃掉退出码**）
2. 禁止 `git checkout --` / `git restore` / `git stash` / `git clean -fd`
3. 禁止删除 `backup/local-line-20260904` 与 10 条 stash
4. **不用 `pkill -f` / `kill -9` 配 `ps|grep`**（本会话已两次误杀自己的 shell）
5. **窗口纪律**：跑 `apply`/`export`/`codegen`/`probe`/`match` 前**在对话里报明"进入窗口"**，结束报"退出"；不把测试性 apply 混进正式链

---

## 5. 测试策略

| 层 | 方式 |
|---|---|
| **单元** | 方案 1：`compare_units` 的 diff 字段对 1 个 partial 函数**手工比对字节**；方案 3：`layout_sizeof_check` 对 2 个已知类（`UIWnd` 96→68、`SceneObj` 3196→1784）**回归** |
| **注入式负例** | 方案 1 的棘轮必须能被**人为降低的 partial** 触发（否则是死门禁——本会话已有 4 例恒真门禁的教训） |
| **端到端** | 每步后跑 `check → apply → export → codegen all → probe all → match`（**独占窗口、开始结束通报**），记录 `ok`/`L1`/partial 中位数三元组 |
| **对抗性复核** | 方案 4（路线定案）与方案 3（最大改动）**各派一次独立复核**；其余步骤由 captain 自测 + 注入式负例 |

---

## 6. 规格自检结果（行内已修）

1. **占位符扫描**：无 `TBD`/`TODO`；§3 各步均有判据与风险。
2. **内部一致性**：§3 方案 1 的棘轮判据与 §2 问题 1 的决策一致；§3 方案 3 的判据与 §2 问题 3 的"乙"一致。
3. **范围检查**：5 步含 **1 个新增门禁工具**（`layout_sizeof_check.py`）、**1 个新增产物**（`s4_diffs.json`）、
   **3 处代码修改**、**2 次对抗性复核** —— **超单一实现计划容量**，需在 writing-plans 阶段**按 Z 拆成 5 个子计划**。
4. **歧义检查（已消歧）**：
   - "partial 中位数不得降"——**明确为中位数 + 总和双看**（防"翻转成 L1"造成的假降）
   - "受影响类"——**明确由 `layout_sizeof_check.py` 的清单定义，不沿用 59/145**
   - "逐条证明新错误来自布局"——**明确要求 文件:行号 + 错误码 + 该行引用的成员偏移**
5. **诚实标注的未验证项**：59/145 未复跑；C-V 的"逐字节一致"只在**结构层**验证过（槽序/thunk），
   **未验证**项目级链接布局（COMDAT 折叠、dtor 对）；`MISATTRIBUTED` 26 条的逐条归属未核。

---

## 7. 请求复核

本文档为**设计**，未实施任何改动。**请复核 §3 各步判据与 §4 回滚策略**；
如无异议，我将进入 `superpower-writing-plans` 按 Z 拆出 5 个子计划。
---

# 附：第 5 任独立复核的证伪与强制修订（2026-09-15）

> **复核交付**：`data/status/_cleanup_review_plan1to5_design.json`（子 agent `1632a7e8`）
> **总裁定**：**不可按原文实施**。§1 全部可核数值复核者独立复现（**无"以缺席反推"型数值错误**），
> 问题在**判据设计层**。以下 R1–R5 为强制修订。

## R1 方案 1 的棘轮自相矛盾（**captain 独立验证，成立**）

**漏洞**：任何 `partial → L1` 的**进步**都会触发中位数判据。结构性原因是 **n 的奇偶性**：

```
n=123（奇）: median = sorted[61] = 24.10
n=122（偶）: median = (sorted[60]+sorted[61])/2 = (24.00+24.10)/2 = 24.05
            ⇒ 与移出者的分值无关 ⇒ **移出任何元素都使中位数降 0.05**
```

captain 用 `s4_baseline.json` 的 123 个真值实测：

| 移出（= 修成 L1） | 中位数 | 总和 | 判据 |
|---|---|---|---|
| `95.0` | 24.10→**24.05** | 3803.9→3708.9（**−2.50%**）| **双重触发** |
| `94.1` | 24.10→**24.00** | →3615.7（**−4.95%**）| **双重触发** |
| `88.2` | →**24.05** | →3715.7（**−2.32%**）| **双重触发** |
| `84.4` | →**24.05** | →3719.5（**−2.22%**）| **双重触发** |

⇒ **方案 2 的全部目标成功即被方案 1 判死；方案 3 修好任何 partial 同样触发。**
反之中位数对**下半区（多数）**的真实退化**不敏感**——**该严不严、该松不松**。

**注入式负例方向也写反了**（captain 原文"把某 partial 的 `match_pct` 改低 → `match` 必须 exit≠0"）：
改低**旧基线**只会让旧值更差，两判据都判"未退化" ⇒ `exit=0`，**负例触发不了**；
若实现者为让负例通过而反转比较，会得到**把进步报成退化**的坏门禁。

**修订**：棘轮改**按 symbol 键控**——
```
旧∩新 逐符号: new_pct >= old_pct      （partial→L1 天然通过）
L1 单调不降
哨兵: stats.unmatched 不增、oob 不增（现=0）、symbols/matched 不缩水
中位数 / 总和 → 降为 advisory（只打印，不判失败）
```
**注入负例改为**：旧基线整体 +10（med 24.1→34.1）**或**真实退化一个源文件。

## R2 方案 1 的 diff 产物信息不足

- **`ctx_hex`（单窗口 ±8B）不够**：`asm/pal3/decomp/*.json` **只有 Hex-Rays 伪代码、无指令层**；
  单窗口只够 1–2 字节差异的小函数，对多差异点大函数会漏。
- **更便宜的路径**：`compare_bytes` **内部已算出完整 diffs 却丢弃**（`gbengine_compare.py:246-291`）
  ⇒ 方案 1 应**存全量 `diff_offsets` + 两侧全函数 hex + reloc 掩码**（复核者估 129 行 <100KB）。

## R3 方案 2 的前提被证伪：**3/4 的根因是方案 3**

复核者用同款 flags 重编 4 个单元（`/tmp` 隔离），`match_pct` 完全复现（captain 读数属实），
但**差异性质与 captain 的清单不符**：

| 目标 | 差异 | 实测 `sizeof` 生成/二进制 | 定性 |
|---|---|---|---|
| `ClearName` | 1 字节：`lea edi,[edx+0x115]` vs `[edx+0x105]`；注解 `m_szName=+0x105` 与二进制**一致** | **408 / 392** | **布局病（方案 3 族）** |
| `FindInOpen/Closed` | 各 2 字节：off2 系统性 +4 | **28 / 24** | **vtable 双重认领**（正是根因 A 的类型级实证） |
| `GetEntryPtr` | 2 字节：disp32 `0x1b58` vs `0xd60` | **548 / 268（+280）** | **`UIDialog` 基类链烂** ⇒ 布局链修好前**不可修** |
| `SetActive` | 5 字节：编译发 `push ecx; call; pop ecx`，二进制是对 `0x41C1E0`（`ScriptPoolPage_Alloc`，`__thiscall`）**直接调用** | — | **归属/声明问题** ⇒ **唯一不依赖方案 3 的目标** |

**⇒ "便宜果实先摘"的 Z 序前提被证伪**：`0/4` 是 flag 差异、`0/4` 是 `hexrays_limit`。
**修订**：顺序改 **1 → 4 → 3 → 2 → 5**，或把方案 2 拆成「`SetActive` 先行 + 其余 3 个后置」。
`L1 6→≥10` **在方案 3 之前不成立**。

## R4 方案 4 的 P3 按现文字是**恒真门禁**（本会话第 5 例）

设计原文 P3 = 「`vtable_scanner` 取到的槽位序列 == 二进制真实表槽位序列」
——**scanner 读的就是二进制，是自比自**。**修订**必须把两侧分开：

- **二进制侧**：`tools/vtable_scanner.py`（已有）
- **编译产物侧**：**需新增 COFF 提取器**。复核者实测可行（自写 ~60 行）：
  ```
  ??_7VBase@@6B@:    [COL=??_R4] [f1] [f2] [f3] [??_E]                 (4 槽)
  ??_7VDerived@@6B@: [COL=??_R4] [f1@VDerived] [f2@VBase] [f3@VBase] [??_E@VDerived] [extra]  (5 槽)
  ```
  override 原位替换 / 继承槽指基类 / 新增槽追加 / `/GR` 下 `vtable[-1]=RTTI COL` 全符合合成语义。
  **坑**：reloc 的符号索引是**原始 COFF 索引**（aux 占位），现有 `parse_coff_obj` 会错位 ⇒ 需按 raw index 建映射。
- **`CEffCylinder` 试点 P1 现在就不过**（实测 `sizeof=4344` vs 二进 `4292`，+52）⇒ 试点**含一次真实头修复**。

## R5 59/145 复现但"多继承头"是误称

- **59** = 含 `char _gap_000[` ∧ `virtual` 的生成头 —— **精确复现**
- **145** = 有基类 ∧ 含任意 `char _gap_` 的头 —— **精确复现**
- ️ **"多继承头"是误称**：真正 ≥2 基类只有 **30**（注解侧 `base_class≥2` = 31 交叉印证）；
  其余 **115 是单继承 + gap**。
- `sizeof` 抽样 19 类：**11 个含 `_gap`/`virtual` 的类全部漂移**
  （`SceneObj` 1872/1784（+88 恰 = `_gap[88]` 双计）、`AStar` +4、`UIWnd` 72/68、`CEffCylinder` +52、
  `UINote` +280、`CGameData` +364、`SceneMgr` +232…），**8 个干净类全部 MATCH**
  ⇒ **炸弹真实、边界清晰、门禁可实现**。**注意漂移量非单一 +4**（+88/+364/+280 = 嵌套脏基类**传播**）
  ⇒ **P1 清单需含传递闭包**。
- ️ **§5 的回归样例已过期**：`UIWnd 96→68` 实为现树 **72→68**；`SceneObj 3196→1784` 实为 **1872→1784**
  （`pal3/src` 是 gitignored 生成物）⇒ **写死的数字必须实现时再生成，门禁须绑定 codegen 状态指纹**。
- **两个门禁噪音源**：`PAL_GDB.h→RoleAtt.h:87` `gbVec3D` 未定义（C2061，个别头不能自编译）；
  `wine_cl` 偶发 `C1034`（同参数先失败后成功）⇒ **门禁需重试 + 容错**。

## R6 判据豁免（乙）不够，扩为五条

原三条只盯 `ok` 降。**防不住**：
- **不降 `ok` 但系统性拉低多个 partial pct** 的真实退化
- **行蒸发盲区**：`compare_pal3.py:277` 只遍历 `ok` 单元 ⇒ 文件跌出 `ok` 则符号**整体从新基线消失**

**修订为五条**：① `L1` 不降 ② **逐符号 pct 不降** ③ `ok` 降须逐条证明
④ `unmatched`/`oob` 不增、`symbols`/`matched` **不缩水** ⑤ `diffs` 产物支撑逐条归因

## R7 成本重报

| 步 | captain 原估 | 复核定 |
|---|---|---|
| 1 | 半天 | **1–2 天**（两次端到端窗口 + 负例重做）|
| 4 | — | **1–2 天** |
| 3 | 天级 | **3–5 天** |
| 2 | 便宜 | **0.5–1 天**（前置后）|
| 5 | — | **1 天** |
| **合计** | — | **约 7–11 天**（captain 原估约低估 2×）|

## captain 的 §6 规格自检漏了一问

复核指出：§6 的 4 项自检**恰缺"集合变化时聚合量是否可比"**——这正是 R1 漏洞的根源。
**已补入自检清单**（见下）。

### 补充自检项（第 5 项）

> **当聚合量的定义域（集合）本身随操作变化时（如 partial 集合因"修成 L1"而变小），
> 聚合统计量（中位数/总和）是否仍可作棘轮判据？**
> ⇒ 本设计的答案是**不可**，故改用**逐符号键控**（R1）。

## 复核者未验证项（如实转记）

`err=3703`/`C2039=1068` 未独立重跑；26 条 `MISATTRIBUTED` 仅采信 captain 的 `Array::Insert` 单抽查
（**轻度"以偏概全"**）；链接级（整链 `.exe`）表槽位未测（`.obj` 层对 P3 门禁已足够）；
C-V 的 43 处 thunk 同构**采信前复核者结论**。

## R8（第 6 任复核者 kiro 在停止前发现，captain 已独立验证并量化）

**`oob = 0` 是一个近乎空洞的读数** —— 本会话发现的**第 6 例"恒真/近恒真门禁"**。

```
pipeline/compare_pal3.py:45-59  exe_text_image():
    if name == '.text':
        return image_base, data[raw_ptr:raw_ptr + 0x10000000], virt_addr
        #                          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        #                          从 raw_ptr 到**文件末尾**（Python 切片超尾静默截断），
        #                          **不是** .text 的 raw_ptr .. raw_ptr + raw_size
```

实测（`original/PAL3.exe`）：

| 项 | 值 |
|---|---|
| 文件大小 | `0x212000` |
| `.text` | `raw_ptr=0x1000`、`raw_size=0x169000` ← **真实代码区** |
| `exe_text_image` 实际返回 | `data[0x1000:]` = **`0x211000` 字节** |
| 该窗口实际跨越 | `.text`(0x1000) + `.rdata`(0x16A000) + `.data`(0x180000) + `.rsrc`(0x20C000) |

`oob` 判定（`:166-168`）：
```python
idx0 = e['va'] - image_base - text_rva
if idx0 < 0 or idx0 + size > len(text):   # len(text)=0x211000，而非 .text 的 0x169000
    stats['oob'] += 1
```

**⇒ `oob=0` 只证明"没有符号越过文件末尾"，不证明任何符号落在 `.text` 内**；
`.rdata` 里的地址也会被判"在界内"。**它量的边界比 `.text` 大 `0xA8000` 字节。**

**影响**：
1. **captain 此前两次把 `oob == 0` 当"证据"引用**（在 t3/t5 判据与方案 1 设计中）——
   该读数**为真但接近恒真**，**不构成"尺寸/偏移正确"的证据**。
2. **字节比对的边界不可信**：函数体读取若越过 `.text` 尾（`va ≥ 0x16A000`）会**静默读到 `.rdata` 的字节**，
   而非报错 ⇒ 理论上可造成"匹配上了但比的是错的数据"。**当前 129 个符号是否受影响 ⇒ 待窗口核实**
   （可用 `s4_diffs.json` 的 `size`/`va` 与 `.text` 尾 `0x16A000` 对照，静态即可判）。

**修订（列入方案 1，因它属同一文件同一职责）**：
```
exe_text_image 应返回 data[raw_ptr : raw_ptr + raw_size]，并把越界判定改为
   idx0 + size > raw_size      （.text 内，而非文件末尾）
另：应在 stats 中区分 `oob_text_end`（越过 .text）与 `oob_file_end`（越过文件），
    二者语义不同，不得合并计数
```

**captain 的自省**：这是本会话第 6 例恒真/近恒真门禁，且**是 kiro 复核者而非 captain 发现的**；
captain 此前引用它两次，**属"把恒真读数当证据"**——与"以缺席反推事实"同族（都是**用弱读数支撑强结论**）。

### R8 的落地实测（captain，2026-09-15）

**已实施**：`pipeline/compare_pal3.py`

| 改动 | 内容 |
|---|---|
| `exe_text_image()` | 返回 `data[raw_ptr : raw_ptr + raw_size]`（原先 `+0x10000000` → 切片超尾截断成"到文件末尾"）；**一并返回 `raw_size`** 供正确边界判定 |
| `compare_units()` / `_flags_matrix()` | 增 `text_raw_size` 参数并逐层传递 |
| 越界判据 | `_limit = text_raw_size`（**`.text` 的 raw_size**），不再用 `len(text)` |
| `stats` | 拆分 `oob_text_end`（越过 `.text` 尾 ⇒ 比对数据不可信）与 `oob_file_end`（越过文件末尾），**不再合并计数** |

**实测验证**：

```
修复前: exe .text: ... captured 2166784 bytes   (0x211000，跨越 .rdata/.data/.rsrc)
修复后: exe .text: ... captured 1478656 bytes   (0x169000 == .text raw_size) ✓
matched 129/189 symbols | L1 6 | partial 123 | oob 0 (text_end 0 / file_end 0) | unmatched 60
[L1 ratchet] previous 6 -> current 6
```

**独立复核的额外结论（captain 静态核实，重要）**：
用**正确的 `.text` 上界**（`0x56A000`）复核全部 129 个符号 ⇒ **越过 `.text` 的符号 = 0**，
且**没有任何符号的 VA ≥ `.text` 上界**（即 `symbols` 里没有落在 `.rdata` 的）。
⇒ **`oob=0` 当前"结论正确但推理错"**：正确性来自"所有符号都恰好在 `.text` 内"的
**副作用**，而非边界正确。**现有匹配结果不受本缺陷影响**（`L1`/`partial` 逐位不变已验证）。

⇒ 本修订是**纯正确性修复 + 恢复判据判别力**，无行为副作用。

**captain 的 3 处执行失误（如实留痕）**：
1. 首次补丁脚本**在写文件前断言失败** ⇒ `oob` 判定与打印行**未落地**，而 captain 一度以为已修
   （`oob_text_end: None` 就是线索）——**又是"以缺席读数误判完成状态"**。
2. 漏改 `compare_units()` **自己的签名**（只改了调用点）⇒ 运行期 `TypeError`。
3. 漏改 `_flags_matrix` 的传递（它同样调用 `compare_units`）。

---

## R9（第 6 任复核者 kiro 停止前报出，captain 已独立验证并量化）

**Mangler 缺陷直接产生 `unmatched = 60`（占 `symbols=189` 的 32%）** ——
而 `unmatched` **前 5 任复核者从未问过**（注意力全在 `partial` 123 与 `L1` 6 上）。

### 机制（captain 实读 `compare_pal3.py`）

```python
def match_symbols(funcs, mangled_map, base_idx):
    for sym in funcs:
        if sym in mangled_map: matched[sym] = ...; continue
        if sym.startswith('?'):
            continue        # ← mangled 但 mangler 生不出 ⇒ 计入 unmatched
        cand = sym[1:] if sym.startswith('_') else sym
        cand = re.sub(r'@\d+$', '', cand)
        if cand in base_idx: matched[sym] = base_idx[cand]
```

⇒ **`unmatched` = 「`.obj` 里是 mangled（`?` 开头）但 `mangler` 生不出该名字」的符号**。
**mangler 缺陷与 `unmatched` 是同一件事。**

### 实测（captain 编一个 passing 单元直接看符号）

编译 `pal3/src/Combat/CCBAIWindow.cpp`（同款 flags）⇒ `parse_coff_obj` 得 5 个符号：

```
MATCH   ?Reset@CCBAIWindow@@QAEXPAH@Z
MATCH   ?Destroy@CCBAIWindow@@UAEXXZ
UNMATCH ?OnMessage@CCBAIWindow@@QAEDPAPAVUIListBox@@@Z
UNMATCH ?Update@CCBAIWindow@@QAEDPAPAVCCBUI@@@Z
UNMATCH ?ShowWindow@CCBAIWindow@@QAEDPAPAVCCBControlWindow@@@Z
```

**⇒ 本样本 unmatched = 3/5（60%）**，与全局 32% 同量级。

### 两处已定位的具体缺陷（与 kiro 所报一致）

| # | 缺陷 | 实测 |
|---|---|---|
| **① 类类型前缀 `U`（应为 `V`）** | `UIListBox` 是 **class** 却生成 `PAUUIListBox` | mangler 手测： `mangle('CCBAIWindow','OnMessage','char __thiscall(UIListBox **)')` → `?OnMessage@CCBAIWindow@@QAEDPAPAUUIListBox@@@Z`，而真实 obj 是 `...PAPAVUIListBox@@@Z` |
| **② 缺 back-reference 压缩** | 重复类型应生成 `V1@` | 真实名末尾 `...UIListBox@@@Z`（**3 个 `@`**）vs mangler 的 `...UIListBox@@@Z` 少一个 ⇒ 无压缩；**`grep -nE "V\d\|back.?ref\|backref\|repeat\|seen" pipeline/ida/vc6_mangler.py` 零命中** |

kiro 另报第 ③ 处：**`CHAR`/`LPCSTR` 等 typedef 未解析为 `D`/`PBD`**（captain 未独立验证）。

### 为什么这条比方案 1–5 都更该先做

1. **它是"让本来无法评分的函数进入评分"**：`matched` 增大 ⇒ `L1`/`partial` 的**分母**增大。
   **当前 `L1=6` 是"129 个可判定函数里的 6 个"**；若 `unmatched` 大部分可救，
   可判定池可能显著扩大 —— **这改变整个评分的代表性**。
2. **它是**（近）纯 bug 修复**，不改 codegen、不改布局 ⇒ 风险远低于方案 3。**
3. **它直接服务第一优先级**（字节匹配）：`unmatched` 的函数**从未被比对过**，
   修好 mangler 后它们**第一次进入字节比对**。
4. **前 5 任复核者全部漏掉它** —— 这正是第 5 任自陈的"**框架内复核**"盲区的实例：
   5 轮都在 `partial`/`L1`/错误族的框架里，**没人问"这 189 个符号是怎么选出来的"**。

### 修订（**建议新增为方案 0，排在方案 1 之前**）

| 步 | 内容 | 判据 |
|---|---|---|
| **0** | 修 `pipeline/ida/vc6_mangler.py`：① class 用 `V`（或从注解取 class/struct 信息）② 实现 back-reference 压缩（`Vn@`）③ `CHAR`/`LPCSTR` 等 typedef 解析 | `unmatched` **显著下降**；`matched` **上升**；`L1` 不回退；**新增 `unmatched` 率作为门禁**（现无任何门禁盯它） |
| — | 承认：`matched` 上升后 `L1`/`partial` 的**分母变化**⇒ 必须**同时记录分母**（本会话已有"分母变即不可比"的教训） |

**⚠️ captain 的诚实标注**：`unmatched=60` 中**多少比例**是这两处缺陷造成的——**未验证**
（只测了 1 个单元 3/5）。且 kiro 的第 ③ 处（typedef）**未独立验证**。
**故方案 0 的第一步应是"把 `unmatched` 逐符号分类"（静态、无需窗口）**，再决定修哪些。

---

## R9 落地准备：`unmatched` 0a 分类完成 + 4 处缺陷精确定位（captain，2026-09-15）

### 0a 结果：**复现与基线逐位吻合**，证明该复现就是管线在做的事

```
.obj 符号总数=189   mangler 命中=129   unmatched=60 (31.7%)
```

与 `s4_baseline.json` 的 `symbols=189 / matched=129 / unmatched=60` **逐位一致**
⇒ 下面的分类可信（不再是"以缺席反推"）。

**特征分布**（一符号可多特征）：

| 特征 | 条数 |
|---|---|
| `??` ctor/dtor 形态 | **32** |
| `ptr-to-class`（`PAU`/`PAV`） | 19 |
| `by-value`（`H` 前缀） | 6 |
| `char*`（`PBD`/`PAD`） | 5 |
| `@N`（嵌套层级） | 5 |

### 4 处缺陷（**逐一手测定位**，非推断）

| # | 缺陷 | 实测证据 | 影响面 |
|---|---|---|---|
| **① 虚性未传入 mangler** | `mangle()` **有** `virtual_` 参数（`:149` `'U' if virtual_ else 'Q'`），但 `compare_pal3.py:build_mangled_map` **只探测 `{'virtual_':True}` 作变体、从不传真实虚性**。实测 `?Update@UIStatic@@`**`U`**`AEHMH@Z`（真）vs `@@`**`Q`**`AEHMH@Z`（产出） | 最大族（`??` 32 条中多为虚 dtor；`UAE` 形态） |
| **② 嵌套类名未转层级号** | 真实 `PAU`**`NODE@1@`**；mangler 产出 `PAU`**`AStarPathFinder::NODE@@`**。实测 `?PushOpen@AStarPathFinder@@QAEHPAUNODE@1@@Z`（真）vs `...PAUAStarPathFinder::NODE@@@Z`（产出） | 5+ 条，且**所有以嵌套类为参数/返回的函数** |
| **③ 类/结构体前缀未区分** | `encode_type:48-49`：`code is None and ptr > 0` ⇒ 一律 `'U' + t + '@@'`（struct 前缀）。实测 `UIListBox`（**class**）生成 `PAUUIListBox`，真实 obj 是 `PAVUIListBox`。且 `NODE *` 这类**裸类型名**（无 `struct`/`class` 关键字）根本走不到 `:43-46` 的 `tag` 分支 | 19 条 |
| **④ scalar-dtor 命名形态** | 真实 `??_GCEffGroupNode@@UAEPAXI@Z`；产出 `?_scalar_dtor@CEffGroupNode@@QAEPAXD@Z` —— **既非 `??_G`、虚性也错、参数还错** | 含 `??_G` 的若干条 |

**captain 的自我修正**：kiro 报的第 1 处缺陷写作「缺 back-reference 压缩（`V1@`）」，
captain 初读也以为是压缩；**实测证明 `@1@` 是嵌套类层级号、不是 back-ref 压缩**
（`?TryExpand` 的注解签名只有 1 个 `NODE *`，若为压缩则参数个数不符）。
⇒ **该表述需修正为「嵌套类名未转层级号」**。此为 captain 第三次修正复核者的成因表述
（前两次：`union` 变体、CRT 区域）——**但这次是我先信了它，再用实测纠正两个人。**

### 为何 0b 应排在方案 1–5 之前（保留前议）

`match_symbols` 的**唯一** `matched` 路径是 mangler（`base_idx` fallback 只对**非 `?` 符号**生效，
而 `.obj` 符号全是 `?` 开头）⇒ **mangler 是整个字节匹配判据的单点故障**。
修 0b ⇒ `matched` 上升 ⇒ `L1`/`partial` **分母**上升 ⇒ **`L1=6` 的代表性改变**。

### 0b 的范围（已定，勿扩大）

1. `compare_pal3.py:build_mangled_map` 改为**按函数传入真实虚性**
   （从注解 `methods` 或 decomp 签名里的 `virtual` 关键字提取）
2. `vc6_mangler.encode_type`：裸类型名（无 `struct`/`class` 关键字）也走类分支；
   用已知的 class/struct 表决定 `V`/`U`
3. `encode_type`：生成**嵌套类层级号**（`NODE@1@`）而非完整限定名
4. `mangle`：`scalar_dtor`/`??_G` 形态

**判据**：`unmatched` 显著下降 · `matched` 上升 · `L1` 不回退 ·
**新增 `unmatched` 率门禁**（现无任何门禁盯它）· **同时记录分母**（本会话已有"分母变即不可比"的教训）。

**诚实未验证**：60 条中每处缺陷的**精确**条数（特征可叠加，32+19+6+5+5 > 60）；
kiro 报的 `CHAR`/`LPCSTR` typedef 一处（captain **未能独立复现**，列为待核）。
