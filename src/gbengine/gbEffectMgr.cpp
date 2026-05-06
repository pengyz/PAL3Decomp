/**
 * gbengine.dll - gbEffectMgr
 * Effect manager for shader/render effect management
 */

#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbGfxManager.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include <stdlib.h>

extern gbVFileSystem* g_pVFileSys;

gbRenderEffect* gbEffectMgr::GetDefaultEffect(void) {
    if (m_nNumEffects > 0) {
        return m_pEffects[0];
    }
    return NULL;
}

