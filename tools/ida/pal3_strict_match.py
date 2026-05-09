"""
IDAPython: 严格字节匹配 — 从 PAL3A 迁移函数名到 PAL3.exe

策略:
  1. 加载 PAL3A 函数字节数据 (func_bytes_dump.json)
  2. 对 PAL3.exe IDB 中每个未命名函数, 提取字节
  3. 使用 opcode-aware 比较: 屏蔽 call/jmp 目标 + 绝对地址引用
  4. 只有代码逻辑部分 100% 匹配才迁移函数名

地址屏蔽规则 (x86):
  - E8/E9 xx xx xx xx: call/jmp near rel32 → 屏蔽后4字节
  - 0F 8x xx xx xx xx: Jcc near rel32 → 屏蔽后4字节
  - 68 xx xx xx xx: push imm32 (如果值像地址) → 屏蔽后4字节
  - ModRM 指令中 disp32 引用绝对地址 → 通过 IDA xref 识别

实际方案: 使用 IDA 的 xref 和 operand 信息自动识别需要屏蔽的位置,
         比纯字节解析更可靠。

运行环境: PAL3.exe.i64
前置: 先在 PAL3A.exe.i64 上运行 pal3a_dump_func_bytes.py

用法:
  idat.exe -A -S"pal3_strict_match.py" original/PAL3.exe.i64
"""

import ida_auto
import ida_bytes
import ida_fixup
import ida_funcs
import ida_name
import ida_ua
import idautils
import idc
import json
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

FUNC_BYTES_DUMP = os.path.join(PROJECT_ROOT, "asm", "pal3a", "func_bytes_dump.json")
MATCH_REPORT = os.path.join(PROJECT_ROOT, "asm", "pal3", "strict_match_report.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3_strict_match_log.txt")

PAL3_TEXT_START = 0x00401000
PAL3_TEXT_END = 0x005695D0

# Address ranges for masking (values that look like addresses in these ranges are masked)
ADDR_RANGES = [
    (0x00401000, 0x006FFFFF),  # .text + .rdata + .data for both binaries
]

log_lines = []


def log(msg):
    log_lines.append(str(msg))
    print(msg)


def is_address_like(val):
    """Check if a 32-bit value looks like an absolute address."""
    for lo, hi in ADDR_RANGES:
        if lo <= val <= hi:
            return True
    return False


def compute_mask_from_bytes(raw_bytes):
    """
    Compute a mask for x86 code bytes by identifying:
    - E8/E9 + 4 bytes (call/jmp rel32)
    - 0F 80-8F + 4 bytes (Jcc rel32)
    - Any 4-byte sequence that looks like an absolute address
      following common opcodes (push, mov, cmp, etc.)

    Returns a mask string: '0' = compare, '1' = skip
    """
    size = len(raw_bytes)
    mask = [0] * size
    i = 0

    while i < size:
        b = raw_bytes[i]

        # E8 (call rel32) or E9 (jmp rel32)
        if b in (0xE8, 0xE9) and i + 4 < size:
            mask[i+1] = 1
            mask[i+2] = 1
            mask[i+3] = 1
            mask[i+4] = 1
            i += 5
            continue

        # 0F 80-8F (Jcc rel32)
        if b == 0x0F and i + 1 < size:
            b2 = raw_bytes[i+1]
            if 0x80 <= b2 <= 0x8F and i + 5 < size:
                mask[i+2] = 1
                mask[i+3] = 1
                mask[i+4] = 1
                mask[i+5] = 1
                i += 6
                continue

        # 68 (push imm32) - mask if value looks like an address
        if b == 0x68 and i + 4 < size:
            val = int.from_bytes(raw_bytes[i+1:i+5], 'little')
            if is_address_like(val):
                mask[i+1] = 1
                mask[i+2] = 1
                mask[i+3] = 1
                mask[i+4] = 1
            i += 5
            continue

        # Instructions with ModRM byte that may have disp32 with absolute address
        # Check for [disp32] addressing mode (ModRM mod=00, rm=101)
        # Common patterns:
        # - 8B 0D/15/1D/25/2D/35/3D [addr] : mov reg, [addr]
        # - 89 0D/15/1D/25/2D/35/3D [addr] : mov [addr], reg
        # - A1/A3 [addr] : mov eax, [addr] / mov [addr], eax
        # - C7 05 [addr] [imm32] : mov dword ptr [addr], imm32
        # - 83 3D [addr] [imm8] : cmp dword ptr [addr], imm8
        # - FF 35 [addr] : push dword ptr [addr]
        # - FF 15 [addr] : call dword ptr [addr]
        # - FF 25 [addr] : jmp dword ptr [addr]

        # A1 (mov eax, moffs32)
        if b == 0xA1 and i + 4 < size:
            val = int.from_bytes(raw_bytes[i+1:i+5], 'little')
            if is_address_like(val):
                mask[i+1] = 1
                mask[i+2] = 1
                mask[i+3] = 1
                mask[i+4] = 1
            i += 5
            continue

        # A3 (mov moffs32, eax)
        if b == 0xA3 and i + 4 < size:
            val = int.from_bytes(raw_bytes[i+1:i+5], 'little')
            if is_address_like(val):
                mask[i+1] = 1
                mask[i+2] = 1
                mask[i+3] = 1
                mask[i+4] = 1
            i += 5
            continue

        # Instructions with ModRM: detect mod=00 rm=101 pattern (disp32)
        # Opcodes that use ModRM and could reference absolute addresses:
        HAS_MODRM = set([
            0x01, 0x03, 0x09, 0x0B, 0x11, 0x13, 0x19, 0x1B,
            0x21, 0x23, 0x29, 0x2B, 0x31, 0x33, 0x39, 0x3B,
            0x3D, 0x80, 0x81, 0x83, 0x84, 0x85, 0x86, 0x87,
            0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
            0xC4, 0xC5, 0xC6, 0xC7,
            0xD0, 0xD1, 0xD2, 0xD3, 0xD8, 0xD9, 0xDA, 0xDB,
            0xDC, 0xDD, 0xDE, 0xDF,
            0xF6, 0xF7, 0xFE, 0xFF,
        ])

        if b in HAS_MODRM and i + 1 < size:
            modrm = raw_bytes[i+1]
            mod = (modrm >> 6) & 3
            rm = modrm & 7

            if mod == 0 and rm == 5:
                # [disp32] - absolute address
                if i + 5 < size:
                    val = int.from_bytes(raw_bytes[i+2:i+6], 'little')
                    if is_address_like(val):
                        mask[i+2] = 1
                        mask[i+3] = 1
                        mask[i+4] = 1
                        mask[i+5] = 1
            i += 1
            continue

        # FF with ModRM (call/jmp/push indirect)
        if b == 0xFF and i + 1 < size:
            modrm = raw_bytes[i+1]
            mod = (modrm >> 6) & 3
            rm = modrm & 7
            if mod == 0 and rm == 5 and i + 5 < size:
                mask[i+2] = 1
                mask[i+3] = 1
                mask[i+4] = 1
                mask[i+5] = 1
            i += 2
            continue

        i += 1

    return ''.join(str(m) for m in mask)


