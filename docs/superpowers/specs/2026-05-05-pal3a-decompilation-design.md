# PAL3A.exe 完整反编译设计规格

## 目标

将 PAL3A.exe（仙剑奇侠传三外传）反编译为功能正确的 C++ 源代码。
利用 PAL3A.PDB 提供的完整调试符号精确复刻原始项目结构。
不要求字节匹配，但要求逻辑正确可运行。

## 前提条件

| 资源 | 状态 | 说明 |
|------|------|------|
| PAL3Aunpacked.exe | ✅ 已有 | 脱壳后的可执行文件 |
| PAL3A.pdb | ✅ 已有 | PDB 2.0 (JG)，7MB，完整调试符号 |
| gbengine.lib | ✅ 已有 | gbengine.dll 导入库 |
| topo.lib | ✅ 已有 | topo.dll 导入库 |
| Ghidra + PDB 加载 | ❌ 未完成 | 需要在 Ghidra 中导入并应用 PDB |

## 技术参数

- **编译器**: MSVC 7.0 (Visual Studio .NET 2002)，链接器 MSVC 7.1
- **目标**: 32-bit x86 Windows PE
- **运行时依赖**: gbengine.dll, topo.dll, DirectX 9, Miles Sound System
- **编译单元**: ~170 个 .obj（从 PDB 提取）
- **源文件**: ~200 个 .cpp + 对应 .h（头文件和源文件同目录）
- **子目录**: 14 个功能模块

## 文件组织：严格复刻 PDB 原始结构

### 核心原则

1. `.h` 和 `.cpp` 放在同一目录（复刻 `D:\PAL3A\PAL3\<subdir>\`）
2. 文件名大小写严格遵循 PDB 记录
3. 不使用单独的 `include/pal3a/` 头文件树
4. 编译 include path 设为 `src/pal3a/`
5. 源文件间用相对路径引用：`#include "gamebase/RoleDef.h"`
6. Windows 大小写不敏感的重复目录合并为小写

### 目录结构

