"""
IDAPython: 验证并修正 PDB 函数名与 IDA 函数地址的映射

问题: PDB 地址空间 (0x401000-0x754450) 与 IDA 分析的二进制地址空间
可能不完全对应。之前的脚本可能把 PDB 名称贴到了错误的 IDA 地址。

策略:
  1. 收集 IDA 中所有已命名函数 (非 sub_)
  2. 对比 PDB 中相同名称的函数大小
  3. 如果大小严重不匹配 (>2x 差异), 标记为可疑
  4. 对于 PDB 地址在 IDA 中存在的函数, 优先用地址匹配
  5. 对于 PDB 地址不在 IDA 中的函数, 按名称+大小匹配

用法:
  idat.exe -A -S"ida_verify_names.py" PAL3A.exe.i64
"""

import ida_auto
import ida_funcs
import ida_name
import idautils
import idc
import json
import os
import builtins

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
TEXT_START = 0x00401000
TEXT_END = 0x00558000


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] IDA ready - 验证 PDB 名称映射")

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        pdb_funcs = pdb_data['functions']
        log(f"[*] PDB 函数: {len(pdb_funcs)}")

        # Build PDB name -> info lookup
        pdb_by_name = {}
        pdb_by_addr = {}
        for f in pdb_funcs:
            name = f.get('name', '')
            addr_str = f.get('address', '')
            if name and addr_str:
                safe = name.replace('::', '_').replace('~', '_dtor_')
                safe = safe.replace('<', '_').replace('>', '_').replace(' ', '_')
                pdb_by_name[safe] = f
                pdb_by_name[name] = f
                try:
                    addr = int(addr_str, 16)
                    pdb_by_addr[addr] = f
                except ValueError:
                    pass

        # Collect IDA named functions
        ida_named = {}
        for ea in idautils.Functions():
            n = ida_name.get_name(ea)
            if n and not n.startswith("sub_") and not n.startswith("nullsub_"):
                func = ida_funcs.get_func(ea)
                size = func.size() if func else 0
                ida_named[n] = (ea, size)

        log(f"[*] IDA 已命名函数: {len(ida_named)}")

        # Phase 1: Check address-based matches (PDB addr exists in IDA)
        addr_match = 0
        addr_mismatch = 0
        for ea, pdb_info in pdb_by_addr.items():
            func = ida_funcs.get_func(ea)
            if func and func.start_ea == ea:
                addr_match += 1
            # If IDA has a function at this address, it should match
        log(f"[*] PDB 地址在 IDA 中有函数入口: {addr_match}")

        # Phase 1.5: Remove names where PDB address is OUTSIDE .text
        # These were incorrectly applied by Phase A2 name-matching in earlier runs.
        # If PDB says a function is at 0x706044 (outside .text), but IDA has a
        # function named that way, it's a false match - the code at that IDA address
        # is a completely different function.
        removed_outside = 0
        for ida_name_str, (ea, ida_size) in list(ida_named.items()):
            pdb_info = pdb_by_name.get(ida_name_str)
            if not pdb_info:
                continue
            pdb_addr_str = pdb_info.get('address', '')
            if not pdb_addr_str:
                continue
            try:
                pdb_addr = int(pdb_addr_str, 16)
            except ValueError:
                continue
            # If PDB address is outside .text AND the IDA address doesn't match PDB
            if not (TEXT_START <= pdb_addr < TEXT_END) and ea != pdb_addr:
                # This name was incorrectly applied - remove it
                ida_name.set_name(ea, "", ida_name.SN_NOWARN)
                removed_outside += 1
                if removed_outside <= 20:
                    log(f"    [REMOVE] {ida_name_str} @ 0x{ea:08X} (PDB addr 0x{pdb_addr:08X} outside .text)")

        log(f"[*] Phase 1.5: 移除 PDB 地址在 .text 外的错误命名: {removed_outside}")

        # Rebuild ida_named after removals
        if removed_outside > 0:
            ida_named = {}
            for ea in idautils.Functions():
                n = ida_name.get_name(ea)
                if n and not n.startswith("sub_") and not n.startswith("nullsub_"):
                    func = ida_funcs.get_func(ea)
                    size = func.size() if func else 0
                    ida_named[n] = (ea, size)
            log(f"[*] 重建后 IDA 已命名函数: {len(ida_named)}")

        # Phase 2: Verify name matches - check size consistency
        correct = 0
        suspicious = 0
        wrong_size = []
        not_in_pdb = 0

        for ida_name_str, (ea, ida_size) in ida_named.items():
            pdb_info = pdb_by_name.get(ida_name_str)
            if not pdb_info:
                not_in_pdb += 1
                continue

            pdb_size = pdb_info.get('size', 0)
            if pdb_size == 0:
                correct += 1
                continue

            # Size check: allow 2x tolerance (compiler differences)
            ratio = max(ida_size, pdb_size) / max(min(ida_size, pdb_size), 1)
            if ratio > 3.0 and abs(ida_size - pdb_size) > 50:
                suspicious += 1
                if len(wrong_size) < 50:
                    wrong_size.append({
                        'name': ida_name_str,
                        'ida_addr': f"0x{ea:08X}",
                        'ida_size': ida_size,
                        'pdb_addr': pdb_info.get('address', '?'),
                        'pdb_size': pdb_size,
                        'ratio': round(ratio, 1),
                    })
            else:
                correct += 1

        log(f"[*] 名称验证结果:")
        log(f"    正确 (大小匹配): {correct}")
        log(f"    可疑 (大小严重不匹配): {suspicious}")
        log(f"    不在 PDB 中: {not_in_pdb}")

        if wrong_size:
            log(f"\n[!] 大小不匹配样本 (前{min(20, len(wrong_size))}个):")
            for ws in wrong_size[:20]:
                log(f"    {ws['name']:40s} IDA:{ws['ida_size']:5d}B@{ws['ida_addr']} "
                    f"PDB:{ws['pdb_size']:5d}B@{ws['pdb_addr']} ratio={ws['ratio']}")

        # Phase 3: For mismatched names, try to find the correct IDA function
        # by searching for a function of the right size near the PDB address
        relocated = 0
        for ws in wrong_size:
            pdb_info = pdb_by_name.get(ws['name'])
            if not pdb_info:
                continue
            pdb_size = pdb_info.get('size', 0)
            pdb_addr = int(pdb_info['address'], 16)

            # Look for an unnamed function with matching size
            # Search in a range around the PDB address
            best_match = None
            best_diff = 999999

            for ea in idautils.Functions():
                func = ida_funcs.get_func(ea)
                if not func:
                    continue
                # Only consider unnamed or same-named functions
                n = ida_name.get_name(ea) or ""
                if n and not n.startswith("sub_") and n != ws['name']:
                    continue
                # Size must be close
                size_diff = abs(func.size() - pdb_size)
                if size_diff <= max(pdb_size * 0.2, 10):
                    # Prefer the one closest to PDB address
                    addr_diff = abs(ea - pdb_addr)
                    if addr_diff < best_diff:
                        best_diff = addr_diff
                        best_match = ea

            if best_match and best_match != int(ws['ida_addr'], 16):
                # Found a better match - rename it
                old_ea = int(ws['ida_addr'], 16)
                # Remove old name
                ida_name.set_name(old_ea, "", ida_name.SN_NOWARN)
                # Apply to new address
                safe = ws['name']
                if ida_name.set_name(best_match, safe, ida_name.SN_NOWARN | ida_name.SN_NOCHECK):
                    relocated += 1
                    if relocated <= 10:
                        log(f"    [RELOCATE] {ws['name']}: 0x{old_ea:08X} -> 0x{best_match:08X}")

        log(f"\n[*] 重新定位: {relocated} 个函数")

        # Save report
        report = {
            'total_ida_named': len(ida_named),
            'correct_size': correct,
            'suspicious_size': suspicious,
            'not_in_pdb': not_in_pdb,
            'relocated': relocated,
            'wrong_size_samples': wrong_size,
        }

        os.makedirs(LOG_DIR, exist_ok=True)
        report_path = os.path.join(LOG_DIR, "verify_names_report.json")
        with open(report_path, 'w', encoding='utf-8') as f:
            json.dump(report, f, indent=2, ensure_ascii=False)
        log(f"\n[*] 报告已保存: {report_path}")

        idc.save_database(idc.get_idb_path(), 0)

    except Exception as e:
        log(f"[!] 错误: {e}")
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    log_path = os.path.join(LOG_DIR, "ida_verify_names_log.txt")
    with open(log_path, "w", encoding="utf-8") as f:
        f.write("\n".join(log_lines))

    if not getattr(builtins, '_IDA_PIPELINE_RUNNING', False):
        try:
            idc.qexit(0)
        except:
            pass


if __name__ == '__main__':
    main()
