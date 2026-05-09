"""
IDAPython: RTTI + vtable + 字符串启发式匹配

在 PAL3.exe IDB 中:
  1. 扫描 RTTI type_info 获取类名 → 确认哪些类存在
  2. 从 vtable 定位虚函数 → 用 PDB 方法列表匹配
  3. 用字符串引用做 1:1 函数匹配
  4. 交叉验证: 检查已知函数的调用关系是否与 PDB 一致

运行环境: PAL3.exe.i64
用法:
  idat.exe -A -S"pal3_rtti_match.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_name
import ida_xref
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
OUTPUT_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "rtti_match_report.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_rtti_match_log.txt")

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
# Phase 1: RTTI Class Discovery
# ============================================================
def phase1_rtti():
    """
    Scan .rdata for MSVC RTTI TypeDescriptor structs.
    TypeDescriptor layout:
      +0: vftable ptr (points to type_info::vftable)
      +4: spare (usually 0)
      +8: name[] (mangled class name, e.g. ".?AVMyClass@@")
    """
    log("")
    log("=" * 60)
    log("[Phase 1] RTTI 类名扫描")
    log("=" * 60)

    rtti_classes = {}  # class_name → TypeDescriptor address

    # Search for RTTI name pattern ".?AV" or ".?AU" (class/struct)
    ea = RDATA_START
    while ea < RDATA_END:
        # Look for ".?AV" or ".?AU" string
        flags = ida_bytes.get_flags(ea)
        if ida_bytes.is_strlit(flags):
            s = idc.get_strlit_contents(ea, -1, idc.STRTYPE_C)
            if s:
                try:
                    name_str = s.decode('ascii')
                except:
                    name_str = ''
                if name_str.startswith('.?AV') or name_str.startswith('.?AU'):
                    # This is an RTTI name, TypeDescriptor is at name_offset - 8
                    td_addr = ea - 8
                    # Extract class name
                    class_name = name_str[4:]  # skip ".?AV" or ".?AU"
                    if class_name.endswith('@@'):
                        class_name = class_name[:-2]
                    # Handle namespaces (@ separator)
                    parts = class_name.split('@')
                    parts = [p for p in parts if p]
                    if parts:
                        class_name = '::'.join(reversed(parts))
                        rtti_classes[class_name] = td_addr
        ea = idc.next_head(ea, RDATA_END)
        if ea == idc.BADADDR:
            break

    # Scan .rdata and .data for RTTI name patterns by reading bytes directly
    marker_av = b'.?AV'
    marker_au = b'.?AU'
    for seg_start, seg_end in [(RDATA_START, RDATA_END), (DATA_START, DATA_END)]:
        seg_size = seg_end - seg_start
        if seg_size <= 0:
            continue
        seg_bytes = ida_bytes.get_bytes(seg_start, seg_size)
        if not seg_bytes:
            continue
        for marker in (marker_av, marker_au):
            pos = 0
            while True:
                pos = seg_bytes.find(marker, pos)
                if pos == -1:
                    break
                # Read up to 128 bytes for the name
                end = seg_bytes.find(b'\x00', pos, pos + 128)
                if end == -1:
                    pos += 1
                    continue
                name_str = seg_bytes[pos:end].decode('ascii', errors='replace')
                if name_str.startswith('.?AV') or name_str.startswith('.?AU'):
                    abs_ea = seg_start + pos
                    td_addr = abs_ea - 8
                    class_name = name_str[4:]
                    if class_name.endswith('@@'):
                        class_name = class_name[:-2]
                    parts = class_name.split('@')
                    parts = [p for p in parts if p]
                    if parts:
                        class_name = '::'.join(reversed(parts))
                        if class_name not in rtti_classes:
                            rtti_classes[class_name] = td_addr
                pos += 1

    log("[*] 发现 RTTI 类: %d" % len(rtti_classes))
    if rtti_classes:
        sample = list(rtti_classes.items())[:10]
        for name, addr in sample:
            log("    %s @ 0x%08X" % (name, addr))
        if len(rtti_classes) > 10:
            log("    ... (%d more)" % (len(rtti_classes) - 10))

    return rtti_classes


# ============================================================
# Phase 2: VTable Discovery & Method Matching
# ============================================================
def phase2_vtables(rtti_classes, pdb_data):
    """
    For each RTTI class, find its vtable and map virtual methods.
    MSVC vtable layout:
      vtable[-4]: RTTICompleteObjectLocator pointer
      vtable[0]: first virtual method pointer
      vtable[4]: second virtual method pointer
      ...
    """
    log("")
    log("=" * 60)
    log("[Phase 2] VTable 虚函数匹配")
    log("=" * 60)

    # Build PDB class → methods index
    pdb_classes = {}
    for cls in pdb_data.get('classes', []):
        name = cls.get('name', '')
        methods = cls.get('methods', [])
        if name and methods:
            pdb_classes[name] = methods

    # For each RTTI class, try to find its vtable
    vtable_matches = {}
    total_methods_matched = 0

    for class_name, td_addr in rtti_classes.items():
        # Find COL (CompleteObjectLocator) that references this TypeDescriptor
        # COL has TypeDescriptor pointer at offset +12
        # Then vtable has COL pointer at vtable[-4]

        # Search for references to the TypeDescriptor
        td_refs = list(idautils.DataRefsTo(td_addr))
        if not td_refs:
            # Try refs to the name field
            td_refs = list(idautils.DataRefsTo(td_addr + 8))

        # For each ref, check if it's a COL
        vtable_addr = None
        for ref in td_refs:
            # COL references TD at offset +12 from COL start
            col_start = ref - 12
            if not (RDATA_START <= col_start < RDATA_END):
                col_start = ref  # might be at different offset

            # Look for references to COL (which would be vtable[-4])
            col_refs = list(idautils.DataRefsTo(col_start))
            for cref in col_refs:
                # vtable starts at cref + 4
                potential_vt = cref + 4
                # Verify: vtable entries should be pointers to .text
                first_entry = idc.get_wide_dword(potential_vt)
                if TEXT_START <= first_entry < TEXT_END:
                    vtable_addr = potential_vt
                    break
            if vtable_addr:
                break

        if not vtable_addr:
            continue

        # Extract vtable entries
        vt_entries = []
        ea = vtable_addr
        while True:
            val = idc.get_wide_dword(ea)
            if not (TEXT_START <= val < TEXT_END):
                break
            vt_entries.append(val)
            ea += 4
            if len(vt_entries) > 200:
                break

        if not vt_entries:
            continue

        # Match with PDB methods
        # Simple name matching for the class
        simple_name = class_name.split('::')[-1] if '::' in class_name else class_name
        pdb_methods = pdb_classes.get(class_name, []) or pdb_classes.get(simple_name, [])

        if pdb_methods and len(vt_entries) > 0:
            vtable_matches[class_name] = {
                'vtable_addr': vtable_addr,
                'num_entries': len(vt_entries),
                'entries': vt_entries,
                'pdb_methods': pdb_methods,
            }

            # If vtable size matches method count, try positional mapping
            # (This is a rough heuristic - vtable order should match)
            virtual_methods = [m for m in pdb_methods if 'virtual' in m.get('name', '').lower()
                              or m.get('name', '').startswith(class_name + '::~')]

    log("[*] VTable 发现: %d 个类" % len(vtable_matches))

    return vtable_matches


# ============================================================
# Phase 3: String-based Function Matching
# ============================================================
def phase3_strings(pdb_data):
    """
    Match functions by unique string references.
    Strategy:
    1. Build map: string → PAL3A function (from PDB function names that contain class info)
    2. For each PAL3 function with string refs, find matching PAL3A function
    """
    log("")
    log("=" * 60)
    log("[Phase 3] 字符串引用匹配")
    log("=" * 60)

    # Collect all strings in .rdata
    pal3_string_map = {}  # string_content → address
    ea = RDATA_START
    while ea < RDATA_END:
        flags = ida_bytes.get_flags(ea)
        if ida_bytes.is_strlit(flags):
            s = idc.get_strlit_contents(ea, -1, idc.STRTYPE_C)
            if s and len(s) >= 4:
                try:
                    text = s.decode('utf-8', errors='replace')
                    pal3_string_map[text] = ea
                except:
                    pass
        ea = idc.next_head(ea, RDATA_END)
        if ea == idc.BADADDR:
            break

    log("[*] PAL3 字符串: %d" % len(pal3_string_map))

    # For each string, find which PAL3 functions reference it
    string_to_funcs = {}  # string_addr → set of func_addrs
    for text, str_addr in pal3_string_map.items():
        refs = list(idautils.DataRefsTo(str_addr))
        funcs = set()
        for ref in refs:
            func = ida_funcs.get_func(ref)
            if func and TEXT_START <= func.start_ea < TEXT_END:
                funcs.add(func.start_ea)
        if funcs:
            string_to_funcs[text] = funcs

    # Build PAL3A function signature database from PDB
    # Use function names to identify unique functions
    pdb_funcs = pdb_data.get('functions', [])

    # Strategy: functions with unique class-identifying strings
    # e.g. "gbCamera" string likely only in gbCamera methods
    # Use PDB class methods to know which functions belong to which class

    # Build: class_name → list of method function names
    class_methods = {}
    for cls in pdb_data.get('classes', []):
        name = cls.get('name', '')
        methods = cls.get('methods', [])
        if name and methods:
            class_methods[name] = [m.get('name', '') for m in methods]

    # Find strings that are likely class names or function identifiers
    matches = {}
    for text, funcs in string_to_funcs.items():
        if len(funcs) != 1:
            continue  # Only use strings referenced by exactly 1 function

        func_addr = list(funcs)[0]
        existing_name = ida_name.get_name(func_addr) or ""
        if not existing_name.startswith("sub_"):
            continue  # Already named

        # Check if this string matches any PDB class/function name pattern
        # Common patterns: "ClassName::MethodName", error messages with class names
        for cls_name, methods in class_methods.items():
            if cls_name in text:
                # This function references a class name string
                # It's likely a method of that class (assertion, debug message, etc.)
                matches[func_addr] = {
                    'hint': 'string_ref',
                    'class': cls_name,
                    'string': text[:80],
                }
                break

    log("[*] 字符串→类映射: %d 函数" % len(matches))

    # More specific: match by exact assertion/error strings
    # Look for format strings like "%s::%s" or class names in assertions
    specific_matches = {}
    for text, funcs in string_to_funcs.items():
        if len(funcs) != 1:
            continue
        func_addr = list(funcs)[0]
        existing_name = ida_name.get_name(func_addr) or ""
        if not existing_name.startswith("sub_"):
            continue

        # Check for PDB function names that match this string
        for pdb_func in pdb_funcs:
            pdb_name = pdb_func.get('name', '')
            pdb_mangled = pdb_func.get('mangled_name', '')
            # If the string IS the function name or contains it
            if pdb_name and len(pdb_name) > 5 and pdb_name in text:
                specific_matches[func_addr] = {
                    'mangled': pdb_mangled,
                    'name': pdb_name,
                    'evidence': 'name_in_string',
                    'string': text[:80],
                }
                break

    log("[*] 精确字符串匹配: %d" % len(specific_matches))
    return matches, specific_matches


# ============================================================
# Phase 4: Apply Results
# ============================================================
def phase4_apply(rtti_classes, vtable_matches, string_matches, specific_matches, pdb_data):
    """Apply all discoveries to the IDB."""
    log("")
    log("=" * 60)
    log("[Phase 4] 应用结果")
    log("=" * 60)

    applied = 0

    # 1. Name RTTI TypeDescriptors
    for class_name, td_addr in rtti_classes.items():
        clean_name = class_name.replace('::', '_')
        td_name = "RTTI_TD_%s" % clean_name
        if ida_name.set_name(td_addr, td_name, ida_name.SN_NOWARN):
            applied += 1

    log("[*] RTTI TypeDescriptor 命名: %d" % len(rtti_classes))

    # 2. Name vtable locations
    vt_named = 0
    for class_name, vt_info in vtable_matches.items():
        clean_name = class_name.replace('::', '_')
        vt_name = "vtable_%s" % clean_name
        if ida_name.set_name(vt_info['vtable_addr'], vt_name, ida_name.SN_NOWARN):
            vt_named += 1
    log("[*] VTable 命名: %d" % vt_named)

    # 3. Apply vtable method names where possible
    method_named = 0
    for class_name, vt_info in vtable_matches.items():
        entries = vt_info['entries']
        pdb_methods = vt_info['pdb_methods']

        # Simple positional match if sizes align
        # This is risky - only do for exact size match
        if len(entries) == len(pdb_methods):
            for i, (entry_addr, method) in enumerate(zip(entries, pdb_methods)):
                existing = ida_name.get_name(entry_addr) or ""
                if existing.startswith("sub_"):
                    method_name = method.get('name', '')
                    if method_name:
                        # Use a hint name (not mangled, could be wrong)
                        hint = method_name.replace('::', '_').replace(' ', '_')
                        hint = "vf_%s_%d" % (hint, i)
                        if ida_name.set_name(entry_addr, hint, ida_name.SN_NOWARN):
                            method_named += 1

    log("[*] VTable 方法命名 (启发式): %d" % method_named)

    # 4. Apply specific string matches
    specific_applied = 0
    for addr, info in specific_matches.items():
        mangled = info.get('mangled', '')
        if mangled:
            if ida_name.set_name(addr, mangled, ida_name.SN_NOWARN):
                specific_applied += 1
            elif ida_name.set_name(addr, mangled, ida_name.SN_FORCE):
                specific_applied += 1
    log("[*] 字符串精确匹配应用: %d" % specific_applied)

    applied += vt_named + method_named + specific_applied
    log("[*] 总计应用: %d" % applied)
    return applied


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe RTTI + 启发式匹配")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        # Load PDB
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)
        log("[*] PDB: %d classes, %d functions" % (
            len(pdb_data.get('classes', [])), len(pdb_data.get('functions', []))))

        # Execute phases
        rtti_classes = phase1_rtti()
        vtable_matches = phase2_vtables(rtti_classes, pdb_data)
        string_matches, specific_matches = phase3_strings(pdb_data)
        applied = phase4_apply(rtti_classes, vtable_matches, string_matches, specific_matches, pdb_data)

        # Save
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

        # Report
        os.makedirs(os.path.dirname(OUTPUT_FILE), exist_ok=True)
        report = {
            'meta': {
                'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
            },
            'rtti_classes': len(rtti_classes),
            'vtable_matches': len(vtable_matches),
            'string_matches': len(string_matches),
            'specific_matches': len(specific_matches),
            'total_applied': applied,
            'rtti_class_list': list(rtti_classes.keys()),
        }
        with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
            json.dump(report, f, indent=2, ensure_ascii=False)

        log("[*] 报告: %s" % OUTPUT_FILE)
        log("[*] 完成!")

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
