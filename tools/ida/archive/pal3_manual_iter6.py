"""
IDAPython: Manual iteration 6 - CameraUpdate callees (depth 3).
RoleSystem methods + CameraCtrl methods confirmed by this-source.

Usage:
  idat.exe -A -S"pal3_manual_iter6.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter6_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # RoleSystem methods (this = g_pRoleSystem, confirmed by this-source)
    (0x00412E60, "RoleSystem::MoveRole",
     "int __thiscall RoleSystem::MoveRole(int this, float *pPos, int a3, int a4, int a5)"),
    (0x00413010, "RoleSystem::UpdateRole",
     "char __thiscall RoleSystem::UpdateRole(int this, int a2, int a3, int a4)"),
    (0x00414980, "RoleSystem::GetPosition",
     "void __thiscall RoleSystem::GetPosition(int this, void *pOut, int a3)"),
    (0x00414A30, "RoleSystem::PathFind",
     "int __thiscall RoleSystem::PathFind(int this, float *pTarget)"),
    (0x00416790, "RoleSystem::UpdateAnimation",
     "void __thiscall RoleSystem::UpdateAnimation(int this, int a2)"),
    (0x00416F10, "RoleSystem::GetActiveRole",
     "int __thiscall RoleSystem::GetActiveRole(int this)"),
    (0x00417AC0, "RoleSystem::SetState",
     "char __thiscall RoleSystem::SetState(int this, int state)"),
    (0x00419A80, "RoleSystem::GetDirection",
     "int __thiscall RoleSystem::GetDirection(float *this, float *pOut)"),
    (0x0041BBE0, "RoleSystem::GetCount",
     "int __thiscall RoleSystem::GetCount(void *this)"),

    # CameraCtrl methods (this = g_pCamera, confirmed by this-source)
    (0x0041CAC0, "CameraCtrl::GetViewTarget",
     "void * __thiscall CameraCtrl::GetViewTarget(char *this, void *pTarget, float *pPos)"),
    (0x0041D5B0, "CameraCtrl::SetCamMode",
     "int __thiscall CameraCtrl::SetCamMode(void *this, int mode)"),

    # GRPinput (this = &stru_BFAD70 / g_Input)
    (0x004022F0, "GRPinput::GetMousePos",
     "int __thiscall GRPinput::GetMousePos(void *this, void *pOut, void *pOut2)"),

    # ScriptSystem
    (0x0040E5F0, "ScriptSystem::Execute",
     "int __cdecl ScriptSystem::Execute(int a1, char a2)"),

    # CameraUpdate internal helpers (not class methods)
    (0x0041D9A0, "CameraUpdate_Internal",
     "void __cdecl CameraUpdate_Internal(float a1)"),
    (0x0041E7D0, "Camera::CheckCollision1",
     "int __cdecl Camera::CheckCollision1(void *pPos, void *pBounds, float *pDist)"),
    (0x0041EA00, "Camera::CheckCollision2",
     "int __cdecl Camera::CheckCollision2(void *pPos, int rolePtr, void *pBounds)"),
    (0x0041EE60, "Camera::IsTransitioning",
     "char __cdecl Camera::IsTransitioning()"),
    (0x00420CD0, "UICamera::GetViewMode",
     "int __cdecl UICamera::GetViewMode(int a1)"),
    (0x00420E50, "UICamera::CalcPosition",
     "float * __cdecl UICamera::CalcPosition(float *pMat)"),
    (0x004230D0, "UICamera::GetState",
     "int __cdecl UICamera::GetState()"),
    (0x004232D0, "UICamera::GetTarget",
     "int __cdecl UICamera::GetTarget(float *pMat)"),
    (0x0053D1E0, "CScreenMode::SetAudioParam",
     "void __thiscall CScreenMode::SetAudioParam(void *this)"),
    (0x0053D2D0, "CScreenMode::IsAudioReady",
     "char __thiscall CScreenMode::IsAudioReady(void *this)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 6: CameraUpdate callees")
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
        import traceback
        log(traceback.format_exc())
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
