#include "UIWnd.h"
#pragma once
// Auto-generated: UIStatic

#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"

class Parent_Data;
class _PlugInfo;

class UIStatic : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    gbTexture * pDebugTex; // +0x44
    int m_align; // +0x48
    float m_ratiow; // +0x4C
    float m_ratioh; // +0x50
    int m_textx; // +0x54
    int m_texty; // +0x58
    Parent_Data * m_fonttype; // +0x5C
    char m_text[16]; // +0x60
    gbTexture * m_pbk; // +0x70
    _PlugInfo * m_pbkInfo; // +0x74
    gbTexture * m_ppic; // +0x78
    _PlugInfo * m_ppicInfo; // +0x7C
    gbTexture * m_disablepic; // +0x80
    _PlugInfo * m_disablepicInfo; // +0x84
    gbTexture * m_pbk2; // +0x88
    BYTE m_mouseoff; // +0x8C
    char _gap_08D[3]; // +0x8D
    int m_FVF; // +0x90
    int m_nTextW; // +0x94
    // total size: 0x98 (152)

    virtual ~UIStatic() {}

    virtual void Render(); // 0x00440F30
    virtual BOOL Update(float deltatime, int haveinput); // 0x00440DD0
    virtual int OnMessage(); // 0x00440BA0
    virtual gbVFileSystem * CreateWithTextures(int id, void *pRect, gbVFileSystem *parent, const char *pszName, char pData); // 0x00440810
    virtual void Destroy(); // 0x0043D920
    void RenderQuadSlice(int *pnVal, int nVal); // 0x0043DAB0
    UIStatic(); // 0x00440740
    void _UIStatic(); // 0x004407C0
    void FormatText(); // 0x00440960
    gbVFileSystem * LoadResource(LPCSTR lpString, char nFlags); // 0x00440A20
    void LoadTexture(); // 0x00440AE0
    void SetText(); // 0x00440CE0
    void LoadTextureByName(LPCSTR lpString, char pData); // 0x00442480
    void CreateFromTemplate(); // 0x004426B0
    UIStatic * CtorWithFlag(); // 0x00442D00
    UIStatic * UIStatic_Base(); // 0x00443380
    virtual int GetUIElements(float fVal, int nVal); // 0x0044A820
    virtual void RenderText(); // 0x0044A870
    void RenderTile(int nVal, char pData); // 0x0044AA20
    void DestroyChainToBase(); // 0x0044BE60
    BOOL IsHidden(); // 0x004538D0
};
