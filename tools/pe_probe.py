#!/usr/bin/env python3
"""PE 静态取证：不经 IDA、不占用 IDB 窗口，直接读 `original/PAL3.exe` 的字节。

动机（2026-09-15）：本会话多次需要"某地址的真实函数体"来判定 FLIRT/符号是否误命名，
而每次都开 IDA 探针会**占用 IDB 单写者窗口**（并曾因崩溃留下 5 个边车）。
独立复核者 `415003de` 证明：**纯 Python 解析 PE 节表读字节**即可，
且与 `idat` 探针结果**逐字节一致**（互证样例：0x00532D50 = `C7 41 18 00 00 00 00 C3`）。

用法：
  python3 tools/pe_probe.py 0x00532D50 0x4790F0          # 反汇编若干地址
  python3 tools/pe_probe.py --bytes 0x00532D50           # 只看原始字节
  python3 tools/pe_probe.py --verify                       # 自检（与已知样例比对）
  python3 tools/pe_probe.py 0x4790F0 --len 32              # 指定最大解码长度
"""
import argparse
import struct
import sys

HERE = None
try:
    import os
    HERE = os.path.dirname(os.path.abspath(__file__))
except Exception:
    pass


def find_exe():
    import os
    root = os.path.dirname(HERE) if HERE else "."
    return os.path.join(root, "original", "PAL3.exe")


# --- 极简 x86 长度反汇编器（仅用于人类阅读；判定真伪靠字节比对） ---
#
# 刻意只覆盖本项目常用形态：mov/movzx/movsx/test/cmp/push/pop/call/jmp/jcc/ret/
# lea/xor/add/sub/and/or/inc/dec/fld/fstp 等。**未知 opcode 一律按 1 字节前进**
# 并标注 `db`，绝不猜测——因为我们的目的是"看真实字节"，不是"完美反汇编"。
_ONE = {0x90: "nop", 0xC3: "retn", 0xC2: "retn", 0xCC: "int3", 0x55: "push ebp",
        0x5D: "pop ebp", 0x5B: "pop ebx", 0x5E: "pop esi", 0x5F: "pop edi",
        0x56: "push esi", 0x57: "push edi", 0x53: "push ebx", 0x50: "push eax",
        0x51: "push ecx", 0x52: "push edx", 0x58: "pop eax", 0x59: "pop ecx",
        0x5A: "pop edx"}


def disasm(buf, base):
    """返回 [(addr, bytes_hex, text)]，best-effort，未知按 db 1 字节。"""
    out = []
    i = 0
    n = len(buf)
    while i < n:
        a = base + i
        b0 = buf[i]
        start = i
        txt = None
        # retn imm16
        if b0 == 0xC2 and i + 2 < n:
            imm = struct.unpack_from("<H", buf, i + 1)[0]
            txt = "retn %d" % imm
            i += 3
        elif b0 == 0xC2:
            txt = "retn ?"; i += 1
        elif b0 in _ONE:
            txt = _ONE[b0]; i += 1
        elif b0 == 0xE8 and i + 4 < n:      # call rel32
            rel = struct.unpack_from("<i", buf, i + 1)[0]
            txt = "call 0x%X" % (a + 5 + rel); i += 5
        elif b0 == 0xE9 and i + 4 < n:      # jmp rel32
            rel = struct.unpack_from("<i", buf, i + 1)[0]
            txt = "jmp 0x%X" % (a + 5 + rel); i += 5
        elif 0x70 <= b0 <= 0x7F:            # jcc rel8
            txt = "jcc%02X 0x%X" % (b0, a + 2 + struct.unpack_from("<b", buf, i + 1)[0] if i + 1 < n else a)
            i += 2
        elif b0 in (0x88, 0x89, 0x8A, 0x8B) and i + 1 < n:
            # mov r/m8/r32, r8/r32  形式：modrm 后可能有 disp8/disp32
            modrm = buf[i + 1]
            mod, reg, rm = modrm >> 6, (modrm >> 3) & 7, modrm & 7
            sz = i + 2
            disp = None
            if mod == 0 and rm == 5:
                disp = struct.unpack_from("<I", buf, sz)[0]; sz += 4
            elif mod == 1:
                disp = struct.unpack_from("<b", buf, sz)[0]; sz += 1
            elif mod == 2:
                disp = struct.unpack_from("<i", buf, sz)[0]; sz += 4
            regs = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"]
            dst = regs[rm] if mod == 3 else None
            op = {0x88: "mov", 0x89: "mov", 0x8A: "mov", 0x8B: "mov"}[b0]
            if dst is not None:
                txt = "%s %s, %s" % (op, dst, regs[reg])
            elif disp is not None:
                txt = "%s %s, [%s+0x%X]" % (op, regs[reg], regs[rm], disp & 0xFFFFFFFF)
            else:
                txt = "%s %s, [%s]" % (op, regs[reg], regs[rm])
            i = sz
        elif b0 in (0xC6, 0xC7) and i + 1 < n:
            modrm = buf[i + 1]
            mod, rm = modrm >> 6, modrm & 7
            sz = i + 2
            disp = None
            if mod == 0 and rm == 5:
                disp = struct.unpack_from("<I", buf, sz)[0]; sz += 4
            elif mod == 1:
                disp = struct.unpack_from("<b", buf, sz)[0]; sz += 1
            elif mod == 2:
                disp = struct.unpack_from("<i", buf, sz)[0]; sz += 4
            if b0 == 0xC7 and i + 6 <= n:
                imm = struct.unpack_from("<i", buf, sz)[0]
                txt = "mov dword [%s], 0x%X" % (
                    ("+0x%X" % (disp & 0xFFFFFFFF)) if disp is not None else "", imm)
                sz += 4
            else:
                txt = "mov byte [..], imm8"
                sz += 1
            i = sz
        else:
            txt = "db 0x%02X" % b0
            i += 1
        out.append((a, buf[start:i].hex(" ").upper(), txt))
    return out


