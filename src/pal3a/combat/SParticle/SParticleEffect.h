#ifndef PAL3A_SPARTICLEEFFECT_H
#define PAL3A_SPARTICLEEFFECT_H

#include "pal3a_types.h"

class CEmitter {
public:
    char _data[228];

    void UpdateTrackPos(float fElapsedTime);
    void Emit(void* pUnit);
    CEmitter();
};

class CParticleEffect {
public:
    char _data[56];

    ~CParticleEffect();
    void Update();
    void Setup(gbGfxManager * pGfxMgr);
    float GetTime();
    void SetTimeScale(float fTimeScale);
    unsigned long GetNumOfParticles();
    void Start();
    void Display(int bVisible);
    int IsPlay();
    CParticleSystem * GetParticleSystem(ulong dwParticleIndex);
    CParticleSystem * GetParticleSystem(char * strParticleName);
    unsigned long GetNumOfParticleSystem();
    int Render();
    void SetTransform(gbMatrix4 * matTransform, float fWidthScale, float fHeightScale);
    void Stop();
    CParticleEffect();
    int Load(char * strFileName);
};

class CParticleSystem {
public:
    char _data[220];

    CEmitter * GetEmitter();
    unsigned long GetId();
    void Setup(gbGfxManager * pGfxMgr);
    void Update(float fElapsedTime);
    ~CParticleSystem();
    void Start();
    int GetNumOfParticles();
    void UpdateOneParticle(void* pUnit, float fElapsedTime);
    void SetMode(int bManual);
    void* CreateOneParticle();
    int LoadTexture(char * strTexFile);
    void UpdateAllUnits(float fElapsedTime);
    int GetMode();
    void UpdateFrameData(float fElapsedTime);
    void Stop();
    char const * GetName();
    void SetTransform(gbMatrix4 * matTransform, float fWidthScale, float fHeightScale);
    gbVec3D const & GetEmitterPos();
    void UpdateEmitter(float fElapsedTime);
    unsigned long GetNumOfUnitFrames();
    int Emit(int nNumOfUnits);
    void SetEmitterPos(gbVec3D * vPos);
    void Display(int bVisible);
    void EmitUnits(float fElapsedTime);
    int Render();
    CParticleSystem(char * strParticleName, int nMaxNum, int nChunk);
};

class KeyFrame {
public:
    char _data[264];

    ~KeyFrame();
    KeyFrame();
};

#endif // PAL3A_SPARTICLEEFFECT_H
