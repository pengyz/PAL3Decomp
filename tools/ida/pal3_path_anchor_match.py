"""
IDAPython: PAL3.exe 路径锚点 + 大规模顺序匹配

已知: 源文件路径存储为 "D:\PAL3\...\CBSystem.cpp" 格式
PAL3.exe 中路径可能略有不同但包含文件名

本脚本:
  1. 在 .data/.rdata 中搜索所有包含 .cpp 的路径字符串
  2. 找到引用这些路径的函数作为锚点
  3. 用PDB的source_file_index确定函数顺序
  4. 从锚点开始进行大范围顺序匹配

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
LOG_FILE = os.path.join(LOG_DIR, "pal3_path_anchor_match_log.txt")

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


def find_all_string_refs(text_bytes, str_va):
    """Find ALL code references to a given VA."""
    needle = struct.pack('<I', str_va)
    refs = []
    pos = 0
    while True:
        pos = text_bytes.find(needle, pos)
        if pos == -1:
            break
        code_ea = TEXT_START + pos
        func = ida_funcs.get_func(code_ea)
        if func:
            refs.append(func.start_ea)
        pos += 1
    return list(set(refs))


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 路径锚点匹配")
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

        # ============================================================
        # Phase 1: Extract ALL path strings from binary
        # ============================================================
        log("[Phase 1] 提取所有路径字符串")

        path_strings = {}  # va → (basename, full_path)
        for seg_bytes, seg_start in [(data_bytes, DATA_START), (rdata_bytes, RDATA_START)]:
            if not seg_bytes:
                continue
            # Search for ":\\" which indicates a path
            pos = 0
            while True:
                pos = seg_bytes.find(b':\\', pos)
                if pos == -1:
                    break
                # Walk back to find start of string
                start = pos - 1
                while start > 0 and seg_bytes[start] >= 0x20 and seg_bytes[start] < 0x7F:
                    start -= 1
                start += 1
                # Walk forward to find end
                end = pos + 2
                while end < len(seg_bytes) and seg_bytes[end] >= 0x20 and seg_bytes[end] < 0x7F:
                    end += 1
                if end < len(seg_bytes) and seg_bytes[end] == 0 and end - start >= 8:
                    text = seg_bytes[start:end].decode('ascii', errors='replace')
                    if '.cpp' in text.lower() or '.h' in text.lower() or '.c' in text.lower():
                        va = seg_start + start
                        bn = os.path.basename(text).lower()
                        path_strings[va] = (bn, text)
                pos = end + 1

        log("[*] 路径字符串: %d" % len(path_strings))
        for va, (bn, path) in sorted(path_strings.items())[:30]:
            log("    0x%08X: %s → %s" % (va, bn, path[:60]))

        # ============================================================
        # Phase 2: Map paths to referencing functions
        # ============================================================
        log("")
        log("[Phase 2] 路径→函数引用映射")

        # Group by basename
        file_anchors = {}  # basename → [(func_ea, full_path), ...]
        for str_va, (bn, full_path) in path_strings.items():
            refs = find_all_string_refs(text_bytes, str_va)
            for func_ea in refs:
                if bn not in file_anchors:
                    file_anchors[bn] = []
                file_anchors[bn].append((func_ea, full_path))

        log("[*] 有函数引用的文件: %d" % len(file_anchors))
        for bn in sorted(file_anchors.keys()):
            funcs = file_anchors[bn]
            func_addrs = sorted(set(ea for ea, _ in funcs))
            log("    %s: %d refs → %s" % (bn, len(func_addrs),
                ['0x%X' % ea for ea in func_addrs[:5]]))

        # ============================================================
        # Phase 3: For each file with anchors, try order matching
        # ============================================================
        log("")
        log("[Phase 3] 大规模顺序匹配")

        applied = 0
        all_matches = []
        files_matched = 0

        # Process files that have clear anchors
        for basename, anchor_list in sorted(file_anchors.items()):
            pdb_funcs = pdb_by_file.get(basename, [])
            if not pdb_funcs:
                # Try without extension
                name_no_ext = os.path.splitext(basename)[0]
                # Try .cpp if we found .h
                if basename.endswith('.h'):
                    pdb_funcs = pdb_by_file.get(name_no_ext + '.cpp', [])
                if not pdb_funcs:
                    continue

            # Get unique anchor addresses, sorted
            anchor_eas = sorted(set(ea for ea, _ in anchor_list))

            # Sort PDB functions by address
            pdb_sorted = []
            for f in pdb_funcs:
                addr = f.get('address', '0')
                if isinstance(addr, str):
                    addr = int(addr, 16)
                pdb_sorted.append((addr, f))
            pdb_sorted.sort(key=lambda x: x[0])

            if len(pdb_sorted) < 3:
                continue  # Too few to meaningfully match

            # Determine the code range for this file
            # Use anchor addresses to estimate range
            min_anchor = min(anchor_eas)
            max_anchor = max(anchor_eas)

            # Extend range to cover likely full file
            # Heuristic: file boundaries are ~20% wider than anchor span
            span = max_anchor - min_anchor if max_anchor > min_anchor else 0x2000
            range_start = min_anchor - max(span // 4, 0x200)
            range_end = max_anchor + max(span // 4, 0x2000)

            # Clamp to .text
            range_start = max(range_start, TEXT_START)
            range_end = min(range_end, TEXT_END)

            # Get IDB functions in range
            idb_funcs = []
            for ea in idautils.Functions(range_start, range_end):
                size = get_func_size(ea)
                name = ida_name.get_name(ea) or ""
                idb_funcs.append((ea, size, name))

            if not idb_funcs:
                continue

            # Find anchor position in IDB list
            # Use the first anchor that falls in a known position
            best_anchor_ea = anchor_eas[0]
            anchor_idb_idx = -1
            for i, (ea, _, _) in enumerate(idb_funcs):
                if ea == best_anchor_ea:
                    anchor_idb_idx = i
                    break

            if anchor_idb_idx < 0:
                continue

            # Now, which PDB function is this anchor?
            # Functions with asserts/errors typically reference their own file path
            # The first or one of the first few large functions usually has asserts
            # We can try multiple possible PDB positions and see which gives best results

            # Strategy: try each PDB function as the anchor, pick the alignment
            # that matches the most named functions already in IDB
            best_offset = None
            best_score = 0

            for try_pdb_idx in range(len(pdb_sorted)):
                offset = anchor_idb_idx - try_pdb_idx
                score = 0
                for pi, (_, pf) in enumerate(pdb_sorted):
                    ii = pi + offset
                    if 0 <= ii < len(idb_funcs):
                        ea, _, existing = idb_funcs[ii]
                        if not existing.startswith("sub_") and not existing.startswith("maybe_"):
                            # Check if existing name matches PDB name
                            pdb_name = pf['name']
                            demangled = idc.demangle_name(existing, idc.get_inf_attr(idc.INF_SHORT_DN))
                            if demangled and pdb_name in demangled:
                                score += 10
                            elif pdb_name.split('::')[-1] in (demangled or existing):
                                score += 5
                if score > best_score:
                    best_score = score
                    best_offset = offset

            # If no named functions to validate against, try size-based alignment
            if best_offset is None or best_score == 0:
                # Default: assume anchor is one of the larger PDB functions
                # Use first function with >200 byte PDB size that has a reasonable match
                anchor_idb_size = idb_funcs[anchor_idb_idx][1] if anchor_idb_idx < len(idb_funcs) else 0
                for try_pdb_idx in range(len(pdb_sorted)):
                    pdb_addr = pdb_sorted[try_pdb_idx][0]
                    if try_pdb_idx + 1 < len(pdb_sorted):
                        pdb_size = pdb_sorted[try_pdb_idx + 1][0] - pdb_addr
                    else:
                        pdb_size = 200
                    if pdb_size > 100 and anchor_idb_size > 50:
                        ratio = float(anchor_idb_size) / pdb_size
                        if 0.3 <= ratio <= 3.0:
                            best_offset = anchor_idb_idx - try_pdb_idx
                            break

            if best_offset is None:
                continue

            # Apply matches using best offset
            file_applied = 0
            for pdb_idx, (pdb_addr, pdb_func) in enumerate(pdb_sorted):
                idb_idx = pdb_idx + best_offset
                if idb_idx < 0 or idb_idx >= len(idb_funcs):
                    continue

                ea, idb_size, existing = idb_funcs[idb_idx]
                if not existing.startswith("sub_") and not existing.startswith("maybe_"):
                    continue

                pdb_name = pdb_func['name']
                mangled = pdb_func.get('mangled_name', '')
                if not mangled:
                    continue

                # Calculate PDB size
                if pdb_idx + 1 < len(pdb_sorted):
                    pdb_size = pdb_sorted[pdb_idx + 1][0] - pdb_addr
                else:
                    pdb_size = 200

                # Size sanity check (relaxed for validated alignments)
                if best_score > 0:
                    # Validated by existing matches - use relaxed ratio
                    if pdb_size > 30 and idb_size > 30:
                        ratio = float(idb_size) / pdb_size
                        if ratio < 0.15 or ratio > 6.0:
                            continue
                else:
                    # Unvalidated - strict ratio
                    if pdb_size > 30 and idb_size > 30:
                        ratio = float(idb_size) / pdb_size
                        if ratio < 0.3 or ratio > 3.5:
                            continue

                if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                    applied += 1
                    file_applied += 1
                    all_matches.append({
                        'addr': '0x%08X' % ea,
                        'name': pdb_name,
                        'file': basename,
                    })

            if file_applied > 0:
                files_matched += 1
                log("    %s: %d matched (offset=%d, score=%d, PDB=%d, IDB=%d)" % (
                    basename, file_applied, best_offset, best_score,
                    len(pdb_sorted), len(idb_funcs)))

        log("[*] Phase 3 总计: %d matches from %d files" % (applied, files_matched))

        # ============================================================
        # Phase 4: Expand using newly named functions as new anchors
        # ============================================================
        log("")
        log("[Phase 4] 二次扩展")

        # After Phase 3, we have more named functions
        # Use them to validate/extend matches in nearby regions

        # Find files where we matched functions but might have missed some
        # due to alignment issues
        # Collect newly named class functions
        new_class_funcs = {}  # class → [(ea, method), ...]
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name.startswith("sub_"):
                continue
            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            if demangled and '::' in demangled:
                parts = demangled.split('(')[0]
                if '::' in parts:
                    cls = parts.split('::')[0].strip()
                    method = parts.split('::')[-1].strip()
                    if cls not in new_class_funcs:
                        new_class_funcs[cls] = []
                    new_class_funcs[cls].append((ea, method))

        log("[*] 当前已知类: %d, 方法: %d" % (
            len(new_class_funcs),
            sum(len(v) for v in new_class_funcs.values())))

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
        log("[*] 匹配文件: %d" % files_matched)

        if all_matches:
            # Group by file
            by_file = {}
            for m in all_matches:
                fn = m.get('file', '?')
                if fn not in by_file:
                    by_file[fn] = []
                by_file[fn].append(m)
            for fn, matches in sorted(by_file.items()):
                log("  %s: %d matches" % (fn, len(matches)))
                for m in matches[:5]:
                    log("    %s = %s" % (m['addr'], m['name']))
                if len(matches) > 5:
                    log("    ... and %d more" % (len(matches) - 5))

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
