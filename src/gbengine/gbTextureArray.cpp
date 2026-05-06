/**
 * gbengine.dll - gbTextureArray
 * Texture array container (up to 2 textures for multi-texturing)
 */

#include "gbengine/gbTexture.h"
#include <string.h>

gbTextureArray::gbTextureArray(gbTexture* tex0, gbTexture* tex1) {
    /* STUB */
    pTex[0] = tex0;
    pTex[1] = tex1;
}

gbTextureArray& gbTextureArray::operator=(const gbTextureArray& other) {
    if (this != &other) {
        pTex[0] = other.pTex[0];
        pTex[1] = other.pTex[1];
    }
    return *this;
}

