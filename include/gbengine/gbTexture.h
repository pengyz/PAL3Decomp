#pragma once

#include "gbengine/gbengine_types.h"
#include <d3d9.h>

// Forward declarations
class gbResManager;

// ============================================================================
// gbRefObject - reference-counted base
// ============================================================================
class gbRefObject {
public:
    int refCount;       // +0x04 (vtable at +0x00)

    gbRefObject();
    gbRefObject(const gbRefObject& other);
    virtual ~gbRefObject();

    void IncRef();
    void DecRef();
    int GetRef();
    void Release();
    gbRefObject& operator=(const gbRefObject& other);
};


// ============================================================================
// gbResource - managed resource base (inherits gbRefObject)
// ============================================================================
class gbResource : public gbRefObject {
public:
    char* name;             // +0x08
    unsigned int nameCrc;   // +0x0C
    int isLoaded;           // +0x10
    gbResManager* manager;  // +0x14

    gbResource();
    gbResource(const gbResource& other);
    virtual ~gbResource();

    void SetName(const char* name);
    const char* GetName();
    unsigned int GetNameCrc32();
    gbResource& operator=(const gbResource& other);
};


// ============================================================================
// gbImage2DInfo
// ============================================================================
struct gbImage2DInfo {
    int isdiskinfo;
    int goal;
    int ngrade;
    int detail[8];
    int wdiv[8];
    int hdiv[8];
    int wrap_u;
    int wrap_v;
    int mipmap;
    int minfilter;
    int magfilter;

    // 0x1001e470 (22B)
    int IsPreferAlpha(void);

    // Exported: operator=
    gbImage2DInfo& operator=(const gbImage2DInfo& other);
};


// ============================================================================
// gbImage2D - 2D bitmap image
// ============================================================================
class gbImage2D {
public:
    gbImage2DInfo ImgInfo;
    int Width;
    int Height;
    gbPixelFormat PixelFmt;
    int BitCount;
    char* pBits;
    gbColorQuad* pPalette;
    int numPalEntry;
    gbColorQuad ColorKey;

    // 0x1001e3e0 (47B) - Constructor
    gbImage2D(void);

    // Destructor
    ~gbImage2D();

    // 0x1001ea30 (131B) - Create image buffer
    unsigned char* CreateImage(int w, int h, int bpp);

    // Exported: GetBitCount
    int GetBitCount(void);

    // 0x10004150 (44B) - Get pointer to pixel at (x, y)
    unsigned char* GetBits(int x, int y);

    // Exported: GetBits(void) - get raw bits pointer
    unsigned char* GetBits(void);

    // Exported: GetHeight
    int GetHeight(void);

    // Exported: GetWidth
    int GetWidth(void);

    // 0x10004180 (16B) - Get palette entry
    gbColorQuad* GetPalEntry(int index);

    // 0x1001e490 (1262B) - Load image file using D3DX
    int LoadImageFile(char* filename, int flags);

    // 0x1001e980 (162B) - Scale image to new dimensions
    void ScaleTo(int newW, int newH);

    // 0x1001efc0 (224B) - Write TGA image
    void WriteTGAImage(char* filename);

    // 0x1001f5f0 (193B) - Write JPEG image
    void WriteJpegImage(char* filename, int quality);

    // 0x1001f6c0 (265B) - Write JPEG to memory buffer
    int WriteJpegToBuffer(unsigned char* buffer, int bufSize);

    // Exported: Release
    void Release(void);

    // Exported: GetPixelFmtType
    gbPixelFmtType GetPixelFmtType(void);

    // Exported: GetImgInfo
    gbImage2DInfo* GetImgInfo(void);

    // Private loader methods (0x1001EAC0, 0x1001EB80, 0x1001ED50, 0x1001F0A0, 0x1001F410)
    void ConvertPaletteToRGB24(void);
    int LoadBMPFile(char* filename);
    int LoadTGAFile(char* filename);
    int LoadPCXFile(char* filename);
    int LoadJPEGFile(char* filename);
};


// ============================================================================
// gbTexture - base texture class (virtual)
// ============================================================================
class gbTexture : public gbResource {
public:

