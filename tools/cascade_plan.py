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


_ALIGN = {'double': 8, '__int64': 8, 'int64': 8, 'LONGLONG': 8, 'float': 4, 'int': 4,
          'unsigned int': 4, 'DWORD': 4, '_DWORD': 4, 'long': 4, 'short': 2, 'char': 1}


def _align_of(t):
    """成员对齐（用于**对齐不变量** ✓，复核 Q1-⑤/F）：标量查表 ✓；类取 4（保守 ✓）。"""
    if not isinstance(t, str):
        return 1
    base = __import__('re').sub(r'^(struct|class|union|enum)\s+', '', t.strip()).split('[')[0].strip()
    return _ALIGN.get(base, 4)


_SCALAR = {'char': 1, 'unsigned char': 1, '_BYTE': 1, 'BYTE': 1, 'bool': 1, 'short': 2,
           'unsigned short': 2, '_WORD': 2, 'WORD': 2, 'wchar_t': 2, 'int': 4, 'unsigned int': 4,
           'long': 4, 'unsigned long': 4, '_DWORD': 4, 'DWORD': 4, 'float': 4, 'double': 8,
           '__int64': 8, 'int64': 8}


def member_dims(t, mdict=None):
    """元素数 = `count` 字段（若有 ✓ 注入 #8）× 数组维度连乘 ✓。"""
    _b, _k, dims = parse_type(t)
    c = 1
    if isinstance(mdict, dict):
        try:
            c = int(mdict.get('count') or 1)
        except Exception:
            c = 1
    return dims * max(c, 1)


def parse_type(t):
    """共享类型解析器 ✓（复核 7f6a52cd Q1/Q5 要求）：返回 (base, kind, dims)。

    kind ∈ {'class','scalar','ptr','ref','inline','unknown'}；**指针/引用不参与增长** ✓；
    内联 dict（struct/union）**显式拒绝**而非静默跳过 ✓（复核者要求）。
    """
    if isinstance(t, dict):
        return None, 'inline', 1          # 内联 struct/union ⇒ 调用方须**拒绝** ✓（不静默 ✗）
    if not isinstance(t, str):
        return None, 'unknown', 1
    tt = __import__('re').sub(r'^(struct|class|union|enum)\s+', '', t.strip())
    dims = 1
    for d in _DIM.findall(tt):
        dims *= int(d)
    # `count` 字段（若成员带 count ⇒ 元素数 = count × 维度 ✓，注入测试 #8）
    if isinstance(t, str):
        pass
    if '&' in tt:
        return None, 'ref', dims
    if '*' in tt:
        return tt.split('*')[0].strip(), 'ptr', dims
    base = tt.split('[')[0].strip()
    if base in _SCALAR:
        return base, 'scalar', dims
    return base, 'class', dims


