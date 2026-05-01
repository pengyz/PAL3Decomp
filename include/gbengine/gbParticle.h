#pragma once

#include "gbengine/gbengine_types.h"

// Forward declarations
class gbVFile;
class gbTexture;
class gbRenderEffect;
class gbCamera;
struct gbStaticChainNode;
class gbStaticChain;
struct gbRenderInfoObj;
class gbVisNode;

/* ======== gbEmitterData ======== */

struct gbEmitterData {
    gbVec3D velocity;        // +0x00
    float speedScale;        // +0x0c
    float speedVariance;     // +0x10
    float unused1;           // +0x14
    float unused2;           // +0x18
    float lifetime;          // +0x1c
    float lifetimeVariance;  // +0x20

    gbEmitterData();
    gbEmitterData& operator=(const gbEmitterData& p0);
};

/* ======== gbPartParamControl ======== */

class gbPartParamControl {
public:
    int controlType;           // +0x00
    int numKeys;               // +0x04
    float keys[16];            // +0x08
    float values[16][4];       // +0x48

    gbPartParamControl(void);
    gbPartParamControl& operator=(const gbPartParamControl& other);
    void LoadFromFile(gbVFile* vfile);
    void GetValue(float* result, float t);
};

/* ======== gbParticleUnit ======== */

struct gbParticleUnit {
    int alive;               // +0x00
    int unused1;             // +0x04
    double age;              // +0x08
    float lifetime;          // +0x10
    int frame;               // +0x14
    int randomSeed;          // +0x18
    gbVec3D velocity;        // +0x1c
    float velocityY;         // +0x28
    gbVec3D acceleration;    // +0x2c
    int unused2;             // +0x38
    gbVec3D position;        // +0x3c
    float size;              // +0x48
    float rotation;          // +0x4c
    unsigned char colorR;    // +0x50
    unsigned char colorG;    // +0x51
    unsigned char colorB;    // +0x52
    unsigned char colorA;    // +0x53
    int unused3;             // +0x54
    int rotationDir;         // +0x58
    int unused4;             // +0x5c

    gbParticleUnit(void);
    gbParticleUnit(const gbParticleUnit& other);
    gbParticleUnit(gbParticleUnit& other);
    gbParticleUnit& operator=(const gbParticleUnit& p0);
};

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
    char padding[0x3790];              // remaining controls
    gbTexture* pTexture;               // +0x48f8
    int textureLoaded;                 // +0x4938
    gbRenderEffect* pRenderEffect;     // +0x493c

    gbPartGroupParam(void);
    ~gbPartGroupParam(void);
    gbPartGroupParam& operator=(const gbPartGroupParam& other);

    void LoadFromFile(gbVFile* vfile);
    void ComputeAirResist(gbParticleUnit* particle, float deltaTime);
    void ComputeParticleParam(gbParticleUnit* particle, float lifeFactor, float deltaTime);
    void InitParticleParam(gbParticleUnit* particle);

    gbTexture* GetTexture(void);
    gbRenderEffect* GetRenderEffect(void);
};

/* ======== gbPartEmitter ======== */

class gbPartEmitter {
public:
    char data[0x520];

    gbPartEmitter(void);
    ~gbPartEmitter(void);
    gbPartEmitter& operator=(const gbPartEmitter& other);

    void LoadFromFile(gbVFile* vfile);
    int ComputeEmitterData(gbEmitterData* data, double time, double deltaTime);
    void ComputeParticleInitPos(gbParticleUnit* particle);
    void ComputeParticleInitVel(gbEmitterData* data, gbParticleUnit* particle);
    void SetLoopEmit(bool loop);
};

/* ======== gbParticleGroup ======== */

class gbParticleEffect;

