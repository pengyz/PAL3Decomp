#pragma once

#include "gbengine/gbVisNode.h"

// Forward declarations
class gbBaseMesh;
class gbStaticMesh;
class gbRenderEffect;
class gbTexture;
class gbVFile;
struct gbRenderInfoObj;

/* ======== gbGeomNode ======== */

class gbGeomNode : public gbVisNode {
public:
    // Memory layout based on decompilation
    gbMatrix4 localTransform;              // +0x58 (64 bytes)
    gbMatrix4 worldTransform;              // +0x98 (64 bytes)
    gbBaseMesh* mesh;                      // +0xd8
    void* animController;                  // +0xdc
    void* materialData;                    // +0xe0
    float animTime;                        // +0xe4
    void* bladeEffect;                     // +0xe8
    void* shadowData;                      // +0xec
    int shadowEnabled;                     // +0xf0
    int bladeEnabled;                      // +0xf4
    void* textureOverride;                 // +0xf8
    int animLoop;                          // +0xfc
    int loopPast;                          // +0x100
    void* boundingBox;                     // +0x104
    float bladeTime;                       // +0x108
    float bladeTimeScale;                  // +0x10c
    gbVec3D* lastBladePos;                 // +0x110

    // Constructor
    gbGeomNode(void);
    // Copy constructor
    gbGeomNode(const gbGeomNode& other);
    // Assignment operator
    gbGeomNode& operator=(const gbGeomNode& other);
    // Destructor
    virtual ~gbGeomNode(void);

    // Load geometry from CVD file
    int LoadFromFile(const char* filename, const char* texPath, void* progressCallback);
    int LoadCVDFile(const char* filename);
    void LoadCVDFromStream(gbVFile* file, float scale);
    static void LoadCVDFromStream(gbVFile* file, float scale, gbGeomNode** outNodes, int& outCount);

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
