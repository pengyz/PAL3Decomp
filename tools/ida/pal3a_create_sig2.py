"""
IDAPython: 从 PAL3A.exe.i64 按 PDB 地址提取 FLIRT 签名

不依赖 IDB 函数命名，直接用 PDB 地址+名称+IDB字节 生成 .pat 文件。
这避免了 IDA 命名冲突问题。

运行环境: PAL3A.exe.i64
输出: tools/ida/pal3a_text.pat
"""

import ida_auto
import ida_bytes
import ida_fixup
import ida_funcs
import idautils
import idc
import json
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
OUTPUT_PAT = os.path.join(SCRIPT_DIR, "pal3a_text.pat")
LOG_FILE = os.path.join(LOG_DIR, "pal3a_create_sig2_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x00558000
PATTERN_LEN = 32
MIN_FUNC_SIZE = 8


def has_reloc(ea):
    """Check if address has a fixup (relocation)"""
    fd = ida_fixup.fixup_data_t()
    return ida_fixup.get_fixup(fd, ea)


def get_pattern(ea, length):
    """Extract byte pattern with relocation wildcards from IDB"""
    # Find relocation positions
    reloc_bytes = set()
    for i in range(length):
        if has_reloc(ea + i):
            for j in range(4):
                if i + j < length:
                    reloc_bytes.add(i + j)

    parts = []
    for i in range(length):
        if i in reloc_bytes:
            parts.append('..')
        else:
            parts.append('%02X' % ida_bytes.get_byte(ea + i))
    return ''.join(parts)


def crc16(ea, length, max_len=255):
    """CRC16 over IDB bytes (FLAIR algorithm)"""
    actual_len = min(length, max_len)
    crc = 0
    for i in range(actual_len):
        if not has_reloc(ea + i):
            b = ida_bytes.get_byte(ea + i)
            crc ^= b << 8
            for _ in range(8):
                if crc & 0x8000:
                    crc = ((crc << 1) ^ 0x8005) & 0xFFFF
                else:
                    crc = (crc << 1) & 0xFFFF
    return crc, actual_len


def main():
    lines = []

    def log(msg):
        lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] PAL3A FLIRT 签名提取 (PDB-guided, IDB bytes)")

        if not os.path.exists(PDB_EXPORT):
            log("[!] 找不到 PDB 数据: %s" % PDB_EXPORT)
            return

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        functions = pdb_data['functions']
        log("[*] PDB 函数总数: %d" % len(functions))

        # Collect .text functions with valid size
        text_funcs = []
        for func in functions:
            addr = int(func['address'], 16)
            size = func.get('size', 0)
            mangled = func.get('mangled_name', '')
            if not mangled:
                continue
            if size < MIN_FUNC_SIZE:
                continue
            if TEXT_START <= addr < TEXT_END:
                text_funcs.append((addr, size, mangled))

        log("[*] .text 函数 (size >= %d): %d" % (MIN_FUNC_SIZE, len(text_funcs)))

        # Deduplicate by address (some PDB entries might overlap)
        addr_map = {}
        for addr, size, name in text_funcs:
            if addr not in addr_map or len(name) > len(addr_map[addr][1]):
                addr_map[addr] = (size, name)

        unique_funcs = [(addr, size, name) for addr, (size, name) in sorted(addr_map.items())]
        log("[*] 去重后: %d" % len(unique_funcs))

        # Check IDB has bytes at these addresses
        readable = 0
        unreadable = 0
        for addr, size, name in unique_funcs:
            if ida_bytes.is_loaded(addr):
                readable += 1
            else:
                unreadable += 1

        log("[*] IDB 可读: %d, 不可读: %d" % (readable, unreadable))

        # Generate .pat
        pat_lines = []
        skipped = 0

        for addr, size, name in unique_funcs:
            if not ida_bytes.is_loaded(addr):
                skipped += 1
                continue

            # Get pattern bytes (first PATTERN_LEN bytes)
            avail = min(PATTERN_LEN, size)
            try:
                pattern = get_pattern(addr, avail)
            except Exception:
                skipped += 1
                continue

            # Pad if needed
            if avail < PATTERN_LEN:
                pattern += '..' * (PATTERN_LEN - avail)

            # CRC over remaining bytes
            crc_len = min(255, max(0, size - PATTERN_LEN))
            crc = 0
            if crc_len > 0 and ida_bytes.is_loaded(addr + PATTERN_LEN):
                crc, crc_len = crc16(addr + PATTERN_LEN, crc_len)

            # .pat format
            line = '%s %02X %04X %04X :0000 %s' % (
                pattern, crc_len & 0xFF, crc & 0xFFFF, size & 0xFFFF, name
            )
            pat_lines.append(line)

        pat_lines.append("---")
        log("[*] 生成签名: %d (跳过: %d)" % (len(pat_lines) - 1, skipped))

        with open(OUTPUT_PAT, 'w', encoding='utf-8') as f:
            f.write('\n'.join(pat_lines))
            f.write('\n')

        log("[*] 输出: %s" % OUTPUT_PAT)
        log("[*] 下一步:")
        log("    1. sigmake pal3a_text.pat pal3a_text.sig")
        log("    2. 复制 .sig 到 IDA sig/ 目录")
        log("    3. 在 PAL3.exe IDB 中: File → Load → FLIRT signature")

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(lines))

    idc.qexit(0)


if __name__ == '__main__':
    main()
