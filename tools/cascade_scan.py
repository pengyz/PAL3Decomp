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
    """需平移的成员 offset —— **语义正确口径**（独立复算 238b2ed8 裁定 ✓）+ 历史口径并列。

    正确判据（一句话）：**某成员 offset 要改 ⇔ 有"尺寸会变大的内嵌对象"整体位于它之前** ✓
    ⇒ 用**每类首个内嵌位置 P_min** 分档（`o > P_min` ✓），**不是**全局旧尺寸 ✗；
    P_min 处那个内嵌元素自身**不动** ✓，但其后**所有**成员（含后续元素声明 ✓）都要改 ✓。
    范围：**族（自身+递归派生）+ "按值/数组包含"的传递闭包** ✓（传递性正是 54 vs 60 的差 ✗）。

    并列保留历史口径（ge_old_size / 复核者的 960 口径），便于日后对齐 ✓。
    """
    def _n(k):
        ks = str(k)
        if ks[:2].lower() == '0x':
            return int(ks, 16)
        if '_' in ks:
            ks = ks.split('_')[0]
        return int(ks, 10) if ks.isdigit() else None

    def _base_type(cls, k):
        t = (structs[cls].get('known_members') or {}).get(k, {})
        t = t.get('type') if isinstance(t, dict) else None
        if not isinstance(t, str):
            return None
        m = _ARR.match(t)
        return m.group(1) if m else t

    fam = {target} | set(derived)
    # 按值/数组包含的**传递闭包**（谁（直接或间接）把族里的类按值装进去 ✓）
    changed = set(fam)
    owners = set()
    while True:
        newc = {c for c in structs if c not in changed
                and any(_base_type(c, k) in changed for k in (structs[c].get('known_members') or {}))}
        if not newc:
            break
        owners |= newc
        changed |= newc
    # 每类 P_min 分档（含族内与持有者 ✓）
    shift_keys = 0
    for c in sorted(changed):
        K = structs[c].get('known_members') or {}
        if c in fam:
            # 族内（目标 + 递归派生）：成员因**基类变大**而移动 ⇒ 判据是 offset ≥ 旧尺寸 ✓
            # （它们内部并不一定"内嵌"了族对象 ⇒ 不能用 P_min 分档 ✗ —— 这正是 1421 vs 1442 差的 21 ✓）
            shift_keys += sum(1 for k in K if (_n(k) is not None and _n(k) >= old_size))
            continue
        sites = [_n(k) for k in K if _base_type(c, k) in changed]
        sites = [x for x in sites if x is not None]
        if not sites:
            continue
        P = min(sites)
        shift_keys += sum(1 for k in K if (_n(k) is not None and _n(k) > P))
    # 历史口径（保持向后可比 ✓）
    ge_old = sum(1 for c in sorted(changed) for k in (structs[c].get('known_members') or {})
                 if (_n(k) is not None and _n(k) >= old_size))
    holders_direct = {r['holder'] for r in refs}
    r960 = 0
    for c in sorted(holders_direct):
        K = structs[c].get('known_members') or {}
        sites = [_n(k) for k in K if _base_type(c, k) == target and _n(k) is not None]
        if not sites:
            continue
        P = min(sites)
        r960 += sum(1 for k in K
                    if (_n(k) is not None and _n(k) >= P and _base_type(c, k) != target))
    derived_only = sum(1 for c in set(derived) for k in (structs[c].get('known_members') or {})
                       if (_n(k) is not None and _n(k) >= old_size))
    return {
        'shift_member_keys': shift_keys,        # **语义正确**（独立复算裁定 = 1442）✓
        'scope_classes': len(changed),          # 传递闭包后的类数（= 60）✓
        'r960_caliber': r960,                   # 复核者口径（排除元素、仅直接持有者）✓
        'ge_old_size': ge_old,                  # 我原口径（多算后续元素与 P 前成员）✗
        'derived_only_ge_old_size': derived_only,
    }


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
