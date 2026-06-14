#include "RoleCamera.h"
#pragma once
// Auto-generated: CCBStageCam

#include "tagCam.h"
#include "tagCamTask.h"

class CCBStage;
class CUtil;

class CCBStageCam : public RoleCamera {
public:
    char _gap_000[692]; // +0x0
    CCBStage * m_pStage; // +0x2B4
    CUtil * m_pUtil; // +0x2B8
    float m_fLastMouseX; // +0x2BC
    float m_fLastMouseY; // +0x2C0
    char _gap_2C4[4]; // +0x2C4
    char * m_fp; // +0x2C8
    char _gap_2CC[12]; // +0x2CC
    int m_nTask; // +0x2D8
    int m_nCurTask; // +0x2DC
    tagCamTask m_Task[50]; // +0x2E0
    char _gap_3A8[3800]; // +0x3A8
    tagCam m_EditorCam[64]; // +0x1280
    char _tail_1380[1280]; // +0x1380
    // total size: 0x1880 (6272)

    virtual ~CCBStageCam() {}

    int UpdateEditorState(); // 0x004E6020
    LRESULT ApplyShake(HWND hDlg); // 0x004E7060
    LRESULT UpdateSmooth(); // 0x004E7280
    int PopulateCameraListView(); // 0x004E7350
    void UpdateOrbit(); // 0x004E74E0
    char ClampViewAngle(); // 0x004E75E0
    char LerpToTarget(); // 0x004E7B50
    int StoreCurrentView(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam); // 0x004E8450
    int UpdateStageCamera(float *pfVal, HWND hDlg, int nVal, int nVal2, int nVal3); // 0x004E8480
    int sub_4E95A0(HWND hDlg); // 0x004E95A0
    LRESULT SetBlendWeight(HWND hDlg); // 0x004E9890
    LRESULT InterpolateAngle(HWND hDlg); // 0x004E9950
    LRESULT UpdateFollowTarget(HWND hDlg); // 0x004E9A70
    char SetViewDistance(HWND hDlg); // 0x004E9C50
    void CalculateFOV(HWND hDlg); // 0x004E9F70
    LRESULT UpdateTransition(HWND hDlg); // 0x004EA2E0
    CCBStage * ResetViewport(); // 0x00504DD0
    char _CCBStageCam(); // 0x00504E60
    CCBStageCam(CCBStageCam *Buffer); // 0x00504E70
    void Reset(int nVal, const void *pData); // 0x00505060
    void LoadEditorCam(int nVal, int nVal2, const void *pData); // 0x005050D0
    void SaveEditorCam(int nVal, int nVal2, int nVal3); // 0x00505180
    char AddCurCamToEditor(int nVal, int nVal2); // 0x005051E0
    void DelEditorCam(int nCamIndex); // 0x00505250
    bool IsEditorCamValid(int nCamIndex); // 0x00505290
    bool IsCamValid(); // 0x005052C0
    bool Create(); // 0x00505410
    bool Destroy(); // 0x00505490
    void Update(); // 0x005054E0
};
