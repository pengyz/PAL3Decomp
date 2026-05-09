#pragma once
// Auto-generated from IDA decomp - CCBStageCam
// 19 methods

class CCBStageCam {
public:
    char CCBStageCam(char *Buffer);  // 0x00504E70
    char ~CCBStageCam();  // 0x00504F40
    char Reset(int a2, const void *a3);  // 0x00505060
    char LoadEditorCam(int a2, int a3, const void *a4);  // 0x005050D0
    char SaveEditorCam(int a2, int a3, int a4);  // 0x00505180
    char AddCurCamToEditor(int a2, int a3);  // 0x005051E0
    char DelEditorCam(int a2);  // 0x00505250
    int IsEditorCamValid(int a2);  // 0x00505290
    int IsCamValid();  // 0x005052C0
    static _DWORD *__thiscall(_DWORD *this, int **a2, int a3) SetCamPos();  // 0x005052E0
    int Create();  // 0x00505410
    char Destroy();  // 0x00505490
    char Init();  // 0x005054B0
    char Update();  // 0x005054E0
    void DoTask();  // 0x005054F0
    char ClearFinishedTask(int a2);  // 0x00505770
    int AddTask();  // 0x00505800
    int ProcCamMove();  // 0x00505820
    int SwitchEditorCamPos();  // 0x005058E0
};
