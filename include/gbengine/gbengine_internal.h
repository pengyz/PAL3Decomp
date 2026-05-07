#pragma once
/**
 * gbengine_internal.h - Internal class definitions for gbengine
 * Classes that don't have their own public header but need definitions for compilation.
 */

#include "gbengine/gbengine_types.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbRenderEffect.h"
#include <string.h>

// Forward declarations
class gbGfxManager;
class gbVolModNode;
class gbVolumeModifier;
class gbResource;

// ========= gbResManager =========
// sizeof = 0x0C (12 bytes) - simple resource list manager
class gbResManager {
public:
    gbResource** array;  // +0x00: resource array
    int capacity;        // +0x04: array capacity
    int count;           // +0x08: current resource count

    gbResManager();
    gbResManager(const gbResManager& other);
    ~gbResManager();
    gbResManager& operator=(const gbResManager& other);
    void AddResource(gbResource* res);
    void DelResource(gbResource* res);
    gbResource* FindResByName(const char* name);
    void CleanAllResource(void);
};

// ========= BEZIER =========
class BEZIER {
public:
    int coeff[4];           // +0x00: binomial coefficients (1,3,3,1)
    gbVec3D ctrlPt[4];     // +0x10: 4 control points (48 bytes)
    char dirty;             // +0x40: needs coefficient recomputation

public:
    BEZIER(struct gbVec3D * p0);

public:
    BEZIER();

public:
    ~BEZIER();

public:
    class BEZIER & operator=(class BEZIER const & p0);

public:
    struct gbVec3D * GetControlPt();

public:
    void SetControlPt(struct gbVec3D * p0);

private:
    void computerCoefficient();

public:
    struct gbVec3D getInterpolatePoint(float p0);

public:
    struct gbVec3D getTangentVector(float p0);

};

// ========= gbAnimNodeGroup =========
class gbAnimNodeGroup {
public:
    void* pNode;              // +0x00: pointer to root animation node
    int field_04;             // +0x04
    double lastTime;          // +0x08: ctor sets as {int 0, float -1.0f}; Update reads/writes as double
    double elapsedTime;       // +0x10: ctor sets as {int 0, int 0}; Update reads/writes as double
    int field_18;             // +0x18: frame counter
    int field_1c;             // +0x1c
    int field_20;             // +0x20: total frame count
    int field_24;             // +0x24
    int field_28;             // +0x28: loop counter
    int isDead;               // +0x2c: dead flag
    int field_30;             // +0x30: active/priority flag
    gbMatrix4 posMatrix;      // +0x34: position matrix (64 bytes)
    // total: 0x74 = 116 bytes

    static gbGfxManager* s_pGfxMgr;  // stored at DAT_101379b0

public:
    gbAnimNodeGroup(class gbGfxManager * p0);
    ~gbAnimNodeGroup();
    class gbAnimNodeGroup & operator=(class gbAnimNodeGroup const & p0);
    void Attach();
    class gbAnimNodeGroup * Clone();
    int IsDead();
    void LoadFromFile(char * p0);
    void Reset();
    void SetPosition(struct gbMatrix4 const & p0);
    void SetPosition(struct gbVec3D const & p0);
    void SetPriority(int p0);
    static void SetSoundFileDir(char * p0);
    void SetToDead();
    void ShowGroup(int p0);
    void Update();
};

// ========= gbEmitterSquare =========
struct gbEmitterSquare {
    char _stub_data[128];

public:
    gbEmitterSquare();

public:
    struct gbEmitterSquare & operator=(struct gbEmitterSquare const & p0);

};

// gbGfxManager_D3D: full definition in gbGfxManager.h

// ========= gbMatrixStack =========
class gbMatrixStack {
public:
    struct gbMatrix4 *pStack;   // +0x00: pointer to array of gbMatrix4
    int maxDepth;               // +0x04: maximum stack depth
    int curDepth;               // +0x08: current stack index
    int dirty;                  // +0x0C: invalidation flag

public:
    gbMatrixStack(int p0);

public:
    ~gbMatrixStack();

public:
    class gbMatrixStack & operator=(class gbMatrixStack const & p0);

public:
    int GetDepth();

public:
    struct gbMatrix4 * GetTop();

public:
    void LoadIdentity();

public:
    void LoadMatrix(struct gbMatrix4 * p0);

public:
    void MultMatrix(struct gbMatrix4 * p0);

public:
    void Pop();

public:
    void Push();

public:
    void Rotate(struct gbQuaternion & p0);

public:
    void Rotate(float p0, struct gbVec3D & p1);

public:
    void Scale(struct gbVec3D & p0);

public:
    void Scale(float p0, float p1, float p2);

public:
    void Translate(struct gbVec3D & p0);

public:
    void Translate(float p0, float p1, float p2);

};

