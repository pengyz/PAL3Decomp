#pragma once
/**
 * Auto-generated from gbengine.dll export table
 * 1019 exported functions
 *
 * NOTE: This is a reference file showing the DLL's API surface.
 * Parameter names are inferred and may not match original source.
 */

#ifndef GBENGINE_API_H
#define GBENGINE_API_H

#include "pal3_types.h"

// 42 methods
class gbCamera {
public:
    __thiscall gbCamera::gbCamera(class gbGfxManager *);  // 0x218D0
    void __thiscall gbCamera::AddControler(class gbCamControler *,double);  // 0x225F0
    unsigned int __thiscall gbCamera::ClipAABBox(struct gbVec3D *,struct gbVec3D *,unsigned int);  // 0x21C80
    int __thiscall gbCamera::ClipOBBox(struct gbOBBox *);  // 0x21D80
    int __thiscall gbCamera::ClipPoint(struct gbVec3D *);  // 0x21F00
    int __thiscall gbCamera::ClipSphere(struct gbVec3D *,float);  // 0x21F60
    float __thiscall gbCamera::GetAspect(void);  // 0x59B0
    class gbCamControler * __thiscall gbCamera::GetCurControl(void);  // 0x5A00
    float __thiscall gbCamera::GetFOV(void);  // 0x5990
    struct gbMatrix4 * __thiscall gbCamera::GetInvViewMatrix(void);  // 0x59F0
    float __thiscall gbCamera::GetOrthoSize(void);  // 0x59A0
    void __thiscall gbCamera::GetRayToScreen(float,float,struct gbRay *);  // 0x222C0
    struct gbMatrix4 * __thiscall gbCamera::GetViewMatrix(void);  // 0x59E0
    void __thiscall gbCamera::GetViewPort(float &,float &,float &,float &);  // 0x223D0
    void __thiscall gbCamera::GetViewSizeOnNearPlane(float &,float &);  // 0x21A10
    float __thiscall gbCamera::GetZFar(void);  // 0x5980
    float __thiscall gbCamera::GetZNear(void);  // 0x5970
    int __thiscall gbCamera::IsCurCtrlDefault(void);  // 0x5A10
    void __thiscall gbCamera::MoveInEyeDir(float);  // 0x22500
    void __thiscall gbCamera::OffsetZBuffer(double);  // 0x224B0
    void __thiscall gbCamera::PointDevToScr(int *,int *,float,float);  // 0x22440
    void __thiscall gbCamera::PointEyeToScr(struct gbVec3D *,struct gbVec3D *);  // 0x22170
    void __thiscall gbCamera::PointEyeToScr(struct gbVec3D *,float &,float &);  // 0x220B0
    void __thiscall gbCamera::PointEyetoWorld(struct gbVec3D *,struct gbVec3D *);  // 0x22250
    void __thiscall gbCamera::PointScrToEye(float,float,struct gbVec3D *);  // 0x22050
    void __thiscall gbCamera::PointScrToWorld(float,float,struct gbVec3D *);  // 0x21FC0
    void __thiscall gbCamera::PointWorld2Scr_NR(struct gbVec3D *,float &,float &);  // 0x22630
    void __thiscall gbCamera::PointWorldToEye(struct gbVec3D *,struct gbVec3D *);  // 0x22030
    void __thiscall gbCamera::PointWorldToScr(struct gbVec3D *,float &,float &);  // 0x22270
    void __thiscall gbCamera::RecoverZBuffer(void);  // 0x224E0
    void __thiscall gbCamera::RotateVector(struct gbVec3D *,struct gbVec3D *);  // 0x59C0
    void __thiscall gbCamera::RotateVector(struct gbVec3D *,struct gbVec3D *,enum gbAxis);  // 0x22490
    void __thiscall gbCamera::SetAsCurrent(int);  // 0x21A80
    void __thiscall gbCamera::SetDimention(int,int);  // 0x21C50
    void __thiscall gbCamera::SetEyeDir(struct gbQuaternion *);  // 0x5900
    void __thiscall gbCamera::SetEyeLoc(float,float,float);  // 0x58D0
    void __thiscall gbCamera::SetFOV(float);  // 0x5940
    void __thiscall gbCamera::SetLookAt(struct gbVec3D *,struct gbVec3D *,struct gbVec3D *);  // 0x21970
    void __thiscall gbCamera::SetOrthoSize(float);  // 0x5930
    void __thiscall gbCamera::SetZRange(float,float);  // 0x5950
    void __thiscall gbCamera::Update(double);  // 0x22590
    class gbCamera & __thiscall gbCamera::operator=(class gbCamera const &);  // 0x5A20
};

// 40 methods
class gbGfxManager {
public:
    __thiscall gbGfxManager::gbGfxManager(int &,struct gbGfxDriverInfo *);  // 0x1D910
    virtual __thiscall gbGfxManager::~gbGfxManager(void);  // 0x1DAA0
    virtual int __thiscall gbGfxManager::BeginScene(void);  // 0x1DB10
    int __thiscall gbGfxManager::ClipBoundVolume(struct gbAABBox *);  // 0x1E220
    void __thiscall gbGfxManager::EnableEmissive(int);  // 0x4FF0
    struct gbColorFlt __thiscall gbGfxManager::GetAmbientLight(void);  // 0x4FC0
    unsigned int __thiscall gbGfxManager::GetCurTick(void);  // 0x4F20
    double __thiscall gbGfxManager::GetCurTime(void);  // 0x4F10
    unsigned int __thiscall gbGfxManager::GetDeltaTick(void);  // 0x1DAF0
    double __thiscall gbGfxManager::GetDeltaTime(void);  // 0x1DAC0
    struct gbGfxDriverInfo const * __thiscall gbGfxManager::GetDriverInfo(void);  // 0x5E20
    class gbEffectMgr * __thiscall gbGfxManager::GetEffectMgr(void);  // 0x4EB0
    float __thiscall gbGfxManager::GetEmissiveFactor(void);  // 0x5030
    struct gbFogParam * __thiscall gbGfxManager::GetFog(void);  // 0x5040
    virtual int __thiscall gbGfxManager::GetGfxCaps(struct gbGfxCaps *);  // 0x3800
    unsigned int __thiscall gbGfxManager::GetGraphWnd(void);  // 0x39F0
    struct gbLight const * __thiscall gbGfxManager::GetLight(int)const;  // 0x4F50
    class gbMatrixStack * __thiscall gbGfxManager::GetMatrixStack(int);  // 0x4ED0
    class gbPrintFont * __thiscall gbGfxManager::GetPrintFont(enum gbFontType);  // 0x4EE0
    class gbPrintFontMgr * __thiscall gbGfxManager::GetPrintFontMgr(void);  // 0x4EF0
    class gbResManager * __thiscall gbGfxManager::GetResManager(void);  // 0x4F30
    class gbSceneGraph * __thiscall gbGfxManager::GetSceneGraph(void);  // 0x4F00
    struct gbGfxStatistic * __thiscall gbGfxManager::GetStatistic(void);  // 0x4F40
    void __thiscall gbGfxManager::GetTMMatrix(int,struct gbMatrix4 *);  // 0x1DF40
    class gbVertPoolMgr * __thiscall gbGfxManager::GetVertPoolMgr(void);  // 0x4EC0
    struct gbMatrix4 const & __thiscall gbGfxManager::GetViewMatrix(void);  // 0x1E370
    void __thiscall gbGfxManager::GetViewport(struct gbViewPort &);  // 0x1E070
    struct gbMatrix4 const & __thiscall gbGfxManager::GetWorldMatrix(void);  // 0x1E330
    void __thiscall gbGfxManager::IdentityWorldMatrix(void);  // 0x1E380
    int __thiscall gbGfxManager::IsLightEnable(int)const;  // 0x4F70
    int __thiscall gbGfxManager::IsWireMode(void);  // 0x4F80
    virtual class gbBaseMesh * __thiscall gbGfxManager::NewMesh(char const *,enum gbMeshType);  // 0x1E160
    void __thiscall gbGfxManager::OffsetZBuffer(int);  // 0x1E2C0
    void __thiscall gbGfxManager::SetAmbientLight(struct gbColorFlt const &);  // 0x4F90
    void __thiscall gbGfxManager::SetCameraMatrix(struct gbMatrix4 const &,struct gbMatrix4 const &);  // 0x1E3A0
    void __thiscall gbGfxManager::SetClearParam(struct gbClearParam *);  // 0x1E090
    void __thiscall gbGfxManager::SetEmissiveFactor(float);  // 0x5020
    virtual void __thiscall gbGfxManager::SetFog(struct gbFogParam *);  // 0x1E300
    void __thiscall gbGfxManager::SetSceneGraph(class gbSceneGraph *);  // 0x4EA0
    void __thiscall gbGfxManager::SetWireMode(int);  // 0x1E2F0
};

// 39 methods
class gbMatrix4 {
public:
    __thiscall gbMatrix4::gbMatrix4(void);  // 0x25110
    struct gbVec3D * __thiscall gbMatrix4::GetColumn(struct gbVec3D *,int)const;  // 0x262F0
    struct gbVec4D * __thiscall gbMatrix4::GetColumn(struct gbVec4D *,int)const;  // 0x262A0
    struct gbVec3D * __thiscall gbMatrix4::GetRow(struct gbVec3D *,int)const;  // 0x262D0
    struct gbVec4D * __thiscall gbMatrix4::GetRow(struct gbVec4D *,int)const;  // 0x26270
    void __thiscall gbMatrix4::Invert(void);  // 0x25A20
    void __thiscall gbMatrix4::Invert(struct gbMatrix4 *)const;  // 0x25BC0
    bool __thiscall gbMatrix4::IsIdentity(void)const;  // 0x25660
    bool __thiscall gbMatrix4::IsOrthonormal(void)const;  // 0x256D0
    bool __thiscall gbMatrix4::IsValid(void)const;  // 0x256A0
    void __thiscall gbMatrix4::LeftMultiply(struct gbMatrix4 const &);  // 0x251E0
    void __thiscall gbMatrix4::LeftMultiply(struct gbQuaternion const &);  // 0x25FA0
    void __thiscall gbMatrix4::LeftScale(float,float,float);  // 0x26210
    void __thiscall gbMatrix4::LeftTranslate(struct gbVec3D &);  // 0x26070
    void __thiscall gbMatrix4::LeftTranslate(float,float,float);  // 0x260D0
    void __thiscall gbMatrix4::LoadIdentity(void);  // 0x25640
    void __thiscall gbMatrix4::MakeMatrix(struct gbVec3D &,struct gbVec3D &,struct gbVec3D &);  // 0x25D90
    void __thiscall gbMatrix4::RightMultiply(struct gbMatrix4 const &);  // 0x25160
    void __thiscall gbMatrix4::RightMultiply(struct gbQuaternion const &);  // 0x25ED0
    void __thiscall gbMatrix4::RightScale(float,float,float);  // 0x26190
    void __thiscall gbMatrix4::RightTranslate(struct gbVec3D &);  // 0x26130
    void __thiscall gbMatrix4::RightTranslate(float,float,float);  // 0x26160
    void __thiscall gbMatrix4::Rotate(struct gbVec3D const *,struct gbVec3D *)const;  // 0x25480
    void __thiscall gbMatrix4::RotateIn(struct gbVec3D *);  // 0x254E0
    void __thiscall gbMatrix4::SetAxisAngle(struct gbVec3D *,float);  // 0x259D0
    void __thiscall gbMatrix4::SetAxisAngle(enum gbAxis,float);  // 0x259A0
    void __thiscall gbMatrix4::SetAxisAngle(enum gbAxis,float,float);  // 0x25910
    void __thiscall gbMatrix4::Transform(struct gbVec3D *,struct gbVec3D *,int)const;  // 0x252C0
    void __thiscall gbMatrix4::Transform(struct gbVec3D *,int)const;  // 0x25400
    void __thiscall gbMatrix4::Transform(struct gbVec3D const *,struct gbVec3D *)const;  // 0x25260
    void __thiscall gbMatrix4::TransformPlane(float * const);  // 0x25530
    void __thiscall gbMatrix4::Transform_W(struct gbVec3D *,struct gbVec3D *,int)const;  // 0x25340
    void __thiscall gbMatrix4::Transpose(void);  // 0x25D20
    void __thiscall gbMatrix4::Transpose(struct gbMatrix4 *)const;  // 0x25D60
    float __thiscall gbMatrix4::operator()(int,int);  // 0x2110
    void __thiscall gbMatrix4::operator*=(struct gbMatrix4 const &);  // 0x251E0
    void __thiscall gbMatrix4::operator*=(struct gbQuaternion const &);  // 0x25FA0
    void __thiscall gbMatrix4::operator*=(float const *);  // 0x251E0
    void __thiscall gbMatrix4::operator=(struct gbMatrix4 const &);  // 0x25140
};

