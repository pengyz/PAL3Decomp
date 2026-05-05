#ifndef PAL3A_EFFAUDIO_H
#define PAL3A_EFFAUDIO_H

#include "pal3a_types.h"

class CEffAudio {
public:
    char _data[688];

    void Init(tagEffObjType * pType, float fx, float fy, float fz);
    unsigned long ProcCommonTask(ulong dwParam);
    ~CEffAudio();
    void Render();
    void Destroy();
    char * GetEditorTaskDescription(int nIndex);
    void CreateTask(tagEffTaskParam * p);
    bool Create(tagEffObjType * pType);
    unsigned long ProcInitTask(ulong dwParam);
    void PreLoadObjInTask(tagEffTaskParam * p);
    void Attach();
    CEffAudio();
    void Update(float fCurTime);
};

#endif // PAL3A_EFFAUDIO_H
