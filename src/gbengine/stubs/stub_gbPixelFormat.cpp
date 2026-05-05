#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbPixelFormat & gbPixelFormat::operator=(gbPixelFormat const & p1) { static gbPixelFormat _d; return _d; }

void gbPixelFormat::Convert(unsigned char * p1, gbPixelFormat * p2, unsigned char * p3, int p4) { }

void gbPixelFormat::Init(gbPixelFormat * p1) { }

void gbPixelFormat::Init(gbPixelFmtType p1) { }

void gbPixelFormat::Init(int p1, gbColorQuad * p2) { }

void gbPixelFormat::Init(int p1, unsigned int p2, unsigned int p3, unsigned int p4, unsigned int p5) { }

void gbPixelFormat::Release() { }

