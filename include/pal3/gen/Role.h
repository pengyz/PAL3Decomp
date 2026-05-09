#pragma once
// Auto-generated: Role

#include "ACTION_KIND.h"
#include "Actor.h"
#include "GlowObj.h"
#include "NPCInfo.h"
#include "NavTriangle.h"
#include "Object.h"
#include "PalScriptWaitObj.h"
#include "PathObj.h"
#include "ROLE_BEHAVIOUR.h"
#include "ROLE_CTRL.h"
#include "gbVec3D.h"
#include "tagPOINT.h"

class PalScript;
class RoleAtt;
class SceneObj;
class SceneProp;
class gbGeomNode;

class Role : public Object, public PalScriptWaitObj, public GlowObj {
public:
    std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > > m_cmdqueue; // +0x60
    int m_bInView; // +0x90
    gbVec3D m_groundpos; // +0x94
    gbVec3D m_renderpos; // +0xA0
    NPCInfo m_npcinfo; // +0xAC
    int m_onlayer; // +0x274
    int m_active; // +0x278
    unsigned char bCGMonster; // +0x27C
    int nCGMonsterID; // +0x280
    int nCGMonsterType; // +0x284
    unsigned char bRelive; // +0x288
    unsigned char bInvincible; // +0x289
    float fRattrapWait; // +0x28C
    float fMirrorWait; // +0x290
    unsigned char bMirror; // +0x294
    float fCGBIXIE; // +0x298
    unsigned char bCGBIXIE; // +0x29C
    unsigned char bCrossAlpha; // +0x29D
    float fCrossAlpha; // +0x2A0
    unsigned char bCGMonsterHitObj; // +0x2A4
    unsigned char bStill; // +0x2A5
    SceneProp * pCG_SceneProp; // +0x2A8
    Actor m_actor; // +0x2AC
    unsigned char m_MachineryID; // +0x500
    int m_bPet; // +0x504
    float m_scale; // +0x508
    NavTriangle m_tri; // +0x50C
    Role::SPECIAL_ACTION m_specact; // +0x530
    ROLE_CTRL m_ctrlmode; // +0x554
    ROLE_BEHAVIOUR m_curbehaviour; // +0x558
    int m_bPathOut; // +0x55C
    int m_bShowActAutoStand; // +0x560
    unsigned char m_bNeedShowActEnd; // +0x564
    ACTION_KIND m_curact; // +0x568
    float m_curspeed; // +0x56C
    float m_curforce; // +0x570
    gbVec3D m_velocity; // +0x574
    gbVec3D m_desirevel; // +0x580
    gbVec3D m_steer; // +0x58C
    gbVec3D m_lastautodir; // +0x598
    gbVec3D m_targetpt; // +0x5A4
    int m_targetlayer; // +0x5B0
    int m_targetportal; // +0x5B4
    gbVec3D m_startpt; // +0x5B8
    gbVec3D m_wanderdir; // +0x5C4
    int m_talkflag; // +0x5D0
    Role * m_talknpc; // +0x5D4
    PalScript * m_talkscript; // +0x5D8
    ROLE_BEHAVIOUR m_talkoldbeh; // +0x5DC
    ACTION_KIND m_talkoldact; // +0x5E0
    float m_talkoldface; // +0x5E4
    SceneObj * m_talkobj; // +0x5E8
    int m_mstate; // +0x5EC
    RoleAtt * m_matt; // +0x5F0
    float m_mfreedist; // +0x5F4
    float m_mattackrange; // +0x5F8
    float m_mfindradius; // +0x5FC
    float m_statetime; // +0x600
    gbGeomNode * m_weapon; // +0x604
    unsigned char m_bLeftWeapon; // +0x608
    unsigned char m_bRightWeapon; // +0x609
    int m_nRad; // +0x60C
    int m_nRealHeadPos; // +0x610
    int m_nOverlapState; // +0x614
    tagPOINT m_tpos; // +0x618
    gbVec3D m_vTagHeadPos; // +0x620
    int m_overlap; // +0x62C
    int m_bPathMove; // +0x630
    int m_pathMoveCounter; // +0x634
    gbVec3D m_lastpos; // +0x638
    gbVec3D m_notePos; // +0x644
    PathObj m_path; // +0x650
    float m_rotate; // +0x2278
    gbVec3D m_wanapos; // +0x227C
    // total size: 0x2288 (8840)

    static int CreateXueJian(int a1, int a2); // 0x00408D10
    static int CreateLongKui(int a1, int a2); // 0x00408D80
    static int CreateZiXuan(int a1, int a2); // 0x00408E30
    static int CreateChangQing(int a1, int a2); // 0x00408E90
    static int CreateHuaYing(int a1, int a2); // 0x00408F30
};
