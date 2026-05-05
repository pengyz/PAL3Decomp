# gbengine.dll Stub 批量实现计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 将 gbengine/stubs/ 中 ~327 个空函数实现为功能正确的 C++ 代码，清理所有 stub 文件。

**Architecture:** 按 L0→L3 依赖层次实现。每个类新建独立 .cpp 文件，从对应 stub 文件中提取签名并填充实现。参考 topo.dll 源码（数学类）、已有 gbengine 主文件（模式推断）、PAL3patch 社区代码（结构体）和头文件中的类布局。

**Tech Stack:** C++ (MSVC 6.0 SP5 风格), DirectX 9 COM interfaces, Win32 API

---

## 文件结构总览

### 需要删除的文件（冗余/空）

```
src/gbengine/stubs/stub_gbActor.cpp        (冗余，主文件已有)
src/gbengine/stubs/stub_gbAudioManager.cpp  (冗余)
src/gbengine/stubs/stub_gbCamera.cpp        (冗余)
src/gbengine/stubs/stub_gbGeomNode.cpp      (冗余)
src/gbengine/stubs/stub_gbGfxManager.cpp    (冗余)
src/gbengine/stubs/stub_gbPrintFont.cpp     (冗余)
src/gbengine/stubs/stub_gbResManager.cpp    (冗余)
src/gbengine/stubs/stub_gbSceneGraph.cpp    (冗余)
src/gbengine/stubs/stub_gbTexture.cpp       (冗余)
src/gbengine/stubs/stub_gbVFileSystem.cpp   (冗余)
src/gbengine/stubs/stub_gbVisNode.cpp       (冗余)
src/gbengine/stubs/stub_gbActorMgr.cpp      (空/冗余)
src/gbengine/stubs/stub_gbAudioMgrDesc.cpp  (空)
src/gbengine/stubs/stub_gbCamControler.cpp  (空)
src/gbengine/stubs/stub_gbChain1DNode.cpp   (空)
src/gbengine/stubs/stub_gbChain2DNode.cpp   (空)
src/gbengine/stubs/stub_gbColorQuad.cpp     (空)
src/gbengine/stubs/stub_gbEmitterData.cpp   (空)
src/gbengine/stubs/stub_gbEmitterSquare.cpp (空)
src/gbengine/stubs/stub_gbPartEmitter.cpp   (空)
src/gbengine/stubs/stub_gbPartParamControl.cpp (空)
src/gbengine/stubs/stub_gbParticleUnit.cpp  (空)
src/gbengine/stubs/stub_gbVolumeModifier.cpp (空)
```

### 需要新建的文件

```
L0: src/gbengine/gbMatrix4.cpp, gbVec3D.cpp, gbQuaternion.cpp,
    gbMatrixStack.cpp, gbRotMatrix.cpp, gbRay.cpp, gbOBBox.cpp,
    gbAABBox.cpp, gbSphere.cpp, gbPlane.cpp, gbColorFlt.cpp, BEZIER.cpp

L1: gbStaticChain.cpp, gbChain1D_ext.cpp, gbChain2D_ext.cpp,
    gbNBTreeNode_ext.cpp, gbNBTree_ext.cpp, gbBinaryTree_ext.cpp,
    gbBinaryTreeNode_ext.cpp, gbNameVarBuf.cpp, gbVFile1.cpp,
    gbVTextFile.cpp, gbPixelFormat.cpp, gbUIRect.cpp,
    gbTimeCounter.cpp, gbIndexBubble.cpp, gbGlobals.cpp

L2: gbImage2D.cpp (new), gbImage2DInfo.cpp, gbRenderEffect_impl.cpp,
    gbDynVertBuf.cpp, gbBaseMesh.cpp, gbStaticMesh.cpp,
    gbTexture_D3D.cpp, gbTextureArray.cpp, gbLightObj.cpp,
    gbVertPoolMgr_ext.cpp, gbPrintFontMgr.cpp

L3: CPK.cpp, gbAnimNodeGroup.cpp, gbEffectMgr_impl.cpp,
    gbParticleGroup.cpp, gbPartGroupParam.cpp, gbParticleEffect.cpp,
    gbVolModNode_ext.cpp, gbRain.cpp, gbSnow.cpp, gbDropGroup.cpp,
    gbSound2DNode.cpp, gbSound3DNode.cpp, gbCamQuakeControl.cpp,
    gbCamSpringControl.cpp, gbGfxManager_D3D_ext.cpp
```

**命名约定**：当一个类已经有部分实现在主文件（如 gbChain.cpp 已有 gbChain1D 基础方法）时，扩展方法放在 `XXX_ext.cpp` 中。当类完全没有主文件时直接用类名。

---

## Task 0: 清理冗余和空 stub 文件

**Files:**
- Delete: 23 个 stub 文件（见上方列表）

- [ ] **Step 1: 删除冗余 stub 文件（已有主文件的类）**

```bash
cd src/gbengine/stubs
rm stub_gbActor.cpp stub_gbAudioManager.cpp stub_gbCamera.cpp \
   stub_gbGeomNode.cpp stub_gbGfxManager.cpp stub_gbPrintFont.cpp \
   stub_gbResManager.cpp stub_gbSceneGraph.cpp stub_gbTexture.cpp \
   stub_gbVFileSystem.cpp stub_gbVisNode.cpp
```

- [ ] **Step 2: 删除空 stub 文件（0 个需实现的函数）**

```bash
rm stub_gbActorMgr.cpp stub_gbAudioMgrDesc.cpp stub_gbCamControler.cpp \
   stub_gbChain1DNode.cpp stub_gbChain2DNode.cpp stub_gbColorQuad.cpp \
   stub_gbEmitterData.cpp stub_gbEmitterSquare.cpp stub_gbPartEmitter.cpp \
   stub_gbPartParamControl.cpp stub_gbParticleUnit.cpp stub_gbVolumeModifier.cpp
```

- [ ] **Step 3: 验证编译不受影响**

```bash
cmake -B build_gbengine -DBUILD_TARGET=gbengine && cmake --build build_gbengine 2>&1 | head -50
```

如果出现链接符号缺失（来自被删除的 stub 中非空函数如 `gbActorMgr::operator=`），需将该函数移入对应主文件。

- [ ] **Step 4: 提交**

```bash
git add -A src/gbengine/stubs/
git commit -m "chore: remove redundant and empty gbengine stub files (23 files)"
```

---

## Task 1: L0 数学类 — gbMatrix4, gbVec3D, gbQuaternion, gbRotMatrix, gbMatrixStack

