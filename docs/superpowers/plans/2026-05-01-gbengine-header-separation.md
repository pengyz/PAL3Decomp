# gbengine Header/Source Separation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Extract all class/struct declarations from .cpp files into proper .h headers, leaving only implementations in .cpp files.

**Architecture:** Bottom-up by dependency layer (L0 first, L4 last). Each task creates one header, modifies related .cpp files to remove declarations and add `#include`, then verifies the build still passes. Headers are self-contained (include their own dependencies).

**Tech Stack:** C++ (MSVC 6.0 SP5 compatible), CMake, Win32

**Spec:** `docs/superpowers/specs/2026-05-01-gbengine-header-separation-design.md`

---

## File Structure

### Headers to Create (in `include/gbengine/`)

| File | Responsibility |
|------|---------------|
| `gbChain.h` | Linked list/tree data structures (gbChain1DNode, gbChain1D, gbChain2DNode, gbChain2D, gbNBTreeNode, gbNBTree, gbBinaryTreeNode, gbBinaryTree, gbStaticChainNode, gbStaticChain) |
| `gbMisc.h` | Utility types + free function declarations (gbNameVarBuf, gbTimeCounter, CRC32, string utils, time functions) |
| `gbTexture.h` | Image and texture classes (gbImage2DInfo, gbImage2D, gbTexture, gbTexture_D3D, gbTextureArray) |
| `gbMesh.h` | Mesh classes (gbBaseMesh, gbStaticMesh, gbDynVertBuf, gbVertexPool, gbIndexPool, gbVertPoolMgr, gbIndexBubble, gbVertexBubble) |
| `gbRenderEffect.h` | Shader effect wrappers (gbRenderEffect, gbEffectMgr, GBPARAMHANDLE) |
| `gbCamera.h` | Camera system (gbCamera, gbCamControler, gbCamSpringControl, gbCamQuakeControl, gbViewPort) |
| `gbAudio.h` | Audio system (gbAudioManager, gbAudioMgrDesc, gbSoundData, gbSound2DNode, gbSound3DNode) |
| `gbVFileSystem.h` | Virtual file system (gbVFileSystem, gbVFile, gbVFile1, gbVTextFile, CPK, CPKFile, CIniFile) |
| `gbGfxManager.h` | Graphics manager (gbGfxManager, gbGfxManager_D3D, gbGfxDriverInfo, gbClearParam, gbFogParam, gbGfxCaps, gbGfxStatistic, gbLight) |
| `gbVisNode.h` | Scene node base (gbVisNode) |
| `gbSceneGraph.h` | Scene graph (gbSceneGraph, gbLightObj, gbVolModNode, gbVolumeModifier, gbRenderInfoObj) |
| `gbGeomNode.h` | Geometry node (gbGeomNode) |
| `gbActor.h` | Actor/animation (gbActor, gbActorDef, gbActorMgr, gbAnimNodeGroup, gbActionState, gbActorExpNode, gbMixActInfo) |
| `gbParticle.h` | Particle system (gbParticleEffect, gbParticleGroup, gbParticleUnit, gbPartEmitter, gbPartGroupParam, gbPartParamControl, gbEmitterData, gbEmitterSquare, gbDropGroup, gbDropUnit, gbDropDesc, gbRain, gbSnow, BEZIER) |
| `gbPrintFont.h` | Font rendering (gbPrintFont, gbPrintFontMgr) |

### .cpp Files to Modify

Every .cpp file listed above will be modified to:
1. Remove class/struct declarations (move to .h)
2. Add `#include` of corresponding header
3. Keep only: static helpers, global variable definitions, method implementations

---

## Task 1: Create `gbChain.h` (Layer 0)

**Files:**
- Create: `include/gbengine/gbChain.h`
- Modify: `src/gbengine/gbChain.cpp`
- Modify: `src/gbengine/gbVisNode.cpp` (remove duplicate gbChain1DNode/gbChain1D/gbNBTreeNode declarations)
- Modify: `src/gbengine/gbVertPool.cpp` (remove duplicate gbChain1DNode/gbChain1D declarations)

- [ ] **Step 1: Create `include/gbengine/gbChain.h`**

