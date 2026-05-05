#ifndef PAL3A_CG_ENTRY_H
#define PAL3A_CG_ENTRY_H

#include "pal3a_types.h"

class CG_Entry {
public:
    char _data[204];

    bool InitUI();
    void Render(gbMatrixStack * pView);
    void Restart(int nLevel);
    ~CG_Entry();
    bool Init();
    void Update(float deltatime);
    void ExitGame();
    void DestroyUI();
    void Destroy();
    CG_Entry();
};

#endif // PAL3A_CG_ENTRY_H
