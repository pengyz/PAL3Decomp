"""
IDAPython: PAL3.exe 启发式函数匹配 (第二轮)

利用 .data 段中的丰富信息:
  1. 源代码路径字符串 (D:\Project\PAL3\...) → 确定函数所属源文件
  2. RTTI 类名 (在 .data 段) → 确定类的虚表和方法
  3. 游戏特征字符串 → 匹配具体函数
  4. PDB source_file_index → 知道每个函数属于哪个 .cpp

运行环境: PAL3.exe.i64
用法:
  idat.exe -A -S"pal3_heuristic_match.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_name
import ida_xref
import idautils
import idc
import json
import os
import re
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
OUTPUT_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "heuristic_match_report.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_heuristic_match_log.txt")

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


# ============================================================
# Phase 1: Extract all strings from .data and .rdata
# ============================================================
def phase1_strings():
    """Extract all meaningful strings and map them to referencing functions."""
    log("")
    log("=" * 60)
    log("[Phase 1] 字符串提取与函数映射")
    log("=" * 60)

    # Scan .data for strings (where most game strings live)
    all_strings = {}  # addr → string_text
    for seg_start, seg_end in [(RDATA_START, RDATA_END), (DATA_START, DATA_END)]:
        ea = seg_start
        while ea < seg_end:
            # Try to get string at this address
            s = idc.get_strlit_contents(ea, -1, idc.STRTYPE_C)
            if s and len(s) >= 3:
                try:
                    text = s.decode('utf-8', errors='replace')
                    all_strings[ea] = text
                    ea += len(s) + 1
                    continue
                except:
                    pass
            ea += 1

    log("[*] 总字符串: %d" % len(all_strings))

    # Categorize strings
    source_paths = {}  # path → addr (source file references)
    rtti_names = {}   # class_name → addr
    game_strings = {}  # string → addr (meaningful game strings)

    for addr, text in all_strings.items():
        if text.startswith('.?AV') or text.startswith('.?AU'):
            # RTTI type name
            class_name = text[4:]
            if class_name.endswith('@@'):
                class_name = class_name[:-2]
            parts = class_name.split('@')
            parts = [p for p in parts if p]
            if parts:
                class_name = '::'.join(reversed(parts))
                rtti_names[class_name] = addr
        elif ':\\' in text and '.cpp' in text.lower():
            source_paths[text] = addr
        elif ':\\' in text and '.h' in text.lower():
            source_paths[text] = addr
        elif len(text) >= 5 and text.isprintable():
            game_strings[text] = addr

    log("[*] 源代码路径: %d" % len(source_paths))
    log("[*] RTTI 类名: %d" % len(rtti_names))
    log("[*] 游戏字符串: %d" % len(game_strings))

    # Show source paths (key for function-to-file mapping)
    if source_paths:
        log("[*] 源代码路径样本:")
        for path in sorted(source_paths.keys())[:15]:
            log("    %s" % path)

    # Map strings to referencing functions
    string_func_map = {}  # string_addr → set(func_start_ea)
    for addr in all_strings:
        refs = list(idautils.DataRefsTo(addr))
        if not refs:
            continue
        funcs = set()
        for ref in refs:
            func = ida_funcs.get_func(ref)
            if func and TEXT_START <= func.start_ea < TEXT_END:
                funcs.add(func.start_ea)
        if funcs:
            string_func_map[addr] = funcs

    log("[*] 有函数引用的字符串: %d" % len(string_func_map))

    return all_strings, source_paths, rtti_names, game_strings, string_func_map


# ============================================================
# Phase 2: Source File → Function Mapping
# ============================================================
def phase2_source_mapping(source_paths, string_func_map, pdb_data):
    """
    Map functions to source files using assertion/debug path strings.
    If a function references "D:\Project\PAL3\gamebase\FileSys.cpp",
    it's likely defined in (or asserts from) FileSys.cpp.
    Cross-reference with PDB source_file_index.
    """
    log("")
    log("=" * 60)
    log("[Phase 2] 源文件→函数映射")
    log("=" * 60)

    # PDB source_file_index maps function → source file
    pdb_source_index = pdb_data.get('source_file_index', {})
    pdb_functions = pdb_data.get('functions', [])

    # Build: source_filename → list of PDB functions
    file_to_pdb_funcs = {}
    for func in pdb_functions:
        src = func.get('source_file', '')
        if src:
            basename = os.path.basename(src).lower()
            if basename not in file_to_pdb_funcs:
                file_to_pdb_funcs[basename] = []
            file_to_pdb_funcs[basename].append(func)

    log("[*] PDB 源文件: %d" % len(file_to_pdb_funcs))

    # Map PAL3 source path strings to file basenames
    func_to_source = {}  # func_ea → source_basename
    for path_str, str_addr in source_paths.items():
        if str_addr not in string_func_map:
            continue
        # Extract basename from path
        basename = os.path.basename(path_str).lower()
        for func_ea in string_func_map[str_addr]:
            if func_ea not in func_to_source:
                func_to_source[func_ea] = set()
            func_to_source[func_ea].add(basename)

    log("[*] PAL3 函数→源文件映射: %d 个函数" % len(func_to_source))

    # For each mapped function, list its PDB candidates
    file_matches = {}
    for func_ea, basenames in func_to_source.items():
        for basename in basenames:
            if basename in file_to_pdb_funcs:
                if func_ea not in file_matches:
                    file_matches[func_ea] = []
                file_matches[func_ea].append({
                    'source_file': basename,
                    'pdb_func_count': len(file_to_pdb_funcs[basename]),
                })

    log("[*] 有 PDB 候选的函数: %d" % len(file_matches))

    return func_to_source, file_to_pdb_funcs


# ============================================================
# Phase 3: RTTI + VTable Analysis
# ============================================================
def phase3_rtti_vtables(rtti_names, pdb_data):
    """
    For each RTTI class found in PAL3.exe:
    1. Find its TypeDescriptor
    2. Find COL (CompleteObjectLocator) referencing it
    3. Find vtable referencing COL
    4. Map vtable entries to PDB virtual methods
    """
    log("")
    log("=" * 60)
    log("[Phase 3] RTTI VTable 分析")
    log("=" * 60)

    # Build PDB class info index
    pdb_classes = {}
    for cls in pdb_data.get('classes', []):
        name = cls.get('name', '')
        if name:
            pdb_classes[name] = cls

    # Cross-reference RTTI classes with PDB
    matched_classes = set()
    for rtti_name in rtti_names:
        # Try direct match
        if rtti_name in pdb_classes:
            matched_classes.add(rtti_name)
        else:
            # Try without namespace
            simple = rtti_name.split('::')[-1]
            for pdb_name in pdb_classes:
                if pdb_name == simple or pdb_name.endswith('::' + simple):
                    matched_classes.add(rtti_name)
                    break

    log("[*] RTTI类与PDB匹配: %d / %d" % (len(matched_classes), len(rtti_names)))

    # Find vtables by tracing RTTI references
    vtables_found = {}
    for class_name, rtti_addr in rtti_names.items():
        # TypeDescriptor is at rtti_addr - 8 (name field is at +8 of TD)
        td_addr = rtti_addr - 8

        # Find who references the TypeDescriptor
        # COL.pTypeDescriptor is at COL+12 (32-bit)
        td_refs = list(idautils.DataRefsTo(td_addr))
        if not td_refs:
            # Also try refs to the string itself
            td_refs = list(idautils.DataRefsTo(rtti_addr))

        for ref in td_refs:
            # This ref might be inside a COL (at offset +12)
            # COL structure: signature(4), offset(4), cdOffset(4), pTypeDescriptor(4), ...
            col_start = ref - 12
            # Verify COL: first dword should be 0 (for 32-bit)
            if not ida_bytes.is_loaded(col_start):
                continue
            sig = idc.get_wide_dword(col_start)
            if sig != 0:
                continue

            # Find references to COL (vtable[-4] points to COL)
            col_refs = list(idautils.DataRefsTo(col_start))
            for cref in col_refs:
                # vtable starts right after COL pointer
                vt_start = cref + 4
                # Verify: first entry should be in .text
                first_entry = idc.get_wide_dword(vt_start)
                if TEXT_START <= first_entry < TEXT_END:
                    # Extract vtable entries
                    entries = []
                    ea = vt_start
                    while True:
                        val = idc.get_wide_dword(ea)
                        if not (TEXT_START <= val < TEXT_END):
                            break
                        entries.append(val)
                        ea += 4
                        if len(entries) > 200:
                            break

                    if entries:
                        vtables_found[class_name] = {
                            'td_addr': td_addr,
                            'col_addr': col_start,
                            'vt_addr': vt_start,
                            'entries': entries,
                        }
                        break
            if class_name in vtables_found:
                break

    log("[*] VTable 定位: %d 个类" % len(vtables_found))

    # Apply vtable names and method hints
    named = 0
    methods_named = 0

    for class_name, vt_info in vtables_found.items():
        # Name the vtable
        clean = class_name.replace('::', '_')
        vt_name = "vtbl_%s" % clean
        if ida_name.set_name(vt_info['vt_addr'], vt_name, ida_name.SN_NOWARN):
            named += 1

        # Try to match methods with PDB
        pdb_cls = pdb_classes.get(class_name)
        if not pdb_cls:
            simple = class_name.split('::')[-1]
            pdb_cls = pdb_classes.get(simple)

        if pdb_cls:
            methods = pdb_cls.get('methods', [])
            # Name vtable entries with class context
            for i, entry_addr in enumerate(vt_info['entries']):
                existing = ida_name.get_name(entry_addr) or ""
                if existing.startswith("sub_"):
                    # Give a hint name
                    if i < len(methods):
                        method = methods[i]
                        mname = method.get('name', '')
                        if mname:
                            short = mname.split('::')[-1] if '::' in mname else mname
                            hint = "%s_vf%d_%s" % (clean, i, short)
                            if len(hint) > 80:
                                hint = hint[:80]
                            if ida_name.set_name(entry_addr, hint, ida_name.SN_NOWARN):
                                methods_named += 1
                    else:
                        hint = "%s_vf%d" % (clean, i)
                        ida_name.set_name(entry_addr, hint, ida_name.SN_NOWARN)

    log("[*] VTable 命名: %d, 方法提示: %d" % (named, methods_named))
    return vtables_found


# ============================================================
# Phase 4: Unique String Function Matching
# ============================================================
def phase4_unique_strings(all_strings, string_func_map, pdb_data, func_to_source, file_to_pdb_funcs):
    """
    Match functions by unique string usage combined with source file info.
    If a function:
      1. References source path "Foo.cpp"
      2. Has unique game strings only used by one function
    And PDB shows a function in Foo.cpp with matching characteristics,
    we can make a high-confidence match.
    """
    log("")
    log("=" * 60)
    log("[Phase 4] 唯一字符串精确匹配")
    log("=" * 60)

    pdb_functions = pdb_data.get('functions', [])

    # Build index: PDB function name keywords
    # Many PDB functions have names like "ClassName::MethodName"
    # If a PAL3 function references "ClassName" string, it might be that method

    # Find strings that are referenced by exactly 1 function
    unique_str_funcs = {}  # func_ea → list of unique strings
    for str_addr, funcs in string_func_map.items():
        if len(funcs) == 1 and str_addr in all_strings:
            func_ea = list(funcs)[0]
            text = all_strings[str_addr]
            if len(text) >= 5 and text.isprintable() and not text.startswith('.?'):
                if func_ea not in unique_str_funcs:
                    unique_str_funcs[func_ea] = []
                unique_str_funcs[func_ea].append(text)

    log("[*] 有唯一字符串的函数: %d" % len(unique_str_funcs))

    # For functions with source file info + unique strings,
    # try to match against PDB functions in the same file
    matches = {}
    for func_ea, unique_strs in unique_str_funcs.items():
        existing = ida_name.get_name(func_ea) or ""
        if not existing.startswith("sub_"):
            continue

        # Get source file for this function
        sources = func_to_source.get(func_ea, set())
        if not sources:
            continue

        # Get PDB functions in the same source file
        for src in sources:
            pdb_funcs_in_file = file_to_pdb_funcs.get(src, [])
            if not pdb_funcs_in_file:
                continue

            # Look for PDB functions whose name matches one of the unique strings
            for pdb_func in pdb_funcs_in_file:
                pdb_name = pdb_func.get('name', '')
                pdb_mangled = pdb_func.get('mangled_name', '')
                if not pdb_name:
                    continue

                # Check if any unique string contains the function/class name
                for s in unique_strs:
                    # Exact function name in string (common in asserts)
                    if pdb_name in s:
                        matches[func_ea] = {
                            'mangled': pdb_mangled,
                            'name': pdb_name,
                            'source': src,
                            'evidence': 'name_in_assert',
                            'string': s[:80],
                        }
                        break
                    # Class name from method (e.g. "CBattleField" in string for CBattleField::Update)
                    if '::' in pdb_name:
                        cls_part = pdb_name.split('::')[0]
                        if len(cls_part) >= 5 and cls_part in s:
                            # Only if this is the only function in the file matching
                            matches[func_ea] = {
                                'mangled': pdb_mangled,
                                'name': pdb_name,
                                'source': src,
                                'evidence': 'class_in_string',
                                'string': s[:80],
                            }
                            break
                if func_ea in matches:
                    break

    log("[*] 字符串+源文件匹配: %d" % len(matches))

    # Apply high-confidence matches
    applied = 0
    for func_ea, info in matches.items():
        mangled = info['mangled']
        if mangled:
            if ida_name.set_name(func_ea, mangled, ida_name.SN_NOWARN):
                applied += 1
            elif ida_name.set_name(func_ea, mangled, ida_name.SN_FORCE):
                applied += 1

    log("[*] 应用: %d" % applied)
    return matches


# ============================================================
# Phase 5: Name functions by vtable cross-references
# ============================================================
def phase5_vtable_callers(vtables_found, pdb_data):
    """
    Functions that load a vtable pointer (lea ecx, [vtable]) are likely
    constructors of that class. Name them accordingly.
    """
    log("")
    log("=" * 60)
    log("[Phase 5] 构造函数识别 (vtable 加载)")
    log("=" * 60)

    pdb_classes = {}
    for cls in pdb_data.get('classes', []):
        name = cls.get('name', '')
        if name:
            pdb_classes[name] = cls

    ctor_named = 0
    for class_name, vt_info in vtables_found.items():
        vt_addr = vt_info['vt_addr']

        # Find functions that reference this vtable address
        # (constructors store vtable ptr: mov [ecx], offset vtable)
        refs = list(idautils.DataRefsTo(vt_addr))
        ctor_candidates = set()
        for ref in refs:
            func = ida_funcs.get_func(ref)
            if func and TEXT_START <= func.start_ea < TEXT_END:
                existing = ida_name.get_name(func.start_ea) or ""
                if existing.startswith("sub_"):
                    ctor_candidates.add(func.start_ea)

        if len(ctor_candidates) == 1:
            # Unique reference → likely constructor
            ctor_ea = list(ctor_candidates)[0]
            clean = class_name.replace('::', '_')
            ctor_name = "%s_ctor" % clean
            if ida_name.set_name(ctor_ea, ctor_name, ida_name.SN_NOWARN):
                ctor_named += 1
        elif len(ctor_candidates) == 2:
            # Could be ctor + dtor, or ctor + copy ctor
            for i, ea in enumerate(sorted(ctor_candidates)):
                clean = class_name.replace('::', '_')
                name = "%s_ctor%d" % (clean, i)
                existing = ida_name.get_name(ea) or ""
                if existing.startswith("sub_"):
                    if ida_name.set_name(ea, name, ida_name.SN_NOWARN):
                        ctor_named += 1

    log("[*] 构造函数命名: %d" % ctor_named)
    return ctor_named


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 启发式匹配 (第二轮)")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)
        log("[*] PDB: %d classes, %d functions" % (
            len(pdb_data.get('classes', [])), len(pdb_data.get('functions', []))))

        # Execute phases
        all_strings, source_paths, rtti_names, game_strings, string_func_map = phase1_strings()
        func_to_source, file_to_pdb_funcs = phase2_source_mapping(source_paths, string_func_map, pdb_data)
        vtables_found = phase3_rtti_vtables(rtti_names, pdb_data)
        matches = phase4_unique_strings(all_strings, string_func_map, pdb_data, func_to_source, file_to_pdb_funcs)
        ctor_count = phase5_vtable_callers(vtables_found, pdb_data)

        # Save
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

        # Summary
        log("")
        log("=" * 60)
        log("[Summary]")
        log("  RTTI 类: %d" % len(rtti_names))
        log("  VTable 定位: %d" % len(vtables_found))
        log("  源文件映射: %d 函数" % len(func_to_source))
        log("  字符串匹配: %d 函数" % len(matches))
        log("  构造函数: %d" % ctor_count)
        log("=" * 60)

        # Report
        os.makedirs(os.path.dirname(OUTPUT_FILE), exist_ok=True)
        report = {
            'meta': {'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S")},
            'rtti_classes': list(rtti_names.keys()),
            'vtables': {name: {'addr': '0x%08X' % info['vt_addr'], 'size': len(info['entries'])}
                       for name, info in vtables_found.items()},
            'source_paths': list(source_paths.keys()),
            'func_source_mapping': {
                '0x%08X' % ea: list(srcs) for ea, srcs in func_to_source.items()
            },
            'matches': {
                '0x%08X' % ea: info for ea, info in matches.items()
            },
        }
        with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
            json.dump(report, f, indent=2, ensure_ascii=False)

        log("[*] 报告: %s" % OUTPUT_FILE)

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
