/**
 * gbengine.dll - gbLightObj
 * Light object for scene graph
 */

#include "gbengine/gbSceneGraph.h"
#include <string.h>
#include <math.h>

gbLightObj::gbLightObj(void) {
    lightType = LIGHT_POINT;
    diffuse.r = diffuse.g = diffuse.b = diffuse.a = 1.0f;
    ambient.r = ambient.g = ambient.b = ambient.a = 0.0f;
    enabled = 0;
    _field30 = 0;
    _field34 = 0;
    _field38 = 0;
    _field3C = 0;
    range = 1000.0f;
    _field44 = 0.0f;
    _field48 = 0.0f;
    attenuation0 = 1.0f;
    attenuation1 = 0.0f;
    attenuation2 = 0.0f;
    _field58 = 0.0f;

    memset(&boundSphere, 0, sizeof(boundSphere));
    memset(&sysLight, 0, sizeof(sysLight));
    bDirty = 0;
}

gbLightObj::gbLightObj(const gbLightObj& other) {
    int* dst = (int*)this;
    const int* src = (const int*)&other;
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
    dst[20] = src[20];
    dst[21] = src[21];
    dst[22] = src[22];
    dst[23] = src[23];
    dst[24] = src[24];
    dst[25] = src[25];
    dst[26] = src[26];
    memcpy((char*)this + 108, (char*)&other + 108, 0x6C);
}

gbLightObj::~gbLightObj(void) {
}

gbLightObj& gbLightObj::operator=(const gbLightObj& other) {
    lightType = other.lightType;
    diffuse.r = other.diffuse.r;
    diffuse.g = other.diffuse.g;
    diffuse.b = other.diffuse.b;
    diffuse.a = other.diffuse.a;
    ambient.r = other.ambient.r;
    ambient.g = other.ambient.g;
    ambient.b = other.ambient.b;
    ambient.a = other.ambient.a;
    enabled = other.enabled;
    _field30 = other._field30;
    _field34 = other._field34;
    _field38 = other._field38;
    _field3C = other._field3C;
    range = other.range;
    _field44 = other._field44;
    _field48 = other._field48;
    attenuation0 = other.attenuation0;
    attenuation1 = other.attenuation1;
    attenuation2 = other.attenuation2;
    _field58 = other._field58;
    boundSphere.center.x = other.boundSphere.center.x;
    boundSphere.center.y = other.boundSphere.center.y;
    boundSphere.center.z = other.boundSphere.center.z;
    boundSphere.radius = other.boundSphere.radius;
    sysLight.type = other.sysLight.type;
    sysLight.diffuse.r = other.sysLight.diffuse.r;
    sysLight.diffuse.g = other.sysLight.diffuse.g;
    sysLight.diffuse.b = other.sysLight.diffuse.b;
    sysLight.diffuse.a = other.sysLight.diffuse.a;
    sysLight.specular.r = other.sysLight.specular.r;
    sysLight.specular.g = other.sysLight.specular.g;
    sysLight.specular.b = other.sysLight.specular.b;
    sysLight.specular.a = other.sysLight.specular.a;
    sysLight.ambient.r = other.sysLight.ambient.r;
    sysLight.ambient.g = other.sysLight.ambient.g;
    sysLight.ambient.b = other.sysLight.ambient.b;
    sysLight.ambient.a = other.sysLight.ambient.a;
    sysLight.position.x = other.sysLight.position.x;
    sysLight.position.y = other.sysLight.position.y;
    sysLight.position.z = other.sysLight.position.z;
    sysLight.direction.x = other.sysLight.direction.x;
    sysLight.direction.y = other.sysLight.direction.y;
    sysLight.direction.z = other.sysLight.direction.z;
    sysLight.range = other.sysLight.range;
    sysLight.falloff = other.sysLight.falloff;
    sysLight.attenuation0 = other.sysLight.attenuation0;
    sysLight.attenuation1 = other.sysLight.attenuation1;
    sysLight.attenuation2 = other.sysLight.attenuation2;
    sysLight.theta = other.sysLight.theta;
    sysLight.phi = other.sysLight.phi;
    bDirty = other.bDirty;
    return *this;
}

void gbLightObj::Init(enum LIGHT_TYPE lt) {
    float sqrtMax = (float)sqrt(3.402823466385289e38);
    lightType = lt;
    diffuse.a = 1.0f;
    diffuse.b = 1.0f;
    diffuse.g = 1.0f;
    diffuse.r = 1.0f;
    ambient.a = 0.0f;
    ambient.b = 0.0f;
    ambient.g = 0.0f;
    ambient.r = 0.0f;
    enabled = 1;
    _field30 = 1;
    _field38 = 0;
    _field34 = 0;
    _field44 = 0;
    _field48 = 1.0f;
    attenuation0 = 0;
    *(int*)((char*)this + 0x50) = 0x42B40000;
    *(int*)((char*)this + 0x54) = 0x42B60000;
    _field58 = 1.0f;
    *(float*)((char*)this + 0x40) = sqrtMax;
    *(float*)((char*)this + 0x3C) = sqrtMax;
    *(int*)((char*)this + 0x68) = 0;
    *(int*)((char*)this + 0x64) = 0;
    *(int*)((char*)this + 0x60) = 0;
    *(int*)((char*)this + 0x5C) = 0x7F7FFFFF;
    bDirty = 0;
}

void gbLightObj::ComputeBoundSphere(void) {
    boundSphere.radius = range;
    boundSphere.center.x = 0.0f;
    boundSphere.center.y = 0.0f;
    boundSphere.center.z = 0.0f;
}

int gbLightObj::GetType(void) {
    return 0;
}

const gbSphere* gbLightObj::GetBoundSphere(void) {
    return &boundSphere;
}

gbLight* gbLightObj::GetSysLight(void) {
    return (gbLight*)&sysLight;
}
