#ifndef PAL3A_EFFECTSYSTEM_H
#define PAL3A_EFFECTSYSTEM_H

#include "pal3a_types.h"

class CEffect {
public:
    char _data[245800];

    void Destroy();
    void Reset();
    ~CEffect();
    void Update(double gbTime);
    void DestroyAllPartical();
    void HandleViewMove(float x, float y);
    bool SetOnePartical(int n, tagPartical * pPartical);
    bool Init();
    void LoadTexture(char * pFileName);
    void ToNextFrame(int nParticalIndex);
    void DestroyOnePartical(int n);
    CEffect(CEffectSystem * pES);
    void DestroyTexture();
    void FillQuadByPartical(int nParticalIndex);
    void Render();
    bool CreateOnePartical(tagPartical * pPartical);
};

class CEffectBubble {
public:
    char _data[245800];

    bool CreateGroup(float fX, float fY, float fZ, float fSize, float fFramePerSec, int nNum);
    CEffectBubble(CEffectSystem * pES);
};

class CEffectSimple {
public:
    char _data[245800];

    CEffectSimple(CEffectSystem * pES);
    bool CreateOne(float fX, float fY, float fZ, float fSize, float fFramePerSec);
};

class CEffectSystem {
public:
    char _data[344];

    bool Init();
    void Render();
    void DestroyEffect(int nIndex);
    void DestroyEffect(EEffect effect);
    void FillDefaultUVSet();
    CEffect * CreateEffect(EEffect effect);
    ~CEffectSystem();
    CEffect * GetEffect(int nIndex);
    void Set256UV(tagUVSet * pUVSet, int nIndex, int nSizePerPic);
    void Destroy();
    int GetEffectIndex(CEffect * pEffect);
    int GetEffectIndex(EEffect effect);
    void SetVisible(EEffect effect, uchar bVisible);
    void DestroyAllEffect();
    void HandleViewMove(float x, float y);
    bool IsVisible(EEffect effect);
    void Reset();
    void Update(double gbTime);
    CEffectSystem(gbGfxManager * pDisplay);
    bool IsValid(EEffect effect);
};

#endif // PAL3A_EFFECTSYSTEM_H
