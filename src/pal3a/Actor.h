#ifndef PAL3A_ACTOR_H
#define PAL3A_ACTOR_H

#include "pal3a_types.h"

class Actor {
public:
    char _data[596];

    int CheckAction(char * pName);
    int IsAction(char * name);
    int GetLoopPast();
    int IsOver();
    void GotoAction(char * name, char * event1, char * event2);
    int GotoAction(ACTION_KIND act, int flags);
    int GotoAction(char * name, int flags);
    int IfMsg(char * str);
    ~Actor();
    void SetFPS(float fps);
    Actor();
    int Attach(gbRenderEffect * eft);
    void Reset2Msg(char * msgname);
    int IfHaveAction(ulong name, gbActor * pact);
    void Update();
    void CheckMatChange(ulong dwMsg);
    void Init(char * rolename, int type);
    void GetCollideOBB(gbOBBox * box);
    void EnableActionTransMtl(char * pName, uchar b);
    void Destroy();
    int LoadAction(char * pName);
    void SetTexture(char * filename);
};

#endif // PAL3A_ACTOR_H
