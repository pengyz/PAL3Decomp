# 全量布局审计（2026-09-22）—— 冲突清单与修复计划
命令：`python3 tools/audit_type_layout.py --limit 712 --json`（编译器裁判：`offsetof(Cls,m) == 注解偏移`）

## 总览
| 结果 | 类数 |
|---|---|
| ✓ 一致 | 355 |
| **✗ 冲突** | **91** |
| 测量不可信（需查）| 22 |

## 冲突形态

| 形态 | 类数 | 可能成因 |
|---|---|---|
| 10–50% | 32 | 局部成员尺寸/类型错 |
| >50% | 26 | 部分成员的尺寸/类型错，或中间某成员把布局带偏 |
| 全部成员（疑 vptr/虚函数） | 26 | 类被注入/声明了虚函数 ⇒ 多出 vptr ⇒ 全员 +4（见 P1 闸门） |
| <10% | 7 | 个别成员尺寸/类型错 |

## 冲突清单（按冲突数降序；`vt` = 注解/IDB 是否多态）

| 类 | 冲突/成员 | vt | 基类 |
|---|---|---|---|
| `PalScriptMgr` | 269/269 | ✓ | — |
| `PAL3` | 87/87 | — | — |
| `CCBRoleState` | 86/86 | — | SceneObj |
| `CCBUIPanel` | 72/72 | ✓ | UIListBox |
| `SaleUI` | 72/80 | ✓ | UIFrameWnd |
| `SwordUI` | 72/182 | — | UIFrameWnd |
| `CameraCtrl` | 67/112 | ✓ | — |
| `Role` | 54/54 | ✓ | Object,PalScriptWaitObj,GlowObj |
| `SceneObj` | 50/50 | ✓ | PalScriptWaitObj,GlowObj,TaskMgr_SceneObjParam_SceneObj |
| `CCBCamControl` | 47/47 | — | — |
| `CEffCylinder` | 35/35 | ✓ | CEffObj,CTaskTpl_tagEffTaskParam_CEffCylinder |
| `CEffMeteor` | 35/35 | ✓ | CEffObj,CTaskTpl_tagEffTaskParam_CEffMeteor |
| `EquipUI` | 34/111 | ✓ | UIFrameWnd |
| `CEffGrid` | 32/32 | ✓ | CEffObj,CTaskTpl_tagEffTaskParam_CEffGrid |
| `CG_Scene` | 32/39 | — | — |
| `JusticeBookUI` | 32/75 | ✓ | UIFrameWnd |
| `CCBStageRole` | 28/111 | — | — |
| `MainPropUI` | 28/114 | ✓ | UIFrameWnd |
| `CParticleSystem` | 27/32 | — | — |
| `GRPinput` | 27/40 | — | — |
| `RoleCamera` | 27/42 | — | gbCamera |
| `CG_UI` | 25/96 | — | UIFrameWnd |
| `CUtil` | 24/24 | ✓ | — |
| `PropUI` | 24/143 | ✓ | UIFrameWnd |
| `ARC_PlayerAtt` | 23/27 | — | ARC_RoleAtt |
| `Comp_DonateUI` | 21/42 | — | UIFrameWnd |
| `MagicUI` | 18/92 | — | UIFrameWnd |
| `CEffect` | 14/14 | ✓ | — |
| `CEffectSystem` | 14/14 | ✓ | — |
| `SoundMgr` | 14/18 | — | — |
| `ArcLocale` | 13/20 | — | — |
| `PalScript` | 13/87 | ✓ | — |
| `UIPushButton` | 12/18 | ✓ | UIWnd |
| `CCBStageCam` | 11/11 | — | RoleCamera |
| `CEffModel` | 11/11 | ✓ | CEffObj,CTaskTpl_tagEffTaskParam_CEffModel |
| `CEffSParticle` | 11/11 | ✓ | CEffObj,CTaskTpl_tagEffTaskParam_CEffSParticle |
| `FontPrintInfo` | 11/12 | — | — |
| `DealUI` | 10/26 | — | UIFrameWnd |
| `DIDEVICEOBJECTINSTANCEA` | 9/15 | — | — |
| `FontPrint3DInfo` | 9/10 | — | — |
| `CEffgbParticle` | 8/8 | ✓ | CEffObj,CTaskTpl_tagEffTaskParam_CEffgbParticle |
| `CTaskTpl` | 8/9 | — | — |
| `ARC_PlayerMgrInfo` | 7/11 | — | — |
| `CEffMgr` | 7/48 | — | — |
| `RoleShadow` | 7/13 | — | — |
| `Scene` | 7/21 | — | — |
| `ARC_Inventory` | 5/6 | — | — |
| `Archive` | 5/6 | — | — |
| `CCBControl` | 5/18 | — | — |
| `Inventory` | 5/6 | — | — |
| `LineupUI` | 5/92 | ✓ | UIFrameWnd |
| `MXTransport` | 5/11 | — | MeshFx |
| `MainEquipUI` | 5/116 | ✓ | UIFrameWnd |
| `RoleTaskPool` | 5/6 | — | — |
| `CEffTrackCustomShape` | 4/4 | — | CEffCustomShape,CEffObj |
| `CEffTrackCylinder` | 4/4 | — | CEffCylinder,CEffObj |
| `CEffTrackGrid` | 4/4 | — | CEffGrid,CEffObj |
| `CEffTrackModel` | 4/4 | — | CEffModel,CEffObj |
| `UIStaticFlex` | 4/9 | — | UIWnd |
| `UIRoleDialog` | 4/5 | ✓ | UIDialog,PalScriptWaitObj |
| `CUSTOMSHAPEVERTEX` | 4/5 | — | — |
| `ChoseCompose` | 4/15 | — | UIFrameWnd,PalScriptWaitObj |
| `DIDEVICEINSTANCEA` | 4/9 | — | — |
| `HeadMsg` | 4/8 | — | — |
| `ParticleEffect` | 4/4 | — | sg_particle_scene |
| `Param1` | 4/5 | — | — |
| `ArcMsic` | 3/10 | — | — |
| `ArcScene` | 3/5 | — | — |
| `UITextArea` | 3/4 | ✓ | UIWnd |
| `UITabBtn` | 3/4 | — | — |
| `ProtectPanel` | 3/6 | — | UIFrameWnd |
| `PurgeEffect` | 3/8 | — | — |
| `tagCmdData` | 2/9 | — | — |
| `CCBStageShadow` | 2/7 | — | — |
| `CCBSystem` | 2/46 | — | — |
| `UISceneMap` | 2/6 | ✓ | UIWnd |
| `CTrail` | 2/13 | — | — |
| `LayerNode` | 2/5 | — | — |
| `MXSavePoint` | 2/7 | — | MeshFx |
| `ARC_Reoccupy` | 1/2 | — | — |
| `CEffAction` | 1/1 | ✓ | CEffObj,CTaskTpl_tagEffTaskParam_CEffAction |
| `CEffCustomShape` | 1/24 | — | CEffObj,CTaskTpl_tagEffTaskParam_CEffCustomShape |
| `CEffQuake` | 1/1 | ✓ | CEffObj,CTaskTpl_tagEffTaskParam_CEffQuake |
| `CEffTrackSParticle` | 1/1 | — | CEffSParticle,CEffObj |
| `CScreenMode` | 1/106 | ✓ | — |
| `UIListBox` | 1/26 | ✓ | UIWnd |
| `UIRoleSelect` | 1/4 | — | UIDialog,PalScriptWaitObj |
| `EffectItem` | 1/5 | — | — |
| `Reoccupy` | 1/2 | — | — |
| `SceneMgr` | 1/167 | — | — |
| `ScriptObj` | 1/1 | ✓ | — |

## 修复顺序（DAG 序：基础类型先）
1. **先清「按值内嵌」的基础类型**（其尺寸错会沿 DAG 传播；实测 `UIWnd`→`RoleSystem`→`SceneMgr` 的 −16/−40 链）
2. 再修**多态但注解未计入 vptr** 的类（形态"全部成员"）：先跑 `tools/audit_attribution_evidence.py` 确认多态 ✓
3. 最后修**局部成员尺寸/类型**错（形态 <10% / 10–50%）
4. 每类一批，过**四道门**（见 `annotation-audit` skill）✓

## 22 个「测量不可信」类（工具限制，需单独处理）

主要是 `CTaskTpl_<模板实例>` 命名（头无法独立编译）；另有 `CEmitter`、`RoleCameraCtrl` 等。
⇒ 需要：为该类找**能编译的 include 集**，或改用手工探针（单值 `offsetof` 比较）✓
