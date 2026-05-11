"""Fix SceneMgr::Create and other key function signatures."""
import ida_auto, ida_typeinf, idc

ida_auto.auto_wait()
til = ida_typeinf.get_idati()

# Ensure types exist
for t in ["gbGfxManager", "gbCamera", "gbSceneGraph", "SceneMgr"]:
    decl = "struct %s;" % t
    tinfo = ida_typeinf.tinfo_t()
    ida_typeinf.parse_decl(tinfo, til, decl, ida_typeinf.PT_TYP)

fixes = [
    (0x004CDA10, "void * __thiscall SceneMgr::Create(SceneMgr *this, gbGfxManager *gfxMgr, gbCamera *cam, gbSceneGraph *pRoot)"),
]

for addr, sig in fixes:
    if idc.SetType(addr, sig):
        print("[+] 0x%08X: OK" % addr)
    else:
        print("[!] 0x%08X: FAILED" % addr)

idc.qexit(0)
