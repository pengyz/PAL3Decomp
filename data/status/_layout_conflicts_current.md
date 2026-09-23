# 布局冲突榜单（2026-09-24 goal r14 全量重测后）

冲突类 20 / 712 · 冲突成员 465 · 会话累计：81 → 20 类

## 剩余清单（按冲突数）
- PAL3: 87/87
- CCBRoleState: 86/86
- SceneObj: 50/50
- CCBCamControl: 47/47
- CG_Scene: 31/38
- GRPinput: 27/40
- CUtil: 24/24
- ARC_PlayerAtt: 23/27
- CEffectSystem: 14/14
- ArcLocale: 13/20
- CEffect: 13/13
- DIDEVICEOBJECTINSTANCEA: 9/15
- CTaskTpl: 8/8
- TaskMgr: 8/9
- ARC_PlayerMgrInfo: 7/11
- CEffMgr: 7/48
- DIDEVICEINSTANCEA: 4/9
- Param1: 4/5
- CTrail: 2/13
- SceneMgr: 1/167

## 家族归类（已知病灶）

- PAL3(87,+8) 全局单例：独立专查
- CCBRoleState(86)/SceneObj(50)：复用槽批——前置=ReleaseObject 矛盾的 provenance 扫描（r9 发现反证）
- CCBCamControl(47,+4)/GRPinput(27,+4)：vptr/基类尺寸族
- CG_Scene(31,+1028)/CUtil(24)/ARC_PlayerAtt(23)：整类重建队列
- CEffectSystem(14,+8)/CEffect(13,+8200)：尺寸/重建
- DIDEVICEOBJECTINSTANCEA(9/15)/DIDEVICEINSTANCEA(4/9)：SDK 头尺寸
- CTaskTpl(8/8)：通用模板死头（全被特化 typedef 覆盖）⇒ 无布局影响，建议豁免
- TaskMgr(8/9)/ARC_PlayerMgrInfo(7/11)/CEffMgr(7/48)/Param1(4/5)：待诊
