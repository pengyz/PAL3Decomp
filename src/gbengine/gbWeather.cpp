/**
 * gbengine.dll - gbWeather
 * Weather effects implementation (rain, snow)
 * Functions: 13
 */

#include "gbengine/gbParticle.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

// External globals
extern double g_CurrentTime;
extern unsigned int g_CurrentTick;

/* ======== gbDropUnit ======== */

gbDropUnit::gbDropUnit(void) {
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    velocity.z = 0.0f;
    size = 1.0f;
    alpha = 1.0f;
    age = 0.0f;
    alive = 0;
}

/* ======== gbDropGroup ======== */

gbDropGroup::gbDropGroup(int maxCount, const gbDropDesc* dropDesc, const char* texName) {
    units = NULL;
    maxUnits = maxCount;
    numActiveUnits = 0;

    if (dropDesc) {
        memcpy(&desc, dropDesc, sizeof(gbDropDesc));
    } else {
        memset(&desc, 0, sizeof(gbDropDesc));
    }

    if (texName) {
        strncpy(textureName, texName, 63);
        textureName[63] = '\0';
    } else {
        textureName[0] = '\0';
    }

    pTexture = NULL;
    elapsedTime = 0.0f;
    spawnTimer = 0.0f;

    if (maxCount > 0) {
        units = (gbDropUnit*)malloc(sizeof(gbDropUnit) * maxCount);
        if (units) {
            memset(units, 0, sizeof(gbDropUnit) * maxCount);
        }
    }
}

gbDropGroup::gbDropGroup(const gbDropGroup& other) {
    maxUnits = other.maxUnits;
    numActiveUnits = 0;
    units = new gbDropUnit[maxUnits];
    memcpy(&desc, &other.desc, sizeof(gbDropDesc));
    strcpy(textureName, other.textureName);
    pTexture = other.pTexture;
    elapsedTime = 0.0f;
    spawnTimer = 0.0f;
}

gbDropGroup::~gbDropGroup(void) {
    if (units) {
        delete[] units;
        units = NULL;
    }
}

void gbDropGroup::Render(gbCamera* camera) {
    if (!pTexture) return;

    for (int i = 0; i < numActiveUnits; i++) {
        if (units[i].alive) {
            // Render billboard at units[i].position
        }
    }
}

void gbDropGroup::CreateUnit(float heightOffset, gbCamera* camera) {
    if (numActiveUnits >= maxUnits) return;

    gbDropUnit* unit = &units[numActiveUnits];
    numActiveUnits++;

    float range = desc.viewDistance;
    unit->position.x = ((float)rand() / RAND_MAX) * range * 2.0f - range;
    unit->position.y = heightOffset;
    unit->position.z = ((float)rand() / RAND_MAX) * range * 2.0f - range;

    unit->velocity.x = desc.windX;
    unit->velocity.y = -desc.speed;
    unit->velocity.z = desc.windZ;

    unit->size = desc.size;
    unit->alpha = desc.alpha;
    unit->age = 0.0f;
    unit->alive = 1;
}

/* ======== gbRain ======== */

gbRain::gbRain(int maxDrops, const gbDropDesc* dropDesc, const char* texName)
    : gbDropGroup(maxDrops, dropDesc, texName) {
    (void)maxDrops; (void)dropDesc; (void)texName;
}

gbRain::gbRain(const gbRain& other)
    : gbDropGroup(other) {
    memcpy((char*)this + 8, (const char*)&other + 8, sizeof(gbRain) - 8);
}

gbRain::~gbRain(void) {
}

