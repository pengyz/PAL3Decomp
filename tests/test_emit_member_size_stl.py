"""`_estimate_member_size` 对 **STL/模板成员** 的尺寸 —— **先写测试**（TDD）。

## 背景（2026-09-22 实测，`UIListBox` 那次布局冲突的根因）

`emit_headers._estimate_member_size` 的兜底是 `return 4` ✗ ⇒ 注解里的 `std::vector<int>` 成员
被当成 4 字节，而真实 `sizeof(vector<int>) = **16**` ⇒
`UIListBox` 的 tail 被算到 0x4AC（实际 0x4B8）⇒ 类尺寸 1220 vs 注解 1208（**+12**）✗
更严重：`UIListBox` **被 26 个类按值内嵌** ⇒ 这个 +12 会**沿 DAG 传播** ✗✗

## 判据
用**本工具链实测**的尺寸（不是猜）：`vector/string=16` · `stack/queue/deque=48` · `list=12` · `map/set=4096`
（map/set 的 4096 是仓库 `pal3_stl.h` 的自定义 shim ⇒ 大但真实 ✓）

运行：`python3 tests/test_emit_member_size_stl.py`
"""
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT))                    # 模块内用 `from pipeline.gen...` ⇒ 需仓根 ✓
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline' / 'gen'))

from stages import emit_headers as E  # noqa: E402

# 实测（前三个由 tests 之外的探针测得，见提交信息）：
MEASURED = {
    'vector<int>': 16,
    'vector<unsigned int>': 16,
    'string': 16,
    'stack<int>': 48,
    'queue<int>': 48,
    'deque<int>': 48,
    'list<int>': 12,
    'map<int,int>': 4096,
    'set<int>': 4096,
}


def test_stl_sizes_match_measured_values():
    for t, want in MEASURED.items():
        got = E._estimate_member_size(t)
        assert got == want, '%s: 期望 %d（实测），实得 %s' % (t, want, got)


def test_stl_array_of_containers_multiplies():
    """`vector<int> arr[4]` ⇒ 4 × 16 = 64 ✓（数组分支必须先于类型分支 ✓）"""
    assert E._estimate_member_size('vector<int>[4]') == 64


def test_primitives_unchanged():
    """回归：基本类型不得被这次改动影响 ✓"""
    assert E._estimate_member_size('int') == 4
    assert E._estimate_member_size('unsigned char') == 1
    assert E._estimate_member_size('void *') == 4
    assert E._estimate_member_size('float') == 4


def test_pointer_to_container_is_still_4():
    """`vector<int> *` ⇒ **指针** 4 字节（不是容器 16 ✗）"""
    assert E._estimate_member_size('vector<int> *') == 4


if __name__ == '__main__':
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)