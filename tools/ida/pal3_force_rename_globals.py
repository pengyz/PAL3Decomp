"""
IDAPython: 强制重命名全局变量 (跳过 is_loaded 检查)

PAL3.exe 加壳后 .data 大部分 is_loaded=False，但 IDA 仍然有这些地址的引用。
直接用 set_name + MakeDword 来强制标注。

用法:
  idat.exe -A -S"pal3_force_rename_globals.py" original/PAL3.exe.i64
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
LOG_FILE = os.path.join(LOG_DIR, "pal3_force_rename_globals_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 全局变量强制重命名 (跳过 is_loaded)")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        with open(CALLGRAPH, 'r', encoding='utf-8') as f:
            cg = json.load(f)

        globals_data = cg.get('globals', {})
        log("[*] 全局变量: %d" % len(globals_data))

        rename_ok = 0
        rename_skip = 0
        rename_fail = 0

        for addr_str, info in sorted(globals_data.items()):
            name = info.get('name', '')
            ida_nm = info.get('ida_name', '')
            typ = info.get('type', '')

            if not name or name == ida_nm:
                continue

            try:
                addr = int(addr_str, 16)
            except ValueError:
                continue

            # Check current name in IDA
            cur = ida_name.get_name(addr) or ""

            # Only rename if current name is auto-generated
            if cur and not cur.startswith("dword_") and not cur.startswith("byte_") and \
               not cur.startswith("unk_") and not cur.startswith("flt_") and \
               not cur.startswith("off_") and not cur.startswith("word_"):
                rename_skip += 1
                continue

            clean = name.replace('::', '_').replace(' ', '_')
            clean = clean.replace('<', '_').replace('>', '_')

            # Force set name regardless of is_loaded status
            if ida_name.set_name(addr, clean, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                rename_ok += 1
                log("  [+] 0x%08X: %s -> %s" % (addr, cur, clean))
            else:
                # Try alternative: force create the name entry
                idc.set_name(addr, clean, idc.SN_NOWARN | idc.SN_FORCE)
                verify = ida_name.get_name(addr) or ""
                if verify == clean:
                    rename_ok += 1
                    log("  [+] 0x%08X: %s -> %s (via idc)" % (addr, cur, clean))
                else:
                    rename_fail += 1
                    log("  [-] 0x%08X: FAILED %s -> %s (got: %s)" % (addr, cur, clean, verify))

        log("")
        log("[*] 结果: 成功=%d, 跳过=%d, 失败=%d" % (rename_ok, rename_skip, rename_fail))

        # Also apply types where possible
        log("")
        log("[*] 应用类型...")
        til = ida_typeinf.get_idati()
        type_ok = 0

        for addr_str, info in globals_data.items():
            typ = info.get('type', '')
            name = info.get('name', '')
            if not typ or typ in ('int', 'DWORD', 'char', ''):
                continue

            try:
                addr = int(addr_str, 16)
            except ValueError:
                continue

            if typ.endswith('*'):
                base = typ.rstrip('*').strip()
                tinfo = ida_typeinf.tinfo_t()
                if tinfo.get_named_type(til, base):
                    decl = "%s *" % base
                else:
                    decl = "void *"
            elif typ == 'float':
                decl = "float"
            elif typ.startswith('char['):
                decl = typ
            else:
                continue

            if idc.SetType(addr, decl):
                type_ok += 1

        log("[*] 类型标注: %d" % type_ok)

        ida_auto.auto_wait()
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] IDB 已保存")

        # Re-export
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
            nm = ida_name.get_name(ea) or ""
            if not nm or nm.startswith("nullsub_") or nm.startswith("j_"):
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() <= 1:
                continue
            targets.append((ea, nm, func.size()))

        targets.sort()
        named = sum(1 for _, n, _ in targets if not n.startswith("sub_"))
        log("[*] 目标: %d (命名: %d)" % (len(targets), named))

        exported = 0
        errors = 0
        t0 = time.time()

        for i, (ea, nm, size) in enumerate(targets):
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
                demangled = idc.demangle_name(nm, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else nm

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
            'globals_renamed': rename_ok,
            'globals_typed': type_ok,
            'exported': exported,
            'named_functions': named,
        }
        with open(os.path.join(OUTPUT_DIR, "_export_summary.json"), 'w', encoding='utf-8') as f:
            json.dump(summary, f, indent=2)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 全部完成!")

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
