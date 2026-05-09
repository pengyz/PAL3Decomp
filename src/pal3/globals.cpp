// PAL3.exe globals.cpp - Global variables, string constants, and function stubs
// This file provides definitions for all symbols referenced by decompiled code
// that don't yet have their own implementation file.

#include <windows.h>
#include "pal3/pal3_globals.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

// ============================================================
// Global variables
// ============================================================

char Data[260] = {0};            // 0x01894970 - CD drive path buffer
char Filename[260] = {0};        // 0x01894A74 - exe path buffer
double dbl_1895070 = 0.0;        // 0x01895070 - last frame time
DWORD g_bGameActive = 0;          // 0x005833B8 - game active flag
HINSTANCE hInstance = 0;         // 0x00BFDA48
char WindowName[32] = "PAL3--SOFTSTAR.sh";  // 0x005839C4
HWND hWnd = 0;                   // 0x00BFDA4C
HWND hWndParent = 0;             // 0x00BFDA50
int xRight = 0;                  // 0x00BFDA54
int yBottom = 0;                 // 0x00BFDA58
int g_hCursor = 0;            // 0x00BFDA94
void *g_pCBSystem = 0;         // 0x00BFDA74 - CCBSystem instance
int g_pSceneMgr = 0;            // 0x00BFDA78 - scene manager
gbGfxManager *g_pGfxManager = 0;            // 0x00BFDA60 - gbGfxManager
void *g_pCamera = 0;            // 0x00BFDA68
char byte_BFDA90 = 0;            // 0x00BFDA90
char byte_5833C0 = 0;            // 0x005833C0
int g_GDB = 0;            // 0x00975ED8
int g_UIManager = 0;            // 0x00C11758
char g_Logger = 0;           // 0x17B1EC0
int g_pCursorNode1 = 0;            // 0x00A3A6EC
int g_pCursorNode2 = 0;            // 0x00A3A6F0
void *unk_A3A7D8 = 0;           // 0x00A3A7D8
#include "pal3/GRPinput.h"
GRPinput g_Input;
void *off_56A66C = 0;            // 0x0056A66C - vtable pointer
void *g_pActorMgr = 0;            // 0x00BFDA64 - gbActorMgr*
CGameData g_GameData;            // 0x00DB9FD0

// ============================================================
// String constants (IDA-named, from .rdata/.data sections)
// ============================================================

const char aSoftwareSoftst_1[] = "software\\softstar\\pal3";
const char aCdriver[]           = "CDriver";
const char asc_5D41EC[]         = "\\";
const char aPal3[]              = "Pal3";
const char aPercentSMovie[]     = "%sMovie";
const char aPlsInsertDisc[]     = "Please Insert Disc4 to Dirver %c:";
const char aDatascriptComb[]    = "data\\script\\combat";
const char aDatascriptLang[]    = "data\\script\\language";
const char aAppname[]           = "PAL3";
const char aInputDeviceCre[]    = "Input Device Create Failed!";
const char aDProjectPal3Ga_0[]  = "D:\\project\\pal3\\gamebase\\PAL3.cpp";
const char aFightDatabaseL[]    = "Fight Database Load Error!!";
const char aCouldNotAlloca[]    = "Could not allocate CCBSystem";
const char aCouldNotAlloca_0[]  = "Could not allocate CSceneMgr";
const char aAssislangLang[]     = "assislang\\lang";
const char aSBulidSS[]          = "%s Bulid: %s";
const char aV104[]              = "V1.04";
const char aGameCreateOk[]      = "Game Create OK ...";
const char aObjectG02Cvd[]      = "object\\g02.cvd";
const char aObjectG03Cvd[]      = "object\\g03.cvd";
const char aMovieLogoBik[]      = "Movie\\logo.bik";
const char aCreateGfxManag[]    = "Create GfxManager Failed!";
const char aCreateActorman[]    = "Create ActorManager Failed!";
const char aCNewFailed[]        = "C++ new Failed!";

