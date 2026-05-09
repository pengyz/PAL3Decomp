"""
IDAPython: PAL3.exe 直接字符串引用匹配

不依赖 IDA 的 xref 数据库，直接在 .text 中搜索对字符串地址的引用。
这解决了 IDA 在 .data 段未建立 xref 的问题。

策略:
  1. 从 .data 段提取所有有意义的字符串及其 VA
  2. 在 .text 段中搜索这些 VA（作为 push/mov 操作数出现）
  3. 定位引用所在的函数
  4. 从字符串中提取 Class::Method 模式
  5. 与 PDB 匹配并应用

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
OUTPUT_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "direct_match_report.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_direct_string_match_log.txt")

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


def extract_class_method(text):
    """Extract ClassName::MethodName from a string."""
    matches = re.findall(r'([A-Z][A-Za-z0-9_]+)::([A-Za-z_]\w+)', text)
    return matches


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 直接字符串引用匹配")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        # Load PDB
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        pdb_functions = pdb_data.get('functions', [])
        log("[*] PDB 函数: %d" % len(pdb_functions))

        # Build PDB lookup: "ClassName::Method" → mangled_name
        pdb_by_name = {}
        for func in pdb_functions:
            name = func.get('name', '')
            mangled = func.get('mangled_name', '')
            if name and mangled:
                pdb_by_name[name] = mangled

        log("[*] PDB 名称索引: %d" % len(pdb_by_name))

        # Phase 1: Extract strings from .data and .rdata
        log("")
        log("[Phase 1] 字符串提取")

        interesting_strings = {}  # va → text (only strings with useful patterns)

        for seg_start, seg_end in [(RDATA_START, RDATA_END), (DATA_START, DATA_END)]:
            seg_size = seg_end - seg_start
            raw = ida_bytes.get_bytes(seg_start, seg_size)
            if not raw:
                continue

            i = 0
            while i < len(raw):
                if 0x20 <= raw[i] < 0x7F:
                    j = i
                    while j < len(raw) and (0x20 <= raw[j] < 0x7F or raw[j] in (0x0D, 0x0A, 0x09)):
                        j += 1
                    if j < len(raw) and raw[j] == 0 and j - i >= 5:
                        text = raw[i:j].decode('ascii', errors='replace')
                        va = seg_start + i
                        # Keep strings with class::method, source paths, or other useful info
                        if '::' in text or ':\\' in text or len(text) >= 8:
                            interesting_strings[va] = text
                    i = j + 1
                else:
                    i += 1

        log("[*] 有效字符串: %d" % len(interesting_strings))

        # Separate out key categories
        cm_strings = {}  # va → (text, [(class, method), ...])
        path_strings = {}  # va → source_path
        for va, text in interesting_strings.items():
            cms = extract_class_method(text)
            if cms:
                cm_strings[va] = (text, cms)
            if ':\\' in text and ('.cpp' in text.lower() or '.h' in text.lower()):
                path_strings[va] = text

        log("[*] Class::Method 字符串: %d" % len(cm_strings))
        log("[*] 源文件路径字符串: %d" % len(path_strings))

        for va, (text, cms) in list(cm_strings.items())[:10]:
            log("    0x%08X: \"%s\" → %s" % (va, text[:50], cms))

        # Phase 2: Find references in .text by searching for VA as immediate operand
        log("")
        log("[Phase 2] 在 .text 中搜索字符串地址引用")

        text_size = TEXT_END - TEXT_START
        text_bytes = ida_bytes.get_bytes(TEXT_START, text_size)
        if not text_bytes:
            log("[!] 无法读取 .text 段")
            return

        # For each interesting string VA, search for it as a 32-bit LE value in .text
        string_refs = {}  # str_va → list of (code_ea, func_ea)

        target_vas = list(cm_strings.keys()) + list(path_strings.keys())
        log("[*] 搜索 %d 个字符串地址的引用..." % len(target_vas))

        for str_va in target_vas:
            needle = struct.pack('<I', str_va)
            pos = 0
            refs = []
            while True:
                pos = text_bytes.find(needle, pos)
                if pos == -1:
                    break
                code_ea = TEXT_START + pos
                func = ida_funcs.get_func(code_ea)
                if func:
                    refs.append((code_ea, func.start_ea))
                pos += 1

            if refs:
                string_refs[str_va] = refs

        log("[*] 找到引用: %d 个字符串" % len(string_refs))

        # Phase 3: Match Class::Method strings to functions
        log("")
        log("[Phase 3] Class::Method → 函数匹配")

        matches = []
        applied = 0

        for str_va, (text, cms) in cm_strings.items():
            if str_va not in string_refs:
                log("    DEBUG: 0x%08X no refs (%s)" % (str_va, text[:40]))
                continue

            refs = string_refs[str_va]
            # Get unique functions referencing this string
            ref_funcs = list(set(func_ea for _, func_ea in refs))

            for cls, method in cms:
                full_name = "%s::%s" % (cls, method)
                if full_name not in pdb_by_name:
                    log("    DEBUG: %s not in PDB" % full_name)
                    continue

                mangled = pdb_by_name[full_name]

                log("    DEBUG: %s → %d funcs, names: %s" % (
                    full_name, len(ref_funcs),
                    [ida_name.get_name(ea) or "?" for ea in ref_funcs]))

                # If only one function references this string → high confidence
                # String evidence is the strongest signal — override any previous name
                if len(ref_funcs) == 1:
                    func_ea = ref_funcs[0]
                    existing = ida_name.get_name(func_ea) or ""

                    if ida_name.set_name(func_ea, mangled, ida_name.SN_FORCE):
                        applied += 1
                        matches.append({
                            'addr': '0x%08X' % func_ea,
                            'name': full_name,
                            'mangled': mangled,
                            'confidence': 'high',
                            'evidence': text[:80],
                            'prev_name': existing,
                        })
                        log("    MATCH: 0x%08X = %s (was: %s)" % (func_ea, full_name, existing))
                elif len(ref_funcs) <= 3:
                    # Multiple functions — apply to all with lower confidence marker
                    for func_ea in ref_funcs:
                        existing = ida_name.get_name(func_ea) or ""
                        if existing.startswith("sub_"):
                            # Use a hint rather than definitive name
                            hint_name = "maybe_%s_%s" % (cls, method)
                            if ida_name.set_name(func_ea, hint_name, ida_name.SN_NOWARN):
                                matches.append({
                                    'addr': '0x%08X' % func_ea,
                                    'name': full_name,
                                    'confidence': 'low',
                                    'evidence': text[:80],
                                })

        log("[*] 精确匹配: %d" % applied)

        # Phase 4: Source file paths → function group identification
        log("")
        log("[Phase 4] 源文件路径定位")

        source_func_map = {}  # basename → set of func_eas
        for str_va, path in path_strings.items():
            if str_va not in string_refs:
                continue
            basename = os.path.basename(path).lower()
            ref_funcs = set(func_ea for _, func_ea in string_refs[str_va])
            if basename not in source_func_map:
                source_func_map[basename] = set()
            source_func_map[basename].update(ref_funcs)

        log("[*] 源文件→函数组:")
        for basename, funcs in sorted(source_func_map.items()):
            log("    %s: %d 函数" % (basename, len(funcs)))

        # Phase 5: Use PDB source_file_index for further matching
        log("")
        log("[Phase 5] PDB 源文件索引辅助匹配")

        # Build file → PDB functions
        pdb_by_file = {}
        for func in pdb_functions:
            src = func.get('source_file', '')
            if src:
                bn = os.path.basename(src).lower()
                if bn not in pdb_by_file:
                    pdb_by_file[bn] = []
                pdb_by_file[bn].append(func)

        # For files with very few functions in both PAL3 and PDB
        file_matches = 0
        for basename, pal3_funcs in source_func_map.items():
            pdb_funcs = pdb_by_file.get(basename, [])
            if not pdb_funcs:
                continue

            # If PAL3 has 1 function referencing this file path, and PDB has few in that file
            unnamed_funcs = [ea for ea in pal3_funcs
                           if (ida_name.get_name(ea) or "").startswith("sub_")]

            if len(unnamed_funcs) == 1 and len(pdb_funcs) <= 5:
                # Try to narrow down: the function referencing the path is likely
                # one that does error checking (assert/throw) in that file
                # Just annotate it for now
                func_ea = unnamed_funcs[0]
                comment = "Source: %s (PDB has %d funcs)" % (basename, len(pdb_funcs))
                idc.set_func_cmt(func_ea, comment, 0)
                file_matches += 1

        log("[*] 文件标注: %d" % file_matches)

        # Save
        idc.save_database(idc.get_idb_path(), 0)
        log("")
        log("[*] 总结:")
        log("    精确函数名匹配: %d" % applied)
        log("    源文件定位: %d 文件, %d 函数" % (len(source_func_map), sum(len(f) for f in source_func_map.values())))
        log("[*] 数据库已保存")

        # Report
        os.makedirs(os.path.dirname(OUTPUT_FILE), exist_ok=True)
        report = {
            'meta': {'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S")},
            'stats': {
                'interesting_strings': len(interesting_strings),
                'cm_strings': len(cm_strings),
                'path_strings': len(path_strings),
                'strings_with_refs': len(string_refs),
                'applied': applied,
            },
            'matches': matches,
            'source_file_groups': {
                basename: ['0x%08X' % ea for ea in sorted(funcs)]
                for basename, funcs in source_func_map.items()
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