```cpp
#pragma once

#include "gbengine/gbengine_types.h"

// ============================================================================
// gbChain1DNode - Single-linked list node (8 bytes)
// ============================================================================
class gbChain1DNode {
public:
    gbChain1DNode* pNext;   // +0x04 (vptr at +0x00 from virtual dtor)

    gbChain1DNode(void);
    gbChain1DNode(const gbChain1DNode& src);
    virtual ~gbChain1DNode();
    gbChain1DNode& operator=(const gbChain1DNode& other);
};

// ============================================================================
// gbChain1D - Single-linked list (16 bytes)
// ============================================================================
class gbChain1D {
public:
    gbChain1DNode* pHead;      // +0x00
    gbChain1DNode* pTail;      // +0x04
    int nCount;                // +0x08
    gbChain1DNode* pIterator;  // +0x0C

    gbChain1D(void);
    ~gbChain1D();
    gbChain1D& operator=(const gbChain1D& other);

    void ClearAllNodePtr(void);
    void AddNodeOnHead(gbChain1DNode* node);
    void AddNodeOnTail(gbChain1DNode* node);
    void AddNode(gbChain1DNode* node);
    void InsertBefore(gbChain1DNode* newNode, gbChain1DNode* beforeNode);
    void InsertAfter(gbChain1DNode* newNode, gbChain1DNode* afterNode);
    void DelNodeFromChain(gbChain1DNode* node);
    bool IsContainNode(gbChain1DNode* node);
    int GetNumNode(void);
    gbChain1DNode* BeginIterate(void);
    gbChain1DNode* Iterate(void);
    gbChain1DNode* operator[](int index);
};

// ============================================================================
// gbChain2DNode - Double-linked list node (12 bytes)
// ============================================================================
class gbChain2DNode {
public:
    gbChain2DNode* pPrev;   // +0x04
    gbChain2DNode* pNext;   // +0x08

    gbChain2DNode(void);
    gbChain2DNode(const gbChain2DNode& src);
    virtual ~gbChain2DNode();
    gbChain2DNode& operator=(const gbChain2DNode& other);
};

// ============================================================================
// gbChain2D - Double-linked list (20 bytes)
// ============================================================================
class gbChain2D {
public:
    gbChain2DNode* pHead;      // +0x00
    gbChain2DNode* pTail;      // +0x04
    int nDirection;            // +0x08
    int nCount;                // +0x0C
    gbChain2DNode* pIterator;  // +0x10

    gbChain2D(void);
    ~gbChain2D();
    gbChain2D& operator=(const gbChain2D& other);

    void AddNode(gbChain2DNode* node);
    void DelNodeFromChain(gbChain2DNode* node);
    bool IsContainNode(gbChain2DNode* node);
    int GetNumNode(void);
    gbChain2DNode* BeginIterate(int dir);
    gbChain2DNode* Iterate(void);
};

// ============================================================================
// gbNBTreeNode - N-ary tree node (28 bytes, inherits gbChain1DNode)
// ============================================================================
class gbNBTreeNode : public gbChain1DNode {
public:
    gbNBTreeNode* pParent;         // +0x08
    gbChain1D children;            // +0x0C (16 bytes)
    gbNBTreeNode* pChildIterator;  // +0x18

    gbNBTreeNode(void);
    gbNBTreeNode(const gbNBTreeNode& src);
    virtual ~gbNBTreeNode();
    gbNBTreeNode& operator=(const gbNBTreeNode& other);

    void AddChildOnHead(gbNBTreeNode* child);
    void AddChildOnTail(gbNBTreeNode* child);
    void AddChild(gbNBTreeNode* child);
    void DelChildFromChain(gbNBTreeNode* child);
    int IsChild(gbNBTreeNode* child);
    int GetNumChildren(void);
    gbChain1D& GetChildren(void);
    gbNBTreeNode* GetFather(void);
    gbNBTreeNode* BeginIterateChild(void);
    gbNBTreeNode* IterateChild(void);
    gbNBTreeNode* GetChild(int index);
};

// ============================================================================
// gbNBTree - N-ary tree (4 bytes)
// ============================================================================
class gbNBTree {
public:
    gbNBTreeNode* pRoot;  // +0x00

    gbNBTree(void);
    ~gbNBTree();
    gbNBTree& operator=(const gbNBTree& other);

    void SetRoot(gbNBTreeNode* node);
    gbNBTreeNode* GetRoot(void);
};

// ============================================================================
// gbBinaryTreeNode - Binary tree node (16 bytes)
// ============================================================================
class gbBinaryTreeNode {
public:
    gbBinaryTreeNode* pLeft;       // +0x04
    gbBinaryTreeNode* pRight;      // +0x08
    gbBinaryTreeNode* pParent;     // +0x0C

    gbBinaryTreeNode(void);
    gbBinaryTreeNode(const gbBinaryTreeNode& src);
    virtual ~gbBinaryTreeNode();
    gbBinaryTreeNode& operator=(const gbBinaryTreeNode& other);

    gbBinaryTreeNode* GetFather(void);
    gbBinaryTreeNode* GetLeft(void);
    gbBinaryTreeNode* GetRight(void);
};

// ============================================================================
// gbBinaryTree - Binary tree (4 bytes)
// ============================================================================
class gbBinaryTree {
public:
    gbBinaryTreeNode* pRoot;  // +0x00

    gbBinaryTree(void);
    ~gbBinaryTree();
    gbBinaryTree& operator=(const gbBinaryTree& other);

    void SetRoot(gbBinaryTreeNode* node);
    gbBinaryTreeNode* GetRoot(void);
};

// ============================================================================
// gbStaticChainNode - Static chain node (8 bytes header)
// ============================================================================
struct gbStaticChainNode {
    gbStaticChainNode* pPrev;  // +0x00
    gbStaticChainNode* pNext;  // +0x04
};

// ============================================================================
// gbStaticChain - Static memory pool with linked list (28 bytes)
// ============================================================================
class gbStaticChain {
public:
    void* pBuffer;                  // +0x00
    gbStaticChainNode* pFreeHead;   // +0x04
    gbStaticChainNode* pUsedHead;   // +0x08
    gbStaticChainNode* pIterator;   // +0x0C
    int nMaxNodes;                  // +0x10
    int nNodeSize;                  // +0x14
    int nUsedCount;                 // +0x18

    gbStaticChain(void);
    gbStaticChain& operator=(const gbStaticChain& other);

    void InitBuffer(int maxNodes, int nodeSize);
    void ReleaseBuffer(void);
    gbStaticChainNode* NewOneNode(void);
    void DelOneNode(gbStaticChainNode* ptr);
    gbStaticChainNode* BeginIterate(void);
    gbStaticChainNode* Iterate(void);
    gbStaticChainNode* BeginReverseIterate(void);
    gbStaticChainNode* ReverseIterate(void);
};
```

