"""
IDAPython: 强制应用所有全局变量命名和类型 (不限地址范围)

从 call_graph.json 读取 globals，直接 set_name + SetType。
然后重新导出所有反编译。

用法:
  idat.exe -A -S"pal3_fix_globals.py" original/PAL3.exe.i64
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

CALLGRAPH = os.path.join(PROJECT_ROOT, "asm", "pal3", "call_graph.json")
OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
LOG_FILE = os.path.join(LOG_DIR, "pal3_fix_globals_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 全局变量强制标注")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        with open(CALLGRAPH, 'r', encoding='utf-8') as f:
            cg = json.load(f)

        globals_data = cg.get('globals', {})
        til = ida_typeinf.get_idati()

        log("[*] 全局变量总数: %d" % len(globals_data))

        # Phase 1: Rename ALL globals that have a name different from ida_name
        rename_ok = 0
        rename_fail = 0
        type_ok = 0

        for addr_str, info in sorted(globals_data.items()):
            name = info.get('name', '')
            ida_nm = info.get('ida_name', '')
            typ = info.get('type', '')

            if not name:
                continue

            try:
                addr = int(addr_str, 16)
            except ValueError:
                continue

            if not ida_bytes.is_loaded(addr):
                continue

            # Rename if needed
            if name != ida_nm:
                cur = ida_name.get_name(addr) or ""
                need_rename = (
                    cur.startswith("dword_") or cur.startswith("byte_") or
                    cur.startswith("unk_") or cur.startswith("flt_") or
                    cur.startswith("off_") or cur.startswith("word_") or
                    not cur
                )
                if need_rename:
                    clean = name.replace('::', '_').replace(' ', '_')
                    clean = clean.replace('<', '_').replace('>', '_')
                    if ida_name.set_name(addr, clean, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                        rename_ok += 1
                        log("  [+] 0x%08X: %s -> %s" % (addr, cur, clean))
                    else:
                        rename_fail += 1
                        log("  [-] 0x%08X: failed %s -> %s" % (addr, cur, clean))

            # Apply type
            if typ and typ not in ('int', 'DWORD', 'char', ''):
                # Pointer types
                if typ.endswith('*'):
                    base = typ.rstrip('*').strip()
                    # Check if struct exists
                    tinfo = ida_typeinf.tinfo_t()
                    if tinfo.get_named_type(til, base):
                        decl = "%s * %s;" % (base, name.replace('::', '_'))
                    else:
                        decl = "void * %s;" % name.replace('::', '_')
                elif typ == 'float':
                    decl = "float %s;" % name
                elif typ == 'HWND' or typ == 'HINSTANCE':
                    decl = "void * %s;" % name
                elif typ.startswith('char['):
                    decl = "%s %s;" % (typ, name)
                else:
                    decl = None

                if decl and idc.SetType(addr, decl):
                    type_ok += 1

        log("")
        log("[*] 重命名: 成功=%d, 失败=%d" % (rename_ok, rename_fail))
        log("[*] 类型标注: %d" % type_ok)

        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB 已保存")

        # Phase 2: Re-export all
        log("")
        log("[*] 重新导出...")
        os.makedirs(OUTPUT_DIR, exist_ok=True)

        import glob
        old_files = glob.glob(os.path.join(OUTPUT_DIR, "*.json"))
        for f in old_files:
            if os.path.basename(f).startswith('_'):
                continue
            os.remove(f)

        targets = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if not name or name.startswith("nullsub_") or name.startswith("j_"):
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() <= 1:
                continue
            targets.append((ea, name, func.size()))

        targets.sort()
        named = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] 目标: %d (命名: %d)" % (len(targets), named))

        exported = 0
        errors = 0
        t0 = time.time()

        for i, (ea, name, size) in enumerate(targets):
            if (i + 1) % 1000 == 0:
                elapsed = time.time() - t0
                log("  [%d/%d] exported=%d (%.0f f/s)" % (
                    i+1, len(targets), exported, (i+1)/elapsed))

            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    continue
                code = str(cfunc)
                sig = cfunc.type.dstr()
                demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else name

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
            except Exception:
                errors += 1

        elapsed = time.time() - t0
        log("[*] 导出: %d 成功, %d 错误 (%.1fs)" % (exported, errors, elapsed))

        summary = {
            'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
            'binary': 'PAL3.exe',
            'globals_fixed': True,
            'renamed': rename_ok,
            'typed': type_ok,
            'total_targets': len(targets),
            'named_functions': named,
            'exported': exported,
        }
        with open(os.path.join(OUTPUT_DIR, "_export_summary.json"), 'w', encoding='utf-8') as f:
            json.dump(summary, f, indent=2)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 完成!")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write("\n".join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
