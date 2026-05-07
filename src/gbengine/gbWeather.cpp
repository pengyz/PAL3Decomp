/**
 * gbengine.dll - gbWeather
 * Weather effects implementation (rain, snow)
 * Functions: 13
 */

#include "gbengine/gbParticle.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbRenderEffect.h"
#include <string.h>
#include <stdlib.h>

// External globals
extern double g_CurrentTime;
extern gbGfxManager* dword_101379A8;

// External random float function
extern "C" float sub_10027620(float minVal, float maxVal);

/* ======== gbDropUnit ======== */

gbDropUnit::gbDropUnit(void) {
    int* p = (int*)this + 1;
    p[0] = 0; p[1] = 0; p[2] = 0;
    p[3] = 0; p[4] = 0; p[5] = 0;
    p[6] = 0; p[7] = 0; p[8] = 0;
}

gbDropUnit& gbDropUnit::operator=(const gbDropUnit& other) {
    *(((int*)this) + 0) = *(((int*)&other) + 0);
    *(((int*)this) + 1) = *(((int*)&other) + 1);
    *(((int*)this) + 2) = *(((int*)&other) + 2);
    *(((int*)this) + 3) = *(((int*)&other) + 3);
    *(((int*)this) + 4) = *(((int*)&other) + 4);
    *(((int*)this) + 5) = *(((int*)&other) + 5);
    *(((int*)this) + 6) = *(((int*)&other) + 6);
    *(((int*)this) + 7) = *(((int*)&other) + 7);
    *(((int*)this) + 8) = *(((int*)&other) + 8);
    *(((int*)this) + 9) = *(((int*)&other) + 9);
    return *this;
}

/* ======== gbDropDesc ======== */

gbDropDesc& gbDropDesc::operator=(const gbDropDesc& other) {
    memcpy(this, &other, 0x24);
    return *this;
}

/* ======== gbDropGroup ======== */

gbDropGroup::gbDropGroup(int maxCount, const gbDropDesc* dropDesc, const char* texName) {
    maxUnits = maxCount;

    gbDropUnit* p = (gbDropUnit*)operator new(40 * maxCount);
    if (p) {
        if (maxCount - 1 >= 0) {
            int* v7 = (int*)((char*)p + 12);
            int v8 = maxCount;
            do {
                *(v7 - 2) = 0;
                *(v7 - 1) = 0;
                *v7 = 0;
                v7[1] = 0;
                v7[2] = 0;
                v7[3] = 0;
                v7[4] = 0;
                v7[5] = 0;
                v7[6] = 0;
                v7 += 10;
                --v8;
            } while (v8);
        }
    } else {
        p = NULL;
    }
    units = p;

    if (maxCount > 0) {
        int v9 = 0;
        int v4 = maxCount;
        do {
            v9 += 40;
            --v4;
            *(int*)((char*)units + v9 - 40) = 0;
        } while (v4);
    }

    gbGfxManager* v10 = dword_101379A8;
    if (texName) {
        gbTexture* v11 = (gbTexture*)(*(int (**)())(*(int*)dword_101379A8 + 8))();
        pTexture = v11;
    } else {
        pTexture = NULL;
    }

    pRenderEffect = ((gbEffectMgr**)v10)[50]->NewRenderEffect("gfxscript\\p_add_g.fx", 0);

    *(((int*)this) + 4) = *(((int*)dropDesc) + 0);
    *(((int*)this) + 5) = *(((int*)dropDesc) + 1);
    *(((int*)this) + 6) = *(((int*)dropDesc) + 2);
    *(((int*)this) + 7) = *(((int*)dropDesc) + 3);
    *(((int*)this) + 8) = *(((int*)dropDesc) + 4);
    *(((int*)this) + 9) = *(((int*)dropDesc) + 5);
    *(((int*)this) + 10) = *(((int*)dropDesc) + 6);
    *(((int*)this) + 11) = *(((int*)dropDesc) + 7);
    int v12 = *(((int*)dropDesc) + 8);
    elapsedTime = 0.0;
    *(((int*)this) + 12) = v12;
    numActiveUnits = 0;
    spawnTimer = 0.0f;
    *(((int*)this) + 16) = 0;
}


gbDropGroup::~gbDropGroup(void) {
    gbRefObject* v2 = (gbRefObject*)pRenderEffect;
    v2->Release();
    gbRefObject* v3 = (gbRefObject*)pTexture;
    if (v3)
        v3->Release();
    operator delete(units);
}