**Files:**
- Create: `src/gbengine/gbMatrix4.cpp`, `src/gbengine/gbVec3D.cpp`, `src/gbengine/gbQuaternion.cpp`, `src/gbengine/gbRotMatrix.cpp`, `src/gbengine/gbMatrixStack.cpp`
- Reference: `src/topo/gbMatrix4.cpp`, `src/topo/gbVec3D.cpp`, `src/topo/gbQuaternion.cpp`, `src/topo/gbRotMatrix.cpp`, `src/topo/gbMatrixStack.cpp`
- Delete: `src/gbengine/stubs/stub_gbMatrix4.cpp`, `stub_gbVec3D.cpp`, `stub_gbQuaternion.cpp`, `stub_gbRotMatrix.cpp`, `stub_gbMatrixStack.cpp`

**关键原则**：gbengine.dll 和 topo.dll 导出相同的数学函数。topo 源码中的实现可以直接复用。区别仅在于：
- gbengine 版本使用 `#include "gbengine/gbengine_types.h"` 而非 `#include "pal3.h"`
- 无需地址注释（不做字节匹配）

- [ ] **Step 1: 创建 src/gbengine/gbMatrix4.cpp**

从 `src/topo/gbMatrix4.cpp` 复制所有函数实现。保留函数体逻辑，修改头文件引用。只复制 stub 中列出的函数（36 个）。文件格式：

```cpp
#include "gbengine/gbengine_types.h"
#include <math.h>
#include <string.h>

// gbMatrix4 implementation for gbengine.dll
// Source: adapted from topo.dll implementation (identical logic)

gbMatrix4::gbMatrix4(void) {
    LoadIdentity();
}

void gbMatrix4::operator=(const gbMatrix4& other) {
    float* pSrc = (float*)&other;
    float* pDst = (float*)this;
    for (int i = 16; i != 0; i--) {
        *pDst++ = *pSrc++;
    }
}

void gbMatrix4::LoadIdentity(void) {
    memset(m, 0, sizeof(m));
    m[0][0] = 1.0f;
    m[1][1] = 1.0f;
    m[2][2] = 1.0f;
    m[3][3] = 1.0f;
}

// ... (remaining 33 functions from topo source)
```

对照 `src/gbengine/stubs/stub_gbMatrix4.cpp` 中的签名列表，确保每个函数都有实现。

- [ ] **Step 2: 创建 src/gbengine/gbVec3D.cpp**

同上，从 `src/topo/gbVec3D.cpp` 复制 13 个函数的实现。

- [ ] **Step 3: 创建 src/gbengine/gbQuaternion.cpp**

从 `src/topo/gbQuaternion.cpp` 复制 18 个函数的实现。

- [ ] **Step 4: 创建 src/gbengine/gbRotMatrix.cpp**

从 `src/topo/gbRotMatrix.cpp` 复制 6 个函数的实现。

- [ ] **Step 5: 创建 src/gbengine/gbMatrixStack.cpp**

从 `src/topo/gbMatrixStack.cpp` 复制 13 个函数的实现。

- [ ] **Step 6: 删除对应 stub 文件**

```bash
rm src/gbengine/stubs/stub_gbMatrix4.cpp src/gbengine/stubs/stub_gbVec3D.cpp \
   src/gbengine/stubs/stub_gbQuaternion.cpp src/gbengine/stubs/stub_gbRotMatrix.cpp \
   src/gbengine/stubs/stub_gbMatrixStack.cpp
```

- [ ] **Step 7: 编译验证**

```bash
cmake --build build_gbengine 2>&1 | grep -i error
```

Expected: 无编译错误（可能有链接警告）。

- [ ] **Step 8: 提交**

```bash
git add src/gbengine/gbMatrix4.cpp src/gbengine/gbVec3D.cpp \
        src/gbengine/gbQuaternion.cpp src/gbengine/gbRotMatrix.cpp \
        src/gbengine/gbMatrixStack.cpp src/gbengine/stubs/
git commit -m "feat(gbengine): implement L0 math classes from topo reference (86 functions)"
```

---

## Task 2: L0 几何类 — gbRay, gbOBBox, gbAABBox, gbSphere, gbPlane, BEZIER, gbColorFlt

**Files:**
- Create: `src/gbengine/gbRay.cpp`, `src/gbengine/gbOBBox.cpp`, `src/gbengine/gbAABBox.cpp`, `src/gbengine/gbSphere.cpp`, `src/gbengine/gbPlane.cpp`, `src/gbengine/BEZIER.cpp`, `src/gbengine/gbColorFlt.cpp`
- Reference: `src/gbengine/gbMath.cpp`（已有部分几何实现）, `include/gbengine/gbengine_types.h`
- Delete: 对应 7 个 stub 文件

**实现指导**：

这些类是几何基元，函数主要是：
- 构造/赋值（从类布局推断）
- 碰撞检测（射线-三角形、AABB 重叠、球体相交等）
- 标准数学公式

- [ ] **Step 1: 创建 src/gbengine/gbRay.cpp (8 个函数)**

```cpp
#include "gbengine/gbengine_types.h"
#include <math.h>

// gbRay 类布局（参考 gbMath.cpp 中的 gbIntersectTriangle）：
//   +0x00: gbVec3D origin
//   +0x0C: gbVec3D direction

gbRay::gbRay() {
    origin.x = origin.y = origin.z = 0.0f;
    direction.x = 0.0f;
    direction.y = 0.0f;
    direction.z = 1.0f;
}

gbRay::gbRay(const gbRay& other) {
    origin = other.origin;
    direction = other.direction;
}

gbRay& gbRay::operator=(const gbRay& other) {
    origin = other.origin;
    direction = other.direction;
    return *this;
}

// Set ray from origin point and direction vector
void gbRay::Set(gbVec3D* org, gbVec3D* dir) {
    origin = *org;
    direction = *dir;
}

// Intersect ray with plane, return parametric t
float gbRay::IntersectPlane(gbPlane* plane) {
    float denom = direction.x * plane->a + direction.y * plane->b + direction.z * plane->c;
    if (denom == 0.0f) return -1.0f;
    float numer = -(origin.x * plane->a + origin.y * plane->b + origin.z * plane->c + plane->d);
    return numer / denom;
}

// Intersect ray with sphere, return parametric t (closest hit)
float gbRay::IntersectSphere(gbSphere* sphere) {
    float dx = origin.x - sphere->center.x;
    float dy = origin.y - sphere->center.y;
    float dz = origin.z - sphere->center.z;
    float a = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
    float b = 2.0f * (dx * direction.x + dy * direction.y + dz * direction.z);
    float c = dx * dx + dy * dy + dz * dz - sphere->radius * sphere->radius;
    float disc = b * b - 4.0f * a * c;
    if (disc < 0.0f) return -1.0f;
    float sqrtDisc = (float)sqrt(disc);
    float t = (-b - sqrtDisc) / (2.0f * a);
    if (t < 0.0f) t = (-b + sqrtDisc) / (2.0f * a);
    return t;
}

// ... remaining functions follow same pattern
```

查看 `src/gbengine/stubs/stub_gbRay.cpp` 中完整签名列表来确定所有 8 个函数。

- [ ] **Step 2: 创建 gbOBBox.cpp (7 个函数)**

