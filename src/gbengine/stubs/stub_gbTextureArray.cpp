#include "gbengine/gbTexture.h"
#include "gbengine/gbengine_types.h"
#pragma optimize("", off)

gbTextureArray::gbTextureArray(gbTexture * p1) {}

gbTextureArray::gbTextureArray(gbTexture * p1, gbTexture * p2) {}

gbTextureArray::gbTextureArray() {}

gbTextureArray & gbTextureArray::operator=(gbTextureArray const & p1) { static gbTextureArray _d; return _d; }

void gbTextureArray::SetTexture(gbTexture * p1) { }