```
src/pal3a/                     ← 对应 D:\PAL3A\PAL3\
├── (根文件 13个)
│   WinMain.cpp, Actor.cpp, gbExt.cpp, gbExt.h, Console.cpp,
│   SoundMgr.cpp, SkyBox.cpp, Archive.cpp, BinkVideo.cpp,
│   UIBase.cpp, UI_TextureInfo.cpp, ObjLockInput.cpp,
│   SEHException.cpp, MXCEft.cpp, StdAfx.cpp
├── support/                   (4 .cpp + .h)
│   ConfigFile.cpp/.h, ORect.cpp/.h, TxtFile.cpp/.h, StringTable.cpp/.h
├── script/                    (4 .cpp + .h)
│   PalScript.cpp/.h, PtrArray.cpp/.h, ScriptCmd.cpp/.h, scAsmDecoder.cpp/.h
├── gamebase/                  (24 .cpp + .h)
│   Role.cpp, RoleDef.h, RoleCtrl.h/.cpp, RoleTask.cpp,
│   RoleShadow.cpp, rolecamera.cpp/.h, Scene.cpp, SceneData.cpp,
│   SceneMgr.cpp/.h, SceneObj.cpp/.h, SceneObj_Common.cpp,
│   SceneObj_ProcFunc.cpp, PathFinder.cpp, AStarPathFinder.cpp,
│   PlayerMgr.cpp/.h, NavigationInfo.cpp/.h, FileSys.cpp,
│   GrpInput.cpp/.h, HeadMsg.cpp/.h, NameSys.cpp/.h,
│   BillBoardFace.cpp, CollidePack.cpp, PAL3.cpp, TaskObj.cpp/.h
├── ui/                        (20 .cpp + .h, 合并 ui/ + UI/)
│   UIWnd.cpp/.h, UIButton.cpp/.h, UIDialog.cpp/.h, UIStatic.cpp/.h,
│   UIListBox.cpp/.h, UIFrameWnd.cpp/.h, UIScrollBar.cpp/.h,
│   UIProgressBar.cpp/.h, UITabBtn.cpp/.h, UIAnimateCtrl.cpp/.h,
│   UIAnimateCtrlEX.cpp/.h, UIDragBar.cpp/.h, UIFlexBar.cpp/.h,
│   UIPlugInfo.cpp/.h, UIPushButton.cpp/.h, UIStaticCB.cpp/.h,
│   UIStaticEX.cpp/.h, UIStaticFlex.cpp/.h, UITab.cpp/.h,
│   UI3DCtrl.cpp/.h
├── effect/                    (22 .cpp + .h, 合并 effect/ + Effect/)
│   Glow.cpp, GlowObj.cpp, GrayScale.cpp, MeshFx.cpp,
│   MeshFxCreator.cpp, GeomFactory.cpp, particle.cpp/.h,
│   ParticleEffect.cpp/.h, ScreenEffect.cpp/.h, ScreenEffectMgr.cpp,
│   ScreenFadeIn.cpp, ScreenFadeOut.cpp, ScreenFadeWhite.cpp,
│   ScreenFadeWhite2.cpp, RenderTarget.cpp, PoisonFog.cpp,
│   MXFire.cpp, MXSavePoint.cpp, UnderWater.cpp, Transport.cpp,
│   EffectSystem.cpp/.h, EffectTrail.cpp
├── gameui/                    (22 .cpp + .h, 合并 gameui/ + GameUI/ + GAMEUI/)
│   UIGameFrm.cpp/.h, UICaption.cpp, UIChatRest.cpp, UICoverFrm.cpp,
│   UIEmote.cpp, UIGameOver.cpp, UIHeadDialog.cpp, UILoadingFrm.cpp,
│   UINote.cpp, UIRoleSelect.cpp, UISceneFace.cpp, UISceneMap.cpp,
│   UIBigMap.cpp, UITextArea.cpp, UITitle_BBTY.cpp, UITitle_JDHY.cpp,
│   UITitle_QCYM.cpp, UITitle_ArcSave.cpp, UITitle_XJTM.cpp,
│   UITitle_YXXX.cpp, UIRoleDialog.cpp, UISceneFrm.cpp
├── gamemainui/                (14 .cpp + .h, 合并 GameMainUI/ + gamemainui/ + GAMEMAINUI/)
│   3DObject.cpp/.h, StateUI.cpp/.h, SwordUI.cpp/.h, MagicUI.cpp,
│   MainPropUI.cpp/.h, MainEquipUI.cpp, LineupUI.cpp/.h,
│   SystemUI.cpp/.h, TaskBookUI.cpp, MUIDialog.cpp/.h,
│   UIParticle.cpp/.h, UIGroupCtrl.cpp, ChoseCompose.cpp/.h,
│   JusticeBookUI.cpp, MU_tex_define.h
├── combat/                    (49 .cpp + .h, 合并 combat/ + Combat/)
│   CBAI.cpp, CBSystem.cpp/.h, CBUI.cpp, CBStage.cpp,
│   CBStageCam.cpp, CBStageRole.cpp, CBStageScene.cpp,
│   CBStageEffect.cpp, CBStageShadow.cpp, CBRoleState.cpp,
│   CBControl.cpp, CBEditor.cpp, CBAttackSequen.cpp,
│   CBDisplayChain.cpp, CB2DEffect.cpp, CB3DEffect.cpp,
│   CBUIDefine.h, SParticleEffect.cpp, Util.cpp/.h,
│   UtilObj.cpp, 3ds.cpp, EffMgr.cpp, EffObj.cpp,
│   EffAction.cpp, EffAudio.cpp, EffBink.cpp, EffCallBack.cpp,
│   EffCamera.cpp/.h, EffCustomShape.cpp/.h, EffCylinder.cpp/.h,
│   EffExplosive.cpp/.h, EffGrid.cpp/.h, EffMeteor.cpp,
│   EffModel.cpp, EffQuad.cpp, EffQuake.cpp, EffSPartical.cpp,
│   EffShock.cpp, EffTemplate.cpp, EffTime.cpp,
│   EffTrackCustomShape.cpp, EffTrackCylinder.cpp, EffTrackGrid.cpp,
│   EffTrackModel.cpp, EffTrackQuad.cpp, EffTrackSParticle.cpp,
│   EffgbParticle.cpp/.h, EffectSystem.cpp, EffectTrail.cpp,
│   Transport.cpp, UnderWater.cpp
├── fight/                     (19 .cpp + .h)
│   DealData.cpp, DealUI.cpp, EquipUI.cpp, PropUI.cpp, SaleUI.cpp,
│   LoadData.cpp, UIAnimate.cpp, UIRoleDialog.cpp, UIRoleSelect.cpp,
│   UISceneFace.cpp, UISceneFrm.cpp, UISceneMap.cpp, UITextArea.cpp,
│   UITitle_ArcSave.cpp, UITitle_BBTY.cpp, UITitle_JDHY.cpp,
│   UITitle_QCYM.cpp, UITitle_XJTM.cpp, UITitle_YXXX.cpp
├── arcinfo/                   (4 .cpp + .h)
│   ArcLoaddata.cpp, Arc_common.cpp, CJ_FindFile.cpp, FindArc.cpp
├── catchghost/                (4 .cpp + .h)
│   CG_Edit.cpp, CG_Entry.cpp, CG_Scene.cpp, CG_SceneParser.cpp
├── compose/                   (3 .cpp + .h)
│   Comp_DonateUI.cpp, ComposeUI.cpp, UIRoleSelectDialog.cpp
└── assistant_system/          (2 .cpp + .h)
    DealData.cpp, UIAnimate.cpp
```

