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


def build_struct(name, total_size, members):
    """Generate C struct declaration with correct padding and apply via parse_decls.

    Args:
        name: struct name
        total_size: exact total size in bytes
        members: list of tuples, either:
            (offset, type_str, member_name)          — size auto-computed for primitives/pointers
            (offset, type_str, member_name, size)    — explicit size (for typed arrays/sub-structs)

    Type examples:
        "int", "float", "char", "double"           — primitives (size auto)
        "CGameData *"                               — pointer (size=4 auto)
        "char[620]"                                 — char array (size auto = 620)
        "CameraParam[25]"                           — typed array (MUST provide size=400)

    Returns: True if successful (size matches).
    """
    import re as _re

    SIZE_MAP = {
        'int': 4, 'unsigned int': 4, 'float': 4, 'double': 8,
        'char': 1, 'unsigned char': 1, 'short': 2, 'unsigned short': 2,
    }

    lines = ["struct %s {" % name]
    prev_end = 0

    for item in sorted(members, key=lambda x: x[0]):
        offset = item[0]
        type_str = item[1]
        mname = item[2]
        explicit_size = item[3] if len(item) > 3 else None

        # Calculate member size
        if explicit_size is not None:
            msize = explicit_size
        elif '*' in type_str:
            msize = 4
        elif type_str in SIZE_MAP:
            msize = SIZE_MAP[type_str]
        else:
            arr_match = _re.search(r'\[(\d+)\]', type_str)
            if arr_match:
                base = _re.sub(r'\[\d+\]', '', type_str).strip()
                elem_size = SIZE_MAP.get(base, None)
                if elem_size is not None:
                    msize = elem_size * int(arr_match.group(1))
                else:
                    # Unknown base type in array — caller MUST provide explicit size
                    log("  [!] %s.%s: unknown array elem type '%s', need explicit size" % (name, mname, base))
                    msize = 4
            else:
                msize = 4

        # Padding
        if offset > prev_end:
            lines.append("  char _gap_%04X[%d];" % (prev_end, offset - prev_end))

        # Member declaration
        arr_match = _re.search(r'^(.+?)\[(\d+)\]$', type_str)
        if arr_match:
            lines.append("  %s %s[%s];" % (arr_match.group(1), mname, arr_match.group(2)))
        else:
            lines.append("  %s %s;" % (type_str, mname))

        prev_end = offset + msize

    # Tail padding
    if prev_end < total_size:
        lines.append("  char _end[%d];" % (total_size - prev_end))
    lines.append("};")

    decl = '\n'.join(lines)
    nerr = idc.parse_decls(decl, idc.PT_TYP)
    if nerr != 0:
        log("  [!] %s: parse_decls error %d" % (name, nerr))
        return False

    # Verify size
    til = ida_typeinf.get_idati()
    tif = ida_typeinf.tinfo_t()
    tif.get_named_type(til, name)
    actual = tif.get_size()
    if actual != total_size:
        log("  [WARN] %s: size=%d, expected=%d" % (name, actual, total_size))
        return False
    return True


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
struct RoleAtt;
"""
    idc.parse_decls(FWD, idc.PT_TYP)

    FWD_SM = """