// ========= gbVTextFile =========
class gbVTextFile {
public:
    char lineBuf[0x400];    // +0x000: line buffer (1024 bytes)
    gbVFile* m_pFile;       // +0x400: file handle

public:
    gbVTextFile(char * p0);

public:
    gbVTextFile();

public:
    ~gbVTextFile();

public:
    class gbVTextFile & operator=(class gbVTextFile const & p0);

public:
    void Close();

public:
    void Open(char * p0);

public:
    char * ReadLine();

public:
    void Rewind();

};

// ========= gbVolModNode =========
// Inherits: gbChain1DNode -> gbNBTreeNode -> gbVisNode -> gbVolModNode
// Layout:
//   +0x00: vfptr
//   +0x04: gbChain1DNode::pNext
//   +0x08: gbNBTreeNode::pParent
//   +0x0C: gbNBTreeNode::children (gbChain1D, 16 bytes)
//   +0x1C: gbVisNode fields start (msgBuffer, etc.)
//   +0x58: gbMatrix4 localMatrix (local transform, 64 bytes)
//   +0x98: gbMatrix4 worldMatrix (world transform, 64 bytes)
//   +0xD8: gbVolumeModifier* pVolMod
class gbVolModNode {
public:
    char _base_visnode[0x54];       // base class data (after vfptr: chain+nbtree+visnode fields)
    gbMatrix4 localMatrix;          // +0x58: local transform matrix
    gbMatrix4 worldMatrix;          // +0x98: world transform matrix
    gbVolumeModifier* pVolMod;      // +0xD8: gbVolumeModifier pointer (ref-counted)

public:
    gbVolModNode(class gbVolModNode const & p0);
    gbVolModNode();
    virtual ~gbVolModNode();
    class gbVolModNode & operator=(class gbVolModNode const & p0);
    virtual int Attach(class gbRenderEffect * p0);
    virtual void GetBoundSphere(struct gbSphere * p0);
    class gbLightObj * GetLightObj();
    virtual void Render(struct gbRenderInfoObj * p0);
    void SetVolModObj(class gbVolumeModifier * p0);
};

// ========= gbLight =========
// Light parameters structure (maps to D3DLIGHT9, 104 bytes)
struct gbLight {
    int type;
    gbColorFlt diffuse;
    gbColorFlt specular;
    gbColorFlt ambient;
    gbVec3D position;
    gbVec3D direction;
    float range;
    float falloff;
    float attenuation0;
    float attenuation1;
    float attenuation2;
    float theta;
    float phi;
};

// ========= gbVolumeModifier =========
// sizeof(gbVolumeModifier) == 0xD8 (216 bytes)
// Base class for light objects and other volume modifiers
class gbVolumeModifier : public gbRefObject {
public:
    int lightType;          // +0x08: light type (0=point, 1=spot, 2=directional)
    gbColorFlt diffuse;     // +0x0C: diffuse color (16 bytes)
    gbColorFlt ambient;     // +0x1C: ambient color (16 bytes)
    int enabled;            // +0x2C: enabled flag
    int _field30;           // +0x30
    int _field34;           // +0x34
    int _field38;           // +0x38
    int _field3C;           // +0x3C
    float range;            // +0x40: effective range (DWORD index 16)
    float _field44;         // +0x44
    float _field48;         // +0x48
    float attenuation0;     // +0x4C: constant attenuation
    float attenuation1;     // +0x50: linear attenuation
    float attenuation2;     // +0x54: quadratic attenuation
    float _field58;         // +0x58
    gbSphere boundSphere;   // +0x5C: bounding sphere (16 bytes, DWORD index 23-26)
    gbLight sysLight;       // +0x6C: D3D-compatible light structure (104 bytes)
    int bDirty;             // +0xD4: needs recompute flag
    // Total: 0xD8 = 216 bytes

    gbVolumeModifier(const gbVolumeModifier& other);
    gbVolumeModifier();
    virtual ~gbVolumeModifier();
    virtual float GetEffectOnPoint(const gbVec3D& point, int useAttenuation);
    virtual void Compute(gbVolModNode* volmod);
    virtual int GetType(void);
    virtual const gbSphere* GetBoundSphere(void);
    gbVolumeModifier& operator=(const gbVolumeModifier& other);
};

