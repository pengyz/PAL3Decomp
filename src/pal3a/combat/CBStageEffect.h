#ifndef PAL3A_CBSTAGEEFFECT_H
#define PAL3A_CBSTAGEEFFECT_H

#include "pal3a_types.h"

class CCBStageEffect {
public:
    char _data[25488];

    bool SaveLinker();
    bool Destroy();
    bool Init();
    void PreLoadEffGroup(int nLinker);
    unsigned long RunEffGroup(int nLinker, int nOneOrTwo, tagCmdData * pCmd, uchar opp);
    bool Create();
    int GetLinkerIndex(ulong dwTrickID);
    void Reset();
    bool LoadLinker();
    ~CCBStageEffect();
    CCBStageEffect(CCBStage * pStage);
};

#endif // PAL3A_CBSTAGEEFFECT_H
