#pragma once
// Auto-generated: CCBStageEffect

#include "gbengine/gbRenderEffect.h"
#include "gbengine/gbengine_internal.h"
#include "tagEffLinker.h"

class CCBStage;
class CCBSystem;

class CCBStageEffect {
public:
    double m_DeltaTime; // +0x0
    CCBStage * m_pStage; // +0x8
    CCBSystem * m_pCBSystem; // +0xC
    gbVolModNode m_EnvLight; // +0x10
    char _gap_014[216]; // +0x14
    gbVolModNode m_Light[10]; // +0xEC
    char _gap_114[2160]; // +0x114
    gbRenderEffect * m_pGeomFlashEffect; // +0x984
    gbRenderEffect * m_pGeomFlashEffect_t; // +0x988
    tagEffLinker m_Linker[4]; // +0x98C
    char _tail_99C[240]; // +0x99C
    // total size: 0xA8C (2700)

    CCBStageEffect(); // 0x00508E30
    void _CCBStageEffect(); // 0x00508F30
    bool Create(); // 0x00509050
    bool Destroy(); // 0x00509060
    void Init(); // 0x00509070
    void GetLinkerIndex(); // 0x00509080
    void PreLoadEffGroup(); // 0x00509090
    void LoadLinker(); // 0x005090E0
};
