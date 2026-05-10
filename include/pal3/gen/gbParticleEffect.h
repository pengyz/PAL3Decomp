#pragma once
// Auto-generated: gbParticleEffect

#include "gbVisNode.h"

class gbPartEmitter;
class gbPartGroupParam;
class gbParticleGroup;
class gbParticleUnit;

class gbParticleEffect : public gbVisNode {
public:
    char Name[64]; // +0x58
    int nPartGroup; // +0x98
    int nGroupParam; // +0x9C
    int nEmitter; // +0xA0
    gbParticleGroup * pPartGroups; // +0xA4
    gbPartGroupParam * pGroupParams; // +0xA8
    gbPartEmitter * pEmitters; // +0xAC
    int maxparticle; // +0xB0
    int emittedto; // +0xB4
    int npwmr; // +0xB8
    gbParticleUnit * pParticles; // +0xBC
    float gravity; // +0xC0
    float timescale; // +0xC4
    int maxfps; // +0xC8
    int camerafollow; // +0xCC
    float camerafollowdis; // +0xD0
    int gravityeffect; // +0xD4
    float frontplane; // +0xD8
    float backplane; // +0xDC
    gbVec3D objectoffset; // +0xE0
    gbVec3D systemoffset; // +0xEC
    gbVec3D systemvelocity; // +0xF8
    double CurTime; // +0x108
    double ElapseTime; // +0x110
    float SpaceScale; // +0x118
    gbMatrix4 m_ToWorld; // +0x11C
    // total size: 0x160 (352)

    void GetBoundSphere(struct gbSphere *a2); // 0x005420E4
    void Reset(float a2); // 0x005420EA
    void Update(); // 0x005420F0
    int Attach(struct gbRenderEffect *a2); // 0x005420F6
    void Render(struct gbRenderInfoObj *a2); // 0x00542108
};
