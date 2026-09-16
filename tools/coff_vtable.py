#!/usr/bin/env python3
"""从 COFF `.obj`（VC6 产物）提取**编译器合成的 vtable**，供 C-V 前提验证。

## 为什么需要它（这是本工具存在的唯一理由）

C-V 设计（`docs/specs/2026-09-15-cv-layout-design.md`）主张"vtable 表示收口到 C++ `virtual`，
由编译器合成表"。复核者 `ad32c455` 只验证了**结构**同构（槽序/override 原位替换/thunk 形态），
**从未验证**关键前提：

    **VC6 实际合成的 vtable，与二进制里的真实表，是否逐槽一致？**

若不一致 ⇒ "用 `virtual`" 这条路线在**原理上**就不能字节匹配 ⇒ 应放弃并改设计（省 3–5 天）。
若一致 ⇒ 布局修复（方案 3）才值得投入。

**注意 P3 判据的恒真陷阱**：`tools/vtable_scanner.py` 读的是**二进制**，
若拿它与"二进制"比就是自比自（恒真）。本工具提供**编译产物侧**，两侧分开才有意义。

## 做法

  `??_7<Cls>@@6B@` 是 vtable 符号（`??_7` 前缀 = vftable；`6B` = vftable 段选择）。
  遍历 COFF 符号表找到它 → 读其所在 section 的 DWORD 序列 →
  每个 DWORD 位置若有 `IMAGE_REL_I386_DIR32` 重定位，则解出**目标符号名**（槽位的函数名）。
  ⇒ 得到**槽位函数名序列**，可与二进制侧（`vtable_scanner` 取到的槽位地址 → 函数名）逐槽比对。

## 已知坑（复核者实测，务必保留）

  - **reloc 的符号索引是原始 COFF 索引**（含 aux 占位）⇒ 必须按**原始索引**建映射，
    不能按"遍历到的第 i 个"计数，否则 aux 符号会造成错位。
  - reloc 覆盖 **4 字节**，需把该 4 字节全部登记，避免把中间字节误当槽位边界。
  - 表首可能是 RTTI COL 指针（`/GR` 下 `vtable[-1] = ??_R4...`）。

用法：
    python3 tools/coff_vtable.py /tmp/cvt/t.obj              # 列出该 obj 的所有 vtable
    python3 tools/coff_vtable.py /tmp/cvt/t.obj --cls CEffCylinder
    python3 tools/coff_vtable.py --selfcheck                  # 自检
"""
import argparse
import os
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def parse_obj(path):
    """返回 (sections, symbols_raw, name_of_index, reloc_targets)。

    `symbols_raw`: 按**原始 COFF 索引**排列的 {index: {...}}（含 aux 条目占位），
    这样 relocation 里的 symbol index 可以直接查表（复核者点名的坑）。
    `reloc_targets`: {(sec_idx, offset): target_symbol_name} —— DIR32 重定位的目标名。
    """
    with open(path, 'rb') as f:
        data = f.read()
    num_sections = struct.unpack_from('<H', data, 2)[0]
    sym_off = struct.unpack_from('<I', data, 8)[0]
    num_syms = struct.unpack_from('<I', data, 12)[0]
    opt_hdr = struct.unpack_from('<H', data, 16)[0]
    str_tab = sym_off + num_syms * 18

    def read_name(field):
        if field[0:4] == b'\x00\x00\x00\x00':
            o = struct.unpack_from('<I', field, 4)[0]
            end = data.index(b'\x00', str_tab + o)
            return data[str_tab + o:end].decode('ascii', errors='replace')
        return field.rstrip(b'\x00').decode('ascii', errors='replace')

    # --- sections ---
    sections = []
    so = 20 + opt_hdr
    for _ in range(num_sections):
        nb = data[so:so + 8]
        vsz, va, rsz, roff = struct.unpack_from('<IIII', data, so + 8)
        reloc_off = struct.unpack_from('<I', data, so + 24)[0]
        nrel = struct.unpack_from('<H', data, so + 32)[0]
        chars = struct.unpack_from('<I', data, so + 36)[0]
        if nb[0:1] == b'/':
            o = int(nb[1:].rstrip(b'\x00').decode())
            end = data.index(b'\x00', str_tab + o)
            nm = data[str_tab + o:end].decode('ascii', errors='replace')
        else:
            nm = nb.rstrip(b'\x00').decode('ascii', errors='replace')
        sections.append({'name': nm, 'data': data[roff:roff + rsz] if roff else b'',
                         'raw_size': rsz, 'chars': chars,
                         'relocs': [], 'reloc_off': reloc_off, 'nrel': nrel})
        so += 40

    # --- symbols, by RAW index (aux entries occupy indices) ---
    by_index = {}
    raw_names = {}
    i = 0
    while i < num_syms:
        o = sym_off + i * 18
        nm = read_name(data[o:o + 8])
        val = struct.unpack_from('<I', data, o + 8)[0]
        sec = struct.unpack_from('<h', data, o + 12)[0]
        typ = struct.unpack_from('<H', data, o + 14)[0]
        st = data[o + 16]
        naux = data[o + 17]
        by_index[i] = {'name': nm, 'value': val, 'section': sec,
                       'type': typ, 'storage': st, 'naux': naux}
        raw_names[i] = nm
        i += 1 + naux

    # --- relocations: resolve target symbol via RAW index ---
    reloc_targets = {}
    for si, sec in enumerate(sections):
        if not sec['nrel'] or not sec['reloc_off']:
            continue
        for r in range(sec['nrel']):
            ro = sec['reloc_off'] + r * 10
            rva, sym_idx, rtype = struct.unpack_from('<IIH', data, ro)
            tgt = raw_names.get(sym_idx, '?idx%d' % sym_idx)
            if rtype == 0x0006:      # IMAGE_REL_I386_DIR32
                reloc_targets[(si, rva)] = tgt
    return sections, by_index, reloc_targets


