#pragma once

class CCBStage;

class CCBSystem {
public:
    ~CCBSystem();
    void ProcFling(void);
    unsigned long ProcUseItem(unsigned long hwnd);

    char _pad[0x1C];
    CCBStage *m_pStage;  // offset 0x1C
};