// InitGFX globals
int dword_BFD6C8 = 0;            // 0x00BFD6C8 - gbGfxDriverInfo
void *off_56A694 = 0;             // 0x0056A694 - gbVolumeModifier vtable
char unk_A3A6F8 = 0;             // 0x00A3A6F8 - gbVolModNode

// Forward declarations
extern "C" FILE *__cdecl LogMessage(const char *, ...);
extern "C" char *__cdecl LoggerWrite(char *, const char *, ...);

// ============================================================
// Function stubs (callees of PAL3::Create and WinMain)
// These will be replaced with real implementations as BFS expands.
// ============================================================

// 0x0053CF80 - InitLogFiles (174B)
// Opens Pal3Log.txt + EngineLog.txt, writes header with timestamp
const char aWt[] = "wt";
const char aEnginelogTxt[] = "EngineLog.txt";

extern "C" FILE *__cdecl InitLogFiles(void)
{
    FILE *pPal3Log;
    FILE *pEngineLog;
    char szFilename[512];

    pPal3Log = fopen("Pal3Log.txt", aWt);
    pEngineLog = fopen(aEnginelogTxt, aWt);
    if (pPal3Log)
    {
        if (pEngineLog)
        {
            GetModuleFileNameA(0, szFilename, 0x200u);
            fprintf(pPal3Log, "[%s Log at ", szFilename);
            _strdate(szFilename);
            fprintf(pPal3Log, szFilename);
            _strtime(szFilename);
            fprintf(pPal3Log, " %s]\r\n\r\n", szFilename);
            fclose(pPal3Log);
            fprintf(pEngineLog, "Log At:%s\r\n", szFilename);
            return (FILE *)fclose(pEngineLog);
        }
    }
    return pEngineLog;
}

// === STUB: 0x00??????  - FileSysInit ===
extern "C" void __cdecl FileSysInit(void) {}

extern "C" void __cdecl sub_41EFA0(void) {}

extern "C" void __cdecl sub_4318B0(const char *) {}

extern "C" void __cdecl sub_430290(const char *) {}

extern "C" void __cdecl sub_430570(const char *) {}

// 0x0053DF70 - CScreenMode::GetInstance (6B, matched)
// asm: B8 xx xx xx xx C3 = mov eax, &g_ScreenMode; ret

// asm: 8B 44 24 04; 89 81 24 12 00 00; C2 04 00

// asm: 8B 81 28 03 00 00; C3


// C linkage wrappers (PAL3::Update calls these by extern "C" name)

// === STUB: 0x0053DD70 - CScreenMode::SetMode ===




extern "C" void __cdecl sub_53C340(int a, int b) {}

extern "C" void __cdecl sub_41C1B0(int *v) {}

// === STUB: 0x00??????  - PAL_GDB_PAL_GDB ===
extern "C" int __cdecl PAL_GDB_PAL_GDB(void *) { return 1; }

extern "C" void __cdecl sub_457410(const char *) {}

extern "C" void __cdecl sub_408BE0(void) {}

// UIQuadManager_GetInstance (was sub_5415F0): moved to ui/UIQuadManager.cpp

// === STUB: UIRenderQuadList ===
extern "C" void __cdecl UIRenderQuadList(int) {}

extern "C" void __cdecl sub_41F5E0(void *) {}

// 0x0053CE90 - LoggerRegisterCallbacks (47B)
// Registers two log output callbacks: screen display + file output
extern "C" int __cdecl LoggerRegisterCB(int *, int, char *, char *);
#define sub_53CC10(a,b,c,d) LoggerRegisterCB(a,b,(char*)(c),(char*)(d))
extern "C" void __cdecl sub_423500(void);
extern "C" char *__cdecl DebugPrintRoleStats(char *);
#define sub_53CE20 ((void (__cdecl *)(void))DebugPrintRoleStats)
const char aKm[] = "KM";
const char aFv[] = "FV";
char byte_608944;
char byte_608930;

