# 社区已逆向结构体汇总

来源：PAL3patch (zhangboyang) + OpenPAL3 (dontpanic92)

## 基本信息

- 编译器：MSVC (待确认具体版本，需分析 Rich Header)
- 图形 API：DirectX 9 (IDirect3DDevice9)
- 音频：Miles Sound System (AIL)
- 视频：Bink Video
- 输入：DirectInput 8
- 文件系统：CPK 自定义压缩包（LZO 压缩）
- 脚本：SCE 字节码虚拟机

## PE 内存布局

```
Section   Base Address    End Address    Size
-------   -----------    -----------    --------
.text     0x00401000     0x00569018     0x168018 (代码段)
.rdata    0x0056A000     0x0057F1F2     0x0151F2 (只读数据)
.data     0x00580000     0x0060C000     0x08C000 (数据段)
.rsrc     0x01897000     0x0189833C     0x00133C (资源)
.rsrc2    0x0189833C     0x0189C3CA     0x00408E (资源2)
.brick    0x0189E000     0x018BFCA4     0x021CA4 (加密/保护?)
```

## 已确认结构体大小

| 结构体 | sizeof | 来源 |
|--------|--------|------|
| CCBUI | 0xA48 | PAL3patch |
| UIStatic | 0x98 | PAL3patch |
| CCBLineupWindow | 0x7C | PAL3patch |
| UI3DCtrl | 0x134 | PAL3patch |
| gbCamera | 0x178 | PAL3patch |
| LineupUI | 0x29CEC | PAL3patch |
| ObjectCamera | 0x7C | PAL3patch |
| UIStaticEXA | 0xC0 | PAL3patch |
| UICaption | 0x60 | PAL3patch |
| UINote | 0x10C | PAL3patch |
| ScreenEffect | 0x18 | PAL3patch |
| UIRoleSelect | 0x5D0 | PAL3patch |
| UIHeadDialog | 0x160 | PAL3patch |
| UIRoleDialog | 0x454 | PAL3patch |
| UIChatRest | 0x252C | PAL3patch |
| UIEmote | 0x8E0 | PAL3patch |
| UIGameFrm | 0x6E1C | PAL3patch |
| UISceneMap | 0x3F4 | PAL3patch |
| UISceneFace | 0x6F4 | PAL3patch |
| UISceneFrm | 0xB30 | PAL3patch |
| UISkee | 0x1DB0 | PAL3patch |
| UIGameOver | 0xE8 | PAL3patch |
| HeadMsg | 0x24 | PAL3patch |
| gbTexture_D3D | 0x60 | PAL3patch |
| GRPinput | 0x2958 | PAL3patch |
| SoundMgr | 0xE04FC | PAL3patch |
| gbAudioManager | 0xF4 | PAL3patch |
| gbBinkVideo | 0x1C0388 | PAL3patch |
| CD3DSettings | 0x6C | PAL3patch |
| gbGfxManager_D3D | 0x8F0 | PAL3patch |
| tagCmdData | 0x2C | PAL3patch |
| tagThread | 0x58 | PAL3patch |
| tagPlayerSet | 0x34 | PAL3patch |
| CCBSystem | 0x162D8 | PAL3patch |
| UICursor | 0x20 | PAL3patch |
| UnderWater | 0x18 | PAL3patch |
| RenderTarget | 0xC8 | PAL3patch |
| tagAttackSequen | 0x28 | PAL3patch |
| CCBAttackSequen | 0x1C8 | PAL3patch |
| gbPrintFont_UNICODE | 0xC4 | PAL3patch |
| Role | 0x2200 | PAL3patch |

## 已知全局变量地址

| 变量名 | 地址 | 类型 |
|--------|------|------|
| GB_GfxMgr | 0x00BFDA60 | gbGfxManager_D3D** |
| g_msgbk | 0x00BFDAB0 | UIStaticFlex |
| PAL3_s_gamestate | 0x00BFDA6C | int* |
| PAL3_s_drvinfo | 0x00BFD6C8 | gbGfxDriverInfo |
| PAL3_s_bActive | 0x005833B8 | int* |
| PAL3_s_flag | 0x005833BC | unsigned* |
| PAL3_m_gametime | 0x00BFDAA0 | float* |
| PAL3_m_pCBSystem | 0x00BFDA74 | CCBSystem** |
| PAL3_m_screenImg | 0x008ACC10 | gbImage2D |
| g_pVFileSys | gboffset+0x1015D3A8 | gbVFileSystem** |
| g_gamefrm | 0x00DB9FD0 | UIGameFrm |
| g_bink | 0x00A3A7D8 | gbBinkVideo |
| g_CurrentTime | gboffset+0x1015D338 | double* |
| g_input | 0x00BFAD70 | GRPinput |
| g_lastupdateloading | 0x00C12B20 | DWORD* |
| ui_tex_color_gbf | 0x01895058 | gbRenderEffect** |