## 分层实现策略

### 总体方法：先搭框架再逐层填充

1. Ghidra 加载 PDB → 导出全部函数签名 + 类型 + 头文件信息
2. 批量生成所有 stub 文件（.h 含类声明，.cpp 含空函数体）→ 确保可编译
3. 按依赖层级逐批替换 stub 为真实实现
4. 每层完成后编译验证

### 依赖层级

| Layer | 模块 | 文件数 | 依赖 | 难度 |
|-------|------|--------|------|------|
| 0 | 基础设施（Ghidra导出 + stub生成 + 构建系统） | 全部 | 无 | 工具开发 |
| 1 | support/ + 根目录工具文件 (gbExt, Console, SEHException) | ~7 | 仅 gbengine API | 低 |
| 2 | script/ — SCE 脚本系统 | 4 | support + gbengine | 中（有社区参考） |
| 3 | gamebase/ — 核心数据结构 | 24 | support + script + gbengine | 高（核心） |
| 4 | ui/ — UI 框架 | 20 | gbengine UI 类 | 中 |
| 5 | effect/ — 特效系统 | 22 | gbengine 渲染 + gamebase | 中 |
| 6 | gameui/ + gamemainui/ — 游戏界面 | 36 | ui + gamebase + effect | 中 |
| 7 | combat/ + fight/ — 战斗系统 | 68 | 全部上层 | 高（最大） |
| 8 | arcinfo/ + catchghost/ + compose/ + assistant_system/ + 剩余根文件 | ~13 | gamebase + ui | 低 |

### 每层交付标准

1. 所有函数有功能正确的实现（不确定处标记 `/* UNCERTAIN */`）
2. `cmake -B build -DBUILD_TARGET=pal3a && cmake --build build` 编译 0 error
3. 不引入未解析外部符号（除 gbengine/topo 已知导出）

## Phase 1 定义

**Phase 1 = Layer 0 + Layer 1**：基础设施搭建 + 第一批实际代码

### Layer 0 具体任务

1. **Ghidra 项目设置**
   - 导入 PAL3Aunpacked.exe 到 Ghidra
   - 加载 PAL3A.pdb（Ghidra 原生支持 PDB 2.0）
   - 验证：函数名、参数类型、源文件映射是否正确加载

2. **导出脚本**（`tools/ghidra/export_pal3a_full.py`）
   - 导出所有函数：地址、名称、返回类型、参数列表、所属源文件、大小
   - 导出所有全局变量：地址、名称、类型
   - 导出所有类/结构体：名称、大小、成员列表（名称+类型+偏移）
   - 导出头文件引用：每个编译单元引用了哪些 .h
   - 输出到 `asm/pal3a/pdb_export.json`

3. **符号索引构建**
   - 运行 `tools/pal3a_build_index.py` 处理导出数据
   - 生成 `build/pal3a/pdb_index.json`

