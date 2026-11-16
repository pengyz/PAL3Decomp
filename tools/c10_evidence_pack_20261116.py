#!/usr/bin/env python3
"""[C10证据包生成器 2026-11-16] 每冲突类产出三方证据(取证不裁决, 不批量改)。

对每个C10a违规类输出:
1. 机器码位移直方图: 该类全部decomp函数的[reg+disp]访问偏移分布(capstone)
2. 尺寸算术: binary_size vs maxend(可计算成员) vs 声明基尺寸
3. 声明基链: bases[]与各基binary_size
输出: data/status/c10_evidence_packs_20261116.json — 逐类人审材料
"""
import json
import glob
import os
import re
import struct
import collections

import capstone

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
OUT = os.path.join(ROOT, 'data', 'status', 'c10_evidence_packs_20261116.json')

SCALAR = {'int': 4, 'unsigned int': 4, 'bool': 1, 'BOOL': 4, 'long': 4, 'unsigned long': 4,
          'DWORD': 4, 'LONG': 4, 'UINT': 4, 'float': 4, 'BYTE': 1, 'char': 1,
          'unsigned char': 1, 'WORD': 2, 'short': 2, 'unsigned short': 2, 'double': 8,
          'HANDLE': 4, 'HWND': 4, 'HINSTANCE': 4, 'HCURSOR': 4}


def load_pe(data):
    e_lfanew = struct.unpack_from('<I', data, 0x3C)[0]
    opt_off = e_lfanew + 24
    image_base = struct.unpack_from('<I', data, opt_off + 28)[0]
    n_sec = struct.unpack_from('<H', data, e_lfanew + 6)[0]
    sec_off = opt_off + struct.unpack_from('<H', data, e_lfanew + 20)[0]
    sections = []
    for i in range(n_sec):
        o = sec_off + i * 40
        vsize, va, rsize, raw = struct.unpack_from('<IIII', data, o + 8)
        sections.append((va, vsize, raw, rsize))

    def va2off(va):
        rva = va - image_base
        for sva, vsize, raw, rsize in sections:
            if sva <= rva < sva + max(vsize, rsize):
                return raw + (rva - sva)
        return None
    return image_base, sections, va2off


def disp_hist(va2off, data, va, span=1600):
    """[reg+disp]位移直方图(小非负disp, this指向访问)。"""
    off = va2off(va)
    if off is None:
        return {}
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    h = collections.Counter()
    n = 0
    for insn in md.disasm(data[off:off + span], va):
        n += 1
        if n > 3000 or insn.mnemonic == 'ret':
            break
        for op in insn.operands:
            if op.type == capstone.x86.X86_OP_MEM and op.mem.base != 0:
                d_ = op.mem.disp
                if 0 <= d_ < 0x1000:
                    h[d_] += 1
    return dict(h)


def main():
    data = open(os.path.join(ROOT, 'original', 'PAL3.exe'), 'rb').read()
    image_base, sections, va2off = load_pe(data)

    # 注解装载
    sizes, anns = {}, {}
    for f in sorted(glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json'))):
        cls = os.path.basename(f)[:-5]
        d = json.load(open(f, encoding='utf-8'))
        anns[cls] = d
        bs = d.get('binary_size')
        if isinstance(bs, int) and bs > 0:
            sizes[cls] = bs

    def tsize(t, dep=0):
        if dep > 6 or not t:
            return None
        t = str(t).strip()
        if t.endswith('*'):
            return 4
        m = re.match(r'^(.+?)\[(\d+)\]$', t)
        if m:
            e = tsize(m.group(1).strip(), dep + 1)
            return e * int(m.group(2)) if e is not None else None
        if t in SCALAR:
            return SCALAR[t]
        return sizes.get(t)

    def members_of(d):
        out = []
        for k, v in (d.get('known_members') or {}).items():
            try:
                out.append((int(str(k).split('_')[0], 16), v.get('name'), v.get('type')))
            except (ValueError, TypeError):
                pass
        return sorted(out)

    # 冲突类清单(C10a语义重算)
    packs = {}
    for cls, d in sorted(anns.items()):
        ms = members_of(d)
        bs = d.get('binary_size')
        bases = d.get('bases') or []
        if not bases or not ms:
            continue
        hit_base = None
        for b in bases:
            bn = b.get('name') if isinstance(b, dict) else b
            bo = b.get('offset', 0) if isinstance(b, dict) else 0
            sb = sizes.get(bn)
            if sb is None:
                continue
            if any(bo <= o < bo + sb for o, nm, t in ms):
                hit_base = (bn, bo, sb)
                break
        if not hit_base:
            continue
        bn, bo, sb = hit_base
        comp = [(o, tsize(t), nm) for o, nm, t in ms]
        maxend = max((o + s) for o, s, nm in comp if s is not None)
        implied = bs - maxend

        # 类的decomp函数地址集(类前缀文件名)
        func_addrs = []
        for fp in glob.glob(os.path.join(ROOT, 'asm', 'pal3', 'decomp',
                                         '%s_*.json' % cls)):
            try:
                dd = json.load(open(fp, encoding='utf-8'))
            except Exception:
                continue
            a = str(dd.get('address') or '').lower()
            try:
                func_addrs.append(int(a, 16))
            except (ValueError, TypeError):
                pass
        # 机器码位移直方图聚合(前8函数, 防超时)
        hist = collections.Counter()
        for va in sorted(set(func_addrs))[:8]:
            h = disp_hist(va2off, data, va)
            hist.update(h)
        # 与注解偏移吻合度
        ann_offs = {o for o, nm, t in ms}
        matches = sum(v for k, v in hist.items() if k in ann_offs)
        total_disp = sum(hist.values())
        packs[cls] = {
            'claimed_base': {'name': bn, 'offset': bo, 'size': sb},
            'binary_size': bs, 'maxend': maxend, 'implied_base_zone': implied,
            'member_count': len(ms),
            'disp_hist_top': sorted(hist.items(), key=lambda x: -x[1])[:24],
            'ann_offset_match': '%d/%d' % (matches, total_disp) if total_disp else 'n/a',
            'match_ratio': round(matches / total_disp, 2) if total_disp else None,
            'funcs_sampled': len(set(func_addrs))[:0] if False else min(8, len(set(func_addrs))),
            'func_total': len(set(func_addrs)),
        }

    json.dump(packs, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('证据包: %d 类 → %s' % (len(packs), OUT))
    for cls, p in list(packs.items())[:10]:
        print('%-20s 声明基=%s(%d) bin=%d maxend=%d 隐含区=%d 吻合率=%s' % (
            cls, p['claimed_base']['name'], p['claimed_base']['size'],
            p['binary_size'], p['maxend'], p['implied_base_zone'],
            p['ann_offset_match']))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
