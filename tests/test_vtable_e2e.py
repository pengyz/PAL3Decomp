#!/usr/bin/env python3
"""Task 8：**端到端双裁判**（L1 函数体 + `.rdata` vtable）—— 先写测试（TDD，红→绿）。

## 为什么要"双裁判"

* **L1 裁判**（`pipeline/compare_pal3.py`）：把 TU 编译成 `.obj`，按 mangled 名/基名把
  COFF 符号对上 decomp 条目，再**只比 `.text` 里那段函数体字节**。
  ⇒ 它对 **vtable 数据（`.rdata`）结构性失明**：整张表缺失、槽序错位、多出 18 个槽，
  只要函数体字节相同，L1 全绿。
* **`.rdata` 裁判**（Task 6 `tools/vtable_verify.py`）：`force_emit` 强制发射编译产物的
  `??_7<Cls>@@` COMDAT 表，与 `original/PAL3.exe` 里 ctor 实写的真实表逐槽对比。
  ⇒ 它覆盖 vtable 数据，但**看不见函数体**。

Task 8 把两者接起来，并对**3 个已知断裂单元**给出可复现的双裁判判词与分歧归因。

## 三个断裂单元（本文件的花名册，均为已确认存在的真实 TU）

| 单元 | 类 | 双裁判实测判词（2026-09-25） |
|---|---|---|
| `pal3/src/Combat/CCBStageShadow.cpp` | `CCBStageShadow` | L1 破（0 字节全同 / 8 partial）；`.rdata` **不适用**（两侧都非多态：头 0 virtual + ctor `0x511EE0` 无 vptr 写）⇒ 该单元只有 L1 一个裁判有判词 |
| `pal3/src/Misc/PalScriptWaitObj.cpp` | `PalScriptWaitObj` | L1 破（0/1）；`.rdata` **结构性缺失**：头 0 virtual 而二进制要求 vfptr（PDB size 8 且 `RoleCameraCtrl` 成员自 +8 起；Task 4 编译器裁判 PMF=8）⇒ `rdata_missing_vtable` |
| `pal3/src/Misc/UI3DCtrl.cpp` | `UI3DCtrl` | L1 破（0/12）；`.rdata` 真破：编译产物 **26 槽 vs 二进制 8 槽**（发射器把 UIWnd 的 21 个 virtual 整体抄进派生头，自家 `slot_0` 被追加到 21 而不是覆盖 `ShowWindow`@12）|

## 判词是**数据派生**的，不钉死当前缺陷状态

Task 5 评审 Q4 的教训：把"当前缺陷状态"写死成必须成立，会在**正确修复**时报红。
⇒ 本文件的断言全部是"**harness 把这些输入分类对了**"（纯函数 + 夹具可证）；
真实数据只用于**报告**（`data/status/vtable_e2e_report.json`）与不变量。

## 两条已量化的工具边界（本文件的 e2e 归因产出；**不在此修工具**）

1. `bin_table_from_image` 的**类族一致性**判据在派生类覆写槽上过度截断：实测
   **92/189（49%）** 张真机表被截短（`0x56ACFC`：槽 0 = `UIWnd::ShowWindow`
   ⇒ 族 `UIWnd`，槽 1 = `UI3DCtrl::Render` ⇒ 族不同 ⇒ 立刻断表）；注解表 **76/94**。
   交叉核对：raw 界定 **1164 槽** vs 族判据 **639 槽** = Task 6 报告发表的"189 表/639 槽"
   ⇒ Task 6 的真机数字是在被截断的表上算出来的。
   ⇒ 双裁判用 **raw 界定**（只保留"非代码指针即断"）作槽数分母，并记录两者差值。
2. `.obj` 侧占位槽名 `slot_N`（发射器补位命名）在 idx 里无 VA 可归约 ⇒ 该槽退化为名字
   判据、与 bin 侧真实 VA 不可比 ⇒ 保守报 `slot_key`（不静默放过）。

运行：`python3 tests/test_vtable_e2e.py`（离线，毫秒级）
真机：`PAL3_E2E_LIVE=1 python3 tests/test_vtable_e2e.py`
出报告：`PAL3_E2E_LIVE=1 python3 tests/test_vtable_e2e.py --e2e --out data/status/vtable_e2e_report.json`
"""
import argparse
import contextlib
import importlib.util
import io
import json
import os
import re
import struct
import subprocess
import sys
import unittest
from datetime import datetime
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))

LIVE = os.environ.get('PAL3_E2E_LIVE') == '1'
EXE = PROJECT_ROOT / 'original' / 'PAL3.exe'
WINE_CL = PROJECT_ROOT / 'tools' / 'wine_cl.sh'
CENSUS = PROJECT_ROOT / 'data' / 'status' / 'probe_census.json'
STRUCTS = PROJECT_ROOT / 'data' / 'annotations' / 'structs'
SPIKE_CLS = 'AStarPathFinder'
SPIKE_HEADER = 'Misc/AStarPathFinder.h'
REPORT_OUT = PROJECT_ROOT / 'data' / 'status' / 'vtable_e2e_report.json'
RATCHET_BASELINE = PROJECT_ROOT / 'data' / 'status' / 'vtable_ratchet_baseline.json'
MAPPER_BASELINE = PROJECT_ROOT / 'data' / 'status' / 'vtable_baseline.json'
WORKDIR = Path(os.environ.get('PAL3_E2E_WORKDIR', '/tmp/pal3_e2e'))

# =====================================================================================
# 花名册：3 个断裂单元
# =====================================================================================
TARGETS = (
    {'unit': 'pal3/src/Combat/CCBStageShadow.cpp', 'cls': 'CCBStageShadow',
     'header': 'Combat/CCBStageShadow.h',
     'binary_polymorphic': False,
     'evidence': 'ctor 0x511EE0 无 vptr 写（字节级扫描）+ PDB 成员自 +0 起（无 vfptr 空隙）'},
    {'unit': 'pal3/src/Misc/PalScriptWaitObj.cpp', 'cls': 'PalScriptWaitObj',
     'header': 'Misc/PalScriptWaitObj.h',
     'binary_polymorphic': True,
     'evidence': 'PDB size 8 / RoleCameraCtrl 成员自 +8 起 + Task4 编译器裁判 sizeof(PMF)=8'},
    {'unit': 'pal3/src/Misc/UI3DCtrl.cpp', 'cls': 'UI3DCtrl',
     'header': 'Misc/UI3DCtrl.h',
     'binary_polymorphic': True,
     'evidence': 'ctor 0x43D83A `movl $0x56ACFC,(%esi)` + 注解 vtables[0].addr 同址'},
)

# =====================================================================================
# 判词常量
# =====================================================================================
L1_GREEN = 'l1_green'                     # 全部 matched 函数逐字节全同
L1_PARTIAL = 'l1_partial'                 # 有 partial（字节不同）⇒ 破
L1_SKIP = 'l1_compile_skip'               # 单元编不过 ⇒ 无判词
L1_NO_SYMBOLS = 'l1_no_symbols'           # 编过但无符号可比对

RD_CLEAN = 'rdata_clean'
RD_DEVIATIONS = 'rdata_deviations'
RD_MISSING_VTABLE = 'rdata_missing_vtable'      # 二进制要多态、源侧无 vtable
RD_NOT_APPLICABLE = 'rdata_not_applicable'      # 两侧都非多态
RD_PROBE_FAILED = 'rdata_probe_failed'
RD_NO_EVIDENCE = 'rdata_no_binary_evidence'     # 找不到二进制表地址证据

DIV_AGREE_CLEAN = 'agree_clean'
DIV_AGREE_NONPOLY = 'agree_nonpolymorphic'
DIV_L1_BLIND = 'l1_blind_rdata_broken'
DIV_BOTH_BROKEN = 'both_broken'
DIV_RDATA_CLEAN_L1_BROKEN = 'rdata_clean_l1_broken'
DIV_L1_BROKEN_RDATA_NA = 'l1_broken_rdata_na'
DIV_RDATA_UNAVAILABLE = 'rdata_unavailable'

