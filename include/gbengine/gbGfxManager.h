#pragma once
// gbGfxManager — 接口头文件（PAL3.exe 消费者使用）
// 完整类定义见 gbGfxManager_impl.h（仅供 gbengine.dll 内部参考）

#include "gbengine/gbengine_export.h"

struct gbGfxDriverInfo;
struct gbClearParam {
    unsigned int color;
    float depth;
    unsigned int stencil;
    unsigned int flags;
};
struct gbFogParam;
struct gbGfxCaps;
struct gbLight;
struct gbColorFlt;
struct gbMatrix4;

class gbCamera;
class gbSceneGraph;
class gbMatrixStack;
class gbBaseMesh;
class gbTexture;
class gbPrintFont;
class gbPrintFontMgr;
class gbResManager;
class gbVertPoolMgr;
class gbEffectMgr;

class GBAPI gbGfxManager {
public:
    virtual ~gbGfxManager();

    void SetClearParam(gbClearParam *);
    void SetCameraMatrix(const gbMatrix4 &, const gbMatrix4 &);
    void SetSceneGraph(gbSceneGraph *);
    int BeginScene(void);
    void SetFog(gbFogParam *);
    void SetAmbientLight(const gbColorFlt &);
    void SetLight(int, const gbLight *);
    unsigned int GetGraphWnd(void);
    unsigned int GetCurTick(void);
    double GetCurTime(void);
    double GetDeltaTime(void);
    gbMatrixStack *GetMatrixStack(int);
    gbPrintFont *GetPrintFont(int);
    gbResManager *GetResManager(void);
    gbSceneGraph *GetSceneGraph(void);
    gbCamera *GetCamera(void);
};

GBAPI gbGfxManager *__cdecl gbCreateGraphManager(gbGfxDriverInfo *);
