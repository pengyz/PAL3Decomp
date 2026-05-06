#pragma once

#include "gbengine/gbVisNode.h"

// Forward declarations
class gbBaseMesh;
class gbStaticMesh;
class gbRenderEffect;
class gbTexture;
class gbVFile;
class gbAnimNodeGroup;
struct gbRenderInfoObj;

// Animation curve interface - polymorphic objects with virtual GetValue + dtor
// Used for translation, rotation, scale interpolation in gbGeomNode
// IDA: called as (**pCurve)(&result, time) in Update, virtual dtor in ~gbGeomNode
class gbAnimCurve {
public:
    virtual void GetValue(void* result, float time) = 0;
    virtual ~gbAnimCurve() {}
};

/* ======== gbGeomNode ======== */

// sizeof(gbGeomNode) = 0x118 = 280
class gbGeomNode : public gbVisNode {
public:
    // gbVisNode base: 0x00-0x57 (88 bytes)
    gbMatrix4 worldTransform;              // +0x58 (64B) - GetCacheToWorld returns &this->worldTransform
    gbMatrix4 staticTransform;             // +0x98 (64B) - initial local pose/orientation
    gbAnimCurve* pAnimTranslate;           // +0xD8: translation curve (virtual dtor + GetValue)
    gbAnimCurve* pAnimRotate;              // +0xDC: rotation curve
    gbAnimCurve* pAnimScale;              // +0xE0: scale curve
    float scaleValue;                      // +0xE4: uniform scale (init 1.0f)
    int hasAnimation;                      // +0xE8: non-zero if animated
    gbAnimNodeGroup* animController;       // +0xEC: animation node group
    double currentTime;                    // +0xF0: current playback time
    float animMaxTime;                     // +0xF8: total animation duration
    int animLoop;                          // +0xFC: loop count (0=infinite)
    int loopPast;                          // +0x100: completed loop count
    int bladeEnabled;                      // +0x104: blade trail effect enabled
    gbStaticMesh* mesh;                    // +0x108: geometry mesh (gbRefObject)
    void* pLightmapData;                   // +0x10C: lightmap/attach data (heap alloc)
    int numAttachPoints;                   // +0x110: attach point count
    void* pAttachPointArray;               // +0x114: attach point transform array

    // Constructor
    gbGeomNode(void);
    // Copy constructor
    gbGeomNode(const gbGeomNode& other);
    // Assignment operator
    gbGeomNode& operator=(const gbGeomNode& other);
    // Destructor
    virtual ~gbGeomNode(void);

    // Load geometry from CVD file
    int LoadFromFile(const char* filename, const char* texPath, void (__cdecl *progressCallback)(int, int));

private:
    int LoadCVDFile(const char* filename);
    void LoadCVDFromStream(gbVFile* file, float scale);
    static void LoadCVDFromStream(gbVFile* file, float scale, gbGeomNode** outNodes, int& outCount);

public:

    virtual void Update(void);
    virtual void AttachSelf(gbRenderEffect* effect);
    virtual int Attach(gbRenderEffect* effect);
    virtual void Render(gbRenderInfoObj* renderInfo);
    virtual void RenderShadowVolume(gbRenderInfoObj* renderInfo);
    virtual void Reset(float time);
    virtual void GetBoundSphere(gbSphere* sphere);
    void SetAnimLoop(int loop);
    virtual void EnableShadow(int enable);
    virtual int GetAABBox(gbAABBox* box);
    void SetBladeTime(float time);
    void SetBladeTimeScale(float scale);
    gbVec3D* GetLastBladePos(gbGeomNode* node);
    void ReplaceTexture(const char* textureName);
    void ReplaceTexture(gbTexture* texture);
    gbOBBox* GetOBBox(gbOBBox* box);
    gbOBBox* GetTotalOBBox(gbOBBox* box);
    void EnableBlade(int enable);
    gbMatrix4* GetCacheToWorld();
    int GetLoopPast();
    gbBaseMesh* GetMesh();
    float GetAnimMaxTime();
};
