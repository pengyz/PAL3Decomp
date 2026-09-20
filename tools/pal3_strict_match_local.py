"""
本地严格字节匹配: PAL3A → PAL3.exe 函数名迁移

不需要 IDA 运行，直接读取:
  - asm/pal3a/func_bytes_dump.json (PAL3A 函数字节, 从 IDB 导出)
  - original/PAL3.exe (PAL3 二进制文件)
  - PAL3.exe 的函数列表 (从已导出的 JSON 文件名解析地址)

匹配策略:
  - 按函数大小索引候选
  - Opcode-aware mask: 屏蔽所有 call/jmp 目标 + 绝对地址引用
  - 100% 非屏蔽字节匹配 + 覆盖率 >= 50%
  - 唯一匹配或所有候选同名时才应用

输出:
  - asm/pal3/strict_match_result.json (匹配结果, 供 IDA 脚本应用)
"""

import json
import os
import struct
import time
import sys
import re
from pathlib import Path


# ---- 2026-09-20 审计 P2-4：无参数解析工具的统一护栏 ----------------------------
# 本工具**会写盘**且**没有任何 argparse/sys.argv 处理** ⇒ 传任何 `-` 开头的参数
# （最典型的是 `--help`）此前会被当作普通输入，**执行全流程并覆盖产物**。
# 本次审计期间已因此发生 **2 起事故**（`sig_evidence.py` 删掉 6020 行、
# `misattribution_ledger.py` 把 197 cluster 改写成 3）。
# 统一护栏：见到任何以 `-` 开头的参数即打印用法并**退出，不执行任何工作**。
import sys as _sys_guard
if any(_a.startswith('-') for _a in _sys_guard.argv[1:]):
    print('[%s] 本工具不接受命令行开关；收到 %r ⇒ 不执行任何操作。'
          % (__file__.rsplit('/', 1)[-1], _sys_guard.argv[1:]))
    print('用法: python3 %s    # 无参数，直接运行' % __file__)
    _sys_guard.exit(0)
# ---------------------------------------------------------------------------

PROJECT_ROOT = os.path.dirname(os.path.abspath(__file__))
if os.path.basename(PROJECT_ROOT) == 'tools':
    PROJECT_ROOT = os.path.dirname(PROJECT_ROOT)

FUNC_BYTES_DUMP = os.path.join(PROJECT_ROOT, "asm", "pal3a", "func_bytes_dump.json")
PAL3_EXE = os.path.join(PROJECT_ROOT, "original", "PAL3.exe")
PAL3_FUNCS_DIR = os.path.join(PROJECT_ROOT, "asm", "pal3")
OUTPUT_FILE = os.path.join(PROJECT_ROOT, "asm", "pal3", "strict_match_result.json")

# PAL3.exe section layout
TEXT_VA_START = 0x00401000
TEXT_VA_END = 0x005695D0
TEXT_FILE_OFF = 0x1000

# Address-like value range (for masking)
ADDR_LO = 0x00401000
ADDR_HI = 0x006FFFFF


