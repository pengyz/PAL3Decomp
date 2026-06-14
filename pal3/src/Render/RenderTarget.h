#pragma once
// Auto-generated: RenderTarget

#include "gbengine/gbParticle.h"
#include "gbengine/gbParticle.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"
#include "gbengine/gbVFileSystem.h"

class RenderTarget {
public:
    // vtable (7 methods, order matches binary layout)

    int m_iMode; // +0x0
    gbTexture_D3D * m_Texture; // +0x4
    int m_nRenderX; // +0x8
    int m_nRenderY; // +0xC
    int m_nHalfW; // +0x10
    BYTE m_nHalfH; // +0x14
    char _gap_015[3]; // +0x15
    int m_nHalfWidth; // +0x18
    int m_nHalfHeight; // +0x1C
    int m_nWidth; // +0x20
    int m_nHeight; // +0x24
    BYTE _field_028; // +0x28
    char _gap_029[3]; // +0x29
    float _field_02C; // +0x2C
    float m_fX; // +0x30
    float m_fY; // +0x34
    int _field_038; // +0x38
    int _field_03C; // +0x3C
    float m_fileHeader; // +0x40
    float m_fRenderX; // +0x44
    float m_fRenderY; // +0x48
    float m_fileData; // +0x4C
    float m_fFileParam; // +0x50
    int m_nColor; // +0x54
    int m_szPath; // +0x58
    int m_nDefaultH; // +0x5C
    char _gap_060[4]; // +0x60
    gbTexture_D3D * m_ScreenPlane; // +0x64
    char _gap_068[20]; // +0x68
    int m_nAlpha; // +0x7C
    int m_bVisible; // +0x80
    float m_fRenderIntensity; // +0x84
    float m_fOffsetParam; // +0x88
    float m_fRender; // +0x8C
    int m_nOffsetX; // +0x90
    int m_nOffsetY; // +0x94
    int m_nScaleX; // +0x98
    int m_nScaleY; // +0x9C
    char m_szTexPath[16]; // +0xA0
    float m_fInvScale; // +0xB0
    char _gap_0B4[4]; // +0xB4
    int m_nDeviceLost; // +0xB8
    int _todo_BC; // +0xBC
    char _gap_0C0[4]; // +0xC0
    int m_nState; // +0xC4
    // total size: 0xC8 (200)

    virtual ~RenderTarget() {}

    virtual int OnRender(); // 0x0048F3A0
    int InitParticleRenders(); // 0x0047A400
    int InitChildPanels(); // 0x004867F0
    int * Init(); // 0x00486CE0
    void InitNPCPanel(); // 0x004870C0
    void SetVisible(BOOL bVisible); // 0x004B4820
    void SetField084(); // 0x004B4840
    void SetColor(unsigned __int8 r, unsigned __int8 g, unsigned __int8 b); // 0x004B4850
    void SetAlpha(unsigned __int8 nAlpha); // 0x004B48B0
    void SetSize(int nHeight); // 0x004B48E0
    void SetState(); // 0x004B4910
    gbVFileSystem * LoadTexture(const char *szFilename); // 0x004B4920
    void UpdateTransform(float fX, float fY); // 0x004B49C0
    void CalcRenderDimensions(int nVal, int nVal2); // 0x004B4B10
    void Render(int nY, int nWidth, int nHeight); // 0x004B4C60
    void SetOffset(int nOffY); // 0x004B4D80
    void SetScale(int nScaleY); // 0x004B4DA0
    void ReadVFile(struct gbVFile *pFile); // 0x004BB050
    int ClearTexture(); // 0x004BB0B0
    int ApplyScale(float fVal); // 0x004BB0F0
    int fn_4BB180(int nVal); // 0x004BB180
    void ScreenToLocal(float *pOutX, float *pInX, float *pInY); // 0x004BB200
    void LoadFromFile(gbVFile *pFile); // 0x004BB260
    void UpdateTimeStep(); // 0x004BC7B0
    int RenderToTexture(); // 0x004BC8A0
    char LoadParticleTextures(const char *pszName); // 0x004BD6C0
    void GetManagedTexture(); // 0x004BD870
    gbParticleEffect * CreateParticleEffect(int nVal); // 0x004BD880
    struct gbParticleGroup * UpdateParticleEffect(int nVal); // 0x004BD900
    int Stop(int nVal); // 0x004BD950
    int ReleaseDefault(); // 0x004BD970
    void SetPathMode(int nVal); // 0x004BD990
    int SetDefaultParams(int nVal); // 0x004BD9C0
    RenderTarget(); // 0x004BDAC0
    void Create(); // 0x004BDB60
    void OnDeviceLost(int nVal); // 0x004BDC10
    bool OnResetDevice(int nVal); // 0x004BDC40
    int RenderToScreen(); // 0x004BDD90
    gbTexture * GetActiveTexture(); // 0x004BDEB0
    int * Destroy(); // 0x004BDF10
    int ResetHorizontal(); // 0x004BE8D0
    RenderTarget * ResetVertical(); // 0x004BEA60
    RenderTarget * ResetVertical2(); // 0x004BEBB0
    RenderTarget * ResetBase(); // 0x004BED00
};
