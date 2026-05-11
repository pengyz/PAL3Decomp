"""
PAL3 Master Annotation Pipeline — runs ALL IDA annotation steps in correct order.

This is the single script to run for a complete IDA setup from scratch.
Order matters: structs first, then function signatures, then names/globals.

Usage:
  idat.exe -A -S"pal3_master_annotate.py" original/PAL3.exe.i64

Pipeline steps:
  1. Batch import PDB structs (no-base classes only, DAG-ordered)
  2. PAL3-specific struct overrides (binary-verified sizes/layouts)
  3. UIFrameWnd/UIWnd/CEffect family struct imports (with typed base)
  4. Safe-inherited class imports (recursive base verification)
  5. Auto-fix this-types for all thiscall functions
  6. Name top sub_ functions with correct signatures
  7. Name and type global variables
"""
import ida_auto
import ida_name
import ida_typeinf
import idc
import idautils
import json
import os
import re
import sys
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
PDB_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)


def main():
    ida_auto.auto_wait()
    log("[*] PAL3 Master Annotation Pipeline")
    log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))
    t0 = time.time()

    # Step 1: Run batch import
    log("\n=== Step 1: Batch PDB import ===")
    exec(open(os.path.join(SCRIPT_DIR, "pal3_batch_import_structs.py")).read().replace("idc.qexit(0)", "pass"))

    # Step 2: Run overrides
    log("\n=== Step 2: PAL3 overrides ===")
    exec(open(os.path.join(SCRIPT_DIR, "pal3_override_structs.py")).read().replace("idc.qexit(0)", "pass"))

    # Step 3: Auto-fix this types
    log("\n=== Step 3: This-type fix ===")
    exec(open(os.path.join(SCRIPT_DIR, "pal3_autofix_this_types.py")).read().replace("idc.qexit(0)", "pass"))

    # Step 4: Name globals
    log("\n=== Step 4: Global variables ===")
    name_globals()

    # Step 5: Name functions
    log("\n=== Step 5: Function names ===")
    name_functions()

    elapsed = time.time() - t0
    log("\n[*] Pipeline complete in %.1fs" % elapsed)
    idc.qexit(0)


def name_globals():
    """Name and type key global variables."""
    til = ida_typeinf.get_idati()

    FWD = "struct gbGfxManager; struct CameraCtrl; struct CCBSystem; struct GRPinput;"
    idc.parse_decls(FWD, idc.PT_TYP)

    GLOBALS = [
        (0xBFDA60, "g_pGfxMgr", "gbGfxManager *"),
        (0xBFDA68, "g_pCameraCtrl", "CameraCtrl *"),
        (0xBFDA6C, "g_nGameState", "int"),
        (0xBFDA74, "g_pCBSystem", "CCBSystem *"),
        (0xBFD6D0, "g_pGameTime", "double *"),
        (0xBFD6D4, "g_pAbsTime", "double *"),
        (0xBFDA4C, "g_pRoleSystem", "void *"),
        (0xBFDB80, "g_pScriptSystem", "void *"),
        (0x17A990C, "g_nCombatMode", "int"),
        (0x189598E, "g_bInitFlags", "unsigned char"),
        (0x17AA870, "g_bRoleActive", "unsigned char"),
        (0x17AAF64, "g_bSceneLoaded", "unsigned char"),
        (0xBFDA70, "g_pEffectSystem", "void *"),
        (0xBFDB84, "g_pUIManager", "void *"),
        (0xBFDB90, "g_pSoundMgr", "void *"),
        (0xBFDB98, "g_hWnd", "int"),
        (0xBFDB9C, "g_hInstance", "int"),
        (0xBFDBA0, "g_nScreenW", "int"),
        (0xBFDBA4, "g_nScreenH", "int"),
        (0xBFFDB0, "g_pNPCSystem", "void *"),
        (0xBFDBB0, "g_pActorSystem", "void *"),
        (0xD8C2B8, "g_InputState", "GRPinput"),
        (0x5DC3DC, "g_bDebugMode", "int"),
        (0x5CEFA8, "g_bConsoleOpen", "unsigned char"),
        (0x60B534, "g_nFrameCount", "int"),
    ]

    named = 0
    for addr, name, type_str in GLOBALS:
        if ida_name.set_name(addr, name, ida_name.SN_FORCE):
            named += 1
    log("  Named %d globals" % named)