def extract_vtables(path):
    """返回 {vtable_symbol: [slot_target_name_or_None, ...]}。"""
    sections, by_index, reloc = parse_obj(path)
    out = {}
    for idx, sym in by_index.items():
        nm = sym['name']
        if not nm.startswith('??_7'):
            continue
        si = sym['section'] - 1
        if si < 0 or si >= len(sections):
            continue
        sec = sections[si]
        base = sym['value']
        slots = []
        off = base
        # 连续读到 section 尾或遇到"非重定位且值为 0"的终止
        while off + 4 <= sec['raw_size']:
            tgt = reloc.get((si, off))
            if tgt is not None:
                slots.append(tgt)
                off += 4
                continue
            raw = struct.unpack_from('<I', sec['data'], off)[0] if off + 4 <= len(sec['data']) else 0
            if raw == 0:
                slots.append(None)
                off += 4
                # 连续两个空槽即认为表结束
                nxt = reloc.get((si, off))
                raw2 = struct.unpack_from('<I', sec['data'], off)[0] if off + 4 <= len(sec['data']) else 0
                if nxt is None and raw2 == 0:
                    break
                continue
            break
        out[nm] = slots
    return out


def _selfcheck():
    """自检：用固定源码编一个已知类，验证提取出的槽序与 override 语义。"""
    import tempfile
    src = os.path.join(tempfile.gettempdir(), 'cvt_selfcheck.cpp')
    obj = os.path.join(tempfile.gettempdir(), 'cvt_selfcheck.obj')
    with open(src, 'w') as f:
        f.write('class B { public: virtual ~B(); virtual int f1(); virtual int f2(); };\n'
                'class D : public B { public: ~D(); int f1(); int f3(); };\n'
                'B::~B(){} int B::f1(){return 1;} int B::f2(){return 2;}\n'
                'D::~D(){} int D::f1(){return 11;} int D::f3(){return 33;}\n')
    r = subprocess.run(['bash', os.path.join(ROOT, 'tools', 'wine_cl.sh'),
                        '/nologo', '/TP', '/c', '/W3', '/O2',
                        '/Fo' + obj, src], capture_output=True, text=True, cwd=ROOT)
    if not os.path.exists(obj):
        print('selfcheck: 编译失败\n%s' % (r.stdout + r.stderr)[-400:])
        return 1
    vt = extract_vtables(obj)
    ok = True
    for name, slots in sorted(vt.items()):
        print('  %s' % name)
        for i, s in enumerate(slots):
            print('     [%d] %s' % (i, s))
        nm = name.split('@')[0][4:]
        # override 语义：D 的槽 1/2 应是 D::f1、B::f2（原位替换 + 继承）
        if nm == 'D':
            got = [s for s in slots if s and ('f1' in s or 'f2' in s or 'f3' in s)]
            exp_d1 = any(s and 'f1@D@' in s for s in slots)
            exp_f2 = any(s and 'f2@B@' in s for s in slots)
            print('     D::f1 原位替换=%s  B::f2 继承=%s' % (exp_d1, exp_f2))
            ok = ok and exp_d1 and exp_f2
    print('selfcheck: %s' % ('PASS' if ok else 'FAIL'))
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument('obj', nargs='?', help='COFF .obj 路径')
    ap.add_argument('--cls', help='只显示该类的 vtable')
    ap.add_argument('--selfcheck', action='store_true', help='自检')
    args = ap.parse_args()
    if args.selfcheck:
        return _selfcheck()
    if not args.obj:
        ap.print_help()
        return 0
    vt = extract_vtables(args.obj)
    print('vtable 符号: %d' % len(vt))
    for name in sorted(vt):
        if args.cls and args.cls not in name:
            continue
        print('  %s' % name)
        for i, s in enumerate(vt[name]):
            print('     [%d] %s' % (i, s))
    return 0


if __name__ == '__main__':
    sys.exit(main())