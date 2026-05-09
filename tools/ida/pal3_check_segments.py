"""
IDAPython: 检查 PAL3.exe IDB 的段布局 + 测试全局变量可达性
"""
import ida_auto
import ida_bytes
import ida_segment
import ida_name
import idc
import json
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "pal3_check_segments_log.txt")
CALLGRAPH = os.path.join(PROJECT_ROOT, "asm", "pal3", "call_graph.json")

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def main():
    ida_auto.auto_wait()
    log("[*] PAL3.exe 段布局检查")

    # List all segments
    log("\n=== 段列表 ===")
    seg = ida_segment.get_first_seg()
    while seg:
        name = ida_segment.get_segm_name(seg) or "?"
        log("  %-12s 0x%08X - 0x%08X (size: 0x%X = %d KB)" % (
            name, seg.start_ea, seg.end_ea,
            seg.end_ea - seg.start_ea,
            (seg.end_ea - seg.start_ea) // 1024))
        seg = ida_segment.get_next_seg(seg.start_ea)

    # Check specific addresses from call_graph globals
    log("\n=== 全局变量可达性测试 ===")
    test_addrs = [
        (0x005833B8, "g_bGameActive"),
        (0x005833BC, "g_nGameFlags"),
        (0x00975ED8, "g_GDB"),
        (0x00A3A6EC, "g_pCursorNode1"),
        (0x00BFDA34, "g_pVideoPlayer"),
        (0x00BFDA60, "g_pGfxManager"),
        (0x00BFDA64, "g_pActorMgr"),
        (0x00BFDA68, "g_pCamera"),
        (0x00BFDA6C, "g_nGameState"),
        (0x00BFDA74, "g_pCBSystem"),
        (0x00C116EC, "g_pRoleSystem"),
        (0x00DB9FD0, "g_GameData"),
        (0x017B1EC0, "g_Logger"),
    ]

    for addr, expected_name in test_addrs:
        loaded = ida_bytes.is_loaded(addr)
        cur_name = ida_name.get_name(addr) or "(none)"
        seg = ida_segment.getseg(addr)
        seg_name = ida_segment.get_segm_name(seg) if seg else "(no seg)"
        log("  0x%08X %-20s loaded=%s seg=%-8s cur_name=%s" % (
            addr, expected_name, loaded, seg_name, cur_name))

        # Try to rename if loaded
        if loaded and (cur_name.startswith("dword_") or cur_name.startswith("byte_") or
                       cur_name.startswith("flt_") or cur_name.startswith("unk_") or
                       not cur_name or cur_name == "(none)"):
            clean = expected_name.replace('::', '_')
            result = ida_name.set_name(addr, clean, ida_name.SN_NOWARN | ida_name.SN_FORCE)
            log("    -> rename to %s: %s" % (clean, "OK" if result else "FAIL"))

    idc.save_database(idc.get_idb_path(), 0)

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
