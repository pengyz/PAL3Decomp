/**
 * gbengine.dll - gbTextureArray
 * Texture array container (up to 16 textures for multi-texturing)
 */

#include "gbengine/gbTexture.h"
#include <string.h>

gbTextureArray::gbTextureArray(void) {
    nTex = 0;
}

gbTextureArray::gbTextureArray(gbTexture* tex0) {
    nTex = 1;
    pTexPt[0] = tex0;
}

gbTextureArray::gbTextureArray(gbTexture* tex0, gbTexture* tex1) {
    nTex = 2;
    pTexPt[0] = tex0;
    pTexPt[1] = tex1;
}

void gbTextureArray::SetTexture(gbTexture* tex) {
    nTex = 1;
    pTexPt[0] = tex;
}

gbTextureArray& gbTextureArray::operator=(const gbTextureArray& other) {
    memcpy(this, &other, sizeof(gbTextureArray));
    return *this;
}

