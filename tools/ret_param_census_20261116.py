#!/usr/bin/env python3
"""[ABI参个数普查 2026-11-16] 全树vtable槽函数 RET 指令判参 → decomp签名对撞。

判据: MSVC __thiscall 被调方清栈 — `ret n` 尾指令弹出 n 字节栈参 =
ABI级参数个数真相(二进制唯一真相源)。decomp签名(Hex-Rays推断)与此冲突者
= hexrays伪影(体未读参时常见, 0x51afe0 "Update(float,int)" 实为 RET 0参实证)。

取证用途: C9 slot3全链0参契约(UIWnd::HideAll体内0参虚调子物件slot3)已单点定谳,
本工具将其推广为全树普查, 为名字/签名链律修复提供逐地址证据。
输出: data/status/ret_param_census_20261116.json
"""
import json
import struct
import glob
import os
import sys

try:
    from pipeline.sigmodel import parse_signature
except ImportError:
    sys.path.insert(0, os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')))
    from pipeline.sigmodel import parse_signature

import capstone

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
OUT = os.path.join(ROOT, 'data', 'status', 'ret_param_census_20261116.json')
MAX_INSN = 20000
THUNK_WINDOW = 0x400  # 无ret在此窗内 = thunk/jmp型, 诚实标unknown不误报


def load_pe(data):
    e_lfanew = struct.unpack_from('<I', data, 0x3C)[0]
    opt_off = e_lfanew + 24
    image_base = struct.unpack_from('<I', data, opt_off + 28)[0]
    num_sections = struct.unpack_from('<H', data, e_lfanew + 6)[0]
    sec_off = opt_off + struct.unpack_from('<H', data, e_lfanew + 20)[0]
    sections = []
    for i in range(num_sections):
        o = sec_off + i * 40
        vsize, va, rsize, raw = struct.unpack_from('<IIII', data, o + 8)
        sections.append((va, vsize, raw, rsize))
    return image_base, sections


def make_va2off(image_base, sections, data):
    def va2off(va):
        rva = va - image_base
        for sva, vsize, raw, rsize in sections:
            if sva <= rva < sva + max(vsize, rsize):
                off = raw + (rva - sva)
                if off < len(data):
                    return off
        return None
    return va2off


def ret_pop_bytes(data, va2off, va, _depth=0):
    """函数起始线性capstone解码, 首个ret的弹栈字节数。None=thunk/越界(诚实unknown)。
    直跳jmp rel32单跳跟随(adjustor thunk=add ecx,n; jmp / 纯jmp两种形态),
    超窗/int3填充/寄存器间接jmp = unknown。"""
    off = va2off(va)
    if off is None:
        return None
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    code = data[off:off + THUNK_WINDOW]
    n_insn = 0
    for insn in md.disasm(code, va):
        n_insn += 1
        if n_insn > MAX_INSN:
            return None
        if insn.mnemonic == 'ret':
            if insn.op_str:
                try:
                    return int(insn.op_str, 16) if insn.op_str.startswith('0x') else int(insn.op_str)
                except ValueError:
                    return None
            return 0
        if insn.mnemonic == 'jmp':
            if insn.op_str.startswith('0x'):
                if _depth >= 2:
                    return None  # 跳链过深=表数据, 不跟随
                tgt = int(insn.op_str, 16)
                return ret_pop_bytes(data, va2off, tgt, _depth + 1)
            return None  # reg jmp = thunk型, 诚实unknown
        if insn.mnemonic in ('call',) and not insn.op_str.startswith('0x'):
            pass  # 间接call不跟随, 线性继续(其后的字节属本函数)
    return None


def decomp_params(addr_lower):
    """decomp签名参个数(不含this)。文件名无关, 读signature字段结构解析。"""
    for fp in glob.glob(os.path.join(ROOT, 'asm', 'pal3', 'decomp', '*.json')):
        pass  # 太慢——改用索引
    return None


def main():
    data = open(EXE, 'rb').read()
    image_base, sections = load_pe(data)
    va2off = make_va2off(image_base, sections, data)

    # 全树vtable槽地址集
    slot_addrs = set()
    for fp in sorted(glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json'))):
        try:
            d = json.load(open(fp, encoding='utf-8'))
        except Exception:
            continue
        for vt in (d.get('vtables') or []):
            for s in (vt.get('slots') or []):
                try:
                    slot_addrs.add(int(s.get('addr'), 16))
                except (ValueError, TypeError):
                    pass

    # decomp签名索引(地址→参数个数)
    dcd = {}
    for fp in sorted(glob.glob(os.path.join(ROOT, 'asm', 'pal3', 'decomp', '*.json'))):
        try:
            dd = json.load(open(fp, encoding='utf-8'))
        except Exception:
            continue
        a = str(dd.get('address') or '').lower()
        n = parse_signature(dd.get('signature'))
        if n is None or n.get('pending'):
            continue
        dcd[a] = len(n.get('params') or [])

    # 已知真值自检(单点定谳锚)
    anchors = {
        0x00445c60: 2,  # UIWnd::Update(int,int) RET 8
        0x00445c10: 0,  # UIWnd::HideAll() RET 0
        0x0043bbc0: 2,  # UIFrameWnd::Update RET 8
        0x0051b0b0: 2,  # CCB slot2 RET 8
        0x0051afe0: 0,  # CCB slot3 RET 0 (decomp伪影靶)
        0x00445d10: 3,  # UIWnd::OnMessage RET 12
        0x00445b20: 1,  # UIWnd slot5 RET 4
    }

    items = []
    anchor_fail = []
    n_abi = n_mismatch = n_unknown = 0
    for va in sorted(slot_addrs):
        pop = ret_pop_bytes(data, va2off, va)
        key = '0x%08x' % va
        if pop is None:
            n_unknown += 1
            items.append({'addr': key, 'abi_params': None, 'note': 'thunk/unknown'})
            continue
        ap = pop // 4
        n_abi += 1
        if va in anchors and anchors[va] != ap:
            anchor_fail.append((hex(va), anchors[va], ap))
        dp = dcd.get(key)
        row = {'addr': key, 'abi_params': ap, 'decomp_params': dp}
        if dp is not None and dp != ap:
            row['mismatch'] = True
            n_mismatch += 1
        items.append(row)

    report = {
        'date': '2026-11-16',
        'judgement': 'MSVC __thiscall ret n 弹栈字节=ABI参数个数真相; 与decomp签名参个数冲突=hexrays伪影',
        'anchors_pass': not anchor_fail,
        'anchor_fail': anchor_fail,
        'stats': {'slots': len(slot_addrs), 'abi_ok': n_abi, 'unknown': n_unknown,
                  'mismatch': n_mismatch},
        'items': items,
    }
    os.makedirs(os.path.dirname(OUT), exist_ok=True)
    json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('锚自检: %s %s' % ('PASS' if not anchor_fail else 'FAIL %s' % anchor_fail, anchors))
    print('槽总数=%d ABI判参=%d unknown=%d decomp冲突=%d' % (
        len(slot_addrs), n_abi, n_unknown, n_mismatch))
    print('输出: %s' % OUT)
    mm = [i for i in items if i.get('mismatch')]
    for i in mm[:15]:
        print('  MISMATCH %s ABI=%s decomp=%s' % (i['addr'], i['abi_params'], i['decomp_params']))
    return 0


if __name__ == '__main__':
    sys.exit(main())
