#pragma once
// CRenderTarget / CRenderTarget2 - render target management
// PDB source: D:\PAL3A\PAL3\effect\RenderTarget.cpp

class CRenderTarget {
public:
    int  m_iMode;
    char m_Texture[0x60];
    char m_ScreenPlane[0x60];
    int  m_nState;

    void Destroy(void);
};

struct IUnknown;

class CRenderTarget2 {
public:
    int       m_iMode;
    IUnknown *m_pSurface1;
    IUnknown *m_pSurface2;
    IUnknown *m_pSurface3;

    void Destroy(void);
};
