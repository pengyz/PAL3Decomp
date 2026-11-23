#!/usr/bin/env python3
"""[地址级签名统一 2026-11-14] C2555 根治——家族槽位契约签名统一。

模型(用户质问修正): 签名长在地址上(methods条目=真值), 槽位sig字段撤销。
统一规则:
  - 家族 = from链连通分量(基 = 全槽from=None的类)
  - 每槽位收集族内全部成员函数签名(基桩+叶覆写), 归一化(剥this/参数名/virtual)
  - 基条目 pure('= 0'/pure字段) ⇒ 基sig=契约, 全叶服从
  - 否则 ⇒ 叶多数裁决(真实反编译体>基桩猜测), 基桩条目跟随
  - 统一sig写回: 基条目 + 叶覆写条目 (+槽位sig字段如存在, 保持一致)
v2铁律: 每类独立load/dump。
用法: python3 tools/unify_family_slot_sigs_20261114.py [--apply]
"""
import json, glob, os, re, sys, collections

S = 'data/annotations/structs/%s.json'
def norm(a):
    a = str(a)
    return '0x%08x' % int(a, 16) if a.lower().startswith('0x') else a
APPLY = '--apply' in sys.argv

def parse_sig(sig):
    """→ (ret, params_norm) 归一化: 剥virtual/this参/参数名"""
    s = str(sig or '').replace('virtual', ' ').replace('= 0', '').strip()
    m = re.match(r'^(.*?)\b(__thiscall|__cdecl|__stdcall|__fastcall)\s*\((.*)\)\s*$', s)
    if not m:
        m = re.match(r'^(.*?)\((.*)\)\s*$', s)
        if not m: return (str(sig).strip(), ())
        ret, cc, params = m.group(1).strip(), '', m.group(2)
    else:
        ret, cc, params = m.group(1).strip(), m.group(2), m.group(3)
    ret = re.sub(r'\s+', ' ', ret).strip()
    if not params.strip():
        return (ret, ())
    ps = []
    depth = 0; cur = ''
    for ch in params:
        if ch in '(<[': depth += 1
        if ch in ')>]': depth -= 1
        if ch == ',' and depth == 0:
            ps.append(cur); cur = ''
        else: cur += ch
    if cur.strip(): ps.append(cur)
    out = []
    for p0 in ps:
        p0 = p0.strip()
        if not p0: continue
        # 剥参数名: 尾部独立标识符(非数组/指针星号的一部分)
        p0 = re.sub(r'\s+\w+\s*$', '', p0).strip()
        # 剥纯this参(X *this / this)
        if re.match(r'^[\w:]+\s*\*\s*$', p0) or p0 == 'this':
            continue
        p0 = re.sub(r'\s+', ' ', p0)
        out.append(p0)
    return (ret, tuple(out))

def fmt_sig(ret, params, cc='__thiscall'):
    return '%s %s(%s)' % (ret, cc, ', '.join(params))

# 1) 收集: 类→(vtables, methods)
classes = [os.path.basename(f)[:-5] for f in glob.glob(S % '*')]
data = {c: json.load(open(S % c, encoding='utf-8')) for c in classes}

def _load_canonical():
    try:
        led = json.load(open('data/status/canonical_slot_names_20261114.json', encoding='utf-8'))
        return {int(k[4:]): v for k, v in led['slots'].items() if k[4:].isdigit()}
    except Exception:
        return {}

# 2) 家族连通分量: from链 + 槽addr共享
parent = {c: c for c in classes}
def find(c):
    while parent[c] != c: parent[c] = parent[parent[c]]; c = parent[c]
    return c
def union(a, b):
    ra, rb = find(a), find(b)
    if ra != rb: parent[ra] = rb
for cls in classes:
    d = data[cls]
    # [bases链 2026-11-14] 家族 = C++继承链(注解bases字段=发射的class X: public Y)
    # —— vtables from链≠继承链(C2555实证: scScriptInstance链漏统)
    for b in (d.get('bases') or []):
        bn = b.get('name') if isinstance(b, dict) else b
        if bn and bn in data: union(cls, bn)
fams = collections.defaultdict(list)
for c in classes: fams[find(c)].append(c)

# 3) 每族每槽位: 签名统一
changed = 0
for root, members in sorted(fams.items()):
    # 有vtables的成员(叶+基), 按槽位数分组
    vt_members = [c for c in members if data[c].get('vtables')]
    if not vt_members: continue
    nslots = max((len(vt.get('slots') or []) for c in vt_members for vt in (data[c].get('vtables') or [])), default=0)
    for si in range(nslots):
        entries = []   # (cls, addr, entry, is_base_stub)
        # [无表成员纳入 2026-11-14] 恢复旧态类(gbVisNode形)无vtables但methods里
        # 有家族槽位地址的实现条目 —— 按地址匹配纳入统一(否则旧sig泄漏C2555)
        _fam_addrs = set()
        for c2 in vt_members:
            d2 = data[c2]
            for vt2 in (d2.get('vtables') or []):
                for s2 in (vt2.get('slots') or []):
                    if s2.get('addr'): _fam_addrs.add(norm(s2['addr']))
        for c in vt_members:
            d = data[c]
            vts = d.get('vtables') or []
            if not vts:
                ms0 = d.get('methods') or {}
                for a in ms0.keys():
                    if norm(a) in _fam_addrs:
                        entries.append((c, norm(a), ms0[a]))
                continue
            slots = vts[0].get('slots') or []  # ★主表恒定(多表类的槽位映射bug修复)
            if si >= len(slots): continue
            a = norm(slots[si].get('addr') or '')
            m = (d.get('methods') or {}).get(a)
            if m: entries.append((c, a, m))
        if len(entries) < 1: continue
        # pure契约优先
        # [正名账锁定 2026-11-14] CEff族槽位契约 = canonical账sig(字节形态裁决)
        # —— restored成员的旧decomp猜测会污染多数派(slot10实证) → 账sig优先
        _canon = _load_canonical()
        _ck = _canon.get(si)
        if _ck and root == 'CEffObj':
            contract = parse_sig(_ck['sig'])
        elif pure:
            contract = parse_sig(pure[0][2].get('signature'))
        else:
            votes = collections.Counter()
            for c, a, m in entries:
                r, p = parse_sig(m.get('signature'))
                votes[(r, p)] += 1
            if len(votes) <= 1: continue
            # 叶真实体优先: 非void返回的多数派 > void多数派 > 任意
            nonvoid = [(k, v) for k, v in votes.items() if k[0] not in ('void', '')]
            pick = max(nonvoid or votes.items(), key=lambda x: x[1])[0]
            contract = pick
        # 写回全部成员
        for c, a, m in entries:
            cur = parse_sig(m.get('signature'))
            if cur == contract: continue
            old = m.get('signature')
            m['signature'] = fmt_sig(contract[0], contract[1])
            if not m.get('semantic_name') and m.get('name') and not m['name'].startswith('slot_'):
                m['semantic_name'] = m['name']
            changed += 1
            if c == root or True:
                pass
        # 槽位sig字段同步(存在的类)
        for c in vt_members:
            d = data[c]
            vts = d.get('vtables') or []
            if not vts: continue
            slots = vts[0].get('slots') or []
            if si < len(slots) and slots[si].get('sig'):
                slots[si]['sig'] = fmt_sig(contract[0], contract[1])
        _ = changed

print('签名统一改写: %d 条' % changed)
if APPLY:
    for c in set(list(fams.values())[0] if fams else []) | set(classes):
        pass
    for c in classes:
        json.dump(data[c], open(S % c, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    print('落盘完成')
else:
    print('[dry-run] 加 --apply')
