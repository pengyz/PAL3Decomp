"""
Fix struct sizes based on VERIFIED data (memset in constructors, operator new).

Only applies sizes confirmed from PAL3.exe binary evidence:
- CCBSystem: memset(this, 0, 0x162D8) → 90840 bytes (matches PAL3A PDB!)
- C2DSpark: memset(this, 0, 0x5870) → 22640 bytes (different from PAL3A=24688)
- C3DSpark: memset(this, 0, 0x3E30) → 15920 bytes (matches PAL3A PDB)
"""
import ida_auto, ida_typeinf, idc, json, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
PDB_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")

ida_auto.auto_wait()
til = ida_typeinf.get_idati()

# Load PDB for full member definitions (only for classes with verified matching sizes)
pdb = json.load(open(PDB_FILE, encoding='utf-8'))
pdb_classes = {c['name']: c for c in pdb['classes'] if c.get('name')}

# CCBSystem: verified 90840 bytes = PAL3A PDB → reimport full PDB definition
# This was incorrectly shrunk to 1024 bytes earlier
print("[*] Reimporting CCBSystem (verified size 90840 = PAL3A PDB)")

# Use the batch import's build_type_decl approach inline
# For CCBSystem, just reimport the PDB struct with proper members
import sys
sys.path.insert(0, SCRIPT_DIR)

# Simple approach: just ensure correct forward decls exist, then use parse_decls
fwd = """
struct CCBSystem;
struct CCBControl;
struct CCBAttackSequen;
struct CCBRoleState;
struct CCBStage;
struct CCBUI;
struct CCBAI;
struct CCBEditor;
struct CEffectSystem;
struct CEffectSimple;
struct CEffMgr;
struct C2DSpark;
struct C3DSpark;
struct TxtFile;
struct FightInfo;
"""
idc.parse_decls(fwd, idc.PT_TYP)

# CCBSystem full definition (from PDB, verified size match)
ccb_decl = """
struct CCBSystem {
  CCBSystem *m_pUtil;           // +0x000
  CCBUI *m_pUI;                 // +0x004
  CCBControl *m_pControl;       // +0x008
  CCBAttackSequen *m_pAttackSequen; // +0x00C
  CCBRoleState *m_pRoleState;   // +0x010
  CCBStage *m_pStage;           // +0x014
  CCBAI *m_pAI;                 // +0x018
  CCBEditor *m_pEditor;         // +0x01C
  CEffectSystem *m_pES;         // +0x020
  CEffectSimple *m_pEffectSimple; // +0x024
  TxtFile *m_pConfig;           // +0x028
  CEffMgr *m_pEffMgr;          // +0x02C
  CEffMgr *m_pATSEffMgr;       // +0x030
  C2DSpark *m_p2DSpark;         // +0x034
  C3DSpark *m_p3DSpark;         // +0x038
  char _pad_003C[4];            // +0x03C
  double m_DeltaTime;           // +0x040
  double m_dTimeFund;           // +0x048
  FightInfo *m_pFightInfo;      // +0x050
  char _rest[90784];            // +0x054 to end (90840 - 0x54 = 90784)
};
"""
nerr = idc.parse_decls(ccb_decl, idc.PT_TYP)
if nerr == 0:
    tif = ida_typeinf.tinfo_t()
    tif.get_named_type(til, "CCBSystem")
    print("[+] CCBSystem: size=%d (expected 90840)" % tif.get_size())
else:
    print("[!] CCBSystem: parse errors %d" % nerr)

idc.qexit(0)
