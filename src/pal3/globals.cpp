// PAL3.exe globals.cpp - Global variables, string constants, and function stubs
// This file provides definitions for all symbols referenced by decompiled code
// that don't yet have their own implementation file.

#include <windows.h>
#include <stdio.h>
#include <string.h>

// ============================================================
// Global variables
// ============================================================

extern "C" char Data[260] = {0};            // 0x01894970 - CD drive path buffer
extern "C" char Filename[260] = {0};        // 0x01894A74 - exe path buffer
extern "C" double dbl_1895070 = 0.0;        // 0x01895070 - last frame time
extern "C" DWORD g_bGameActive = 0;          // 0x005833B8 - game active flag
extern "C" HINSTANCE hInstance = 0;         // 0x00BFDA48
extern "C" char WindowName[32] = "PAL3--SOFTSTAR.sh";  // 0x005839C4
extern "C" HWND hWnd = 0;                   // 0x00BFDA4C
extern "C" HWND hWndParent = 0;             // 0x00BFDA50
extern "C" int xRight = 0;                  // 0x00BFDA54
extern "C" int yBottom = 0;                 // 0x00BFDA58
extern "C" int g_hCursor = 0;            // 0x00BFDA94
extern "C" void *g_pCBSystem = 0;         // 0x00BFDA74 - CCBSystem instance
extern "C" int g_pSceneMgr = 0;            // 0x00BFDA78 - scene manager
extern "C" int g_pGfxManager = 0;            // 0x00BFDA60 - gbGfxManager
extern "C" int g_pCamera = 0;            // 0x00BFDA68
extern "C" char byte_BFDA90 = 0;            // 0x00BFDA90
extern "C" char byte_5833C0 = 0;            // 0x005833C0
extern "C" int g_GDB = 0;            // 0x00975ED8
extern "C" int g_UIManager = 0;            // 0x00C11758
extern "C" char g_Logger = 0;           // 0x17B1EC0
extern "C" int g_pCursorNode1 = 0;            // 0x00A3A6EC
extern "C" int g_pCursorNode2 = 0;            // 0x00A3A6F0
extern "C" void *unk_A3A7D8 = 0;           // 0x00A3A7D8
extern "C" void *ppvOut = 0;                // DirectInput device pointer
extern "C" void *off_56A66C = 0;            // 0x0056A66C - vtable pointer
extern "C" int g_pActorMgr = 0;            // 0x00BFDA64 - gbActorMgr*
extern "C" int g_GameData = 0;            // 0x00DB9FD0

// ============================================================
// String constants (IDA-named, from .rdata/.data sections)
// ============================================================

extern "C" const char aSoftwareSoftst_1[] = "software\\softstar\\pal3";
extern "C" const char aCdriver[]           = "CDriver";
extern "C" const char asc_5D41EC[]         = "\\";
extern "C" const char aPal3[]              = "Pal3";
extern "C" const char aPercentSMovie[]     = "%sMovie";
extern "C" const char aPlsInsertDisc[]     = "Please Insert Disc4 to Dirver %c:";
extern "C" const char aDatascriptComb[]    = "data\\script\\combat";
extern "C" const char aDatascriptLang[]    = "data\\script\\language";
extern "C" const char aAppname[]           = "PAL3";
extern "C" const char aInputDeviceCre[]    = "Input Device Create Failed!";
extern "C" const char aDProjectPal3Ga_0[]  = "D:\\project\\pal3\\gamebase\\PAL3.cpp";
extern "C" const char aFightDatabaseL[]    = "Fight Database Load Error!!";
extern "C" const char aCouldNotAlloca[]    = "Could not allocate CCBSystem";
extern "C" const char aCouldNotAlloca_0[]  = "Could not allocate CSceneMgr";
extern "C" const char aAssislangLang[]     = "assislang\\lang";
extern "C" const char aSBulidSS[]          = "%s Bulid: %s";
extern "C" const char aV104[]              = "V1.04";
extern "C" const char aGameCreateOk[]      = "Game Create OK ...";
extern "C" const char aObjectG02Cvd[]      = "object\\g02.cvd";
extern "C" const char aObjectG03Cvd[]      = "object\\g03.cvd";
extern "C" const char aMovieLogoBik[]      = "Movie\\logo.bik";
extern "C" const char aCreateGfxManag[]    = "Create GfxManager Failed!";
extern "C" const char aCreateActorman[]    = "Create ActorManager Failed!";
extern "C" const char aCNewFailed[]        = "C++ new Failed!";

