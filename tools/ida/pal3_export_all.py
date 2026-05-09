"""
IDAPython: PAL3.exe 全函数 Hex-Rays 反编译导出

运行环境: PAL3.exe IDB (已导入类型 + 应用 FLIRT 签名)
输出: asm/pal3/ 目录，每个函数一个 JSON 文件

输出格式:
{
  "name": "Scene::Update",
  "mangled_name": "?Update@Scene@@UAEXXZ",
  "address": "0x00456F40",
  "size_bytes": 92,
  "signature": "void __thiscall Scene::Update(Scene *this)",
  "decompiled_c": "..."
}

用法:
  idat.exe -A -S"pal3_export_all.py" PAL3.exe.i64
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
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3")
LOG_FILE = os.path.join(LOG_DIR, "pal3_export_log.txt")
SUMMARY_FILE = os.path.join(OUTPUT_DIR, "_export_summary.json")

# PAL3.exe .text section range
TEXT_START = 0x00401000
TEXT_END = 0x005695D0


def safe_filename(display_name, ea):
    """Create a filesystem-safe filename from function name + address"""
    safe = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
    safe = safe.replace('*', '_').replace(' ', '_')
    safe = safe.replace('?', '_').replace('@', '_')
    safe = safe.replace('$', '_').replace(',', '_')
    safe = safe.replace('(', '').replace(')', '')
    safe = safe.replace('/', '_').replace('\\', '_')
    safe = safe.replace('"', '').replace("'", '')
    # Remove consecutive underscores
    while '__' in safe:
        safe = safe.replace('__', '_')
    safe = safe.strip('_')
    if len(safe) > 100:
        safe = safe[:100]
    return '%s_%08x.json' % (safe, ea)


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA ready - PAL3.exe 反编译导出")
        log("[*] .text range: 0x%08X - 0x%08X" % (TEXT_START, TEXT_END))

        # Clean old export files
        if os.path.exists(OUTPUT_DIR):
            import glob
            old_files = glob.glob(os.path.join(OUTPUT_DIR, "*.json"))
            removed = 0
            for old_f in old_files:
                if os.path.basename(old_f).startswith('_'):
                    continue
                os.remove(old_f)
                removed += 1
            if removed:
                log("[*] 清理旧导出文件: %d 个" % removed)

        os.makedirs(OUTPUT_DIR, exist_ok=True)

        # Collect functions in .text section
        targets = []
        named_count = 0
        sub_count = 0

        for ea in idautils.Functions(TEXT_START, TEXT_END):
            if ea < TEXT_START or ea >= TEXT_END:
                continue
            name = ida_name.get_name(ea) or ""
            if not name:
                continue
            # Skip compiler-generated stubs
            if name.startswith("nullsub_") or name.startswith("j_"):
                continue
            func = ida_funcs.get_func(ea)
            if not func or func.size() == 0:
                continue

            is_named = not name.startswith("sub_")
            if is_named:
                named_count += 1
            else:
                sub_count += 1
            targets.append((ea, name, func.size(), is_named))

        log("[*] 目标函数: %d (命名: %d, sub_: %d)" % (
            len(targets), named_count, sub_count))

        exported = 0
        errors = 0
        error_samples = []
        t0 = time.time()

        for i, (ea, name, size, is_named) in enumerate(targets):
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
                        error_samples.append(
                            "  0x%08X %s (decompile returned None)" % (ea, name))
                    continue

                code = str(cfunc)
                sig = cfunc.type.dstr()

                # Demangle for readable display name
                demangled = idc.demangle_name(
                    name, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else name

                filename = safe_filename(display_name, ea)
                filepath = os.path.join(OUTPUT_DIR, filename)

                result = {
                    'name': display_name,
                    'mangled_name': name,
                    'address': '0x%08X' % ea,
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
                    error_samples.append(
                        "  0x%08X %s (%s)" % (ea, name, str(e)[:60]))

        elapsed = time.time() - t0
        log("")
        log("[*] 导出完成!")
        log("  目标: %d" % len(targets))
        log("  导出: %d" % exported)
        log("  命名函数: %d" % named_count)
        log("  未命名(sub_): %d" % sub_count)
        log("  错误: %d" % errors)
        log("  耗时: %.1fs" % elapsed)

        if error_samples:
            log("[*] 错误样本:")
            for e in error_samples:
                log(e)

        # Size distribution
        sizes = [s for _, _, s, _ in targets]
        buckets = [0, 32, 64, 128, 256, 512, 1024, float('inf')]
        log("[*] 函数大小分布:")
        for i in range(len(buckets) - 1):
            count = sum(1 for s in sizes if buckets[i] <= s < buckets[i + 1])
            label = "%d-%d" % (buckets[i], buckets[i + 1]) if buckets[i + 1] != float('inf') else "%d+" % buckets[i]
            log("    %8s bytes: %d" % (label, count))

        # Save summary
        summary = {
            'total_targets': len(targets),
            'named_functions': named_count,
            'unnamed_functions': sub_count,
            'exported': exported,
            'errors': errors,
            'elapsed_seconds': round(elapsed, 1),
            'text_start': '0x%08X' % TEXT_START,
            'text_end': '0x%08X' % TEXT_END,
        }
        with open(SUMMARY_FILE, 'w', encoding='utf-8') as f:
            json.dump(summary, f, indent=2)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
