"""
IDAPython: PAL3.exe 链接顺序匹配

利用 PDB 文件链接顺序推断 PAL3.exe 中未知文件的位置。
已知文件的地址范围 + PDB 链接顺序 → 推断相邻未知文件的位置

关键假设:
  PAL3.exe 和 PAL3A.exe 使用相同的 .vcproj/.dsp 文件列表
  → 源文件的编译和链接顺序相同
  → 代码在 .text 中的排列顺序相同

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
LOG_FILE = os.path.join(LOG_DIR, "pal3_link_order_match_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def get_func_size(ea):
    func = ida_funcs.get_func(ea)
    return func.end_ea - func.start_ea if func else 0


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 链接顺序匹配")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        pdb_functions = pdb_data.get('functions', [])
        pdb_by_file = {}
        for func in pdb_functions:
            src = func.get('source_file', '')
            addr = func.get('address', '0')
            if isinstance(addr, str):
                addr = int(addr, 16)
            if src and addr > 0:
                bn = os.path.basename(src).lower()
                if bn not in pdb_by_file:
                    pdb_by_file[bn] = []
                pdb_by_file[bn].append(func)

        # ============================================================
        # Phase 1: Determine PDB link order
        # ============================================================
        log("[Phase 1] PDB 链接顺序")

        pdb_file_order = []  # (min_addr, basename, func_count, funcs_sorted)
        for bn, funcs in pdb_by_file.items():
            if not bn.endswith('.cpp'):
                continue
            addrs = []
            for f in funcs:
                a = f.get('address', '0')
                if isinstance(a, str):
                    a = int(a, 16)
                addrs.append(a)
            min_addr = min(addrs)
            pdb_file_order.append((min_addr, bn, len(funcs),
                                  sorted(funcs, key=lambda f: int(f['address'], 16)
                                         if isinstance(f.get('address'), str) else f.get('address', 0))))
        pdb_file_order.sort()

        # ============================================================
        # Phase 2: Determine current IDB file boundaries
        # ============================================================
        log("")
        log("[Phase 2] IDB 文件边界")

        # Collect named functions and determine which file they belong to
        idb_file_ranges = {}  # basename → (min_ea, max_ea)
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name.startswith("sub_") or name.startswith("nullsub_"):
                continue
            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            if not demangled:
                continue
            base_name = demangled.split('(')[0].strip()

            # Find in PDB to get source file
            for bn, funcs in pdb_by_file.items():
                for f in funcs:
                    if f['name'] == base_name:
                        if bn not in idb_file_ranges:
                            idb_file_ranges[bn] = [ea, ea]
                        idb_file_ranges[bn][0] = min(idb_file_ranges[bn][0], ea)
                        idb_file_ranges[bn][1] = max(idb_file_ranges[bn][1], ea)
                        break
                else:
                    continue
                break

        # Sort by min address
        idb_known_files = sorted(idb_file_ranges.items(), key=lambda x: x[1][0])

        log("[*] 已知 IDB 文件边界: %d" % len(idb_known_files))
        for bn, (min_ea, max_ea) in idb_known_files:
            log("    0x%08X-0x%08X: %s" % (min_ea, max_ea, bn))

        # ============================================================
        # Phase 3: Infer adjacent file positions
        # ============================================================
        log("")
        log("[Phase 3] 推断相邻文件位置")

        # For each known file in IDB, find what comes AFTER it in PDB order
        # Then look at the IDB address space after the known file

        applied = 0
        inferred_files = []

        for i, (known_bn, (known_min, known_max)) in enumerate(idb_known_files):
            # Find this file in PDB order
            pdb_idx = -1
            for j, (_, pdb_bn, _, _) in enumerate(pdb_file_order):
                if pdb_bn == known_bn:
                    pdb_idx = j
                    break

            if pdb_idx < 0:
                continue

            # What's the next file in PDB order?
            if pdb_idx + 1 < len(pdb_file_order):
                next_pdb_file = pdb_file_order[pdb_idx + 1]
                next_bn = next_pdb_file[1]
                next_pdb_count = next_pdb_file[2]
                next_pdb_funcs = next_pdb_file[3]

                # Is this next file already known in IDB?
                if next_bn in idb_file_ranges:
                    continue  # Already mapped

                # Find the next known file's start in IDB
                next_known_start = TEXT_END
                for k in range(i + 1, len(idb_known_files)):
                    next_known_start = idb_known_files[k][1][0]
                    break

                # The gap between current file end and next known file start
                # should contain the next PDB file (and possibly others)
                gap_start = known_max + get_func_size(known_max)
                gap_end = next_known_start

                if gap_end <= gap_start or gap_end - gap_start < 0x100:
                    continue

                # Count functions in gap
                gap_funcs = []
                for ea in idautils.Functions(gap_start, gap_end):
                    size = get_func_size(ea)
                    name = ida_name.get_name(ea) or ""
                    gap_funcs.append((ea, size, name))

                unnamed_in_gap = [f for f in gap_funcs if f[2].startswith("sub_")]

                if not unnamed_in_gap:
                    continue

                # Check if the gap could contain the next PDB file
                # Rough check: similar function count
                if len(gap_funcs) < next_pdb_count * 0.3:
                    continue  # Too few functions for this file

                inferred_files.append((next_bn, gap_start, gap_end, len(gap_funcs),
                                      next_pdb_count, len(unnamed_in_gap)))

        log("[*] 推断文件位置: %d" % len(inferred_files))
        for bn, start, end, idb_count, pdb_count, unnamed in inferred_files:
            log("    %s: 0x%08X-0x%08X (IDB=%d, PDB=%d, unnamed=%d)" % (
                bn, start, end, idb_count, pdb_count, unnamed))

        # ============================================================
        # Phase 4: Match inferred files
        # ============================================================
        log("")
        log("[Phase 4] 推断文件匹配")

        for next_bn, gap_start, gap_end, idb_count, pdb_count, unnamed_count in inferred_files:
            # Get PDB functions for this file
            pdb_funcs = pdb_by_file.get(next_bn, [])
            if not pdb_funcs:
                continue

            pdb_sorted = sorted(pdb_funcs,
                               key=lambda f: int(f['address'], 16)
                               if isinstance(f.get('address'), str)
                               else f.get('address', 0))

            # Get IDB functions in gap
            idb_funcs = []
            for ea in idautils.Functions(gap_start, gap_end):
                size = get_func_size(ea)
                name = ida_name.get_name(ea) or ""
                idb_funcs.append((ea, size, name))

            if not idb_funcs:
                continue

            # Try offset 0 (first IDB func = first PDB func)
            # This works if the gap starts exactly at the file boundary
            # Validate with size comparison

            # Calculate PDB sizes
            pdb_sizes = []
            for k in range(len(pdb_sorted)):
                addr = pdb_sorted[k].get('address', '0')
                if isinstance(addr, str):
                    addr = int(addr, 16)
                if k + 1 < len(pdb_sorted):
                    next_addr = pdb_sorted[k + 1].get('address', '0')
                    if isinstance(next_addr, str):
                        next_addr = int(next_addr, 16)
                    pdb_sizes.append(next_addr - addr)
                else:
                    pdb_sizes.append(200)

            # Try different offsets and score them by size correlation
            best_offset = None
            best_score = 0

            max_offset = min(len(idb_funcs), 50)  # Don't try too many
            for try_offset in range(-10, max_offset):
                score = 0
                matches = 0
                for pdb_idx in range(min(len(pdb_sorted), 20)):  # Check first 20
                    idb_idx = pdb_idx + try_offset
                    if idb_idx < 0 or idb_idx >= len(idb_funcs):
                        continue
                    _, idb_size, _ = idb_funcs[idb_idx]
                    pdb_size = pdb_sizes[pdb_idx] if pdb_idx < len(pdb_sizes) else 200

                    if pdb_size > 30 and idb_size > 30:
                        ratio = float(idb_size) / pdb_size
                        if 0.3 <= ratio <= 3.0:
                            score += 1
                            # Bonus for close match
                            if 0.6 <= ratio <= 1.6:
                                score += 1
                        matches += 1

                if score > best_score and matches >= 3:
                    best_score = score
                    best_offset = try_offset

            if best_offset is None:
                log("    %s: no good offset found" % next_bn)
                continue

            # Apply matches
            file_applied = 0
            for pdb_idx, pdb_func in enumerate(pdb_sorted):
                idb_idx = pdb_idx + best_offset
                if idb_idx < 0 or idb_idx >= len(idb_funcs):
                    continue

                ea, idb_size, existing = idb_funcs[idb_idx]
                if not existing.startswith("sub_") and not existing.startswith("maybe_"):
                    continue

                mangled = pdb_func.get('mangled_name', '')
                if not mangled:
                    continue

                pdb_size = pdb_sizes[pdb_idx] if pdb_idx < len(pdb_sizes) else 200

                # Size filter
                if pdb_size > 30 and idb_size > 30:
                    ratio = float(idb_size) / pdb_size
                    if ratio < 0.15 or ratio > 7.0:
                        continue

                if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                    applied += 1
                    file_applied += 1

            if file_applied > 0:
                log("    %s: +%d (offset=%d, score=%d)" % (
                    next_bn, file_applied, best_offset, best_score))

        log("[*] Phase 4 总计: %d" % applied)

        # ============================================================
        # Phase 5: scriptcmd.cpp special handling
        # ============================================================
        log("")
        log("[Phase 5] scriptcmd.cpp 特殊处理")

        # scriptcmd.cpp is the largest file (238 functions)
        # In PDB order it comes after palscript.cpp (index 27) and scasmdecoder.cpp (index 29)
        # ptrarray.cpp (index 28) is between them

        # In PAL3.exe:
        # palscript.cpp ends around 0x432550
        # After that: sub_4329B0 (size=4149!) which could be a large scriptcmd function

        # Let's find where scriptcmd would start
        # PDB: palscript 0x49F380-0x4A0329, ptrarray 0x4A0810-0x4A0B4C,
        #      scasmdecoder 0x4A0DDF-0x4A226F, scriptcmd 0x4A5944-0x4B3C20

        # So after palscript, there's ptrarray (7 funcs), scasmdecoder (23 funcs),
        # then scriptcmd (238 funcs)

        # In IDB after palscript (0x432550): how many functions until we hit
        # the next known file?
        palscript_end = 0x432600  # approximate end
        # Next known file: uilistbox.cpp starts at 0x43DD60
        # Gap: 0x432600 - 0x43DD60 = ~47KB

        gap_start = 0x432600
        gap_end = 0x43DD60  # uilistbox.cpp start

        gap_funcs = []
        for ea in idautils.Functions(gap_start, gap_end):
            size = get_func_size(ea)
            name = ida_name.get_name(ea) or ""
            gap_funcs.append((ea, size, name))

        log("[*] Gap after palscript: 0x%X-0x%X, %d functions" % (
            gap_start, gap_end, len(gap_funcs)))

        # Expected in this gap: ptrarray(7) + scasmdecoder(23) + scriptcmd(238) = 268
        # Plus possibly some others between scasmdecoder and uilistbox

        # The FIRST large function (4149 bytes at 0x4329B0) is likely the main
        # script command dispatcher - in PDB this might be ScriptCmd::ExecuteCommand

        # Let's try to match scriptcmd.cpp
        pdb_scriptcmd = sorted(pdb_by_file.get('scriptcmd.cpp', []),
                              key=lambda f: int(f['address'], 16)
                              if isinstance(f.get('address'), str)
                              else f.get('address', 0))

        if pdb_scriptcmd:
            log("[*] PDB scriptcmd.cpp: %d functions" % len(pdb_scriptcmd))
            # First few functions
            for f in pdb_scriptcmd[:5]:
                log("    %s  %s" % (f.get('address', '?'), f['name']))

            # In PDB, scriptcmd starts at 0x4A5944
            # Before it: scasmdecoder ends at ~0x4A226F
            # Gap between: ~0x3000 (possibly other small files)

            # In IDB: after palscript(7+23=30 funcs from gap_start),
            # scriptcmd should start around function index 30+

            # Try to find the start by looking for the largest function
            # (the dispatcher is usually very large)
            large_funcs = [(i, ea, sz) for i, (ea, sz, _) in enumerate(gap_funcs) if sz > 1000]
            log("[*] Large functions in gap:")
            for idx, ea, sz in large_funcs[:10]:
                log("    [%d] 0x%08X size=%d" % (idx, ea, sz))

            # PDB scriptcmd sizes
            pdb_sc_sizes = []
            for k in range(len(pdb_scriptcmd)):
                addr = pdb_scriptcmd[k].get('address', '0')
                if isinstance(addr, str):
                    addr = int(addr, 16)
                if k + 1 < len(pdb_scriptcmd):
                    next_addr = pdb_scriptcmd[k + 1].get('address', '0')
                    if isinstance(next_addr, str):
                        next_addr = int(next_addr, 16)
                    pdb_sc_sizes.append(next_addr - addr)
                else:
                    pdb_sc_sizes.append(200)

            # Find largest PDB function
            max_pdb_idx = max(range(len(pdb_sc_sizes)), key=lambda i: pdb_sc_sizes[i])
            log("[*] Largest PDB scriptcmd func: [%d] %s size=%d" % (
                max_pdb_idx, pdb_scriptcmd[max_pdb_idx]['name'], pdb_sc_sizes[max_pdb_idx]))

            # Try to align using the largest function
            # The IDB's 4149-byte function at 0x4329B0 (index in gap)
            large_idb_idx = -1
            for i, (ea, sz, _) in enumerate(gap_funcs):
                if ea == 0x4329B0:
                    large_idb_idx = i
                    break

            if large_idb_idx >= 0:
                # Try aligning this with the largest PDB function
                try_offset = large_idb_idx - max_pdb_idx
                log("[*] Trying offset %d (IDB[%d]=0x4329B0 ↔ PDB[%d]=%s)" % (
                    try_offset, large_idb_idx, max_pdb_idx, pdb_scriptcmd[max_pdb_idx]['name']))

                # Validate with size correlation
                score = 0
                for pdb_idx in range(len(pdb_scriptcmd)):
                    idb_idx = pdb_idx + try_offset
                    if idb_idx < 0 or idb_idx >= len(gap_funcs):
                        continue
                    _, idb_size, _ = gap_funcs[idb_idx]
                    pdb_size = pdb_sc_sizes[pdb_idx]
                    if pdb_size > 30 and idb_size > 30:
                        ratio = float(idb_size) / pdb_size
                        if 0.3 <= ratio <= 3.0:
                            score += 1

                log("    Score: %d / %d" % (score, min(len(pdb_scriptcmd), len(gap_funcs))))

                if score >= 30:  # At least 30 functions match size ratio
                    # Apply
                    sc_applied = 0
                    for pdb_idx, pdb_func in enumerate(pdb_scriptcmd):
                        idb_idx = pdb_idx + try_offset
                        if idb_idx < 0 or idb_idx >= len(gap_funcs):
                            continue
                        ea, idb_size, existing = gap_funcs[idb_idx]
                        if not existing.startswith("sub_"):
                            continue
                        mangled = pdb_func.get('mangled_name', '')
                        if not mangled:
                            continue
                        pdb_size = pdb_sc_sizes[pdb_idx]
                        if pdb_size > 30 and idb_size > 30:
                            ratio = float(idb_size) / pdb_size
                            if ratio < 0.15 or ratio > 7.0:
                                continue
                        if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                            sc_applied += 1
                            applied += 1

                    log("    scriptcmd.cpp: +%d" % sc_applied)
                else:
                    # Try other offsets
                    best_sc_offset = None
                    best_sc_score = 0
                    # The first function of scriptcmd should be after ptrarray+scasmdecoder
                    # ptrarray(7)+scasmdecoder(23) = 30 functions after palscript
                    for try_off in range(20, 60):
                        sc_score = 0
                        for pdb_idx in range(min(len(pdb_scriptcmd), 50)):
                            idb_idx = pdb_idx + try_off
                            if idb_idx < 0 or idb_idx >= len(gap_funcs):
                                continue
                            _, idb_size, _ = gap_funcs[idb_idx]
                            pdb_size = pdb_sc_sizes[pdb_idx]
                            if pdb_size > 30 and idb_size > 30:
                                ratio = float(idb_size) / pdb_size
                                if 0.3 <= ratio <= 3.0:
                                    sc_score += 1
                        if sc_score > best_sc_score:
                            best_sc_score = sc_score
                            best_sc_offset = try_off

                    log("    Best alternative: offset=%s score=%d" % (best_sc_offset, best_sc_score))

                    if best_sc_offset is not None and best_sc_score >= 30:
                        sc_applied = 0
                        for pdb_idx, pdb_func in enumerate(pdb_scriptcmd):
                            idb_idx = pdb_idx + best_sc_offset
                            if idb_idx < 0 or idb_idx >= len(gap_funcs):
                                continue
                            ea, idb_size, existing = gap_funcs[idb_idx]
                            if not existing.startswith("sub_"):
                                continue
                            mangled = pdb_func.get('mangled_name', '')
                            if not mangled:
                                continue
                            pdb_size = pdb_sc_sizes[pdb_idx]
                            if pdb_size > 30 and idb_size > 30:
                                ratio = float(idb_size) / pdb_size
                                if ratio < 0.15 or ratio > 7.0:
                                    continue
                            if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                                sc_applied += 1
                                applied += 1
                        log("    scriptcmd.cpp: +%d" % sc_applied)

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
