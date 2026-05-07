/**
 * gbengine.dll - gbWeather
 * Weather effects implementation (rain, snow)
 * Functions: 13
 *
 * Compiler: MSVC 6.0 SP5
 */

#include "gbengine/gbParticle.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbengine_internal.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

// External globals
extern double g_CurrentTime;
extern gbGfxManager* g_pGfxManager;

// Random float in range [minVal, maxVal] - 0x10027620
float gbRandFloat(float minVal, float maxVal);

/* ======== gbDropUnit ======== */

// 0x10032870 - gbDropUnit default constructor
gbDropUnit::gbDropUnit(void) {
    // Zero all fields except first (lifetime is NOT zeroed by constructor from Ghidra)
    // Ghidra: starts at "puVar5[-2]" which is offset +0x04
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    velocity.z = 0.0f;
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;
    prevPosition.x = 0.0f;
    prevPosition.y = 0.0f;
    prevPosition.z = 0.0f;
}

// 0x100328E0 - gbDropUnit operator=
gbDropUnit& gbDropUnit::operator=(const gbDropUnit& other) {
    lifetime = other.lifetime;
    velocity.x = other.velocity.x;
    velocity.y = other.velocity.y;
    velocity.z = other.velocity.z;
    position.x = other.position.x;
    position.y = other.position.y;
    position.z = other.position.z;
    prevPosition.x = other.prevPosition.x;
    prevPosition.y = other.prevPosition.y;
    prevPosition.z = other.prevPosition.z;
    return *this;
}

/* ======== gbDropDesc ======== */

gbDropDesc& gbDropDesc::operator=(const gbDropDesc& other) {
    memcpy(this, &other, sizeof(gbDropDesc));
    return *this;
}

/* ======== gbDropGroup ======== */

// 0x10031E40 - gbDropGroup constructor
gbDropGroup::gbDropGroup(int maxCount, const gbDropDesc* dropDesc, const char* texName) {
    maxUnits = maxCount;

    // Allocate unit array (sizeof(gbDropUnit) = 40 = 0x28)
    gbDropUnit* p = (gbDropUnit*)operator new(sizeof(gbDropUnit) * maxCount);
    if (p == NULL) {
        p = NULL;
    } else if (maxCount - 1 >= 0) {
        // Initialize all units (zero velocity/position/prevPosition fields)
        int* v = (int*)((char*)p + 12);
        int cnt = maxCount;
        do {
            v[-2] = 0;
            v[-1] = 0;
            *v = 0;
            v[1] = 0;
            v[2] = 0;
            v[3] = 0;
            v[4] = 0;
            v[5] = 0;
            v[6] = 0;
            v += 10;
            --cnt;
        } while (cnt != 0);
    }
    units = p;

    // Zero lifetime for all units
    if (maxCount > 0) {
        int offset = 0;
        int cnt = maxCount;
        do {
            *(int*)((char*)units + offset) = 0;
            offset += sizeof(gbDropUnit);
            --cnt;
        } while (cnt != 0);
    }

    // Create texture if name provided
    if (texName != NULL) {
        gbTexture* tex = g_pGfxManager->NewTexture(texName);
        pTexture = tex;
        tex->LoadTexture(1);
    } else {
        pTexture = NULL;
    }

    // Create render effect
    pRenderEffect = g_pGfxManager->pEffectMgr->NewRenderEffect("gfxscript\\p_add_g.gbf", 0);

    // Copy drop description
    desc = *dropDesc;

    // Initialize timing/count
    elapsedTime = 0.0;
    numActiveUnits = 0;
    spawnTimer = 0.0f;
    field_04 = 0;
}

// 0x10032120 - gbDropGroup destructor (shared by gbRain, gbSnow)
gbDropGroup::~gbDropGroup(void) {
    ((gbRefObject*)pRenderEffect)->Release();
    if (pTexture != NULL) {
        ((gbRefObject*)pTexture)->Release();
    }
    operator delete(units);
}

// 0x10031F40 - gbDropGroup::Render
void gbDropGroup::Render(gbCamera* camera) {
    double curTime = g_CurrentTime;
    float dt = (float)(g_CurrentTime - elapsedTime);
    if (dt > 0.2f)
        dt = 0.2f;
    CreateUnit(dt, camera);
    Update(dt);
    if (numActiveUnits != 0) {
        Draw();
    }
    elapsedTime = curTime;
}

