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

enum gbPixelFmtType {
    GB_PFT_UNKNOWN = 0,
    GB_PFT_R8G8B8 = 1,
    GB_PFT_A8R8G8B8 = 2,
    GB_PFT_R5G6B5 = 3,
    GB_PFT_A1R5G5B5 = 4,
    GB_PFT_A4R4G4B4 = 5,
    GB_PFT_P8 = 6,
    GB_PFT_A8 = 7,
    GB_PFT_X8R8G8B8 = 8,
    GB_PFT_X1R5G5B5 = 9,
    GB_PFT_X4R4G4B4 = 10
};

struct gbPixelFormat {
    gbPixelFmtType Type;
    int Bpp;
    gbColorQuad* Pal;
    unsigned int r_mask;
    unsigned int g_mask;
    unsigned int b_mask;
    unsigned int a_mask;
    unsigned int r_shift;
    unsigned int g_shift;
    unsigned int b_shift;
    unsigned int a_shift;
};

// Globals
extern double g_CurrentTime;
extern unsigned int g_CurrentTick;
