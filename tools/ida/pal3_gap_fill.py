"""
IDAPython: PAL3.exe 地址间隔填充

利用已命名函数划定的文件边界，在间隔中匹配更多函数。

策略:
  1. 收集所有已命名函数的源文件信息
  2. 构建地址→源文件的分区图
  3. 对于每个已知分区内的未命名函数，尝试从PDB中按顺序匹配
  4. 利用函数间的调用关系验证匹配

核心假设: MSVC 链接器按 .cpp 文件顺序放置函数，同一文件的函数地址连续

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
LOG_FILE = os.path.join(LOG_DIR, "pal3_gap_fill_log.txt")

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
        log("[*] PAL3.exe 地址间隔填充")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        pdb_functions = pdb_data.get('functions', [])
        pdb_by_file = {}
        pdb_by_name = {}
        pdb_by_class = {}
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
            if '::' in name:
                cls = name.split('::')[0]
                if cls not in pdb_by_class:
                    pdb_by_class[cls] = []
                pdb_by_class[cls].append(func)

        # ============================================================
        # Phase 1: Build file → address range map from named functions
        # ============================================================
        log("[Phase 1] 构建地址分区图")

        # Collect all named functions with their PDB file info
        named_funcs_with_file = []  # (ea, pdb_name, filename)

        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name.startswith("sub_") or name.startswith("nullsub_"):
                continue

            # Try to find this function in PDB
            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            if demangled:
                # Strip params
                base = demangled.split('(')[0].strip()
                # Look up in PDB
                pdb_func = pdb_by_name.get(base)
                if pdb_func:
                    src = pdb_func.get('source_file', '')
                    if src:
                        bn = os.path.basename(src).lower()
                        named_funcs_with_file.append((ea, base, bn))

        log("[*] 有源文件信息的命名函数: %d" % len(named_funcs_with_file))

        # Sort by address
        named_funcs_with_file.sort(key=lambda x: x[0])

        # Build file regions: consecutive functions from same file
        file_regions = []  # (start_ea, end_ea, filename, func_count)
        if named_funcs_with_file:
            current_file = named_funcs_with_file[0][2]
            region_start = named_funcs_with_file[0][0]
            region_funcs = [named_funcs_with_file[0]]

            for i in range(1, len(named_funcs_with_file)):
                ea, name, filename = named_funcs_with_file[i]
                prev_ea = named_funcs_with_file[i-1][0]

                # Same file and not too far apart (< 64KB gap)
                if filename == current_file and ea - prev_ea < 0x10000:
                    region_funcs.append(named_funcs_with_file[i])
                else:
                    # Close current region
                    region_end = region_funcs[-1][0] + get_func_size(region_funcs[-1][0])
                    if len(region_funcs) >= 2:
                        file_regions.append((region_start, region_end, current_file, len(region_funcs)))
                    # Start new region
                    current_file = filename
                    region_start = ea
                    region_funcs = [named_funcs_with_file[i]]

            # Close last region
            region_end = region_funcs[-1][0] + get_func_size(region_funcs[-1][0])
            if len(region_funcs) >= 2:
                file_regions.append((region_start, region_end, current_file, len(region_funcs)))

        log("[*] 文件区域: %d" % len(file_regions))
        for start, end, filename, count in file_regions[:20]:
            log("    0x%08X-0x%08X: %s (%d named funcs)" % (start, end, filename, count))

        # ============================================================
        # Phase 2: For each region, find unnamed functions and match
        # ============================================================
        log("")
        log("[Phase 2] 区域内未命名函数匹配")

        applied = 0

        for region_start, region_end, filename, named_count in file_regions:
            pdb_funcs = pdb_by_file.get(filename, [])
            if not pdb_funcs:
                continue

            # Get ALL functions in this region
            idb_funcs = []
            for ea in idautils.Functions(region_start, region_end):
                size = get_func_size(ea)
                name = ida_name.get_name(ea) or ""
                idb_funcs.append((ea, size, name))

            if not idb_funcs:
                continue

            # Count unnamed
            unnamed_count = sum(1 for _, _, n in idb_funcs if n.startswith("sub_"))
            if unnamed_count == 0:
                continue

            # Sort PDB functions by address
            pdb_sorted = sorted(pdb_funcs,
                               key=lambda f: int(f['address'], 16)
                               if isinstance(f.get('address'), str)
                               else f.get('address', 0))

            # Find the best alignment using already-named functions
            # Build a map of named IDB functions to their PDB indices
            named_alignments = []  # (idb_idx, pdb_idx)
            for idb_idx, (ea, _, idb_name) in enumerate(idb_funcs):
                if idb_name.startswith("sub_"):
                    continue
                demangled = idc.demangle_name(idb_name, idc.get_inf_attr(idc.INF_SHORT_DN))
                if not demangled:
                    continue
                base_name = demangled.split('(')[0].strip()
                for pdb_idx, pdb_func in enumerate(pdb_sorted):
                    if pdb_func['name'] == base_name:
                        named_alignments.append((idb_idx, pdb_idx))
                        break

            if not named_alignments:
                continue

            # Calculate offsets from each alignment point
            offsets = [idb_idx - pdb_idx for idb_idx, pdb_idx in named_alignments]

            # Use most common offset (mode)
            offset_counts = {}
            for off in offsets:
                offset_counts[off] = offset_counts.get(off, 0) + 1
            best_offset = max(offset_counts, key=offset_counts.get)
            offset_agreement = offset_counts[best_offset]

            # Only proceed if we have good agreement
            if offset_agreement < 2 and named_count > 3:
                continue  # Offsets disagree too much

            # Apply matches
            region_applied = 0
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

                # Size check
                if pdb_idx + 1 < len(pdb_sorted):
                    pdb_addr = pdb_sorted[pdb_idx].get('address', '0')
                    next_addr = pdb_sorted[pdb_idx + 1].get('address', '0')
                    if isinstance(pdb_addr, str):
                        pdb_addr = int(pdb_addr, 16)
                    if isinstance(next_addr, str):
                        next_addr = int(next_addr, 16)
                    pdb_size = next_addr - pdb_addr
                else:
                    pdb_size = 200

                if pdb_size > 30 and idb_size > 30:
                    ratio = float(idb_size) / pdb_size
                    if ratio < 0.15 or ratio > 7.0:
                        continue

                if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                    applied += 1
                    region_applied += 1

            if region_applied > 0:
                log("    %s: +%d (offset=%d, agreement=%d/%d)" % (
                    filename, region_applied, best_offset,
                    offset_agreement, len(named_alignments)))

        log("[*] Phase 2 总计: %d" % applied)

        # ============================================================
        # Phase 3: Use known class boundaries to infer file boundaries
        # ============================================================
        log("")
        log("[Phase 3] 类→文件边界推断")

        # Many files contain a single class. If we know where the class starts
        # (from named functions), we can infer the file boundary.
        # Then match functions in that inferred range.

        # Group named functions by class
        class_ranges = {}  # class → (min_ea, max_ea, method_count)
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name.startswith("sub_"):
                continue
            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            if demangled and '::' in demangled:
                cls = demangled.split('::')[0].split('(')[0].strip()
                if cls not in class_ranges:
                    class_ranges[cls] = [ea, ea, 0]
                class_ranges[cls][0] = min(class_ranges[cls][0], ea)
                class_ranges[cls][1] = max(class_ranges[cls][1], ea)
                class_ranges[cls][2] += 1

        # Find classes with good address clustering (methods close together)
        well_clustered = []
        for cls, (min_ea, max_ea, count) in class_ranges.items():
            if count >= 3:
                span = max_ea - min_ea
                if span < 0x20000:  # Less than 128KB span
                    well_clustered.append((cls, min_ea, max_ea, count, span))

        well_clustered.sort(key=lambda x: -x[3])
        log("[*] Well-clustered classes: %d" % len(well_clustered))
        for cls, min_ea, max_ea, count, span in well_clustered[:15]:
            log("    %s: 0x%X-0x%X (%d methods, span=%d)" % (cls, min_ea, max_ea, count, span))

        # For each well-clustered class, find its PDB source file
        # and try to match remaining unnamed functions in the range
        phase3_applied = 0
        for cls, min_ea, max_ea, count, span in well_clustered:
            if cls not in pdb_by_class:
                continue

            # Get source file for this class from PDB
            cls_funcs = pdb_by_class[cls]
            src_files = set()
            for f in cls_funcs:
                src = f.get('source_file', '')
                if src:
                    src_files.add(os.path.basename(src).lower())

            if len(src_files) != 1:
                continue  # Ambiguous or no source

            src_file = list(src_files)[0]
            pdb_funcs = pdb_by_file.get(src_file, [])
            if not pdb_funcs:
                continue

            # Extended range around the class
            ext_start = min_ea - 0x500
            ext_end = max_ea + 0x2000

            # Get IDB functions
            idb_funcs = []
            for ea in idautils.Functions(max(TEXT_START, ext_start), min(TEXT_END, ext_end)):
                size = get_func_size(ea)
                name = ida_name.get_name(ea) or ""
                idb_funcs.append((ea, size, name))

            # Sort PDB
            pdb_sorted = sorted(pdb_funcs,
                               key=lambda f: int(f['address'], 16)
                               if isinstance(f.get('address'), str)
                               else f.get('address', 0))

            # Find alignment using named class methods
            named_alignments = []
            for idb_idx, (ea, _, idb_name) in enumerate(idb_funcs):
                if idb_name.startswith("sub_"):
                    continue
                demangled = idc.demangle_name(idb_name, idc.get_inf_attr(idc.INF_SHORT_DN))
                if not demangled:
                    continue
                base_name = demangled.split('(')[0].strip()
                for pdb_idx, pdb_func in enumerate(pdb_sorted):
                    if pdb_func['name'] == base_name:
                        named_alignments.append((idb_idx, pdb_idx))
                        break

            if len(named_alignments) < 2:
                continue

            offsets = [idb_idx - pdb_idx for idb_idx, pdb_idx in named_alignments]
            offset_counts = {}
            for off in offsets:
                offset_counts[off] = offset_counts.get(off, 0) + 1
            best_offset = max(offset_counts, key=offset_counts.get)
            agreement = offset_counts[best_offset]

            if agreement < 2:
                continue

            # Apply
            cls_applied = 0
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

                # Size check
                if pdb_idx + 1 < len(pdb_sorted):
                    pdb_addr = int(pdb_sorted[pdb_idx].get('address', '0'), 16) if isinstance(pdb_sorted[pdb_idx].get('address'), str) else pdb_sorted[pdb_idx].get('address', 0)
                    next_addr = int(pdb_sorted[pdb_idx + 1].get('address', '0'), 16) if isinstance(pdb_sorted[pdb_idx + 1].get('address'), str) else pdb_sorted[pdb_idx + 1].get('address', 0)
                    pdb_size = next_addr - pdb_addr
                else:
                    pdb_size = 200

                if pdb_size > 30 and idb_size > 30:
                    ratio = float(idb_size) / pdb_size
                    if ratio < 0.15 or ratio > 7.0:
                        continue

                if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                    phase3_applied += 1
                    cls_applied += 1

            if cls_applied > 0:
                log("    %s (%s): +%d (offset=%d, agreement=%d)" % (
                    cls, src_file, cls_applied, best_offset, agreement))

        applied += phase3_applied
        log("[*] Phase 3 总计: %d" % phase3_applied)

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
