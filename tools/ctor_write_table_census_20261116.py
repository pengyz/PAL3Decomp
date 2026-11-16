#!/usr/bin/env python3
"""[ctor写表归属普查 2026-11-16] 机器码级裁决: 每张vtable归谁 = 谁的ctor/dtor写它。

判据([[vtable-writer-evidence-law-20261114]]): 表归属=ctor写表裁决。
MSVC ctor/dtor 必写 `mov dword ptr [reg], &vftable`(this入表)。decomp层已把该store
吸收进类型显示不可靠(实证: CCBControlWindow ctor体无写表痕迹), 故下沉机器码:
capstone线性扫ctor/dtor, 收集 MEM=IMM 存储且IMM∈.rdata(0x56A000-0x57F178)。

裁决矩阵:
- CONFIRMED  标注表 ⊆ 写表集
- PARTIAL    有交集不覆盖
- EXTRA      写了标注外.rdata地址(候选漏表/错归属)
- NO_EVIDENCE 找不到ctor/dtor或无写表
- SHARED     同表被多类写(attribution夺主)

输出: data/status/ctor_write_table_census_20261116.json
"""
import json
import struct
import glob
import os
import re
import sys

import capstone

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
OUT = os.path.join(ROOT, 'data', 'status', 'ctor_write_table_census_20261116.json')
RDATA_LO, RDATA_HI = 0x56A000, 0x57F178
MAX_INSN = 4000


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
                off = raw + (rva - sva)
                return off if off < len(data) else None
        return None
    return va2off


def rdata_stores(data, va2off, va):
    """函数起始线性扫, 只收 [this系寄存器+0]=表址 形态 = vftable赋值。
    直接形: mov [this], imm(.rdata); 中转形: mov r, imm(.rdata) 后 mov [this], r。
    disp!=0 → 成员字段初始化, 非[reg]形态 → 实参压栈, 均排除。"""
    off = va2off(va)
    if off is None:
        return None
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    hits = []
    this_regs = {'ecx'}
    imm_regs = {}   # reg -> rdata imm (寄存器中转)
    n = 0
    for insn in md.disasm(data[off:off + 0x800], va):
        n += 1
        if n > MAX_INSN:
            break
        if insn.mnemonic == 'ret':
            break
        if (insn.mnemonic == 'mov' and len(insn.operands) == 2
                and insn.operands[0].type == capstone.x86.X86_OP_REG
                and insn.operands[1].type == capstone.x86.X86_OP_REG
                and insn.reg_name(insn.operands[1].reg) in this_regs):
            this_regs.add(insn.reg_name(insn.operands[0].reg))
            continue
        if insn.mnemonic == 'mov' and len(insn.operands) == 2:
            dst, src = insn.operands
            # 中转: reg = imm(.rdata)
            if dst.type == capstone.x86.X86_OP_REG and src.type == capstone.x86.X86_OP_IMM:
                imm = src.imm & 0xFFFFFFFF
                if RDATA_LO <= imm < RDATA_HI:
                    imm_regs[insn.reg_name(dst.reg)] = imm
                else:
                    imm_regs.pop(insn.reg_name(dst.reg), None)
                continue
            # [this+0] = imm 直接 或 = 中转寄存器
            if dst.type == capstone.x86.X86_OP_MEM:
                base = dst.mem.base
                if base != 0 and dst.mem.disp == 0 and insn.reg_name(base) in this_regs:
                    if src.type == capstone.x86.X86_OP_IMM:
                        imm = src.imm & 0xFFFFFFFF
                        if RDATA_LO <= imm < RDATA_HI:
                            hits.append(imm)
                    elif src.type == capstone.x86.X86_OP_REG:
                        r = insn.reg_name(src.reg)
                        if r in imm_regs:
                            hits.append(imm_regs[r])
    return hits


