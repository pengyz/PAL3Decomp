"""
IDAPython: 根据 PDB 信息拆分 IDA 中被合并的函数

PDB 记录了每个函数的精确入口地址，但 IDA 有时会把多个小函数
合并成一个大函数。此脚本尝试在 PDB 指定的入口点拆分函数。

策略:
  1. 收集所有 PDB 地址指向"函数中间"的情况
  2. 检查该地址是否是合法的拆分点（前面有 ret/jmp 指令）
  3. 如果是，执行拆分：truncate + add_func
"""

import ida_auto
import ida_typeinf
import ida_funcs
import ida_bytes
import ida_name
import ida_ua
import idc
import json
import os
import traceback
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")
LOG_FILE = os.path.join(LOG_DIR, "ida_split_functions_log.txt")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
TEXT_START = 0x00401000
TEXT_END = 0x00558000  # .text actual end


def is_valid_split_point(addr):
    """检查 addr 前面是否有 ret/jmp 等终止指令，是合法的函数入口"""
    # Check bytes before addr for ret (C3, C2 xx xx) or jmp
    prev_byte = ida_bytes.get_byte(addr - 1)
    prev2_byte = ida_bytes.get_byte(addr - 2) if addr >= 2 else 0
    prev3_byte = ida_bytes.get_byte(addr - 3) if addr >= 3 else 0
    prev5_byte = ida_bytes.get_byte(addr - 5) if addr >= 5 else 0

    # ret = 0xC3, retn = 0xC2 xx xx
    if prev_byte == 0xC3:
        return True
    if prev3_byte == 0xC2:
        return True

    # jmp rel32 = 0xE9 xx xx xx xx (5 bytes)
    if prev5_byte == 0xE9:
        return True

    # jmp rel8 = 0xEB xx (2 bytes)
    if prev2_byte == 0xEB:
        return True

    # int3 padding (0xCC)
    if prev_byte == 0xCC:
        return True

    return False


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA 9.x ready")

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        funcs = pdb_data['functions']

        # Find mid-function addresses
        targets = []
        for f in funcs:
            addr_str = f.get('address', '')
            if not addr_str:
                continue
            try:
                addr = int(addr_str, 16)
            except ValueError:
                continue
            if addr < TEXT_START or addr >= TEXT_END:
                continue
            name = f.get('name', '')
            if not name or '[thunk]' in name or '??' in name:
                continue
            if name.startswith('std::') or '<' in name:
                continue
            if "'" in name or '`' in name or 'adjustor' in name:
                continue

            func = ida_funcs.get_func(addr)
            if func and func.start_ea != addr:
                targets.append((addr, func, f))

        log(f"[*] 中间地址函数: {len(targets)}")

        # Analyze split candidates
        valid_splits = 0
        invalid_splits = 0
        split_success = 0
        split_fail = 0

        # Group by containing function
        containing = {}
        for addr, func, fi in targets:
            if func.start_ea not in containing:
                containing[func.start_ea] = []
            containing[func.start_ea].append((addr, fi))

        log(f"[*] 涉及 {len(containing)} 个宿主函数")

        # Show top containing functions
        big_hosts = sorted(containing.items(), key=lambda x: len(x[1]), reverse=True)[:10]
        log("[*] 最大宿主函数 (包含最多 PDB 子函数):")
        for host_addr, subs in big_hosts:
            host_name = ida_name.get_name(host_addr) or f"sub_{host_addr:08X}"
            host_func = ida_funcs.get_func(host_addr)
            host_size = host_func.size() if host_func else 0
            log(f"  0x{host_addr:08X} {host_name} ({host_size} bytes) -> {len(subs)} 个子函数")

        # Try to split
        for addr, func, fi in targets:
            if is_valid_split_point(addr):
                valid_splits += 1
                # Attempt split: truncate the containing function, create new one
                old_end = func.end_ea
                # Set the containing function's end to this address
                if ida_funcs.set_func_end(func.start_ea, addr):
                    # Create new function at addr
                    if ida_funcs.add_func(addr, old_end):
                        split_success += 1
                        # Name the new function
                        name = fi.get('name', '')
                        safe = name.replace('::', '_').replace('~', '_dtor_')
                        safe = safe.replace('<', '_').replace('>', '_').replace(' ', '_')
                        ida_name.set_name(addr, safe, ida_name.SN_NOWARN | ida_name.SN_NOCHECK)
                    else:
                        # add_func failed, try without end
                        if ida_funcs.add_func(addr):
                            split_success += 1
                            name = fi.get('name', '')
                            safe = name.replace('::', '_').replace('~', '_dtor_')
                            safe = safe.replace('<', '_').replace('>', '_').replace(' ', '_')
                            ida_name.set_name(addr, safe, ida_name.SN_NOWARN | ida_name.SN_NOCHECK)
                        else:
                            # Restore original function end
                            ida_funcs.set_func_end(func.start_ea, old_end)
                            split_fail += 1
                else:
                    split_fail += 1
            else:
                invalid_splits += 1

        log(f"\n[*] 拆分结果:")
        log(f"  合法拆分点: {valid_splits}")
        log(f"  非法拆分点: {invalid_splits}")
        log(f"  拆分成功: {split_success}")
        log(f"  拆分失败: {split_fail}")

        if split_success > 0:
            ida_auto.auto_wait()
            idc.save_database(idc.get_idb_path(), 0)
            log("[*] 数据库已保存")

    except Exception as e:
        log(f"[!] 错误: {e}")
        log(traceback.format_exc())

    os.makedirs(os.path.dirname(LOG_FILE), exist_ok=True)
    with open(LOG_FILE, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
