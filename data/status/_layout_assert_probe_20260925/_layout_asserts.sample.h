/* _layout_asserts.h —— 数据布局的编译期校验（由 tools/layout_assert_gen.py 生成，请勿手改）
 * 生成口径: untrusted-policy=comment
 * 统计: total=190 active=5 commented=185 omitted=0 skipped=0
 *   trusted=5 same-source=1 suspect=184 consistency-only=0
 * 注记: --structs data/annotations/structs --only CCBUI,CEffSParticle,MUIDialog,Role,SceneObj,UIEmote
 */
/* ============================ 错误处理表 ============================
 * 编译失败时按以下分支归因，**不要**跳过分支直接改注解：
 *
 *  branch 1  断言失败 ∧ 常量可信（A 形态 ∧ 独立于 annotation ∧ 无疑似误归属）
 *            ⇒ 真布局错误：修 annotation / 类型 / 成员偏移（本仓四道门流程）。
 *  branch 2  断言失败 ∧ **常量本身可疑**（行首 [SUSPECT]：形态非 A，或已疑误归属 E-1）
 *            ⇒ 常量（或其归属）错，**不得**改动正确注解 —— w1/w2.cpp 实测：被污染的
 *              A 级常量会把正确注解判死（C2118），工程师唯一"合规"出路是把注解改坏 ⇒
 *              全下游成员位移连环错。正确动作：重取**独立**的 IDA 二进制证据
 *              （reg+disp32 / 绝对地址），再解除注释。
 *              同理，[SAME-SOURCE] 行（A 形态但同源，E-2）编译通过**不代表**布局正确：
 *              它与注解出自同一次读数，零判别力。
 *  branch 3  C2057 'expected constant expression' / C2466（offsetof 于虚基区域）
 *            ⇒ 生成器本应跳过该类成员（E-3：p3.cpp:28 与 off.cpp:18 实测虚基成员、
 *              虚基的非虚基之成员都不是常量表达式）⇒ 报生成器缺陷，不要手删断言了事。
 *              注：虚基区域走**整个继承闭包**（R=1 C-1：`VB2 : virtual V1; IVB : VB2`
 *              的 `offsetof(IVB, vv)` 实测 C2057+C2466，只看直接虚基会漏）。
 *  branch 4  生效行带 [CONSISTENCY-ONLY] 断言失败（`--untrusted-policy consistency-only`）
 *            ⇒ 常量与注解同源，失败意味着 **codegen 发射的声明与注解常量漂移**
 *              （stage 变换 / F59 static 化 / 多继承内嵌建模），不是布局真值错误：
 *              先查 stage，再决定改注解还是改 stage；该档**不得**当作布局真值证据（E-2）。
 *
 * 另：本文件必须在**全部类声明之后**包含（sizeof/offsetof 需要完整类型）；
 *     若报 C2027 'use of undefined type' ⇒ include 位置不对，不是布局错误。
 * MSVC6 无编译期静态断言关键字 ⇒ 全部断言用负数组技巧（false ⇒ 负下标 ⇒ C2118）。
 * ==================================================================== */

#ifndef PAL3_LAYOUT_ASSERTS_H
#define PAL3_LAYOUT_ASSERTS_H

#include <stddef.h>   /* offsetof */