extern "C" int __cdecl LoggerRegisterCallbacks(int *pLogger)
{
    sub_53CC10(pLogger, (int)sub_423500, aKm, &byte_608944);
    return sub_53CC10(pLogger, (int)sub_53CE20, aFv, &byte_608930);
}

// 0x0053CC10 - Logger::RegisterCallback (92B)
// Logger callback entry layout (136 bytes each):
//   +0x00: char szName[32]
//   +0x20: char szDesc[100]
//   +0x84: int pfnCallback
// Logger header: this[0] = nCount (max 34), entries at this+4

#define LOGGER_MAX_CALLBACKS  34
#define LOGGER_CB_ENTRY_SIZE  136
#define LOGGER_CB_NAME_MAX    0x20
#define LOGGER_CB_DESC_MAX    0x64
#define LOGGER_CB_FUNC_OFFSET 132

const char aConsoleErrorCo[] = "Console Error: command overflow";

extern "C" int __cdecl LoggerRegisterCB(int *pLogger, int pfnCallback, char *pName, char *pDesc)
{
    int nCount = *pLogger;
    if (nCount >= LOGGER_MAX_CALLBACKS)
        return (int)LoggerWrite((char *)pLogger, aConsoleErrorCo);

    char *pEntry = (char *)(pLogger + LOGGER_MAX_CALLBACKS * nCount + 1);
    *(int *)(pEntry + LOGGER_CB_FUNC_OFFSET) = pfnCallback;
    strncpy(pEntry, pName, LOGGER_CB_NAME_MAX);
    strncpy(pEntry + LOGGER_CB_NAME_MAX, pDesc, LOGGER_CB_DESC_MAX);
    *pLogger = nCount + 1;
    return nCount + 1;
}
// === STUB: sub_423500 - ScreenLogCallback ===
void __cdecl sub_423500(void) {}
// 0x0053CE20 - FileLogCallback / DebugPrintRoleStats (105B)
// Prints all 5 role stat values to logger
const char aXuejian[] = "XueJian";
const char aLongkui[] = "LongKui";
const char aZixuan[] = "ZiXuan";
const char aChangqing[] = "ChangQing";
const char aHuaying[] = "HuaYing";
int dword_C04338[5];

extern "C" char *__cdecl DebugPrintRoleStats(char *pArg)
{
    char *result = pArg;
    const char *roleNames[5];
    int i;

    roleNames[0] = aXuejian;
    roleNames[1] = aLongkui;
    roleNames[2] = aZixuan;
    roleNames[3] = aChangqing;
    roleNames[4] = aHuaying;

    if (!pArg)
    {
        for (i = 0; i < 5; ++i)
            result = LoggerWrite(&g_Logger, "%s = %d", roleNames[i], dword_C04338[i]);
    }
    return result;
}


// 0x0053CC70 - Logger::Write (128B)
//   +0x1294 (4756): log scroll buffer destination (1600 bytes = 0x640)
//   +0x12F8 (4856): log scroll buffer source
//   +0x18D4 (6356): current log line (99 chars max)
#define LOGGER_SCROLL_DST   4756
#define LOGGER_SCROLL_SRC   4856
#define LOGGER_SCROLL_SIZE  0x640
#define LOGGER_CURLINE      6356
#define LOGGER_CURLINE_MAX  0x63

static char Source[1024];
char byte_17B1D23[];