def caller_delivered_tables(data, va2off, ctor_va, tables):
    """调用方交付表模式裁决: ctor体 [this]=param(运行时值) 时, 表由调用方push。
    E8直调扫描 + 调用点前窗内 push imm32(0x68) / mov e?x,imm32 匹配标注表。"""
    hits = set()
    tgt = struct.pack('<I', ctor_va)
    for sec_name in ('.text',):
        pass
    # 全 .text E8 扫描
    e_lfanew = struct.unpack_from('<I', data, 0x3C)[0]
    opt_off = e_lfanew + 24
    image_base = struct.unpack_from('<I', data, opt_off + 28)[0]
    n_sec = struct.unpack_from('<H', data, e_lfanew + 6)[0]
    sec_off = opt_off + struct.unpack_from('<H', data, e_lfanew + 20)[0]
    for i in range(n_sec):
        o = sec_off + i * 40
        vsize, sva, rsize, raw = struct.unpack_from('<IIII', data, o + 8)
        blob = data[raw:raw + rsize]
        j = 0
        while True:
            j = blob.find(b'\xE8', j)
            if j < 0 or j + 5 > len(blob):
                break
            rel = struct.unpack_from('<i', blob, j + 1)[0]
            frm = image_base + sva + j
            if frm + 5 + rel == ctor_va:
                # 调用点前窗 0x20 字节找 push imm32
                w0 = max(0, j - 0x20)
                window = blob[w0:j]
                k = 0
                while k < len(window) - 4:
                    if window[k] == 0x68:  # push imm32
                        imm = struct.unpack_from('<I', window, k + 1)[0]
                        if imm in tables:
                            hits.add(imm)
                    if window[k] in (0xB8, 0xB9, 0xBA, 0xBB, 0xBE, 0xBF):  # mov e?x, imm32
                        imm = struct.unpack_from('<I', window, k + 1)[0]
                        if imm in tables:
                            hits.add(imm)
                    k += 1
            j += 1
    return hits


def rdata_stores_anydisp(data, va2off, va):
    """[MI次表射程 2026-11-16] 收集 [this系+任意disp]=IMM(.rdata), 返回 {disp: imm}。
    次基表写=dispN(复核P0-1实证: [eax+0xC]=次表); 主表=disp0。"""
    off = va2off(va)
    if off is None:
        return {}
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    this_regs = {'ecx'}
    imm_regs = {}
    out = {}
    n = 0
    for insn in md.disasm(data[off:off + 0x800], va):
        n += 1
        if n > MAX_INSN:
            break
        if insn.mnemonic == 'ret':
            break
        if (insn.mnemonic == 'mov' and len(insn.operands) == 2
                and insn.operands[0].type == capstone.x86.X86_OP_REG
                and insn.operands[1].type == capstone.x86.X86_OP_REG
                and insn.reg_name(insn.operands[1].reg) in this_regs):
            this_regs.add(insn.reg_name(insn.operands[0].reg))
            continue
        if insn.mnemonic == 'mov' and len(insn.operands) == 2:
            dst, src2 = insn.operands
            if dst.type == capstone.x86.X86_OP_REG and src2.type == capstone.x86.X86_OP_IMM:
                imm = src2.imm & 0xFFFFFFFF
                if RDATA_LO <= imm < RDATA_HI:
                    imm_regs[insn.reg_name(dst.reg)] = imm
                else:
                    imm_regs.pop(insn.reg_name(dst.reg), None)
                continue
            if dst.type == capstone.x86.X86_OP_MEM:
                base = dst.mem.base
                if base != 0 and insn.reg_name(base) in this_regs:
                    disp = dst.mem.disp
                    imm = None
                    if src2.type == capstone.x86.X86_OP_IMM:
                        imm = src2.imm & 0xFFFFFFFF
                    elif src2.type == capstone.x86.X86_OP_REG:
                        imm = imm_regs.get(insn.reg_name(src2.reg))
                    if imm is not None and RDATA_LO <= imm < RDATA_HI:
                        out[disp] = imm
    return out


