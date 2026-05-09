// PAL3.exe PAL3::Create - Matching Decompilation
// Address: 0x00404800, Size: 1331 bytes
// Compiler: MSVC 7.1, /O2 /Oy /EHsc (FPO + C++ EH, no ebp frame)
// Calling convention: static void __cdecl PAL3::Create(HINSTANCE)
// EH: 5 unwind states, 0 try blocks (RAII destructors only)
//
// This is the core game initialization function called from WinMain.
// It initializes all subsystems: filesystem, graphics, input, scripts,
// game database, scene manager, render targets, and plays logo video.

#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <new>

// ============================================================
// Class forward declarations
// ============================================================

class PAL3 {
public:
    static void __cdecl Create(HINSTANCE hInst);
    static void __cdecl CreateGfxWindow(void);
    static void __cdecl CheckSystemRequire(HINSTANCE hInst);
    static void __cdecl InitGFX(HINSTANCE hInst);
    static void __cdecl CreateEffectSystem(void);
    static void __cdecl GetCommandLineParam(void);
};

class _Exception {
public:
    char data[1024];
};

class gbGeomNode {
public:
    gbGeomNode();
    void LoadFromFile(const char *filename, int a, int b);
    char _data[0x118];
};

class OpenBaseFile {
public:
    OpenBaseFile(void **pv);
    ~OpenBaseFile();
};

class OpenNULLFile {
public:
    static void *OpenNULLFile_ctor(void **pv);
};

// ============================================================
// External functions (called from PAL3::Create)
// ============================================================
extern "C" void __cdecl sub_53CF80(void);
extern "C" void __cdecl FileSysInit(void);
__declspec(dllimport) void __cdecl gbTimeCounterInit(void);

extern "C" void __cdecl sub_41EFA0(void);
extern "C" void __cdecl sub_4318B0(const char *);
extern "C" void __cdecl sub_430290(const char *);
extern "C" void __cdecl sub_430570(const char *);
extern "C" int  __cdecl sub_53DF70(void);
extern "C" void __cdecl sub_53DD70(int);
extern "C" int  __cdecl sub_4020E0(void *ppvOut, HINSTANCE hInst, HWND hwnd, int flag);
extern "C" void __cdecl sub_402270(void *ppvOut, int a, int b, int c, int d);
extern "C" void __cdecl sub_4022B0(void *ppvOut, int mode);
extern "C" void __cdecl sub_53C340(int a, int b);
extern "C" void __cdecl sub_41C1B0(int *v);
extern "C" int  __cdecl PAL_GDB_PAL_GDB(void *);
extern "C" void __cdecl sub_457410(const char *);
extern "C" void __cdecl sub_408BE0(void);
extern "C" int  __cdecl sub_5415F0(void);
extern "C" void __cdecl UIRenderQuadList(int);
extern "C" void __cdecl sub_41F5E0(void *);
extern "C" void __cdecl sub_53CE90(void *);
extern "C" void __cdecl sub_53CC70(void *, const char *, const char *);
extern "C" void *__cdecl sub_512500(void *);
extern "C" void __cdecl CCBSystem_ProcNormalAttack(void *);
extern "C" int  __cdecl sub_4CDA10(int, int, int);
extern "C" void __cdecl sub_44F130(void *);
extern "C" void __cdecl sub_44F610(int);
extern "C" int  __cdecl sub_4BDB10(void);
extern "C" void __cdecl RenderTarget_Create(int);
extern "C" int  __cdecl sub_4B65A0(void);
extern "C" void __cdecl sub_4B65F0(int);
extern "C" int  __cdecl sub_4BFD20(void);
extern "C" void __cdecl sub_4BF780(int);
extern "C" int  __cdecl sub_4B6D30(void);
extern "C" void __cdecl sub_4B6D80(int);
extern "C" int  __cdecl CEffectSystem_DestroyAllEffect(void);
extern "C" void __cdecl CEffectSystem_IsVisible(int);
extern "C" void __cdecl sub_41ED00(int);
extern "C" void __cdecl sub_53C440(const char *, HWND, int, int);
extern "C" int  __cdecl sub_53C720(void *);
extern "C" int  __cdecl sub_53C710(void *);
extern "C" void __cdecl sub_53C6F0(int, int);
extern "C" void __cdecl sub_53C5A0(int);
extern "C" const char *__cdecl sub_53CEF0(char *buf, const char *msg, const char *file, int line);

