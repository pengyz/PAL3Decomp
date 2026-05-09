"""
IDAPython: PAL3.exe 字符串启发式匹配 v2

改进策略:
  1. 从断言/错误信息中提取函数名 (如 "new fail in ClassName::Method")
  2. 从源文件路径确定函数所属文件
  3. 利用 PDB 的 source_file_index 定位具体函数
  4. 对于多候选情况，用调用关系和位置信息消歧

字符串模式:
  - "ClassName::MethodName" → 直接匹配
  - "new fail in ClassName::Method" → 提取 ClassName::Method
  - "D:\Project\PAL3\...\File.cpp" → 确定源文件
  - "ASSERT: condition, file, line" → 确定文件+附近行号

运行环境: PAL3.exe.i64
用法:
  idat.exe -A -S"pal3_string_match_v2.py" original/PAL3.exe.i64
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
OUTPUT_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "string_match_v2_report.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_string_match_v2_log.txt")

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


def extract_class_method_from_string(text):
    """
    从字符串中提取 ClassName::MethodName 模式。
    常见格式:
      - "new fail in CEffCylinder::Create"
      - "CEffCylinder::Create: error"
      - "Assert failed: condition, CEffCylinder::Create"
    """
    # Pattern: Word::Word (C++ method reference)
    matches = re.findall(r'([A-Z]\w+)::(\w+)', text)
    if matches:
        return [(cls, method) for cls, method in matches]

    # Pattern: ClassName.MethodName (less common)
    matches = re.findall(r'([A-Z][a-zA-Z0-9_]+)\.([a-z]\w+)', text)
    if matches:
        return [(cls, method) for cls, method in matches]

    return []


def get_all_strings():
    """Get all strings from .rdata and .data segments by scanning raw bytes."""
    strings = {}
    for seg_start, seg_end in [(RDATA_START, RDATA_END), (DATA_START, DATA_END)]:
        seg_size = seg_end - seg_start
        if seg_size <= 0:
            continue
        raw = ida_bytes.get_bytes(seg_start, seg_size)
        if not raw:
            continue
        # Scan for null-terminated ASCII strings >= 3 chars
        i = 0
        while i < len(raw):
            if 0x20 <= raw[i] < 0x7F:
                j = i
                while j < len(raw) and 0x20 <= raw[j] < 0x7F:
                    j += 1
                if j < len(raw) and raw[j] == 0 and j - i >= 3:
                    try:
                        text = raw[i:j].decode('ascii')
                        strings[seg_start + i] = text
                    except:
                        pass
                i = j + 1
            else:
                i += 1
    return strings


def get_string_xrefs(strings):
    """Map each string to the function(s) that reference it."""
    str_to_funcs = {}  # str_addr → set(func_ea)
    for str_addr in strings:
        # Try both data refs and all xrefs
        refs = set()
        for xref in idautils.XrefsTo(str_addr, 0):
            refs.add(xref.frm)
        # Also try DataRefsTo
        for ref in idautils.DataRefsTo(str_addr):
            refs.add(ref)

        funcs = set()
        for ref in refs:
            func = ida_funcs.get_func(ref)
            if func and TEXT_START <= func.start_ea < TEXT_END:
                funcs.add(func.start_ea)
        if funcs:
            str_to_funcs[str_addr] = funcs
    return str_to_funcs


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 字符串匹配 v2")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        # Load PDB
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        pdb_functions = pdb_data.get('functions', [])
        log("[*] PDB 函数: %d" % len(pdb_functions))

        # Build PDB lookup indices
        # 1. By class::method name
        pdb_by_classmethod = {}  # "ClassName::Method" → [pdb_func, ...]
        for func in pdb_functions:
            name = func.get('name', '')
            mangled = func.get('mangled_name', '')
            if '::' in name and mangled:
                if name not in pdb_by_classmethod:
                    pdb_by_classmethod[name] = []
                pdb_by_classmethod[name].append(func)

        # 2. By source file
        pdb_by_file = {}  # basename → [pdb_func, ...]
        for func in pdb_functions:
            src = func.get('source_file', '')
            if src:
                basename = os.path.basename(src).lower()
                if basename not in pdb_by_file:
                    pdb_by_file[basename] = []
                pdb_by_file[basename].append(func)

        # 3. By class name
        pdb_by_class = {}  # class_name → [pdb_func, ...]
        for func in pdb_functions:
            name = func.get('name', '')
            if '::' in name:
                cls = name.split('::')[0]
                if cls not in pdb_by_class:
                    pdb_by_class[cls] = []
                pdb_by_class[cls].append(func)

        log("[*] PDB 索引: %d class::method, %d files, %d classes" % (
            len(pdb_by_classmethod), len(pdb_by_file), len(pdb_by_class)))

        # Phase 1: Extract strings
        log("")
        log("[Phase 1] 提取字符串")
        all_strings = get_all_strings()
        log("[*] 字符串: %d" % len(all_strings))

        str_to_funcs = get_string_xrefs(all_strings)
        log("[*] 有引用的字符串: %d" % len(str_to_funcs))

        # Phase 2: Extract function names from strings
        log("")
        log("[Phase 2] 从字符串提取 Class::Method")

        # For each string, extract potential class::method references
        func_candidates = {}  # func_ea → list of (class, method, confidence, evidence)

        for str_addr, text in all_strings.items():
            if str_addr not in str_to_funcs:
                continue

            funcs = str_to_funcs[str_addr]
            class_methods = extract_class_method_from_string(text)

            if not class_methods:
                continue

            for cls, method in class_methods:
                full_name = "%s::%s" % (cls, method)
                # Check if this exists in PDB
                if full_name in pdb_by_classmethod:
                    for func_ea in funcs:
                        existing = ida_name.get_name(func_ea) or ""
                        if not existing.startswith("sub_"):
                            continue
                        if func_ea not in func_candidates:
                            func_candidates[func_ea] = []

                        # Determine confidence
                        # High: string says "in ClassName::Method" or "ClassName::Method failed"
                        # Medium: string contains ClassName::Method among other text
                        if ("in %s" % full_name) in text or \
                           text.startswith(full_name) or \
                           ("%s:" % full_name) in text or \
                           ("%s fail" % full_name) in text:
                            confidence = 'high'
                        elif len(funcs) == 1:
                            confidence = 'high'  # unique function reference
                        else:
                            confidence = 'medium'

                        func_candidates[func_ea].append({
                            'class': cls,
                            'method': method,
                            'full_name': full_name,
                            'confidence': confidence,
                            'string': text[:80],
                            'unique_ref': len(funcs) == 1,
                        })

        log("[*] 候选函数: %d" % len(func_candidates))

        # Phase 3: Resolve and apply
        log("")
        log("[Phase 3] 解析与应用")

        applied = 0
        high_matches = 0
        medium_matches = 0
        conflicts = 0
        all_matches = []

        for func_ea, candidates in func_candidates.items():
            # Deduplicate by full_name
            name_counts = {}
            for c in candidates:
                fn = c['full_name']
                conf = c['confidence']
                if fn not in name_counts:
                    name_counts[fn] = {'high': 0, 'medium': 0, 'evidence': []}
                name_counts[fn][conf] += 1
                name_counts[fn]['evidence'].append(c['string'])

            # Pick best candidate
            best = None
            best_score = 0
            for fn, counts in name_counts.items():
                score = counts['high'] * 3 + counts['medium']
                if score > best_score:
                    best = fn
                    best_score = score

            if not best:
                continue

            # Check for conflicts (multiple different names)
            if len(name_counts) > 1 and best_score < 3:
                conflicts += 1
                continue

            # Look up mangled name from PDB
            pdb_matches = pdb_by_classmethod.get(best, [])
            if not pdb_matches:
                continue

            # If multiple PDB functions with same name (overloads), pick first
            mangled = pdb_matches[0].get('mangled_name', '')
            if not mangled:
                continue

            # Apply
            confidence = 'high' if name_counts[best]['high'] > 0 else 'medium'
            if ida_name.set_name(func_ea, mangled, ida_name.SN_NOWARN) or \
               ida_name.set_name(func_ea, mangled, ida_name.SN_FORCE):
                applied += 1
                if confidence == 'high':
                    high_matches += 1
                else:
                    medium_matches += 1

                all_matches.append({
                    'addr': '0x%08X' % func_ea,
                    'name': best,
                    'mangled': mangled,
                    'confidence': confidence,
                    'evidence': name_counts[best]['evidence'][:3],
                })

        log("[*] 应用: %d (高=%d, 中=%d, 冲突=%d)" % (
            applied, high_matches, medium_matches, conflicts))

        # Phase 4: Source file path → narrow function location
        log("")
        log("[Phase 4] 源文件路径辅助定位")

        # Functions that reference a source path are in that file
        # This helps future analysis even if we can't name them now
        source_mappings = {}
        for str_addr, text in all_strings.items():
            if ':\\' not in text or not ('.cpp' in text.lower() or '.h' in text.lower()):
                continue
            if str_addr not in str_to_funcs:
                continue
            basename = os.path.basename(text).lower()
            for func_ea in str_to_funcs[str_addr]:
                if func_ea not in source_mappings:
                    source_mappings[func_ea] = set()
                source_mappings[func_ea].add(basename)

        # For functions mapped to a source file with few PDB candidates,
        # we can do more aggressive matching
        additional = 0
        for func_ea, files in source_mappings.items():
            existing = ida_name.get_name(func_ea) or ""
            if not existing.startswith("sub_"):
                continue

            for fname in files:
                pdb_in_file = pdb_by_file.get(fname, [])
                if len(pdb_in_file) == 1:
                    # Only one function in this file! Direct match
                    mangled = pdb_in_file[0].get('mangled_name', '')
                    name = pdb_in_file[0].get('name', '')
                    if mangled:
                        if ida_name.set_name(func_ea, mangled, ida_name.SN_NOWARN):
                            additional += 1
                            all_matches.append({
                                'addr': '0x%08X' % func_ea,
                                'name': name,
                                'mangled': mangled,
                                'confidence': 'high',
                                'evidence': ['sole function in ' + fname],
                            })
                            break

        log("[*] 源文件唯一函数匹配: %d" % additional)
        applied += additional

        # Save
        idc.save_database(idc.get_idb_path(), 0)
        log("")
        log("[*] 总计应用: %d 个函数名" % applied)
        log("[*] 数据库已保存")

        # Report
        os.makedirs(os.path.dirname(OUTPUT_FILE), exist_ok=True)
        report = {
            'meta': {'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S")},
            'stats': {
                'total_strings': len(all_strings),
                'strings_with_refs': len(str_to_funcs),
                'candidates': len(func_candidates),
                'applied': applied,
                'high_confidence': high_matches,
                'medium_confidence': medium_matches,
                'conflicts': conflicts,
                'source_file_matches': additional,
            },
            'matches': all_matches,
            'source_files_found': sorted(set(
                os.path.basename(text)
                for text in all_strings.values()
                if ':\\' in text and '.cpp' in text.lower()
            )),
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