def name_functions():
    """Name top sub_ functions with correct signatures."""
    til = ida_typeinf.get_idati()
    FWD = """
struct UIWnd; struct UIFrameWnd; struct PalScript;
struct GRPinput; struct CCBStage; struct CCBRoleState; struct CCBStageRole;
"""
    idc.parse_decls(FWD, idc.PT_TYP)

    SIGS = [
        (0x4B47E0, "UIFrameWnd_Destructor_4B47E0", "void __thiscall UIFrameWnd_Destructor_4B47E0(UIWnd *this)"),
        (0x4B4690, "UIObj_Reset", "void __thiscall UIObj_Reset(UIWnd *this)"),
        (0x44BD80, "SafeDelete_44BD80", "void __thiscall SafeDelete_44BD80(void **this)"),
        (0x445E50, "UIObj_SetState", "int __thiscall UIObj_SetState(UIWnd *this, int state)"),
        (0x444F60, "UIWnd_Init_444F60", "UIWnd * __thiscall UIWnd_Init_444F60(UIWnd *this)"),
        (0x444AC0, "UIFrameWnd_Destructor_444AC0", "void __thiscall UIFrameWnd_Destructor_444AC0(UIWnd *this)"),
        (0x43A070, "SetFloatParam", "int __thiscall SetFloatParam(void *this, float value)"),
        (0x4318A0, "PalScript_Cleanup", "void __thiscall PalScript_Cleanup(PalScript *this)"),
        (0x43EBB0, "GetGridOffset", "void __thiscall GetGridOffset(void *this, int *pOut, int index)"),
        (0x44BD60, "PtrArray_Init", "void __thiscall PtrArray_Init(void *this)"),
        (0x4A1530, "UIWnd_SetByte", "int __thiscall UIWnd_SetByte(UIWnd *this, char value)"),
        (0x43FD90, "SetIntParam", "int __thiscall SetIntParam(void *this, int value)"),
        (0x4A2BD0, "UIWnd_GetChild", "UIWnd * __thiscall UIWnd_GetChild(UIWnd *this, int index)"),
        (0x4A2F90, "UIWnd_FindChild", "UIWnd * __thiscall UIWnd_FindChild(UIWnd *this, int id)"),
        (0x445010, "UIWnd_Destructor", "void __thiscall UIWnd_Destructor(UIWnd *this)"),
        (0x4031D0, "GRPinput_GetState", "int __thiscall GRPinput_GetState(GRPinput *this)"),
        (0x4F4AA0, "CCBStage_GetRole", "CCBStageRole * __thiscall CCBStage_GetRole(CCBStage *this, int index)"),
        (0x4F2C30, "CCBRoleState_GetRole", "void * __thiscall CCBRoleState_GetRole(CCBRoleState *this, int index)"),
        (0x4326A0, "String_Assign_4326A0", "void __thiscall String_Assign_4326A0(void *this, char *src, int len)"),
        (0x557CA2, "UnhandledExceptionFilter", None),
    ]

    named = 0
    for item in SIGS:
        addr, name = item[0], item[1]
        sig = item[2] if len(item) > 2 else None
        cur = ida_name.get_name(addr) or ""
        if cur and not cur.startswith("sub_"):
            continue
        if ida_name.set_name(addr, name, ida_name.SN_FORCE):
            named += 1
        if sig:
            idc.SetType(addr, sig)
    log("  Named %d functions" % named)


try:
    main()
except Exception as e:
    log("[ERROR] %s" % str(e))
    import traceback
    log(traceback.format_exc())
finally:
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(os.path.join(LOG_DIR, "pal3_master_annotate_log.txt"), 'w') as f:
        f.write('\n'.join(log_lines))
