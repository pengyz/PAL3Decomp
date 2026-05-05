#ifndef PAL3A_EFFGRID_H
#define PAL3A_EFFGRID_H

#include "pal3a_types.h"

class CEffGrid {
public:
    char _data[4280];

    void DoTear(float fStartTime);
    unsigned long ProcInitTask(ulong dwParam);
    ~CEffGrid();
    void DoWave();
    void Destroy();
    void Attach();
    char * GetEditorTaskDescription(int nIndex);
    void DoFlap();
    void FillQuadViaMesh();
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    void InitDefaultUVSet(int nFramePerRow, int nFramePerCol);
    void Render();
    void LoadTexture(char * pFileName);
    char * GetEditorObjDescription(int nIndex);
    unsigned long ProcCommonTask(ulong dwParam);
    void CreateTask(tagEffTaskParam * p);
    bool Create(tagEffObjType * pType);
    void Update(float fCurTime);
    CEffGrid();
    void CreateGeom();
};

#endif // PAL3A_EFFGRID_H
