#ifndef PAL3A_CBCONTROL_H
#define PAL3A_CBCONTROL_H

#include "pal3a_types.h"

class CCBControl {
public:
    char _data[1392];

    void ShowItemListBox(uchar bVisi);
    bool Create();
    void ForceRelease();
    unsigned long ProcMagicList(ulong __formal);
    unsigned long ProcItemList(ulong __formal);
    bool Control(int nRoleIndex);
    unsigned long TranslateOldRangeToNew(ulong dwOldRange);
    void Update();
    int GetController();
    bool Release(int nRoleIndex);
    void Reset();
    bool CanChangeLineup();
    unsigned long ProcLineupList(ulong __formal);
    void UIMsgNotify(ulong dwID, ulong dwP1, ulong dwP2);
    unsigned long ProcForceRelease(ulong __formal);
    unsigned long ProcSelectRole(ulong __formal);
    void ShowRightPanel(uchar bVisi);
    unsigned long ProcAIList(ulong __formal);
    ~CCBControl();
    void DoThread();
    bool Destroy();
    unsigned long ProcProtect(ulong __formal);
    unsigned long ProcMainPanel(ulong __formal);
    bool DelThread(int nIndex);
    int AddThread(void * fp, void * fpCaller, ulong dwCmdKind, ulong dwCmdID);
    bool Init();
    CCBControl(CCBSystem * pCBSystem);
    void ShowLeftPanel(uchar bVisi);
    bool GetInputData(ulong * dwKey, ulong * dwParam1, ulong * dwParam2);
    unsigned long ProcParabolaList(ulong __formal);
    unsigned long ProcSkillList(ulong __formal);
};

#endif // PAL3A_CBCONTROL_H
