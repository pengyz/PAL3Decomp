/**
 * gbengine.dll - gbParticle
 * Particle system implementation
 * Functions: 38
 */

#include "gbengine/gbParticle.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Forward declarations
class gbVFile1;
class gbVFileSystem;
class gbEffectMgr;
class gbResManager;

// External globals
extern gbVFileSystem* g_pVFileSys;
extern gbResManager* g_pResMgr;
extern gbEffectMgr* g_pEffectMgr;

// Constants
static const float HALF_FACTOR = 0.5f;
static const float DEG2RAD = 0.017453292f;

static float RandomFloat(float fmin, float fmax) {
    float t = (float)rand() / (float)RAND_MAX;
    return fmin + t * (fmax - fmin);
}

static int RandomInt(int imin, int imax) {
    if (imax <= imin) return imin;
    return imin + (rand() % (imax - imin + 1));
}

/* ======== gbPartParamControl ======== */

gbPartParamControl::gbPartParamControl(void) {
    controlType = 0;
    numKeys = 0;
    memset(keys, 0, sizeof(keys));
    memset(values, 0, sizeof(values));
}

gbPartParamControl& gbPartParamControl::operator=(const gbPartParamControl& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbPartParamControl));
    }
    return *this;
}

void gbPartParamControl::LoadFromFile(gbVFile* vfile) {
    if (!vfile) return;
    controlType = 0;
    numKeys = 0;
}

void gbPartParamControl::GetValue(float* result, float t) {
    if (numKeys == 0) {
        result[0] = 0.0f;
        return;
    }

    if (t <= keys[0]) {
        result[0] = values[0][0];
        return;
    }

    if (t >= keys[numKeys - 1]) {
        result[0] = values[numKeys - 1][0];
        return;
    }

    for (int i = 0; i < numKeys - 1; i++) {
        if (t >= keys[i] && t <= keys[i + 1]) {
            float factor = (t - keys[i]) / (keys[i + 1] - keys[i]);
            result[0] = values[i][0] + (values[i + 1][0] - values[i][0]) * factor;
            return;
        }
    }
}

/* ======== gbPartGroupParam ======== */

gbPartGroupParam::gbPartGroupParam(void) {
    memset(this, 0, sizeof(gbPartGroupParam));
}

gbPartGroupParam::~gbPartGroupParam(void) {
}

gbPartGroupParam& gbPartGroupParam::operator=(const gbPartGroupParam& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbPartGroupParam));
    }
    return *this;
}

void gbPartGroupParam::LoadFromFile(gbVFile* vfile) {
    if (!vfile) return;
    gravity = 0.0f;
    numFrames = 1;
}

void gbPartGroupParam::ComputeAirResist(gbParticleUnit* particle, float deltaTime) {
    float* vel = &particle->velocity.x;
    float speed = sqrtf(vel[0] * vel[0] + vel[1] * vel[1] + vel[2] * vel[2]);
    float invSpeed = 1.0f / speed;

    if (speed <= airResistance) return;

    int turbFlag = *(int*)((char*)this + 0x30);
    float dragCoeff = *(float*)((char*)this + 0x34);
    float turbX = 0.0f, turbY = 0.0f, turbZ = 0.0f;

    if (turbFlag == 0) {
        turbX = turbY = turbZ = 0.0f;
    } else {
        float turbForce = particle->size * dragCoeff;
        turbX = invSpeed * vel[0] * turbForce;
        turbY = invSpeed * vel[1] * turbForce;
        turbZ = invSpeed * vel[2] * turbForce;
    }

    vel[0] -= (dragCoeff * vel[0] * deltaTime + turbX * deltaTime);
    vel[1] -= (turbY * deltaTime + dragCoeff * vel[1] * deltaTime);
    vel[2] -= (turbZ * deltaTime + dragCoeff * vel[2] * deltaTime);
}