// 30 methods
class CPK {
public:
    __thiscall CPK::CPK(void);  // 0x2C4B0
    __thiscall CPK::~CPK(void);  // 0x2C590
    bool __thiscall CPK::Close(class CPKFile *);  // 0x2D1A0
    unsigned long __thiscall CPK::Compress(void *,void *,unsigned long);  // 0x2D6E0
    static unsigned long __cdecl CPK::Crc(char const *);  // 0x2C430
    unsigned long __thiscall CPK::DeCompress(void *,void *,unsigned long);  // 0x2D730
    unsigned long __thiscall CPK::GetAllocationGranularity(void);  // 0x2DA70
    unsigned long __thiscall CPK::GetCPKHandle(void);  // 0x5DC0
    bool __thiscall CPK::GetFileSize(unsigned long &,unsigned long &,unsigned long);  // 0x2D780
    unsigned long __thiscall CPK::GetSize(class CPKFile *);  // 0x5DE0
    int __thiscall CPK::GetTableIndex(char const *);  // 0x2D8D0
    int __thiscall CPK::GetTableIndexFromCRC(unsigned long);  // 0x2DA00
    static void __cdecl CPK::InitCrcTable(void);  // 0x2C3E0
    bool __thiscall CPK::IsDir(unsigned long);  // 0x2D840
    bool __thiscall CPK::IsFileExist(char const *);  // 0x2CAD0
    bool __thiscall CPK::IsLoaded(void);  // 0x5DB0
    bool __thiscall CPK::IsValidCPK(char const *);  // 0x2C9E0
    bool __thiscall CPK::Load(char const *);  // 0x2C660
    unsigned long __thiscall CPK::LoadFile(void *,char const *);  // 0x2D3F0
    class CPKFile * __thiscall CPK::Open(char const *);  // 0x2CC50
    bool __thiscall CPK::Read(void *,unsigned long,class CPKFile *);  // 0x2D270
    int __thiscall CPK::ReadChar(class CPKFile *);  // 0x2D350
    char * __thiscall CPK::ReadLine(char *,int,class CPKFile *);  // 0x2D380
    void __thiscall CPK::Reset(void);  // 0x2C5D0
    void __thiscall CPK::Rewind(class CPKFile *);  // 0x5DF0
    unsigned long __thiscall CPK::Seek(class CPKFile *,int,unsigned long);  // 0x2D2E0
    void __thiscall CPK::SetOpenMode(enum ECPKMode);  // 0x2C640
    unsigned long __thiscall CPK::Tell(class CPKFile *);  // 0x5DD0
    bool __thiscall CPK::Unload(void);  // 0x2C940
    class CPK & __thiscall CPK::operator=(class CPK const &);  // 0x5E00
};

// 30 methods
class gbActor {
public:
    __thiscall gbActor::gbActor(class gbActor const &);  // 0x50D0
    __thiscall gbActor::gbActor(class gbActorDef *);  // 0x2AD0
    virtual __thiscall gbActor::~gbActor(void);  // 0x2C20
    virtual int __thiscall gbActor::Attach(class gbRenderEffect *);  // 0x3200
    void __thiscall gbActor::EnableActionTransMtl(char *,bool);  // 0x30A0
    virtual void __thiscall gbActor::EnableShadow(int);  // 0x3580
    unsigned int __thiscall gbActor::GetActionDuration(char *);  // 0x3090
    struct gbActorExpNode * __thiscall gbActor::GetAllExpNode(void);  // 0x50B0
    virtual void __thiscall gbActor::GetBoundSphere(struct gbSphere *);  // 0x3550
    struct gbAABBox * __thiscall gbActor::GetCollideAABBox(void);  // 0x5070
    void __thiscall gbActor::GetCollideOBB(struct gbOBBox &);  // 0x5050
    unsigned int __thiscall gbActor::GetEventTime(char *,char *);  // 0x34F0
    struct gbMixActInfo const * __thiscall gbActor::GetMixInfo(void);  // 0x5090
    int __thiscall gbActor::GetNumExpNodes(void);  // 0x50A0
    int __thiscall gbActor::GetNumMixInfo(void);  // 0x5080
    int __thiscall gbActor::GetTagNodeTM(struct gbMatrix4 *,char *);  // 0x30F0
    void __thiscall gbActor::GotoAction(unsigned long,int,unsigned int,unsigned int,unsigned long);  // 0x2F20
    void __thiscall gbActor::GotoAction(char *,char *,char *);  // 0x2E50
    void __thiscall gbActor::GotoAction(char *,int);  // 0x2DD0
    void __thiscall gbActor::GotoAction(char *,float,float);  // 0x2E00
    void __thiscall gbActor::LockAction(char *,float);  // 0x2FF0
    virtual void __thiscall gbActor::Render(struct gbRenderInfoObj *);  // 0x3180
    virtual void __thiscall gbActor::RenderShadowVolume(struct gbRenderInfoObj *);  // 0x31C0
    virtual void __thiscall gbActor::Reset(float);  // 0x3260
    void __thiscall gbActor::SetCurMaterial(char *);  // 0x50C0
    static void __cdecl gbActor::SetSunDirection(struct gbVec3D *);  // 0x3150
    void __thiscall gbActor::UnlockAction(char *);  // 0x3050
    virtual void __thiscall gbActor::Update(void);  // 0x32E0
    void __thiscall gbActor::UpdateExportNodes(void);  // 0x2CD0
    class gbActor & __thiscall gbActor::operator=(class gbActor const &);  // 0x5190
};

// 30 methods
class gbGeomNode {
public:
    __thiscall gbGeomNode::gbGeomNode(class gbGeomNode const &);  // 0xC9F0
    __thiscall gbGeomNode::gbGeomNode(void);  // 0xFC10
    virtual __thiscall gbGeomNode::~gbGeomNode(void);  // 0xFCE0
    virtual int __thiscall gbGeomNode::Attach(class gbRenderEffect *);  // 0x11440
    virtual void __thiscall gbGeomNode::AttachSelf(class gbRenderEffect *);  // 0x11130
    void __thiscall gbGeomNode::EnableBlade(int);  // 0xC9E0
    virtual void __thiscall gbGeomNode::EnableShadow(int);  // 0x11780
    virtual int __thiscall gbGeomNode::GetAABBox(struct gbAABBox *);  // 0x117B0
    float __thiscall gbGeomNode::GetAnimMaxTime(void);  // 0xC9D0
    virtual void __thiscall gbGeomNode::GetBoundSphere(struct gbSphere *);  // 0x11650
    struct gbMatrix4 * __thiscall gbGeomNode::GetCacheToWorld(void);  // 0xC9B0
    struct gbVec3D * __thiscall gbGeomNode::GetLastBladePos(class gbGeomNode *);  // 0x11820
    int __thiscall gbGeomNode::GetLoopPast(void);  // 0xC9A0
    class gbBaseMesh * __thiscall gbGeomNode::GetMesh(void);  // 0xC9C0
    struct gbOBBox * __thiscall gbGeomNode::GetOBBox(struct gbOBBox *);  // 0xFDE0
    struct gbOBBox * __thiscall gbGeomNode::GetTotalOBBox(struct gbOBBox *);  // 0xFEC0
    int __thiscall gbGeomNode::LoadCVDFile(char const *);  // 0x108B0
    void __thiscall gbGeomNode::LoadCVDFromStream(class gbVFile *,float);  // 0x10CD0
    static void __cdecl gbGeomNode::LoadCVDFromStream(class gbVFile *,float,class gbGeomNode * *,int &);  // 0x10C10
    int __thiscall gbGeomNode::LoadFromFile(char const *,char const *,void (__cdecl*)(int,int));  // 0x102C0
    virtual void __thiscall gbGeomNode::Render(struct gbRenderInfoObj *);  // 0x11460
    virtual void __thiscall gbGeomNode::RenderShadowVolume(struct gbRenderInfoObj *);  // 0x11520
    void __thiscall gbGeomNode::ReplaceTexture(class gbTexture *);  // 0x11880
    void __thiscall gbGeomNode::ReplaceTexture(char const *);  // 0x11840
    virtual void __thiscall gbGeomNode::Reset(float);  // 0x115E0
    void __thiscall gbGeomNode::SetAnimLoop(int);  // 0x11740
    void __thiscall gbGeomNode::SetBladeTime(float);  // 0x117E0
    void __thiscall gbGeomNode::SetBladeTimeScale(float);  // 0x11800
    virtual void __thiscall gbGeomNode::Update(void);  // 0x10EC0
    class gbGeomNode & __thiscall gbGeomNode::operator=(class gbGeomNode const &);  // 0xCB60
};

// 28 methods
class gbAudioManager {
public:
    __thiscall gbAudioManager::gbAudioManager(int &,struct gbAudioMgrDesc *);  // 0x1120
    __thiscall gbAudioManager::gbAudioManager(class gbAudioManager const &);  // 0x2240
    __thiscall gbAudioManager::~gbAudioManager(void);  // 0x1440
    void __thiscall gbAudioManager::AttachSampleHandle(class gbSound2DNode *);  // 0x1A10
    void __thiscall gbAudioManager::AttachSampleHandle(class gbSound3DNode *);  // 0x1620
    int __thiscall gbAudioManager::CanBeHeard(class gbSound3DNode *);  // 0x1DA0
    void __thiscall gbAudioManager::DeleteSoundData(class gbSoundData *);  // 0x15F0
    void __thiscall gbAudioManager::DetachAll3D(void);  // 0x1970
    void __thiscall gbAudioManager::DetachSampleHandle(class gbSound2DNode *);  // 0x1B00
    void __thiscall gbAudioManager::DetachSampleHandle(class gbSound3DNode *);  // 0x18D0
    float __thiscall gbAudioManager::Get2DMasterVolume(void);  // 0x21D0
    float __thiscall gbAudioManager::Get3DMasterVolume(void);  // 0x21F0
    unsigned long __thiscall gbAudioManager::Get3DProvider(char *);  // 0x1020
    void __thiscall gbAudioManager::GetListenerPosition(struct gbVec3D &);  // 0x2210
    float __thiscall gbAudioManager::GetMusicMasterVolume(void);  // 0x2200
    int __thiscall gbAudioManager::GetStreamStatus(int);  // 0x1D10
    class gbSoundData * __thiscall gbAudioManager::LoadSoundFile(char *);  // 0x1560
    void __thiscall gbAudioManager::PauseSoundStream(int);  // 0x1CD0
    void __thiscall gbAudioManager::PlaySoundStream(int,char *,int);  // 0x1BC0
    void __thiscall gbAudioManager::ReStartSoundStream(int);  // 0x1B70
    void __thiscall gbAudioManager::ResumeSoundStream(int);  // 0x1CF0
    void __thiscall gbAudioManager::Set2DMasterVolume(float);  // 0x21C0
    void __thiscall gbAudioManager::Set3DMasterVolume(float);  // 0x21E0
    void __thiscall gbAudioManager::SetListenerOrientation(struct gbVec3D &,struct gbVec3D &);  // 0x1D60
    void __thiscall gbAudioManager::SetListenerPosition(struct gbVec3D const &);  // 0x1D20
    void __thiscall gbAudioManager::SetMusicMasterVolume(float);  // 0x1C80
    void __thiscall gbAudioManager::StopSoundStream(int);  // 0x1C50
    class gbAudioManager & __thiscall gbAudioManager::operator=(class gbAudioManager const &);  // 0x2360
};

