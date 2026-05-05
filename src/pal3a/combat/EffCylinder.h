#ifndef PAL3A_EFFCYLINDER_H
#define PAL3A_EFFCYLINDER_H

#include "pal3a_types.h"

class CEffCylinder {
public:
    char _data[4292];

    char * GetEditorTaskDescription(int nIndex);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    void InitDefaultUVSet(int nFramePerRow, int nFramePerCol);
    void LoadTexture(char * pFileName);
    void Render();
    char * GetEditorObjDescription(int nIndex);
    unsigned long ProcCommonTask(ulong dwParam);
    void CreateTask(tagEffTaskParam * p);
    bool Create(tagEffObjType * pType);
    void Update(float fCurTime);
    void CreateGeom();
    ~CEffCylinder();
    unsigned long ProcInitTask(ulong dwParam);
    void Destroy();
    CEffCylinder();
    void Attach();
};

#endif // PAL3A_EFFCYLINDER_H
