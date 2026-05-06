/**
 * gbengine.dll - gbTextureArray
 * Texture array container (up to 16 textures for multi-texturing)
 */

#include "gbengine/gbTexture.h"
#include <string.h>

gbTextureArray::gbTextureArray(void) {
    numTextures = 0;
}

gbTextureArray::gbTextureArray(gbTexture* tex0) {
    numTextures = 1;
    pTex[0] = tex0;
}

gbTextureArray::gbTextureArray(gbTexture* tex0, gbTexture* tex1) {
    numTextures = 2;
    pTex[0] = tex0;
    pTex[1] = tex1;
}

void gbTextureArray::SetTexture(gbTexture* tex) {
    numTextures = 1;
    pTex[0] = tex;
}

gbTextureArray& gbTextureArray::operator=(const gbTextureArray& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbTextureArray));
    }
    return *this;
}