// InitGFX globals
extern "C" int dword_BFD6C8 = 0;            // 0x00BFD6C8 - gbGfxDriverInfo
extern "C" void *off_56A694 = 0;             // 0x0056A694 - gbVolumeModifier vtable
extern "C" char unk_A3A6F8 = 0;             // 0x00A3A6F8 - gbVolModNode

// ============================================================
// Function stubs (callees of PAL3::Create and WinMain)
// These will be replaced with real implementations as BFS expands.
// ============================================================

// === STUB: 0x0053CF80 - 初始化内部系统 ===
extern "C" void __cdecl sub_53CF80(void) {}

// === STUB: 0x00??????  - FileSysInit ===
extern "C" void __cdecl FileSysInit(void) {}

// === STUB: 0x0041EFA0 - 脚本系统初始化 ===
extern "C" void __cdecl sub_41EFA0(void) {}

// === STUB: 0x004318B0 - 加载战斗脚本 ===
extern "C" void __cdecl sub_4318B0(const char *) {}

// === STUB: 0x00430290 - 加载语言脚本 ===
extern "C" void __cdecl sub_430290(const char *) {}

// === STUB: 0x00430570 - 设置应用名 ===
extern "C" void __cdecl sub_430570(const char *) {}

// 0x0053DF70 - CScreenMode::GetInstance (6B, matched)
// asm: B8 xx xx xx xx C3 = mov eax, &g_ScreenMode; ret

// asm: 8B 44 24 04; 89 81 24 12 00 00; C2 04 00

// asm: 8B 81 28 03 00 00; C3


// C linkage wrappers (PAL3::Update calls these by extern "C" name)

// === STUB: 0x0053DD70 - CScreenMode::SetMode ===

// === STUB: 0x004020E0 - DirectInput初始化 ===

// === STUB: 0x00402270 - 设置输入范围 ===

// === STUB: 0x004022B0 - 设置输入模式 ===

// === STUB: 0x0053C340 - 未知初始化 ===
extern "C" void __cdecl sub_53C340(int a, int b) {}

// === STUB: 0x0041C1B0 - 输入状态初始化 ===
extern "C" void __cdecl sub_41C1B0(int *v) {}

// === STUB: 0x00??????  - PAL_GDB_PAL_GDB ===
extern "C" int __cdecl PAL_GDB_PAL_GDB(void *) { return 1; }

// === STUB: 0x00457410 - 加载辅助语言 ===
extern "C" void __cdecl sub_457410(const char *) {}

// === STUB: 0x00408BE0 - 未知初始化 ===
extern "C" void __cdecl sub_408BE0(void) {}

// === STUB: 0x005415F0 - 获取UIQuadList ===
// UIQuadManager_GetInstance (was sub_5415F0): moved to ui/UIQuadManager.cpp

// === STUB: UIRenderQuadList ===
extern "C" void __cdecl UIRenderQuadList(int) {}

// === STUB: 0x0041F5E0 - 未知初始化(C11758相关) ===
extern "C" void __cdecl sub_41F5E0(void *) {}

// === STUB: 0x0053CE90 - 日志初始化 ===
extern "C" void __cdecl sub_53CE90(void *) {}

// === STUB: 0x0053CC70 - 日志写入 ===
extern "C" void __cdecl sub_53CC70(void *, const char *, const char *) {}

// 0x0053CEF0 - FormatExceptionMessage (61B)
// Formats "file(line):msg" into 1024-byte buffer, then logs it
extern "C" void __cdecl sub_53D030(const char *, ...);
extern "C" const char aExceptionS[] = "Exception: %s";

extern "C" char *__cdecl FormatExceptionMessage(char *pBuf, const char *pMsg, const char *pFile, int nLine)
{
    pBuf[1023] = 0;
    _snprintf(pBuf, 0x400u, "%s(%d):%s", pFile, nLine, pMsg);
    sub_53D030(aExceptionS, pBuf);
    return pBuf;
}

// === STUB: 0x00512500 - CCBSystem构造 ===
extern "C" void *__cdecl sub_512500(void *mem) { return mem; }

// === STUB: CCBSystem_ProcNormalAttack ===
extern "C" void __cdecl CCBSystem_ProcNormalAttack(void *) {}

