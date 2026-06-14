#pragma once
// Auto-generated: tagEffObjType

class tagEffObjType {
public:
    UINT dwClassNameCRC; // +0x0
    char szTypeName[30]; // +0x4
    char _gap_022[2]; // +0x22
    UINT dwTypeNameCRC; // +0x24
    char szTexture[128]; // +0x28
    int nFramePerRow; // +0xA8
    int nFramePerCol; // +0xAC
    int nFrame; // +0xB0
    float fFramePerSec; // +0xB4
    float fX; // +0xB8
    float fY; // +0xBC
    float fZ; // +0xC0
    float fStartYRot; // +0xC4
    float fSize; // +0xC8
    UINT dwColor; // +0xCC
    int nMaxQuad; // +0xD0
    BYTE bValid; // +0xD4
    BYTE bAdditiveBlend; // +0xD5
    BYTE bBillBoard; // +0xD6
    BYTE bNoZTest; // +0xD7
    float fStartXRot; // +0xD8
    float fStartZRot; // +0xDC
    float fSacleX; // +0xE0
    float fSacleY; // +0xE4
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
