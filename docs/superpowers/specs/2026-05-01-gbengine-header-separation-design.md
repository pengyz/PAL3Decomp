# gbengine.dll Header/Source Separation Design

## Goal

Restructure gbengine source code to properly separate class declarations (.h) from implementations (.cpp). Currently all class definitions are embedded in .cpp files, making cross-file references fragile and the codebase hard to navigate.

## Constraints

- Must not break the build (1021/1022 exports currently matched)
- Name mangling must remain identical (no signature changes)
- MSVC 6.0 SP5 compatibility (no modern C++ features)
- Keep `include/gbengine/` as the header location

## Architecture

### Header Organization

One header per module, organized by dependency layer. Each header is self-contained (includes its own dependencies).

**Layer 0 — No engine dependencies:**

| Header | Classes/Structs |
|--------|----------------|
| `gbengine_types.h` | (exists) gbVec3D, gbMatrix4, gbQuaternion, gbRotMatrix, gbRay, gbAABBox, gbOBBox, gbSphere, gbPlane, gbColorQuad, gbColorFlt, gbPixelFormat, gbUIRect |
| `gbChain.h` | gbChain1DNode, gbChain1D, gbChain2DNode, gbChain2D, gbNBTreeNode, gbNBTree, gbBinaryTreeNode, gbBinaryTree, gbStaticChainNode, gbStaticChain |

**Layer 1 — Depends on L0:**

| Header | Classes/Structs |
|--------|----------------|
| `gbMisc.h` | gbNameVarBuf, gbTimeCounter; function declarations for gbCrc32Init, gbCrc32Compute, gbStrChr, gbStrRChr, gbStrToLowCase, gbstricmp, gbstrindex, gbstrchr, gbIsMultiChar, gbIsMultiCharHead, gbIsMultiCharTail, gbTimeCounterInit, gbUpdateCurTime, gbGetCurTime, gbGetCurTick, gbGetDeltaTime, gbMemCopy, gbLogInfo, gbPopErrorBox, gbReportError, ProfileInit, ProfileBegin, ProfileEnd, ProfileDumpOutputToFile |
| `gbTexture.h` | gbImage2DInfo, gbImage2D, gbTexture, gbTexture_D3D, gbTextureArray |
| `gbMesh.h` | gbBaseMesh, gbStaticMesh, gbDynVertBuf, gbVertexPool, gbIndexPool, gbVertPoolMgr, gbIndexBubble, gbVertexBubble |

**Layer 2 — Depends on L0+L1:**

| Header | Classes/Structs |
|--------|----------------|
| `gbRenderEffect.h` | gbRenderEffect, gbEffectMgr, GBPARAMHANDLE enum |
| `gbCamera.h` | gbCamera, gbCamControler, gbCamSpringControl, gbCamQuakeControl, gbViewPort |
| `gbAudio.h` | gbAudioManager, gbAudioMgrDesc, gbSoundData, gbSound2DNode, gbSound3DNode |
| `gbVFileSystem.h` | gbVFileSystem, gbVFile, gbVFile1, gbVTextFile, CPK, CPKFile, CIniFile |

**Layer 3 — Depends on L0-L2:**

| Header | Classes/Structs |
|--------|----------------|
| `gbGfxManager.h` | gbGfxManager, gbGfxManager_D3D, gbGfxDriverInfo, gbClearParam, gbFogParam, gbGfxCaps, gbGfxStatistic, gbLight |
| `gbVisNode.h` | gbVisNode |
| `gbSceneGraph.h` | gbSceneGraph, gbLightObj, gbVolModNode, gbVolumeModifier, gbRenderInfoObj |

**Layer 4 — Depends on L0-L3:**

| Header | Classes/Structs |
|--------|----------------|
| `gbGeomNode.h` | gbGeomNode |
| `gbActor.h` | gbActor, gbActorDef, gbActorMgr, gbAnimNodeGroup, gbActionState, gbActorExpNode, gbMixActInfo |
| `gbParticle.h` | gbParticleEffect, gbParticleGroup, gbParticleUnit, gbPartEmitter, gbPartGroupParam, gbPartParamControl, gbEmitterData, gbEmitterSquare, gbDropGroup, gbDropUnit, gbDropDesc, gbRain, gbSnow, BEZIER |
| `gbPrintFont.h` | gbPrintFont, gbPrintFontMgr, gbFontType enum |

### Dependency Graph (include relationships)

