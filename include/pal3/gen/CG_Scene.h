#pragma once
// Auto-generated: CG_Scene

#include "BOSSHURT.h"
#include "CG_PROPINFO.h"
#include "GhostParam.h"
#include "NGHHURT.h"
#include "OBJHELPER.h"
#include "ObjParam.h"
#include "RoleCameraCtrl.h"
#include "SceneObj.h"
#include "TxtFile.h"

class BARRIER;
class CG_Entry;
class RELIVEPARAM;
class Role;
class Scene;

class CG_Scene {
public:
    BARRIER * m_pBarrier; // +0x0
    int m_nBarrier; // +0x4
    unsigned char m_bShowHelper; // +0x8
    CG_Entry * m_pFather; // +0xC
    Scene * m_pScene; // +0x10
    RoleCameraCtrl m_CameraCtrl; // +0x14
    Role * m_pNPC; // +0x60
    RELIVEPARAM * m_pRelive; // +0x64
    SceneObj m_OBJ[256]; // +0x68
    OBJHELPER m_ObjHelper[256]; // +0x6F868
    ObjParam m_OBJPARAM[9]; // +0x72868
    GhostParam m_GHOSTPARAM[4]; // +0x7384C
    Role * m_pBOSS; // +0x7390C
    BOSSHURT m_BossHurt; // +0x73910
    NGHHURT m_NGHHurt; // +0x73924
    unsigned char m_bEdit; // +0x73938
    int m_nLevel; // +0x7393C
    int m_nNPC; // +0x73940
    int m_nOBJ; // +0x73944
    int m_nSpecialOBJ; // +0x73948
    float m_fEffTime; // +0x7394C
    unsigned char m_bGameOver; // +0x73950
    TxtFile m_ObjFile; // +0x73954
    gbRenderEffect * EFT_LINE; // +0x73B60
    gbRenderEffect * EFT_GEOM; // +0x73B64
    gbRenderEffect * EFT_GEOM_NOTEX; // +0x73B68
    gbRenderEffect * EFT_GEOM_NOTEX_LINE; // +0x73B6C
    gbTexture * m_pObjFlagTex; // +0x73B70
    gbVec3D m_SpecialObjPos[16]; // +0x73B74
    unsigned char m_DoFlingAct; // +0x73C34
    CG_PROPINFO m_propinfo; // +0x73C38
    unsigned long m_propid; // +0x73C3C
    gbVec3D m_tmpPos; // +0x73C40
    char m_PropArray[12]; // +0x73C4C (std::list<SceneProp *,std::allocator<SceneProp *> >)
    // total size: 0x73C58 (474200)

};
