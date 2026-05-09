"""
IDAPython: PAL3.exe 最终清理遍 — 多锚点对齐

利用已有的 1460 个命名函数进行全局对齐验证和间隙填充。
核心方法: 对于每个 PDB 源文件，找到所有已在 IDB 中命名的锚点，
计算一致偏移量，用该偏移填充剩余未命名函数。

只在偏移一致性 >= 60% 时应用匹配（高置信度）。

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
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_final_pass_log.txt")

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
        log("[*] PAL3.exe 最终清理遍")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        pdb_functions = pdb_data.get('functions', [])
        pdb_by_file = {}
        for func in pdb_functions:
            src = func.get('source_file', '')
            if src:
                bn = os.path.basename(src).lower()
                if bn not in pdb_by_file:
                    pdb_by_file[bn] = []
                pdb_by_file[bn].append(func)

        # ============================================================
        # Phase 1: Build comprehensive IDB→PDB mapping
        # ============================================================
        log("[Phase 1] 构建全局 IDB→PDB 映射")

        # For every named function in IDB, find its PDB entry and source file
        idb_to_pdb = {}  # ea → (pdb_func, source_file_basename)

        # First build a fast PDB name lookup
        pdb_name_lookup = {}  # demangled_base_name → pdb_func
        for func in pdb_functions:
            name = func.get('name', '')
            if name:
                pdb_name_lookup[name] = func

        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name.startswith("sub_") or name.startswith("nullsub_"):
                continue

            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            if not demangled:
                continue

            base_name = demangled.split('(')[0].strip()
            pdb_func = pdb_name_lookup.get(base_name)
            if pdb_func:
                src = pdb_func.get('source_file', '')
                if src:
                    bn = os.path.basename(src).lower()
                    idb_to_pdb[ea] = (pdb_func, bn)

        log("[*] IDB→PDB 映射: %d 函数" % len(idb_to_pdb))

        # ============================================================
        # Phase 2: For each source file, compute multi-anchor alignment
        # ============================================================
        log("")
        log("[Phase 2] 多锚点全局对齐")

        applied = 0
        files_processed = 0

        # Group IDB functions by their PDB source file
        file_idb_anchors = {}  # basename → [(ea, pdb_func), ...]
        for ea, (pdb_func, bn) in idb_to_pdb.items():
            if bn not in file_idb_anchors:
                file_idb_anchors[bn] = []
            file_idb_anchors[bn].append((ea, pdb_func))

        log("[*] 有锚点的源文件: %d" % len(file_idb_anchors))

        for basename, anchors in sorted(file_idb_anchors.items()):
            if len(anchors) < 2:
                continue  # Need at least 2 anchors for validation

            pdb_funcs = pdb_by_file.get(basename, [])
            if not pdb_funcs:
                continue

            # Sort PDB functions by address
            pdb_sorted = sorted(pdb_funcs,
                               key=lambda f: int(f['address'], 16)
                               if isinstance(f.get('address'), str)
                               else f.get('address', 0))

            # Build PDB index: name → position in sorted list
            pdb_name_to_idx = {}
            for idx, f in enumerate(pdb_sorted):
                pdb_name_to_idx[f['name']] = idx

            # Get the address range in IDB that contains these anchors
            anchor_eas = sorted([ea for ea, _ in anchors])
            range_start = anchor_eas[0] - 0x1000
            range_end = anchor_eas[-1] + 0x2000
            range_start = max(range_start, TEXT_START)
            range_end = min(range_end, TEXT_END)

            # Get all IDB functions in this range
            idb_funcs = []
            for ea in idautils.Functions(range_start, range_end):
                size = get_func_size(ea)
                name = ida_name.get_name(ea) or ""
                idb_funcs.append((ea, size, name))

            if not idb_funcs:
                continue

            # Build IDB index: ea → position
            idb_ea_to_idx = {ea: idx for idx, (ea, _, _) in enumerate(idb_funcs)}

            # Calculate offset for each anchor
            offsets = []
            for ea, pdb_func in anchors:
                pdb_idx = pdb_name_to_idx.get(pdb_func['name'], -1)
                idb_idx = idb_ea_to_idx.get(ea, -1)
                if pdb_idx >= 0 and idb_idx >= 0:
                    offsets.append(idb_idx - pdb_idx)

            if not offsets:
                continue

            # Find most common offset
            offset_counts = {}
            for off in offsets:
                offset_counts[off] = offset_counts.get(off, 0) + 1
            best_offset = max(offset_counts, key=offset_counts.get)
            agreement = offset_counts[best_offset]
            total_anchors = len(offsets)

            # Require >= 60% agreement among anchors
            agreement_ratio = float(agreement) / total_anchors
            if agreement_ratio < 0.6:
                continue

            # High confidence: apply matches for this file
            file_applied = 0
            # Calculate PDB sizes
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
                    addr = pdb_sorted[pdb_idx].get('address', '0')
                    next_addr = pdb_sorted[pdb_idx + 1].get('address', '0')
                    if isinstance(addr, str):
                        addr = int(addr, 16)
                    if isinstance(next_addr, str):
                        next_addr = int(next_addr, 16)
                    pdb_size = next_addr - addr
                else:
                    pdb_size = 200

                if pdb_size > 30 and idb_size > 30:
                    ratio = float(idb_size) / pdb_size
                    if ratio < 0.15 or ratio > 7.0:
                        continue

                if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                    applied += 1
                    file_applied += 1

            if file_applied > 0:
                files_processed += 1
                log("    %s: +%d (anchors=%d, agreement=%d/%d=%.0f%%, offset=%d)" % (
                    basename, file_applied, total_anchors,
                    agreement, total_anchors, agreement_ratio * 100, best_offset))

        log("")
        log("[*] Phase 2 总计: %d from %d files" % (applied, files_processed))

        # ============================================================
        # Summary
        # ============================================================
        log("")
        log("[*] === 最终统计 ===")
        named = sum(1 for ea in idautils.Functions(TEXT_START, TEXT_END)
                   if not (ida_name.get_name(ea) or "").startswith("sub_"))
        total = sum(1 for _ in idautils.Functions(TEXT_START, TEXT_END))
        log("[*] 命名: %d / %d (%.1f%%)" % (named, total, 100.0*named/total))
        log("[*] 本次新增: %d" % applied)

        # Breakdown by category
        game_named = 0
        game_total = 0
        crt_named = 0
        crt_total = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if ea < 0x540000:
                game_total += 1
                if not name.startswith("sub_"):
                    game_named += 1
            else:
                crt_total += 1
                if not name.startswith("sub_"):
                    crt_named += 1

        log("[*] Game code: %d / %d (%.1f%%)" % (game_named, game_total, 100.0*game_named/game_total))
        log("[*] CRT code: %d / %d (%.1f%%)" % (crt_named, crt_total, 100.0*crt_named/crt_total))

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
