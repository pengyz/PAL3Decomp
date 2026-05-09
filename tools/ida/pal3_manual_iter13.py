"""
IDAPython: Manual iteration 13 - Actor/SceneObj area (0x536000).
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter13_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # Actor gbengine wrappers
    (0x00536D00, "Actor::SetTimeScale",
     "void __thiscall Actor::SetTimeScale(void *this, float scale)"),
    (0x00536FB0, "Actor::QueryState",
     "int __thiscall Actor::QueryState(void *this)"),
    (0x00536FC0, "Actor::DispatchAction",
     "int __thiscall Actor::DispatchAction(void *this, int actionId)"),
    (0x00536FF0, "Actor::UpdateAllActions",
     "int __thiscall Actor::UpdateAllActions(void *this)"),
    (0x00536AC0, "Actor::LoadAction",
     "int __thiscall Actor::LoadAction(void *this, char *name)"),

    # Actor larger methods
    (0x00536160, "Actor::SetParam",
     "int __thiscall Actor::SetParam(void *this, int a2)"),
    (0x005363A0, "Actor::ResetState",
     "int __thiscall Actor::ResetState(void *this)"),
    (0x005363C0, "Actor::Cleanup",
     "int __thiscall Actor::Cleanup(void *this)"),
    (0x005363E0, "Actor::SetAction",
     "void __thiscall Actor::SetAction(void *this, int actionId)"),
    (0x005364B0, "Actor::InitComponents",
     "int __thiscall Actor::InitComponents(void *this)"),
    (0x00536560, "Actor::ProcessFrame",
     "char __thiscall Actor::ProcessFrame(void *this)"),
    (0x005368A0, "Actor::HandleEvent",
     "BOOL __thiscall Actor::HandleEvent(void *this, int a2, int a3)"),

    # SceneObj/UI construction
    (0x00536260, "SceneObj::CreateUI",
     "int __thiscall SceneObj::CreateUI(void *this)"),
    (0x005362F0, "SceneObj::Destructor",
     "void * __thiscall SceneObj::Destructor(void *this)"),
    (0x00536310, "SceneObj::DestroyInternal",
     "void __thiscall SceneObj::DestroyInternal(void *this)"),

    # Thunks (trivial, mark as named)
    (0x00536220, "Actor::GetDefaultFOV_thunk",
     "int __cdecl Actor::GetDefaultFOV_thunk()"),
    (0x00536230, "Actor::SetDefaultFOV",
     "int __cdecl Actor::SetDefaultFOV()"),
    (0x00536240, "Actor::GetDefaultDist_thunk",
     "int __cdecl Actor::GetDefaultDist_thunk()"),
    (0x00536250, "Actor::SetDefaultDist",
     "void __cdecl Actor::SetDefaultDist()"),
    (0x00536A40, "Actor::GetDefaultFOV2_thunk",
     "int __cdecl Actor::GetDefaultFOV2_thunk()"),
    (0x00536A50, "Actor::SetDefaultFOV2",
     "int __cdecl Actor::SetDefaultFOV2()"),
    (0x00536A60, "Actor::GetDefaultDist2_thunk",
     "int __cdecl Actor::GetDefaultDist2_thunk()"),
    (0x00536A70, "Actor::SetDefaultDist2",
     "void __cdecl Actor::SetDefaultDist2()"),
    (0x00536A80, "Actor::FastInit",
     "int __fastcall Actor::FastInit(int a1)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 13: Actor/SceneObj area")
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
        log("[*] Named: %d, Sigs: %d" % (named, sigs))
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] Done")
    except Exception as e:
        log("[!] %s" % str(e))
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
