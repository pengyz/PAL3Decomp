#pragma once
// PAL3 main game class + _Exception
// PDB source: D:\PAL3A\PAL3\gamebase\PAL3.cpp

#include <windows.h>

class _Exception {
public:
    char data[1024];
};

class PAL3 {
public:
    static void Create(HINSTANCE hInst);
    static void Destroy(void);
    static void Update(float dt);
    static void Render(void);
    static int  PrintScreen(void);
    static void CreateGfxWindow(void);
    static void CheckSystemRequire(HINSTANCE hInst);
    static void InitGFX(HINSTANCE hInst);
    static void CreateEffectSystem(void);
    static void DestroyEffectSystem(void);
    static void GetCommandLineParam(void);
};