- [ ] **Step 2: Modify `src/gbengine/gbChain.cpp` — remove declarations, add include**

Replace the top of the file (lines 1-219, everything before the first method implementation) with:

```cpp
/**
 * gbengine.dll - gbChain
 * Linked lists, trees, and static chain implementations
 * Functions: 41
 */

#include "gbengine/gbChain.h"
#include <stdlib.h>
#include <string.h>
```

Keep all method implementations (`gbChain1DNode::gbChain1DNode(void) { ... }` etc.) unchanged.

- [ ] **Step 3: Modify `src/gbengine/gbVisNode.cpp` — remove duplicate gbChain class declarations**

Remove the duplicate definitions of `gbChain1DNode`, `gbChain1D`, `gbNBTreeNode` (lines 35-63) and replace with:

```cpp
#include "gbengine/gbChain.h"
```

- [ ] **Step 4: Modify `src/gbengine/gbVertPool.cpp` — remove duplicate gbChain class declarations**

Remove the duplicate definitions of `gbChain1DNode`, `gbChain1D` (lines 33-55) and replace with:

```cpp
#include "gbengine/gbChain.h"
```

- [ ] **Step 5: Build and verify**

Run:
```bash
cmake -B build_gbengine -S . -G "Visual Studio 17 2022" -A Win32 -DBUILD_TARGET=gbengine
cmake --build build_gbengine --config Release
```

Expected: Build succeeds with 0 errors. Export count remains 1021/1022.

- [ ] **Step 6: Commit**

```bash
git add include/gbengine/gbChain.h src/gbengine/gbChain.cpp src/gbengine/gbVisNode.cpp src/gbengine/gbVertPool.cpp
git commit -m "refactor(gbengine): extract gbChain class declarations to gbChain.h"
```

---

## Task 2: Create `gbMisc.h` (Layer 1)

**Files:**
- Create: `include/gbengine/gbMisc.h`
- Modify: `src/gbengine/gbMisc.cpp`

- [ ] **Step 1: Create `include/gbengine/gbMisc.h`**

```cpp
#pragma once

#include "gbengine/gbengine_types.h"

// ============================================================================
// gbTimeCounter
// ============================================================================
struct gbTimeCounter {
    LARGE_INTEGER startTime;
    LARGE_INTEGER freq;
    double elapsed;
};

// ============================================================================
// gbNameVarBuf
// ============================================================================
struct gbNameVarBuf {
    void* impl;
};

// ============================================================================
// Free function declarations
// ============================================================================

// CRC32
void gbCrc32Init(void);
unsigned int gbCrc32Compute(const char* data, int len);
unsigned int gbCrc32Compute(const char* str);

// String utilities
char* gbStrChr(const char* str, const char* chars);
char* gbStrRChr(const char* str, const char* chars);
void gbStrToLowCase(char* str);
int gbstricmp(const char* s1, const char* s2);
int gbstrindex(const char* str, const char* sub);
char* gbstrchr(const char* str, char ch);
int gbIsMultiChar(const char* str);
int gbIsMultiCharHead(char c);
int gbIsMultiCharTail(char c);

// Time functions
void gbTimeCounterInit(gbTimeCounter* tc);
void gbUpdateCurTime(void);
double gbGetCurTime(void);
unsigned int gbGetCurTick(void);
double gbGetDeltaTime(void);

// Memory/Debug utilities
void gbMemCopy(void* dst, const void* src, int size);
void gbLogInfo(const char* fmt, ...);
void gbPopErrorBox(const char* title, const char* fmt, ...);
void gbReportError(const char* fmt, ...);

// Profiling
void ProfileInit(void);
void ProfileBegin(const char* name);
void ProfileEnd(const char* name);
void ProfileDumpOutputToFile(const char* filename);
```

- [ ] **Step 2: Modify `src/gbengine/gbMisc.cpp` — remove struct declarations, add include**

Replace lines 1-25 (header comment, includes, and struct declarations for `gbTimeCounter` and `gbNameVarBuf`) with:

```cpp
/**
 * gbengine.dll - gbMisc
 * Utility functions and classes for gbengine
 */

#include "gbengine/gbMisc.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <mmsystem.h>
```

Remove the `class gbGfxManager;` forward declaration (line 24 area) since it's not needed for implementations in this file.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