有向包围盒。参考 gbCamera.cpp 中的 ClipOBBox 调用方式。类布局：center(gbVec3D) + axes(3xgbVec3D) + halfExtent(gbVec3D)。

- [ ] **Step 3: 创建 gbAABBox.cpp (3 个函数)**

轴对齐包围盒。类布局：min(gbVec3D) + max(gbVec3D)。参考 gbCamera::ClipAABBox。

- [ ] **Step 4: 创建 gbSphere.cpp (3 个函数)**

球体。类布局：center(gbVec3D) + radius(float)。

- [ ] **Step 5: 创建 gbPlane.cpp (2 个函数)**

平面。类布局：a, b, c, d (float)。平面方程 ax+by+cz+d=0。

- [ ] **Step 6: 创建 BEZIER.cpp (5 个函数)**

贝塞尔曲线。参考 `src/gbengine/stubs/stub_BEZIER.cpp` 签名和 gbMath.cpp 中已有的 BEZIER 类使用模式。

- [ ] **Step 7: 创建 gbColorFlt.cpp (2 个函数)**

浮点颜色。类布局：Red, Green, Blue, Alpha (float)。PAL3patch 结构体已定义。

- [ ] **Step 8: 删除对应 stub 文件并编译验证**

```bash
rm src/gbengine/stubs/stub_gbRay.cpp src/gbengine/stubs/stub_gbOBBox.cpp \
   src/gbengine/stubs/stub_gbAABBox.cpp src/gbengine/stubs/stub_gbSphere.cpp \
   src/gbengine/stubs/stub_gbPlane.cpp src/gbengine/stubs/stub_BEZIER.cpp \
   src/gbengine/stubs/stub_gbColorFlt.cpp
cmake --build build_gbengine 2>&1 | grep -i error
```

- [ ] **Step 9: 提交**

```bash
git add src/gbengine/gb*.cpp src/gbengine/BEZIER.cpp src/gbengine/stubs/
git commit -m "feat(gbengine): implement L0 geometry classes (33 functions)"
```

---

## Task 3: L1 数据结构 — 链表扩展和树

**Files:**
- Create: `src/gbengine/gbChain1D_ext.cpp`, `src/gbengine/gbChain2D_ext.cpp`, `src/gbengine/gbStaticChain.cpp`, `src/gbengine/gbNBTreeNode_ext.cpp`, `src/gbengine/gbNBTree_ext.cpp`, `src/gbengine/gbBinaryTree_ext.cpp`, `src/gbengine/gbBinaryTreeNode_ext.cpp`
- Reference: `src/gbengine/gbChain.cpp`（已有基础方法）, `include/gbengine/gbChain.h`（完整类布局）
- Delete: 对应 7 个 stub 文件

**关键原则**：`gbChain.cpp` 已实现 gbChain1D 的构造/析构/AddNode/AddNodeOnHead 等基础方法。stub 中剩余的是 BeginIterate/Iterate/operator[]/IsContainNode/InsertBefore/GetNumNode 等。这些可以从类布局（见 gbChain.h）直接推断。

- [ ] **Step 1: 创建 src/gbengine/gbChain1D_ext.cpp (9 个函数)**

```cpp
#include "gbengine/gbChain.h"

// 以下函数是 gbChain1D 的补充方法
// 基础方法（构造/AddNode/DelNode等）已在 gbChain.cpp 中实现

bool gbChain1D::IsContainNode(gbChain1DNode* node) {
    gbChain1DNode* cur = pHead;
    while (cur) {
        if (cur == node) return true;
        cur = cur->pNext;
    }
    return false;
}

gbChain1D& gbChain1D::operator=(const gbChain1D& other) {
    if (this != &other) {
        pHead = other.pHead;
        pTail = other.pTail;
        nCount = other.nCount;
        pIterator = other.pIterator;
    }
    return *this;
}

gbChain1DNode* gbChain1D::BeginIterate() {
    pIterator = pHead;
    return pIterator;
}

gbChain1DNode* gbChain1D::Iterate() {
    if (pIterator) {
        pIterator = pIterator->pNext;
    }
    return pIterator;
}

gbChain1DNode* gbChain1D::operator[](int index) {
    if (index < 0 || index >= nCount) return NULL;
    gbChain1DNode* cur = pHead;
    for (int i = 0; i < index; i++) {
        cur = cur->pNext;
    }
    return cur;
}

int gbChain1D::GetNumNode() {
    return nCount;
}

void gbChain1D::AddNodeOnHead(gbChain1DNode* node) {
    if (!node) return;
    node->pNext = pHead;
    pHead = node;
    if (!pTail) pTail = node;
    nCount++;
}

void gbChain1D::AddNodeOnTail(gbChain1DNode* node) {
    if (!node) return;
    node->pNext = NULL;
    if (pTail) {
        pTail->pNext = node;
    } else {
        pHead = node;
    }
    pTail = node;
    nCount++;
}

void gbChain1D::ClearAllNodePtr() {
    pHead = NULL;
    pTail = NULL;
    nCount = 0;
    pIterator = NULL;
}

void gbChain1D::InsertBefore(gbChain1DNode* newNode, gbChain1DNode* beforeNode) {
    if (!newNode || !beforeNode) return;
    if (beforeNode == pHead) {
        newNode->pNext = pHead;
        pHead = newNode;
    } else {
        gbChain1DNode* prev = pHead;
        while (prev && prev->pNext != beforeNode) {
            prev = prev->pNext;
        }
        if (prev) {
            newNode->pNext = beforeNode;
            prev->pNext = newNode;
        }
    }
    nCount++;
}
```

注意：如果 gbChain.cpp 中已有 `operator=` 或 `AddNodeOnHead` 等函数导致重复定义，则 _ext 文件中只保留 stub 中列出但主文件中没有的函数。实现前先对比去重。

- [ ] **Step 2: 创建 src/gbengine/gbChain2D_ext.cpp (6 个函数)**

双向链表的补充方法。参考 gbChain.h 中 gbChain2D 布局和 gbChain.cpp 已有方法。

```cpp
#include "gbengine/gbChain.h"

gbChain2D& gbChain2D::operator=(const gbChain2D& other) {
    if (this != &other) {
        pHead = other.pHead;
        pTail = other.pTail;
        nDirection = other.nDirection;
        nCount = other.nCount;
        pIterator = other.pIterator;
    }
    return *this;
}

void gbChain2D::AddNode(gbChain2DNode* node) {
    if (!node) return;
    node->pNext = NULL;
    node->pPrev = pTail;
    if (pTail) pTail->pNext = node;
    else pHead = node;
    pTail = node;
    nCount++;
}

void gbChain2D::DelNodeFromChain(gbChain2DNode* node) {
    if (!node) return;
    if (node->pPrev) node->pPrev->pNext = node->pNext;
    else pHead = node->pNext;
    if (node->pNext) node->pNext->pPrev = node->pPrev;
    else pTail = node->pPrev;
    node->pPrev = NULL;
    node->pNext = NULL;
    nCount--;
}

bool gbChain2D::IsContainNode(gbChain2DNode* node) {
    gbChain2DNode* cur = pHead;
    while (cur) {
        if (cur == node) return true;
        cur = cur->pNext;
    }
    return false;
}

int gbChain2D::GetNumNode() {
    return nCount;
}

gbChain2DNode* gbChain2D::BeginIterate(int dir) {
    nDirection = dir;
    pIterator = (dir == 0) ? pHead : pTail;
    return pIterator;
}

gbChain2DNode* gbChain2D::Iterate() {
    if (!pIterator) return NULL;
    pIterator = (nDirection == 0) ? pIterator->pNext : pIterator->pPrev;
    return pIterator;
}
```

