/**
 * gbengine.dll - gbParticle
 * Particle system implementation
 * Functions: 38
 */

#include "gbengine/gbengine_types.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Forward declarations
class gbVFile;
class gbVFile1;
class gbVFileSystem;
class gbTexture;
class gbRenderEffect;
class gbEffectMgr;
class gbResManager;
class gbCamera;
struct gbParticleUnit;
class gbVisNode;
class gbStaticChain;

// External globals
extern gbVFileSystem* g_pVFileSys;
extern gbResManager* g_pResMgr;
extern gbEffectMgr* g_pEffectMgr;

// Constants
static const float HALF_FACTOR = 0.5f;

/* ======== gbEmitterData ======== */

struct gbEmitterData {
    gbVec3D velocity;        // +0x00
    float speedScale;        // +0x0c
    float speedVariance;     // +0x10
    float unused1;           // +0x14
    float unused2;           // +0x18
    float lifetime;          // +0x1c
    float lifetimeVariance;  // +0x20
};

class gbEmitterData_Class {
public:
    gbEmitterData_Class(void) {}
};

/* ======== gbEmitterSquare ======== */

struct gbEmitterSquare {
    int type;
    float width;
    float height;
    float depth;
};

class gbEmitterSquare_Class {
public:
    gbEmitterSquare_Class(void) {}
};

/* ======== gbPartParamControl ======== */

class gbPartParamControl {
public:
    int controlType;           // +0x00
    int numKeys;               // +0x04
    float keys[16];            // +0x08
    float values[16][4];       // +0x48

    gbPartParamControl(void);
    void LoadFromFile(gbVFile* vfile);
    void GetValue(float* result, float t);
};

gbPartParamControl::gbPartParamControl(void) {
    controlType = 0;
    numKeys = 0;
    memset(keys, 0, sizeof(keys));
    memset(values, 0, sizeof(values));
}

void gbPartParamControl::LoadFromFile(gbVFile* vfile) {
    // Read control type and key count
    // Read key times and values
    // Implementation based on gbVFileSystem::Read calls
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

    // Linear interpolation between keys
    for (int i = 0; i < numKeys - 1; i++) {
        if (t >= keys[i] && t <= keys[i + 1]) {
            float factor = (t - keys[i]) / (keys[i + 1] - keys[i]);
            result[0] = values[i][0] + (values[i + 1][0] - values[i][0]) * factor;
            return;
        }
    }
}

/* ======== gbPartGroupParam ======== */

struct gbPartGroupParam {
    char name[32];                     // +0x00
    int flags;                         // +0x20
    float gravity;                     // +0x24
    float airResistance;               // +0x28
    float unused1;                     // +0x2c
    float unused2;                     // +0x30
    float unused3;                     // +0x34
    char textureName[256];             // +0x38
    int blendMode;                     // +0x138
    int unused4;                       // +0x13c
    int unused5;                       // +0x140
    int unused6;                       // +0x144
    int unused7;                       // +0x148
    int unused8;                       // +0x14c
    int randomRotation;                // +0x150
    int unused9;                       // +0x154
    int unused10;                      // +0x158
    int unused11;                      // +0x15c
    int numFrames;                     // +0x160
    int blendType;                     // +0x164
    gbPartParamControl sizeControl;    // +0x168
    // More controls follow (color, alpha, rotation)
    // Total size approximately 0x4940 bytes

    gbTexture* pTexture;               // +0x48f8
    gbRenderEffect* pRenderEffect;     // +0x493c
    int textureLoaded;                 // +0x4938
};

class gbPartGroupParam_Class {
public:
    gbPartGroupParam param;

    gbPartGroupParam_Class(void);
    ~gbPartGroupParam_Class(void);
    void LoadFromFile(gbVFile* vfile);
    void ComputeAirResist(gbParticleUnit* particle, float deltaTime);
    void ComputeParticleParam(gbParticleUnit* particle, float lifeFactor, float deltaTime);
    void InitParticleParam(gbParticleUnit* particle);

    gbTexture* GetTexture(void) { return param.pTexture; }
    gbRenderEffect* GetRenderEffect(void) { return param.pRenderEffect; }
};

gbPartGroupParam_Class::gbPartGroupParam_Class(void) {
    memset(&param, 0, sizeof(param));
}

gbPartGroupParam_Class::~gbPartGroupParam_Class(void) {
}

void gbPartGroupParam_Class::LoadFromFile(gbVFile* vfile) {
    // Load all particle group parameters from file
    // This involves many Read() calls based on the JSON
}

void gbPartGroupParam_Class::ComputeAirResist(gbParticleUnit* particle, float deltaTime) {
    // Apply air resistance to particle velocity
    float resist = param.airResistance * deltaTime;
    // particle->velocity *= (1.0f - resist);
}

void gbPartGroupParam_Class::ComputeParticleParam(gbParticleUnit* particle, float lifeFactor, float deltaTime) {
    // Compute particle parameters based on lifetime
    // Update color, size, alpha based on control curves
}

void gbPartGroupParam_Class::InitParticleParam(gbParticleUnit* particle) {
    // Initialize particle parameters at spawn time
}

