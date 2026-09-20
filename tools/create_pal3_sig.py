"""
从 PAL3A 二进制 + PDB 数据创建 FLIRT .pat 签名文件

不依赖 IDA，直接操作二进制文件:
1. 从 pdb_export.json 读取函数列表 (名称 + 地址 + 大小)
2. 从 PAL3A.exe 二进制读取对应字节
3. 生成 IDA FLIRT .pat 格式文件

用法:
  python tools/create_pal3_sig.py

输出:
  tools/ida/pal3a_text.pat  — FLIRT 模式文件
  然后用 sigmake 转为 .sig:
    sigmake tools/ida/pal3a_text.pat tools/ida/pal3a_text.sig
"""

import json
import struct
import os
import sys


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

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(SCRIPT_DIR)

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
PAL3A_BIN = os.path.join(PROJECT_ROOT, "original", "PAL3A.exe")
OUTPUT_PAT = os.path.join(PROJECT_ROOT, "tools", "ida", "pal3a_text.pat")

# .text section in PAL3A.exe (same as PAL3.exe)
TEXT_VA_START = 0x00401000
TEXT_VA_END = 0x00558000

PATTERN_LEN = 32
MIN_FUNC_SIZE = 8


def load_pe_sections(data):
    """Parse PE headers to get section VA→file offset mapping"""
    # DOS header
    pe_offset = struct.unpack_from('<I', data, 0x3C)[0]
    # COFF header
    num_sections = struct.unpack_from('<H', data, pe_offset + 6)[0]
    opt_size = struct.unpack_from('<H', data, pe_offset + 20)[0]

    # Parse optional header for ImageBase
    image_base = struct.unpack_from('<I', data, pe_offset + 24 + 28)[0]

    # Section table starts after optional header
    section_offset = pe_offset + 24 + opt_size
    sections = []
    for i in range(num_sections):
        off = section_offset + i * 40
        name = data[off:off + 8].rstrip(b'\x00').decode('ascii', 'replace')
        vsize = struct.unpack_from('<I', data, off + 8)[0]
        vaddr = struct.unpack_from('<I', data, off + 12)[0]
        rawsize = struct.unpack_from('<I', data, off + 16)[0]
        rawptr = struct.unpack_from('<I', data, off + 20)[0]
        sections.append({
            'name': name,
            'va': image_base + vaddr,
            'vsize': vsize,
            'rawptr': rawptr,
            'rawsize': rawsize,
        })
    return sections, image_base


def va_to_file_offset(sections, va):
    """Convert virtual address to file offset"""
    for sec in sections:
        if sec['va'] <= va < sec['va'] + sec['rawsize']:
            return sec['rawptr'] + (va - sec['va'])
    return None


def find_relocations(data, sections, image_base):
    """
    Parse PE relocation table to find all relocated addresses.
    Returns set of file offsets that are part of relocations.
    """
    reloc_offsets = set()

    # Find .reloc section or parse data directory
    pe_offset = struct.unpack_from('<I', data, 0x3C)[0]
    # Data directory entry 5 = Base Relocation Table
    # Optional header starts at pe_offset + 24
    # Data directories start at offset 96 (PE32) into optional header
    dd_offset = pe_offset + 24 + 96 + 5 * 8  # 5th entry (0-indexed)
    reloc_rva = struct.unpack_from('<I', data, dd_offset)[0]
    reloc_size = struct.unpack_from('<I', data, dd_offset + 4)[0]

    if reloc_rva == 0 or reloc_size == 0:
        return reloc_offsets

    reloc_va = image_base + reloc_rva
    reloc_file_off = va_to_file_offset(sections, reloc_va)
    if reloc_file_off is None:
        return reloc_offsets

    # Parse relocation blocks
    pos = reloc_file_off
    end = reloc_file_off + reloc_size

    while pos < end:
        block_rva = struct.unpack_from('<I', data, pos)[0]
        block_size = struct.unpack_from('<I', data, pos + 4)[0]
        if block_size == 0:
            break

        num_entries = (block_size - 8) // 2
        for i in range(num_entries):
            entry = struct.unpack_from('<H', data, pos + 8 + i * 2)[0]
            entry_type = entry >> 12
            entry_offset = entry & 0xFFF

            if entry_type == 3:  # IMAGE_REL_BASED_HIGHLOW (32-bit)
                reloc_addr = image_base + block_rva + entry_offset
                file_off = va_to_file_offset(sections, reloc_addr)
                if file_off is not None:
                    # Mark 4 bytes as relocated
                    for j in range(4):
                        reloc_offsets.add(file_off + j)

        pos += block_size

    return reloc_offsets


