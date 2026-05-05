#ifndef PAL3A_ROLECTRL_H
#define PAL3A_ROLECTRL_H

#include "pal3a_types.h"

class RoleCtrl {
public:
    char _data[1];

    int GetClickPoint(tagPOINT * cursorpt, int onlayer, gbVec3D * clickpt);
    int GetClickPoint(tagPOINT * cursorpt, gbVec3D * clickpt, int * clicklayer);
    bool IfJumpAllowed();
    ~RoleCtrl();
    int GetClickPointWithObj(tagPOINT * cursorpt, gbVec3D * clickpt, int * clicklayer, int * bResult);
    void UpdateSnd();
    void StopSnd();
    void SetRole(Role * prole);
    void Enable(int bEnable);
    void Update(float deltatime);
    void Init();
    void ResetEnable();
    RoleCtrl();
};

int Floor2SndIndex(FLOOR_KIND f);

#endif // PAL3A_ROLECTRL_H
