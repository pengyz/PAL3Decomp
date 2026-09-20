#pragma once

#include "gbengine/gbengine_export.h"
#pragma warning(disable: 4521) // multiple copy constructors (gbParticleUnit exports both)

#include "gbengine/gbengine_types.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbCamera.h"
#include "gbengine/gbChain.h"
#include "gbengine/gbSceneGraph.h"
#include "gbengine/gbVisNode.h"

/* ======== gbEmitterData ======== */

struct gbEmitterData {
    gbVec3D velocity;           // +0x00: emission velocity direction
    float speedMin;             // +0x0C: min speed (from paramControls[1])
    float speedMax;             // +0x10: max speed
    float lifetimeMin;          // +0x14: min lifetime (from paramControls[2])
    float lifetimeMax;          // +0x18: max lifetime
    float emitRateMin;          // +0x1C: min emit rate (from paramControls[3])
    float emitRateMax;          // +0x20: max emit rate
    int pad_24;                 // +0x24: alignment
    double emitAccumulator;     // +0x28: fractional particle accumulator
    // sizeof = 0x30 = 48

    gbEmitterData();
    gbEmitterData& operator=(const gbEmitterData& p0);
};

/* ======== gbPartParamControl ======== */

// sizeof = 0x11E4 (4580 bytes)
// Keyframe-based parameter control with 3 output channels and up to 101 keys.
// GetValue interpolates across channels, returning result[0..2].

#define GB_PARTCTRL_MAX_KEYS 101

struct gbPartKeyframeCh0 {
    float time;
    float value;
    float tangent;
};

struct gbPartKeyframeCh1 {
    float value;
    float tangentIn;
    float tangentOut;
};

class gbPartParamControl {
public:
    int controlType;                        // +0x00
    int numKeys;                            // +0x04
    char configData[0xC0];                  // +0x08
    int stateData[6];                       // +0xC8 (24 bytes)
    gbVec3D curveKeys[60];                  // +0xE0 (720 bytes = 0x2D0)
    gbVec3D keyData[303];                   // +0x3B0 (3636 bytes = 0xE34)

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
    float unused1;                     // +0x2C
    int turbulenceFlag;                // +0x30
    float dragCoefficient;             // +0x34
    char textureName[256];             // +0x38
    int blendMode;                     // +0x138
    int unused4;                       // +0x13C
    int unused5;                       // +0x140
    int unused6;                       // +0x144
    int rotRandMin;                    // +0x148
    int rotRandMax;                    // +0x14C
    int randomRotation;                // +0x150
    int unused9;                       // +0x154
    int unused10;                      // +0x158
    int unused11;                      // +0x15C
    int numFrames;                     // +0x160
    int blendType;                     // +0x164
    gbPartParamControl sizeControl;    // +0x168 (0x11E4 bytes)
    gbPartParamControl rotControl;     // +0x134C (0x11E4 bytes)
    gbPartParamControl alphaControl;   // +0x2530 (0x11E4 bytes)
    gbPartParamControl colorControl;   // +0x3714 (0x11E4 bytes)
    gbTexture* pTextures[16];          // +0x48F8: texture array (16 slots)
    int textureLoaded;                 // +0x4938: number of textures loaded
    gbRenderEffect* pRenderEffect;     // +0x493C
    // sizeof(gbPartGroupParam) == 0x4940

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

class GBAPI gbPartEmitter {
public:
    char configData[0x40];          // +0x00: emitter config (timing, repeat count etc.)
    gbVec3D basePosition;           // +0x40: emission origin
    gbVec3D velocityDeviation;      // +0x4C: random velocity spread
    char meshFilename[0x40];        // +0x58: mesh filename (only used when emitType==2)
    int emitType;                   // +0x98: 0=box, 1=sphere, 2=mesh
    float emitDuration;             // +0x9C: total emission duration
    float emitStartTime;            // +0xA0: emission start time offset
    int loopFlag;                   // +0xA4: loop emission (SetLoopEmit)
    int field_A8;                   // +0xA8
    gbVec3D boxMin;                 // +0xAC: box emitter min bounds
    gbVec3D boxMax;                 // +0xB8: box emitter max bounds
    float sphereRadius;             // +0xC4: sphere emitter radius
    float sphereRadiusVar;          // +0xC8: sphere radius variance
    gbVec3D* pMeshVertices;         // +0xCC: mesh emitter vertices
    int meshVertBufSize;            // +0xD0
    int numMeshVertices;            // +0xD4: mesh vertex count
    gbMatrix4 meshTransform;        // +0xD8: mesh emitter transform (64 bytes)
    int meshDataVersion;            // +0x118: mesh data version flag
    int pad_11C;                    // +0x11C
    gbPartParamControl paramControls[6]; // +0x120: 6 parameter control blocks (velocity, size, etc.)
    // sizeof(gbPartEmitter) = 0x120 + 6*0x11E4 = 0x6C78 = 27768

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
    char baseData[0x40];                   // +0x00: base group data (read from file)
    int field_40;                          // +0x40
    int field_44;                          // +0x44
    char* groupName;                       // +0x48
    int unused1;                           // +0x4C
    int unused2;                           // +0x50
    char padding2[0x1C];                   // +0x54
    int field_70;                          // +0x70
    int field_74;                          // +0x74
    gbPartGroupParam* pGroupParam;         // +0x78
    gbPartEmitter* pEmitter;               // +0x7C
    gbParticleUnit* particleArray;         // +0x80
    int maxParticles;                      // +0x84
    int numAliveParticles;                 // +0x88
    gbParticleEffect* pParticleEffect;     // +0x8C

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
    char _visnode_data[0x54];
    gbVisNodeBase();
    virtual ~gbVisNodeBase();
    virtual void Update();
    virtual void Render(gbRenderInfoObj* renderInfo);
    virtual int Attach(gbRenderEffect* effect);
    virtual void GetBoundSphere(gbSphere* sphere);
    virtual void Reset(float time);
};

/* ======== gbParticleEffect ======== */

class GBAPI gbParticleEffect : public gbVisNodeBase {
public:
    char _effectBaseData[64];              // +0x58: effect config data (read as block)
    int numGroups;                         // +0x98: number of particle groups
    int numParams;                         // +0x9C: number of group params
    int numEmitters;                       // +0xA0: number of emitters
    gbParticleGroup* particleGroups;       // +0xA4: array of groups
    gbPartGroupParam* groupParams;         // +0xA8: array of group params
    gbPartEmitter* emitters;               // +0xAC: array of emitters
    int field_B0;                          // +0xB0: read from file
    int field_B4;                          // +0xB4: read from file
    int field_B8;                          // +0xB8: read from file
    char _effectData2[0x5C];               // +0xBC: remaining data (offsets 188-279)
    float spaceScale;                      // +0x118: space scale factor
    gbMatrix4 worldTransform;              // +0x11C: world transform matrix

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

// sizeof = 0x24 = 36 bytes (verified from operator= memcpy size)
struct gbDropDesc {
    float unitsize;           // +0x00
    float range;      // +0x04: half-range for spawn area
    int emitrate;             // +0x08: spawn rate (particles/sec, int for FILD)
    float minlife;         // +0x0C: speed range X min
    float maxlife;         // +0x10: speed range X max
    float minvelocity;         // +0x14: speed range Y min
    float maxvelocity;         // +0x18: speed range Y max
    float minheight;         // +0x1C: speed range Z min
    float maxheight;         // +0x20: speed range Z max

