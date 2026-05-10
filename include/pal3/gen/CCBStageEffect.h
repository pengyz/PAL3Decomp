#pragma once
// Auto-generated: CCBStageEffect

#include "gbVolModNode.h"
#include "tagEffLinker.h"

class CCBStage;
class CCBSystem;

class CCBStageEffect {
public:
    double m_DeltaTime; // +0x0
    CCBStage * m_pStage; // +0x8
    CCBSystem * m_pCBSystem; // +0xC
    gbVolModNode m_EnvLight; // +0x10
    gbVolModNode m_Light[10]; // +0xEC
    gbRenderEffect * m_pGeomFlashEffect; // +0x984
    gbRenderEffect * m_pGeomFlashEffect_t; // +0x988
    tagEffLinker m_Linker[384]; // +0x98C
    // total size: 0x6390 (25488)

    CCBStageEffect(); // 0x00508E30
    ~CCBStageEffect(); // 0x00508F30
    static int Create(); // 0x00509050
    static int Destroy(); // 0x00509060
    static void Init(); // 0x00509070
    static void GetLinkerIndex(); // 0x00509080
    static int PreLoadEffGroup(); // 0x00509090
    static int LoadLinker(); // 0x005090E0
};
