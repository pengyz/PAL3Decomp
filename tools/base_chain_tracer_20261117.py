#!/usr/bin/env python3
"""[基构造链追踪器 2026-11-17] 复核验证方法论制度化: 继承定谳唯一判据=ctor/dtor链。

对每个C10冲突类:
1. 找其主表写入者(ctor/dtor候选) — .text字节扫描 mov [reg+disp0],imm(.rdata表址)
2. 对每个写入者做E8直调扫描, 对照基ctor注册表 → 输出候选继承链
3. 注册表: 已验证ctor(本机capstone实证) + 未验证基类的表写入者(自动发现)
输出: data/status/base_chain_evidence_20261117.json (取证不裁决)
"""
import json
import glob
import os
import re
import struct
import collections

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
EXE = os.path.join(ROOT, 'original', 'PAL3.exe')
OUT = os.path.join(ROOT, 'data', 'status', 'base_chain_evidence_20261117.json')

# 已验证基ctor(本机capstone实证: 存表+基构造调用链)
REGISTRY_VERIFIED = {
    0x445AA0: 'UIWnd', 0x43DCD0: 'UIListBox', 0x43BB70: 'UIFrameWnd',
    0x4422E0: 'UIFrameContainer', 0x444F60: 'UITextArea',
}
# 已验证dtor(用于把写入者分类为ctor/dtor)
DTOR_KNOWN = {0x445B40: 'UIWnd~', 0x43DD10: 'UIListBox~', 0x43BBB0: 'UIFrameWnd~thunk',
              0x442390: 'UIFrameContainer~', 0x445010: 'UITextArea~'}


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

    def off2va(off):
        for sva, vsize, raw, rsize in sections:
            if raw <= off < raw + rsize:
                return image_base + sva + (off - raw)
        return None
    return image_base, sections, va2off, off2va


def find_table_writers(data, image_base, sections, off2va, table_va, func_starts):
    """字节级扫描: 写table_va的所有 mov [reg(/0)],imm 指令 → 归属函数(语料函数起点)。
    modrm形态: mod=00 rm∈{0,1,2,3,6,7}([eax..edi], 05=disp32/04=SIB排除) + mod=01 disp8。"""
    import bisect
    target = struct.pack('<I', table_va)
    starts = [s for s in func_starts]
    writers = []
    for sva, vsize, raw, rsize in sections:
        blob = data[raw:raw + rsize]
        pos = 0
        while True:
            i = blob.find(target, pos)
            if i < 0:
                break
            pos = i + 1
            insn_va = None
            if i >= 2 and blob[i - 2] == 0xC7 and blob[i - 1] in (0x00, 0x01, 0x02, 0x03, 0x06, 0x07):
                insn_va = image_base + sva + (i - 2)   # mod=00: mov [reg],imm32
            elif i >= 3 and blob[i - 3] == 0xC7 and 0x40 <= blob[i - 2] <= 0x47:
                insn_va = image_base + sva + (i - 3)   # mod=01: mov [reg+disp8],imm32
            if insn_va is None:
                continue
            # 归属函数: 最近的语料函数起点
            k = bisect.bisect_right(starts, insn_va) - 1
            func_start = starts[k] if k >= 0 and insn_va - starts[k] < 0x3000 else None
            writers.append({'insn': insn_va, 'func': func_start,
                            'disp': 'main' if blob[i - 2] in (0x00, 0x01, 0x02, 0x03, 0x06, 0x07)
                            else 'disp8(次表嫌疑)'})
    return writers


def full_trace(data, image_base, sections, va2off, va, span=0x600):
    """函数trace: E8直调序列 + [this系+disp]=表址存表序列(存表律证据)。
    返回 (calls, table_stores=[(disp, table, insn)])。"""
    import capstone as _cs
    off = va2off(va)
    if off is None:
        return [], []
    md = _cs.Cs(_cs.CS_ARCH_X86, _cs.CS_MODE_32)
    md.detail = True
    calls, stores = [], []
    this_regs = {'ecx'}
    imm_regs = {}
    n = 0
    for insn in md.disasm(data[off:off + span], va):
        n += 1
        if n > 800 or insn.mnemonic == 'ret':
            break
        ops = insn.operands
        if (insn.mnemonic == 'mov' and len(ops) == 2 and ops[0].type == _cs.x86.X86_OP_REG
                and ops[1].type == _cs.x86.X86_OP_REG
                and md.reg_name(ops[1].reg) in this_regs):
            this_regs.add(md.reg_name(ops[0].reg))
            continue
        if insn.mnemonic == 'mov' and len(ops) == 2 and ops[0].type == _cs.x86.X86_OP_REG and ops[1].type == _cs.x86.X86_OP_IMM:
            imm = ops[1].imm & 0xFFFFFFFF
            if 0x56A000 <= imm < 0x57F178:
                imm_regs[md.reg_name(ops[0].reg)] = imm
            else:
                imm_regs.pop(md.reg_name(ops[0].reg), None)
            continue
        if insn.mnemonic == 'mov' and len(ops) == 2 and ops[0].type == _cs.x86.X86_OP_MEM:
            mo = ops[0].mem
            if mo.base != 0 and md.reg_name(mo.base) in this_regs:
                imm = None
                if ops[1].type == _cs.x86.X86_OP_IMM:
                    imm = ops[1].imm & 0xFFFFFFFF
                elif ops[1].type == _cs.x86.X86_OP_REG:
                    imm = imm_regs.get(md.reg_name(ops[1].reg))
                if imm is not None and 0x56A000 <= imm < 0x57F178:
                    stores.append((mo.disp, imm, insn.address))
        if insn.mnemonic == 'call' and ops and ops[0].type == _cs.x86.X86_OP_IMM:
            t = ops[0].imm
            if 0x401000 <= t < 0x570000:
                calls.append(t)
        if insn.mnemonic in ('jmp',) :
            break  # thunk尾jmp=函数边界
    return calls, stores


