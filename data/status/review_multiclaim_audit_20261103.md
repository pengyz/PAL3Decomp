# 「annotation 多注残余审计」独立对抗性复核（2026-11-03）

- 复核对象：三条审计结论（触发链 / 审计数据 134·229·16 / 病灶类定性①②③）。
- 铁律执行：**不准确=不判定**；凡裁定必带 `文件路径:行号`。测量性数字注明测量口径与数据源。
- 数据态锚点：`data/status/probe_census.json` `generated_at=2026-11-03T17:47:27`（S2 128/215）·
  `data/status/baselines/latest.json` `timestamp=2026-10-30T18:07:57`（"8"的出处）·
  decomp 产物 mtime 2026-11-03 17:41（不受 git 跟踪，见 `git log -- asm/pal3/decomp`：
  cb2f111a9 已把生成物移出 git）。

## 1. 总裁：**部分成立，根因机制须替代**

| 结论层 | 裁定 |
|---|---|
| 事实面（双注存在、8→102、C2039×52/C2228×30、m_nLayoutOffX 落籍、0x4C0510=7 类、批14=语义推断） | **成立**（逐条见 §2） |
| 触发链根因归因「0x485230 双注（**批13 'CalcState'** vs rejected 'StateUI::sub'）⇒ 混血」 | **替代**——混血载体是 **CScreenMode.json 那条 gap_fill 复制品单源自相矛盾**（name 自带 `StateUI::` 前缀 vs 文件类 CScreenMode），批13 的真实作用是**撤掉 `owner:"StateUI"` 对冲控制**（diff 实证 §2-A5⑦）；「CalcState」从未进入 IDB/decomp/codegen（grep 全 `pal3/src` 0 命中） |
| 数字口径「229 组**全库**多注」「语义批内 **16** 组」「成员全属 CScreenMode/**EquipUI/PropUI**」「8→102」 | **部分更正**：229 非全库口径（实测 474/232/222 三口径并存，§3）；16 组**不可复现**（实测 30，§2-B3）；EquipUI/PropUI **不成立**（10/10 成员仅 CScreenMode，§2-B1）；102 为 **C1003 截断读数**（§2-A7） |
| 病灶类定性①多注残余 ②语义猜名 ③dtor 撞名 | **成立**（②③措辞微调：②批14 自述「快速推断」有 commit 实证；③应为「同址身份冲突」而非「撞名」，§2-B6） |

## 2. 证据核对表

### A. 触发链（攻1/攻3）

| # | 审计主张 | 裁定 | 证据 |
|---|---|---|---|
| A1 | `StateUI.cpp:727`（sprintf into m_nLayoutOffX） | **成立** | `pal3/src/UI/StateUI.cpp:727` = `sprintf((char *const)&this->m_nLayoutOffX, "%02d:%02d:%02d", ...)`；同函数头 `pal3/src/UI/StateUI.cpp:652-653`（`// 0x00485230` + `void StateUI::sub(int fVal, int a3)`） |
| A2 | decomp 文件 sig 为 `CScreenMode *this` | **成立** | `asm/pal3/decomp/StateUI_subint_int_00485230.json`：`name:"StateUI::sub(int,int)"`、`signature:"virtual void __thiscall(CScreenMode *this, int fVal, int a3)"`、正文首行 `void __thiscall StateUI::sub(CScreenMode *this, ...)` |
| A3 | `m_nLayoutOffX` 落籍 CScreenMode | **成立** | `data/annotations/structs/CScreenMode.json:264`（offset `104`，type int，`source:"B:naming_m_n+FPU_misattrib"`，`evidence_level:"unverified"`）；全 `data/annotations/structs/*.json` grep 仅 CScreenMode.json 命中 |
| A4 | 「文件名 StateUI_subint_int = 混血出码证据」 | **部分成立** | 文件名实测 `StateUI_subint_int_00485230.json` ✓；但该名**全部来自 CScreenMode.json 单条目**（name `StateUI::sub` + sig `(int, int)`，`data/annotations/structs/CScreenMode.json:926-933`）——是**条目内**自相矛盾（名带类前缀 vs 文件类），不是两条目拼接。真正的跨条目混血在 0x4850E0（A6） |
| A5 | 根因=「批13 猜名致混血」 | **替代机制**（见 §2-A5 机制链） | ①「CalcState」零实效：`grep -r CalcState pal3/src` 0 命中；decomp 名= `StateUI::sub(int,int)` = CScreenMode 条目名。②合并规则 first-wins+owner 且**不看 adjudication**：`pipeline/ida/apply_annotations.py:1385`（`if addr not in functions or minfo.get("owner") == sname`）、`pipeline/ida/export_full.py:369`（同形）——`CScreenMode.json` 字典序先于 `StateUI.json`（`pipeline/gen/annotation_view.py:52-55` `sorted(glob)`），StateUI 条目无 `owner` ⇒ 被丢弃。③类归属按**名字 `::` 前缀**派生：`pipeline/ida/export_full.py:398-400`（`_cls = _name.rsplit('::',1)[0]` ⇒ "StateUI"）与 codegen 同规则 `pipeline/gen/stages/collect.py:196-198`（`cls = base.rsplit('::', 1)[0]`）。④this 型来自 methods dict 文件归属（CScreenMode 的 `set_methods`，`pipeline/ida/apply_annotations.py:1233`）⇒ Hex-Rays 按 CScreenMode 成员表渲染。⑤`virtual` 前缀是 export 对 vtable 地址的补旗：`pipeline/ida/export_full.py:622-623`。⑥「StateUI::sub」名字史：`79eb382fe`（vtable_gap_fill_v1 造 `StateUI::sub_485230`，自相矛盾名**当轮已被 CHANGE_LOG 记录**：`data/annotations/CHANGE_LOG.md:5944-5945`「其 name 自带 `StateUI::` 前缀，自相矛盾」）→ `46e671785`（机械去戳改 `StateUI::sub`，diff 实证）→ `88a2bf45c`（批13 撤 owner）。⑦F4(b) 裁决现成：`data/annotations/CHANGE_LOG.md:5940-5949`（A 级双证 vtable slot[2]+ctor vptr ⇒ 胜方 StateUI；**「真名待证，保留 sub_485230」**）——批13 改名 CalcState 时**未附新证据且撤 owner**（`git show 88a2bf45c -- data/annotations/structs/StateUI.json`：`-"owner": "StateUI"`） |
| A6 | （并联病灶）0x4850E0 同型 | **实测补充** | `CScreenMode.json:940-945`（键 `0x004850E0` 大写 E，批13 "CalcPosition"，sig `virtual int __thiscall(StateUI *this)`——**StateUI *this 落在 CScreenMode methods 里**）与 `StateUI.json:572-576`（键 `0x004850e0` 小写 e，"sub_4850E0"）**键大小写分叉** ⇒ 合并层视为两键双双存活 ⇒ 名（StateUI 侧）与 sig/this（CScreenMode 侧）分取两条目=真·跨条目混血（decomp `StateUI_sub_4850E0void_004850e0.json` name `StateUI::sub_4850E0(void)` vs sig `virtual int __thiscall(StateUI *this)`） |
| A7 | 「8→102 全归因 0x485230 双注」 | **部分成立** | 数字✓：基线 8（`data/status/baselines/latest.json:5913` `error_count: 8`，2026-10-30 态，8 条在 672/1510/1619/1621/1637/1641/1643/2372 行，现**全部消失**）→ 现 102（`data/status/probe_census.json` StateUI 条目）。但：①102 内 **92 条在 0x485230 体**（行 652-991，其中恰为 C2039×52+C2228×30=82「交叉类成员访问」+C2227×4+C2653×4+C2660×1+C1003×1）、**10 条在 0x4850E0 体**（行 591-651，C2440×4+C2227×3+C2653×3——cast/名空间形，**非成员访问**，因果未复验 §5-4）；②**102=C1003 截断读数**：`probe_census.json` 内含 `{"code":"C1003","line":830,"msg":"error count exceeds 100; stopping compilation"}` ⇒ 真错误数 ≥100 未知（CLAUDE.md「度量盲区：C1003 截断单元」纪律适用；StateUI.cpp 已成新截断单元） |

**A5 机制链（替代归因，逐跳带行号）**：
```
vtable_gap_fill_v1 造自相矛盾条目 name="StateUI::sub"（类前缀≠文件类）
  （CScreenMode.json:926-933；CHANGE_LOG.md:5944-5945 当时即记录"自相矛盾"）
→ 机械去戳 46e671785 改名 "StateUI::sub"（_485230 后缀剥除）
→ 批13 88a2bf45c 撤 StateUI 侧 owner=StateUI 对冲（git diff 实证）+ 名改 CalcState（未生效）
→ apply/export 合并 first-wins + owner，不消费 adjudication
  （apply_annotations.py:1385 · export_full.py:369 ⇒ rejected 条目照常胜出）
→ export mangler pre-pass 按 name 的 "::" 前缀定类 "StateUI"
  （export_full.py:398-400 ⇒ IDB 名 ?sub@StateUI@@… ⇒ 文件名 StateUI_subint_int_00485230.json，
   export_full.py:639）
→ 同条目经 CScreenMode set_methods 定 this=CScreenMode*
  （apply_annotations.py:1233 ⇒ Hex-Rays 按 CScreenMode 成员表渲染 m_nLayoutOffX@104 等）
→ codegen 按 decomp name 定类归文件
  （collect.py:196-198 ⇒ pal3/src/UI/StateUI.cpp:653 void StateUI::sub(int,int)）
→ StateUI* 编译单元里访问 CScreenMode 成员 ⇒ C2039×52 / C2228×30
```
因果链的跳跃点：审计把「双注」压成「⇒混血」，漏掉中间三层（合并语义/名字派生归属/UDT this 传播），
并把载体误指为批13 猜名——**双注不是必要条件**（单条自相矛盾条目即产出同型混血）；
但该"非必要"为代码推读结论，全管线反事实未跑（§5-5）。

### B. 审计数据（攻2/攻3/攻4）

| # | 审计主张 | 裁定 | 证据 |
|---|---|---|---|
| B1 | C2039 用成员（m_nLayoutOffX/m_FrameB/_embed_UIFrameWnd_968 等）「全属 CScreenMode/**EquipUI/PropUI**」 | **部分成立** | 数字✓：C2039×52、C2228×30 与 `probe_census.json` 逐码计数分毫不差；成员落籍**不成立部分**：10 个 C2039 成员名（m_nLayoutOffX/m_RoleDialog/m_nAudioState/m_nAudioFileId/m_fPan/m_StaticArray/m_nVideoState/m_fSceneVolume/_embed_UIFrameWnd_968/m_FrameB）经全 structs grep **全部仅 CScreenMode.json 命中**（m_nVideoState 另见 CCBRoleState.json）；**无一属 EquipUI/PropUI**。C2228 子成员（m_ppic/m_bvisible/m_disablepicInfo/m_pbkInfo/m_wndcolor 等）落 UIWnd/UIStatic/UIButton/UIProgressBar/UIDragBar 等 UI 基类（嵌入件的基类成员），亦非 EquipUI/PropUI |
| B2 | codegen 归属规则=？（按 decomp this 型还是 methods dict） | **实测=按 decomp name** | `pipeline/gen/stages/collect.py:196-198`（`name.split('(')[0]` → `rsplit('::',1)` → `cls`）；N1 注记明文「**分类保持 name 形原判**」`collect.py:200-202`。this 型只影响体渲染不影响归文件 |
| B3 | 「134 语义批溯源件·229 组全库多注·语义批内 16 组典型 0x4C0510=7 类」 | **部分成立** | 134✓：全 structs `name_source` 含「IDA语义分析 批N」实测 134 条（批1-16 求和恰=134，与 `audit_semantic_batch_multiclaims_20261103.json:5` `provenance_claims:134` 吻合）。229✓：`audit_…json:6` 与 `len(multi_claims)` 均=229。**「全库」不成立**：见 §3 三口径（474/232/222）。**「16 组」不可复现**：实测含语义条目组=30（严格「IDA语义分析」）/35（宽口径）；批13-14 组=7；批13-16 组=14；语义条目唯一类数=20；无任何自然口径产出 16 ⇒ 不判定该数字（审计 JSON 无生成器脚本、无口径元数据；全仓 grep `multiclaim` 仅命中该 JSON 与 `tools/cxx_gate.py` 无关）。0x4C0510=7 类✓：`audit_…json:737-787`（CEffSParticle/CEffgbParticle/CEffModel/CEffQuake/CEffAction/CEffect/RenderTarget2） |
| B4 | 病灶①「多注残余（同址多类 methods 认领，各阶段各取一注）」 | **成立** | 合并语义实证（A5）：apply/export 各自 first-wins+owner（apply_annotations.py:1385 · export_full.py:369）、rename 环对大小写分叉键 last-wins（apply_annotations.py:2326-2359 按 `int(addr_str,16)` 逐条 set_name）、export 前缀改写（export_full.py:398-400）——**各阶段取的可以是不同条目的不同字段**（0x4850E0 实证：名取 StateUI 条目、sig/this 取 CScreenMode 条目） |
| B5 | 病灶②「语义猜名（批14『Render/Update/Destroy 快速定名』=语义推断无成员证据）」 | **成立** | commit `88a2bf45c`（2026-11-01）自述：「批 14（20 条）：快速定名（Render/Update/Destroy/Init/Show/Get/Set 等语义推断）」、「Evidence: decomp 语义推断」、「Confidence: 85（批 14 为快速推断，语义精度低于逐件分析）」——**溯源=读 decomp 文本的语义推断**，无成员访问证据。旁证：0x4BE060 条目 `name_note:"从 decomp 推断（_todo_E060）"`（`data/annotations/structs/ScreenEffect.json:42-46`）。同 commit 自带误覆盖先例：「3 条误覆盖恢复（ArraySort__ovl_Jump/AnimUpdate/RandLerpF）」 |
| B6 | 病灶③「dtor 撞名（0x4BE060 ScreenEffect.Reset × ScreenEffectMgr._scalar_dtor_E060）」 | **成立（措辞更正）** | 双注实证：`data/annotations/structs/ScreenEffect.json:42-46` 0x004BE060 = `Reset`（批14，`name_note:"从 decomp 推断（_todo_E060）"`）vs `data/annotations/structs/ScreenEffectMgr.json:305-311` 0x004BE060 = `_scalar_dtor_E060`（`evidence_level:"A"`，五面卡正名+`declaration_only:true`）。合并结果=**语义猜名盖掉 A 级析构身份**：decomp `ScreenEffect_Resetvoid_004be060.json` name=`ScreenEffect::Reset(void)`（ScreenEffect.json 字典序先胜）。机制上是**同址身份冲突**非「撞名」（"Reset" 全库 34 类各居异址，无同址第二 Reset；且 `_scalar_dtor` 形本应被 codegen 跳过——`collect.py:251`——但 decomp 名已变成 Reset ⇒ 逃过 dtor 跳过守卫，析构体将以普通方法发射） |

### C. 语义猜名判据（攻4）

| # | 问题 | 裁定 | 证据 |
|---|---|---|---|
| C1 | 「禁伪语义命名」红线对函数名适用吗 | **文本未定，不判定违规** | 红线原文 `CLAUDE.md:92`：「禁止伪语义命名：`m_nState_4968`、`m_fParam_0A0` 这类用地址后缀伪装的名字没有语义价值，和 `_todo_` 没有区别。不确定含义时保留 `_todo_`。」——**示例（m_nState/m_fParam）与回退占位（_todo_）皆成员形**；原文未写"仅限成员名"也未明示覆盖函数名 ⇒ 适用面无明文。旁证：批13-14 的「Destroy 重名消歧（Destroy_XXXX 后缀）」是 commit `88a2bf45c` 明文既定做法（与红线示例的"地址后缀伪装语义"不同型——语义词在前后缀只做消歧）。⇒ 该红线对函数名是否适用**交项目裁定**，本复核不判违规。**但同节 `CLAUDE.md:94`「禁止仅凭 signature this 修正函数归属——必须有 decomp member access evidence」直接命中批13**：`CScreenMode.json:940-945` 把 sig `virtual int __thiscall(StateUI *this)` 的条目放进 CScreenMode methods（=凭 signature this 表归属），无成员访问证据 |
| C2 | 134 件里 name_note 含语义内容比例 | **134/134 = 100%** | 全 structs 扫描：`name_source` 含「IDA语义分析」的 134 条**全部**带 name_note 且含中文语义内容（如 `StateUI.json:570` `"状态计算（int64+float 比较）"`、`CScreenMode.json:944` `"位置计算（gbVec3D+循环）"`）。名字风格分布：语义词 90 / 语义词+地址后缀 25（Update_1CC0 形）/ Method_ 占位 13 / sub_ 残留 6 |
| C3 | 「语义分析」溯源=IDA 人工还是工具推断 | **=读 decomp 的语义推断（人或 agent 对反编译文本的推断），非二进制证据；CHANGE_LOG 无交代，仅 commit 自述** | `data/annotations/CHANGE_LOG.md` 全文无批13-14/2026-11-01 条目（语义分析条目止于 2026-05-17，`CHANGE_LOG.md:1017,1325`）；唯一交代在 commit `88a2bf45c` message（B5 引文）。批次对照：批13（8 条，含 `CScreenMode::CalcPosition/StateUI::CalcState`——**归属即凭 signature this，违 CLAUDE.md:94**）、批14（20 条快速推断）、批15-16（`35b6aeab9`「58 条定名，收敛完成」） |

## 3. 229 组口径分层

### 3.1 口径对照（实测）

| 口径 | 判定面 | 计数 | 位置 |
|---|---|---|---|
| 审计 JSON | 同 int 地址多**类** struct methods 条目（排除规则不明） | **229** | `audit_semantic_batch_multiclaims_20261103.json:6` |
| int 归一·多类·structs only | 同 int 地址 ≥2 不同类 | **232** | 复算（审计 ⊂ 此集，差 3 组：0x411BD0/0x41B640/0x41B6A0，排除规则未复验 §5-2） |
| claim_gate 生产闸 | **raw key 字符串**（大小写敏感）≥2 不同类，structs only | **222** | `tools/claim_gate.py:82-83`（`claims.setdefault(k,…)` 按原始键）⇒ **10 组大小写分叉双录逃逸生产闸**（含 0x4850E0/0x004850E0 型） |
| cxx_gate 闸① same_addr | 同 int 地址 ≥2 条目（structs+functions.json） | **474** | `tools/cxx_gate.py:46-47`（`by_addr[int(str(e['addr']),16)]`），`load_entries` 含 functions.json（`tools/cxx_gate.py:63-73`） |
| cxx_gate 闸③ cxx_rule | （类+归一名+严格签名）双**址**=重复定义面 | **4** | `tools/cxx_gate.py:55-58`——与"同址多注"**正交**，不是同一判定面 |

⇒ 审计定义（同 addr 多类 methods）≈ cxx_gate 闸①的**多类子集**，与 cxx_rule 无交集；
「全库多注」按字面应为 474（全来源）或 232（多类），229 是 232 减 3 组的窄口径。
**合法重载问题**：同址不可能是重载（一址=一个函数体）；跨类同名异签属合法 C++ 且被
`tools/cxx_gate.py:49-54` 闸②明文豁免（「同名异签=合法重载 ⇒ 仅同签双址=违规」，当前 same_name 违规=0）。
故 229 内的"合法形"只能是**裁定为共享实现**的组，不是重载。

### 3.2 真冲突 / 合法形 / 未定（裁定单源=`methods.adjudication`，依 `tools/answer_mechanical_verdicts.py:1-5` 的裁定口径；合法值集 `tools/claim_gate.py:15`）

| 层 | 组数 | 说明 |
|---|---|---|
| **真冲突残余**（含 `rejected` 条目仍被消费） | **34** | 含触发组 0x00485230（`audit_…json:2825-2843`）；rejected 条目照常进 IDB（A5 机制） |
| **合法形·闭合**（全条目 `shared_impl`） | **1** | 0x004c3db0（字节真值多表实含，`tools/answer_mechanical_verdicts.py:22-26` 的 P:multi_owned 判定） |
| **未定/未闭合** | **194** | 全未裁 126 + shared_impl 混未裁 51 + confirmed 混未裁 17 |

条目级：`rejected` 34 · `shared_impl` 102 · `confirmed` 17 · 未裁 401（共 554 条）。
「合法重载」贡献 = 0（定义上不可含）。shared_impl 是唯一合法形；102 条 shared_impl 中仅 1 组闭合。

## 4. 修复案评审

| 案 | 内容 | 成本 | 风险 | 评审 |
|---|---|---|---|---|
| **A** 逐组成员访问证据裁决 | `tools/audit_attribution_evidence.py` + decomp 实访逐组裁 | 高（229 组）；但机制现成：`db965829d`（R7×P 机械裁定已自动清偿 177 件、人裁余量 216→39）、`tools/answer_mechanical_verdicts.py`（P 档字节真值→裁定） | 低——符合 `CLAUDE.md:94`（member access evidence）与铁律「准确=判定」 | **系统路径推荐**；对 34 组 rejected 残余可先机械清（裁定已记录，非新判断） |
| **B** 机械撤 unverified+rejected ⇒ 语义批认领 | 按 evidence_level/adjudication 批量撤后让批定名上位 | 低（机械） | **高**：①0x4BE060 型——A 级 `_scalar_dtor_E060` 与批14 `Reset` 并存，机械序若不按证据级排序即砍真名；②0x485230 型——F4(b) 已裁「真名待证，保留 sub_485230」（`CHANGE_LOG.md:5948-5949`），机械保留 CalcState=**锁死未证名**；③批13-14 已有 3 条误覆盖先例（`88a2bf45c`） | **不推荐**作为独立方案；若做必须带证据级序 + 名字留白纪律 + 逐条 diff 复核 |
| **C** 只修 StateUI +94 病灶组 | 0x485230 按 F4(b) 现成裁决回落（删 CScreenMode.json:926-933 rejected 条目或恢复 `owner:"StateUI"`；名回 `sub_485230` 留白或留 CalcState 须显式裁）；0x4850E0 消键大小写双录（CScreenMode.json:940 与 StateUI.json:572 并键） | 低（1-2 组，裁决已有） | 低；遗留 227 组 + 0x4850E0 的 10 个 cast 形错误不保证随修消失（§5-4） | **先行推荐**（当轮即可做，且零新猜测） |

**推荐序：C → A**（B 仅作 A 的机械加速档，带证据级序）。
**安全前提（无论 C/B 都必须先做）**：合并层消费 `adjudication`（`apply_annotations.py:1385`、`export_full.py:369`
对 `rejected` 条目跳过）+ 方法键归一化 int（消除 claim_gate 222↔232 的 10 组逃逸）——
否则修完 0x485230 后，0x4850E0 型大小写双录仍会持续产出名/型分取两条目的混血。
**衰退纪律核**：撤批定名确有砍真名风险（B-①②），故任何撤名必须带反向证据（P:misowned 型正向反证，
`tools/answer_mechanical_verdicts.py:22-26`）或人工裁决，禁纯机械批量；修复后读数必须当场
apply→export→codegen→probe（CLAUDE.md 验证前强制全链），StateUI 已是 C1003 截断单元（A7），
判据用「最大行号是否前进 + 新增错误是否同族」而非总错误数。

## 5. 未复验

1. **「语义批内 16 组」**：无生成器脚本、无口径元数据；实测候选值 30/35/14/7/20/4 无一=16 ⇒ 数字不判。
2. **审计 229 vs 实测 232 的 3 组差**（0x411BD0 Object/ScriptObj dtor 对、0x41B640/0x41B6A0 GlowObj/Role 对——后者键大小写分叉 `0x0041b640`/`0x0041B640`）排除规则不明 ⇒ 口径闭合性不判。
3. **decomp 签名实参名 `fVal, a3`** 的来源：当前 CScreenMode.json:926-933 签名为 `void __thiscall(int, int)`（无名）、`lvars.json` 无 0x485230 条目、全 tools/pipeline grep 无生成点 ⇒ 疑 IDB 历史残留，未溯源，不判。
4. **0x4850E0 体 10 错**（`pal3/src/UI/StateUI.cpp:607` 等，C2440 `gbVec3D→Object3D*` cast 形）与双注的因果：未跑反事实（若只消双录不改 cast 形，错误可能留存）⇒ 因果不判。
5. **「双注非必要」**（单条自相矛盾条目即致混血）：系合并代码推读结论（A5 ②③④ 均为静态行号证据），全管线反事实未跑（decomp 产物不受 git 跟踪，无法回看批13 前态）⇒ 机制方向判、必要性不判。
6. **修复后实效**（S2/L1/字节面）：本次纯审读未跑 apply→export→codegen→probe→match；任何方案落地后的读数须按 CLAUDE.md 检查点当场读，L1 引用须带三限定（`docs/knowledge/gotcha_l1_reloc_dontcare_three_qualifications.md`）。
