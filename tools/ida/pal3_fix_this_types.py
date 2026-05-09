"""
IDAPython: Fix all previously annotated thiscall signatures to use proper class types.
Previously many used void* or int as this, now corrected to ClassName*.

Also imports forward declarations for all referenced classes.

Usage:
  idat.exe -A -S"pal3_fix_this_types.py" original/PAL3.exe.i64
"""
import ida_auto, ida_name, ida_typeinf, idc, os, re

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_fix_this_types_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# All classes that need forward declarations
CLASSES = [
    "GRPinput", "CGameData", "CameraCtrl", "UIWnd", "UIDialog",
    "UIBigDialog", "UISelectDialog", "UINote", "UIManager", "UIScene",
    "PropUI", "EquipUI", "StateUI", "MagicUI", "Object3D",
    "PalScript", "TextureLib", "SceneMgr", "RoleSystem",
    "CCBSystem", "CCBControl", "CCBAttackSequen", "CCBRoleState",
    "CCBStage", "CCBUI", "CCBEditor", "CCBStageRole",
    "CScreenMode", "CRenderTarget", "CRenderTarget2",
    "ScreenEffectMgr", "Logger", "PAL_GDB",
    "MiniGame1", "MiniGame2", "MiniGame3",
    "NPC", "Scene", "Camera",
]