def compute_opcode_mask(raw_bytes):
    """
    Compute mask for x86 code: mark bytes that are address operands.
    Returns list of 0/1 (1=skip in comparison).

    Covers:
    - E8/E9 + rel32 (call/jmp)
    - 0F 80-8F + rel32 (Jcc)
    - 68 + imm32 if address-like (push)
    - A1/A3 + moffs32 (mov eax, [addr])
    - ModRM with mod=00 rm=101 (disp32 = [abs_addr])
    - ModRM with SIB and base=101, mod=00 (disp32)
    - B8-BF + imm32 if address-like (mov reg, imm32)
    - C7 with mod=xx and imm32 if address-like
    """
    size = len(raw_bytes)
    mask = bytearray(size)
    i = 0

    while i < size:
        b = raw_bytes[i]

        # E8 call rel32, E9 jmp rel32
        if b in (0xE8, 0xE9) and i + 4 < size:
            mask[i+1] = mask[i+2] = mask[i+3] = mask[i+4] = 1
            i += 5
            continue

        # 0F 80-8F: Jcc rel32
        if b == 0x0F and i + 1 < size and 0x80 <= raw_bytes[i+1] <= 0x8F and i + 5 < size:
            mask[i+2] = mask[i+3] = mask[i+4] = mask[i+5] = 1
            i += 6
            continue

        # 68: push imm32
        if b == 0x68 and i + 4 < size:
            val = int.from_bytes(raw_bytes[i+1:i+5], 'little')
            if ADDR_LO <= val <= ADDR_HI:
                mask[i+1] = mask[i+2] = mask[i+3] = mask[i+4] = 1
            i += 5
            continue

        # A1: mov eax, [moffs32]
        if b == 0xA1 and i + 4 < size:
            mask[i+1] = mask[i+2] = mask[i+3] = mask[i+4] = 1
            i += 5
            continue

        # A3: mov [moffs32], eax
        if b == 0xA3 and i + 4 < size:
            mask[i+1] = mask[i+2] = mask[i+3] = mask[i+4] = 1
            i += 5
            continue

        # B8-BF: mov reg, imm32
        if 0xB8 <= b <= 0xBF and i + 4 < size:
            val = int.from_bytes(raw_bytes[i+1:i+5], 'little')
            if ADDR_LO <= val <= ADDR_HI:
                mask[i+1] = mask[i+2] = mask[i+3] = mask[i+4] = 1
            i += 5
            continue

        # Instructions with ModRM byte
        # We need to detect: mod=00, rm=101 → disp32 (absolute address)
        # Also: any instruction with disp32 that looks like an address
        # Common single-byte opcodes with ModRM:
        MODRM_1BYTE = {
            0x00, 0x01, 0x02, 0x03, 0x08, 0x09, 0x0A, 0x0B,
            0x10, 0x11, 0x12, 0x13, 0x18, 0x19, 0x1A, 0x1B,
            0x20, 0x21, 0x22, 0x23, 0x28, 0x29, 0x2A, 0x2B,
            0x30, 0x31, 0x32, 0x33, 0x38, 0x39, 0x3A, 0x3B,
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
            0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
            0xC0, 0xC1, 0xC4, 0xC5, 0xC6, 0xC7,
            0xD0, 0xD1, 0xD2, 0xD3,
            0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
            0xF6, 0xF7, 0xFE, 0xFF,
        }

        if b in MODRM_1BYTE and i + 1 < size:
            modrm = raw_bytes[i + 1]
            mod = (modrm >> 6) & 3
            rm = modrm & 7
            reg = (modrm >> 3) & 7

            disp_offset = i + 2  # default: right after ModRM

            if mod == 0 and rm == 4:
                # SIB follows
                if i + 2 < size:
                    sib = raw_bytes[i + 2]
                    sib_base = sib & 7
                    disp_offset = i + 3
                    if sib_base == 5:
                        # mod=00 + SIB base=101 → disp32
                        if disp_offset + 3 < size:
                            val = int.from_bytes(raw_bytes[disp_offset:disp_offset+4], 'little')
                            if ADDR_LO <= val <= ADDR_HI:
                                mask[disp_offset] = mask[disp_offset+1] = 1
                                mask[disp_offset+2] = mask[disp_offset+3] = 1
                i += 1
                continue

            if mod == 0 and rm == 5:
                # [disp32] - absolute address reference
                if disp_offset + 3 < size:
                    mask[disp_offset] = mask[disp_offset+1] = 1
                    mask[disp_offset+2] = mask[disp_offset+3] = 1
                i += 1
                continue

            if mod == 2:
                # [reg + disp32]
                actual_disp_off = disp_offset
                if rm == 4:
                    actual_disp_off += 1  # SIB byte
                if actual_disp_off + 3 < size:
                    val = int.from_bytes(raw_bytes[actual_disp_off:actual_disp_off+4], 'little')
                    if ADDR_LO <= val <= ADDR_HI:
                        mask[actual_disp_off] = mask[actual_disp_off+1] = 1
                        mask[actual_disp_off+2] = mask[actual_disp_off+3] = 1

            # For C7 (mov r/m32, imm32), also mask the immediate if address-like
            if b == 0xC7:
                # Calculate where imm32 starts (after ModRM + possible SIB + possible disp)
                imm_off = i + 2
                if rm == 4:
                    imm_off += 1  # SIB
                if mod == 0 and rm == 5:
                    imm_off += 4  # disp32
                elif mod == 1:
                    imm_off += 1  # disp8
                elif mod == 2:
                    imm_off += 4  # disp32
                if imm_off + 3 < size:
                    val = int.from_bytes(raw_bytes[imm_off:imm_off+4], 'little')
                    if ADDR_LO <= val <= ADDR_HI:
                        mask[imm_off] = mask[imm_off+1] = 1
                        mask[imm_off+2] = mask[imm_off+3] = 1

            i += 1
            continue

        i += 1

    return bytes(mask)


