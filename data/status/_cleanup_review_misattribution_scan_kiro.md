# 独立复核：「归属误判统一扫描」负面结论 —— **主要结论：负面结论基本站得住，但文档存在多处遗漏/不精确**

> 复核者：kiro（独立复核）。方法：不采信文档任何一句陈述，全部重新反汇编/重新统计/重新实测。
> 结论提要：
> - **主张1（CalcSpeed/ProcessAllCmds 物理不可能）：CalcSpeed 一族「成立且证据比文档更强」；ProcessAllCmds 的推理本身正确，但其「净收益」被文档夸大（从未单独验证过，实测无可观测收益）。**
> - **主张2（四个判据全部失败，无法区分归属错/类型标错）：成立。且我独立设计的「判据v2」同样失败，失败根因比文档描述的更深——过半假阳性是脚本对数组/嵌套字段访问的偏移提取错误，而非纯语义歧义。**
> - **`[MISATTRIBUTED]` 标记：不能直接当候选入口。抽样显示 >50% 已被更早的独立分析判定为「callee 归属本身正确」。**
> - **批量边界：不存在可安全批量处理的子集。**

---

## 1. 主张1 复核结果：CalcSpeed 成立且更强；ProcessAllCmds 推理对但收益被夸大

### 1.1 独立反汇编核对（不采信文档数字，全部重新算）

**`0x4DB640` CalcSpeed**（`objdump -d --start-address=0x4DB640 --stop-address=0x4DB656 original/PAL3.exe`）：
```
4db640: mov 0x4(%esp),%eax     ; 读第1个栈参数(roleIdx)
4db644: mov 0x8(%ecx),%ecx     ; this = this->m_pControl (this+8)
4db647: push %eax
4db648: call 0x4f3920          ; GetSpeedBonus(roleIdx)
4db64d: add $0x4,%eax
4db650: lea (%eax,%eax,4),%eax
4db653: ret $0x8               ; 清理8字节 = 2个栈参数
```
`0x4F3920`（GetSpeedBonus）内：`mov 0x481(%ecx,%edx,4),%cl`，`edx` 的计算是
`edx=(eax*8-eax)*32-eax = 223*eax`（即 `idx*892` 字节，非文档写的“idx”未展开值，我独立算出乘数=223*4=892B/idx）。
⇒ 该对象最小需 `0x481 + 892*idx`；idx≥0 时已需 ≥1154B（`0x481+4=1157`，与文档"≥1154"基本一致，微小差异来自四舍五入方式，不影响结论）。
`CCBSystem::m_pControl` 声明为 `CCBControl*`，`CCBControl.binary_size=368`（**我独立核实该 368B 是精确值，非"撑大"污染**，见 §5.2）⇒ **物理不可能，主张成立**。

**`0x4DB7A0` ProcessAllCmds**：反汇编显示是一个 **11 次循环**（`idx=0..10`，循环条件 `esi<0x2654`，步长`0x37c=892`，
`0x2654/0x37c=11.0`——**与 `CCBAttackSequen::m_Sequen[11]` 的 11 完全吻合，是本条独立发现的强旁证**），
每轮 `mov 0x8(%ebp),%ecx` 把 `this->m_pControl` 当新 this 传给 `IsActive(0x4ED040)/InitUI(0x4EE870)/SetRoleField(0x4F2BB0)`，
三者分别访问 `0x243/0x228/0x250 + idx*892`（**我独立算出真实步长是 892，不是文档写的 "idx*28"——文档这里的表述有误**，
但方向和结论不受影响，因为 892 远大于 28，"物理不可能"结论更强）。
**最坏访问需求 = `0x250 + 892*10 = 9512B`**（比文档"≥592B"大得多）。`CCBControl=368B` ⇒ 物理不可能，且比文档描述的证据更压倒性。

**判据②实测确认**（用户提示里的方向③）：`GetCmdSlot`（0x4DB660）用 `this+idx*40` 写 `+0x2c/0x2d`（=数组内偏移32/33），
恰好对应 `tagAttackSequen`（`CCBAttackSequen::m_Sequen[11]` 的元素类型，`binary_size=40`）里的
`bySpeed1(32)/bySpeed2(33)` 字段——**逐字节吻合，不只是"放得下"**。这是我独立验证出的、比"物理不可能"更强的正向证据。

