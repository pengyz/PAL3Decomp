#!/usr/bin/env python3
"""[gbengine 共享头完成度战役 T1 普查 2026-11-22]

背景: gbCamera/gbMatrixStack 已重建(include/gbengine/ 有定义), gbLightObj/gbOBBox
疑似仅前置声明。战役第一步=规模评估: 谁在缺什么成员, 缺口面多大, 域归属如何。

四问:
  Q1 S2 错误面 gb 族归因: 错误 msg 中引用的 gb* 类×成员(域前缀) 聚合
      — C2039 "not a member of 'X'" / C2027 "use of undefined type 'X'"
  Q2 gbLightObj/gbOBBox 使用形态: decomp 语料中的 成员/指针/方法调用 普查
  Q3 IAT 域归属: 普查 gb* 方法是否 GBENGINE 导入(声明须 dllimport 合规=F70)
  Q4 api.h dump 完备度: gbengine_api.h 每类方法数 × 共享头现有方法数 差额

输出: 控制台报告 + data/status/gbsdk_header_gap_20261122.json

用法: python3 tools/census_gbsdk_header_gap_20261122.py
"""
import json
import re
import glob
from pathlib import Path
from collections import Counter, defaultdict

REPO = Path(__file__).parent.parent

# gb 域类名清单(共享头类+基础类型)
GB_CLASSES = set()
for fp in glob.glob(str(REPO / 'include' / 'gbengine' / '*.h')):
    for m in re.finditer(r'class\s+(?:GBAPI\s+)?(\w+)', Path(fp).read_text(encoding='utf-8', errors='replace')):
        GB_CLASSES.add(m.group(1))
# 基础类型(gbengine_types.h)
GB_TYPES = {'gbVec3D', 'gbMatrix4', 'gbQuaternion', 'gbRay', 'gbAxis', 'gbViewPort',
            'gbColor', 'gbPlane'}

print('== gb 共享头类清单 %d ==' % len(GB_CLASSES))
print('  ', ', '.join(sorted(GB_CLASSES)))

# ── Q1: S2 错误面 gb 族归因 ──────────────────────────────
census = json.load(open(REPO / 'data' / 'status' / 'probe_census.json'))
s2 = census['s2']
# C2039: "'member' : is not a member of 'Cls'"
# C2027: "use of undefined type 'Cls'"
pats = {
    'C2039': re.compile(r"'([\w:]+)' : is not a member of '(?:class |struct )?([\w:]+)'"),
    'C2027': re.compile(r"use of undefined type '(?:class |struct )?([\w:]+)'"),
}
member_gap = defaultdict(set)      # cls → {member...} (仅 gb 族类)
err_by_code_gb = Counter()
err_units_gb = Counter()
gb_cls_set = GB_CLASSES | GB_TYPES
for r in s2['results']:
    if r['status'] != 'fail':
        continue
    unit = r['unit']
    for e in r.get('errors', []):
        code, msg = e.get('code', ''), e.get('msg', '')
        hit = False
        if code == 'C2039':
            m = pats['C2039'].search(msg)
            if m and m.group(2).split('::')[-1] in gb_cls_set:
                member_gap[m.group(2).split('::')[-1]].add(m.group(1))
                hit = True
        elif code == 'C2027':
            m = pats['C2027'].search(msg)
            if m and m.group(1).split('::')[-1] in gb_cls_set:
                member_gap[m.group(1).split('::')[-1]].add('<undefined-type>')
                hit = True
        if hit:
            err_by_code_gb[code] += 1
            err_units_gb[unit] += 1

print('\n== Q1 S2 错误面 gb 族缺口(按类) ==')
total_gap = 0
for cls, mems in sorted(member_gap.items(), key=lambda kv: -len(kv[1])):
    total_gap += len(mems)
    print('  %-18s 缺成员 %d: %s' % (cls, len(mems), ', '.join(sorted(mems)[:12])))
print('  合计: 类 %d, 成员缺口 %d, 错误 %s' % (
    len(member_gap), total_gap, dict(err_by_code_gb)))
print('  涉及单元 %d:' % len(err_units_gb))
for u, n in err_units_gb.most_common(12):
    print('    %-44s %d' % (u, n))

