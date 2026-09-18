"""retn 立即数解析与证据包修复范围的回归测试。

背景（2026-09-18 定谳）：`tools/sig_evidence.py` 的 `RET_RE` 原先把 `h?` 写在
**捕获组之外**，于是 `retn 20h` 只捕获到 `20`、`h` 被吃掉，`parse_ret_num` 里
`rest.endswith('h')` 的十六进制分支成了**死代码** ⇒ 所有多位立即数按十进制解析：

    20h -> 20 (真值 32)  => slots 5 而非 8       （静默发布错 slots）
    10h -> 10 (真值 16)  => 非 4 的倍数 => B-ODDRET => 不发 slots => 门永久阻塞
    0Ch -> int('0C')     => ValueError，被 rets_of 的 except 吞成 C-DISASM-ERR

依据（A 级）：`original/PAL3.exe.asm` 里所有多位立即数都带 `h`，且"无 h 的多位数"
零条 —— 故凡是 >=10 的旧值，其源文本必然是某个 `NNh`。

本测试只断言解析/判定行为，不依赖仓库当前的 pack 或 annotation 状态。
"""
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / "tools"))

import sig_evidence as se  # noqa: E402


def _parse(text):
    m = se.RET_RE.match(text)
    return se.parse_ret_num(m.group(1)) if m else None


def test_hex_suffix_is_captured_and_parsed_as_hex():
    """h 必须在捕获组内，否则十六进制分支是死代码。"""
    assert _parse('retn 20h') == 32
    assert _parse('retn 10h') == 16
    assert _parse('retn 14h') == 20
    assert _parse('retn 18h') == 24
    assert _parse('retn 44h') == 68
    assert _parse('retn 0Ch') == 12      # 修前这里是 ValueError
    assert _parse('retn 1Ch') == 28
    assert _parse('ret 8') == 8


def test_single_digit_and_zero_are_unambiguous():
    for d in range(10):
        assert _parse('retn %d' % d) == d
    assert _parse('retn') == 0
    assert _parse('retn  8') == 8        # 多个空格
    assert _parse('mov eax, 1') is None
    assert _parse('retn 0x20') is None   # 0x 形态不是 IDA 清单的写法


def test_slots_derivation_matches_asm_truth():
    """4 的倍数才可能是 __thiscall 的栈字节数（retn N => N/4 个栈参）。"""
    for text, slots in (('retn 20h', 8), ('retn 10h', 4), ('retn 14h', 5),
                        ('retn 18h', 6), ('retn 0Ch', 3), ('retn 4', 1)):
        n = _parse(text)
        assert n % 4 == 0, text
        assert n // 4 == slots, (text, n, slots)


def test_provably_misparsed_scope_is_narrow():
    """修复范围必须只含**自证**解析错的条目。

    pack 里有 54 条 `A-V2` 是现行评分函数产不出的更高等级（由别的版本写入），
    对它做"顺手重评"会误伤 —— 实测那样会改动 54+ 条无关条目。
    """
    # 自证：非 4 倍数
    assert se.provably_misparsed({'grade': 'B-ODDRET', 'rets': [10]})
    # 自证：pack 里已记录 '0C' 的 ValueError 现场
    assert se.provably_misparsed({'grade': 'C-DISASM-ERR'})
    # 自证：>=10 且为 4 的倍数 => 通过了 %4 校验，静默发了错 slots
    assert se.provably_misparsed({'grade': 'B-SLOTMISMATCH', 'rets': [20]})
    assert se.provably_misparsed({'grade': 'B-SLOTMISMATCH', 'rets': [28, 28]})
    # 不是自证：正常值 / 更高等级 / 单值歧义
    assert not se.provably_misparsed({'grade': 'A', 'rets': [8]})
    assert not se.provably_misparsed({'grade': 'A-V2', 'rets': [0]})
    assert not se.provably_misparsed({'grade': 'SDK', 'slots': 1})
    assert not se.provably_misparsed({'grade': 'B-NORET', 'rets': []})
    assert not se.provably_misparsed({'grade': 'C-NOADDR'})


def test_grading_semantics_preserved():
    """"发布 retn 真值"是对的：B-SLOTMISMATCH 是"调用点在说谎"的信号。"""
    e = se.apply_rets_grading({'args': [9]}, [32, 32])
    assert e['slots'] == 8 and e['grade'] == 'B-SLOTMISMATCH', e
    e = se.apply_rets_grading({'args': [8]}, [32, 32])
    assert e['slots'] == 8 and e['grade'] == 'A', e      # 9 参调用点 - 1 = 8
    e = se.apply_rets_grading({'args': [3]}, [12])
    assert e['slots'] == 3 and e['grade'] == 'A', e
    e = se.apply_rets_grading({'args': [1, 2]}, [12])
    assert e['grade'] == 'B-ARGCONFLICT', e
    e = se.apply_rets_grading({'args': [2]}, [10])       # 真值非 4 倍数
    assert e['grade'] == 'B-ODDRET' and 'slots' not in e, e
    e = se.apply_rets_grading({'args': [2]}, [])
    assert e['grade'] == 'B-NORET' and 'slots' not in e, e
    e = se.apply_rets_grading({'args': [2]}, [8, 12])
    assert e['grade'] == 'B-MIXEDRET' and 'slots' not in e, e
    # 带旧 slots 的条目被降级时必须清掉 slots，否则门会读到陈旧值
    e = se.apply_rets_grading({'args': [2], 'slots': 7}, [10])
    assert 'slots' not in e and 'err' not in e, e
    # 旧的 err 必须清掉，否则 C-DISASM-ERR 的现场会留在已修好的条目上
    e = se.apply_rets_grading({'args': [3], 'err': "invalid literal"}, [12])
    assert 'err' not in e and e['slots'] == 3, e


if __name__ == "__main__":
    tests = [v for k, v in sorted(globals().items()) if k.startswith("test_")]
    failed = 0
    for t in tests:
        try:
            t()
            print("  ✅ %s" % t.__name__)
        except AssertionError as e:
            print("  ❌ %s: %s" % (t.__name__, e))
            failed += 1
        except Exception as e:
            print("  ⚠️  %s: %s" % (t.__name__, e))
            failed += 1
    print("\nResults: %d passed, %d failed" % (len(tests) - failed, failed))
    sys.exit(1 if failed else 0)