// ============================================================
// Global variables
// ============================================================
extern "C" HWND hWnd;
extern "C" HWND hWndParent;
extern "C" int xRight;
extern "C" int yBottom;
extern "C" int dword_BFDA94;
extern "C" void *dword_BFDA74;
extern "C" int dword_BFDA78;
extern "C" int dword_BFDA60;
extern "C" int dword_BFDA68;
extern "C" char byte_BFDA90;
extern "C" char byte_BFDA91;
extern "C" char byte_5833C0;
extern "C" int dword_975ED8;
extern "C" int dword_C11758;
extern "C" char byte_17B1EC0;
extern "C" int dword_A3A6EC;
extern "C" int dword_A3A6F0;
extern "C" void *unk_A3A7D8;
extern "C" void *ppvOut;

// String constants
extern "C" const char aDatascriptComb[];
extern "C" const char aDatascriptLang[];
extern "C" const char aAppname[];
extern "C" const char aInputDeviceCre[];
extern "C" const char aDProjectPal3Ga_0[];
extern "C" const char aFightDatabaseL[];
extern "C" const char aCouldNotAlloca[];
extern "C" const char aCouldNotAlloca_0[];
extern "C" const char aAssislangLang[];
extern "C" const char aSBulidSS[];
extern "C" const char aV104[];
extern "C" const char aGameCreateOk[];
extern "C" const char aObjectG02Cvd[];
extern "C" const char aObjectG03Cvd[];
extern "C" const char aMovieLogoBik[];

extern "C" void *off_56A66C;

