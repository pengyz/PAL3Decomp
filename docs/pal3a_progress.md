# PAL3A Decompilation Progress

Per-file progress tracking. Updated as functions are completed.

## Status Legend

- **File Status**: stub = has stub file | wip = work in progress | done = all functions compilable | match = byte-matched
- **Function Status**: stub | filled (IDA output filled) | compiles | matches (byte-identical)

## Summary

| Metric | Count |
|--------|-------|
| Source files (from PDB) | 185 |
| Files with stubs | 181 |
| Total functions | 4523 |
| Functions compilable | 0 |
| Functions byte-matched | 0 |

## Per-File Progress

| File | Functions | Status | Compiles | Matches | Notes |
|------|-----------|--------|----------|---------|-------|
| Actor.cpp | 22 | stub | 0/22 | 0/22 | |
| Archive.cpp | 28 | stub | 0/28 | 0/28 | |
| BinkVideo.cpp | 15 | stub | 0/15 | 0/15 | |
| Console.cpp | 63 | stub | 0/63 | 0/63 | |
| GAMEMAINUI/TaskBookUI.cpp | 15 | stub | 0/15 | 0/15 | |
| GAMEUI/UITitle_ArcSave.cpp | 6 | stub | 0/6 | 0/6 | |
| GAMEUI/UITitle_XJTM.cpp | 15 | stub | 0/15 | 0/15 | |
| GAMEUI/UITitle_YXXX.cpp | 11 | stub | 0/11 | 0/11 | |
| MXCEft.cpp | 12 | stub | 0/12 | 0/12 | |
| ObjLockInput.cpp | 9 | stub | 0/9 | 0/9 | |
| SEHException.cpp | 11 | stub | 0/11 | 0/11 | |
| SkyBox.cpp | 26 | stub | 0/26 | 0/26 | |
| SoundMgr.cpp | 29 | stub | 0/29 | 0/29 | |
| UIBase.cpp | 30 | stub | 0/30 | 0/30 | |
| UI_TextureInfo.cpp | 17 | stub | 0/17 | 0/17 | |
| WinMain.cpp | 7 | stub | 0/7 | 0/7 | |
| arcinfo/ArcLoaddata.cpp | 16 | stub | 0/16 | 0/16 | |
| arcinfo/Arc_common.cpp | 16 | stub | 0/16 | 0/16 | |
| arcinfo/CJ_FindFile.cpp | 18 | stub | 0/18 | 0/18 | |
| arcinfo/FindArc.cpp | 10 | stub | 0/10 | 0/10 | |
| assistant system/deal/UIAnimate.cpp | 1 | - | 0/1 | 0/1 | |
| assistant_system/Deal/DealData.cpp | 12 | stub | 0/12 | 0/12 | |
| assistant_system/Deal/DealUI.cpp | 21 | stub | 0/21 | 0/21 | |
| assistant_system/Deal/EquipUI.cpp | 31 | stub | 0/31 | 0/31 | |
| assistant_system/Deal/PropUI.cpp | 25 | stub | 0/25 | 0/25 | |
| assistant_system/Deal/SaleUI.cpp | 29 | stub | 0/29 | 0/29 | |
| catchghost/CG_Edit.cpp | 10 | stub | 0/10 | 0/10 | |
| catchghost/CG_Entry.cpp | 10 | stub | 0/10 | 0/10 | |
| catchghost/CG_Scene.cpp | 43 | stub | 0/43 | 0/43 | |
| catchghost/CG_SceneParser.cpp | 9 | - | 0/9 | 0/9 | |
| combat/3ds.cpp | 16 | stub | 0/16 | 0/16 | |
| combat/CB2DEffect.cpp | 10 | stub | 0/10 | 0/10 | |
| combat/CB3DEffect.cpp | 7 | stub | 0/7 | 0/7 | |
| combat/CBAI.cpp | 53 | stub | 0/53 | 0/53 | |
| combat/CBAttackSequen.cpp | 44 | stub | 0/44 | 0/44 | |
| combat/CBControl.cpp | 31 | stub | 0/31 | 0/31 | |
| combat/CBDisplayChain.cpp | 20 | stub | 0/20 | 0/20 | |
| combat/CBEditor.cpp | 104 | stub | 0/104 | 0/104 | |
| combat/CBRoleState.cpp | 243 | stub | 0/243 | 0/243 | |
| combat/CBStage.cpp | 152 | stub | 0/152 | 0/152 | |
| combat/CBStageCam.cpp | 65 | stub | 0/65 | 0/65 | |
| combat/CBStageEffect.cpp | 11 | stub | 0/11 | 0/11 | |
| combat/CBStageRole.cpp | 104 | stub | 0/104 | 0/104 | |
| combat/CBStageScene.cpp | 32 | stub | 0/32 | 0/32 | |
| combat/CBStageShadow.cpp | 9 | stub | 0/9 | 0/9 | |
| combat/CBSystem.cpp | 80 | stub | 0/80 | 0/80 | |
| combat/CBUI.cpp | 187 | stub | 0/187 | 0/187 | |
| combat/EffAction.cpp | 13 | stub | 0/13 | 0/13 | |
| combat/EffAudio.cpp | 13 | stub | 0/13 | 0/13 | |
| combat/EffBink.cpp | 12 | stub | 0/12 | 0/12 | |
| combat/EffCallBack.cpp | 13 | stub | 0/13 | 0/13 | |
| combat/EffCamera.cpp | 12 | stub | 0/12 | 0/12 | |
| combat/EffCustomShape.cpp | 13 | stub | 0/13 | 0/13 | |
| combat/EffCylinder.cpp | 16 | stub | 0/16 | 0/16 | |
| combat/EffExplosive.cpp | 18 | stub | 0/18 | 0/18 | |
| combat/EffGrid.cpp | 20 | stub | 0/20 | 0/20 | |
| combat/EffMeteor.cpp | 26 | stub | 0/26 | 0/26 | |
| combat/EffMgr.cpp | 30 | stub | 0/30 | 0/30 | |
| combat/EffModel.cpp | 15 | stub | 0/15 | 0/15 | |
| combat/EffQuad.cpp | 23 | stub | 0/23 | 0/23 | |
| combat/EffQuake.cpp | 12 | stub | 0/12 | 0/12 | |
| combat/EffSPartical.cpp | 13 | stub | 0/13 | 0/13 | |
| combat/EffShock.cpp | 18 | stub | 0/18 | 0/18 | |
| combat/EffTemplate.cpp | 12 | stub | 0/12 | 0/12 | |
| combat/EffTime.cpp | 12 | stub | 0/12 | 0/12 | |
| combat/EffTrackCustomShape.cpp | 7 | stub | 0/7 | 0/7 | |
| combat/EffTrackCylinder.cpp | 7 | stub | 0/7 | 0/7 | |
| combat/EffTrackGrid.cpp | 7 | stub | 0/7 | 0/7 | |
| combat/EffTrackModel.cpp | 7 | stub | 0/7 | 0/7 | |
| combat/EffTrackQuad.cpp | 7 | stub | 0/7 | 0/7 | |
| combat/EffTrackSParticle.cpp | 7 | stub | 0/7 | 0/7 | |
| combat/EffgbParticle.cpp | 13 | stub | 0/13 | 0/13 | |
| combat/SParticle/SParticleEffect.cpp | 48 | stub | 0/48 | 0/48 | |
| combat/Util.cpp | 13 | stub | 0/13 | 0/13 | |
| combat/UtilObj.cpp | 7 | stub | 0/7 | 0/7 | |
| compose/Comp_DonateUI.cpp | 20 | stub | 0/20 | 0/20 | |
| compose/ComposeUI.cpp | 12 | stub | 0/12 | 0/12 | |
| compose/UIRoleSelectDialog.cpp | 14 | stub | 0/14 | 0/14 | |
| effect/EffectSystem.cpp | 40 | stub | 0/40 | 0/40 | |
| effect/EffectTrail.cpp | 10 | stub | 0/10 | 0/10 | |
| effect/GeomFactory.cpp | 1 | stub | 0/1 | 0/1 | |
| effect/Glow.cpp | 11 | stub | 0/11 | 0/11 | |
| effect/GlowObj.cpp | 2 | stub | 0/2 | 0/2 | |
| effect/GrayScale.cpp | 6 | stub | 0/6 | 0/6 | |
| effect/MXFire.cpp | 10 | stub | 0/10 | 0/10 | |
| effect/MXSavePoint.cpp | 10 | stub | 0/10 | 0/10 | |
| effect/MeshFx.cpp | 4 | stub | 0/4 | 0/4 | |
| effect/MeshFxCreator.cpp | 4 | stub | 0/4 | 0/4 | |
| effect/ParticleEffect.cpp | 9 | stub | 0/9 | 0/9 | |
| effect/PoisonFog.cpp | 10 | stub | 0/10 | 0/10 | |
| effect/RenderTarget.cpp | 11 | stub | 0/11 | 0/11 | |
| effect/ScreenEffect.cpp | 5 | stub | 0/5 | 0/5 | |
| effect/ScreenEffectMgr.cpp | 8 | stub | 0/8 | 0/8 | |
| effect/ScreenFadeIn.cpp | 5 | stub | 0/5 | 0/5 | |
| effect/ScreenFadeOut.cpp | 3 | stub | 0/3 | 0/3 | |
| effect/ScreenFadeWhite.cpp | 3 | stub | 0/3 | 0/3 | |
| effect/ScreenFadeWhite2.cpp | 3 | stub | 0/3 | 0/3 | |
| effect/Transport.cpp | 10 | stub | 0/10 | 0/10 | |
| effect/UnderWater.cpp | 11 | stub | 0/11 | 0/11 | |
| effect/particle.cpp | 65 | stub | 0/65 | 0/65 | |
| fight/LoadData.cpp | 15 | stub | 0/15 | 0/15 | |
| gamebase/AStarPathFinder.cpp | 17 | stub | 0/17 | 0/17 | |
| gamebase/BillBoardFace.cpp | 5 | stub | 0/5 | 0/5 | |
| gamebase/CollidePackage/CollidePack.cpp | 16 | stub | 0/16 | 0/16 | |
| gamebase/FileSys.cpp | 11 | stub | 0/11 | 0/11 | |
| gamebase/GrpInput.cpp | 42 | stub | 0/42 | 0/42 | |
| gamebase/HeadMsg.cpp | 7 | stub | 0/7 | 0/7 | |
| gamebase/NameSys.cpp | 12 | stub | 0/12 | 0/12 | |
| gamebase/NavigationInfo.cpp | 16 | stub | 0/16 | 0/16 | |
| gamebase/PAL3.cpp | 41 | stub | 0/41 | 0/41 | |
| gamebase/PathFinder.cpp | 10 | stub | 0/10 | 0/10 | |
| gamebase/PlayerMgr.cpp | 103 | stub | 0/103 | 0/103 | |
| gamebase/Role.cpp | 120 | stub | 0/120 | 0/120 | |
| gamebase/RoleCtrl.cpp | 16 | stub | 0/16 | 0/16 | |
| gamebase/RoleDef.cpp | 3 | stub | 0/3 | 0/3 | |
| gamebase/RoleShadow.cpp | 9 | stub | 0/9 | 0/9 | |
| gamebase/RoleTask.cpp | 16 | stub | 0/16 | 0/16 | |
| gamebase/Scene.cpp | 93 | stub | 0/93 | 0/93 | |
| gamebase/SceneData.cpp | 5 | stub | 0/5 | 0/5 | |
| gamebase/SceneMgr.cpp | 26 | stub | 0/26 | 0/26 | |
| gamebase/SceneObj.cpp | 61 | stub | 0/61 | 0/61 | |
| gamebase/SceneObj_Common.cpp | 28 | - | 0/28 | 0/28 | |
| gamebase/SceneObj_ProcFunc.cpp | 79 | - | 0/79 | 0/79 | |
| gamebase/rolecamera.cpp | 48 | stub | 0/48 | 0/48 | |
| gamemainui/3DObject.cpp | 30 | stub | 0/30 | 0/30 | |
| gamemainui/ChoseCompose.cpp | 8 | stub | 0/8 | 0/8 | |
| gamemainui/JusticeBookUI.cpp | 29 | stub | 0/29 | 0/29 | |
| gamemainui/LineupUI.cpp | 33 | stub | 0/33 | 0/33 | |
| gamemainui/MUIDialog.cpp | 12 | stub | 0/12 | 0/12 | |
| gamemainui/MagicUI.cpp | 50 | stub | 0/50 | 0/50 | |
| gamemainui/MainEquipUI.cpp | 40 | stub | 0/40 | 0/40 | |
| gamemainui/MainPropUI.cpp | 42 | stub | 0/42 | 0/42 | |
| gamemainui/StateUI.cpp | 40 | stub | 0/40 | 0/40 | |
| gamemainui/SwordUI.cpp | 35 | stub | 0/35 | 0/35 | |
| gamemainui/SystemUI.cpp | 27 | stub | 0/27 | 0/27 | |
| gamemainui/UIGroupCtrl.cpp | 11 | stub | 0/11 | 0/11 | |
| gamemainui/UIParticle.cpp | 42 | stub | 0/42 | 0/42 | |
| gameui/UIBigMap.cpp | 21 | stub | 0/21 | 0/21 | |
| gameui/UICaption.cpp | 11 | stub | 0/11 | 0/11 | |
| gameui/UIChatRest.cpp | 15 | stub | 0/15 | 0/15 | |
| gameui/UICoverFrm.cpp | 30 | stub | 0/30 | 0/30 | |
| gameui/UIEmote.cpp | 8 | stub | 0/8 | 0/8 | |
| gameui/UIGameFrm.cpp | 18 | stub | 0/18 | 0/18 | |
| gameui/UIGameOver.cpp | 6 | stub | 0/6 | 0/6 | |
| gameui/UIHeadDialog.cpp | 9 | stub | 0/9 | 0/9 | |
| gameui/UILoadingFrm.cpp | 6 | stub | 0/6 | 0/6 | |
| gameui/UINote.cpp | 7 | stub | 0/7 | 0/7 | |
| gameui/UIRoleDialog.cpp | 15 | stub | 0/15 | 0/15 | |
| gameui/UIRoleSelect.cpp | 11 | stub | 0/11 | 0/11 | |
| gameui/UISceneFace.cpp | 6 | stub | 0/6 | 0/6 | |
| gameui/UISceneFrm.cpp | 6 | stub | 0/6 | 0/6 | |
| gameui/UISceneMap.cpp | 9 | stub | 0/9 | 0/9 | |
| gameui/UITextArea.cpp | 9 | stub | 0/9 | 0/9 | |
| gameui/UITitle_BBTY.cpp | 10 | stub | 0/10 | 0/10 | |
| gameui/UITitle_JDHY.cpp | 26 | stub | 0/26 | 0/26 | |
| gameui/UITitle_QCYM.cpp | 10 | stub | 0/10 | 0/10 | |
| gbExt.cpp | 2 | stub | 0/2 | 0/2 | |
| script/PalScript.cpp | 31 | stub | 0/31 | 0/31 | |
| script/PtrArray.cpp | 7 | stub | 0/7 | 0/7 | |
| script/ScriptCmd.cpp | 238 | stub | 0/238 | 0/238 | |
| script/scAsmDecoder.cpp | 23 | stub | 0/23 | 0/23 | |
| support/ConfigFile.cpp | 10 | stub | 0/10 | 0/10 | |
| support/ORect.cpp | 8 | stub | 0/8 | 0/8 | |
| support/StringTable.cpp | 4 | stub | 0/4 | 0/4 | |
| support/TxtFile.cpp | 10 | stub | 0/10 | 0/10 | |
| ui/UI3DCtrl.cpp | 18 | stub | 0/18 | 0/18 | |
| ui/UIAnimateCtrl.cpp | 10 | stub | 0/10 | 0/10 | |
| ui/UIAnimateCtrlEX.cpp | 5 | stub | 0/5 | 0/5 | |
| ui/UIButton.cpp | 24 | stub | 0/24 | 0/24 | |
| ui/UIDialog.cpp | 3 | stub | 0/3 | 0/3 | |
| ui/UIDragBar.cpp | 16 | stub | 0/16 | 0/16 | |
| ui/UIFlexBar.cpp | 7 | stub | 0/7 | 0/7 | |
| ui/UIFrameWnd.cpp | 5 | stub | 0/5 | 0/5 | |
| ui/UIListBox.cpp | 35 | stub | 0/35 | 0/35 | |
| ui/UIPlugInfo.cpp | 18 | stub | 0/18 | 0/18 | |
| ui/UIProgressBar.cpp | 20 | stub | 0/20 | 0/20 | |
| ui/UIPushButton.cpp | 14 | stub | 0/14 | 0/14 | |
| ui/UIScrollBar.cpp | 23 | stub | 0/23 | 0/23 | |
| ui/UIStatic.cpp | 18 | stub | 0/18 | 0/18 | |
| ui/UIStaticCB.cpp | 3 | stub | 0/3 | 0/3 | |
| ui/UIStaticEX.cpp | 45 | stub | 0/45 | 0/45 | |
| ui/UIStaticFlex.cpp | 11 | stub | 0/11 | 0/11 | |
| ui/UITab.cpp | 9 | stub | 0/9 | 0/9 | |
| ui/UITabBtn.cpp | 6 | stub | 0/6 | 0/6 | |
| ui/UIWnd.cpp | 33 | stub | 0/33 | 0/33 | |

---
Last updated: 2026-05-06
