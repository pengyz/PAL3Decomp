#pragma once
// Auto-generated: SceneObj

#include "GlowObj.h"
#include "MyMdl.h"
#include "ObjectInfo.h"
#include "PalScriptWaitObj.h"
#include "SaveTask.h"
#include "TaskMgr.h"
#include "subPARAM.h"

class PalScript;
class PathObj;
class SceneMapObj;
class gbSound3DNode;

class SceneObj : public PalScriptWaitObj, public GlowObj, public TaskMgr {
public:
    SaveTask _SaveTaskInfo; // +0x4C
    float m_fTime; // +0x58
    float m_fDeltaTime; // +0x5C
    float m_fTimeScale; // +0x60
    float m_deltatime; // +0x64
    int m_bLockPropUI; // +0x68
    unsigned char m_bLockCamera; // +0x6C
    int m_bProcessLinkObj; // +0x70
    int m_bCallProcessGroupObj; // +0x74
    int m_bMainGroupObj; // +0x78
    unsigned long dwEffGroupRunningID; // +0x7C
    unsigned char bCGObj; // +0x80
    char sCGSHELF[64]; // +0x81
    tagRECT rCGSelfArea; // +0xC4
    tagRECT rTouchAreaCG; // +0xD4
    float fLastTime; // +0xE4
    subPARAM mParam; // +0xE8
    gbVec3D mVelocity; // +0x130
    float mTime; // +0x13C
    gbVec3D mStorePos; // +0x140
    int mRetrorse; // +0x14C
    int mTouchCounter; // +0x150
    int m_iState; // +0x154
    unsigned char m_bCVDOver; // +0x158
    gbOBBox mOBBox; // +0x15C
    char m_pObjMsgBuffer[256]; // +0x1A8
    char m_pObjMsgBuffer2[256]; // +0x2A8
    gbVec3D m_renderpos; // +0x3A8
    char m_subobj[36]; // +0x3B4 (SceneObj::SubObj)
    MyMdl m_mdl; // +0x3D8
    ObjectInfo m_info; // +0x42C
    PathObj * m_path; // +0x688
    SceneMapObj * m_pmap; // +0x68C
    unsigned char m_mapindex; // +0x690
    int m_pushboxdir; // +0x694
    tagRECT m_maprect; // +0x698
    int m_liftrole; // +0x6A8
    char m_common[48]; // +0x6AC (std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >)
    gbSound3DNode * m_snd; // +0x6DC
    float m_radius; // +0x6E0
    PalScript * m_runscript; // +0x6E4
    float m_fRotateX; // +0x6E8
    float m_fRotateY; // +0x6EC
    float m_fRotateZ; // +0x6F0
    float m_fParam; // +0x6F4
    // total size: 0x6F8 (1784)

    char Update(unsigned int a2); // 0x00407B50
    int CreateUI(); // 0x00536260
    void * Destructor(); // 0x005362F0
    void DestroyInternal(); // 0x00536310
};