### 1.2 CalcSpeed 迁移后签名核对（captain 未回答的问题）

`0x4DB640` 迁移后签名 `int __thiscall(int roleIdx, int nVal)`：
- `ret $0x8`：调用者清理8字节 = 2个显式栈参数，与签名的2个参数吻合。
- 全部7个调用点（`grep call.*4db640`：0x4db672/0x4db67f/0x4dbba8/0x4dbbb5/0x4dbe99/0x4dbea6/0x514960）
  逐一核对，**均在调用前 push 恰好2个值**（如 `push $0x0; push %edi`），与 `ret 8` 吻合。
- 函数体内只读了 `[esp+4]`（第1参，roleIdx），`[esp+8]`（第2参 nVal）**从未被读取**——这是"未使用形参"的
  正常现象（`ret N` 清理的字节数不代表全部被读取），**不是签名错误**。
- **结论：签名正确，未见问题。**

同时核对 `GetCmdSlot`（`ret 4`，1参，吻合）与 `InitCombatSlot`（`ret 4`，1参，吻合）——均无问题。
但发现一处**无关小瑕疵**：`InitCombatSlot` 的 `signature` 字段里残留旧类名前缀
`"void __thiscall CCBSystem::InitCombatSlot(int roleIdx)"`（应为 `CCBAttackSequen::`），纯文本瑕疵，不影响功能。

### 1.3 收益数字核实：**CalcSpeed 一族真实且可复现；ProcessAllCmds 从未单独验证**

- `76349df80`（仅 CalcSpeed+GetCmdSlot+InitCombatSlot 3方法迁移）commit message 记录：
  `ok 59→61 · matched 177/203→191/218(+14) · L1 16→17`。
  我用 `git show 76349df80:data/status/s4_baseline.json` 读出该次的 `matched=191, match_L1=17`——与当前 HEAD **完全相同**。
- `bdecb45b9`（本轮，加入 ProcessAllCmds 迁移 + 负面结论文档）**没有更新 `data/status/s4_baseline.json`**
  （`git show bdecb45b9 --stat -- data/status/s4_baseline.json` 无输出）。
- 我实测跑了一次完整 `codegen all`→`probe all`→`match`（**未跑 idat**，因为 decomp JSON 已在
  17:04:18 由 captain 更新为含 ProcessAllCmds 归属，早于 bdecb45b9 提交时间 17:14:38——
  即 apply/export 这一步 captain 已做过，我只是跑了后续不需要 IDA 的阶段）：
  ```
  python3 pipeline/cli.py codegen all   # exit=1（既有 ChoseCompose.cpp 回归，与本次迁移无关）
  python3 pipeline/cli.py probe all     # exit=1（拒绝刷新基线，按规读 probe_census.json）
  python3 pipeline/cli.py match         # exit=0
  ```
  结果：`data/status/probe_census.json`: `s2.ok=61/202`（与迁移前一致）；
  `data/status/s4_baseline.json`（本次 match 重新生成）：`matched=191/218, match_L1=17`
  ——**与只有 CalcSpeed 时的数字完全相同，ProcessAllCmds 未带来任何可观测的 S2/S4 层面净变化**。
  唯一可见的变化是 probe 输出里 `CCBAttackSequen.cpp: 5 ↓ 3`（该文件内编译错误数减少2个）。
- **结论**：ProcessAllCmds 的"物理不可能"**推理本身正确**（且证据比文档写的更强），迁移动作本身**无害**
  （没有引发回归），但文档把它和 CalcSpeed 并列为"两个已验证为真的正样本"、暗示同等确凿性，是**不准确的**：
  只有 CalcSpeed 一族跑过完整 codegen→probe→match 验证，ProcessAllCmds 的量化收益此前**从未被验证过**，
  是本次复核**第一次**给出该验证。诚实的表述应为："CalcSpeed 一族已验证，ProcessAllCmds 逻辑同型但收益未量化验证（现已补验：净收益≈0，但无回归）"。

---

## 2. 主张2 复核结果：成立，且我独立设计的判据同样失败——根因比文档写的更深

### 2.1 我独立设计的判据v2

