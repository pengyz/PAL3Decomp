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


def _ctor_dtor_methods(d):
    nm = d.get('name')
    hits = []
    for a, v in (d.get('methods') or {}).items():
        n = (v or {}).get('name') or ''
        if n == nm or n == '~' + nm:
            hits.append((a, n))
    return hits


def scan(target, new_size, structs):
    d = structs.get(target)
    if d is None:
        return {'error': 'no such class: %s' % target}
    old_size = d.get('binary_size')
    delta = (new_size - old_size) if isinstance(old_size, int) and isinstance(new_size, int) else None

    # ① SI 派生（直接）
    derived = []
    for name, sd in structs.items():
        names, mi = _bases(sd)
        if target in names or target in mi:
            base_size = sd.get('base_size')
            own = sd.get('binary_size')
            if mi and target in mi:
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
            mt = _ARR.match(t)
            if mt and mt.group(1) == target:
                arrays.append({'holder': holder, 'offset': off, 'name': m.get('name'), 'type': t})
            elif t == target:
                byvalue.append({'holder': holder, 'offset': off, 'name': m.get('name')})
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
        'counts': {'derived': len(derived), 'byvalue': len(byvalue),
                   'arrays': len(arrays), 'unions': len(unions)},
        # 刻意区分：扫描器**能估计**的影响面 vs **历史观测**（不得把历史数伪装成预测 ✗）
        'estimated_exposed_tus': None,
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
    if rep['historical_observation']:
        print('历史观测（非预测能力）：%s' % rep['historical_observation'])
    return 0


if __name__ == '__main__':
    sys.exit(main())