DIVERGENCES = (DIV_AGREE_CLEAN, DIV_AGREE_NONPOLY, DIV_L1_BLIND, DIV_BOTH_BROKEN,
               DIV_RDATA_CLEAN_L1_BROKEN, DIV_L1_BROKEN_RDATA_NA, DIV_RDATA_UNAVAILABLE)

RD_BROKEN = (RD_DEVIATIONS, RD_MISSING_VTABLE)
RD_UNAVAILABLE = (RD_PROBE_FAILED, RD_NO_EVIDENCE)
ALL_RD = (RD_CLEAN,) + RD_BROKEN + (RD_NOT_APPLICABLE,) + RD_UNAVAILABLE
ALL_L1 = (L1_GREEN, L1_PARTIAL, L1_SKIP, L1_NO_SYMBOLS)


# =====================================================================================
# 纯分析层（离线可证）：判词 / 分歧分类 / 报告
# =====================================================================================

def l1_verdict(stats):
    """L1 裁判判词（纯函数）。`stats` = `compare_pal3.compare_units` 的 stats。"""
    matched = int(stats.get('matched') or 0)
    l1 = int(stats.get('match_L1') or 0)
    partial = int(stats.get('partial') or 0)
    skip = int(stats.get('compile_skip') or 0)
    total = l1 + partial
    rate = (l1 / total) if total else None
    if skip:
        status, note = L1_SKIP, '单元编译失败（compile-skip=%d）⇒ L1 无判词' % skip
    elif matched == 0 or total == 0:
        status, note = L1_NO_SYMBOLS, '编译通过但无可比对符号（matched=%d）⇒ L1 无判词' % matched
    elif partial == 0:
        status, note = L1_GREEN, '全部 %d 个 matched 函数逐字节全同' % l1
    else:
        status, note = L1_PARTIAL, '%d/%d 个已比对函数体字节不同（partial）' % (partial, total)
    return {'stage': 'l1', 'status': status, 'note': note, 'rate': rate,
            'match_L1': l1, 'partial': partial, 'matched': matched,
            'symbols': int(stats.get('symbols') or 0),
            'unmatched': int(stats.get('unmatched') or 0),
            'unresolved_synth': int(stats.get('unresolved_synth') or 0),
            'oob': int(stats.get('oob') or 0), 'compile_skip': skip}


def rdata_verdict(ev):
    """`.rdata` 裁判判词（纯函数）。

    `ev` 字段：`header_virtuals`（int，发射头里 `virtual` 计数）、`binary_table`
    （hex 字符串或 None）、`binary_polymorphic`（bool，二进制是否需要 vtable）、
    `probe`（{'ok','obj_slots','error'}）、`compare`（{'ok','obj_slots','bin_slots',
    'bin_slots_family_rule','deviations'}）。
    """
    hv = int(ev.get('header_virtuals') or 0)
    table = ev.get('binary_table')
    bp = ev.get('binary_polymorphic')
    probe = ev.get('probe') or {}
    cmp_ = ev.get('compare')
    out = {'stage': 'rdata', 'header_virtuals': hv, 'binary_table': table,
           'binary_polymorphic': bp, 'probe_ok': bool(probe.get('ok')),
           'obj_slots': None, 'bin_slots': None, 'bin_slots_family_rule': None,
           'deviations': []}
    if hv == 0:
        if bp:
            out['status'] = RD_MISSING_VTABLE
            out['note'] = ('发射头 0 virtual 而二进制有多态证据 ⇒ vtable 维度**结构性缺失**'
                           '（vptr 根本不被建模）')
        else:
            out['status'] = RD_NOT_APPLICABLE
            out['note'] = '发射头 0 virtual 且二进制无多态证据 ⇒ vtable 维度不适用'
        return out
    if not table:
        out['status'] = RD_NO_EVIDENCE
        out['note'] = '找不到二进制表地址证据（注解 vtables[] 与 ctor 字节扫描都没有）'
        return out
    if not probe.get('ok'):
        out['status'] = RD_PROBE_FAILED
        out['note'] = '强制发射失败：%s' % (probe.get('error') or '?')
        return out
    if not cmp_:
        out['status'] = RD_NO_EVIDENCE
        out['note'] = '没有可用的两侧归一结果（compare 缺失）'
        return out
    out['obj_slots'] = cmp_.get('obj_slots')
    out['bin_slots'] = cmp_.get('bin_slots')
    out['bin_slots_family_rule'] = cmp_.get('bin_slots_family_rule')
    out['deviations'] = list(cmp_.get('deviations') or [])
    if cmp_.get('ok'):
        out['status'] = RD_CLEAN
        out['note'] = ('逐槽一致（identity=%s）：obj %s 槽 vs bin %s 槽'
                       % (cmp_.get('identity_mode'), cmp_.get('obj_slots'),
                          cmp_.get('bin_slots')))
    else:
        out['status'] = RD_DEVIATIONS
        out['note'] = ('%d 处偏差：obj %s 槽 vs bin %s 槽（identity=%s）'
                       % (len(out['deviations']), cmp_.get('obj_slots'),
                          cmp_.get('bin_slots'), cmp_.get('identity_mode')))
    return out


def classify_divergence(l1_status, rdata_status):
    """双裁判分歧分类（纯函数）。**未知状态必须抛异常**（不得静默归一类）。"""
    if l1_status not in ALL_L1:
        raise ValueError('未知 L1 判词：%r' % (l1_status,))
    if rdata_status not in ALL_RD:
        raise ValueError('未知 .rdata 判词：%r' % (rdata_status,))
    l1_broken = l1_status != L1_GREEN
    if rdata_status in RD_UNAVAILABLE:
        return DIV_RDATA_UNAVAILABLE
    if rdata_status == RD_NOT_APPLICABLE:
        return DIV_L1_BROKEN_RDATA_NA if l1_broken else DIV_AGREE_NONPOLY
    if rdata_status in RD_BROKEN:
        return DIV_BOTH_BROKEN if l1_broken else DIV_L1_BLIND
    return DIV_RDATA_CLEAN_L1_BROKEN if l1_broken else DIV_AGREE_CLEAN


def gr_spike_analysis(ev):
    """`/GR` spike 结论（纯函数）。

    `ev`：`obj_value_no_gr` / `col_no_gr` / `obj_value_gr` / `col_gr`
    （同一个探针源两种 flag 下 `??_7<Cls>@@6B@` 的符号 value 与 COL 符号）、
    `bin_col`（二进制表 address point 前 4 字节被识别出的 COL，None = 无）、
    `bin_base_minus4`（该 4 字节的字面值）/ `bin_base_minus4_in_code`（是否落在代码节）。
    """
    col_injected = ev.get('col_gr') is not None and ev.get('col_no_gr') is None
    target_has_col = ev.get('bin_col') is not None
    byte_match_possible = (not col_injected) or target_has_col
    if col_injected and not target_has_col:
        verdict = 'GR_IS_STRUCTURAL_BLOCKER'
        recommendation = (
            '移除管线 /GR：cmake/MSVCSettings.cmake:89 · pipeline/compare.py:69/81 · '
            'pipeline/cli.py:690；vtable 维度的探针产物也必须无 /GR'
            '（tools/vtable_verify.py:161 DEFAULT_PROBE_FLAGS 现为 (\'/Od\',\'/GR\')，'
            '与无 RTTI 的目标不一致）。保留 /GR 时的替代口径：vtable 维度只做**归一化**槽'
            '对比（槽序列仍可比），并把 address_point_rtti 偏差读作"目标无 COL"的已知差异，'
            '**不得**声称 byte-match。')
    elif col_injected and target_has_col:
        verdict = 'GR_MATCHED_BOTH_SIDES'
        recommendation = '两侧都有 COL ⇒ /GR 与目标一致，无需改动；byte-match 口径成立。'
    else:
        verdict = 'GR_ALIGNED'
        recommendation = '未注入 COL 且目标无 COL ⇒ 布局对齐；byte-match 口径成立。'
    return {'col_injected': col_injected, 'target_has_col': target_has_col,
            'byte_match_possible': byte_match_possible, 'verdict': verdict,
            'recommendation': recommendation,
            'obj_value_no_gr': ev.get('obj_value_no_gr'),
            'obj_value_gr': ev.get('obj_value_gr'),
            'col_gr': ev.get('col_gr'), 'bin_col': ev.get('bin_col'),
            'bin_base_minus4': ev.get('bin_base_minus4'),
            'bin_base_minus4_in_code': ev.get('bin_base_minus4_in_code')}


