# gbengine.dll 100% Functional Decompilation Spec

## Goal

Produce a compilable C++ source tree that builds into a `gbengine.dll` fully replacing the original:
- Exports the same 1019 mangled symbols at identical ordinals
- All exported functions behave identically to the original
- PAL3.exe can load and run with the replacement DLL

**Non-goal:** Byte-identical output. Compiler differences (MSVC 6.0 vs modern MSVC) make exact binary matching impractical.

## Current State

- 24 source files generated with stub functions (678 classified gbengine functions)
- 2535 D3DX/CRT library functions identified and excluded
- `gbMatrixStack` (14 methods) fully implemented
- Build system configured, compiles zero errors
- PAL3A.PDB provides complete debug symbols for all classes
- `build/gbengine_demangled.txt` has all 1019 export signatures

## Architecture

### Dependency Layers

```
Layer 0: Math + Data Structures (no dependencies)
├── gbVec3D, gbMatrix4, gbRotMatrix, gbQuaternion (math ops)
├── gbMatrixStack (matrix stack - DONE)
├── gbChain1D, gbChain1DNode (singly linked list)
├── gbChain2D, gbChain2DNode (doubly linked list)
├── gbStaticChain (static chain)
├── gbBinaryTree, gbBinaryTreeNode (binary tree)
├── gbNBTree, gbNBTreeNode (n-ary tree)
├── gbColorQuad, gbColorFlt (color types)
├── gbAABBox, gbOBBox, gbSphere, gbPlane, gbRay (geometry)
└── BEZIER (bezier curve)

Layer 1: Node System + Resource Pools (depends on L0)
├── gbVisNode (scene node base, uses gbChain1D)
├── gbIndexBubble, gbIndexPool (index management, uses gbChain1D)
├── gbVertexPool, gbVertPoolMgr (vertex pools, uses gbChain1D)
├── gbAnimNodeGroup (animation nodes, uses gbChain1D)
├── gbRefObject (reference counting base)
└── gbResource, gbResManager (resource management base)

Layer 2: Scene + Model + Particles (depends on L1)
├── gbGeomNode (geometry node, uses gbVisNode)
├── gbSceneGraph (scene graph, uses gbVisNode)
├── gbBaseMesh, gbStaticMesh (mesh classes)
├── gbActor, gbActorMgr (character models)
├── gbParticleEffect, gbParticleGroup, gbParticleUnit (particles)
├── gbPartEmitter, gbPartGroupParam, gbPartParamControl
├── gbEmitterData, gbEmitterSquare
├── gbLightObj (lights)
└── gbDropGroup, gbDropUnit, gbRain, gbSnow (weather)

Layer 3: I/O + Graphics Core (depends on L2)
├── CPK, CPKFile (archive file system)
├── gbVFileSystem, gbVFile, gbVFile1, gbVTextFile (virtual FS)
├── CIniFile (config parser, uses gbVFileSystem)
├── gbImage2D, gbImage2DInfo (image loading)
├── gbTexture, gbTexture_D3D, gbTextureArray (textures)
├── gbGfxManager, gbGfxManager_D3D (D3D9 device management)
├── gbCamera, gbCamControler (camera system)
├── gbCamQuakeControl, gbCamSpringControl
└── gbRenderEffect (render effects)

Layer 4: High-level Systems (depends on L3)
├── gbAudioManager, gbAudioMgrDesc (Miles Sound System)
├── gbSound2DNode, gbSound3DNode (audio nodes)
├── gbEffectMgr (effect manager)
├── gbPrintFont, gbPrintFontMgr (text rendering)
├── gbDynVertBuf (dynamic vertex buffers)
├── gbTimeCounter (timing)
├── gbNameVarBuf (named variable buffer)
├── gbPixelFormat, gbUIRect (utility types)
└── gbGfxManager_D3D advanced methods

Layer 5: Integration + Export (depends on all)
├── DllMain + global initialization
├── Global functions (gbUpdateCurTime, ProfileBegin, etc.)
├── .def file with all 1019 exports
└── D3DX9 static library linkage
```

### D3DX Strategy

The original gbengine.dll statically links D3DX9 from DirectX SDK Summer 2003. This accounts for ~2535 of the 3214 total functions in the binary.