- [ ] **Step 3: 创建 src/gbengine/gbStaticChain.cpp (11 个函数)**

静态内存池链表。参考 gbChain.h 中完整类布局。

```cpp
#include "gbengine/gbChain.h"
#include <stdlib.h>
#include <string.h>

gbStaticChain::gbStaticChain() {
    pBuffer = NULL;
    pFreeHead = NULL;
    pUsedHead = NULL;
    pIterator = NULL;
    nMaxNodes = 0;
    nNodeSize = 0;
    nUsedCount = 0;
}

gbStaticChain& gbStaticChain::operator=(const gbStaticChain& other) {
    if (this != &other) {
        pBuffer = other.pBuffer;
        pFreeHead = other.pFreeHead;
        pUsedHead = other.pUsedHead;
        pIterator = other.pIterator;
        nMaxNodes = other.nMaxNodes;
        nNodeSize = other.nNodeSize;
        nUsedCount = other.nUsedCount;
    }
    return *this;
}

gbStaticChainNode* gbStaticChain::GetNode(int index) {
    return (gbStaticChainNode*)((char*)pBuffer + index * nNodeSize);
}

void gbStaticChain::InitBuffer(int maxNodes, int nodeSize) {
    nMaxNodes = maxNodes;
    nNodeSize = nodeSize;
    pBuffer = malloc(maxNodes * nodeSize);
    memset(pBuffer, 0, maxNodes * nodeSize);

    // 初始化 free list：所有节点串在一起
    pFreeHead = GetNode(0);
    for (int i = 0; i < maxNodes - 1; i++) {
        gbStaticChainNode* node = GetNode(i);
        node->pPrev = (i > 0) ? GetNode(i - 1) : NULL;
        node->pNext = GetNode(i + 1);
    }
    gbStaticChainNode* last = GetNode(maxNodes - 1);
    last->pPrev = (maxNodes > 1) ? GetNode(maxNodes - 2) : NULL;
    last->pNext = NULL;

    pUsedHead = NULL;
    nUsedCount = 0;
}

void gbStaticChain::ReleaseBuffer() {
    if (pBuffer) {
        free(pBuffer);
        pBuffer = NULL;
    }
    pFreeHead = NULL;
    pUsedHead = NULL;
    nMaxNodes = 0;
    nUsedCount = 0;
}

gbStaticChainNode* gbStaticChain::NewOneNode() {
    if (!pFreeHead) return NULL;
    gbStaticChainNode* node = pFreeHead;
    pFreeHead = pFreeHead->pNext;
    if (pFreeHead) pFreeHead->pPrev = NULL;

    // 插入 used list 头部
    node->pNext = pUsedHead;
    node->pPrev = NULL;
    if (pUsedHead) pUsedHead->pPrev = node;
    pUsedHead = node;
    nUsedCount++;
    return node;
}

void gbStaticChain::DelOneNode(gbStaticChainNode* node) {
    if (!node) return;
    // 从 used list 移除
    if (node->pPrev) node->pPrev->pNext = node->pNext;
    else pUsedHead = node->pNext;
    if (node->pNext) node->pNext->pPrev = node->pPrev;

    // 插回 free list 头部
    node->pNext = pFreeHead;
    node->pPrev = NULL;
    if (pFreeHead) pFreeHead->pPrev = node;
    pFreeHead = node;
    nUsedCount--;
}

gbStaticChainNode* gbStaticChain::BeginIterate() {
    pIterator = pUsedHead;
    return pIterator;
}

gbStaticChainNode* gbStaticChain::Iterate() {
    if (pIterator) pIterator = pIterator->pNext;
    return pIterator;
}

gbStaticChainNode* gbStaticChain::BeginReverseIterate() {
    // 找到 used list 的尾部
    pIterator = pUsedHead;
    if (pIterator) {
        while (pIterator->pNext) pIterator = pIterator->pNext;
    }
    return pIterator;
}

gbStaticChainNode* gbStaticChain::ReverseIterate() {
    if (pIterator) pIterator = pIterator->pPrev;
    return pIterator;
}

gbStaticChainNode* gbStaticChain::GetOldestNode() {
    // used list 尾部是最早插入的
    gbStaticChainNode* node = pUsedHead;
    if (!node) return NULL;
    while (node->pNext) node = node->pNext;
    return node;
}

gbStaticChainNode* gbStaticChain::GetNewestNode() {
    return pUsedHead;
}
```

- [ ] **Step 4: 创建 gbNBTreeNode_ext.cpp (10 个函数)**

N叉树节点。参考 gbChain.h 中 gbNBTreeNode 布局：继承 gbChain1DNode，有 pParent, children(gbChain1D), pChildIterator。

```cpp
#include "gbengine/gbChain.h"

gbNBTreeNode::gbNBTreeNode(const gbNBTreeNode& src) : gbChain1DNode(src) {
    pParent = src.pParent;
    children = src.children;
    pChildIterator = src.pChildIterator;
}

gbNBTreeNode& gbNBTreeNode::operator=(const gbNBTreeNode& other) {
    if (this != &other) {
        gbChain1DNode::operator=(other);
        pParent = other.pParent;
        children = other.children;
        pChildIterator = other.pChildIterator;
    }
    return *this;
}

gbChain1D& gbNBTreeNode::GetChildren() {
    return children;
}

gbNBTreeNode* gbNBTreeNode::GetFather() {
    return pParent;
}

gbNBTreeNode* gbNBTreeNode::BeginIterateChild() {
    pChildIterator = (gbNBTreeNode*)children.BeginIterate();
    return pChildIterator;
}

gbNBTreeNode* gbNBTreeNode::IterateChild() {
    pChildIterator = (gbNBTreeNode*)children.Iterate();
    return pChildIterator;
}

gbNBTreeNode* gbNBTreeNode::GetChild(int index) {
    return (gbNBTreeNode*)children[index];
}

int gbNBTreeNode::GetNumChildren() {
    return children.GetNumNode();
}

int gbNBTreeNode::IsChild(gbNBTreeNode* child) {
    return children.IsContainNode(child) ? 1 : 0;
}

void gbNBTreeNode::AddChild(gbNBTreeNode* child) {
    if (!child) return;
    child->pParent = this;
    children.AddNode(child);
}

void gbNBTreeNode::AddChildOnHead(gbNBTreeNode* child) {
    if (!child) return;
    child->pParent = this;
    children.AddNodeOnHead(child);
}

void gbNBTreeNode::AddChildOnTail(gbNBTreeNode* child) {
    if (!child) return;
    child->pParent = this;
    children.AddNodeOnTail(child);
}

void gbNBTreeNode::DelChildFromChain(gbNBTreeNode* child) {
    if (!child) return;
    children.DelNodeFromChain(child);
    child->pParent = NULL;
}
```

