#pragma once

#include "gbengine/gbengine_types.h"
#include <d3d9.h>

// Forward declarations
class gbGfxManager;
class gbTexture;
struct ID3DXEffect;
struct gbVertexElement;

// ============================================================================
// GBPARAMHANDLE enum
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
// ============================================================================
class gbRenderEffect {
    // Private constructor: only gbEffectMgr can create these
    friend class gbEffectMgr;

private:
    ID3DXEffect* m_pEffect;
    unsigned int m_nPasses;
    unsigned int m_dwFlags;
    D3DVERTEXELEMENT9* m_pDecl;
    int m_nTechnique;

    // 0x1001cef0 (139B) - Private constructor from effect and flags
    gbRenderEffect(ID3DXEffect* pEffect, unsigned int flags);

    // Private virtual destructor
    virtual ~gbRenderEffect();

public:
    // 0x10004bf0 (92B) - Copy constructor
    gbRenderEffect(const gbRenderEffect& other);

    // operator=
    gbRenderEffect& operator=(const gbRenderEffect& other);

    // 0x10004be0 (10B) - Set vertex declaration handle
    void SetDeclHandle(IDirect3DVertexDeclaration9* decl);

    // 0x1001cfe0 (32B) - Compare two effects for sorting
    int Compare(gbRenderEffect* other);

    // 0x1001d000 (119B) - Validate the effect
    int Validate(void);

    // 0x1001d080 (26B) - Begin rendering with this effect
    int Begin(void);

    // 0x1001d0a0 (52B) - Set a pass
    void Pass(int passIndex);

    // 0x1001d0e0 (20B) - End rendering with this effect
    void End(void);

    // 0x1001d100 (72B) - Apply current effect state (commit changes)
    void Apply(void);

    // Get/Set variant by GBPARAMHANDLE enum
    void GetVariant(enum GBPARAMHANDLE handle, void* pValue);
    void SetVariant(enum GBPARAMHANDLE handle, void* pValue);

    // Get/Set variant by name
    void GetVariant(char* name, void* pValue);
    void SetVariant(char* name, void* pValue);

    // Exported: GetD3DEffect
    ID3DXEffect* GetD3DEffect(void);

    // Exported: GetFlag
    unsigned int GetFlag(void);
};


// ============================================================================
// gbEffectMgr - manages creation and caching of render effects
// ============================================================================
class gbEffectMgr {
public:
    gbGfxManager* m_pGfxMgr;
    gbTexture* m_pWhiteTexture;
    gbTexture* m_pGrayTexture;
    gbRenderEffect** m_pEffects;    // array of effect pointers
    int m_nMaxEffects;
    int m_nNumEffects;
    void** m_pVertDecls;            // registered vertex declarations
    int m_nMaxDecls;
    int m_nNumDecls;
    int m_bInitialized;

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
