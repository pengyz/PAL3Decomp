#ifndef PAL3A_EFFSHOCK_H
#define PAL3A_EFFSHOCK_H

#include "pal3a_types.h"

class CEffShock {
public:
    char _data[4272];

    char * GetEditorTaskDescription(int nIndex);
    void CreateTask(tagEffTaskParam * p);
    void Destroy();
    ~CEffShock();
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    unsigned long ProcCommonTask(ulong dwParam);
    void Render();
    CEffShock();
    void UpdateShock();
    void LoadTexture(char * pFileName);
    void Update(float fCurTime);
    void Attach();
    void StartShock(int nRequireLoops);
    void InitDefaultUVSet(int nFramePerRow, int nFramePerCol);
    bool Create(tagEffObjType * pType);
    unsigned long ProcInitTask(ulong dwParam);
    void CreateGeom();
    char * GetEditorObjDescription(int nIndex);
};

#endif // PAL3A_EFFSHOCK_H