/* ===== CCBUI ===== bases: UIFrameWnd | pmf(CCBUI) = 4 | 单继承链且 vfptr 载体 UIWnd 无直接基（vfptr 在偏移 0）⇒ 4 */
// [SUSPECT] typedef char _a_CCBUI_m_pAttackSequenBack[(offsetof(CCBUI, m_pAttackSequenBack) == 72) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_pPanel[(offsetof(CCBUI, pPanel) == 76) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pBattleFieldAttr[(offsetof(CCBUI, m_pBattleFieldAttr) == 80) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pAttackSequenFace[(offsetof(CCBUI, m_pAttackSequenFace) == 104) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStatePanel[(offsetof(CCBUI, m_pRoleStatePanel) == 148) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateFace[(offsetof(CCBUI, m_pRoleStateFace) == 164) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateFaceName[(offsetof(CCBUI, m_pRoleStateFaceName) == 184) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateAttackInc[(offsetof(CCBUI, m_pRoleStateAttackInc) == 204) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateAttackDec[(offsetof(CCBUI, m_pRoleStateAttackDec) == 248) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateDefenceInc[(offsetof(CCBUI, m_pRoleStateDefenceInc) == 292) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateDefenceDec[(offsetof(CCBUI, m_pRoleStateDefenceDec) == 336) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateLuckInc[(offsetof(CCBUI, m_pRoleStateLuckInc) == 380) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateLuckDec[(offsetof(CCBUI, m_pRoleStateLuckDec) == 424) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateSpeedInc[(offsetof(CCBUI, m_pRoleStateSpeedInc) == 468) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateSpeedDec[(offsetof(CCBUI, m_pRoleStateSpeedDec) == 512) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateStable[(offsetof(CCBUI, m_pRoleStateStable) == 556) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateBlank[(offsetof(CCBUI, m_pRoleStateBlank) == 600) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateForbid[(offsetof(CCBUI, m_pRoleStateForbid) == 644) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateSleep[(offsetof(CCBUI, m_pRoleStateSleep) == 688) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateChaos[(offsetof(CCBUI, m_pRoleStateChaos) == 732) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateMad[(offsetof(CCBUI, m_pRoleStateMad) == 776) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateMirror[(offsetof(CCBUI, m_pRoleStateMirror) == 820) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateWall[(offsetof(CCBUI, m_pRoleStateWall) == 864) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateBound[(offsetof(CCBUI, m_pRoleStateBound) == 908) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateHermit[(offsetof(CCBUI, m_pRoleStateHermit) == 952) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateImmunity[(offsetof(CCBUI, m_pRoleStateImmunity) == 996) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pWinPanel[(offsetof(CCBUI, m_pWinPanel) == 1040) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pLosePanel[(offsetof(CCBUI, m_pLosePanel) == 1044) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateHP[(offsetof(CCBUI, m_pRoleStateHP) == 1048) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateGP[(offsetof(CCBUI, m_pRoleStateGP) == 1064) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateMP[(offsetof(CCBUI, m_pRoleStateMP) == 1080) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pRoleStateSword[(offsetof(CCBUI, m_pRoleStateSword) == 1096) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pTrickName[(offsetof(CCBUI, m_pTrickName) == 1100) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pTrickName2[(offsetof(CCBUI, m_pTrickName2) == 1104) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pDialogBack[(offsetof(CCBUI, m_pDialogBack) == 1108) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pResultLevelup[(offsetof(CCBUI, m_pResultLevelup) == 1112) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pResultWindLvup[(offsetof(CCBUI, m_pResultWindLvup) == 1116) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pResultThunderLvup[(offsetof(CCBUI, m_pResultThunderLvup) == 1120) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pResultWaterLvup[(offsetof(CCBUI, m_pResultWaterLvup) == 1124) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pResultFireLvup[(offsetof(CCBUI, m_pResultFireLvup) == 1128) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pResultEarthLvup[(offsetof(CCBUI, m_pResultEarthLvup) == 1132) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pResultDoubleLvup[(offsetof(CCBUI, m_pResultDoubleLvup) == 1136) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pResultGetItem[(offsetof(CCBUI, m_pResultGetItem) == 1140) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pMain[(offsetof(CCBUI, m_pMain) == 1144) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pItemWindow[(offsetof(CCBUI, m_pItemWindow) == 1148) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pParabolaWindow[(offsetof(CCBUI, m_pParabolaWindow) == 1152) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pMagicWindow[(offsetof(CCBUI, m_pMagicWindow) == 1156) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pSkillWindow[(offsetof(CCBUI, m_pSkillWindow) == 1160) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pAIWindow[(offsetof(CCBUI, m_pAIWindow) == 1164) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pLineupWindow[(offsetof(CCBUI, m_pLineupWindow) == 1168) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pProtectWindow[(offsetof(CCBUI, m_pProtectWindow) == 1172) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pResultWindow[(offsetof(CCBUI, m_pResultWindow) == 1176) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pFiveNimbusWindow[(offsetof(CCBUI, m_pFiveNimbusWindow) == 1192) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pCBSystem[(offsetof(CCBUI, m_pCBSystem) == 1196) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_pUtil[(offsetof(CCBUI, m_pUtil) == 1200) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_m_Task[(offsetof(CCBUI, m_Task) == 1208) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CCBUI_fp[(offsetof(CCBUI, fp) == 2608) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
typedef char _a_CCBUI_pmf[(sizeof(void (CCBUI::*)()) == 4) ? 1 : -1]; /* shape | trusted | MSVC6 SP0 实测矩阵 E-4：虚基⇒12 / 多继承分支⇒8 / 单继承⇒4（data/status/_layout_assert_probe_20260925） */
// [SUSPECT] typedef char _a_CCBUI_size[(sizeof(CCBUI) == 2648) ? 1 : -1]; /* size | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */

/* ===== CEffSParticle ===== bases: CEffObj, CTaskTpl_tagEffTaskParam_CEffSParticle | pmf(CEffSParticle) = 8 | 继承闭包内有多继承分支 ⇒ 8（★ 单直接基但基类是多继承类时也是 8） */
// [SUSPECT] typedef char _a_CEffSParticle_m_pEffect[(offsetof(CEffSParticle, m_pEffect) == 48) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CEffSParticle_m_vecPos[(offsetof(CEffSParticle, m_vecPos) == 52) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CEffSParticle_m_fX[(offsetof(CEffSParticle, m_fX) == 64) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CEffSParticle_m_fY[(offsetof(CEffSParticle, m_fY) == 68) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CEffSParticle_m_fZ[(offsetof(CEffSParticle, m_fZ) == 72) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CEffSParticle_m_fPX[(offsetof(CEffSParticle, m_fPX) == 76) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CEffSParticle_m_fPY[(offsetof(CEffSParticle, m_fPY) == 80) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CEffSParticle_m_fPZ[(offsetof(CEffSParticle, m_fPZ) == 84) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CEffSParticle_m_fRotX[(offsetof(CEffSParticle, m_fRotX) == 88) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CEffSParticle_m_fRotY[(offsetof(CEffSParticle, m_fRotY) == 92) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_CEffSParticle_m_fRotZ[(offsetof(CEffSParticle, m_fRotZ) == 96) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
typedef char _a_CEffSParticle_pmf[(sizeof(void (CEffSParticle::*)()) == 8) ? 1 : -1]; /* shape | trusted | MSVC6 SP0 实测矩阵 E-4：虚基⇒12 / 多继承分支⇒8 / 单继承⇒4（data/status/_layout_assert_probe_20260925） */
// [SUSPECT] typedef char _a_CEffSParticle_size[(sizeof(CEffSParticle) == 100) ? 1 : -1]; /* size | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */

/* ===== MUIDialog ===== bases: UIDialog, MUIDialogMgr, UIFrameWnd | pmf(MUIDialog) = 8 | 继承闭包内有多继承分支 ⇒ 8（★ 单直接基但基类是多继承类时也是 8） */
// [SUSPECT] typedef char _a_MUIDialog_ptr_Dlg[(offsetof(MUIDialog, ptr_Dlg) == 72) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_MUIDialog_m_DlgId[(offsetof(MUIDialog, m_DlgId) == 76) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_MUIDialog_m_rect[(offsetof(MUIDialog, m_rect) == 80) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_MUIDialog_m_textRc[(offsetof(MUIDialog, m_textRc) == 96) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_MUIDialog_m_bk[(offsetof(MUIDialog, m_bk) == 112) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_MUIDialog_m_static[(offsetof(MUIDialog, m_static) == 304) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_MUIDialog_m_text[(offsetof(MUIDialog, m_text) == 464) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_MUIDialog_m_btnW[(offsetof(MUIDialog, m_btnW) == 624) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_MUIDialog_m_btnH[(offsetof(MUIDialog, m_btnH) == 628) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_MUIDialog_m_btRc[(offsetof(MUIDialog, m_btRc) == 632) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_MUIDialog_pCallbackVtable2[(offsetof(MUIDialog, pCallbackVtable2) == 976) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
typedef char _a_MUIDialog_pmf[(sizeof(void (MUIDialog::*)()) == 8) ? 1 : -1]; /* shape | trusted | MSVC6 SP0 实测矩阵 E-4：虚基⇒12 / 多继承分支⇒8 / 单继承⇒4（data/status/_layout_assert_probe_20260925） */
// [SUSPECT] typedef char _a_MUIDialog_size[(sizeof(MUIDialog) == 1288) ? 1 : -1]; /* size | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */

/* ===== Role ===== bases: Object, PalScriptWaitObj, GlowObj | pmf(Role) = 8 | 继承闭包内有多继承分支 ⇒ 8（★ 单直接基但基类是多继承类时也是 8） */
// [SUSPECT] typedef char _a_Role_m_cmdqueue[(offsetof(Role, m_cmdqueue) == 96) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_bInView[(offsetof(Role, m_bInView) == 144) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_groundpos[(offsetof(Role, m_groundpos) == 148) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_renderpos[(offsetof(Role, m_renderpos) == 160) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_npcinfo[(offsetof(Role, m_npcinfo) == 172) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_onlayer[(offsetof(Role, m_onlayer) == 628) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_active[(offsetof(Role, m_active) == 632) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_bCGMonster[(offsetof(Role, bCGMonster) == 636) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_nCGMonsterID[(offsetof(Role, nCGMonsterID) == 640) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_nCGMonsterType[(offsetof(Role, nCGMonsterType) == 644) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_bRelive[(offsetof(Role, bRelive) == 648) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_bInvincible[(offsetof(Role, bInvincible) == 649) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_fRattrapWait[(offsetof(Role, fRattrapWait) == 652) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_fMirrorWait[(offsetof(Role, fMirrorWait) == 656) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_bMirror[(offsetof(Role, bMirror) == 660) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_fCGBIXIE[(offsetof(Role, fCGBIXIE) == 664) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_bCGBIXIE[(offsetof(Role, bCGBIXIE) == 668) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_bCrossAlpha[(offsetof(Role, bCrossAlpha) == 669) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_fCrossAlpha[(offsetof(Role, fCrossAlpha) == 672) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_bCGMonsterHitObj[(offsetof(Role, bCGMonsterHitObj) == 676) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_bStill[(offsetof(Role, bStill) == 677) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_pCG_SceneProp[(offsetof(Role, pCG_SceneProp) == 680) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_actor[(offsetof(Role, m_actor) == 684) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_talkoldact[(offsetof(Role, m_talkoldact) == 1504) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_talkoldface[(offsetof(Role, m_talkoldface) == 1508) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_talkobj[(offsetof(Role, m_talkobj) == 1512) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_mstate[(offsetof(Role, m_mstate) == 1516) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_matt[(offsetof(Role, m_matt) == 1520) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_mfreedist[(offsetof(Role, m_mfreedist) == 1524) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_mattackrange[(offsetof(Role, m_mattackrange) == 1528) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_mfindradius[(offsetof(Role, m_mfindradius) == 1532) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_statetime[(offsetof(Role, m_statetime) == 1536) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_weapon[(offsetof(Role, m_weapon) == 1540) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_bLeftWeapon[(offsetof(Role, m_bLeftWeapon) == 1544) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_bRightWeapon[(offsetof(Role, m_bRightWeapon) == 1545) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_nRad[(offsetof(Role, m_nRad) == 1548) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_nRealHeadPos[(offsetof(Role, m_nRealHeadPos) == 1552) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_nOverlapState[(offsetof(Role, m_nOverlapState) == 1556) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_tpos[(offsetof(Role, m_tpos) == 1560) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_vTagHeadPos[(offsetof(Role, m_vTagHeadPos) == 1568) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_overlap[(offsetof(Role, m_overlap) == 1580) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_bPathMove[(offsetof(Role, m_bPathMove) == 1584) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_pathMoveCounter[(offsetof(Role, m_pathMoveCounter) == 1588) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_lastpos[(offsetof(Role, m_lastpos) == 1592) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_notePos[(offsetof(Role, m_notePos) == 1604) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_path_region[(offsetof(Role, m_path_region) == 1616) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_Role_m_wanapos[(offsetof(Role, m_wanapos) == 8692) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
typedef char _a_Role_pmf[(sizeof(void (Role::*)()) == 8) ? 1 : -1]; /* shape | trusted | MSVC6 SP0 实测矩阵 E-4：虚基⇒12 / 多继承分支⇒8 / 单继承⇒4（data/status/_layout_assert_probe_20260925） */
// [SUSPECT] typedef char _a_Role_size[(sizeof(Role) == 8704) ? 1 : -1]; /* size | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */

