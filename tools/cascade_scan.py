#!/usr/bin/env python3
"""只读：binary_size 级联扫描（Spike 阶段）。

范围（双路复核裁定，见 docs/specs/2026-09-20-cascade-tool-design.md §C）：
  * **SI①**：直接派生类 + 其尺寸是否 stale（基类改了而派生类未跟）⇒ 三态 mechanical/proposal/unresolved
  * **②按值成员**：哪些类**按值**持有目标类（非指针、非内联 dict）
  * **③数组元素**：`T name[N]` 形式的元素类型
  * **④union 平凡性（reverse）**：哪些 union 的**按值**变体是目标类；若该类有 ctor/dtor 形态方法 ⇒ landmine
**不做**：MI 推断 / overlap / --apply / 挂 check ✓
**绝不写盘**（JSON 只到 stdout ✓）；`-` 开头未知开关 ⇒ 拒绝执行 ✓。

用法：
    python3 tools/cascade_scan.py <Class> --new-size N [--json]
"""
import argparse
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
STRUCTS = os.path.join(ROOT, 'data', 'annotations', 'structs')
_ARR = re.compile(r'^([A-Za-z_]\w*)\s*\[')


def _load():
    out = {}
    for f in sorted(os.listdir(STRUCTS)) if os.path.isdir(STRUCTS) else []:
        if not f.endswith('.json'):
            continue
        try:
            d = json.load(open(os.path.join(STRUCTS, f), encoding='utf-8'))
        except Exception:
            continue
        out[d.get('name') or f[:-5]] = d
    return out


def _bases(d):
    """归一化 base_class：str | [str] | None（含 bases:[{name,offset}] 的 MI 形式）。"""
    b = d.get('base_class')
    names = []
    if isinstance(b, str):
        names = [b]
    elif isinstance(b, list):
        names = [x for x in b if isinstance(x, str)]
    mi = d.get('bases') or []
    mi_names = [x.get('name') for x in mi if isinstance(x, dict) and x.get('name')]
    return names, mi_names


def _children_map(structs):
    """父类 -> 直接子类列表（含 base_class 的 str/list 与 bases 的 name）。"""
    kids = {}
    for name, sd in structs.items():
        names, mi = _bases(sd)
        for b in set(names) | set(mi):
            kids.setdefault(b, []).append(name)
    return kids


def _descendants(target, structs):
    """**递归**后代（BFS）：只走真实的父子边，绝不扫全库。

    为什么必须递归（评审 e0ea83d9 查出的正确性 bug）：`UIStatic` 实为 5 个派生类 ——
    漏掉 `UIStaticEXA`（`base_class=[UIStaticEX]`）会让"只改 4 个直接派生"的落地仍被 apply 越界拒绝 ✗。
    """
    kids = _children_map(structs)
    out, seen, frontier = [], set(), list(kids.get(target, []))
    while frontier:
        n = frontier.pop(0)
        if n in seen:
            continue
        seen.add(n)
        out.append(n)
        frontier.extend(kids.get(n, []))
    return sorted(out)


def _ctor_dtor_methods(d):
    nm = d.get('name')
    hits = []
    for a, v in (d.get('methods') or {}).items():
        n = (v or {}).get('name') or ''
        if n == nm or n == '~' + nm:
            hits.append((a, n))
    return hits


def _shift_calibers(structs, target, old_size, derived, refs):
    """需平移的自有成员 —— 四种口径并列（供对齐用 ✓）。

    语义：基类/元素尺寸变化后，**落在变化区之后**的自有成员必须平移 ✓；之前的成员不动 ✓。
    因此"正确的口径"与"范围选择"强相关 ⇒ 把范围×判据全部列出，避免双方各说各话 ✗。
    """
    import re as _re
    def _n(k):
        ks = str(k)
        if ks.startswith('0x') or ks.startswith('0X'):
            return int(ks, 16)
        if '_' in ks:
            h = ks.split('_')[0]
            return int(h, 10) if _re.fullmatch(r'\d+', h) else None
        return int(ks, 10) if _re.fullmatch(r'\d+', ks) else None
    holders = {r['holder']: [] for r in refs}
    for r in refs:
        v = _n(r['offset'])
        if v is not None:
            holders[r['holder']].append(v)
    scope_self = {target} | set(derived)
    out = {'ge_old_size': 0, 'derived_only_ge_old_size': 0,
           'after_embedding': 0, 'unique_positions_ge_old_size': 0}
    seen_pos = set()
    for cls, d in structs.items():
        ms = [( _n(k), k) for k in (d.get('known_members') or {})]
        ms = [(o, k) for o, k in ms if o is not None]
        if cls in scope_self or cls in holders:
            out['ge_old_size'] += sum(1 for o, _ in ms if o >= old_size)
            for o, _ in ms:
                if o >= old_size:
                    seen_pos.add((cls, o))
        if cls in set(derived):
            out['derived_only_ge_old_size'] += sum(1 for o, _ in ms if o >= old_size)
        for p in holders.get(cls, []):
            out['after_embedding'] += sum(1 for o, _ in ms if o >= p)
    out['unique_positions_ge_old_size'] = len(seen_pos)
    return out