// 0x10031FE0 - gbDropGroup::CreateUnit
void gbDropGroup::CreateUnit(float deltaTime, gbCamera* camera) {
    spawnTimer = deltaTime + spawnTimer;
    double rate = (double)desc.density;
    int numToSpawn = (int)(rate * (double)spawnTimer);
    if (numToSpawn > 0) {
        spawnTimer = spawnTimer - (float)((double)numToSpawn / rate);
        int idx = 0;
        if (maxUnits > 0) {
            int offset = 0;
            do {
                float* pUnit = (float*)((char*)units + offset);
                if (*pUnit <= 0.0f) {
                    float halfDist = desc.viewDistance * 0.5f;
                    // position.x = random in [-halfDist, halfDist]
                    pUnit[4] = gbRandFloat(-halfDist, halfDist);
                    // position.z = random in [-viewDistance, -halfDist]
                    pUnit[6] = gbRandFloat(-desc.viewDistance, -halfDist);
                    // position.y = random in [speedMinZ, speedMaxZ]
                    pUnit[5] = gbRandFloat(desc.speedMinZ, desc.speedMaxZ);
                    // lifetime = random in [speedMinX, speedMaxX]
                    *pUnit = gbRandFloat(desc.speedMinX, desc.speedMaxX);
                    // velocity.z = 0
                    pUnit[3] = 0.0f;
                    // velocity.x = 0
                    pUnit[1] = 0.0f;
                    // velocity.y = -random in [speedMinY, speedMaxY]
                    pUnit[2] = -gbRandFloat(desc.speedMinY, desc.speedMaxY);
                    ++numActiveUnits;
                    if (--numToSpawn == 0)
                        break;
                }
                ++idx;
                offset += sizeof(gbDropUnit);
            } while (idx < maxUnits);
        }
    }
}

// operator=
gbDropGroup& gbDropGroup::operator=(const gbDropGroup& other) {
    maxUnits = other.maxUnits;
    numActiveUnits = other.numActiveUnits;
    desc = other.desc;
    elapsedTime = other.elapsedTime;
    spawnTimer = other.spawnTimer;
    units = other.units;
    pTexture = other.pTexture;
    pRenderEffect = other.pRenderEffect;
    field_04 = other.field_04;
    return *this;
}

/* ======== gbRain ======== */

// 0x100320F0 - gbRain constructor
gbRain::gbRain(int maxDrops, const gbDropDesc* dropDesc, const char* texName)
    : gbDropGroup(maxDrops, dropDesc, texName) {
}

gbRain::gbRain(const gbRain& other)
    : gbDropGroup(other) {
}

gbRain::~gbRain(void) {
}

// 0x10032150 - gbRain::Update
void gbRain::Update(float deltaTime) {
    int i = 0;
    if (maxUnits > 0) {
        int offset = 0;
        do {
            float* pUnit = (float*)((char*)units + offset);
            if (*pUnit > 0.0f) {
                // Save previous position
                pUnit[7] = pUnit[4];
                pUnit[8] = pUnit[5];
                pUnit[9] = pUnit[6];
                // Update position by velocity * dt
                pUnit[4] = deltaTime * pUnit[1] + pUnit[4];
                pUnit[5] = deltaTime * pUnit[2] + pUnit[5];
                pUnit[6] = deltaTime * pUnit[3] + pUnit[6];
                // Decrease lifetime
                float life = *pUnit;
                *pUnit = life - deltaTime;
                if (life - deltaTime <= 0.0f) {
                    --numActiveUnits;
                }
            }
            ++i;
            offset += sizeof(gbDropUnit);
        } while (i < maxUnits);
    }
}