class gbParticleGroup {
public:
    char padding1[0x48];
    char* groupName;                       // +0x48
    int unused1;
    int unused2;
    char padding2[0x24];
    gbPartGroupParam* pGroupParam;         // +0x78
    gbPartEmitter* pEmitter;               // +0x7c
    gbParticleUnit* particleArray;         // +0x80
    int maxParticles;                      // +0x84
    int numAliveParticles;                 // +0x88
    void* pParticleEffect;                 // +0x8c

    gbParticleGroup(void);
    ~gbParticleGroup(void);
    gbParticleGroup& operator=(const gbParticleGroup& other);

    void LoadFromFile(gbVFile* vfile, gbParticleEffect* effect);
    void Reset(void);
    void Update(double deltaTime);
    void Render(void);
    int GetAlivePartNum(void);
    char* GetName(void);
    gbPartGroupParam* GetGroupParam(void);

private:
    gbParticleUnit* GetOldestParticle(void);
    gbParticleUnit* CreateOneParticle(gbEmitterData* data);
    int UpdateOneParticle(gbParticleUnit* particle, double deltaTime);
};

/* ======== gbVisNodeBase (particle system base) ======== */

class gbVisNodeBase {
public:
    char _visnode_data[0x58];
    gbVisNodeBase();
    virtual ~gbVisNodeBase();
    virtual void Update();
    virtual void Render(gbRenderInfoObj* renderInfo);
    virtual int Attach(gbRenderEffect* effect);
    virtual void GetBoundSphere(gbSphere* sphere);
    virtual void Reset(float time);
};

/* ======== gbParticleEffect ======== */

class gbParticleEffect : public gbVisNodeBase {
public:
    gbParticleGroup** particleGroups;      // offset
    int numGroups;
    gbPartGroupParam** groupParams;
    int numParams;
    gbPartEmitter** emitters;
    int numEmitters;
    char* effectName;
    int unused1;
    int unused2;
    char padding1[0xc];
    int unused3;
    float unused4;
    char padding2[0xc];
    float spaceScale;
    gbMatrix4 worldTransform;

    gbParticleEffect(void);
    gbParticleEffect(const gbParticleEffect& other);
    virtual ~gbParticleEffect(void);

    gbParticleEffect& operator=(const gbParticleEffect& other);

    int LoadFromFile(char* filename);
    void Reset(float time);
    virtual void Update(void);
    void UpdateInternal(void);
    virtual int Attach(gbRenderEffect* effect);
    virtual void GetBoundSphere(gbSphere* sphere);
    virtual void Render(gbRenderInfoObj* renderInfo);

    gbParticleGroup* GetParticleGroup(int index);
    gbPartGroupParam* GetGroupParam(int index);
    gbPartEmitter* GetEmitter(int index);
    void SetSpaceScale(float scale);
    float GetSpaceScale(void);
};

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

    gbDropGroup(int maxDrops, const gbDropDesc* dropDesc, const char* texName);
    gbDropGroup(const gbDropGroup& other);
    virtual ~gbDropGroup(void);

    void Render(gbCamera* camera);
    gbDropGroup& operator=(const gbDropGroup& other);

private:
    void CreateUnit(float heightOffset, gbCamera* camera);

    friend class gbRain;
    friend class gbSnow;
};

/* ======== gbRain ======== */

class gbRain : public gbDropGroup {
public:
    gbRain(int maxDrops, const gbDropDesc* dropDesc, const char* texName);
    gbRain(const gbRain& other);
    virtual ~gbRain(void);

    gbRain& operator=(const gbRain& other);

private:
    virtual void Update(float deltaTime);
    virtual void Draw(void);
};

/* ======== gbSnow ======== */

class gbSnow : public gbDropGroup {
public:
    float swayAmplitude;
    float swayFrequency;

    gbSnow(int maxDrops, const gbDropDesc* dropDesc, const char* texName, float amplitude);
    gbSnow(const gbSnow& other);
    virtual ~gbSnow(void);

    gbSnow& operator=(const gbSnow& other);

private:
    virtual void Update(float deltaTime);
    virtual void Draw(void);
};
