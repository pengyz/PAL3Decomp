"""
IDAPython: PAL3.exe WinMain 调用链匹配

已知:
  - PAL3.exe WinMain = 0x541900
  - WinMain 调用: sub_404800, sub_4055D0, sub_405C00, sub_406230, sub_513380, sub_5382D0, sub_541860, sub_541C40
  - PDB: WinMain calls PAL3::Create (0x427135)
  - PDB: pal3.cpp range 0x426E03-0x42B408 (41 funcs)
  - PAL3.exe: pal3.cpp range 0x404800-0x406310 (22 funcs in range, 路径字符串确认)

策略:
  1. WinMain → PAL3::Create (most likely sub_404800, first callee)
  2. 从 PAL3::Create 的已知调用模式继续匹配
  3. PalScript::Update 已在 PAL3.exe 中命名 → 从它扩展
  4. 利用 PAL3.exe 中 CRT 函数的已知位置辅助匹配

运行环境: PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_name
import idautils
import idc
import json
import os
import re
import struct
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_winmain_chain_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0
RDATA_START = 0x0056A000
RDATA_END = 0x0057F178
DATA_START = 0x00580000
DATA_END = 0x0060C000

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def get_callees_ordered(func_ea, text_bytes):
    """Get call targets in order of appearance (preserving call sequence)."""
    func = ida_funcs.get_func(func_ea)
    if not func:
        return []
    callees = []
    seen = set()
    start_off = func.start_ea - TEXT_START
    end_off = func.end_ea - TEXT_START
    if start_off < 0 or end_off > len(text_bytes):
        return callees

    i = start_off
    while i < end_off - 4:
        if text_bytes[i] == 0xE8:  # CALL rel32
            rel = struct.unpack_from('<i', text_bytes, i + 1)[0]
            target = (TEXT_START + i + 5 + rel) & 0xFFFFFFFF
            if TEXT_START <= target < TEXT_END and target not in seen:
                callees.append(target)
                seen.add(target)
            i += 5
        else:
            i += 1
    return callees


def get_func_size(ea):
    """Get function size."""
    func = ida_funcs.get_func(ea)
    if func:
        return func.end_ea - func.start_ea
    return 0


def find_string_refs(text_bytes, str_va):
    """Find all code locations that reference a string VA."""
    needle = struct.pack('<I', str_va)
    refs = []
    pos = 0
    while True:
        pos = text_bytes.find(needle, pos)
        if pos == -1:
            break
        refs.append(TEXT_START + pos)
        pos += 1
    return refs


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe WinMain 调用链匹配")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        # Load PDB
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        pdb_functions = pdb_data.get('functions', [])

        # Build indices
        pdb_by_name = {}
        pdb_by_file = {}
        for func in pdb_functions:
            name = func.get('name', '')
            mangled = func.get('mangled_name', '')
            src = func.get('source_file', '')
            if name and mangled:
                pdb_by_name[name] = func
            if src:
                bn = os.path.basename(src).lower()
                if bn not in pdb_by_file:
                    pdb_by_file[bn] = []
                pdb_by_file[bn].append(func)

        # Read .text
        text_bytes = ida_bytes.get_bytes(TEXT_START, TEXT_END - TEXT_START)
        rdata_bytes = ida_bytes.get_bytes(RDATA_START, RDATA_END - RDATA_START)
        data_bytes = ida_bytes.get_bytes(DATA_START, DATA_END - DATA_START)
        if not text_bytes:
            log("[!] Cannot read .text")
            return

        applied = 0

        # ============================================================
        # Phase 1: WinMain analysis
        # ============================================================
        log("")
        log("[Phase 1] WinMain 调用链分析")

        WINMAIN_EA = 0x00541900
        winmain_callees = get_callees_ordered(WINMAIN_EA, text_bytes)
        log("[*] WinMain (0x%08X) callees: %d" % (WINMAIN_EA, len(winmain_callees)))
        for i, ea in enumerate(winmain_callees):
            name = ida_name.get_name(ea) or "sub_%X" % ea
            size = get_func_size(ea)
            log("    [%d] 0x%08X size=%d %s" % (i, ea, size, name[:60]))

        # From PDB: WinMain in pal3.cpp calls PAL3::Create as the main initialization
        # PAL3::Create (PDB 0x427135) is a large function that:
        #   - Creates windows, initializes GFX, creates subsystems
        # In PAL3.exe, the first non-CRT callee from WinMain is likely PAL3::Create
        # sub_404800 is first and it's in the pal3.cpp range (confirmed by source path string)

        # Let's verify: sub_404800 should be large (PAL3::Create is ~1700 bytes in PDB)
        candidate_create = 0x00404800
        create_size = get_func_size(candidate_create)
        log("")
        log("[*] PAL3::Create 候选: 0x%08X (size=%d)" % (candidate_create, create_size))

        # Examine its callees
        create_callees = get_callees_ordered(candidate_create, text_bytes)
        log("    Callees: %d" % len(create_callees))
        for i, ea in enumerate(create_callees[:20]):
            name = ida_name.get_name(ea) or "sub_%X" % ea
            size = get_func_size(ea)
            log("      [%d] 0x%08X size=%d %s" % (i, ea, size, name[:50]))

        # PAL3::Create in PDB calls:
        #   PAL3::CreateGfxWindow, PAL3::InitGFX, PAL3::CreateEffectSystem, etc.
        # These are all in pal3.cpp, so addresses should be nearby (0x404xxx-0x406xxx range)

        # Apply PAL3::Create name
        mangled_create = "?Create@PAL3@@SAXPAUHINSTANCE__@@@Z"
        existing = ida_name.get_name(candidate_create) or ""
        if existing.startswith("sub_"):
            if ida_name.set_name(candidate_create, mangled_create, ida_name.SN_FORCE):
                applied += 1
                log("    APPLIED: 0x%08X = PAL3::Create" % candidate_create)

        # ============================================================
        # Phase 2: pal3.cpp function ordering
        # ============================================================
        log("")
        log("[Phase 2] pal3.cpp 函数顺序匹配")

        # Get all functions in pal3.cpp range (0x404800-0x406310)
        pal3_range_start = 0x00404800
        pal3_range_end = 0x00406400
        pal3_range_funcs = []
        for ea in idautils.Functions(pal3_range_start, pal3_range_end):
            name = ida_name.get_name(ea) or ""
            size = get_func_size(ea)
            pal3_range_funcs.append((ea, size, name))
            log("    0x%08X size=%4d %s" % (ea, size, name[:50]))

        log("[*] pal3.cpp 范围内函数: %d" % len(pal3_range_funcs))

        # PDB pal3.cpp functions sorted by address:
        # (they should appear in the same order in PAL3.exe)
        pdb_pal3_funcs = sorted(pdb_by_file.get('pal3.cpp', []),
                                key=lambda f: int(f.get('address', '0x0'), 16)
                                if isinstance(f.get('address'), str)
                                else f.get('address', 0))

        # The $E187-$E233 functions are static initializers (small, at beginning)
        # First real function is PAL3::PAL3 (constructor)
        # Then PAL3::~PAL3, PAL3::Create, WinProc, ...

        # Since we confirmed sub_404800 = PAL3::Create,
        # functions before it in the range could be PAL3::PAL3, PAL3::~PAL3, or $E statics
        # Functions after it are PAL3::InitGFX etc.

        # Let's trace what PAL3::Create calls in this range
        create_local_callees = [ea for ea in create_callees
                               if pal3_range_start <= ea <= pal3_range_end]
        log("")
        log("[*] PAL3::Create 的本地 (pal3.cpp) callees:")
        for ea in create_local_callees:
            name = ida_name.get_name(ea) or "sub_%X" % ea
            size = get_func_size(ea)
            log("    0x%08X size=%d %s" % (ea, size, name[:50]))

        # PDB tells us PAL3::Create calls these pal3.cpp functions:
        # PAL3::CreateGfxWindow (large, creates D3D window)
        # PAL3::InitGFX (large, initializes graphics)
        # PAL3::CreateEffectSystem
        # These are ordered by address in PDB: InitGFX(0x427DB4), CreateEffectSystem(0x428177),
        # DestroyEffectSystem(0x4284B0), Update(0x42855F), Render(0x428AAE), Destroy(0x42916E)

        # ============================================================
        # Phase 3: CEffMgr identification via string "CEffMgr"
        # ============================================================
        log("")
        log("[Phase 3] CEffMgr 类识别")

        # Search for "CEffMgr" string in data
        effmgr_pattern = b'CEffMgr'
        effmgr_refs = []
        for seg_bytes, seg_start in [(data_bytes, DATA_START), (rdata_bytes, RDATA_START)]:
            if not seg_bytes:
                continue
            pos = 0
            while True:
                pos = seg_bytes.find(effmgr_pattern, pos)
                if pos == -1:
                    break
                va = seg_start + pos
                # Find functions referencing this
                refs = find_string_refs(text_bytes, va)
                for ref in refs:
                    func = ida_funcs.get_func(ref)
                    if func:
                        effmgr_refs.append((func.start_ea, va))
                pos += 1

        log("[*] CEffMgr 字符串引用: %d" % len(effmgr_refs))
        for ea, str_va in effmgr_refs[:10]:
            name = ida_name.get_name(ea) or "sub_%X" % ea
            log("    0x%08X %s" % (ea, name[:50]))

        # ============================================================
        # Phase 4: Known CRT/compiler functions → neighborhood analysis
        # ============================================================
        log("")
        log("[Phase 4] 已知 CRT 函数定位")

        # From WinMain callees, we know:
        # 0x00541D10 = operator delete (??3@YAXPAX@Z)
        # 0x0055353B = operator new (??2@YAPAXI@Z)
        # 0x00553082 = _sprintf
        # 0x00554670 = _strrchr
        # These CRT functions are at the high end of .text (0x541000+)

        # Game code is roughly 0x401000-0x540000
        # CRT/compiler code is 0x540000-0x569500

        # Count game vs CRT functions
        game_funcs = 0
        crt_funcs = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            if ea < 0x540000:
                game_funcs += 1
            else:
                crt_funcs += 1

        log("[*] Game code (<0x540000): %d funcs" % game_funcs)
        log("[*] CRT code (>=0x540000): %d funcs" % crt_funcs)

        # ============================================================
        # Phase 5: PalScript::Update neighborhood
        # ============================================================
        log("")
        log("[Phase 5] PalScript::Update 邻域分析")

        # Find PalScript::Update in current IDB
        palscript_update_ea = None
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if 'PalScript' in name and 'Update' in name:
                palscript_update_ea = ea
                break

        if palscript_update_ea:
            log("[*] PalScript::Update = 0x%08X" % palscript_update_ea)
            ps_callees = get_callees_ordered(palscript_update_ea, text_bytes)
            log("    Callees: %d" % len(ps_callees))
            for ea in ps_callees[:10]:
                name = ida_name.get_name(ea) or "sub_%X" % ea
                log("      0x%08X %s" % (ea, name[:50]))

            # PDB: PalScript::Update (0x49FC5C) is in palscript.cpp
            # palscript.cpp functions in PDB range from 0x49F380 to 0x4A0790
            # So nearby functions in PAL3.exe should also be PalScript methods

            # Get functions near PalScript::Update
            nearby_start = palscript_update_ea - 0x2000
            nearby_end = palscript_update_ea + 0x2000
            log("    Nearby functions [0x%X - 0x%X]:" % (nearby_start, nearby_end))
            nearby_funcs = []
            for ea in idautils.Functions(max(TEXT_START, nearby_start), min(TEXT_END, nearby_end)):
                name = ida_name.get_name(ea) or "sub_%X" % ea
                size = get_func_size(ea)
                nearby_funcs.append((ea, size, name))
                if abs(ea - palscript_update_ea) < 0x1000:
                    log("      0x%08X size=%4d %s" % (ea, size, name[:50]))

        # ============================================================
        # Phase 6: Comprehensive source file → address range mapping
        # ============================================================
        log("")
        log("[Phase 6] 源文件地址范围总结")

        # From advanced_match_report, we have file groups
        # Let's consolidate what we know about code layout:
        known_ranges = {
            'pal3.cpp': (0x404800, 0x406310),
            'effcylinder.cpp': (0x4C4060, None),  # starts at CEffCylinder::Create
            'effexplosive.cpp': (0x4C6C10, 0x4C7CB0),
            'effgrid.cpp': (0x4C98F0, 0x4CABE0),
            'effmeteor.cpp': (0x4CB800, 0x4CD0D0),
            'effmgr.cpp': (0x4CE100, 0x4CE2A0),
            'effquad.cpp': (0x4D1090, 0x4D1F30),
            'effshock.cpp': (0x4D3AD0, None),  # starts at CEffShock::Create
            'cbstagescene.cpp': (0x50FEE0, 0x511340),
            'cbsystem.cpp': (0x5125E0, 0x515D10),
            'cbui.cpp': (0x5177B0, 0x51D4A0),
        }

        for filename, (start, end) in known_ranges.items():
            pdb_funcs = pdb_by_file.get(filename, [])
            if end:
                count = sum(1 for ea in idautils.Functions(start, end))
                log("    %s: 0x%X-0x%X (%d IDB funcs, %d PDB funcs)" % (
                    filename, start, end, count, len(pdb_funcs)))
            else:
                log("    %s: 0x%X-? (%d PDB funcs)" % (filename, start, len(pdb_funcs)))

        # ============================================================
        # Phase 7: Match effmgr.cpp precisely
        # ============================================================
        log("")
        log("[Phase 7] effmgr.cpp 精确匹配")

        # effmgr.cpp range: 0x4CE100-0x4CE2A0 (only 21 funcs in IDB, PDB has 30)
        # But this is a tight range - likely just 2 functions referenced the source path
        # Let's look at what's actually there
        effmgr_start = 0x4CE100
        effmgr_end = 0x4D1090  # up to effquad.cpp start
        log("[*] effmgr.cpp extended range 0x%X - 0x%X:" % (effmgr_start, effmgr_end))

        pdb_effmgr = sorted(pdb_by_file.get('effmgr.cpp', []),
                           key=lambda f: int(f.get('address', '0x0'), 16)
                           if isinstance(f.get('address'), str)
                           else f.get('address', 0))

        log("    PDB effmgr.cpp functions (%d):" % len(pdb_effmgr))
        for f in pdb_effmgr[:15]:
            log("      %s  %s" % (f.get('address', '?'), f['name']))

        # IDB functions in this range
        effmgr_idb_funcs = []
        for ea in idautils.Functions(effmgr_start, effmgr_end):
            name = ida_name.get_name(ea) or "sub_%X" % ea
            size = get_func_size(ea)
            effmgr_idb_funcs.append((ea, size, name))
        log("    IDB functions in range: %d" % len(effmgr_idb_funcs))
        for ea, size, name in effmgr_idb_funcs[:15]:
            log("      0x%08X size=%4d %s" % (ea, size, name[:50]))

        # ============================================================
        # Phase 8: Use function size as discriminator
        # ============================================================
        log("")
        log("[Phase 8] 函数大小签名匹配")

        # For source files where we know the address range AND function count matches,
        # try to match by function size.
        # PDB has function sizes (from address differences)

        # Calculate PDB function sizes for effmgr.cpp
        log("[*] PDB effmgr.cpp 函数大小:")
        for i, f in enumerate(pdb_effmgr):
            addr = f.get('address', '0')
            if isinstance(addr, str):
                addr = int(addr, 16)
            if i + 1 < len(pdb_effmgr):
                next_addr = pdb_effmgr[i+1].get('address', '0')
                if isinstance(next_addr, str):
                    next_addr = int(next_addr, 16)
                pdb_size = next_addr - addr
            else:
                pdb_size = 0
            log("      %s size~%d  %s" % (f.get('address', '?'), pdb_size, f['name']))

        # ============================================================
        # Final statistics
        # ============================================================
        log("")
        log("[*] === 最终统计 ===")
        named = sum(1 for ea in idautils.Functions(TEXT_START, TEXT_END)
                   if not (ida_name.get_name(ea) or "").startswith("sub_"))
        total = sum(1 for _ in idautils.Functions(TEXT_START, TEXT_END))
        log("[*] 命名: %d / %d (%.1f%%)" % (named, total, 100.0*named/total))
        log("[*] 本次新增: %d" % applied)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
