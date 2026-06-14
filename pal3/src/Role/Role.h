#include "GlowObj.h"
#include "PalScriptWaitObj.h"
#include "Object.h"
#pragma once
// Auto-generated: Role

#include "ACTION_KIND.h"
#include "Actor.h"
#include "NPCInfo.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbGeomNode.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_types.h"

class RoleAtt;
class SceneObj;
class SceneProp;
class ScriptObj;

class Role : public Object, public PalScriptWaitObj, public GlowObj {
public:
    char _gap_000[96]; // +0x0
    char m_cmdqueue[48]; // +0x60
    int m_bInView; // +0x90
    gbVec3D m_groundpos; // +0x94
    char _gap_098[8]; // +0x98
    gbVec3D m_renderpos; // +0xA0
    char _gap_0A4[8]; // +0xA4
    NPCInfo m_npcinfo; // +0xAC
    char _gap_0B0[452]; // +0xB0
    int m_onlayer; // +0x274
    int m_active; // +0x278
    BYTE bCGMonster; // +0x27C
    char _gap_27D[3]; // +0x27D
    int nCGMonsterID; // +0x280
    int nCGMonsterType; // +0x284
    BYTE bRelive; // +0x288
    BYTE bInvincible; // +0x289
    char _gap_28A[2]; // +0x28A
    float fRattrapWait; // +0x28C
    float fMirrorWait; // +0x290
    BYTE bMirror; // +0x294
    char _gap_295[3]; // +0x295
    int fCGBIXIE; // +0x298
    BYTE bCGBIXIE; // +0x29C
    BYTE bCrossAlpha; // +0x29D
    char _gap_29E[2]; // +0x29E
    int fCrossAlpha; // +0x2A0
    BYTE bCGMonsterHitObj; // +0x2A4
    BYTE bStill; // +0x2A5
    char _gap_2A6[2]; // +0x2A6
    SceneProp * pCG_SceneProp; // +0x2A8
    Actor m_actor; // +0x2AC
    char _gap_2B0[816]; // +0x2B0
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
    BYTE m_bLeftWeapon; // +0x608
    BYTE m_bRightWeapon; // +0x609
    char _gap_60A[2]; // +0x60A
    int m_nRad; // +0x60C
    int m_nRealHeadPos; // +0x610
    int m_nOverlapState; // +0x614
    tagPOINT m_tpos; // +0x618
    char _gap_61C[4]; // +0x61C
    gbVec3D m_vTagHeadPos; // +0x620
    char _gap_624[8]; // +0x624
    int m_overlap; // +0x62C
    int m_bPathMove; // +0x630
    int m_pathMoveCounter; // +0x634
    gbVec3D m_lastpos; // +0x638
    char _gap_63C[8]; // +0x63C
    gbVec3D m_notePos; // +0x644
    char _gap_648[8]; // +0x648
    char m_path_region[7076]; // +0x650
    gbVec3D m_wanapos; // +0x21F4
    char _tail_21F8[232]; // +0x21F8
    // total size: 0x22E0 (8928)

    virtual void UpdateBoundingBox(struct gbAABBox *pBox); // 0x0041B640
    virtual gbGfxManager * GetGfxManager(); // 0x0041B6A0
    virtual ScriptObj * _sdtor_22(char a2); // 0x0041BE30
    static int CalcXueJianInit(int nVal, int nVal2); // 0x00408D10
    static int CalcLongKuiInit(int nVal, int nVal2); // 0x00408D80
    static int CalcZiXuanInit(int nVal, int nVal2); // 0x00408E30
    static int CalcChangQingInit(int nVal, int nVal2); // 0x00408E90
    static int CalcHuaYingInit(int nVal, int nVal2); // 0x00408F30
    Role(); // 0x00411900
    int CheckOBBCollision(struct gbOBBox *p); // 0x00418170
};