    gbDropDesc& operator=(const gbDropDesc& other);
};

/* ======== gbDropUnit ======== */

// sizeof = 40 bytes (10 DWORDs, verified from operator= and constructor)
struct gbDropUnit {
    float lifetime;          // +0x00: remaining lifetime (decremented each frame)
    gbVec3D velocity;        // +0x04: current velocity
    gbVec3D position;        // +0x10: current position
    gbVec3D prevPosition;    // +0x1C: previous frame position (for streak rendering)

    gbDropUnit(void);
    gbDropUnit& operator=(const gbDropUnit& other);
};

/* ======== gbDropGroup ======== */

// sizeof = 0x50 = 80 bytes (verified from IDA constructor)
// Layout: vtable + 19 DWORDs
class gbDropGroup {
public:
    // vtable at +0x00
    int field_04;                // +0x04: unused (not initialized, not copied)
    int maxUnits;                // +0x08
    int numActiveUnits;          // +0x0C
    gbDropDesc desc;             // +0x10 (9 DWORDs = 0x24 bytes, ends at +0x34)
    int field_34;                // +0x34: padding/unused (skipped in copy ctor)
    double elapsedTime;          // +0x38: last render time (double, 8 bytes)
    float spawnTimer;            // +0x40
    gbDropUnit* units;           // +0x44
    gbTexture* pTexture;         // +0x48
    gbRenderEffect* pRenderEffect; // +0x4C

    gbDropGroup(void);
    gbDropGroup(int maxDrops, const gbDropDesc* dropDesc, const char* texName);
    gbDropGroup(const gbDropGroup& other);
    virtual ~gbDropGroup(void);

    virtual void Update(float deltaTime) = 0;
    virtual void Draw(void) = 0;

    void Render(gbCamera* camera);
    gbDropGroup& operator=(const gbDropGroup& other);

private:
    void CreateUnit(float deltaTime, gbCamera* camera);

    friend class gbRain;
    friend class gbSnow;
};

/* ======== gbRain ======== */

class GBAPI gbRain : public gbDropGroup {
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

class GBAPI gbSnow : public gbDropGroup {
public:
    float swayAmplitude;         // +0x50 (IDA: this[20])

    gbSnow(int maxDrops, const gbDropDesc* dropDesc, const char* texName, float amplitude);
    gbSnow(const gbSnow& other);
    virtual ~gbSnow(void);

    gbSnow& operator=(const gbSnow& other);

private:
    virtual void Update(float deltaTime);
    virtual void Draw(void);
};