def wiring_decision(*, header_virtuals, assertions, positive_rc, negative_rc):
    """`_layout_asserts.h` 接线验证的判词（纯函数）。"""
    if assertions <= 0:
        return {'verdict': 'no_assertions', 'header_virtuals': header_virtuals,
                'assertions': assertions, 'note': '该类没有可生效的断言 ⇒ 无判别力'}
    if positive_rc != 0:
        return {'verdict': 'false_kill', 'header_virtuals': header_virtuals,
                'assertions': assertions,
                'note': '正相（真实头 + 生成断言）编不过 ⇒ 假杀；按类试运行（--only）并降档'}
    if negative_rc == 0:
        return {'verdict': 'not_enforced', 'header_virtuals': header_virtuals,
                'assertions': assertions,
                'note': '负相（篡改常量）也编译通过 ⇒ 断言被注释/未生效，接线无效'}
    return {'verdict': 'wired_and_enforced', 'header_virtuals': header_virtuals,
            'assertions': assertions,
            'note': '正相 0 错误 ∧ 负相 C2118 ⇒ 断言在编译中真实生效'}


def wiring_plan():
    """接线方案（纯数据，供报告与评审引用）。"""
    return {
        'problem': ('Task 4 的 _layout_asserts.h 无消费者 ⇒ 今天没有一条断言在编译中生效'
                    '（I-3）'),
        'placement': ('生成器自身契约：本文件必须在**全部类声明之后**包含'
                      '（sizeof/offsetof 需要完整类型）⇒ 自然接线点是 codegen 发射的 .cpp '
                      '的 include 块**末尾**（emit_headers 追加 #include "_layout_asserts.h"），'
                      '不是文件头。'),
        'force_include_not_viable': ('/FI 强包含发生在 TU 自身 include 之前 ⇒ 类类型尚未声明，'
                                     '实测报 C2059/C2143/C2118（本文件 verify_wiring 记录）'
                                     '——即使 VC6 支持 /FI 也不可用于本头。'),
        'rollout': ('按类试运行：layout_assert_gen --only <Cls> --untrusted-policy '
                    'consistency-only，逐类接入（本文件 verify_wiring 即该口径）；'
                    '真实数据一次性全开会产生 64 假杀 + 71 C2039（Task 4 评审实测），'
                    '⇒ 禁止全量开启。'),
        'gate': ('每接一类必须同时给正相（编过）与负相（篡改常量 ⇒ C2118）两条证据，'
                 '缺一即"未生效"（wiring_decision）。'),
        'trust_caveat': ('consistency-only 档是**漂移探测器**不是布局真值证据（E-2 同源）：'
                         '它只捕获 codegen 声明相对注解常量的 stage 漂移。'),
    }


def header_facts(header_path):
    """发射头的静态事实：`virtual` 数 / 是否声明 ctor / 是否虚析构 / 纯虚条数。"""
    path = Path(header_path)
    text = path.read_text(encoding='utf-8', errors='replace')
    cls = path.stem
    return {
        'path': str(path.relative_to(PROJECT_ROOT)) if str(path).startswith(str(PROJECT_ROOT))
                else str(path),
        'cls': cls,
        'virtuals': len(re.findall(r'\bvirtual\b', text)),
        'has_virtual_dtor': bool(re.search(r'virtual\s+~', text)),
        'ctor_declared': bool(re.search(r'(?<!~)\b%s\s*\(' % re.escape(cls), text)),
        'pure_virtuals': len(re.findall(r'=\s*0\s*;', text)),
        'lines': len(text.splitlines()),
    }


def build_report(units, *, meta=None):
    """把双裁判逐单元结果合成机读报告（纯函数，JSON 可序列化）。"""
    by_unit = {}
    summary = {d: 0 for d in DIVERGENCES}
    for u in units:
        key = u.get('unit') or u.get('cls')
        by_unit[key] = u
        div = u.get('divergence')
        if div is not None:
            if div not in summary:
                raise ValueError('未知分歧分类：%r' % (div,))
            summary[div] += 1
    return {
        'generated_by': 'tests/test_vtable_e2e.py',
        'generated_at': datetime.now().isoformat(timespec='seconds'),
        'meta': dict(meta or {}),
        'units': by_unit,
        'summary': summary,
    }


def render_report(rep):
    """机读报告 → 人读小结（纯函数）。"""
    lines = ['=== 双裁判报告（L1 函数体 + .rdata vtable）===',
             '生成: %s' % rep.get('generated_at')]
    for k, v in sorted((rep.get('meta') or {}).items()):
        lines.append('  %s: %s' % (k, v))
    lines.append('')
    lines.append('%-42s %-14s %-26s %s' % ('unit', 'L1', '.rdata', '分歧'))
    for unit, u in sorted((rep.get('units') or {}).items()):
        l1 = (u.get('l1') or {}).get('status', '?')
        rd = (u.get('rdata') or {}).get('status', '?')
        lines.append('%-42s %-14s %-26s %s' % (unit, l1, rd, u.get('divergence', '?')))
    lines.append('')
    lines.append('分歧统计: %s' % json.dumps(rep.get('summary') or {}, ensure_ascii=False))
    extra = rep.get('gr_spike') or {}
    if extra.get('analysis'):
        lines.append('')
        lines.append('/GR spike: %s（no-GR value=%s col=%s | /GR value=%s col=%s | '
                     'bin_col=%s）'
                     % (extra['analysis']['verdict'], extra.get('obj_value_no_gr'),
                        extra.get('col_no_gr'), extra.get('obj_value_gr'),
                        extra.get('col_gr'), extra.get('bin_col')))
        lines.append('  建议: %s' % extra['analysis']['recommendation'])
    w = rep.get('wiring') or {}
    if w.get('decision'):
        lines.append('接线: %s（断言 %s 条，正相 rc=%s / 负相 rc=%s）'
                     % (w['decision']['verdict'], w.get('assertions'),
                        w.get('positive_rc'), w.get('negative_rc')))
    c = rep.get('bin_census') or {}
    if c:
        lines.append('表长界定: 类族判据在 %s/%s 张真机表上过度截断（注解表 %s/%s）'
                     % (c.get('truncated_family_rule'), c.get('targets'),
                        c.get('annotated_truncated'), c.get('annotated_tables')))
    b = rep.get('baselines') or {}
    if b:
        lines.append('基线: 棘轮 rc=%s（%s 类 / %s 槽）· 缺 --baseline rc=%s · mapper 漂移=%s'
                     % (b.get('ratchet_rc'), b.get('ratchet_classes'),
                        b.get('ratchet_slots_total'), b.get('write_without_baseline_rc'),
                        b.get('mapper_drift') or '{}'))
    return '\n'.join(lines)


# =====================================================================================
# 真机层（LIVE 才跑）
# =====================================================================================

def _include_dirs():
    import probe_compile as pc
    return list(pc.INCLUDE_DIRS)


def l1_context():
    """L1 裁判的共享上下文（decomp 索引 / mangling 映射 / `.text` 镜像）。"""
    global _L1_CTX
    if _L1_CTX is None:
        import compare_pal3 as cp
        di = cp.load_decomp_index()
        mm, mf = cp.build_mangled_map(di)
        bi = cp.build_basename_index(di)
        ib, text, trva, trs = cp.exe_text_image()
        _L1_CTX = {'cp': cp, 'di': di, 'mm': mm, 'bi': bi, 'ib': ib, 'text': text,
                   'trva': trva, 'trs': trs, 'mangle_failed': mf}
    return _L1_CTX


_L1_CTX = None


def _decomp_sizes():
    global _DECOMP_SIZES
    if _DECOMP_SIZES is None:
        idx = l1_context()['di']
        out = {}
        for e in idx.values():
            try:
                out[int(e['va'])] = int(e.get('size') or 0)
            except (KeyError, TypeError, ValueError):
                continue
        _DECOMP_SIZES = out
    return _DECOMP_SIZES


_DECOMP_SIZES = None


