#!/usr/bin/env python3
"""Multiple-inheritance base subobject offsets, derived from the BINARY ONLY.

# 为什么需要

codegen 要把限定形 vtable 访问 `this->A::B::__vftable` 折算成距对象起点的字节偏移
（`stage3_cleanup._qualified_vftable_offset`），而基类子对象偏移在注解里**普遍缺失**
（179 个有基类的类里只有 1 个的 `bases` 带 offset）。缺了它，这段访问只能原样跳过 ——
实测这一条缺口对应 **741 条编译错误 / 38 个文件**（占全部错误 23%）。

# 方法论：三条**纯二进制**路线，交叉印证

MSVC 在构造函数里按**基类声明顺序**写入各基类的 vfptr。于是：

    第 i 个基类的偏移 = 该 ctor 里**第 i 次** vfptr 安装的位移

路线 A：用类**注解里的 ctor 方法**定位 ctor
路线 B：用类**注解里的主 vtable** → 找安装它的函数 → 那就是 ctor
路线 C：类名下**任一被注解的函数**里出现非零位移的 vtable 安装 ⇒ 该位移是一个基类偏移

**只写"可确证"的结果**：
  * 偏移序列长度必须等于基类个数；
  * 两条及以上路线都可用时，**必须完全一致**（不一致 ⇒ 报冲突、不写）；
  * 首个基类必须是 0（MS C++ ABI：主基类子对象在偏移 0）；
  * 单路线可用时**允许**采用，但在 `bases_source` 里注明是单路线。

`data/pdb/pdb_export.json` 在这些判定里**不参与**：它只在 `--cross-check` 时打印出来
供人眼比对（PDB 来自 PAL3A，按项目规则只能作参考）。

用法：
    python3 tools/mi_base_offsets.py                 # 报告（默认，不写文件）
    python3 tools/mi_base_offsets.py --cross-check   # 附 PDB 对照（仅供参考）
    python3 tools/mi_base_offsets.py --json out.json # 导出结果
"""
import argparse
import glob
import json
import os
import re
import sys

PROJECT_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ASM = os.path.join(PROJECT_ROOT, 'original', 'PAL3.exe.asm')
ANN = os.path.join(PROJECT_ROOT, 'data', 'annotations', 'structs')

_MOVI = re.compile(r'mov\s+dword ptr \[(e[a-z]{2})(?:\+([0-9A-F]+)h)?\], offset (off_[0-9A-F]+)')
_MOVR = re.compile(r'mov\s+dword ptr \[(e[a-z]{2})(?:\+([0-9A-F]+)h)?\], (e[a-z]{2})\s*$')
_MOVV = re.compile(r'mov\s+(e[a-z]{2}), offset (off_[0-9A-F]+)\s*$')
_LEA = re.compile(r'lea\s+(e[a-z]{2}),\s*\[(e[a-z]{2})\+([0-9A-F]+)h\]')


class Asm:
    """`PAL3.exe.asm` 的惰性索引：函数区间 + 每函数文本。"""

    def __init__(self, path=ASM):
        self.lines = open(path, encoding='utf-8', errors='replace').read().split('\n')
        self.spans = {}
        cur = None
        for i, l in enumerate(self.lines):
            m = re.match(r'^(sub_[0-9A-F]+)\s+proc near', l)
            if m:
                cur = (m.group(1), i)
            elif cur and re.match(r'^%s\s+endp' % cur[0], l):
                self.spans[cur[0]] = (cur[1], i)
                cur = None
        self._seg = {}

    def seg(self, lab):
        if lab not in self._seg:
            s, e = self.spans[lab]
            self._seg[lab] = '\n'.join(self.lines[s:e])
        return self._seg[lab]

    def installs(self, lab):
        """某函数内**按出现顺序**的 vfptr 安装位移（含 lea / 寄存器装载形态）。"""
        if lab not in self.spans:
            return None
        s, e = self.spans[lab]
        reg, vreg, seq = {}, {}, []
        for k in range(s, e):
            line = self.lines[k]
            lm = _LEA.search(line)
            if lm:
                reg[lm.group(1)] = int(lm.group(3), 16)
                continue
            vm = _MOVV.search(line)
            if vm:
                vreg[vm.group(1)] = vm.group(2)
                continue
            mm = _MOVI.search(line)
            if mm:
                seq.append(reg.get(mm.group(1), 0) +
                           (int(mm.group(2), 16) if mm.group(2) else 0))
                continue
            mr = _MOVR.search(line)
            if mr and mr.group(3) in vreg:
                seq.append(reg.get(mr.group(1), 0) +
                           (int(mr.group(2), 16) if mr.group(2) else 0))
        return seq


def load_classes():
    out = {}
    for f in sorted(glob.glob(os.path.join(ANN, '*.json'))):
        try:
            d = json.load(open(f, encoding='utf-8'))
        except Exception:
            continue
        name = d.get('name') or os.path.basename(f)[:-5]
        out[name] = (d, f)
    return out


