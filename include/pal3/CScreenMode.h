#pragma once

class gbAudioManager;

class CScreenMode {
public:
    static CScreenMode *GetInstance(void);
    void SetState(int state);
    gbAudioManager *GetAudioManager(void);
    void Restore(void);

    char _pad[0x1300];
};
