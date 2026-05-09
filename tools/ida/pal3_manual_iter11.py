"""
IDAPython: Manual iteration 11 - Next high-frequency batch.
"""
import ida_auto, ida_name, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter11_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # Actor wrappers (gbActor calls)
    (0x00536CC0, "Actor::GetAnimDuration",
     "unsigned int __thiscall Actor::GetAnimDuration(void *this, int animId)"),
    (0x00536C50, "Actor::CompareAction",
     "int __thiscall Actor::CompareAction(void *this, int actionIdx, int a3)"),

    # GRPinput
    (0x004022E0, "GRPinput::GetCursorPos",
     "BOOL __stdcall GRPinput::GetCursorPos(void *pPoint)"),

    # Generic utility
    (0x00401810, "ArraySort",
     "int __stdcall ArraySort(int base, int count, int elemSize, int compareFunc)"),

    # Combat logging
    (0x004DFD20, "Combat::LogMessage",
     "char __cdecl Combat::LogMessage(int a1, int a2, int a3, char *format)"),

    # Config system
    (0x0042FDE0, "Config::ReadINI",
     "bool __thiscall Config::ReadINI(void *this, char *filename, char *section)"),
    (0x0042FDA0, "Config::ReadINIInt",
     "int __thiscall Config::ReadINIInt(void *this, char *filename, char *key)"),
    (0x0042FDC0, "Config::ReadINIString",
     "char * __thiscall Config::ReadINIString(void *this, char *filename, char *key)"),

    # CCBStageRole methods
    (0x0050B330, "CCBStageRole::GetState",
     "char __thiscall CCBStageRole::GetState(CCBStageRole *this)"),

    # Scene object
    (0x00407B50, "SceneObj::Update",
     "char __thiscall SceneObj::Update(void *this, unsigned int a2)"),

    # Effect system
    (0x004CA400, "CEffect::SetParam",
     "int __thiscall CEffect::SetParam(void *this, int a2)"),

    # CCBRoleState additional
    (0x004F3A50, "CCBRoleState::GetRoleAttr",
     "int __thiscall CCBRoleState::GetRoleAttr(CCBRoleState *this, int roleIdx)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 11")
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
