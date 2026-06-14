#include "UIWnd.h"
#pragma once
// Auto-generated: UIScene

#include "gbengine/gbTexture.h"
#include "gbengine/gbVFileSystem.h"

class Parent_Data;
class PlayerItem;
class UICursor;
class UIWnd;

class UIScene : public UIWnd {
public:
    char _gap_000[68]; // +0x0
    int m_nViewW; // +0x44
    float m_fScaleY; // +0x48
    float m_fScaleX; // +0x4C
    BYTE _todo_050; // +0x50
    char _gap_051[3]; // +0x51
    int m_nScrollState; // +0x54
    int m_nScrollIdx; // +0x58
    int m_nShowState; // +0x5C
    UIWnd * m_pChildWnd; // +0x60
    int m_nClipX; // +0x64
    int m_nClipY; // +0x68
    int m_nRectX; // +0x6C
    int m_nRectY; // +0x70
    int m_nClipW; // +0x74
    int m_nRectH; // +0x78
    int m_nRectW; // +0x7C
    int m_nScrollWidget; // +0x80
    int m_nPosX; // +0x84
    int m_nPosY; // +0x88
    int m_nLoadResource; // +0x8C
    int m_nNotifyRender; // +0x90
    UINT m_dwColor; // +0x94
    int m_hScrollBar; // +0x98
    int m_nColors; // +0x9C
    int m_bLoadState; // +0xA0
    char * m_pChildData; // +0xA4
    float m_fAngle; // +0xA8
    float m_fCameraOffset; // +0xAC
    Parent_Data * m_bFieldCC; // +0xB0
    int m_nFieldD0; // +0xB4
    Parent_Data * m_bVisible; // +0xB8
    int m_hFont; // +0xBC
    Parent_Data * m_bEnabled; // +0xC0
    gbTexture * m_pTexture; // +0xC4
    BYTE m_bOverlayRender; // +0xC8
    BYTE _todo_0DD; // +0xC9
    char _gap_0CA[2]; // +0xCA
    BYTE m_bCursorLeft; // +0xCC
    char _gap_0CD[3]; // +0xCD
    int m_hTexture; // +0xD0
    char _tail_0D4[132]; // +0xD4
    // total size: 0x158 (344)

    virtual ~UIScene() {}

    virtual int Render_cdf0(); // 0x0043CDF0
    virtual BOOL CheckMouseHit(int nVal, int nVal2); // 0x0043D1A0
    virtual void ReleaseTexture(); // 0x0043BE80
    virtual gbVFileSystem * CreateScrollWidget(int id, int *p_DWORD, int parent, gbVFileSystem *pVFileSystem, char pData); // 0x0043C7B0
    int RenderVertexPool(); // 0x00419C20
    int NotifyRender(); // 0x00421A10
    int OverlayRender(int nVal); // 0x004220A0
    int CombatCheck(); // 0x004234D0
    static BOOL ProcessInput(char *String1, char *pszBuf); // 0x004235B0
    int SetController(int nVal); // 0x0043A4B0
    void LoadResource(void *path); // 0x0043A4C0
    gbVFileSystem * OpenAndLoadResource(BOOL bVisible, UIWnd *pWnd); // 0x0043A5D0
    int ResetState(); // 0x0043A660
    int SetColors(int nVal); // 0x0043A680
    static struct NameSys * GetSys(); // 0x0043A770
    virtual gbVFileSystem * CreateChildWidget(int id, void *pRect, gbVFileSystem *parent, const char *pszName, char pData, char pData2); // 0x0043A870
    virtual BOOL Update2(int nVal, int nVal2); // 0x0043AB20
    virtual void Render(); // 0x0043AD40
    unsigned __int8 SetupRenderClip(int nVal, unsigned int dwVal, unsigned int dwVal2, int nVal2); // 0x0043AFE0
    gbVFileSystem * CreateTextureWidget(int id, void *pRect, gbVFileSystem *parent, const char *pszName, char pData); // 0x0043B060
    BOOL Update(int nVal, int nVal2); // 0x0043B1E0
    unsigned __int8 GetChildWidget(unsigned int dwVal, unsigned int dwVal2, int nVal); // 0x0043B500
    virtual gbVFileSystem * CreateLabelWidget(int id, void *pRect, gbVFileSystem *parent, LPCSTR lpString, char pData); // 0x0043B570
    virtual int Render_b660(); // 0x0043B660
    virtual BOOL Update_b900(int nVal, int nVal2); // 0x0043B900
    int * ctor(); // 0x0043BCE0
    void SetTexture(LPCSTR lpString, char pData); // 0x0043BEB0
    void UpdateLayout(float fVal); // 0x0043C0F0
    int RefreshLayout(); // 0x0043C330
    static void fill(PlayerItem *a1, PlayerItem *a2, PlayerItem *a3); // 0x0043C9D0
    int ResizeContentAlt(int nVal); // 0x0043CBD0
    int GetChildCount(); // 0x0043FA00
    int GetChildAt(); // 0x0043FAE0
    void SetTextParam(); // 0x0043FBC0
    void SetFirstShow(); // 0x00442060
    int SetShow(int bShow); // 0x004427A0
    void SetState(); // 0x00445930
    unsigned __int8 GetPixelChannel(int nX, int nY, int nW, int nH); // 0x00445F80
    virtual void Render_dac0(); // 0x0044DAC0
    virtual int OnMessage(UICursor *msg, int wparam, int lparam); // 0x0044DFC0
    int SetParam(int nVal); // 0x00455190
    int RenderUI(); // 0x00459900
    void DestroyParent(); // 0x0045ADF0
    int LoadRoleSkillData(int nRoleIndex); // 0x004932D0
    char InitScriptScene(int nVal); // 0x00524230
    void LoadMapData(); // 0x0052E120
    int CalcViewTransform(int nVal); // 0x0052E140
    void UpdateAlpha(); // 0x00532D60
    int ClearColors(); // 0x00535AE0
    int ResetCameraOffset(); // 0x00535BA0
};