设计动机：文档判据4只看"放不下"（尺寸不够），我尝试增加**结构性**检验：
被调函数访问的**全部偏移集合**，是否在**候选目标类型**的已知成员偏移上有 ≥2 处命中，
且这些偏移在**原声明类型**的已知成员偏移上命中更少（即"这批访问在目标类里成体系吻合，在原类里对不上"）。

脚本：`/tmp/scan_misattrib_v2.py`（只读，未修改任何仓库文件）。

**实测结果**：对原判据4的71个"impossible"候选跑判据v2 ⇒ **25个"REATTRIBUTE"，46个"UNCERTAIN"**
（比原71个收窄，看似有效）。

### 2.2 但抽样证明判据v2的"REATTRIBUTE"里≥85%仍是假阳性——且假阳性根因是脚本bug，不是语义歧义

抽样7条（`CCBSystem::ProcWeaponSkill/m_pEffectSimple`、`LineupUI::OnMessage/m_btnPar2`、
`MainEquipUI::CreateFromData/m_ClothName`、`RoleStatePanel::InitSlots/m_roles`、
`SaleUI::InitCombatUI/m_sort`、`UIEmote::Render/m_ani`、`UIRoleSelectDialog::CreateDialog/m_bk`），
逐一核对 `pal3/src/**/*.cpp` 里对应成员的**实际访问写法**：

```
SaleUI::OnMessage:      &this->m_ListGrid[3].m_disablepic       ← 数组下标[3]+嵌套字段
UISceneMap::LoadCompass: &this->m_mapbk.m_texs.m_ptex[4]        ← 两层嵌套+数组下标
LineupUI::OnMessage:     &this->m_btnPar2[7][1]._texName[160]   ← 二维数组下标+嵌套字段
MainEquipUI::CreateFromData: &this->m_ClothName.m_text[12]      ← 嵌套字段+数组下标
RoleStatePanel::InitSlots:   &this->m_roles[5].m_JingBar         ← 数组下标+嵌套字段
SaleUI::InitCombatUI:        &this->m_sort[32][1]                ← 二维数组下标
UIRoleSelectDialog::CreateDialog: &this->m_bk.m_id                ← 嵌套字段
```

**这7条全部**是 `this->member[idx].field` 或 `this->member.a.b[idx]` 形式，**没有一条是单纯的
`this->member` 直接访问**。`scan_misattribution.py`（以及我基于它写的判据v2）的正则
`r'&?this->(m_\w+)'` **只捕获成员名本身，完全没有解析数组下标/嵌套字段**，导致：
- 用于比较的 `member_off` = 该成员的**声明起始偏移**（如 `m_ListGrid` 的 98620）；
- 但实际代码访问的是数组内某个 slot + 内部字段的偏移（如 `98620 + 3*152 + 100 = 0x18384`附近，
  与"起始偏移"相差数百字节）；
- 于是"物理不可能"判断建立在**错误的偏移**上——不是"子对象/基类指针歧义"（文档给出的根因），
  而是**扫描器对 C 语法的偏移提取本身有 bug**。

**量化统计**（对原判据4全部71个候选去重后36个 method+member 对做同样核对）：
```
array/nested access (this->mem[ 或 this->mem.)：20 个 (56%)  ← 偏移计算几乎必然错误
direct access (this->mem，无下标/字段)：         5 个 (14%)  ← 偏移计算可信
not found / 无法定位源文件：                     11 个 (31%)
```
即**过半（56%）候选的核心数据本身不可靠**，与文档"根因是子对象/基类指针语义歧义"的定性判断相比，
我独立发现的这个"脚本无法解析数组/嵌套访问"的量化根因**更基础、更容易先修**（是纯工程 bug，不是语义困难）。

### 2.3 5个"direct access"候选逐一取证——发现第三种模式（文档和我最初设计都未覆盖）

