"""
Fix SceneMgr struct in IDA for PAL3.exe.

Based on binary analysis (tools/analyze_scenemgr.py):
- Header: 7 DWORD pointers (+0x00 to +0x18)
- 5-element array at +0x288, stride 0x580
- Embedded CCBAI data at +0x1BA0
- Float vectors at +0xA91C
- Second hot zone at +0xC5D0-0xD360

Uses ida_typeinf API (IDA 9.x compatible).
"""
import ida_auto
import ida_typeinf
import ida_bytes
import ida_name
import idc
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_fix_SceneMgr_log.txt")

log_lines = []
def log(msg):
    log_lines.append(str(msg))
    print(msg)

SCENEMGR_ADDR = 0x00C04390

def main():
    ida_auto.auto_wait()
    til = ida_typeinf.get_idati()

    log("[*] Creating SceneMgr struct for PAL3.exe")
    log("[*] g_SceneMgr @ 0x%08X" % SCENEMGR_ADDR)

    udt = ida_typeinf.udt_type_data_t()

    def add_member(offset, name, size, tif=None):
        m = ida_typeinf.udt_member_t()
        m.name = name
        m.offset = offset * 8  # bits
        m.size = size * 8      # bits
        if tif:
            m.type = tif
        elif size == 4:
            m.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT32)
        elif size == 1:
            m.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT8 | ida_typeinf.BTMT_UNSIGNED)
        elif size == 2:
            m.type = ida_typeinf.tinfo_t(ida_typeinf.BT_INT16)
        else:
            arr = ida_typeinf.tinfo_t()
            arr.create_array(ida_typeinf.tinfo_t(ida_typeinf.BT_INT8), size)
            m.type = arr
        udt.push_back(m)

    # Make a DWORD pointer type
    ptr_tif = ida_typeinf.tinfo_t(ida_typeinf.BT_INT32)

    # Helper: create pointer-to-named-type
    def make_ptr_type(type_name):
        """Create a pointer type to a named struct/class."""
        base = ida_typeinf.tinfo_t()
        if not base.get_named_type(til, type_name):
            # Create forward declaration
            decl = "struct %s;" % type_name
            ida_typeinf.parse_decl(base, til, decl, ida_typeinf.PT_TYP)
            base.get_named_type(til, type_name)
        p = ida_typeinf.tinfo_t()
        p.create_ptr(base)
        return p

    # === HEADER: Runtime pointers (typed) ===
    add_member(0x0000, "m_pGfxMgr",      4, make_ptr_type("gbGfxManager"))
    add_member(0x0004, "m_pSceneRoot",    4, make_ptr_type("gbSceneGraph"))
    add_member(0x0008, "m_pAddEffect2",   4, make_ptr_type("gbRenderEffect"))
    add_member(0x000C, "m_pAlphaEffect2", 4, make_ptr_type("gbRenderEffect"))
    add_member(0x0010, "m_pAddEffect",    4, make_ptr_type("gbRenderEffect"))
    add_member(0x0014, "m_pAlphaEffect",  4, make_ptr_type("gbRenderEffect"))
    add_member(0x0018, "m_pCamera",       4, make_ptr_type("gbCamera"))

    # === PRE-ARRAY REGION ===
    add_member(0x001C, "_preArray", 0x288 - 0x1C)

    # === MAIN ARRAY: 5 elements x 0x580 bytes ===
    for i in range(5):
        base = 0x288 + i * 0x580
        add_member(base, "m_slot%d" % i, 0x580)

    # === POST-ARRAY ===
    add_member(0x1E08, "_postSlots", 0x3DC0 - 0x1E08)

    # === Script state ===
    add_member(0x3DC0, "m_scriptState0", 4)
    add_member(0x3DC4, "m_scriptState1", 4)
    add_member(0x3DC8, "m_scriptState2", 4)
    add_member(0x3DCC, "m_scriptState3", 4)

    # === Float/scene region ===
    add_member(0x3DD0, "_midRegion", 0xA91C - 0x3DD0)

    # === Light/direction floats ===
    float_tif = ida_typeinf.tinfo_t(ida_typeinf.BT_FLOAT)
    add_member(0xA91C, "m_lightDirX", 4, float_tif)
    add_member(0xA920, "m_lightDirY", 4, float_tif)
    add_member(0xA924, "m_lightDirZ", 4, float_tif)
    add_member(0xA928, "m_upX",       4, float_tif)
    add_member(0xA92C, "m_upY",       4, float_tif)

    # === Extended region ===
    add_member(0xA930, "_extended", 0xC5D0 - 0xA930)

    # === Second hot zone ===
    add_member(0xC5D0, "m_pGameData",      4, ptr_tif)
    add_member(0xC5D4, "_c5d4",            4)
    add_member(0xC5D8, "m_pCameraCtrl",    4, ptr_tif)
    add_member(0xC5DC, "m_pScriptCtrl",    4, ptr_tif)
    add_member(0xC5E0, "_gap_c5e0",        0xC938 - 0xC5E0)
    add_member(0xC938, "m_nCameraState",   4)
    add_member(0xC93C, "_gap_c93c",        0xC9A8 - 0xC93C)
    add_member(0xC9A8, "m_szUIString",     512)  # char[512] string buffer
    add_member(0xCBA8, "_gap_cba8",        0xCD0C - 0xCBA8)
    add_member(0xCD0C, "m_fMoveParam",     4, float_tif)
    add_member(0xCD10, "_gap_cd10",        0xD35C - 0xCD10)
    add_member(0xD35C, "m_pCollisionNode", 4, ptr_tif)
    add_member(0xD360, "_tail",            4)

    # Create the type
    tif = ida_typeinf.tinfo_t()
    tif.create_udt(udt, ida_typeinf.BTF_STRUCT)
    final_size = tif.get_size()
    log("[*] SceneMgr struct size: 0x%X (%d bytes)" % (final_size, final_size))

    # Save to til
    tif.set_named_type(til, "SceneMgr", ida_typeinf.NTF_REPLACE)
    log("[+] SceneMgr type saved to TIL")

    # Apply at global address
    ida_name.set_name(SCENEMGR_ADDR, "g_SceneMgr", ida_name.SN_FORCE)
    ida_bytes.del_items(SCENEMGR_ADDR, 0, final_size)
    ida_bytes.create_struct(SCENEMGR_ADDR, final_size,
                           ida_typeinf.get_struc_id("SceneMgr") if hasattr(ida_typeinf, 'get_struc_id') else -1)

    # Try applying tinfo directly
    if ida_typeinf.apply_tinfo(SCENEMGR_ADDR, tif, ida_typeinf.TINFO_DEFINITE):
        log("[+] Applied SceneMgr type at 0x%08X" % SCENEMGR_ADDR)
    else:
        log("[!] Failed to apply type at address, try manually")

    log("[*] Done. Re-decompile SceneMgr methods to verify.")

    ida_auto.auto_wait()
    idc.qexit(0)

try:
    main()
except Exception as e:
    log("[ERROR] %s" % str(e))
    import traceback
    log(traceback.format_exc())
finally:
    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w') as f:
        f.write('\n'.join(log_lines))