// === STUB: 0x004CDA10 - CSceneMgr构造 ===
extern "C" int __cdecl sub_4CDA10(int a, int b, int c) { return 0; }

// === STUB: 0x0044F130 - 渲染初始化 ===
extern "C" void __cdecl sub_44F130(void *) {}

// === STUB: 0x0044F610 - 渲染模式设置 ===
extern "C" void __cdecl sub_44F610(int) {}

// === STUB: 0x004BDB10 - CRenderTarget::GetInstance ===
// RenderTarget_GetInstance (was sub_4BDB10): moved to effect/RenderTarget.cpp

// === STUB: RenderTarget_Create ===
extern "C" void __cdecl RenderTarget_Create(int) {}

// === STUB: 0x004B65A0 ===
// RenderTarget3_GetInstance (was sub_4B65A0): moved to effect/RenderTarget34.cpp

// === STUB: 0x004B65F0 ===
// RenderTarget3_Init (was sub_4B65F0): moved to gamebase/GfxHelper.cpp
extern "C" const char aGfxscriptGlowG[] = "gfxscript\\glow.gfx";
extern "C" const char aGfxscriptGeomG[] = "gfxscript\\geom.gfx";

// === STUB: 0x004BFD20 ===
// RenderTarget2_GetInstance (was sub_4BFD20): moved to effect/RenderTarget2.cpp

// === STUB: 0x004BF780 ===
extern "C" void __cdecl sub_4BF780(int) {}

// === STUB: 0x004B6D30 ===
// RenderTarget4_GetInstance (was sub_4B6D30): moved to effect/RenderTarget34.cpp

// === STUB: 0x004B6D80 ===
extern "C" void __cdecl sub_4B6D80(int) {}

// === STUB: CEffectSystem_DestroyAllEffect ===
extern "C" int __cdecl CEffectSystem_DestroyAllEffect(void) { return 0; }

// === STUB: CEffectSystem_IsVisible ===
extern "C" void __cdecl CEffectSystem_IsVisible(int) {}

// === STUB: 0x0041ED00 ===
extern "C" void __cdecl sub_41ED00(int) {}

// === STUB: 0x0053C440 - 视频播放初始化 ===
// sub_53C440: moved to ScreenMode.cpp

// === STUB: 0x0053C720 - 获取视频高度 ===
// sub_53C720: moved to ScreenMode.cpp

// === STUB: 0x0053C710 - 获取视频宽度 ===
// sub_53C710: moved to ScreenMode.cpp

// === STUB: 0x0053C6F0 - 设置视频位置 ===
// sub_53C6F0: moved to ScreenMode.cpp

// === STUB: 0x0053C5A0 - 开始视频播放 ===
extern "C" void __cdecl sub_53C5A0(int) {}

// === STUB: 0x0041BE80 - Camera 构造 ===
extern "C" void __cdecl sub_41BE80(int) {}

// === STUB: 0x0041CA90 - Camera::SetDimention ===
extern "C" void __cdecl sub_41CA90(int, int) {}

// === STUB: 0x0041D100 - Camera 设置 ===
extern "C" void __cdecl sub_41D100(int) {}

// === STUB: 0x0041C630 - Camera 模式 ===
extern "C" void __cdecl sub_41C630(int) {}

// gbGfxManager::SetClearParam — 通过 gbengine.lib 链接 (thiscall)

// === STUB: gbVolModNode::SetVolModObj ===
extern "C" void __cdecl gbVolModNode_SetVolModObj(void *, void *) {}

// === STUB: gbRefObject::Release ===
extern "C" void __cdecl gbRefObject_Release(void *) {}

// === STUB: gbLightObj::Init ===
extern "C" void __cdecl gbLightObj_Init(void *, int) {}