注：`gboffset` 是 GBENGINE.dll 的加载基址。

## 已知函数地址

### PAL3.exe 函数

| 地址 | 函数名 | 签名 |
|------|--------|------|
| 0x005563DE | _setdefaultprecision | void(void) |
| 0x005536A9 | pal3malloc | void*(size_t) |
| 0x00552F55 | pal3free | void(void*) |
| 0x00553A61 | pal3fsopen | FILE*(const char*, const char*, int) |
| 0x00404800 | PAL3_Create | void(HINSTANCE) |
| 0x00406230 | PAL3_Destroy | void(void) |
| 0x004055D0 | PAL3_Update | void(float) |
| 0x00404D60 | WndProc | LRESULT(HWND, UINT, WPARAM, LPARAM) |
| 0x00404FF0 | PAL3_InitGFX | void(void) |
| 0x00538320 | PrepareDir | int(void) |
| 0x00541210 | UIDrawTextEx | void(const char*, RECT*, gbPrintFont*, int, int) |
| 0x00540FD0 | UIPrint | void(int, int, char*, gbColorQuad*, int) |
| 0x005415F0 | UICursor_Inst | UICursor*(void) |
| 0x0041F9F0 | UpdateLoading | void(void) |
| 0x00408BE0 | PlayerMgr_Create | void(void) |
| 0x0040C7D0 | PlayerMgr_DrawMsg | void(void) |
| 0x00445B90 | UIWnd_Create | void(__thiscall)(UIWnd*, int, RECT*, UIWnd*) |
| 0x00445D20 | UIWnd_MoveWindow | void(__thiscall)(UIWnd*, int, int) |
| 0x00445FA0 | UIWnd_SetRect | void(__thiscall)(UIWnd*, RECT*) |
| 0x00445CD0 | UIWnd_Render | void(__thiscall)(UIWnd*) |
| 0x0043DDF0 | UIFrameWnd_Render | void(__thiscall)(UIFrameWnd*) |
| 0x0044F130 | UIGameFrm_Create | void(__thiscall)(UIGameFrm*) |
| 0x00450F90 | UIRoleDialog_Create | void(__thiscall)(...) |
| 0x005163D0 | CCBUI_Create | bool(__thiscall)(CCBUI*) |
| 0x0053DD70 | SoundMgr_Create | void(__thiscall)(SoundMgr*) |
| 0x0053DEF0 | SoundMgr_Destroy | void(__thiscall)(SoundMgr*) |
| 0x004C6460 | CTrail_Create | bool(__thiscall)(CTrail*) |
| 0x00538500 | Archive_Save | BOOL(__thiscall)(Archive*, int) |
| 0x004142E0 | Role_OnBehaviourFinish | void(__thiscall)(Role*) |
| 0x00411E00 | Role_UpdateMove | void(__thiscall)(Role*, float, bool) |

### GBENGINE.dll 函数（相对偏移）

