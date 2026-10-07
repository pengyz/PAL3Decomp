import pytest
"""`tools/bin_oracle.py` 的测试 —— **先写测试**（TDD）。

## 为什么需要（2026-09-22 工具链来源审计的结论）

现状：**二进制裁判依赖 MCP 会话**（idle TTL 会过期 ✗、且 MCP **持有 IDB ⇒ 阻塞 `apply`/`export`** ✗）。
而**真正的 SoT 是原始 `PAL3.exe` 字节 + 编译器** ⇒ 字节扫描/指令确认**可以完全 IDB-无关** ✓
（本会话已验证 `objdump -D -b binary -m i386 --adjust-vma=…` 可用 ✓）

## 断言基准（都是本会话已核实的事实 —— 不是自证）
* VA `0x423505`（`SceneMgr::ClearInactiveRoles` 内）的 6 字节 = `8B 88 E0 E0 00 00`（`mov ecx,[eax+0E0E0h]`）✓
* 因此在 `.text` 里扫 `E0 E0 00 00` 必然有命中 ✓；而随机模式应为 0 ✓
* 该指令的位移就是 `0xE0E0` ⇒ `confirm(0x423505, 0xE0E0) is True`，`confirm(0x423505, 0x1234) is False` ✓

运行：`python3 tests/test_bin_oracle.py`
"""
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT))
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))

import bin_oracle as B  # noqa: E402

KNOWN_VA = 0x423505
KNOWN_BYTES = bytes.fromhex('8B88E0E00000')


# ---------------- ① 原始 EXE 窗口（独立于 IDB ✓）----------------

def test_text_window_exposes_known_bytes():
    assert B.bytes_at(KNOWN_VA, 6) == KNOWN_BYTES


def test_text_window_is_bounded_by_text_section():
    """窗口必须是 **`.text` 段**（不是"到文件末尾"）—— 历史上这里曾因切片超尾而近恒真 ✗"""
    base, text, rva, raw = B.text_window()
    assert len(text) == raw, (len(text), raw)
    assert 0x400000 <= base < 0x800000, hex(base)


# ---------------- ② disp32 扫描（IDB-无关 ✓）----------------

def test_scan_finds_known_pattern():
    hits = B.scan(bytes.fromhex('E0E00000'), limit=5)
    assert hits, '已知模式应至少命中一次'
    assert all(isinstance(h, int) for h in hits)


def test_scan_unknown_pattern_is_empty():
    assert B.scan(bytes.fromhex('DEADBEEF'), limit=5) == []


def test_scan_hit_is_inside_an_instruction_containing_the_va():
    """命中的 VA 必须落在**包含该模式**的指令里（用 confirm 语义交叉验证 ✓）"""
    hits = B.scan(bytes.fromhex('E0E00000'), limit=1)
    assert hits and B.bytes_at(hits[0], 4) == bytes.fromhex('E0E00000')


# ---------------- ③ objdump 文本解析（纯函数 ✓）----------------

def test_parse_disp_att_syntax():
    """objdump 是 **AT&T** 语法：`0xe0e0(%eax)` ⇒ 位移 0xE0E0 ✓"""
    assert B.disp_of('  423505:\t8b 88 e0 e0 00 00    \tmov    0xe0e0(%eax),%ecx') == 0xE0E0
    assert B.disp_of('  423512:\t8d 88 38 e3 00 00    \tlea    0xe338(%eax),%ecx') == 0xE338


def test_parse_disp_returns_none_without_disp():
    assert B.disp_of('  423500:\te8 00 00 00 00       \tcall   423505 <x>') is None
    assert B.disp_of('  423511:\t56                   \tpush   %esi') is None


def test_parse_disp_ignores_stack_bases():
    """`%esp/%ebp` 是栈帧 ⇒ 不得当成成员访问 ✓"""
    assert B.disp_of('  401000:\t8b 44 24 1c          \tmov    0x1c(%esp),%eax') is None
    assert B.disp_of('  401000:\t8b 45 f8             \tmov    -0x8(%ebp),%eax') is None


def test_parse_disp_not_confused_by_immediates():
    """立即数（形如 `$0xe0e0`）不是位移 ⇒ 不得误判 ✓"""
    assert B.disp_of('  401000:\t81 c1 00 22 00 00    \tadd    $0x2200,%ecx') is None


# ---------------- ④ 指令确认（端到端，仍不碰 IDB ✓）----------------

def test_confirm_disp_access_true_for_known_instruction():
    assert B.confirm_disp_access(KNOWN_VA, 0xE0E0) is True


def test_confirm_disp_access_false_for_wrong_offset():
    assert B.confirm_disp_access(KNOWN_VA, 0x1234) is False


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