extern "C" char *__cdecl LoggerWrite(char *pLogger, const char *pFormat, ...)
{
    va_list va;
    va_start(va, pFormat);
    vsprintf(Source, pFormat, va);
    va_end(va);

    memcpy(pLogger + LOGGER_SCROLL_DST, pLogger + LOGGER_SCROLL_SRC, LOGGER_SCROLL_SIZE);
    strncpy(pLogger + LOGGER_CURLINE, Source, LOGGER_CURLINE_MAX);

    if ((int)(strlen(Source) - 99) > 0)
    {
        memcpy(pLogger + LOGGER_SCROLL_DST, pLogger + LOGGER_SCROLL_SRC, LOGGER_SCROLL_SIZE);
        return strncpy(pLogger + LOGGER_CURLINE, byte_17B1D23, LOGGER_CURLINE_MAX);
    }
    return 0;
}

// === STUB: byte_17B1D23 (truncation marker) ===
char byte_17B1D23[100] = {0};

// 0x0053CEF0 - FormatExceptionMessage (61B)
// Formats "file(line):msg" into 1024-byte buffer, then logs it
const char aExceptionS[] = "Exception: %s";

extern "C" char *__cdecl FormatExceptionMessage(char *pBuf, const char *pMsg, const char *pFile, int nLine)
{
    pBuf[1023] = 0;
    _snprintf(pBuf, 0x400u, "%s(%d):%s", pFile, nLine, pMsg);
    LogMessage(aExceptionS, pBuf);
    return pBuf;
}

extern "C" void *__cdecl sub_512500(void *mem) { return mem; }

// === STUB: CCBSystem_ProcNormalAttack ===
extern "C" void __cdecl CCBSystem_ProcNormalAttack(void *) {}

extern "C" int __cdecl sub_4CDA10(int a, int b, int c) { return 0; }

extern "C" void __cdecl sub_44F130(void *) {}

extern "C" void __cdecl sub_44F610(int) {}

// === STUB: 0x004BDB10 - CRenderTarget::GetInstance ===
// RenderTarget_GetInstance (was sub_4BDB10): moved to effect/RenderTarget.cpp

// === STUB: RenderTarget_Create ===
extern "C" void __cdecl RenderTarget_Create(int) {}

// === STUB: 0x004B65A0 ===
// RenderTarget3_GetInstance (was sub_4B65A0): moved to effect/RenderTarget34.cpp

// === STUB: 0x004B65F0 ===
// RenderTarget3_Init (was sub_4B65F0): moved to gamebase/GfxHelper.cpp
const char aGfxscriptGlowG[] = "gfxscript\\glow.gfx";
const char aGfxscriptGeomG[] = "gfxscript\\geom.gfx";

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

// sub_53C440: moved to ScreenMode.cpp

// sub_53C720: moved to ScreenMode.cpp

// sub_53C710: moved to ScreenMode.cpp

// sub_53C6F0: moved to ScreenMode.cpp

extern "C" void __cdecl sub_53C5A0(int) {}

extern "C" void __cdecl sub_41BE80(int) {}

// === STUB: 0x0041CA90 - Camera::SetDimention ===
// 0x0041CA90 - CameraCtrl::SetDimention (34B)
// Sets resolution on camera controller and its embedded gbCamera
// CameraCtrl layout: +0x04 = gbCamera, +0x1D8 = nWidth, +0x1DC = nHeight
#define CAMERACTRL_CAMERA_OFFSET   4
#define CAMERACTRL_WIDTH_OFFSET    472
#define CAMERACTRL_HEIGHT_OFFSET   476

struct gbVec3D;

class gbCamera {
public:
    void SetDimention(int nWidth, int nHeight);
    void SetLookAt(struct gbVec3D *pTarget, struct gbVec3D *pEye, struct gbVec3D *pUp);
    void SetAsCurrent(int nFlags);
};

extern "C" void __cdecl CameraCtrl_SetDimention(int nWidth, int nHeight)
{
    // ecx (this) comes from prior call - use g_pCamera as the controller
    char *pThis = (char *)g_pCamera;
    *(int *)(pThis + CAMERACTRL_WIDTH_OFFSET) = nWidth;
    *(int *)(pThis + CAMERACTRL_HEIGHT_OFFSET) = nHeight;
    ((gbCamera *)(pThis + CAMERACTRL_CAMERA_OFFSET))->SetDimention(nWidth, nHeight);
}

