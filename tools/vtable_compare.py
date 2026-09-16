#!/usr/bin/env python3
"""vtable 逐槽对比：**编译产物合成表** vs **二进制真实表**（C-V 前提的判定工具）。

## 为什么需要第三个工具

- `tools/vtable_scanner.py` 读**二进制**，但它的终止判据（"遇到非 `.text` 指针即停"）
  在本项目**失效**：实测 `CEffAction` 表 `0x56F5E4` 读出了 **96 槽**，
  因为 `0x56F5E4` 之后**所有 DWORD 都落在 `.text`**（多张相邻表连续排布）。
  ⇒ 它无法界定表边界。
- `tools/coff_vtable.py` 读**编译产物**，但只给出槽位的**符号名**，没有地址。

**本工具用"ctor 实写的 vptr 地址"界定边界**：实测 `original/PAL3.exe` 里有 **467 个**
`movl $0x5xxxxx, (%reg)` 形式的 vptr 存储，其目标就是各表的**起始地址**。
相邻两个起始地址之间的差 = 前一张表的长度（精确，不靠启发式）。

**两侧可比的关键**：把编译产物侧的槽位**符号名**与二进制侧的**地址**都归约到
**"函数 VA"**（通过 mangled 名 → 注解/decomp 的 VA 反查），再比序列。

用法：
    python3 tools/vtable_compare.py --obj /tmp/x.obj --bin-base 0x56F7C8
    python3 tools/vtable_compare.py --list-bin            # 列出所有 ctor 实写的表起始
"""
import argparse
import glob
import json
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))

EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
RDATA_VA, RDATA_RAW = 0x56A000, 0x16A000
RDATA_END = 0x580000


def _exe():
    with open(EXE, 'rb') as f:
        return f.read()


def read_dword(va, data=None):
    if data is None:
        data = _exe()
    off = RDATA_RAW + (va - RDATA_VA)
    return struct.unpack_from('<I', data, off)[0]


_VPTR_WRITE = re.compile(
    r'^\s*[0-9a-f]+:\s+(?:[0-9a-f]{2} )+\s*movl?\s+\$0x(5[0-9a-f]{5}),(?:0x0\()?(%[a-z]+)\)?',
    re.M)


def bin_vptr_targets(dis_path='/tmp/pal3.dis'):
    """从反汇编里收集 ctor 实写的 vptr 目标（= 各表起始地址）。"""
    if not os.path.exists(dis_path):
        import subprocess
        with open(dis_path, 'w') as f:
            f.write(subprocess.run(['objdump', '-d', EXE], capture_output=True,
                                   text=True, cwd=ROOT).stdout)
    out = set()
    with open(dis_path) as f:
        for ln in f:
            m = _VPTR_WRITE.match(ln)
            if m:
                v = int(m.group(1), 16)
                if RDATA_VA <= v < RDATA_END:
                    out.add(v)
    return sorted(out)


def bin_table(base, targets):
    """按"下一个 ctor 实写地址"界定表长，返回槽位地址列表。"""
    nxt = [t for t in targets if t > base]
    end = nxt[0] if nxt else base + 0x400
    n = (end - base) // 4
    data = _exe()
    return [read_dword(base + i * 4, data) for i in range(n)], end


def va_index():
    """VA -> 名字（decomp + 注解 functions + 注解 struct methods）。"""
    idx = {}
    for p in glob.glob(os.path.join(ROOT, 'asm', 'pal3', 'decomp', '*.json')):
        try:
            with open(p, encoding='utf-8') as f:
                d = json.load(f)
        except (OSError, json.JSONDecodeError):
            continue
        if d.get('address'):
            idx[int(d['address'], 16)] = d.get('name')
    try:
        with open(os.path.join(ROOT, 'data', 'annotations', 'functions.json'),
                  encoding='utf-8') as f:
            for a, v in json.load(f).items():
                try:
                    idx.setdefault(int(a, 16), (v or {}).get('name'))
                except (ValueError, TypeError):
                    continue
    except (OSError, json.JSONDecodeError):
        pass
    for p in glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json')):
        try:
            with open(p, encoding='utf-8') as f:
                d = json.load(f)
        except (OSError, json.JSONDecodeError):
            continue
        cls = d.get('name')
        for a, m in (d.get('methods') or {}).items():
            try:
                idx.setdefault(int(a, 16), '%s::%s' % (cls, (m or {}).get('name')))
            except (ValueError, TypeError):
                continue
    return idx


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument('--obj', help='编译产物 .obj（取合成表）')
    ap.add_argument('--bin-base', help='二进制表起始 VA，如 0x56F7C8')
    ap.add_argument('--list-bin', action='store_true', help='列出所有表起始地址')
    ap.add_argument('--range', help='--list-bin 的过滤区间，如 56F5,56F8')
    args = ap.parse_args()
    targets = bin_vptr_targets()
    if args.list_bin:
        lo = hi = None
        if args.range:
            a, b = args.range.split(',')
            lo, hi = int(a, 16), int(b, 16)
        print('ctor 实写的表起始共 %d 个' % len(targets))
        for t in targets:
            if lo is not None and not (lo << 16 <= t <= (hi << 16) + 0xFFFF):
                continue
            print('  0x%X' % t)
        return 0
    if args.bin_base:
        base = int(args.bin_base, 16)
        slots, end = bin_table(base, targets)
        idx = va_index()
        print('二进制表 0x%X .. 0x%X （%d 槽，边界 = 下一个 ctor 实写地址）' % (base, end, len(slots)))
        for i, v in enumerate(slots):
            print('  [%2d] 0x%08X  %s' % (i, v, idx.get(v, '')))
    if args.obj:
        import coff_vtable as cv
        vt = cv.extract_vtables(args.obj)
        print('编译产物侧 vtable: %d' % len(vt))
        for k in sorted(vt):
            print('  %s' % k)
            for i, s in enumerate(vt[k]):
                print('     [%2d] %s' % (i, s))
    if not (args.list_bin or args.bin_base or args.obj):
        ap.print_help()
    return 0


if __name__ == '__main__':
    sys.exit(main())