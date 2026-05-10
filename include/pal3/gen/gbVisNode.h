#pragma once
// Auto-generated: gbVisNode

#include "NodeBlend.h"
#include "gbNBTreeNode.h"

class gbOctreeNode;

class gbVisNode : public gbNBTreeNode {
public:
    char MsgBuffer[24]; // +0x1C (gbCycleQueue<gbNodeMsgObj>)
    int Priority; // +0x34
    float TimeScale; // +0x38
    int bShow; // +0x3C
    int bDoShadow; // +0x40
    gbOctreeNode * pCullObj; // +0x44
    gbVisNode * pCullPrev; // +0x48
    gbVisNode * pCullNext; // +0x4C
    float BlendParam; // +0x50
    NodeBlend BlendFlag; // +0x54
    gbSceneGraph * pSceneGraph; // +0x0
    gbGfxManager * pGfxMgr; // +0x0
    // total size: 0x58 (88)

    void EnableShadow(int a2); // 0x005420D8
    int GetAABBox(struct gbAABBox *a2); // 0x005420DE
    void AttachSelf(struct gbRenderEffect *a2); // 0x005420FC
    void RenderShadowVolume(struct gbRenderInfoObj *a2); // 0x00542102
    void GetBoundSphere(struct gbSphere *a2); // 0x0054210E
    void Reset(float a2); // 0x00542114
    void Update(); // 0x0054211A
    int Attach(struct gbRenderEffect *a2); // 0x00542120
    void Render(struct gbRenderInfoObj *a2); // 0x00542126
};
