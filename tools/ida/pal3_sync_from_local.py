"""
IDAPython: 从本地 BFS 分析结果同步标注到 PAL3.exe IDB

读取 asm/pal3/_sync_to_ida.json，执行:
  Phase 1: 函数重命名 (sub_ -> 语义名)
  Phase 2: 全局变量重命名 + 类型标注
  Phase 3: 全量重新导出 (含 frontier sub_ 函数)

用法:
  idat.exe -A -S"pal3_sync_from_local.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_hexrays
import ida_name
import ida_typeinf
import idautils
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

SYNC_DATA = os.path.join(PROJECT_ROOT, "asm", "pal3", "_sync_to_ida.json")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
LOG_FILE = os.path.join(LOG_DIR, "pal3_sync_from_local_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def phase1_rename_functions(sync):
    """重命名 BFS 中已识别的函数"""
    log("")
    log("=" * 60)
    log("[Phase 1] 函数重命名")
    log("=" * 60)

    renames = sync.get('func_renames', [])
    log("[*] 待重命名: %d" % len(renames))

    ok = 0
    skip = 0
    fail = 0

    for addr_str, name in renames:
        try:
            addr = int(addr_str, 16)
        except (ValueError, TypeError):
            fail += 1
            continue

        if addr < TEXT_START or addr >= TEXT_END:
            skip += 1
            continue

        # Check if function exists at this address
        func = ida_funcs.get_func(addr)
        if not func:
            skip += 1
            continue

        # Get current name
        cur_name = ida_name.get_name(addr) or ""
        if cur_name and not cur_name.startswith("sub_"):
            # Already has a meaningful name, skip
            skip += 1
            continue

        # Sanitize name for IDA
        clean = name.split('(')[0].strip()  # Remove parameters
        clean = clean.replace('::', '_').replace(' ', '_')
        clean = clean.replace('<', '_').replace('>', '_')
        clean = clean.replace('*', 'p').replace('&', 'r')

        if ida_name.set_name(addr, clean, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            ok += 1
            log("  [+] 0x%08X: %s -> %s" % (addr, cur_name, clean))
        else:
            fail += 1

    log("[*] 结果: 成功=%d, 跳过=%d, 失败=%d" % (ok, skip, fail))
    return ok


def phase2_globals(sync):
    """全局变量重命名 + 类型标注"""
    log("")
    log("=" * 60)
    log("[Phase 2] 全局变量标注")
    log("=" * 60)

    renames = sync.get('global_renames', [])
    types = sync.get('global_types', [])
    log("[*] 待重命名: %d, 待标注类型: %d" % (len(renames), len(types)))

    til = ida_typeinf.get_idati()
    rename_ok = 0
    type_ok = 0

    # Rename globals (no address range restriction - let is_loaded check handle it)
    for addr_str, name in renames:
        try:
            addr = int(addr_str, 16)
        except (ValueError, TypeError):
            continue

        if not ida_bytes.is_loaded(addr):
            log("  [!] 0x%08X not loaded: %s" % (addr, name))
            continue

        cur = ida_name.get_name(addr) or ""
        if cur and not cur.startswith("dword_") and not cur.startswith("byte_") and \
           not cur.startswith("unk_") and not cur.startswith("flt_") and \
           not cur.startswith("off_"):
            continue

        clean = name.replace('::', '_').replace(' ', '_')
        clean = clean.replace('<', '_').replace('>', '_')
        if ida_name.set_name(addr, clean, ida_name.SN_NOWARN | ida_name.SN_FORCE):
            rename_ok += 1
            log("  [+] 0x%08X: %s -> %s" % (addr, cur, clean))

    # Apply types
    TYPE_MAP = {
        'void*': 'void *',
        'float': 'float',
        'double': 'double',
        'HINSTANCE': 'void *',
        'HWND': 'void *',
        'char[32]': 'char[32]',
        'char[64]': 'char[64]',
        'char[128]': 'char[128]',
        'char[256]': 'char[256]',
    }

    for addr_str, name, type_str in types:
        try:
            addr = int(addr_str, 16)
        except (ValueError, TypeError):
            continue

        if not ida_bytes.is_loaded(addr):
            continue

        # Map type to IDA-parseable form
        ida_type = type_str
        if type_str in TYPE_MAP:
            ida_type = TYPE_MAP[type_str]
        elif type_str.endswith('*'):
            # Pointer to struct/class
            base = type_str[:-1].strip()
            # Check if struct is defined in IDA
            tinfo = ida_typeinf.tinfo_t()
            if tinfo.get_named_type(til, base):
                ida_type = "%s *" % base
            else:
                ida_type = "void *"  # fallback

        # Try to set type
        decl = "%s %s;" % (ida_type, name.replace('::', '_'))
        if idc.SetType(addr, decl):
            type_ok += 1
        else:
            # Try simpler approach - just the type
            if idc.SetType(addr, ida_type):
                type_ok += 1

    log("[*] 结果: 重命名=%d, 类型标注=%d" % (rename_ok, type_ok))
    return rename_ok + type_ok


def phase3_export_all(sync):
    """全量导出反编译结果 (含 frontier sub_ 函数)"""
    log("")
    log("=" * 60)
    log("[Phase 3] 全量反编译导出")
    log("=" * 60)

    os.makedirs(OUTPUT_DIR, exist_ok=True)

    # Clean old files
    import glob
    old_files = glob.glob(os.path.join(OUTPUT_DIR, "*.json"))
    removed = 0
    for f in old_files:
        if os.path.basename(f).startswith('_'):
            continue
        os.remove(f)
        removed += 1
    if removed:
        log("[*] 清理旧文件: %d" % removed)

    # Collect ALL functions in .text (not just named ones)
    targets = []
    for ea in idautils.Functions(TEXT_START, TEXT_END):
        if ea < TEXT_START or ea >= TEXT_END:
            continue
        name = ida_name.get_name(ea) or ""
        if not name or name.startswith("nullsub_") or name.startswith("j_"):
            continue
        func = ida_funcs.get_func(ea)
        if not func or func.size() == 0:
            continue
        # Skip tiny thunks (1 byte = just ret)
        if func.size() <= 1:
            continue
        targets.append((ea, name, func.size()))

    # Also add frontier addresses that might not be in Functions list
    frontier_addrs = sync.get('frontier_addrs', [])
    frontier_set = set()
    for addr_str in frontier_addrs:
        try:
            frontier_set.add(int(addr_str, 16))
        except (ValueError, TypeError):
            pass

    existing_eas = {ea for ea, _, _ in targets}
    for fa in frontier_set:
        if fa not in existing_eas and TEXT_START <= fa < TEXT_END:
            func = ida_funcs.get_func(fa)
            if func and func.size() > 1:
                name = ida_name.get_name(fa) or ("sub_%X" % fa)
                targets.append((fa, name, func.size()))

    targets.sort(key=lambda x: x[0])
    named = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
    log("[*] 目标: %d (命名: %d, sub_: %d)" % (len(targets), named, len(targets) - named))

    exported = 0
    errors = 0
    error_samples = []
    t0 = time.time()

    for i, (ea, name, size) in enumerate(targets):
        if (i + 1) % 500 == 0:
            elapsed = time.time() - t0
            rate = (i + 1) / elapsed if elapsed > 0 else 0
            log("  [%d/%d] exported=%d errors=%d (%.0f f/s)" % (
                i + 1, len(targets), exported, errors, rate))

        try:
            cfunc = ida_hexrays.decompile(ea)
            if not cfunc:
                errors += 1
                if len(error_samples) < 10:
                    error_samples.append("0x%08X %s (None)" % (ea, name))
                continue

            code = str(cfunc)
            sig = cfunc.type.dstr()

            # Demangled name for display
            demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
            display_name = demangled if demangled else name

            # Safe filename
            safe = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
            safe = safe.replace('*', '_').replace(' ', '_').replace('?', '_')
            safe = safe.replace('@', '_').replace('$', '_').replace(',', '_')
            safe = safe.replace('(', '').replace(')', '').replace('/', '_')
            safe = safe.replace('"', '').replace("'", '').replace('\\', '_')
            while '__' in safe:
                safe = safe.replace('__', '_')
            safe = safe.strip('_')
            if len(safe) > 100:
                safe = safe[:100]
            filename = '%s_%08x.json' % (safe, ea)

            result = {
                'name': display_name,
                'address': '0x%08X' % ea,
                'size_bytes': size,
                'signature': sig,
                'decompiled_c': code,
            }

            with open(os.path.join(OUTPUT_DIR, filename), 'w', encoding='utf-8') as f:
                json.dump(result, f, indent=2, ensure_ascii=False)

            exported += 1

        except Exception as e:
            errors += 1
            if len(error_samples) < 10:
                error_samples.append("0x%08X %s (%s)" % (ea, name, str(e)[:50]))

    elapsed = time.time() - t0
    log("")
    log("[*] 导出完成: %d 成功, %d 错误 (%.1fs)" % (exported, errors, elapsed))

    if error_samples:
        log("[*] 错误样本:")
        for s in error_samples:
            log("  " + s)

    # Summary
    summary = {
        'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
        'binary': 'PAL3.exe',
        'sync_applied': True,
        'total_targets': len(targets),
        'named_functions': named,
        'exported': exported,
        'errors': errors,
        'elapsed_seconds': round(elapsed, 1),
    }
    with open(os.path.join(OUTPUT_DIR, "_export_summary.json"), 'w', encoding='utf-8') as f:
        json.dump(summary, f, indent=2)

    return exported


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 本地标注同步 + 全量导出")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        if not os.path.exists(SYNC_DATA):
            log("[!] 同步数据不存在: %s" % SYNC_DATA)
            log("    请先运行本地脚本生成 _sync_to_ida.json")
            return

        with open(SYNC_DATA, 'r', encoding='utf-8') as f:
            sync = json.load(f)

        log("[*] 同步数据: 函数=%d, 全局变量=%d+%d, frontier=%d" % (
            len(sync.get('func_renames', [])),
            len(sync.get('global_renames', [])),
            len(sync.get('global_types', [])),
            len(sync.get('frontier_addrs', [])),
        ))

        # Phase 1: Rename functions
        phase1_rename_functions(sync)
        ida_auto.auto_wait()

        # Phase 2: Global variables
        phase2_globals(sync)
        ida_auto.auto_wait()

        # Save after annotations
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB 已保存 (标注完成)")

        # Phase 3: Full export
        phase3_export_all(sync)
        idc.save_database(idc.get_idb_path(), 0)

        log("")
        log("[*] 全部完成!")

    except Exception as e:
        log("[!] 致命错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
