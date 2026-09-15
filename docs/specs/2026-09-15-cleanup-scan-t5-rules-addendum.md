# t5 追加规则：`N1_STUB_CALL_NO_FIX` 与 C2660「跨类 this 直呼」族的分类（2026-09-15）

本文件是 `docs/specs/2026-09-15-cleanup-scan-t5-rules.md` 的**追加章节**，
承载 captain 追加的第三条 t5 规则（新增 `N1_STUB_CALL_NO_FIX` 类别 + C2660 族分开计数）。
判定依据分级见 `docs/specs/2026-09-15-cleanup-scan-taxonomy.md` §2。

---

## 1. 新增类别 `N1_STUB_CALL_NO_FIX`（非 misattribution 记录区，动作 `NO_FIX`）

### 登记规则（t5 固化）

- 存放位置：**独立的"非 misattribution 记录区"**（captain 给的二选一，推荐此者），
  或 `C2_intentional_signal`；**不得**归入 C3a（C3a 语义是"未修根的 misattribution"，与此类相反）。
- `class` / `action`：`N1_STUB_CALL_NO_FIX` / `recommended_action=NO_FIX`。
- **唯一目的**：防止这类站点被后续会话**反复当待修 misattribution 重扫**。
  故每条必须写明"已定案、NO_FIX、不可再开工"的判据，而不是留成 open 状态。
- 证据引用：`data/status/_cleanup_evidence_stub_call_4014F0.json`（engineer-annotation 落盘，
  captain 已授权；仅此一文件）。

### 已定案实例（我独立复核，与证据包逐项一致）

`0x004014F0`（annotations 名 `AStarPathFinder::GetHeuristicIdx`）：

| 项 | 实测 | 与证据包 |
|----|------|----------|
| 字节 | `32 C0 C2 08 00` = `xor al,al ; retn 8`（3 字节桩，恒返 0，不读任何 `this->member`） | 一致 |
| 邻槽 | `0x004014E0` = `33 C0 C2 08 00`（同为桩） | 一致 |
| vtable | `0x0056A600` 三槽 = `0x00401030 / 0x004014E0 / 0x004014F0`；callee 为 **slot 2** | 一致 |
| dword 引用 | 全文件仅 **1** 处（`0x0056A608` = vtable+8） | 一致 |
| 直接调用点 | **3** 处（`0x004D7576` / `0x004D7BB4` / `0x004D824C`，均 `E8 rel32`） | 一致 |
| 结构 | `AStarPathFinder` bases=[] size=24 vtables=[0x0056A600]；`CCBAI` bases=[] size=3664 **vtables=[]** | 一致（我已独立确认 `CCBAI.json` 的 `base_class` 为空、`vtables` 为空） |
| caller `this` | `esi`（`CCBAI`），签名 `CCBAI::HandleEnemyAction(AStarPathFinder *this, int, int)` 的 `this` 只因被调方命名而被渲染成 AStarPathFinder | 一致 |

**因此 M1/M4 均不成立**：
- M1 不成立（callee 地址唯一、vtable slot 映射正确；名字错误对字节无影响，且函数体零信息 → 无可依据的改名证据）；
- M4 不成立（两者**无继承关系**；三个调用方的归属由成员访问强证据独立支撑，不需要修正）。

---

## 2. C2660「跨类 this 直呼」族 —— **我不同意"标记判据被证伪"这一表述**，请按本节口径落地

captain 为此族给的两点定性是：
(a) 该族"可能不是归属错误，而是合法的直呼 vtable slot 函数"；
(b) 由此，"标记的判据与建议文本**被这组证据证伪**"。

**我的复核结论：证据只证伪了"建议文本"，没有证伪"判据本身"。** 两点必须分开，否则会把一条刻意设计当缺陷推翻。

### 证据：真实指令序列（非 Hex-Rays 渲染文本）

`original/PAL3.exe.asm:320345-320352`（调用点 1）：
```
loc_4D756D:
                push    edi
                push    ebx
                mov     ecx, esi          ; __thiscall 的 this
                call    sub_4014F0
                test    al, al
                jnz     loc_4D71F8
```
- **恰好 2 个参数**（`push edi` / `push ebx`），与 callee 自身签名 `retn 8`（2 参）**一致**；
- 被调地址 `sub_4014F0` 即 `0x004014F0`，**真实存在于二进制**，无"假调用"。

