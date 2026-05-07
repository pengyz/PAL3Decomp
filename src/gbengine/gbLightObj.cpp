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
