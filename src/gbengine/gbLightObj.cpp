/**
 * gbengine.dll - gbLightObj
 * Light object for scene graph
 */

#include "gbengine/gbSceneGraph.h"
#include <string.h>
#include <math.h>

gbLightObj::gbLightObj(void) {
    memset(&position, 0, sizeof(position));
    memset(&direction, 0, sizeof(direction));
    direction.z = 1.0f;

    diffuse.r = diffuse.g = diffuse.b = diffuse.a = 1.0f;
    ambient.r = ambient.g = ambient.b = ambient.a = 0.0f;
    specular.r = specular.g = specular.b = specular.a = 1.0f;

    range = 1000.0f;
    attenuation0 = 1.0f;
    attenuation1 = 0.0f;
    attenuation2 = 0.0f;
    lightType = LIGHT_POINT;
    enabled = 0;

    memset(&boundingSphere, 0, sizeof(boundingSphere));
    memset(&sysLight, 0, sizeof(sysLight));
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

void gbLightObj::Init(enum LIGHT_TYPE type) {
    lightType = type;
    enabled = 1;
    ComputeBoundSphere();
}

void gbLightObj::ComputeBoundSphere(void) {
    boundingSphere.center = position;
    boundingSphere.radius = range;
}

float gbLightObj::GetEffectOnPoint(const gbVec3D& point, int useAttenuation) {
    if (!enabled) return 0.0f;

    float dx = point.x - position.x;
    float dy = point.y - position.y;
    float dz = point.z - position.z;
    float distance = sqrtf(dx * dx + dy * dy + dz * dz);

    if (distance > range) return 0.0f;

    if (useAttenuation) {
        float attenuation = attenuation0 + attenuation1 * distance + attenuation2 * distance * distance;
        if (attenuation < 0.001f) attenuation = 0.001f;
        return 1.0f / attenuation;
    }

    return 1.0f;
}

void gbLightObj::Compute(gbVolModNode* volmod) {
    // Update system light structure from light parameters
    /* UNCERTAIN: gbLight structure mapping to D3DLIGHT9 */
    ComputeBoundSphere();
}

int gbLightObj::GetType(void) {
    return lightType;
}

const gbSphere* gbLightObj::GetBoundSphere(void) {
    return &boundingSphere;
}

gbLight* gbLightObj::GetSysLight(void) {
    return &sysLight;
}
