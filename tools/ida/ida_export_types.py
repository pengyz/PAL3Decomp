"""
IDAPython: 导出 IDA Local Types 为 C 头文件
用于备份手动修正后的类型定义，可重新导入恢复。

用法:
  idat.exe -A -S"ida_export_types.py" PAL3A.exe.i64

输出:
  tools/ida/pal3a_types_exported.h
"""

import ida_auto
import ida_typeinf
import idc
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

OUTPUT_FILE = os.path.join(SCRIPT_DIR, "pal3a_types_exported.h")
LOG_FILE = os.path.join(LOG_DIR, "ida_export_types_log.txt")


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        til = ida_typeinf.get_idati()
        count = ida_typeinf.get_ordinal_qty(til)
        log(f"[*] Local Types 数量: {count}")

        lines = []
        lines.append("// PAL3A IDA Local Types Export")
        lines.append("// Auto-generated - do not edit directly")
        lines.append(f"// Total types: {count}")
        lines.append("")
        lines.append("#pragma pack(push, 1)")
        lines.append("")

        exported = 0
        for ordinal in range(1, count + 1):
            tif = ida_typeinf.tinfo_t()
            if tif.get_numbered_type(til, ordinal):
                name = tif.get_type_name()
                if not name:
                    continue
                # Skip compiler internal types
                if name.startswith('$') or name.startswith('_'):
                    continue

                decl = tif.dstr()
                if not decl:
                    continue

                # Get the full C declaration
                c_str = ""
                if tif.is_struct():
                    c_str = idc.print_decls(name, idc.PDF_DEF_BASE)
                elif tif.is_enum():
                    c_str = idc.print_decls(name, idc.PDF_DEF_BASE)
                elif tif.is_typedef():
                    c_str = f"typedef {decl} {name};"

                if c_str:
                    lines.append(c_str)
                    lines.append("")
                    exported += 1

        lines.append("#pragma pack(pop)")

        log(f"[*] 导出: {exported} 个类型定义")

        os.makedirs(os.path.dirname(OUTPUT_FILE), exist_ok=True)
        with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
            f.write('\n'.join(lines))

        log(f"[*] 已保存: {OUTPUT_FILE}")

    except Exception as e:
        log(f"[!] 错误: {e}")
        import traceback
        log(traceback.format_exc())

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    import builtins
    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
