// manual/pal3/core/CUtil.cpp - CUtil (migration from original)
// Source: CUtil::RenderFrameY (0x5236e0) + CUtil::RenderFrame (0x523670)
// Original game logic: game update + render dispatch (byte-identical target)

#include <windows.h>

// CUtil (migration from original)
class CUtil {
public:
    int m_nRenderMode;
    void *m_pScreenMode;
    void *m_pBattleSystem;
    void *m_pListView;
    void *m_pPropUI;

    int RenderFrameY(void *fTime, int nVal);
    int RenderFrame();
};

// RenderFrameY (0x5236e0 - game update - byte-identical target)
// Original: update dispatch by m_nRenderMode (scene/battle/list/prop/game)
int CUtil::RenderFrameY(void *fTime, int nVal) {
    // TODO: byte-identical migration (full function body from decomp)
    // Original logic (from decomp/CUtil_RenderFrameYPalScript_int_005236e0.json):
    //   if (g_nSceneState != 2 && (g_dwGameFlags & 1) != 0) { ... DetachAll3D ... }
    //   if (!UIParabolaCtrl_GetState(v7)) CUtil_Update(2);
    //   switch (m_nRenderMode) { case 0-6: dispatch ... }
    switch (this->m_nRenderMode) {
        case 0: return 1;  // SceneObj::Update
        case 1: return 1;  // CScreenMode update
        case 2: return 1;  // BattleSystem update
        case 3: return 1;  // ListView update
        case 4: return 1;  // PropUI update
        case 5: return 1;  // CGameData::Load
        case 6: return 1;  // CGameData::Load
        default: return 1;
    }
}

// RenderFrame (0x523670 - render dispatch - byte-identical target)
int CUtil::RenderFrame() {
    // TODO: byte-identical migration (full function body from decomp)
    switch (this->m_nRenderMode) {
        case 0: return 0;  // CCBControlWindow::Render
        case 1: return 0;  // CScreenMode render
        case 2: return 0;  // BattleSystem render
        case 3: return 0;  // ListView render
        case 4: return 0;  // PropUI render
        default: return 0;
    }
}