def build_plan(target, new_size, structs):
    d = structs[target]
    old = d.get('binary_size')
    delta = new_size - old

    def _bt(c, k):
        v = (structs[c].get('known_members') or {}).get(k)
        t = v.get('type') if isinstance(v, dict) else None
        base, kind, dims = parse_type(t)
        return (base if kind == 'class' else None), kind, dims, t

    # ① 族（目标 + 递归派生），并**记录直接基类**（用于 set_base_size 与 Δ 累加 ✓）
    der = cs._descendants(target, structs)
    fam = [target] + der
    kids = cs._children_map(structs)

    def direct_bases(c):
        b = structs[c].get('base_class')
        names = [b] if isinstance(b, str) else ([x for x in b if isinstance(x, str)] if isinstance(b, list) else [])
        names += [x.get('name') for x in (structs[c].get('bases') or []) if isinstance(x, dict) and x.get('name')]
        return [n for n in names if n in structs]

    # ② 包含 ∪ 继承的**合并图** + **环检测**（有环 ⇒ 拒绝 ✓，复核 Q2）
    def deps(c):
        out = set(direct_bases(c))
        for k in (structs[c].get('known_members') or {}):
            base, kind, _dims_, _t = _bt(c, k)
            if kind == 'class' and base in structs:
                out.add(base)
        return out
    # 环检测（DFS）
    WHITE, GREY, BLACK = 0, 1, 2
    color = {}
    cycle = []
    def dfs(c, stack):
        color[c] = GREY
        for nb in deps(c):
            if color.get(nb, WHITE) == GREY:
                cycle.append((nb, c)); return True
            if color.get(nb, WHITE) == WHITE and dfs(nb, stack + [nb]):
                return True
        color[c] = BLACK
        return False
    # **全库**跑环检测 ✓（此前只跑 fam ⇒ 注入的"持有者环 X⇄Y"漏检 ✗，注入测试 #10 实证 ✓）
    for c in sorted(structs):
        if color.get(c, WHITE) == WHITE and dfs(c, [c]):
            break
    if cycle:
        return {'error': '包含/继承图存在**环** ⇒ 拒绝生成计划 ✗（合法 C++ 必为 DAG）',
                'cycle': cycle[:3], 'target': target}

    # ③ 逐类 Δ （拓扑序：leaf→root ⇒ 依赖先算 ✓）
    # 先算"受影响集合"（族 ∪ 按值/数组包含的传递闭包 ∪ 持有者的派生类 ✓）
    changed = set(fam)
    while True:
        newc = set()
        for c in structs:
            if c in changed:
                continue
            for k in (structs[c].get('known_members') or {}):
                base, kind, _d, _t = _bt(c, k)
                if kind == 'class' and base in changed:
                    newc.add(c); break
        for c in list(newc):
            newc |= set(cs._descendants(c, structs))     # 持有者长大 ⇒ 其派生类也受影响 ✓
        if not newc:
            break
        changed |= newc
    changed |= {s2 for c in list(changed) for s2 in cs._descendants(c, structs)}

    order = []
    seen = set()
    def topo(c):
        if c in seen:
            return
        seen.add(c)
        for nb in sorted(deps(c)):
            if nb in structs:
                topo(nb)
        order.append(c)
    for c in sorted(changed):        # **全 changed 集合** ✓（此前只算族 ⇒ 持有者 Δ=None ✗）
        topo(c)
    delta_of = {target: delta}
    for c in order:
        if c == target:
            continue
        s = 0
        for b in direct_bases(c):
            if b in delta_of:
                s += delta_of[b]
        for k in (structs[c].get('known_members') or {}):
            base, kind, dims, _t = _bt(c, k)
            if kind == 'class' and base in delta_of:
                s += dims * delta_of[base]
        delta_of[c] = s

    depth = {}
    def dep(n, stack=()):
        if n in depth: return depth[n]
        if n in stack: return 0
        ps = [p for p, ks_ in kids.items() if n in ks_]
        depth[n] = 0 if not ps else 1 + max(dep(p, stack + (n,)) for p in ps)
        return depth[n]
    for c in structs: dep(c)

    # ⑤ 生成编辑（逐类型 Δ ✓；平移限 o ≥ base_size ✓；**拒绝**内联 dict / `_N` 重复 ✓）
    edits = []
    rejected = []
    # #7（注入）：同 base offset 的 `_N` 变体键会**重复计数** ✗（复核 Q1-⑦）⇒ 检出即拒绝 ✓
    _seen_base = {}
    for c in sorted(changed):
        for k in (structs[c].get('known_members') or {}):
            base_off = str(k).split('_')[0]
            if base_off in _seen_base and _seen_base[base_off] != str(k):
                rejected.append({'class': c, 'key': k, 'why': '同 base offset 的 `_N` 变体键（%s）⇒ 拒绝以免重复计数 ✗'
                                 % _seen_base[base_off]})
            else:
                _seen_base[base_off] = str(k)
    for c in sorted(changed, key=lambda x: (-dep(x,), x)):
        K = structs[c].get('known_members') or {}
        row = {'class': c, 'depth': dep(c), 'role': None, 'ops': []}
        if c == target:
            row['role'] = 'target'
            row['ops'].append({'kind': 'set_size', 'class': c, 'size': new_size,
                               'from': old, 'to': new_size, 'evidence': EV})
        elif c in der:
            row['role'] = 'derived'
            bs = structs[c].get('base_size'); own = structs[c].get('binary_size')
            db = direct_bases(c)
            # 复核 Q1-⑥b：base_size 应 = **直接基类的新尺寸** ✓（传递派生如 UIStaticEXA ⇒ UIStaticEX 的新尺寸 ✓）
            newbase = (structs[db[0]].get('binary_size', 0) + delta_of.get(db[0], 0)) if db else new_size
            if isinstance(bs, int):
                row['ops'].append({'kind': 'set_base_size', 'class': c, 'from': bs, 'to': newbase, 'evidence': EV})
            if isinstance(own, int):
                row['ops'].append({'kind': 'set_size', 'class': c, 'size': own + delta_of.get(c, 0),
                                   'from': own, 'to': own + delta_of.get(c, 0), 'evidence': EV})
            for k in K:
                o = _n(k)
                if o is None:
                    continue
                if o >= (bs if isinstance(bs, int) else 0):     # 平移限 o ≥ base_size ✓（不动 +0 的 __vftable ✓）
                    base, kind, dims, t = _bt(c, k)
                    if kind == 'inline':
                        rejected.append({'class': c, 'key': k, 'why': '内联 dict 成员 ⇒ 拒绝（不静默 ✗）'})
                        continue
                    row['ops'].append({'kind': 'shift_offset', 'key': k, 'from': o,
                                       'to': o + delta_of.get(db[0], 0) if db else o + delta_of.get(target, 0),
                                       'mult': None, 'evidence': EV})
        else:
            row['role'] = 'holder'
            # 内嵌成员（按值/数组，且其类型在 changed 内 ✓）
            emb = []
            for k in K:
                base, kind, dims, t = _bt(c, k)
                if kind == 'inline':
                    # #4（注入）：内联 union/struct 的**按值变体**若含 changed 类 ⇒ 必须**拒绝** ✓
                    # （此前只是跳过 ⇒ 影响面被静默漏掉 ✗）
                    _blob = __import__('json').dumps(t, ensure_ascii=False)
                    if any((('"%s"' % x) in _blob) or (': %s' % x) in _blob for x in changed):
                        rejected.append({'class': c, 'key': k,
                                         'why': '内联 dict 的按值变体含受影响类 ⇒ 拒绝（不静默 ✗）'})
                    continue
                o = _n(k)
                if o is None:
                    continue
                if kind == 'class' and base in changed:
                    emb.append((o, member_dims(t, (K[k] if isinstance(K[k], dict) else None)), base, t, k))
            if not emb:
                continue
            own = structs[c].get('binary_size')
            own_delta = sum(dims * delta_of.get(base, 0) for _o, dims, base, _t, _k in emb)
            if isinstance(own, int) and own_delta:
                row['ops'].append({'kind': 'set_size', 'class': c, 'size': own + own_delta,
                                   'from': own, 'to': own + own_delta, 'evidence': EV})
            for k in K:
                o = _n(k)
                if o is None:
                    continue
                # 平移 = Σ_{内嵌 e 满足 off_e + old_size(T_e) ≤ o} dims_e × Δ(T_e) ✓（复核 Q3 公式）
                shift = 0
                for (eo, edims, ebase, et, _ek) in emb:
                    oldsz = structs[ebase].get('binary_size')
                    if not isinstance(oldsz, int):
                        continue
                    if eo + oldsz * edims <= o:      # 内嵌对象**整体在它之前** ✓
                        shift += edims * delta_of.get(ebase, 0)
                if shift:
                    row['ops'].append({'kind': 'shift_offset', 'key': k, 'from': o, 'to': o + shift,
                                       'mult': shift // delta if delta else None, 'evidence': EV})
        if row['ops']:
            edits.append(row)

    plan = {'target': target, 'old_size': old, 'new_size': new_size, 'delta': delta,
            'classes': len(changed), 'total_ops': sum(len(e['ops']) for e in edits),
            'leaf_to_root': [e['class'] for e in edits], 'rejected': rejected[:8],
            'delta_of': {c: delta_of.get(c) for c in sorted(delta_of)}, 'edits': edits}

    # ⑥ 自检：**含真实尺寸**（数组×元素 ✓、类查 binary_size ✓、指针 4 ✓）
    def size_of(t, sizes):
        base, kind, dims = parse_type(t)
        if kind == 'ptr':
            return 4 * dims
        if kind in ('ref', 'inline', 'unknown'):
            return None
        if kind == 'scalar':
            return _SCALAR.get(base, 1) * dims
        bs2 = sizes.get(base)
        return bs2 * dims if isinstance(bs2, int) else None
    new_size_of, new_off = {}, {}
    for e in edits:
        for o in e['ops']:
            if o['kind'] == 'set_size':
                new_size_of[e['class']] = o['to']
            elif o['kind'] == 'shift_offset':
                new_off[(e['class'], str(o['from']))] = o['to']
    sizes_now = {c: structs[c].get('binary_size') for c in structs}
    sizes_new = dict(sizes_now); sizes_new.update(new_size_of)
    viol = []
    for c in sorted(changed):
        K = structs[c].get('known_members') or {}
        bs = sizes_new.get(c)
        if not isinstance(bs, int):
            continue
        ends = []
        for k in K:
            o = _n(k)
            if o is None:
                continue
            v = K[k] if isinstance(K[k], dict) else {}
            sz = size_of(v.get('type'), sizes_new)
            if sz is None:
                continue
            ends.append(new_off.get((c, str(o)), o) + sz)
        if ends and max(ends) > bs:
            viol.append({'class': c, 'binary_size': bs, 'member_end': max(ends)})
    # **对齐不变量** ✓（复核 Q1-⑤：`dims×Δ` 一般不足；Δ=+12 含 double 时工具原本零告警 ✗）
    misalign = []
    for c in sorted(changed):
        dd = delta_of.get(c)
        if not dd:
            continue
        for k in (structs[c].get('known_members') or {}):
            v = structs[c].get('known_members', {}).get(k)
            t = v.get('type') if isinstance(v, dict) else None
            al = _align_of(t)
            o = _n(k)
            if o is None:
                continue
            # **只报新引入的错位** ✓（既有 o 本就不对齐的不算 ✗ —— 否则 25 个类被误报 ✓）
            if dd % al != 0 or ((o % al == 0) and ((o + dd) % al != 0)):
                misalign.append({'class': c, 'key': k, 'align': al, 'delta': dd, 'offset': o})
                break
    plan['self_check'] = {'ok': (not viol) and (not misalign), 'violations': viol[:8],
                          'n_violations': len(viol), 'n_rejected': len(rejected),
                          'misalign': misalign[:5], 'n_misalign': len(misalign)}
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
