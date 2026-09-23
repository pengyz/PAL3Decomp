# 布局冲突榜单（2026-09-25 goal r32 全量重测）

冲突类 15 / 712 · 冲突成员 268 · 会话累计 81 → 15 类

## 剩余清单

- PAL3: 87/87
- CCBCamControl: 47/47
- GRPinput: 27/40
- CUtil: 24/24
- CEffectSystem: 14/14
- ArcLocale: 13/20
- CEffect: 13/13
- DIDEVICEOBJECTINSTANCEA: 9/15
- CTaskTpl: 8/8
- TaskMgr: 8/9
- CEffMgr: 7/48
- DIDEVICEINSTANCEA: 4/9
- Param1: 4/5
- CTrail: 2/13
- SceneMgr: 1/167

## 豁免/噪声（不计入）

- SceneMgr 1/167：审计噪声（内联 union 成员误计），直接探测已证布局正确 ✓
- CTaskTpl 8/8：通用模板死头（全被特化 typedef 覆盖，无实例化）⇒ 无布局影响

## 已知病灶族

- PAL3(87,+8) 全局单例：独立专查
- CCBCamControl(47,+4)/GRPinput(27,+4)/CUtil(24,+4)：vptr 接缝族（同 SceneObj 模式：首基 vfptr 槽）
- CEffectSystem(14,+8)/CEffect(13,+8200)：竞技场/欠模型族（operator new 0x10C0 铁证）
- ArcLocale(13/20)：待诊
- DIDEVICEOBJECTINSTANCEA/DIDEVICEINSTANCEA：dinput.h SDK 头尺寸（Windows SDK 权威）
- TaskMgr(8/9)/Param1(4/5)/CEffMgr(7/48)/CTrail(2/13)：小漂移待诊

## 方法论（已制度化）
- 唯一 SoT：vtable 存储反查 + 调用约定 + stride 铁证；调用点强转类型/邻居/PDB 名 ✗
- 全局语义改动必须过 L1 棘轮；落地单位 = 类型 + 内嵌级联闭包
- audit 一致 ≠ 布局正确（注解⇄编译头可自洽地一致错）⇒ ctor 逐指令为最终裁判