def judge_l1(unit, ctx=None):
    """L1 裁判：编译单元 + 逐函数体字节比对（`pipeline/compare_pal3` 原语）。

    与生产 L1 同一口径：`compare_pal3.PROBE_FLAGS`（`/nologo /TP /c /W3`，
    **不含 /O2、不含 /GR**）。
    """
    ctx = ctx or l1_context()
    cp = ctx['cp']
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf):
        stats, rows, _detail = cp.compare_units(
            [unit], cp.PROBE_FLAGS, ctx['di'], ctx['mm'], ctx['bi'],
            ctx['ib'], ctx['text'], ctx['trva'], ctx['trs'])
    v = l1_verdict(stats)
    v['unit'] = unit
    v['flags'] = list(cp.PROBE_FLAGS)
    v['partial_rows'] = [{'symbol': r.get('symbol'), 'va': r.get('va'),
                          'status': r.get('status'), 'match_pct': r.get('match_pct'),
                          'size': r.get('size')}
                         for r in rows if r.get('status') == 'partial']
    tail = [ln for ln in buf.getvalue().strip().splitlines() if ln.strip()]
    v['log_tail'] = tail[-1] if tail else ''
    return v


def _ctor_vptr_writes(image, va, size, targets):
    """**字节级** ctor vptr 写扫描（A 级证据：指令字节，不依赖反汇编文本/IDB）。

    形态：`c7 <modrm> <imm32>`，其中 `modrm` 是 `[reg]` 或 `[reg+disp8]`，
    `imm32 ∈ targets`（ctor 实写的表起始集合）。`c7 /0` 正是 MSVC6 的
    `movl $imm32,(%reg)` vptr 写（真机 `43d83a: c7 06 fc ac 56 00`）。
    """
    tset = set(targets)
    try:
        data = image.read(va, size)
    except Exception:
        return []
    out = []
    i = 0
    while i + 6 <= len(data):
        if data[i] != 0xC7:
            i += 1
            continue
        modrm = data[i + 1]
        mod, rm = modrm >> 6, modrm & 7
        if rm == 4 or mod == 3:            # SIB / 寄存器目的 ⇒ 不是 [reg] 形态
            i += 1
            continue
        off = i + 2 + (0 if mod == 0 else (1 if mod == 1 else 4))
        if mod == 2:
            i += 1
            continue
        if off + 4 <= len(data):
            imm = struct.unpack_from('<I', data, off)[0]
            if imm in tset:
                out.append({'offset': i, 'target': imm,
                            'bytes': ' '.join('%02x' % b for b in data[i:off + 4])})
        i += 1
    return out


def binary_table_evidence(cls):
    """二进制侧表地址证据：注解 `vtables[].addr` + ctor 字节扫描（两条独立来源）。"""
    import vtable_verify as vv
    ann_path = STRUCTS / (cls + '.json')
    ann = json.loads(ann_path.read_text(encoding='utf-8')) if ann_path.exists() else {}
    annotated = []
    for v in (ann.get('vtables') or []):
        try:
            annotated.append(int(str(v.get('addr')), 16))
        except (TypeError, ValueError):
            continue
    image = vv.PEImage(str(EXE))
    targets = vv.load_bin_targets()
    sizes = _decomp_sizes()
    scans = []
    raw_hits = []
    for addr, m in sorted((ann.get('methods') or {}).items()):
        try:
            va = int(str(addr), 16)
        except (TypeError, ValueError):
            continue
        size = min(max(sizes.get(va, 0), 0x40), 0x800)
        hits = _ctor_vptr_writes(image, va, size, targets)
        raw_hits.extend(h['target'] for h in hits)
        if hits:
            scans.append({'method_va': '0x%08X' % va,
                          'name': (m or {}).get('name'),
                          'window': size,
                          'hits': [{'offset': h['offset'],
                                    'target': '0x%08X' % h['target'],
                                    'bytes': h['bytes']} for h in hits]})
    ctor_targets = sorted(set(raw_hits))
    missing = [t for t in annotated if t not in set(ctor_targets)]
    return {
        'annotated': ['0x%08X' % a for a in annotated],
        'ctor_scan': scans,
        'ctor_targets': ['0x%08X' % t for t in ctor_targets],
        'annotated_without_ctor_write': ['0x%08X' % t for t in missing],
        'primary': (('0x%08X' % annotated[0]) if annotated
                    else (('0x%08X' % ctor_targets[0]) if ctor_targets else None)),
        'source': ('annotation' if annotated else ('ctor_scan' if ctor_targets else None)),
    }


def judge_rdata(target, workdir=None, include_dirs=None, flags=None):
    """`.rdata` 裁判：`force_emit` 强制发射 + 与真实表逐槽对比。

    ⚠️ 槽数分母用 **raw 界定**（`family_of=lambda va: None`）：类族一致性判据实测在
    87/189 张真机表上过度截断（见 `bin_table_census`）⇒ 用它会把工具自身缺陷报成
    "槽数不同"。两者都记进判词（`bin_slots` vs `bin_slots_family_rule`）。
    探针 flags 用 `/Od`（**不带 /GR**）：/GR 会注入 COL（见 `run_gr_spike`），
    逐槽地址整体位移 4 字节。
    """
    import vtable_verify as vv
    cls = target['cls']
    wd = Path(workdir or (WORKDIR / ('rdata_' + cls)))
    facts = header_facts(PROJECT_ROOT / 'pal3' / 'src' / target['header'])
    ev = binary_table_evidence(cls)
    out = {'cls': cls, 'unit': target['unit'], 'header': target['header'],
           'header_facts': facts,
           'header_virtuals': facts['virtuals'],
           'binary_polymorphic': target['binary_polymorphic'],
           'binary_table': ev['primary'], 'binary_evidence': ev,
           'probe_flags': list(flags or ['/Od'])}
    if facts['virtuals'] == 0:
        out['probe'] = {'ok': False, 'obj_slots': 0,
                        'error': '发射头 0 virtual ⇒ 不可能发射 vtable（未编译探针）'}
        out['compare'] = None
        return rdata_verdict(out)
    spec = vv.ProbeSpec(cls=cls, header=target['header'],
                        ctor_declared=facts['ctor_declared'],
                        has_virtual_dtor=facts['has_virtual_dtor'])
    try:
        emit = vv.force_emit(spec, str(wd), include_dirs=include_dirs or _include_dirs(),
                             flags=out['probe_flags'])
    except vv.EmissionError as e:
        out['probe'] = {'ok': False, 'obj_slots': 0, 'error': str(e)[:300],
                        'attempts': [dict(a) for a in e.attempts]}
        out['compare'] = None
        return rdata_verdict(out)
    art = vv.parse_obj_artifacts(emit.obj_path)
    prim = vv._pick_obj_table(vv.obj_vtables(emit.obj_path), cls)
    out['probe'] = {'ok': prim is not None,
                    'obj_slots': len(prim.slots) if prim else 0,
                    'obj': emit.obj_path, 'strategy': emit.strategy,
                    'symbol': prim.symbol if prim else None,
                    'col_symbol': prim.col_symbol if prim else None,
                    'error': None if prim else '发射成功但找不到 %s 的表' % cls}
    if prim is None or ev['primary'] is None:
        out['compare'] = None
        return rdata_verdict(out)
    image = vv.PEImage(str(EXE))
    idx = vv.load_va_index()
    targets = vv.load_bin_targets()
    base = int(ev['primary'], 16)
    bt_raw = vv.bin_table_from_image(image, base, idx=idx, targets=targets,
                                     family_of=lambda va: None)
    bt_fam = vv.bin_table_from_image(image, base, idx=idx, targets=targets)
    cands = vv.name_to_va_candidates(idx, image)
    osl = vv.normalize_obj_slots(prim, art, va_candidates_of=cands)
    bsl = vv.normalize_bin_slots(bt_raw, image, idx)
    res = vv.compare_tables(osl, bsl, obj_col=prim.col_symbol, bin_col=bt_raw.col,
                            obj_label='%s:%s' % (cls, prim.symbol),
                            bin_label='0x%X' % base,
                            obj_address_point_offset=prim.address_point_offset,
                            bin_address_point_offset=bt_raw.address_point_offset)
    out['compare'] = {'ok': res.ok, 'obj_slots': len(osl), 'bin_slots': len(bsl),
                      'bin_slots_raw': len(bt_raw.slots),
                      'bin_slots_family_rule': len(bt_fam.slots),
                      'identity_mode': res.identity_mode,
                      'bin_confidence': bt_raw.confidence,
                      'bin_broken_at': bt_raw.broken_at,
                      'deviations': [d.to_dict() for d in res.deviations],
                      'notes': list(res.notes)}
    v = rdata_verdict(out)
    v['cls'] = cls
    v['unit'] = target['unit']
    v['header_facts'] = facts
    v['binary_evidence'] = ev
    v['probe'] = out['probe']
    v['compare'] = out['compare']
    v['probe_flags'] = out['probe_flags']
    return v


