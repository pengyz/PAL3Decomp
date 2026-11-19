#!/usr/bin/env python3
"""[R4-T1 2026-11-19] tag簇三合一裁决取证——推翻 tag_census_20261119 的"三'类'=同一结构体"结论。

裁决三支柱 (全部可独立复验):
  P1 分配边界: g_CombatTaskData@0x17AAD4C 的 384B "struct" 实为 408B lazy-init
     静态数组 [0x17AAD48, 0x17AAEE0) 的行窗口锚名——基址 g_fCBAnimTime,
     6 行 × 17 dword (68B), flag byte_17AAEE0 恰贴数组尾 (基址+0x198)。
     ~CCCTData@0x505930 内 ArraySort×6 循环 + flag&1 懒初始化守卫为直接证据。
  P2 窗口 inventory: g_fCombatHalfParam(基址+12)/g_fCombatTimer(StageRoleData+0x7C)
     语料 0 独立访问 0 地址取用 = 分配区内部 IDA 切割窗口, 非真全局。
  P3 三"同值证据"归属解体: SetPause 545→g_StageRoleData 专属; RenderScenePass 1.0
     →g_17A7BData (第四个同批发明型) 专属; CCCTData 级联→408B 数组几何暂存。
     三条证据分属三个互不相关全局, "同值"只是同批 cluster 方法给所有发明型
     分配了相同 偏移→名字 对 ⇒ 普查对照=循环论证。

用法: python3 tools/probe_tagcluster_3in1_20261119.py
输出: data/status/tagcluster_3in1_evidence_20261119.json
"""
import json
import re
import glob
from pathlib import Path

REPO = Path(__file__).parent.parent
DECOMP = REPO / 'asm/pal3/decomp'

# ── 已定谳的地址事实 (反汇编+globals.json 邻域) ──
ARR_BASE = 0x17AAD48      # g_fCBAnimTime = 数组真基址
ARR_FLAG = 0x17AAEE0      # byte_17AAEE0 = init flag
ARR_ROWS = 6
ARR_STRIDE_DWORDS = 17    # 68B
SRD_ADDR = 0x17ABC60      # g_StageRoleData
SRD_SIZE = 0xA0           # 160B
SRD_NEXT = 0x17ABD00      # byte_17ABD00 char[256] sprintf 缓冲 = 右边界

def corpus_files(*names):
    """含任一名字的语料文件集合"""
    pats = [re.compile(re.escape(n)) for n in names]
    hits = []
    for fp in sorted(DECOMP.glob('*.json')):
        body = fp.read_text(encoding='utf-8', errors='ignore')
        if any(p.search(body) for p in pats):
            hits.append(fp.name)
    return hits

def member_spectrum(global_name, own_type):
    """按全局自己的类型映射 member→offset, 提取访问偏移谱 (避免跨型名碰撞)"""
    ann = json.loads((REPO / ('data/annotations/structs/%s.json' % own_type)).read_text(encoding='utf-8'))
    n2o = {m['name']: int(o, 16) for o, m in (ann.get('known_members') or {}).items()}
    spec = {}
    for fp in sorted(DECOMP.glob('*.json')):
        try:
            d = json.loads(fp.read_text(encoding='utf-8'))
        except Exception:
            continue
        body = d.get('decompiled_c') or ''
        if global_name not in body:
            continue
        for m in re.finditer(re.escape(global_name) + r'\.(\w+)', body):
            nm = m.group(1)
            if nm in n2o:
                spec.setdefault(n2o[nm], set()).add(fp.name.split('_')[0])
    return spec

def main():
    ev = {'_doc': 'R4-T1 tag簇三合一裁决取证 2026-11-19 (推翻 tag_census 同日结论)'}

    # P1: 408B 数组算术
    total = ARR_STRIDE_DWORDS * 4 * ARR_ROWS
    ev['P1_array_408B'] = {
        'base': hex(ARR_BASE), 'flag': hex(ARR_FLAG),
        'flag_offset_from_base': ARR_FLAG - ARR_BASE,
        'rows': ARR_ROWS, 'stride_bytes': ARR_STRIDE_DWORDS * 4,
        'total_bytes': total,
        'end': hex(ARR_BASE + total),
        'flag_adjacent_to_end': (ARR_BASE + total == ARR_FLAG),
        'accessor_files': corpus_files('g_CombatTaskData', 'g_fCBAnimTime', 'byte_17AAEE0'),
        'verdict': 'g_CombatTaskData@base+4 = 行窗口锚名, 384B struct = 数组(去头4B)误读, '
                   '~CCCTData 写入为跨 6 行盒半边长几何暂存 (NewTrivalEffect(3) 盒效应)'
    }

    # P2: 窗口 inventory
    wins = {}
    for nm in ['g_fCombatHalfParam', 'g_fCombatTimer', 'g_fCBAnimTime', 'byte_17AAEE0']:
        fs = corpus_files(nm)
        wins[nm] = {'corpus_files': len(fs), 'files': fs[:3]}
    wins['g_fCombatHalfParam']['offset'] = '数组基址+12 (0x17AAD54)'
    wins['g_fCombatTimer']['offset'] = 'g_StageRoleData+0x7C (0x17ABCDC)'
    ev['P2_windows'] = wins

    # P3: 两真全局偏移谱 (per-type 映射) + 证据归属解体
    spec_ctd = member_spectrum('g_CombatTaskData', 'tagCombatTaskData')
    spec_srd = member_spectrum('g_StageRoleData', 'tagStageRoleData')
    ev['P3_spectra'] = {
        'g_CombatTaskData': {'n_offsets': len(spec_ctd),
                             'min_off': hex(min(spec_ctd)), 'max_off': hex(max(spec_ctd)),
                             'max_end': hex(max(spec_ctd) + 4),
                             'files': corpus_files('g_CombatTaskData')},
        'g_StageRoleData': {'n_offsets': len(spec_srd),
                            'max_off': hex(max(spec_srd)), 'max_end': hex(max(spec_srd) + 4),
                            'next_alloc': hex(SRD_NEXT),
                            'size_airtight': (max(spec_srd) + 4 == SRD_SIZE == SRD_NEXT - SRD_ADDR),
                            'n_files': len(corpus_files('g_StageRoleData'))},
        'evidence_rehoming': {
            'SetPause_545': 'g_StageRoleData 0x3C-0x48 (CCBStage_SetPause 专属)',
            'CCCTData_cascade': '408B 数组几何暂存 (~CCCTData 专属)',
            'RenderScenePass_1.0': 'g_17A7BData 0x18/0x24 (CEffModel::RenderScenePass 专属, '
                                   '第四个同批发明型) — 语料实证: g_17A7BData.m_nEffParam24/1/0=1065353216'
        }
    }

    outp = REPO / 'data/status/tagcluster_3in1_evidence_20261119.json'
    outp.write_text(json.dumps(ev, indent=1, ensure_ascii=False), encoding='utf-8')
    print('取证完成 ->', outp.name)
    print('P1 flag 贴尾:', ev['P1_array_408B']['flag_adjacent_to_end'],
          '| P3 StageRoleData 尺寸闭合:', ev['P3_spectra']['g_StageRoleData']['size_airtight'])

if __name__ == '__main__':
    main()