def compare_functions(bytes1, mask1, bytes2, mask2):
    """
    Compare two function byte sequences with masks.
    Returns (is_match, compared_count, total_size).
    Match requires 100% on non-masked bytes.
    """
    if len(bytes1) != len(bytes2):
        return False, 0, 0

    size = len(bytes1)
    compared = 0

    for i in range(size):
        if mask1[i] or mask2[i]:
            continue
        compared += 1
        if bytes1[i] != bytes2[i]:
            return False, compared, size

    return True, compared, size


def get_pal3_functions():
    """Get PAL3.exe function list from exported JSON filenames."""
    funcs = []
    pattern = re.compile(r'_([0-9a-f]{8})\.json$')

    for fname in os.listdir(PAL3_FUNCS_DIR):
        if not fname.endswith('.json') or fname.startswith('_'):
            continue
        m = pattern.search(fname)
        if m:
            addr = int(m.group(1), 16)
            if TEXT_VA_START <= addr < TEXT_VA_END:
                funcs.append(addr)

    return sorted(set(funcs))


def get_pal3_func_size(addr, all_addrs):
    """Estimate function size from the gap to next function."""
    idx = all_addrs.index(addr)
    if idx + 1 < len(all_addrs):
        return all_addrs[idx + 1] - addr
    return TEXT_VA_END - addr


def read_pe_bytes(pe_data, va, size):
    """Read bytes from PAL3.exe at given VA."""
    file_off = TEXT_FILE_OFF + (va - TEXT_VA_START)
    if file_off + size > len(pe_data):
        return None
    return pe_data[file_off:file_off + size]