而生成源码把它渲染成 `AStarPathFinder::GetHeuristicIdx((AStarPathFinder *)this, nRoleIndex, (int)&this->m_nHandleEnemyWell)`
——**3 个参数**。故"C2660 参数个数不符"是 **decomp/IDB 侧的渲染问题**，不是调用点本身的问题。

### 结论：判据与建议文本要分开定性

**（i）建议文本 = 已证伪**（captain 对，证据包也如此主张）：
`-> fix IDB name of callee` 对本案无依据——callee 名字即使错也与字节无关，且函数体零信息无从改名。
→ **须改文案**（改成 `N1_STUB_CALL_NO_FIX` 语义 / `NO_FIX` / "二进制行为即如此"）。

**（ii）判据本身 = 未被证伪，且与仓库刻意设计一致**：
`git log -1 2010eb3ad` 提交信息原文：
> a qualified call on our own this via an unrelated class (`(((A*)this)->A::f`, or even `this->A::f`)
> **can never appear in the original source — its presence proves the callee's IDB name is misattributed**.
> The previous change laundered these into C-style-cast legal syntax, which compiles but **bakes the false type relationship into the decompiled source**.

即 2010eb3ad 的**刻意设计**是：可疑时**保留静态形态 + 保留标记**，
**不把错误的关系洗成合法语法**——因为洗白会掩盖类型关系错误。该提交同时记录了
"+2 S2 wins 全部来自合法形态、无一依赖洗白"，S2 45/201 零回退，并建立 1124 站点的改名 backlog。

对一个"callee 是桩、返回常量"的案例，**"callee 名字是否错"本就不可判定**——
恰恰是"保留静态形态 + 保住信号"的适用场景。故本案**不构成推翻判据的证据**。

**（iii）我要明确标注的风险（与 (ii) 不矛盾）**：
本案确实证明该族的**建议动作不可盲从**。若后人照 `-> fix IDB name of callee` 直接改名，
会造成**无证据批量改名**，正踩 `docs/knowledge/pattern_annotation_batch_rename_no_evidence.md`。
这正是"改文案"而非"改判据"的理由。

### 关于你提到的相反政策先例（非虚 callee 直呼改为 `((Cls*)this)->M(...)`）

该政策与 2010eb3ad 相反，且你已指出必须由**用户**裁决。我同意，并补一条**技术判据**供你上报时使用：
2010eb3ad 的论证是"合法形态并**不会**改善 `this` 类型关系，只会把错误关系写成看起来合法的代码"，
且它已**用数据检验过**（+2 S2 wins 均非洗白所得）。反向政策若要成立，必须给出**同样强度的检验**：
说明洗白后 S2/L1 的改善**不是**来自"把类型错误静默藏起来"换取的可编译性。
**在该检验给出之前，不得改判据**——这是我给 t5/t13 的建议口径。

---

## 3. 分开计数的规模：我能验证的数字与**无法验证的 110**

captain 要求"前者 110、后者多少"。**我逐项核对了所有可能有 110 的分桶，没有任何一个等于 110**：

| 来源 | 实测数字 |
|------|----------|
| `[MISATTRIBUTED]` 站点（生成源码，`.cpp` 口径） | **344** 站点 / **74** 文件 |
| `misattribution_ledger.json` cluster（按 `callee_class::method` 聚合） | **197**（`sites` 求和亦为 344；全 bucket `C`、`rename_to` 全 null） |
| `_c2660_join.json` 分桶（共 357 条 / 882 站点） | `DECL-OK` **171**条/294站点；`NO-ANNOTATION` 94/308；`DEEPER` 52/174；`AUTO-FIX` 32/81；`ODD-N` 7/24；`NO-RET` 1/1 |
| `DECL-OK` 中 top 条目 | `AStarPathFinder::GetHeuristicIdx` caller_args=3 vs declared_slots=2 sites=3（即本案例，在 **DECL-OK** 桶内） |

