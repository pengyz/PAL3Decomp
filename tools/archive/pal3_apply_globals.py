"""
IDAPython: 将 PAL3A 全局变量名应用到 PAL3.exe IDB

运行环境: PAL3.exe IDB
输入: asm/pal3a/globals_export.json

PAL3.exe 和 PAL3A.exe 共享相同的 .rdata/.data 布局 (0x56A000-0x60C000)。
在此范围内的全局变量可以直接命名。

用法:
  idat.exe -A -S"pal3_apply_globals.py" PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_name
import ida_typeinf
import idc
import json
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

GLOBALS_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3a", "globals_export.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_apply_globals_log.txt")

# PAL3.exe section ranges (from PE analysis)
PAL3_TEXT_START = 0x00401000
PAL3_TEXT_END = 0x005695D0
PAL3_RDATA_START = 0x0056A000
PAL3_RDATA_END = 0x0057F178
PAL3_DATA_START = 0x00580000
PAL3_DATA_END = 0x0060C000  # Conservative: only first 0x8C000 of .data is shared


def is_valid_pal3_addr(addr):
    """Check if address falls within analyzable PAL3.exe sections"""
    if PAL3_RDATA_START <= addr < PAL3_RDATA_END:
        return True
    if PAL3_DATA_START <= addr < PAL3_DATA_END:
        return True
    return False


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 全局变量命名")

        if not os.path.exists(GLOBALS_FILE):
            log("[!] 找不到 globals 文件: %s" % GLOBALS_FILE)
            return

        log("[*] 加载: %s" % GLOBALS_FILE)
        with open(GLOBALS_FILE, 'r', encoding='utf-8') as f:
            globals_data = json.load(f)

        # globals_export.json format: list of {name, address, type, section, ...}
        if isinstance(globals_data, dict):
            globals_list = globals_data.get('globals', globals_data.get('variables', []))
        elif isinstance(globals_data, list):
            globals_list = globals_data
        else:
            log("[!] 未知格式")
            return

        log("[*] 全局变量总数: %d" % len(globals_list))

        applied = 0
        skipped_range = 0
        skipped_conflict = 0
        skipped_other = 0

        for g in globals_list:
            name = g.get('name', '')
            addr_str = g.get('address', '')
            gtype = g.get('type', '')

            if not name or not addr_str:
                skipped_other += 1
                continue

            # Parse address
            try:
                addr = int(addr_str, 16) if isinstance(addr_str, str) else int(addr_str)
            except (ValueError, TypeError):
                skipped_other += 1
                continue

            # Only apply to valid PAL3.exe address range
            if not is_valid_pal3_addr(addr):
                skipped_range += 1
                continue

            # Check if address has data in IDB
            if not ida_bytes.is_loaded(addr):
                skipped_other += 1
                continue

            # Check for existing name
            existing = ida_name.get_name(addr)
            if existing and not existing.startswith("dword_") and \
               not existing.startswith("byte_") and \
               not existing.startswith("unk_") and \
               not existing.startswith("off_"):
                # Already has a meaningful name
                skipped_conflict += 1
                continue

            # Apply name
            # Clean name for IDA (remove :: prefix issues, etc.)
            clean_name = name.replace('::', '_').replace('<', '_').replace('>', '_')
            clean_name = clean_name.replace(' ', '_').replace('*', 'p')

            if ida_name.set_name(addr, clean_name, ida_name.SN_NOWARN | ida_name.SN_FORCE):
                applied += 1

                # Try to apply type if available
                if gtype:
                    til = ida_typeinf.get_idati()
                    tinfo = ida_typeinf.tinfo_t()
                    if ida_typeinf.parse_decl(tinfo, til, gtype + ' x;', ida_typeinf.PT_VAR):
                        ida_typeinf.apply_tinfo(addr, tinfo, ida_typeinf.TINFO_DEFINITE)
            else:
                skipped_other += 1

        log("")
        log("[*] 完成!")
        log("    应用: %d" % applied)
        log("    超出范围: %d" % skipped_range)
        log("    已有名称: %d" % skipped_conflict)
        log("    其他跳过: %d" % skipped_other)

        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))


if __name__ == '__main__':
    main()