def main():
    print("[*] PAL3A → PAL3.exe 严格字节匹配 (本地版)")
    print("[*] 时间: %s" % time.strftime("%Y-%m-%d %H:%M:%S"))

    # Load PAL3A data
    if not os.path.exists(FUNC_BYTES_DUMP):
        print("[!] PAL3A 字节数据不存在: %s" % FUNC_BYTES_DUMP)
        return

    print("[*] 加载 PAL3A 字节数据...")
    with open(FUNC_BYTES_DUMP, 'r', encoding='utf-8') as f:
        dump_data = json.load(f)

    pal3a_funcs = dump_data['functions']
    print("[*] PAL3A 函数: %d" % len(pal3a_funcs))

    # Pre-compute masks
    print("[*] 计算 PAL3A opcode masks...")
    t0 = time.time()
    pal3a_data = []
    for func in pal3a_funcs:
        raw = bytes.fromhex(func['bytes'])
        mask = compute_opcode_mask(raw)
        pal3a_data.append({
            'raw': raw,
            'mask': mask,
            'size': func['size'],
            'mangled': func['mangled'],
            'name': func['name'],
            'addr': func['addr'],
        })
    print("[*] 完成 (%.1fs)" % (time.time() - t0))

    # Build size index
    size_index = {}
    for d in pal3a_data:
        sz = d['size']
        if sz not in size_index:
            size_index[sz] = []
        size_index[sz].append(d)
    print("[*] 大小索引: %d 种" % len(size_index))

    # Load PAL3.exe
    print("[*] 加载 PAL3.exe...")
    with open(PAL3_EXE, 'rb') as f:
        pe_data = f.read()

    # Get PAL3 function addresses
    print("[*] 获取 PAL3 函数列表...")
    pal3_addrs = get_pal3_functions()
    print("[*] PAL3 函数: %d" % len(pal3_addrs))

    # Match
    print("[*] 开始匹配...")
    t0 = time.time()
    matches = []
    no_match = 0
    no_candidates = 0
    multi_conflict = 0
    low_coverage = 0

    for idx, addr in enumerate(pal3_addrs):
        if (idx + 1) % 500 == 0:
            elapsed = time.time() - t0
            print("  [%d/%d] matches=%d (%.0f f/s)" % (
                idx + 1, len(pal3_addrs), len(matches),
                (idx + 1) / elapsed if elapsed > 0 else 0))

        # Estimate size
        size = get_pal3_func_size(addr, pal3_addrs)
        if size < 4 or size > 100000:
            continue

        # Check candidates
        if size not in size_index:
            no_candidates += 1
            continue

        candidates = size_index[size]

        # Read PAL3 bytes
        pal3_raw = read_pe_bytes(pe_data, addr, size)
        if pal3_raw is None:
            continue

        pal3_mask = compute_opcode_mask(pal3_raw)

        # Compare
        found = []
        for cand in candidates:
            is_match, compared, total = compare_functions(
                pal3_raw, pal3_mask, cand['raw'], cand['mask'])

            if is_match and compared >= max(4, size * 0.4):
                found.append((cand, compared))

        if len(found) == 1:
            cand, compared = found[0]
            matches.append({
                'pal3_addr': '0x%08X' % addr,
                'pal3a_addr': '0x%08X' % cand['addr'],
                'size': size,
                'compared': compared,
                'coverage': round(compared / size, 3),
                'mangled': cand['mangled'],
                'name': cand['name'],
            })
        elif len(found) > 1:
            # Check if all have same name
            names = set(c['mangled'] for c, _ in found)
            if len(names) == 1:
                cand, compared = found[0]
                matches.append({
                    'pal3_addr': '0x%08X' % addr,
                    'pal3a_addr': '0x%08X' % cand['addr'],
                    'size': size,
                    'compared': compared,
                    'coverage': round(compared / size, 3),
                    'mangled': cand['mangled'],
                    'name': cand['name'],
                })
            else:
                multi_conflict += 1
        else:
            no_match += 1

    elapsed = time.time() - t0
    print("")
    print("[*] 匹配完成 (%.1fs)" % elapsed)
    print("[*] 结果:")
    print("    精确匹配: %d" % len(matches))
    print("    无候选 (大小不匹配): %d" % no_candidates)
    print("    多候选冲突: %d" % multi_conflict)
    print("    无匹配 (字节不同): %d" % no_match)

    if matches:
        coverages = [m['coverage'] for m in matches]
        print("    覆盖率: avg=%.1f%% min=%.1f%% max=%.1f%%" % (
            100 * sum(coverages) / len(coverages),
            100 * min(coverages),
            100 * max(coverages)))

    # Save results
    os.makedirs(os.path.dirname(OUTPUT_FILE), exist_ok=True)
    result = {
        'meta': {
            'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
            'pal3a_functions': len(pal3a_funcs),
            'pal3_functions': len(pal3_addrs),
            'elapsed_seconds': round(elapsed, 1),
        },
        'stats': {
            'matches': len(matches),
            'no_candidates': no_candidates,
            'multi_conflict': multi_conflict,
            'no_match': no_match,
        },
        'matches': matches,
    }

    with open(OUTPUT_FILE, 'w', encoding='utf-8') as f:
        json.dump(result, f, indent=2, ensure_ascii=False)

    print("[*] 结果已保存: %s" % OUTPUT_FILE)
    print("")
    print("[*] 下一步: 在 IDA 中运行 pal3_apply_strict_matches.py 应用名称")


if __name__ == '__main__':
    main()