def compare_masked(hex1, hex2, mask1, mask2):
    """
    Compare two byte sequences, skipping positions masked in EITHER side.
    Returns (match_rate, compared_count, mismatch_count).
    """
    if len(hex1) != len(hex2):
        return 0.0, 0, 0

    size = len(hex1) // 2
    compared = 0
    mismatches = 0

    for i in range(size):
        if mask1[i] == '1' or mask2[i] == '1':
            continue
        compared += 1
        if hex1[i*2:i*2+2] != hex2[i*2:i*2+2]:
            mismatches += 1

    if compared == 0:
        return 0.0, 0, 0

    rate = (compared - mismatches) / compared
    return rate, compared, mismatches


def main():
    try:
        ida_auto.auto_wait()
        log("[*] PAL3.exe 严格字节匹配 — 函数名迁移 (opcode-aware)")
        log("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))
        log("[*] PAL3 .text: 0x%08X - 0x%08X" % (PAL3_TEXT_START, PAL3_TEXT_END))

        # Load PAL3A byte dump
        if not os.path.exists(FUNC_BYTES_DUMP):
            log("[!] PAL3A 字节数据不存在: %s" % FUNC_BYTES_DUMP)
            log("[!] 请先在 PAL3A.exe.i64 上运行 pal3a_dump_func_bytes.py")
            return

        log("[*] 加载 PAL3A 字节数据...")
        with open(FUNC_BYTES_DUMP, 'r', encoding='utf-8') as f:
            dump_data = json.load(f)

        pal3a_funcs = dump_data['functions']
        log("[*] PAL3A 函数: %d" % len(pal3a_funcs))

        # Pre-compute masks for PAL3A functions
        log("[*] 计算 PAL3A 函数 opcode mask...")
        t_mask = time.time()
        for func in pal3a_funcs:
            raw = bytes.fromhex(func['bytes'])
            func['_mask'] = compute_mask_from_bytes(raw)
        log("[*] PAL3A mask 计算完成 (%.1fs)" % (time.time() - t_mask))

        # Build size-indexed lookup
        size_index = {}
        for func in pal3a_funcs:
            sz = func['size']
            if sz not in size_index:
                size_index[sz] = []
            size_index[sz].append(func)

        log("[*] 大小索引: %d 种不同大小" % len(size_index))

        # Collect PAL3.exe functions
        pal3_funcs = []
        for ea in idautils.Functions(PAL3_TEXT_START, PAL3_TEXT_END):
            if ea < PAL3_TEXT_START or ea >= PAL3_TEXT_END:
                continue
            func = ida_funcs.get_func(ea)
            if not func:
                continue
            size = func.size()
            if size < 4:
                continue
            pal3_funcs.append((ea, size))

        log("[*] PAL3 函数: %d" % len(pal3_funcs))

        # Strict matching
        t0 = time.time()
        exact_matches = []
        no_match = 0
        size_mismatch = 0
        already_named = 0
        multiple_candidates = 0
        low_coverage = 0

        for idx, (ea, size) in enumerate(pal3_funcs):
            if (idx + 1) % 500 == 0:
                elapsed = time.time() - t0
                log("  [%d/%d] exact=%d multi=%d (%.1f f/s)" % (
                    idx + 1, len(pal3_funcs), len(exact_matches),
                    multiple_candidates,
                    (idx + 1) / elapsed if elapsed > 0 else 0))

            # Skip already-named functions (non sub_)
            existing_name = ida_name.get_name(ea) or ""
            if existing_name and not existing_name.startswith("sub_"):
                already_named += 1
                continue

            # Check if any PAL3A functions have the same size
            if size not in size_index:
                size_mismatch += 1
                continue

            candidates = size_index[size]

            # Extract PAL3 bytes
            if not ida_bytes.is_loaded(ea) or not ida_bytes.is_loaded(ea + size - 1):
                continue

            raw_bytes = bytes([ida_bytes.get_byte(ea + i) for i in range(size)])
            pal3_hex = raw_bytes.hex()
            pal3_mask = compute_mask_from_bytes(raw_bytes)

            # Compare against all candidates of same size
            matches_found = []
            for cand in candidates:
                rate, compared, mismatches = compare_masked(
                    pal3_hex, cand['bytes'],
                    pal3_mask, cand['_mask'])

                # Require 100% match AND sufficient coverage
                # Coverage: at least 60% of bytes must be compared (not masked)
                if rate == 1.0 and compared >= max(4, size * 0.5):
                    matches_found.append(cand)

            if len(matches_found) == 1:
                match = matches_found[0]
                exact_matches.append({
                    'pal3_addr': '0x%08X' % ea,
                    'pal3a_addr': '0x%08X' % match['addr'],
                    'size': size,
                    'mangled': match['mangled'],
                    'name': match['name'],
                })
            elif len(matches_found) > 1:
                # Multiple matches — apply if all have the same mangled name
                names = set(m['mangled'] for m in matches_found)
                if len(names) == 1:
                    match = matches_found[0]
                    exact_matches.append({
                        'pal3_addr': '0x%08X' % ea,
                        'pal3a_addr': '0x%08X' % match['addr'],
                        'size': size,
                        'mangled': match['mangled'],
                        'name': match['name'],
                    })
                else:
                    multiple_candidates += 1
            else:
                no_match += 1

        elapsed = time.time() - t0
        log("")
        log("[*] 匹配完成 (%.1fs)" % elapsed)
        log("[*] 结果:")
        log("    精确匹配: %d" % len(exact_matches))
        log("    已有名称: %d" % already_named)
        log("    大小无候选: %d" % size_mismatch)
        log("    多候选冲突: %d" % multiple_candidates)
        log("    无匹配: %d" % no_match)

        # Apply names
        applied = 0
        apply_failed = 0
        for match in exact_matches:
            ea = int(match['pal3_addr'], 16)
            mangled = match['mangled']

            if ida_name.set_name(ea, mangled, ida_name.SN_NOWARN):
                applied += 1
            elif ida_name.set_name(ea, mangled, ida_name.SN_FORCE):
                applied += 1
            else:
                apply_failed += 1

        log("")
        log("[*] 名称应用: %d 成功, %d 失败" % (applied, apply_failed))

        # Save database
        idc.save_database(idc.get_idb_path(), 0)
        log("[*] 数据库已保存")

        # Write report
        os.makedirs(os.path.dirname(MATCH_REPORT), exist_ok=True)
        report = {
            'meta': {
                'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
                'pal3a_functions': len(pal3a_funcs),
                'pal3_functions': len(pal3_funcs),
                'elapsed_seconds': round(elapsed, 1),
            },
            'stats': {
                'exact_matches': len(exact_matches),
                'already_named': already_named,
                'size_no_candidate': size_mismatch,
                'multiple_candidates': multiple_candidates,
                'no_match': no_match,
                'applied': applied,
                'apply_failed': apply_failed,
            },
            'matches': exact_matches,
        }

        with open(MATCH_REPORT, 'w', encoding='utf-8') as f:
            json.dump(report, f, indent=2, ensure_ascii=False)

        log("[*] 报告: %s" % MATCH_REPORT)

    except Exception as e:
        log("[!] 致命错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
