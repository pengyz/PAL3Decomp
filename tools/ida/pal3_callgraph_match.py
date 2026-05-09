"""
IDAPython: 启发式调用链匹配 — 从 WinMain 出发分析 PAL3.exe

策略:
  1. 找到 PAL3.exe 的 WinMain (entry point → __tmainCRTStartup → WinMain)
  2. 递归提取调用图 (BFS)
  3. 对每个函数提取特征:
     - 调用约定 (__thiscall/__cdecl/__stdcall)
     - 参数数量
     - 引用的字符串常量
     - 调用的其他函数数量
     - 被调用次数
     - 函数大小
  4. 与 PAL3A PDB 函数列表匹配:
     - 字符串引用 (最强特征)
     - 调用约定 + 参数特征
     - 结构性匹配 (调用图拓扑)

输出:
  - asm/pal3/callgraph_matches.json (匹配结果)
  - IDB 中直接重命名高置信度匹配

运行环境: PAL3.exe.i64 (已导入类型后)
用法:
  idat.exe -A -S"pal3_callgraph_match.py" original/PAL3.exe.i64
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
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
OUTPUT_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "callgraph_matches.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_callgraph_match_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0
RDATA_START = 0x0056A000
RDATA_END = 0x0057F178

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def get_string_refs(func_ea, func_end):
    """Get all string references from a function."""
    strings = []
    for head in idautils.Heads(func_ea, func_end):
        for xref in idautils.DataRefsFrom(head):
            if RDATA_START <= xref < RDATA_END:
                s = idc.get_strlit_contents(xref, -1, idc.STRTYPE_C)
                if s:
                    try:
                        strings.append(s.decode('utf-8', errors='replace'))
                    except:
                        strings.append(s.decode('latin-1'))
    return strings


def get_callees(func_ea, func_end):
    """Get all functions called by this function."""
    callees = set()
    for head in idautils.Heads(func_ea, func_end):
        for xref in idautils.CodeRefsFrom(head, 0):
            if xref != func_ea and TEXT_START <= xref < TEXT_END:
                callee_func = ida_funcs.get_func(xref)
                if callee_func:
                    callees.add(callee_func.start_ea)
    return callees


def get_callers(func_ea):
    """Get all functions that call this function."""
    callers = set()
    for xref in idautils.CodeRefsTo(func_ea, 0):
        caller_func = ida_funcs.get_func(xref)
        if caller_func and caller_func.start_ea != func_ea:
            callers.add(caller_func.start_ea)
    return callers


def extract_function_features(ea):
    """Extract matching features for a function."""
    func = ida_funcs.get_func(ea)
    if not func:
        return None

    func_end = func.end_ea
    size = func.size()
    name = ida_name.get_name(ea) or ""

    # Get function type info
    func_type = idc.get_type(ea) or ""

    # Calling convention
    flags = func.flags
    cc = "unknown"
    if "__thiscall" in func_type:
        cc = "__thiscall"
    elif "__stdcall" in func_type:
        cc = "__stdcall"
    elif "__fastcall" in func_type:
        cc = "__fastcall"
    else:
        cc = "__cdecl"

    # String references
    strings = get_string_refs(ea, func_end)

    # Callees and callers
    callees = get_callees(ea, func_end)
    callers = get_callers(ea)

    return {
        'addr': ea,
        'size': size,
        'name': name,
        'cc': cc,
        'type': func_type,
        'strings': strings,
        'num_callees': len(callees),
        'num_callers': len(callers),
        'callees': list(callees),
        'callers': list(callers),
    }


def find_winmain():
    """Find WinMain by tracing from entry point."""
    entry = idc.get_inf_attr(idc.INF_START_EA)
    log("[*] Entry point: 0x%08X" % entry)

    # In MSVC, entry → __tmainCRTStartup which calls WinMain
    # WinMain signature: int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
    # Look for a function called with 4 args from the startup code

    # Alternative: search for "WinMain" name
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        name = ida_name.get_name(ea) or ""
        if "WinMain" in name or "wWinMain" in name:
            log("[*] Found WinMain: 0x%08X (%s)" % (ea, name))
            return ea

    # Heuristic: trace from entry to find the main function
    # CRT startup typically calls main/WinMain after setting up
    func = ida_funcs.get_func(entry)
    if func:
        callees = get_callees(func.start_ea, func.end_ea)
        for callee in callees:
            name = ida_name.get_name(callee) or ""
            if "main" in name.lower():
                log("[*] Found main-like: 0x%08X (%s)" % (callee, name))
                return callee

    log("[!] WinMain not found, using entry point")
    return entry


def build_pal3a_string_index(pdb_data):
    """
    Build index: string literal → list of PAL3A function names that reference it.
    Uses the decompiled output to find string references.
    """
    # We don't have direct string-ref data from PDB, but we can use function names
    # and class structure to build a matching index.
    # For now, use the function name/signature as the primary matching criterion.
    funcs_by_name = {}
    for func in pdb_data['functions']:
        name = func.get('name', '')
        mangled = func.get('mangled_name', '')
        if name and mangled:
            funcs_by_name[name] = mangled
    return funcs_by_name


def match_by_strings(pal3_features, pal3a_decomp_dir):
    """
    Match PAL3 functions to PAL3A by comparing string references.
    Load PAL3A decompiled JSONs and extract their string constants.
    """
    # Build PAL3A string → function mapping from decompiled output
    pal3a_string_map = {}  # string → [(mangled_name, func_name)]

    if not os.path.exists(pal3a_decomp_dir):
        return {}

    decomp_files = [f for f in os.listdir(pal3a_decomp_dir)
                    if f.endswith('.json') and not f.startswith('_')]

    log("[*] 加载 PAL3A 反编译数据 (%d 文件)..." % len(decomp_files))

    for fname in decomp_files:
        filepath = os.path.join(pal3a_decomp_dir, fname)
        try:
            with open(filepath, 'r', encoding='utf-8') as f:
                data = json.load(f)
            code = data.get('decompiled_c', '')
            mangled = data.get('mangled_name', '')
            func_name = data.get('name', '')

            # Extract string literals from decompiled code
            import re
            strings = re.findall(r'"([^"]{3,})"', code)
            for s in strings:
                if s not in pal3a_string_map:
                    pal3a_string_map[s] = []
                pal3a_string_map[s].append((mangled, func_name))
        except:
            continue

    log("[*] PAL3A 字符串索引: %d 个唯一字符串" % len(pal3a_string_map))

    # Match PAL3 functions by their string refs
    matches = {}
    for feat in pal3_features:
        if not feat['strings']:
            continue
        if not feat['name'].startswith('sub_'):
            continue

        # Find PAL3A functions that share strings
        candidates = {}
        for s in feat['strings']:
            if s in pal3a_string_map:
                for mangled, func_name in pal3a_string_map[s]:
                    if mangled not in candidates:
                        candidates[mangled] = {'name': func_name, 'shared_strings': []}
                    candidates[mangled]['shared_strings'].append(s)

        if not candidates:
            continue

        # Rank by number of shared strings
        ranked = sorted(candidates.items(), key=lambda x: len(x[1]['shared_strings']), reverse=True)
        best_mangled, best_info = ranked[0]
        shared_count = len(best_info['shared_strings'])

        # Only accept if:
        # 1. Multiple shared strings (strong signal), OR
        # 2. Single shared string that's unique (only one function uses it)
        is_unique = len(pal3a_string_map.get(best_info['shared_strings'][0], [])) == 1

        if shared_count >= 2 or (shared_count == 1 and is_unique):
            confidence = 'high' if shared_count >= 3 else ('medium' if shared_count >= 2 or is_unique else 'low')
            matches[feat['addr']] = {
                'mangled': best_mangled,
                'name': best_info['name'],
                'shared_strings': best_info['shared_strings'][:5],
                'confidence': confidence,
            }

    return matches


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 启发式调用链匹配")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        # Load PDB data
        if not os.path.exists(PDB_EXPORT):
            log("[!] PDB 数据不存在: %s" % PDB_EXPORT)
            return

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        log("[*] PDB 函数: %d" % len(pdb_data['functions']))

        # Phase 1: Find WinMain and trace call graph
        winmain = find_winmain()

        # Phase 2: Extract features for all functions (not just reachable from WinMain)
        log("[*] 提取所有函数特征...")
        t0 = time.time()
        all_features = []
        unnamed_count = 0

        for ea in idautils.Functions(TEXT_START, TEXT_END):
            if ea < TEXT_START or ea >= TEXT_END:
                continue
            feat = extract_function_features(ea)
            if feat:
                all_features.append(feat)
                if feat['name'].startswith('sub_'):
                    unnamed_count += 1

        log("[*] 函数特征: %d (未命名: %d) (%.1fs)" % (
            len(all_features), unnamed_count, time.time() - t0))

        # Phase 3: String-based matching
        log("")
        log("[Phase 3] 字符串引用匹配")

        # Check for PAL3A decompiled output
        pal3a_decomp_dir = os.path.join(PROJECT_ROOT, "asm", "pal3a", "decomp")
        if not os.path.exists(pal3a_decomp_dir):
            # Try alternative path
            pal3a_decomp_dir = os.path.join(PROJECT_ROOT, "asm", "pal3a")

        string_matches = match_by_strings(all_features, pal3a_decomp_dir)
        log("[*] 字符串匹配: %d 函数" % len(string_matches))

        # Phase 4: Apply high-confidence matches
        log("")
        log("[Phase 4] 应用匹配结果")

        applied = 0
        high_conf = 0
        med_conf = 0

        for addr, match_info in string_matches.items():
            confidence = match_info['confidence']
            if confidence == 'high':
                high_conf += 1
            elif confidence == 'medium':
                med_conf += 1

            mangled = match_info['mangled']

            # Apply name (high and medium confidence)
            if confidence in ('high', 'medium'):
                if ida_name.set_name(addr, mangled, ida_name.SN_NOWARN):
                    applied += 1
                elif ida_name.set_name(addr, mangled, ida_name.SN_FORCE):
                    applied += 1

        log("[*] 高置信: %d, 中置信: %d" % (high_conf, med_conf))
        log("[*] 应用名称: %d" % applied)

        # Save
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

        # Write report
        os.makedirs(os.path.dirname(OUTPUT_FILE), exist_ok=True)
        report = {
            'meta': {
                'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
                'total_functions': len(all_features),
                'unnamed_functions': unnamed_count,
            },
            'stats': {
                'string_matches': len(string_matches),
                'high_confidence': high_conf,
                'medium_confidence': med_conf,
                'applied': applied,
            },
            'matches': [
                {
                    'addr': '0x%08X' % addr,
                    'mangled': info['mangled'],
                    'name': info['name'],
                    'confidence': info['confidence'],
                    'shared_strings': info['shared_strings'],
                }
                for addr, info in sorted(string_matches.items())
            ],
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