Expected: 0 errors.

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbMisc.h src/gbengine/gbMisc.cpp
git commit -m "refactor(gbengine): extract gbMisc declarations to gbMisc.h"
```

---

## Task 3: Create `gbTexture.h` (Layer 1)

**Files:**
- Create: `include/gbengine/gbTexture.h`
- Modify: `src/gbengine/gbTexture.cpp`

- [ ] **Step 1: Create `include/gbengine/gbTexture.h`**

```cpp
#pragma once

#include "gbengine/gbengine_types.h"
#include <d3d9.h>

// Forward declarations
class gbResManager;
class gbGfxManager;

// ============================================================================
// gbRefObject - reference-counted base
// ============================================================================
struct gbRefObject {
    void* vfptr;    // vtable pointer
    int RefCount;
};

// ============================================================================
// gbResource - managed resource base
// ============================================================================
struct gbResource {
    gbRefObject baseclass;
    char* pName;
    unsigned int NameCrc32;
    int IsLoaded;
    gbResManager* pMgr;
};

// ============================================================================
// gbImage2DInfo
// ============================================================================
struct gbImage2DInfo {
    int isdiskinfo;
    int goal;
    int ngrade;
    int detail[8];
    int wdiv[8];
    int hdiv[8];
    int wrap_u;
    int wrap_v;
    int mipmap;
    int minfilter;
    int magfilter;

    int IsPreferAlpha(void);
    gbImage2DInfo& operator=(const gbImage2DInfo& other);
};

// ============================================================================
// gbImage2D - 2D bitmap image
// ============================================================================
class gbImage2D {
public:
    gbImage2DInfo ImgInfo;
    int Width;
    int Height;
    gbPixelFormat PixelFmt;
    int BitCount;
    char* pBits;
    gbColorQuad* pPalette;
    int numPalEntry;
    gbColorQuad ColorKey;

    gbImage2D(void);
    ~gbImage2D();

    unsigned char* CreateImage(int w, int h, int bpp);
    int GetBitCount(void);
    unsigned char* GetBits(int x, int y);
    unsigned char* GetBits(void);
    int GetHeight(void);
    int GetWidth(void);
    gbColorQuad* GetPalEntry(int index);
    int LoadImageFile(char* filename, int flags);
    void ScaleTo(int newW, int newH);
    void WriteTGAImage(char* filename);
    void WriteJpegImage(char* filename, int quality);
    int WriteJpegToBuffer(unsigned char* buffer, int bufSize);
    void Release(void);
    gbPixelFmtType GetPixelFmtType(void);
    gbImage2DInfo* GetImgInfo(void);
};

// ============================================================================
// gbTexture - base texture class (virtual)
// ============================================================================
class gbTexture {
public:
    gbRefObject refObj;
    char* pName;
    unsigned int NameCrc32;
    int IsLoaded;
    gbResManager* pMgr;

    int Width;
    int Height;
    gbImage2D* pTexImage;
    gbPixelFormat InFmt;
    int nLevels;

    gbTexture(void);
    virtual ~gbTexture();

    int IsInit(void);
    void CreateTexture(int w, int h, gbPixelFmtType fmt, int mips);
    virtual IDirect3DTexture9* GetTexture(void);
    int GetHeight(void);
    int GetWidth(void);
    gbPixelFmtType GetInternalFormat(gbImage2D* img);
    unsigned char* GetBits(void);
    unsigned char GetPixelChannel(int x, int y, int channel);
    int GetLevels(void);
    void LoadFromImage2D(gbImage2D* img);
    void LoadTexture(int resIndex);
    void UpdateTexture(int x, int y, gbImage2D* img);
    void UpdateTexture(gbImage2D* img);
};

// ============================================================================
// gbTexture_D3D - Direct3D 9 texture implementation
// ============================================================================
class gbTexture_D3D : public gbTexture {
public:
    IDirect3DBaseTexture9* pTex;
    IDirect3DSurface9* pDS;
    ULONG m_ImgFormat;

    gbTexture_D3D(void);
    virtual ~gbTexture_D3D();
    virtual IDirect3DTexture9* GetTexture(void);

    void CreateFromMemory(int w, int h, gbPixelFmtType srcFmt, int levels,
                          gbPixelFmtType dstFmt, void* data);
    void UpdateTexture(int x, int y, int w, int h, gbPixelFmtType srcFmt, void* data);
    void CreateFromFileMemory(void* data, int size);
    int CreateForRenderTarget(int w, int h, gbPixelFmtType fmt);
    unsigned char GetByte(int x, int y);
    IDirect3DBaseTexture9* GetTexName(void);
    IDirect3DBaseTexture9* GetMiscTexName(void);
};

// ============================================================================
// gbTextureArray - texture collection
// ============================================================================
struct gbTextureArray {
    gbTexture_D3D** ppTextures;
    int nTextures;
    int nCapacity;

    gbTextureArray(void);
    ~gbTextureArray();
    gbTextureArray& operator=(const gbTextureArray& other);

