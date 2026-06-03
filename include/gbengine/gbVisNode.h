#pragma once

#include "gbengine/gbChain.h"

// Forward declarations (circular deps: gbGfxManager.h/gbSceneGraph.h include this indirectly)
class gbGfxManager;
class gbSceneGraph;
class gbRenderEffect;
struct gbRenderInfoObj;

struct gbNodeMsgObj {
    union {
        int data[4];            // raw array access (used by gbengine code)
        struct {
            int msgid;          // +0x00: message identifier
            unsigned int param[2]; // +0x04: message parameters (8 bytes)
            int _pad0C;         // +0x0C: padding
        };
    };
};

enum NodeBlend {
    BLEND_NONE = 0,
    BLEND_ALPHA = 1,
    BLEND_ADD = 2
};

/* ======== gbVisNode ======== */

class gbVisNode : public gbNBTreeNode {
public:
    // gbNBTreeNode ends at +0x1B (7 DWORDs: vtable, pNext, pParent, children[4])
    gbNodeMsgObj* msgBuffer;     // +0x1C [7]: message queue buffer
    int msgCapacity;             // +0x20 [8]: message queue capacity (default 8)
    int msgUnused;               // +0x24 [9]: unused field
    int msgOverflow;             // +0x28 [10]: overflow flag
    int msgReadIndex;            // +0x2C [11]: read index
    int msgWriteIndex;           // +0x30 [12]: write index
    int renderPriority;          // +0x34 [13]: render priority
    float timeScale;             // +0x38 [14]: time scale (default 1.0)
    int visible;                 // +0x3C [15]: visibility flag (default 1)
    int enableShadow;            // +0x40 [16]: shadow enable flag
    int field_44;                // +0x44 [17]: unknown
    gbVisNode* cullPrev;         // +0x48 [18]: cull list prev
    gbVisNode* cullNext;         // +0x4C [19]: cull list next
    float blendValue;            // +0x50 [20]: blend value
    NodeBlend blendMode;         // +0x54 [21]: blend mode

    // Static members
    static gbGfxManager* pGfxMgr;
    static gbSceneGraph* pSceneGraph;

    gbVisNode();
    gbVisNode(const gbVisNode& other);
    virtual ~gbVisNode();

    void PushMessage(gbNodeMsgObj& msg);
    int PopMessage(gbNodeMsgObj& msg);
    virtual void Render(gbRenderInfoObj* renderInfo);          // vtable[1]
    virtual void RenderShadowVolume(gbRenderInfoObj* renderInfo); // vtable[2]
    virtual void AttachSelf(gbRenderEffect* effect);           // vtable[3]
    virtual int Attach(gbRenderEffect* effect);                // vtable[4]
    virtual void Update();                                     // vtable[5]
    virtual void Reset(float time);                            // vtable[6]
    virtual void GetBoundSphere(gbSphere* sphere);             // vtable[7]
    virtual void EnableShadow(int enable);                     // vtable[8]
    virtual int GetAABBox(gbAABBox* box);                      // vtable[9]
    void ShowNode(int show);
    void SetTimeScale(float scale);
    float GetTimeScale();
    int IsNodeShow();
    int GetRenderPriority();
    void SetRenderPriority(int priority);
    gbVisNode* GetCullNext();
    gbVisNode* GetCullPrev();
    void SetBlend(NodeBlend mode, float value);
    NodeBlend GetBlend(float& outValue);
    void SetBlendRecursive(NodeBlend mode, float value);
    void GetTotalBoundSphere(gbSphere* sphere);

    gbVisNode& operator=(const gbVisNode& other);
};
