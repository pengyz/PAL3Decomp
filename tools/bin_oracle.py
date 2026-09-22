#!/usr/bin/env python3
"""**二进制裁判（IDB-无关）** —— 只读 `original/PAL3.exe` 的字节 + `objdump` 反汇编。

## 为什么（2026-09-22 工具链来源审计结论）

真正的 SoT 是 **原始 EXE 字节**，不是任何导出物 ✓。但此前的二进制裁判走 **MCP 会话**：
* 会话有 **idle TTL**，会突然失效 ✗（本会话踩过两次）
* MCP **持有 IDB ⇒ 阻塞 `apply`/`export`** ✗（R14）
⇒ 本模块把"扫 disp32 + 确认承载指令"做成**完全 IDB-无关** ✓：
直接读 PE 的 `.text` 窗口，用 `objdump -D -b binary -m i386` 反汇编（**一次建索引**，之后查询是字典查找 ✓）

## 来源等级（供上层标注）
* 本模块 = **O2**（纯反汇编）✓ 独立于注解与 IDB ✓
* `compare_pal3.exe_text_image()` = **O1**（原始字节）✓ —— 本模块建立在它之上 ✓
* 编译器布局/尺寸 = **O3** ✓
* IDB 导出物（`ida_structs.json` 的**结构体偏移**）= **注解的回声** ✗ ⇒ **不得单独作证据**

用法::

    python3 tools/bin_oracle.py --scan E0E00000          # 扫 disp32（小端字节十六进制）
    python3 tools/bin_oracle.py --confirm 0x423505 0xE0E0
    python3 tools/bin_oracle.py --at 0x423505
"""
import argparse
import bisect
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'pipeline'))

_WIN = None
_INSNS = None      # {va: (text, disp)}
_ADDRS = None      # sorted list of instruction VAs

# objdump 是 **AT&T** 语法：`0xe0e0(%eax)`；排除栈基址与立即数（`$0x…`）✓
ATT_DISP_RX = re.compile(r'(?<![\$\w])(-?)0x([0-9a-f]+)\(\s*%(e?[abcd]x|e?[sd]i|e?[sb]p|e?bp)\s*\)')


def text_window():
    """→ (image_base, text_bytes, text_rva, raw_size)（复用 O1 读取器 ✓）"""
    global _WIN
    if _WIN is None:
        import compare_pal3 as cp
        _WIN = cp.exe_text_image()
    return _WIN


def bytes_at(va, n):
    base, text, rva, raw = text_window()
    off = va - base - rva
    if off < 0 or off + n > len(text):
        return b''
    return text[off:off + n]


def scan(pattern, limit=32):
    """在 `.text` 里扫字节模式 → 命中处的 VA 列表 ✓（O2，独立于 IDB ✓）"""
    base, text, rva, raw = text_window()
    out, start = [], 0
    while len(out) < limit:
        i = text.find(pattern, start)
        if i < 0:
            break
        out.append(base + rva + i)
        start = i + 1
    return out


def disp_of(line):
    """从**一行 objdump 文本**取位移（成员访问）→ int 或 None ✓（纯函数）

    排除：`%esp`/`%ebp`（栈帧 ✗）· 立即数 `$0x…` ✗ · 负位移（成员偏移无意义 ✗）
    """
    m = ATT_DISP_RX.search(line or '')
    if not m:
        return None
    if m.group(3).lower().lstrip('e') in ('sp', 'bp'):
        return None
    if m.group(1) == '-':
        return None
    try:
        return int(m.group(2), 16)
    except Exception:
        return None


ABS_DISP_RX = re.compile(r'(?<![\$\w])0x([0-9a-f]{5,8})(?!\s*\()')


def abs_disp_of(line):
    """从一行 objdump 取**绝对地址**形态的位移（`mov 0xc057b8,%ecx`）→ int 或 None ✓

    用于**全局对象成员访问**（形态②）：`g_X.member` 编译成 `[g_X_addr + off]` 的**绝对地址** ✓
    （IDB 里的 MCP 版本会把该地址渲染成**符号名** ✗；objdump 给的是十六进制 ✓ 反而更直接）
    """
    m = ABS_DISP_RX.search(line or '')
    if not m:
        return None
    try:
        return int(m.group(1), 16)
    except Exception:
        return None


