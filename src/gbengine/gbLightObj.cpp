/**
 * gbengine.dll - gbLightObj
 * Light object for scene graph
 */

#include "gbengine/gbSceneGraph.h"
#include <string.h>
#include <math.h>

gbLightObj::gbLightObj(void) {
    /* STUB */
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
    /* STUB */
    memcpy(this, &other, sizeof(gbLightObj));
}

gbLightObj::~gbLightObj(void) {
    /* STUB */
}

gbLightObj& gbLightObj::operator=(const gbLightObj& other) {
    /* STUB */
    if (this != &other) {
        memcpy(this, &other, sizeof(gbLightObj));
    }
    return *this;
}

void gbLightObj::Init(enum LIGHT_TYPE type) {
    /* STUB */
    lightType = type;
    enabled = 1;
    ComputeBoundSphere();
}

void gbLightObj::ComputeBoundSphere(void) {
    /* STUB */
    boundingSphere.center = position;
    boundingSphere.radius = range;
}

int gbLightObj::GetType(void) {
    /* STUB */
    return lightType;
}

const gbSphere* gbLightObj::GetBoundSphere(void) {
    /* STUB */
    return &boundingSphere;
}

gbLight* gbLightObj::GetSysLight(void) {
    /* STUB */
    return &sysLight;
}