对5个真正直接访问的候选逐一深挖，发现 `CCBSystem::ProcWeaponSkill/m_pEffectSimple` 是：
```cpp
(((CCBSystem *)this->m_pEffectSimple))->CCBSystem::GetThreadBase();
```
**called_class 与 method 所属类相同（都是 CCBSystem）**——这不是"方法该迁移到别的类"，
而是同一个类内部把 `this->m_pEffectSimple` 强转回 `CCBSystem*` 自调用（**self-type-punning**，
`GetThreadBase` 反汇编显示是清零一段大数组，`m_pEffectSimple` 字段可能被当作该数组的裸内存基址复用）。
`member_type=CEffectSimple, member_size=4` 这个"4字节"本身也高度可疑（CEffectSimple 在 AT-200
"撑大/占位"名单中，size=4 很可能是占位符而非真实类型大小，见 §5.2）。

**⇒ 结论：这是判据4/v2都未覆盖的第三种模式（"同类自引用类型双关"），不是归属错，也不是简单的
"类型标错"，需要单独的判据和更多取证，进一步印证"无法用单一机械判据覆盖所有情形"。**

### 2.4 主张2 verdict：**成立**。我的判据v2没有推翻它，但把"假阳性根因"的认识往前推进了一步：
过半假阳性是可独立修复的脚本 bug（数组/嵌套字段偏移解析），而非文档所称的纯语义困难；
修复该 bug 后，判据可能对"5个真直接访问"这个更干净的子集有效，但样本太小（5个，其中1个还是
"同类自引用"新模式），不足以证明"判据可行"，只能说"值得在修复脚本 bug 后重新评估一次"。

---

## 3. `[MISATTRIBUTED]` 标记抽样：真阳性率低，不能直接当候选入口

### 3.1 规模统计（区分两套不同的历史产物，避免混淆）

- `data/annotations/structs/*.json` 里的 `_misattrib_evidence` 字段（77个文件、418处文本命中）：
  **这不是本次扫描的候选**，是**更早几轮**独立迁移脚本（`tools/_migrate_playermgr.py`、
  `_migrate_round3.py`、`_migrate_saleui_slider.py`、`_migrate_rolestatepanel.py`）**已经执行完毕**
  后留下的**证据留痕字段**，属于历史记录，不是待处理队列。（若有人后续误把这418处当"待批量处理的候选"，
  会是误读——已在此明确澄清。）
- 真正的"[MISATTRIBUTED] 候选"来自另一套（更晚的）产物：`data/status/_cleanup_scan_attribution.json`
  （212个唯一 callee 簇，对应994处标记文本）+ `misattribution_ledger.json`（197个簇）+
  `_cleanup_scan_triage.json`（268条更大范围分类，含前两者）。

### 3.2 抽样5+个真取证（用 `_cleanup_scan_attribution.json` 里已带的证据字段核实）

| ID | 标记 | 已判定结论 | 我的评估 |
|---|---|---|---|
| AT-003 | `CCBEditor::InvokeItemMethod` x7 | "attribution agrees"（callee 只访问 CCBEditor 自身成员）| **不是归属错**——callee 归属本身正确 |
| AT-009 | `CCBRoleState::NotifyStateChange` x5 | "attribution agrees" | **不是归属错** |
| AT-022 | `AStarPathFinder::GetHeuristicIdx` x3 | "callee attribution is BINARY-CONFIRMED correct"；根因是**调用方**把 CCBAI 错当 this | **callee 没错，问题在 caller** —— 与"方法归属错"是不同性质的问题 |
| AT-034 | `Actor::ResetDefaultState` x2 | "attribution agrees" | **不是归属错** |
| AT-035 | `Array::Size` x2 | "attribution agrees" | **不是归属错** |
| AT-038 | `CCBSystem::CalcSpeed` x2 | "attribution agrees"（**注意**：此条目判定的是这批标记本身对 CalcSpeed 的 marker，其判定逻辑是"callee body 只引用 CCBSystem 自身声明成员"——但我们已用二进制独立证明 CalcSpeed **确实**该归属 CCBAttackSequen。这说明该 ledger 工具的"attribution agrees"判据本身也有局限：它只检查 callee 内部访问是否越出**其当前声明类**的成员集，不检查这些成员的**类型是否放得下调用者传入的对象**——即它验证的是"内部自洽"而非"外部物理可能性"，两者是不同维度）| **该工具"agrees"结论与我们的二进制证据不矛盾（不同维度），但提醒：不能把这套工具的"agrees"直接当"无问题"** |