def bin_table_census():
    """量化 `bin_table_from_image` 类族判据的截断面（189 表 / 92 注解表）。"""
    import vtable_verify as vv
    image = vv.PEImage(str(EXE))
    idx = vv.load_va_index()
    targets = vv.load_bin_targets()
    tot_fam = tot_raw = trunc = 0
    examples = []
    for base in targets:
        raw = vv.bin_table_from_image(image, base, idx=idx, targets=targets,
                                      family_of=lambda va: None)
        fam = vv.bin_table_from_image(image, base, idx=idx, targets=targets)
        tot_raw += len(raw.slots)
        tot_fam += len(fam.slots)
        if len(fam.slots) < len(raw.slots):
            trunc += 1
            if len(examples) < 8:
                examples.append({'base': '0x%X' % base,
                                 'family_rule': len(fam.slots),
                                 'raw': len(raw.slots),
                                 'broken_at': fam.broken_at})
    ann_total = ann_trunc = 0
    for p in sorted(STRUCTS.glob('*.json')):
        d = json.loads(p.read_text(encoding='utf-8'))
        for v in (d.get('vtables') or []):
            try:
                base = int(str(v.get('addr')), 16)
            except (TypeError, ValueError):
                continue
            ann_total += 1
            fam = vv.bin_table_from_image(image, base, idx=idx, targets=targets)
            if len(fam.slots) < len(v.get('slots') or []):
                ann_trunc += 1
    return {'targets': len(targets), 'targets_slots_raw': tot_raw,
            'targets_slots_family_rule': tot_fam,
            'truncated_family_rule': trunc,
            'annotated_tables': ann_total, 'annotated_truncated': ann_trunc,
            'examples': examples}


def run_gr_spike(workdir=None, include_dirs=None):
    """`/GR` spike：同一探针源有/无 `/GR` 的 `.obj` vtable 布局 vs 二进制 `.rdata`。"""
    import vtable_verify as vv
    wd = Path(workdir or (WORKDIR / 'gr_spike'))
    spec = vv.ProbeSpec(cls=SPIKE_CLS, header=SPIKE_HEADER, ctor_declared=True)
    ev = {'cls': SPIKE_CLS, 'header': SPIKE_HEADER}
    for tag, flags in (('no_gr', ['/Od']), ('gr', ['/Od', '/GR'])):
        emit = vv.force_emit(spec, str(wd / tag),
                             include_dirs=include_dirs or _include_dirs(), flags=flags)
        art = vv.parse_obj_artifacts(emit.obj_path)
        tbl = vv.obj_vtables(emit.obj_path)['??_7%s@@6B@' % SPIKE_CLS]
        ev['obj_value_' + tag] = tbl.address_point_offset
        ev['col_' + tag] = tbl.col_symbol
        ev['obj_size_' + tag] = os.path.getsize(emit.obj_path)
        ev['section_len_' + tag] = len(art.section(tbl.section_index)['data'])
        ev['section_name_' + tag] = art.section(tbl.section_index)['name']
        ev['symbols_' + tag] = list(emit.symbols)
    ann = json.loads((STRUCTS / (SPIKE_CLS + '.json')).read_text(encoding='utf-8'))
    base = int(str(ann['vtables'][0]['addr']), 16)
    image = vv.PEImage(str(EXE))
    bt = vv.bin_table_from_image(image, base, idx=vv.load_va_index(),
                                 targets=vv.load_bin_targets())
    ev['bin_base'] = '0x%X' % base
    ev['bin_base_minus4'] = image.dword(base - 4)
    ev['bin_base_minus4_in_code'] = image.in_code(ev['bin_base_minus4'])
    ev['bin_base_minus4_in_rdata'] = image.in_section(ev['bin_base_minus4'], '.rdata')
    ev['bin_col'] = bt.col
    ev['bin_slots'] = ['0x%08X' % s for s in bt.slots]
    ev['bin_address_point_offset'] = bt.address_point_offset
    ev['analysis'] = gr_spike_analysis(ev)
    return ev


def verify_wiring(cls='CCBStageShadow', workdir=None):
    """`_layout_asserts.h` 接线验证：正相编译 + 负相 C2118 + 生成器台账。"""
    import layout_assert_gen as lag
    wd = Path(workdir or (WORKDIR / ('wiring_' + cls)))
    wd.mkdir(parents=True, exist_ok=True)
    header = wd / ('_layout_asserts_%s.h' % cls)
    census = wd / ('census_%s.json' % cls)
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf), contextlib.redirect_stderr(buf):
        gen_rc = lag.main(['--only', cls, '--untrusted-policy', 'consistency-only',
                           '--out', str(header), '--census-json', str(census), '--quiet'])
    text = header.read_text(encoding='utf-8') if header.exists() else ''
    assertions = len(re.findall(r'typedef char', text))
    target = next((t for t in TARGETS if t['cls'] == cls), None)
    rel = target['header'] if target else None
    incs = _include_dirs()
    out = {'cls': cls, 'generator_rc': gen_rc, 'assertions': assertions,
           'header': str(header), 'census': (json.loads(census.read_text()) if census.exists()
                                            else None),
           'include_relative': rel}
    if not rel:
        out['positive_rc'] = out['negative_rc'] = None
        out['decision'] = wiring_decision(header_virtuals=0, assertions=assertions,
                                         positive_rc=1, negative_rc=1)
        return out
    src = wd / ('wire_%s.cpp' % cls)
    src.write_text('#include "%s"\n#include "%s"\nint wire_used() { return (int)sizeof(%s); }\n'
                   % (rel, header, cls), encoding='utf-8')

    def _cl(src_path, obj_name):
        cmd = ['bash', str(WINE_CL), '/c', '/nologo', '/Od']
        cmd += ['/I' + d for d in incs]
        cmd.append('/Fo' + str(wd / obj_name))
        cmd.append(str(src_path))
        p = subprocess.run(cmd, capture_output=True, text=True, cwd=str(PROJECT_ROOT))
        return p.returncode, (p.stdout or '') + (p.stderr or '')

    out['positive_rc'], out['positive_output'] = _cl(src, 'wire_pos.obj')

    # 负相：把该类断言里的第一个期望常量改掉 ⇒ 必须 C2118
    bad_text = text
    m = re.search(r'sizeof\(%s\)\s*==\s*(\d+)' % re.escape(cls), text)
    if m:
        bad_text = text[:m.start(1)] + str(int(m.group(1)) + 1) + text[m.end(1):]
        out['mutated'] = 'sizeof(%s) == %s' % (cls, m.group(1))
    else:
        m2 = re.search(r'offsetof\(%s\s*,\s*(\w+)\)\s*==\s*(\d+)' % re.escape(cls), text)
        if m2:
            bad_text = text[:m2.start(2)] + str(int(m2.group(2)) + 4) + text[m2.end(2):]
            out['mutated'] = 'offsetof(%s, %s) == %s' % (cls, m2.group(1), m2.group(2))
        else:
            out['mutated'] = None
    bad_header = wd / ('_layout_asserts_%s.bad.h' % cls)
    bad_header.write_text(bad_text, encoding='utf-8')
    bad_src = wd / ('wire_%s_bad.cpp' % cls)
    bad_src.write_text('#include "%s"\n#include "%s"\nint wire_used() { return 0; }\n'
                       % (rel, bad_header), encoding='utf-8')
    out['negative_rc'], out['negative_output'] = _cl(bad_src, 'wire_neg.obj')
    facts = header_facts(PROJECT_ROOT / 'pal3' / 'src' / rel)
    out['decision'] = wiring_decision(header_virtuals=facts['virtuals'],
                                      assertions=assertions,
                                      positive_rc=out['positive_rc'],
                                      negative_rc=out['negative_rc'])
    # /FI 不可行（强包含发生在 TU 自身 include 之前）——留痕
    fi_rc, fi_out = None, ''
    cmd = ['bash', str(WINE_CL), '/c', '/nologo', '/Od'] + ['/I' + d for d in incs]
    cmd += ['/FI' + str(header), '/Fo' + str(wd / 'wire_fi.obj'), str(src)]
    p = subprocess.run(cmd, capture_output=True, text=True, cwd=str(PROJECT_ROOT))
    fi_rc, fi_out = p.returncode, (p.stdout or '') + (p.stderr or '')
    out['force_include_rc'] = fi_rc
    out['force_include_output'] = fi_out[-400:]
    out['plan'] = wiring_plan()
    return out