// 0x100321F0 (690B) - gbRain::Draw
// Renders rain streaks as two-triangle quads (current pos to previous pos)
void gbRain::Draw(void) {
    gbDynVertBuf* pVB = g_pGfxManager->pVertPoolMgr->GetDynVertBuf(0x15);
    gbTexture* tex = pTexture;
    int useWhite = 1;

    if (tex == NULL) {
        tex = g_pGfxManager->pEffectMgr->GetWhiteTexture();
    }

    gbMatrixStack* pMatStack = g_pGfxManager->pMatrixStack[1];
    pMatStack->GetTop();

    // Vertex format: position(3f) + color(DWORD) + padding + texcoord(1f)
    // 6 DWORDs per vertex = 24 bytes

    // Define vertex templates for 6 vertices (two triangles forming a quad streak)
    // Colors: semi-transparent white (0x80FFFFFF for endpoints, 0x96FFFFFF for midpoints)
    struct RainVert {
        float x, y, z;
        unsigned int color;
        unsigned int pad;
        float u;
    };

    float halfWidth = 2.3509886e-38f; // very small offset for line width

    // Lock vertex buffer for numActiveUnits * 6 vertices
    float* pVerts = (float*)pVB->Lock(numActiveUnits * 6);
    if (pVerts != NULL) {
        int i = 0;
        int offset = 0;
        if (maxUnits > 0) {
            do {
                float* pUnit = (float*)((char*)units + offset);
                if (*pUnit > 0.0f) {
                    float px = pUnit[4];
                    float py = pUnit[5];
                    float pz = pUnit[6];
                    float prevX = pUnit[7];
                    float prevY = pUnit[8];
                    float prevZ = pUnit[9];

                    // Build 6 vertices for this rain drop (2 triangles)
                    // v0: prevPos - halfWidth
                    RainVert v0;
                    v0.x = prevX - halfWidth; v0.y = prevY; v0.z = prevZ;
                    v0.color = 0x80FFFFFF; v0.pad = 0; v0.u = 1.0f;

                    // v1: curPos - halfWidth
                    RainVert v1;
                    v1.x = px - halfWidth; v1.y = py; v1.z = pz;
                    v1.color = 0x96FFFFFF; v1.pad = 0; v1.u = 0.0f;

                    // v2: curPos + halfWidth
                    RainVert v2;
                    v2.x = px + halfWidth; v2.y = py; v2.z = pz;
                    v2.color = 0x96FFFFFF; v2.pad = 0x3F800000; v2.u = 0.0f;

                    // v3: prevPos + halfWidth
                    RainVert v3;
                    v3.x = prevX + halfWidth; v3.y = prevY; v3.z = prevZ;
                    v3.color = 0x80FFFFFF; v3.pad = 0x3F800000; v3.u = 0x3F800000;

                    // Copy 6 vertices: v0, v1, v2, v0, v2, v3
                    memcpy(pVerts, &v0, 24); pVerts += 6;
                    memcpy(pVerts, &v1, 24); pVerts += 6;
                    memcpy(pVerts, &v2, 24); pVerts += 6;
                    memcpy(pVerts, &v0, 24); pVerts += 6;
                    memcpy(pVerts, &v2, 24); pVerts += 6;
                    memcpy(pVerts, &v3, 24); pVerts += 6;
                }
                ++i;
                offset += sizeof(gbDropUnit);
            } while (i < maxUnits);
        }
        pMatStack->Push();
        pMatStack->LoadIdentity();
        pVB->Draw(1, pRenderEffect, (gbTextureArray*)tex);
        pMatStack->Pop();
    }
}

// operator=
gbRain& gbRain::operator=(const gbRain& other) {
    maxUnits = other.maxUnits;
    numActiveUnits = other.numActiveUnits;
    desc.gravity = other.desc.gravity;
    desc.viewDistance = other.desc.viewDistance;
    desc.density = other.desc.density;
    desc.speedMinX = other.desc.speedMinX;
    desc.speedMaxX = other.desc.speedMaxX;
    desc.speedMinY = other.desc.speedMinY;
    desc.speedMaxY = other.desc.speedMaxY;
    desc.speedMinZ = other.desc.speedMinZ;
    desc.speedMaxZ = other.desc.speedMaxZ;
    elapsedTime = other.elapsedTime;
    spawnTimer = other.spawnTimer;
    units = other.units;
    pTexture = other.pTexture;
    pRenderEffect = other.pRenderEffect;
    return *this;
}

/* ======== gbSnow ======== */

// 0x100324A0 - gbSnow constructor
gbSnow::gbSnow(int maxDrops, const gbDropDesc* dropDesc, const char* texName, float amplitude)
    : gbDropGroup(maxDrops, dropDesc, texName) {
    swayAmplitude = amplitude;
}

gbSnow::gbSnow(const gbSnow& other)
    : gbDropGroup(other) {
    swayAmplitude = other.swayAmplitude;
}

gbSnow::~gbSnow(void) {
}