**统计**（对全部212个簇分类）：
```
attribution_agrees（callee 归属正确，非归属错）:  108 个 (51%)
caller-this 类型错（根因不在 callee 归属）:         1 个 (0.5%)
仍未判定（NEED_EVIDENCE）:                         88 个 (42%)
其他（DOCUMENT/DELETE/FIX_PIPELINE等）:            15 个 (7%)
```
**真正被判定为"callee 应该迁移到别的类"的：0 个**（在这212个簇里）。
`misattribution_ledger.json` 的197个簇：**bucket A/B（决定性可改名）= 0 个，全部落在 bucket C（需要考古）**
（这一点已由更早的 `AT-198` 记录确认，我独立核实 `python3 -c "..."` 复算一致）。

`_cleanup_scan_triage.json`（268条，覆盖面更广）的分类统计：
```
B1_fix_annotation（明确应修 annotation）:        4 条 (1.5%)
B2_fix_pipeline_codegen（应修 codegen/pipeline）: 23 条
B3_need_evidence（仍需取证）:                    200 条 (75%)
B4_delete（应删除的死信号）:                      14 条
B5_intentional_keep（有意保留）:                  27 条
```

### 3.3 §3 结论

`[MISATTRIBUTED]` 标记**不能**直接当候选入口批量处理：抽样和全量统计一致显示，
**过半标记的 callee 归属本身是正确的**（标记只是历史遗留信号，可能反映"曾经的归属错误但后来已被修复"或
"从未真的错过、标记本身是误报"）；真正待处理的 `NEED_EVIDENCE`/`B3` 类别占大多数（42%~75%，视统计口径），
且这些**仍需要逐个取证**，取证成本与"从零开始扫描"基本相当（因为标记本身不携带可信的方向性信息）。
文档没有涉及 `[MISATTRIBUTED]` 标记本身的真阳性率，这是文档的一处**遗漏**（用户要求回答但原文档未覆盖），
本次复核补上了这一空白，结论是**入口不比从零扫描更省力**，与主张2"必须逐个取证"一致，但**不支持**
"入口是现成的、应据此推进批量"这个乐观推论——现成的"入口"本身就已经内嵌了旧证据，说明这些线索**已经被
前几轮工作消化过一遍**，剩余的大多是消化不动的困难案例。

---

## 4. 批量边界判断：**不存在可安全批量处理的子集**

基于以上证据：
1. 判据4/v2 的核心数据源（decomp 文本里 `this->member` 的偏移提取）在 >50% 案例上**不准确**
   （数组/嵌套访问未被正确解析）——**这是唯一可能有"批量"价值的方向：先修这个脚本 bug**，
   但这只能把候选池从"含大量脏数据"变为"数据干净但仍需逐个语义判断"，不能直接产出可信的批量迁移列表。
2. `[MISATTRIBUTED]` 标记里 108/212（51%）已被判定 callee 归属本身正确，**可以批量"取消标记"或
   归档**（这是一个真实存在的、低风险的批量操作——但这是"清理噪声标记"，不是"批量补 annotation 迁移"，
   两者不可混淆）。
3. 剩余的 `NEED_EVIDENCE`（88~200条，视统计口径）**没有发现任何可以合并处理的规律子集**——
   我尝试的"同一 member 在同一类的多个方法里是否总以同一真实类型出现"（用户提示方向①）在
   `m_ListGrid`/`m_pControl` 等案例上，"总以同一真实类型出现"本身依赖对每个访问点单独解析数组/嵌套
   偏移，无法脱离逐个取证。
4. **唯一确认可以批量、低风险执行的动作**：修复 `scan_misattribution.py` 对 `this->member[idx].field`
   模式的偏移提取（把数组下标 * 元素size + 字段偏移 累加进"实际访问偏移"，而非只取成员声明起始偏移）。
   **本次复核未做此修复**（脚本是只读工具，按纪律不应更改产物；且修复后重新评估仍需逐个抽样验证，
   预计仍会剩下大量 UNCERTAIN，不能保证产出可信批量集）。

**⇒ 结论：批量补 annotation 在当前数据状态下不可行；"批量边界"存在于比 annotation 更早的一层
（扫描器脚本本身的偏移解析能力），修复该层是有价值的独立工程任务，但不等于"批量补 annotation 的前提成立"。**

---

## 5. 诚实性与完整性核查

