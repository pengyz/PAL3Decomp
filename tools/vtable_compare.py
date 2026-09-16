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


# ️ 2026-09-15 修：原正则 `(?:[0-9a-f]{2} )+` **要求每个字节后都有空格**，
# 而 objdump 对指令字节做**列对齐**：
#   6 字节指令 `c7 06 00 a6 56 00   movl ...`（字节后**单空格**）⇒ 原正则**匹配失败**
#   7 字节指令 `c7 45 00 e4 f5 56 00  movl ...`（**双空格**）⇒ 匹配成功
# ⇒ 原实现只收集到"**奇数字节**"的 vptr 写（476 条），**丢掉全部偶数字节形态**
#   （`c7 06`/`c7 00`/`c7 01`…即 `mov [reg],imm32`，正是最常见的 vptr 写）
#   实测后果：`AStarPathFinder` 的表 0x56A600（写在 `401007: c7 06 00 a6 56 00`）
#   不在集合里 ⇒ 注解 93 个表地址与它只有 **7 个交集**的假象由此而来。
# 修法：字节串与助记符之间用 `\s+`，且不要求每字节后都有空格。
# ⚠️ 正则踩坑记录（2026-09-15，本会话在此错了 4 次，逐条留痕）：
#   objdump 对指令字节做**列对齐**，且不同长度的指令字节数与空格数不同：
#     6 字节 `c7 06 00 a6 56 00    \tmovl ...`（无位移 `(%esi)`）
#     7 字节 `c7 45 00 e4 f5 56 00 \tmovl ...`（有位移 `0x0(%ebp)`）
#   错误写法与后果：
#     ① `(?:[0-9a-f]{2} )+`（每字节后必须空格）⇒ 只命中"奇数字节"的行；
#     ② 加了 `\s*` 后再写 `(?:[0-9a-f]{2}\s+)+` ⇒ 字节组的尾部 `\s+` 把 `movl` 前的
#        空隙吃掉，`movl` 处无空白可匹配 ⇒ **匹配失败**（两个量词不能共享同一段空白）；
#     ③ 把位移写成 `(?:0x0\()?` ⇒ 要求字面量 `0x0`，**无位移形态全丢**（丢掉了 AStarPathFinder 的表）。
#   ✅ 正确形态：`(?:\s*[0-9a-f]{2})+` —— **`\s*` 在每字节之前**，最后一段空隙留给 `\s+movl?`。
#   实测：修前收集 467 条（= 仅"有位移"形态），修后实测见 tools 自检。
_VPTR_WRITE = re.compile(
    r'^\s*[0-9a-f]+:\s+'
    r'(?:\s*[0-9a-f]{2})+'
    r'\s+movl?\s+'
    r'\$0x(5[0-9a-f]{5})'
    r',\s*'
    r'(?:0x[0-9a-f]+)?\(%[a-z]+\)',
    re.M)


def bin_vptr_targets(dis_path='/tmp/pal3.dis'):
    """从反汇编里收集 ctor 实写的 vptr 目标（= 各表起始地址）。"""
    # ️ 必须按 EXE 的 mtime 判断新鲜度——**不能只看"文件存在"**：
    # 2026-09-15 踩坑：修正则后复用陈旧的 /tmp/pal3.dis，导致结果不变（467→467），
    # 一度让我以为修复无效。改为：反汇编文件比 EXE 旧就重建。
    need = (not os.path.exists(dis_path)
            or os.path.getmtime(dis_path) < os.path.getmtime(EXE))
    if need:
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


def class_family(name):
    """从一个函数名里提"它属于哪个类族"（用于槽位归属一致性判据）。

    `?DestroyEffBase@RenderTarget2@@QAEHXZ` → `RenderTarget2`
    `CEffCylinder::Create`                 → `CEffCylinder`
    `??0CEffShock@@QAE@XZ`                 → `CEffShock`
    提不出（`sub_xxx` / `unknown_libname_*` / 空）→ None
    """
    if not name:
        return None
    if '::' in name:
        return name.split('::')[0]
    if name.startswith('?'):
        s = name
        for p in ('??_7', '??_G', '??_E', '??0', '??1', '??2', '??3'):
            if s.startswith(p):
                s = s[len(p):]
                break
        else:
            s = s[1:]
            m = re.match(r'^[^@]*@(.+)$', s)
            if not m:
                return None
            s = m.group(1)
        m = re.match(r'^([^@]+)@', s)
        return m.group(1) if m else None
    return None


def bin_table(base, targets, idx=None):
    """界定二进制表长，返回 (槽位地址列表, end, confidence, broken_at, family)。

    ## 为什么需要"归属一致性"判据（2026-09-15 修）

    原先只用"**下一个 ctor 实写地址**"作边界 ⇒ 在**多继承的连续子表**排布下失效：
    实测 `CEffShock` 的三张表被读出 **28 槽 / 43 槽**，里面混进了
    `RenderTarget2::CalcDeltaTime`、`CEffQuake::AllocSegments` 等**别的类**的函数
    ⇒ 无法据此写 `vtables` 注解（违反"禁止未验证修改"）。

    ## 判据（三信号）

    1. **硬上界**：下一个 ctor 实写地址（原有逻辑）；
    2. **非 `.text` 槽**：直接断（`.rdata`/数据/0）；
    3. **归属一致性**：从槽 0 的类族出发，**一旦出现"可识别为其它类族"的槽，表在该槽结束**。
       提不出类族的槽（`sub_`/无名）**不算断裂**。

    ⚠️ 仍是启发式：`confidence` 用于告知可信度（`high` = 未发生归属断裂；
    `low` = 发生过 ⇒ 可能是子表续接，需人工核）。
    """
    nxt = [t for t in targets if t > base]
    hard_end = nxt[0] if nxt else base + 0x400
    data = _exe()
    if idx is None:
        idx = va_index()

    from vtable_scanner import in_section  # 复用节判定（SECTIONS 由调用方加载）

    fam = class_family(idx.get(read_dword(base, data), ''))
    slots = []
    end = hard_end
    broken_at = None
    a = base
    while a + 4 <= hard_end:
        v = read_dword(a, data)
        if not in_section(v, '.text'):
            end = a
            break
        f = class_family(idx.get(v, ''))
        if fam and f and f != fam:
            end = a
            broken_at = '%s(0x%X)' % (f, v)
            break
        slots.append(v)
        a += 4
    else:
        end = a
    conf = 'high' if broken_at is None else 'low'
    return slots, end, conf, broken_at, fam


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
        import vtable_scanner as _vs
        _vs.SECTIONS = _vs.load_sections()
        idx = va_index()
        slots, end, conf, broken, fam = bin_table(base, targets, idx)
        print('二进制表 0x%X .. 0x%X （%d 槽）' % (base, end, len(slots)))
        print('  类族=%s  置信=%s%s' % (fam, conf,
              ('  在 %s 处断裂（别的类族）' % broken) if broken else ''))
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