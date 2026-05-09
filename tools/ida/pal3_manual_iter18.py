"""
IDAPython: Manual iteration 18 - Clear remaining class stubs.
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter18_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    (0x00402310, "GRPinput::AcquireDevices",
     "int __thiscall GRPinput::AcquireDevices(GRPinput *this)"),
    (0x00402380, "GRPinput::ReleaseDevices",
     "int __thiscall GRPinput::ReleaseDevices(GRPinput *this)"),
    (0x0047D9D0, "Object3D::SetupCamera",
     "void * __thiscall Object3D::SetupCamera(void *this)"),
    (0x0050A560, "CCBStageRole::GetWorldPos",
     "float * __thiscall CCBStageRole::GetWorldPos(CCBStageRole *this)"),
    (0x0050B530, "CCBStageRole::GetTaskState",
     "int __thiscall CCBStageRole::GetTaskState(CCBStageRole *this)"),
    (0x00536CE0, "Actor::EnableTransition",
     "void __thiscall Actor::EnableTransition(void *this, int a2, int a3)"),
    (0x0041C900, "CCCTData::CalcDist",
     "void __stdcall CCCTData::CalcDist(float a1, float a2)"),
    (0x005044C0, "CCCTData::UpdateCamera",
     "int __thiscall CCCTData::UpdateCamera(void *this, int a2)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 18: Clear all remaining class stubs")
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
