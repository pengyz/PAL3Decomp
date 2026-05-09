"""
IDAPython: PAL3.exe 名称传播 — 从已知函数向外扩展

策略:
  从已确认的函数出发 (如 CEffCylinder::Create),
  分析其调用的和被调用的函数:
  1. 同类方法传播: Create 调用的未命名函数可能是同类其他方法
  2. vtable 交叉: 已知类的 vtable 中其他条目
  3. 构造函数链: 构造函数通常被 Create 调用
  4. 析构函数链: 被 Release/Destroy 调用的是析构函数

同时执行更广泛的启发式:
  - 搜索所有字符串中包含类名的引用
  - 搜索格式化字符串中的标识符 ("loading %s from %s")
  - 利用 import 表中的函数名 (D3D, Miles, etc.)

运行环境: PAL3.exe.i64
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
import struct
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_propagate_names_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0
DATA_START = 0x00580000
DATA_END = 0x0060C000

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def get_callees(func_ea):
    """Get functions called by func_ea."""
    func = ida_funcs.get_func(func_ea)
    if not func:
        return set()
    callees = set()
    for head in idautils.Heads(func.start_ea, func.end_ea):
        for xref in idautils.CodeRefsFrom(head, 0):
            if xref != func_ea and TEXT_START <= xref < TEXT_END:
                target_func = ida_funcs.get_func(xref)
                if target_func:
                    callees.add(target_func.start_ea)
    return callees


def get_callers(func_ea):
    """Get functions that call func_ea."""
    callers = set()
    for xref in idautils.CodeRefsTo(func_ea, 0):
        caller_func = ida_funcs.get_func(xref)
        if caller_func and caller_func.start_ea != func_ea:
            if TEXT_START <= caller_func.start_ea < TEXT_END:
                callers.add(caller_func.start_ea)
    return callers


def find_vtable_for_class(class_name, text_bytes):
    """
    Find vtable for a class by searching .data for RTTI TypeDescriptor with the class name.
    """
    # Search for the mangled RTTI name
    rtti_name = ".?AV%s@@" % class_name
    data_size = DATA_END - DATA_START
    data_bytes = ida_bytes.get_bytes(DATA_START, data_size)
    if not data_bytes:
        return None

    pos = data_bytes.find(rtti_name.encode('ascii'))
    if pos == -1:
        return None

    td_name_va = DATA_START + pos
    td_addr = td_name_va - 8

    # Find COL referencing this TD
    td_bytes = struct.pack('<I', td_addr)
    # COL has TD at offset +12
    col_pos = 0
    while True:
        col_pos = data_bytes.find(td_bytes, col_pos)
        if col_pos == -1:
            break
        # Check if this could be offset +12 of a COL
        col_start = DATA_START + col_pos - 12
        if ida_bytes.is_loaded(col_start):
            sig = idc.get_wide_dword(col_start)
            if sig == 0:  # Valid COL signature for 32-bit
                # Find vtable referencing this COL
                col_bytes = struct.pack('<I', col_start)
                vt_pos = text_bytes.find(col_bytes)
                if vt_pos == -1:
                    # Also search in .data
                    vt_pos2 = data_bytes.find(col_bytes)
                    if vt_pos2 != -1:
                        vt_addr = DATA_START + vt_pos2 + 4
                        first_entry = idc.get_wide_dword(vt_addr)
                        if TEXT_START <= first_entry < TEXT_END:
                            return vt_addr
                # Search in .rdata too
        col_pos += 1

    return None


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 名称传播")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        # Load PDB
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        # Build class → methods index
        pdb_by_class = {}  # class_name → [func_info, ...]
        pdb_by_name = {}  # full_name → mangled
        for func in pdb_data.get('functions', []):
            name = func.get('name', '')
            mangled = func.get('mangled_name', '')
            if not name or not mangled:
                continue
            pdb_by_name[name] = mangled
            if '::' in name:
                cls = name.split('::')[0]
                if cls not in pdb_by_class:
                    pdb_by_class[cls] = []
                pdb_by_class[cls].append(func)

        log("[*] PDB: %d classes with methods" % len(pdb_by_class))

        # Phase 1: Collect all currently named functions with class context
        log("")
        log("[Phase 1] 收集已知类函数")

        known_class_funcs = {}  # class_name → [(func_ea, method_name), ...]
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name.startswith("sub_") or name.startswith("nullsub_"):
                continue
            # Demangle or parse class::method from name
            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            if demangled and '::' in demangled:
                parts = demangled.split('(')[0]  # Remove params
                if '::' in parts:
                    cls = parts.split('::')[0].strip()
                    method = parts.split('::')[-1].strip()
                    if cls not in known_class_funcs:
                        known_class_funcs[cls] = []
                    known_class_funcs[cls].append((ea, method))

        total_known = sum(len(v) for v in known_class_funcs.values())
        log("[*] 已知类: %d, 已知方法: %d" % (len(known_class_funcs), total_known))

        if known_class_funcs:
            for cls, methods in sorted(known_class_funcs.items())[:10]:
                log("    %s: %s" % (cls, [m for _, m in methods][:5]))

        # Phase 2: For each known class, find neighboring functions
        log("")
        log("[Phase 2] 从已知函数扩展匹配")

        text_bytes = ida_bytes.get_bytes(TEXT_START, TEXT_END - TEXT_START)
        newly_named = 0

        for cls, known_methods in known_class_funcs.items():
            if cls not in pdb_by_class:
                continue

            pdb_methods = pdb_by_class[cls]
            known_method_names = set(m for _, m in known_methods)

            # Get all callees and callers of known methods
            related_unnamed = set()
            for ea, _ in known_methods:
                for callee in get_callees(ea):
                    callee_name = ida_name.get_name(callee) or ""
                    if callee_name.startswith("sub_"):
                        related_unnamed.add(callee)
                for caller in get_callers(ea):
                    caller_name = ida_name.get_name(caller) or ""
                    if caller_name.startswith("sub_"):
                        related_unnamed.add(caller)

            if not related_unnamed:
                continue

            # Try to match related unnamed functions to PDB methods of same class
            unmatched_pdb = [f for f in pdb_methods
                           if f['name'].split('::')[-1] not in known_method_names]

            # For now, just annotate with class hint
            for ea in related_unnamed:
                existing_cmt = idc.get_func_cmt(ea, 0) or ""
                if cls not in existing_cmt:
                    new_cmt = "likely %s method (near %s)" % (cls, ', '.join(known_method_names)[:50])
                    idc.set_func_cmt(ea, new_cmt, 0)

        # Phase 3: Search ALL strings for class names and map to functions
        log("")
        log("[Phase 3] 全局类名字符串搜索")

        data_bytes = ida_bytes.get_bytes(DATA_START, DATA_END - DATA_START)
        if not data_bytes or not text_bytes:
            log("[!] 无法读取段数据")
            return

        # For each PDB class, search for its name in .data strings
        class_string_funcs = {}  # class_name → set of func_eas that reference class name strings

        for cls in list(pdb_by_class.keys()):
            if len(cls) < 4:
                continue
            # Search for class name in .data
            cls_bytes = cls.encode('ascii')
            pos = 0
            str_addrs = set()
            while True:
                pos = data_bytes.find(cls_bytes, pos)
                if pos == -1:
                    break
                str_addrs.add(DATA_START + pos)
                pos += 1

            if not str_addrs:
                continue

            # Find which functions reference these addresses
            funcs = set()
            for str_addr in str_addrs:
                needle = struct.pack('<I', str_addr)
                tpos = 0
                while True:
                    tpos = text_bytes.find(needle, tpos)
                    if tpos == -1:
                        break
                    code_ea = TEXT_START + tpos
                    func = ida_funcs.get_func(code_ea)
                    if func:
                        funcs.add(func.start_ea)
                    tpos += 1

            if funcs:
                # Filter to unnamed functions only
                unnamed = set(ea for ea in funcs
                            if (ida_name.get_name(ea) or "").startswith("sub_"))
                if unnamed:
                    class_string_funcs[cls] = unnamed

        log("[*] 类名字符串引用: %d 个类, %d 个未命名函数" % (
            len(class_string_funcs),
            sum(len(v) for v in class_string_funcs.values())))

        # Phase 4: For classes with few referencing functions, try to match
        log("")
        log("[Phase 4] 类名引用→方法匹配")

        for cls, funcs in class_string_funcs.items():
            pdb_methods = pdb_by_class.get(cls, [])
            if not pdb_methods:
                continue

            # If only 1 unnamed function references this class name
            if len(funcs) == 1:
                func_ea = list(funcs)[0]
                # Annotate with class
                cmt = "references '%s' (PDB: %d methods)" % (cls, len(pdb_methods))
                idc.set_func_cmt(func_ea, cmt, 0)

            # If very few functions and matching count with PDB
            elif len(funcs) <= 3:
                for ea in funcs:
                    cmt = "likely %s (1 of %d referencing funcs)" % (cls, len(funcs))
                    existing_cmt = idc.get_func_cmt(ea, 0) or ""
                    if cls not in existing_cmt:
                        idc.set_func_cmt(ea, cmt, 0)

        # Phase 5: Name import thunks and well-known functions
        log("")
        log("[Phase 5] 统计和保存")

        # Count named functions
        named_count = 0
        unnamed_count = 0
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name.startswith("sub_"):
                unnamed_count += 1
            else:
                named_count += 1

        log("[*] 当前状态: %d 命名, %d 未命名 (总 %d)" % (
            named_count, unnamed_count, named_count + unnamed_count))

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
