"""
IDAPython: 从 PAL3A.exe.i64 提取 FLIRT 签名模式

运行环境: PAL3A.exe.i64 (已加载 PDB 符号)
输出: tools/ida/pal3a_text.pat (IDA FLIRT .pat 格式)

用法:
  idat64.exe -A -S"pal3a_create_sig.py" PAL3A.exe.i64

生成 .pat 后，使用 sigmake 转换为 .sig:
  sigmake pal3a_text.pat pal3a_text.sig

将 .sig 复制到 IDA 的 sig/ 目录，在 PAL3.exe IDB 中加载:
  File → Load file → FLIRT signature file
"""

import ida_auto
import ida_bytes
import ida_funcs
import ida_name
import ida_fixup
import idautils
import idc
import os
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

TEXT_START = 0x00401000
TEXT_END = 0x00558000

OUTPUT_PAT = os.path.join(SCRIPT_DIR, "pal3a_text.pat")
LOG_FILE = os.path.join(LOG_DIR, "pal3a_create_sig_log.txt")

# FLIRT pattern length (bytes to capture per function)
PATTERN_LEN = 32
# Minimum function size to include
MIN_FUNC_SIZE = 8


def has_reloc_at(ea):
    """Check if address has a relocation (fixup)"""
    return ida_fixup.get_fixup(ea) is not None


def get_pattern_bytes(ea, length):
    """
    Extract byte pattern with relocation wildcards.
    Returns (pattern_hex, mask) where masked positions use '..'
    """
    pattern = []
    for i in range(length):
        addr = ea + i
        if has_reloc_at(addr):
            # Mark relocation bytes as wildcard (4 bytes for 32-bit reloc)
            pattern.append('..')
        else:
            byte = ida_bytes.get_byte(addr)
            pattern.append('%02X' % byte)
    return ''.join(pattern)


def make_pat_line(ea, name, func_size):
    """
    Create a FLIRT .pat format line for a function.

    Format: PATTERN_HEX.. CRC_LEN CRC_VALUE FUNC_SIZE :OFFSET NAME [TAIL_BYTES]
    Simplified: just first PATTERN_LEN bytes + name
    """
    # Get actual bytes available (function might be shorter than PATTERN_LEN)
    avail = min(PATTERN_LEN, func_size)
    pattern = get_pattern_bytes(ea, avail)

    # Pad with wildcards if function is shorter than pattern length
    if avail < PATTERN_LEN:
        pattern += '..' * (PATTERN_LEN - avail)

    # Calculate CRC16 over bytes 32..32+crc_len (IDA FLAIR standard)
    # For simplicity, use the bytes after the pattern for CRC
    crc_len = min(255, max(0, func_size - PATTERN_LEN))
    crc = 0
    if crc_len > 0:
        for i in range(crc_len):
            addr = ea + PATTERN_LEN + i
            if not has_reloc_at(addr):
                byte = ida_bytes.get_byte(addr)
                # CRC16 update (FLAIR algorithm)
                crc ^= byte << 8
                for _ in range(8):
                    if crc & 0x8000:
                        crc = ((crc << 1) ^ 0x8005) & 0xFFFF
                    else:
                        crc = (crc << 1) & 0xFFFF

    # Format: PATTERN CRC_LEN CRC TOTAL_SIZE :0000 NAME
    # Additional referenced names with offsets can follow
    line = '%s %02X %04X %04X :0000 %s' % (
        pattern, crc_len & 0xFF, crc & 0xFFFF, func_size & 0xFFFF, name
    )
    return line


def main():
    log_lines = []

    def log(msg):
        log_lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] PAL3A FLIRT 签名提取")
        log("[*] .text range: 0x%08X - 0x%08X" % (TEXT_START, TEXT_END))

        # Collect named functions in .text
        targets = []
        for ea in idautils.Functions(TEXT_START, TEXT_END):
            if ea < TEXT_START or ea >= TEXT_END:
                continue
            name = ida_name.get_name(ea) or ""
            if not name:
                continue
            # Skip unnamed and auto-generated names
            if name.startswith("sub_") or name.startswith("nullsub_"):
                continue
            if name.startswith("j_") or name.startswith("unknown_"):
                continue
            func = ida_funcs.get_func(ea)
            if not func:
                continue
            size = func.size()
            if size < MIN_FUNC_SIZE:
                continue
            targets.append((ea, name, size))

        log("[*] 目标函数: %d" % len(targets))

        # Generate .pat file
        pat_lines = []
        skipped = 0

        for ea, name, size in targets:
            try:
                line = make_pat_line(ea, name, size)
                pat_lines.append(line)
            except Exception as e:
                skipped += 1
                if skipped <= 10:
                    log("  [!] Skip 0x%08X %s: %s" % (ea, name, str(e)))

        # FLIRT .pat terminator
        pat_lines.append("---")

        log("[*] 生成签名: %d (跳过: %d)" % (len(pat_lines) - 1, skipped))

        # Write .pat file
        with open(OUTPUT_PAT, 'w', encoding='utf-8') as f:
            f.write('\n'.join(pat_lines))
            f.write('\n')

        log("[*] 输出: %s" % OUTPUT_PAT)
        log("[*] 下一步: sigmake %s pal3a_text.sig" % os.path.basename(OUTPUT_PAT))

        # Size statistics
        sizes = [s for _, _, s in targets]
        log("[*] 函数大小统计:")
        log("    最小: %d bytes" % min(sizes))
        log("    最大: %d bytes" % max(sizes))
        log("    平均: %d bytes" % (sum(sizes) // len(sizes)))
        log("    总计: %d KB" % (sum(sizes) // 1024))

    except Exception as e:
        log("[!] 错误: %s" % str(e))
        import traceback
        log(traceback.format_exc())

    os.makedirs(LOG_DIR, exist_ok=True)
    with open(LOG_FILE, 'w', encoding='utf-8') as f:
        f.write('\n'.join(log_lines))


if __name__ == '__main__':
    main()