/* ======== gbPartEmitter ======== */

struct gbEmitterSquareData {
    gbVec3D posVariance;     // +0x4c
    gbVec3D velVariance;     // +0x50
    // More fields...
};

class gbPartEmitter {
public:
    char data[0x520];        // Emitter data
    gbEmitterSquareData* emitterData;  // +offset

    gbPartEmitter(void);
    ~gbPartEmitter(void);
    void LoadFromFile(gbVFile* vfile);
    int ComputeEmitterData(gbEmitterData* data, double time, double deltaTime);
    void ComputeParticleInitPos(gbParticleUnit* particle);
    void ComputeParticleInitVel(gbEmitterData* data, gbParticleUnit* particle);
    void SetLoopEmit(bool loop);
};

gbPartEmitter::gbPartEmitter(void) {
    memset(data, 0, sizeof(data));
}

gbPartEmitter::~gbPartEmitter(void) {
}

void gbPartEmitter::LoadFromFile(gbVFile* vfile) {
    // Load emitter parameters
}

int gbPartEmitter::ComputeEmitterData(gbEmitterData* emitData, double time, double deltaTime) {
    // Compute emission data for this frame
    return 1;
}

void gbPartEmitter::ComputeParticleInitPos(gbParticleUnit* particle) {
    // Set initial particle position based on emitter shape
}

void gbPartEmitter::ComputeParticleInitVel(gbEmitterData* emitData, gbParticleUnit* particle) {
    // Set initial particle velocity
}

void gbPartEmitter::SetLoopEmit(bool loop) {
    // Set looping mode
}

/* ======== gbParticleUnit ======== */

struct gbParticleUnit {
    int alive;               // +0x00
    int unused1;             // +0x04
    double age;              // +0x08
    float lifetime;          // +0x10
    int frame;               // +0x14
    int randomSeed;          // +0x18
    gbVec3D velocity;        // +0x1c
    float velocityY;         // +0x20 (separate for gravity)
    gbVec3D acceleration;    // +0x24
    int unused2;             // +0x28
    int unused3;             // +0x2c
    int unused4;             // +0x30
    gbVec3D position;        // +0x34
    float size;              // +0x40
    float rotation;          // +0x44
    unsigned char colorR;    // +0x48
    unsigned char colorG;    // +0x49
    unsigned char colorB;    // +0x4a
    unsigned char colorA;    // +0x4b
    int unused5;             // +0x4c
    int rotationDir;         // +0x50
    int unused6;             // +0x54
};

class gbParticleUnit_Class {
public:
    gbParticleUnit_Class(void);
    gbParticleUnit_Class(gbParticleUnit* other);
};

gbParticleUnit_Class::gbParticleUnit_Class(void) {
    // Constructor initializes offsets 0x1c through 0x3c to zero
}

gbParticleUnit_Class::gbParticleUnit_Class(gbParticleUnit* other) {
    // Copy constructor
}

/* ======== gbParticleGroup ======== */

// Forward declare gbParticleEffect
class gbParticleEffect;

class gbParticleGroup {
public:
    char padding1[0x48];                   // +0x00
    char* groupName;                       // +0x48
    int unused1;                           // +0x4c
    int unused2;                           // +0x50
    gbPartGroupParam_Class* pGroupParam;   // +0x78
    gbPartEmitter* pEmitter;               // +0x7c
    gbParticleUnit* particleArray;         // +0x80
    int maxParticles;                      // +0x84
    int numAliveParticles;                 // +0x88
    void* pParticleEffect;                 // +0x8c

    gbParticleGroup(void);
    ~gbParticleGroup(void);
    void LoadFromFile(gbVFile* vfile, gbParticleEffect* effect);
    void Reset(void);
    gbParticleUnit* GetOldestParticle(void);
    gbParticleUnit* CreateOneParticle(gbEmitterData* data);
    int UpdateOneParticle(gbParticleUnit* particle, double deltaTime);
    void Update(double deltaTime);
    void Render(void);

    int GetAlivePartNum(void) { return numAliveParticles; }
    char* GetName(void) { return groupName; }
    gbPartGroupParam_Class* GetGroupParam(void) { return pGroupParam; }
};

gbParticleGroup::gbParticleGroup(void) {
    groupName = NULL;
    unused1 = 0;
    unused2 = 0;
}

gbParticleGroup::~gbParticleGroup(void) {
}

void gbParticleGroup::LoadFromFile(gbVFile* vfile, gbParticleEffect* effect) {
    // Load particle group data
}

void gbParticleGroup::Reset(void) {
    numAliveParticles = 0;
}