def refresh_baselines(out_baseline=None):
    """当日基线：Task 5 棘轮基线 `--write-baseline`（**显式** `--baseline`）+ mapper 漂移核查。

    代码生成之后取基线才有意义（否则基线取自陈旧生成头）。
    """
    import vtable_decl_check as vdc
    path = Path(out_baseline or RATCHET_BASELINE)
    path.parent.mkdir(parents=True, exist_ok=True)
    decls = str(PROJECT_ROOT / 'pal3' / 'src')
    structs = str(STRUCTS)
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf), contextlib.redirect_stderr(buf):
        rc = vdc.main(['--decls', decls, '--structs', structs,
                       '--baseline', str(path), '--write-baseline', '-q'])
        rc2 = vdc.main(['--decls', decls, '--structs', structs, '--write-baseline', '-q'])
    base = json.loads(path.read_text(encoding='utf-8')) if path.exists() else {}
    classes = base.get('classes') or {}
    # mapper 基线（data/status/vtable_baseline.json）漂移核查：该文件由注解派生，
    # 合法注解瘦身会让它成为**过严锚点**（Task 5 评审 Q4 的根因）
    spec = importlib.util.spec_from_file_location(
        'vtable_mapper', str(PROJECT_ROOT / 'tools' / 'vtable_mapper.py'))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    _errs, _warns, stats = mod.check()
    old = json.loads(MAPPER_BASELINE.read_text(encoding='utf-8'))
    keys = ('total_slots', 'resolved', 'pass', 'fail', 'order_mismatch')
    drift = {k: [old.get(k), stats.get(k)] for k in keys if old.get(k) != stats.get(k)}
    stale = {k: [old.get(k), stats.get(k)] for k in keys if old.get(k) != stats.get(k)}
    return {'ratchet_path': str(path), 'ratchet_rc': rc,
            'write_without_baseline_rc': rc2,
            'ratchet_classes': len(classes),
            'ratchet_slots_total': sum(int(c.get('slots') or 0) for c in classes.values()),
            'mapper_stats': {k: stats.get(k) for k in ('total_slots', 'resolved',
                                                       'own_unresolved', 'pass', 'fail')},
            'mapper_baseline': {k: old.get(k) for k in keys},
            'mapper_drift': drift,
            'mapper_baseline_stale': bool(stale),
            'mapper_baseline_refresh': ('与今日一致（无需刷新）' if not stale else
                                        '需刷新 data/status/vtable_baseline.json：'
                                        + json.dumps(drift, ensure_ascii=False))}


def run_e2e(write=False, workdir=None):
    """完整端到端：3 单元 × 双裁判 + `/GR` spike + 接线 + 表长普查 + 基线。"""
    ctx = l1_context()
    units = []
    for t in TARGETS:
        l1 = judge_l1(t['unit'], ctx)
        rd = judge_rdata(t, workdir=(Path(workdir) / ('rdata_' + t['cls'])
                                     if workdir else None))
        units.append({'unit': t['unit'], 'cls': t['cls'], 'header': t['header'],
                      'binary_polymorphic': t['binary_polymorphic'],
                      'binary_evidence_note': t['evidence'],
                      'l1': l1, 'rdata': rd,
                      'divergence': classify_divergence(l1['status'], rd['status'])})
    rep = build_report(units, meta={
        'l1_flags': list(ctx['cp'].PROBE_FLAGS),
        'decomp_entries': len(ctx['di']),
        's2_units': 'n/a'})
    rep['gr_spike'] = run_gr_spike(workdir=(Path(workdir) / 'gr_spike') if workdir else None)
    rep['wiring'] = verify_wiring('CCBStageShadow',
                                  workdir=(Path(workdir) / 'wiring') if workdir else None)
    rep['bin_census'] = bin_table_census()
    rep['baselines'] = refresh_baselines()
    if write:
        REPORT_OUT.parent.mkdir(parents=True, exist_ok=True)
        REPORT_OUT.write_text(json.dumps(rep, ensure_ascii=False, indent=1),
                              encoding='utf-8')
        rep['report_path'] = str(REPORT_OUT)
    return rep


# =====================================================================================
# 离线测试：纯分析层（毫秒级，无 wine/无 IDB）
# =====================================================================================

def _l1(**kw):
    base = {'symbols': 4, 'matched': 3, 'unmatched': 1, 'match_L1': 3, 'partial': 0,
            'oob': 0, 'compile_skip': 0, 'unresolved_synth': 0}
    base.update(kw)
    return base


def test_l1_verdict_green_requires_all_matched_byte_identical():
    v = l1_verdict(_l1())
    assert v['status'] == L1_GREEN, v
    assert v['rate'] == 1.0, v
    # matched 为 0 ⇒ 不是"绿"，而是"无可比对"
    v = l1_verdict(_l1(match_L1=0, partial=0, matched=0))
    assert v['status'] == L1_NO_SYMBOLS, v
    # 只要有 1 条 partial 就不是绿
    v = l1_verdict(_l1(match_L1=2, partial=1))
    assert v['status'] == L1_PARTIAL and abs(v['rate'] - 2 / 3) < 1e-9, v


def test_l1_verdict_compile_skip_is_not_green():
    v = l1_verdict(_l1(compile_skip=1, match_L1=0, partial=0, matched=0))
    assert v['status'] == L1_SKIP, v
    assert 'compile' in v['note']


def test_l1_verdict_keeps_coverage_gaps_visible():
    """`unmatched` / `unresolved_synth` 是 L1 的**覆盖缺口**，必须留在判词里（不静默）。"""
    v = l1_verdict(_l1(matched=2, symbols=5, unmatched=3, unresolved_synth=1))
    assert v['matched'] == 2 and v['symbols'] == 5
    assert v['unmatched'] == 3 and v['unresolved_synth'] == 1


def test_rdata_verdict_clean_and_deviations():
    ev = {'header_virtuals': 8, 'binary_table': '0x56ACFC', 'binary_polymorphic': True,
          'probe': {'ok': True, 'obj_slots': 8, 'error': None},
          'compare': {'ok': True, 'obj_slots': 8, 'bin_slots': 8,
                      'bin_slots_family_rule': 1, 'deviations': []}}
    v = rdata_verdict(ev)
    assert v['status'] == RD_CLEAN, v
    # 类族判据把表截到 1 槽是**已知边界**，必须留痕而不是被当成"clean"的理由
    assert v['bin_slots_family_rule'] == 1 and v['bin_slots'] == 8, v

    ev2 = json.loads(json.dumps(ev))
    ev2['compare'] = {'ok': False, 'obj_slots': 26, 'bin_slots': 8,
                      'bin_slots_family_rule': 1,
                      'deviations': [{'kind': 'slot_count', 'index': 7}]}
    v2 = rdata_verdict(ev2)
    assert v2['status'] == RD_DEVIATIONS, v2
    assert v2['deviations'][0]['kind'] == 'slot_count'


def test_rdata_verdict_missing_vtable_when_binary_is_polymorphic():
    """二进制要多态、发射头 0 virtual ⇒ **结构性缺失**（不是"不适用"）。"""
    ev = {'header_virtuals': 0, 'binary_table': None, 'binary_polymorphic': True,
          'probe': {'ok': False, 'obj_slots': 0, 'error': '未发射'},
          'compare': None}
    v = rdata_verdict(ev)
    assert v['status'] == RD_MISSING_VTABLE, v
    ev['binary_polymorphic'] = False
    v2 = rdata_verdict(ev)
    assert v2['status'] == RD_NOT_APPLICABLE, v2