```
gbengine_types.h  (base - no includes except windows.h/d3d9.h)
    |
    +-- gbChain.h
    |       |
    |       +-- gbVisNode.h
    |       |       |
    |       |       +-- gbGeomNode.h
    |       |       +-- gbActor.h
    |       |       +-- gbParticle.h
    |       |
    |       +-- gbSceneGraph.h
    |
    +-- gbMisc.h
    |
    +-- gbTexture.h
    |       |
    |       +-- gbGfxManager.h
    |
    +-- gbMesh.h
    |       |
    |       +-- gbGfxManager.h
    |
    +-- gbRenderEffect.h
    |       |
    |       +-- gbGfxManager.h
    |       +-- gbSceneGraph.h
    |       +-- gbGeomNode.h
    |
    +-- gbCamera.h
    |       |
    |       +-- gbGfxManager.h
    |
    +-- gbAudio.h
    +-- gbVFileSystem.h
    +-- gbPrintFont.h
```

### .cpp File Rules

Each .cpp file contains ONLY:
1. `#include` of its corresponding header (and any additional headers needed for implementations)
2. Static/local helper functions
3. Global variable definitions (e.g., `gbGfxManager* g_pGfxManager = NULL;`)
4. Out-of-line method implementations: `ReturnType ClassName::Method(params) { ... }`

**Prohibited in .cpp files:**
- class/struct member declarations (these go in .h)
- Forward declarations of types that have headers (use #include instead)
- Duplicate type definitions

### Source File Mapping

| Header | Implementation File(s) |
|--------|----------------------|
| `gbChain.h` | `gbChain.cpp` |
| `gbMisc.h` | `gbMisc.cpp` |
| `gbTexture.h` | `gbTexture.cpp` |
| `gbMesh.h` | `gbMesh.cpp`, `gbVertPool.cpp` |
| `gbRenderEffect.h` | `gbGfxManager.cpp` (shared file for GfxManager + RenderEffect + EffectMgr) |
| `gbCamera.h` | `gbCamera.cpp` |
| `gbAudio.h` | `gbAudioManager.cpp` |
| `gbVFileSystem.h` | `gbVFileSystem.cpp` |
| `gbGfxManager.h` | `gbGfxManager.cpp` |
| `gbVisNode.h` | `gbVisNode.cpp` |
| `gbSceneGraph.h` | `gbSceneGraph.cpp` |
| `gbGeomNode.h` | `gbGeomNode.cpp` |
| `gbActor.h` | `gbActor.cpp` |
| `gbParticle.h` | `gbParticle.cpp`, `gbWeather.cpp` |
| `gbPrintFont.h` | `gbPrintFont.cpp` |
| (no header) | `gbengine.cpp` (global functions), `gbengine_stubs.cpp`, `gbengine_exports.cpp`, `d3dx9_stubs.cpp`, `gbMath.cpp`, `gbResManager.cpp` |

### Header Template

```cpp
#pragma once

#include "gbengine/gbengine_types.h"
// Additional includes as needed:
// #include "gbengine/gbChain.h"

// Forward declarations (ONLY for pointer/reference parameters where full definition not needed)
class gbGfxManager;

// ============================================================================
// ClassName - brief description
// ============================================================================
class ClassName {
public:
    // Member variables (with offset comments from decompilation)
    int m_field;        // +0x04

    // Constructors/Destructor
    ClassName();
    ClassName(const ClassName& other);
    virtual ~ClassName();
    ClassName& operator=(const ClassName& other);

    // Methods (grouped logically)
    void Method(int param);
    int GetValue(void);
};
```

## Success Criteria

1. `cmake --build build_gbengine --config Release` succeeds with 0 errors
2. Export count remains 1021/1022 (or better)
3. No class/struct definitions remain in any .cpp file (only implementations)
4. Each .h is self-contained (can be included alone without errors)
5. No circular include dependencies

## Execution Order

Process files bottom-up by dependency layer:
1. L0: `gbChain.h` (extract from gbChain.cpp)
2. L1: `gbMisc.h`, `gbTexture.h`, `gbMesh.h`
3. L2: `gbRenderEffect.h`, `gbCamera.h`, `gbAudio.h`, `gbVFileSystem.h`
4. L3: `gbGfxManager.h`, `gbVisNode.h`, `gbSceneGraph.h`
5. L4: `gbGeomNode.h`, `gbActor.h`, `gbParticle.h`, `gbPrintFont.h`

Each step: create .h, modify .cpp to remove declarations and add #include, verify build passes.
