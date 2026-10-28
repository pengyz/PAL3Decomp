# 独立复核：Plan A-T1（Destroy__ovl_03 归属+声明修复）

- 复核人：独立复核员（攻击式复核，不信任自述、只信实测）
- 日期：2026-10-28
- 范围：git 最近 2 commit（`9ec29fb10` T1 基建 + `5f17b64a5` T1 实效兑现）
- 方法：IDA MCP（original/PAL3.exe.i64，session 0fe83798，用毕 save=false 关闭）原始字节扫描 + 反汇编；管线侧全量测试 + 新旧分类器对照实测 + 基线快照多重集 diff。凡批量读数均以单发 `get_bytes`/原始字节复核（py_eval 批量 print 循环曾出现陈旧输出异常，所有引用数字均经原始字节二次确认）。

---

## 1. 总结：ACCEPT-WITH-FIXES

**修复本体正确、实效真实、无回归**：签名 ABI 等价论证成立（体 this 入 ecx + bare ret，调用形 `(int)this` 零改动），S2 124→133、L1 110→147、fixed=9 均实测复现，C1003「非真退化」定谳成立（且证据比自述更强）。`free_sig_decl` 平价性实测为**严格超集**（真实语料 5 增 0 损）。

**扣分在证据记述与欠账记录面**：source 证据行存在可证伪的细节（「双命中表」分解、五表计数、"27 类同体 override 簇"把不可判定的推断写成定论）；「9 处 C2065 全清」实为 14 处；T1 Step 5（10 处 overlay 注释回收）未做且 commit 叙事面未记（仅计划复选框在案）——存在被读作收官的漏报风险。这些均不动摇修复正确性，但按本仓「annotation 修改必须有二进制直接证据、禁止猜测性写入」的红线，source 证据行需订正后才算干净落地。

---

## 2. 逐项 verdict 表

