#pragma once
// Auto-generated: TextureLib

#include "gbengine/gbTexture.h"

class TextureLib {
public:
    // vtable (2 methods, order matches binary layout)

    gbTexture * m_pResultTex; // +0x0
    char _gap_004[8]; // +0x4
    int m_szPathBuf; // +0xC
    char _gap_010[16]; // +0x10
    int m_nTextureId; // +0x20
    int m_szPath; // +0x24
    char _gap_028[8]; // +0x28
    float m_fTexCoordU; // +0x30
    float m_fTexCoordV; // +0x34
    char _gap_038[4]; // +0x38
    float m_fTexScale; // +0x3C
    BYTE m_bTexFilter; // +0x40
    char _gap_041[3]; // +0x41
    int m_nTexParam1; // +0x44
    int m_nTexParam2; // +0x48
    int m_nTexParam3; // +0x4C
    BYTE m_bTexClamp; // +0x50
    char _gap_051[46]; // +0x51
    BYTE m_bMipMap; // +0x7F
    BYTE m_bAlphaChannel; // +0x80
    char _gap_081[3]; // +0x81
    float m_fTexParam; // +0x84
    float m_fAngle; // +0x88
    float m_fColorModR; // +0x8C
    float m_fColorModG; // +0x90
    float m_fColorModB; // +0x94
    float m_fColorModA; // +0x98
    float m_fColorAdd; // +0x9C
    char _gap_0A0[24]; // +0xA0
    int m_nTexWidth; // +0xB8
    int m_nTexHeight; // +0xBC
    char _gap_0C0[12]; // +0xC0
    char m_Image[48]; // +0xCC
    int m_nImageOffset; // +0xFC
    int m_nImageSize; // +0x100
    char _gap_104[44]; // +0x104
    int m_nColorKey; // +0x130
    char _gap_134[24]; // +0x134
    int m_nStride; // +0x14C
    int m_nDataSize; // +0x150
    char _gap_154[4]; // +0x154
    int m_nTexFormat; // +0x158
    char _gap_15C[36]; // +0x15C
    int m_nBPP; // +0x180
    int m_nDataOffset; // +0x184
    char _gap_188[16]; // +0x188
    void * m_pPalette; // +0x198
    int m_nDataStart; // +0x19C
    int m_nDataEnd; // +0x1A0
    char _gap_1A4[4]; // +0x1A4
    BYTE m_bLoaded; // +0x1A8
    char _gap_1A9[35]; // +0x1A9
    int m_nPaletteSize; // +0x1CC
    char _gap_1D0[24]; // +0x1D0
    int m_nTexFlags; // +0x1E8
    char _gap_1EC[32]; // +0x1EC
    int m_szText; // +0x20C
    char * m_pTexture; // +0x210
    // total size: 0x214 (532)

    virtual char AddEntryFromConfig(char *lpString2, char *Delimiter); // 0x0053F680
    virtual int sub_53F5C0(void *Block, char a3); // 0x0053F5C0
    char LoadTexture(char *pszPath); // 0x004A6930
    gbTexture * CreateFromFile(); // 0x004A6960
    gbTexture * CreateFromMemory(_BYTE *pData, int nSize, char nFormat); // 0x004A6CA0
    int CheckEndKey(LPCSTR lpString1, LPCSTR lpString2); // 0x0053F500
    void ClearAndJump(); // 0x0053F550
    int * ClearGlobalVars(); // 0x0053F560
    void FreeTexture(); // 0x0053F5E0
    int ParseConfigFile(char *String); // 0x0053F610
    char * SetPath(char *path); // 0x0053F920
};
