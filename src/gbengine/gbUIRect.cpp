#include "gbengine/gbengine_types.h"
#include "gbengine/gbGfxManager.h"
#include <string.h>

// gbUIRect - UI rectangle rendering

// Forward declaration
class gbTexture;

gbUIRect& gbUIRect::operator=(const gbUIRect& other) {
    if (this != &other) {
        m_pTexture = other.m_pTexture;
        m_pGfx = other.m_pGfx;
        left = other.left;
        top = other.top;
        width = other.width;
        height = other.height;
    }
    return *this;
}

void gbUIRect::Init(char* textureName, float l, float t, float w, float h, gbGfxManager* gfx) {
    /* UNCERTAIN */
    // This should load the texture and initialize the rectangle
    // Actual implementation requires texture loading system
    m_pGfx = gfx;
    left = l;
    top = t;
    width = w;
    height = h;
    m_pTexture = NULL;

    // TODO: Load texture by name from resource manager
    // if (gfx && textureName) {
    //     m_pTexture = gfx->GetResManager()->LoadTexture(textureName);
    // }
}

void gbUIRect::Release() {
    // Release texture reference
    if (m_pTexture) {
        // TODO: Decrease reference count
        m_pTexture = NULL;
    }
    m_pGfx = NULL;
}

void gbUIRect::Render(int flags) {
    /* UNCERTAIN */
    // This should render the rectangle using the graphics manager
    // Actual implementation requires render system details

    if (!m_pGfx || !m_pTexture) {
        return;
    }

    // TODO: Render quad with texture
    // Typically involves:
    // 1. Set render states
    // 2. Set texture
    // 3. Draw screen-space quad with UV coordinates
    // 4. Restore render states
}
