#ifndef PAL3A_SCENEMGR_H
#define PAL3A_SCENEMGR_H

#include "pal3a_types.h"

class SceneMgr {
public:
    char _data[1];

    bool SetGeomNote(char * cityname, char * name);
    void Destroy();
    void _CON_KillMonsters(char * agv);
    void SetCameraRefer();
    void DefaultCamera(SCENE_TYPE scenetype);
    bool IsScene(char * cityname, char * name);
    SceneMapPlayer * GetMap(int layer);
    Role * GetSelRole(gbRay * ray);
    void LoadSpecialVariable(_iobuf * fp);
    void Update(float deltatime);
    void SetEmissiveFactor();
    Role * GetSelRole_RoleCtrl();
    void LoadScene(char * cityname, char * name, uchar showloading, uchar savescn);
    ~SceneMgr();
    void SaveSpecialVariable(_iobuf * fp);
    int AttachLights();
    SceneMgr();
    void SFLB_OnSceneChange(uchar savescn);
    Scene * GetCurScene();
};

void SceneIndex(SCENE_TYPE type);

#endif // PAL3A_SCENEMGR_H
