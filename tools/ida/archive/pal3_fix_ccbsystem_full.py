"""Import full CCBSystem struct with all typed members (verified size=90840)."""
import ida_auto, ida_typeinf, idc

ida_auto.auto_wait()

# Forward declarations and enums
PREAMBLE = """
struct CCBSystem;
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
idc.parse_decls(PREAMBLE, idc.PT_TYP)

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

nerr = idc.parse_decls(DECL, idc.PT_TYP)
if nerr == 0:
    til = ida_typeinf.get_idati()
    tif = ida_typeinf.tinfo_t()
    tif.get_named_type(til, "CCBSystem")
    print("[+] CCBSystem: size=%d (expected ~90840)" % tif.get_size())
else:
    print("[!] CCBSystem parse errors: %d" % nerr)

idc.qexit(0)
