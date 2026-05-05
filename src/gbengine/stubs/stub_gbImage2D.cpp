#include "gbengine/gbGfxManager.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbImage2D::gbImage2D() {}

gbImage2D::~gbImage2D() {}

gbPixelFmtType gbImage2D::GetPixelFmtType() { return 0; }

int gbImage2D::GetBitCount() { return 0; }

int gbImage2D::GetHeight() { return 0; }

int gbImage2D::GetWidth() { return 0; }

int gbImage2D::LoadImageFile(char * p1, int p2) { return 0; }

int gbImage2D::WriteJpegToBuffer(unsigned char * p1, int p2) { return 0; }

gbColorQuad * gbImage2D::GetPalEntry(int p1) { return 0; }

gbImage2DInfo * gbImage2D::GetImgInfo() { return 0; }

unsigned char * gbImage2D::CreateImage(int p1, int p2, int p3) { return 0; }

unsigned char * gbImage2D::GetBits(int p1, int p2) { return 0; }

unsigned char * gbImage2D::GetBits() { return 0; }

void gbImage2D::Release() { }

void gbImage2D::ScaleTo(int p1, int p2) { }

void gbImage2D::WriteJpegImage(char * p1, int p2) { }

void gbImage2D::WriteTGAImage(char * p1) { }

