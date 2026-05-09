#pragma once
// Auto-generated from IDA decomp - CScreenMode
// 17 methods

class CScreenMode {
public:
    char InitCPK(int a2, int a3);  // 0x0053C340
    int CreateDevice(int a, int b, int c, int d);  // 0x0053C440
    int PlayVideo(int a2);  // 0x0053C5A0
    int SetViewport(int x, int y);  // 0x0053C6F0
    int GetWidth();  // 0x0053C710
    int GetHeight();  // 0x0053C720
    int SetState(int state);  // 0x0053CDD0
    void SetAudioParam();  // 0x0053D1E0
    char IsAudioReady();  // 0x0053D2D0
    void SetMode(int mode);  // 0x0053DD70
    void Restore();  // 0x0053DEF0
    static char *() GetInstance();  // 0x0053DF70
    void AudioSetPosition(void *pPos, int a3);  // 0x0053E2E0
    void AudioUpdate();  // 0x0053E490
    int GetAudioManager();  // 0x0053E500
    void AudioStopAll();  // 0x0053E950
    void AudioFadeOut();  // 0x0053EA60
};