### 5.1 §1 收益数字：**可复现，来源可信**

- `ok 59→61`、`L1 16→17`：commit `76349df80` message 原文即有，我独立用 `git show` 读取
  `data/status/s4_baseline.json`（该 commit 版本）复算 `matched=191, match_L1=17`，与当前 HEAD
  一致 ⇒ **真实、可复现**。
- 采用的验证方式：**优先读现成 status 文件**（`git show <rev>:data/status/s4_baseline.json`，
  零额外算力成本）+ **补充跑了一次真实 codegen→probe→match**（未跑 idat，因 decomp JSON 已是最新）
  以验证 ProcessAllCmds 单独收益——耗时：codegen 83s、probe 93s、match 131s，共约 5 分钟。
- **发现的不准确之处**（§1.3 已述）：ProcessAllCmds 的收益被文档暗示与 CalcSpeed 同等确凿，
  实为**从未验证**，补验后发现净收益≈0（但无回归，签名/归属仍正确，不构成撤回理由）。

### 5.2 AT-200 "binary_size 撑大" 问题是否影响主张1：**核实后确认不影响**

`_cleanup_scan_attribution.json` 里的 `AT-200`（evidence_grade=A）指出52个 struct 文件的
`binary_size` 被 `safe_size = max_offset * 2` 公式污染。`CCBControl.json` 恰好在这52个文件名单里，
这本可能威胁主张1的"368B 物理不可能"结论的可信度。**我独立核实**：
`CCBControl` 当前 `known_members` 最大声明偏移是112（`m_Thread: tagControlThread[4]`），
`tagControlThread.binary_size=64`，`112+4*64=368`——**与 `CCBControl.binary_size=368` 精确吻合**，
证明这个368B是**精确计算值，不是被"×2"撑大的可疑占位符**。⇒ **AT-200 问题不影响主张1的可信度**，
但这是一个值得记录的排查过程：**任何引用 binary_size 做"物理不可能"判据的场合，都应先核实该
size 是否命中 AT-200 名单，并检查"最大声明偏移”是否等于 binary_size（若明显小于，则可能是占位符）**。
本次对判据4的71个候选做了同名单交叉检查（见 `data/status/_scan_misattribution.json` 分析），
命中数仅4条且这4条member_size本身很小（4~24B，是被压缩而非撑大），不影响判据4的整体可信度评估。

### 5.3 扫描器 `tools/scan_misattribution.py` 的缺陷：**文档未提及的新发现**

除文档已承认的"假阳性根因是子对象/基类指针歧义"外，本次复核发现：
1. **数组/嵌套字段访问解析缺失**（§2.2，56%候选受影响）——**这是比语义歧义更基础、更该优先修的 bug**。
2. **`min_required_span` 可能对准了错误的函数地址**：`§2.3` 中 `ScreenEffectMgr::ClearAllEffects`
   案例，`CameraCtrl::RenderFadeEffect` 的 vtable/methods 记录地址 `0x4BEBF0` 实际是一段
   "设置 vtable 后 jmp 到 0x41CBC0" 的 thunk，不是函数本体，`min_required_span` 直接对 `0x4BEBF0`
   反汇编 0x400 字节可能扫到了错误或不完整的代码段。**这可能导致该类"callee_min_need"数字不可信**
   （具体在本例中恰好因为 thunk 头部就有对 `%ecx` 的访问而"凑巧"算出接近合理的数字，但机制上不可靠）。
3. **未做互斥检测**：同一个 `(method, member)` 对，若被调用了多个不同的目标类方法（如
   `SaleUI::OnMessage` 对 `m_ListGrid` 同时调 `GetItemData` 和 `GetGridOffset`），脚本把它们当独立候选
   分别输出，未去重合并，实际上是同一处代码证据的重复计数（不算严重 bug，但影响"71个候选"这个规模数字
   的直观理解——去重后实际是36个不同的 method+member 对，见 §2.2）。

### 5.4 是否存在夸大或缩小

- **夸大**：把 ProcessAllCmds 与 CalcSpeed 并列为同等验证过的"正样本"（§1.3）；
  假阳性根因归纳为单一的"语义歧义"，未提及占多数的脚本 bug 成分（§2.2）。