| # | 复验项 | verdict | 实测要点 |
|---|---|---|---|
| 1a | vtable 槽数=27 | **CONFIRMED** | 全镜像（0x400000–0x5A0000）原始字节扫描：dword `0x43DE40` 恰 27 处，全部落在 0x56AD20–0x570890 的 27 张表；DataRefsTo 27 址逐一 get_bytes 复核吻合 |
| 1b | 「25×槽3+0x56B898 槽6+双命中表」分解 | **REFUTED**（总数对、分解错） | 实测 **26 表命中在 +0x0C（record 槽3）+ 0x56B898 在 +0x18**（10 槽 MI 复合表，+0x18 在嵌套族表视图下仍是族槽3，角色一致）。「双命中表」物理不存在：全镜像 27 个物理命中一一对应 27 表；IDA 名录复核 0x5705D0/0x5706CC 区间无重叠 stru_ 定义（review_dtor_identity_20261028.md 的「2 处相邻表同址复命中」同被原始字节证伪）。计划文本「25×槽3+槽6+2 相邻表」与 source「双命中表×1」两版本自身也互斥 |
| 1c | 五表前缀同形（slot0/2/4=0x445e70/0x445c60/0x445b90 全同） | **PARTIAL** | 全镜像模式扫描（任意 slot0，条件 slot2/slot4）：恰 **4 表**满足——0x56ACFC、0x56AD20、0x56AEC8、0x56B200（get_bytes 抽验 3+ 表；slot6=0x445D10 亦同）。「五」不可复现（无第 5 表）；同形簇本身成立（n=4，含 UIWnd 本表） |
| 1d | UIWnd 槽3 ≠ 0x43DE40、基体=SceneObj::HideAll@0x445c10 | **CONFIRMED** | UIWnd 构造 `?_UIWnd@UIWnd` @0x445B40：`mov dword ptr [esi], offset stru_56AEC8`（0x445B5D）；stru_56AEC8 槽3=0x445C10（`?HideAll@SceneObj@@QAEXXZ`）≠0x43DE40。「PDB 名」出处已如实标注 ✓。与 review_dtor_identity_20261028.md 独立测得的 UIWnd vtable 逐槽值一致 |
| 1e | 「SceneObj 族 override 簇」（27 类同体 override）vs 单一中间类 | **PARTIAL** | 槽3 角色归属（族虚方法共享实现、UIWnd 本体不 override、override 体内调基体 0x445C10）**成立**；但「27 类同体 override 簇」是源形态推断——二进制不可判定（27 份同体 inline override 经 COMDAT 折叠 vs 1 个中间类继承，产物等价）。反证线索：17 处**直接** call 0x43DE40（dtor/Destroy 直调形）更支持「具名共享体」读法而非纯虚分发。把推断写成定论属过度断言 |
| 2 | fastcall ABI 论证 | **CONFIRMED** | 体 32B：`push esi; mov esi, ecx`（this→ecx）…`pop esi; retn`（bare，栈帧仅 __return_address，无栈参）✓。`void __fastcall(int self)` 首 int 参恰走 ecx、0 栈参⇒bare ret，与体 ABI 等价 ✓；旧签名 `int __thiscall Destroy(int nMode)` 隐含栈参+ret 4 与体矛盾且 MSVC6 禁自由 __thiscall，确需换载体 ✓。调用形：0x43dd20（??1UIListBox）复核 ecx=this、call 前无 push ✓；9 单元编译转绿=端到端零改动实证 ✓ |
| 3 | free_sig_decl 行为 | **CONFIRMED**（注记 1 条） | `tests/test_free_func_sig_decl.py` 6/6 绿；两测文件 15/15；全量 874 passed/355 skipped。4cc×有名/无名 8 组合逐一对照旧代码：语义差 6 处**全部为新增面**（thiscall-named、cdecl-named@decomp 路径、stdcall-named@decomp 路径、fastcall×2、~dtor 名）+ 1 处边缘收紧（数字开头名：旧 supplement 收、新拒）——真实语料 0 命中。真实语料平价：decomp 431 对 **0 差异**；supplement 46 对 **5 新增 0 损**（only_old=0、changed=0）：Destroy__ovl_03 + **IsAnimDone/IsFadeDone/ResetIdle/ResetContainerState 4 个 thiscall 条目**（commit 1 未提此附带新增面——见缺陷 D4） |
| 4 | 实效数字 | **CONFIRMED**（措辞 1 处不准） | probe_census.json：S2 **133/214** ✓；s4_baseline.json：match_L1=**147**、symbols 938→**1141** ✓（HEAD~2 取证 pre=110/938 ✓）；fixed=**9**、new_fail=**0** ✓；9 单元清单=overlay 9 文件=预期 10 减 PropUI ✓（PropUI 残留确为 `UIFrameWnd__deleting_view` C2065 异根因 ✓）。match [metric] 三限定读数在场：l1_bytes=6151 / reloc 覆盖 1692(27.5%) / hidden 1209；rsite mismatch=1@0x4B7310（pre/post 同一 sample ⇒ 旧案 ✓）。**「9 处 C2065 全清」措辞不准**：实测 **14 处** C2065 全清（14→0，跨 14 单元），9 是转绿单元数 |
| 5 | C1003 回归定谳审计 | **CONFIRMED**（证据强于自述） | free_functions.cpp pre=101 / post=101 ✓ 恒定。多重集 diff：GONE=C2065 `Destroy__ovl_03`@L6074（修复本体）；NEW=C2664@**L12385**——**超出旧截断视野（pre max line 12334）** ⇒ 真·隐藏错误暴露（此前按行序推理的疑点系我方输出截断误读 line 为 1238，已全量重测证伪疑点）；NEW 的 (code,msg) 与既有 3 处**全等**（3→4）⇒ 同族性成立（比「PointWorldToScr 等同族」更强：同 msg 全等）；截断进度 12334→12385 前进 ✓（CLAUDE.md C1003 换血条款判据全数满足）⇒ **非真退化成立** |
| 6 | 遗漏检查（欠账如实记录？） | **PARTIAL** | ①overlay 47 条（48 文件含 .gitkeep）中 Destroy__ovl_03 注释块 **10 处/9 文件**（CCBItemWindow×2、CCBParabolaWindow×2）实测全部未回收（T1 Step 5 未做）✓ 欠账客观在案；②但**记录面不全**：计划 Step 5 复选框未勾（计划面在案），**commit 2 message 无「未完」段**（commit 1 有此段）且标题「T1 实效兑现」易被读作 Task 1 收官 ⇒ 叙事面漏报风险；overlay 注释文本「待归属定谳」已过时（定谳已完成）无人更新；③PropUI deleting_view 欠账：commit「留案吻合」+ research_dtor_identity_20261028.md 已定谳 `UIFrameWnd__deleting_view`=0x43D880 纯析构 thunk（名字误导）——身份已研究，但解除动作（补声明/路由）无独立挂账条目 |

---

## 3. 缺陷清单（按 矛盾 > 证据不足 > 遗漏 排序）

### 矛盾（自述与实测不符）

- **D1（中）source 证据行「双命中表」不成立**：`functions.json` 0x0043DE40 source 写「25×槽3+0x56B898 槽6+双命中表」。实测全镜像 27 个物理命中 = 26×record槽3(+0x0C) + 1×0x56B898(+0x18)，**不存在任何表内双命中**（物理字节 + IDA stru_ 名录双重确认，0x5705D0/0x5706CC 无重叠 struct 定义）。0x56B898 是 10 槽 MI 复合表，+0x18 在嵌套族表视图下即族槽3（角色一致，更支持「全员族槽3」结论）。计划文本「25×槽3+槽6+2 相邻表」与 source「双命中表×1」两版本互相矛盾。**修**：source 改「26×槽3 + 0x56B898（10 槽复合表，嵌套族表槽3）」。
- **D2（中）「五表前缀同形」实为四表**：slot0/2/4=0x445e70/0x445c60/0x445b90 全同的表全镜像恰 4 张（0x56ACFC/0x56AD20/0x56AEC8/0x56B200，slot6=0x445D10 亦同），无第 5 张。**修**：source 证据行「五表前缀比对」改「四表」（同形簇结论本身保留）。
- **D3（低）「9 处 C2065 全清」计数口径错**：实测 14 处 C2065（14 单元）全清、9 单元转绿。计划「10 个调用点」亦欠数（实 14 单元含该 C2065）。**修**：叙事改「14 处 C2065 全清 / 9 单元转绿（预期 10 减 PropUI）」。

