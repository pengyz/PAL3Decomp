#pragma once
// Auto-generated: SceneMgr

#include "GeomNote.h"
#include "SCENE_TYPE.h"
#include "SCNFile.h"
#include "Scene.h"
#include "SceneMapPlayer.h"
#include "SceneObjScript.h"

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

    void * Create(gbGfxManager *gfxMgr, gbCamera *cam, gbSceneGraph *pRoot); // 0x004CDA10
    char RenderAll(); // 0x004CDBF0
    char RenderUpdate(); // 0x004CDC20
};