- [ ] **Step 5: 创建 gbNBTree_ext.cpp (2 个函数) 和 gbBinaryTree/Node (5 个函数)**

这些是简单的 getter/setter，直接从类布局实现。

- [ ] **Step 6: 删除对应 stub 文件并编译验证**

- [ ] **Step 7: 提交**

```bash
git commit -m "feat(gbengine): implement L1 data structures (42 functions)"
```

---

## Task 4: L1 工具类 — gbNameVarBuf, gbVFile1, gbVTextFile, gbPixelFormat, gbUIRect, gbTimeCounter, gbIndexBubble, globals

**Files:**
- Create: 8 个新 .cpp 文件
- Reference: `include/gbengine/gbVFileSystem.h`, `include/gbengine/gbGfxManager.h`, PAL3patch 代码
- Delete: 对应 8 个 stub 文件

- [ ] **Step 1: 创建 src/gbengine/gbGlobals.cpp (10 个全局函数)**

```cpp
#include "gbengine/gbengine_types.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbVFileSystem.h"
#include <windows.h>
#include <string.h>

// 从路径中提取目录部分
char* gbVfgetdir(const char* path, char* buf, int bufSize) {
    if (!path || !buf) return NULL;
    strncpy(buf, path, bufSize - 1);
    buf[bufSize - 1] = '\0';
    char* lastSlash = strrchr(buf, '\\');
    if (!lastSlash) lastSlash = strrchr(buf, '/');
    if (lastSlash) *(lastSlash + 1) = '\0';
    else buf[0] = '\0';
    return buf;
}

// 从路径中提取文件名部分
char* gbVfgetname(const char* path, char* buf, int bufSize) {
    if (!path || !buf) return NULL;
    const char* lastSlash = strrchr(path, '\\');
    if (!lastSlash) lastSlash = strrchr(path, '/');
    const char* name = lastSlash ? lastSlash + 1 : path;
    strncpy(buf, name, bufSize - 1);
    buf[bufSize - 1] = '\0';
    return buf;
}

// 创建图形管理器
gbGfxManager* gbCreateGraphManager(gbGfxDriverInfo* info) {
    /* UNCERTAIN - 需要知道 gbGfxManager_D3D 的具体创建方式 */
    return NULL;
}

// 加载灯光文件
gbVisNode* gbLoadLightFile(const char* filename) {
    /* UNCERTAIN - 需要知道灯光文件格式 */
    return NULL;
}

// 半角转全角
int gbConvertToSBC(unsigned char* src, int srcLen, unsigned char* dst, int dstLen) {
    /* UNCERTAIN - 需要字符集转换细节 */
    int written = 0;
    for (int i = 0; i < srcLen && written < dstLen - 1; i++) {
        if (src[i] >= 0x21 && src[i] <= 0x7E) {
            unsigned short sbc = src[i] + 0xFEE0;
            dst[written++] = (unsigned char)(sbc >> 8);
            dst[written++] = (unsigned char)(sbc & 0xFF);
        } else {
            dst[written++] = src[i];
        }
    }
    return written;
}

// 执行外部程序
int gbExecProgram(const char* cmdLine) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    memset(&pi, 0, sizeof(pi));
    if (!CreateProcessA(NULL, (LPSTR)cmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
        return 0;
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 1;
}

// 射线-三角形相交（Moller-Trumbore 算法）
int gbIntersectTriangle(gbVec3D* orig, gbVec3D* dir,
                        gbVec3D* v0, gbVec3D* v1, gbVec3D* v2,
                        gbVec3D* tuv) {
    gbVec3D edge1, edge2, pvec, tvec, qvec;
    edge1.x = v1->x - v0->x; edge1.y = v1->y - v0->y; edge1.z = v1->z - v0->z;
    edge2.x = v2->x - v0->x; edge2.y = v2->y - v0->y; edge2.z = v2->z - v0->z;

    // cross(dir, edge2)
    pvec.x = dir->y * edge2.z - dir->z * edge2.y;
    pvec.y = dir->z * edge2.x - dir->x * edge2.z;
    pvec.z = dir->x * edge2.y - dir->y * edge2.x;

    float det = edge1.x * pvec.x + edge1.y * pvec.y + edge1.z * pvec.z;
    if (det > -0.00001f && det < 0.00001f) return 0;
    float inv_det = 1.0f / det;

    tvec.x = orig->x - v0->x; tvec.y = orig->y - v0->y; tvec.z = orig->z - v0->z;
    float u = (tvec.x * pvec.x + tvec.y * pvec.y + tvec.z * pvec.z) * inv_det;
    if (u < 0.0f || u > 1.0f) return 0;

    qvec.x = tvec.y * edge1.z - tvec.z * edge1.y;
    qvec.y = tvec.z * edge1.x - tvec.x * edge1.z;
    qvec.z = tvec.x * edge1.y - tvec.y * edge1.x;
    float v = (dir->x * qvec.x + dir->y * qvec.y + dir->z * qvec.z) * inv_det;
    if (v < 0.0f || u + v > 1.0f) return 0;

    float t = (edge2.x * qvec.x + edge2.y * qvec.y + edge2.z * qvec.z) * inv_det;
    tuv->x = t; tuv->y = u; tuv->z = v;
    return 1;
}

// 启用/禁用系统热键
void gbEnableSystemKeys(HINSTANCE hInst, int enable) {
    /* UNCERTAIN - 可能使用 RegisterHotKey/UnregisterHotKey 或低级键盘钩子 */
    if (!enable) {
        // 禁用 Alt+Tab, Alt+F4 等
    }
}

// 获取当前显示模式
void gbGetCurDispMode(int& width, int& height, int& bpp) {
    DEVMODEA dm;
    memset(&dm, 0, sizeof(dm));
    dm.dmSize = sizeof(dm);
    EnumDisplaySettingsA(NULL, ENUM_CURRENT_SETTINGS, &dm);
    width = dm.dmPelsWidth;
    height = dm.dmPelsHeight;
    bpp = dm.dmBitsPerPel;
}

// 获取当前系统时间
void gbGetRealWorldTime(gbRealWorldTime* t) {
    SYSTEMTIME st;
    GetLocalTime(&st);
    t->year = st.wYear;
    t->month = st.wMonth;
    t->day = st.wDay;
    t->hour = st.wHour;
    t->minute = st.wMinute;
    t->second = st.wSecond;
}
```