**Approach:** Link against `d3dx9.lib` from DirectX SDK Summer 2003. We do NOT reimplement D3DX code. The linker resolves all D3DX references automatically.

**Required:** DirectX SDK Summer 2003 installed (or its lib/include extracted).

### Export Strategy

Use a `.def` file (`gbengine.def`) listing all 1019 exports with their exact mangled names:

```def
LIBRARY gbengine
EXPORTS
    ??0BEZIER@@QAE@XZ @1
    ??0CIniFile@@QAE@XZ @2
    ...
    ?gbstrindex@@YAHPADPBD@Z @1019
```

This ensures the replacement DLL has identical export ordinals and names.

### File Organization (Final)

```
src/gbengine/
├── gbMath.cpp            # L0: Math operations (105 functions)
├── gbChain.cpp           # L0: Chain/tree data structures (41 functions)
├── gbVertPool.cpp        # L1: Vertex/index pools (27 functions)
├── gbResManager.cpp      # L1: Resource management (11 functions)
├── gbVisNode.cpp         # L1: Scene node base (17 functions)
├── gbSceneGraph.cpp      # L2: Scene graph (18 functions)
├── gbGeomNode.cpp        # L2: Geometry nodes (23 functions)
├── gbActor.cpp           # L2: Actor/model (38 functions)
├── gbMesh.cpp            # L2: Mesh classes (22 functions)
├── gbParticle.cpp        # L2: Particle system (38 functions)
├── gbWeather.cpp         # L2: Weather effects (13 functions)
├── CPK.cpp               # L3: Archive system (25 functions)
├── gbVFileSystem.cpp     # L3: Virtual file system (27 functions)
├── CIniFile.cpp          # L3: INI parser (16 functions)
├── gbImage2D.cpp         # L3: Image loading (10 functions)
├── gbTexture.cpp         # L3: Textures (20 functions)
├── gbGfxManager.cpp      # L3: D3D9 device (25 functions)
├── gbCamera.cpp          # L3: Camera system (42 functions)
├── gbRenderEffect.cpp    # L3: Render effects (13 functions)
├── gbAudioManager.cpp    # L4: Audio system (46 functions)
├── gbPrintFont.cpp       # L4: Font rendering (17 functions)
├── gbEffectMgr.cpp       # L4: Effect manager (10 functions)
├── gbMisc.cpp            # L4: Misc utilities (28 functions)
├── gbengine.cpp          # L5: DllMain + globals (46 functions)
└── gbengine.def          # Export definition file

include/gbengine/
└── gbengine_types.h      # All struct/class definitions
```

## Implementation Process (Per Function)

1. Read Ghidra JSON for the function (`asm/gbengine/<name>_<addr>.json`)
2. Understand the algorithm from decompiled C + PDB type info
3. Rewrite as clean C++ with correct class structure
4. Ensure it compiles without errors
5. Move to next function

## Verification

1. **Compile check:** `cmake --build` succeeds with zero errors
2. **Export check:** `dumpbin /exports gbengine.dll` matches all 1019 symbols
3. **Functional check:** PAL3.exe loads and runs with replacement DLL
4. **Per-class check:** Each class's public methods produce correct results

## Estimated Scope

| Layer | Functions | Complexity | Estimate |
|-------|-----------|------------|----------|
| L0 | ~160 | Low (math, simple data structures) | Small |
| L1 | ~90 | Low-Medium (linked list operations) | Small |
| L2 | ~120 | Medium (scene graph, model management) | Medium |
| L3 | ~130 | Medium-High (I/O, D3D9 calls) | Large |
| L4 | ~80 | Medium (Miles audio, font rendering) | Medium |
| L5 | ~100 | Low (wrappers, global init) | Small |
| **Total** | **~680** | | |

Note: The 2535 D3DX functions are handled by linking `d3dx9.lib` — zero manual work.

## Constraints

- **Compiler:** MSVC (modern, with `/GX /O2 /MD` flags matching original style)
- **Platform:** Win32 (x86, 32-bit)
- **Dependencies:** DirectX SDK Summer 2003 (d3dx9.lib, d3d9.lib), Miles Sound System headers
- **Functional correctness only:** No byte-matching requirement
- **Source of truth:** Ghidra JSON decompilations + PAL3A.PDB type information
