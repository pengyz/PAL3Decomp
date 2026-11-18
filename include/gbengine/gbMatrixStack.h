#pragma once
// [重建 2026-11-18] gbengine内部类——注解known_members真值渲染
// (语料引用 pMatBuf×83/MaxVol×15/CurPos×3/ValidFlag 12 断链实证)
#include "gbengine/gbengine_types.h"

class gbMatrix4;

class gbMatrixStack {  // 内部类非导出(GBAPI会在fwd声明链上引发C2011)
public:
    gbMatrix4* pMatBuf;    // +0x0
    int MaxVol;            // +0x4
    int CurPos;            // +0x8
    int ValidFlag;         // +0xC
    // total size: 0x10 (16)
};