def main():
    data = open(EXE, 'rb').read()
    image_base, sections, va2off, off2va = load_pe(data)

    # 注解装载
    anns = {}
    for f in sorted(glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json'))):
        cls = os.path.basename(f)[:-5]
        anns[cls] = json.load(open(f, encoding='utf-8'))

    # 语料函数起点(归属基准)
    import bisect as _bs
    func_starts = []
    for fp in glob.glob(os.path.join(ROOT, 'asm', 'pal3', 'decomp', '*.json')):
        try:
            _ad = json.load(open(fp, encoding='utf-8'))
            func_starts.append(int(str(_ad.get('address') or 'x'), 16))
        except (ValueError, TypeError, Exception):
            pass
    func_starts = sorted(set(a for a in func_starts if a))

    # C10冲突类清单(硬编码自check读数, 避免重算)
    conflict = ['PalScript', 'CScreenMode', 'CGameData', 'TextureLib_Data', 'scScriptInstance',
                'SaleUI', 'RoleCamera', 'UIRoleSelect', 'UIRoleDialog', 'UIHeadDialog',
                'UIEmote', 'UIAnimateCtrlEX', 'StateUI', 'EquipUI', 'CCBUI']
    # 涉及的基类(发现其ctor)
    bases_needed = set()
    for cls in conflict:
        for b in (anns[cls].get('bases') or []):
            bn = b.get('name') if isinstance(b, dict) else b
            if bn:
                bases_needed.add(bn)

    # 注册表发现: 每个基类的主表写入者
    registry = dict(REGISTRY_VERIFIED)  # addr→name
    reg_info = {}
    for bn in sorted(bases_needed):
        vts = anns.get(bn, {}).get('vtables') or []
        if not vts:
            reg_info[bn] = {'status': 'no_table'}
            continue
        ta = int(vts[0].get('addr'), 16)
        writers = find_table_writers(data, image_base, sections, off2va, ta, func_starts)
        # 分类ctor/dtor: E8含已知ctor=ctor; 含已知dtor=dtor
        entry = {'table': '0x%08x' % ta, 'writers': []}
        for w in writers[:6]:
            calls, stores = full_trace(data, image_base, sections, va2off, w['func'] or w['insn'], 0x500)
            base_ctor_hits = [registry[c] for c in calls if c in registry]
            dtor_hits = [DTOR_KNOWN[c] for c in calls if c in DTOR_KNOWN]
            store_tables = sorted({('0x%08x' % t) for _d, t, _i in stores})
            role = 'ctor' if (base_ctor_hits or [t for _d, t, _i in stores if t == ta]) else (
                'dtor' if dtor_hits else '?')
            entry['writers'].append({'func': '0x%08x' % (w['func'] or w['insn']),
                                     'role': role, 'base_ctor_calls': base_ctor_hits,
                                     'dtor_calls': dtor_hits,
                                     'store_tables': store_tables,
                                     'calls_sample': ['0x%08x' % c for c in calls[:10]]})
            if role == 'ctor' and (w['func'] or w['insn']) not in registry:
                registry[w['func'] or w['insn']] = bn
        reg_info[bn] = entry

    # 冲突类链取证
    report = {}
    for cls in conflict:
        d = anns[cls]
        vts = d.get('vtables') or []
        entry = {'claimed_bases': [(b.get('name') if isinstance(b, dict) else b)
                                   for b in (d.get('bases') or [])],
                 'binary_size': d.get('binary_size'), 'base_size': d.get('base_size'),
                 'ctors': []}
        if vts:
            ta = int(vts[0].get('addr'), 16)
            writers = find_table_writers(data, image_base, sections, off2va, ta, func_starts)
            for w in writers[:4]:
                fn = w['func'] or w['insn']
                calls, stores = full_trace(data, image_base, sections, va2off, fn, 0x800)
                chain = [registry[c] for c in calls if c in registry]
                dtors = [DTOR_KNOWN[c] for c in calls if c in DTOR_KNOWN]
                entry['ctors'].append({'func': '0x%08x' % fn,
                                       'base_ctor_chain': chain,
                                       'dtor_calls': dtors,
                                       'store_seq': [['0x%08x' % t, 'disp+%d' % d2]
                                                     for d2, t, _i in stores],
                                       'n_calls': len(calls)})
        report[cls] = entry

    json.dump({'registry': {'0x%08x' % k: v for k, v in sorted(registry.items())},
               'base_discovery': reg_info, 'conflict_classes': report},
              open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)

    print('== 注册表(最终) ==')
    for a, n in sorted(registry.items()):
        print('  0x%08x %s' % (a, n))
    print('== 冲突类链候选 ==')
    for cls, e in report.items():
        cts = ['%s←%s' % (c['func'], c['base_ctor_chain'] or c['dtor_calls'] or '?')
               for c in e['ctors']]
        print('  %-18s 声明=%s ctor候选: %s' % (cls, e['claimed_bases'], cts or '无写入者'))
    print('输出: %s' % OUT)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