# Signatures to fix: (address, corrected_signature)
# Rule: ClassName::Method(void *this, ...) -> ClassName::Method(ClassName *this, ...)
FIXES = [
    # Iter 1 fixes
    (0x0041C1B0, "int __thiscall CameraCtrl::InitParams(CameraCtrl *this, void *pParams)"),
    (0x0041F5E0, "void * __thiscall UIManager::LoadShadowTexture(UIManager *this)"),
    (0x00430290, "int __thiscall PalScript::LoadScript(PalScript *this, int pathAddr)"),
    (0x00430570, "char * __thiscall PalScript::SetAppName(PalScript *this, char *name)"),
    (0x004318B0, "void * __thiscall PalScript::LoadFromFile(PalScript *this, char *filename)"),
    (0x0044F130, "void * __thiscall CGameData::Init(CGameData *this)"),
    (0x00457410, "char __thiscall PAL_GDB::LoadLanguage(PAL_GDB *this, char *path)"),
    (0x004B6D80, "void * __thiscall RenderTarget4::Init(void *this)"),
    (0x004BF780, "int __thiscall RenderTarget2::Init(void *this)"),
    (0x004CDA10, "void * __thiscall SceneMgr::Create(SceneMgr *this, int gfxMgr, int cam, int a4)"),
    (0x00512500, "int __thiscall CCBSystem::CCBSystem(CCBSystem *this)"),
    (0x0053C340, "char __thiscall CScreenMode::InitCPK(CScreenMode *this, int a2, int a3)"),
    (0x0053C5A0, "int __thiscall CScreenMode::PlayVideo(CScreenMode *this, int a2)"),

    # Iter 2 fixes
    (0x0041F370, "void __thiscall UIManager::Render(UIManager *this)"),
    (0x0044F5B0, "int __thiscall CGameData::Render(CGameData *this)"),
    (0x004BE4A0, "void __thiscall ScreenEffectMgr::Render(ScreenEffectMgr *this)"),
    (0x004CDBF0, "char __thiscall SceneMgr::RenderAll(SceneMgr *this)"),
    (0x004CDC20, "char __thiscall SceneMgr::RenderUpdate(SceneMgr *this)"),
    (0x00513120, "char __thiscall CCBSystem::RenderCheck(CCBSystem *this)"),
    (0x0053C990, "int __thiscall Logger::Render(Logger *this)"),

    # Iter 3 fixes
    (0x00445B90, "int __thiscall UIWnd::Create(UIWnd *this, int id, void *pRect, int parent)"),
    (0x00445DB0, "int __thiscall UIWnd::SetVisible(UIWnd *this, int bVisible)"),
    (0x0044ADE0, "int __thiscall CGameData::InitRoles(CGameData *this, int a2)"),
    (0x0044E660, "int __thiscall CGameData::InitItems(CGameData *this, int a2)"),
    (0x004503D0, "void __thiscall UIDialog::Create(UIDialog *this, int id, int x, int y, int parent, char *tex)"),
    (0x00450550, "void __thiscall UIDialog::Show(UIDialog *this)"),
    (0x00450B30, "int __thiscall UIDialog::Init(UIDialog *this)"),
    (0x00450F90, "int __thiscall UIBigDialog::Create(UIBigDialog *this, int id, void *pRect, int parent, char *tex)"),
    (0x00451980, "int __thiscall UISelectDialog::Create(UISelectDialog *this, int id, void *pRect, int parent, char *tex)"),
    (0x00452580, "int __thiscall PropUI::Create(PropUI *this)"),
    (0x00452670, "void __thiscall PropUI::Init(PropUI *this)"),
    (0x0047DCA0, "int __thiscall Object3D::Create(Object3D *this)"),
    (0x0047DE40, "void __thiscall Object3D::Init(Object3D *this)"),
    (0x004A1E40, "int __thiscall EquipUI::Create(EquipUI *this)"),
    (0x004A4220, "void __thiscall EquipUI::Init(EquipUI *this)"),
    (0x004A48B0, "void __thiscall EquipUI::InitSlots(EquipUI *this)"),
    (0x004A4960, "int __thiscall StateUI::Create(StateUI *this)"),
    (0x004A4A10, "void __thiscall StateUI::Init(StateUI *this)"),
    (0x004A4AC0, "int __thiscall MagicUI::Create(MagicUI *this)"),
    (0x004A4B70, "void __thiscall MagicUI::Init(MagicUI *this)"),
    (0x0053F920, "char * __thiscall TextureLib::SetPath(TextureLib *this, char *path)"),
    (0x0053F960, "char __thiscall TextureLib::LoadFromFile(TextureLib *this, char *filename)"),
    (0x004319F0, "int __thiscall PalScript::SetDirectory(PalScript *this, char *dir)"),
    (0x00431A60, "int __thiscall PalScript::HasNext(PalScript *this)"),
    (0x00431B60, "int __thiscall PalScript::LoadNext(PalScript *this)"),

    # Iter 4 fixes
    (0x0043A250, "int __thiscall PalScript::Reset(PalScript *this)"),
    (0x00445920, "int __thiscall UIWnd::Reset(UIWnd *this)"),
    (0x0043A4C0, "void __thiscall UIScene::LoadResource(UIScene *this, char *path)"),
    (0x004450A0, "void * __thiscall UINote::Create(UINote *this, int id, int a3, int a4, char *tex)"),
    (0x00445930, "int __thiscall UIWnd::SetState(UIWnd *this, int state)"),

    # Iter 5 fixes
    (0x0040BE50, "int * __thiscall RoleSystem::Init(RoleSystem *this)"),
    (0x0040BE80, "int __thiscall RoleSystem::LoadData(RoleSystem *this, char a2)"),
    (0x0041C170, "int __thiscall RoleSystem::SetActive(RoleSystem *this, int a2)"),
    (0x00410990, "int __thiscall Scene::LoadConfig(Scene *this, void *pConfig)"),
    (0x004125D0, "void __thiscall Camera::SetParams(Camera *this, int a2)"),

    # Iter 6 fixes
    (0x00412E60, "int __thiscall RoleSystem::MoveRole(RoleSystem *this, float *pPos, int a3, int a4, int a5)"),
    (0x00413010, "char __thiscall RoleSystem::UpdateRole(RoleSystem *this, int a2, int a3, int a4)"),
    (0x00414980, "void __thiscall RoleSystem::GetPosition(RoleSystem *this, void *pOut, int a3)"),
    (0x00414A30, "int __thiscall RoleSystem::PathFind(RoleSystem *this, float *pTarget)"),
    (0x00416790, "void __thiscall RoleSystem::UpdateAnimation(RoleSystem *this, int a2)"),
    (0x00416F10, "int __thiscall RoleSystem::GetActiveRole(RoleSystem *this)"),
    (0x00417AC0, "char __thiscall RoleSystem::SetState(RoleSystem *this, int state)"),
    (0x00419A80, "int __thiscall RoleSystem::GetDirection(RoleSystem *this, float *pOut)"),
    (0x0041BBE0, "int __thiscall RoleSystem::GetCount(RoleSystem *this)"),
    (0x0041CAC0, "void * __thiscall CameraCtrl::GetViewTarget(CameraCtrl *this, void *pTarget, float *pPos)"),
    (0x0041D5B0, "int __thiscall CameraCtrl::SetCamMode(CameraCtrl *this, int mode)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Fixing this pointer types in all annotated functions")

        til = ida_typeinf.get_idati()

        # Import all class forward declarations
        for cls in CLASSES:
            decl = "struct %s;" % cls
            tinfo = ida_typeinf.tinfo_t()
            if ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP) is not None:
                tinfo.set_named_type(til, cls, ida_typeinf.NTF_REPLACE)

        log("[*] Imported %d class forward declarations" % len(CLASSES))

        # Apply corrected signatures
        fixed = 0
        for addr, sig in FIXES:
            if idc.SetType(addr, sig):
                fixed += 1
            else:
                log("  [-] 0x%08X: FAILED" % addr)

        log("[*] Fixed signatures: %d / %d" % (fixed, len(FIXES)))
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
