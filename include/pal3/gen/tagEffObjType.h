#pragma once
// Auto-generated: tagEffObjType

class tagEffObjType {
public:
    unsigned long dwClassNameCRC; // +0x0
    char szTypeName[30]; // +0x4
    unsigned long dwTypeNameCRC; // +0x24
    char szTexture[128]; // +0x28
    char szParticleFileName[128]; // +0x28
    char szSoundNamePrefix[128]; // +0x28
    char szBinkNamePrefix[128]; // +0x28
    char szEffectIniFile[128]; // +0x28
    int nFramePerRow; // +0xA8
    int nFramePerCol; // +0xAC
    int nFrame; // +0xB0
    float fFramePerSec; // +0xB4
    float fX; // +0xB8
    float fY; // +0xBC
    float fZ; // +0xC0
    float fStartAngle; // +0xC4
    float fStartYRot; // +0xC4
    float fSize; // +0xC8
    unsigned long dwColor; // +0xCC
    int nMaxQuad; // +0xD0
    unsigned char bValid; // +0xD4
    unsigned char bAdditiveBlend; // +0xD5
    unsigned char bBillBoard; // +0xD6
    unsigned char bNoZTest; // +0xD7
    float fStartXRot; // +0xD8
    float fStartZRot; // +0xDC
    float fRotAngle; // +0xE0
    float fSacleX; // +0xE0
    float fWide; // +0xE4
    float fSacleY; // +0xE4
    float fDivision; // +0xE8
    float fSacleZ; // +0xE8
    float fTopShrink; // +0xEC
    float fBottomShrink; // +0xF0
    float fTopRadius; // +0xF4
    float fBottomRadius; // +0xF8
    float fTopRadiusIncSpeed; // +0xFC
    float fBottomRadiusIncSpeed; // +0x100
    float fTopRiseSpeed; // +0x104
    float fBottomRiseSpeed; // +0x108
    float fTextureRepeat; // +0x10C
    float fParam[2]; // +0x110
    // total size: 0x118 (280)

};
