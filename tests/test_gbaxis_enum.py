"""任务 4：`gbAxis` enum 声明（data/annotations/enums.json）。

机理（data/status/_attr_cards_20261009/N3_N4_finding.md）：Hex-Rays 在 IDB 已知
目标类型是 enum 时会自动补 cast；`gbAxis` 不在 enums.json ⇒ SetAxisAngle(2, …)
裸整型 ⇒ C2664。本测试锁住声明的**取值**与**命名合规**（禁伪语义名）。

两条绿路：
  python -m pytest --assert=plain tests/test_gbaxis_enum.py -v
  python3 tests/test_gbaxis_enum.py
"""
import json
import os

_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def test_gbaxis_declared():
    d = json.load(open('data/annotations/enums.json'))
    assert 'gbAxis' in d
    assert set(d['gbAxis']['values'].values()) == {'0','1','2'}


def test_no_pseudo_semantic_axis_names():
    d = json.load(open('data/annotations/enums.json'))
    names = set(d['gbAxis']['values'].keys())
    assert names == {'GB_AXIS_0', 'GB_AXIS_1', 'GB_AXIS_2'}   # 不得出现 X/Y/Z 之类伪语义名


def test_gbaxis_source_records_evidence_grade():
    """source 逐字锁死（简报「照抄，不要改值」）：证据分级 mangled 名 A 级 +
    值有二进制分支实证 + 重建源只作参考 + 常量名无证据。"""
    d = json.load(open('data/annotations/enums.json'))
    src = d['gbAxis']['source']
    assert src == (
        "mangled ?SetAxisAngle@gbMatrix4@@QAEXW4gbAxis@@M@Z 编码了 enum 类型(A级)；"
        "值 0/1/2 由目标 exe 分支常量实证；topo/src/gbMatrix4.cpp:366 仅作参考"
        "（重建源非二进制证据）；常量名无二进制证据故用中性名 GB_AXIS_0/1/2（禁伪语义命名）"
    )


if __name__ == '__main__':
    os.chdir(_ROOT)   # 独立 runner 可从任意 cwd 启动
    tests = [test_gbaxis_declared,
             test_no_pseudo_semantic_axis_names,
             test_gbaxis_source_records_evidence_grade]
    failed = 0
    for t in tests:
        try:
            t()
            print('PASS %s' % t.__name__)
        except AssertionError as e:
            failed += 1
            print('FAIL %s: %s' % (t.__name__, e))
        except Exception as e:
            failed += 1
            print('ERROR %s: %r' % (t.__name__, e))
    print('%d/%d passed' % (len(tests) - failed, len(tests)))
    raise SystemExit(1 if failed else 0)