- [ ] **Step 2: 创建 gbTimeCounter.cpp (2 个函数)**

高精度计时器，使用 QueryPerformanceCounter。

- [ ] **Step 3: 创建 gbPixelFormat.cpp (6 个函数)**

像素格式转换工具。参考 D3DFORMAT 枚举和常见 ARGB/RGB565 转换模式。

- [ ] **Step 4: 创建 gbNameVarBuf.cpp (6 个函数)**

名称-值对缓冲区。类似简单的 hash map。

- [ ] **Step 5: 创建 gbVFile1.cpp (1), gbVTextFile.cpp (4), gbUIRect.cpp (3), gbIndexBubble.cpp (1)**

这些都是小型工具类，从签名和上下文可推断实现。

- [ ] **Step 6: 删除对应 stub 文件，编译验证**

- [ ] **Step 7: 提交**

```bash
git commit -m "feat(gbengine): implement L1 utility classes (38 functions)"
```

---

## Task 5: L2 图像和纹理 — gbImage2D, gbImage2DInfo, gbTexture_D3D, gbTextureArray

**Files:**
- Create: `src/gbengine/gbImage2D_impl.cpp`, `src/gbengine/gbImage2DInfo.cpp`, `src/gbengine/gbTexture_D3D.cpp`, `src/gbengine/gbTextureArray.cpp`
- Reference: `include/gbengine/gbGfxManager.h`, PAL3patch（gbResource 结构体）, IJL15（Intel JPEG Library）
- Delete: 对应 4 个 stub 文件

**注意**：gbImage2D 使用 IJL15.dll（Intel JPEG Library）加载 JPEG。gbTexture_D3D 使用 IDirect3DDevice9::CreateTexture。

- [ ] **Step 1: 创建 gbImage2D_impl.cpp (15+1 个函数)**

```cpp
#include "gbengine/gbGfxManager.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>

// gbImage2D 类布局（推断）:
//   +0x00: int width
//   +0x04: int height
//   +0x08: int bitCount (8/16/24/32)
//   +0x0C: gbPixelFmtType pixelFmt
//   +0x10: unsigned char* pBits
//   +0x14: gbImage2DInfo* pInfo
//   +0x18: gbColorQuad palette[256] (if 8-bit)

gbImage2D::gbImage2D() {
    memset(this, 0, sizeof(gbImage2D)); /* UNCERTAIN - 需确认类大小 */
}

gbImage2D::~gbImage2D() {
    Release();
}

int gbImage2D::GetWidth() { return width; }
int gbImage2D::GetHeight() { return height; }
int gbImage2D::GetBitCount() { return bitCount; }
gbPixelFmtType gbImage2D::GetPixelFmtType() { return pixelFmt; }
gbImage2DInfo* gbImage2D::GetImgInfo() { return pInfo; }

unsigned char* gbImage2D::GetBits() { return pBits; }
unsigned char* gbImage2D::GetBits(int x, int y) {
    if (!pBits) return NULL;
    int pitch = width * (bitCount / 8);
    return pBits + y * pitch + x * (bitCount / 8);
}

gbColorQuad* gbImage2D::GetPalEntry(int index) {
    /* UNCERTAIN */ return NULL;
}

unsigned char* gbImage2D::CreateImage(int w, int h, int bpp) {
    Release();
    width = w;
    height = h;
    bitCount = bpp;
    int size = w * h * (bpp / 8);
    pBits = (unsigned char*)malloc(size);
    memset(pBits, 0, size);
    return pBits;
}

void gbImage2D::Release() {
    if (pBits) { free(pBits); pBits = NULL; }
    width = 0;
    height = 0;
}

int gbImage2D::LoadImageFile(char* filename, int flags) {
    /* UNCERTAIN - 使用 IJL15 加载 JPEG，或 TGA/BMP 自行解析 */
    return 0;
}

void gbImage2D::ScaleTo(int newW, int newH) {
    /* UNCERTAIN - 双线性缩放 */
}

void gbImage2D::WriteJpegImage(char* filename, int quality) {
    /* UNCERTAIN - 使用 IJL15 写 JPEG */
}

int gbImage2D::WriteJpegToBuffer(unsigned char* buffer, int bufSize) {
    /* UNCERTAIN */ return 0;
}

void gbImage2D::WriteTGAImage(char* filename) {
    /* UNCERTAIN - TGA 文件写入 */
}
```

- [ ] **Step 2: 创建其余 3 个文件**

gbTexture_D3D (7 个函数): 围绕 IDirect3DTexture9 的加载/锁定/释放操作。
gbTextureArray (1 个函数): 纹理数组容器。
gbImage2DInfo (1 个函数): 图像元信息。

- [ ] **Step 3: 删除 stub 文件，编译验证，提交**

```bash
git commit -m "feat(gbengine): implement L2 image/texture classes (24 functions)"
```

---

## Task 6: L2 网格和顶点 — gbDynVertBuf, gbBaseMesh, gbStaticMesh, gbVertPoolMgr

**Files:**
- Create: `src/gbengine/gbDynVertBuf.cpp`, `src/gbengine/gbBaseMesh_impl.cpp`, `src/gbengine/gbStaticMesh.cpp`, `src/gbengine/gbVertPoolMgr_ext.cpp`
- Reference: `include/gbengine/gbMesh.h`, `src/gbengine/gbMesh.cpp`（已有部分网格实现）
- Delete: 对应 4 个 stub 文件

- [ ] **Step 1: 创建 gbDynVertBuf.cpp (11 个函数)**

动态顶点缓冲区，封装 IDirect3DVertexBuffer9 的 Lock/Unlock/DrawPrimitive 流程。Getter 函数从类布局推断。Render 函数标记 UNCERTAIN。

- [ ] **Step 2: 创建 gbBaseMesh_impl.cpp (7) 和 gbStaticMesh.cpp (2)**

- [ ] **Step 3: 创建 gbVertPoolMgr_ext.cpp (1)**

- [ ] **Step 4: 删除 stub，编译验证，提交**

```bash
git commit -m "feat(gbengine): implement L2 mesh/vertex classes (21 functions)"
```

---

## Task 7: L2 渲染和灯光 — gbRenderEffect, gbLightObj, gbPrintFontMgr

**Files:**
- Create: `src/gbengine/gbRenderEffect_impl.cpp`, `src/gbengine/gbLightObj.cpp`, `src/gbengine/gbPrintFontMgr_ext.cpp`
- Reference: `include/gbengine/gbRenderEffect.h`（完整类布局）, PAL3patch（gbLight 结构体）
- Delete: 对应 3 个 stub 文件

- [ ] **Step 1: 创建 gbRenderEffect_impl.cpp (13 个函数)**

