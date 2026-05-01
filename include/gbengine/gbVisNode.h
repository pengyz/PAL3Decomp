#pragma once

#include "gbengine/gbChain.h"

// Forward declarations
class gbGfxManager;
class gbSceneGraph;
class gbRenderEffect;
struct gbRenderInfoObj;

struct gbNodeMsgObj {
    int data[4];  // 16 bytes message object
};

enum NodeBlend {
    BLEND_NONE = 0,
    BLEND_ALPHA = 1,
    BLEND_ADD = 2
};

/* ======== gbVisNode ======== */

class gbVisNode : public gbNBTreeNode {
public:
    gbNodeMsgObj* msgBuffer;     // +0x1c - message queue buffer
    int msgCapacity;             // +0x20 - message queue capacity (default 8)
    int msgUnused;               // +0x24 - unused field
    int msgOverflow;             // +0x28 - overflow flag
    int msgReadIndex;            // +0x2c - read index
    int msgWriteIndex;           // +0x30 - write index
    int renderPriority;          // +0x34
    float timeScale;             // +0x38 - time scale (default 1.0)
    int visible;                 // +0x3c - visibility flag (default 1)
    gbVisNode* cullNext;         // +0x40 - cull list next
    gbVisNode* cullPrev;         // +0x44 - cull list prev
    void* unknown48;             // +0x48
    void* unknown4c;             // +0x4c
    float blendValue;            // +0x50 - blend value
    NodeBlend blendMode;         // +0x54 - blend mode

    // Static members
    static gbGfxManager* pGfxMgr;
    static gbSceneGraph* pSceneGraph;

    gbVisNode();
    gbVisNode(const gbVisNode& other);
    virtual ~gbVisNode();

    void PushMessage(gbNodeMsgObj& msg);
    int PopMessage(gbNodeMsgObj& msg);
    virtual int Attach(gbRenderEffect* effect);
    virtual void AttachSelf(gbRenderEffect* effect);
    virtual void Render(gbRenderInfoObj* renderInfo);
    virtual void RenderShadowVolume(gbRenderInfoObj* renderInfo);
    virtual void Update();
    virtual void Reset(float time);
    void ShowNode(int show);
    void SetTimeScale(float scale);
    float GetTimeScale();
    int IsNodeShow();
    int GetRenderPriority();
    void SetRenderPriority(int priority);
    gbVisNode* GetCullNext();
    gbVisNode* GetCullPrev();
    virtual void GetBoundSphere(gbSphere* sphere);
    virtual void EnableShadow(int enable);
    void SetBlend(NodeBlend mode, float value);
    NodeBlend GetBlend(float& outValue);
    void SetBlendRecursive(NodeBlend mode, float value);
    void GetTotalBoundSphere(gbSphere* sphere);
    virtual int GetAABBox(gbAABBox* box);

    gbVisNode& operator=(const gbVisNode& other);
};
