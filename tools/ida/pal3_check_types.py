"""
IDAPython: Check if class types are properly loaded (members + inheritance).
Quick verification script - does NOT modify IDB.
"""
import ida_auto, ida_typeinf, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_check_types_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

CHECK_CLASSES = [
    "CCBSystem", "CCBRoleState", "CCBStage", "CCBStageCam",
    "CCBStageRole", "CCBStageScene", "CCBUI", "UIWnd",
    "Actor", "CScreenMode", "PAL3", "CEffMgr",
    "SceneMgr", "PalScript", "CGameData", "GRPinput",
    "Config", "UIScene", "Object3D", "Logger",
]

def check_class(til, name):
    """Check if a class type exists and has members/bases."""
    tif = ida_typeinf.tinfo_t()
    if not tif.get_named_type(til, name):
        return None

    result = {
        "name": name,
        "size": tif.get_size(),
        "is_struct": tif.is_struct(),
        "members": 0,
        "bases": 0,
        "base_names": [],
        "first_members": [],
    }

    if tif.is_struct():
        si = ida_typeinf.udt_type_data_t()
        if tif.get_udt_details(si):
            for i in range(si.size()):
                member = si[i]
                if member.is_baseclass():
                    result["bases"] += 1
                    mtype_str = member.type.dstr() if member.type else "?"
                    result["base_names"].append(mtype_str)
                else:
                    result["members"] += 1
                    if len(result["first_members"]) < 5:
                        mtype_str = member.type.dstr() if member.type else "?"
                        result["first_members"].append(
                            "+0x%X %s %s" % (member.offset // 8, mtype_str, member.name))

    return result


def main():
    try:
        ida_auto.auto_wait()
        log("[*] Checking class type definitions in PAL3 IDB")

        til = ida_typeinf.get_idati()
        total_types = til.get_ordinal_qty() if hasattr(til, 'get_ordinal_qty') else ida_typeinf.get_ordinal_qty(til) if hasattr(ida_typeinf, 'get_ordinal_qty') else 0
        log("[*] Total local types: %d" % total_types)
        log("")

        found = 0
        has_members = 0
        has_bases = 0

        for name in CHECK_CLASSES:
            info = check_class(til, name)
            if info is None:
                log("  [X] %-20s NOT FOUND" % name)
                continue

            found += 1
            if info["members"] > 0:
                has_members += 1
            if info["bases"] > 0:
                has_bases += 1

            bases_str = " : " + ", ".join(info["base_names"]) if info["base_names"] else ""
            log("  [+] %-20s size=%d, %d members, %d bases%s" % (
                name, info["size"], info["members"], info["bases"], bases_str))
            for m in info["first_members"]:
                log("      %s" % m)

        log("")
        log("[*] Summary: %d/%d found, %d have members, %d have bases" % (
            found, len(CHECK_CLASSES), has_members, has_bases))

        # Also count total structs with bases
        total_with_bases = 0
        total_structs = 0
        if total_types > 0:
            for ordinal in range(1, total_types + 1):
                tif = ida_typeinf.tinfo_t()
                if not tif.get_numbered_type(til, ordinal):
                    continue
                if not tif.is_struct():
                    continue
                total_structs += 1
                si = ida_typeinf.udt_type_data_t()
                if tif.get_udt_details(si):
                    for i in range(si.size()):
                        if si[i].is_baseclass():
                            total_with_bases += 1
                            break

        log("[*] Total structs: %d, with inheritance: %d" % (total_structs, total_with_bases))

    except Exception as e:
        import traceback
        log("[!] %s" % str(e))
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))
    idc.qexit(0)

if __name__ == '__main__':
    main()
