"""__ovl_ 迁移防回流锁（2026-11-04 设计定案）——取代旧 test_ovl_strip2.py。

设计契约（用户裁定）：
  ① 戳归一**只**发生在 annotation 层（已全量剥除 17 处）；
  ② 管线（collect/emit）**不再有任何 __ovl_ 剥离**——戳名原样透传，撞名如实显形；
  ③ annotation 活数据（name/signature 字段）不得再出现 __ovl_/_ovl 戳名。

旧 test_ovl_strip2.py 测的是 emit_cpp 剥离正则的字面量行为（生产已删）= 断言死代码，
按「测试必须断言契约而非现状」纪律退役，由本锁取代。
背景：out/_adversarial_review_verdict.md #1/#2（对抗复核定谳）。
"""
import glob
import json
import re

STRIP_CONSUMER = re.compile(r'strip_ovl\s*\(|re\.sub\([^)]*__ovl_')
LIVE_NAME = re.compile(r'__ovl_[0-9a-fA-F]+$|_ovl$')


def test_pipeline_has_no_ovl_stripping():
    """pipeline/gen 各 stage 不得再调用 strip_ovl/持有 __ovl_ 剥离正则（防回流）。

    按行剥 `#` 注释后匹配——历史注释里的模式字样（如退役记录）不算回流。
    """
    offenders = []
    for f in glob.glob('pipeline/gen/**/*.py', recursive=True):
        if f.endswith('annotation_view.py'):
            continue          # strip_ovl 唯一定义处（工具保留，供审计/迁移用）
        text = open(f, encoding='utf-8').read()
        code_only = '\n'.join(line.split('#')[0] for line in text.splitlines())
        if STRIP_CONSUMER.search(code_only):
            offenders.append(f)
    assert not offenders, '管线又出现 __ovl_ 剥离副本（应下沉 annotation 层）: %s' % offenders


def test_annotations_carry_no_live_ovl_names():
    """annotation 活数据（name/signature）不得带 __ovl_/_ovl 戳名（source 历史注记除外）。"""
    stamped = []

    def _check(where, addr, field, v):
        head = v.split('(')[0]
        toks = head.split()
        tail = toks[-1] if toks else ''
        if tail and LIVE_NAME.search(tail):
            stamped.append((where, addr, field, v))

    for f in glob.glob('data/annotations/structs/*.json'):
        d = json.load(open(f, encoding='utf-8'))
        for addr, m in (d.get('methods') or {}).items():
            if isinstance(m, dict):
                for field in ('name', 'signature'):
                    _check(f, addr, field, str(m.get(field) or ''))
    fn = json.load(open('data/annotations/functions.json', encoding='utf-8'))
    for addr, m in fn.items():
        if isinstance(m, dict):
            _check('functions.json', addr, 'name', str(m.get('name') or ''))
    assert not stamped, 'annotation 活数据仍有戳名（应回落 _attr 迁移或裁决）: %s' % stamped[:5]


if __name__ == '__main__':
    test_pipeline_has_no_ovl_stripping()
    test_annotations_carry_no_live_ovl_names()
    print('OK: ovl 迁移防回流锁 2/2')
