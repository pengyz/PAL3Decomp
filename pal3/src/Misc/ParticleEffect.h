#include "sg_particle_scene.h"
#pragma once
// Auto-generated: ParticleEffect

#include "gbengine/gbTexture.h"

class ParticleEffect : public sg_particle_scene {
public:
    char _gap_000[362836]; // +0x0
    int active_parnum; // +0x58954
    gbTexture_D3D * m_pTexture[4]; // +0x58958
    char _gap_5895C[12]; // +0x5895C
    float deltatime; // +0x58968
    // total size: 0x5896C (362860)

    int LoadSceneFile(const char *pszName, const char *pszName2); // 0x004BA510
    ParticleEffect * Reset(); // 0x004BC760
    int SetDeltaTime(int nVal); // 0x004BC7E0
    int UpdateParticles(float fVal, int nVal, int nVal2, int nVal3); // 0x004BC7F0
    char LoadTextures(const char *pszName, const char *pszName2); // 0x004BD520
    int SetTimeParam(int nVal); // 0x004BD7C0
    bool LoadFromFile(char *filename); // 0x0053F960
};
