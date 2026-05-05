#ifndef PAL3A_PALSCRIPT_H
#define PAL3A_PALSCRIPT_H

#include "pal3a_types.h"

class PalScript {
public:
    char _data[40];

    int Update(float deltatime);
    void ClearAllCamObj();
    ~PalScript();
    void ClearAllWaitObj();
    void Destroy();
    void AddCamObj(PalScriptWaitObj * obj);
    void AddWaitObj(PalScriptWaitObj * obj);
    PalScript();
};

class PalScriptMgr {
public:
    char _data[1];

    PalScript * FindScript(scScriptInstance * pinst);
    void RunSceneScript(char * cityname, char * name);
    void _CON_CloseScript(char * agv);
    void ClearAllScript();
    unsigned long FindScriptByDesc(char * desc);
    void Destroy();
    ~PalScriptMgr();
    void OpenSCE(char * filename);
    void InitSys();
    void _CON_State(char * agv);
    bool IfAnyScriptRunning();
    void _CON_ReLoadScript(char * agv);
    bool IfHaveScript(ulong id);
    void Update(float deltatime);
    PalScriptMgr();
    PalScript * RunScript(ulong id, uchar bBigMap);
    int IsScriptRuning(PalScript * pal);
};

#endif // PAL3A_PALSCRIPT_H
