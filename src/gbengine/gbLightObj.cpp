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
    memcpy(this, &other, sizeof(gbLightObj));
}

gbLightObj::~gbLightObj(void) {
}

gbLightObj& gbLightObj::operator=(const gbLightObj& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbLightObj));
    }
    return *this;
}

void gbLightObj::Init(enum LIGHT_TYPE lt) {
    lightType = lt;
    enabled = 1;
    ComputeBoundSphere();
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