    void Init(int capacity);
    void Release(void);
    int AddTexture(gbTexture_D3D* tex);
    gbTexture_D3D* GetTexture(int index);
    int GetNumTextures(void);
};
```

- [ ] **Step 2: Modify `src/gbengine/gbTexture.cpp` — remove declarations, add include**

Replace lines 1-99 (everything before the first `static` helper function `gbPixelFmtToD3D`) with:

```cpp
/**
 * gbengine.dll - gbTexture, gbTexture_D3D, gbTextureArray, gbImage2D
 */

#include "gbengine/gbTexture.h"
#include <d3dx9.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Forward declarations for types only used in implementations
class gbGfxManager_D3D;
class gbVFileSystem;
class gbVFile;

// External globals
extern gbGfxManager* g_pGfxManager;
```

Remove all class/struct definitions that were moved to the header (gbRefObject, gbResource, gbImage2DInfo, gbImage2D, gbTexture, gbTexture_D3D, gbTextureArray). Keep static helper functions and all method implementations.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbTexture.h src/gbengine/gbTexture.cpp
git commit -m "refactor(gbengine): extract gbTexture class declarations to gbTexture.h"
```

---

## Task 4: Create `gbMesh.h` (Layer 1)

**Files:**
- Create: `include/gbengine/gbMesh.h`
- Modify: `src/gbengine/gbMesh.cpp`
- Modify: `src/gbengine/gbVertPool.cpp`

- [ ] **Step 1: Create `include/gbengine/gbMesh.h`**

Extract class declarations from `gbMesh.cpp` and `gbVertPool.cpp` into a single header. Include:
- `gbBaseMesh`, `gbStaticMesh`, `gbMeshSection`, `gbMeshMemCache`
- `gbVertexPool`, `gbIndexPool`, `gbVertPoolMgr`, `gbDynVertBuf`
- `gbIndexBubble`, `gbVertexBubble`
- Enums: `gbPrimType`, `gbPoolType`

The header must `#include "gbengine/gbengine_types.h"` and `#include "gbengine/gbChain.h"` (for gbChain1DNode inheritance in gbIndexBubble/gbVertexBubble).

- [ ] **Step 2: Modify `src/gbengine/gbMesh.cpp` and `src/gbengine/gbVertPool.cpp`**