// 27 methods
class gbVisNode {
public:
    __thiscall gbVisNode::gbVisNode(class gbVisNode const &);  // 0x4A60
    __thiscall gbVisNode::gbVisNode(void);  // 0x16590
    virtual __thiscall gbVisNode::~gbVisNode(void);  // 0x49C0
    virtual int __thiscall gbVisNode::Attach(class gbRenderEffect *);  // 0x166F0
    virtual void __thiscall gbVisNode::AttachSelf(class gbRenderEffect *);  // 0x9420
    virtual void __thiscall gbVisNode::EnableShadow(int);  // 0x16830
    virtual int __thiscall gbVisNode::GetAABBox(struct gbAABBox *);  // 0x16B90
    enum NodeBlend __thiscall gbVisNode::GetBlend(float &);  // 0x16860
    virtual void __thiscall gbVisNode::GetBoundSphere(struct gbSphere *);  // 0x16820
    class gbVisNode * __thiscall gbVisNode::GetCullNext(void);  // 0x4A40
    class gbVisNode * __thiscall gbVisNode::GetCullPrev(void);  // 0x4A50
    int __thiscall gbVisNode::GetRenderPriority(void);  // 0x25A0
    float __thiscall gbVisNode::GetTimeScale(void);  // 0x2580
    void __thiscall gbVisNode::GetTotalBoundSphere(struct gbSphere *);  // 0x168B0
    int __thiscall gbVisNode::IsNodeShow(void);  // 0x4A30
    int __thiscall gbVisNode::PopMessage(struct gbNodeMsgObj &);  // 0x166A0
    void __thiscall gbVisNode::PushMessage(struct gbNodeMsgObj &);  // 0x16640
    virtual void __thiscall gbVisNode::Render(struct gbRenderInfoObj *);  // 0x9420
    virtual void __thiscall gbVisNode::RenderShadowVolume(struct gbRenderInfoObj *);  // 0x9420
    virtual void __thiscall gbVisNode::Reset(float);  // 0x16760
    void __thiscall gbVisNode::SetBlend(enum NodeBlend,float);  // 0x16840
    void __thiscall gbVisNode::SetBlendRecursive(enum NodeBlend,float);  // 0x16870
    void __thiscall gbVisNode::SetRenderPriority(int);  // 0x167F0
    void __thiscall gbVisNode::SetTimeScale(float);  // 0x167C0
    void __thiscall gbVisNode::ShowNode(int);  // 0x16790
    virtual void __thiscall gbVisNode::Update(void);  // 0x16730
    class gbVisNode & __thiscall gbVisNode::operator=(class gbVisNode const &);  // 0x4AF0
};

// 20 methods
class CIniFile {
public:
    __thiscall CIniFile::CIniFile(void);  // 0x311B0
    __thiscall CIniFile::~CIniFile(void);  // 0x311C0
    void __thiscall CIniFile::CloseFile(void);  // 0x312F0
    class gbVFile * __thiscall CIniFile::GetFilePointer(void);  // 0x311F0
    int __thiscall CIniFile::IfRead(void);  // 0x31200
    int __thiscall CIniFile::OpenFileRead(char const *);  // 0x31210
    int __thiscall CIniFile::OpenFileWrite(char const *);  // 0x31280
    int __thiscall CIniFile::ReadLine(char const *,char *,int);  // 0x313E0
    int __thiscall CIniFile::ReadLine(char const *,int *);  // 0x31560
    int __thiscall CIniFile::ReadLine(char const *,float *);  // 0x315B0
    int __thiscall CIniFile::ReadLine(char const *,double *);  // 0x31600
    int __thiscall CIniFile::ReadSection(char *);  // 0x31310
    void __thiscall CIniFile::ReadStart(void);  // 0x31650
    void __thiscall CIniFile::WriteLine(char const *,char const *);  // 0x31690
    void __thiscall CIniFile::WriteLine(char const *,int);  // 0x316B0
    void __thiscall CIniFile::WriteLine(char const *,float);  // 0x316D0
    void __thiscall CIniFile::WriteLine(char const *,double);  // 0x31700
    void __thiscall CIniFile::WriteLineSeperator(void);  // 0x31730
    void __thiscall CIniFile::WriteSection(char const *);  // 0x31670
    class CIniFile & __thiscall CIniFile::operator=(class CIniFile const &);  // 0x63C0
};

// 20 methods
class gbQuaternion {
public:
    __thiscall gbQuaternion::gbQuaternion(void);  // 0x2130
    void __thiscall gbQuaternion::GetAxisAngle(struct gbVec3D *,float *);  // 0x26890
    void __thiscall gbQuaternion::GetMatrix(struct gbMatrix4 *)const;  // 0x26B60
    void __thiscall gbQuaternion::GetVec3D(float *,struct gbVec3D *);  // 0x269F0
    void __thiscall gbQuaternion::Inverse(void);  // 0x26F20
    int __thiscall gbQuaternion::IsNormal(void);  // 0x2150
    bool const __thiscall gbQuaternion::IsUnit(void)const;  // 0x26980
    bool const __thiscall gbQuaternion::IsValid(void)const;  // 0x26910
    float const __thiscall gbQuaternion::Magnitude(void);  // 0x26E70
    void __thiscall gbQuaternion::MultiplyBy(struct gbQuaternion *,struct gbQuaternion *);  // 0x26D80
    float __thiscall gbQuaternion::Normalize(void);  // 0x26EA0
    void __thiscall gbQuaternion::RotateVector(struct gbVec3D *,struct gbVec3D *);  // 0x26F40
    void __thiscall gbQuaternion::SetAxisAngle(struct gbVec3D *,float);  // 0x26850
    void __thiscall gbQuaternion::SetMatrix(struct gbMatrix4 *);  // 0x26A10
    void __thiscall gbQuaternion::SetTwoVector(struct gbVec3D *,struct gbVec3D *);  // 0x26750
    void __thiscall gbQuaternion::SetUnit(void);  // 0x2180
    void __thiscall gbQuaternion::SetVec3D(float,struct gbVec3D *);  // 0x269D0
    void __thiscall gbQuaternion::SetYawPitchRoll(float,float,float);  // 0x26670
    void __thiscall gbQuaternion::Slerp(struct gbQuaternion *,struct gbQuaternion *,float);  // 0x26C40
    struct gbQuaternion & __thiscall gbQuaternion::operator=(struct gbQuaternion const &);  // 0x300C0
};

// 19 methods
class gbBaseMesh {
public:
    __thiscall gbBaseMesh::gbBaseMesh(class gbBaseMesh const &);  // 0x4810
    __thiscall gbBaseMesh::gbBaseMesh(class gbGfxManager *);  // 0xE860
    virtual __thiscall gbBaseMesh::~gbBaseMesh(void);  // 0xE920
    virtual void __thiscall gbBaseMesh::ComputeShadowVolume(void);  // 0x98E0
    struct gbAABBox * __thiscall gbBaseMesh::GetAABBox(void);  // 0xC9B0
    unsigned int __thiscall gbBaseMesh::GetFVF(void);  // 0x4A30
    struct gbMeshMemCache * __thiscall gbBaseMesh::GetMemoryCache(void);  // 0x47E0
    class gbMeshSection * __thiscall gbBaseMesh::GetMeshSection(int);  // 0x47C0
    enum gbMeshType __thiscall gbBaseMesh::GetMeshType(void);  // 0x4D10
    int __thiscall gbBaseMesh::GetNumFaces(void);  // 0xEAC0
    int __thiscall gbBaseMesh::GetNumSection(void);  // 0x47B0
    char const * __thiscall gbBaseMesh::GetObjectName(void);  // 0x4800
    virtual void __thiscall gbBaseMesh::RenderShadowVolume(class gbVisNode *,struct gbRenderInfoObj *);  // 0x9990
    void __thiscall gbBaseMesh::ReplaceTexture(class gbTexture *);  // 0xEC10
    void __thiscall gbBaseMesh::ReplaceTexture(char const *);  // 0xEBE0
    void __thiscall gbBaseMesh::SetCurTime(float);  // 0x47F0
    static void __cdecl gbBaseMesh::SetMeshTexDir(char *);  // 0xEB00
    void __thiscall gbBaseMesh::SetTexture(int,class gbTexture *);  // 0xEB60
    class gbBaseMesh & __thiscall gbBaseMesh::operator=(class gbBaseMesh const &);  // 0x48B0
};

// 19 methods
class gbSound3DNode {
public:
    __thiscall gbSound3DNode::gbSound3DNode(void);  // 0x2640
    __thiscall gbSound3DNode::~gbSound3DNode(void);  // 0x26B0
    float __thiscall gbSound3DNode::GetMaxDist(void);  // 0x2590
    float __thiscall gbSound3DNode::GetMinDist(void);  // 0x2580
    int __thiscall gbSound3DNode::GetPlayLoop(void);  // 0x25A0
    void __thiscall gbSound3DNode::GetPosition(struct gbVec3D &);  // 0x2560
    bool __thiscall gbSound3DNode::IfAttached(void);  // 0x24D0
    int __thiscall gbSound3DNode::IsPlaying(void);  // 0x2830
    int __thiscall gbSound3DNode::LoadFromFile(char *);  // 0x2700
    void __thiscall gbSound3DNode::Play(void);  // 0x2760
    void __thiscall gbSound3DNode::SetDistParam(float,float);  // 0x4420
    void __thiscall gbSound3DNode::SetLoopNum(int);  // 0x24F0
    void __thiscall gbSound3DNode::SetOrientation(struct gbVec3D &);  // 0x2540
    void __thiscall gbSound3DNode::SetPosition(struct gbVec3D &);  // 0x2500
    void __thiscall gbSound3DNode::SetVelocity(struct gbVec3D &);  // 0x2520
    void __thiscall gbSound3DNode::SetVolume(float);  // 0x24E0
    void __thiscall gbSound3DNode::Stop(void);  // 0x2810
    int __thiscall gbSound3DNode::Update(double);  // 0x2860
    class gbSound3DNode & __thiscall gbSound3DNode::operator=(class gbSound3DNode const &);  // 0x25B0
};

// 19 methods
class gbVFileSystem {
public:
    __thiscall gbVFileSystem::gbVFileSystem(void);  // 0x5EA0
    __thiscall gbVFileSystem::~gbVFileSystem(void);  // 0x5EC0
    void __thiscall gbVFileSystem::CloseFile(class gbVFile *);  // 0x307A0
    void __thiscall gbVFileSystem::DelFileEntry(class gbVFile *);  // 0x5E90
    int __thiscall gbVFileSystem::FileExistNum(char *);  // 0x30CA0
    int __thiscall gbVFileSystem::FindItem(char const *);  // 0x30E90
    long __thiscall gbVFileSystem::GetFileSize(class gbVFile *);  // 0x30BE0
    int __thiscall gbVFileSystem::Init(char *);  // 0x30240
    class gbVFile * __thiscall gbVFileSystem::NewFileEntry(void);  // 0x30510
    class gbVFile * __thiscall gbVFileSystem::OpenFile(char const *,unsigned int);  // 0x30540
    void __thiscall gbVFileSystem::Read(void *,unsigned int,class gbVFile *);  // 0x30810
    int __thiscall gbVFileSystem::ReadChar(class gbVFile *);  // 0x30990
    char * __thiscall gbVFileSystem::ReadLine(char *,int,class gbVFile *);  // 0x30DC0
    void __thiscall gbVFileSystem::Release(void);  // 0x304B0
    void __thiscall gbVFileSystem::Rewind(class gbVFile *);  // 0x30B20
    void __thiscall gbVFileSystem::Seek(class gbVFile *,long,int);  // 0x30A00
    long __thiscall gbVFileSystem::TellPos(class gbVFile *);  // 0x30B80
    void __thiscall gbVFileSystem::Write(void *,unsigned int,class gbVFile *);  // 0x308C0
    class gbVFileSystem & __thiscall gbVFileSystem::operator=(class gbVFileSystem const &);  // 0x5ED0
};

