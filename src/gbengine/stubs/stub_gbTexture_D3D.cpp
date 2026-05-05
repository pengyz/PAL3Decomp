#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbTexture_D3D::gbTexture_D3D() {}

IDirect3DBaseTexture9 * gbTexture_D3D::GetTexName() { return 0; }

IDirect3DSurface9 * gbTexture_D3D::GetMiscTexName() { return 0; }

unsigned char gbTexture_D3D::GetByte(int p1, int p2) { return 0; }

gbTexture_D3D::~gbTexture_D3D() {}

int gbTexture_D3D::CreateForRenderTarget(int p1, int p2, gbPixelFmtType p3) { return 0; }

void gbTexture_D3D::CreateFromFileMemory(void * p1, int p2) { }

void gbTexture_D3D::CreateFromMemory(int p1, int p2, gbPixelFmtType p3, int p4, gbPixelFmtType p5, void * p6) { }

void gbTexture_D3D::UpdateTexture(int p1, int p2, int p3, int p4, gbPixelFmtType p5, void * p6) { }

