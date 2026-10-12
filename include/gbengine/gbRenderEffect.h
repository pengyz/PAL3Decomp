#pragma once

#include "gbengine/gbengine_export.h"

#include "gbengine/gbengine_types.h"
#include <d3d9.h>
#include <d3dx9.h>

#include "gbengine/gbTexture.h"
#include "gbengine/gbResManager.h"

// Forward declarations (circular dep / no header)
class gbGfxManager;
struct gbVertexElement;

// ============================================================================
// GBPARAMHANDLE enum - indices into m_ParamHandle[]
// ============================================================================
enum GBPARAMHANDLE {
    GBPARAM_WORLDMATRIX = 0,
    GBPARAM_VIEWMATRIX = 1,
    GBPARAM_PROJMATRIX = 2,
    GBPARAM_TEXTURE0 = 3,
    GBPARAM_TEXTURE1 = 4,
    GBPARAM_COUNT = 5
};

// ============================================================================
// gbRenderEffect - wraps an ID3DXEffect for shader management
// Inherits gbResource: gbRefObject -> gbResource -> gbRenderEffect
// Layout (IDA-verified, sizeof = 68 bytes / 17 DWORDs):
//   [0] vtable           (gbRefObject)
//   [1] refCount         (gbRefObject)
//   [2] name             (gbResource)
//   [3] nameCrc          (gbResource)
//   [4] isLoaded         (gbResource)
//   [5] manager          (gbResource)
//   [6] m_pEffect        (ID3DXEffect*)
//   [7] m_dwFlags        (unsigned int)
//   [8] m_pDecl          (IDirect3DVertexDeclaration9*)
//   [9..16] m_ParamHandle[8] (D3DXHANDLE array)
// ============================================================================
// IDA-verified: inherits gbResource (which inherits gbRefObject)
class GBAPI gbRenderEffect : public gbResource {
public:
    friend class gbEffectMgr;

protected:
    ID3DXEffect* m_pEffect;                 // +0x18
    unsigned int m_dwFlags;                 // +0x1C
    IDirect3DVertexDeclaration9* m_pDecl;   // +0x20
public:
    // [T10] 访问级实证：PAL3::DefaultKeyMap@0x406B80 外部访问本参数块
    //（生成 PAL3.cpp:1345-1409 六站点 12 处 C2248；指令 0x406ba4/0x406bc9
    // `[reg-0x1]` 字节访问经 IDB 类型解析为 m_ParamHandle[7] HIBYTE）
    // ⇒ 原始声明必允许外部访问，protected 为重建误标。
    D3DXHANDLE m_ParamHandle[8];           // +0x24

private:
    gbRenderEffect(ID3DXEffect* pEffect, unsigned int flags);
    virtual ~gbRenderEffect();

public:
    gbRenderEffect(const gbRenderEffect& other);
    gbRenderEffect& operator=(const gbRenderEffect& other);

    void SetDeclHandle(IDirect3DVertexDeclaration9* decl);
    int Compare(gbRenderEffect* other);
    int Validate(void);
    int Begin(void);
    void Pass(int passIndex);
    void End(void);
    void Apply(void);

    void GetVariant(enum GBPARAMHANDLE handle, void* pValue);
    void SetVariant(enum GBPARAMHANDLE handle, void* pValue);
    void GetVariant(char* name, void* pValue);
    void SetVariant(char* name, void* pValue);

    ID3DXEffect* GetD3DEffect(void);
    unsigned int GetFlag(void);
};


// ============================================================================
// gbEffectMgr - manages creation and caching of render effects
// ============================================================================
struct gbVertFormatEntry {
    char name[28];                         // +0x00 (0x1C bytes)
    IDirect3DVertexDeclaration9* pDecl;    // +0x1C
    // sizeof = 0x20 = 32
};

class GBAPI gbEffectMgr : public gbResManager {
public:
    // Layout verified from IDA (Init, RegisterVertexFormat, GetRenderEffect)
    // Total sizeof ~ 0x828 bytes
    // Base class gbResManager provides: array (+0x00), capacity (+0x04), count (+0x08)
    gbGfxManager* m_pGfxMgr;       // +0x0C
    gbTexture* m_pWhiteTexture;     // +0x10
    gbTexture* m_pGrayTexture;      // +0x14
    gbRenderEffect* m_pDefEffect; // +0x18
    gbVertFormatEntry m_vertFormats[64]; // +0x1C (32*64=2048 bytes, to +0x81C)
    int m_nNumVertFormats;          // +0x81C [519]
    int m_nMaxVertFormats;          // +0x820 [520]
    int m_nFrameCounter;            // +0x824 [521]: cleared each BeginScene

    // 0x10004d20 (12B) - Default constructor
    gbEffectMgr(void);

    // 0x10004d30 (148B) - Copy constructor
    gbEffectMgr(const gbEffectMgr& other);

    // Destructor
    ~gbEffectMgr();

    // operator=
    gbEffectMgr& operator=(const gbEffectMgr& other);

    // 0x1001d1f0 (786B) - Initialize the effect manager
    void Init(gbGfxManager* gfxMgr);

    // 0x1001d510 (67B) - Release all managed effects
    void Release(void);

    // 0x1001d560 (50B) - Handle device lost
    int OnLostDevice(void);

    // 0x1001d5a0 (50B) - Handle device reset
    int OnResetDevice(void);

    // 0x1001d5e0 (232B) - Register a vertex format declaration
    IDirect3DVertexDeclaration9* RegisterVertexFormat(const char* name, gbVertexElement* pElements);

    // 0x1001d6d0 (353B) - Create a new render effect from a .gbf file
    gbRenderEffect* NewRenderEffect(const char* filename, unsigned int flags);

    // 0x1001d840 (107B) - Create a trivial (fixed-function emulation) effect
    gbRenderEffect* NewTrivalEffect(int type);

    // 0x1001d8b0 (39B) - Get effect by index
    gbRenderEffect* GetRenderEffect(unsigned int index);

    // Exported: GetDefaultEffect
    gbRenderEffect* GetDefaultEffect(void);

    // Exported: GetGrayTexture
    gbTexture* GetGrayTexture(void);

    // Exported: GetWhiteTexture
    gbTexture* GetWhiteTexture(void);
};