| 偏移 | 函数名 | 签名 |
|------|--------|------|
| +0x1001AC50 | gbGfxManager_D3D_Reset3DEnvironment | int(__thiscall)(...) |
| +0x1001A190 | gbGfxManager_D3D_BuildPresentParams | void(__thiscall)(...) |
| +0x10018F00 | gbGfxManager_D3D_EndScene | void(__thiscall)(...) |
| +0x1001BF80 | gbTexture_D3D_CreateForRenderTarget | int(__thiscall)(...) |
| +0x1001C010 | gbTexture_D3D_CreateFromFileMemory | void(__thiscall)(...) |
| +0x1001BA60 | gbTexture_D3D_Ctor | ctor(__thiscall)(...) |
| +0x1001BAA0 | gbTexture_D3D_Dtor | dtor(__thiscall)(...) |
| +0x10004450 | gbPrintFontMgr_GetFont | gbPrintFont*(__thiscall)(...) |
| +0x10022BF0 | gbPrintFont_PrintString | void(__thiscall)(...) |
| +0x10021A80 | gbCamera_SetAsCurrent | void(__thiscall)(...) |
| +0x100220B0 | gbCamera_PointEyeToScr | void(__thiscall)(...) |
| +0x100222C0 | gbCamera_GetRayToScreen | void(__thiscall)(...) |
| +0x10021C50 | gbCamera_SetDimention | void(__thiscall)(...) |
| +0x10030540 | gbVFileSystem_OpenFile | gbVFile*(__thiscall)(...) |
| +0x10030BE0 | gbVFileSystem_GetFileSize | long(__thiscall)(...) |
| +0x10030810 | gbVFileSystem_Read | void(__thiscall)(...) |
| +0x100307A0 | gbVFileSystem_CloseFile | void(__thiscall)(...) |
| +0x100277E0 | gbCrc32Compute | unsigned(const char*) |
| +0x10027730 | gbCrc32Init | void(void) |
| +0x10001C80 | gbAudioManager_SetMusicMasterVolume | void(__thiscall)(...) |
| +0x100E4B0D | gbmalloc | void*(size_t) |
| +0x100E4B99 | gbfree | void(void*) |
| +0x1001E0C0 | gbCreateGraphManager | gbGfxManager*(gbGfxDriverInfo*) |
| +0x10001120 | gbAudioManager_Ctor | ctor(__thiscall)(...) |

## 已知 RTTI 类名

来自 PAL3patch notes/pal3/known_classes.txt:

### 战斗系统
- CCBSystem, CCBUI, CCBStage, CCBControl, CCBAI
- CCBRoleState, CCBAttackSequen, CCBEditor
- CEffectSystem, CEffectSimple, CEffMgr
- C2DSpark, C3DSpark
- CUtil

### UI 系统
- UIWnd, UIFrameWnd, UIStatic, UIStaticEX, UIStaticEXA
- UIButton, UIButtonEx, UIButtonEXA
- UIDialog, UINote, UICaption
- UIScrollBar, UIFlexBar, UIListBox
- UIProgressBar, UIAnimateCtrl, UITextArea
- UIStaticFlex, UIStaticFlip
- UIRoleDialog, UIHeadDialog, UIRoleSelect
- UISceneFrm, UISceneMap, UISceneFace
- UIGameFrm, UIGameOver
- UIChatRest, UIEmote, UICursor
- UI3DCtrl, UIRenderObj, MUIDialog
- UIKillFlyer, UIRowing, UIEncampment, UISkee

### 游戏逻辑
- Role, ObjectCamera, Object3D
- PalScript, PalScriptWaitObj
- ScreenEffect, HeadMsg
- Archive, RestScript, ScriptData
- LineupUI, CCBLineupWindow
- GrayScale, UnderWater

### 引擎核心 (gbEngine)
- gbGfxManager_D3D, gbTexture_D3D, gbTexture
- gbCamera, gbPrintFont, gbPrintFont_UNICODE
- gbImage2D, gbBinkVideo
- gbVFileSystem, gbResManager, gbResource
- gbAudioManager, GRPinput
- gbRenderEffect, gbMatrixStack, gbVertPoolMgr

## 游戏状态枚举

```c
enum GAME_STATE {
    GAME_NONE = 0,
    GAME_UI = 1,
    GAME_SCENE = 2,
    GAME_COMBAT = 3,
    GAME_SUBGAME_ENCAMPMENT = 4,
    GAME_SUBGAME_SKEE = 5,
    GAME_SUBGAME_ROWING = 6,
    GAME_SUBGAME_HIDEANDSEEK = 7,
    GAME_SUBGAME_NIGHTADVENTURE = 8,
    GAME_OVER = 9,
};
```

## 模块划分（根据已知类推断）

| 模块 | 主要类/结构体 | 地址范围（估计） |
|------|-------------|-----------------|
| 引擎核心 | gbGfxManager_D3D, gbCamera | GBENGINE.dll |
| UI 框架 | UIWnd, UIStatic, UIButton | 0x0043xxxx - 0x0045xxxx |
| 游戏 UI | UIGameFrm, UISceneFrm | 0x0044xxxx - 0x0054xxxx |
| 战斗系统 | CCBSystem, CCBUI | 0x004Dxxxx - 0x0052xxxx |
| 角色系统 | Role, PlayerMgr | 0x0040xxxx - 0x0041xxxx |
| 脚本引擎 | PalScript | 待确认 |
| 音频 | SoundMgr, gbAudioManager | 0x0053xxxx |
| 视频 | gbBinkVideo | 0x0053Cxxx |
| 文件 IO | gbVFileSystem, CPK | GBENGINE.dll |