void gbRain::Update(float deltaTime) {
    elapsedTime += deltaTime;
    spawnTimer += deltaTime;

    float spawnInterval = 1.0f / (desc.density * 10.0f);
    while (spawnTimer >= spawnInterval && numActiveUnits < maxUnits) {
        CreateUnit(50.0f, NULL);
        spawnTimer -= spawnInterval;
    }

    for (int i = 0; i < numActiveUnits; ) {
        if (units[i].alive) {
            units[i].position.x += units[i].velocity.x * deltaTime;
            units[i].position.y += units[i].velocity.y * deltaTime;
            units[i].position.z += units[i].velocity.z * deltaTime;

            units[i].velocity.y -= desc.gravity * deltaTime;
            units[i].age += deltaTime;

            if (units[i].position.y < -10.0f || units[i].age > 10.0f) {
                units[i].alive = 0;
                if (i < numActiveUnits - 1) {
                    units[i] = units[numActiveUnits - 1];
                }
                numActiveUnits--;
                continue;
            }
        }
        i++;
    }
}

void gbRain::Draw(void) {
    if (!pTexture) return;

    for (int i = 0; i < numActiveUnits; i++) {
        if (units[i].alive) {
            // Render rain streak
        }
    }
}

/* ======== gbSnow ======== */

gbSnow::gbSnow(int maxDrops, const gbDropDesc* dropDesc, const char* texName, float amplitude)
    : gbDropGroup(maxDrops, dropDesc, texName) {
    swayAmplitude = amplitude;
    swayFrequency = 1.0f;
}

gbSnow::gbSnow(const gbSnow& other)
    : gbDropGroup(other) {
    swayAmplitude = other.swayAmplitude;
    swayFrequency = other.swayFrequency;
}

gbSnow::~gbSnow(void) {
}

void gbSnow::Update(float deltaTime) {
    elapsedTime += deltaTime;
    spawnTimer += deltaTime;

    float spawnInterval = 1.0f / (desc.density * 5.0f);
    while (spawnTimer >= spawnInterval && numActiveUnits < maxUnits) {
        CreateUnit(30.0f, NULL);
        spawnTimer -= spawnInterval;
    }

    for (int i = 0; i < numActiveUnits; ) {
        if (units[i].alive) {
            float sway = sinf(units[i].age * swayFrequency) * swayAmplitude;
            units[i].position.x += (units[i].velocity.x + sway) * deltaTime;
            units[i].position.y += units[i].velocity.y * deltaTime;
            units[i].position.z += units[i].velocity.z * deltaTime;

            units[i].age += deltaTime;

            if (units[i].position.y < -5.0f || units[i].age > 15.0f) {
                units[i].alive = 0;
                if (i < numActiveUnits - 1) {
                    units[i] = units[numActiveUnits - 1];
                }
                numActiveUnits--;
                continue;
            }

            if (units[i].position.y < 5.0f) {
                units[i].alpha = desc.alpha * (units[i].position.y / 5.0f);
            }
        }
        i++;
    }
}

void gbSnow::Draw(void) {
    if (!pTexture) return;

    for (int i = 0; i < numActiveUnits; i++) {
        if (units[i].alive) {
            // Render snowflake billboard
        }
    }
}

// Export assignment operators
gbDropDesc& gbDropDesc::operator=(const gbDropDesc& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbDropDesc));
    }
    return *this;
}

gbDropUnit& gbDropUnit::operator=(const gbDropUnit& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbDropUnit));
    }
    return *this;
}

gbDropGroup& gbDropGroup::operator=(const gbDropGroup& other) {
    if (this != &other) {
        if (units) delete[] units;
        maxUnits = other.maxUnits;
        numActiveUnits = 0;
        units = new gbDropUnit[maxUnits];
        memcpy(&desc, &other.desc, sizeof(gbDropDesc));
        strcpy(textureName, other.textureName);
        pTexture = other.pTexture;
        elapsedTime = 0.0f;
        spawnTimer = 0.0f;
    }
    return *this;
}

gbRain& gbRain::operator=(const gbRain& other) {
    if (this != &other) {
        gbDropGroup::operator=(other);
    }
    return *this;
}

gbSnow& gbSnow::operator=(const gbSnow& other) {
    if (this != &other) {
        gbDropGroup::operator=(other);
        swayAmplitude = other.swayAmplitude;
        swayFrequency = other.swayFrequency;
    }
    return *this;
}
