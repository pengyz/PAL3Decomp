"""
IDAPython: PAL3.exe 函数大小+顺序匹配

核心原理:
  同一源文件中的函数在编译后保持相同顺序。
  函数大小虽因编译器不同而异,但大/小函数的相对区分仍然明显。
  利用已知锚点(如 CEffCylinder::Create)验证匹配正确性。

策略:
  1. 对每个已知地址范围的源文件:
     - 从PDB获取函数列表(按地址排序)
     - 从IDB获取同范围函数列表
     - 如果数量接近且有锚点验证,按顺序匹配
  2. 锚点验证:
     - 如果范围内已有命名函数(如Create),验证其在序列中的位置
     - 只有通过验证的匹配才会应用

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
import struct
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_size_order_match_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0
DATA_START = 0x00580000
DATA_END = 0x0060C000
RDATA_START = 0x0056A000
RDATA_END = 0x0057F178

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def get_func_size(ea):
    func = ida_funcs.get_func(ea)
    return func.end_ea - func.start_ea if func else 0


def find_string_in_data(text_bytes, data_bytes, rdata_bytes, search_str):
    """Find a string in data/rdata and return functions that reference it."""
    search_bytes = search_str.encode('ascii')
    results = []
    for seg_bytes, seg_start in [(data_bytes, DATA_START), (rdata_bytes, RDATA_START)]:
        if not seg_bytes:
            continue
        pos = 0
        while True:
            pos = seg_bytes.find(search_bytes, pos)
            if pos == -1:
                break
            va = seg_start + pos
            needle = struct.pack('<I', va)
            tpos = 0
            while True:
                tpos = text_bytes.find(needle, tpos)
                if tpos == -1:
                    break
                code_ea = TEXT_START + tpos
                func = ida_funcs.get_func(code_ea)
                if func:
                    results.append(func.start_ea)
                tpos += 1
            pos += 1
    return list(set(results))


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 函数大小+顺序匹配")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        pdb_functions = pdb_data.get('functions', [])
        pdb_by_file = {}
        pdb_by_name = {}
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

        text_bytes = ida_bytes.get_bytes(TEXT_START, TEXT_END - TEXT_START)
        data_bytes = ida_bytes.get_bytes(DATA_START, DATA_END - DATA_START)
        rdata_bytes = ida_bytes.get_bytes(RDATA_START, RDATA_END - RDATA_START)

        if not text_bytes:
            log("[!] Cannot read .text")
            return

        applied = 0
        all_matches = []

        # ============================================================
        # Known anchors from previous runs
        # ============================================================
        anchors = {
            # address → (name, source_file)
            0x004C4060: ('CEffCylinder::Create', 'effcylinder.cpp'),
            0x004C6C10: ('CEffExplosive::Create', 'effexplosive.cpp'),
            0x004C98F0: ('CEffGrid::Create', 'effgrid.cpp'),
            0x004CB800: ('CEffMeteor::Create', 'effmeteor.cpp'),
            0x004D1090: ('CEffQuad::Create', 'effquad.cpp'),
            0x004D3AD0: ('CEffShock::Create', 'effshock.cpp'),
            0x00404800: ('PAL3::Create', 'pal3.cpp'),
            0x00431FB0: ('PalScript::Update', 'palscript.cpp'),
        }

        # Source files with known address ranges
        # range_start is the first known function, range_end is estimated from next file
        file_ranges = [
            # (filename, range_start, range_end_estimate, anchor_positions)
            ('effcylinder.cpp', 0x4C4060, 0x4C6C10),
            ('effexplosive.cpp', 0x4C6C10, 0x4C98F0),
            ('effgrid.cpp', 0x4C98F0, 0x4CB800),
            ('effmeteor.cpp', 0x4CB800, 0x4CE100),
            ('effmgr.cpp', 0x4CE100, 0x4D1090),
            ('effquad.cpp', 0x4D1090, 0x4D3AD0),
            ('effshock.cpp', 0x4D3AD0, 0x4D5500),
        ]

        # ============================================================
        # Phase 1: For each file range, try size-order matching
        # ============================================================
        log("")
        log("[Phase 1] 文件范围顺序匹配")

        for filename, range_start, range_end in file_ranges:
            log("")
            log("--- %s [0x%X - 0x%X] ---" % (filename, range_start, range_end))

            # Get PDB functions for this file, sorted by address
            pdb_funcs = pdb_by_file.get(filename, [])
            if not pdb_funcs:
                log("    No PDB data")
                continue

            pdb_sorted = []
            for f in pdb_funcs:
                addr = f.get('address', '0')
                if isinstance(addr, str):
                    addr = int(addr, 16)
                pdb_sorted.append((addr, f))
            pdb_sorted.sort(key=lambda x: x[0])

            # Calculate PDB function sizes
            pdb_with_sizes = []
            for i, (addr, f) in enumerate(pdb_sorted):
                if i + 1 < len(pdb_sorted):
                    size = pdb_sorted[i+1][0] - addr
                else:
                    size = 200  # estimate for last function
                pdb_with_sizes.append((f, size))

            # Get IDB functions in range
            idb_funcs = []
            for ea in idautils.Functions(range_start, range_end):
                size = get_func_size(ea)
                name = ida_name.get_name(ea) or ""
                idb_funcs.append((ea, size, name))

            log("    PDB: %d funcs, IDB: %d funcs" % (len(pdb_with_sizes), len(idb_funcs)))

            if not idb_funcs:
                continue

            # Find anchor in this range
            anchor_idx_pdb = -1
            anchor_idx_idb = -1
            for anchor_ea, (anchor_name, anchor_file) in anchors.items():
                if anchor_file == filename and range_start <= anchor_ea < range_end:
                    # Find in PDB list
                    for i, (f, _) in enumerate(pdb_with_sizes):
                        if f['name'] == anchor_name:
                            anchor_idx_pdb = i
                            break
                    # Find in IDB list
                    for i, (ea, _, _) in enumerate(idb_funcs):
                        if ea == anchor_ea:
                            anchor_idx_idb = i
                            break
                    if anchor_idx_pdb >= 0 and anchor_idx_idb >= 0:
                        log("    Anchor: %s at PDB[%d], IDB[%d]" % (
                            anchor_name, anchor_idx_pdb, anchor_idx_idb))
                        break

            if anchor_idx_pdb < 0 or anchor_idx_idb < 0:
                log("    No anchor found, skipping")
                continue

            # Use anchor to align: offset = anchor_idx_idb - anchor_idx_pdb
            offset = anchor_idx_idb - anchor_idx_pdb

            # Try to match functions using the offset
            matched_count = 0
            for pdb_idx, (pdb_func, pdb_size) in enumerate(pdb_with_sizes):
                idb_idx = pdb_idx + offset
                if idb_idx < 0 or idb_idx >= len(idb_funcs):
                    continue

                ea, idb_size, existing_name = idb_funcs[idb_idx]
                pdb_name = pdb_func['name']
                mangled = pdb_func.get('mangled_name', '')

                # Skip if already correctly named
                if not existing_name.startswith("sub_") and not existing_name.startswith("maybe_"):
                    # Verify: if this is the anchor, should match
                    if ea in anchors:
                        matched_count += 1
                    continue

                if not mangled:
                    continue

                # Size similarity check (allow 50% variance due to different compilers)
                if pdb_size > 20 and idb_size > 20:
                    ratio = float(idb_size) / pdb_size
                    if ratio < 0.3 or ratio > 3.0:
                        # Too different in size, might be misaligned
                        log("    SKIP: %s (PDB size %d, IDB size %d, ratio %.2f)" % (
                            pdb_name, pdb_size, idb_size, ratio))
                        continue

                # Apply name
                if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                    applied += 1
                    matched_count += 1
                    all_matches.append({
                        'addr': '0x%08X' % ea,
                        'name': pdb_name,
                        'mangled': mangled,
                        'evidence': 'order+size in %s (idx %d, offset %d)' % (filename, pdb_idx, offset),
                        'idb_size': idb_size,
                        'pdb_size': pdb_size,
                    })
                    log("    MATCH: 0x%08X = %s (idb=%d, pdb=%d)" % (
                        ea, pdb_name, idb_size, pdb_size))

            log("    Matched: %d / %d" % (matched_count, len(pdb_with_sizes)))

        # ============================================================
        # Phase 2: PalScript neighborhood matching
        # ============================================================
        log("")
        log("[Phase 2] PalScript 邻域匹配")

        # PalScript::Update is at 0x431FB0 in PAL3.exe
        # In PDB, palscript.cpp functions range from PalScript::PalScript (0x49F380) to PalScript::GetScriptInstance (0x4A0790)
        # Let's find the full palscript range in PAL3.exe

        palscript_funcs = pdb_by_file.get('palscript.cpp', [])
        if palscript_funcs:
            pdb_ps_sorted = []
            for f in palscript_funcs:
                addr = f.get('address', '0')
                if isinstance(addr, str):
                    addr = int(addr, 16)
                pdb_ps_sorted.append((addr, f))
            pdb_ps_sorted.sort(key=lambda x: x[0])

            log("[*] PDB palscript.cpp: %d functions" % len(pdb_ps_sorted))
            for addr, f in pdb_ps_sorted:
                log("    0x%08X  %s" % (addr, f['name']))

            # Find PalScript::Update position in PDB list
            ps_update_pdb_idx = -1
            for i, (_, f) in enumerate(pdb_ps_sorted):
                if f['name'] == 'PalScript::Update':
                    ps_update_pdb_idx = i
                    break

            if ps_update_pdb_idx >= 0:
                log("[*] PalScript::Update at PDB index %d" % ps_update_pdb_idx)

                # Estimate palscript.cpp range in PAL3.exe
                # PalScript::Update = 0x431FB0
                # In PDB, it's at index ps_update_pdb_idx out of N functions
                # The range before/after it should have other PalScript functions

                # Get IDB functions near PalScript::Update
                ps_range_start = 0x431040  # ~3KB before Update
                ps_range_end = 0x4344F0  # ~9KB after Update
                idb_ps_funcs = []
                for ea in idautils.Functions(ps_range_start, ps_range_end):
                    size = get_func_size(ea)
                    name = ida_name.get_name(ea) or ""
                    idb_ps_funcs.append((ea, size, name))

                log("[*] IDB palscript range: %d functions" % len(idb_ps_funcs))

                # Find PalScript::Update index in IDB list
                ps_update_idb_idx = -1
                for i, (ea, _, _) in enumerate(idb_ps_funcs):
                    if ea == 0x431FB0:
                        ps_update_idb_idx = i
                        break

                if ps_update_idb_idx >= 0:
                    offset = ps_update_idb_idx - ps_update_pdb_idx
                    log("[*] Offset: %d (PDB[%d] = IDB[%d])" % (
                        offset, ps_update_pdb_idx, ps_update_idb_idx))

                    # Calculate PDB sizes
                    pdb_ps_with_sizes = []
                    for i, (addr, f) in enumerate(pdb_ps_sorted):
                        if i + 1 < len(pdb_ps_sorted):
                            size = pdb_ps_sorted[i+1][0] - addr
                        else:
                            size = 200
                        pdb_ps_with_sizes.append((f, size))

                    # Apply matches
                    for pdb_idx, (pdb_func, pdb_size) in enumerate(pdb_ps_with_sizes):
                        idb_idx = pdb_idx + offset
                        if idb_idx < 0 or idb_idx >= len(idb_ps_funcs):
                            continue

                        ea, idb_size, existing_name = idb_ps_funcs[idb_idx]
                        pdb_name = pdb_func['name']
                        mangled = pdb_func.get('mangled_name', '')

                        if not existing_name.startswith("sub_") and not existing_name.startswith("maybe_"):
                            continue
                        if not mangled:
                            continue

                        # Size check
                        if pdb_size > 20 and idb_size > 20:
                            ratio = float(idb_size) / pdb_size
                            if ratio < 0.3 or ratio > 3.0:
                                log("    SKIP: %s (PDB %d, IDB %d, ratio %.2f)" % (
                                    pdb_name, pdb_size, idb_size, ratio))
                                continue

                        if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                            applied += 1
                            all_matches.append({
                                'addr': '0x%08X' % ea,
                                'name': pdb_name,
                                'mangled': mangled,
                                'evidence': 'order in palscript.cpp (idx %d, offset %d)' % (pdb_idx, offset),
                            })
                            log("    MATCH: 0x%08X = %s" % (ea, pdb_name))

        # ============================================================
        # Phase 3: Additional string-based identification
        # ============================================================
        log("")
        log("[Phase 3] 额外字符串识别")

        # Look for more "new fail in" patterns and other error messages
        # that directly name functions
        string_patterns = [
            # (search_string, class, method)
            (b"CCBSystem", None, None),  # Find all references to class name
            (b"CCBStage", None, None),
            (b"CCBRoleState", None, None),
            (b"PalScript", None, None),
            (b"CEffectSystem", None, None),
            (b"PlayerMgr", None, None),
            (b"SceneObj", None, None),
        ]

        # For each major class, find where its name appears as a string
        class_func_mapping = {}
        for pattern_bytes, _, _ in string_patterns:
            class_name = pattern_bytes.decode('ascii')
            # Search in data
            funcs_referencing = find_string_in_data(text_bytes, data_bytes, rdata_bytes, class_name)
            if funcs_referencing:
                unnamed = [ea for ea in funcs_referencing
                          if (ida_name.get_name(ea) or "").startswith("sub_")]
                if unnamed:
                    class_func_mapping[class_name] = unnamed
                    log("    %s: %d refs (%d unnamed)" % (class_name, len(funcs_referencing), len(unnamed)))

        # ============================================================
        # Phase 4: Find more anchors via unique string content
        # ============================================================
        log("")
        log("[Phase 4] 独特字符串锚点")

        # Strings that appear only in one function and clearly identify it
        unique_identifiers = [
            # (string_to_search, expected_pdb_name)
            ("PAL3 VERSION", "PAL3::Create"),
            ("pal3.ini", None),  # File loading - likely PAL3::Create or ParseCmdLine
            ("d3dapp.ini", None),
            (".scn", None),  # Scene loading
            (".cpk", None),  # CPK archive
            ("basedata.cpk", None),
            ("music.cpk", None),
            ("movie.cpk", None),
            ("GAMEDATA\\", None),
            ("SCE\\", None),
        ]

        for search_str, expected_name in unique_identifiers:
            funcs = find_string_in_data(text_bytes, data_bytes, rdata_bytes, search_str)
            if funcs:
                func_names = [(ea, ida_name.get_name(ea) or "sub_%X" % ea) for ea in funcs]
                log("    \"%s\" → %s" % (search_str,
                    [(hex(ea), n[:30]) for ea, n in func_names[:5]]))

        # ============================================================
        # Summary
        # ============================================================
        log("")
        log("[*] === 总结 ===")
        named = sum(1 for ea in idautils.Functions(TEXT_START, TEXT_END)
                   if not (ida_name.get_name(ea) or "").startswith("sub_"))
        total = sum(1 for _ in idautils.Functions(TEXT_START, TEXT_END))
        log("[*] 命名: %d / %d (%.1f%%)" % (named, total, 100.0*named/total))
        log("[*] 本次新增: %d" % applied)
        log("[*] 匹配列表:")
        for m in all_matches:
            log("    %s = %s" % (m['addr'], m['name']))

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