// ========================================================================
// PAL3::Create implementation
// This follows the IDA decompilation output structure faithfully.
// ========================================================================
void __cdecl PAL3::Create(HINSTANCE hInstance)
{
    int screenMode;
    HCURSOR hCursor;
    HWND hwnd;
    int uiQuadList;
    void *pCBSystemMem;
    void *pCBSystem;
    int pSceneCam;
    int pSceneMgr;
    int rt0, rt1, rt2, rt3, rt4, rt5, rt6, rt7, rt8, rt9;
    gbGeomNode *pCursorNode, *pCursorNodeInit;
    void *pCursor2Mem, *pCursor2Init;
    int videoWidth;
    _Exception pExceptionObject;
    char ehState[24];
    int hwCaps;
    char ArgList[1024];
    void *pFileSystem;
    int inputState[3];
    void *pSceneMem;

    PAL3::CreateGfxWindow();
    sub_53CF80();
    FileSysInit();
    gbTimeCounterInit();
    PAL3::CheckSystemRequire(hInstance);
    PAL3::InitGFX(hInstance);
    PAL3::CreateEffectSystem();

    // Script system initialization
    sub_41EFA0();
    sub_4318B0(aDatascriptComb);
    sub_430290(aDatascriptLang);
    sub_430570(aAppname);

    screenMode = sub_53DF70();
    sub_53DD70(screenMode);

    hCursor = LoadCursorA(hInstance, MAKEINTRESOURCEA(0x73));
    hwnd = hWnd;
    dword_BFDA94 = (int)hCursor;
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hwnd);

    // DirectInput initialization
    if (!sub_4020E0(&ppvOut, hInstance, (HWND)(int)hwnd, 0))
    {
        memcpy(&pExceptionObject,
            sub_53CEF0(ArgList, aInputDeviceCre, aDProjectPal3Ga_0, 180),
            sizeof(pExceptionObject));
        throw pExceptionObject;
    }

    sub_402270(&ppvOut, 0, 0, xRight, yBottom);
    sub_4022B0(&ppvOut, 0x40000000);
    sub_53C340(0, 1);

    memset(inputState, 0, sizeof(inputState));
    sub_41C1B0(inputState);

    // Game database initialization
    if (!(unsigned char)PAL_GDB_PAL_GDB(&dword_975ED8))
    {
        memcpy(&pExceptionObject,
            sub_53CEF0(ArgList, aFightDatabaseL, aDProjectPal3Ga_0, 191),
            sizeof(pExceptionObject));
        throw pExceptionObject;
    }

    sub_457410(aAssislangLang);
    sub_408BE0();
    uiQuadList = sub_5415F0();
    UIRenderQuadList(uiQuadList);
    sub_41F5E0(&dword_C11758);

    // Logging
    sub_53CE90(&byte_17B1EC0);
    sub_53CC70(&byte_17B1EC0, aSBulidSS, aV104);
    sub_53CC70(&byte_17B1EC0, aGameCreateOk, NULL);

    // Allocate CCBSystem (0x162D8 bytes)
    pCBSystemMem = operator new(0x162D8u);
    if (pCBSystemMem)
        pCBSystem = sub_512500(pCBSystemMem);
    else
        pCBSystem = 0;
    dword_BFDA74 = pCBSystem;
    if (!pCBSystem)
    {
        memcpy(&pExceptionObject,
            sub_53CEF0(ArgList, aCouldNotAlloca, aDProjectPal3Ga_0, 214),
            sizeof(pExceptionObject));
        throw pExceptionObject;
    }

    CCBSystem_ProcNormalAttack(pCBSystem);

    // Allocate scene manager (0xA930 bytes)
    pSceneMem = operator new(0xA930u);
    if (pSceneMem)
    {
        if (dword_BFDA68)
            pSceneCam = dword_BFDA68 + 4;
        else
            pSceneCam = 0;
        pSceneMgr = sub_4CDA10(dword_BFDA60, pSceneCam, 0);
    }
    else
    {
        pSceneMgr = 0;
    }
    dword_BFDA78 = pSceneMgr;
    if (!pSceneMgr)
    {
        memcpy(&pExceptionObject,
            sub_53CEF0(ArgList, aCouldNotAlloca_0, aDProjectPal3Ga_0, 222),
            sizeof(pExceptionObject));
        throw pExceptionObject;
    }

    // Render system setup
    if (byte_BFDA90)
    {
        if (byte_5833C0)
            sub_44F130(&dword_975ED8);
        rt5 = sub_4BDB10();
        RenderTarget_Create(rt5);
        rt6 = sub_4B65A0();
        sub_4B65F0(rt6);
        rt7 = sub_4BFD20();
        sub_4BF780(rt7);
        rt8 = sub_4B6D30();
        sub_4B6D80(rt8);
        rt9 = CEffectSystem_DestroyAllEffect();
        CEffectSystem_IsVisible(rt9);
        PAL3::GetCommandLineParam();
    }
    else
    {
        sub_44F130(&dword_975ED8);
        sub_44F610(4);
        rt0 = sub_4BDB10();
        RenderTarget_Create(rt0);
        rt1 = sub_4B65A0();
        sub_4B65F0(rt1);
        rt2 = sub_4BFD20();
        sub_4BF780(rt2);
        rt3 = sub_4B6D30();
        sub_4B6D80(rt3);
        rt4 = CEffectSystem_DestroyAllEffect();
        CEffectSystem_IsVisible(rt4);
    }

    // Check hardware caps
    // (*(void (__stdcall **)(...))(**(_DWORD **)(dword_BFDA60 + 1816) + 28))(...)
    // v35 = result field
    // if (!v35) byte_BFDA91 = 1;

    sub_41ED00(0);  // placeholder for the ebp-based call from IDA

    // Load geometry nodes for cursor/UI
    OpenBaseFile openBase(&pFileSystem);

    pCursorNode = (gbGeomNode *)operator new(0x118u);
    pCursorNodeInit = pCursorNode;
    if (pCursorNode)
    {
        pCursorNode->gbGeomNode::gbGeomNode();
        *(void **)pCursorNodeInit->_data = &off_56A66C;
    }
    else
    {
        pCursorNodeInit = 0;
    }
    dword_A3A6EC = (int)pCursorNodeInit;
    pCursorNodeInit->LoadFromFile(aObjectG02Cvd, 0, 0);

    pCursor2Mem = operator new(0x118u);
    pCursor2Init = pCursor2Mem;
    if (pCursor2Mem)
    {
        ((gbGeomNode *)pCursor2Mem)->gbGeomNode::gbGeomNode();
        *(void **)((gbGeomNode *)pCursor2Init)->_data = &off_56A66C;
    }
    else
    {
        pCursor2Init = 0;
    }
    dword_A3A6F0 = (int)pCursor2Init;
    ((gbGeomNode *)pCursor2Init)->LoadFromFile(aObjectG03Cvd, 0, 0);

    // Play logo video
    sub_53C440(aMovieLogoBik, hWndParent, 0, 0);
    int videoHeight = sub_53C720(&unk_A3A7D8);
    videoWidth = sub_53C710(&unk_A3A7D8);
    sub_53C6F0((800 - videoWidth) / 2, (600 - videoHeight) / 2);
    sub_53C5A0(1);

    // OpenNULLFile cleanup
    OpenNULLFile::OpenNULLFile_ctor(&pFileSystem);
}
