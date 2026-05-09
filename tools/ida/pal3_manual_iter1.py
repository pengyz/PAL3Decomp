"""
IDAPython: Manual iteration 1 - PAL3::Create callees analysis.
Each function analyzed by reading decomp + understanding logic.

Usage:
  idat.exe -A -S"pal3_manual_iter1.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, ida_typeinf, idc, os, time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter1_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Analyzed from PAL3::Create callees - logic-based identification
ANNOTATIONS = [
    # (addr, name, signature_or_None)
    # CameraCtrl methods (this = g_pCamera)
    (0x0041C1B0, "CameraCtrl::InitParams",
     "int __thiscall CameraCtrl::InitParams(void *this, void *pParams)"),

    # Sound/Script system init
    (0x0041ED00, "SoundSystem::Init", None),
    (0x0041EFA0, "ScriptSystem::Init", None),

    # UI Manager
    (0x0041F5E0, "UIManager::LoadShadowTexture",
     "void * __thiscall UIManager::LoadShadowTexture(void *this)"),

    # PalScript (script engine)
    (0x00430290, "PalScript::LoadScript",
     "int __thiscall PalScript::LoadScript(void *this, int pathAddr)"),
    (0x00430570, "PalScript::SetAppName",
     "char * __thiscall PalScript::SetAppName(void *this, char *name)"),
    (0x004318B0, "PalScript::LoadFromFile",
     "void * __thiscall PalScript::LoadFromFile(int this, char *filename)"),

    # CGameData
    (0x0044F130, "CGameData::Init",
     "void * __thiscall CGameData::Init(int this)"),

    # PAL_GDB (game database)
    (0x00457410, "PAL_GDB::LoadLanguage",
     "char __thiscall PAL_GDB::LoadLanguage(void *this, char *path)"),

    # RenderTarget init
    (0x004B6D80, "RenderTarget4::Init",
     "void * __thiscall RenderTarget4::Init(void *this)"),
    (0x004BF780, "RenderTarget2::Init",
     "int __thiscall RenderTarget2::Init(void *this)"),

    # Scene Manager
    (0x004CDA10, "SceneMgr::Create",
     "void * __thiscall SceneMgr::Create(void *this, int gfxMgr, int cam, int a4)"),

    # CCBSystem constructor
    (0x00512500, "CCBSystem::CCBSystem",
     "int __thiscall CCBSystem::CCBSystem(int this)"),

    # CScreenMode
    (0x0053C340, "CScreenMode::InitCPK",
     "char __thiscall CScreenMode::InitCPK(int this, int a2, int a3)"),
    (0x0053C5A0, "CScreenMode::PlayVideo",
     "int __thiscall CScreenMode::PlayVideo(int *this, int a2)"),

    # Misc init
    (0x00408BE0, "PAL3::InitSubsystems", None),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 1: PAL3::Create callees")
        log("[*] Time: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        til = ida_typeinf.get_idati()
        named = 0
        sigs = 0

        for entry in ANNOTATIONS:
            addr = entry[0]
            name = entry[1]
            sig = entry[2] if len(entry) > 2 else None

            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                named += 1
                log("  [+] 0x%08X: %s" % (addr, name))
            else:
                log("  [-] 0x%08X: name FAILED %s" % (addr, name))

            if sig:
                if idc.SetType(addr, sig):
                    sigs += 1
                else:
                    log("  [-] 0x%08X: sig FAILED" % addr)

        log("[*] Named: %d, Signatures: %d" % (named, sigs))
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB saved")

    except Exception as e:
        log("[!] %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
