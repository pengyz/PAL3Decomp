"""
IDAPython: 清除所有通过 PDB 管线贴上的错误函数名

将所有非 IDA 原始分析产生的函数名恢复为 sub_XXXXXX。
保留: sub_, nullsub_, j_, 以及 IDA 自动识别的库函数名。
"""

import ida_auto
import ida_funcs
import ida_name
import idautils
import idc
import os
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA ready - 清除 PDB 管线贴上的名称")

        # Collect all named functions
        total = 0
        cleared = 0
        kept = 0

        for ea in idautils.Functions():
            name = ida_name.get_name(ea) or ""
            if not name:
                continue
            total += 1

            # Keep IDA auto-names
            if name.startswith("sub_") or name.startswith("nullsub_"):
                kept += 1
                continue

            # Keep thunk jumps
            if name.startswith("j_"):
                kept += 1
                continue

            # Keep library functions identified by IDA (FLIRT)
            flags = idc.get_func_attr(ea, idc.FUNCATTR_FLAGS)
            if flags != -1 and (flags & 0x4):  # FUNC_LIB
                kept += 1
                continue

            # Keep known Windows API / CRT functions
            if name.startswith("_") and not name.startswith("__"):
                # Likely CRT function like _sprintf, _fopen etc
                kept += 1
                continue

            # Keep imports
            if ida_name.get_name_ea(0, name) != ea:
                pass  # not an import name conflict

            # Clear everything else - these are from our PDB pipeline
            ida_name.set_name(ea, "", ida_name.SN_NOWARN)
            cleared += 1

            if cleared <= 20:
                log(f"    [CLEAR] 0x{ea:08X} {name}")

        log(f"\n[*] 完成:")
        log(f"    总函数: {total}")
        log(f"    清除: {cleared}")
        log(f"    保留: {kept}")

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    log_path = os.path.join(LOG_DIR, "ida_clear_pdb_names_log.txt")
    with open(log_path, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
