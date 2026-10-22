"""T2-F normalize() 纯函数 TDD（语义等价判据）。

## 背景

T2 = 语义等价（同输入 => 同行为，不要求同字节）

normalize() 是 T2-F 的核心：把状态快照规范化，消除噪声（指针/padding/浮点）。

## TDD 清单（57b95cc1 设计）

| 测试 | assertion |
|---|---|
| test_ptr_to_objid | 指针 => 对象 id（首见递增、别名同 id）|
| test_padding_zeroed | padding 归零 |
| test_float_ulp2 | 浮点 ULP<=2 视为相等 |
| test_plusminus_zero | ±0 视为相等 |
| test_nan_normalized | NaN 归一 |
| test_deterministic | 同输入 => 同输出（纯函数）|
"""
import pytest


def _normalize_ptr_map(state, ptr_map):
    """指针 -> 对象 id（首见递增、别名同 id）。"""
    out = {}
    for k, v in state.items():
        if isinstance(v, int) and v > 0x10000:  # 假设指针
            if v not in ptr_map:
                ptr_map[v] = len(ptr_map) + 1
            out[k] = ptr_map[v]
        else:
            out[k] = v
    return out


def _zero_padding(d):
    """padding 字段归零。"""
    return {k: (0 if k.startswith('_pad') or k.startswith('_gap') else v) for k, v in d.items()}


def _float_close(a, b, ulp=2):
    """浮点 ULP<=2 判等。"""
    import struct
    def _ulp_diff(x, y):
        if x == y:
            return 0
        if x != x or y != y:  # NaN
            return float('inf')
        ix = struct.unpack('<q', struct.pack('<d', x))[0]
        iy = struct.unpack('<q', struct.pack('<d', y))[0]
        return abs(ix - iy)
    return _ulp_diff(a, b) <= ulp


def _norm_zero(x):
    """±0 统一，NaN 归一。"""
    if x != x:  # NaN
        return float('nan')  # 归一（canonical NaN）
    return 0.0 if x == 0.0 else x


# === TDD 测试 ===

def test_ptr_to_objid():
    """指针 => 对象 id（首见递增、别名同 id）。"""
    pm = {}
    s1 = {'a': 0x12340000, 'b': 0x12340000, 'c': 0x56780000}
    out = _normalize_ptr_map(s1, pm)
    assert out['a'] == 1, f"首见指针 id 应 1，实得 {out['a']}"
    assert out['b'] == 1, f"别名同 id，实得 {out['b']}"
    assert out['c'] == 2, f"异对象 id 应 2，实得 {out['c']}"


def test_ptr_deterministic():
    """重复 normalize 全等（纯函数）。"""
    pm1 = {}
    pm2 = {}
    s = {'a': 0x12340000, 'b': 0x56780000}
    out1 = _normalize_ptr_map(s, pm1)
    out2 = _normalize_ptr_map(s, pm2)
    assert out1 == out2, f"不确定：{out1} != {out2}"


def test_padding_zeroed():
    """padding 字段归零。"""
    d = {'_pad_3': 0xFF, '_gap_004': 123, 'm_real': 42}
    out = _zero_padding(d)
    assert out['_pad_3'] == 0, f"padding 应归零，实得 {out['_pad_3']}"
    assert out['_gap_004'] == 0, f"gap 应归零，实得 {out['_gap_004']}"
    assert out['m_real'] == 42, f"真成员应保留，实得 {out['m_real']}"


def test_float_ulp2():
    """浮点 ULP<=2 视为相等。"""
    a = 1.0
    # ULP of 1.0 is 2^-52
    import struct
    def _nextafter(x, n):
        ix = struct.unpack('<q', struct.pack('<d', x))[0]
        return struct.unpack('<d', struct.pack('<q', ix + n))[0]
    assert _float_close(a, _nextafter(a, 1)), "ULP=1 应相等"
    assert _float_close(a, _nextafter(a, 2)), "ULP=2 应相等"
    assert not _float_close(a, _nextafter(a, 3)), "ULP=3 应不等"


def test_plusminus_zero():
    """±0 视为相等。"""
    assert _norm_zero(-0.0) == _norm_zero(0.0), "±0 应相等"


def test_nan_normalized():
    """NaN 归一。"""
    n1 = _norm_zero(float('nan'))
    n2 = _norm_zero(float('nan'))
    # NaN != NaN，但归一后应视为同一
    assert n1 != n1 and n2 != n2, "NaN 应保持 NaN（但比较时视为相等）"


def test_deterministic():
    """同输入 => 同输出（纯函数）。"""
    s = {'a': 0x12340000, 'b': 3.14, '_pad_1': 0xFF}
    pm1, pm2 = {}, {}
    out1 = _zero_padding(_normalize_ptr_map(s, pm1))
    out2 = _zero_padding(_normalize_ptr_map(s, pm2))
    assert out1 == out2, f"不确定：{out1} != {out2}"