```cpp
#include "gbengine/gbRenderEffect.h"
#include <d3d9.h>

// 类布局 (from gbRenderEffect.h):
//   +0x00: vfptr
//   +0x04: ID3DXEffect* m_pEffect
//   +0x08: unsigned int m_nPasses
//   +0x0C: unsigned int m_dwFlags
//   +0x10: D3DVERTEXELEMENT9* m_pDecl
//   +0x14: int m_nTechnique

gbRenderEffect::gbRenderEffect(ID3DXEffect* pEffect, unsigned int flags) {
    m_pEffect = pEffect;
    m_dwFlags = flags;
    m_nPasses = 0;
    m_pDecl = NULL;
    m_nTechnique = 0;
}

gbRenderEffect::~gbRenderEffect() {
    if (m_pEffect) {
        m_pEffect->Release();
        m_pEffect = NULL;
    }
}

gbRenderEffect::gbRenderEffect(const gbRenderEffect& other) {
    m_pEffect = other.m_pEffect;
    if (m_pEffect) m_pEffect->AddRef();
    m_nPasses = other.m_nPasses;
    m_dwFlags = other.m_dwFlags;
    m_pDecl = other.m_pDecl;
    m_nTechnique = other.m_nTechnique;
}

gbRenderEffect& gbRenderEffect::operator=(const gbRenderEffect& other) {
    if (this != &other) {
        if (m_pEffect) m_pEffect->Release();
        m_pEffect = other.m_pEffect;
        if (m_pEffect) m_pEffect->AddRef();
        m_nPasses = other.m_nPasses;
        m_dwFlags = other.m_dwFlags;
        m_pDecl = other.m_pDecl;
        m_nTechnique = other.m_nTechnique;
    }
    return *this;
}

ID3DXEffect* gbRenderEffect::GetD3DEffect() { return m_pEffect; }
unsigned int gbRenderEffect::GetFlag() { return m_dwFlags; }
void gbRenderEffect::SetDeclHandle(IDirect3DVertexDeclaration9* decl) { m_pDecl = (D3DVERTEXELEMENT9*)decl; /* UNCERTAIN */ }

int gbRenderEffect::Compare(gbRenderEffect* other) {
    if (m_dwFlags < other->m_dwFlags) return -1;
    if (m_dwFlags > other->m_dwFlags) return 1;
    return 0;
}

int gbRenderEffect::Validate() {
    if (!m_pEffect) return 0;
    return SUCCEEDED(m_pEffect->ValidateTechnique(NULL)) ? 1 : 0; /* UNCERTAIN */
}

int gbRenderEffect::Begin() {
    if (!m_pEffect) return 0;
    UINT passes = 0;
    m_pEffect->Begin(&passes, 0);
    m_nPasses = passes;
    return (int)passes;
}

void gbRenderEffect::End() {
    if (m_pEffect) m_pEffect->End();
}

void gbRenderEffect::Pass(int passIndex) {
    if (m_pEffect) m_pEffect->BeginPass(passIndex); /* UNCERTAIN - 可能是 Pass() */
}

void gbRenderEffect::Apply() {
    if (m_pEffect) m_pEffect->CommitChanges();
}

void gbRenderEffect::SetVariant(char* name, void* value) {
    /* UNCERTAIN - 需要知道 value 的类型如何确定 */
    if (m_pEffect && name) {
        D3DXHANDLE h = m_pEffect->GetParameterByName(NULL, name);
        if (h) m_pEffect->SetValue(h, value, sizeof(float) * 4);
    }
}

void gbRenderEffect::SetVariant(GBPARAMHANDLE handle, void* value) {
    /* UNCERTAIN */ 
}

void gbRenderEffect::GetVariant(char* name, void* value) {
    /* UNCERTAIN */
}

void gbRenderEffect::GetVariant(GBPARAMHANDLE handle, void* value) {
    /* UNCERTAIN */
}
```

- [ ] **Step 2: 创建 gbLightObj.cpp (7 个函数)**

灯光对象，封装 D3DLIGHT9。参考 PAL3patch 中 gbLight 结构体。

- [ ] **Step 3: 创建 gbPrintFontMgr_ext.cpp (1 个函数)**

- [ ] **Step 4: 删除 stub，编译验证，提交**

```bash
git commit -m "feat(gbengine): implement L2 rendering/light classes (21 functions)"
```

---

## Task 8: L3 文件包 — CPK

**Files:**
- Create: `src/gbengine/CPK.cpp`
- Reference: PAL3patch `rawcpk_open/read/close`, OpenPAL3 CPK 解析器, `include/gbengine/gbVFileSystem.h`
- Delete: `src/gbengine/stubs/stub_CPK.cpp`

- [ ] **Step 1: 创建 src/gbengine/CPK.cpp (16 个函数)**

CPK 是仙剑3的文件打包格式。关键特征：
- CRC32 哈希用于文件名查找
- LZO 压缩
- 文件表头在 CPK 文件开头

```cpp
#include "gbengine/gbVFileSystem.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>

// CPK 文件格式常量
#define CPK_LABEL 0x1A545352  // "RST\x1A"
#define CPK_VERSION 1

// CRC32 表（标准 polynomial 0xEDB88320）
unsigned long* CPK::CrcTable = NULL;

void CPK::InitCrcTable() {
    if (CrcTable) return;
    CrcTable = (unsigned long*)malloc(256 * sizeof(unsigned long));
    for (int i = 0; i < 256; i++) {
        unsigned long crc = i;
        for (int j = 0; j < 8; j++) {
            if (crc & 1) crc = (crc >> 1) ^ 0xEDB88320UL;
            else crc >>= 1;
        }
        CrcTable[i] = crc;
    }
}

unsigned long CPK::Crc(const char* str) {
    if (!CrcTable) InitCrcTable();
    unsigned long crc = 0xFFFFFFFF;
    while (*str) {
        char c = *str++;
        if (c >= 'A' && c <= 'Z') c += 32; // to lowercase
        if (c == '/') c = '\\';             // normalize path separator
        crc = CrcTable[(crc ^ c) & 0xFF] ^ (crc >> 8);
    }
    return crc ^ 0xFFFFFFFF;
}

unsigned long CPK::GetAllocationGranularity() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwAllocationGranularity;
}

void CPK::Reset() {
    /* UNCERTAIN - 重置 CPK 内部状态 */
}

bool CPK::IsLoaded() {
    /* UNCERTAIN - 检查是否已加载 */
    return false;
}

bool CPK::IsValidCPK(const char* filename) {
    /* UNCERTAIN - 检查文件头标记 */
    HANDLE hFile = CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) return false;
    unsigned long label = 0;
    DWORD read;
    ReadFile(hFile, &label, 4, &read, NULL);
    CloseHandle(hFile);
    return label == CPK_LABEL;
}

bool CPK::Load(const char* filename) {
    /* UNCERTAIN - 加载 CPK 文件表 */
    return false;
}

bool CPK::Unload() {
    /* UNCERTAIN - 卸载 CPK */
    return false;
}

int CPK::GetTableIndex(const char* filename) {
    unsigned long crc = Crc(filename);
    return GetTableIndexFromCRC(crc);
}

int CPK::GetTableIndexFromCRC(unsigned long crc) {
    /* UNCERTAIN - 在文件表中查找 CRC */
    return -1;
}

bool CPK::GetFileSize(unsigned long& origSize, unsigned long& compSize, unsigned long index) {
    /* UNCERTAIN */ return false;
}

bool CPK::IsDir(unsigned long index) {
    /* UNCERTAIN */ return false;
}

bool CPK::IsFileExist(const char* filename) {
    return GetTableIndex(filename) >= 0;
}

bool CPK::Close(CPKFile* file) {
    /* UNCERTAIN */ return false;
}

bool CPK::Read(void* buffer, unsigned long size, CPKFile* file) {
    /* UNCERTAIN - 读取并解压数据 */ return false;
}

unsigned long CPK::Seek(CPKFile* file, int offset, unsigned long origin) {
    /* UNCERTAIN */ return 0;
}
```

