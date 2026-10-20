# 对抗评审：编译错误自动分层归因（attribution）方案

- 评审对象：analyzer《编译错误自动分层归因——方案》
- 评审者：verifier（对抗立场，独立实测）
- 日期：2026-10-20
- 基线：`HEAD ce60e355c` · S2 121/214 · 总错误 1290

## 结论：**PASS-WITH-CHANGES**（6 项必改，否则不得实现）

方案骨架（token-provenance + decomp 对照 + B3 抽样校准）**方向成立**，且有两个关键前提
经我实测**得到证实**（见 §0）。但作为"100% 覆盖的自动判定器"**不成立**，必须降级为
**「带置信度与证据指针的候选清单」**；另有 6 处判据/验证缺陷会系统性误导。

---

## §0 先确认方案中**正确**的部分（避免误伤）

| 方案主张 | 实测 | 判定 |
|---|---|---|
| census error 有 `file` 字段且可 ≠ `unit` | `keys=('code','file','line','msg')` 全 1290 条 | ✅ 成立；`file≠unit` **50 条（3%）**，均为头文件错误 |
| decomp 无行号，但有 `address` | keys `= {address, decompiled_c, local_vars, name, signature, size_bytes}` | ✅ 成立 |
| 生成源 `// 0xADDR` 锚可映射 decomp `address` | 坐标**同一套**：CCBStage.cpp 锚 226 个 ∩ decomp 样本 400 个 = 25 | ✅ 成立 |

---

## §1 判据有效性（**必改 1、2**）

### 1.1【必改】`_tail_/reg_/_inline_/_field_/_unk_` 是 **codegen 自造名**，不是注解自造
实测生成源中 codegen 自造标识符合计 **1846** 处；它们在 annotation 中的命中：

| 名族 | annotation 命中 |
|---|---|
| `_tail_*` | **0** |
| `reg_*` | **0** |
| `_inline_*` | **0** |
| `_field_*` | **0** |
| `_unk_*` | **0** |
| `_gap_*` | 5（少量注解也有） |

⇒ 方案规则「token 在 decomp/annotation 找不到 ⇒ DATA（注解自造）」会把这些
**codegen 侧产物误判为 DATA**。实证：错误 msg 中出现这些名的有 **34 条（2%）**，例如
`'skillCount' : is not a member of '_inline_RoleAttRemarkSkills_skillCount'`、
`'_inline_RoleSystemTeamSlotOverlay_m_teamSlots' → double`。

**可检验条件**：对每条 DATA 判定，若 token 命中上述 6 族前缀 ⇒ 必须转 UNKNOWN 或反转
为 codegen-side 信号，不得直接 DATA。

### 1.2【必改】`void *` 不能单独作为 DATA 信号
`data/annotations/functions.json` 中 `void *` 出现 **26 处**，多为**真实 API 签名**
（`memcpy`/`memset`/`LPVOID` 语义）。把「类型是 void*」直接判 DATA 会把合法的
通用指针接口判错。

**可检验条件**：`void*` 仅在**同时满足**「是自定义类成员/自定义函数形参」且「decomp 侧
有具体类型消费证据（如传入 `char*`/`strcpy`/`T*` 形参）」时才计入 DATA。

### 1.3 双重根因确实存在，二元标签必错一部分
实测「占位型 token + 参数/赋值转换」同现的错误 **80 条（6%）**：
```
pal3/src/Combat/CCBRoleState.cpp:L11373  '=' cannot convert from 'void *' to 'unsigned long *'
pal3/src/Combat/CCBStageCam.cpp:L1876    'EditBoxGetFloat' param1 'void *' -> 'HWND__ *'
```
这类既可能是「占位型没真型化」（DATA），也可能是「C++ 要求显式铸而生成侧没补」（MECHANISM）。
**强制二元标签会让 6% 的样本必然标错**。
**可检验条件**：标签集必须是 `{DATA, MECHANISM, BOTH, UNKNOWN}`；`BOTH` 必须允许。

---

## §2 定位可靠性（**必改 3**）

### 2.1 锚覆盖 **97%**，非 100%；缺锚导致 **119 条（9%）必落 UNKNOWN**
精确统计（函数定义 = 行首 `Type Class::Name(` 且下一非空行以 `{` 开始）：