void gbDropGroup::Render(gbCamera* camera) {
    double v5 = g_CurrentTime;
    float v4 = (float)(g_CurrentTime - elapsedTime);
    if (v4 > 0.2f)
        v4 = 0.2f;
    CreateUnit(v4, camera);
    // vtable[1] = Update
    (*(void (**)(gbDropGroup*, float))(*(int*)this + 4))(this, v4);
    if (numActiveUnits)
        // vtable[2] = Draw
        (*(void (**)(gbDropGroup*))(*(int*)this + 8))(this);
    elapsedTime = v5;
}

void gbDropGroup::CreateUnit(float deltaTime, gbCamera* camera) {
    float v4 = deltaTime + spawnTimer;
    spawnTimer = v4;
    double v5 = (double)(*(int*)((char*)this + 0x18));
    int v16 = (int)(v5 * v4);
    if (v16 > 0) {
        int v6 = maxUnits;
        int v7 = 0;
        spawnTimer = v4 - (float)((double)v16 / v5);
        if (v6 > 0) {
            int v8 = 0;
            do {
                float* v9 = (float*)((char*)units + v8);
                if (*v9 <= 0.0f) {
                    float half = *((float*)this + 5) * 0.5f;
                    float negHalf = *((float*)this + 5) * -0.5f;
                    v9[4] = sub_10027620(negHalf, half);
                    float negFull = -*((float*)this + 5);
                    v9[6] = sub_10027620(negFull, *((float*)this + 5) * -0.5f);
                    v9[5] = sub_10027620(*((float*)this + 11), *((float*)this + 12));
                    *v9 = sub_10027620(*((float*)this + 7), *((float*)this + 8));
                    v9[3] = 0;
                    v9[1] = 0;
                    v9[2] = -sub_10027620(*((float*)this + 9), *((float*)this + 10));
                    ++numActiveUnits;
                    if (!--v16)
                        break;
                }
                ++v7;
                v8 += 40;
            } while (v7 < maxUnits);
        }
    }
}

gbDropGroup& gbDropGroup::operator=(const gbDropGroup& other) {
    *(((int*)this) + 2) = *(((int*)&other) + 2);
    *(((int*)this) + 3) = *(((int*)&other) + 3);
    *(((int*)this) + 4) = *(((int*)&other) + 4);
    *(((int*)this) + 5) = *(((int*)&other) + 5);
    *(((int*)this) + 6) = *(((int*)&other) + 6);
    *(((int*)this) + 7) = *(((int*)&other) + 7);
    *(((int*)this) + 8) = *(((int*)&other) + 8);
    *(((int*)this) + 9) = *(((int*)&other) + 9);
    *(((int*)this) + 10) = *(((int*)&other) + 10);
    *(((int*)this) + 11) = *(((int*)&other) + 11);
    *(((int*)this) + 12) = *(((int*)&other) + 12);
    *(((int*)this) + 14) = *(((int*)&other) + 14);
    *(((int*)this) + 15) = *(((int*)&other) + 15);
    *(((int*)this) + 16) = *(((int*)&other) + 16);
    *(((int*)this) + 17) = *(((int*)&other) + 17);
    *(((int*)this) + 18) = *(((int*)&other) + 18);
    *(((int*)this) + 19) = *(((int*)&other) + 19);
    return *this;
}

/* ======== gbRain ======== */

gbRain::gbRain(int maxDrops, const gbDropDesc* dropDesc, const char* texName)
    : gbDropGroup(maxDrops, dropDesc, texName) {
}

gbRain::gbRain(const gbRain& other)
    : gbDropGroup(other) {
}

gbRain::~gbRain(void) {
}

void gbRain::Update(float a2) {
    int v2;
    int v3;
    int v4;
    float v5;
    float v6;
    float v7;

    v2 = 0;
    if (*(int*)((char*)this + 8) > 0) {
        v3 = 0;
        do {
            v4 = v3 + *(int*)((char*)this + 0x44);
            if (*(float*)v4 > 0.0f) {
                *(int*)(v4 + 28) = *(int*)(v4 + 16);
                *(int*)(v4 + 32) = *(int*)(v4 + 20);
                *(int*)(v4 + 36) = *(int*)(v4 + 24);
                v6 = a2 * *(float*)(v4 + 8);
                v7 = a2 * *(float*)(v4 + 12);
                *(float*)(v4 + 16) = a2 * *(float*)(v4 + 4) + *(float*)(v4 + 16);
                *(float*)(v4 + 20) = v6 + *(float*)(v4 + 20);
                *(float*)(v4 + 24) = v7 + *(float*)(v4 + 24);
                v5 = *(float*)v4 - a2;
                *(float*)v4 = v5;
                if (v5 <= 0.0f)
                    --*(int*)((char*)this + 0x0C);
            }
            ++v2;
            v3 += 40;
        } while (v2 < *(int*)((char*)this + 8));
    }
}

