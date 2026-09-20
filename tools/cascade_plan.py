#!/usr/bin/env python3
"""只读：为"改某类 binary_size"生成**精确编辑计划**（A 窄核的输入 ✓，本工具**绝不写盘**）。

计划内容（每条都可机械执行 ✓）：
  * 目标/族：`binary_size`、`base_size` 如何改
  * 持有者：哪些**成员 offset 键**要平移、平移多少（**按每类首个内嵌位置 P_min 分档** ✓）
  * 次序：**leaf→root**（深度大的先 ✓）
  * `0x` 归一 ✓（禁用 `int(k,0)` ✗）
用法：python3 tools/cascade_plan.py <Class> --new-size N [--json]
"""
import argparse, json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cascade_scan as cs


EV = ('A 级三重（2026-09-20/21）：??_L size=248 且 ctor=0x440740 ×3（sub_483280/sub_498820/sub_525120）；'
      'operator new(248)+call 0x440740（alloc_sizeof，exhibits 逐字节校验 28/28 OK）；'
      'ctor 0x440740 写入 0x56AD88 正是 UIStatic 自己声明的 vtable；成员位移上界 ≥200>152。'
      '配套改动由 tools/cascade_plan.py 生成（口径：每类首个内嵌位置 P_min 分档；族内用 ≥旧尺寸），'
      '独立复算裁定 1442 成员 offset / 60 个类。')


_DIM = __import__('re').compile(r'\[(\d+)\]')


def _elems_of(t):
    """成员的元素数：数组维度**连乘** ✓（`UIStatic[10]` ⇒ 10；`X[6][5]` ⇒ 30 ✓）。"""
    n = 1
    for d in _DIM.findall(t or ''):
        n *= int(d)
    return n


def _n(k):
    ks = str(k)
    if ks[:2].lower() == '0x':
        return int(ks, 16)
    if '_' in ks:
        ks = ks.split('_')[0]
    return int(ks, 10) if ks.isdigit() else None