void gbPartGroupParam::ComputeParticleParam(gbParticleUnit* particle, float lifeFactor, float deltaTime) {
    int frameIdx = (int)((float)numFrames * lifeFactor);
    particle->frame = frameIdx;
    if (particle->frame >= numFrames) {
        particle->frame = numFrames - 1;
    }

    float val[3];
    sizeControl.GetValue(val, lifeFactor);
    particle->size = val[0];

    gbPartParamControl* rotCtrl = (gbPartParamControl*)((char*)this + 0x134C);
    rotCtrl->GetValue(val, lifeFactor);
    int rotRandMin = *(int*)((char*)this + 0x148);
    int rotRandMax = *(int*)((char*)this + 0x14C);
    int randDev = RandomInt(rotRandMin, rotRandMax);
    particle->rotation = ((float)randDev + val[0]) * deltaTime + particle->rotation;
    particle->rotation *= particle->rotationDir;

    gbPartParamControl* alphaCtrl = (gbPartParamControl*)((char*)this + 0x2530);
    alphaCtrl->GetValue(val, lifeFactor);
    float alphaVal = val[0];

    gbPartParamControl* colorCtrl = (gbPartParamControl*)((char*)this + 0x3714);
    colorCtrl->GetValue(val, lifeFactor);
    particle->colorR = (unsigned char)(int)val[0];
    particle->colorG = (unsigned char)(int)val[1];
    particle->colorB = (unsigned char)(int)val[2];
    particle->colorA = (unsigned char)(int)(alphaVal * 255.0f);
}

void gbPartGroupParam::InitParticleParam(gbParticleUnit* particle) {
    particle->frame = 0;

    float val[3];
    sizeControl.GetValue(val, 0.0f);
    particle->size = val[0];

    gbPartParamControl* rotCtrl = (gbPartParamControl*)((char*)this + 0x134C);
    rotCtrl->GetValue(val, 0.0f);
    particle->rotation = 0.0f;

    gbPartParamControl* alphaCtrl = (gbPartParamControl*)((char*)this + 0x2530);
    alphaCtrl->GetValue(val, 0.0f);
    float alphaInit = val[0];

    gbPartParamControl* colorCtrl = (gbPartParamControl*)((char*)this + 0x3714);
    colorCtrl->GetValue(val, 0.0f);
    particle->colorR = (unsigned char)(int)val[0];
    particle->colorG = (unsigned char)(int)val[1];
    particle->colorB = (unsigned char)(int)val[2];
    particle->colorA = (unsigned char)(int)(alphaInit * 255.0f);
}

gbTexture* gbPartGroupParam::GetTexture(void) {
    return pTexture;
}

gbRenderEffect* gbPartGroupParam::GetRenderEffect(void) {
    return pRenderEffect;
}

/* ======== gbPartEmitter ======== */

gbPartEmitter::gbPartEmitter(void) {
    memset(data, 0, sizeof(data));
}

gbPartEmitter::~gbPartEmitter(void) {
}

gbPartEmitter& gbPartEmitter::operator=(const gbPartEmitter& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbPartEmitter));
    }
    return *this;
}

void gbPartEmitter::LoadFromFile(gbVFile* vfile) {
    if (!vfile) return;
    memset(data, 0, sizeof(data));
}

int gbPartEmitter::ComputeEmitterData(gbEmitterData* emitData, double time, double deltaTime) {
    if (!emitData) return 0;
    return 1;
}

void gbPartEmitter::ComputeParticleInitPos(gbParticleUnit* particle) {
    int emitType = *(int*)((char*)data + 0x98);
    float* basePos = (float*)((char*)data + 0x40);

    if (emitType == 0) {
        float* rangeMin = (float*)((char*)data + 0xAC);
        float* rangeMax = (float*)((char*)data + 0xB8);
        particle->position.x = RandomFloat(rangeMin[0], rangeMax[0]) + basePos[0];
        particle->position.y = RandomFloat(rangeMin[1], rangeMax[1]) + basePos[1];
        particle->position.z = RandomFloat(rangeMin[2], rangeMax[2]) + basePos[2];
    } else if (emitType == 1) {
        float radius = *(float*)((char*)data + 0xC4);
        float radiusVar = *(float*)((char*)data + 0xC8);
        float r = RandomFloat(0.0f, (rand() & 1) ? radius : radius + radiusVar);
        float theta = RandomFloat(0.0f, 180.0f);
        float phi = RandomFloat(0.0f, 360.0f);
        float sinTheta = sinf(theta * DEG2RAD);
        float sinPhi = sinf(phi * DEG2RAD);
        particle->position.x = sinPhi * sinTheta * r + basePos[0];
        particle->position.y = cosf(theta * DEG2RAD) * r + basePos[1];
        particle->position.z = cosf(phi * DEG2RAD) * sinTheta * r + basePos[2];
    } else if (emitType == 2) {
        int numVerts = *(int*)((char*)data + 0xD4);
        int idx = RandomInt(0, numVerts - 1);
        gbVec3D* verts = *(gbVec3D**)((char*)data + 0xCC);
        gbMatrix4* mat = (gbMatrix4*)((char*)data + 0xD8);
        gbVec3D pos;
        pos.x = mat->m[0][0] * verts[idx].x + mat->m[1][0] * verts[idx].y + mat->m[2][0] * verts[idx].z + mat->m[3][0];
        pos.y = mat->m[0][1] * verts[idx].x + mat->m[1][1] * verts[idx].y + mat->m[2][1] * verts[idx].z + mat->m[3][1];
        pos.z = mat->m[0][2] * verts[idx].x + mat->m[1][2] * verts[idx].y + mat->m[2][2] * verts[idx].z + mat->m[3][2];
        particle->position.x = pos.x + basePos[0];
        particle->position.y = pos.y + basePos[1];
        particle->position.z = pos.z + basePos[2];
    }
}

