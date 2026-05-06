"""
IDAPython: gbengine.dll 全函数 Hex-Rays 反编译导出

工作流:
1. 从 PE 导出表读取所有导出函数 (已在加载时由 IDA 自动处理)
2. 对所有已命名函数 (非 sub_) 执行 Hex-Rays 反编译
3. 输出 JSON 到 asm/gbengine_ida/ 目录，格式与 fill_stubs 兼容

输出格式 (每函数一个 .json):
{
  "name": "gbActor::Update",
  "address": "0x10003210",
  "size_bytes": 420,
  "signature": "int __thiscall gbActor::Update(gbActor *this, float deltaTime)",
  "decompiled_c": "..."
}
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

OUTPUT_DIR = os.path.join(PROJECT_ROOT, "asm", "gbengine_ida")
LOG_FILE = os.path.join(LOG_DIR, "gbengine_export_log.txt")
SUMMARY_FILE = os.path.join(OUTPUT_DIR, "_export_summary.json")


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA ready - gbengine.dll 反编译导出")

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
                log(f"[*] 清理旧导出文件: {removed} 个")

        os.makedirs(OUTPUT_DIR, exist_ok=True)

        # Collect all named functions (IDA auto-identifies DLL exports)
        targets = []
        for ea in idautils.Functions():
            name = ida_name.get_name(ea) or ""
            if not name:
                continue
            if name.startswith("sub_") or name.startswith("nullsub_"):
                continue
            func = ida_funcs.get_func(ea)
            if func:
                targets.append((ea, name, func.size()))

        log(f"[*] 目标函数: {len(targets)}")

        exported = 0
        errors = 0
        error_samples = []
        t0 = time.time()

        for i, (ea, name, size) in enumerate(targets):
            if (i + 1) % 200 == 0:
                elapsed = time.time() - t0
                rate = (i + 1) / elapsed if elapsed > 0 else 0
                log(f"  [{i+1}/{len(targets)}] exported={exported} errors={errors} ({rate:.0f} f/s)")

            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    if len(error_samples) < 20:
                        error_samples.append(f"  0x{ea:08X} {name} (decompile returned None)")
                    continue

                code = str(cfunc)
                sig = cfunc.type.dstr()

                # Demangle for readable filename
                demangled = idc.demangle_name(name, idc.get_inf_attr(idc.INF_SHORT_DN))
                display_name = demangled if demangled else name

                # Safe filename
                safe_name = display_name.replace('::', '_').replace('<', '_').replace('>', '_')
                safe_name = safe_name.replace('*', '_').replace(' ', '_')
                safe_name = safe_name.replace('?', '_').replace('@', '_')
                safe_name = safe_name.replace('$', '_').replace(',', '_')
                safe_name = safe_name.replace('(', '').replace(')', '')
                if len(safe_name) > 100:
                    safe_name = safe_name[:100]
                filename = f"{safe_name}_{ea:08x}.json"
                filepath = os.path.join(OUTPUT_DIR, filename)

                result = {
                    'name': display_name,
                    'mangled_name': name,
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
                if len(error_samples) < 20:
                    error_samples.append(f"  0x{ea:08X} {name} ({str(e)[:60]})")

        elapsed = time.time() - t0
        log("")
        log("[*] 导出完成!")
        log(f"  目标: {len(targets)}")
        log(f"  导出: {exported}")
        log(f"  错误: {errors}")
        log(f"  耗时: {elapsed:.1f}s")

        if error_samples:
            log("[*] 错误样本:")
            for e in error_samples:
                log(e)

        # Save summary
        summary = {
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
        log(f"[!] 错误: {e}")
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
