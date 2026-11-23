"""fixture_proof — 金标链跑器（spec v2 §1·R8）。

链（控制器裁定·记账）：annotation → load_ann_dir → build_import_plan →
plan_to_facts（**机械投影**：仅搬运 plan op 字段，零语义）→ diff vs 手写 oracle。
oracle 独立性：expected/facts_oracle.json 人工写定（来源注 expected/README.md），
禁从 annotation 脚本派生（防循环论证）。
活体全链证明=verify_b_import（T4）；本件=计划级正确性锚。
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from import_annotation import build_import_plan, load_ann_dir  # noqa: E402  （链=被证对象）
from verify_core import diff_facts, norm_addr  # noqa: E402


def plan_to_facts(plan):
    """plan op → canonical facts（机械投影：只搬字段不作语义判断）。"""
    facts = {'functions': {}, 'structs': {}, 'globals': {}, 'skips': {}}
    for op in plan or []:
        k = op.get('kind')
        if k == '_meta':
            continue
        if k == 'set_name':
            e = facts['functions'].setdefault(norm_addr(op['addr']), {})
            e['name'] = op.get('name')
            if op.get('owner'):
                e['owner'] = op['owner']
        elif k == 'set_func_sig':
            e = facts['functions'].setdefault(norm_addr(op['addr']), {})
            ret = op.get('ret') or 'void'
            conv = op.get('conv') or ''
            params = op.get('params') or []
            e['signature'] = '%s %s(%s)' % (ret, conv, ', '.join(params))
            if op.get('cls'):
                e['class'] = op['cls']
        elif k == 'define_struct':
            facts['structs'][op['name']] = {
                'size': op.get('size'),
                'members': {int(m['offset']): {'name': m['name'], 'type': m['type']}
                            for m in (op.get('members') or [])}}
        elif k == 'define_union':
            # union 变体无偏移语义——键=声明序（README 记载；非偏移伪造）
            facts['structs'][op['name']] = {
                'size': op.get('size'),
                'members': {i: {'name': m['name'], 'type': m['type']}
                            for i, m in enumerate(op.get('members') or [])}}
        elif k == 'define_global':
            facts['globals'][norm_addr(op['addr'])] = {
                'name': op.get('name'), 'type': op.get('type')}
    return facts


def run_fixture(case_dir):
    """金标链：annotation → plan → facts vs 手写 oracle → 零差判定。"""
    ann = os.path.join(case_dir, 'annotations')
    funcs, structs, g = load_ann_dir(ann)
    plan = build_import_plan(functions=funcs, structs=structs, globals=g)
    actual = plan_to_facts(plan)
    expected = json.load(open(os.path.join(case_dir, 'expected', 'facts_oracle.json')))
    diffs = diff_facts(expected, actual)
    bad = diffs['missing'] or diffs['changed'] or diffs['extra'] or \
        any(not u.get('reason') for u in diffs['unverifiable'])
    return {'verdict': 'FAIL' if bad else 'PASS', 'diffs': diffs,
            'case': os.path.basename(case_dir)}