Replace all class/struct declarations with `#include "gbengine/gbMesh.h"`. Keep method implementations.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbMesh.h src/gbengine/gbMesh.cpp src/gbengine/gbVertPool.cpp
git commit -m "refactor(gbengine): extract gbMesh class declarations to gbMesh.h"
```

---

## Task 5: Create `gbRenderEffect.h` (Layer 2)

**Files:**
- Create: `include/gbengine/gbRenderEffect.h`
- Modify: `src/gbengine/gbGfxManager.cpp` (gbRenderEffect and gbEffectMgr are defined here)

- [ ] **Step 1: Create `include/gbengine/gbRenderEffect.h`**

Extract `GBPARAMHANDLE` enum, `gbRenderEffect` class, and `gbEffectMgr` class from `gbGfxManager.cpp` (lines 338-end of gbEffectMgr definition).

The header must include:
```cpp
#include "gbengine/gbengine_types.h"
#include <d3d9.h>
```

Forward declare: `class gbGfxManager;`, `struct ID3DXEffect;`

- [ ] **Step 2: Modify `src/gbengine/gbGfxManager.cpp`**

Remove the gbRenderEffect and gbEffectMgr class declarations. Add `#include "gbengine/gbRenderEffect.h"`.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbRenderEffect.h src/gbengine/gbGfxManager.cpp
git commit -m "refactor(gbengine): extract gbRenderEffect declarations to gbRenderEffect.h"
```

---

## Task 6: Create `gbCamera.h` (Layer 2)

**Files:**
- Create: `include/gbengine/gbCamera.h`
- Modify: `src/gbengine/gbCamera.cpp`

- [ ] **Step 1: Create `include/gbengine/gbCamera.h`**

Extract from `gbCamera.cpp`:
- `gbViewPort` struct
- `gbCamControler` class
- `gbCamSpringControl` class
- `gbCamQuakeControl` class
- `gbCamera` class

The header must include `"gbengine/gbengine_types.h"`. Forward declare `class gbGfxManager;`.

- [ ] **Step 2: Modify `src/gbengine/gbCamera.cpp`**

Remove all class/struct declarations. Replace with `#include "gbengine/gbCamera.h"`. Keep method implementations and the `extern gbGfxManager* g_pGfxManager;` reference.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbCamera.h src/gbengine/gbCamera.cpp
git commit -m "refactor(gbengine): extract gbCamera declarations to gbCamera.h"
```

---

## Task 7: Create `gbAudio.h` (Layer 2)

**Files:**
- Create: `include/gbengine/gbAudio.h`
- Modify: `src/gbengine/gbAudioManager.cpp`

- [ ] **Step 1: Create `include/gbengine/gbAudio.h`**

Extract from `gbAudioManager.cpp`:
- `gbAudioMgrDesc` struct
- `gbSoundData` class
- `gbSound2DNode` class
- `gbSound3DNode` class
- `gbAudioManager` class

Miles Sound System typedefs (`HSAMPLE`, `H3DSAMPLE`, etc.) stay in the .cpp since they're implementation details. The header should only use opaque `void*` for handle types in the class declarations, or forward-declare them.

- [ ] **Step 2: Modify `src/gbengine/gbAudioManager.cpp`**

Remove class/struct declarations. Add `#include "gbengine/gbAudio.h"`. Keep Miles typedefs, stub functions, and method implementations.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbAudio.h src/gbengine/gbAudioManager.cpp
git commit -m "refactor(gbengine): extract gbAudio declarations to gbAudio.h"
```

---

## Task 8: Create `gbVFileSystem.h` (Layer 2)

**Files:**
- Create: `include/gbengine/gbVFileSystem.h`
- Modify: `src/gbengine/gbVFileSystem.cpp`

- [ ] **Step 1: Create `include/gbengine/gbVFileSystem.h`**

Extract from `gbVFileSystem.cpp`:
- `ECPKMode` enum
- `CPKHeader` struct
- `CPKTable` struct
- `CPK` class
- `CPKFile` class
- `gbVFile` class
- `gbVFile1` class
- `gbVTextFile` class
- `gbVFileSystem` class
- `CIniFile` class

CPK constants (`CPK_LABEL`, `CPK_MAX_TABLE_NUM`, etc.) go in the header since they're part of the public interface.

- [ ] **Step 2: Modify `src/gbengine/gbVFileSystem.cpp`**

Remove all class/struct declarations and constants that moved to the header. Add `#include "gbengine/gbVFileSystem.h"`. Keep LZO stubs and method implementations.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbVFileSystem.h src/gbengine/gbVFileSystem.cpp
git commit -m "refactor(gbengine): extract gbVFileSystem declarations to gbVFileSystem.h"
```

---

## Task 9: Create `gbGfxManager.h` (Layer 3)

**Files:**
- Create: `include/gbengine/gbGfxManager.h`
- Modify: `src/gbengine/gbGfxManager.cpp`

- [ ] **Step 1: Create `include/gbengine/gbGfxManager.h`**

Extract from `gbGfxManager.cpp`:
- `gbClearParam` struct
- `gbFogParam` struct
- `gbGfxCaps` struct
- `gbGfxStatistic` struct
- `gbLight` struct (from gbSceneGraph.cpp)
- `gbGfxDriverInfo` struct
- `gbViewPort` struct (if not already in gbCamera.h — check for conflicts, may need single definition location)
- `gbTransformType` enum
- `gbMeshType` enum
- `gbFontType` enum
- `gbGfxManager` class
- `gbGfxManager_D3D` class (if present)

Include: `"gbengine/gbengine_types.h"`, `<d3d9.h>`

Forward declare: `class gbEffectMgr;`, `class gbResManager;`, `class gbVertPoolMgr;`, `class gbPrintFontMgr;`, `class gbPrintFont;`, `class gbMatrixStack;`, `class gbSceneGraph;`, `class gbCamera;`, `class gbBaseMesh;`

- [ ] **Step 2: Modify `src/gbengine/gbGfxManager.cpp`**

Remove all struct/class/enum declarations that moved to the header. Add `#include "gbengine/gbGfxManager.h"`. Keep `gbGfxManager* g_pGfxManager = NULL;` definition and all method implementations.

- [ ] **Step 3: Resolve `gbViewPort` duplicate**

