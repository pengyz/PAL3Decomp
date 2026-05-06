/**
 * gbengine struct definitions for IDA import
 *
 * Usage in IDA:
 *   File > Load file > Parse C header file...
 *   Or via IDAPython: idc.parse_decls("""...""", 0)
 *
 * After import, set function 'this' parameter types to verify layout.
 * e.g. for gbGeomNode methods, change first arg type to "gbGeomNode *"
 */

// Basic types
typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef int BOOL;

// ============ Math Types ============

struct gbVec3D {
    float x, y, z;
};

struct gbVec4D {
    float x, y, z, w;
};

struct gbColorQuad {
    unsigned char b, g, r, a;
};

struct gbColorFlt {
    float r, g, b, a;
};

struct gbMatrix4 {
    float m[4][4];  // 64 bytes
};

struct gbAABBox {
    struct gbVec3D vMin;
    struct gbVec3D vMax;
};

struct gbOBBox {
    struct gbMatrix4 matrix;
    struct gbVec3D extent;
};

struct gbSphere {
    struct gbVec3D center;
    float radius;
};

// ============ Chain/Tree (base classes) ============

// gbChain1DNode: vptr(4) + pNext(4) = 8 bytes
struct gbChain1DNode {
    void *__vftable;        // +0x00
    struct gbChain1DNode *pNext;  // +0x04
};

// gbChain1D: 16 bytes (no vptr)
struct gbChain1D {
    struct gbChain1DNode *pHead;      // +0x00
    struct gbChain1DNode *pTail;      // +0x04
    int nCount;                       // +0x08
    struct gbChain1DNode *pIterator;  // +0x0C
};

// gbNBTreeNode: inherits gbChain1DNode(8) + pParent(4) + children(16) = 28 bytes
struct gbNBTreeNode {
    void *__vftable;                  // +0x00
    struct gbNBTreeNode *pNext;       // +0x04
    struct gbNBTreeNode *pParent;     // +0x08
    struct gbChain1D children;        // +0x0C (16 bytes)
};
// sizeof(gbNBTreeNode) = 0x1C = 28

// ============ gbVisNode ============
// Inherits gbNBTreeNode (28 bytes) + own fields = 0x58 (88 bytes)

struct gbNodeMsgObj {
    int data[4];  // 16 bytes
};

struct gbVisNode {
    // --- gbNBTreeNode base (28 bytes) ---
    void *__vftable;                  // +0x00
    struct gbNBTreeNode *pNext;       // +0x04
    struct gbNBTreeNode *pParent;     // +0x08
    struct gbChain1D children;        // +0x0C (16 bytes: pHead, pTail, nCount, pIterator)
    // --- gbVisNode own fields ---
    struct gbNodeMsgObj *msgBuffer;   // +0x1C
    int msgCapacity;                  // +0x20
    int msgUnused;                    // +0x24
    int msgOverflow;                  // +0x28
    int msgReadIndex;                 // +0x2C
    int msgWriteIndex;                // +0x30
    int renderPriority;               // +0x34
    float timeScale;                  // +0x38
    int visible;                      // +0x3C
    struct gbVisNode *cullNext;       // +0x40
    struct gbVisNode *cullPrev;       // +0x44
    void *unknown48;                  // +0x48
    void *unknown4c;                  // +0x4C
    float blendValue;                 // +0x50
    int blendMode;                    // +0x54
};
// sizeof(gbVisNode) = 0x58 = 88

// ============ Forward decls ============

struct gbAnimNodeGroup;
struct gbStaticMesh;
struct gbBaseMesh;
struct gbRenderEffect;
struct gbRenderInfoObj;
struct gbMatrixStack;
struct gbGfxManager;

// ============ gbGeomNode ============
// Inherits gbVisNode (0x58) + own fields
// sizeof(gbGeomNode) = 0x118 = 280

struct gbAnimCurve;  // polymorphic: virtual GetValue + virtual dtor

struct gbGeomNode {
    // --- gbVisNode base (0x58 bytes) ---
    void *__vftable;                  // +0x00
    struct gbNBTreeNode *pNext;       // +0x04
    struct gbNBTreeNode *pParent;     // +0x08
    struct gbChain1D children;        // +0x0C (16 bytes)
    struct gbNodeMsgObj *msgBuffer;   // +0x1C
    int msgCapacity;                  // +0x20
    int msgUnused;                    // +0x24
    int msgOverflow;                  // +0x28
    int msgReadIndex;                 // +0x2C
    int msgWriteIndex;                // +0x30
    int renderPriority;               // +0x34
    float timeScale;                  // +0x38
    int visible;                      // +0x3C
    struct gbVisNode *cullNext;       // +0x40
    struct gbVisNode *cullPrev;       // +0x44
    void *unknown48;                  // +0x48
    void *unknown4c;                  // +0x4C
    float blendValue;                 // +0x50
    int blendMode;                    // +0x54
    // --- gbGeomNode own fields ---
    struct gbMatrix4 worldTransform;  // +0x58 (64 bytes) - GetCacheToWorld returns &this->worldTransform
    struct gbMatrix4 staticTransform; // +0x98 (64 bytes)
    struct gbAnimCurve *pAnimTranslate; // +0xD8
    struct gbAnimCurve *pAnimRotate;    // +0xDC
    struct gbAnimCurve *pAnimScale;     // +0xE0
    float scaleValue;                 // +0xE4 (init 1.0f)
    int hasAnimation;                 // +0xE8
    struct gbAnimNodeGroup *animController; // +0xEC
    double currentTime;               // +0xF0 (8 bytes)
    float animMaxTime;                // +0xF8
    int animLoop;                     // +0xFC
    int loopPast;                     // +0x100
    int bladeEnabled;                 // +0x104
    struct gbStaticMesh *mesh;        // +0x108
    void *pLightmapData;              // +0x10C
    int numAttachPoints;              // +0x110
    void *pAttachPointArray;          // +0x114
};
// sizeof(gbGeomNode) = 0x118

// ============ Verification offsets ============
// GetCacheToWorld returns (char*)this + 0x58  => &worldTransform
// GetMesh returns *(this+66)  => +0x108 => mesh  (66*4=264=0x108)
// GetAnimMaxTime returns *((float*)this+62) => +0xF8 => animMaxTime (62*4=248=0xF8)
// GetLoopPast returns *(this+64)  => +0x100 => loopPast (64*4=256=0x100)
// EnableBlade sets *(this+65)  => +0x104 => bladeEnabled (65*4=260=0x104)
// Reset accesses *((double*)this+30) => +0xF0 => currentTime (30*8=240=0xF0)
// Reset accesses *((float*)this+62) => +0xF8 => animMaxTime
// Reset writes *(this+64) => +0x100 => loopPast
// Render/RenderShadowVolume check *(this+15) => +0x3C => visible (from gbVisNode)
// Render/RenderShadowVolume use *(this+66) => +0x108 => mesh

// ============ gbBaseMesh (partial, for mesh vtable calls) ============

struct gbBaseMesh_vtbl {
    void *dtor;                     // +0x00: destructor
    void *ComputeShadowVolume;      // +0x04
    void *RenderShadowVolume;       // +0x08: void(gbVisNode*, gbRenderInfoObj*)
    void *DrawSubSet;               // +0x0C: void(int, gbRenderInfoObj*)
};

// ============ gbMatrixStack ============

struct gbMatrixStack_vtbl {
    void *Push;
    void *Pop;
    void *LoadMatrix;
};
