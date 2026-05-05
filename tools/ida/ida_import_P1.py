"""
IDAPython: 批量导入 PDB 结构体定义 (12 个)
自动生成 by gen_ida_struct_import.py
"""

import ida_auto
import ida_typeinf
import ida_hexrays
import ida_funcs
import ida_name
import idautils
import idc
import traceback
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "ida_import_P1_log.txt")
TEXT_START = 0x00401000
TEXT_END = 0x00558000

STRUCT_HEADER = r"""
struct NavigationInfo;
struct SceneMapObj;
struct Actor;
struct Role;
struct PtrArray;
struct MyMdl;
struct SceneObj;
struct Scene;
struct PalScript;

struct NavigationInfo {
    int m_numlayer;
    char m_tilelayer[328]; // NavTileLayer[2]
    char m_facelayer[32]; // NavFaceLayer[2]
};

struct SceneMapObj {
    char _gap_0[16];
    Scene * m_scene;
};

struct Actor {
    char m_actarray[16]; // std::vector<gbActor *,std::allocator<gbActor *> >
    gbActor * m_pact;
    char m_name[260];
    char m_szTexture[260];
    unsigned int m_dwMatMsg[11];
    unsigned char m_bChangedMat;
    char m_curact[8];
};

struct Role {
    char _gap_0[96];
    char m_cmdqueue[48]; // std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > >
    int m_bInView;
    char m_groundpos[12]; // gbVec3D
    char m_renderpos[12]; // gbVec3D
    char m_npcinfo[456]; // NPCInfo
    int m_onlayer;
    int m_active;
    unsigned char bCGMonster;
    int nCGMonsterID;
    int nCGMonsterType;
    unsigned char bRelive;
    unsigned char bInvincible;
    float fRattrapWait;
    float fMirrorWait;
    unsigned char bMirror;
    float fCGBIXIE;
    unsigned char bCGBIXIE;
    unsigned char bCrossAlpha;
    float fCrossAlpha;
    unsigned char bCGMonsterHitObj;
    unsigned char bStill;
    void * pCG_SceneProp;
    Actor m_actor;
    unsigned char m_MachineryID;
    int m_bPet;
    float m_scale;
    char m_tri[36]; // NavTriangle
    char m_specact[36]; // Role::SPECIAL_ACTION
    char m_ctrlmode[4]; // ROLE_CTRL
    char m_curbehaviour[4]; // ROLE_BEHAVIOUR
    int m_bPathOut;
    int m_bShowActAutoStand;
    unsigned char m_bNeedShowActEnd;
    char m_curact[4]; // ACTION_KIND
    float m_curspeed;
    float m_curforce;
    char m_velocity[12]; // gbVec3D
    char m_desirevel[12]; // gbVec3D
    char m_steer[12]; // gbVec3D
    char m_lastautodir[12]; // gbVec3D
    char m_targetpt[12]; // gbVec3D
    int m_targetlayer;
    int m_targetportal;
    char m_startpt[12]; // gbVec3D
    char m_wanderdir[12]; // gbVec3D
    int m_talkflag;
    Role * m_talknpc;
    PalScript * m_talkscript;
    char m_talkoldbeh[4]; // ROLE_BEHAVIOUR
    char m_talkoldact[4]; // ACTION_KIND
    float m_talkoldface;
    SceneObj * m_talkobj;
    int m_mstate;
    void * m_matt;
    float m_mfreedist;
    float m_mattackrange;
    float m_mfindradius;
    float m_statetime;
    gbGeomNode * m_weapon;
    unsigned char m_bLeftWeapon;
    unsigned char m_bRightWeapon;
    int m_nRad;
    int m_nRealHeadPos;
    int m_nOverlapState;
    char m_tpos[8]; // tagPOINT
    char m_vTagHeadPos[12]; // gbVec3D
    int m_overlap;
    int m_bPathMove;
    int m_pathMoveCounter;
    char m_lastpos[12]; // gbVec3D
    char m_notePos[12]; // gbVec3D
    char m_path[7208]; // PathObj
    float m_rotate;
    char m_wanapos[12]; // gbVec3D
};

struct PtrArray {
    void * m_pData;
    int m_nSize;
    int m_nMaxSize;
    int m_nGrowBy;
};

struct MyMdl {
    int m_mdltype;
    gbActor * m_actor;
    gbGeomNode * m_geom;
    MeshFx * m_fx;
    char box[76]; // gbOBBox
};

struct SceneObj {
    char _gap_0[76];
    char _SaveTaskInfo[12]; // SaveTask
    float m_fTime;
    float m_fDeltaTime;
    float m_fTimeScale;
    float m_deltatime;
    int m_bLockPropUI;
    unsigned char m_bLockCamera;
    int m_bProcessLinkObj;
    int m_bCallProcessGroupObj;
    int m_bMainGroupObj;
    unsigned int dwEffGroupRunningID;
    unsigned char bCGObj;
    char sCGSHELF[64];
    char rCGSelfArea[16]; // tagRECT
    char rTouchAreaCG[16]; // tagRECT
    float fLastTime;
    char mParam[72]; // subPARAM
    char mVelocity[12]; // gbVec3D
    float mTime;
    char mStorePos[12]; // gbVec3D
    int mRetrorse;
    int mTouchCounter;
    int m_iState;
    unsigned char m_bCVDOver;
    char mOBBox[76]; // gbOBBox
    char m_pObjMsgBuffer[256];
    char m_pObjMsgBuffer2[256];
    char m_renderpos[12]; // gbVec3D
    char m_subobj[36]; // SceneObj::SubObj
    MyMdl m_mdl;
    char m_info[604]; // ObjectInfo
    void * m_path;
    SceneMapObj * m_pmap;
    unsigned char m_mapindex;
    int m_pushboxdir;
    char m_maprect[16]; // tagRECT
    int m_liftrole;
    char m_common[48]; // std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >
    gbSound3DNode * m_snd;
    float m_radius;
    PalScript * m_runscript;
    float m_fRotateX;
    float m_fRotateY;
    float m_fRotateZ;
    float m_fParam;
};

struct Scene {
    char m_info[132]; // SceneInfo
    gbGeomNode * m_geomnode;
    gbVisNode * m_lights;
    char m_aabb[24]; // gbAABBox
    PtrArray m_bbArray;
    SceneMapObj m_objmap[2];
    int m_numobj;
    SceneObj m_obj[256];
    int m_numnpc;
    Role m_npc[72];
    NavigationInfo m_nav;
    gbGeomNode * m_cvd;
    NavigationInfo m_CamCollide;
    unsigned char m_bHasNavCollide;
    int m_bLoad;
    int m_battached;
    unsigned char m_lastobj;
    int m_bStar;
};

struct PalScript {
    unsigned char m_bLoadSceneScript;
    void * m_pinst;
    PtrArray m_waitobj;
    PtrArray m_CamObj;
};

"""


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        # Step 1: Parse all struct definitions
        log("[STEP 1] 导入结构体定义...")
        ret = idc.parse_decls(STRUCT_HEADER, idc.PT_TYP)
        log(f"  parse_decls 返回: {ret} (0=成功)")

        # Verify
        til = ida_typeinf.get_idati()
        count = 0
        for name in ['NavigationInfo', 'std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >', 'SceneMapObj', 'Role', 'Scene', 'std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > >', 'PalScript', 'Actor', 'PtrArray', 'MyMdl', 'std::vector<gbActor *,std::allocator<gbActor *> >', 'SceneObj']:
            tif = ida_typeinf.tinfo_t()
            if tif.get_named_type(til, name):
                count += 1
        log(f"  可访问结构体: {count}/12")

        # Step 2: Clear Hex-Rays cache for affected functions
        log("")
        log("[STEP 2] 清除 Hex-Rays 反编译缓存...")
        cleared = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            # Only clear functions belonging to imported classes
            cls = name.split("::")[0] if "::" in name else ""
            if cls in {'NavigationInfo', 'std::queue<SceneObj::Common_State,std::deque<SceneObj::Common_State,std::allocator<SceneObj::Common_State> > >', 'SceneMapObj', 'Role', 'Scene', 'std::queue<Role::ScriptCmd,std::deque<Role::ScriptCmd,std::allocator<Role::ScriptCmd> > >', 'PalScript', 'Actor', 'PtrArray', 'MyMdl', 'std::vector<gbActor *,std::allocator<gbActor *> >', 'SceneObj'}:
                try:
                    ida_hexrays.mark_cfunc_dirty(ea)
                    cleared += 1
                except:
                    pass
        log(f"  标记需重新反编译: {cleared} 个函数")

        # Step 3: Save
        log("")
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    import builtins
    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