`gbViewPort` is defined in both `gbGfxManager.cpp` and `gbCamera.cpp`. Choose ONE canonical location (recommend `gbGfxManager.h` since it's lower-level), and have `gbCamera.h` include `gbGfxManager.h` or forward-declare and use pointer. Alternatively, put `gbViewPort` in `gbengine_types.h` since it's a simple struct.

- [ ] **Step 4: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 5: Commit**

```bash
git add include/gbengine/gbGfxManager.h src/gbengine/gbGfxManager.cpp
git commit -m "refactor(gbengine): extract gbGfxManager declarations to gbGfxManager.h"
```

---

## Task 10: Create `gbVisNode.h` (Layer 3)

**Files:**
- Create: `include/gbengine/gbVisNode.h`
- Modify: `src/gbengine/gbVisNode.cpp`
- Modify: `src/gbengine/gbGeomNode.cpp` (remove duplicate gbVisNode declaration)
- Modify: `src/gbengine/gbActor.cpp` (remove duplicate gbVisNode declaration)

- [ ] **Step 1: Create `include/gbengine/gbVisNode.h`**

Extract from `gbVisNode.cpp`:
- `gbNodeMsgObj` struct
- `NodeBlend` enum
- `gbVisNode` class (the full version with all members)

Include: `"gbengine/gbChain.h"` (for gbNBTreeNode base class)

Forward declare: `class gbGfxManager;`, `class gbSceneGraph;`, `class gbRenderEffect;`, `struct gbRenderInfoObj;`

- [ ] **Step 2: Modify `src/gbengine/gbVisNode.cpp`**

Remove class declarations. Add `#include "gbengine/gbVisNode.h"`. Keep method implementations.

- [ ] **Step 3: Modify `src/gbengine/gbGeomNode.cpp`**

Remove the partial `gbVisNode` forward class definition (lines 27-33). Add `#include "gbengine/gbVisNode.h"`.

- [ ] **Step 4: Modify `src/gbengine/gbActor.cpp`**

Remove the partial `gbVisNode` class declaration (lines 70-87). Add `#include "gbengine/gbVisNode.h"`.

- [ ] **Step 5: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 6: Commit**

```bash
git add include/gbengine/gbVisNode.h src/gbengine/gbVisNode.cpp src/gbengine/gbGeomNode.cpp src/gbengine/gbActor.cpp
git commit -m "refactor(gbengine): extract gbVisNode declaration to gbVisNode.h"
```

---

## Task 11: Create `gbSceneGraph.h` (Layer 3)

**Files:**
- Create: `include/gbengine/gbSceneGraph.h`
- Modify: `src/gbengine/gbSceneGraph.cpp`

- [ ] **Step 1: Create `include/gbengine/gbSceneGraph.h`**

Extract from `gbSceneGraph.cpp`:
- `gbLight` struct (or reference from gbGfxManager.h if already there)
- `gbRenderInfoObj` struct
- `gbLightObj` class
- `gbSceneGraph` class

Include: `"gbengine/gbengine_types.h"`

Forward declare: `class gbVisNode;`, `class gbGfxManager;`, `class gbCamera;`, `class gbRenderEffect;`, `class gbEffectMgr;`, `class gbVolModNode;`

- [ ] **Step 2: Modify `src/gbengine/gbSceneGraph.cpp`**

Remove class/struct declarations. Add `#include "gbengine/gbSceneGraph.h"`. Keep global variable definitions and method implementations.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbSceneGraph.h src/gbengine/gbSceneGraph.cpp
git commit -m "refactor(gbengine): extract gbSceneGraph declarations to gbSceneGraph.h"
```

---

## Task 12: Create `gbGeomNode.h` (Layer 4)

**Files:**
- Create: `include/gbengine/gbGeomNode.h`
- Modify: `src/gbengine/gbGeomNode.cpp`

- [ ] **Step 1: Create `include/gbengine/gbGeomNode.h`**

Extract from `gbGeomNode.cpp`:
- `gbGeomNode` class

Include: `"gbengine/gbVisNode.h"` (for base class)

Forward declare: `class gbBaseMesh;`, `class gbStaticMesh;`, `class gbRenderEffect;`, `class gbTexture;`, `class gbVFile;`, `struct gbRenderInfoObj;`

- [ ] **Step 2: Modify `src/gbengine/gbGeomNode.cpp`**

Remove class declaration. Add `#include "gbengine/gbGeomNode.h"`. Keep method implementations.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbGeomNode.h src/gbengine/gbGeomNode.cpp
git commit -m "refactor(gbengine): extract gbGeomNode declaration to gbGeomNode.h"
```

---

## Task 13: Create `gbActor.h` (Layer 4)

**Files:**
- Create: `include/gbengine/gbActor.h`
- Modify: `src/gbengine/gbActor.cpp`

- [ ] **Step 1: Create `include/gbengine/gbActor.h`**

Extract from `gbActor.cpp`:
- `gbActorExpNode` struct
- `gbMixActInfo` struct
- `gbActionState` struct
- `gbActorDef` class
- `gbActor` class
- `gbActorMgr` class (if present)
- `gbAnimNodeGroup` class (if present)

Include: `"gbengine/gbVisNode.h"`

Forward declare: `class gbGfxManager;`, `class gbRenderEffect;`, `class gbTexture;`, `class gbVFileSystem;`, `class gbResManager;`

- [ ] **Step 2: Modify `src/gbengine/gbActor.cpp`**

Remove all class/struct declarations. Add `#include "gbengine/gbActor.h"`. Keep method implementations.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbActor.h src/gbengine/gbActor.cpp
git commit -m "refactor(gbengine): extract gbActor declarations to gbActor.h"
```

---

## Task 14: Create `gbParticle.h` (Layer 4)

**Files:**
- Create: `include/gbengine/gbParticle.h`
- Modify: `src/gbengine/gbParticle.cpp`
- Modify: `src/gbengine/gbWeather.cpp`

- [ ] **Step 1: Create `include/gbengine/gbParticle.h`**

Extract from `gbParticle.cpp` and `gbWeather.cpp`:
- `gbEmitterData` struct
- `gbPartParamControl` class
- `gbPartGroupParam` struct (if present)
- `gbParticleUnit` struct
- `gbPartEmitter` class
- `gbEmitterSquare` class (if present)
- `gbParticleGroup` class
- `gbParticleEffect` class
- `gbDropDesc` struct
- `gbDropUnit` struct
- `gbDropGroup` class
- `gbRain` class
- `gbSnow` class
- `BEZIER` struct (if present)

Include: `"gbengine/gbengine_types.h"`

Forward declare: `class gbVFile;`, `class gbTexture;`, `class gbRenderEffect;`, `class gbCamera;`, `class gbStaticChain;`, `struct gbRenderInfoObj;`

- [ ] **Step 2: Modify `src/gbengine/gbParticle.cpp`**

Remove class/struct declarations. Add `#include "gbengine/gbParticle.h"`. Keep method implementations.

- [ ] **Step 3: Modify `src/gbengine/gbWeather.cpp`**

Remove class/struct declarations (gbDropDesc, gbDropUnit, gbDropGroup, gbRain, gbSnow). Add `#include "gbengine/gbParticle.h"`. Keep method implementations.

- [ ] **Step 4: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 5: Commit**

```bash
git add include/gbengine/gbParticle.h src/gbengine/gbParticle.cpp src/gbengine/gbWeather.cpp
git commit -m "refactor(gbengine): extract gbParticle declarations to gbParticle.h"
```

---

## Task 15: Create `gbPrintFont.h` (Layer 4)

**Files:**
- Create: `include/gbengine/gbPrintFont.h`
- Modify: `src/gbengine/gbPrintFont.cpp`

- [ ] **Step 1: Create `include/gbengine/gbPrintFont.h`**

Extract from `gbPrintFont.cpp`:
- `gbPrintFont` class
- `gbPrintFontMgr` class (if present)

Include: `"gbengine/gbengine_types.h"`

Forward declare: `class gbGfxManager;`, `class gbMatrixStack;`

- [ ] **Step 2: Modify `src/gbengine/gbPrintFont.cpp`**

Remove class declarations. Add `#include "gbengine/gbPrintFont.h"`. Keep method implementations.

- [ ] **Step 3: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 4: Commit**

```bash
git add include/gbengine/gbPrintFont.h src/gbengine/gbPrintFont.cpp
git commit -m "refactor(gbengine): extract gbPrintFont declarations to gbPrintFont.h"
```

---

## Task 16: Clean up remaining .cpp files

**Files:**
- Modify: `src/gbengine/gbResManager.cpp` — remove gbRefObject/gbResource/gbResManager class declarations, add `#include "gbengine/gbTexture.h"` (which already has gbRefObject/gbResource)
- Modify: `src/gbengine/gbengine.cpp` — ensure it includes relevant headers instead of forward-declaring
- Modify: `src/gbengine/gbMesh.cpp` — remove any remaining `gbRenderInfoObj` duplicate struct definitions (use the one from gbSceneGraph.h)
- Modify: `src/gbengine/gbGeomNode.cpp` — remove `gbRenderInfoObj` duplicate
- Modify: `src/gbengine/gbActor.cpp` — remove `gbRenderInfoObj`, `gbNodeMsgObj` duplicates

- [ ] **Step 1: Audit all .cpp files for remaining struct/class declarations**

Search for `^class ` and `^struct ` declarations still in .cpp files (excluding forward declarations that are just `class Foo;`).

```bash
grep -n "^class \|^struct " src/gbengine/*.cpp
```

- [ ] **Step 2: Remove duplicates**

For each remaining declaration found:
- If it's already in a header, delete it and add the `#include`
- If it's a small helper struct used only in that file, leave it (it's an implementation detail)