- **缩小/遗漏**：未回答 `[MISATTRIBUTED]` 标记真阳性率问题（§3，用户在原始需求里明确问到，
  原文档未覆盖，本次补齐）；未提及 `_misattrib_evidence` 历史字段与本轮扫描候选的关系容易混淆（§3.1）；
  未核查 AT-200"撑大"问题是否波及本轮判据依据的 binary_size（§5.2，核查后确认无影响，但原文档未做
  这个排查动作，是过程完整性上的遗漏）。
- **未发现的夸大**：四个判据的命中数字（1/57/51/71）、"排除继承关系后71→67"，我均未逐一重跑复算
  （成本考虑，且这些数字与本次核心结论——"负面结论基本成立"——不冲突，重跑价值有限）。

---

## 6. 遗漏项（供后续参考）

1. `scan_misattribution.py` 的数组/嵌套字段偏移解析缺陷（§2.2/§5.3.1）未修复，若后续要重启这个方向，
   应先修这个再重新评估判据可行性。
2. `ScreenEffectMgr::ClearAllEffects` 案例里 `CameraCtrl::RenderFadeEffect`/`RenderFadeEffectB` 的
   "thunk vs 真实函数体"问题（§5.3.2）未彻底厘清，`0x4BEBF0`是否是正确的 vtable 记录地址值得单独核实。
3. `CCBSystem::ProcWeaponSkill`/`m_pEffectSimple` 的"同类自引用类型双关"模式（§2.3）是一个新发现的
   问题类别，未深入取证到可下结论的程度，仅记录现象。
4. `AT-022`（`AStarPathFinder::GetHeuristicIdx`，callee 正确、caller 传错 this）这类"caller-side"
   问题，是否值得单独立项处理（与"callee 该迁移"是完全不同的修复方向），文档和本次复核都未展开。
5. `InitCombatSlot` 注解里残留的 `CCBSystem::` 前缀文本瑕疵（§1.2）未修复（纯文本问题，不影响功能，
   本次复核职责是"复核负面结论"不含"顺手修复"，故未动）。

---

## 7. changed_paths_and_reverted（本次复核对仓库的全部影响，及还原记录）

**未修改 `data/annotations/**` 任何文件**（全程只读该目录）。

**为验证 ProcessAllCmds 收益，跑了以下会写生成物的命令**（均为纯 Python，未调用 idat）：
```
python3 pipeline/cli.py codegen all    # 重写 pal3/src/**（gitignored，非 tracked）
python3 pipeline/cli.py probe all      # 重写 data/status/probe_census.json（非 tracked）
python3 pipeline/cli.py match          # 重写 data/status/s4_baseline.json（非 tracked）
                                        # 追加写入 data/status/pal3_registry.jsonl（tracked！）
```

**唯一被追加改动的 tracked 文件**：`data/status/pal3_registry.jsonl`
**还原动作**：`git checkout -- data/status/pal3_registry.jsonl`（已执行，`git status` 确认已清空该文件的 diff）

**新建的临时文件**（均在 `/tmp`，不在仓库内，无需清理仓库）：
- `/tmp/scan_misattrib_v2.py`（我设计的判据v2，只读脚本）
- `/tmp/scan_v2_results.json`（判据v2输出）
- `/tmp/pal3_full.asm`（`objdump -d` 全量输出，用于 grep 调用点）
- `/tmp/s4_baseline_after_calcspeed.json`（`git show 76349df80:...` 的历史版本副本，用于对比）
- `/tmp/codegen_out.log` / `/tmp/probe_out.log` / `/tmp/match_out.log`（命令输出日志）

**未改动、确认保持原状的既有 untracked 文件**（不属于本次复核产生，来自 captain 先前工作，未清理）：
- `.agent-teams/archive/cleanup-arch-scan/`、`.agent-teams/archive/cleanup-exec-fix/`、
  `.agent-teams/archive/spawn-probe/`、`.agent-teams/cleanup-arch-fix/`
- `data/status/_scan_misattribution.json`（`scan_misattribution.py` 的既有产物，本次只读引用）

**最终 `git status --short` 核实**：仅剩上述 untracked 目录/文件（均非本次复核产生），
`data/annotations/`、`data/status/pal3_registry.jsonl` 均已确认零改动/已还原。