void gbPartEmitter::ComputeParticleInitVel(gbEmitterData* emitData, gbParticleUnit* particle) {
    float speedMin = *(float*)((char*)emitData + 0x0C);
    float speedMax = *(float*)((char*)emitData + 0x10);
    float speed = RandomFloat(speedMin, speedMax);
    float* randDeviation = (float*)((char*)data + 0x4C);

    particle->velocity.x = speed * emitData->velocity.x + RandomFloat(-randDeviation[0], randDeviation[0]);
    particle->velocity.y = speed * emitData->velocity.y + RandomFloat(-randDeviation[1], randDeviation[1]);
    particle->velocity.z = speed * emitData->velocity.z + RandomFloat(-randDeviation[2], randDeviation[2]);
}

void gbPartEmitter::SetLoopEmit(bool loop) {
    *(int*)((char*)data + 0x9C) = loop ? 1 : 0;
}

/* ======== gbParticleUnit ======== */

gbParticleUnit::gbParticleUnit(void) {
    memset(this, 0, sizeof(gbParticleUnit));
}

gbParticleUnit::gbParticleUnit(const gbParticleUnit& other) {
    memcpy(this, &other, sizeof(gbParticleUnit));
}

/* ======== gbParticleGroup ======== */

gbParticleGroup::gbParticleGroup(void) {
    groupName = NULL;
    unused1 = 0;
    unused2 = 0;
}

gbParticleGroup::~gbParticleGroup(void) {
}

gbParticleGroup& gbParticleGroup::operator=(const gbParticleGroup& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbParticleGroup));
    }
    return *this;
}

void gbParticleGroup::LoadFromFile(gbVFile* vfile, gbParticleEffect* effect) {
    if (!vfile || !effect) return;
    numAliveParticles = 0;
}

void gbParticleGroup::Reset(void) {
    numAliveParticles = 0;
}

int gbParticleGroup::GetAlivePartNum(void) {
    return numAliveParticles;
}

char* gbParticleGroup::GetName(void) {
    return groupName;
}

gbPartGroupParam* gbParticleGroup::GetGroupParam(void) {
    return pGroupParam;
}

gbParticleUnit* gbParticleGroup::GetOldestParticle(void) {
    if (numAliveParticles <= 0) return NULL;

    double maxAge = -1.0;
    int oldestIndex = 0;

    for (int i = 0; i < numAliveParticles; i++) {
        if (particleArray[i].age > maxAge) {
            maxAge = particleArray[i].age;
            oldestIndex = i;
        }
    }

    return &particleArray[oldestIndex];
}

gbParticleUnit* gbParticleGroup::CreateOneParticle(gbEmitterData* emitData) {
    gbParticleUnit* particle = NULL;

    if (numAliveParticles == maxParticles) {
        particle = GetOldestParticle();
        if (!particle) return NULL;
    } else {
        particle = &particleArray[numAliveParticles];
        numAliveParticles++;
    }

    particle->age = 0.0;
    particle->alive = 1;
    particle->lifetime = emitData->lifetime;
    particle->frame = 0;
    particle->rotationDir = (rand() & 1) ? -1 : 1;
    particle->velocity = emitData->velocity;

    pEmitter->ComputeParticleInitPos(particle);
    pGroupParam->InitParticleParam(particle);

    return particle;
}