- [ ] **Step 3: Resolve `gbRenderInfoObj` — single canonical location**

`gbRenderInfoObj` is defined in gbSceneGraph.cpp, gbMesh.cpp, and gbGeomNode.cpp with slightly different layouts. Pick the gbSceneGraph.h version as canonical and have other files include it.

- [ ] **Step 4: Build and verify**

```bash
cmake --build build_gbengine --config Release
```

- [ ] **Step 5: Commit**

```bash
git add -u src/gbengine/
git commit -m "refactor(gbengine): remove remaining duplicate declarations from .cpp files"
```

---

## Task 17: Final verification

- [ ] **Step 1: Full clean rebuild**

```bash
cmake -B build_gbengine -S . -G "Visual Studio 17 2022" -A Win32 -DBUILD_TARGET=gbengine
cmake --build build_gbengine --config Release
```

Expected: 0 errors, 0 warnings related to redefinition.

- [ ] **Step 2: Verify export count**

```bash
dumpbin /exports build_gbengine/Release/gbengine.dll | find /c "ordinal"
```

Expected: 1021 or 1022 exports.

- [ ] **Step 3: Verify no class/struct definitions remain in .cpp**

```bash
grep -rn "^class [A-Za-z].*{" src/gbengine/*.cpp
grep -rn "^struct [A-Za-z].*{" src/gbengine/*.cpp
```

Expected: No matches (only forward declarations like `class Foo;` are acceptable, plus helper structs that are implementation-only).

- [ ] **Step 4: Verify each header is self-contained**

Create a test file:
```cpp
// test_includes.cpp
#include "gbengine/gbChain.h"
#include "gbengine/gbMisc.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbMesh.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbAudio.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbVisNode.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbGeomNode.h"
#include "gbengine/gbActor.h"
#include "gbengine/gbParticle.h"
#include "gbengine/gbPrintFont.h"
int main() { return 0; }
```

Compile this to verify no missing includes or circular dependencies.

- [ ] **Step 5: Final commit (if any fixes needed)**

```bash
git add -A
git commit -m "refactor(gbengine): header separation complete - final fixes"
```
