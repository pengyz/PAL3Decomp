// ===== IDA parse prelude for gbengine headers =====
// 解决编译依赖：让 IDA 的 C 解析器能处理 gbengine 头文件
#ifndef GBAPI
#define GBAPI
#endif
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// Windows 基本类型
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned int UINT;
typedef int BOOL;
typedef int HRESULT;
typedef void* HWND;
typedef void* HANDLE;
typedef void* LPVOID;
typedef char CHAR;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int ULONG;
typedef long LONG;
typedef float FLOAT;
typedef unsigned long ULONG_PTR;
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;
// D3D9 前向声明（gbengine 头只引用指针）
struct IDirect3DDevice9;
struct IDirect3DTexture9;
struct IDirect3DSurface9;
struct IDirect3DBaseTexture9;
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
struct D3DXMATRIX;
struct D3DXVECTOR3;
struct D3DMATERIAL9;
struct D3DLIGHT9;
struct D3DVIEWPORT9;
struct D3DGAMMARAMP;
struct D3DCAPS9;
// gbengine 前向声明
struct gbRefObject;
struct gbResource;
struct gbVisNode;
struct gbSceneGraph;
struct gbCamera;
struct gbTexture;
struct gbImage2D;
struct gbMesh;
struct gbRenderEffect;
struct gbEffectMgr;
struct gbResManager;
struct gbPrintFontMgr;
struct gbVertPoolMgr;
struct gbMatrixStack;
struct gbGfxManager;
struct Console;