def scan(target, new_size, structs):
    d = structs.get(target)
    if d is None:
        return {'error': 'no such class: %s' % target}
    old_size = d.get('binary_size')
    delta = (new_size - old_size) if isinstance(old_size, int) and isinstance(new_size, int) else None

    # ① SI 派生（**递归**）
    derived = []
    for name in _descendants(target, structs):
        sd = structs[name]
        names, mi = _bases(sd)
        if True:
            base_size = sd.get('base_size')
            own = sd.get('binary_size')
            if len(names) + len(mi) > 1:
                # MI 护栏（评审 e0ea83d9）：只要声明了多个基类就降级 —— 原实现会因 base_size
                # 恰好等于某个基类尺寸而误报 mechanical ✗（10 个 MI 类今天纯属运气才是 proposal）
                state, why = 'unresolved_mi', '多基类声明（%d 个）⇒ 不自动推断' % (len(names) + len(mi))
            elif mi and target in mi:
                state, why = 'unresolved_mi', '多继承边（bases 偏移完整率低）⇒ 不自动推断'
            elif not isinstance(base_size, int):
                state, why = 'unresolved', '派生类未声明 base_size ⇒ 无法机械推导平移'
            elif base_size != old_size:
                state, why = 'proposal', '派生类 base_size(%s) 与基类旧尺寸(%s) 不一致 ⇒ 需人确认' % (base_size, old_size)
            elif isinstance(own, int) and delta is not None:
                state, why = 'mechanical', 'SI 且 base_size==旧基类尺寸 ⇒ 候选 new_size=%d（成员 offset 需 +%d）' % (own + delta, delta)
            else:
                state, why = 'unresolved', '派生类 binary_size 缺失'
            derived.append({'class': name, 'base_size': base_size, 'binary_size': own,
                            'state': state, 'why': why})
    # ②③ 直接引用（按值成员 / 数组元素）
    byvalue, arrays = [], []
    for holder, hd in structs.items():
        for off, m in (hd.get('known_members') or {}).items():
            if not isinstance(m, dict):
                continue
            t = m.get('type')
            if not isinstance(t, str):
                continue
            elems = 1
            mt = _ARR.match(t)
            if mt:
                for dim in re.findall(r'\[(\d+)\]', t):
                    elems *= int(dim)      # 元素连乘（评审 V2/E1：站点口径会低估 2–7× ✗）
            if mt and mt.group(1) == target:
                arrays.append({'holder': holder, 'offset': off, 'name': m.get('name'),
                               'type': t, 'elements': elems})
            elif t == target:
                byvalue.append({'holder': holder, 'offset': off, 'name': m.get('name'),
                                'elements': elems})
    # ④ union reverse（泛化 check_union_member_triviality：找"按值变体是目标类"的 union）
    unions = []
    for holder, hd in structs.items():
        for off, m in (hd.get('known_members') or {}).items():
            if not isinstance(m, dict):
                continue
            t = m.get('type')
            if not (isinstance(t, dict) and isinstance(t.get('union'), list)):
                continue
            for v in t['union']:
                if isinstance(v, dict) and v.get('type') == target:
                    unions.append({'holder': holder, 'offset': off, 'member': m.get('name'),
                                   'variant': v.get('name')})
    cdtor = _ctor_dtor_methods(d)
    return {
        'target': target, 'old_size': old_size, 'new_size': new_size, 'delta': delta,
        'derived_direct': derived,
        'byvalue_refs': byvalue,
        'array_refs': arrays,
        'union_byvalue_refs': unions,
        'target_ctor_dtor_methods': cdtor,
        'union_landmine': bool(unions) and bool(cdtor),
        'counts': {
            'derived': len(derived),
            'byvalue': len(byvalue), 'arrays': len(arrays), 'unions': len(unions),
            'sites': len(byvalue) + len(arrays),
            'holders': len({x['holder'] for x in byvalue} | {x['holder'] for x in arrays}),
            'elements': sum(x['elements'] for x in byvalue) + sum(x['elements'] for x in arrays),
            'bytes_if_delta': (sum(x['elements'] for x in byvalue) + sum(x['elements'] for x in arrays)) * (delta or 0),
        },
        # 刻意区分：扫描器**能估计**的影响面 vs **历史观测**（不得把历史数伪装成预测 ✗）
        'estimated_exposed_tus': None,
        # 需平移成员的**多口径并列**（评审 e0ea83d9 的 960 与我的 1750 不一致 ⇒ 把口径显式化 ✓）
        # 口径 = 范围 × 判据；全部只读、可复算 ✓
        'shift_candidates': _shift_calibers(structs, target, old_size,
                                            [x['class'] for x in derived],
                                            byvalue + arrays),
        'historical_observation': {
            'UIStatic': '152→248 曾致 76 单元 C2079（派生 UDT 布局过期 ⇒ apply 越界拒绝）',
            'tagRoleSlot': '加 ctor/dtor 曾致 208 单元 C2620（union 平凡性）',
        }.get(target),
    }


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    known = {'--new-size', '--json'}
    unk = [a for a in argv if a.startswith('-') and a.split('=')[0] not in known]
    if unk:
        print('[cascade_scan] 未知开关 %r ⇒ 不执行任何操作（防误触覆盖产物）' % unk)
        return 0
    ap = argparse.ArgumentParser()
    ap.add_argument('class_name')
    ap.add_argument('--new-size', type=int, required=True)
    ap.add_argument('--json', action='store_true', help='输出 JSON 到 stdout（本工具绝不写文件）')
    a = ap.parse_args(argv)
    if not os.path.isdir(STRUCTS):
        print('[ERROR] 缺注解目录: %s' % STRUCTS, file=sys.stderr)
        return 2
    rep = scan(a.class_name, a.new_size, _load())
    if a.json:
        print(json.dumps(rep, ensure_ascii=False, indent=1))
        return 0
    if rep.get('error'):
        print('[ERROR] %s' % rep['error'], file=sys.stderr)
        return 2
    print('== cascade scan: %s  %s -> %s (delta=%s) =='
          % (rep['target'], rep['old_size'], rep['new_size'], rep['delta']))
    print('① 直接派生类 %d：' % rep['counts']['derived'])
    for x in rep['derived_direct']:
        print('   %-22s base_size=%-6s size=%-6s %-16s %s'
              % (x['class'], x['base_size'], x['binary_size'], x['state'], x['why']))
    print('② 按值持有者 %d：%s' % (rep['counts']['byvalue'],
          ', '.join('%s@%s' % (x['holder'], x['offset']) for x in rep['byvalue_refs'][:8])))
    print('③ 数组元素引用 %d：%s' % (rep['counts']['arrays'],
          ', '.join('%s.%s(%s)' % (x['holder'], x['name'], x['type']) for x in rep['array_refs'][:6])))
    print('④ union 按值变体引用 %d：%s' % (rep['counts']['unions'],
          ', '.join('%s.%s[%s]' % (x['holder'], x['member'], x['variant']) for x in rep['union_byvalue_refs'][:6])))
    if rep['union_landmine']:
        print('   ⚠️ LANDMINE：目标类有 ctor/dtor 形态方法 %s ⇒ 破坏 union 平凡性（B34 成因 ✗）'
              % rep['target_ctor_dtor_methods'])
    sc = rep.get('shift_candidates') or {}
    if sc:
        print('   需平移成员（多口径并列，供对齐 ✓）: ge_old_size=%d · derived_only=%d · after_embedding=%d · unique_positions=%d'
              % (sc['ge_old_size'], sc['derived_only_ge_old_size'], sc['after_embedding'],
                 sc['unique_positions_ge_old_size']))
    if rep['historical_observation']:
        print('历史观测（非预测能力）：%s' % rep['historical_observation'])
    return 0


if __name__ == '__main__':
    sys.exit(main())
