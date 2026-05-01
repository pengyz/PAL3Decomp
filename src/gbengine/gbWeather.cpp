/**
 * gbengine.dll - gbWeather
 * Weather effects implementation (rain, snow)
 * Functions: 13
 */

#include "gbengine/gbengine_types.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Forward declarations
class gbCamera;
class gbTexture;

// External globals
extern double g_CurrentTime;
extern unsigned int g_CurrentTick;

/* ======== gbDropDesc ======== */

struct gbDropDesc {
    float gravity;           // +0x00
    float windX;             // +0x04
    float windZ;             // +0x08
    float speed;             // +0x0c
    float size;              // +0x10
    float viewDistance;      // +0x14
    float density;           // +0x18
    gbColorFlt color;        // +0x1c
    float alpha;             // +0x2c
    int textureIndex;        // +0x30

    gbDropDesc& operator=(const gbDropDesc& other);
};

/* ======== gbDropUnit ======== */

struct gbDropUnit {
    gbVec3D position;        // +0x00
    gbVec3D velocity;        // +0x0c
    float size;              // +0x18
    float alpha;             // +0x1c
    float age;               // +0x20
    int alive;               // +0x24

    gbDropUnit(void);
    gbDropUnit& operator=(const gbDropUnit& other);
};

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

class gbDropGroup {
public:
    gbDropUnit* units;           // +0x00
    int maxUnits;                // +0x04
    int numActiveUnits;          // +0x08
    gbDropDesc desc;             // +0x0c
    char textureName[64];        // +0x40
    gbTexture* pTexture;         // +0x80
    float elapsedTime;           // +0x84
    float spawnTimer;            // +0x88

    gbDropGroup(int maxDrops, gbDropDesc* dropDesc, char* texName);
    gbDropGroup(gbDropGroup* other);
    virtual ~gbDropGroup(void);

    void Render(gbCamera* camera);
    void CreateUnit(float heightOffset, gbCamera* camera);
    gbDropGroup& operator=(const gbDropGroup& other);
};

gbDropGroup::gbDropGroup(int maxDrops, gbDropDesc* dropDesc, char* texName) {
    maxUnits = maxDrops;
    numActiveUnits = 0;

    // Allocate drop units
    units = new gbDropUnit[maxDrops];

    // Copy descriptor
    memcpy(&desc, dropDesc, sizeof(gbDropDesc));

    // Copy texture name
    if (texName) {
        strncpy(textureName, texName, 63);
        textureName[63] = '\0';
    } else {
        textureName[0] = '\0';
    }

    pTexture = NULL;
    elapsedTime = 0.0f;
    spawnTimer = 0.0f;

    // Load texture if name provided
    // pTexture = LoadTexture(textureName);
}

gbDropGroup::gbDropGroup(gbDropGroup* other) {
    // Copy constructor
    maxUnits = other->maxUnits;
    numActiveUnits = 0;
    units = new gbDropUnit[maxUnits];
    memcpy(&desc, &other->desc, sizeof(gbDropDesc));
    strcpy(textureName, other->textureName);
    pTexture = other->pTexture;
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

    // Render all active drop units as billboards
    for (int i = 0; i < numActiveUnits; i++) {
        if (units[i].alive) {
            // Render billboard at units[i].position
            // Use units[i].size and units[i].alpha
        }
    }
}

void gbDropGroup::CreateUnit(float heightOffset, gbCamera* camera) {
    // Find free unit
    if (numActiveUnits >= maxUnits) return;

    gbDropUnit* unit = &units[numActiveUnits];
    numActiveUnits++;

    // Initialize position (random around camera)
    float range = desc.viewDistance;
    unit->position.x = ((float)rand() / RAND_MAX) * range * 2.0f - range;
    unit->position.y = heightOffset;
    unit->position.z = ((float)rand() / RAND_MAX) * range * 2.0f - range;

    // Initialize velocity
    unit->velocity.x = desc.windX;
    unit->velocity.y = -desc.speed;
    unit->velocity.z = desc.windZ;

    // Initialize properties
    unit->size = desc.size;
    unit->alpha = desc.alpha;
    unit->age = 0.0f;
    unit->alive = 1;
}

/* ======== gbRain ======== */

class gbRain : public gbDropGroup {
public:
    gbRain(int maxDrops, gbDropDesc* dropDesc, char* texName);
    gbRain(gbRain* other);
    virtual ~gbRain(void);

    virtual void Update(float deltaTime);
    virtual void Draw(void);
    gbRain& operator=(const gbRain& other);
};

gbRain::gbRain(int maxDrops, gbDropDesc* dropDesc, char* texName)
    : gbDropGroup(maxDrops, dropDesc, texName) {
    // Rain-specific initialization
}

