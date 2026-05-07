/**
 * gbengine.dll - gbParticle
 * Particle system implementation
 * Functions: 38
 */

#include "gbengine/gbParticle.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_internal.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

// External globals
extern gbVFileSystem* g_pVFileSys;
extern gbGfxManager* g_pGfxManager;
extern char* gbVfgetname(const char* path, char* buf, int maxLen);

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

// Ghidra: gbPartParamControl_1000cd90 (93 bytes)
gbPartParamControl::gbPartParamControl(void) {
    memset(stateData, 0, sizeof(stateData));
    memset(curveConfig, 0, sizeof(curveConfig));
    memset(ch0Keys, 0, sizeof(ch0Keys));
    ch0Pad = 0;
    memset(ch1Keys, 0, sizeof(ch1Keys));
    memset(ch2Keys, 0, sizeof(ch2Keys));
    ch2LastValue = 0.0f;
    ch2LastTangentIn = 0.0f;
}

gbPartParamControl& gbPartParamControl::operator=(const gbPartParamControl& other) {
    int i;
    controlType = other.controlType;
    numKeys = other.numKeys;
    for (i = 0; i < 0xC0; i++) configData[i] = other.configData[i];
    for (i = 0; i < 0x18; i++) stateData[i] = other.stateData[i];
    for (i = 0; i < 0x2D0; i++) curveConfig[i] = other.curveConfig[i];
    for (i = 0; i < GB_PARTCTRL_MAX_KEYS; i++) ch0Keys[i] = other.ch0Keys[i];
    ch0Pad = other.ch0Pad;
    for (i = 0; i < GB_PARTCTRL_MAX_KEYS; i++) ch1Keys[i] = other.ch1Keys[i];
    for (i = 0; i < GB_PARTCTRL_MAX_KEYS - 1; i++) ch2Keys[i] = other.ch2Keys[i];
    ch2LastValue = other.ch2LastValue;
    ch2LastTangentIn = other.ch2LastTangentIn;
    return *this;
}