### 证据不足（推断写成定论）

- **D4（低）「27 类同体 override 簇」为不可判定推断**：27 张表共享槽3 实现 ✓，但「每类各自 override（同体折叠）」与「单一中间类继承」二进制不可判定；17 处直调反而支持「具名共享体」。source 已写「confidence: high」，建议在 source 或 spec 记「源形态未定谳（簇 vs 中间类），仅槽3 角色定谳」。
- **D5（低）4 个 thiscall 附带新增 decl 未入 commit 叙述**：supplement 路径接线顺带把 thiscall 也接入（旧代码该路径无 thiscall 分支）⇒ IsAnimDone/IsFadeDone/ResetIdle/ResetContainerState 4 条新 decl 进 free_functions.h（实测 456→461 decl）。无害（0 损、全量测试绿；ResetIdle 与 CEffQuake 成员同名共存无冲突），但「修 __fastcall 空档+双形兼容」的 commit 摘要未提，属变更面叙述不全。

### 遗漏（欠账/记录缺口）

- **D6（中）T1 Step 5 欠账 commit 面漏报**：10 处 Destroy__ovl_03 overlay 注释块（9 文件）全部未回收（Step 5 未做），计划复选框在案但 commit 2 message 无任何「未完/欠账」段（commit 1 有），标题「T1 实效兑现」存在被读作 Task 1 收官的漏报风险；overlay 注释「待归属定谳」已过时未更新。**修**：状态文档/commit 补记「Step 5 未做（10 处回收）」并把 overlay 注释文本更新为「定谳已完成，待回收」。
- **D7（低）PropUI deleting_view 解除动作无独立挂账**：身份已有定谳（research_dtor_identity_20261028.md），但「补 UIFrameWnd__deleting_view 声明/路由」的解除动作只存在于 dtor-identity 文档语境，未见独立待办条目。

---

## 4. 未复验清单

1. **「管线 loop×4 全绿」逐轮 rc**：工作区 `pipeline/_logs/loop_*.log` 只反映旧轮稳态（match 日志尾为 L1 110→110），commit 内 7 个 baseline 快照与多轮相容但无法严格核「4 轮、每轮全绿」。
2. **「28 测」口径**：复核实测为两测文件 15/15、全量 874 passed；「28 测」的具体选集未核（不影响结论）。
3. **「MSVC6 禁自由 __thiscall」的编译器级实证**：按 MSVC6 文档常识成立（__thiscall 仅限成员函数），但未在本仓 vc6 工具链上做最小反例编译实验。
4. **「单一中间类」替代假说的源级判别**：二进制不可判定（已述）；若需定谳需引入 PDB（PAL3A 参考级）或 MSVC 同体重载/COMDAT 折叠实验，本次未做。
5. **decomp 路径 named/fastcall 双形的真实触发面**：真实语料 0 命中——该路径的双形兼容目前是防御性代码，无实效样本验证。
6. **PropUI deleting_view / Step 5 overlay 回收的后续动作**：均为欠账，本复核只核对记录面，未验解除。

---

## 附：关键实测值速查

- 0x43DE40 体：`push esi; mov esi,ecx; mov ecx,[esi+44h]; test; jz; call gbRefObject::Release; mov [esi+44h],0; mov ecx,esi; call SceneObj::HideAll@0x445c10; pop esi; retn`，32B，栈帧仅 __return_address
- 27 命中槽位：26×(表基+0x0C) + 0x56B898+0x18；全镜像 0x43DE40 dword 计数=27（0x560000–0x580000 外 0 处）
- slot0/2/4(/6)=0x445e70/0x445c60/0x445b90(/0x445d10) 全同表：0x56ACFC、0x56AD20、0x56AEC8(UIWnd)、0x56B200 —— 4 张
- UIWnd vtable=stru_56AEC8=[0x445E70, 0x445CD0, 0x445C60, **0x445C10**, 0x445B90, 0x445B20, 0x445D10]（构造 0x445B5D 直证）
- S2：pre 124/214 → post 133/214；fixed=9：CCBItemWindow/CCBMagicWindow/CCBParabolaWindow/CCBProtectWindow/CCBResultWindow/CCBFiveNimbusWindow/UISceneFrm/UITitle_ArcSave/UIListBox
- L1：110/938 → 147/1141；三限定 l1_bytes=6151、reloc 覆盖 1692(27.5%)、hidden 1209；rsite mismatch=1@0x4B7310（旧案，pre 同）
- free_functions.cpp：101→101，GONE C2065@L6074，NEW C2664@L12385（同 msg 3→4），截断视野 12334→12385
- 新旧分类器平价：8 组合 6 处语义差全为新增面；真实语料 decomp 0 差异 / supp 5 增 0 损（456→461 decl）
- overlay：47 .cpp 条目，Destroy__ovl_03 注释块 10 处/9 文件，0 处已回收
