#pragma once
// Auto-generated: CCBStageCam

#include "RoleCamera.h"
#include "tagCam.h"
#include "tagCamTask.h"

class CCBStage;
class CUtil;

class CCBStageCam : public RoleCamera {
public:
    CCBStage * m_pStage; // +0x2B4
    CUtil * m_pUtil; // +0x2B8
    float m_fLastMouseX; // +0x2BC
    float m_fLastMouseY; // +0x2C0
    void * * m_fp; // +0x2C8
    int m_nTask; // +0x2D8
    int m_nCurTask; // +0x2DC
    tagCamTask m_Task[50]; // +0x2E0
    tagCam m_EditorCam[64]; // +0x1280
    // total size: 0x1880 (6272)

    char Reset(int a2, const void *a3); // 0x00505060
    char LoadEditorCam(int a2, int a3, const void *a4); // 0x005050D0
    char SaveEditorCam(int a2, int a3, int a4); // 0x00505180
    char AddCurCamToEditor(int a2, int a3); // 0x005051E0
    char DelEditorCam(int a2); // 0x00505250
    int IsEditorCamValid(int a2); // 0x00505290
    int IsCamValid(); // 0x005052C0
    _DWORD * SetCamPos(int **a2, int a3); // 0x005052E0
    int Create(); // 0x00505410
    char Destroy(); // 0x00505490
    char Init(); // 0x005054B0
    char Update(); // 0x005054E0
    void DoTask(); // 0x005054F0
    char ClearFinishedTask(int a2); // 0x00505770
    int AddTask(); // 0x00505800
    char ProcCamMove(); // 0x00505820
    int SwitchEditorCamPos(); // 0x005058E0
};
