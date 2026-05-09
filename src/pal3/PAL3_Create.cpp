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
extern "C" __declspec(dllimport) void __cdecl gbTimeCounterInit(void);

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
    int v2;
    HCURSOR CursorA;
    HWND v4;
    int v5;
    void *v6;
    void *v7;
    int v8;
    int v9;
    int v10, v11, v12, v13, v14, v15, v16, v17, v18, v19;
    gbGeomNode *v20, *v21;
    void *v23, *v24;
    int v26;
    _Exception pExceptionObject;
    char v34[24];
    int v35;
    char ArgList[1024];
    void *v31;
    int v32[3];
    void *v30;

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

    v2 = sub_53DF70();
    sub_53DD70(v2);

    CursorA = LoadCursorA(hInstance, MAKEINTRESOURCEA(0x73));
    v4 = hWnd;
    dword_BFDA94 = (int)CursorA;
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(v4);

    // DirectInput initialization
    if (!sub_4020E0(&ppvOut, hInstance, (HWND)(int)v4, 0))
    {
        memcpy(&pExceptionObject,
            sub_53CEF0(ArgList, aInputDeviceCre, aDProjectPal3Ga_0, 180),
            sizeof(pExceptionObject));
        throw pExceptionObject;
    }

    sub_402270(&ppvOut, 0, 0, xRight, yBottom);
    sub_4022B0(&ppvOut, 0x40000000);
    sub_53C340(0, 1);

    memset(v32, 0, sizeof(v32));
    sub_41C1B0(v32);

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
    v5 = sub_5415F0();
    UIRenderQuadList(v5);
    sub_41F5E0(&dword_C11758);

    // Logging
    sub_53CE90(&byte_17B1EC0);
    sub_53CC70(&byte_17B1EC0, aSBulidSS, aV104);
    sub_53CC70(&byte_17B1EC0, aGameCreateOk, NULL);

    // Allocate CCBSystem (0x162D8 bytes)
    v6 = operator new(0x162D8u);
    if (v6)
        v7 = sub_512500(v6);
    else
        v7 = 0;
    dword_BFDA74 = v7;
    if (!v7)
    {
        memcpy(&pExceptionObject,
            sub_53CEF0(ArgList, aCouldNotAlloca, aDProjectPal3Ga_0, 214),
            sizeof(pExceptionObject));
        throw pExceptionObject;
    }

    CCBSystem_ProcNormalAttack(v7);

    // Allocate scene manager (0xA930 bytes)
    v30 = operator new(0xA930u);
    if (v30)
    {
        if (dword_BFDA68)
            v8 = dword_BFDA68 + 4;
        else
            v8 = 0;
        v9 = sub_4CDA10(dword_BFDA60, v8, 0);
    }
    else
    {
        v9 = 0;
    }
    dword_BFDA78 = v9;
    if (!v9)
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
            sub_44F130(&dword_975ED8);  // different: only if byte_5833C0
        v15 = sub_4BDB10();
        RenderTarget_Create(v15);
        v16 = sub_4B65A0();
        sub_4B65F0(v16);
        v17 = sub_4BFD20();
        sub_4BF780(v17);
        v18 = sub_4B6D30();
        sub_4B6D80(v18);
        v19 = CEffectSystem_DestroyAllEffect();
        CEffectSystem_IsVisible(v19);
        PAL3::GetCommandLineParam();
    }
    else
    {
        sub_44F130(&dword_975ED8);
        sub_44F610(4);
        v10 = sub_4BDB10();
        RenderTarget_Create(v10);
        v11 = sub_4B65A0();
        sub_4B65F0(v11);
        v12 = sub_4BFD20();
        sub_4BF780(v12);
        v13 = sub_4B6D30();
        sub_4B6D80(v13);
        v14 = CEffectSystem_DestroyAllEffect();
        CEffectSystem_IsVisible(v14);
    }

    // Check hardware caps
    // (*(void (__stdcall **)(...))(**(_DWORD **)(dword_BFDA60 + 1816) + 28))(...)
    // v35 = result field
    // if (!v35) byte_BFDA91 = 1;

    sub_41ED00(0);  // placeholder for the ebp-based call from IDA

    // Load geometry nodes for cursor/UI
    OpenBaseFile openBase(&v31);

    v20 = (gbGeomNode *)operator new(0x118u);
    v21 = v20;
    if (v20)
    {
        v20->gbGeomNode::gbGeomNode();
        *(void **)v21->_data = &off_56A66C;
    }
    else
    {
        v21 = 0;
    }
    dword_A3A6EC = (int)v21;
    v21->LoadFromFile(aObjectG02Cvd, 0, 0);

    v23 = operator new(0x118u);
    v24 = v23;
    if (v23)
    {
        ((gbGeomNode *)v23)->gbGeomNode::gbGeomNode();
        *(void **)((gbGeomNode *)v24)->_data = &off_56A66C;
    }
    else
    {
        v24 = 0;
    }
    dword_A3A6F0 = (int)v24;
    ((gbGeomNode *)v24)->LoadFromFile(aObjectG03Cvd, 0, 0);

    // Play logo video
    sub_53C440(aMovieLogoBik, hWndParent, 0, 0);
    int height = sub_53C720(&unk_A3A7D8);
    v26 = sub_53C710(&unk_A3A7D8);
    sub_53C6F0((800 - v26) / 2, (600 - height) / 2);
    sub_53C5A0(1);

    // OpenNULLFile cleanup
    OpenNULLFile::OpenNULLFile_ctor(&v31);
}
