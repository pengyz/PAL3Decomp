/**
 * gbengine.dll - gbLightObj
 * Light object for scene graph
 */

#include "gbengine/gbSceneGraph.h"
#include <string.h>
#include <math.h>

gbLightObj::gbLightObj(void) {
    m_LightType = LIGHT_POINT;
    m_Color.Red = m_Color.Green = m_Color.Blue = m_Color.Alpha = 1.0f;
    m_Ambient.Red = m_Ambient.Green = m_Ambient.Blue = m_Ambient.Alpha = 0.0f;
    m_UseDiffuse = 0;
    m_UseSpecular = 0;
    m_NearStart = 0;
    m_NearEnd = 0;
    m_FarStart = 0;
    m_FarEnd = 1000.0f;
    m_DecayType = 0.0f;
    m_DecayRadius = 0.0f;
    m_LightShape = 1.0f;
    m_HotSize = 0.0f;
    m_Falloff = 0.0f;
    m_Aspect = 0.0f;

    memset(&m_BoundSphere, 0, sizeof(m_BoundSphere));
    memset(&m_SysLight, 0, sizeof(m_SysLight));
    m_BakedLight = 0;
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
    m_LightType = other.m_LightType;
    m_Color.Red = other.m_Color.Red;
    m_Color.Green = other.m_Color.Green;
    m_Color.Blue = other.m_Color.Blue;
    m_Color.Alpha = other.m_Color.Alpha;
    m_Ambient.Red = other.m_Ambient.Red;
    m_Ambient.Green = other.m_Ambient.Green;
    m_Ambient.Blue = other.m_Ambient.Blue;
    m_Ambient.Alpha = other.m_Ambient.Alpha;
    m_UseDiffuse = other.m_UseDiffuse;
    m_UseSpecular = other.m_UseSpecular;
    m_NearStart = other.m_NearStart;
    m_NearEnd = other.m_NearEnd;
    m_FarStart = other.m_FarStart;
    m_FarEnd = other.m_FarEnd;
    m_DecayType = other.m_DecayType;
    m_DecayRadius = other.m_DecayRadius;
    m_LightShape = other.m_LightShape;
    m_HotSize = other.m_HotSize;
    m_Falloff = other.m_Falloff;
    m_Aspect = other.m_Aspect;
    m_BoundSphere.center.x = other.m_BoundSphere.center.x;
    m_BoundSphere.center.y = other.m_BoundSphere.center.y;
    m_BoundSphere.center.z = other.m_BoundSphere.center.z;
    m_BoundSphere.radius = other.m_BoundSphere.radius;
    m_SysLight.type = other.m_SysLight.type;
    m_SysLight.diffuse.Red = other.m_SysLight.diffuse.Red;
    m_SysLight.diffuse.Green = other.m_SysLight.diffuse.Green;
    m_SysLight.diffuse.Blue = other.m_SysLight.diffuse.Blue;
    m_SysLight.diffuse.Alpha = other.m_SysLight.diffuse.Alpha;
    m_SysLight.specular.Red = other.m_SysLight.specular.Red;
    m_SysLight.specular.Green = other.m_SysLight.specular.Green;
    m_SysLight.specular.Blue = other.m_SysLight.specular.Blue;
    m_SysLight.specular.Alpha = other.m_SysLight.specular.Alpha;
    m_SysLight.ambient.Red = other.m_SysLight.ambient.Red;
    m_SysLight.ambient.Green = other.m_SysLight.ambient.Green;
    m_SysLight.ambient.Blue = other.m_SysLight.ambient.Blue;
    m_SysLight.ambient.Alpha = other.m_SysLight.ambient.Alpha;
    m_SysLight.position.x = other.m_SysLight.position.x;
    m_SysLight.position.y = other.m_SysLight.position.y;
    m_SysLight.position.z = other.m_SysLight.position.z;
    m_SysLight.direction.x = other.m_SysLight.direction.x;
    m_SysLight.direction.y = other.m_SysLight.direction.y;
    m_SysLight.direction.z = other.m_SysLight.direction.z;
    m_SysLight.range = other.m_SysLight.range;
    m_SysLight.falloff = other.m_SysLight.falloff;
    m_SysLight.attenuation0 = other.m_SysLight.attenuation0;
    m_SysLight.attenuation1 = other.m_SysLight.attenuation1;
    m_SysLight.attenuation2 = other.m_SysLight.attenuation2;
    m_SysLight.theta = other.m_SysLight.theta;
    m_SysLight.phi = other.m_SysLight.phi;
    m_BakedLight = other.m_BakedLight;
    return *this;
}

void gbLightObj::Init(enum LIGHT_TYPE lt) {
    float sqrtMax = (float)sqrt(3.402823466385289e38);
    m_LightType = lt;
    m_Color.Alpha = 1.0f;
    m_Color.Blue = 1.0f;
    m_Color.Green = 1.0f;
    m_Color.Red = 1.0f;
    m_Ambient.Alpha = 0.0f;
    m_Ambient.Blue = 0.0f;
    m_Ambient.Green = 0.0f;
    m_Ambient.Red = 0.0f;
    m_UseDiffuse = 1;
    m_UseSpecular = 1;
    m_NearEnd = 0;
    m_NearStart = 0;
    m_DecayType = 0;
    m_DecayRadius = 1.0f;
    m_LightShape = 0;
    *(int*)((char*)this + 0x50) = 0x42B40000;
    *(int*)((char*)this + 0x54) = 0x42B60000;
    m_Aspect = 1.0f;
    *(float*)((char*)this + 0x40) = sqrtMax;
    *(float*)((char*)this + 0x3C) = sqrtMax;
    *(int*)((char*)this + 0x68) = 0;
    *(int*)((char*)this + 0x64) = 0;
    *(int*)((char*)this + 0x60) = 0;
    *(int*)((char*)this + 0x5C) = 0x7F7FFFFF;
    m_BakedLight = 0;
}

void gbLightObj::ComputeBoundSphere(void) {
    m_BoundSphere.radius = m_FarEnd;
    m_BoundSphere.center.x = 0.0f;
    m_BoundSphere.center.y = 0.0f;
    m_BoundSphere.center.z = 0.0f;
}

int gbLightObj::GetType(void) {
    return 0;
}

const gbSphere* gbLightObj::GetBoundSphere(void) {
    return &m_BoundSphere;
}

gbLight* gbLightObj::GetSysLight(void) {
    return (gbLight*)&m_SysLight;
}
