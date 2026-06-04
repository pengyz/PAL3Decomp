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
    stateData[0] = 0;
    stateData[1] = 0;
    stateData[2] = 0;
    stateData[3] = 0;
    stateData[4] = 0;
    stateData[5] = 0;
}

gbPartParamControl& gbPartParamControl::operator=(const gbPartParamControl& other) {
    int i;
    controlType = other.controlType;
    numKeys = other.numKeys;
    for (i = 0; i < 0xC0; i++) configData[i] = other.configData[i];
    for (i = 0; i < 6; i++) stateData[i] = other.stateData[i];
    for (i = 0; i < 60; i++) curveKeys[i] = other.curveKeys[i];
    for (i = 0; i < 303; i++) keyData[i] = other.keyData[i];
    return *this;
}

void gbPartParamControl::LoadFromFile(gbVFile* vfile) {
    g_pVFileSys->Read(&controlType, 4u, vfile);
    g_pVFileSys->Read(&numKeys, 4u, vfile);
    g_pVFileSys->Read(configData, 0x40u, vfile);
    g_pVFileSys->Read(configData + 0x40, 0x80u, vfile);
    g_pVFileSys->Read((char*)stateData + 0x0C, 0x0Cu, vfile);
    g_pVFileSys->Read(stateData, 0x0Cu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read(curveKeys, 0x2D0u, vfile);
    g_pVFileSys->Read(keyData, 0xE34u, vfile);
}

// Ghidra: GetValue_100299b0 (252 bytes)
void gbPartParamControl::GetValue(float* result, float t) {
    // keyData layout: ch0[101] at +0, pad 4B, ch1[101] at +1216, ch2[100] at +2428, last 8B
    gbPartKeyframeCh0* ch0 = (gbPartKeyframeCh0*)keyData;
    gbPartKeyframeCh1* ch1 = (gbPartKeyframeCh1*)((char*)keyData + 1216);
    gbPartKeyframeCh1* ch2 = (gbPartKeyframeCh1*)((char*)keyData + 2428);

    if (t <= ch0[0].time) {
        result[0] = ch0[0].value;
        result[1] = ch1[0].value;
        result[2] = ch2[0].value;
        return;
    }

    int i = 1;
    do {
        if (t < ch0[i].time) {
            float factor = (t - ch0[i - 1].time) / (ch0[i].time - ch0[i - 1].time);
            float invFactor = 1.0f - factor;

            result[0] = factor * ch0[i].value + invFactor * ch0[i - 1].value;
            result[1] = factor * ch1[i].value + invFactor * ch1[i - 1].value;
            result[2] = factor * ch2[i].value + invFactor * ch2[i - 1].value;
            return;
        }
        i++;
    } while (i <= 0x64);

    result[0] = ch0[GB_PARTCTRL_MAX_KEYS - 1].value;
    result[1] = ch1[GB_PARTCTRL_MAX_KEYS - 1].value;
    float* lastData = (float*)((char*)keyData + 3628);
    result[2] = *lastData;
}

/* ======== gbPartGroupParam ======== */

gbPartGroupParam::gbPartGroupParam(void) {
    sizeControl.stateData[0] = 0;
    sizeControl.stateData[1] = 0;
    sizeControl.stateData[2] = 0;
    sizeControl.stateData[3] = 0;
    sizeControl.stateData[4] = 0;
    sizeControl.stateData[5] = 0;
    rotControl.stateData[0] = 0;
    rotControl.stateData[1] = 0;
    rotControl.stateData[2] = 0;
    rotControl.stateData[3] = 0;
    rotControl.stateData[4] = 0;
    rotControl.stateData[5] = 0;
    alphaControl.stateData[0] = 0;
    alphaControl.stateData[1] = 0;
    alphaControl.stateData[2] = 0;
    alphaControl.stateData[3] = 0;
    alphaControl.stateData[4] = 0;
    alphaControl.stateData[5] = 0;
    colorControl.stateData[0] = 0;
    colorControl.stateData[1] = 0;
    colorControl.stateData[2] = 0;
    colorControl.stateData[3] = 0;
    colorControl.stateData[4] = 0;
    colorControl.stateData[5] = 0;
    textureLoaded = 0;
    pRenderEffect = NULL;
    pTextures[0] = NULL;
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
    char Str[256];
    char v9[256];

    g_pVFileSys->Read((char*)this, 0x20u, vfile);
    g_pVFileSys->Read((char*)this + 32, 4u, vfile);
    g_pVFileSys->Read((char*)this + 36, 4u, vfile);
    g_pVFileSys->Read((char*)this + 40, 4u, vfile);
    g_pVFileSys->Read((char*)this + 44, 4u, vfile);
    g_pVFileSys->Read((char*)this + 48, 4u, vfile);
    g_pVFileSys->Read((char*)this + 52, 4u, vfile);
    g_pVFileSys->Read((char*)this + 56, 0x100u, vfile);
    g_pVFileSys->Read((char*)this + 312, 4u, vfile);
    g_pVFileSys->Read((char*)this + 316, 4u, vfile);
    g_pVFileSys->Read((char*)this + 320, 4u, vfile);
    g_pVFileSys->Read((char*)this + 324, 4u, vfile);
    g_pVFileSys->Read((char*)this + 328, 4u, vfile);
    g_pVFileSys->Read((char*)this + 332, 4u, vfile);
    g_pVFileSys->Read((char*)this + 336, 4u, vfile);
    g_pVFileSys->Read((char*)this + 340, 4u, vfile);
    g_pVFileSys->Read((char*)this + 344, 4u, vfile);
    g_pVFileSys->Read((char*)this + 348, 4u, vfile);
    g_pVFileSys->Read((char*)this + 352, 4u, vfile);
    g_pVFileSys->Read((char*)this + 356, 4u, vfile);
    // param control 0 (base=360)
    g_pVFileSys->Read((char*)this + 360, 4u, vfile);
    g_pVFileSys->Read((char*)this + 364, 4u, vfile);
    g_pVFileSys->Read((char*)this + 368, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 432, 0x80u, vfile);
    g_pVFileSys->Read((char*)this + 572, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 560, 0xCu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read((char*)this + 584, 0x2D0u, vfile);
    g_pVFileSys->Read((char*)this + 1304, 0xE34u, vfile);
    // param control 1 (base=4940)
    g_pVFileSys->Read((char*)this + 4940, 4u, vfile);
    g_pVFileSys->Read((char*)this + 4944, 4u, vfile);
    g_pVFileSys->Read((char*)this + 4948, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 5012, 0x80u, vfile);
    g_pVFileSys->Read((char*)this + 5152, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 5140, 0xCu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read((char*)this + 5164, 0x2D0u, vfile);
    g_pVFileSys->Read((char*)this + 5884, 0xE34u, vfile);
    // param control 2 (base=9520)
    g_pVFileSys->Read((char*)this + 9520, 4u, vfile);
    g_pVFileSys->Read((char*)this + 9524, 4u, vfile);
    g_pVFileSys->Read((char*)this + 9528, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 9592, 0x80u, vfile);
    g_pVFileSys->Read((char*)this + 9732, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 9720, 0xCu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read((char*)this + 9744, 0x2D0u, vfile);
    g_pVFileSys->Read((char*)this + 10464, 0xE34u, vfile);
    // param control 3 (base=14100)
    g_pVFileSys->Read((char*)this + 14100, 4u, vfile);
    g_pVFileSys->Read((char*)this + 14104, 4u, vfile);
    g_pVFileSys->Read((char*)this + 14108, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 14172, 0x80u, vfile);
    g_pVFileSys->Read((char*)this + 14312, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 14300, 0xCu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read((char*)this + 14324, 0x2D0u, vfile);
    g_pVFileSys->Read((char*)this + 15044, 0xE34u, vfile);
    // texture and effect loading
    gbVfgetname((const char*)this + 56, v9, 256);
    if (*((char*)this + 56)) {
        ((gbVFile1*)vfile)->GetDir(Str, 256);
        strcat(Str, "partexture\\");
        strcat(Str, v9);
        gbTexture* tex = g_pGfxManager->NewTexture(Str);
        tex->LoadTexture(1);
        textureLoaded = 1;
        pTextures[0] = tex;
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
    int* dst = (int*)configData;
    const int* src = (const int*)other.configData;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
    dst[8] = src[8];
    dst[9] = src[9];
    dst[10] = src[10];
    dst[11] = src[11];
    dst[12] = src[12];
    dst[13] = src[13];
    dst[14] = src[14];
    dst[15] = src[15];
    basePosition.x = other.basePosition.x;
    basePosition.y = other.basePosition.y;
    basePosition.z = other.basePosition.z;
    velocityDeviation.x = other.velocityDeviation.x;
    velocityDeviation.y = other.velocityDeviation.y;
    velocityDeviation.z = other.velocityDeviation.z;
    int* dst2 = (int*)meshFilename;
    const int* src2 = (const int*)other.meshFilename;
    dst2[0] = src2[0];
    dst2[1] = src2[1];
    dst2[2] = src2[2];
    dst2[3] = src2[3];
    dst2[4] = src2[4];
    dst2[5] = src2[5];
    dst2[6] = src2[6];
    dst2[7] = src2[7];
    dst2[8] = src2[8];
    dst2[9] = src2[9];
    dst2[10] = src2[10];
    dst2[11] = src2[11];
    dst2[12] = src2[12];
    dst2[13] = src2[13];
    dst2[14] = src2[14];
    dst2[15] = src2[15];
    emitType = other.emitType;
    emitDuration = other.emitDuration;
    emitStartTime = other.emitStartTime;
    loopFlag = other.loopFlag;
    field_A8 = other.field_A8;
    boxMin.x = other.boxMin.x;
    boxMin.y = other.boxMin.y;
    boxMin.z = other.boxMin.z;
    boxMax.x = other.boxMax.x;
    boxMax.y = other.boxMax.y;
    boxMax.z = other.boxMax.z;
    sphereRadius = other.sphereRadius;
    sphereRadiusVar = other.sphereRadiusVar;
    pMeshVertices = other.pMeshVertices;
    meshVertBufSize = other.meshVertBufSize;
    numMeshVertices = other.numMeshVertices;
    meshTransform.m[0][0] = other.meshTransform.m[0][0];
    meshTransform.m[0][1] = other.meshTransform.m[0][1];
    meshTransform.m[0][2] = other.meshTransform.m[0][2];
    meshTransform.m[0][3] = other.meshTransform.m[0][3];
    meshTransform.m[1][0] = other.meshTransform.m[1][0];
    meshTransform.m[1][1] = other.meshTransform.m[1][1];
    meshTransform.m[1][2] = other.meshTransform.m[1][2];
    meshTransform.m[1][3] = other.meshTransform.m[1][3];
    meshTransform.m[2][0] = other.meshTransform.m[2][0];
    meshTransform.m[2][1] = other.meshTransform.m[2][1];
    meshTransform.m[2][2] = other.meshTransform.m[2][2];
    meshTransform.m[2][3] = other.meshTransform.m[2][3];
    meshTransform.m[3][0] = other.meshTransform.m[3][0];
    meshTransform.m[3][1] = other.meshTransform.m[3][1];
    meshTransform.m[3][2] = other.meshTransform.m[3][2];
    meshTransform.m[3][3] = other.meshTransform.m[3][3];
    meshDataVersion = other.meshDataVersion;
    int i;
    for (i = 0; i < 6; i++) paramControls[i] = other.paramControls[i];
    return *this;
}

// Global particle file version (determines which fields are present in file format)
int g_particleFileVersion;

static void LoadMeshVertices(char* path) {
}

void gbPartEmitter::LoadFromFile(gbVFile* vfile) {
    char Str[256];

    g_pVFileSys->Read((char*)this, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 64, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 76, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 152, 4u, vfile);
    if (g_particleFileVersion > 0x10000) {
        g_pVFileSys->Read((char*)this + 88, 0x40u, vfile);
        g_pVFileSys->Read((char*)this + 280, 4u, vfile);
    }
    g_pVFileSys->Read((char*)this + 156, 4u, vfile);
    g_pVFileSys->Read((char*)this + 160, 4u, vfile);
    g_pVFileSys->Read((char*)this + 164, 4u, vfile);
    g_pVFileSys->Read((char*)this + 168, 4u, vfile);
    g_pVFileSys->Read((char*)this + 196, 8u, vfile);
    g_pVFileSys->Read((char*)this + 172, 0x18u, vfile);
    // param control 0
    g_pVFileSys->Read((char*)this + 288, 4u, vfile);
    g_pVFileSys->Read((char*)this + 292, 4u, vfile);
    g_pVFileSys->Read((char*)this + 296, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 360, 0x80u, vfile);
    g_pVFileSys->Read((char*)this + 500, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 488, 0xCu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read((char*)this + 512, 0x2D0u, vfile);
    g_pVFileSys->Read((char*)this + 1232, 0xE34u, vfile);
    // param control 1
    g_pVFileSys->Read((char*)this + 4868, 4u, vfile);
    g_pVFileSys->Read((char*)this + 4872, 4u, vfile);
    g_pVFileSys->Read((char*)this + 4876, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 4940, 0x80u, vfile);
    g_pVFileSys->Read((char*)this + 5080, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 5068, 0xCu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read((char*)this + 5092, 0x2D0u, vfile);
    g_pVFileSys->Read((char*)this + 5812, 0xE34u, vfile);
    // param control 2
    g_pVFileSys->Read((char*)this + 9448, 4u, vfile);
    g_pVFileSys->Read((char*)this + 9452, 4u, vfile);
    g_pVFileSys->Read((char*)this + 9456, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 9520, 0x80u, vfile);
    g_pVFileSys->Read((char*)this + 9660, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 9648, 0xCu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read((char*)this + 9672, 0x2D0u, vfile);
    g_pVFileSys->Read((char*)this + 10392, 0xE34u, vfile);
    // param control 3
    g_pVFileSys->Read((char*)this + 14028, 4u, vfile);
    g_pVFileSys->Read((char*)this + 14032, 4u, vfile);
    g_pVFileSys->Read((char*)this + 14036, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 14100, 0x80u, vfile);
    g_pVFileSys->Read((char*)this + 14240, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 14228, 0xCu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read((char*)this + 14252, 0x2D0u, vfile);
    g_pVFileSys->Read((char*)this + 14972, 0xE34u, vfile);
    // param control 4
    g_pVFileSys->Read((char*)this + 18608, 4u, vfile);
    g_pVFileSys->Read((char*)this + 18612, 4u, vfile);
    g_pVFileSys->Read((char*)this + 18616, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 18680, 0x80u, vfile);
    g_pVFileSys->Read((char*)this + 18820, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 18808, 0xCu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read((char*)this + 18832, 0x2D0u, vfile);
    g_pVFileSys->Read((char*)this + 19552, 0xE34u, vfile);
    // param control 5
    g_pVFileSys->Read((char*)this + 23188, 4u, vfile);
    g_pVFileSys->Read((char*)this + 23192, 4u, vfile);
    g_pVFileSys->Read((char*)this + 23196, 0x40u, vfile);
    g_pVFileSys->Read((char*)this + 23260, 0x80u, vfile);
    g_pVFileSys->Read((char*)this + 23400, 0xCu, vfile);
    g_pVFileSys->Read((char*)this + 23388, 0xCu, vfile);
    g_pVFileSys->Seek(vfile, 720, 2);
    g_pVFileSys->Read((char*)this + 23412, 0x2D0u, vfile);
    g_pVFileSys->Read((char*)this + 24132, 0xE34u, vfile);
    // mesh path loading
    if (*((int*)((char*)this + 152)) == 2) {
        ((gbVFile1*)vfile)->GetDir(Str, 255);
        strcat(Str, (const char*)this + 88);
        LoadMeshVertices(Str);
    }
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
    int* dst = (int*)baseData;
    const int* src = (const int*)other.baseData;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
    dst[8] = src[8];
    dst[9] = src[9];
    dst[10] = src[10];
    dst[11] = src[11];
    dst[12] = src[12];
    dst[13] = src[13];
    dst[14] = src[14];
    dst[15] = src[15];
    field_40 = other.field_40;
    field_44 = other.field_44;
    groupName = other.groupName;
    int* dst2 = (int*)padding2;
    const int* src2 = (const int*)other.padding2;
    dst2[0] = src2[0];
    dst2[1] = src2[1];
    dst2[2] = src2[2];
    dst2[3] = src2[3];
    dst2[4] = src2[4];
    dst2[5] = src2[5];
    dst2[6] = src2[6];
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
    double maxAge = -1.0;
    int count = numAliveParticles;
    int oldestIndex;

    if (count > 0) {
        oldestIndex = 0;
        double* pAge = (double*)((char*)particleArray + 8);
        int i = 0;
        do {
            if (maxAge < *pAge) {
                maxAge = *pAge;
                oldestIndex = i;
            }
            ++i;
            pAge += 11;
        } while (i < count);
    }
    return (gbParticleUnit*)((char*)particleArray + 88 * oldestIndex);
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
    texArray.nTex = 1;
    texArray.pTexPt[0] = pGroupParam->pTextures[0];

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
    // VC6 copy ctor with inheritance chain vtable assignments
    // gbChain1DNode base (offsets 0-24)
    ((int*)this)[1] = ((int*)&other)[1];
    ((int*)this)[2] = ((int*)&other)[2];
    ((int*)this)[3] = ((int*)&other)[3];
    ((int*)this)[4] = ((int*)&other)[4];
    ((int*)this)[5] = ((int*)&other)[5];
    ((int*)this)[6] = ((int*)&other)[6];
    // gbNBTreeNode base (offsets 28-87)
    memcpy((char*)this + 28, (char*)&other + 28, 0x3C);
    // gbVisNode base (offsets 88-259)
    memcpy((char*)this + 88, (char*)&other + 88, 0xAC);
    // gbParticleEffect members (offsets 264-347)
    ((int*)this)[66] = ((int*)&other)[66];
    ((int*)this)[67] = ((int*)&other)[67];
    ((int*)this)[68] = ((int*)&other)[68];
    ((int*)this)[69] = ((int*)&other)[69];
    ((int*)this)[70] = ((int*)&other)[70];
    memcpy((char*)this + 284, (char*)&other + 284, 0x40);
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
    int* dst = (int*)(_visnode_data + 4);
    const int* src = (const int*)(other._visnode_data + 4);
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
    dst[8] = src[8];
    dst[9] = src[9];
    dst[10] = src[10];
    dst[11] = src[11];
    dst[12] = src[12];
    dst[13] = src[13];
    dst[14] = src[14];
    dst[15] = src[15];
    dst[16] = src[16];
    dst[17] = src[17];
    dst[18] = src[18];
    dst[19] = src[19];
    int* dst2 = (int*)_effectBaseData;
    const int* src2 = (const int*)other._effectBaseData;
    dst2[0] = src2[0];
    dst2[1] = src2[1];
    dst2[2] = src2[2];
    dst2[3] = src2[3];
    dst2[4] = src2[4];
    dst2[5] = src2[5];
    dst2[6] = src2[6];
    dst2[7] = src2[7];
    dst2[8] = src2[8];
    dst2[9] = src2[9];
    dst2[10] = src2[10];
    dst2[11] = src2[11];
    dst2[12] = src2[12];
    dst2[13] = src2[13];
    dst2[14] = src2[14];
    dst2[15] = src2[15];
    numGroups = other.numGroups;
    numParams = other.numParams;
    numEmitters = other.numEmitters;
    particleGroups = other.particleGroups;
    groupParams = other.groupParams;
    emitters = other.emitters;
    field_B0 = other.field_B0;
    field_B4 = other.field_B4;
    field_B8 = other.field_B8;
    int* dst3 = (int*)_effectData2;
    const int* src3 = (const int*)other._effectData2;
    dst3[0] = src3[0];
    dst3[1] = src3[1];
    dst3[2] = src3[2];
    dst3[3] = src3[3];
    dst3[4] = src3[4];
    dst3[5] = src3[5];
    dst3[6] = src3[6];
    dst3[7] = src3[7];
    dst3[8] = src3[8];
    dst3[9] = src3[9];
    dst3[10] = src3[10];
    dst3[11] = src3[11];
    dst3[12] = src3[12];
    dst3[13] = src3[13];
    dst3[14] = src3[14];
    dst3[15] = src3[15];
    dst3[16] = src3[16];
    dst3[17] = src3[17];
    dst3[18] = src3[18];
    dst3[19] = src3[19];
    dst3[20] = src3[20];
    dst3[21] = src3[21];
    dst3[22] = src3[22];
    spaceScale = other.spaceScale;
    worldTransform.m[0][0] = other.worldTransform.m[0][0];
    worldTransform.m[0][1] = other.worldTransform.m[0][1];
    worldTransform.m[0][2] = other.worldTransform.m[0][2];
    worldTransform.m[0][3] = other.worldTransform.m[0][3];
    worldTransform.m[1][0] = other.worldTransform.m[1][0];
    worldTransform.m[1][1] = other.worldTransform.m[1][1];
    worldTransform.m[1][2] = other.worldTransform.m[1][2];
    worldTransform.m[1][3] = other.worldTransform.m[1][3];
    worldTransform.m[2][0] = other.worldTransform.m[2][0];
    worldTransform.m[2][1] = other.worldTransform.m[2][1];
    worldTransform.m[2][2] = other.worldTransform.m[2][2];
    worldTransform.m[2][3] = other.worldTransform.m[2][3];
    worldTransform.m[3][0] = other.worldTransform.m[3][0];
    worldTransform.m[3][1] = other.worldTransform.m[3][1];
    worldTransform.m[3][2] = other.worldTransform.m[3][2];
    worldTransform.m[3][3] = other.worldTransform.m[3][3];
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
    if (*(double*)((char*)this + 0x110) > 0.0) {
        const gbMatrix4& worldMat = gbVisNode::pGfxMgr->GetWorldMatrix();
        worldTransform = worldMat;
        int i = 0;
        if (i < numGroups) {
            int offset = 0;
            do {
                gbParticleGroup* grp = (gbParticleGroup*)((char*)particleGroups + offset);
                grp->Update(*(double*)((char*)this + 0x110));
                i++;
                offset += 0x90;
            } while (i < numGroups);
        }
        *(int*)((char*)this + 0x110) = 0;
        *(int*)((char*)this + 0x114) = 0;
    }

    int j = 0;
    gbSceneGraph* pScene = gbVisNode::pGfxMgr->pSceneGraph;
    gbMatrixStack* pMat = gbVisNode::pGfxMgr->pMatrixStack[1];
    gbVec3D localPos;
    gbVec3D worldPos;
    localPos.x = 0.0f; localPos.y = 0.0f; localPos.z = 0.0f;
    worldPos.x = 0.0f; worldPos.y = 0.0f; worldPos.z = 0.0f;
    if (j < numGroups) {
        int ofs = 0;
        do {
            gbRenderInfoObj* rObj = pScene->NewOneRenderObj((gbVisNode*)this);
            rObj->Flags = 0;
            rObj->Param = j;
            int iParam = *(int*)((char*)particleGroups + ofs + 0x78);
            int iEff = *(int*)(iParam + 0x493c);
            rObj->pTexArray = (void*)(iParam + 0x48f8);
            rObj->pEffect = (gbRenderEffect*)iEff;
            gbMatrix4* topMat = pMat->GetTop();
            topMat->Transform(&localPos, &worldPos);
            rObj->Priority = 1;
            rObj->Z = (void*)(*(int*)&worldPos.z);
            j++;
            ofs += 0x90;
        } while (j < numGroups);
    }

    this->gbVisNodeBase::Attach(NULL);
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

// Internal animation tree node type (extends gbNBTreeNode with render/anim fields)
// Used by gbAnimNodeGroup::Attach and SetPriority
class gbAnimTreeNode : public gbNBTreeNode {
public:
    void AttachInternal(int frame);
    void SetPriorityInternal(int priority);
};

void gbAnimTreeNode::SetPriorityInternal(int priority) {
    int nodeType = *(int*)((char*)this + 0x15c);
    if (nodeType == 3 || nodeType == 1) {
        gbVisNode* visNode = *(gbVisNode**)((char*)this + 0x168);
        visNode->SetRenderPriority(priority);
    }
    int i = 0;
    if (i < children.m_numNode) {
        do {
            gbAnimTreeNode* child = (gbAnimTreeNode*)children[i];
            child->SetPriorityInternal(priority);
            i++;
        } while (i < children.m_numNode);
    }
}

void gbAnimTreeNode::AttachInternal(int frame) {
    // Stub - complex recursive attach with matrix stack operations
    // Not exported, not compared
}

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
    pNode = p0.pNode;
    lastTime = p0.lastTime;
    elapsedTime = p0.elapsedTime;
    field_18 = p0.field_18;
    field_1c = p0.field_1c;
    field_20 = p0.field_20;
    field_24 = p0.field_24;
    field_28 = p0.field_28;
    isDead = p0.isDead;
    field_30 = p0.field_30;
    posMatrix = p0.posMatrix;
    return *this;
}

void gbAnimNodeGroup::Attach() {
    if (isDead == 0) return;
    if (field_30 == 0) return;
    gbMatrixStack* matStack = s_pGfxMgr->pMatrixStack[1];
    matStack->Push();
    matStack->MultMatrix(&posMatrix);
    ((gbAnimTreeNode*)pNode)->AttachInternal(field_18);
    matStack->Pop();
}

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
    gbAnimTreeNode* node = (gbAnimTreeNode*)pNode;
    if (!node) return;
    int nodeType = *(int*)((char*)node + 0x15c);
    if (nodeType == 3 || nodeType == 1) {
        gbVisNode* visNode = *(gbVisNode**)((char*)node + 0x168);
        visNode->SetRenderPriority(p0);
    }
    int i = 0;
    if (i < node->children.m_numNode) {
        do {
            gbAnimTreeNode* child = (gbAnimTreeNode*)node->children[i];
            child->SetPriorityInternal(p0);
            i++;
        } while (i < node->children.m_numNode);
    }
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
    velocity.x = p0.velocity.x;
    velocity.y = p0.velocity.y;
    velocity.z = p0.velocity.z;
    speedMin = p0.speedMin;
    speedMax = p0.speedMax;
    lifetimeMin = p0.lifetimeMin;
    lifetimeMax = p0.lifetimeMax;
    emitRateMin = p0.emitRateMin;
    emitRateMax = p0.emitRateMax;
    emitAccumulator = p0.emitAccumulator;
    return *this;
}

// ---- gbEmitterSquare ----
gbEmitterSquare::gbEmitterSquare() { memset(this, 0, sizeof(*this)); }

struct gbEmitterSquare & gbEmitterSquare::operator=(struct gbEmitterSquare const & p0) {
    if (this != &p0) memcpy(this, &p0, sizeof(*this)); return *this;
}

// ---- gbParticleUnit ----
gbParticleUnit::gbParticleUnit(struct gbParticleUnit & other) { memcpy(this, &other, sizeof(gbParticleUnit)); }
struct gbParticleUnit & gbParticleUnit::operator=(struct gbParticleUnit const & p0) {
    alive = p0.alive;
    age = p0.age;
    lifetime = p0.lifetime;
    frame = p0.frame;
    randomSeed = p0.randomSeed;
    velocity.x = p0.velocity.x;
    velocity.y = p0.velocity.y;
    velocity.z = p0.velocity.z;
    velocityY = p0.velocityY;
    acceleration.x = p0.acceleration.x;
    acceleration.y = p0.acceleration.y;
    acceleration.z = p0.acceleration.z;
    unused2 = p0.unused2;
    position.x = p0.position.x;
    position.y = p0.position.y;
    position.z = p0.position.z;
    size = p0.size;
    rotation = p0.rotation;
    *(int*)&colorR = *(int*)&p0.colorR;
    unused3 = p0.unused3;
    rotationDir = p0.rotationDir;
    return *this;
}

