#ifndef PAL3A_EFFEXPLOSIVE_H
#define PAL3A_EFFEXPLOSIVE_H

#include "pal3a_types.h"

class CEffExplosive {
public:
    char _data[4288];

    char * GetEditorTaskDescription(int nIndex);
    void CreateTask(tagEffTaskParam * p);
    void Destroy();
    ~CEffExplosive();
    unsigned long ProcCommonTask(ulong dwParam);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    void Render();
    void LoadTexture(char * pFileName);
    void Update(float fCurTime);
    void Attach();
    void StartExplosive();
    CEffExplosive();
    void InitDefaultUVSet(int nFramePerRow, int nFramePerCol);
    unsigned long ProcInitTask(ulong dwParam);
    void CreateGeom();
    bool Create(tagEffObjType * pType);
    void UpdateExplosive(float fDeltaTime, float fTime);
    char * GetEditorObjDescription(int nIndex);
};

#endif // PAL3A_EFFEXPLOSIVE_H
