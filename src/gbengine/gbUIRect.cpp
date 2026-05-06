#include "gbengine/gbengine_types.h"
#include "gbengine/gbGfxManager.h"
#include <string.h>

// gbUIRect - UI rectangle rendering

// Forward declaration
class gbTexture;

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