def candidate_offsets(cls, d, asm):
    """返回 {route: 偏移**集合**}（只保留"去重后恰好等于基类个数"的路线）。

    **不按顺序判定**：实测 MSVC 未必按声明顺序写 vfptr（`CEffCylinder` 的 ctor 是
    `[12, 0]`、基类的组织构造变体又是 `[12, 0, 12]`），故"第 i 个安装 = 第 i 个基类"
    这个假设**不成立**，只能比集合。长度不足 ⇒ 该路线给不出完整信息，丢弃。
    """
    bc = d.get('base_class')
    if not isinstance(bc, list) or len(bc) < 2:
        return {}
    n = len(bc)
    res = {}

    def _add(route, seq):
        if not seq:
            return
        st = set(seq)
        if len(st) == n and 0 in st:
            res[route] = sorted(st)

    ctor = next((int(a, 16) for a, v in (d.get('methods') or {}).items()
                 if v.get('name') == cls), None)
    if ctor is not None:
        _add('A', asm.installs('sub_%X' % ctor))

    vts = [int(v['addr'], 16) for v in (d.get('vtables') or []) if v.get('addr')]
    if vts:
        key = 'off_%X' % vts[0]
        labs = [lab for lab in asm.spans if key in asm.seg(lab)]
        if labs:
            _add('B', asm.installs(labs[0]))

    seen = []
    for a in (d.get('methods') or {}):
        try:
            va = int(a, 16)
        except ValueError:
            continue
        for disp in (asm.installs('sub_%X' % va) or []):
            if disp and disp not in seen:
                seen.append(disp)
    _add('C', [0] + seen)
    return res


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--cross-check', action='store_true',
                    help='附 PDB 偏移对照（仅供参考，不作为证据）')
    ap.add_argument('--json', help='把结果写到该路径')
    args = ap.parse_args()

    asm = Asm()
    classes = load_classes()
    pdb = {}
    if args.cross_check:
        try:
            pdb = {c['name']: c for c in
                   json.load(open(os.path.join(PROJECT_ROOT, 'data', 'pdb',
                                               'pdb_export.json'),
                                  encoding='utf-8'))['classes']}
        except Exception as e:
            print('[WARN] PDB 读不到：%s' % e, file=sys.stderr)

    confirmed, single, conflicted, none_ = {}, {}, [], []
    for cls, (d, _f) in sorted(classes.items()):
        bc = d.get('base_class')
        if not isinstance(bc, list) or len(bc) < 2:
            continue
        cands = candidate_offsets(cls, d, asm)
        vals = {tuple(v) for v in cands.values()}
        if len(vals) > 1:
            conflicted.append((cls, cands))
            continue
        if not vals:
            none_.append(cls)
            continue
        seq = list(next(iter(vals)))
        if seq[0] != 0:
            conflicted.append((cls, cands))
            continue
        pairs = list(zip(bc, seq))
        if len(cands) >= 2:
            confirmed[cls] = (pairs, '+'.join(sorted(cands)))
        else:
            single[cls] = (pairs, next(iter(cands)))

    print('=' * 74)
    print('MI 基类偏移（**纯二进制**推导；PDB 不参与判定，仅在 --cross-check 时打印对照）')
    print('=' * 74)
    print('路线: A=注解 ctor 方法  B=注解主表的安装函数  C=本类任一注解函数里的非零位移安装')
    print()

    def show(title, table, multi):
        if not table:
            return
        print('【%s】%d 个类' % (title, len(table)))
        for cls, (pairs, routes) in sorted(table.items()):
            extra = ''
            if args.cross_check and cls in pdb:
                pb = sorted(b['offset'] for b in (pdb[cls].get('bases') or []))
                extra = '   PDB(参考)=%s %s' % (pb, '一致' if pb == [o for _, o in pairs] else '**不一致**')
            print('   %-38s %-8s %s%s' % (cls[:38], routes,
                                          ' '.join('%s:%d' % (b[:18], o) for b, o in pairs),
                                          extra))
        print()

    show('两路线及以上一致（最高置信）', confirmed, True)
    show('单路线', single, False)
    if conflicted:
        print('【冲突 —— 不写】%d 个类' % len(conflicted))
        for cls, cands in conflicted:
            print('   %-38s %s' % (cls[:38], {k: v for k, v in cands.items()}))
        print()
    if none_:
        print('【两条路线都拿不到 —— 不写】%d 个类' % len(none_))
        print('   ', ', '.join(none_))
        print()

    if args.json:
        out = {c: [(b, o) for b, o in p] for c, (p, _r) in
               {**confirmed, **single}.items()}
        json.dump(out, open(args.json, 'w', encoding='utf-8'),
                  ensure_ascii=False, indent=1)
        print('结果 -> %s' % args.json)


if __name__ == '__main__':
    main()