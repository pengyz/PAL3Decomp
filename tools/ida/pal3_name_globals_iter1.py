"""
IDAPython: Name and type top unnamed global variables (iteration 1).
Based on usage pattern analysis from generated source code.
"""
import ida_auto, ida_name, ida_typeinf, idc, os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_name_globals_iter1_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

# (address, name, type_string_or_None)
GLOBALS = [
    # stru_BFAD70: GRPinput instance (has m_mouseMaxX, m_lpDI members)
    (0x00BFAD70, "g_Input", "GRPinput"),

    # stru_C04390: PAL3 game state (huge static object)
    # Size analysis: references up to .m_info[54112] -> this is likely SceneMgr or similar large object
    # Based on address C04390 and refs to CScreenMode, GRPinput -> likely the main game manager
    # Leave type as-is for now, just name it
    (0x00C04390, "g_SceneMgr", None),

    # dword_5DFDEC: CRT rand seed (214013*x + 2531011 is MSVC LCG)
    (0x005DFDEC, "g_RandSeed", "int"),

    # dword_17AD310: rand call counter (always incremented with rand)
    (0x017AD310, "g_nRandCallCount", "int"),

    # dword_C04388: near g_SceneMgr, likely related field
    (0x00C04388, "g_nSceneType", "int"),

    # dword_C04384: near g_SceneMgr
    (0x00C04384, "g_nSceneState", "int"),

    # dword_1895580: frequently accessed state
    (0x01895580, "g_nCursorState", "int"),

    # byte_1895560: flag
    (0x01895560, "g_bCursorVisible", "unsigned char"),

    # dword_1896BE0: frequently accessed
    (0x01896BE0, "g_nUIState", "int"),

    # dword_D8E4C0: game data area
    (0x00D8E4C0, "g_GameData", "CGameData"),

    # off_60AD00: likely a vtable or function table
    (0x0060AD00, "g_pVtbl_SceneMgr", None),

    # dword_BFDB84: near our other BFDA globals
    (0x00BFDB84, "g_bShowRenderInfo", "int"),

    # stru_8ACBF8: referenced in PAL3 init
    (0x008ACBF8, "g_PAL3Data", None),

    # dword_C04370..C04374: scene-related cluster
    (0x00C04370, "g_nSceneFlags", "int"),
    (0x00C04374, "g_nSceneMode", "int"),
]

def main():
    try:
        ida_auto.auto_wait()
        log("[*] Naming global variables (iteration 1)")

        til = ida_typeinf.get_idati()
        named = 0
        typed = 0

        for entry in GLOBALS:
            addr = entry[0]
            name = entry[1]
            type_str = entry[2] if len(entry) > 2 else None

            # Set name
            if ida_name.set_name(addr, name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                named += 1
                log("  [+] 0x%08X: %s" % (addr, name))
            else:
                log("  [-] 0x%08X: name failed for %s" % (addr, name))

            # Set type if provided
            if type_str:
                tif = ida_typeinf.tinfo_t()
                decl = "%s %s;" % (type_str, name)
                if ida_typeinf.parse_decl(tif, til, decl, ida_typeinf.PT_VAR) is not None:
                    if ida_typeinf.apply_tinfo(addr, tif, ida_typeinf.TINFO_DEFINITE):
                        typed += 1

        log("[*] Named: %d / %d, Typed: %d" % (named, len(GLOBALS), typed))
        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] Saved. Done.")

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