→ **`110` 无对应分桶**。请 captain 给出 110 的来源（哪个文件/哪个字段/用什么命令算出），
我才能做"110 vs 其余"的分列。**在此之前 t5 不得写出该数字**（写了就是不可复核的数字）。

**可立即用于分列的、我可验证的切分**（建议 t5 采用其一并注明口径）：
- **切分 A（站点口径，最贴近"族"的含义）**：`[MISATTRIBUTED]` **344 站点 / 74 文件**；
  其中 `_c2660_join.json` 判定为 `DECL-OK`（声明可解析）者 294 站点，
  其余 5 桶合计 588 站点。注意两套数据是**不同的人在不同时点**测的（`_c2660_join.json` 无时间戳），
  我**未验证**两者可逐条对齐，故只能作并行列示，不能相互扣减。
- **切分 B（cluster 口径）**：ledger **197** cluster；
  `DECL-OK` 171 条与之**数量接近但语义不同**（前者按 callee 聚合、后者按 C2660 报错条目聚合），
  **不可互相替代**。
- **切分 C（本案例所在的诊断口径）**：该族在 `_c2660_join.json` 中被判 `DECL-OK`
  —— 即"声明存在、只是调用形式不可编译"，与 `NO-ANNOTATION`（94/308，无注解可依）性质不同。
  **建议以 `DECL-OK` 作为"可能是合法直呼"的候选族**（294 站点），
  再以"callee 是桩 / callee 无第二个地址 / caller 与 callee 无继承"三项逐一复核收敛。
  这个收敛过程正是 `N1_STUB_CALL_NO_FIX` 的登记条件，也是防止盲目改名的手段。

---

## 4. 需 t5 单列的 C1/C3 条目（captain 指定的语义，按我的口径修正）

- **问题**：诊断信号与被证伪的**建议文本**混同——`[MISATTRIBUTED]` 标记把
  "合法直呼（callee 为桩）"与"真归属错误"报成同一个动作（`fix IDB name of callee`）。
- **修复性质**：**codegen 策略/文案变更**（`pipeline/gen/ast_transform.py`）。
- **批次**：**禁止进入"可立即修"批次**，标注 **"需 captain/用户裁决"**，由 captain 上报用户定夺
  （理由：与仓库刻意设计 `2010eb3ad` 相反，且涉及是否推翻"保留静态形态"这一 policy）。
- **不得**由团队静默改；**不得**以"改善 L1/ok"为由单方面翻转 policy。

**建议的条目字段取值**：
```
class: C1_arch_violation          # 诊断信号不可靠 → 属层职责/信号可信度问题
subclass: null
evidence_grade: A                 # 字节级 + asm 指令序列 + vtable + 提交信息
recommended_action: DOCUMENT      # 本轮不动；等待用户裁决后再定 FIX_PIPELINE
proof_needed: null（证据已足）     # 但需用户裁决"policy 是否翻转"
notes: 建议文本已证伪（须改）；判据本身未被证伪（保留静态形态+标记），
       请勿把两者混为一谈；规模分列待 captain 给出 110 的来源。
```

---

## 5. 其余规则不变（沿用 t5-rules §3）

M4 不进改名批次；`C/D/E` 级禁 `FIX_*`；`M_UNDETERMINED` 只进"需补证据"（但**本案已升级为 N1/NO_FIX**，
不再留在"需补证据"——见 §1）；ledger 无 `evidence_grade` → t5 必须显式写；
`binary_size` 撑大项逐 struct 取证。锚点 **L1 ≥ 5、ok ≥ 53/198**（分母 198 变动即判不可比）。

> **注（分类学一致性）**：`_cleanup_evidence_stub_call_4014F0.json` 内部同时写了
> `class=N1_STUB_CALL_NO_FIX` 与 `subclass=M_UNDETERMINED`。按本文件 §1 的登记规则，
> 该类应落在**独立的非 misattribution 记录区**；故 `M_UNDETERMINED` 在此是**遗留的过程性标签**，
> **不是**该条目的最终处置（最终处置 = `NO_FIX`）。t5 登记时须以 `NO_FIX` 为准，避免与
> `t5-rules §1`"M_UNDETERMINED 只进需补证据"的规则冲突。