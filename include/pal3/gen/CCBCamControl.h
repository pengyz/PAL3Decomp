#pragma once
// Auto-generated: CCBCamControl

#include "CCCTData.h"
#include "tagCam.h"

class CCBStage;
class CCBStageCam;
class CUtil;

class CCBCamControl {
public:
    CCCTData m_CCT; // +0x0
    CCBStage * m_pStage; // +0x68FB0
    CCBStageCam * m_pCam; // +0x68FB4
    CUtil * m_pUtil; // +0x68FB8
    BYTE m_bRunning; // +0x68FBC
    void * * m_fp; // +0x68FC0
    int m_nCurList; // +0x68FD0
    int m_nCurTask; // +0x68FD4
    float m_fStartSpeed; // +0x68FD8
    float m_fNextSpeed; // +0x68FDC
    gbVec3D m_vecSpeed; // +0x68FE0
    gbVec3D m_vecNextSpeed; // +0x68FEC
    float m_fDistance; // +0x68FF8
    float m_fQuake; // +0x68FFC
    float m_fQuakeDec; // +0x69000
    float m_fQuakeFre; // +0x69004
    tagCam m_StartPos; // +0x69008
    tagCam m_CurPos; // +0x69020
    gbVec3D m_vecCurPos; // +0x69038
    gbOBBox m_OBBox; // +0x69044
    gbGeomNode * m_pPointer; // +0x69090
    gbVec3D m_vecCircleCenter; // +0x69094
    gbVec3D m_vecCircleEnd; // +0x690A0
    BYTE m_bShowCircleSet; // +0x690AC
    BYTE m_bCircleCenterSelected; // +0x690AD
    BYTE m_bCircleEndSelected; // +0x690AE
    // total size: 0x690B0 (430256)

    CCBCamControl(); // 0x005081D0
    ~CCBCamControl(); // 0x005081E0
    static int Reset(); // 0x00508220
    static int Create(); // 0x00508230
    static int Destroy(); // 0x00508270
    static int Init(); // 0x00508280
    static int Update(); // 0x005082C0
    static int StartList(); // 0x005082D0
    static int StopList(); // 0x00508320
    static int HandleInput(); // 0x00508360
    static int UpdateCircleSet(); // 0x00508370
    char * SetCircle(int a2); // 0x005083B0
    char IsPointerUnderMouse(); // 0x005084C0
    _DWORD * LoadPointer(); // 0x00508660
    char DoList(); // 0x00508680
    int ResetListFlag(); // 0x00508690
    int KeepCurCam(int a2); // 0x00508880
    int DoLineMove(unsigned int a2); // 0x005088D0
};