def test_rdata_verdict_probe_failure_is_not_clean():
    ev = {'header_virtuals': 5, 'binary_table': '0x56A600', 'binary_polymorphic': True,
          'probe': {'ok': False, 'obj_slots': 0, 'error': '编译失败 exit=2'},
          'compare': None}
    v = rdata_verdict(ev)
    assert v['status'] == RD_PROBE_FAILED, v
    assert 'exit=2' in v['note']


def test_rdata_verdict_no_binary_evidence():
    ev = {'header_virtuals': 3, 'binary_table': None, 'binary_polymorphic': None,
          'probe': {'ok': True, 'obj_slots': 3, 'error': None},
          'compare': None}
    v = rdata_verdict(ev)
    assert v['status'] == RD_NO_EVIDENCE, v


def test_divergence_matrix_covers_every_combination():
    """**每种组合**都有确定归类 —— 这张矩阵就是"双裁判"的可证语义。"""
    green, broken = L1_GREEN, L1_PARTIAL
    cases = {
        (green, RD_CLEAN): DIV_AGREE_CLEAN,
        (green, RD_NOT_APPLICABLE): DIV_AGREE_NONPOLY,
        (green, RD_DEVIATIONS): DIV_L1_BLIND,
        (green, RD_MISSING_VTABLE): DIV_L1_BLIND,
        (broken, RD_DEVIATIONS): DIV_BOTH_BROKEN,
        (broken, RD_MISSING_VTABLE): DIV_BOTH_BROKEN,
        (broken, RD_CLEAN): DIV_RDATA_CLEAN_L1_BROKEN,
        (broken, RD_NOT_APPLICABLE): DIV_L1_BROKEN_RDATA_NA,
        (broken, RD_PROBE_FAILED): DIV_RDATA_UNAVAILABLE,
        (green, RD_NO_EVIDENCE): DIV_RDATA_UNAVAILABLE,
    }
    for (l1, rd), want in cases.items():
        got = classify_divergence(l1, rd)
        assert got == want, (l1, rd, got, want)
        assert got in DIVERGENCES


def test_divergence_rejects_unknown_status():
    """未知状态**必须抛异常**：静默归一类会把"判不了"伪装成"判过了"。"""
    for bad in ('l1_whatever', 'rdata_whatever', None, ''):
        try:
            classify_divergence(bad, RD_CLEAN)
        except ValueError:
            pass
        else:
            raise AssertionError('未拒绝 L1 状态 %r' % (bad,))
        try:
            classify_divergence(L1_GREEN, bad)
        except ValueError:
            pass
        else:
            raise AssertionError('未拒绝 rdata 状态 %r' % (bad,))


def test_gr_spike_analysis_flags_structural_blocker():
    """`/GR` 注入 COL ⇒ 每表多 4 字节 + 逐槽位移 ⇒ byte-match 结构性不可能。"""
    ev = {'obj_value_no_gr': 0, 'col_no_gr': None,
          'obj_value_gr': 4, 'col_gr': '??_R4AStarPathFinder@@6B@',
          'bin_col': None, 'bin_base_minus4': 0x3F800000,
          'bin_base_minus4_in_code': False}
    r = gr_spike_analysis(ev)
    assert r['col_injected'] is True, r
    assert r['target_has_col'] is False, r
    assert r['byte_match_possible'] is False, r
    assert r['verdict'] == 'GR_IS_STRUCTURAL_BLOCKER', r
    assert '/GR' in r['recommendation'] and '移除' in r['recommendation'], r


def test_gr_spike_analysis_no_gr_is_aligned():
    ev = {'obj_value_no_gr': 0, 'col_no_gr': None,
          'obj_value_gr': 0, 'col_gr': None,
          'bin_col': None, 'bin_base_minus4': 0x3F800000,
          'bin_base_minus4_in_code': False}
    r = gr_spike_analysis(ev)
    assert r['col_injected'] is False and r['byte_match_possible'] is True, r
    assert r['verdict'] == 'GR_ALIGNED', r


def test_gr_spike_analysis_both_sides_have_col_is_not_blocker():
    ev = {'obj_value_no_gr': 4, 'col_no_gr': '??_R4X@@6B@',
          'obj_value_gr': 4, 'col_gr': '??_R4X@@6B@',
          'bin_col': 0x569000, 'bin_base_minus4': 0x569000,
          'bin_base_minus4_in_code': False}
    r = gr_spike_analysis(ev)
    assert r['target_has_col'] is True, r
    assert r['byte_match_possible'] is True, r


def test_wiring_decision_positive_and_negative_control():
    ok = wiring_decision(header_virtuals=0, assertions=9, positive_rc=0, negative_rc=2)
    assert ok['verdict'] == 'wired_and_enforced', ok
    # 正相过、负相也过 ⇒ 断言根本没生效（被注释掉了）
    dead = wiring_decision(header_virtuals=0, assertions=9, positive_rc=0, negative_rc=0)
    assert dead['verdict'] == 'not_enforced', dead
    # 正相编不过 ⇒ 假杀（真实数据全量开启会 64 假杀 + 71 C2039）
    kill = wiring_decision(header_virtuals=8, assertions=200, positive_rc=2, negative_rc=2)
    assert kill['verdict'] == 'false_kill', kill
    # 0 条断言 ⇒ 无判别力
    none = wiring_decision(header_virtuals=0, assertions=0, positive_rc=0, negative_rc=0)
    assert none['verdict'] == 'no_assertions', none


def test_wiring_plan_documents_include_placement_and_rollout():
    p = wiring_plan()
    txt = json.dumps(p, ensure_ascii=False)
    # 生成器明写"必须在全部类声明之后包含"（sizeof/offsetof 需完整类型）⇒ 方案必须遵守
    assert '全部类声明之后' in txt, txt
    # I-2 档是按类试运行：--only + consistency-only
    assert '--only' in txt and 'consistency-only' in txt, txt
    # 全量一次性开启的代价必须写明
    assert '64' in txt and 'C2039' in txt, txt
    # /FI 不可行也要写明（否则后人会重复踩）
    assert '/FI' in txt, txt


def test_header_facts_reads_emitted_header():
    f = header_facts(PROJECT_ROOT / 'pal3' / 'src' / 'UI' / 'UIWnd.h')
    assert f['virtuals'] >= 18, f
    assert f['has_virtual_dtor'] is True, f
    g = header_facts(PROJECT_ROOT / 'pal3' / 'src' / 'Combat' / 'CCBStageShadow.h')
    assert g['virtuals'] == 0, g
    assert g['has_virtual_dtor'] is False, g
    h = header_facts(PROJECT_ROOT / 'pal3' / 'src' / 'Misc' / 'UI3DCtrl.h')
    assert h['virtuals'] >= 8 and h['has_virtual_dtor'] is True, h


def test_report_is_json_serializable_and_summarizes_divergences():
    units = [
        {'unit': 'a.cpp', 'cls': 'A', 'l1': {'status': L1_GREEN, 'match_L1': 2, 'partial': 0},
         'rdata': {'status': RD_DEVIATIONS}, 'divergence': DIV_L1_BLIND},
        {'unit': 'b.cpp', 'cls': 'B', 'l1': {'status': L1_PARTIAL, 'match_L1': 0, 'partial': 1},
         'rdata': {'status': RD_CLEAN}, 'divergence': DIV_RDATA_CLEAN_L1_BROKEN},
    ]
    rep = build_report(units, meta={'generated_by': 'x'})
    back = json.loads(json.dumps(rep))
    assert back['summary'][DIV_L1_BLIND] == 1, back['summary']
    assert back['summary'][DIV_RDATA_CLEAN_L1_BROKEN] == 1, back['summary']
    assert set(back['summary']) == set(DIVERGENCES), back['summary']
    txt = render_report(back)
    assert 'l1_blind_rdata_broken' in txt and 'b.cpp' in txt, txt