// 0x100324D0 - gbSnow::Update
void gbSnow::Update(float deltaTime) {
    int i = 0;
    if (maxUnits > 0) {
        int offset = 0;
        do {
            float* pUnit = (float*)(offset + (int)units);
            if (*pUnit > 0.0f) {
                // Update position
                pUnit[4] = deltaTime * pUnit[1] + pUnit[4];
                pUnit[5] = deltaTime * pUnit[2] + pUnit[5];
                pUnit[6] = deltaTime * pUnit[3] + pUnit[6];
                // Decrease lifetime
                *pUnit = *pUnit - deltaTime;
                // Periodically randomize horizontal drift
                unsigned int phase = (unsigned int)(*pUnit * 15.0f);
                if ((phase & 1) == 0) {
                    pUnit[1] = gbRandFloat(-swayAmplitude, swayAmplitude);
                    pUnit[3] = gbRandFloat(-swayAmplitude, swayAmplitude);
                }
                if (*pUnit <= 0.0f) {
                    --numActiveUnits;
                }
            }
            ++i;
            offset += sizeof(gbDropUnit);
        } while (i < maxUnits);
    }
}

// 0x100325B0 (690B) - gbSnow::Draw
// Renders snowflakes as flat billboard quads
void gbSnow::Draw(void) {
    gbDynVertBuf* pVB = g_pGfxManager->pVertPoolMgr->GetDynVertBuf(0x15);
    gbTexture* tex = pTexture;
    int useWhite = 1;

    if (tex == NULL) {
        tex = g_pGfxManager->pEffectMgr->GetWhiteTexture();
    }

    gbMatrixStack* pMatStack = g_pGfxManager->pMatrixStack[1];
    pMatStack->GetTop();

    float halfSize = desc.gravity * 0.5f;

    // Lock vertex buffer
    float* pVerts = (float*)pVB->Lock(numActiveUnits * 6);
    if (pVerts != NULL) {
        int i = 0;
        int offset = 0;
        if (maxUnits > 0) {
            do {
                float* pUnit = (float*)((char*)units + offset);
                if (*pUnit > 0.0f) {
                    float px = pUnit[4];
                    float py = pUnit[5];
                    float pz = pUnit[6];

                    // Build 6 vertices for quad (2 triangles)
                    // Expand in XY plane around particle position
                    struct SnowVert {
                        float x, y, z;
                        unsigned int color;
                        unsigned int pad;
                        float u;
                    };

                    SnowVert v0, v1, v2, v3;
                    v0.x = px - halfSize; v0.y = py + halfSize; v0.z = pz;
                    v0.color = 0xFFFFFFFF; v0.pad = 0; v0.u = 1.0f;

                    v1.x = px - halfSize; v1.y = py - halfSize; v1.z = pz;
                    v1.color = 0xFFFFFFFF; v1.pad = 0; v1.u = 0.0f;

                    v2.x = px + halfSize; v2.y = py - halfSize; v2.z = pz;
                    v2.color = 0xFFFFFFFF; v2.pad = 0x3F800000; v2.u = 0.0f;

                    v3.x = px + halfSize; v3.y = py + halfSize; v3.z = pz;
                    v3.color = 0xFFFFFFFF; v3.pad = 0x3F800000; v3.u = 0x3F800000;

                    // Copy 6 vertices: v0, v1, v2, v0, v2, v3
                    memcpy(pVerts, &v0, 24); pVerts += 6;
                    memcpy(pVerts, &v1, 24); pVerts += 6;
                    memcpy(pVerts, &v2, 24); pVerts += 6;
                    memcpy(pVerts, &v0, 24); pVerts += 6;
                    memcpy(pVerts, &v2, 24); pVerts += 6;
                    memcpy(pVerts, &v3, 24); pVerts += 6;
                }
                ++i;
                offset += sizeof(gbDropUnit);
            } while (i < maxUnits);
        }
        pMatStack->Push();
        pMatStack->LoadIdentity();
        pVB->Draw(1, pRenderEffect, (gbTextureArray*)tex);
        pMatStack->Pop();
    }
}

// operator=
gbSnow& gbSnow::operator=(const gbSnow& other) {
    maxUnits = other.maxUnits;
    numActiveUnits = other.numActiveUnits;
    desc.gravity = other.desc.gravity;
    desc.viewDistance = other.desc.viewDistance;
    desc.density = other.desc.density;
    desc.speedMinX = other.desc.speedMinX;
    desc.speedMaxX = other.desc.speedMaxX;
    desc.speedMinY = other.desc.speedMinY;
    desc.speedMaxY = other.desc.speedMaxY;
    desc.speedMinZ = other.desc.speedMinZ;
    desc.speedMaxZ = other.desc.speedMaxZ;
    elapsedTime = other.elapsedTime;
    spawnTimer = other.spawnTimer;
    units = other.units;
    pTexture = other.pTexture;
    pRenderEffect = other.pRenderEffect;
    swayAmplitude = other.swayAmplitude;
    return *this;
}
