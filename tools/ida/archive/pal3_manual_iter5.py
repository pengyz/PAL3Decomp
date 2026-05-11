"""
IDAPython: Manual iteration 5 - PAL3::FullInit callees (depth 3).

Usage:
  idat.exe -A -S"pal3_manual_iter5.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter5_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # Role creation (5 party members: results stored in dword_C0461C-C0462C)
    (0x00408D10, "Role::CreateXueJian",
     "int __cdecl Role::CreateXueJian(int a1, int a2)"),
    (0x00408D80, "Role::CreateLongKui",
     "int __cdecl Role::CreateLongKui(int a1, int a2)"),
    (0x00408E30, "Role::CreateZiXuan",
     "int __cdecl Role::CreateZiXuan(int a1, int a2)"),
    (0x00408E90, "Role::CreateChangQing",
     "int __cdecl Role::CreateChangQing(int a1, int a2)"),
    (0x00408F30, "Role::CreateHuaYing",
     "int __cdecl Role::CreateHuaYing(int a1, int a2)"),

    # RoleSystem (this = &unk_C05F60 = g_RoleSystem)
    (0x0040BE50, "RoleSystem::Init",
     "int * __thiscall RoleSystem::Init(int *this)"),
    (0x0040BE80, "RoleSystem::LoadData",
     "int __thiscall RoleSystem::LoadData(void *this, char a2)"),
    (0x0041C170, "RoleSystem::SetActive",
     "int __thiscall RoleSystem::SetActive(void *this, int a2)"),

    # NPC system
    (0x0040EB90, "NPC::Create",
     "unsigned int __cdecl NPC::Create(int index)"),
    (0x0040EC20, "NPC::Init",
     "void * __cdecl NPC::Init(int index)"),
    (0x0040F060, "NPC::SetParams",
     "int __cdecl NPC::SetParams(int a1)"),
    (0x0040F620, "NPC::InitAll",
     "int * __cdecl NPC::InitAll()"),

    # Scene/Camera
    (0x00410990, "Scene::LoadConfig",
     "int __thiscall Scene::LoadConfig(int this, void *pConfig)"),
    (0x004125D0, "Camera::SetParams",
     "void __thiscall Camera::SetParams(int this, int a2)"),
    (0x0041D980, "CameraSystem::Init",
     "int __cdecl CameraSystem::Init(int a1)"),

    # Array utility functions (generic)
    (0x00411170, "Array::Insert",
     "void * __stdcall Array::Insert(void *arr, void *elem, void *end)"),
    (0x004111C0, "Array::Size",
     "int __thiscall Array::Size(int *this)"),
    (0x004111E0, "Array::Erase",
     "void * __stdcall Array::Erase(void *arr, int index, void *pConfig)"),
    (0x00411240, "Array::Copy",
     "void * __cdecl Array::Copy(void *dst, void *src)"),

    # Globals
    # unk_C05F60 = g_RoleSystem (RoleSystem instance)
    # dword_C04354/C04358 = role team pointers
    # dword_C0461C-C0462C = 5 role instances
]

GLOBALS = [
    (0x00C05F60, "g_RoleSystem"),
    (0x00C04354, "g_RoleTeam1"),
    (0x00C04358, "g_RoleTeam2"),
    (0x00C0461C, "g_pRoleXueJian"),
    (0x00C04620, "g_pRoleLongKui"),
    (0x00C04624, "g_pRoleZiXuan"),
    (0x00C04628, "g_pRoleChangQing"),
    (0x00C0462C, "g_pRoleHuaYing"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 5: PAL3::FullInit depth 3")
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

        for addr, gname in GLOBALS:
            cur = ida_name.get_name(addr) or ""
            if cur.startswith("dword_") or cur.startswith("unk_") or not cur:
                ida_name.set_name(addr, gname, ida_name.SN_NOWARN | ida_name.SN_FORCE)
                log("  [g] 0x%08X: %s" % (addr, gname))

        log("[*] Named: %d, Sigs: %d" % (named, sigs))
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
