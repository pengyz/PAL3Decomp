"""Import gbGfxManager struct definition from PAL3A PDB data.
Uses padded byte arrays for complex sub-types to ensure correct size/offsets."""
import ida_auto, ida_typeinf, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))

ida_auto.auto_wait()
til = ida_typeinf.get_idati()

# Forward declarations for referenced types
fwd_decls = """
struct gbEffectMgr;
struct gbVertPoolMgr;
struct gbResManager;
struct gbPrintFontMgr;
struct gbMatrixStack;
struct gbSceneGraph;
"""
idc.parse_decls(fwd_decls, idc.PT_TYP)

# gbGfxManager: size=1520 (0x5F0) from PAL3A PDB
# Offsets verified from PDB, sizes calculated from consecutive member offsets
DECL = """
struct gbGfxManager {
  char _vftable[8];                     // +0x000 (vtable + padding)
  unsigned int hGfxWnd;                 // +0x008
  char DrvInfo[184];                    // +0x00C (gbGfxDriverInfo, size=0xB8)
  gbVertPoolMgr *pVertPoolMgr;         // +0x0C4
  gbEffectMgr *pEffectMgr;             // +0x0C8
  gbResManager *pTexResMgr;            // +0x0CC
  gbPrintFontMgr *pFontMgr;           // +0x0D0
  gbMatrixStack *pMatrixStack[4];      // +0x0D4
  char ViewMatrix[64];                  // +0x0E4 (gbMatrix4)
  char InvViewMatrix[64];              // +0x124 (gbMatrix4)
  char WorldMatrix[64];                 // +0x164 (gbMatrix4)
  int CurZBias;                         // +0x1A4
  int bWireMode;                        // +0x1A8
  char AmbientLight[16];               // +0x1AC (gbColorFlt)
  float fSelfIllum;                     // +0x1BC
  gbSceneGraph *pSceneGraph;           // +0x1C0
  char Viewport[20];                    // +0x1C4 (gbViewPort)
  char ClearParam[16];                  // +0x1D8 (gbClearParam)
  char _pad1E8[8];                      // +0x1E8
  double LastTime;                      // +0x1F0
  double CurTime;                       // +0x1F8
  unsigned int LastTick;               // +0x200
  char _tail[1004];                     // +0x204 to end (0x5F0)
};
"""

nerrors = idc.parse_decls(DECL, idc.PT_TYP)
if nerrors == 0:
    # Verify
    tif = ida_typeinf.tinfo_t()
    tif.get_named_type(til, "gbGfxManager")
    print("[+] gbGfxManager imported: size=%d (expected 1520)" % tif.get_size())
else:
    print("[!] parse_decls errors: %d" % nerrors)

idc.qexit(0)