gbParticleUnit* gbParticleGroup::GetOldestParticle(void) {
    // Find particle with highest age
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

    // Find free particle slot or reuse oldest
    if (numAliveParticles == maxParticles) {
        // Reuse strategy based on settings
        particle = GetOldestParticle();
        if (!particle) return NULL;
    } else {
        particle = &particleArray[numAliveParticles];
        numAliveParticles++;
    }

    // Initialize particle
    particle->age = 0.0;
    particle->alive = 1;
    particle->lifetime = emitData->lifetime;
    particle->frame = 0;

    // Set random rotation direction
    particle->rotationDir = (rand() & 1) ? -1 : 1;

    // Initialize velocity
    particle->velocity = emitData->velocity;

    // Compute initial position
    pEmitter->ComputeParticleInitPos(particle);

    // Initialize particle parameters
    pGroupParam->InitParticleParam(particle);

    return particle;
}

int gbParticleGroup::UpdateOneParticle(gbParticleUnit* particle, double deltaTime) {
    // Update particle age
    particle->age += deltaTime;

    // Check if particle is dead
    if (particle->age >= particle->lifetime) {
        return 0;
    }

    // Update frame index
    float lifeFactor = (float)(particle->age / particle->lifetime);
    particle->frame = (int)(lifeFactor * pGroupParam->param.numFrames);
    if (particle->frame >= pGroupParam->param.numFrames) {
        particle->frame = 0;
    }

    // Apply air resistance
    float dt = (float)deltaTime;
    pGroupParam->ComputeAirResist(particle, dt);

    // Update particle parameters (color, size, etc.)
    pGroupParam->ComputeParticleParam(particle, lifeFactor, dt);

    // Apply gravity
    particle->velocityY -= pGroupParam->param.gravity * dt;

    // Update position
    particle->position.x += particle->velocity.x * dt;
    particle->position.y += particle->velocityY * dt - pGroupParam->param.gravity * dt * dt * HALF_FACTOR;
    particle->position.z += particle->velocity.z * dt;

    return 1;
}

void gbParticleGroup::Update(double deltaTime) {
    // Update all particles
    for (int i = 0; i < numAliveParticles; ) {
        if (!UpdateOneParticle(&particleArray[i], deltaTime)) {
            // Particle died, swap with last particle
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
    // Render all particles using the render effect
    if (!pGroupParam->GetRenderEffect()) return;

    // Setup render state and draw particles
    // This would involve D3D calls to render billboards
}

/* ======== gbVisNode (base class layout for inheritance) ======== */

class gbVisNode {
public:
    char _visnode_data[0x58];
    gbVisNode();
    virtual ~gbVisNode();
    virtual void Update();
    virtual void Render(void* renderInfo);
    virtual int Attach(gbRenderEffect* effect);
    virtual void GetBoundSphere(gbSphere* sphere);
    virtual void Reset(float time);
};

/* ======== gbParticleEffect ======== */

class gbParticleEffect : public gbVisNode {
public:

    gbParticleGroup** particleGroups;     // +0xe0
    int numGroups;                         // +0xe4
    gbPartGroupParam** groupParams;        // +0xe8
    int numParams;                         // +0xec
    gbPartEmitter** emitters;              // +0xf0
    int numEmitters;                       // +0xf4
    char* effectName;                      // +0xf8
    int unused1;                           // +0xfc
    int unused2;                           // +0x100
    char padding1[0xc];                    // +0x104
    int unused3;                           // +0x108
    float unused4;                         // +0x10c
    char padding2[0xc];                    // +0x110
    float spaceScale;                      // +0x118
    gbMatrix4 worldTransform;              // +0x11c

    gbParticleEffect(void);
    gbParticleEffect(gbParticleEffect* other);
    virtual ~gbParticleEffect(void);

    int LoadFromFile(char* filename);
    void Reset(float time);
    virtual void Update(void);
    void UpdateInternal(void);
    virtual int Attach(gbRenderEffect* effect);
    virtual void GetBoundSphere(gbSphere* sphere);
    virtual void Render(void* renderInfo);

    gbParticleGroup* GetParticleGroup(int index);
    gbPartGroupParam* GetGroupParam(int index);
    gbPartEmitter* GetEmitter(int index);
    void SetSpaceScale(float scale) { spaceScale = scale; }
    float GetSpaceScale(void) { return spaceScale; }
};

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
    unused4 = -256.0f;  // 0xbff00000
}

gbParticleEffect::gbParticleEffect(gbParticleEffect* other) {
    // Copy constructor
}

gbParticleEffect::~gbParticleEffect(void) {
    // Cleanup
}

int gbParticleEffect::LoadFromFile(char* filename) {
    // Load particle effect from file
    return 1;
}

void gbParticleEffect::Reset(float time) {
    // Reset all particle groups
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
    // Update all particle groups
    double deltaTime = 0.016;  // ~60fps
    for (int i = 0; i < numGroups; i++) {
        if (particleGroups[i]) {
            particleGroups[i]->Update(deltaTime);
        }
    }
}

int gbParticleEffect::Attach(gbRenderEffect* effect) {
    // Attach to render effect
    return 1;
}

void gbParticleEffect::GetBoundSphere(gbSphere* sphere) {
    // Compute bounding sphere for all particles
    sphere->center.x = 0.0f;
    sphere->center.y = 0.0f;
    sphere->center.z = 0.0f;
    sphere->radius = 100.0f;
}

void gbParticleEffect::Render(void* renderInfo) {
    // Render all particle groups
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
