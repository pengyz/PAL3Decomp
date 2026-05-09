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
extern "C" char byte_17B1EC0 = 0;           // 0x17B1EC0
extern "C" int dword_A3A6EC = 0;            // 0x00A3A6EC
extern "C" int dword_A3A6F0 = 0;            // 0x00A3A6F0
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

// === STUB: 0x0053DF70 - CScreenMode::GetInstance ===
extern "C" int __cdecl sub_53DF70(void) { return 0; }

// === STUB: 0x0053DD70 - CScreenMode::SetMode ===
extern "C" void __cdecl sub_53DD70(int) {}

// === STUB: 0x004020E0 - DirectInput初始化 ===
extern "C" int __cdecl sub_4020E0(void *ppv, HINSTANCE hInst, HWND hwnd, int flag) { return 1; }

// === STUB: 0x00402270 - 设置输入范围 ===
extern "C" void __cdecl sub_402270(void *ppv, int a, int b, int c, int d) {}

// === STUB: 0x004022B0 - 设置输入模式 ===
extern "C" void __cdecl sub_4022B0(void *ppv, int mode) {}

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
extern "C" int __cdecl sub_5415F0(void) { return 0; }

// === STUB: UIRenderQuadList ===
extern "C" void __cdecl UIRenderQuadList(int) {}

// === STUB: 0x0041F5E0 - 未知初始化(C11758相关) ===
extern "C" void __cdecl sub_41F5E0(void *) {}

// === STUB: 0x0053CE90 - 日志初始化 ===
extern "C" void __cdecl sub_53CE90(void *) {}

// === STUB: 0x0053CC70 - 日志写入 ===
extern "C" void __cdecl sub_53CC70(void *, const char *, const char *) {}

// === STUB: 0x0053CEF0 - 格式化异常消息 ===
extern "C" const char *__cdecl sub_53CEF0(char *buf, const char *msg, const char *file, int line)
{
    if (buf) {
        sprintf(buf, "%s (%s:%d)", msg ? msg : "", file ? file : "", line);
    }
    return buf;
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
extern "C" int __cdecl sub_4BDB10(void) { return 0; }

// === STUB: RenderTarget_Create ===
extern "C" void __cdecl RenderTarget_Create(int) {}

// === STUB: 0x004B65A0 ===
extern "C" int __cdecl sub_4B65A0(void) { return 0; }

// === STUB: 0x004B65F0 ===
extern "C" void __cdecl sub_4B65F0(int) {}

// === STUB: 0x004BFD20 ===
extern "C" int __cdecl sub_4BFD20(void) { return 0; }

// === STUB: 0x004BF780 ===
extern "C" void __cdecl sub_4BF780(int) {}

// === STUB: 0x004B6D30 ===
extern "C" int __cdecl sub_4B6D30(void) { return 0; }

// === STUB: 0x004B6D80 ===
extern "C" void __cdecl sub_4B6D80(int) {}

// === STUB: CEffectSystem_DestroyAllEffect ===
extern "C" int __cdecl CEffectSystem_DestroyAllEffect(void) { return 0; }

// === STUB: CEffectSystem_IsVisible ===
extern "C" void __cdecl CEffectSystem_IsVisible(int) {}

// === STUB: 0x0041ED00 ===
extern "C" void __cdecl sub_41ED00(int) {}

// === STUB: 0x0053C440 - 视频播放初始化 ===
extern "C" void __cdecl sub_53C440(const char *, HWND, int, int) {}

// === STUB: 0x0053C720 - 获取视频高度 ===
extern "C" int __cdecl sub_53C720(void *) { return 480; }

// === STUB: 0x0053C710 - 获取视频宽度 ===
extern "C" int __cdecl sub_53C710(void *) { return 640; }

// === STUB: 0x0053C6F0 - 设置视频位置 ===
extern "C" void __cdecl sub_53C6F0(int, int) {}

// === STUB: 0x0053C5A0 - 开始视频播放 ===
extern "C" void __cdecl sub_53C5A0(int) {}

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
    static void __cdecl InitGFX(HINSTANCE hInst);
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

// === STUB: PAL3::InitGFX ===
void __cdecl PAL3::InitGFX(HINSTANCE hInst) {}

// === STUB: PAL3::CreateEffectSystem ===
void __cdecl PAL3::CreateEffectSystem(void) {}

// === STUB: PAL3::DestroyEffectSystem ===
void __cdecl PAL3::DestroyEffectSystem(void) {}

// === STUB: PAL3::GetCommandLineParam ===
void __cdecl PAL3::GetCommandLineParam(void) {}

// === STUB: PAL3::Update (0x004055D0) ===
void __cdecl PAL3::Update(float dt) {}

// === STUB: PAL3::Render (0x00405C00) ===
void __cdecl PAL3::Render(void) {}

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
class CRenderTarget { public: void Destroy(void); };
class CRenderTarget2 { public: void Destroy(void); };
class UIQuadManager { public: void Destroy(void); };
class CGameData { public: void Destroy(void); };
class CScreenMode { public: void Restore(void); };

void CRenderTarget::Destroy(void) {}
void CRenderTarget2::Destroy(void) {}
void UIQuadManager::Destroy(void) {}
void CGameData::Destroy(void) {}
void CScreenMode::Restore(void) {}

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

// CCBStage::ProcUseItem - called from CBSystem.cpp
class CCBStage {
public:
    unsigned long ProcUseItem(unsigned long hwnd);
};

unsigned long CCBStage::ProcUseItem(unsigned long hwnd) { return 1; }

