#pragma once
// Auto-generated: SceneMgr
// CEffMgr embedded at +0 (ends at +0xA930). SceneMgr-own fields from +0xA940. View B (PlayerSlots/RoleSystems) is reinterpret_cast overlay on EffClass+EffTable region.

#include "GeomNote.h"
#include "PlayerAtts.h"
#include "RoleSystem.h"
#include "SCENE_TYPE.h"
#include "SCNFile.h"
#include "Scene.h"
#include "SceneMapPlayer.h"
#include "SceneObjScript.h"

class CCBStageRole;
class CEffMgr;
class RenderTarget;
class gbCamera;
class gbGfxManager;
class gbRenderEffect;
class gbSceneGraph;

class SceneMgr {
public:
    SCENE_TYPE s_curscene; // +0x0
    Scene s_scene[3]; // +0x0
    SCNFile s_scnfile; // +0x0
    SceneObjScript m_objscript; // +0x0
    float m_fHurtTime; // +0x0
    SceneMapPlayer s_map[4]; // +0x0
    int m_specialvariable_m17water; // +0x0
    int m_specialvariable_m13unite; // +0x0
    GeomNote m_GeomNote[10]; // +0x0
    BYTE reverse[58]; // +0x0
    // total size: 0x1 (1)

    static int ResetPlayerAtts(); // 0x00408850
    static int InitSceneRoles(); // 0x0040CA40
    static int GetValidPartyCount(); // 0x0040FC70
    int RenderActiveRoles(); // 0x00421C00
    int * FindRoleByState(char nState); // 0x00422050
    static int ClearInactiveRoles(); // 0x00423500
    static int ResetSceneFlags(); // 0x004236B0
    void FormatStatusCaption(int nVal); // 0x00493E40
    SceneMgr * _scalar_dtor(void *Block, char pData); // 0x004CD930
    CEffMgr * Create(int gfxMgr, int cam, int nVal); // 0x004CDA10
    char RenderAll(); // 0x004CDBF0
    char RenderUpdate(); // 0x004CDC20
    int LoadMainUITexture(); // 0x00528D50
    int * GetCurrentNode(); // 0x0052EC90
};