// 18 methods
class gbVec3D {
public:
    __thiscall gbVec3D::gbVec3D(float,float,float);  // 0x1F20
    void __thiscall gbVec3D::CrossProduct(struct gbVec3D const *,struct gbVec3D *)const;  // 0x25060
    float __thiscall gbVec3D::DotProduct(struct gbVec3D const *)const;  // 0x2070
    void __thiscall gbVec3D::Inverse(void);  // 0x20D0
    int __thiscall gbVec3D::IsNormal(void);  // 0x2090
    bool __thiscall gbVec3D::IsValid(void)const;  // 0x25010
    float __thiscall gbVec3D::Length(void)const;  // 0x24FE0
    float __thiscall gbVec3D::LengthSquare(void)const;  // 0x2050
    void __thiscall gbVec3D::Normalize(void);  // 0x250A0
    void __thiscall gbVec3D::Zero(void);  // 0x20F0
    void __thiscall gbVec3D::`default constructor closure'(void);  // 0x2100
    void __thiscall gbVec3D::operator*=(float);  // 0x1F80
    void __thiscall gbVec3D::operator+=(struct gbVec3D const &);  // 0x3930
    struct gbVec3D __thiscall gbVec3D::operator-(void)const;  // 0x2010
    void __thiscall gbVec3D::operator-=(struct gbVec3D const &);  // 0x1F60
    void __thiscall gbVec3D::operator/=(float);  // 0x1FA0
    void __thiscall gbVec3D::operator=(struct gbVec3D const &);  // 0x1F40
    bool __thiscall gbVec3D::operator==(struct gbVec3D const &);  // 0x1FC0
};

// 17 methods
class gbDynVertBuf {
public:
    __thiscall gbDynVertBuf::gbDynVertBuf(class gbDynVertBuf const &);  // 0x4270
    __thiscall gbDynVertBuf::gbDynVertBuf(unsigned int,int);  // 0x1C790
    virtual __thiscall gbDynVertBuf::~gbDynVertBuf(void);  // 0x1C7D0
    struct gbColorQuad * __thiscall gbDynVertBuf::GetColor1(void);  // 0x4240
    struct gbColorQuad * __thiscall gbDynVertBuf::GetColor2(void);  // 0x4250
    float * __thiscall gbDynVertBuf::GetNormal(void);  // 0x4230
    float * __thiscall gbDynVertBuf::GetUV(int);  // 0x4260
    int __thiscall gbDynVertBuf::GetVertNum(void);  // 0x39F0
    int __thiscall gbDynVertBuf::GetVertexStride(void);  // 0x3CE0
    float * __thiscall gbDynVertBuf::GetXYZ(void);  // 0x4BD0
    void __thiscall gbDynVertBuf::RenderGeomQuad(struct gbGeomQuad *,int,class gbRenderEffect *,struct gbTextureArray *);  // 0x1CAB0
    void __thiscall gbDynVertBuf::RenderGeomQuadViaStrip(struct gbGeomQuad *,int,class gbRenderEffect *,struct gbTextureArray *);  // 0x1CD50
    void __thiscall gbDynVertBuf::RenderGeomQuadViaStrip(struct gbGeomQuad *,int,class gbRenderEffect *,struct gbTextureArray *,unsigned long);  // 0x1CC10
    void __thiscall gbDynVertBuf::RenderLineStrip(struct gbColorQuad,struct gbVec3D *,int,class gbRenderEffect *);  // 0x1CE50
    void __thiscall gbDynVertBuf::RenderUIQuad(struct gbUIQuad *,int,class gbRenderEffect *,struct gbTextureArray *);  // 0x1C860
    void __thiscall gbDynVertBuf::StepVertexPtr(void);  // 0x1C7E0
    class gbDynVertBuf & __thiscall gbDynVertBuf::operator=(class gbDynVertBuf const &);  // 0x42E0
};

// 17 methods
class gbImage2D {
public:
    __thiscall gbImage2D::gbImage2D(void);  // 0x1E3E0
    __thiscall gbImage2D::~gbImage2D(void);  // 0x1E410
    unsigned char * __thiscall gbImage2D::CreateImage(int,int,int);  // 0x1EA30
    int __thiscall gbImage2D::GetBitCount(void);  // 0x4130
    unsigned char * __thiscall gbImage2D::GetBits(int,int);  // 0x4150
    unsigned char * __thiscall gbImage2D::GetBits(void);  // 0x4140
    int __thiscall gbImage2D::GetHeight(void);  // 0x4120
    struct gbImage2DInfo * __thiscall gbImage2D::GetImgInfo(void);  // 0xD950
    struct gbColorQuad * __thiscall gbImage2D::GetPalEntry(int);  // 0x4180
    enum gbPixelFmtType __thiscall gbImage2D::GetPixelFmtType(void);  // 0xD960
    int __thiscall gbImage2D::GetWidth(void);  // 0x4110
    int __thiscall gbImage2D::LoadImageFile(char *,int);  // 0x1E490
    void __thiscall gbImage2D::Release(void);  // 0x1E410
    void __thiscall gbImage2D::ScaleTo(int,int);  // 0x1E980
    void __thiscall gbImage2D::WriteJpegImage(char *,int);  // 0x1F5F0
    int __thiscall gbImage2D::WriteJpegToBuffer(unsigned char *,int);  // 0x1F6C0
    void __thiscall gbImage2D::WriteTGAImage(char *);  // 0x1EFC0
};

// 17 methods
class gbRenderEffect {
public:
    __thiscall gbRenderEffect::gbRenderEffect(struct ID3DXEffect *,unsigned int);  // 0x1CEF0
    __thiscall gbRenderEffect::gbRenderEffect(class gbRenderEffect const &);  // 0x4BF0
    virtual __thiscall gbRenderEffect::~gbRenderEffect(void);  // 0x1CF80
    void __thiscall gbRenderEffect::Apply(void);  // 0x1D100
    int __thiscall gbRenderEffect::Begin(void);  // 0x1D080
    int __thiscall gbRenderEffect::Compare(class gbRenderEffect *);  // 0x1CFE0
    void __thiscall gbRenderEffect::End(void);  // 0x1D0E0
    struct ID3DXEffect * __thiscall gbRenderEffect::GetD3DEffect(void);  // 0x1D900
    unsigned int __thiscall gbRenderEffect::GetFlag(void);  // 0x4BD0
    void __thiscall gbRenderEffect::GetVariant(char *,void *);  // 0x1D190
    void __thiscall gbRenderEffect::GetVariant(enum GBPARAMHANDLE,void *);  // 0x1D150
    void __thiscall gbRenderEffect::Pass(int);  // 0x1D0A0
    void __thiscall gbRenderEffect::SetDeclHandle(struct IDirect3DVertexDeclaration9 *);  // 0x4BE0
    void __thiscall gbRenderEffect::SetVariant(char *,void *);  // 0x1D1C0
    void __thiscall gbRenderEffect::SetVariant(enum GBPARAMHANDLE,void *);  // 0x1D170
    int __thiscall gbRenderEffect::Validate(void);  // 0x1D000
    class gbRenderEffect & __thiscall gbRenderEffect::operator=(class gbRenderEffect const &);  // 0x4C50
};

// 16 methods
class gbMatrixStack {
public:
    __thiscall gbMatrixStack::gbMatrixStack(int);  // 0x26FE0
    __thiscall gbMatrixStack::~gbMatrixStack(void);  // 0x27080
    int __thiscall gbMatrixStack::GetDepth(void);  // 0x17B0
    struct gbMatrix4 * __thiscall gbMatrixStack::GetTop(void);  // 0x27590
    void __thiscall gbMatrixStack::LoadIdentity(void);  // 0x270D0
    void __thiscall gbMatrixStack::LoadMatrix(struct gbMatrix4 *);  // 0x27110
    void __thiscall gbMatrixStack::MultMatrix(struct gbMatrix4 *);  // 0x27140
    void __thiscall gbMatrixStack::Pop(void);  // 0x270C0
    void __thiscall gbMatrixStack::Push(void);  // 0x27090
    void __thiscall gbMatrixStack::Rotate(struct gbQuaternion &);  // 0x27300
    void __thiscall gbMatrixStack::Rotate(float,struct gbVec3D &);  // 0x271E0
    void __thiscall gbMatrixStack::Scale(struct gbVec3D &);  // 0x27450
    void __thiscall gbMatrixStack::Scale(float,float,float);  // 0x27520
    void __thiscall gbMatrixStack::Translate(struct gbVec3D &);  // 0x273E0
    void __thiscall gbMatrixStack::Translate(float,float,float);  // 0x274B0
    class gbMatrixStack & __thiscall gbMatrixStack::operator=(class gbMatrixStack const &);  // 0x300C0
};

// 16 methods
class gbParticleEffect {
public:
    __thiscall gbParticleEffect::gbParticleEffect(class gbParticleEffect const &);  // 0xDA40
    __thiscall gbParticleEffect::gbParticleEffect(void);  // 0x2BAF0
    virtual __thiscall gbParticleEffect::~gbParticleEffect(void);  // 0x2BBA0
    virtual int __thiscall gbParticleEffect::Attach(class gbRenderEffect *);  // 0x2C160
    virtual void __thiscall gbParticleEffect::GetBoundSphere(struct gbSphere *);  // 0x2C2C0
    class gbPartEmitter * __thiscall gbParticleEffect::GetEmitter(int);  // 0x2C3A0
    struct gbPartGroupParam * __thiscall gbParticleEffect::GetGroupParam(int);  // 0x2C380
    class gbParticleGroup * __thiscall gbParticleEffect::GetParticleGroup(int);  // 0x2C360
    float __thiscall gbParticleEffect::GetSpaceScale(void);  // 0xDA20
    int __thiscall gbParticleEffect::LoadFromFile(char *);  // 0x2BCA0
    virtual void __thiscall gbParticleEffect::Render(struct gbRenderInfoObj *);  // 0x2C2E0
    virtual void __thiscall gbParticleEffect::Reset(float);  // 0x2BFD0
    void __thiscall gbParticleEffect::SetSpaceScale(float);  // 0xDA30
    virtual void __thiscall gbParticleEffect::Update(void);  // 0x2C070
    void __thiscall gbParticleEffect::UpdateInternal(void);  // 0x2C0D0
    class gbParticleEffect & __thiscall gbParticleEffect::operator=(class gbParticleEffect const &);  // 0xDC60
};

// 15 methods
class gbAnimNodeGroup {
public:
    __thiscall gbAnimNodeGroup::gbAnimNodeGroup(class gbGfxManager *);  // 0xC3C0
    __thiscall gbAnimNodeGroup::~gbAnimNodeGroup(void);  // 0xC460
    void __thiscall gbAnimNodeGroup::Attach(void);  // 0xC750
    class gbAnimNodeGroup * __thiscall gbAnimNodeGroup::Clone(void);  // 0xC490
    int __thiscall gbAnimNodeGroup::IsDead(void);  // 0xCD10
    void __thiscall gbAnimNodeGroup::LoadFromFile(char *);  // 0xC5D0
    void __thiscall gbAnimNodeGroup::Reset(void);  // 0xC890
    void __thiscall gbAnimNodeGroup::SetPosition(struct gbMatrix4 const &);  // 0xC740
    void __thiscall gbAnimNodeGroup::SetPosition(struct gbVec3D const &);  // 0xC710
    void __thiscall gbAnimNodeGroup::SetPriority(int);  // 0xC900
    static void __cdecl gbAnimNodeGroup::SetSoundFileDir(char *);  // 0xC960
    void __thiscall gbAnimNodeGroup::SetToDead(void);  // 0xCD20
    void __thiscall gbAnimNodeGroup::ShowGroup(int);  // 0x24E0
    void __thiscall gbAnimNodeGroup::Update(void);  // 0xC7A0
    class gbAnimNodeGroup & __thiscall gbAnimNodeGroup::operator=(class gbAnimNodeGroup const &);  // 0xCD30
};

// 15 methods
class gbChain1D {
public:
    __thiscall gbChain1D::gbChain1D(void);  // 0x2EA50
    __thiscall gbChain1D::~gbChain1D(void);  // 0x2EA60
    void __thiscall gbChain1D::AddNode(class gbChain1DNode *);  // 0x2EAA0
    void __thiscall gbChain1D::AddNodeOnHead(class gbChain1DNode *);  // 0x2EA80
    void __thiscall gbChain1D::AddNodeOnTail(class gbChain1DNode *);  // 0x2EAA0
    class gbChain1DNode * __thiscall gbChain1D::BeginIterate(void);  // 0x3AF0
    void __thiscall gbChain1D::ClearAllNodePtr(void);  // 0x3A00
    void __thiscall gbChain1D::DelNodeFromChain(class gbChain1DNode *);  // 0x2EB90
    int __thiscall gbChain1D::GetNumNode(void);  // 0x39F0
    void __thiscall gbChain1D::InsertAfter(class gbChain1DNode *,class gbChain1DNode *);  // 0x2EB40
    void __thiscall gbChain1D::InsertBefore(class gbChain1DNode *,class gbChain1DNode *);  // 0x2EAD0
    bool __thiscall gbChain1D::IsContainNode(class gbChain1DNode *);  // 0x2EC00
    class gbChain1DNode * __thiscall gbChain1D::Iterate(void);  // 0x3B00
    class gbChain1D & __thiscall gbChain1D::operator=(class gbChain1D const &);  // 0x300C0
    class gbChain1DNode * __thiscall gbChain1D::operator[](int);  // 0x2EC20
};

// 15 methods
class gbEffectMgr {
public:
    __thiscall gbEffectMgr::gbEffectMgr(class gbEffectMgr const &);  // 0x4D30
    __thiscall gbEffectMgr::gbEffectMgr(void);  // 0x4D20
    __thiscall gbEffectMgr::~gbEffectMgr(void);  // 0x4E90
    class gbRenderEffect * __thiscall gbEffectMgr::GetDefaultEffect(void);  // 0x4D10
    class gbTexture * __thiscall gbEffectMgr::GetGrayTexture(void);  // 0x1D8F0
    class gbRenderEffect * __thiscall gbEffectMgr::GetRenderEffect(unsigned int);  // 0x1D8B0
    class gbTexture * __thiscall gbEffectMgr::GetWhiteTexture(void);  // 0x1D8E0
    void __thiscall gbEffectMgr::Init(class gbGfxManager *);  // 0x1D1F0
    class gbRenderEffect * __thiscall gbEffectMgr::NewRenderEffect(char const *,unsigned int);  // 0x1D6D0
    class gbRenderEffect * __thiscall gbEffectMgr::NewTrivalEffect(int);  // 0x1D840
    int __thiscall gbEffectMgr::OnLostDevice(void);  // 0x1D560
    int __thiscall gbEffectMgr::OnResetDevice(void);  // 0x1D5A0
    struct IDirect3DVertexDeclaration9 * __thiscall gbEffectMgr::RegisterVertexFormat(char const *,struct gbVertexElement *);  // 0x1D5E0
    void __thiscall gbEffectMgr::Release(void);  // 0x1D510
    class gbEffectMgr & __thiscall gbEffectMgr::operator=(class gbEffectMgr const &);  // 0x4DD0
};

// 15 methods
class gbNBTreeNode {
public:
    __thiscall gbNBTreeNode::gbNBTreeNode(class gbNBTreeNode const &);  // 0x45B0
    __thiscall gbNBTreeNode::gbNBTreeNode(void);  // 0x4460
    virtual __thiscall gbNBTreeNode::~gbNBTreeNode(void);  // 0x44C0
    void __thiscall gbNBTreeNode::AddChild(class gbNBTreeNode *);  // 0x4540
    void __thiscall gbNBTreeNode::AddChildOnHead(class gbNBTreeNode *);  // 0x4520
    void __thiscall gbNBTreeNode::AddChildOnTail(class gbNBTreeNode *);  // 0x4540
    class gbNBTreeNode * __thiscall gbNBTreeNode::BeginIterateChild(void);  // 0x4590
    void __thiscall gbNBTreeNode::DelChildFromChain(class gbNBTreeNode *);  // 0x4560
    class gbNBTreeNode * __thiscall gbNBTreeNode::GetChild(int);  // 0x47A0
    class gbChain1D & __thiscall gbNBTreeNode::GetChildren(void);  // 0x5E20
    class gbNBTreeNode * __thiscall gbNBTreeNode::GetFather(void);  // 0x39F0
    int __thiscall gbNBTreeNode::GetNumChildren(void);  // 0x3FA0
    int __thiscall gbNBTreeNode::IsChild(class gbNBTreeNode *);  // 0x4570
    class gbNBTreeNode * __thiscall gbNBTreeNode::IterateChild(void);  // 0x45A0
    class gbNBTreeNode & __thiscall gbNBTreeNode::operator=(class gbNBTreeNode const &);  // 0x45F0
};

// 14 methods
class gbTexture {
public:
    __thiscall gbTexture::gbTexture(void);  // 0x20370
    virtual __thiscall gbTexture::~gbTexture(void);  // 0x203C0
    void __thiscall gbTexture::CreateTexture(int,int,enum gbPixelFmtType,int);  // 0x20760
    unsigned char * __thiscall gbTexture::GetBits(void);  // 0x207D0
    int __thiscall gbTexture::GetHeight(void);  // 0x4BD0
    enum gbPixelFmtType __thiscall gbTexture::GetInternalFormat(class gbImage2D *);  // 0x20430
    int __thiscall gbTexture::GetLevels(void);  // 0x41A0
    unsigned char __thiscall gbTexture::GetPixelChannel(int,int,int);  // 0x207E0
    int __thiscall gbTexture::GetWidth(void);  // 0x4D10
    int __thiscall gbTexture::IsInit(void);  // 0x4190
    void __thiscall gbTexture::LoadFromImage2D(class gbImage2D *);  // 0x20490
    void __thiscall gbTexture::LoadTexture(int);  // 0x205A0
    void __thiscall gbTexture::UpdateTexture(int,int,class gbImage2D *);  // 0x20820
    void __thiscall gbTexture::UpdateTexture(class gbImage2D *);  // 0x20860
};

// 13 methods
class gbParticleGroup {
public:
    __thiscall gbParticleGroup::gbParticleGroup(void);  // 0x2B070
    __thiscall gbParticleGroup::~gbParticleGroup(void);  // 0x2B090
    struct gbParticleUnit * __thiscall gbParticleGroup::CreateOneParticle(struct gbEmitterData *);  // 0x2B2A0
    int __thiscall gbParticleGroup::GetAlivePartNum(void);  // 0xD960
    struct gbPartGroupParam * __thiscall gbParticleGroup::GetGroupParam(void);  // 0x11940
    char * __thiscall gbParticleGroup::GetName(void);  // 0xD950
    struct gbParticleUnit * __thiscall gbParticleGroup::GetOldestParticle(void);  // 0x2B230
    void __thiscall gbParticleGroup::LoadFromFile(class gbVFile *,class gbParticleEffect *);  // 0x2B0B0
    void __thiscall gbParticleGroup::Render(void);  // 0x2B770
    void __thiscall gbParticleGroup::Reset(void);  // 0x2B1E0
    void __thiscall gbParticleGroup::Update(double);  // 0x2B6A0
    int __thiscall gbParticleGroup::UpdateOneParticle(struct gbParticleUnit *,double);  // 0x2B590
    class gbParticleGroup & __thiscall gbParticleGroup::operator=(class gbParticleGroup const &);  // 0xD970
};

// 13 methods
class gbSceneGraph {
public:
    __thiscall gbSceneGraph::gbSceneGraph(class gbGfxManager *,struct gbVec3D const &,float);  // 0x14B10
    __thiscall gbSceneGraph::~gbSceneGraph(void);  // 0x14C60
    void __thiscall gbSceneGraph::AddSkyBox(class gbVisNode *);  // 0x14CD0
    void __thiscall gbSceneGraph::AddVisNode(class gbVisNode *);  // 0x155A0
    void __thiscall gbSceneGraph::AddVolModNode(class gbVolModNode *);  // 0x14D90
    void __thiscall gbSceneGraph::Begin(class gbCamera *);  // 0x14CE0
    void __thiscall gbSceneGraph::CalEffectiveVolMod(struct gbRenderInfoObj *,struct gbVec3D const &,int);  // 0x14DC0
    void __thiscall gbSceneGraph::DelVisNode(class gbVisNode *);  // 0x155D0
    void __thiscall gbSceneGraph::End(void);  // 0x14F40
    struct gbRenderInfoObj * __thiscall gbSceneGraph::NewOneRenderObj(class gbVisNode *);  // 0x14D10
    struct gbRenderInfoObj * __thiscall gbSceneGraph::NewShadowVolume(class gbVisNode *);  // 0x14D70
    void __thiscall gbSceneGraph::ResetBladeMgr(void);  // 0x15620
    void __thiscall gbSceneGraph::SetBladeTimeScale(float);  // 0x15600
};

// 13 methods
class gbStaticChain {
public:
    __thiscall gbStaticChain::gbStaticChain(void);  // 0x14AE0
    struct gbStaticChainNode * __thiscall gbStaticChain::BeginIterate(void);  // 0x2F950
    struct gbStaticChainNode * __thiscall gbStaticChain::BeginReverseIterate(void);  // 0x2F970
    void __thiscall gbStaticChain::DelOneNode(struct gbStaticChainNode *);  // 0x2F900
    struct gbStaticChainNode * __thiscall gbStaticChain::GetNewestNode(void);  // 0x2F9A0
    struct gbStaticChainNode * __thiscall gbStaticChain::GetNode(int);  // 0x14AD0
    struct gbStaticChainNode * __thiscall gbStaticChain::GetOldestNode(void);  // 0x2F9B0
    void __thiscall gbStaticChain::InitBuffer(int,int);  // 0x2F810
    struct gbStaticChainNode * __thiscall gbStaticChain::Iterate(void);  // 0x2F960
    struct gbStaticChainNode * __thiscall gbStaticChain::NewOneNode(void);  // 0x2F8C0
    void __thiscall gbStaticChain::ReleaseBuffer(void);  // 0x2F8B0
    struct gbStaticChainNode * __thiscall gbStaticChain::ReverseIterate(void);  // 0x2F990
    class gbStaticChain & __thiscall gbStaticChain::operator=(class gbStaticChain const &);  // 0x14AF0
};

// 13 methods
class gbVertPoolMgr {
public:
    __thiscall gbVertPoolMgr::gbVertPoolMgr(class gbGfxManager *,int,int,int,int);  // 0x210C0
    __thiscall gbVertPoolMgr::~gbVertPoolMgr(void);  // 0x211A0
    void __thiscall gbVertPoolMgr::DelIndexBubble(class gbIndexBubble *);  // 0x21620
    void __thiscall gbVertPoolMgr::DelSrcVertBub(class gbVertexBubble *);  // 0x214F0
    void __thiscall gbVertPoolMgr::DelVertexBubble(class gbVertexBubble *);  // 0x213A0
    int __thiscall gbVertPoolMgr::FindVertexPoolIndex(unsigned int *,unsigned int);  // 0x212A0
    class gbDynVertBuf * __thiscall gbVertPoolMgr::GetDynVertBuf(unsigned int);  // 0x21680
    class gbIndexBubble * __thiscall gbVertPoolMgr::NewIndexBubble(enum gbPrimType,int);  // 0x21590
    class gbVertexBubble * __thiscall gbVertPoolMgr::NewSrcVertBub(unsigned int,int);  // 0x21430
    class gbVertexBubble * __thiscall gbVertPoolMgr::NewVertexBubble(unsigned int,int);  // 0x212E0
    int __thiscall gbVertPoolMgr::OnLostDevice(void);  // 0x21240
    int __thiscall gbVertPoolMgr::OnResetDevice(void);  // 0x21270
    class gbVertPoolMgr & __thiscall gbVertPoolMgr::operator=(class gbVertPoolMgr const &);  // 0x40B0
};

// 12 methods
class gbPrintFont {
public:
    __thiscall gbPrintFont::gbPrintFont(int,int,int);  // 0x22A20
    __thiscall gbPrintFont::~gbPrintFont(void);  // 0x22AC0
    virtual int __thiscall gbPrintFont::Init(void);  // 0x22B00
    virtual void __thiscall gbPrintFont::Print3DString(char *,float,float,float);  // 0x22D60
    void __thiscall gbPrintFont::PrintCenterLine(char *,float,float,float,float);  // 0x22B70
    virtual void __thiscall gbPrintFont::PrintString(char *,float,float,float,float);  // 0x22BF0
    virtual void __thiscall gbPrintFont::Release(void);  // 0x22B40
    void __thiscall gbPrintFont::SetCurFontDepth(float);  // 0x4440
    void __thiscall gbPrintFont::SetCurFontPitch(float,float);  // 0x4420
    void __thiscall gbPrintFont::SetCurFontScale(float,float);  // 0x4400
    void __thiscall gbPrintFont::SetFontColor(unsigned char,unsigned char,unsigned char);  // 0x4340
    void __thiscall gbPrintFont::SetFontColor(unsigned char,unsigned char,unsigned char,unsigned char);  // 0x43A0
};

// 11 methods
class gbLightObj {
public:
    __thiscall gbLightObj::gbLightObj(class gbLightObj const &);  // 0x53D0
    __thiscall gbLightObj::gbLightObj(void);  // 0x5390
    virtual __thiscall gbLightObj::~gbLightObj(void);  // 0x5670
    virtual void __thiscall gbLightObj::Compute(class gbVolModNode *);  // 0x13350
    void __thiscall gbLightObj::ComputeBoundSphere(void);  // 0x13280
    virtual struct gbSphere const * __thiscall gbLightObj::GetBoundSphere(void);  // 0x13270
    virtual float __thiscall gbLightObj::GetEffectOnPoint(struct gbVec3D const &,int);  // 0x132A0
    struct gbLight * __thiscall gbLightObj::GetSysLight(void);  // 0x5380
    virtual int __thiscall gbLightObj::GetType(void);  // 0x9D30
    void __thiscall gbLightObj::Init(enum gbLightObj::LIGHT_TYPE);  // 0x131F0
    class gbLightObj & __thiscall gbLightObj::operator=(class gbLightObj const &);  // 0x54B0
};

// 11 methods
class gbSound2DNode {
public:
    __thiscall gbSound2DNode::gbSound2DNode(void);  // 0x28D0
    __thiscall gbSound2DNode::~gbSound2DNode(void);  // 0x28F0
    bool __thiscall gbSound2DNode::IsPlaying(void);  // 0x29F0
    int __thiscall gbSound2DNode::LoadFromFile(char *);  // 0x2940
    void __thiscall gbSound2DNode::Pause(void);  // 0x2A10
    void __thiscall gbSound2DNode::Play(void);  // 0x2970
    void __thiscall gbSound2DNode::Resume(void);  // 0x2A30
    void __thiscall gbSound2DNode::SetLoopNum(int);  // 0x2630
    void __thiscall gbSound2DNode::SetVolume(float);  // 0x2620
    void __thiscall gbSound2DNode::Stop(void);  // 0x29D0
    class gbSound2DNode & __thiscall gbSound2DNode::operator=(class gbSound2DNode const &);  // 0x300C0
};

// 10 methods
class gbRay {
public:
    __thiscall gbRay::gbRay(void);  // 0x3840
    float __thiscall gbRay::IntersectPlane(struct gbVec3D &,struct gbVec3D &);  // 0x281D0
    int __thiscall gbRay::IsColAABB(struct gbAABBox &);  // 0x28360
    int __thiscall gbRay::IsColOBB(struct gbOBBox &);  // 0x293B0
    int __thiscall gbRay::IsColOBB_H(struct gbOBBox &);  // 0x28260
    int __thiscall gbRay::IsColQuad(struct gbVec3D &,struct gbVec3D &,struct gbVec3D &);  // 0x28A00
    int __thiscall gbRay::IsColSphere(struct gbSphere &);  // 0x280F0
    int __thiscall gbRay::IsColTriangle(struct gbVec3D &,struct gbVec3D &,struct gbVec3D &,struct gbVec3D &);  // 0x28BC0
    int __thiscall gbRay::IsColTriangle(struct gbVec3D &,struct gbVec3D &,struct gbVec3D &);  // 0x28850
    struct gbRay & __thiscall gbRay::operator=(struct gbRay const &);  // 0xD3C0
};

// 9 methods
class BEZIER {
public:
    __thiscall BEZIER::BEZIER(struct gbVec3D *);  // 0x241E0
    __thiscall BEZIER::BEZIER(void);  // 0x24220
    __thiscall BEZIER::~BEZIER(void);  // 0x24140
    struct gbVec3D * __thiscall BEZIER::GetControlPt(void);  // 0x24150
    void __thiscall BEZIER::SetControlPt(struct gbVec3D *);  // 0x24250
    void __thiscall BEZIER::computerCoefficient(void);  // 0x241C0
    struct gbVec3D __thiscall BEZIER::getInterpolatePoint(float);  // 0x24270
    struct gbVec3D __thiscall BEZIER::getTangentVector(float);  // 0x24360
    class BEZIER & __thiscall BEZIER::operator=(class BEZIER const &);  // 0x24160
};

// 9 methods
class gbChain2D {
public:
    __thiscall gbChain2D::gbChain2D(void);  // 0x2EC40
    __thiscall gbChain2D::~gbChain2D(void);  // 0x2EC50
    void __thiscall gbChain2D::AddNode(class gbChain2DNode *);  // 0x2EC70
    class gbChain2DNode * __thiscall gbChain2D::BeginIterate(int);  // 0x3B10
    void __thiscall gbChain2D::DelNodeFromChain(class gbChain2DNode *);  // 0x2ECB0
    int __thiscall gbChain2D::GetNumNode(void);  // 0x3CC0
    bool __thiscall gbChain2D::IsContainNode(class gbChain2DNode *);  // 0x2ED30
    class gbChain2DNode * __thiscall gbChain2D::Iterate(void);  // 0x3B30
    class gbChain2D & __thiscall gbChain2D::operator=(class gbChain2D const &);  // 0x3AD0
};

// 9 methods
class gbIndexBubble {
public:
    __thiscall gbIndexBubble::gbIndexBubble(class gbIndexBubble const &);  // 0x3BD0
    __thiscall gbIndexBubble::gbIndexBubble(class gbIndexPool *,enum gbPrimType,int,int,int);  // 0x3B50
    virtual __thiscall gbIndexBubble::~gbIndexBubble(void);  // 0x3F30
    unsigned short * __thiscall gbIndexBubble::Lock16(void);  // 0x20900
    unsigned int * __thiscall gbIndexBubble::Lock32(void);  // 0x20900
    void __thiscall gbIndexBubble::Set(int,int,int);  // 0x3B90
    void __thiscall gbIndexBubble::SetRange(int,int);  // 0x3BB0
    void __thiscall gbIndexBubble::Unlock(void);  // 0x20920
    class gbIndexBubble & __thiscall gbIndexBubble::operator=(class gbIndexBubble const &);  // 0x3C20
};

// 9 methods
class gbIndexPool {
public:
    __thiscall gbIndexPool::gbIndexPool(class gbIndexPool const &);  // 0x3CF0
    __thiscall gbIndexPool::gbIndexPool(enum gbPoolType,int,int);  // 0x20930
    virtual __thiscall gbIndexPool::~gbIndexPool(void);  // 0x209F0
    void __thiscall gbIndexPool::DelBubble(class gbIndexBubble *);  // 0x20B20
    int __thiscall gbIndexPool::GetIndexSize(void);  // 0x3CC0
    void * __thiscall gbIndexPool::GetInternalMemBuf(void);  // 0x3CE0
    int __thiscall gbIndexPool::IsEmpty(void);  // 0x3CD0
    class gbIndexBubble * __thiscall gbIndexPool::NewBubble(enum gbPrimType,int);  // 0x20A50
    class gbIndexPool & __thiscall gbIndexPool::operator=(class gbIndexPool const &);  // 0x3D60
};

// 9 methods
class gbNameVarBuf {
public:
    __thiscall gbNameVarBuf::gbNameVarBuf(void);  // 0x2ED80
    __thiscall gbNameVarBuf::~gbNameVarBuf(void);  // 0x2EDA0
    void __thiscall gbNameVarBuf::GetVariant(unsigned int,void *);  // 0x2EF30
    int __thiscall gbNameVarBuf::IsVarExist(unsigned int);  // 0x2EF00
    void * __thiscall gbNameVarBuf::LockVariant(unsigned int,int *);  // 0x2EFF0
    void __thiscall gbNameVarBuf::RegVariant(unsigned int,int,int);  // 0x2EDD0
    void __thiscall gbNameVarBuf::SetVariant(unsigned int,void *);  // 0x2EF90
    void __thiscall gbNameVarBuf::UnlockVariant(void);  // 0x2F050
    class gbNameVarBuf & __thiscall gbNameVarBuf::operator=(class gbNameVarBuf const &);  // 0x14AF0
};

// 9 methods
class gbOBBox {
public:
    __thiscall gbOBBox::gbOBBox(void);  // 0x3860
    void __thiscall gbOBBox::GetAABBox(struct gbAABBox &);  // 0x27D60
    struct gbVec3D __thiscall gbOBBox::GetCenter(void)const;  // 0x27C00
    float __thiscall gbOBBox::GetRadius(void)const;  // 0x27DC0
    float __thiscall gbOBBox::GetRadiusInDirection(struct gbVec3D const &)const;  // 0x27DF0
    void __thiscall gbOBBox::GetSphere(struct gbSphere &);  // 0x27D10
    int __thiscall gbOBBox::IsColOBB(struct gbOBBox *);  // 0x27EC0
    int __thiscall gbOBBox::IsColPoint(struct gbVec3D &);  // 0x27C40
    struct gbOBBox & __thiscall gbOBBox::operator=(struct gbOBBox const &);  // 0x3870
};

// 9 methods
class gbPartGroupParam {
public:
    __thiscall gbPartGroupParam::gbPartGroupParam(void);  // 0x2A620
    __thiscall gbPartGroupParam::~gbPartGroupParam(void);  // 0x2A7A0
    void __thiscall gbPartGroupParam::ComputeAirResist(struct gbParticleUnit *,float);  // 0x2AD80
    void __thiscall gbPartGroupParam::ComputeParticleParam(struct gbParticleUnit *,float,float);  // 0x2AED0
    class gbRenderEffect * __thiscall gbPartGroupParam::GetRenderEffect(void);  // 0xD020
    class gbTexture * __thiscall gbPartGroupParam::GetTexture(void);  // 0xD010
    void __thiscall gbPartGroupParam::InitParticleParam(struct gbParticleUnit *);  // 0x2AFC0
    void __thiscall gbPartGroupParam::LoadFromFile(class gbVFile *);  // 0x2A7F0
    struct gbPartGroupParam & __thiscall gbPartGroupParam::operator=(struct gbPartGroupParam const &);  // 0xD030
};

// 9 methods
class gbStaticMesh {
public:
    __thiscall gbStaticMesh::gbStaticMesh(class gbStaticMesh const &);  // 0x11950
    __thiscall gbStaticMesh::gbStaticMesh(class gbGfxManager *);  // 0x15630
    virtual __thiscall gbStaticMesh::~gbStaticMesh(void);  // 0x15660
    virtual void __thiscall gbStaticMesh::ComputeShadowVolume(void);  // 0x16390
    virtual void __thiscall gbStaticMesh::DrawSubSet(int,struct gbRenderInfoObj *);  // 0x15CA0
    class gbVertexBubble * __thiscall gbStaticMesh::GetVertBubble(void);  // 0x11940
    int __thiscall gbStaticMesh::LoadFromStream(class gbVFile *,int,struct GeomNodeDesc *);  // 0x15E80
    virtual void __thiscall gbStaticMesh::RenderShadowVolume(class gbVisNode *,struct gbRenderInfoObj *);  // 0x9990
    class gbStaticMesh & __thiscall gbStaticMesh::operator=(class gbStaticMesh const &);  // 0x11A10
};

// 9 methods
class gbTexture_D3D {
public:
    __thiscall gbTexture_D3D::gbTexture_D3D(void);  // 0x1BA60
    virtual __thiscall gbTexture_D3D::~gbTexture_D3D(void);  // 0x1BAA0
    virtual int __thiscall gbTexture_D3D::CreateForRenderTarget(int,int,enum gbPixelFmtType);  // 0x1BF80
    virtual void __thiscall gbTexture_D3D::CreateFromFileMemory(void *,int);  // 0x1C010
    virtual void __thiscall gbTexture_D3D::CreateFromMemory(int,int,enum gbPixelFmtType,int,enum gbPixelFmtType,void *);  // 0x1BD30
    unsigned char __thiscall gbTexture_D3D::GetByte(int,int);  // 0x1C170
    struct IDirect3DSurface9 * __thiscall gbTexture_D3D::GetMiscTexName(void);  // 0x15E70
    struct IDirect3DBaseTexture9 * __thiscall gbTexture_D3D::GetTexName(void);  // 0x15E60
    virtual void __thiscall gbTexture_D3D::UpdateTexture(int,int,int,int,enum gbPixelFmtType,void *);  // 0x1BEA0
};

// 9 methods
class gbVertexBubble {
public:
    __thiscall gbVertexBubble::gbVertexBubble(class gbVertexBubble const &);  // 0x3E60
    __thiscall gbVertexBubble::gbVertexBubble(class gbVertexPool *,int,int,int);  // 0x3DF0
    virtual __thiscall gbVertexBubble::~gbVertexBubble(void);  // 0x3F30
    void __thiscall gbVertexBubble::ClearPointer(void);  // 0x3DD0
    void * __thiscall gbVertexBubble::Lock(void);  // 0x20C00
    void __thiscall gbVertexBubble::Set(int,int,int);  // 0x3E40
    void __thiscall gbVertexBubble::StepVertexPtr(void);  // 0x20CD0
    void __thiscall gbVertexBubble::Unlock(void);  // 0x20CA0
    class gbVertexBubble & __thiscall gbVertexBubble::operator=(class gbVertexBubble const &);  // 0x3ED0
};

// 9 methods
class gbVertexPool {
public:
    __thiscall gbVertexPool::gbVertexPool(class gbVertexPool const &);  // 0x3FC0
    __thiscall gbVertexPool::gbVertexPool(enum gbPoolType,unsigned int,int);  // 0x20D90
    virtual __thiscall gbVertexPool::~gbVertexPool(void);  // 0x20EB0
    void __thiscall gbVertexPool::DelBubble(class gbVertexBubble *);  // 0x20FE0
    int __thiscall gbVertexPool::GetStride(void);  // 0x4D10
    unsigned int __thiscall gbVertexPool::GetVertType(void);  // 0x3FA0
    int __thiscall gbVertexPool::IsEmpty(void);  // 0x3FB0
    class gbVertexBubble * __thiscall gbVertexPool::NewBubble(int);  // 0x20F10
    class gbVertexPool & __thiscall gbVertexPool::operator=(class gbVertexPool const &);  // 0x4040
};

// 9 methods
class gbVolModNode {
public:
    __thiscall gbVolModNode::gbVolModNode(class gbVolModNode const &);  // 0x5700
    __thiscall gbVolModNode::gbVolModNode(void);  // 0x13040
    virtual __thiscall gbVolModNode::~gbVolModNode(void);  // 0x130B0
    virtual int __thiscall gbVolModNode::Attach(class gbRenderEffect *);  // 0x13190
    virtual void __thiscall gbVolModNode::GetBoundSphere(struct gbSphere *);  // 0x13160
    class gbLightObj * __thiscall gbVolModNode::GetLightObj(void);  // 0x56E0
    virtual void __thiscall gbVolModNode::Render(struct gbRenderInfoObj *);  // 0x56F0
    void __thiscall gbVolModNode::SetVolModObj(class gbVolumeModifier *);  // 0x13140
    class gbVolModNode & __thiscall gbVolModNode::operator=(class gbVolModNode const &);  // 0x57C0
};

// 8 methods
class gbPartEmitter {
public:
    __thiscall gbPartEmitter::gbPartEmitter(void);  // 0xD3F0
    __thiscall gbPartEmitter::~gbPartEmitter(void);  // 0xD940
    int __thiscall gbPartEmitter::ComputeEmitterData(struct gbEmitterData *,double,double);  // 0x2A2C0
    void __thiscall gbPartEmitter::ComputeParticleInitPos(struct gbParticleUnit *);  // 0x2A400
    void __thiscall gbPartEmitter::ComputeParticleInitVel(struct gbEmitterData *,struct gbParticleUnit *);  // 0x2A590
    void __thiscall gbPartEmitter::LoadFromFile(class gbVFile *);  // 0x29CF0
    void __thiscall gbPartEmitter::SetLoopEmit(bool);  // 0x2C3C0
    class gbPartEmitter & __thiscall gbPartEmitter::operator=(class gbPartEmitter const &);  // 0xD600
};

// 8 methods
class gbRefObject {
public:
    __thiscall gbRefObject::gbRefObject(class gbRefObject const &);  // 0x17C0
    __thiscall gbRefObject::gbRefObject(void);  // 0x15E0
    virtual __thiscall gbRefObject::~gbRefObject(void);  // 0x2F7E0
    void __thiscall gbRefObject::DecRef(void);  // 0x1610
    int __thiscall gbRefObject::GetRef(void);  // 0x17B0
    void __thiscall gbRefObject::IncRef(void);  // 0x1600
    void __thiscall gbRefObject::Release(void);  // 0x2F7F0
    class gbRefObject & __thiscall gbRefObject::operator=(class gbRefObject const &);  // 0x3980
};

// 8 methods
class gbResManager {
public:
    __thiscall gbResManager::gbResManager(class gbResManager const &);  // 0x52A0
    __thiscall gbResManager::gbResManager(void);  // 0x20190
    __thiscall gbResManager::~gbResManager(void);  // 0x201A0
    void __thiscall gbResManager::AddResource(class gbResource *);  // 0x20200
    void __thiscall gbResManager::CleanAllResource(void);  // 0x20320
    void __thiscall gbResManager::DelResource(class gbResource *);  // 0x20280
    class gbResource * __thiscall gbResManager::FindResByName(char const *);  // 0x201B0
    class gbResManager & __thiscall gbResManager::operator=(class gbResManager const &);  // 0x19B0
};

// 8 methods
class gbVTextFile {
public:
    __thiscall gbVTextFile::gbVTextFile(char *);  // 0x30FB0
    __thiscall gbVTextFile::gbVTextFile(void);  // 0x30FA0
    __thiscall gbVTextFile::~gbVTextFile(void);  // 0x30FE0
    void __thiscall gbVTextFile::Close(void);  // 0x310E0
    void __thiscall gbVTextFile::Open(char *);  // 0x31050
    char * __thiscall gbVTextFile::ReadLine(void);  // 0x31190
    void __thiscall gbVTextFile::Rewind(void);  // 0x31170
    class gbVTextFile & __thiscall gbVTextFile::operator=(class gbVTextFile const &);  // 0x5EF0
};

// 7 methods
class gbBinaryTreeNode {
public:
    __thiscall gbBinaryTreeNode::gbBinaryTreeNode(class gbBinaryTreeNode const &);  // 0x46E0
    __thiscall gbBinaryTreeNode::gbBinaryTreeNode(void);  // 0x46C0
    virtual __thiscall gbBinaryTreeNode::~gbBinaryTreeNode(void);  // 0x30100
    class gbBinaryTreeNode * __thiscall gbBinaryTreeNode::GetFather(void);  // 0x17B0
    class gbBinaryTreeNode * __thiscall gbBinaryTreeNode::GetLeft(void);  // 0x39F0
    class gbBinaryTreeNode * __thiscall gbBinaryTreeNode::GetRight(void);  // 0x3CC0
    class gbBinaryTreeNode & __thiscall gbBinaryTreeNode::operator=(class gbBinaryTreeNode const &);  // 0x4710
};

// 7 methods
class gbResource {
public:
    __thiscall gbResource::gbResource(class gbResource const &);  // 0x1860
    __thiscall gbResource::gbResource(void);  // 0x1840
    virtual __thiscall gbResource::~gbResource(void);  // 0x200D0
    char const * __thiscall gbResource::GetName(void);  // 0x39F0
    unsigned int __thiscall gbResource::GetNameCrc32(void);  // 0x3CC0
    void __thiscall gbResource::SetName(char const *);  // 0x20040
    class gbResource & __thiscall gbResource::operator=(class gbResource const &);  // 0x18A0
};

// 7 methods
class gbRotMatrix {
public:
    __thiscall gbRotMatrix::gbRotMatrix(void);  // 0x26310
    bool const __thiscall gbRotMatrix::IsOrthonormal(void);  // 0x26480
    bool const __thiscall gbRotMatrix::IsValid(void);  // 0x26450
    void __thiscall gbRotMatrix::LoadIdentity(void);  // 0x26430
    void __thiscall gbRotMatrix::Rotate(struct gbVec3D *,struct gbVec3D *);  // 0x263D0
    void __thiscall gbRotMatrix::operator*=(struct gbRotMatrix &);  // 0x26350
    void __thiscall gbRotMatrix::operator=(struct gbRotMatrix &);  // 0x26330
};

// 7 methods
class gbPixelFormat {
public:
    void __thiscall gbPixelFormat::Convert(unsigned char *,class gbPixelFormat *,unsigned char *,int);  // 0x1FCA0
    void __thiscall gbPixelFormat::Init(int,unsigned int,unsigned int,unsigned int,unsigned int);  // 0x1FA10
    void __thiscall gbPixelFormat::Init(int,struct gbColorQuad *);  // 0x1F7D0
    void __thiscall gbPixelFormat::Init(class gbPixelFormat *);  // 0x1FC00
    void __thiscall gbPixelFormat::Init(enum gbPixelFmtType);  // 0x1F820
    void __thiscall gbPixelFormat::Release(void);  // 0x1FC90
    class gbPixelFormat & __thiscall gbPixelFormat::operator=(class gbPixelFormat const &);  // 0x40D0
};

// 6 methods
class gbActorMgr {
public:
    __thiscall gbActorMgr::gbActorMgr(class gbActorMgr const &);  // 0x52A0
    __thiscall gbActorMgr::gbActorMgr(class gbGfxManager *);  // 0x35A0
    __thiscall gbActorMgr::~gbActorMgr(void);  // 0x3620
    void __thiscall gbActorMgr::DestroyActor(class gbActor *);  // 0x37E0
    class gbActor * __thiscall gbActorMgr::LoadActorFile(char *);  // 0x3680
    class gbActorMgr & __thiscall gbActorMgr::operator=(class gbActorMgr const &);  // 0x19B0
};

// 6 methods
class gbColorFlt {
public:
    __thiscall gbColorFlt::gbColorFlt(float,float,float);  // 0x38A0
    __thiscall gbColorFlt::gbColorFlt(float,float,float,float);  // 0x38C0
    __thiscall gbColorFlt::gbColorFlt(void);  // 0xD950
    int __thiscall gbColorFlt::operator!=(struct gbColorFlt &);  // 0x38E0
    void __thiscall gbColorFlt::operator+=(struct gbColorFlt const &);  // 0x3930
    struct gbColorFlt & __thiscall gbColorFlt::operator=(struct gbColorFlt const &);  // 0x300C0
};

// 6 methods
class gbDropGroup {
public:
    __thiscall gbDropGroup::gbDropGroup(class gbDropGroup const &);  // 0x328E0
    __thiscall gbDropGroup::gbDropGroup(int,struct gbDropDesc const *,char const *);  // 0x31E40
    virtual __thiscall gbDropGroup::~gbDropGroup(void);  // 0x32120
    void __thiscall gbDropGroup::CreateUnit(float,class gbCamera *);  // 0x31FE0
    void __thiscall gbDropGroup::Render(class gbCamera *);  // 0x31F40
    class gbDropGroup & __thiscall gbDropGroup::operator=(class gbDropGroup const &);  // 0x32960
};

// 6 methods
class gbPrintFontMgr {
public:
    __thiscall gbPrintFontMgr::gbPrintFontMgr(void);  // 0x22F40
    void __thiscall gbPrintFontMgr::Flush(void);  // 0x231B0
    void __thiscall gbPrintFontMgr::Flush3D(void);  // 0x231D0
    class gbPrintFont * __thiscall gbPrintFontMgr::GetFont(enum gbFontType);  // 0x4450
    int __thiscall gbPrintFontMgr::Init(class gbGfxManager *);  // 0x22F60
    void __thiscall gbPrintFontMgr::Release(void);  // 0x23150
};

// 6 methods
class gbRain {
public:
    __thiscall gbRain::gbRain(class gbRain const &);  // 0x32A50
    __thiscall gbRain::gbRain(int,struct gbDropDesc const *,char const *);  // 0x320F0
    virtual __thiscall gbRain::~gbRain(void);  // 0x32120
    virtual void __thiscall gbRain::Draw(void);  // 0x321F0
    virtual void __thiscall gbRain::Update(float);  // 0x32150
    class gbRain & __thiscall gbRain::operator=(class gbRain const &);  // 0x32960
};

// 6 methods
class gbSnow {
public:
    __thiscall gbSnow::gbSnow(class gbSnow const &);  // 0x32B30
    __thiscall gbSnow::gbSnow(int,struct gbDropDesc const *,char const *,float);  // 0x324A0
    virtual __thiscall gbSnow::~gbSnow(void);  // 0x32120
    virtual void __thiscall gbSnow::Draw(void);  // 0x325B0
    virtual void __thiscall gbSnow::Update(float);  // 0x324D0
    class gbSnow & __thiscall gbSnow::operator=(class gbSnow const &);  // 0x32BC0
};

// 6 methods
class gbVFile1 {
public:
    char * __thiscall gbVFile1::GetDir(char *,int);  // 0x30180
    unsigned int __thiscall gbVFile1::GetEntry(void);  // 0x17B0
    char * __thiscall gbVFile1::GetFileName(char *,int);  // 0x30130
    char * __thiscall gbVFile1::GetFullPath(void);  // 0x5E20
    char * __thiscall gbVFile1::GetTitle(char *,int);  // 0x301D0
    class gbVFile1 & __thiscall gbVFile1::operator=(class gbVFile1 const &);  // 0x5E30
};

// 5 methods
class gbAABBox {
public:
    __thiscall gbAABBox::gbAABBox(void);  // 0x3840
    int __thiscall gbAABBox::IsColAABB(struct gbAABBox &);  // 0x27BA0
    int __thiscall gbAABBox::IsColPoint(struct gbVec3D &);  // 0x27B40
    void __thiscall gbAABBox::Transform(struct gbMatrix4 *);  // 0x279E0
    struct gbAABBox & __thiscall gbAABBox::operator=(struct gbAABBox const &);  // 0xD3C0
};

// 5 methods
class gbBinaryTree {
public:
    __thiscall gbBinaryTree::gbBinaryTree(void);  // 0x4690
    __thiscall gbBinaryTree::~gbBinaryTree(void);  // 0x300F0
    class gbBinaryTreeNode * __thiscall gbBinaryTree::GetRoot(void);  // 0x46A0
    void __thiscall gbBinaryTree::SetRoot(class gbBinaryTreeNode *);  // 0x4790
    class gbBinaryTree & __thiscall gbBinaryTree::operator=(class gbBinaryTree const &);  // 0x46B0
};

// 5 methods
class gbColorQuad {
public:
    __thiscall gbColorQuad::gbColorQuad(struct gbColorQuad &);  // 0x46B0
    __thiscall gbColorQuad::gbColorQuad(unsigned char,unsigned char,unsigned char);  // 0x13F0
    __thiscall gbColorQuad::gbColorQuad(unsigned char,unsigned char,unsigned char,unsigned char);  // 0x1510
    __thiscall gbColorQuad::gbColorQuad(void);  // 0xD950
    struct gbColorQuad & __thiscall gbColorQuad::operator=(struct gbColorQuad const &);  // 0x46B0
};

// 5 methods
class gbNBTree {
public:
    __thiscall gbNBTree::gbNBTree(void);  // 0x4690
    __thiscall gbNBTree::~gbNBTree(void);  // 0x300F0
    class gbNBTreeNode * __thiscall gbNBTree::GetRoot(void);  // 0x46A0
    void __thiscall gbNBTree::SetRoot(class gbNBTreeNode *);  // 0x4790
    class gbNBTree & __thiscall gbNBTree::operator=(class gbNBTree const &);  // 0x46B0
};

// 5 methods
class gbSphere {
public:
    __thiscall gbSphere::gbSphere(void);  // 0x3810
    int __thiscall gbSphere::IsColPoint(struct gbVec3D &);  // 0x27860
    int __thiscall gbSphere::IsColSphere(struct gbVec3D &,float);  // 0x278B0
    int __thiscall gbSphere::IsColTriangle(struct gbVec3D &,struct gbVec3D &,struct gbVec3D &);  // 0x27920
    struct gbSphere & __thiscall gbSphere::operator=(struct gbSphere const &);  // 0x3820
};

// 5 methods
class gbTextureArray {
public:
    __thiscall gbTextureArray::gbTextureArray(class gbTexture *,class gbTexture *);  // 0x41E0
    __thiscall gbTextureArray::gbTextureArray(class gbTexture *);  // 0x41C0
    __thiscall gbTextureArray::gbTextureArray(void);  // 0x41B0
    void __thiscall gbTextureArray::SetTexture(class gbTexture *);  // 0x4200
    struct gbTextureArray & __thiscall gbTextureArray::operator=(struct gbTextureArray const &);  // 0x4210
};

// 4 methods
class CPKFile {
public:
    __thiscall CPKFile::CPKFile(void);  // 0x5D80
    __thiscall CPKFile::~CPKFile(void);  // 0x24140
    void * __thiscall CPKFile::GetRealData(void);  // 0x4230
    class CPKFile & __thiscall CPKFile::operator=(class CPKFile const &);  // 0x5D90
};

// 4 methods
class gbCamQuakeControl {
public:
    __thiscall gbCamQuakeControl::gbCamQuakeControl(class gbCamQuakeControl const &);  // 0x5CB0
    __thiscall gbCamQuakeControl::gbCamQuakeControl(void);  // 0x5C90
    virtual void __thiscall gbCamQuakeControl::Update(double);  // 0x21830
    class gbCamQuakeControl & __thiscall gbCamQuakeControl::operator=(class gbCamQuakeControl const &);  // 0x5D20
};

// 4 methods
class gbCamSpringControl {
public:
    __thiscall gbCamSpringControl::gbCamSpringControl(class gbCamSpringControl const &);  // 0x5BC0
    __thiscall gbCamSpringControl::gbCamSpringControl(void);  // 0x5B90
    virtual void __thiscall gbCamSpringControl::Update(double);  // 0x21700
    class gbCamSpringControl & __thiscall gbCamSpringControl::operator=(class gbCamSpringControl const &);  // 0x5C30
};

// 4 methods
class gbChain1DNode {
public:
    __thiscall gbChain1DNode::gbChain1DNode(class gbChain1DNode const &);  // 0x3960
    __thiscall gbChain1DNode::gbChain1DNode(void);  // 0x3950
    virtual __thiscall gbChain1DNode::~gbChain1DNode(void);  // 0x2EA40
    class gbChain1DNode & __thiscall gbChain1DNode::operator=(class gbChain1DNode const &);  // 0x3980
};

// 4 methods
class gbChain2DNode {
public:
    __thiscall gbChain2DNode::gbChain2DNode(class gbChain2DNode const &);  // 0x3A30
    __thiscall gbChain2DNode::gbChain2DNode(void);  // 0x3A20
    virtual __thiscall gbChain2DNode::~gbChain2DNode(void);  // 0x3A10
    class gbChain2DNode & __thiscall gbChain2DNode::operator=(class gbChain2DNode const &);  // 0x3A50
};

// 4 methods
class gbPartParamControl {
public:
    __thiscall gbPartParamControl::gbPartParamControl(void);  // 0xCD90
    void __thiscall gbPartParamControl::GetValue(float *,float);  // 0x299B0
    void __thiscall gbPartParamControl::LoadFromFile(class gbVFile *);  // 0x298E0
    class gbPartParamControl & __thiscall gbPartParamControl::operator=(class gbPartParamControl const &);  // 0xCDF0
};

// 4 methods
class gbPlane {
public:
    __thiscall gbPlane::gbPlane(void);  // 0xD360
    int __thiscall gbPlane::IsColAABB(struct gbAABBox &);  // 0x28DE0
    int __thiscall gbPlane::IsColOBB(struct gbOBBox &);  // 0x28EB0
    struct gbPlane & __thiscall gbPlane::operator=(struct gbPlane const &);  // 0x3820
};

// 4 methods
class gbVolumeModifier {
public:
    __thiscall gbVolumeModifier::gbVolumeModifier(class gbVolumeModifier const &);  // 0x5300
    __thiscall gbVolumeModifier::gbVolumeModifier(void);  // 0x52F0
    virtual __thiscall gbVolumeModifier::~gbVolumeModifier(void);  // 0x5670
    class gbVolumeModifier & __thiscall gbVolumeModifier::operator=(class gbVolumeModifier const &);  // 0x3980
};

// 4 methods
class gbUIRect {
public:
    void __thiscall gbUIRect::Init(char *,float,float,float,float,class gbGfxManager *);  // 0x22700
    void __thiscall gbUIRect::Release(void);  // 0x22750
    void __thiscall gbUIRect::Render(int);  // 0x9420
    class gbUIRect & __thiscall gbUIRect::operator=(class gbUIRect const &);  // 0x226E0
};

// 3 methods
class gbCamControler {
public:
    __thiscall gbCamControler::gbCamControler(class gbCamControler const &);  // 0x5B30
    __thiscall gbCamControler::gbCamControler(void);  // 0x5B20
    class gbCamControler & __thiscall gbCamControler::operator=(class gbCamControler const &);  // 0x5B60
};

// 3 methods
class gbParticleUnit {
public:
    __thiscall gbParticleUnit::gbParticleUnit(struct gbParticleUnit &);  // 0xCF00
    __thiscall gbParticleUnit::gbParticleUnit(void);  // 0xCEE0
    struct gbParticleUnit & __thiscall gbParticleUnit::operator=(struct gbParticleUnit const &);  // 0xCF90
};

// 3 methods
class gbVFile {
public:
    __thiscall gbVFile::gbVFile(void);  // 0x5E50
    __thiscall gbVFile::~gbVFile(void);  // 0x24140
    class gbVFile & __thiscall gbVFile::operator=(class gbVFile const &);  // 0x5E70
};

// 3 methods
class gbTimeCounter {
public:
    double __thiscall gbTimeCounter::Off(void);  // 0x2FF70
    void __thiscall gbTimeCounter::On(void);  // 0x2FF00
    class gbTimeCounter & __thiscall gbTimeCounter::operator=(class gbTimeCounter const &);  // 0x300C0
};

// 2 methods
class gbAudioMgrDesc {
public:
    __thiscall gbAudioMgrDesc::gbAudioMgrDesc(void);  // 0x1000
    struct gbAudioMgrDesc & __thiscall gbAudioMgrDesc::operator=(struct gbAudioMgrDesc const &);  // 0x21A0
};

// 2 methods
class gbDropUnit {
public:
    __thiscall gbDropUnit::gbDropUnit(void);  // 0x32870
    struct gbDropUnit & __thiscall gbDropUnit::operator=(struct gbDropUnit const &);  // 0x32890
};

// 2 methods
class gbEmitterData {
public:
    __thiscall gbEmitterData::gbEmitterData(void);  // 0xD360
    struct gbEmitterData & __thiscall gbEmitterData::operator=(struct gbEmitterData const &);  // 0xD370
};

// 2 methods
class gbEmitterSquare {
public:
    __thiscall gbEmitterSquare::gbEmitterSquare(void);  // 0x3840
    struct gbEmitterSquare & __thiscall gbEmitterSquare::operator=(struct gbEmitterSquare const &);  // 0xD3C0
};

// 2 methods
class gbImage2DInfo {
public:
    int __thiscall gbImage2DInfo::IsPreferAlpha(void);  // 0x1E470
    struct gbImage2DInfo & __thiscall gbImage2DInfo::operator=(struct gbImage2DInfo const &);  // 0x40F0
};

// 1 methods
class gbDropDesc {
public:
    struct gbDropDesc & __thiscall gbDropDesc::operator=(struct gbDropDesc const &);  // 0x32850
};

// 1 methods
class gbGfxManager_D3D {
public:
    void __thiscall gbGfxManager_D3D::SetTexture(struct gbTextureArray *);  // 0x1B410
};

#endif // GBENGINE_API_H