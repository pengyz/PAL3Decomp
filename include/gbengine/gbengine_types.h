#pragma once

#include <windows.h>
#include <d3d9.h>

#ifdef GBENGINE_EXPORTS
#define GBAPI __declspec(dllexport)
#else
#define GBAPI __declspec(dllimport)
#endif

// Basic math types
struct gbVec2D {
    float x, y;
};

struct gbVec3D {
    float x, y, z;
};

struct gbVec4D {
    float x, y, z, w;
};

struct gbColorQuad {
    unsigned char b, g, r, a;
};

struct gbColorFlt {
    float r, g, b, a;
};

struct gbMatrix4 {
    float m[4][4];
};

struct gbRotMatrix {
    float m[3][3];
};

struct gbQuaternion {
    float x, y, z, w;
};

struct gbRay {
    gbVec3D origin;
    gbVec3D direction;
};

struct gbAABBox {
    gbVec3D vMin;
    gbVec3D vMax;
};

struct gbOBBox {
    gbVec3D center;
    gbVec3D axis[3];
    gbVec3D extent;
};

struct gbSphere {
    gbVec3D center;
    float radius;
};

struct gbPlane {
    gbVec3D normal;
    float d;
};

struct gbUIRect {
    float left, top, right, bottom;
};

struct gbPixelFormat {
    int format;
};

// Globals
extern double g_CurrentTime;
extern unsigned int g_CurrentTick;
