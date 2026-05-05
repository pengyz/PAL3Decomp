#ifndef PAL3A_DEALDATA_H
#define PAL3A_DEALDATA_H

#include "pal3a_types.h"

class DealData {
public:
    char _data[833340];

    char * LeachStr(char * srcStr, char * tok, char * outfront);
    bool GetLang(char * FileName);
    ~DealData();
    int GetKeyVal(char** srcKey, char * cmpKey);
    void GetManagerData(char * FileName);
    char * GetAtkRange(FightSkill * skill);
    char * GetItemInfo(FightItem * item);
    void TransData();
    void Destroy();
    DealData();
    char * GetSkillInfo(FightSkill * skill);
    char * GetItemRange(FightItem * pFI);
};

#endif // PAL3A_DEALDATA_H