def build_plan(target, new_size, structs):
    d = structs[target]
    old = d.get('binary_size')
    delta = new_size - old
    der = cs._descendants(target, structs)
    fam = [target] + der
    kids = cs._children_map(structs)
    depth = {}
    def dep(n, stack=()):
        if n in depth: return depth[n]
        if n in stack: return 0
        ps = [p for p, ks_ in kids.items() if n in ks_]
        depth[n] = 0 if not ps else 1 + max(dep(p, stack + (n,)) for p in ps)
        return depth[n]
    for c in structs: dep(c)
    # 按值/数组包含的传递闭包
    def bt(c, k):
        t = (structs[c].get('known_members') or {}).get(k, {})
        t = t.get('type') if isinstance(t, dict) else None
        if not isinstance(t, str): return None
        m = cs._ARR.match(t)
        return m.group(1) if m else t
    changed = set(fam); owners = set()
    while True:
        newc = {c for c in structs if c not in changed
                and any(bt(c, k) in changed for k in (structs[c].get('known_members') or {}))}
        if not newc: break
        owners |= newc; changed |= newc
    edits = []
    for c in sorted(changed, key=lambda x: (-depth.get(x, 0), x)):     # leaf→root ✓
        K = structs[c].get('known_members') or {}
        row = {'class': c, 'depth': depth.get(c, 0), 'role': None, 'ops': []}
        if c == target:
            row['role'] = 'target'
            row['ops'].append({'kind': 'set_size', 'class': None, 'size': new_size, 'from': old, 'to': new_size, 'evidence': EV})
        elif c in der:
            row['role'] = 'derived'
            bs = structs[c].get('base_size'); own = structs[c].get('binary_size')
            if isinstance(bs, int): row['ops'].append({'kind': 'set_base_size', 'class': None, 'from': bs, 'to': new_size, 'evidence': EV})
            if isinstance(own, int): row['ops'].append({'kind': 'set_size', 'class': None, 'size': own + delta, 'from': own, 'to': own + delta, 'evidence': EV})
            row['ops'] += [{'kind': 'shift_offset', 'key': k, 'from': _n(k), 'to': _n(k) + delta, 'evidence': EV}
                           for k in K if _n(k) is not None and _n(k) >= old]
        else:
            row['role'] = 'holder'
            sites = [_n(k) for k in K if bt(c, k) in changed and _n(k) is not None]
            if not sites: continue
            P = min(sites)
            # 【系统性修复 1】持有者内嵌了 k 个变大的对象 ⇒ **它自己也要增长 k×Δ** ✓
            # （漏这步 ⇒ 成员越过 binary_size ⇒ apply 取不到按值成员尺寸 ⇒ invalid member_size FATAL ✗）
            own = structs[c].get('binary_size')
            # **系统性修复 3**：必须用"**元素总数**"Σ dims ✓，不是"成员个数" ✗
            # （UIStatic[10] 尺寸会涨 10×Δ ✓ ⇒ 其后成员应移 10×Δ ✓，不是 1×Δ ✗）
            K2 = {k: (structs[c].get('known_members') or {}).get(k) for k in K}
            def _elem_count_at(off):
                tot = 0
                for k2, v2 in K2.items():
                    o2 = _n(k2)
                    if o2 is None or o2 >= off:
                        continue
                    t2 = (v2 or {}).get('type') if isinstance(v2, dict) else None
                    if isinstance(t2, str) and bt(c, k2) in changed:
                        tot += _elems_of(t2)
                return tot
            total_elems = sum(_elems_of((K2[k] or {}).get('type') or '')
                              for k in K if bt(c, k) in changed)
            if isinstance(own, int) and total_elems:
                grow = delta * total_elems          # Σ元素数 ✓
                row['ops'].append({'kind': 'set_size', 'class': c, 'size': own + grow,
                                   'from': own, 'to': own + grow, 'evidence': EV})
            # 第 k 个内嵌对象之后 ⇒ +delta*k（**平移量非常数** ✓，复核者实测分配 {0:591,96:249,…}）
            for k in K:
                o = _n(k)
                if o is None or o <= P: continue
                mult = _elem_count_at(o)            # **元素总数** ✓（不是成员个数 ✗）
                row['ops'].append({'kind': 'shift_offset', 'key': k, 'from': o,
                                   'to': o + delta * mult, 'mult': mult, 'evidence': EV})
        if row['ops']: edits.append(row)
    plan = {'target': target, 'old_size': old, 'new_size': new_size, 'delta': delta,
            'classes': len(changed), 'total_ops': sum(len(e['ops']) for e in edits),
            'leaf_to_root': [e['class'] for e in edits], 'edits': edits}
    # 【系统性修复 2】对自己产出的计划强制 E6 不变量 ✓
    # 逐类模拟"应用后"的 max(成员末端) 与 new binary_size ⇒ 违反则该计划**无效** ✗
    new_size_of = {}
    new_off = {}
    for e in edits:
        for o in e['ops']:
            if o['kind'] == 'set_size':
                new_size_of[e['class']] = o['to']
            elif o['kind'] == 'shift_offset':
                new_off[(e['class'], str(o['from']))] = o['to']
    viol = []
    for c in sorted(changed):
        K = structs[c].get('known_members') or {}
        bs = new_size_of.get(c, structs[c].get('binary_size'))
        if not isinstance(bs, int):
            continue
        def _size_of_type(t):
            if not isinstance(t, str):
                return 1
            m = cs._ARR.match(t)
            base, dims = (m.group(1), _elems_of(t)) if m else (t, 1)
            bs2 = new_size_of.get(base, (structs.get(base) or {}).get('binary_size'))
            return (bs2 * dims) if isinstance(bs2, int) else (1 * dims)
        ends = []
        for k in K:
            o = _n(k)
            if o is None:
                continue
            o2 = new_off.get((c, str(o)), o)
            v = (K[k] or {}).get('type') if isinstance(K[k], dict) else None
            ends.append(o2 + _size_of_type(v))       # **真实尺寸** ✓（含数组连乘 ✓）
        if ends and max(ends) > bs:
            viol.append({'class': c, 'binary_size': bs, 'member_end': max(ends)})
    plan['self_check'] = {'ok': not viol, 'violations': viol[:8], 'n_violations': len(viol)}
    return plan


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    known = {'--new-size', '--json'}
    unk = [a for a in argv if a.startswith('-') and a.split('=')[0] not in known]
    if unk:
        print('[cascade_plan] 未知开关 %r ⇒ 不执行任何操作' % unk); return 0
    ap = argparse.ArgumentParser()
    ap.add_argument('class_name'); ap.add_argument('--new-size', type=int, required=True)
    ap.add_argument('--json', action='store_true')
    a = ap.parse_args(argv)
    plan = build_plan(a.class_name, a.new_size, cs._load())
    if a.json:
        print(json.dumps(plan, ensure_ascii=False, indent=1)); return 0
    print('== 编辑计划: %s %s->%s (delta=%+d) ==' % (plan['target'], plan['old_size'], plan['new_size'], plan['delta']))
    print('  涉及类 %d · 总操作数 %d' % (plan['classes'], plan['total_ops']))
    print('  leaf→root 前 8: %s' % plan['leaf_to_root'][:8])
    for e in plan['edits'][:5]:
        print('   %-22s depth=%d role=%-8s ops=%d 例:%s' % (e['class'], e['depth'], e['role'], len(e['ops']), e['ops'][:1]))
    return 0


if __name__ == '__main__':
    sys.exit(main())
