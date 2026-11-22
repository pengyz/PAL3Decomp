#!/usr/bin/env python3
"""[dtor 对偶证据探针 2026-11-22] 删除式存根 call 目标解析 → 完全形地址全量定谳。

机制: MSVC 标准形 30B 删除式存根 `56 8B F1 E8 <rel32> ...`——call@3 的 REL32
目标=该类完全形 dtor(编译器自身的配对语义, 与名字标签无关=最硬锚定)。
本探针解析全部配对候选, 产出: 删除式VA → 完全形VA + 邻接检查(+0x20) + 形判,
挂账批(六误名/SkillUI双条目/rejected悬空)的证据一次到位。

用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_dtor_pair_adjacency_20261122.py
"""
import json
import struct

REPO = '/home/peng/workspace/PAL3Decomp'
EXE = REPO + '/original/PAL3.exe'
STUB_PREFIX = bytes.fromhex('568bf1')          # 56 8B F1
STUB_LEN = 30


def exe_text():
    d = open(EXE, 'rb').read()
    e_lfanew = struct.unpack_from('<I', d, 0x3C)[0]
    nsec = struct.unpack_from('<H', d, e_lfanew + 6)[0]
    opt = struct.unpack_from('<H', d, e_lfanew + 20)[0]
    sec0 = e_lfanew + 24 + opt
    for i in range(nsec):
        s = sec0 + 40 * i
        name = d[s:s + 8].rstrip(b'\0').decode('ascii', 'replace')
        vsize, vaddr, rsize, raddr = struct.unpack_from('<IIII', d, s + 8)
        if name == '.text':
            return d, vaddr + 0x400000, d[raddr:raddr + rsize]
    raise SystemExit('.text 未找到')


def stub_complete_target(text, va):
    """解析标准形存根 call@3 的 REL32 目标(=完全形)。非标准形返回 None。"""
    off = va - 0x401000
    b = text[off:off + STUB_LEN]
    if b[:3] != STUB_PREFIX or b[3] != 0xE8:
        return None, '非标准形(前缀 %s)' % b[:6].hex()
    rel = int.from_bytes(b[4:8], 'little', signed=True)
    tgt = va + 3 + 5 + rel
    return tgt, '标准形30B'


def main():
    d, text_va, text = exe_text()
    fid = json.load(open(REPO + '/asm/pal3/function_identity.json'))
    rows = fid['rows']
    # 全部已知删除式(注解 flags)——call 目标=完全形真址
    dels = [(r['ann_class'], int(r['va'], 16)) for r in rows
            if r['ann_kind'] == 'deleting_dtor']
    # 完全形候选(注解 kind + 挂账误名 VA)
    comps = {}
    for r in rows:
        if r['ann_kind'] == 'complete_dtor':
            comps.setdefault(r['ann_class'], []).append(int(r['va'], 16))
    mislabels = [(c, va) for c, va in [
        ('CEffQuad', 0x004D0DB0), ('UIMap', 0x004411D0), ('CEffQuake', 0x004D3300),
        ('TaskBookUI', 0x00454BA0), ('RoleCameraCtrl', 0x00450AD0),
        ('CEffgbParticle', 0x004C6980)]]
    for c, va in mislabels:
        comps.setdefault(c, []).append(va)

    report = []
    print('== 删除式 → 完全形 call 目标全量解析 (%d 删除式) ==' % len(dels))
    for cls, dva in sorted(dels, key=lambda x: x[1]):
        tgt, shape = stub_complete_target(text, dva)
        cand = comps.get(cls) or []
        adj = ('+0x20 邻接' if tgt and (tgt - dva) in (0x20, -0x20) else '')
        in_ann = '注解在册' if tgt in cand else ('挂账误名址' if (cls, tgt) in mislabels else '未注解')
        report.append({'cls': cls, 'deleting_va': '0x%08x' % dva, 'shape': shape,
                       'complete_target': ('0x%08x' % tgt) if tgt else None,
                       'adjacency': adj, 'target_ann_state': in_ann})
        print('  %-16s del=0x%08X %s → comp=0x%08X %s %s'
              % (cls, dva, shape[:12], tgt or 0, adj, in_ann))
    # 挂账误名 VA 的形判(反查: 该址字节是什么)
    print('\n== 挂账误名 VA 形判 ==')
    for cls, va in mislabels:
        off = va - 0x401000
        b = text[off:off + 8]
        shape = '标准形存根' if b[:3] == STUB_PREFIX else ('他形 %s' % b[:6].hex())
        print('  %-16s 0x%08X: %s' % (cls, va, shape))
    # SkillUI 双条目形判
    print('\n== SkillUI 双条目形判 ==')
    for va in (0x00525520, 0x00525540):
        off = va - 0x401000
        b = text[off:off + 8]
        shape = '标准形存根(=删除式)' if b[:3] == STUB_PREFIX else ('他形 %s' % b[:6].hex())
        print('  0x%08X: %s' % (va, shape))
    out = REPO + '/data/status/dtor_pair_adjacency_20261122.json'
    json.dump({'_doc': 'dtor 对偶证据探针 20261122——删除式call目标=完全形真址(编译器配对语义)',
               'pairs': report}, open(out, 'w', encoding='utf-8'),
              ensure_ascii=False, indent=1)
    print('\n报告 →', out)


if __name__ == '__main__':
    main()