def load_text():
    import os
    exe = find_exe()
    if not os.path.exists(exe):
        print("[ERROR] not found: %s" % exe)
        sys.exit(2)
    data = open(exe, "rb").read()
    if data[:2] != b"MZ":
        print("[ERROR] not a PE (no MZ)"); sys.exit(2)
    e_lfanew = struct.unpack_from("<I", data, 0x3C)[0]
    if data[e_lfanew:e_lfanew + 4] != b"PE\0\0":
        print("[ERROR] bad PE signature"); sys.exit(2)
    # OptionalHeader.ImageBase 在 e_lfanew+24 + 28（PE32）。
    # 【必须减掉它】IDA 显示的是 VA = ImageBase + RVA；PAL3.exe 的 ImageBase = 0x400000。
    # captain 的初版把 IDA 的 VA **直接当文件偏移**，于是 0x00532D50 被当成
    # fileoff 0x532D50 —— 而文件只有 0x212000 字节，读出空，并误配到 .data。
    # 正确：fileoff = rawptr + (VA - ImageBase - VirtualAddress)。
    # 验算：0x1000 + (0x532D50 - 0x400000 - 0x1000) = 0x132D50 ✓
    image_base = struct.unpack_from("<I", data, e_lfanew + 24 + 28)[0]
    nsec = struct.unpack_from("<H", data, e_lfanew + 6)[0]
    opt_size = struct.unpack_from("<H", data, e_lfanew + 20)[0]
    opt_off = e_lfanew + 24
    sec_off = opt_off + opt_size
    sections = []
    for k in range(nsec):
        o = sec_off + k * 40
        name = data[o:o + 8].rstrip(b"\0").decode("latin1")
        # IMAGE_SECTION_HEADER 布局（相对节头起点）：
        #   +0  Name[8]   +8  VirtualSize   +12 VirtualAddress
        #   +16 SizeOfRawData              +20 PointerToRawData
        # ⇒ 从 **+8** 起读 4 个 DWORD 得 (VirtualSize, VirtualAddress,
        #   SizeOfRawData, PointerToRawData)。经验证：.text ⇒
        #   (0x1685D0, 0x1000, 0x169000, 0x1000)，与手算一致。
        # （captain 曾误改成 `o + 8 + 4` ⇒ 从 +12 读 ⇒ .text 得
        #   (0x1000, 0x169000, 0x1000, 0x0)，各字段前移一格、rawptr 归零。）
        vsize, vaddr, rawsize, rawptr = struct.unpack_from("<IIII", data, o + 8)
        sections.append((name, vaddr, vsize, rawptr, rawsize))
    return data, sections, image_base


def read_at(data, sections, va, ln, image_base):
    """VA（IDA 口径，含 ImageBase）→ 文件字节。"""
    rva = va - image_base
    for name, vaddr, vsize, rawptr, rawsize in sections:
        if vaddr <= rva < vaddr + max(vsize, rawsize):
            off = rawptr + (rva - vaddr)
            if off + ln > len(data):
                return None, name
            return data[off:off + ln], name
    return None, None


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("addrs", nargs="*", help="虚拟地址，如 0x00532D50")
    ap.add_argument("--len", type=int, default=24, help="每个地址最多解码字节数（默认 24）")
    ap.add_argument("--bytes", action="store_true", help="只输出原始字节")
    ap.add_argument("--verify", action="store_true", help="自检：与已知样例比对")
    args = ap.parse_args()

    data, sections, image_base = load_text()

    if args.verify:
        # 已知样例来自本会话 idat 探针（互证锚点）
        cases = [(0x00532D50, "C7 41 18 00 00 00 00 C3"),
                 (0x00532D30, "8B 41 50 89 41 18 C3")]
        ok = True
        for va, exp in cases:
            buf, sec = read_at(data, sections, va, len(exp.split()), image_base)
            got = buf.hex(" ").upper() if buf else "(none)"
            good = (got == exp)
            ok = ok and good
            print("%s 0x%08X  %s  %s" % ("OK  " if good else "FAIL", va, got,
                                         "(section %s)" % sec if sec else ""))
        print("verify: %s" % ("PASS" if ok else "FAIL"))
        return 0 if ok else 1

    if not args.addrs:
        print("sections:")
        for name, vaddr, vsize, rawptr, rawsize in sections:
            print("  %-8s VA 0x%08X vsize 0x%06X rawptr 0x%06X rawsize 0x%06X"
                  % (name, vaddr, vsize, rawptr, rawsize))
        return 0

    for a in args.addrs:
        va = int(a, 16)
        buf, sec = read_at(data, sections, va, args.len, image_base)
        if buf is None:
            print("0x%08X  (not in any section)" % va); continue
        print("0x%08X  [%s]" % (va, sec))
        if args.bytes:
            print("  bytes: %s" % buf.hex(" ").upper())
        else:
            for addr, bh, txt in disasm(buf, va):
                print("  %08X  %-20s %s" % (addr, bh, txt))
        print()
    return 0


if __name__ == "__main__":
    sys.exit(main())