# ── Q2: gbLightObj/gbOBBox 使用形态 ─────────────────────
srcs = list((REPO / 'pal3' / 'src').rglob('*.h')) + list((REPO / 'pal3' / 'src').rglob('*.cpp'))
use_shapes = defaultdict(lambda: Counter())
call_sites = defaultdict(set)
for f in srcs:
    try:
        t = f.read_text(encoding='utf-8', errors='replace')
    except Exception:
        continue
    for cls in ('gbLightObj', 'gbOBBox', 'gbCamControler', 'gbSceneGraph', 'gbVisNode',
                'gbMesh', 'gbGeomNode', 'gbActor', 'gbGfxManager'):
        if cls not in t:
            continue
        for m in re.finditer(r'\b' + cls + r'\b\s*(\*|&)?', t):
            use_shapes[cls]['decl_ptr' if m.group(1) == '*' else 'decl_ref' if m.group(1) == '&' else 'bare'] += 1
        # 方法调用形态 Cls->Method / obj.Method — 抓 ->Name( 调用点
        for m in re.finditer(r'\b(\w+)\s*(?:->|\.)\s*(\w+)\s*\(', t):
            if re.search(r'\b' + cls + r'\b\s*\*+\s*' + m.group(1) + r'\b|\b' + cls + r'\s+' + m.group(1) + r'\b', t):
                call_sites[cls].add(m.group(2))

print('\n== Q2 使用形态(声明点计数) ==')
for cls, c in use_shapes.items():
    print('  %-16s %s' % (cls, dict(c)))
print('\n== Q2 语料可见方法调用名(推断, 按 ->( 调用统计) ==')
for cls, names in sorted(call_sites.items()):
    if names:
        print('  %-16s (%d): %s' % (cls, len(names), ', '.join(sorted(names)[:16])))

# ── Q3: IAT 域归属(GBENGINE 导入的方法名→类名) ──────────
iat = json.load(open(REPO / 'data' / 'status' / 'iat_census_20261122.json'))
gb_import_classes = iat.get('q3_gbengine_classes', [])
print('\n== Q3 GBENGINE 导入涉及类 %d ==' % len(gb_import_classes))
print('  ', ', '.join(gb_import_classes))

# ── Q4: api.h dump × 共享头 方法数差额 ──────────────────
api_h = (REPO / 'include' / 'gbengine_api.h').read_text(encoding='utf-8', errors='replace')
api_methods = defaultdict(set)
for m in re.finditer(r'(\w[\w:<>&\*\s]*?)\s*__thiscall\s+(\w+)::(\w+)\s*\(', api_h):
    api_methods[m.group(2)].add(m.group(3))
share_methods = defaultdict(set)
for fp in glob.glob(str(REPO / 'include' / 'gbengine' / '*.h')):
    t = Path(fp).read_text(encoding='utf-8', errors='replace')
    cur = None
    for line in t.splitlines():
        cm = re.match(r'\s*class\s+(?:GBAPI\s+)?(\w+)', line)
        if cm:
            cur = cm.group(1)
            continue
        if cur:
            dm = re.match(r'\s*(?:virtual\s+)?(?:static\s+)?[\w:<>&\*]+\s+(~?\w+)\s*\(', line)
            if dm and dm.group(1) not in ('if', 'for', 'while', 'switch', 'sizeof'):
                share_methods[cur].add(dm.group(1))

print('\n== Q4 api.h(1019导出) × 共享头 方法名差额 ==')
diff_report = {}
for cls in sorted(set(api_methods) | set(share_methods)):
    api_m, sh_m = api_methods.get(cls, set()), share_methods.get(cls, set())
    missing = api_m - sh_m
    extra = sh_m - api_m
    if missing or extra:
        diff_report[cls] = {'api': len(api_m), 'shared': len(sh_m),
                            'missing_in_shared': sorted(missing), 'extra_in_shared': sorted(extra)}
        print('  %-18s api=%-3d 共享=%-3d 缺%s %s' % (
            cls, len(api_m), len(sh_m), len(missing), ', '.join(sorted(missing)[:10]) or '-'))

out = {
    '_doc': 'gbengine 共享头完成度战役 T1 普查 2026-11-22',
    'q1_member_gap': {k: sorted(v) for k, v in member_gap.items()},
    'q1_err_by_code': dict(err_by_code_gb),
    'q1_err_units': dict(err_units_gb),
    'q2_use_shapes': {k: dict(v) for k, v in use_shapes.items()},
    'q2_call_names': {k: sorted(v) for k, v in call_sites.items()},
    'q3_gbengine_import_classes': gb_import_classes,
    'q4_api_vs_shared': diff_report,
}
outp = REPO / 'data' / 'status' / 'gbsdk_header_gap_20261122.json'
outp.write_text(json.dumps(out, ensure_ascii=False, indent=1), encoding='utf-8')
print('\n报告 →', outp)
