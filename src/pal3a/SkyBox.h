#ifndef PAL3A_SKYBOX_H
#define PAL3A_SKYBOX_H

#include "pal3a_types.h"

class SkyBox {
public:
    char _data[56];

    void ActiveSkyBox(uchar bActive);
    void Destroy();
    SkyBox * Inst();
    void Create(int id, gbVec3D size);
    ~SkyBox();
    SkyBox();
    void Render(gbRenderInfoObj * pobj);
};

class SkyboxEff {
public:
    char _data[144];

    void GetRandomRenderArea(float xOffset, float yOffset);
    void RenderEffect();
    ~SkyboxEff();
    void GetEnumPos(float fSize, eSkyEffPos ePos, uchar bAreaRand, float * fx, float * fy, float * fz);
    void DestroyEffect();
    void CreateEffect(float fSkysize, char * name, EffModeParam effMode, float xOffset, float yOffset, float scale, float fps, float fValidtime, float fWaitTime);
    void UpdateEffect(float deltatime);
    SkyboxEff();
};

class SkyboxEffMgr {
public:
    char _data[7780];

    void DestroyAllEff();
    void StopEffect(char * effName);
    ~SkyboxEffMgr();
    void PreLoadEffect(char * name);
    void PreLoadEffect();
    void Update(float deltatime);
    void RunEffect(char * effName, int nSide, float xOffset, float yOffset, float scale, float fps, float fValidTime, float fWaitTime);
    void DestroyEffectThorough();
    void Render();
    SkyboxEffMgr();
    void UnPreLoadEffect(char * name);
};

#endif // PAL3A_SKYBOX_H
