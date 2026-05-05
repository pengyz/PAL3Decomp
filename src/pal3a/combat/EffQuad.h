#ifndef PAL3A_EFFQUAD_H
#define PAL3A_EFFQUAD_H

#include "pal3a_types.h"

class CEffQuad {
public:
    char _data[4272];

    void Destroy();
    void Attach();
    void Padds(float * fDest, float fSrc);
    void Padds(uchar * byDest, float fSrc);
    void ToNextFrame(int nQuad);
    unsigned long ProcInitTask(ulong dwParam);
    void CreateTask(tagEffTaskParam * p);
    bool Create(tagEffObjType * pType);
    void Update(float fCurTime);
    bool SetQuad(int n, tagQuad * pQuad);
    unsigned long ProcCommonTask(ulong dwParam);
    unsigned long ProcCreateQuad(ulong dwParam);
    void DestroyOneQuad(int n);
    ~CEffQuad();
    void FillGeomQuad(int nQuad);
    CEffQuad();
    void InitDefaultUVSet(int nFramePerRow, int nFramePerCol);
    void LoadTexture(char * pFileName);
    void Render();
    void DestroyAllQuad();
    char * GetEditorTaskDescription(int nIndex);
    bool CreateOneQuad(tagQuad * pQuad);
    void Init(tagEffObjType * pType, float fx, float fy, float fz);
};

#endif // PAL3A_EFFQUAD_H
