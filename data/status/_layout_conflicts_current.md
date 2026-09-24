# 布局冲突榜单（2026-09-25 goal r46 全量重测）

冲突类 13 / 712 · 冲突成员 196 · 会话累计 81 → 13

## 豁免（不计入真实目标）

- DIDEVICEOBJECTINSTANCEA/DIDEVICEINSTANCEA：SDK 类型（dinput.h 定义，audit 探针 include 集不同 ⇒ 测量伪影）
- CTaskTpl/TaskMgr：通用模板（offsetof 无法作用于未实例化模板 ⇒ 测量限制）
- SceneMgr 1/167：审计噪声（内联 union 误计，直接探测已证布局正确）
- CTrail 2/13：无编译单元（零管线影响）

## 真实剩余（按冲突数）

- PAL3: 87/87
- CUtil: 24/24
- CEffectSystem: 16/16
- ArcLocale: 13/20
- CEffect: 13/13
- DIDEVICEOBJECTINSTANCEA: 9/15 [豁免]
- CTaskTpl: 8/8 [豁免]
- TaskMgr: 8/8 [豁免]
- CEffMgr: 7/48
- DIDEVICEINSTANCEA: 4/9 [豁免]
- Param1: 4/5
- CTrail: 2/13 [豁免]
- SceneMgr: 1/167 [豁免]

## 真实可行动（有编译单元 + 非豁免）

- PAL3: 87/87
- CUtil: 24/24
- CEffectSystem: 16/16
- ArcLocale: 13/20
- CEffect: 13/13
- CEffMgr: 7/48
- Param1: 4/5
