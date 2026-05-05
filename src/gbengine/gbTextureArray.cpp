/**
 * gbengine.dll - gbTextureArray
 * Texture array container (up to 8 textures for multi-texturing)
 */

#include "gbengine/gbTexture.h"
#include <string.h>

gbTextureArray::gbTextureArray(void) {
    memset(textures, 0, sizeof(textures));
    numTextures = 0;
}

gbTextureArray::gbTextureArray(gbTexture* tex0) {
    memset(textures, 0, sizeof(textures));
    textures[0] = tex0;
    numTextures = tex0 ? 1 : 0;
}

gbTextureArray::gbTextureArray(gbTexture* tex0, gbTexture* tex1) {
    memset(textures, 0, sizeof(textures));
    textures[0] = tex0;
    textures[1] = tex1;
    numTextures = 0;
    if (tex0) numTextures++;
    if (tex1) numTextures++;
}

gbTextureArray& gbTextureArray::operator=(const gbTextureArray& other) {
    if (this != &other) {
        memcpy(this, &other, sizeof(gbTextureArray));
    }
    return *this;
}

void gbTextureArray::SetTexture(gbTexture* tex) {
    if (tex) {
        textures[0] = tex;
        numTextures = 1;
    } else {
        memset(textures, 0, sizeof(textures));
        numTextures = 0;
    }
}