/* ===== SceneObj ===== bases: PalScriptWaitObj, GlowObj, TaskMgr_SceneObjParam_SceneObj | pmf(SceneObj) = 8 | 继承闭包内有多继承分支 ⇒ 8（★ 单直接基但基类是多继承类时也是 8） */
// [SAME-SOURCE] typedef char _a_SceneObj_m_fTimerLimit[(offsetof(SceneObj, m_fTimerLimit) == 68) ? 1 : -1]; /* offset | same-source | 同源常量: 证据与 annotation 同源 ⇒ 零判别力（E-2：错误注解也会编译通过） */
// [SUSPECT] typedef char _a_SceneObj__SaveTaskInfo[(offsetof(SceneObj, _SaveTaskInfo) == 76) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_fTime[(offsetof(SceneObj, m_fTime) == 88) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_fDeltaTime[(offsetof(SceneObj, m_fDeltaTime) == 92) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_fTimeScale[(offsetof(SceneObj, m_fTimeScale) == 96) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_deltatime[(offsetof(SceneObj, m_deltatime) == 100) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_bLockPropUI[(offsetof(SceneObj, m_bLockPropUI) == 104) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_bLockCamera[(offsetof(SceneObj, m_bLockCamera) == 108) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_bProcessLinkObj[(offsetof(SceneObj, m_bProcessLinkObj) == 112) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_bCallProcessGroupObj[(offsetof(SceneObj, m_bCallProcessGroupObj) == 116) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_bMainGroupObj[(offsetof(SceneObj, m_bMainGroupObj) == 120) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_dwEffGroupRunningID[(offsetof(SceneObj, dwEffGroupRunningID) == 124) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_bCGObj[(offsetof(SceneObj, bCGObj) == 128) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_sCGSHELF[(offsetof(SceneObj, sCGSHELF) == 129) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_rCGSelfArea[(offsetof(SceneObj, rCGSelfArea) == 196) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_rTouchAreaCG[(offsetof(SceneObj, rTouchAreaCG) == 212) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_fLastTime[(offsetof(SceneObj, fLastTime) == 228) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_mParam[(offsetof(SceneObj, mParam) == 232) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_mVelocity[(offsetof(SceneObj, mVelocity) == 304) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_mTime[(offsetof(SceneObj, mTime) == 316) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_mStorePos[(offsetof(SceneObj, mStorePos) == 320) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_mRetrorse[(offsetof(SceneObj, mRetrorse) == 332) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_mTouchCounter[(offsetof(SceneObj, mTouchCounter) == 336) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_iState[(offsetof(SceneObj, m_iState) == 340) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_bCVDOver[(offsetof(SceneObj, m_bCVDOver) == 344) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_mOBBox[(offsetof(SceneObj, mOBBox) == 348) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_pObjMsgBuffer[(offsetof(SceneObj, m_pObjMsgBuffer) == 424) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_pObjMsgBuffer2[(offsetof(SceneObj, m_pObjMsgBuffer2) == 680) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_renderpos[(offsetof(SceneObj, m_renderpos) == 936) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_subobj[(offsetof(SceneObj, m_subobj) == 948) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_mdl[(offsetof(SceneObj, m_mdl) == 984) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_info[(offsetof(SceneObj, m_info) == 1068) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_path[(offsetof(SceneObj, m_path) == 1672) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_pmap[(offsetof(SceneObj, m_pmap) == 1676) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_mapindex[(offsetof(SceneObj, m_mapindex) == 1680) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_pushboxdir[(offsetof(SceneObj, m_pushboxdir) == 1684) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_maprect[(offsetof(SceneObj, m_maprect) == 1688) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_liftrole[(offsetof(SceneObj, m_liftrole) == 1704) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_common[(offsetof(SceneObj, m_common) == 1708) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_snd[(offsetof(SceneObj, m_snd) == 1756) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_radius[(offsetof(SceneObj, m_radius) == 1760) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_runscript[(offsetof(SceneObj, m_runscript) == 1764) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_fRotateX[(offsetof(SceneObj, m_fRotateX) == 1768) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_fRotateY[(offsetof(SceneObj, m_fRotateY) == 1772) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_fRotateZ[(offsetof(SceneObj, m_fRotateZ) == 1776) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_SceneObj_m_fParam[(offsetof(SceneObj, m_fParam) == 1780) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
typedef char _a_SceneObj_pmf[(sizeof(void (SceneObj::*)()) == 8) ? 1 : -1]; /* shape | trusted | MSVC6 SP0 实测矩阵 E-4：虚基⇒12 / 多继承分支⇒8 / 单继承⇒4（data/status/_layout_assert_probe_20260925） */
// [SUSPECT] typedef char _a_SceneObj_size[(sizeof(SceneObj) == 1784) ? 1 : -1]; /* size | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */

/* ===== UIEmote ===== bases: UIWnd, PalScriptWaitObj | pmf(UIEmote) = 8 | 继承闭包内有多继承分支 ⇒ 8（★ 单直接基但基类是多继承类时也是 8） */
// [SUSPECT] typedef char _a_UIEmote_baseclass2[(offsetof(UIEmote, baseclass2) == 68) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_UIEmote_m_cur[(offsetof(UIEmote, m_cur) == 76) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_UIEmote_m_ani[(offsetof(UIEmote, m_ani) == 80) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_UIEmote_m_role[(offsetof(UIEmote, m_role) == 2212) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 B（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_UIEmote_m_loopcount[(offsetof(UIEmote, m_loopcount) == 2216) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 B（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_UIEmote_m_nLoop[(offsetof(UIEmote, m_nLoop) == 2220) ? 1 : -1]; /* offset | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */
// [SUSPECT] typedef char _a_UIEmote_pmf[(sizeof(void (UIEmote::*)()) == 8) ? 1 : -1]; /* shape | suspect | 该类把多继承建模成内嵌基类成员（baseclass2 (offset=68)）⇒ 声明的继承形状 ≠ 注解形状 ⇒ PMF 断言不可证 */
// [SUSPECT] typedef char _a_UIEmote_size[(sizeof(UIEmote) == 2272) ? 1 : -1]; /* size | suspect | 常量可疑: 证据形态等级 C（非 reg+disp32/绝对地址） */

#endif /* PAL3_LAYOUT_ASSERTS_H */
