"""
IDAPython: 按 PDB 地址导出所有可反编译的函数（包括 IDA 中未命名的）
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

PDB_EXPORT = r"D:\workspace\project-x\asm\pal3a\pdb_export.json"
OUTPUT_DIR = r"D:\workspace\project-x\asm\pal3a\decomp"
LOG_FILE = r"D:\workspace\project-x\tools\fulldump\ida_export_by_addr_log.txt"

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

        # Load PDB addresses
        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb = json.load(f)

        pdb_by_addr = {}
        for func in pdb['functions']:
            addr_str = func.get('address', '')
            name = func.get('name', '')
            if addr_str and name:
                try:
                    addr = int(addr_str, 16)
                    if TEXT_START <= addr < TEXT_END:
                        pdb_by_addr[addr] = name
                except ValueError:
                    pass

        log(f"[*] PDB .text 函数: {len(pdb_by_addr)}")

        # Check which PDB addresses don't have a decomp file yet
        existing = set()
        for f in os.listdir(OUTPUT_DIR):
            if f.endswith('.json') and not f.startswith('_'):
                # Extract address from filename
                parts = f.replace('.json', '').split('_')
                if parts:
                    try:
                        addr = int(parts[-1], 16)
                        existing.add(addr)
                    except ValueError:
                        pass

        missing = {addr: name for addr, name in pdb_by_addr.items() if addr not in existing}
        log(f"[*] 已有反编译: {len(existing)}")
        log(f"[*] 需要补充导出: {len(missing)}")

        if not missing:
            log("[*] 无需补充")
            return

        exported = 0
        errors = 0
        struct_access = 0
        t0 = time.time()

        sorted_addrs = sorted(missing.keys())
        total = len(sorted_addrs)

        for i, ea in enumerate(sorted_addrs):
            if (i + 1) % 200 == 0:
                elapsed = time.time() - t0
                rate = (i + 1) / elapsed if elapsed > 0 else 0
                log(f"  [{i+1}/{total}] exported={exported} errors={errors} ({rate:.0f} f/s)")

            # Check if IDA has a function at this address
            func = ida_funcs.get_func(ea)
            if not func:
                errors += 1
                continue

            pdb_name = missing[ea]

            try:
                cfunc = ida_hexrays.decompile(ea)
                if not cfunc:
                    errors += 1
                    continue

                code = str(cfunc)
                sig = cfunc.type.dstr()

                has_struct = 'this->' in code
                if has_struct:
                    struct_access += 1

                # Save using PDB name
                safe_name = pdb_name.replace('::', '_').replace('<', '_').replace('>', '_')
                safe_name = safe_name.replace('*', '_').replace(' ', '_').replace('~', 'dtor_')
                filename = f"{safe_name}_{ea:08x}.json"
                filepath = os.path.join(OUTPUT_DIR, filename)

                result = {
                    'name': pdb_name,
                    'address': f"0x{ea:08X}",
                    'size_bytes': func.size(),
                    'signature': sig,
                    'decompiled_c': code,
                }

                with open(filepath, 'w', encoding='utf-8') as f:
                    json.dump(result, f, indent=2, ensure_ascii=False)

                exported += 1

            except Exception:
                errors += 1

        elapsed = time.time() - t0
        log("")
        log("[*] 补充导出完成!")
        log(f"  新增导出: {exported}")
        log(f"  有结构体访问: {struct_access}")
        log(f"  错误: {errors}")
        log(f"  耗时: {elapsed:.1f}s")

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