    // gbTexture own fields
    gbGfxManager* pGfxMgr;  // +0 union with vfptr/gbResource fields
    int Width;
    int Height;
    gbImage2D* pTexImage;
    gbPixelFormat InFmt;
    int nLevels;

    // 0x10020370 (37B) - Constructor
    gbTexture(void);

    // Virtual destructor
    virtual ~gbTexture();

    // 0x10004190 (12B) - Check if texture is initialized
    int IsInit(void);

    // 0x10020760 (102B) - Create empty texture
    void CreateTexture(int w, int h, gbPixelFmtType fmt, int mips);

    // Get the D3D texture interface (base returns NULL, overridden in D3D subclass)
    virtual IDirect3DTexture9* GetTexture(void);

    // Exported: GetHeight
    int GetHeight(void);

    // Exported: GetWidth
    int GetWidth(void);

    // 0x10020430 (85B) - Get internal D3D format from image
    gbPixelFmtType GetInternalFormat(gbImage2D* img);

    // 0x100207d0 (15B) - Get raw bits pointer
    unsigned char* GetBits(void);

    // 0x100207e0 (53B) - Get pixel channel value at (x, y)
    unsigned char GetPixelChannel(int x, int y, int channel);

    // Exported: GetLevels
    int GetLevels(void);

    // 0x10020490 (269B) - Load texture data from gbImage2D
    void LoadFromImage2D(gbImage2D* img);

    // 0x100205a0 (443B) - Load texture from resource index
    void LoadTexture(int resIndex);

    // Virtual: update texture data (overridden in gbTexture_D3D)
    virtual void UpdateTexture(int x, int y, int w, int h, gbPixelFmtType srcFmt, void* data);

    // 0x10020820 (52B) - Update texture sub-region from image
    void UpdateTexture(int x, int y, gbImage2D* img);

    // 0x10020860 (40B) - Update entire texture from image
    void UpdateTexture(gbImage2D* img);
};


// ============================================================================
// gbTexture_D3D - Direct3D 9 texture implementation
// ============================================================================
class gbTexture_D3D : public gbTexture {
public:
    IDirect3DBaseTexture9* pTex;
    IDirect3DSurface9* pDS;
    ULONG m_ImgFormat;

    // 0x1001ba60 (29B) - Constructor
    gbTexture_D3D(void);

    // 0x1001baa0 - Virtual destructor: release D3D resources
    virtual ~gbTexture_D3D();

    // Override: return the D3D texture pointer
    virtual IDirect3DTexture9* GetTexture(void);

    // 0x1001bea0 (219B) - Override: update existing texture with new data
    virtual void UpdateTexture(int x, int y, int w, int h, gbPixelFmtType srcFmt, void* data);

    // 0x1001bd30 (356B) - Create texture from raw memory data
    virtual void CreateFromMemory(int w, int h, gbPixelFmtType srcFmt, int levels,
                          gbPixelFmtType dstFmt, void* data);

    // 0x1001c010 (344B) - Create texture from file data in memory (e.g. DDS, BMP, TGA)
    virtual void CreateFromFileMemory(void* data, int size);

    // 0x1001bf80 (144B) - Create texture for use as render target
    virtual int CreateForRenderTarget(int w, int h, gbPixelFmtType fmt);

    // 0x1001c170 (144B) - Get a byte from locked texture data
    unsigned char GetByte(int x, int y);

    // Exported: GetTexName
    IDirect3DBaseTexture9* GetTexName(void);

    // Exported: GetMiscTexName
    IDirect3DSurface9* GetMiscTexName(void);
};


// ============================================================================
// gbTextureArray - holds up to 16 texture pointers for multi-texturing
// sizeof = 68 bytes (16 pointers + 1 int count)
// Layout (IDA-verified): pTex[0..15] at [0..15], numTextures at [16]
// ============================================================================
struct gbTextureArray {
    gbTexture* pTexPt[16];  // +0x00 [0..15]: texture pointers (PDB name)
    int nTex;               // +0x40 [16]: active texture count (PDB name)

    gbTextureArray(void);
    gbTextureArray(gbTexture* tex0);
    gbTextureArray(gbTexture* tex0, gbTexture* tex1);
    void SetTexture(gbTexture* tex);
    gbTextureArray& operator=(const gbTextureArray& other);
};
