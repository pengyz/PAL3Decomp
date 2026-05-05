#ifndef PAL3A_SWORDUI_H
#define PAL3A_SWORDUI_H

#include "pal3a_types.h"

class PurgeEffect {
public:
    char _data[428];

    ~PurgeEffect();
    bool LoadDstTexture(char * filename);
    bool LoadSrcTexture(char * filename);
    gbTexture * MergeSrcData(tagRECT srcRect, tagRECT dstRect, uchar bNone);
    gbTexture * UpdateMergeData(uchar * isvalid, int spd, uchar bImmediate);
    int ApproachValue(int srcV, int dstV, int param);
    PurgeEffect();
};

class SwordUI {
public:
    char _data[388952];

    int CalSwordPurgeInfo(int purge_wu, int purge_time);
    void DistributeListData(int Page);
    void CreateStpCtl();
    void ControlPage(int Page);
    void CreatePurge();
    int Update(float deltatime, int haveinput);
    void SetPurgeEffect();
    ~SwordUI();
    void CheckPurge();
    void InitPURGEINFO();
    void Purged();
    void FillListData(int Page);
    void ExitPurge();
    void SetSwordEffect();
    void PurgeWSkill();
    void MgrStpCtrl();
    void Create(UIWnd * pWnd);
    void SortStuffList(int by);
    int OnMessage(uint msg, ulong wparam, ulong lparam);
    void SetBtnParEffect(int flag);
    bool CheckRoleItem(PlayerItem * item, int Page);
    void UpdateKeyCtrl();
    void SwitchPurge(uchar is);
    void ResetData();
    void UnDistributeListData(int SelNum);
    void Render();
    SwordUI();
    void CheckWSkill();
};

#endif // PAL3A_SWORDUI_H
