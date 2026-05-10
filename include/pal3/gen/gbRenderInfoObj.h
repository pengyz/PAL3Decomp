#pragma once
// Auto-generated: gbRenderInfoObj

class gbTextureArray;
class gbVisNode;
class gbVolModNode;

class gbRenderInfoObj {
public:
    gbVisNode * pNode; // +0x0
    float Z; // +0x4
    unsigned int Param; // +0x8
    gbRenderEffect * pEffect; // +0xC
    gbTextureArray * pTexArray; // +0x10
    int Priority; // +0x14
    unsigned int Flags; // +0x18
    unsigned int EffectFlag; // +0x1C
    gbMatrix4 ViewMat; // +0x20
    gbVolModNode * pAllLight[2]; // +0x60
    gbVolModNode * pAllFog[2]; // +0x68
    // total size: 0x70 (112)

};
