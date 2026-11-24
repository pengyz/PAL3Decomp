#!/usr/bin/env python3
"""[探针 2026-11-24 #11 v3] B 案 Scene 归属纠错——完整迁移台账采集。

ecx 来源分类(寄存器源回溯 ≤20 条):
  static7 — mov ecx, imm ∈ 7 静态实例 → 真 RoleSystem
  rs_heap — mov ecx, <符号>(指针型 RoleSystem*) 解引用 → 堆 RoleSystem 实例
  scene   — UISceneUpdate/@Scene@@ 方法链(返回 Scene* 喂下游) / Scene* 指针解引用
  other_imm/derived — 其他
verdict: SCENE(纯 scene) / RS(纯 static7+heap) / MIXED(两类都有) / DERIVED-ONLY / OTHER
用法: /home/peng/.local/ida-mcp-venv/bin/python tools/probe_scene_attribution_ledger_20261124.py
"""
import sys
import re
import os
import json
import collections

sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro

db = idapro.open_database(
    '/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
    run_auto_analysis=False)

import idc
import ida_bytes
import ida_funcs
import ida_name
import idautils
import ida_segment

REPO = '/home/peng/workspace/PAL3Decomp'
OUT = []


def say(s):
    print(s)
    OUT.append(s)


def func_range(ea):
    f = ida_funcs.get_func(ea)
    return (f.start_ea, f.end_ea) if f else (ea, ea + 0x400)


def func_name(ea):
    n = ida_name.get_name(ea)
    return (n if n else 'sub_%X' % ea)[:56]


RS_INSTANCES = (0xBFDBB0, 0xBFFDB0, 0xC020F8, 0xC12B48, 0x17A8AE8, 0xC043A0, 0xC0A360)
UISceneUpdate = 0x4226F0

ts = None
for seg_ea in idautils.Segments():
    sg = ida_segment.getseg(seg_ea)
    if ida_segment.get_segm_name(sg) == '.text':
        ts = sg
blob = ida_bytes.get_bytes(ts.start_ea, ts.end_ea - ts.start_ea) or b''
base = ts.start_ea

# 指针型全局类型表
_gj = json.load(open(os.path.join(REPO, 'data/annotations/globals.json')))
_ptr_types = {}
for _k, _e in _gj.items():
    if isinstance(_e, dict):
        _t = str(_e.get('type', ''))
        if _t.strip() in ('RoleSystem *', 'Scene *'):
            _ptr_types['%08x' % int(_k, 16)] = 'rs_heap' if 'RoleSystem' in _t else 'scene_ptr'


def _deref_kind(name_tok):
    ea = idc.get_name_ea_simple(name_tok)
    if ea and ea != idc.BADADDR:
        kd = _ptr_types.get('%08x' % ea)
        if kd:
            return kd
    m = re.match(r'(?:[ds]s:)?([0-9A-Fa-f]{6,8})h?$', name_tok)
    if m:
        return _ptr_types.get('%08x' % int(m.group(1).rstrip('h'), 16))
    m = re.match(r'\w+_?([0-9A-Fa-f]{6,8})$', name_tok)
    if m:
        return _ptr_types.get('%08x' % int(m.group(1), 16))
    return None


def scene_loose(site):
    cur = site
    for k in range(15):
        prev = idc.prev_head(cur, func_range(site)[0] - 0x2000)
        if prev == idc.BADADDR:
            return False
        cur = prev
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        m = re.match(r'call\s+([^;\s]+)', t)
        if m:
            tok = m.group(1)
            if tok == 'UISceneUpdate' or '@Scene@@' in tok:
                return True
        if re.match(r'mov\s+ecx\s*,\s*[0-9A-Fa-f]+h?\s*(?:;.*)?$', t):
            return False  # ecx 被其他立即数重载 → 非场景链
    return False


def classify_site(site):
    reg = 'ecx'
    cur = site
    for k in range(20):
        prev = idc.prev_head(cur, func_range(site)[0] - 0x2000)
        if prev == idc.BADADDR:
            return 'derived', None
        cur = prev
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        m = re.match(r'call\s+([^;\s]+)', t)
        if m:
            tok = m.group(1)
            if '@Scene@@' in tok or tok == 'UISceneUpdate':
                continue  # Scene 方法链: 返回 Scene* 喂下游
            return 'derived', None
        m2 = re.match(r'mov\s+%s\s*,\s*([^;]+?)(?:;.*)?$' % reg, t)
        if m2:
            operand = m2.group(1).strip()
            if re.match(r'^[0-9A-Fa-f]+h?$', operand):
                imm = int(operand.rstrip('h'), 16)
                if imm in RS_INSTANCES:
                    return 'static7', imm
                return 'other_imm', imm
            if re.match(r'^e[a-z]{2}$', operand):
                reg = operand
                continue
            kd = _deref_kind(operand)
            if kd == 'rs_heap':
                return 'rs_heap', operand
            if kd == 'scene_ptr':
                return 'scene', operand
            return 'derived', operand
        m4 = re.match(r'mov\s+%s\s*,\s*(e[a-z]{2})\s*(?:;.*)?$' % reg, t)
        if m4:
            reg = m4.group(1)
            continue
        if re.match(r'(lea|mov)\s+%s\s*,\s*\[e[a-z]{2}' % reg, t):
            return 'derived', None
    return 'derived', None