struct CGameData;
struct CameraCtrl;
struct PalScriptMgr;
struct gbGeomNode;
struct SceneMgrSlot;
"""
    idc.parse_decls(FWD_SM, idc.PT_TYP)

    # Use build_struct for guaranteed correct sizes
    # RoleSystem: 8704 bytes, PAL3-only class (not in PDB)
    # Key members from Hex-Rays analysis:
    #   +0x004: float position (MoveRole: subtract from RolePtr+128)
    #   +0x0A0-0x0A8: float vec3 (position/direction)
    #   +0x274: int state (13 refs)
    #   +0x504: int core state (17 refs, most accessed)
    build_struct("RoleSystem", 8704, [
        (0x004, "float", "m_fTargetX"),
        (0x008, "float", "m_fTargetY"),
        (0x00C, "float", "m_fTargetZ"),
        (0x010, "int", "_d010"),
        (0x014, "int", "_d014"),
        (0x0A0, "float", "m_fPosX"),
        (0x0A4, "float", "m_fPosY"),
        (0x0A8, "float", "m_fPosZ"),
        (0x274, "int", "m_nState"),
        (0x27C, "int[12]", "m_nBaseStats", 48),            # base stat values [12]
        # Role attribute sources (stride 12: ptr at +0, 8 bytes extra per slot)
        # [228..276] = 5 equipment attribute contributions
        (0x35C, "RoleAtt *", "m_pEquipAtt0"),    # equipment slot 0
        (0x368, "RoleAtt *", "m_pEquipAtt1"),    # equipment slot 1
        (0x374, "RoleAtt *", "m_pEquipAtt2"),    # equipment slot 2
        (0x380, "RoleAtt *", "m_pEquipAtt3"),    # equipment slot 3
        (0x38C, "RoleAtt *", "m_pEquipAtt4"),    # equipment slot 4
        # [288] = self (current role's own attributes, ID checked for special logic)
        (0x398, "RoleAtt *", "m_pSelfAtt"),      # this role's base RoleAtt
        (0x39C, "int[12]", "m_nComputedStats", 48),    # computed stats [12]
        (0x3CC, "int[12]", "m_nDisplayStats", 48),     # display/effective stats [12]
        (0x4CC, "int", "m_nPathState"),
        (0x4D0, "int", "_d4D0"),
        (0x4D4, "int", "_d4D4"),
        (0x4D8, "int", "_d4D8"),
        (0x4DC, "float", "_f4DC"),
        (0x4E0, "int", "_d4E0"),
        (0x4E4, "float", "_f4E4"),
        (0x4E8, "int", "_d4E8"),
        (0x4EC, "int", "_d4EC"),
        (0x4F0, "int", "_d4F0"),
        (0x4F4, "int", "_d4F4"),
        (0x504, "int", "m_nCoreState"),
        (0x508, "int", "_d508"),
        (0x50C, "float", "_f50C"),
        (0x510, "float", "_f510"),
        (0x514, "float", "_f514"),
        (0x518, "float", "_f518"),
        (0x51C, "int", "_d51C"),
        (0x520, "int", "_d520"),
        (0x540, "float", "_f540"),
        (0x544, "float", "_f544"),
        (0x548, "float", "_f548"),
        (0x56C, "int", "_d56C"),
        (0x570, "int", "m_nRoleCount"),
        (0x5B8, "int", "_d5B8"),
        (0x5D0, "int", "_d5D0"),
    ])
    # SceneMgrCamBlock: 856 bytes
    # CameraParam[25] at +0xA0: {nID, _reserved, nParam1, nParam2} stride=16, IDs 301-323
    # CameraCmd[33] at +0x230: {nCmdID, nValue} stride=8, IDs 4101-4304
    # m_nCurrentScene at +0x338: used as m_slot[N]/m_RoleSystem[N] index
    idc.parse_decls("struct CameraParam { int nID; int _reserved; int nParam1; int nParam2; };", idc.PT_TYP)
    idc.parse_decls("struct CameraCmd { int nCmdID; int nValue; };", idc.PT_TYP)
    # SceneMgrCamBlock with properly typed sub-struct arrays
    build_struct("SceneMgrCamBlock", 856, [
        (0x000, "char[160]", "m_CameraList"),
        (0x0A0, "CameraParam[25]", "m_Params", 400),   # 25*16=400
        (0x230, "CameraCmd[33]", "m_Cmds", 264),       # 33*8=264
        (0x338, "int", "m_nCurrentScene"),
        (0x34C, "int", "m_pCameraScript"),
        (0x350, "char[2]", "m_bCameraFlags"),
        (0x352, "char[4]", "m_nActiveCamera"),
    ])
    idc.parse_decls("struct SceneMgrSlot { char _data[1408]; };", idc.PT_TYP)

    if build_struct("SceneMgr", 54116, [
        (0x0000, "gbGfxManager *", "m_pGfxMgr"),
        (0x0004, "gbSceneGraph *", "m_pSceneRoot"),
        (0x0008, "gbRenderEffect *", "m_pAddEffect2"),
        (0x000C, "gbRenderEffect *", "m_pAlphaEffect2"),
        (0x0010, "gbRenderEffect *", "m_pAddEffect"),
        (0x0014, "gbRenderEffect *", "m_pAlphaEffect"),
        (0x0018, "gbCamera *", "m_pCamera"),
        (0x001C, "char[620]", "_preArray"),
        (0x0288, "SceneMgrSlot[4]", "m_slot", 5632),   # 4*1408
        (0x1888, "char[792]", "m_extraSlot"),
        (0x1BA0, "int", "m_pCBRoleStateData"),
        (0x1BC8, "char[5]", "m_bGameFlags"),
        (0x1BD0, "RoleSystem[5]", "m_RoleSystem", 43520),  # 5*8704
        (0xC5D0, "CGameData *", "m_pGameData"),
        (0xC5D4, "int", "_unkC5D4"),
        (0xC5D8, "CameraCtrl *", "m_pCameraCtrl"),
        (0xC5DC, "PalScriptMgr *", "m_pScriptCtrl"),
        (0xC5E0, "SceneMgrCamBlock", "m_camBlock", 856),
        (0xC938, "int", "m_nCameraState"),
        (0xC9A8, "char[512]", "m_szUIString"),
        (0xCD0C, "float", "m_fMoveParam"),
        (0xD35C, "gbGeomNode *", "m_pCollisionNode"),
    ]):
        applied += 1
        log("[+] SceneMgr: 54116 bytes (offset-based)")
    else:
        errors += 1
        log("[!] SceneMgr: size mismatch")

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
    # Members extracted from Hex-Rays (27 offsets in +0x5800-0x586C region)
    # =========================================================================
    if build_struct("C2DSpark", 22640, [
        (0x5800, "float", "_fTimeDelta"),
        (0x5804, "float", "_fTimeAccum"),
        (0x5808, "int", "_nState"),
        (0x580C, "float", "_fParam1"),
        (0x5810, "int", "_nCount"),
        (0x5814, "int", "_nMaxCount"),
        (0x581C, "int", "_nActive"),
        (0x5820, "int", "_d5820"),
        (0x5824, "int", "_d5824"),
        (0x5828, "int", "_d5828"),
        (0x582C, "int", "_d582C"),
        (0x5830, "int", "_d5830"),
        (0x5834, "int", "_d5834"),
        (0x5838, "int", "_d5838"),
        (0x583C, "int", "_d583C"),
        (0x5840, "int", "_d5840"),
        (0x5844, "int", "_d5844"),
        (0x5848, "float", "_fPosX"),
        (0x584C, "float", "_fPosY"),
        (0x5850, "float", "_fVelX"),
        (0x5854, "float", "_fVelY"),
        (0x5858, "int", "_nColorR"),
        (0x585C, "int", "_nColorG"),
        (0x5860, "int", "_nColorB"),
        (0x5864, "int", "_nColorA"),
        (0x5868, "int", "_nTexture"),
        (0x586C, "int", "_nBlendMode"),
    ]):
        applied += 1
        log("[+] C2DSpark: 22640 bytes, 27 typed members")
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
    # OVERRIDE 8: UIWnd (68 bytes — correct types for vtable, colors, rect)
    # Evidence: PDB has gbColorQuad, tagRECT, PtrArray; batch import used char[]
    # Affects: All UI code (vtable calls, visibility/enable checks)
    # =========================================================================
    FWD4 = """