int gbParticleGroup::UpdateOneParticle(gbParticleUnit* particle, double deltaTime) {
    particle->age += deltaTime;

    if (particle->age >= particle->lifetime) {
        return 0;
    }

    float lifeFactor = (float)(particle->age / particle->lifetime);
    particle->frame = (int)(lifeFactor * pGroupParam->numFrames);
    if (particle->frame >= pGroupParam->numFrames) {
        particle->frame = 0;
    }

    float dt = (float)deltaTime;
    pGroupParam->ComputeAirResist(particle, dt);
    pGroupParam->ComputeParticleParam(particle, lifeFactor, dt);

    particle->velocityY -= pGroupParam->gravity * dt;

    particle->position.x += particle->velocity.x * dt;
    particle->position.y += particle->velocityY * dt - pGroupParam->gravity * dt * dt * HALF_FACTOR;
    particle->position.z += particle->velocity.z * dt;

    return 1;
}

void gbParticleGroup::Update(double deltaTime) {
    for (int i = 0; i < numAliveParticles; ) {
        if (!UpdateOneParticle(&particleArray[i], deltaTime)) {
            if (i < numAliveParticles - 1) {
                particleArray[i] = particleArray[numAliveParticles - 1];
            }
            numAliveParticles--;
        } else {
            i++;
        }
    }
}

void gbParticleGroup::Render(void) {
    if (!pGroupParam->GetRenderEffect()) return;
}


/* ======== gbVisNodeBase ======== */

gbVisNodeBase::gbVisNodeBase() {
    memset(_visnode_data, 0, sizeof(_visnode_data));
}

gbVisNodeBase::~gbVisNodeBase() {
}

void gbVisNodeBase::Update() {
    // Base class - no operation
    (void)0;
}

void gbVisNodeBase::Render(gbRenderInfoObj* renderInfo) {
    (void)renderInfo;
}

int gbVisNodeBase::Attach(gbRenderEffect* effect) {
    (void)effect;
    return 0;
}

void gbVisNodeBase::GetBoundSphere(gbSphere* sphere) {
    if (sphere) {
        sphere->center.x = sphere->center.y = sphere->center.z = 0.0f;
        sphere->radius = 0.0f;
    }
}

void gbVisNodeBase::Reset(float time) {
    (void)time;
}

/* ======== gbParticleEffect ======== */

gbParticleEffect::gbParticleEffect(void) {
    particleGroups = NULL;
    numGroups = 0;
    groupParams = NULL;
    numParams = 0;
    emitters = NULL;
    numEmitters = 0;
    effectName = NULL;
    unused1 = 0;
    unused2 = 0;
    unused3 = 0;
    spaceScale = 1.0f;
    unused4 = -256.0f;
}

gbParticleEffect::gbParticleEffect(const gbParticleEffect& other) {
    memcpy(this, &other, sizeof(gbParticleEffect));
}

gbParticleEffect::~gbParticleEffect(void) {
}

gbParticleEffect& gbParticleEffect::operator=(const gbParticleEffect& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbParticleEffect));
    }
    return *this;
}

int gbParticleEffect::LoadFromFile(char* filename) {
    return 1;
}

void gbParticleEffect::Reset(float time) {
    for (int i = 0; i < numGroups; i++) {
        if (particleGroups[i]) {
            particleGroups[i]->Reset();
        }
    }
}

void gbParticleEffect::Update(void) {
    UpdateInternal();
}

void gbParticleEffect::UpdateInternal(void) {
    double deltaTime = 0.016;
    for (int i = 0; i < numGroups; i++) {
        if (particleGroups[i]) {
            particleGroups[i]->Update(deltaTime);
        }
    }
}

int gbParticleEffect::Attach(gbRenderEffect* effect) {
    return 1;
}

void gbParticleEffect::GetBoundSphere(gbSphere* sphere) {
    sphere->center.x = 0.0f;
    sphere->center.y = 0.0f;
    sphere->center.z = 0.0f;
    sphere->radius = 100.0f;
}

void gbParticleEffect::Render(gbRenderInfoObj* renderInfo) {
    for (int i = 0; i < numGroups; i++) {
        if (particleGroups[i]) {
            particleGroups[i]->Render();
        }
    }
}

gbParticleGroup* gbParticleEffect::GetParticleGroup(int index) {
    if (index < 0 || index >= numGroups) return NULL;
    return particleGroups[index];
}

gbPartGroupParam* gbParticleEffect::GetGroupParam(int index) {
    if (index < 0 || index >= numParams) return NULL;
    return groupParams[index];
}

gbPartEmitter* gbParticleEffect::GetEmitter(int index) {
    if (index < 0 || index >= numEmitters) return NULL;
    return emitters[index];
}

void gbParticleEffect::SetSpaceScale(float scale) {
    spaceScale = scale;
}

float gbParticleEffect::GetSpaceScale(void) {
    return spaceScale;
}
