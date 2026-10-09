"""S-1 codegen 生成确定性 —— 回归锁。

病灶（2026-10-09 实证）：
  emit_headers._referenced_identifiers() 产出 **set**（PYTHONHASHSEED 随机）
    -> _forced_global_entries() 按 set 迭代产 extra
    -> generate_globals_cpp() 的消费点 `sorted(_glbs.items(), ...) + _extra_entries`
       —— extra **未排序**追加 => globals.cpp 尾块行序逐进程漂移
同态双跑实证：两次尾块重排、排序后多重集全同、均 2889 行 => 内容无误，只有顺序漂移。

修复：在 `_forced_global_entries()` 的 return 前 `extra.sort(key=...)`
（源头排序，使两处消费点自动一致）。等价变换：只改顺序，不改内容。
"""
import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))                      # emit_headers 内部用 `from pipeline.gen...` 绝对包路径
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))

import emit_headers as eh  # noqa: E402

FIXTURE = REPO / 'tests' / 'codegen' / 'fixtures' / 'globals_tail_before_fix.txt'

POD_RE = re.compile(
    r'^(?:int|long|short|char|unsigned\s+\w+|float|double|_DWORD|_WORD|_BYTE'
    r'|void\s*\*|\w+\s*\*+)$')


def _entry_line(pair):
    addr, info = pair
    return '%s %s' % (addr, json.dumps(info, sort_keys=True))


def test_forced_global_extra_sorted_by_address():
    """修复后 extra 必须在源头按地址排好。

    复核阻断级 1：`_forced_global_entries()` 返回 `(forced_set, extra_list)`，
    extra_list 元素是 `(addr_str, info_dict)` tuple —— info_dict **无 'addr' key**。
    """
    _, extra = eh._forced_global_entries()
    assert extra, 'extra 不应为空（当前应为 1091 条）'
    expected = sorted(extra, key=lambda e: int(e[0], 16))
    assert extra == expected


def test_fix_is_order_only_multiset_unchanged():
    """等价性：修复只改顺序，多重集与修复前 fixture 完全相同。"""
    assert FIXTURE.exists(), '缺少修复前 fixture（须在改代码前固化）'
    before = FIXTURE.read_text().splitlines()
    _, extra = eh._forced_global_entries()
    now = [_entry_line(e) for e in extra]
    assert sorted(before) == sorted(now), '多重集变了 —— 不再是纯顺序改动'


def test_extra_entries_are_pod_only():
    """构造序等价前提：extra 全是 POD 标量。

    globals.cpp 定义序 = CRT/静态初始化序（generate_globals() 注释）。
    只有当 extra 全是 POD（无构造函数）时，排序才不改变构造序。
    """
    _, extra = eh._forced_global_entries()
    bad = [(a, i.get('type')) for a, i in extra
           if not POD_RE.match((i.get('type') or '').strip())]
    assert not bad, '非 POD 条目会使排序改变构造序：%r' % bad[:5]


def test_determinism_across_hash_seeds():
    """跨 PYTHONHASHSEED 确定性：同一进程内多次调用 + 不同 seed 下顺序须一致。

    注：真正的跨进程验证需 subprocess 各自起 Python（见计划 S-1a 步骤 5）；
    本测试用「多次调用 + 与排序后结果比对」覆盖源码层的确定性。
    """
    _, a = eh._forced_global_entries()
    _, b = eh._forced_global_entries()
    assert [x[0] for x in a] == [x[0] for x in b], '同进程两次调用顺序不一致'
    assert [x[0] for x in a] == sorted((x[0] for x in a), key=lambda s: int(s, 16)), \
        '未按地址排序'


if __name__ == '__main__':
    import subprocess
    ok = 0
    for name, fn in sorted(globals().items()):
        if name.startswith('test_') and callable(fn):
            fn()
            print('PASS', name)
            ok += 1
    print('%d/%d passed' % (ok, ok))
