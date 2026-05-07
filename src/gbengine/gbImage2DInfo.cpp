/**
 * gbengine.dll - gbImage2DInfo
 * Image information helper class
 */

#include "gbengine/gbTexture.h"
#include <string.h>

gbImage2DInfo& gbImage2DInfo::operator=(const gbImage2DInfo& other) {
    memcpy(this, &other, 0x80);
    return *this;
}

