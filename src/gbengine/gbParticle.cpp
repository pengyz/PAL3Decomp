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
}

void gbPartGroupParam::ComputeAirResist(gbParticleUnit* particle, float deltaTime) {
}

void gbPartGroupParam::ComputeParticleParam(gbParticleUnit* particle, float lifeFactor, float deltaTime) {
}

void gbPartGroupParam::InitParticleParam(gbParticleUnit* particle) {
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
}

int gbPartEmitter::ComputeEmitterData(gbEmitterData* emitData, double time, double deltaTime) {
    return 1;
}

void gbPartEmitter::ComputeParticleInitPos(gbParticleUnit* particle) {
}

void gbPartEmitter::ComputeParticleInitVel(gbEmitterData* emitData, gbParticleUnit* particle) {
}

void gbPartEmitter::SetLoopEmit(bool loop) {
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
}

void gbVisNodeBase::Render(gbRenderInfoObj* renderInfo) {
}

int gbVisNodeBase::Attach(gbRenderEffect* effect) {
    return 0;
}

void gbVisNodeBase::GetBoundSphere(gbSphere* sphere) {
}

void gbVisNodeBase::Reset(float time) {
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