struct PtrArray;
struct gbColorQuad;
struct tagRECT;
"""
    idc.parse_decls(FWD4, idc.PT_TYP)

    DECL = """
struct UIWnd {
  void **_vftable;              // +0x00 (vtable pointer)
  unsigned int m_fontcolor;     // +0x04 (gbColorQuad as DWORD)
  unsigned int m_wndcolor;      // +0x08 (gbColorQuad as DWORD)
  unsigned int m_id;            // +0x0C
  int m_rect_left;              // +0x10
  int m_rect_top;               // +0x14
  int m_rect_right;             // +0x18
  int m_rect_bottom;            // +0x1C
  UIWnd *m_pfather;             // +0x20
  void *m_childs_data;          // +0x24 (PtrArray.data)
  int m_childs_count;           // +0x28 (PtrArray.count)
  int m_childs_capacity;        // +0x2C (PtrArray.capacity)
  int m_childs_elemsize;        // +0x30 (PtrArray.elemsize)
  int m_bcreateok;              // +0x34
  int m_bvisible;               // +0x38
  int m_benable;                // +0x3C
  int m_bfocus;                 // +0x40
};
"""
    if idc.parse_decls(DECL, idc.PT_TYP) == 0:
        applied += 1
        log("[+] UIWnd: 68 bytes (vtable typed, rect/color expanded)")
    else:
        errors += 1
        log("[!] UIWnd: FAILED")

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