# 收集 RoleSystem-mangled 方法
rs_funcs = {}
for ea in idautils.Functions():
    nm = ida_name.get_name(ea) or ''
    m = re.match(r'\?(\w+)@RoleSystem@@', nm)
    if m:
        rs_funcs[ea] = m.group(1)
say('RoleSystem-mangled 方法: %d' % len(rs_funcs))

# 全部调用点
sites = collections.defaultdict(list)
for ea in idautils.Functions():
    fs, fe = func_range(ea)
    cur = fs
    n = 0
    while cur < fe and n < 6000:
        if not ida_bytes.is_code(ida_bytes.get_flags(cur)):
            break
        t = (idc.generate_disasm_line(cur, 0) or '').strip()
        m = re.match(r'call\s+([^;\s]+)', t)
        if m:
            tok = m.group(1)
            ta = int(tok.rstrip('h'), 16) if re.match(r'^[0-9A-Fa-f]+h?$', tok) \
                else idc.get_name_ea_simple(tok)
            if ta in rs_funcs:
                sites[ta].append(cur)
        cur = idc.next_head(cur, fe)
        n += 1

ledger = {}
for ta, name in sorted(rs_funcs.items()):
    cls = collections.Counter()
    other_addrs = set()
    for site in sites.get(ta, []):
        c, info = classify_site(site)
        cls[c] += 1
        if c == 'other_imm' and info:
            other_addrs.add(info)
    loose = scene_loose(sites[ta][0]) if sites.get(ta) else False
    if not sites.get(ta):
        verdict = 'UNCALLED'
    elif (cls['static7'] or cls['rs_heap']) and not loose:
        verdict = 'RS'
    elif (cls['static7'] or cls['rs_heap']) and loose:
        verdict = 'MIXED'
    elif loose:
        verdict = 'SCENE-LEAN'
    elif cls['other_imm']:
        verdict = 'OTHER'
    else:
        verdict = 'DERIVED-ONLY'
    ledger['0x%08x' % ta] = {
        'name': name,
        'hosts': len(sites.get(ta, [])),
        'static7': cls['static7'], 'rs_heap': cls['rs_heap'],
        'scene': cls['scene'], 'derived': cls['derived'],
        'other_imm': cls['other_imm'],
        'other_addrs': sorted(set('0x%08x' % a for a in other_addrs))[:4],
        'verdict': verdict,
    }

by = collections.Counter(v['verdict'] for v in ledger.values())
say('\n========== B 案归属台账 v3 ==========')
say('verdict 分布: %s' % dict(by))
for v in ('SCENE-LEAN', 'MIXED', 'RS', 'DERIVED-ONLY', 'OTHER'):
    rows = [(k, d) for k, d in ledger.items() if d['verdict'] == v]
    say('\n%s (%d):' % (v, len(rows)))
    for k, d in sorted(rows, key=lambda x: -x[1]['hosts'])[:35]:
        say('  %s %-30s hosts=%-3d s7=%-3d hp=%-3d sc=%-3d der=%-3d oi=%-3d %s' % (
            k, d['name'], d['hosts'], d['static7'], d['rs_heap'],
            d['scene'], d['derived'], d['other_imm'], d['other_addrs'][:2]))

json.dump({'generated': '2026-11-24', 'version': 'v3',
           'rs_instances': ['0x%08x' % a for a in RS_INSTANCES],
           'ledger': ledger},
          open(os.path.join(REPO, 'data/status/archive/scene_attribution_ledger_20261124.json'), 'w'),
          ensure_ascii=False, indent=1)
with open('/home/peng/workspace/PAL3Decomp/pipeline/ida/probe_scene_ledger_out.txt',
          'w', encoding='utf-8') as f:
    f.write('\n'.join(OUT))
print('\n[probe11 v3] ledger saved')
idapro.close_database(False)
