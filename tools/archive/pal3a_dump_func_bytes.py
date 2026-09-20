"""
IDAPython: 从 PAL3A.exe.i64 导出所有函数的完整字节数据

输出格式: asm/pal3a/func_bytes.bin (自定义二进制格式，紧凑高效)
辅助索引: asm/pal3a/func_bytes_index.json

每个函数记录: 地址、大小、mangled_name、完整字节、重定位掩码
用于后续在 PAL3.exe IDB 中做严格字节对比匹配。

运行环境: PAL3A.exe.i64
"""

import ida_auto
import ida_bytes
import ida_fixup
import ida_funcs
import ida_name
import idautils
import idc
import json
import os
import struct
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(os.path.dirname(SCRIPT_DIR))
LOG_DIR = os.path.join(SCRIPT_DIR, "_logs")

PDB_EXPORT = os.path.join(PROJECT_ROOT, "asm", "pal3a", "pdb_export.json")
OUTPUT_JSON = os.path.join(PROJECT_ROOT, "asm", "pal3a", "func_bytes_dump.json")
LOG_FILE = os.path.join(LOG_DIR, "pal3a_dump_func_bytes_log.txt")

TEXT_START = 0x00401000
TEXT_END = 0x00558000
MIN_FUNC_SIZE = 4


def has_reloc(ea):
    fd = ida_fixup.fixup_data_t()
    return ida_fixup.get_fixup(fd, ea)


def extract_func_data(ea, size):
    """
    Extract function bytes and relocation mask.
    Returns (bytes_hex, reloc_mask_hex) where reloc positions are marked.
    Reloc mask: '1' = relocation byte (ignore in comparison), '0' = code byte (must match)
    """
    code_bytes = []
    reloc_mask = []

    # Find all relocation starts in this function
    reloc_positions = set()
    for i in range(size):
        if has_reloc(ea + i):
            # 32-bit relocation covers 4 bytes
            for j in range(4):
                if i + j < size:
                    reloc_positions.add(i + j)

    for i in range(size):
        b = ida_bytes.get_byte(ea + i)
        code_bytes.append(b)
        reloc_mask.append(1 if i in reloc_positions else 0)

    return bytes(code_bytes).hex(), ''.join(str(m) for m in reloc_mask)


def main():
    lines = []

    def log(msg):
        lines.append(str(msg))
        print(msg)

    try:
        ida_auto.auto_wait()
        log("[*] PAL3A 函数字节导出 (严格匹配用)")
        log("[*] .text: 0x%08X - 0x%08X" % (TEXT_START, TEXT_END))

        # Load PDB data for function names/addresses/sizes
        if not os.path.exists(PDB_EXPORT):
            log("[!] PDB 数据不存在: %s" % PDB_EXPORT)
            return

        with open(PDB_EXPORT, 'r', encoding='utf-8') as f:
            pdb_data = json.load(f)

        functions = pdb_data['functions']
        log("[*] PDB 函数: %d" % len(functions))

        # Filter to .text with valid size
        text_funcs = []
        for func in functions:
            addr = int(func['address'], 16)
            size = func.get('size', 0)
            mangled = func.get('mangled_name', '')
            name = func.get('name', '')
            if not mangled or size < MIN_FUNC_SIZE:
                continue
            if TEXT_START <= addr < TEXT_END:
                text_funcs.append((addr, size, mangled, name))

        # Deduplicate by address
        addr_map = {}
        for addr, size, mangled, name in text_funcs:
            if addr not in addr_map:
                addr_map[addr] = (size, mangled, name)

        log("[*] .text 函数 (去重): %d" % len(addr_map))

        # Extract bytes
        t0 = time.time()
        results = []
        skipped = 0

        for addr in sorted(addr_map.keys()):
            size, mangled, name = addr_map[addr]

            if not ida_bytes.is_loaded(addr):
                skipped += 1
                continue

            # Verify we can read all bytes
            if not ida_bytes.is_loaded(addr + size - 1):
                # Truncate to readable range
                actual_size = 0
                for i in range(size):
                    if ida_bytes.is_loaded(addr + i):
                        actual_size = i + 1
                    else:
                        break
                if actual_size < MIN_FUNC_SIZE:
                    skipped += 1
                    continue
                size = actual_size

            code_hex, reloc_mask = extract_func_data(addr, size)

            results.append({
                'addr': addr,
                'size': size,
                'mangled': mangled,
                'name': name,
                'bytes': code_hex,
                'reloc': reloc_mask,
            })

        elapsed = time.time() - t0
        log("[*] 提取完成: %d 函数, 跳过 %d (%.1fs)" % (len(results), skipped, elapsed))

        # Calculate total code bytes
        total_bytes = sum(r['size'] for r in results)
        total_reloc = sum(r['reloc'].count('1') for r in results)
        log("[*] 总字节: %d KB, 重定位字节: %d (%.1f%%)" % (
            total_bytes // 1024, total_reloc, 100.0 * total_reloc / total_bytes if total_bytes else 0))

        # Write output
        with open(OUTPUT_JSON, 'w', encoding='utf-8') as f:
            json.dump({
                'meta': {
                    'source': 'PAL3A.exe.i64',
                    'text_start': TEXT_START,
                    'text_end': TEXT_END,
                    'total_functions': len(results),
                    'total_bytes': total_bytes,
                    'timestamp': time.strftime("%Y-%m-%dT%H:%M:%S"),
                },
                'functions': results,
            }, f)

        file_size = os.path.getsize(OUTPUT_JSON)
        log("[*] 输出: %s (%.1f MB)" % (OUTPUT_JSON, file_size / 1024 / 1024))

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