def test_report_rejects_unknown_divergence():
    """报告层不得把未知分歧静默吞掉（否则统计会漏计数）。"""
    units = [{'unit': 'a.cpp', 'cls': 'A', 'l1': {}, 'rdata': {}, 'divergence': 'wat'}]
    try:
        build_report(units)
    except ValueError:
        return
    raise AssertionError('未知分歧分类未被拒绝')


def test_roster_matches_repo_reality():
    """花名册的 3 个断裂单元**必须**真实存在、类注解可见、且在 S2 通过名单里。"""
    census = json.loads(CENSUS.read_text(encoding='utf-8'))
    ok_units = {r['unit']: r['status'] for r in census['s2']['results']}
    for t in TARGETS:
        assert (PROJECT_ROOT / t['unit']).is_file(), t['unit']
        assert (PROJECT_ROOT / 'pal3' / 'src' / t['header']).is_file(), t['header']
        assert (STRUCTS / (t['cls'] + '.json')).is_file(), t['cls']
        assert ok_units.get(t['unit']) == 'ok', (t['unit'], ok_units.get(t['unit']))
    assert len(TARGETS) == 3


def test_three_targets_are_the_known_broken_ones():
    """3 个单元在花名册里的**断裂判词**由数据派生，但"3 个"这个规模必须钉死。"""
    assert sorted(t['cls'] for t in TARGETS) == [
        'CCBStageShadow', 'PalScriptWaitObj', 'UI3DCtrl']
    for t in TARGETS:
        assert t['evidence'], t


# =====================================================================================
# LIVE：真机端到端（wine 编译 + PAL3.exe）
# =====================================================================================

def _need_live():
    if not LIVE:
        raise unittest.SkipTest('设 PAL3_E2E_LIVE=1 才跑真机端到端')
    if not EXE.exists():
        raise unittest.SkipTest('缺少 %s' % EXE)
    if not WINE_CL.exists():
        raise unittest.SkipTest('缺少 %s' % WINE_CL)


def test_live_l1_judge_three_units():
    _need_live()
    ctx = l1_context()
    for t in TARGETS:
        v = judge_l1(t['unit'], ctx)
        assert v['status'] in ALL_L1, v
        assert v['symbols'] > 0, v
        assert v['compile_skip'] == 0, v
        assert v['matched'] > 0, v


def test_live_rdata_judge_three_units():
    _need_live()
    for t in TARGETS:
        v = judge_rdata(t)
        assert v['status'] in ALL_RD, v
        assert v['status'] != RD_PROBE_FAILED, (t['cls'], v.get('note'))


def test_live_ctor_scan_locates_ui3dctrl_table_byte_exactly():
    """证据生产者自证：`UI3DCtrl` ctor `0x43D83A` 的字节 `c7 06 fc ac 56 00`
    必须被**字节级扫描**找到，且与注解 `vtables[0].addr` 同址（两条独立来源互证）。"""
    _need_live()
    ev = binary_table_evidence('UI3DCtrl')
    assert ev['annotated'] and ev['annotated'][0] == '0x0056ACFC', ev
    hits = [h for s in ev['ctor_scan'] for h in s['hits']]
    assert any(h['target'] == '0x0056ACFC' for h in hits), ev
    assert any(h['bytes'].startswith('c7 06') for h in hits), hits
    # CCBStageShadow 的 ctor 里**没有** vptr 写 ⇒ 非多态（负相）
    ev2 = binary_table_evidence('CCBStageShadow')
    assert ev2['ctor_targets'] == [], ev2


def test_live_bin_table_census_quantifies_family_rule_truncation():
    """已知边界必须**可复现地量化**（报告里的 87/189 不是口头结论）。"""
    _need_live()
    c = bin_table_census()
    assert c['targets'] >= 100, c
    # 639 是 Task 6 报告发表的"189 表/639 槽" ⇒ 与本文件的 raw 界定交叉核对：
    # 两者只差**类族判据**这一条（raw 1164 槽 vs 族判据 639 槽）⇒ 证明 Task 6 的
    # 真机槽数是在**被过度截断**的表上算出来的（本任务 e2e 归因项）。
    assert c['targets_slots_raw'] == 1164, c
    assert c['targets_slots_family_rule'] == 639, c
    assert c['truncated_family_rule'] > 0, c
    assert c['truncated_family_rule'] <= c['targets'], c
    assert c['annotated_tables'] >= 50, c
    assert c['annotated_truncated'] > 0, c


def test_live_gr_spike_is_a_structural_blocker():
    _need_live()
    r = run_gr_spike()
    assert r['obj_value_no_gr'] == 0 and r['col_no_gr'] is None, r
    assert r['obj_value_gr'] == 4, r
    assert r['col_gr'].startswith('??_R4'), r
    # 目标无 COL：表 address point 前 4 字节是 float 数据（1.0f）不是指针
    assert r['bin_col'] is None, r
    assert r['bin_base_minus4_in_code'] is False, r
    assert r['analysis']['verdict'] == 'GR_IS_STRUCTURAL_BLOCKER', r


def test_live_layout_assert_wiring_enforced():
    _need_live()
    w = verify_wiring('CCBStageShadow')
    assert w['generator_rc'] == 0, w
    assert w['assertions'] > 0, w
    assert w['positive_rc'] == 0, w['positive_output'][:300]
    assert w['negative_rc'] != 0, w
    assert 'C2118' in w['negative_output'], w['negative_output'][:300]
    assert w['decision']['verdict'] == 'wired_and_enforced', w
    # /FI 不可行（强包含早于类声明）——留痕且不是"通过"
    assert w['force_include_rc'] != 0, w


def test_live_refresh_baselines():
    _need_live()
    b = refresh_baselines()
    assert b['ratchet_rc'] == 0, b
    assert b['ratchet_classes'] >= 50, b
    assert b['ratchet_slots_total'] >= 800, b
    # 缺 --baseline ⇒ rc=2（Task 5 R=1 Q2：否则门禁永久静默关闭）
    assert b['write_without_baseline_rc'] == 2, b
    assert b['mapper_stats']['total_slots'] >= 800, b


def test_live_dual_judge_report_end_to_end():
    _need_live()
    rep = run_e2e(write=True)
    assert len(rep['units']) == 3, rep['units']
    for t in TARGETS:
        u = rep['units'][t['unit']]
        assert u['l1']['status'] in (L1_GREEN, L1_PARTIAL), u['l1']
        assert u['rdata']['status'] in ALL_RD, u['rdata']
        assert u['rdata']['status'] != RD_NO_EVIDENCE, u['rdata']
        assert u['divergence'] in DIVERGENCES, u
    assert rep['gr_spike']['analysis']['verdict'] == 'GR_IS_STRUCTURAL_BLOCKER'
    assert rep['wiring']['decision']['verdict'] == 'wired_and_enforced'
    assert rep['bin_census']['truncated_family_rule'] > 0
    assert rep['baselines']['ratchet_rc'] == 0
    # 报告落盘且可回读
    back = json.loads(REPORT_OUT.read_text(encoding='utf-8'))
    assert set(back['units']) == set(rep['units'])


# =====================================================================================
# 自带 runner（本仓 pytest 断言重写器在此环境不可用 ⇒ 与既有 vtable 测试同款 runner）
# =====================================================================================
def _self_runner():
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    return 1 if fail else 0


if __name__ == '__main__':
    ap = argparse.ArgumentParser(description='Task 8 端到端双裁判')
    ap.add_argument('--e2e', action='store_true', help='跑完整真机端到端并打印报告')
    ap.add_argument('--out', default=None, help='报告 JSON 输出路径（默认 data/status/vtable_e2e_report.json）')
    ap.add_argument('--workdir', default=None, help='编译产物目录（默认 /tmp/pal3_e2e）')
    args = ap.parse_args()
    if args.e2e:
        if args.workdir:
            WORKDIR = Path(args.workdir)
        rep = run_e2e(write=True, workdir=WORKDIR)
        if args.out:
            Path(args.out).write_text(json.dumps(rep, ensure_ascii=False, indent=1),
                                      encoding='utf-8')
            rep['report_path'] = args.out
        print(render_report(rep))
        print('\n报告 -> %s' % rep.get('report_path', REPORT_OUT))
        sys.exit(0)
    sys.exit(_self_runner())