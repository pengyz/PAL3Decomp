"""
IDAPython: Create missing class types so SetType can use them as this-pointer types.
Then re-apply the signatures that failed in pal3_fix_this_types2.py.
"""
import ida_auto, ida_name, ida_typeinf, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_create_missing_types_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# Classes that need to be created as forward-declared structs
MISSING_CLASSES = [
    "Config",
    "RenderTarget2",
    "RenderTarget3",
    "RenderTarget4",
    "ScriptObj",
    "UIBase",
    "UIItem",
    "UIQuadManager",
]

# Signatures that failed previously
RETRY_FIXES = [
    (0x0042FDA0, "Config::ReadINIInt",
     "int __thiscall Config::ReadINIInt(Config *this, char *filename, char *key)"),
    (0x0042FDC0, "Config::ReadINIString",
     "char * __thiscall Config::ReadINIString(Config *this, char *filename, char *key)"),
    (0x0042FDE0, "Config::ReadINI",
     "bool __thiscall Config::ReadINI(Config *this, char *filename, char *section)"),
    (0x004BF780, "RenderTarget2::Init",
     "int __thiscall RenderTarget2::Init(RenderTarget2 *this)"),
    (0x004BFDD0, "RenderTarget2::Resolve",
     "void __thiscall RenderTarget2::Resolve(RenderTarget2 *this)"),
    (0x004B65F0, "RenderTarget3::Init",
     "void __thiscall RenderTarget3::Init(RenderTarget3 *this)"),
    (0x004B6630, "RenderTarget3::Begin",
     "int __thiscall RenderTarget3::Begin(RenderTarget3 *this)"),
    (0x004B6E20, "RenderTarget3::Resolve",
     "void __thiscall RenderTarget3::Resolve(RenderTarget3 *this)"),
    (0x004B6D80, "RenderTarget4::Init",
     "void * __thiscall RenderTarget4::Init(RenderTarget4 *this)"),
    (0x00412680, "ScriptObj::Destroy",
     "int __thiscall ScriptObj::Destroy(ScriptObj *this)"),
    (0x004A4890, "UIBase::GetSelected",
     "int __thiscall UIBase::GetSelected(UIBase *this)"),
    (0x004A3900, "UIBase::SetItemData",
     "int __thiscall UIBase::SetItemData(UIBase *this, int id, unsigned int data)"),
    (0x004A16C0, "UIItem::Create",
     "int __thiscall UIItem::Create(UIItem *this, int id, int a3)"),
    (0x004A12F0, "UIItem::Refresh",
     "int __thiscall UIItem::Refresh(UIItem *this)"),
    (0x004A14D0, "UIItem::SetData",
     "void * __thiscall UIItem::SetData(UIItem *this, char a2)"),
    (0x004A1410, "UIItem::UIItem",
     "void __thiscall UIItem::UIItem(UIItem *this)"),
    (0x005415C0, "UIQuadManager::Destroy",
     "void __thiscall UIQuadManager::Destroy(UIQuadManager *this)"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Creating missing class types")

        til = ida_typeinf.get_idati()
        created = 0
        for cls_name in MISSING_CLASSES:
            # Create a forward-declared struct
            tif = ida_typeinf.tinfo_t()
            # Try to parse a minimal struct definition
            decl = "struct %s { };" % cls_name
            if ida_typeinf.parse_decl(tif, til, decl, ida_typeinf.PT_TYP) is not None:
                # Import into local types
                if tif.set_named_type(til, cls_name, ida_typeinf.NTF_REPLACE) == 0:
                    created += 1
                    log("  [+] Created type: %s" % cls_name)
                else:
                    log("  [-] Failed to set named type: %s" % cls_name)
            else:
                log("  [-] Failed to parse: %s" % cls_name)

        log("[*] Created %d types, now retrying signatures" % created)

        fixed = 0
        for addr, name, sig in RETRY_FIXES:
            if idc.SetType(addr, sig):
                fixed += 1
                log("  [+] 0x%08X: %s" % (addr, name))
            else:
                log("  [-] 0x%08X: FAILED %s" % (addr, sig))

        log("[*] Fixed: %d / %d" % (fixed, len(RETRY_FIXES)))
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
