"""
IDAPython: PAL3.exe 高级启发式匹配 v3

综合所有可用信号:
  1. 源文件路径 → 函数分组 (已知28个文件, 67个函数)
  2. PDB source_file_index → 已知文件中有哪些函数
  3. 函数地址排序 + 分组匹配: 同一源文件的函数在 .text 中通常连续排列
  4. 导入函数调用链: D3D/Miles/DirectInput 的调用者
  5. 特征字符串: 文件扩展名、格式化字符串、已知常量

运行环境: PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_name
import ida_segment
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
LOG_FILE = os.path.join(LOG_DIR, "pal3_advanced_match_log.txt")
REPORT_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "advanced_match_report.json")

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


def get_callees(func_ea, text_bytes):
    """Get direct call targets from a function by scanning for E8 (call rel32)."""
    func = ida_funcs.get_func(func_ea)
    if not func:
        return set()
    callees = set()
    start_off = func.start_ea - TEXT_START
    end_off = func.end_ea - TEXT_START
    if start_off < 0 or end_off > len(text_bytes):
        return callees

    i = start_off
    while i < end_off - 4:
        if text_bytes[i] == 0xE8:  # CALL rel32
            rel = struct.unpack_from('<i', text_bytes, i + 1)[0]
            target = (TEXT_START + i + 5 + rel) & 0xFFFFFFFF
            if TEXT_START <= target < TEXT_END:
                callees.add(target)
            i += 5
        else:
            i += 1
    return callees


def get_imports():
    """Get all import thunks and their names."""
    imports = {}  # name → ea (thunk address in .text)
    # Scan IAT references - imports are typically jmp [IAT_entry]
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        name = ida_name.get_name(ea) or ""
        # Import thunks often have names like __imp_FunctionName or start with j_
        if name.startswith("_") and not name.startswith("sub_"):
            imports[name] = ea
        # Also check for short jmp thunks
        func = ida_funcs.get_func(ea)
        if func and func.end_ea - func.start_ea <= 6:
            # Very short function - likely a thunk
            if name and not name.startswith("sub_"):
                imports[name] = ea
    return imports


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 高级启发式匹配 v3")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        # Load PDB
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        pdb_functions = pdb_data.get('functions', [])
        log("[*] PDB 函数: %d" % len(pdb_functions))

        # Build indices
        pdb_by_name = {}  # full_name → {mangled, source_file, ...}
        pdb_by_file = {}  # basename → [func, ...]
        pdb_by_class = {}  # class → [func, ...]

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

        log("[*] PDB: %d names, %d files, %d classes" % (
            len(pdb_by_name), len(pdb_by_file), len(pdb_by_class)))

        # Read binary sections
        text_bytes = ida_bytes.get_bytes(TEXT_START, TEXT_END - TEXT_START)
        rdata_bytes = ida_bytes.get_bytes(RDATA_START, RDATA_END - RDATA_START)
        data_bytes = ida_bytes.get_bytes(DATA_START, DATA_END - DATA_START)

        if not text_bytes or not data_bytes:
            log("[!] Cannot read segments")
            return

        # ============================================================
        # Strategy 1: Source file path → function group → order matching
        # ============================================================
        log("")
        log("[Strategy 1] 源文件路径分组匹配")

        # Find all source path strings in .rdata and .data
        all_source_paths = {}  # va → basename
        for seg_bytes, seg_start in [(rdata_bytes, RDATA_START), (data_bytes, DATA_START)]:
            if not seg_bytes:
                continue
            # Search for .cpp and .h paths
            for pattern in [b':\\', b':/']:
                pos = 0
                while True:
                    pos = seg_bytes.find(pattern, pos)
                    if pos == -1:
                        break
                    # Walk back to find string start
                    start = pos
                    while start > 0 and seg_bytes[start-1] >= 0x20 and seg_bytes[start-1] < 0x7F:
                        start -= 1
                    # Walk forward to find string end
                    end = pos + 2
                    while end < len(seg_bytes) and seg_bytes[end] >= 0x20 and seg_bytes[end] < 0x7F:
                        end += 1
                    if end < len(seg_bytes) and seg_bytes[end] == 0:
                        text = seg_bytes[start:end].decode('ascii', errors='replace')
                        if '.cpp' in text.lower() or '.h' in text.lower():
                            va = seg_start + start
                            bn = os.path.basename(text).lower()
                            all_source_paths[va] = bn
                    pos = end + 1

        log("[*] 源文件路径字符串: %d" % len(all_source_paths))

        # Find which functions reference each source path
        source_func_groups = {}  # basename → sorted list of func_eas
        for str_va, basename in all_source_paths.items():
            needle = struct.pack('<I', str_va)
            pos = 0
            while True:
                pos = text_bytes.find(needle, pos)
                if pos == -1:
                    break
                code_ea = TEXT_START + pos
                func = ida_funcs.get_func(code_ea)
                if func:
                    if basename not in source_func_groups:
                        source_func_groups[basename] = set()
                    source_func_groups[basename].add(func.start_ea)
                pos += 1

        log("[*] 有函数引用的源文件: %d" % len(source_func_groups))

        # For each source file group, try to match against PDB
        strategy1_matches = []
        for basename, func_set in source_func_groups.items():
            pdb_funcs = pdb_by_file.get(basename, [])
            if not pdb_funcs:
                continue

            func_list = sorted(func_set)

            # Find ALL functions in the address range between first and last referencing func
            if len(func_list) >= 2:
                range_start = func_list[0]
                range_end = func_list[-1]
                # Get all functions in this range
                all_in_range = []
                for ea in idautils.Functions(range_start, range_end + 0x1000):
                    if ea > range_end + 0x2000:
                        break
                    all_in_range.append(ea)

                # If the number of functions in range roughly matches PDB count for this file
                pdb_count = len(pdb_funcs)
                range_count = len(all_in_range)

                if range_count > 0 and 0.5 <= float(pdb_count) / range_count <= 2.0:
                    log("    %s: %d funcs in range [0x%X-0x%X], PDB has %d" % (
                        basename, range_count, range_start, range_end, pdb_count))

                    # Sort PDB functions by their address in PAL3A (order should be preserved)
                    pdb_sorted = sorted(pdb_funcs, key=lambda f: f.get('address', 0))

                    # If count matches closely, try positional matching
                    if abs(range_count - pdb_count) <= 3:
                        # Match by position: i-th function in range = i-th PDB function
                        unnamed_in_range = [(i, ea) for i, ea in enumerate(all_in_range)
                                           if (ida_name.get_name(ea) or "").startswith("sub_")]
                        for idx, ea in unnamed_in_range:
                            if idx < len(pdb_sorted):
                                pdb_func = pdb_sorted[idx]
                                pdb_name = pdb_func.get('name', '')
                                mangled = pdb_func.get('mangled_name', '')
                                if mangled and pdb_name:
                                    strategy1_matches.append({
                                        'addr': '0x%08X' % ea,
                                        'name': pdb_name,
                                        'mangled': mangled,
                                        'confidence': 'medium',
                                        'evidence': 'positional in %s (pos %d/%d)' % (basename, idx, range_count),
                                    })

        log("[*] Strategy 1 候选: %d" % len(strategy1_matches))

        # ============================================================
        # Strategy 2: Known class → call graph expansion
        # ============================================================
        log("")
        log("[Strategy 2] 已知类调用图扩展")

        # Collect all currently named class functions
        known_class_funcs = {}  # class → [(ea, method), ...]
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name.startswith("sub_") or name.startswith("nullsub_"):
                continue
            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            if demangled and '::' in demangled:
                parts = demangled.split('(')[0]
                if '::' in parts:
                    cls = parts.split('::')[0].strip()
                    method = parts.split('::')[-1].strip()
                    if cls not in known_class_funcs:
                        known_class_funcs[cls] = []
                    known_class_funcs[cls].append((ea, method))

        log("[*] 已知类: %d, 方法: %d" % (
            len(known_class_funcs),
            sum(len(v) for v in known_class_funcs.values())))

        strategy2_matches = []
        for cls, methods in known_class_funcs.items():
            if cls not in pdb_by_class:
                continue
            pdb_methods = pdb_by_class[cls]
            known_method_names = set(m for _, m in methods)
            known_eas = set(ea for ea, _ in methods)

            # Get unmatched PDB methods for this class
            unmatched_pdb = [f for f in pdb_methods
                           if f['name'].split('::')[-1] not in known_method_names]
            if not unmatched_pdb:
                continue

            # For each known method, trace callees
            for ea, method_name in methods:
                callees = get_callees(ea, text_bytes)
                for callee in callees:
                    if callee in known_eas:
                        continue
                    callee_name = ida_name.get_name(callee) or ""
                    if not callee_name.startswith("sub_"):
                        continue

                    # This unnamed function is called by a known class method
                    # Check if it also calls other methods of the same class
                    callee_callees = get_callees(callee, text_bytes)
                    calls_same_class = sum(1 for c in callee_callees if c in known_eas)

                    if calls_same_class >= 1:
                        # Strong signal: called by class method AND calls class methods
                        # Can't determine exact method name yet, but annotate
                        existing_cmt = idc.get_func_cmt(callee, 0) or ""
                        if cls not in existing_cmt:
                            cmt = "strong_%s_candidate (called_by=%s, calls_back=%d)" % (
                                cls, method_name, calls_same_class)
                            idc.set_func_cmt(callee, cmt, 0)

            # Check if known methods form a contiguous block
            sorted_known = sorted(known_eas)
            if len(sorted_known) >= 2:
                # Functions between known class methods are likely same class
                for i in range(len(sorted_known) - 1):
                    start = sorted_known[i]
                    end = sorted_known[i + 1]
                    for ea in idautils.Functions(start, end):
                        if ea in known_eas:
                            continue
                        name = ida_name.get_name(ea) or ""
                        if name.startswith("sub_"):
                            existing_cmt = idc.get_func_cmt(ea, 0) or ""
                            if cls not in existing_cmt:
                                cmt = "between_%s_methods (0x%X-0x%X)" % (cls, start, end)
                                idc.set_func_cmt(ea, cmt, 0)

        log("[*] Strategy 2 注释完成")

        # ============================================================
        # Strategy 3: Import thunk callers → wrapper identification
        # ============================================================
        log("")
        log("[Strategy 3] 导入函数调用者识别")

        # Find import thunks
        import_thunks = {}  # ea → name
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            func = ida_funcs.get_func(ea)
            if not func:
                continue
            # Thunks are very short (jmp [IAT])
            if func.end_ea - func.start_ea <= 6 and not name.startswith("sub_"):
                import_thunks[ea] = name

        # Also scan for indirect calls through IAT
        # IAT is typically in .rdata
        iat_entries = {}  # va of IAT entry → import name
        for ea in range(RDATA_START, RDATA_END, 4):
            name = ida_name.get_name(ea) or ""
            if name.startswith("__imp_"):
                iat_entries[ea] = name[6:]  # strip __imp_ prefix

        log("[*] Import thunks: %d, IAT entries: %d" % (len(import_thunks), len(iat_entries)))

        # Map D3D/Miles/DInput imports to their callers
        d3d_callers = {}  # func_ea → set of D3D functions it calls
        for func_ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(func_ea) or ""
            if not name.startswith("sub_"):
                continue
            callees = get_callees(func_ea, text_bytes)
            for callee in callees:
                if callee in import_thunks:
                    imp_name = import_thunks[callee]
                    if any(prefix in imp_name for prefix in ['Direct3D', 'D3D', 'IDirect',
                                                             'AIL', 'Miles', 'DInput',
                                                             'Bink', 'CreateWindow', 'ShowWindow']):
                        if func_ea not in d3d_callers:
                            d3d_callers[func_ea] = set()
                        d3d_callers[func_ea].add(imp_name)

        log("[*] 调用 D3D/Audio/Input 的未命名函数: %d" % len(d3d_callers))

        # Annotate these functions
        for func_ea, imports_called in d3d_callers.items():
            imp_str = ', '.join(sorted(imports_called))[:60]
            existing_cmt = idc.get_func_cmt(func_ea, 0) or ""
            if 'imports:' not in existing_cmt:
                cmt = "imports: %s" % imp_str
                if existing_cmt:
                    cmt = existing_cmt + "; " + cmt
                idc.set_func_cmt(func_ea, cmt, 0)

        # ============================================================
        # Strategy 4: Unique error message strings (broader patterns)
        # ============================================================
        log("")
        log("[Strategy 4] 扩展字符串模式匹配")

        # Patterns that indicate function identity:
        # - "xxx.bik" → BinkVideo related
        # - "xxx.cpk" → CPK archive related
        # - "xxx.sce" → SCE script related
        # - "xxx.pol" / ".rol" / ".scn" → 3D/scene related
        # - "%s\\%s" with known prefix → file loading
        # - "ASSERT" / "assert" → has source info nearby
        # - Error messages unique to one function

        # Extract ALL strings and find references
        all_strings = {}  # va → text
        for seg_bytes, seg_start, seg_end in [
            (rdata_bytes, RDATA_START, RDATA_END),
            (data_bytes, DATA_START, DATA_END)
        ]:
            if not seg_bytes:
                continue
            i = 0
            while i < len(seg_bytes):
                if 0x20 <= seg_bytes[i] < 0x7F:
                    j = i
                    while j < len(seg_bytes) and (0x20 <= seg_bytes[j] < 0x7F or seg_bytes[j] in (0x0D, 0x0A, 0x09)):
                        j += 1
                    if j < len(seg_bytes) and seg_bytes[j] == 0 and j - i >= 4:
                        text = seg_bytes[i:j].decode('ascii', errors='replace')
                        va = seg_start + i
                        all_strings[va] = text
                    i = j + 1
                else:
                    i += 1

        log("[*] 全部字符串: %d" % len(all_strings))

        # Find unique identifying strings
        # Keywords that help identify function purpose
        identifying_patterns = [
            # File operations
            (r'\.(cpk|pak|bik|scn|pol|rol|sce|sav|ini|cfg|txt|dat)\b', 'file_op'),
            # Assert/error with function name
            (r'assert|ASSERT|Assert', 'assert'),
            # Memory allocation errors with context
            (r'(alloc|malloc|new)\s*(fail|error)', 'alloc_error'),
            # D3D operations
            (r'(Create|Get|Set|Release)(Device|Texture|Surface|Buffer|Shader|State)', 'd3d_op'),
            # Common game patterns
            (r'(Load|Save|Read|Write|Open|Close|Init|Destroy|Create|Update|Render)', 'game_op'),
        ]

        # Build function → string set mapping
        func_strings = {}  # func_ea → [str_text, ...]
        str_ref_count = {}  # str_va → number of functions referencing it

        for str_va, text in all_strings.items():
            needle = struct.pack('<I', str_va)
            pos = 0
            ref_funcs = set()
            while True:
                pos = text_bytes.find(needle, pos)
                if pos == -1:
                    break
                code_ea = TEXT_START + pos
                func = ida_funcs.get_func(code_ea)
                if func:
                    ref_funcs.add(func.start_ea)
                pos += 1

            str_ref_count[str_va] = len(ref_funcs)
            for func_ea in ref_funcs:
                if func_ea not in func_strings:
                    func_strings[func_ea] = []
                func_strings[func_ea].append(text)

        log("[*] 有字符串引用的函数: %d" % len(func_strings))

        # Functions with unique identifying strings
        unique_str_funcs = 0
        for func_ea, strings in func_strings.items():
            name = ida_name.get_name(func_ea) or ""
            if not name.startswith("sub_"):
                continue
            # Find strings unique to this function (referenced only here)
            unique_strs = [s for s in strings
                          if any(re.search(p, s, re.IGNORECASE) for p, _ in identifying_patterns)]
            if unique_strs:
                existing_cmt = idc.get_func_cmt(func_ea, 0) or ""
                unique_str = unique_strs[0][:60]
                if unique_str not in (existing_cmt or ""):
                    cmt = "strings: %s" % '; '.join(unique_strs[:3])[:80]
                    if existing_cmt and len(existing_cmt) < 100:
                        cmt = existing_cmt + " | " + cmt
                    elif not existing_cmt:
                        idc.set_func_cmt(func_ea, cmt, 0)
                unique_str_funcs += 1

        log("[*] 有特征字符串的未命名函数: %d" % unique_str_funcs)

        # ============================================================
        # Strategy 5: Function size + location clustering
        # ============================================================
        log("")
        log("[Strategy 5] 函数大小与地址聚类")

        # Build a map of function sizes in PAL3 and PDB
        pal3_funcs = []  # (ea, size, name)
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            func = ida_funcs.get_func(ea)
            if func:
                size = func.end_ea - func.start_ea
                name = ida_name.get_name(ea) or ""
                pal3_funcs.append((ea, size, name))

        log("[*] PAL3 函数: %d (命名: %d, 未命名: %d)" % (
            len(pal3_funcs),
            sum(1 for _, _, n in pal3_funcs if not n.startswith("sub_")),
            sum(1 for _, _, n in pal3_funcs if n.startswith("sub_"))))

        # Apply Strategy 1 matches (medium confidence, from positional)
        # Only apply if they don't conflict with existing names
        applied_s1 = 0
        for match in strategy1_matches:
            func_ea = int(match['addr'], 16)
            existing = ida_name.get_name(func_ea) or ""
            if existing.startswith("sub_"):
                mangled = match['mangled']
                if ida_name.set_name(func_ea, mangled, ida_name.SN_NOWARN):
                    applied_s1 += 1
                    log("    S1: 0x%s = %s" % (match['addr'], match['name']))

        log("[*] Strategy 1 应用: %d" % applied_s1)

        # ============================================================
        # Strategy 6: WinMain → PAL3::main call chain
        # ============================================================
        log("")
        log("[Strategy 6] 入口点调用链")

        # Find WinMain or _WinMain@16
        winmain_ea = None
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if 'WinMain' in name or 'wWinMain' in name:
                winmain_ea = ea
                break
            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            if demangled and 'WinMain' in demangled:
                winmain_ea = ea
                break

        if winmain_ea:
            log("[*] WinMain: 0x%08X" % winmain_ea)
            # Trace first few levels of call chain
            level0_callees = get_callees(winmain_ea, text_bytes)
            log("    Level 0 callees: %d" % len(level0_callees))
            for callee in sorted(level0_callees):
                name = ida_name.get_name(callee) or "sub_%X" % callee
                log("      0x%08X: %s" % (callee, name[:50]))
        else:
            # Try to find entry point
            entry = idc.get_inf_attr(idc.INF_START_EA)
            log("[*] Entry point: 0x%08X" % entry)
            entry_callees = get_callees(entry, text_bytes)
            log("    Entry callees: %d" % len(entry_callees))
            for callee in sorted(entry_callees)[:10]:
                name = ida_name.get_name(callee) or "sub_%X" % callee
                log("      0x%08X: %s" % (callee, name[:50]))

        # ============================================================
        # Summary
        # ============================================================
        log("")
        log("[*] === 总结 ===")

        # Recount
        named_count = 0
        unnamed_count = 0
        annotated_count = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name.startswith("sub_"):
                unnamed_count += 1
                cmt = idc.get_func_cmt(ea, 0) or ""
                if cmt:
                    annotated_count += 1
            else:
                named_count += 1

        log("[*] 命名: %d, 未命名: %d (其中已注释: %d), 总计: %d" % (
            named_count, unnamed_count, annotated_count, named_count + unnamed_count))
        log("[*] Strategy 1 (位置匹配): %d applied" % applied_s1)
        log("[*] Strategy 2 (调用图): annotations applied")
        log("[*] Strategy 3 (导入追踪): %d functions annotated" % len(d3d_callers))
        log("[*] Strategy 4 (字符串): %d functions with identifying strings" % unique_str_funcs)

        # Save database
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

        # Write report
        report = {
            'meta': {'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S")},
            'stats': {
                'named': named_count,
                'unnamed': unnamed_count,
                'annotated': annotated_count,
                'total': named_count + unnamed_count,
                'strategy1_applied': applied_s1,
                'strategy3_annotated': len(d3d_callers),
                'strategy4_identified': unique_str_funcs,
            },
            'source_file_groups': {
                bn: ['0x%08X' % ea for ea in sorted(funcs)]
                for bn, funcs in source_func_groups.items()
            },
            'strategy1_matches': strategy1_matches[:50],
            'd3d_callers': {
                '0x%08X' % ea: sorted(imports)
                for ea, imports in list(d3d_callers.items())[:50]
            },
        }
        os.makedirs(os.path.dirname(REPORT_FILE), exist_ok=True)
        with open(REPORT_FILE, 'w', encoding='utf-8') as f:
            json.dump(report, f, indent=2, ensure_ascii=False)
        log("[*] 报告: %s" % REPORT_FILE)

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