extern "C" void __cdecl sub_41D100(int) {}

// 0x0041C630 - CameraCtrl::SetAsCurrent (58B)
// CameraCtrl extended layout:
//   +0x1E0: gbVec3D m_vEyePos
//   +0x1EC: gbVec3D m_vLookAt
//   +0x204: gbVec3D m_vUpVec
#define CAMERACTRL_EYE_OFFSET    480
#define CAMERACTRL_LOOKAT_OFFSET 492
#define CAMERACTRL_UP_OFFSET     516

struct gbVec3D { float x, y, z; };

extern "C" void __cdecl CameraCtrl_SetAsCurrent(int nFlags)
{
    char *pThis = (char *)g_pCamera;
    gbCamera *pCam = (gbCamera *)(pThis + CAMERACTRL_CAMERA_OFFSET);

    if ((nFlags & 2) != 0)
        pCam->SetLookAt((gbVec3D *)(pThis + CAMERACTRL_LOOKAT_OFFSET),
                        (gbVec3D *)(pThis + CAMERACTRL_EYE_OFFSET),
                        (gbVec3D *)(pThis + CAMERACTRL_UP_OFFSET));
    pCam->SetAsCurrent(nFlags);
}


// === STUB: gbVolModNode::SetVolModObj ===
extern "C" void __cdecl gbVolModNode_SetVolModObj(void *, void *) {}

// === STUB: gbRefObject::Release ===
extern "C" void __cdecl gbRefObject_Release(void *) {}

// === STUB: gbLightObj::Init ===
extern "C" void __cdecl gbLightObj_Init(void *, int) {}

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

// PAL3:: class methods: all in src/pal3/gamebase/PAL3.cpp

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


// 0x004BDED0 (7B): mov [ecx], -1; ret
// CRenderTarget::Destroy: moved to effect/RenderTarget.cpp
// CRenderTarget2::Destroy: moved to effect/RenderTarget2.cpp
// UIQuadManager::Destroy: moved to ui/UIQuadManager.cpp
void CGameData::Destroy(void) {}
// 0x0044FF60 (7B): mov eax, [ecx+0x38CC]; ret
int CGameData::GetMode(void) { return *(int *)((char *)this + 0x38CC); }



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
// ============================================================

float g_fTotalTime = 0.0f;
float g_fSceneTime = 0.0f;
float g_fEventTimer = 0.0f;
int g_nGameState = 0;
int g_pRoleSystem = 0;
int dword_C1171C = 0;             // 0x00C1171C
int dword_C11754 = 0;             // 0x00C11754
int g_nGameFlags = 0;
char byte_5833D0 = 0;             // 0x005833D0
char byte_C11748 = 0;             // 0x00C11748
char byte_C11750 = 0;             // 0x00C11750
char byte_C11751 = 0;             // 0x00C11751
char byte_D8C339 = 0;             // 0x00D8C339
char byte_D924E8 = 0;             // 0x00D924E8
short word_8ACCD8 = 0;
float flt_C1096C = 0.0f;

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
// ============================================================
int dword_BFDA38 = 0;             // 0x00BFDA38 - gbDropGroup*
int dword_BFDA3C = 0;             // 0x00BFDA3C - gbDropGroup*
char byte_BFDA40 = 0;             // 0x00BFDA40
char byte_BFDA41 = 0;             // 0x00BFDA41
int dword_BFDA80 = 0;             // 0x00BFDA80
int dword_BFDA7C = 0;             // 0x00BFDA7C
int dword_BFDA84 = 0;             // 0x00BFDA84
int dword_BFDA34 = 0;             // 0x00BFDA34
int dword_BFDA98 = 0;             // 0x00BFDA98
char g_bRenderUI = 0;             // 0x005833C2
int dword_D8E488 = 0;             // 0x00D8E488
int dword_C12B28 = 0;             // 0x00C12B28
int dword_C12B2C = 0;             // 0x00C12B2C
int dword_C12B30 = 0;             // 0x00C12B30
char unk_A3A750[64] = {0};        // 0x00A3A750 - gbMatrix4

