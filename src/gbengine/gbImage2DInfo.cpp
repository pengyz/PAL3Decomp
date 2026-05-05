/**
 * gbengine.dll - gbImage2DInfo
 * Image information helper class
 */

#include "gbengine/gbTexture.h"
#include <string.h>

gbImage2DInfo& gbImage2DInfo::operator=(const gbImage2DInfo& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbImage2DInfo));
    }
    return *this;
}

int gbImage2DInfo::IsPreferAlpha(void) {
    // Check if this image prefers alpha channel (based on goal or mipmap settings)
    return (goal != 0) || (mipmap != 0);
}