// === STUB: 0x005382D0 - 检查目录存在 ===
extern "C" BOOL __cdecl sub_5382D0(const char *path)
{
    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(path, &fd);
    if (h == INVALID_HANDLE_VALUE) return FALSE;
    FindClose(h);
    return (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

// ============================================================
// C++ class method stubs
// ============================================================

// PAL3 static methods (called from WinMain.cpp and PAL3.cpp)
class PAL3 {
public:
    static void __cdecl CreateGfxWindow(void);
    static void __cdecl CheckSystemRequire(HINSTANCE hInst);
    static void __cdecl CreateEffectSystem(void);
    static void __cdecl DestroyEffectSystem(void);
    static void __cdecl GetCommandLineParam(void);
    static void __cdecl Update(float dt);
    static void __cdecl Render(void);
};

// === STUB: PAL3::CreateGfxWindow ===
void __cdecl PAL3::CreateGfxWindow(void) {}

// === STUB: PAL3::CheckSystemRequire ===
void __cdecl PAL3::CheckSystemRequire(HINSTANCE hInst) {}

// PAL3::InitGFX — 已实现于 src/pal3/gamebase/PAL3.cpp

// === STUB: PAL3::CreateEffectSystem ===
void __cdecl PAL3::CreateEffectSystem(void) {}

// === STUB: PAL3::DestroyEffectSystem ===
void __cdecl PAL3::DestroyEffectSystem(void) {}

// === STUB: PAL3::GetCommandLineParam ===
void __cdecl PAL3::GetCommandLineParam(void) {}

// PAL3::Update — 已实现于 src/pal3/gamebase/PAL3.cpp

// PAL3::Render — 已实现于 src/pal3/gamebase/PAL3.cpp

// === STUB: 0x0040C960 ===
extern "C" void __cdecl sub_40C960(void) {}

// === STUB: 0x00422DF0 ===
extern "C" void __cdecl sub_422DF0(void) {}

// === STUB: TextureLib_Data::~TextureLib_Data ===
extern "C" void __cdecl TextureLib_Data_dtor(void) {}

// === STUB: PalScriptMgr::_CON_ReLoadScript ===
extern "C" void __cdecl PalScriptMgr_CON_ReLoadScript(void) {}

// === STUB: FileSysDestory ===
extern "C" void __cdecl FileSysDestory(void) {}

// thiscall method stubs for PAL3::Destroy
// CRenderTarget: moved to effect/RenderTarget.cpp
// CRenderTarget2: moved to effect/RenderTarget2.cpp
// UIQuadManager: moved to ui/UIQuadManager.cpp
class CGameData { public: void Destroy(void); int GetMode(void); char _pad[0x38D0]; };


// 0x004BDED0 (7B): mov [ecx], -1; ret
// CRenderTarget::Destroy: moved to effect/RenderTarget.cpp
// CRenderTarget2::Destroy: moved to effect/RenderTarget2.cpp
// UIQuadManager::Destroy: moved to ui/UIQuadManager.cpp
void CGameData::Destroy(void) {}
// 0x0044FF60 (7B): mov eax, [ecx+0x38CC]; ret
int CGameData::GetMode(void) { return *(int *)((char *)this + 0x38CC); }


// CCBSystem — 已移至 src/pal3/Combat/CBSystem.cpp + include/pal3/CCBSystem.h

// gbGeomNode
class gbGeomNode {
public:
    gbGeomNode();
    void LoadFromFile(const char *filename, int a, int b);
    char _data[0x118];
};

gbGeomNode::gbGeomNode() { memset(_data, 0, sizeof(_data)); }
void gbGeomNode::LoadFromFile(const char *, int, int) {}

// OpenBaseFile
class OpenBaseFile {
public:
    OpenBaseFile(void **pv);
    ~OpenBaseFile();
};

OpenBaseFile::OpenBaseFile(void **pv) {}
OpenBaseFile::~OpenBaseFile() {}

// OpenNULLFile
class OpenNULLFile {
public:
    static void *OpenNULLFile_ctor(void **pv);
};

void *OpenNULLFile::OpenNULLFile_ctor(void **pv) { return 0; }



// ============================================================
// PAL3::Update 所需的全局变量和 stub (Iteration #2)
// ============================================================

// 全局变量
extern "C" float g_fTotalTime = 0.0f;         // 0x00BFDAA0 - 累计时间
extern "C" float g_fSceneTime = 0.0f;         // 0x00BFDA5C - 场景累计时间
extern "C" float g_fEventTimer = 0.0f;         // 0x00BFDA58 - wolf/ghost 计时
extern "C" int g_nGameState = 0;             // 0x00BFDA6C - 游戏状态
// dword_BFDA30 — 定义在 PAL3.cpp             // 0x00BFDA30
extern "C" int g_pRoleSystem = 0;             // 0x00C116EC - 角色数据
extern "C" int dword_C1171C = 0;             // 0x00C1171C
extern "C" int dword_C11754 = 0;             // 0x00C11754
extern "C" int g_nGameFlags = 0;             // 0x005833BC - 标志位
// dword_5833CC — 定义在 PAL3.cpp             // 0x005833CC
extern "C" char byte_5833D0 = 0;             // 0x005833D0
extern "C" char byte_C11748 = 0;             // 0x00C11748
extern "C" char byte_C11750 = 0;             // 0x00C11750
extern "C" char byte_C11751 = 0;             // 0x00C11751
extern "C" char byte_D8C339 = 0;             // 0x00D8C339
extern "C" char byte_D924E8 = 0;             // 0x00D924E8
extern "C" short word_8ACCD8 = 0;            // 0x008ACCD8 - 按键映射表起始
// word_8ACD2A — 定义在 PAL3.cpp            // 0x008ACD2A - 按键映射表结束
// flt_C0816C — 定义在 PAL3.cpp          // 0x00C0816C - 角色位置数组
extern "C" float flt_C1096C = 0.0f;          // 0x00C1096C - 角色位置数组结束

// PAL3::Update callees - sub_ stubs
extern "C" void __cdecl sub_40C230(float) {}
extern "C" void __cdecl sub_4105B0(float) {}
extern "C" void __cdecl sub_4181E0(int) {}
extern "C" void __cdecl sub_41C280(float) {}
extern "C" void __cdecl sub_41D9A0(float) {}
extern "C" void __cdecl sub_41EB80(void) {}
extern "C" void __cdecl sub_420150(float) {}
extern "C" int __cdecl sub_421C40(int) { return 0; }
// === STUB: 0x004226F0 - GetActiveUIScene ===
// 依赖全局对象地址 (0x00C22BE8/0x00C9A04C)，需要链接时重定位
extern "C" int __cdecl sub_4226F0(void) { return 0; }
extern "C" void __cdecl sub_422E40(float) {}
extern "C" void __cdecl sub_423540(void) {}
extern "C" int __cdecl sub_44F4C0(int, int) { return 0; }
extern "C" int __cdecl sub_44FF60(void *) { return 0; }
extern "C" void __cdecl sub_4BE460(int) {}
// ScreenEffectMgr_GetInstance (was sub_4BE590): moved to effect/ScreenEffectMgr.cpp
extern "C" void __cdecl sub_4C0200(float) {}
extern "C" void __cdecl sub_4C5BB0(float) {}
extern "C" void __cdecl sub_4CDB70(float) {}
extern "C" void __cdecl sub_513060(float, int) {}
extern "C" void __cdecl sub_52B900(float) {}
extern "C" void __cdecl sub_52F350(float) {}
extern "C" void __cdecl sub_5353A0(float) {}
// sub_53D150: moved to ScreenMode.cpp
// sub_53D1A0: moved to ScreenMode.cpp
extern "C" void __cdecl sub_541590(int) {}

// GRPinput/CScreenMode/CCBStage — 已迁移到独立 .cpp 文件

extern "C" void __cdecl PAL3_IfHideFightSucceed(int) {}
extern "C" void __cdecl PAL3_EndHideFight(void) {}
extern "C" void __cdecl PAL3_EndWolf(int) {}
extern "C" int __cdecl PAL3_EntryCatchGhost(int) { return 0; }

extern "C" void __cdecl PalScriptMgr_RunSceneScript(int) {}
extern "C" int __cdecl PalScriptMgr_Destroy(int, int) { return 0; }
extern "C" int __cdecl PalScriptMgr_IfHaveScript(void) { return 0; }
extern "C" int __cdecl PalScriptMgr_CON_CloseScript(void) { return 0; }

extern "C" void __cdecl gbAudioManager_StopSoundStream(void *, int) {}
extern "C" float __cdecl gbVec3D_Length(void *) { return 0.0f; }

// ============================================================
// PAL3::Render 所需的 stub (Iteration #3)
// ============================================================
extern "C" int dword_BFDA38 = 0;             // 0x00BFDA38 - gbDropGroup*
extern "C" int dword_BFDA3C = 0;             // 0x00BFDA3C - gbDropGroup*
extern "C" char byte_BFDA40 = 0;             // 0x00BFDA40
extern "C" char byte_BFDA41 = 0;             // 0x00BFDA41
extern "C" int dword_BFDA80 = 0;             // 0x00BFDA80
extern "C" int dword_BFDA7C = 0;             // 0x00BFDA7C
extern "C" int dword_BFDA84 = 0;             // 0x00BFDA84
extern "C" int dword_BFDA34 = 0;             // 0x00BFDA34
extern "C" int dword_BFDA98 = 0;             // 0x00BFDA98
extern "C" char g_bRenderUI = 0;             // 0x005833C2
extern "C" int dword_D8E488 = 0;             // 0x00D8E488
extern "C" int dword_C12B28 = 0;             // 0x00C12B28
extern "C" int dword_C12B2C = 0;             // 0x00C12B2C
extern "C" int dword_C12B30 = 0;             // 0x00C12B30
extern "C" char unk_A3A750[64] = {0};        // 0x00A3A750 - gbMatrix4

extern "C" void __cdecl sub_40C630(void *) {}
extern "C" void __cdecl sub_40C7D0(void) {}
extern "C" void __cdecl sub_410430(void *) {}
extern "C" void __cdecl sub_41F370(void *) {}
extern "C" void __cdecl sub_4200A0(void *) {}
extern "C" void __cdecl sub_420110(void *) {}
extern "C" void __cdecl sub_421A10(int) {}
extern "C" void __cdecl sub_421C00(int) {}
extern "C" void __cdecl sub_4220A0(void *) {}
extern "C" int  __cdecl sub_4234D0(void) { return 0; }
extern "C" void __cdecl sub_44F5B0(void *) {}
extern "C" void __cdecl sub_4B6630(int) {}
extern "C" void __cdecl sub_4B6DF0(int) {}
extern "C" void __cdecl sub_4B6E20(int) {}
extern "C" void __cdecl sub_4BE4A0(int) {}
extern "C" void __cdecl sub_4BFD70(int) {}
extern "C" void __cdecl sub_4BFDD0(int) {}
extern "C" void __cdecl sub_4CDBF0(int) {}
extern "C" void __cdecl sub_4CDC20(int) {}
extern "C" void __cdecl sub_513120(void *) {}
extern "C" void __cdecl sub_52B860(int) {}
extern "C" void __cdecl sub_52F2E0(int) {}
extern "C" void __cdecl sub_535320(int) {}
extern "C" void __cdecl sub_53C990(void *) {}
// PushMatrixStacks (was sub_540F60): moved to gamebase/GfxHelper.cpp
// PopMatrixStacks (was sub_540FA0): moved to gamebase/GfxHelper.cpp

extern "C" int __cdecl PAL3_PrintScreen(void) { return 0; }
extern "C" void __cdecl UIRenderObj_UIRenderObj(int) {}

// ============================================================
// 小函数实现 (从二进制反汇编, Iteration #4)
// ============================================================

// 0x0053DF70 - CScreenMode::GetInstance (6B) — 返回静态单例地址
// 原始: mov eax, 0x017B41E8; ret — 但由于当前是 cdecl stub 返回 0，
// 保持 stub 直到有完整 CScreenMode 类型定义

// 0x004BDED0 - CRenderTarget::Destroy (7B)
// 原始: mov [ecx], 0xFFFFFFFF; ret → this->m_state = -1;
// 当前作为 extern "C" void 在 globals.cpp 中，需改为 thiscall 类方法

// 原始: mov eax, [ecx+0x328]; ret → return this->m_pAudioMgr;

// 0x0044FF60 - CGameData::GetMode (7B)
// 原始: mov eax, [ecx+0x38CC]; ret → return this->m_nMode;

// 0x004022B0 - GRPinput::SetMode (10B)
// 原始: mov eax,[esp+4]; mov [ecx+0xC],eax; ret 4 → this->m_mode = arg;

// 原始: mov eax,[esp+4]; mov [ecx+0x1224],eax; ret 4 → this->m_state = arg;

// === STUB: 0x005694F0 - gbGfxManager_D3D internal method ===
extern "C" int __cdecl sub_5694F0(void *pThis, int a, int b, int c, int d) { return 0; }

// === STUB: 0x0053E740 - Audio fade implementation ===
extern "C" void __cdecl sub_53E740(int *, const char *, int *) {}
extern "C" char byte_56A634[] = "";
// === STUB: 0x0053D030 - LogMessage ===
void __cdecl sub_53D030(const char *, ...) {}