extern "C" void __cdecl sub_40C630(void *) {}
extern "C" void __cdecl sub_40C7D0(void) {}
// 0x00410430 - NPCAnimCheck (54B)
// Checks combat state and calls anim update if needed
int dword_C025EC;
int dword_C083D8;
extern "C" int __cdecl sub_412400(int, int);

extern "C" int __cdecl NPCAnimCheck(int nParam)
{
    if (dword_C025EC != 10)
        return sub_412400(nParam, 0);
    if (dword_C083D8)
        return sub_412400(nParam, 0);
    return dword_C083D8;
}

int __cdecl sub_412400(int, int) { return 0; }
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
// 0x0052F2E0 - MiniGame2::Destroy (28B)
// Destroys 3 sub-objects via this[0], this[3], this[4]
struct MiniGame2State {
    int m_pSubObj0;     // [0]
    int m_nUnk1;        // [1]
    int m_nUnk2;        // [2]
    int m_pSubObj3;     // [3]
    int m_pSubObj4;     // [4]
};

extern "C" void __cdecl sub_530C70(int);
extern "C" void __cdecl sub_530350(int);
extern "C" int  __cdecl sub_52FC60(int);

extern "C" int __cdecl MiniGame2_Destroy(MiniGame2State *pThis)
{
    sub_530C70(pThis->m_pSubObj0);
    sub_530350(pThis->m_pSubObj3);
    return sub_52FC60(pThis->m_pSubObj4);
}

// === STUB: MiniGame2 sub-object destructors ===
void __cdecl sub_530C70(int) {}
void __cdecl sub_530350(int) {}
int  __cdecl sub_52FC60(int) { return 0; }
extern "C" void __cdecl sub_535320(int) {}
extern "C" void __cdecl sub_53C990(void *) {}
// PushMatrixStacks (was sub_540F60): moved to gamebase/GfxHelper.cpp
// PopMatrixStacks (was sub_540FA0): moved to gamebase/GfxHelper.cpp

extern "C" int __cdecl PAL3_PrintScreen(void) { return 0; }
extern "C" void __cdecl UIRenderObj_UIRenderObj(int) {}

// ============================================================
// ============================================================


// 0x004BDED0 - CRenderTarget::Destroy (7B)


// 0x0044FF60 - CGameData::GetMode (7B)

// 0x004022B0 - GRPinput::SetMode (10B)


// === STUB: 0x005694F0 - gbGfxManager_D3D internal method ===
extern "C" int __cdecl sub_5694F0(void *pThis, int a, int b, int c, int d) { return 0; }

// === STUB: 0x0053E740 - Audio fade implementation ===
extern "C" void __cdecl sub_53E740(int *, const char *, int *) {}
char byte_56A634[] = "";
// 0x0053D030 - LogMessage (67B)
// Formats message and appends to Pal3Log.txt
static char s_LogBuffer[1024];
const char aAt[] = "at";

extern "C" FILE *__cdecl LogMessage(const char *pFormat, ...)
{
    FILE *pFile;
    va_list va;

    va_start(va, pFormat);
    vsprintf(s_LogBuffer, pFormat, va);
    va_end(va);

    pFile = fopen("Pal3Log.txt", aAt);
    if (pFile)
    {
        fprintf(pFile, s_LogBuffer);
        return (FILE *)fclose(pFile);
    }
    return pFile;
}

// === STUB: 0x00432770 - ScriptSystem::SetVariable ===
extern "C" void __cdecl sub_432770(void *, int, int) {}