def crc16_flair(data_bytes, reloc_set, file_start):
    """Calculate CRC16 as used by IDA FLAIR (polynomial 0x8005)"""
    crc = 0
    for i, b in enumerate(data_bytes):
        if (file_start + i) in reloc_set:
            continue
        crc ^= b << 8
        for _ in range(8):
            if crc & 0x8000:
                crc = ((crc << 1) ^ 0x8005) & 0xFFFF
            else:
                crc = (crc << 1) & 0xFFFF
    return crc


def main():
    print("[*] PAL3A FLIRT 签名生成 (standalone)")

    if not os.path.exists(PDB_EXPORT):
        print("[!] 找不到: %s" % PDB_EXPORT)
        return 1
    if not os.path.exists(PAL3A_BIN):
        print("[!] 找不到: %s" % PAL3A_BIN)
        return 1

    # Load PDB data
    print("[*] 加载 PDB 数据...")
    with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
        pdb_data = json.load(f)

    functions = pdb_data['functions']
    print("[*] PDB 函数总数: %d" % len(functions))

    # Filter to .text functions with valid size
    text_funcs = []
    for func in functions:
        addr = int(func['address'], 16)
        size = func.get('size', 0)
        name = func.get('mangled_name', '') or func.get('name', '')
        if not name or size < MIN_FUNC_SIZE:
            continue
        if TEXT_VA_START <= addr < TEXT_VA_END:
            text_funcs.append((addr, size, name))

    print("[*] .text 函数 (size >= %d): %d" % (MIN_FUNC_SIZE, len(text_funcs)))

    # Load binary
    print("[*] 加载 PAL3A.exe...")
    with open(PAL3A_BIN, 'rb') as f:
        pe_data = f.read()

    sections, image_base = load_pe_sections(pe_data)
    print("[*] ImageBase: 0x%08X, Sections: %d" % (image_base, len(sections)))

    # Find relocations
    print("[*] 解析重定位表...")
    reloc_set = find_relocations(pe_data, sections, image_base)
    print("[*] 重定位字节: %d" % len(reloc_set))

    # Generate .pat lines
    print("[*] 生成 FLIRT 模式...")
    pat_lines = []
    skipped = 0

    for addr, size, name in sorted(text_funcs, key=lambda x: x[0]):
        file_off = va_to_file_offset(sections, addr)
        if file_off is None:
            skipped += 1
            continue

        # Read pattern bytes
        avail = min(PATTERN_LEN, size)
        if file_off + avail > len(pe_data):
            skipped += 1
            continue

        # Build pattern with relocation wildcards
        pattern_parts = []
        for i in range(avail):
            if (file_off + i) in reloc_set:
                pattern_parts.append('..')
            else:
                pattern_parts.append('%02X' % pe_data[file_off + i])

        # Pad if function is shorter than PATTERN_LEN
        if avail < PATTERN_LEN:
            pattern_parts.extend(['..'] * (PATTERN_LEN - avail))

        pattern = ''.join(pattern_parts)

        # CRC over bytes after pattern
        crc_len = min(255, max(0, size - PATTERN_LEN))
        crc = 0
        if crc_len > 0 and file_off + PATTERN_LEN + crc_len <= len(pe_data):
            crc_data = pe_data[file_off + PATTERN_LEN:file_off + PATTERN_LEN + crc_len]
            crc = crc16_flair(crc_data, reloc_set, file_off + PATTERN_LEN)

        # .pat format line
        line = '%s %02X %04X %04X :0000 %s' % (
            pattern, crc_len & 0xFF, crc & 0xFFFF, size & 0xFFFF, name
        )
        pat_lines.append(line)

    pat_lines.append("---")

    print("[*] 生成签名: %d (跳过: %d)" % (len(pat_lines) - 1, skipped))

    # Write output
    os.makedirs(os.path.dirname(OUTPUT_PAT), exist_ok=True)
    with open(OUTPUT_PAT, 'w', encoding='utf-8') as f:
        f.write('\n'.join(pat_lines))
        f.write('\n')

    print("[*] 输出: %s" % OUTPUT_PAT)
    print("[*] 下一步: sigmake %s pal3a_text.sig" % os.path.basename(OUTPUT_PAT))

    # Stats
    sizes = [s for _, s, _ in text_funcs]
    if sizes:
        print("[*] 统计: min=%d, max=%d, avg=%d, total=%dKB" % (
            min(sizes), max(sizes), sum(sizes) // len(sizes), sum(sizes) // 1024))

    return 0


if __name__ == '__main__':
    sys.exit(main())