def main():
    data = open(EXE, 'rb').read()
    va2off = load_pe(data)

    # decomp文件名 → ctor地址索引: <Class>_<Class>..._<hex>.json = ctor (含_Class双下划线形态)
    decomp_ctor = {}
    for fp in glob.glob(os.path.join(ROOT, 'asm', 'pal3', 'decomp', '*.json')):
        base = os.path.basename(fp)[:-5]
        m = re.match(r'^([A-Za-z_]\w*)_(_?[A-Za-z_]\w*)\w*_(0[0-9a-f]{7})$', base)
        if m and m.group(1) == m.group(2):
            try:
                decomp_ctor.setdefault(m.group(1), set()).add(int(m.group(3), 16))
            except ValueError:
                pass

    # 类 → 标注表地址集 / ctor+dtor地址集(methods名: 类名同名=ctor, ~前缀/scalar dtor=dtor族)
    classes = {}
    for fp in sorted(glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json'))):
        cls = os.path.basename(fp)[:-5]
        try:
            d = json.load(open(fp, encoding='utf-8'))
        except Exception:
            continue
        vts = set()
        for vt in (d.get('vtables') or []):
            try:
                vts.add(int(vt.get('addr'), 16))
            except (ValueError, TypeError):
                pass
        funcs = []  # (addr, role)
        for a, e in ((d.get('methods') or {}).items()):
            nm = str(e.get('name') or '')
            try:
                ai = int(a, 16)
            except (ValueError, TypeError):
                continue
            if nm == cls or nm.split('::')[-1] == cls or nm == '_' + cls or nm.split('::')[-1] == '_' + cls:
                funcs.append((ai, 'ctor'))
            elif nm.startswith('~') or re.search(r'_scalar_dtor|scalar_deleting|_sdtor', nm):
                funcs.append((ai, 'dtor'))
        for ai in decomp_ctor.get(cls, ()):
            funcs.append((ai, 'ctor'))
        if vts or funcs:
            classes[cls] = {'vtables': vts, 'funcs': funcs}

    # 扫描
    write_map = {}   # table_addr -> set(cls)
    report = {}
    for cls, info in sorted(classes.items()):
        ann = info['vtables']
        wset = set()
        seen_fn = set()
        for ai, role in info['funcs']:
            if ai in seen_fn:
                continue
            seen_fn.add(ai)
            hs = rdata_stores(data, va2off, ai)
            if hs:
                wset.update(hs)
        if not wset and ann:
            # 调用方交付表回退: ctor/dtor体 [this]=param(运行时) → 调用点push裁决
            # [P2-6修正 2026-11-16] ann已在本循环头部赋值(原use-before-def); 次基表
            # 写在+disp(复核P0-1)不在本census射程, 归属以复核后裁决为准
            for ai, role in info['funcs']:
                wset |= caller_delivered_tables(data, va2off, ai, ann)
        for w in wset:
            write_map.setdefault(w, set()).add(cls)
        ann = info['vtables']
        if not ann:
            verdict = 'NO_TABLES'
        elif not wset:
            verdict = 'NO_EVIDENCE'
        elif ann <= wset:
            verdict = 'CONFIRMED'
        elif ann & wset:
            verdict = 'PARTIAL'
        else:
            verdict = 'EXTRA'
        # MI次表证据: anydisp写覆盖的标注表
        sec_evidence = {}
        seen_fn2 = set()
        for ai, role in info['funcs']:
            if ai in seen_fn2:
                continue
            seen_fn2.add(ai)
            for disp, imm in rdata_stores_anydisp(data, va2off, ai).items():
                if ann and imm in ann:
                    sec_evidence['0x%08x' % imm] = 'disp%s写(%s)' % (hex(disp), role)
        report[cls] = {
            'verdict': verdict,
            'sec_evidence': sec_evidence,
            'annotated': sorted('0x%08x' % a for a in ann),
            'written': sorted('0x%08x' % a for a in wset),
            'extra': sorted('0x%08x' % a for a in (wset - ann)),
            'missing': sorted('0x%08x' % a for a in (ann - wset)),
        }

    # SHARED表
    shared = {'0x%08x' % t: sorted(cs) for t, cs in sorted(write_map.items()) if len(cs) > 1}

    out = {
        'date': '2026-11-16',
        'judgement': '表归属=ctor/dtor机器码写表(.rdata立即数存储); CONFIRMED⊆写集',
        'stats': {},
        'shared_tables': shared,
        'classes': report,
    }
    cnt = {}
    for r in report.values():
        cnt[r['verdict']] = cnt.get(r['verdict'], 0) + 1
    out['stats'] = cnt
    json.dump(out, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('裁决分布:', cnt)
    for cls in ('UIWnd', 'UIFrameWnd', 'CCBControlWindow', 'CCBStage', 'CCBPanelSlot'):
        r = report.get(cls)
        if r:
            print('  %-20s %-11s 标注%s 写%s' % (cls, r['verdict'], r['annotated'], r['written']))
    print('SHARED表(多类共写): %d 张' % len(shared))
    for t, cs in list(shared.items())[:10]:
        print('  %s ← %s' % (t, cs))
    print('输出: %s' % OUT)
    return 0


if __name__ == '__main__':
    sys.exit(main())
