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
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"

class BARRIER;
class CG_Entry;
class RELIVEPARAM;
class Role;
class Scene;

class CG_Scene {
public:
    BARRIER * m_pBarrier; // +0x0
    int m_nBarrier; // +0x4
    BYTE m_bShowHelper; // +0x8
    char _gap_009[3]; // +0x9
    CG_Entry * m_pFather; // +0xC
    Scene * m_pScene; // +0x10
    RoleCameraCtrl m_CameraCtrl; // +0x14
    char _gap_018[72]; // +0x18
    Role * m_pNPC; // +0x60
    RELIVEPARAM * m_pRelive; // +0x64
    SceneObj m_OBJ[256]; // +0x68
    char _gap_468[455680]; // +0x468
    OBJHELPER m_ObjHelper[256]; // +0x6F868
    char _gap_6FC68[11264]; // +0x6FC68
    ObjParam m_OBJPARAM[9]; // +0x72868
    char _gap_7288C[4032]; // +0x7288C
    GhostParam m_GHOSTPARAM[4]; // +0x7384C
    char _gap_7385C[176]; // +0x7385C
    Role * m_pBOSS; // +0x7390C
    BOSSHURT m_BossHurt; // +0x73910
    char _gap_73914[16]; // +0x73914
    NGHHURT m_NGHHurt; // +0x73924
    char _gap_73928[16]; // +0x73928
    BYTE m_bEdit; // +0x73938
    char _gap_73939[3]; // +0x73939
    int m_nLevel; // +0x7393C
    int m_nNPC; // +0x73940
    int m_nOBJ; // +0x73944
    int m_nSpecialOBJ; // +0x73948
    float m_fEffTime; // +0x7394C
    BYTE m_bGameOver; // +0x73950
    char _gap_73951[3]; // +0x73951
    TxtFile m_ObjFile; // +0x73954
    char _gap_73958[520]; // +0x73958
    gbRenderEffect * EFT_LINE; // +0x73B60
    gbRenderEffect * EFT_GEOM; // +0x73B64
    gbRenderEffect * EFT_GEOM_NOTEX; // +0x73B68
    gbRenderEffect * EFT_GEOM_NOTEX_LINE; // +0x73B6C
    gbTexture * m_pObjFlagTex; // +0x73B70
    gbVec3D m_SpecialObjPos[16]; // +0x73B74
    char _gap_73BB4[128]; // +0x73BB4
    BYTE m_DoFlingAct; // +0x73C34
    char _gap_73C35[3]; // +0x73C35
    CG_PROPINFO m_propinfo; // +0x73C38
    UINT m_propid; // +0x73C3C
    gbVec3D m_tmpPos; // +0x73C40
    char _gap_73C44[8]; // +0x73C44
    char m_PropArray[12]; // +0x73C4C
    // total size: 0x73C58 (474200)

};