void gbRain::Draw(void) {
    // TODO: complex rendering with gbDynVertBuf and gbMatrixStack
}

gbRain& gbRain::operator=(const gbRain& other) {
    *(((int*)this) + 2) = *(((int*)&other) + 2);
    *(((int*)this) + 3) = *(((int*)&other) + 3);
    *(((int*)this) + 4) = *(((int*)&other) + 4);
    *(((int*)this) + 5) = *(((int*)&other) + 5);
    *(((int*)this) + 6) = *(((int*)&other) + 6);
    *(((int*)this) + 7) = *(((int*)&other) + 7);
    *(((int*)this) + 8) = *(((int*)&other) + 8);
    *(((int*)this) + 9) = *(((int*)&other) + 9);
    *(((int*)this) + 10) = *(((int*)&other) + 10);
    *(((int*)this) + 11) = *(((int*)&other) + 11);
    *(((int*)this) + 12) = *(((int*)&other) + 12);
    *(((int*)this) + 14) = *(((int*)&other) + 14);
    *(((int*)this) + 15) = *(((int*)&other) + 15);
    *(((int*)this) + 16) = *(((int*)&other) + 16);
    *(((int*)this) + 17) = *(((int*)&other) + 17);
    *(((int*)this) + 18) = *(((int*)&other) + 18);
    *(((int*)this) + 19) = *(((int*)&other) + 19);
    return *this;
}

/* ======== gbSnow ======== */

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

void gbSnow::Update(float a2) {
    int v3;
    int v4;
    float* v5;
    float v6;
    float v11;
    float v12;

    v3 = 0;
    if (*(int*)((char*)this + 8) > 0) {
        v4 = 0;
        do {
            v5 = (float*)(*(int*)((char*)this + 0x44) + v4);
            if (*v5 > 0.0f) {
                v11 = a2 * v5[2];
                v12 = a2 * v5[3];
                v5[4] = a2 * v5[1] + v5[4];
                v5[5] = v11 + v5[5];
                v5[6] = v12 + v5[6];
                v6 = *v5 - a2;
                *v5 = v6;
                if (((int)(v6 * 15.0f) & 1) == 0) {
                    v5[1] = sub_10027620(-*((float*)this + 20), *((float*)this + 20));
                    v5[3] = sub_10027620(-*((float*)this + 20), *((float*)this + 20));
                }
                if (*v5 <= 0.0f)
                    --*(int*)((char*)this + 0x0C);
            }
            ++v3;
            v4 += 40;
        } while (v3 < *(int*)((char*)this + 8));
    }
}

void gbSnow::Draw(void) {
    // TODO: complex rendering with gbDynVertBuf and gbMatrixStack
}

gbSnow& gbSnow::operator=(const gbSnow& other) {
    *(((int*)this) + 2) = *(((int*)&other) + 2);
    *(((int*)this) + 3) = *(((int*)&other) + 3);
    *(((int*)this) + 4) = *(((int*)&other) + 4);
    *(((int*)this) + 5) = *(((int*)&other) + 5);
    *(((int*)this) + 6) = *(((int*)&other) + 6);
    *(((int*)this) + 7) = *(((int*)&other) + 7);
    *(((int*)this) + 8) = *(((int*)&other) + 8);
    *(((int*)this) + 9) = *(((int*)&other) + 9);
    *(((int*)this) + 10) = *(((int*)&other) + 10);
    *(((int*)this) + 11) = *(((int*)&other) + 11);
    *(((int*)this) + 12) = *(((int*)&other) + 12);
    *(((int*)this) + 14) = *(((int*)&other) + 14);
    *(((int*)this) + 15) = *(((int*)&other) + 15);
    *(((int*)this) + 16) = *(((int*)&other) + 16);
    *(((int*)this) + 17) = *(((int*)&other) + 17);
    *(((int*)this) + 18) = *(((int*)&other) + 18);
    *(((int*)this) + 19) = *(((int*)&other) + 19);
    *(((int*)this) + 20) = *(((int*)&other) + 20);
    return *this;
}