```
精确函数定义 2947；有锚 2878 = 97%；缺锚 69
缺锚样例：PAL_GDB::GDB_GetComboID · GRPinput::RunJoystickControlPanel
          GRPinput::GetMouseDeltas · PalScript::Cleanup · PalScript::ClearAllWaitObj
          PalScript::Op_RoleMoveTo
```
缺锚文件内的错误数：`PalScript.cpp 80` + `PAL_GDB.cpp 25` + `GRPinput.cpp 14` = **119（9%）**。

⇒ 若无回退映射，仅锚缺失就吃掉 9%，而不是方案估计的「12–18% 里的一小部分」。

### 2.2【必改】必须加**函数名回退映射**
用生成函数名（`Class::Method`）匹配 decomp 的 `name` 字段（如
`CCBStage::MoveToAbsolute` ↔ `CCBStage_MoveToAbsoluteint_int_0050a770.json`）。
**可检验条件**：对 69 个缺锚函数做回退，映射成功率需实测 ≥90%，否则这些直接 UNKNOWN。

### 2.3 头文件错误（3%）不能走函数锚
`file≠unit` 的 50 条是头文件错误（如 `tagCmdData.h:16`）。方案已提「decl 路径」，
需明确：**这类只查 annotation provenance，不做 decomp 对照**，且结论只能是
`DATA / UNKNOWN`，**不得判 MECHANISM**（无函数上下文，无法证明代码变换有问题）。

---

## §3 度量欺骗（**必改 4**）

### 3.1 「DATA 68%」极易自我实现
判据偏向「占位型」这一类（我人工分类时也偏好它，因为我先看过占位型清单）。
若判据只认占位特征 + decomp 缺失，DATA 档会系统性吸收所有含占位 token 的错误。

**可检验条件**：报告必须**同时**给出：
- 各判据分支的**命中数与占比**（如 provenance 高置信 X 条 / decomp 缺失 Y 条 / 指纹等价 Z 条）
- 若单一分支占比 >60% ⇒ 视为判据失衡告警，要求人工抽样复核该分支至少 20 条

### 3.2 不得当作优化目标
若把「提高 DATA 修复率」当 KPI，会诱导**把 MECHANISM 重新标成 DATA**（因为 DATA 更容易
"修好"——改注解即可）。**可检验条件**：该输出只允许出现在 triage 报告，**禁止**进入任何
门禁/棘轮的目标函数；若要门禁，只能棘轮 `UNKNOWN 不得增长`。

---

## §4 验证设计（**必改 5** —— 这是最严重的问题）

### 4.1【必改·阻断级】我的人工 638 条 gold 集 **没有落盘，不可复现**
实测：`data/status/` 下无任何 `*attribution*`/`*gold*` 文件承载该 638 条分类
（现存 `_attribution_evidence_20260919.md` 等是 9 月旧物，主题不同）。

⇒ 方案的验证门槛「总一致 ≥85% 且 F1 ≥0.80」**当前无法执行**。

**这是阻断项**：必须先建 gold 集并落盘，格式建议
`data/status/attribution_gold.jsonl`，每行
`{unit,file,line,code,msg,label,confidence,evidence,labeled_by,labeled_at}`。
且 gold 集必须包含**我看不到的题**（held-out 20%，由规则实现者之外的人标注），
否则「先用规则想清楚再标注」会污染一致率。

### 4.2 门槛依据不足
85%/F1 0.80 无推导。以二元+UNKNOWN 的四类标签计，**Cohen's κ ≥0.70** 比「一致率」更合适
（一致率会被多数类支配：若 DATA 占 68%，全判 DATA 也能拿 68%）。
**可检验条件**：报告 κ；并给**混淆矩阵**，不只给总数。

### 4.3 「DATA 档随修复单调降」这个校验信号不可直接测
错误总集会 churn（修复引入新错误，例如今天 `_ns_udts.h` 一次改动引出 4 族新错误）。
在 churn 的集合上谈单调性无法判定。**可检验条件**：该信号必须在
**固定错误集快照**（同一 census 的 `(code,msg,file,line)` 集合）上计算，或改用
「同一批错误在修复前后的层级归属是否稳定」来衡量。

---

## §5 失败代价与不对称保守（**必改 6**）

