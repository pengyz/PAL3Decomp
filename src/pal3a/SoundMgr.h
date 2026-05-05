#ifndef PAL3A_SOUNDMGR_H
#define PAL3A_SOUNDMGR_H

#include "pal3a_types.h"

class SoundMgr {
public:
    char _data[918796];

    SoundMgr * Inst();
    gbAudioManager * GetAudioMgr();
    void PlayCombatMusicNotFromTable(char * name);
    void PlayCombatMusic(char * name);
    void ResumeAll2D();
    void PlayStream(int i, char * filename, int nLoop);
    void ReStartScriptMusic();
    SoundItem * LoadSnd(char * pName);
    ~SoundMgr();
    void Update();
    void AutoDetectSceneMusic();
    void Create();
    void PlaySceneMusic();
    void PlaySceneMusic(char * cityname, char * name, int initpause);
    void ClearSndBuf();
    gbSound2DNode * PlaySndA(char * name);
    void StopSnd(char * name);
    void PlaySnd(char * name, int loop);
    void PauseAll2D();
    void Script_PlaySnd(char * name, int loop);
    void StopAll2D();
    bool IsPlaying(char * name);
    void ReInit();
    void PlayStoryMusic(char * musicname, int nLoop);
    void Destroy();
    SoundMgr();
    void ForceStopSnd(char * name, uchar bAll);
};

#endif // PAL3A_SOUNDMGR_H
