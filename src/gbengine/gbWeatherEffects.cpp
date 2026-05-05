/**
 * gbengine.dll - Weather effects
 * gbRain and gbSnow (particle-based weather rendering)
 */

#include "gbengine/gbParticle.h"
#include "gbengine/gbCamera.h"
#include <string.h>

// ======== gbRain ========

gbRain::gbRain(int maxDrops, const gbDropDesc* dropDesc, const char* texName)
    : gbDropGroup(maxDrops, dropDesc, texName) {
    // Base class constructor handles initialization
}

gbRain::gbRain(const gbRain& other)
    : gbDropGroup(other) {
    // Base class copy constructor
}

void gbRain::Update(float deltaTime) {
    /* UNCERTAIN: Rain update logic */
    // Would update all rain drops, apply gravity, respawn
    elapsedTime += deltaTime;

    // Update each drop
    for (int i = 0; i < numActiveUnits; i++) {
        gbDropUnit* drop = &units[i];
        if (!drop->alive) continue;

        // Apply gravity
        drop->velocity.y -= 9.8f * deltaTime;

        // Update position
        drop->position.x += drop->velocity.x * deltaTime;
        drop->position.y += drop->velocity.y * deltaTime;
        drop->position.z += drop->velocity.z * deltaTime;

        // Respawn if below ground
        if (drop->position.y < 0.0f) {
            drop->position.y = 100.0f;
            drop->velocity.y = -desc.speed * desc.gravity;
        }
    }
}

void gbRain::Draw(void) {
    /* UNCERTAIN: Rain rendering */
    // Would render rain drops as textured billboards or line segments
}

// ======== gbSnow ========

gbSnow::gbSnow(int maxFlakes, const gbDropDesc* dropDesc, const char* texName, float windFactor)
    : gbDropGroup(maxFlakes, dropDesc, texName) {
    // windFactor stored in subclass-specific field
    /* UNCERTAIN: Wind factor storage */
}

gbSnow::gbSnow(const gbSnow& other)
    : gbDropGroup(other) {
    // Base class copy constructor
}

void gbSnow::Update(float deltaTime) {
    /* UNCERTAIN: Snow update logic */
    // Would update snowflakes with gentler fall and wind effects
    elapsedTime += deltaTime;

    // Update each snowflake
    for (int i = 0; i < numActiveUnits; i++) {
        gbDropUnit* flake = &units[i];
        if (!flake->alive) continue;

        // Apply gentle gravity
        flake->velocity.y -= 2.0f * deltaTime;

        // Update position with wind sway
        flake->position.x += flake->velocity.x * deltaTime;
        flake->position.y += flake->velocity.y * deltaTime;
        flake->position.z += flake->velocity.z * deltaTime;

        // Respawn if below ground
        if (flake->position.y < 0.0f) {
            flake->position.y = 100.0f;
            flake->velocity.y = -desc.speed * desc.gravity * 0.3f;
        }
    }
}

void gbSnow::Draw(void) {
    /* UNCERTAIN: Snow rendering */
    // Would render snowflakes as textured billboards
}