4. **批量 stub 生成**（增强 `tools/pal3a_emit_function_stub.py`）
   - 按 PDB 源文件路径创建目录结构
   - 生成每个 .h（类声明 + 函数签名）
   - 生成每个 .cpp（#include 对应 .h + 空函数体）
   - 输出到 `src/pal3a/`

5. **构建系统更新**
   - 修改 CMakeLists.txt PAL3A 目标为 `GLOB_RECURSE`
   - `target_include_directories` 包含 `src/pal3a/`
   - 链接 gbengine.lib + topo.lib
   - 验证编译通过

6. **清理**
   - 删除 `.worktrees/pal3a-phase1/` worktree
   - 移除旧的 `include/pal3a/` 目录
   - 更新 CLAUDE.md

### Layer 1 具体任务

**目标文件（~7个）：**
- `src/pal3a/support/ConfigFile.cpp` — INI 配置文件解析
- `src/pal3a/support/ORect.cpp` — 矩形工具类
- `src/pal3a/support/TxtFile.cpp` — 文本文件读取
- `src/pal3a/support/StringTable.cpp` — 字符串表
- `src/pal3a/gbExt.cpp` — gbengine 扩展函数
- `src/pal3a/Console.cpp` — 调试控制台
- `src/pal3a/SEHException.cpp` — 异常处理

**方法：**
- 从 Ghidra 反编译结果提取伪代码
- 改写为标准 C++，修正类型和命名
- 确保每个文件独立可编译
- 标记不确定的实现

## 构建配置

```cmake
# CMakeLists.txt PAL3A target
elseif(BUILD_TARGET STREQUAL "pal3a")
    message(STATUS "Configuring PAL3A.exe build")
    file(GLOB_RECURSE PAL3A_SOURCES "src/pal3a/*.cpp" "src/pal3a/*.c")
    add_executable(PAL3A WIN32 ${PAL3A_SOURCES})
    target_include_directories(PAL3A PRIVATE
        ${CMAKE_SOURCE_DIR}/src/pal3a
        ${CMAKE_SOURCE_DIR}/include
    )
    target_link_libraries(PAL3A
        ${CMAKE_SOURCE_DIR}/lib/gbengine.lib
        ${CMAKE_SOURCE_DIR}/lib/topo.lib
        ${PLATFORM_LIBS}
        advapi32
    )
    set_target_properties(PAL3A PROPERTIES OUTPUT_NAME "PAL3A")
endif()
```

## 工具链

| 工具 | 路径 | 功能 |
|------|------|------|
| Ghidra 导出 | `tools/ghidra/export_pal3a_full.py` | 从 Ghidra 导出全部符号到 JSON |
| PDB 字符串提取 | `tools/pdb_strings.py` | 从 PDB 原始数据提取文件路径（已有） |
| PDB 源文件提取 | `tools/extract_pal3a_sources.py` | 提取 PAL3A 源文件列表（已有） |
| 符号索引 | `tools/pal3a_build_index.py` | 规范化符号索引（已有） |
| Stub 生成 | `tools/pal3a_emit_function_stub.py` | 批量生成 stub .h/.cpp 对（需增强） |
| 进度跟踪 | `tools/progress.py --target pal3a` | 多目标进度报告（已有） |

## 参考资源

- **PAL3patch** (`extra/PAL3patch/`) — 社区逆向结构体、全局变量地址
- **OpenPAL3** — Rust 重实现，有 SCE 脚本 VM 参考
- **gbengine 已有实现** (`src/gbengine/`) — 引擎 API 参考
- **PDB 符号** — 函数名、参数类型、类布局的权威来源

## 成功标准

### Phase 1 完成标准
1. Ghidra 项目可用，PDB 符号已加载
2. `asm/pal3a/pdb_export.json` 包含全部导出数据
3. `src/pal3a/` 包含 ~200 个 stub 文件，目录结构复刻 PDB
4. `cmake -B build -DBUILD_TARGET=pal3a && cmake --build build` 编译通过
5. Layer 1 的 7 个文件有功能正确实现（非 stub）
6. `.worktrees/pal3a-phase1/` 已清理

### 最终完成标准
1. ~200 个源文件全部有功能正确实现
2. 0 个 stub 残留
3. 所有不确定实现标记 `/* UNCERTAIN */`
4. 编译通过