gbRain::gbRain(gbRain* other)
    : gbDropGroup(other) {
    // Rain copy constructor
}

gbRain::~gbRain(void) {
    // Cleanup
}

void gbRain::Update(float deltaTime) {
    elapsedTime += deltaTime;
    spawnTimer += deltaTime;

    // Spawn new rain drops based on density
    float spawnInterval = 1.0f / (desc.density * 10.0f);
    while (spawnTimer >= spawnInterval && numActiveUnits < maxUnits) {
        CreateUnit(50.0f, NULL);  // Rain spawns high
        spawnTimer -= spawnInterval;
    }

    // Update existing drops
    for (int i = 0; i < numActiveUnits; ) {
        if (units[i].alive) {
            // Update position
            units[i].position.x += units[i].velocity.x * deltaTime;
            units[i].position.y += units[i].velocity.y * deltaTime;
            units[i].position.z += units[i].velocity.z * deltaTime;

            // Apply gravity
            units[i].velocity.y -= desc.gravity * deltaTime;

            // Update age
            units[i].age += deltaTime;

            // Kill if below ground or too old
            if (units[i].position.y < -10.0f || units[i].age > 10.0f) {
                units[i].alive = 0;
                // Swap with last unit
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
    // Render rain drops as streaks
    if (!pTexture) return;

    for (int i = 0; i < numActiveUnits; i++) {
        if (units[i].alive) {
            // Render rain streak
            // Start: units[i].position
            // End: units[i].position + velocity * trailLength
            // Color: desc.color
            // Alpha: units[i].alpha
        }
    }
}

/* ======== gbSnow ======== */

class gbSnow : public gbDropGroup {
public:
    float swayAmplitude;         // Additional field for snow
    float swayFrequency;

    gbSnow(int maxDrops, gbDropDesc* dropDesc, char* texName, float amplitude);
    gbSnow(gbSnow* other);
    virtual ~gbSnow(void);

    virtual void Update(float deltaTime);
    virtual void Draw(void);
    gbSnow& operator=(const gbSnow& other);
};

gbSnow::gbSnow(int maxDrops, gbDropDesc* dropDesc, char* texName, float amplitude)
    : gbDropGroup(maxDrops, dropDesc, texName) {
    swayAmplitude = amplitude;
    swayFrequency = 1.0f;
}

gbSnow::gbSnow(gbSnow* other)
    : gbDropGroup(other) {
    swayAmplitude = other->swayAmplitude;
    swayFrequency = other->swayFrequency;
}

gbSnow::~gbSnow(void) {
    // Cleanup
}

void gbSnow::Update(float deltaTime) {
    elapsedTime += deltaTime;
    spawnTimer += deltaTime;

    // Spawn new snowflakes based on density
    float spawnInterval = 1.0f / (desc.density * 5.0f);
    while (spawnTimer >= spawnInterval && numActiveUnits < maxUnits) {
        CreateUnit(30.0f, NULL);  // Snow spawns at medium height
        spawnTimer -= spawnInterval;
    }

    // Update existing snowflakes
    for (int i = 0; i < numActiveUnits; ) {
        if (units[i].alive) {
            // Update position with swaying motion
            float sway = sinf(units[i].age * swayFrequency) * swayAmplitude;
            units[i].position.x += (units[i].velocity.x + sway) * deltaTime;
            units[i].position.y += units[i].velocity.y * deltaTime;
            units[i].position.z += units[i].velocity.z * deltaTime;

            // Snow falls slower than rain, no gravity acceleration
            // Wind affects snow more

            // Update age
            units[i].age += deltaTime;

            // Kill if below ground or too old
            if (units[i].position.y < -5.0f || units[i].age > 15.0f) {
                units[i].alive = 0;
                // Swap with last unit
                if (i < numActiveUnits - 1) {
                    units[i] = units[numActiveUnits - 1];
                }
                numActiveUnits--;
                continue;
            }

            // Fade out near ground
            if (units[i].position.y < 5.0f) {
                units[i].alpha = desc.alpha * (units[i].position.y / 5.0f);
            }
        }
        i++;
    }
}

void gbSnow::Draw(void) {
    // Render snowflakes as textured billboards
    if (!pTexture) return;

    for (int i = 0; i < numActiveUnits; i++) {
        if (units[i].alive) {
            // Render snowflake billboard
            // Position: units[i].position
            // Size: units[i].size
            // Color: desc.color
            // Alpha: units[i].alpha
            // Rotation: based on age for gentle spinning
        }
    }
}

// Export assignment operators (from demangled exports)
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
        // Deep copy
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
