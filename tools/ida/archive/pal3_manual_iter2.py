"""
IDAPython: Manual iteration 2 - PAL3::Render + PAL3::Destroy callees.
Each annotated based on:
  1. Which global variable is passed as this (this-source verification)
  2. Reading function body to confirm purpose

Usage:
  idat.exe -A -S"pal3_manual_iter2.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, ida_typeinf, idc, os, time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter2_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Verified annotations from PAL3::Render analysis
# Method: this-source = known global variable -> class confirmed
ANNOTATIONS = [
    # PAL3::Destroy callees (cdecl, no this)
    (0x0040C960, "ScriptSystem::Destroy",
     "int __cdecl ScriptSystem::Destroy()"),
    (0x00422DF0, "UISystem::Destroy",
     "int __cdecl UISystem::Destroy()"),

    # PAL3::Render callees - all with full signatures
    # this = script system (cdecl, takes gbMatrixStack*)
    (0x0040C630, "ScriptSystem::Render",
     "void __cdecl ScriptSystem::Render(void *a1)"),
    (0x0040C7D0, "ScriptSystem::Render2",
     "char __cdecl ScriptSystem::Render2()"),

    # this = &g_UIManager (thiscall)
    (0x0041F370, "UIManager::Render",
     "void __thiscall UIManager::Render(void *this)"),

    # this = UIScene instance (thiscall, from UISceneUpdate())
    (0x004200A0, "UIScene::Render",
     "int __thiscall UIScene::Render(void *this, int a2)"),
    (0x00420110, "UIScene::RenderWithStack",
     "int __thiscall UIScene::RenderWithStack(void *this, void *pStack)"),
    (0x00421A10, "UIScene::NotifyRender",
     "int __thiscall UIScene::NotifyRender(void *this)"),
    (0x00421C00, "UIScene::EffectRender",
     "int __thiscall UIScene::EffectRender(void *this)"),
    (0x004220A0, "UIScene::OverlayRender",
     "int __thiscall UIScene::OverlayRender(void *this, int a2)"),
    (0x004234D0, "UIScene::CombatCheck",
     "int __cdecl UIScene::CombatCheck()"),

    # this = &g_GameData (thiscall)
    (0x0044F5B0, "CGameData::Render",
     "int __thiscall CGameData::Render(void *this)"),

    # this = RenderTarget3 instance (thiscall)
    (0x004B6630, "RenderTarget3::Begin",
     "int __thiscall RenderTarget3::Begin(void *this)"),
    (0x004B6DF0, "RenderTarget3::End",
     "void * __cdecl RenderTarget3::End()"),
    (0x004B6E20, "RenderTarget3::Resolve",
     "void __thiscall RenderTarget3::Resolve(void *this)"),

    # this = ScreenEffectMgr instance (thiscall)
    (0x004BE4A0, "ScreenEffectMgr::Render",
     "void __thiscall ScreenEffectMgr::Render(void *this)"),

    # this = RenderTarget2 instance
    (0x004BFD70, "RenderTarget2::Begin",
     "void * __cdecl RenderTarget2::Begin()"),
    (0x004BFDD0, "RenderTarget2::Resolve",
     "void __thiscall RenderTarget2::Resolve(void *this)"),

    # this = g_pSceneMgr (thiscall)
    (0x004CDBF0, "SceneMgr::RenderAll",
     "char __thiscall SceneMgr::RenderAll(void *this)"),
    (0x004CDC20, "SceneMgr::RenderUpdate",
     "char __thiscall SceneMgr::RenderUpdate(void *this)"),

    # this = g_pCBSystem (thiscall)
    (0x00513120, "CCBSystem::RenderCheck",
     "char __thiscall CCBSystem::RenderCheck(void *this)"),

    # this = MiniGame instances (thiscall)
    (0x0052B860, "MiniGame1::Render",
     "void __thiscall MiniGame1::Render(void *this)"),
    (0x00535320, "MiniGame3::Render",
     "void __thiscall MiniGame3::Render(void *this)"),

    # this = &g_Logger (thiscall)
    (0x0053C990, "Logger::Render",
     "int __thiscall Logger::Render(void *this)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 2: PAL3::Render + Destroy callees")

        named = 0
        sigs = 0
        for entry in ANNOTATIONS:
            addr, name = entry[0], entry[1]
            sig = entry[2] if len(entry) > 2 else None

            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                named += 1
                log("  [+] 0x%08X: %s" % (addr, name))
            if sig and idc.SetType(addr, sig):
                sigs += 1

        log("[*] Named: %d, Signatures: %d" % (named, sigs))
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] Done")

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
