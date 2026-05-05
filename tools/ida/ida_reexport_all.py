"""
IDAPython: 结构体导入后重新反编译导出所有已命名函数
"""

import ida_auto
import ida_hexrays
import ida_funcs
import ida_name
import idautils
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3a", "decomp")
LOG_FILE = os.path.join(LOG_DIR, "ida_reexport_log.txt")
SUMMARY_FILE = os.path.join(OUTPUT_DIR, "_export_summary.json")

TEXT_START = 0x00401000
TEXT_END = 0x00558000


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        os.makedirs(OUTPUT_DIR, exist_ok=True)

        # Collect all named functions in .text
        targets = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name and not name.startswith("sub_") and not name.startswith("nullsub_"):
                func = ida_funcs.get_func(ea)
                if func:
                    targets.append((ea, name, func.size()))

        log(f"[*] 目标函数: {len(targets)}")

        exported = 0
        errors = 0
        struct_access = 0
        t0 = time.time()

        for i, (ea, name, size) in enumerate(targets):
            if (i + 1) % 500 == 0:
                elapsed = time.time() - t0
                rate = (i + 1) / elapsed if elapsed > 0 else 0
                log(f"  [{i+1}/{len(targets)}] exported={exported} struct_access={struct_access} errors={errors} ({rate:.0f} f/s)")

            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    continue

                code = str(cfunc)
                sig = cfunc.type.dstr()

                # Check for struct field access
                has_struct = 'this->' in code and ('.' in code or '->' in code)
                if has_struct:
                    struct_access += 1

                # Save to JSON
                safe_name = name.replace('::', '_').replace('<', '_').replace('>', '_')
                safe_name = safe_name.replace('*', '_').replace(' ', '_')
                filename = f"{safe_name}_{ea:08x}.json"
                filepath = os.path.join(OUTPUT_DIR, filename)

                result = {
                    'name': name,
                    'address': f"0x{ea:08X}",
                    'size_bytes': size,
                    'signature': sig,
                    'decompiled_c': code,
                }

                with open(filepath, 'w', encoding='utf-8') as f:
                    json.dump(result, f, indent=2, ensure_ascii=False)

                exported += 1

            except Exception as e:
                errors += 1

        elapsed = time.time() - t0
        log("")
        log("[*] 导出完成!")
        log(f"  导出: {exported}")
        log(f"  有结构体访问: {struct_access}")
        log(f"  错误: {errors}")
        log(f"  耗时: {elapsed:.1f}s")

        # Save summary
        summary = {
            'total_targets': len(targets),
            'exported': exported,
            'with_struct_access': struct_access,
            'errors': errors,
            'elapsed_seconds': round(elapsed, 1),
        }
        with open(SUMMARY_FILE, 'w', encoding='utf-8') as f:
            json.dump(summary, f, indent=2)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        import traceback
        log(traceback.format_exc())

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    try:
        idc.qexit(0)
    except:
        pass


main()
