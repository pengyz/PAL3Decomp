# PAL3.exe OOP Refactoring Spec

## Context

The PAL3.exe decompilation codebase was directly transcribed from IDA Hex-Rays output.
This resulted in:
- 500+ `extern "C"` declarations (unnecessary for an exe)
- Global variables declared as `int` instead of correct pointer types
- Class methods written as `extern "C" void __cdecl ClassName_Method()`
- Same class defined inline in multiple .cpp files
- All stubs dumped into one 600-line globals.cpp
- PAL3.cpp at 1000+ lines with repeated extern declarations

This refactoring converts the entire codebase to proper C++ OOP in a single atomic commit.

## Target Structure

### Header Files

```
include/pal3/
  pal3_globals.h      -- all shared global variables (correct types)
  PAL3.h              -- class PAL3 (static methods)
  CRenderTarget.h     -- CRenderTarget + CRenderTarget2 (with static GetInstance)
  UIQuadManager.h     -- UIQuadManager (with static GetInstance)
  CScreenMode.h       -- CScreenMode
  GRPinput.h          -- GRPinput (already exists)
  CCBSystem.h         -- CCBSystem (already exists)
  filesys.h           -- OpenBaseFile, OpenNULLFile
```

gbengine classes use existing `include/gbengine/` headers:
- gbGfxManager.h (public API: GetMatrixStack, GetResManager, etc.)
- gbGeomNode.h, gbCamera.h, gbTexture.h, gbRenderEffect.h
- gbengine_internal.h (gbMatrixStack)

### Source File Reorganization

```
src/pal3/
  globals.cpp              -- ONLY global variable definitions + string constants
  gamebase/
    PAL3_Create.cpp        -- PAL3::Create + PAL3::InitGFX + helper stubs
    PAL3_Update.cpp        -- PAL3::Update + subsystem dispatch
    PAL3_Render.cpp        -- PAL3::Render + matrix stack ops
    PAL3_Destroy.cpp       -- PAL3::Destroy
    GRPinput.cpp           -- GRPinput methods (already correct)
    GfxHelper.cpp          -- PushMatrixStacks, PopMatrixStacks, RenderTarget3_Init
    ScreenMode.cpp         -- CScreenMode methods + Audio functions
  effect/
    RenderTarget.cpp       -- CRenderTarget::GetInstance, ::Destroy
    RenderTarget2.cpp      -- CRenderTarget2::GetInstance, ::Destroy
    RenderTarget34.cpp     -- RenderTarget3/4 GetInstance (unnamed classes)
    ScreenEffectMgr.cpp    -- ScreenEffectMgr::GetInstance
  ui/
    UIQuadManager.cpp      -- UIQuadManager::GetInstance, ::Destroy
  Combat/
    CBSystem.cpp           -- CCBSystem stubs
    CBStage.cpp            -- CCBStage stubs
  WinMain.cpp             -- WinMain + LowLevelKeyboardProc + helpers
```

### Global Variable Types (pal3_globals.h)

```cpp
extern gbGfxManager *g_pGfxManager;    // was: int
extern void *g_pCamera;                // CameraCtrl*, type TBD
extern void *g_pActorMgr;             // gbActorMgr*
extern void *g_pCBSystem;             // CCBSystem*
extern CGameData g_GameData;           // was: int
extern GRPinput g_Input;               // was: void *ppvOut
```

### OOP Conversions

| Current | Target | Evidence |
|---------|--------|----------|
| `RenderTarget_GetInstance()` | `CRenderTarget::GetInstance()` | static, singleton pattern |
| `RenderTarget2_GetInstance()` | `CRenderTarget2::GetInstance()` | static, singleton pattern |
| `UIQuadManager_GetInstance()` | `UIQuadManager::GetInstance()` | static, singleton pattern |
| `g_Input.SetMode()` etc. | same (already OOP) | verified |
| `CameraCtrl_SetDimention(w,h)` | `((CameraCtrl*)g_pCamera)->SetDimention(w,h)` | ecx = g_pCamera confirmed |
| `CameraCtrl_SetAsCurrent(flags)` | `((CameraCtrl*)g_pCamera)->SetAsCurrent(flags)` | ecx = g_pCamera confirmed |
| Unconfirmed thiscall functions | Keep as `void __cdecl func(args)` | Pending IDA verification |

### Elimination of extern "C"

- Global variables: removed, unified via pal3_globals.h
- Static class methods (GetInstance): removed, use C++ mangling
- Confirmed thiscall methods: removed, use class member syntax
- Free functions (stubs, callbacks): removed, declare in shared header
- All function declarations centralized per-file (no repeated extern in each function block)

### VC6 Constraints

- All source files: pure ASCII only (no UTF-8 Chinese comments)
- `const char` arrays: declared with `extern const char xxx[];` in headers
- `struct` vs `class` forward declarations: must match gbengine.lib mangling
- gbengine.lib: regenerated from src/gbengine/gbengine.def (full exports)

## Verification

1. `cmake --build build/pal3` passes (compile + link)
2. No `extern "C"` remaining in any src/pal3/ file
3. No inline class definitions in .cpp files (all via #include)
4. globals.cpp contains ONLY variable definitions and string constants
5. Every function has a meaningful name (no sub_XXXXXX in compiled code)
6. `grep -r "gbGfxManager_Partial" src/` returns nothing

## Non-Goals (deferred)

- Converting unconfirmed thiscall functions to class methods
- Defining CameraCtrl class (type of g_pCamera not fully determined)
- Splitting large functions (PAL3::Update is 1500B - stays as-is until better decomp)
- Byte-match verification (separate concern from code structure)