void gbPartParamControl::LoadFromFile(gbVFile* vfile) {
    g_pVFileSys->Read(&controlType, 4u, vfile);
    g_pVFileSys->Read(&numKeys, 4u, vfile);
    g_pVFileSys->Read(configData, 0x40u, vfile);
    g_pVFileSys->Read(configData + 0x40, 0x80u, vfile);
    g_pVFileSys->Read(stateData + 0x0C, 0x0Cu, vfile);
    g_pVFileSys->Read(stateData, 0x0Cu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read(curveConfig, 0x2D0u, vfile);
    g_pVFileSys->Read(ch0Keys, 0xE34u, vfile);
}

// Ghidra: GetValue_100299b0 (252 bytes)
void gbPartParamControl::GetValue(float* result, float t) {
    if (t <= ch0Keys[0].time) {
        result[0] = ch0Keys[0].value;
        result[1] = ch1Keys[0].value;
        result[2] = ch2Keys[0].value;
        return;
    }

    int i = 1;
    do {
        if (t < ch0Keys[i].time) {
            float factor = (t - ch0Keys[i - 1].time) / (ch0Keys[i].time - ch0Keys[i - 1].time);
            float invFactor = 1.0f - factor;

            result[0] = factor * ch0Keys[i].value + invFactor * ch0Keys[i - 1].value;
            result[1] = factor * ch1Keys[i].value + invFactor * ch1Keys[i - 1].value;
            result[2] = factor * ch2Keys[i].value + invFactor * ch2Keys[i - 1].value;
            return;
        }
        i++;
    } while (i <= 0x64);

    result[0] = ch0Keys[GB_PARTCTRL_MAX_KEYS - 1].value;
    result[1] = ch1Keys[GB_PARTCTRL_MAX_KEYS - 1].value;
    result[2] = ch2LastValue;
}

/* ======== gbPartGroupParam ======== */

gbPartGroupParam::gbPartGroupParam(void) {
    memset(this, 0, sizeof(gbPartGroupParam));
}

gbPartGroupParam::~gbPartGroupParam(void) {
    if (pRenderEffect) {
        ((gbRefObject*)pRenderEffect)->Release();
        pRenderEffect = NULL;
    }
    for (int i = 0; i < textureLoaded; i++) {
        ((gbRefObject*)pTextures[i])->Release();
    }
}

gbPartGroupParam& gbPartGroupParam::operator=(const gbPartGroupParam& other) {
    int i;
    for (i = 0; i < 32; i++) name[i] = other.name[i];
    flags = other.flags;
    gravity = other.gravity;
    airResistance = other.airResistance;
    unused1 = other.unused1;
    turbulenceFlag = other.turbulenceFlag;
    dragCoefficient = other.dragCoefficient;
    for (i = 0; i < 256; i++) textureName[i] = other.textureName[i];
    blendMode = other.blendMode;
    unused4 = other.unused4;
    unused5 = other.unused5;
    unused6 = other.unused6;
    rotRandMin = other.rotRandMin;
    rotRandMax = other.rotRandMax;
    randomRotation = other.randomRotation;
    unused9 = other.unused9;
    unused10 = other.unused10;
    unused11 = other.unused11;
    numFrames = other.numFrames;
    blendType = other.blendType;
    sizeControl = other.sizeControl;
    rotControl = other.rotControl;
    alphaControl = other.alphaControl;
    colorControl = other.colorControl;
    for (i = 0; i < 16; i++) pTextures[i] = other.pTextures[i];
    textureLoaded = other.textureLoaded;
    pRenderEffect = other.pRenderEffect;
    return *this;
}

void gbPartGroupParam::LoadFromFile(gbVFile* vfile) {
    g_pVFileSys->Read(name, 0x20u, vfile);
    g_pVFileSys->Read(&flags, 4u, vfile);
    g_pVFileSys->Read(&gravity, 4u, vfile);
    g_pVFileSys->Read(&airResistance, 4u, vfile);
    g_pVFileSys->Read(&unused1, 4u, vfile);
    g_pVFileSys->Read(&turbulenceFlag, 4u, vfile);
    g_pVFileSys->Read(&dragCoefficient, 4u, vfile);
    g_pVFileSys->Read(textureName, 0x100u, vfile);
    g_pVFileSys->Read(&blendMode, 4u, vfile);
    g_pVFileSys->Read(&unused4, 4u, vfile);
    g_pVFileSys->Read(&unused5, 4u, vfile);
    g_pVFileSys->Read(&unused6, 4u, vfile);
    g_pVFileSys->Read(&rotRandMin, 4u, vfile);
    g_pVFileSys->Read(&rotRandMax, 4u, vfile);
    g_pVFileSys->Read(&randomRotation, 4u, vfile);
    g_pVFileSys->Read(&unused9, 4u, vfile);
    g_pVFileSys->Read(&unused10, 4u, vfile);
    g_pVFileSys->Read(&unused11, 4u, vfile);
    g_pVFileSys->Read(&numFrames, 4u, vfile);
    g_pVFileSys->Read(&blendType, 4u, vfile);

    sizeControl.LoadFromFile(vfile);
    rotControl.LoadFromFile(vfile);
    alphaControl.LoadFromFile(vfile);
    colorControl.LoadFromFile(vfile);

    char filename[256];
    char dir[256];
    gbVfgetname(textureName, filename, 256);

    if (textureName[0]) {
        ((gbVFile1*)vfile)->GetDir(dir, 256);
        strcat(dir, "partexture\\");
        strcat(dir, filename);

        pTextures[0] = g_pGfxManager->NewTexture(dir);
        pTextures[0]->LoadTexture(1);
        textureLoaded = 1;
    }

    gbEffectMgr* effectMgr = g_pGfxManager->GetEffectMgr();
    if (blendType)
        pRenderEffect = effectMgr->NewRenderEffect("gfxscript\\p_alph.gfx", 0);
    else
        pRenderEffect = effectMgr->NewRenderEffect("gfxscript\\p_add_g.gfx", 0);
}

void gbPartGroupParam::ComputeAirResist(gbParticleUnit* particle, float deltaTime) {
    float* vel = &particle->velocity.x;
    float speed = sqrtf(vel[0] * vel[0] + vel[1] * vel[1] + vel[2] * vel[2]);
    float invSpeed = 1.0f / speed;

    if (speed <= airResistance) return;

    float turbX = 0.0f, turbY = 0.0f, turbZ = 0.0f;

    if (turbulenceFlag == 0) {
        turbX = turbY = turbZ = 0.0f;
    } else {
        float turbForce = particle->size * dragCoefficient;
        turbX = invSpeed * vel[0] * turbForce;
        turbY = invSpeed * vel[1] * turbForce;
        turbZ = invSpeed * vel[2] * turbForce;
    }

    vel[0] -= (dragCoefficient * vel[0] * deltaTime + turbX * deltaTime);
    vel[1] -= (turbY * deltaTime + dragCoefficient * vel[1] * deltaTime);
    vel[2] -= (turbZ * deltaTime + dragCoefficient * vel[2] * deltaTime);
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

    rotControl.GetValue(val, lifeFactor);
    int randDev = RandomInt(rotRandMin, rotRandMax);
    particle->rotation = ((float)randDev + val[0]) * deltaTime + particle->rotation;
    particle->rotation *= particle->rotationDir;

    alphaControl.GetValue(val, lifeFactor);
    float alphaVal = val[0];

    colorControl.GetValue(val, lifeFactor);
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

    rotControl.GetValue(val, 0.0f);
    particle->rotation = 0.0f;

    alphaControl.GetValue(val, 0.0f);
    float alphaInit = val[0];

    colorControl.GetValue(val, 0.0f);
    particle->colorR = (unsigned char)(int)val[0];
    particle->colorG = (unsigned char)(int)val[1];
    particle->colorB = (unsigned char)(int)val[2];
    particle->colorA = (unsigned char)(int)(alphaInit * 255.0f);
}

gbTexture* gbPartGroupParam::GetTexture(void) {
    return pTextures[0];
}

gbRenderEffect* gbPartGroupParam::GetRenderEffect(void) {
    return pRenderEffect;
}

/* ======== gbPartEmitter ======== */

gbPartEmitter::gbPartEmitter(void) {
    memset(this, 0, sizeof(gbPartEmitter));
}

gbPartEmitter::~gbPartEmitter(void) {
}

gbPartEmitter& gbPartEmitter::operator=(const gbPartEmitter& other) {
    int i;
    for (i = 0; i < 0x40; i++) configData[i] = other.configData[i];
    basePosition = other.basePosition;
    velocityDeviation = other.velocityDeviation;
    for (i = 0; i < 0x40; i++) meshFilename[i] = other.meshFilename[i];
    emitType = other.emitType;
    emitDuration = other.emitDuration;
    emitStartTime = other.emitStartTime;
    loopFlag = other.loopFlag;
    field_A8 = other.field_A8;
    boxMin = other.boxMin;
    boxMax = other.boxMax;
    sphereRadius = other.sphereRadius;
    sphereRadiusVar = other.sphereRadiusVar;
    pMeshVertices = other.pMeshVertices;
    meshVertBufSize = other.meshVertBufSize;
    numMeshVertices = other.numMeshVertices;
    meshTransform = other.meshTransform;
    meshDataVersion = other.meshDataVersion;
    pad_11C = other.pad_11C;
    for (i = 0; i < 6; i++) paramControls[i] = other.paramControls[i];
    return *this;
}

// Global particle file version (determines which fields are present in file format)
int g_particleFileVersion;

void gbPartEmitter::LoadFromFile(gbVFile* vfile) {
    g_pVFileSys->Read(configData, 0x40u, vfile);
    g_pVFileSys->Read(&basePosition, sizeof(gbVec3D), vfile);
    g_pVFileSys->Read(&velocityDeviation, sizeof(gbVec3D), vfile);
    g_pVFileSys->Read(&emitType, 4u, vfile);

    if (g_particleFileVersion > 0x10000) {
        g_pVFileSys->Read(meshFilename, 0x40u, vfile);
        g_pVFileSys->Read(&meshDataVersion, 4u, vfile);
    }

    g_pVFileSys->Read(&emitDuration, 4u, vfile);
    g_pVFileSys->Read(&emitStartTime, 4u, vfile);
    g_pVFileSys->Read(&loopFlag, 4u, vfile);
    g_pVFileSys->Read(&field_A8, 4u, vfile);
    g_pVFileSys->Read(&sphereRadius, 8u, vfile);
    g_pVFileSys->Read(&boxMin, 0x18u, vfile);

    for (int i = 0; i < 6; i++) {
        paramControls[i].LoadFromFile(vfile);
    }

    /* TODO: mesh emitter path loading (emitType==2)
       Ghidra shows: gbVFile1::GetDir(vfile, path, 255) + strcat(meshFilename)
       But gbVFile* != gbVFile1* — need to understand the actual relationship
       before implementing this branch. */
}

int gbPartEmitter::ComputeEmitterData(gbEmitterData* emitData, double time, double deltaTime) {
    float cycleDuration = emitDuration - emitStartTime;

    int cycleCount = (int)(time / cycleDuration);
    double localTime = time;
    if (cycleCount > 1) {
        if (!loopFlag)
            return 0;
        localTime = time - (double)cycleCount * cycleDuration;
    }

    float t = (float)(localTime / cycleDuration);

    // paramControls[0]: velocity
    paramControls[0].GetValue(&emitData->velocity.x, t);

    // paramControls[1]: speed range
    float speedVals[2];
    paramControls[1].GetValue(speedVals, t);
    if (speedVals[0] <= speedVals[1]) {
        emitData->speedMin = speedVals[1];
        emitData->speedMax = speedVals[0];
    } else {
        emitData->speedMin = speedVals[0];
        emitData->speedMax = speedVals[1];
    }

    // paramControls[2]: lifetime range
    float lifeVals[2];
    paramControls[2].GetValue(lifeVals, t);
    if (lifeVals[0] <= lifeVals[1]) {
        emitData->lifetimeMin = lifeVals[1];
        emitData->lifetimeMax = lifeVals[0];
    } else {
        emitData->lifetimeMin = lifeVals[0];
        emitData->lifetimeMax = lifeVals[1];
    }

    // paramControls[3]: emit rate range
    float rateVals[2];
    paramControls[3].GetValue(rateVals, t);
    if (rateVals[0] <= rateVals[1]) {
        emitData->emitRateMin = rateVals[1];
        emitData->emitRateMax = rateVals[0];
    } else {
        emitData->emitRateMin = rateVals[0];
        emitData->emitRateMax = rateVals[1];
    }

    // Calculate particles to emit this frame
    double accumulated = emitData->emitRateMax * deltaTime + emitData->emitAccumulator;
    int numToEmit = (int)accumulated;
    emitData->emitAccumulator = accumulated - (double)numToEmit;
    return numToEmit;
}

void gbPartEmitter::ComputeParticleInitPos(gbParticleUnit* particle) {
    if (emitType == 0) {
        particle->position.x = RandomFloat(boxMin.x, boxMax.x) + basePosition.x;
        particle->position.y = RandomFloat(boxMin.y, boxMax.y) + basePosition.y;
        particle->position.z = RandomFloat(boxMin.z, boxMax.z) + basePosition.z;
    } else if (emitType == 1) {
        float r = RandomFloat(0.0f, (rand() & 1) ? sphereRadius : sphereRadius + sphereRadiusVar);
        float theta = RandomFloat(0.0f, 180.0f);
        float phi = RandomFloat(0.0f, 360.0f);
        float sinTheta = sinf(theta * DEG2RAD);
        float sinPhi = sinf(phi * DEG2RAD);
        particle->position.x = sinPhi * sinTheta * r + basePosition.x;
        particle->position.y = cosf(theta * DEG2RAD) * r + basePosition.y;
        particle->position.z = cosf(phi * DEG2RAD) * sinTheta * r + basePosition.z;
    } else if (emitType == 2) {
        int idx = RandomInt(0, numMeshVertices - 1);
        gbVec3D pos;
        pos.x = meshTransform.m[0][0] * pMeshVertices[idx].x + meshTransform.m[1][0] * pMeshVertices[idx].y + meshTransform.m[2][0] * pMeshVertices[idx].z + meshTransform.m[3][0];
        pos.y = meshTransform.m[0][1] * pMeshVertices[idx].x + meshTransform.m[1][1] * pMeshVertices[idx].y + meshTransform.m[2][1] * pMeshVertices[idx].z + meshTransform.m[3][1];
        pos.z = meshTransform.m[0][2] * pMeshVertices[idx].x + meshTransform.m[1][2] * pMeshVertices[idx].y + meshTransform.m[2][2] * pMeshVertices[idx].z + meshTransform.m[3][2];
        particle->position.x = pos.x + basePosition.x;
        particle->position.y = pos.y + basePosition.y;
        particle->position.z = pos.z + basePosition.z;
    }
}

void gbPartEmitter::ComputeParticleInitVel(gbEmitterData* emitData, gbParticleUnit* particle) {
    float speed = RandomFloat(emitData->speedMin, emitData->speedMax);

    particle->velocity.x = speed * emitData->velocity.x + RandomFloat(-velocityDeviation.x, velocityDeviation.x);
    particle->velocity.y = speed * emitData->velocity.y + RandomFloat(-velocityDeviation.y, velocityDeviation.y);
    particle->velocity.z = speed * emitData->velocity.z + RandomFloat(-velocityDeviation.z, velocityDeviation.z);
}

void gbPartEmitter::SetLoopEmit(bool loop) {
    loopFlag = loop;
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
    particleArray = NULL;
}

gbParticleGroup::~gbParticleGroup(void) {
    if (particleArray) {
        free(particleArray);
    }
}

gbParticleGroup& gbParticleGroup::operator=(const gbParticleGroup& other) {
    int i;
    for (i = 0; i < 0x40; i++) baseData[i] = other.baseData[i];
    field_40 = other.field_40;
    field_44 = other.field_44;
    groupName = other.groupName;
    unused1 = other.unused1;
    unused2 = other.unused2;
    for (i = 0; i < 0x1C; i++) padding2[i] = other.padding2[i];
    field_70 = other.field_70;
    field_74 = other.field_74;
    pGroupParam = other.pGroupParam;
    pEmitter = other.pEmitter;
    particleArray = other.particleArray;
    maxParticles = other.maxParticles;
    numAliveParticles = other.numAliveParticles;
    pParticleEffect = other.pParticleEffect;
    return *this;
}

void gbParticleGroup::LoadFromFile(gbVFile* vfile, gbParticleEffect* effect) {
    int emitterIdx, groupParamIdx;

    pParticleEffect = effect;
    g_pVFileSys->Read(baseData, 0x40u, vfile);
    g_pVFileSys->Read(&emitterIdx, 4u, vfile);
    g_pVFileSys->Read(&groupParamIdx, 4u, vfile);
    g_pVFileSys->Read(&maxParticles, 4u, vfile);

    pEmitter = effect->GetEmitter(emitterIdx);
    pGroupParam = effect->GetGroupParam(groupParamIdx);

    gbParticleUnit* particles = (gbParticleUnit*)operator new(sizeof(gbParticleUnit) * maxParticles);
    if (particles) {
        for (int i = maxParticles - 1; i >= 0; i--) {
            memset(&particles[i].velocity, 0, 9 * sizeof(int));
        }
    }
    particleArray = particles;

    field_40 = 0;
    field_70 = 0;
    field_44 = 0;
    field_74 = 0;

    for (int i = 0; i < maxParticles; i++) {
        particleArray[i].alive = 0;
    }

    numAliveParticles = 0;
}

void gbParticleGroup::Reset(void) {
    int n = maxParticles;
    int i = 0;
    field_40 = 0;
    field_70 = 0;
    field_44 = 0;
    field_74 = 0;
    if (n <= 0) {
        numAliveParticles = 0;
    } else {
        int off = 0;
        do {
            i++;
            *(int*)((char*)particleArray + off) = 0;
            off += 88;
        } while (i < maxParticles);
        numAliveParticles = 0;
    }
}

int gbParticleGroup::GetAlivePartNum(void) {
    return numAliveParticles;
}

char* gbParticleGroup::GetName(void) {
    return (char*)this;
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
    particle->lifetime = RandomFloat(emitData->lifetimeMin, emitData->lifetimeMax);
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
    gbGfxManager* pGfxMgr = g_pGfxManager;
    gbTextureArray texArray;
    texArray.numTextures = 1;
    texArray.pTex[0] = pGroupParam->pTextures[0];

    gbDynVertBuf* pDVB = pGfxMgr->pVertPoolMgr->GetDynVertBuf(0x15u);
    gbMatrixStack* pMatStack = pGfxMgr->pMatrixStack[1];

    float particleScale = pParticleEffect->spaceScale;
    double invCols = 1.0 / (double)pGroupParam->numFrames;
    double invRows = 1.0 / (double)pGroupParam->unused11;

    float* pVerts = pDVB->Lock(6 * numAliveParticles);
    if (pVerts) {
        int i;
        for (i = 0; i < numAliveParticles; i++) {
            gbParticleUnit* p = &particleArray[i];

            float px, py, pz;
            if (pParticleEffect->field_B4) {
                px = particleScale * p->position.x;
                py = particleScale * p->position.y;
                pz = particleScale * p->position.z;
            } else {
                px = p->position.x;
                py = p->position.y;
                pz = p->position.z;
            }

            gbVec3D pos;
            pos.x = px;
            pos.y = py;
            pos.z = pz;

            gbMatrix4* pTop = pMatStack->GetTop();
            pTop->Transform(&pos, 1);

            unsigned int color = *(unsigned int*)&p->colorR;
            float halfSize = particleScale * p->size * 0.5f;

            float u0 = (float)p->frame * (float)invCols;
            float v0 = 1.0f - (float)(p->randomSeed + 1) * (float)invRows;
            float u1 = u0 + (float)invCols;
            float v1 = v0 + (float)invRows;

            float angle = p->rotation * 0.017453292f;
            float cosR = (float)cos(angle);
            float sinR = (float)sin(angle);

            float negHalf = -halfSize;
            float nc = negHalf * cosR;
            float ns = negHalf * sinR;
            float pc = halfSize * cosR;
            float ps = halfSize * sinR;

            // Rotated billboard quad corners (rotation in XY plane around pos)
            float c0x = nc - ns + pos.x;
            float c0y = nc + ns + pos.y;
            float c1x = pc - ns + pos.x;
            float c1y = ps + nc + pos.y;
            float c2x = pc - ps + pos.x;
            float c2y = pc + ps + pos.y;
            float c3x = nc - ps + pos.x;
            float c3y = pc + ns + pos.y;

            // Triangle list: 6 vertices forming 2 triangles (0,1,3  3,1,2)
            // Vertex 0: corner0, uv=(u0, v0)
            pVerts[0] = c0x; pVerts[1] = c0y; pVerts[2] = pos.z;
            *(unsigned int*)&pVerts[3] = color;
            pVerts[4] = u0; pVerts[5] = v0;
            // Vertex 1: corner1, uv=(u1, v0)
            pVerts[6] = c1x; pVerts[7] = c1y; pVerts[8] = pos.z;
            *(unsigned int*)&pVerts[9] = color;
            pVerts[10] = u1; pVerts[11] = v0;
            // Vertex 2: corner3, uv=(u0, v1)
            pVerts[12] = c3x; pVerts[13] = c3y; pVerts[14] = pos.z;
            *(unsigned int*)&pVerts[15] = color;
            pVerts[16] = u0; pVerts[17] = v1;
            // Vertex 3: corner3, uv=(u0, v1)
            pVerts[18] = c3x; pVerts[19] = c3y; pVerts[20] = pos.z;
            *(unsigned int*)&pVerts[21] = color;
            pVerts[22] = u0; pVerts[23] = v1;
            // Vertex 4: corner1, uv=(u1, v0)
            pVerts[24] = c1x; pVerts[25] = c1y; pVerts[26] = pos.z;
            *(unsigned int*)&pVerts[27] = color;
            pVerts[28] = u1; pVerts[29] = v0;
            // Vertex 5: corner2, uv=(u1, v1)
            pVerts[30] = c2x; pVerts[31] = c2y; pVerts[32] = pos.z;
            *(unsigned int*)&pVerts[33] = color;
            pVerts[34] = u1; pVerts[35] = v1;

            pVerts += 36;
        }

        pMatStack->Push();
        pMatStack->LoadIdentity();
        pDVB->Draw(1, pGroupParam->pRenderEffect, &texArray);
        pMatStack->Pop();
    }
}


/* ======== gbVisNodeBase ======== */

gbVisNodeBase::gbVisNodeBase() {
    memset(_visnode_data, 0, sizeof(_visnode_data));
}

gbVisNodeBase::~gbVisNodeBase() {
}

void gbVisNodeBase::Update() {
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
    memset(_effectBaseData, 0, sizeof(_effectBaseData));
    numGroups = 0;
    numParams = 0;
    numEmitters = 0;
    particleGroups = NULL;
    groupParams = NULL;
    emitters = NULL;
    field_B0 = 0;
    field_B4 = 0;
    field_B8 = 0;
    memset(_effectData2, 0, sizeof(_effectData2));
    spaceScale = 1.0f;
}

gbParticleEffect::gbParticleEffect(const gbParticleEffect& other) {
    memcpy(this, &other, sizeof(gbParticleEffect));
}

gbParticleEffect::~gbParticleEffect(void) {
    if (particleGroups) {
        delete[] particleGroups;
    }
    if (groupParams) {
        delete[] groupParams;
    }
    if (emitters) {
        delete[] emitters;
    }
}

gbParticleEffect& gbParticleEffect::operator=(const gbParticleEffect& other) {
    int i;
    for (i = 4; i < 0x58; i++) _visnode_data[i] = other._visnode_data[i];
    for (i = 0; i < 64; i++) _effectBaseData[i] = other._effectBaseData[i];
    numGroups = other.numGroups;
    numParams = other.numParams;
    numEmitters = other.numEmitters;
    particleGroups = other.particleGroups;
    groupParams = other.groupParams;
    emitters = other.emitters;
    field_B0 = other.field_B0;
    field_B4 = other.field_B4;
    field_B8 = other.field_B8;
    for (i = 0; i < 0x5C; i++) _effectData2[i] = other._effectData2[i];
    spaceScale = other.spaceScale;
    worldTransform = other.worldTransform;
    return *this;
}

int gbParticleEffect::LoadFromFile(char* filename) {
    gbVFile* vfile = g_pVFileSys->OpenFile(filename, 0x201u);
    if (!vfile)
        return 0;

    char magic[8];
    g_pVFileSys->Read(magic, 6u, vfile);
    if (strcmp(magic, "SGPAR") != 0) {
        g_pVFileSys->CloseFile(vfile);
        return 0;
    }

    g_pVFileSys->Read(&g_particleFileVersion, 4u, vfile);
    g_pVFileSys->Read(&field_B0, 4u, vfile);
    g_pVFileSys->Read(&field_B4, 4u, vfile);
    g_pVFileSys->Read(&field_B8, 4u, vfile);

    if (g_particleFileVersion > 0x10000)
        g_pVFileSys->Read(&spaceScale, 4u, vfile);

    g_pVFileSys->Read(&numParams, 4u, vfile);
    g_pVFileSys->Read(&numEmitters, 4u, vfile);
    g_pVFileSys->Read(&numGroups, 4u, vfile);

    particleGroups = new gbParticleGroup[numGroups];
    groupParams = new gbPartGroupParam[numParams];
    emitters = new gbPartEmitter[numEmitters];

    int i;
    for (i = 0; i < numParams; i++)
        groupParams[i].LoadFromFile(vfile);

    for (i = 0; i < numEmitters; i++)
        emitters[i].LoadFromFile(vfile);

    for (i = 0; i < numGroups; i++)
        particleGroups[i].LoadFromFile(vfile, this);

    g_pVFileSys->CloseFile(vfile);
    return 1;
}

void gbParticleEffect::Reset(float time) {
    for (int i = 0; i < numGroups; i++) {
        particleGroups[i].Reset();
    }
}

void gbParticleEffect::Update(void) {
    UpdateInternal();
}

void gbParticleEffect::UpdateInternal(void) {
    double deltaTime = 0.016;
    for (int i = 0; i < numGroups; i++) {
        particleGroups[i].Update(deltaTime);
    }
}

int gbParticleEffect::Attach(gbRenderEffect* effect) {
    return 1;
}

void gbParticleEffect::GetBoundSphere(gbSphere* sphere) {
    sphere->radius = (float)sqrt(3.402823466e38);
    sphere->center.x = 0.0f;
    sphere->center.y = 0.0f;
    sphere->center.z = 0.0f;
}

void gbParticleEffect::Render(gbRenderInfoObj* renderInfo) {
    for (int i = 0; i < numGroups; i++) {
        particleGroups[i].Render();
    }
}

gbParticleGroup* gbParticleEffect::GetParticleGroup(int index) {
    return (gbParticleGroup*)((char*)particleGroups + 144 * index);
}

gbPartGroupParam* gbParticleEffect::GetGroupParam(int index) {
    return (gbPartGroupParam*)((char*)groupParams + 18752 * index);
}

gbPartEmitter* gbParticleEffect::GetEmitter(int index) {
    return (gbPartEmitter*)((char*)emitters + 27768 * index);
}

void gbParticleEffect::SetSpaceScale(float scale) {
    spaceScale = scale;
}

float gbParticleEffect::GetSpaceScale(void) {
    return spaceScale;
}


// ============================================================
// Additional export implementations
// ============================================================

#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbGfxManager.h"

extern gbVFileSystem* g_pVFileSys;
extern char* gbVfgetdir(const char* path, char* dir, int maxLen);

#pragma auto_inline(off)

#include "gbengine/gbengine_internal.h"

// Static member definition
gbGfxManager* gbAnimNodeGroup::s_pGfxMgr = 0;

// ---- gbAnimNodeGroup ----
gbAnimNodeGroup::gbAnimNodeGroup(class gbGfxManager * p0) {
    pNode = 0;
    field_24 = 0;
    s_pGfxMgr = p0;
    field_04 = 0;
    ((int*)&lastTime)[0] = 0;
    ((float*)&lastTime)[1] = -1.0f;
    elapsedTime = 0.0;
    field_18 = 0;
    field_28 = 0;
    isDead = 0;
    field_30 = 1;
}

gbAnimNodeGroup::~gbAnimNodeGroup() {
    if (pNode) {
        int* refCount = (int*)((char*)pNode + 0x174);
        (*refCount)--;
        if (*refCount == 0 && pNode != NULL) {
            delete (gbVisNode*)pNode;
        }
    }
}

class gbAnimNodeGroup & gbAnimNodeGroup::operator=(class gbAnimNodeGroup const & p0) {
    if (this != &p0) {
        memcpy(this, &p0, sizeof(gbAnimNodeGroup));
    }
    return *this;
}

void gbAnimNodeGroup::Attach() { if (!pNode) return; }

class gbAnimNodeGroup * gbAnimNodeGroup::Clone() {
    gbAnimNodeGroup* clone = new gbAnimNodeGroup((gbGfxManager*)s_pGfxMgr);
    *clone = *this;
    return clone;
}

int gbAnimNodeGroup::IsDead() {
    return isDead == 0;
}

void gbAnimNodeGroup::LoadFromFile(char * p0) {
    isDead = 0;
    gbVFile* file = g_pVFileSys->OpenFile(p0, 0x201);
    if (file) {
        char dirBuf[256];
        gbVfgetdir(p0, dirBuf, 256);
        int header;
        g_pVFileSys->Read(&header, 4, file);
        g_pVFileSys->Read(&field_1c, 4, file);
        g_pVFileSys->Read(&field_20, 4, file);
        g_pVFileSys->Read(&field_24, 4, file);
        g_pVFileSys->CloseFile(file);
    }
}

void gbAnimNodeGroup::Reset() {
    ((int*)&lastTime)[0] = 0;
    ((float*)&lastTime)[1] = -1.0f;
    elapsedTime = 0.0;
    field_18 = 0;
    field_28 = 0;
    isDead = 1;
}

void gbAnimNodeGroup::SetPosition(struct gbMatrix4 const & p0) {
    posMatrix = p0;
}

void gbAnimNodeGroup::SetPosition(struct gbVec3D const & p0) {
    posMatrix.LoadIdentity();
    int* dst = (int*)&posMatrix.m[3][0];
    int* src = (int*)&p0;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}

void gbAnimNodeGroup::SetPriority(int p0) {
    field_28 = p0;
}

void gbAnimNodeGroup::SetSoundFileDir(char * p0) {
    static char s_soundFileDir[256];
    if (!p0) {
        s_soundFileDir[0] = '\0';
        return;
    }
    strcpy(s_soundFileDir, p0);
}

void gbAnimNodeGroup::SetToDead() {
    isDead = 0;
}

void gbAnimNodeGroup::ShowGroup(int p0) {
    field_30 = p0;
}

void gbAnimNodeGroup::Update() {
    if (isDead == 0) return;
    if (field_30 == 0) return;

    double curTime = s_pGfxMgr->CurTime;
    double prevTime = lastTime;
    double elapsed = elapsedTime;
    int loopPlay = 0;

    double delta = 0.0;
    if (prevTime < 0.0) {
        loopPlay = 1;
    } else {
        delta = curTime - prevTime;
        if (delta >= 1.0) {
            delta = 0.0;
        }
    }

    lastTime = curTime;
    elapsedTime = elapsed + delta;

    int frames = (int)(elapsed + delta);
    if (frames >= 2) frames = 1;

    if (frames >= 1) {
        elapsedTime = 0.0;
        field_18 = field_18 + frames;
        if (field_20 <= field_18) {
            field_18 = 0;
            field_28 = field_28 + 1;
        }
        loopPlay = 1;
        if (field_24 != 0 && field_28 >= field_24) {
            isDead = 0;
            return;
        }
    }
}

// ---- gbEmitterData ----
gbEmitterData::gbEmitterData() { memset(this, 0, sizeof(*this)); }

struct gbEmitterData & gbEmitterData::operator=(struct gbEmitterData const & p0) {
    if (this != &p0) memcpy(this, &p0, sizeof(*this)); return *this;
}

// ---- gbEmitterSquare ----
gbEmitterSquare::gbEmitterSquare() { memset(this, 0, sizeof(*this)); }

struct gbEmitterSquare & gbEmitterSquare::operator=(struct gbEmitterSquare const & p0) {
    if (this != &p0) memcpy(this, &p0, sizeof(*this)); return *this;
}

// ---- gbParticleUnit ----
gbParticleUnit::gbParticleUnit(struct gbParticleUnit & other) { memcpy(this, &other, sizeof(gbParticleUnit)); }
struct gbParticleUnit & gbParticleUnit::operator=(struct gbParticleUnit const & p0) {
    if (this != &p0) memcpy(this, &p0, sizeof(*this)); return *this;
}