def confirm_abs_access(va, value):
    """确认 `va` 处承载指令引用的是**绝对地址** `value` ✓"""
    got = insn_covering(va)
    if not got:
        return False
    return abs_disp_of(got[1]) == value


def _build_index():
    """**一次**反汇编整个 `.text` 并建索引 ✓（之后查询是二分 + 字典 ✓）"""
    global _INSNS, _ADDRS
    if _INSNS is not None:
        return
    base, text, rva, raw = text_window()
    binpath = '/tmp/bin_oracle_text.bin'
    with open(binpath, 'wb') as f:
        f.write(text)
    r = subprocess.run(['objdump', '-D', '-b', 'binary', '-m', 'i386',
                        '--adjust-vma=0x%X' % (base + rva), binpath],
                       capture_output=True, text=True)
    ins, addrs = {}, []
    for line in r.stdout.split('\n'):
        m = re.match(r'^\s*([0-9a-f]+):\t[0-9a-f ]+\t(.*)$', line)
        if not m:
            continue
        try:
            va = int(m.group(1), 16)
        except Exception:
            continue
        ins[va] = (m.group(2).strip(), disp_of(m.group(2)))
        addrs.append(va)
    _INSNS, _ADDRS = ins, sorted(addrs)


def insn_covering(va):
    """→ (insn_va, text, disp)，若该 VA 落在某条指令内 ✓（否则 None）"""
    _build_index()
    i = bisect.bisect_right(_ADDRS, va) - 1
    if i < 0:
        return None
    a = _ADDRS[i]
    # 覆盖判定：下一条指令的地址必须 > va ✓（线性扫描的指令边界 ✓）
    if i + 1 < len(_ADDRS) and _ADDRS[i + 1] <= va:
        return None
    t, d = _INSNS[a]
    return (a, t, d)


def confirm_disp_access(va, off):
    """确认 `va` 处的**承载指令**访问的就是 `[reg+off]`（非栈 ✓）—— 取代 MCP 版确认 ✓"""
    got = insn_covering(va)
    if not got:
        return False
    return got[2] == off


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--scan', help='小端字节十六进制（如 E0E00000）')
    ap.add_argument('--confirm', nargs=2, metavar=('VA', 'OFF'))
    ap.add_argument('--at')
    ap.add_argument('--limit', type=int, default=16)
    ap.add_argument('--json', action='store_true')
    a = ap.parse_args()

    base, text, rva, raw = text_window()
    print('O1/O2 二进制裁判（IDB-无关）· image_base=0x%X · .text rva=0x%X · raw_size=0x%X'
          % (base, rva, raw))

    if a.scan:
        hits = scan(bytes.fromhex(a.scan), a.limit)
        print('扫描 %s ⇒ 命中 %d 处' % (a.scan, len(hits)))
        rows = []
        for va in hits[:a.limit]:
            got = insn_covering(va)
            rows.append({'va': '0x%X' % va, 'insn_va': ('0x%X' % got[0]) if got else None,
                         'insn': got[1] if got else None})
            print('   0x%-8X %s %s' % (va, ('(指令 0x%X)' % got[0]) if got else '', (got[1] if got else '')[:52]))
        if a.json:
            print(json.dumps(rows, ensure_ascii=False, indent=1))
    elif a.confirm:
        va = int(a.confirm[0], 16) if a.confirm[0].lower().startswith('0x') else int(a.confirm[0], 16)
        off = int(a.confirm[1], 16) if a.confirm[1].lower().startswith('0x') else int(a.confirm[1], 16)
        got = insn_covering(va)
        ok = confirm_disp_access(va, off)
        print('确认 0x%X ⇒ [reg+0x%X] ? %s   %s' % (va, off, ok, (got[1] if got else '(未找到承载指令)')[:60]))
    elif a.at:
        va = int(a.at, 16)
        got = insn_covering(va)
        print('0x%X ⇒ %s' % (va, got if got else '(未找到)'))
    return 0


if __name__ == '__main__':
    sys.exit(main())