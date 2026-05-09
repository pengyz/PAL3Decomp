"""
IDAPython: Manual iteration 3 - CGameData::Init + ScriptSystem::Init callees.

Usage:
  idat.exe -A -S"pal3_manual_iter3.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, ida_typeinf, idc, os, time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_manual_iter3_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

ANNOTATIONS = [
    # CGameData::Init callees
    (0x00445B90, "UIWnd::Create",
     "int __thiscall UIWnd::Create(void *this, int id, void *pRect, int parent)"),
    (0x00445DB0, "UIWnd::SetVisible",
     "int __thiscall UIWnd::SetVisible(void *this, int bVisible)"),
    (0x0044ADE0, "CGameData::InitRoles",
     "int __thiscall CGameData::InitRoles(int this, int a2)"),
    (0x0044E660, "CGameData::InitItems",
     "int __thiscall CGameData::InitItems(int this, int a2)"),
    (0x004503D0, "UIDialog::Create",
     "void __thiscall UIDialog::Create(void *this, int id, int x, int y, int parent, char *tex)"),
    (0x00450550, "UIDialog::Show",
     "void __thiscall UIDialog::Show(void *this)"),
    (0x00450B30, "UIDialog::Init",
     "int __thiscall UIDialog::Init(void *this)"),
    (0x00450F90, "UIBigDialog::Create",
     "int __thiscall UIBigDialog::Create(void *this, int id, void *pRect, int parent, char *tex)"),
    (0x00451980, "UISelectDialog::Create",
     "int __thiscall UISelectDialog::Create(void *this, int id, void *pRect, int parent, char *tex)"),
    (0x00452580, "PropUI::Create",
     "int __thiscall PropUI::Create(void *this)"),
    (0x00452670, "PropUI::Init",
     "void __thiscall PropUI::Init(void *this)"),
    (0x0047DCA0, "Object3D::Create",
     "int __thiscall Object3D::Create(void *this)"),
    (0x0047DE40, "Object3D::Init",
     "void __thiscall Object3D::Init(void *this)"),
    (0x004A1E40, "EquipUI::Create",
     "int __thiscall EquipUI::Create(void *this)"),
    (0x004A4220, "EquipUI::Init",
     "void __thiscall EquipUI::Init(void *this)"),
    (0x004A48B0, "EquipUI::InitSlots",
     "void __thiscall EquipUI::InitSlots(void *this)"),
    (0x004A4960, "StateUI::Create",
     "int __thiscall StateUI::Create(void *this)"),
    (0x004A4A10, "StateUI::Init",
     "void __thiscall StateUI::Init(void *this)"),
    (0x004A4AC0, "MagicUI::Create",
     "int __thiscall MagicUI::Create(void *this)"),
    (0x004A4B70, "MagicUI::Init",
     "void __thiscall MagicUI::Init(void *this)"),
    (0x0053F920, "TextureLib::SetPath",
     "char * __thiscall TextureLib::SetPath(char *this, char *path)"),
    (0x0053F960, "TextureLib::LoadFromFile",
     "char __thiscall TextureLib::LoadFromFile(void *this, char *filename)"),

    # ScriptSystem::Init callees
    (0x004319F0, "PalScript::SetDirectory",
     "int __thiscall PalScript::SetDirectory(char *this, char *dir)"),
    (0x00431A60, "PalScript::HasNext",
     "int __thiscall PalScript::HasNext(void *this)"),
    (0x00431B60, "PalScript::LoadNext",
     "int __thiscall PalScript::LoadNext(void *this)"),

    # Global variables identified
    # dword_BFDA80 = MiniGame1 instance
    # dword_BFDA7C = MiniGame2 instance
    # dword_BFDA84 = MiniGame3 instance
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Manual iteration 3: CGameData::Init + ScriptSystem::Init")

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