- [ ] **Step 2: 删除 stub，编译验证，提交**

```bash
git commit -m "feat(gbengine): implement L3 CPK file system (16 functions)"
```

---

## Task 9: L3 动画和特效 — gbAnimNodeGroup, gbEffectMgr

**Files:**
- Create: `src/gbengine/gbAnimNodeGroup.cpp`, `src/gbengine/gbEffectMgr_impl.cpp`
- Reference: `include/gbengine/gbParticle.h`, `include/gbengine/gbGfxManager.h`
- Delete: 对应 2 个 stub 文件

- [ ] **Step 1: 创建 gbAnimNodeGroup.cpp (12 个函数)**

动画节点组管理器。大部分函数标记 UNCERTAIN，因为动画文件格式和内部状态未知。提供合理骨架实现。

- [ ] **Step 2: 创建 gbEffectMgr_impl.cpp (11 个函数)**

特效管理器，管理 gbRenderEffect 实例。Init/Release/NewRenderEffect/GetRenderEffect 等。利用已有的 gbRenderEffect 类布局。

- [ ] **Step 3: 删除 stub，编译验证，提交**

```bash
git commit -m "feat(gbengine): implement L3 animation/effects (23 functions)"
```

---

## Task 10: L3 粒子系统 — gbParticleGroup, gbPartGroupParam, gbParticleEffect, gbVolModNode

**Files:**
- Create: `src/gbengine/gbParticleGroup.cpp`, `src/gbengine/gbPartGroupParam.cpp`, `src/gbengine/gbParticleEffect.cpp`, `src/gbengine/gbVolModNode_ext.cpp`
- Reference: `include/gbengine/gbParticle.h`, `src/gbengine/gbParticle.cpp`
- Delete: 对应 4 个 stub 文件

- [ ] **Step 1: 实现粒子系统 4 个类 (20 个函数)**

多数函数标记 UNCERTAIN。Getter 函数可确定实现，粒子更新/创建逻辑需推断。

- [ ] **Step 2: 删除 stub，编译验证，提交**

```bash
git commit -m "feat(gbengine): implement L3 particle system (20 functions)"
```

---

## Task 11: L3 杂项 — gbRain, gbSnow, gbDropGroup, gbSound2D/3DNode, gbCamQuake/Spring, gbGfxManager_D3D

**Files:**
- Create: `src/gbengine/gbRain.cpp`, `src/gbengine/gbSnow.cpp`, `src/gbengine/gbDropGroup.cpp`, `src/gbengine/gbSound2DNode.cpp`, `src/gbengine/gbSound3DNode.cpp`, `src/gbengine/gbCamQuakeControl.cpp`, `src/gbengine/gbCamSpringControl.cpp`, `src/gbengine/gbGfxManager_D3D_ext.cpp`
- Delete: 对应 8 个 stub 文件

- [ ] **Step 1: 实现天气类 (5 个函数)**

gbRain (2), gbSnow (2), gbDropGroup (1) — 天气粒子效果。

- [ ] **Step 2: 实现音频节点 (2 个函数)**

gbSound2DNode (1), gbSound3DNode (1) — Miles Sound System 封装。标记 UNCERTAIN。

- [ ] **Step 3: 实现相机控制器 (2 个函数)**

gbCamQuakeControl (1), gbCamSpringControl (1) — 参考已实现的 gbCamControler 基类。

- [ ] **Step 4: 实现 gbGfxManager_D3D::SetTexture (1 个函数)**

```cpp
#include "gbengine/gbGfxManager.h"

void gbGfxManager_D3D::SetTexture(gbTextureArray* texArray) {
    /* UNCERTAIN - 设置 D3D 纹理到各阶段 */
    if (!texArray) return;
    // IDirect3DDevice9::SetTexture(stage, pTexture)
}
```

- [ ] **Step 5: 删除所有剩余 stub 文件，编译验证**

```bash
# 验证 stubs 目录为空
ls src/gbengine/stubs/
# 预期：空目录或不存在
```

- [ ] **Step 6: 提交**

```bash
git commit -m "feat(gbengine): implement L3 weather/audio/camera (10 functions)"
```

---

## Task 12: 最终验证和清理

**Files:**
- Possibly modify: `CMakeLists.txt`（如果需要调整 GLOB 范围）
- Delete: `src/gbengine/stubs/` 目录（如果为空）

- [ ] **Step 1: 确认所有 stub 文件已删除**

```bash
find src/gbengine/stubs/ -name "*.cpp" | wc -l
# 预期: 0
```

- [ ] **Step 2: 完整编译测试**

```bash
cmake -B build_gbengine -DBUILD_TARGET=gbengine
cmake --build build_gbengine 2>&1 | tee build_log.txt
grep -c "error" build_log.txt
```

修复所有编译错误（缺少头文件引用、类型未定义等）。

- [ ] **Step 3: 统计 UNCERTAIN 标记**

```bash
grep -rn "UNCERTAIN" src/gbengine/*.cpp | wc -l
```

输出 UNCERTAIN 统计报告。

- [ ] **Step 4: 删除空 stubs 目录**

```bash
rmdir src/gbengine/stubs 2>/dev/null || true
```

- [ ] **Step 5: 最终提交**

```bash
git add -A
git commit -m "chore(gbengine): remove stubs directory, all functions implemented"
```

---

## 总结

| Task | 层次 | 函数数 | 复杂度 |
|------|------|--------|--------|
| 0 | - | 0 (清理) | 低 |
| 1 | L0 | 86 | 低（复用 topo） |
| 2 | L0 | 33 | 低-中 |
| 3 | L1 | 42 | 低-中 |
| 4 | L1 | 38 | 中 |
| 5 | L2 | 24 | 中-高 |
| 6 | L2 | 21 | 中-高 |
| 7 | L2 | 21 | 中 |
| 8 | L3 | 16 | 高 |
| 9 | L3 | 23 | 高 |
| 10 | L3 | 20 | 高 |
| 11 | L3 | 10 | 中 |
| 12 | - | 0 (验证) | 低 |
| **Total** | | **~334** | |
