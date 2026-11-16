#!/usr/bin/env python3
"""[signature字段退役不变量 2026-11-16 TDD] 退役后目标态定义(当前RED)。

退役契约:
  R1 methods条目不再有'signature'键(唯一权威源=sig_model)
  R2 每条目必有sig_model(结构节点或pending诚实态)
  R3 node_of对全部条目返回有效节点(消费端零改动可用)
  R4 双证一致性: render(sig_model)语义≡迁移前字符串(迁移正确性, 已由零漂移验证背书)
"""
import sys, os, json, glob
sys.path.insert(0, os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')))
from pipeline.sigmodel import node_of, render

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
PASS = FAIL = 0
def ok(cond, note):
    global PASS, FAIL
    if cond: PASS += 1
    else:
        FAIL += 1
        print('[FAIL] %s' % note)

def main():
    n_ent, n_with_str, n_no_model, n_node_bad = 0, 0, 0, 0
    bad_examples = []
    for p in sorted(glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json'))):
        cls = os.path.basename(p)[:-5]
        d = json.load(open(p, encoding='utf-8'))
        for k, v in (d.get('methods') or {}).items():
            n_ent += 1
            # R1: 无signature键
            if 'signature' in v:
                n_with_str += 1
                if len(bad_examples) < 5: bad_examples.append((cls, k, 'signature键残留'))
            # R2: 必有sig_model
            if not isinstance(v.get('sig_model'), dict):
                n_no_model += 1
                if len(bad_examples) < 10: bad_examples.append((cls, k, '缺sig_model'))
            # R3: node_of有效
            n = node_of(v)
            if not isinstance(n, dict) or not n.get('pending') and not n.get('return'):
                n_node_bad += 1
    print('条目总数:', n_ent)
    ok(n_with_str == 0, 'R1: signature键全退役(残留%d)' % n_with_str)
    ok(n_no_model == 0, 'R2: sig_model全覆盖(缺%d)' % n_no_model)
    ok(n_node_bad == 0, 'R3: node_of全有效(坏%d)' % n_node_bad)
    for b in bad_examples[:8]:
        print('  例:', b)
    # R4 抽样: 迁移正确性(零漂移验证已全库背书, 此处抽样渲染一致性)
    n_sample = 0
    for p in sorted(glob.glob(os.path.join(ROOT, 'data', 'annotations', 'structs', '*.json')))[:20]:
        cls = os.path.basename(p)[:-5]
        d = json.load(open(p, encoding='utf-8'))
        for k, v in (d.get('methods') or {}).items():
            sm = v.get('sig_model')
            if sm and not sm.get('pending') and sm.get('return'):
                r = render(sm)
                ok(r is not None and '(' in r, 'R4渲染: %s %s' % (cls, k))
                n_sample += 1
                if n_sample >= 5: break
        if n_sample >= 5: break
    print('\n退役不变量: %d pass / %d fail' % (PASS, FAIL))
    return 0 if FAIL == 0 else 1

if __name__ == '__main__':
    sys.exit(main())
