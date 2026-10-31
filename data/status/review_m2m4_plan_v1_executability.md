# 对抗性复核（可执行性/度量方）：M2-M4 覆盖率爬坡方案 v1

> 2026-10-31 · 评审人：对抗子代理 fed24546（可执行性/度量攻击）· 立场：不信任数字与假设，只信实测。
> 对象：docs/specs/2026-10-31-m2m4-coverage-ramp-plan.md v1 · 判定：**ACCEPT-WITH-FIXES**（F1/F2 = 开工前置 MUST-FIX）
> 13 条发现：2 BLOCKER / 4 HIGH(含 1 MEDIUM-HIGH) / 5 MEDIUM / 2 LOW。全部实测核实（含 pytest 全量实跑）。
> 修复落点见方案 v2 §8 销账表。

## F1 [BLOCKER] 双棘轮锚在两个互斥快照上
probe_census（10-26: 213/124/1116）vs compile_baseline（10-30: 214/135/1110）非同一测量；
13 分止单元实测：12 修复（CCBItemWindow/CCBMagicWindow/CCBParabolaWindow/CCBProtectWindow/
CCBResultWindow/CCBFiveNimbusWindow/Object/UICaption/UISceneFrm/UITitle_ArcSave/CameraCtrl/UIListBox）+
1 回退（SceneVisNode ok→fail 4 err）+ 1 new_unit（CG_Entry）。
修法：归一三读数；13 件归因落账；ratchet 四元组（generated_at+unit-set hash+ok+分母）；
--rebaseline 归因口（仿 link_probe）；--expect-errors 单值化。

## F2 [BLOCKER] M2 对拍链三重断裂 + 素材引用双错
①manual_l1_match.py WINDOW=0x100 vs WinMain size 824（只盖 31%），similarity 非三限定；
②PAL3_manual.map 不在盘 ⇒ 0 符号可对；③过滤器要 '?'+'@' ⇒ _WinMain@16 被漏；
④素材双错：pal3/src 无 WinMain 段（2026-10-27 已搬移）；:26843 实测是 RoleAtt 函数体，WinMain 在 :30668。
修法：对拍改 compare_pal3 三限定单函数模式（mock_link 产物）；素材锚 :30668；验收=判定+三分账。

## F3 [HIGH] 测试口径失实
Windows 实跑 57 failed + 1339 passed + 15 collection errors（非 20+1）；
含真回归（test_global_region_audit: int('external') 崩溃 + 2981==2242 数据漂移）。
断链 2 处（test_audit_callsite_evidence ImportError + _archive ×14）；GBK 默认另炸 3 收集+cli status。
修法：known-fail 三桶清单；门禁=失败集不增；PYTHONUTF8=1；--ignore _archive；真回归挂账 T2。

## F4 [HIGH] T1「28 件快胜」定性不实且与 T3 双计
实测 15 函数+13 数据；零证据快胜仅 16 件（ArraySort/CreateProtectedObj/CCBStageCam ctor+数据 13——
其中 byte_592DA4 等 3 件应归 T3）；12 件需证据（todo_004D0C90 禁猜测红线、_nearby_4b6ca0 身份争端、
gbOBBox::GetBBox+gbLightObj×4=F70 残余与 T3 双计）。
修法：拆 16/12；F70 五件+byte_592DA4 单靶源归属；D4 按 16 件承诺。

## F5 [HIGH] 篡改实验锁不住测量面 + 三口径漂移
单元/文件/函数三口径不一；分母实测已动（213→214）；SceneVisNode 已回退；
WinMain 退役合成条目不减单元数 ⇒ D5 读数入轴无门；与「衰退≠必然回撤」冲突。
修法：四元组锚定；「经归因的单调」+ --rebaseline；篡改用例补分母缩水/rebase 无归因 FAIL。

## F6 [MEDIUM-HIGH] Linux 窗口单点依赖无降级判据
权威读数（census/L1/rsite）只在 Linux 产出；census 已停 5 天。
修法：定义 Windows 可验证面（mock_link/stub_retire/link_probe/compile_regression/pytest）+
降级判据（读数轴冻结、机制轴推进、ratchet 不判决）；D6 冒烟批前置 D4。

## F7 [MEDIUM] T4 top 族未锚定 + C1003 盲区缺位
top 族（文件跨度）C2065 Destroy__ovl_03×14 / C2109×10 / C2059×8 / PointWorldToScr×8；
free_functions+CCBStage 202/1116（18%）=两个 C1003 截断单元，须按最大行号记进展。
修法：§2.4 补 C1003 声明+第三读数；T4 列实测族清单；free_functions 双重身份显式评估。

## F8 [MEDIUM] T2「20 件（8 review_*）」不可复核
pending/ 实测 20 个 review_*.md（33 md + 120+ json），无「20 件」名单定义。
修法：名单落台账（逐件判据+验收）。

## F9 [MEDIUM] M3「零写面」与 retire 子命令矛盾 + 标签双义
修法：retire 语义钉死（v1 只打印计划；实删=人工+闭合回归+git 面确认）；S1-S4 改名。

## F10 [MEDIUM] 工期低估
D5 欠对拍工具改造+WinMain 824B+decl 对齐 ⇒ 拆 1+1 天；D1 未计 227 stub cpp 映射 ⇒ 首版限缩主 stub 面。

## F11 [MEDIUM] T5 台账占位骨架 + 对拍口径分叉
fds_migration_worksheet N=1 全 func_0x 占位；「语义≥95%/字节 100%」与方案三限定口径分叉。
修法：补实名/验收列；统一三限定口径。

## F12 [LOW] 「2833+3435」之 3435 无仓内出处
6268=2833+3435 恰为 5e75ea1e4 提交的「globals 数据 6268 项」——疑数字混用。
修法：可复算计数（stub_gen --count）或删。

## F13 [LOW] rsite 95/0 是预测非现值（现值 92/3）
修法：标注预测 vs 现值；D6 若仍 92/3 判「门未生效」。

## 总判定
ACCEPT-WITH-FIXES。骨架/红线/盲区自声明成立；F1/F2 为开工前置 MUST-FIX；
D4 快胜预期量按 16 件修正后再承诺。
