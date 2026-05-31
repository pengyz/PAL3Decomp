#include "SceneObjParam.h"
#pragma once
// Auto-generated: SceneObj

#include "pal3/pal3_stl.h"
#include "GlowObj.h"
#include "MyMdl.h"
#include "ObjectInfo.h"
#include "PalScriptWaitObj.h"
#include "SaveTask.h"
#include "SceneObj_SubObj.h"
#include "TaskMgr.h"
#include "gbengine/gbengine_types.h"
#include "gbengine/gbengine_types.h"
#include "subPARAM.h"

class PalScript;
class PathObj;
class SceneMapObj;
class UIWnd;
class gbGeomNode;
class gbSound3DNode;
class gbVFileSystem;

class SceneObj : public PalScriptWaitObj, public GlowObj, public TaskMgr<SceneObjParam, unsigned long (__thiscall SceneObj::*)(unsigned long)> {
public:
    SaveTask _SaveTaskInfo; // +0x4C
    float m_fTime; // +0x58
    float m_fDeltaTime; // +0x5C
    float m_fTimeScale; // +0x60
    float m_deltatime; // +0x64
    int m_bLockPropUI; // +0x68
    unsigned char m_bLockCamera; // +0x6C
    int m_bProcessLinkObj; // +0x70
    int m_bCallProcessGroupObj; // +0x74
    int m_bMainGroupObj; // +0x78
    UINT dwEffGroupRunningID; // +0x7C
    unsigned char bCGObj; // +0x80
    char sCGSHELF[64]; // +0x81
    tagRECT rCGSelfArea; // +0xC4
    tagRECT rTouchAreaCG; // +0xD4
    float fLastTime; // +0xE4
    subPARAM mParam; // +0xE8
    gbVec3D mVelocity; // +0x130
    float mTime; // +0x13C
    gbVec3D mStorePos; // +0x140
    int mRetrorse; // +0x14C
    int mTouchCounter; // +0x150
    int m_iState; // +0x154
    unsigned char m_bCVDOver; // +0x158
    gbOBBox mOBBox; // +0x15C
    char m_pObjMsgBuffer[256]; // +0x1A8
    char m_pObjMsgBuffer2[256]; // +0x2A8
    gbVec3D m_renderpos; // +0x3A8
    SceneObj_SubObj m_subobj; // +0x3B4
    MyMdl m_mdl; // +0x3D8
    ObjectInfo m_info; // +0x42C
    PathObj * m_path; // +0x688
    SceneMapObj * m_pmap; // +0x68C
    unsigned char m_mapindex; // +0x690
    int m_pushboxdir; // +0x694
    tagRECT m_maprect; // +0x698
    int m_liftrole; // +0x6A8
    char m_common[48]; // +0x6AC
    gbSound3DNode * m_snd; // +0x6DC
    float m_radius; // +0x6E0
    PalScript * m_runscript; // +0x6E4
    float m_fRotateX; // +0x6E8
    float m_fRotateY; // +0x6EC
    float m_fRotateZ; // +0x6F0
    float m_fParam; // +0x6F4
    // total size: 0x6F8 (1784)

    char UpdateAutoDelete(UINT deltatime); // 0x00407B50
    int ctor(); // 0x00452FD0
    void * _scalar_dtor(char pData); // 0x00453010
    void ctor_3030(); // 0x00453030
    char ValidateState(); // 0x00453200
    char LoadData(); // 0x004538E0
    SceneObj * InsertAt(SceneObj *pSceneObj, UINT dwVal, UINT dwVal2); // 0x00453A70
    int GetVisibleFlag(_BYTE *p_BYTE); // 0x00527D40
    int _todo_527D60(); // 0x00527D60
    gbVFileSystem * LoadGeomFromFile(const char *pszName); // 0x0052F800
    gbVFileSystem * LoadObstruction(); // 0x0052FB70
    gbGeomNode * LoadGeomNode(const char *pszFilename); // 0x00530280
    gbGeomNode * LoadDefaultModel(); // 0x00530330
    int SetScriptDel(int nVal); // 0x00530340
    int CreateUI(); // 0x00536260
    SceneObj * Destructor(); // 0x005362F0
    int CleanupInternal(); // 0x005363C0
    BOOL HandleEvent(int nVal, int nVal2); // 0x005368A0
    char * StringCopyReplace(char *pszBuf, char *pszBuf2); // 0x0053EE60
    static int LoadFromConfig(int *p_DWORD, int *p_DWORD2, int nVal); // 0x0053EF60
    void StringCopyCat(SceneObj *pSceneObj2); // 0x0053F060
};
