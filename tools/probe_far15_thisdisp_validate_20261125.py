#!/usr/bin/env python3
"""probe_far15_thisdisp_validate_20261125.py — this-disp 交叉验证。
对 far 15 (10 已迁+5 留守): 方法体 [reg+disp] 集合 → 匹配目标类已知成员偏移
→ 偏移吻合率 = 置信度量化。
"""
import sys, json, os, glob, re, collections
sys.path.insert(0, '/home/peng/ida-pro-9.1/idalib/python')
import idapro
db = idapro.open_database('/home/peng/workspace/PAL3Decomp/original/PAL3.exe.i64',
                          run_auto_analysis=False)
import idc, ida_funcs

# 1. 构建全项目偏移→(类,成员名) 反查表
offset_index = {}  # offset → set of (cls, member_name, type)
for p in glob.glob('data/annotations/structs/*.json'):
    cls = os.path.basename(p)[:-5]
    try:
        d = json.load(open(p, encoding='utf-8'))
    except:
        continue
    for k, v in (d.get('known_members') or {}).items():
        if not isinstance(v, dict):
            continue
        try:
            off = int(k, 16)
        except:
            continue
        nm = str(v.get('name') or '')
        t = str(v.get('type') or '')
        offset_index.setdefault(off, set()).add((cls, nm, t))

# 2. far 15 清单
cm = json.load(open('data/annotations/structs/CScreenMode.json', encoding='utf-8'))
gb = json.load(open('data/annotations/structs/gbBinkVideo.json', encoding='utf-8'))
# 已迁 10: 从各真主 json 收集(今天迁的)
MIGRATED = {
    'SetTooltipText': 'UIScene', 'SetProgress': 'UIScene', 'GetPlayerAttByIndex': 'UIScene',
    'HideUIBars': 'UIEmote', 'GetMouseScroll': 'TaskBookUI', 'GetMouseDelta': 'UITitle_JDHY',
    'InitGameUI': 'UISceneFrm', 'InitEquipScreen': 'UITitle_ArcSave',
    'ResetProgressList': 'EquipUI', 'SetPosition': 'UILBColumn',
}
# 留守 5: CScreenMode.json 中不在已迁列表的
remaining = {}
for a, m in (cm.get('methods') or {}).items():
    nm = str(m.get('name') or '?')
    if nm in MIGRATED:
        continue
    remaining[nm] = (int(a, 16), 'CScreenMode')

# 已迁方法: 从真主 json 找地址
migrated_methods = {}
for nm, tgt in MIGRATED.items():
    tp = 'data/annotations/structs/%s.json' % tgt
    d = json.load(open(tp, encoding='utf-8'))
    for a, m in (d.get('methods') or {}).items():
        if str(m.get('name') or '') == nm:
            migrated_methods[nm] = (int(a, 16), tgt)

OUT = '/home/peng/workspace/PAL3Decomp/data/status/probe_far15_thisdisp_validate_20261125.json'
report = {}

def census_disps(ea, limit=4000):
    """方法体 [reg+disp] 全集"""
    f = ida_funcs.get_func(ea)
    if not f:
        return set()
    disps = set()
    cur = f.start_ea
    n = 0
    while cur < f.end_ea and n < limit:
        t = (idc.generate_disasm_line(cur, 0) or '').split(';')[0].strip()
        mm = re.search(r'\[(?:e[a-z]{2})\+([0-9A-Fa-f]{1,8})h?\]', t)
        if mm:
            off = int(mm.group(1), 16)
            if off < 0x200000:
                disps.add(off)
        cur = idc.next_head(cur, f.end_ea)
        n += 1
    return disps

def match_class(disps, target_cls):
    """disp 集与目标类 known_members 偏移吻合率"""
    cls_offsets = set()
    for off, entries in offset_index.items():
        for c, nm, t in entries:
            if c == target_cls:
                cls_offsets.add(off)
                break
    if not cls_offsets:
        return 0, 0
    hits = sum(1 for d in disps if d in cls_offsets)
    return hits, len(disps)

# 3. 验证已迁 10
print('=== 已迁 10 this-disp 交叉验证 ===')
for nm, (ea, tgt) in sorted(migrated_methods.items()):
    disps = census_disps(ea)
    hits, total = match_class(disps, tgt)
    # 也查 CScreenMode (对照: 可能才是真主)
    hits_cm, _ = match_class(disps, 'CScreenMode')
    pct = 100.0 * hits / total if total else 0
    top = sorted([(len([d for d in disps if d in set(o for o, e in offset_index.items() if any(c == c for c, _, _ in e))]),
                   c) for c in set(c for offs in offset_index.values() for c, _, _ in offs)],
                 reverse=True)[:3] if disps else []
    result = {'ea': hex(ea), 'target': tgt, 'disp_n': total, 'hits_target': hits,
              'pct': round(pct, 1), 'hits_cscreenmode': hits_cm}
    report['migrated_' + nm] = result
    print('%-24s → %-14s hits=%d/%d (%.0f%%) CScreenMode 命中=%d' % (nm, tgt, hits, total, pct, hits_cm))

# 4. 留守 5: 全类匹配排名
print('\n=== 留守 5 全类匹配排名 ===')
for nm, (ea, _) in sorted(remaining.items()):
    disps = census_disps(ea)
    if not disps:
        report['remaining_' + nm] = {'ea': hex(ea), 'disps': 0, 'note': '零 disp'}
        print('%-24s 零 disp' % nm)
        continue
    # 每类命中数排名
    class_scores = []
    for off in disps:
        for c, _, _ in offset_index.get(off, set()):
            class_scores.append(c)
    scores = collections.Counter(class_scores)
    top3 = scores.most_common(3)
    result = {'ea': hex(ea), 'disp_n': len(disps), 'top3_classes': top3}
    report['remaining_' + nm] = result
    print('%-24s disp=%d top3=%s' % (nm, len(disps), top3))

json.dump(report, open(OUT, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('-> %s' % OUT)
idapro.close_database(False)
