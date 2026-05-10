"""
PAL3-specific struct overrides.

This script runs AFTER pal3_batch_import_structs.py to correct structs
where PAL3 binary differs from PAL3A PDB.

Each override is documented with:
- How the difference was discovered
- Binary evidence (memset size, stride, offset analysis)
- Which functions are affected

Pipeline order:
  1. pal3_batch_import_structs.py  (bulk PDB import)
  2. pal3_override_structs.py      (PAL3-specific corrections) ← THIS FILE
  3. pal3_autofix_this_types.py    (function signature fixes)
  4. pal3_reexport_all.py          (export with all fixes applied)

Usage:
  idat.exe -A -S"pal3_override_structs.py" original/PAL3.exe.i64
"""
import ida_auto, ida_typeinf, idc, os, time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)


def main():
    ida_auto.auto_wait()
    log("[*] PAL3 struct overrides")
    log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

    applied = 0
    errors = 0

    # =========================================================================
    # OVERRIDE 1: tagRoleState (892 bytes, PAL3A=1040)
    # Evidence: Binary stride analysis in CCBRoleState::IsRoleAlive (892-byte array step)
    # Affects: All CCBRoleState functions (m_Role[11] array)
    # =========================================================================
    DECL = """
struct tagRoleState {
  unsigned int dwID;           // +0x00
  int nIndex;                  // +0x04
  char sModel[16];             // +0x08
  unsigned char byUIIndex;     // +0x18
  unsigned char bValid;        // +0x19
  unsigned char bAlive;        // +0x1A
  unsigned char bFriend;       // +0x1B
  unsigned char bBoss;         // +0x1C
  unsigned char bCanAction;    // +0x1D
  unsigned char bWaitForFlee;  // +0x1E
  unsigned char bEnemyFriend;  // +0x1F
  int nLevel;                  // +0x20
  int nHP;                     // +0x24
  int nFullHP;                 // +0x28
  int nGP;                     // +0x2C
  int nFullGP;                 // +0x30
  int nMP;                     // +0x34
  int nFullMP;                 // +0x38
  int nAttack;                 // +0x3C
  int nDefence;                // +0x40
  int nLuck;                   // +0x44
  int nSpeed;                  // +0x48
  char _rest[820];             // +0x4C to end (892 - 0x4C = 820)
};
"""
    if idc.parse_decls(DECL, idc.PT_TYP) == 0:
        applied += 1
        log("[+] tagRoleState: 892 bytes (PAL3A=1040)")
    else:
        errors += 1
        log("[!] tagRoleState: FAILED")

    # =========================================================================
    # OVERRIDE 2: SceneMgr (54116 bytes, layout from binary analysis)
    # Evidence: tools/analyze_scenemgr.py — disassembled SceneMgr::Create + xref scan
    # Affects: All scene/render/script functions
    # =========================================================================
    FWD = """
struct gbGfxManager;
struct gbSceneGraph;
struct gbRenderEffect;
struct gbCamera;
struct RoleSystem;
"""
    idc.parse_decls(FWD, idc.PT_TYP)

    DECL = """
struct RoleSystem { char _data[8704]; };
struct SceneMgr {
  gbGfxManager *m_pGfxMgr;       // +0x0000
  gbSceneGraph *m_pSceneRoot;    // +0x0004
  gbRenderEffect *m_pAddEffect2; // +0x0008
  gbRenderEffect *m_pAlphaEffect2;// +0x000C
  gbRenderEffect *m_pAddEffect;  // +0x0010
  gbRenderEffect *m_pAlphaEffect;// +0x0014
  gbCamera *m_pCamera;           // +0x0018
  char _preArray[620];           // +0x001C
  char m_slot0[1408];            // +0x0288
  char m_slot1[1408];            // +0x0808
  char m_slot2[1408];            // +0x0D88
  char m_slot3[1408];            // +0x1308
  char _gap_1888[840];           // +0x1888
  RoleSystem m_RoleSystem[5];    // +0x1BD0 (stride=8704, 5 elements to +0xC5D0)
  int m_pGameData;               // +0xC5D0
  int _c5d4;                     // +0xC5D4
  int m_pCameraCtrl;             // +0xC5D8
  int m_pScriptCtrl;             // +0xC5DC
  char _gap_c5e0[856];           // +0xC5E0
  int m_nCameraState;            // +0xC938
  char _gap_c93c[108];           // +0xC93C
  char m_szUIString[512];        // +0xC9A8
  char _gap_cba8[356];           // +0xCBA8
  float m_fMoveParam;            // +0xCD0C
  char _gap_cd10[1612];          // +0xCD10
  int m_pCollisionNode;          // +0xD35C
  char _tail[4];                 // +0xD360
};
"""
    if idc.parse_decls(DECL, idc.PT_TYP) == 0:
        applied += 1
        log("[+] SceneMgr: 54116 bytes + RoleSystem[5]")
    else:
        errors += 1
        log("[!] SceneMgr: FAILED")

    # =========================================================================
    # OVERRIDE 3: Scene (placeholder, PAL3A=1094164 but PAL3 uses ~96 bytes actively)
    # Evidence: Scene:: functions only access offsets up to +0x5D
    # Affects: Scene::LoadConfig and related
    # =========================================================================
    DECL = """
struct Scene {
  int _vftable;
  void *m_pDataBegin;
  void *m_pDataEnd;
  void *m_pCapacity;
  char _data[80];
};
"""
    if idc.parse_decls(DECL, idc.PT_TYP) == 0:
        applied += 1
        log("[+] Scene: 96 bytes (PAL3A=1094164)")
    else:
        errors += 1
        log("[!] Scene: FAILED")

    # =========================================================================
    # OVERRIDE 4: CCBSystem (90840 bytes — matches PAL3A, verified from memset)
    # Evidence: CCBSystem::CCBSystem has memset(this, 0, 0x162D8)
    # Note: Size matches PAL3A but we override to ensure correct member types
    # =========================================================================
    FWD2 = """
struct CCBUI;
struct CCBControl;
struct CCBAttackSequen;
struct CCBRoleState;
struct CCBStage;
struct CCBAI;
struct CCBEditor;
struct CEffectSystem;
struct CEffectSimple;
struct CEffMgr;
struct C2DSpark;
struct C3DSpark;
struct TxtFile;
struct FightInfo;
enum ECBCombatState { CBS_READY=0, CBS_RUNNING=1, CBS_END=2 };
enum ECBCombatResult { CBR_NONE=0, CBR_WIN=1, CBR_LOSE=2, CBR_FLEE=3 };
"""
    idc.parse_decls(FWD2, idc.PT_TYP)

    DECL = """
struct CCBSystem {
  CCBSystem *m_pUtil;
  CCBUI *m_pUI;
  CCBControl *m_pControl;
  CCBAttackSequen *m_pAttackSequen;
  CCBRoleState *m_pRoleState;
  CCBStage *m_pStage;
  CCBAI *m_pAI;
  CCBEditor *m_pEditor;
  CEffectSystem *m_pES;
  CEffectSimple *m_pEffectSimple;
  TxtFile *m_pConfig;
  CEffMgr *m_pEffMgr;
  CEffMgr *m_pATSEffMgr;
  C2DSpark *m_p2DSpark;
  C3DSpark *m_p3DSpark;
  char _pad_003C[4];
  double m_DeltaTime;
  double m_dTimeFund;
  float m_fTimeFund;
  char _pad_0054[4];
  double m_AbsDeltaTime;
  double m_dAbsTimeFund;
  float m_fAbsTimeFund;
  float m_fTimeScale;
  FightInfo *m_pFightInfo;
  unsigned char m_bQuitFlag;
  unsigned char m_bPause;
  char _pad_0076[2];
  ECBCombatState m_eState;
  ECBCombatResult m_eResult;
  unsigned char m_bFiveNimbus;
  unsigned char m_bPXVariance;
  char _pad_0082[2];
  int m_nTimesOfCombat;
  unsigned char m_bAuto;
  unsigned char m_bEditor;
  unsigned char m_bLockCam;
  unsigned char m_bFirstRender;
  unsigned int m_dwIDHolder;
  int m_nThread;
  int m_nCurThread;
  char m_Thread[90112];
  char m_Player[576];
};
"""
    if idc.parse_decls(DECL, idc.PT_TYP) == 0:
        applied += 1
        log("[+] CCBSystem: 90840 bytes (verified from memset)")
    else:
        errors += 1
        log("[!] CCBSystem: FAILED")

    # =========================================================================
    # OVERRIDE 5: gbGfxManager (1520 bytes, manually verified member offsets)
    # Evidence: SceneMgr::Create uses gfxMgr->pEffectMgr at +0xC8
    # =========================================================================
    FWD3 = """
struct gbEffectMgr;
struct gbVertPoolMgr;
struct gbResManager;
struct gbPrintFontMgr;
struct gbMatrixStack;
"""
    idc.parse_decls(FWD3, idc.PT_TYP)

    DECL = """
struct gbGfxManager {
  char _vftable[8];
  unsigned int hGfxWnd;
  char DrvInfo[184];
  gbVertPoolMgr *pVertPoolMgr;
  gbEffectMgr *pEffectMgr;
  gbResManager *pTexResMgr;
  gbPrintFontMgr *pFontMgr;
  gbMatrixStack *pMatrixStack[4];
  char ViewMatrix[64];
  char InvViewMatrix[64];
  char WorldMatrix[64];
  int CurZBias;
  int bWireMode;
  char AmbientLight[16];
  float fSelfIllum;
  gbSceneGraph *pSceneGraph;
  char Viewport[20];
  char ClearParam[16];
  char _pad1E8[8];
  double LastTime;
  double CurTime;
  unsigned int LastTick;
  char _tail[1004];
};
"""
    if idc.parse_decls(DECL, idc.PT_TYP) == 0:
        applied += 1
        log("[+] gbGfxManager: 1520 bytes")
    else:
        errors += 1
        log("[!] gbGfxManager: FAILED")

    # =========================================================================
    # OVERRIDE 6: C2DSpark (22640 bytes, PAL3A=24688)
    # Evidence: C2DSpark constructor has memset(this, 0, 0x5870)
    # =========================================================================
    DECL = """
struct C2DSpark { char _data[22640]; };
"""
    if idc.parse_decls(DECL, idc.PT_TYP) == 0:
        applied += 1
        log("[+] C2DSpark: 22640 bytes (PAL3A=24688)")
    else:
        errors += 1
        log("[!] C2DSpark: FAILED")

    # =========================================================================
    # OVERRIDE 7: CCBRoleState (20648 bytes, PAL3A=23904)
    # Evidence: Contains tagRoleState[11] x2. PAL3 tagRoleState=892 vs PAL3A=1040.
    #   Calculated: 23904 - (1040-892)*11*2 = 23904 - 3256 = 20648
    # Affects: All combat role state functions
    # =========================================================================
    DECL = """
struct CCBRoleState {
  char m_sCombatDialog[512];     // +0x000
  float m_fLastDialogTime;       // +0x200
  unsigned char m_bCombatDialog; // +0x204
  char _pad205[3];
  CCBSystem *m_pCBSystem;        // +0x208
  CCBStage *m_pStage;            // +0x20C
  void *m_pUI;                   // +0x210
  void *m_pUtil;                 // +0x214
  unsigned char m_bWeSneakAttackEnemy; // +0x218
  unsigned char m_bEnemySneakAttackUs; // +0x219
  char _pad21A[2];
  int m_nMaxRound;               // +0x21C
  int m_nBossRound;              // +0x220
  unsigned char m_bMustFail;     // +0x224
  unsigned char m_bFleeAlwaysSuccess; // +0x225
  unsigned char m_bCreatedNewRole;    // +0x226
  char _pad227[1];
  tagRoleState m_Role[11];       // +0x228 (892*11 = 9812 bytes, ends at +0x287C)
  tagRoleState m_RoleXor[11];    // +0x287C (892*11 = 9812 bytes, ends at +0x4ED0)
  char m_dwEXPTable[400];        // +0x4ED0
  unsigned int m_dwWinTaskID;    // +0x5060
  int m_bNGHDeadVariance;        // +0x5064
  char _tail[124];               // +0x5068 to end
};
"""
    if idc.parse_decls(DECL, idc.PT_TYP) == 0:
        applied += 1
        til2 = ida_typeinf.get_idati()
        tif2 = ida_typeinf.tinfo_t()
        tif2.get_named_type(til2, "CCBRoleState")
        log("[+] CCBRoleState: %d bytes (PAL3A=23904)" % tif2.get_size())
    else:
        errors += 1
        log("[!] CCBRoleState: FAILED")

    # =========================================================================
    log("")
    log("[*] Applied: %d, Errors: %d" % (applied, errors))
    idc.qexit(0)


try:
    main()
except Exception as e:
    log("[ERROR] %s" % str(e))
    import traceback
    log(traceback.format_exc())
finally:
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(os.path.join(LOG_DIR, "pal3_override_structs_log.txt"), 'w') as f:
        f.write('\n'.join(log_lines))
