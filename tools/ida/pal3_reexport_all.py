"""
IDAPython: PAL3.exe 反编译导出 — 导出所有已命名函数的 Hex-Rays 反编译结果

输出: asm/pal3/decomp/*.json
运行: idat.exe -A -S"pal3_reexport_all.py" original/PAL3.exe.i64
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

OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3", "decomp")
LOG_FILE = os.path.join(LOG_DIR, "pal3_reexport_log.txt")
SUMMARY_FILE = os.path.join(OUTPUT_DIR, "_export_summary.json")

TEXT_START = 0x00401000
TEXT_END = 0x005695D0


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 反编译导出")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

        # Clean old export files
        if os.path.exists(OUTPUT_DIR):
            import glob
            old_files = glob.glob(os.path.join(OUTPUT_DIR, "*.json"))
            for old_f in old_files:
                if os.path.basename(old_f).startswith('_'):
                    continue
                os.remove(old_f)
            log("[*] 清理旧导出文件: %d 个" % len(old_files))

        os.makedirs(OUTPUT_DIR, exist_ok=True)

        # Collect ALL named functions in .text
        targets = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            name = ida_name.get_name(ea) or ""
            if name and not name.startswith("sub_") and not name.startswith("nullsub_"):
                func = ida_funcs.get_func(ea)
                if func:
                    targets.append((ea, name, func.size()))

        log("[*] 目标函数: %d" % len(targets))

        exported = 0
        errors = 0
        error_samples = []
        t0 = time.time()

        for i, (ea, name, size) in enumerate(targets):
            if (i + 1) % 200 == 0:
                elapsed = time.time() - t0
                rate = (i + 1) / elapsed if elapsed > 0 else 0
                log("  [%d/%d] exported=%d errors=%d (%.0f f/s)" % (
                    i + 1, len(targets), exported, errors, rate))

            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    if len(error_samples) < 20:
                        error_samples.append("  0x%08X %s (decompile returned None)" % (ea, name))
                    continue

                code = str(cfunc)
                sig = cfunc.type.dstr()

                # Sanitize filename
                safe_name = name.replace('::', '_').replace('<', '_').replace('>', '_')
                safe_name = safe_name.replace('*', '_').replace(' ', '_')
                safe_name = safe_name.replace('?', '_').replace('@', '_')
                safe_name = safe_name.replace('$', '_').replace(',', '_')
                if len(safe_name) > 100:
                    safe_name = safe_name[:100]
                filename = "%s_%08x.json" % (safe_name, ea)
                filepath = os.path.join(OUTPUT_DIR, filename)

                result = {
                    'name': name,
                    'address': "0x%08X" % ea,
                    'size_bytes': size,
                    'signature': sig,
                    'decompiled_c': code,
                }

                with open(filepath, 'w', encoding='utf-8') as f:
                    json.dump(result, f, indent=2, ensure_ascii=False)

                exported += 1

            except Exception as e:
                errors += 1
                if len(error_samples) < 20:
                    error_samples.append("  0x%08X %s (%s)" % (ea, name, str(e)[:60]))

        elapsed = time.time() - t0
        log("")
        log("[*] 导出完成!")
        log("  导出: %d" % exported)
        log("  错误: %d" % errors)
        log("  耗时: %.1fs" % elapsed)

        if error_samples:
            log("[*] 错误样本:")
            for e in error_samples:
                log(e)

        # Save summary
        summary = {
            'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
            'binary': 'PAL3.exe',
            'total_targets': len(targets),
            'exported': exported,
            'errors': errors,
            'elapsed_seconds': round(elapsed, 1),
        }
        with open(SUMMARY_FILE, 'w', encoding='utf-8') as f:
            json.dump(summary, f, indent=2)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