### 5.1 两个方向的误判都危险，但**误判 MECHANISM 更危险**
- 误判 DATA → 去改 annotation。annotation 有证据门槛（A 级），且 `cli.py check` 挡布局矛盾；
  但**改动会经 apply→export→codegen 放大到全量**。今天实例：一处 emit 声明缺失 ⇒
  C2501 430 + C2143 224 + C2146 218 + C1083 214（合计 1086 条一次性爆出）。
- 误判 MECHANISM → 去改 codegen。**改动影响全部 214 单元产物**，且可能静默改变字节。

⇒ **必须不对称保守**：结论默认 `UNKNOWN`；判 MECHANISM 需**最小可证伪条件**
（能指认到某个 transform 的具体行为，而非仅"decomp 表达式等价"）。

### 5.2 「decomp 等价但编译错」不等于 MECHANISM
反例方向：decomp 表达式可能恰好正确，而根因是 annotation 给出的**声明**（头文件里的
成员/签名）与 decomp 不一致。此时"表达式等价"无法排除 DATA。
**可检验条件**：判 MECHANISM 前，必须 additionally 验证「涉及的类型/成员/签名在 annotation
中被标记为已证（非占位、非误挂、非 _todo_）」；否则降为 UNKNOWN。

---

## §6 「应该自动化」这个方向本身成立吗？

**部分成立，但必须是「候选清单 + 人工确认」，不能是「自动判定」。**

理由（全部实测）：
- 9% 因锚缺失不可映射（+需回退后复测）
- 2% 会被 codegen 自造名误导
- 6% 是双重根因，二元标签必错
- 3% 是头文件错误，只能 DATA/UNKNOWN
- gold 集尚不存在

⇒ **可达形态**：一个离线工具输出
`data/status/attribution_census.json`（每条：候选标签 + 置信度 + 证据指针 + 建议动作），
其中 `UNKNOWN` 允许占 15–25%。**不做 100% 覆盖承诺**。

**替代/补充方案（推荐同时做）**：既然 `MECHANISM` 侧的共性是「变换不变量」，
而 `DATA` 侧的共性是「占位型未真型化」，可以绕过逐条归因，直接做**两条结构性门禁**：
1. `codegen_invariant_lint.py` 扩不变量（已有范式，token 级，不依赖 decomp 映射）
2. 「占位型不得进入指针/字符串位」的 annotation 门禁（`_todo_`/`_BYTE[]`/假类名）

这两条门禁的**收益可当场测量**（错误数下降），不依赖一个可能判错的分类器。

---

## §7 必改清单（按优先级）

| # | 必改 | 阻断级 | 验收条件 |
|---|---|---|---|
| 1 | **建并落盘 gold 集**（含 20% held-out、双人独立标注） | **是** | `data/status/attribution_gold.jsonl` 存在且 ≥400 条，含 held-out 标记 |
| 2 | 标签集改四类 `{DATA,MECHANISM,BOTH,UNKNOWN}`，默认 UNKNOWN | 是 | 报告含 BOTH/UNKNOWN 计数 |
| 3 | 排除 codegen 自造名族（`reg_/_tail_/_gap_/_inline_/_field_/_unk_/_ns_`）出 DATA 判据 | 是 | 34 条（2%）不得判 DATA |
| 4 | `void*` 不作单独 DATA 信号（需消费证据） | 是 | 26 处合法 API 签名不被误判 |
| 5 | 加函数名回退映射（69 个缺锚函数） | 是 | 回退映射成功率 ≥90% |
| 6 | 判 MECHANISM 需最小可证伪条件 + annotation 已证校验；头文件错误禁判 MECHANISM | 是 | 抽 20 条 MECHANISM 判定，≥18 条能指认具体 transform 行为 |
| 7 | 报告给分支命中分布 + κ + 混淆矩阵；不得进任何门禁目标 | 否 | 单一分支 >60% 触发人工复核 |

## §8 最终判定

**PASS-WITH-CHANGES**：方案骨架（B1 骨架 + B2 指纹辅证 + B3 抽样校准）可采纳；
但必须按 §7 改造，且**对外承诺从「100% 自动判定」降级为「带置信度的候选清单」**。

若 §7 第 1 项（gold 集）无法建立，则**本方案不得实现** —— 因为无法证明它比人工更准。
