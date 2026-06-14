#pragma once
// Auto-generated: CCBCamControl

#include "gbengine/gbGeomNode.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_internal.h"
#include "tagCam.h"

class CCBStage;
class CCBStageCam;
class CCCTData;
class CUtil;

class CCBCamControl {
public:
    CCCTData * m_CCT; // +0x0
    char _gap_004[4]; // +0x4
    gbVec3D * m_pvecCenter; // +0x8
    float _todo_C; // +0xC
    gbVolModNode * _todo_010; // +0x10
    char _gap_014[32]; // +0x14
    float m_fCamBlendA; // +0x34
    float m_fCamBlendB; // +0x38
    int m_CamCtrlData; // +0x3C
    char _gap_040[172]; // +0x40
    gbVolModNode _embed_gbVolModNode_EC; // +0xEC
    char _gap_0F0[2196]; // +0xF0
    gbRefObject * m_nList; // +0x984
    int m_nPointerUnderMouse; // +0x988
    int m_CamEntries[1794]; // +0x98C
    int m_nCurCamIdx; // +0x2594
    char _gap_2598[420376]; // +0x2598
    CCBStage * m_pStage; // +0x68FB0
    CCBStageCam * m_pCam; // +0x68FB4
    CUtil * m_pUtil; // +0x68FB8
    BYTE m_bRunning; // +0x68FBC
    char _gap_68FBD[3]; // +0x68FBD
    char * m_fp; // +0x68FC0
    char _gap_68FC4[12]; // +0x68FC4
    int m_nCurList; // +0x68FD0
    int m_nCurTask; // +0x68FD4
    float m_fStartSpeed; // +0x68FD8
    float m_fNextSpeed; // +0x68FDC
    gbVec3D m_vecSpeed; // +0x68FE0
    char _gap_68FE4[8]; // +0x68FE4
    gbVec3D m_vecNextSpeed; // +0x68FEC
    char _gap_68FF0[8]; // +0x68FF0
    float m_fDistance; // +0x68FF8
    float m_fQuake; // +0x68FFC
    float m_fQuakeDec; // +0x69000
    float m_fQuakeFre; // +0x69004
    tagCam m_StartPos; // +0x69008
    char _gap_6900C[20]; // +0x6900C
    tagCam m_CurPos; // +0x69020
    char _gap_69024[20]; // +0x69024
    gbVec3D m_vecCurPos; // +0x69038
    char _gap_6903C[8]; // +0x6903C
    gbOBBox m_OBBox; // +0x69044
    char _gap_69048[72]; // +0x69048
    gbGeomNode * m_pPointer; // +0x69090
    gbVec3D m_vecCircleCenter; // +0x69094
    char _gap_69098[8]; // +0x69098
    gbVec3D m_vecCircleEnd; // +0x690A0
    char _gap_690A4[8]; // +0x690A4
    BYTE m_bShowCircleSet; // +0x690AC
    BYTE m_bCircleCenterSelected; // +0x690AD
    BYTE m_bCircleEndSelected; // +0x690AE
    char _tail_690AF[1]; // +0x690AF
    // total size: 0x690B0 (430256)

    virtual void Render(); // 0x00449C20
    int ProcessRenderQueue(); // 0x0048E600
    int ShowAllSlots(int nVal); // 0x004A9ED0
    int sub_4E9750(HWND hDlg); // 0x004E9750
    void sub_4EB6F0(HWND hDlg); // 0x004EB6F0
    LRESULT sub_4EB720(HWND hDlg); // 0x004EB720
    LRESULT sub_4EB8D0(HWND hDlg); // 0x004EB8D0
    void ShowCameraDialog(HWND hDlg); // 0x004EBD30
    void ReadCameraDialog(HWND hDlg); // 0x004EBF90
    int ProcessCamMove(int nVal); // 0x004FF360
    CCBStageCam * SetCamPos(int **pCamParam, int nVal); // 0x005052E0
    bool Init(); // 0x005054B0
    void DoTask(); // 0x005054F0
    char ClearFinishedTask(int nVal); // 0x00505770
    int AddTask(); // 0x00505800
    char ProcCamMove(); // 0x00505820
    bool SwitchEditorCamPos(); // 0x005058E0
    CCBCamControl(); // 0x005081D0
    void _CCBCamControl(); // 0x005081E0
    void Reset(); // 0x00508220
    bool Create(); // 0x00508230
    bool Destroy(); // 0x00508270
    void Update(); // 0x005082C0
    bool StartList(); // 0x005082D0
    void StopList(); // 0x00508320
    void HandleInput(); // 0x00508360
    void UpdateCircleSet(); // 0x00508370
    CCBCamControl * SetCircle(int pvecCenter); // 0x005083B0
    bool IsPointerUnderMouse(); // 0x005084C0
    int * LoadPointer(); // 0x00508660
    void DoList(); // 0x00508680
    void ResetListFlag(); // 0x00508690
    void KeepCurCam(int pCam); // 0x00508880
    void DoLineMove(unsigned int dwVal); // 0x005088D0
};
