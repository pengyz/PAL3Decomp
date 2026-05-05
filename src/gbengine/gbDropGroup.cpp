/**
 * gbengine.dll - gbDropGroup
 * Drop/particle group for weather effects (rain/snow)
 */

#include "gbengine/gbParticle.h"
#include "gbengine/gbCamera.h"
#include <string.h>
#include <stdlib.h>

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
    memcpy(this, &other, sizeof(gbDropGroup));

    // Deep copy units array
    if (other.units && other.maxUnits > 0) {
        units = (gbDropUnit*)malloc(sizeof(gbDropUnit) * other.maxUnits);
        if (units) {
            memcpy(units, other.units, sizeof(gbDropUnit) * other.maxUnits);
        }
    } else {
        units = NULL;
    }
}

void gbDropGroup::CreateUnit(float deltaTime, gbCamera* camera) {
    if (!units || numActiveUnits >= maxUnits) return;

    /* UNCERTAIN: Drop unit initialization logic */
    spawnTimer += deltaTime;

    // Spawn new drop based on density (density controls spawn rate)
    float spawnRate = 1.0f / (desc.density + 0.01f);
    if (spawnTimer >= spawnRate) {
        gbDropUnit* unit = &units[numActiveUnits];

        // Initialize drop position relative to camera
        unit->position.x = (float)(rand() % 200 - 100);
        unit->position.y = 100.0f;
        unit->position.z = (float)(rand() % 200 - 100);

        // Calculate velocity from gravity and wind
        unit->velocity.x = desc.windX;
        unit->velocity.y = -desc.speed * desc.gravity;
        unit->velocity.z = desc.windZ;
        unit->alive = 1;

        numActiveUnits++;
        spawnTimer = 0.0f;
    }
}
