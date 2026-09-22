"""`verify_fix` 的**"注解 vs 二进制"门** 测试 —— **先写测试**（TDD）。

## 为什么（子 agent 对抗式复核的最危险发现，2026-09-22）

`verify_fix` 原有的基准是**注解**（`offsetof==注解偏移`、`sizeof==binary_size`）⇒
它只证明"**发射 == 注解**"，**不证明"注解 == 二进制"** ✗✗
⇒ 当注解本身错时（实例：`UITextArea.m_buf` 注解为 string@0x44，而二进制 `444FD4 movl $0x3f000000,0x44(%esi)`
写的是 **float 0.5** ✗；且 `mov %edi,0xbc(%esi)` ⇒ 对象 ≥0xBC 而注解 `binary_size=104` ✗✗）
它会把错误**认证为通过** ✗

## 三条判据（可机械执行；按"证据强度"分级，不把弱证据当证明 ✓）
* **R3（决定性）**：访问偏移 **≥ 注解 binary_size** ⇒ **矛盾 ✗**（对象根本没有那一段）
* **R1（决定性）**：向**非 float/double** 成员写 **float 立即数**（如 `$0x3f000000`=0.5）⇒ **矛盾 ✗**
* **R2（可疑，不判死）**：访问宽度 **> 成员注解尺寸** ⇒ `suspicious` ✓
  （⚠️ MSVC 会**合并相邻字节写** ⇒ 单凭宽度不能断死 ✓ —— 复核明确指出）
* **弱来源标注**：成员 `source` 为 `pdb_merge`/`gen_headers*`/纯 `annotation` ⇒ 标 `weak` ✓
  （仓规：PDB 不能单独作证据 ✓；`UITextArea` 两条正是此列 ✗）

运行：`python3 tests/test_verify_fix_anno_vs_bin.py`
"""
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT))
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))
sys.path.insert(0, str(PROJECT_ROOT / 'pipeline'))

import verify_fix as V  # noqa: E402


# ---------------- 访问解析（纯函数 ✓）----------------

def test_access_of_write_dword_to_member():
    a = V.access_of('  444f95:\t89 7e 50             \tmov    %edi,0x50(%esi)')
    assert a and a['disp'] == 0x50 and a['width'] == 4 and a['kind'] == 'write', a


def test_access_of_byte_write_and_read():
    a = V.access_of('  444f8f:\t88 46 48             \tmov    %al,0x48(%esi)')
    assert a and a['disp'] == 0x48 and a['width'] == 1, a
    b = V.access_of('  1000:\t8b 41 3c             \tmov    0x3c(%ecx),%eax')
    assert b and b['disp'] == 0x3c and b['width'] == 4 and b['kind'] == 'read', b


def test_access_of_float_immediate_write():
    a = V.access_of('  444fd4:\tc7 46 44 00 00 00 3f \tmovl   $0x3f000000,0x44(%esi)')
    assert a and a['disp'] == 0x44 and a['float_imm'] is True, a


def test_access_of_ignores_stack_and_no_disp():
    assert V.access_of('  401000:\t8b 44 24 1c          \tmov    0x1c(%esp),%eax') is None
    assert V.access_of('  401000:\t56                   \tpush   %esi') is None


# ---------------- 与注解的一致性（纯函数 ✓）----------------

def test_r3_access_beyond_binary_size_is_contradiction():
    """R3：访问 ≥ binary_size ⇒ 矛盾 ✗（最强判据 ✓）"""
    a = V.access_of('  444fc6:\t89 7e bc             \tmov    %edi,0xbc(%esi)')
    v, why = V.consistency('int', 4, 104, a)
    assert v == 'contradiction' and 'binary_size' in why, (v, why)


def test_r1_float_immediate_into_non_float_is_contradiction():
    """R1：向非 float 成员写 float 立即数 ⇒ 矛盾 ✗（正是 UITextArea 0x44 那条 ✓）"""
    a = V.access_of('  444fd4:\tc7 46 44 00 00 00 3f \tmovl   $0x3f000000,0x44(%esi)')
    v, why = V.consistency('std::basic_string<char>', 12, 0x200, a)
    assert v == 'contradiction' and 'float' in why, (v, why)


def test_r1_not_triggered_for_float_member():
    a = V.access_of('  444fd4:\tc7 46 44 00 00 00 3f \tmovl   $0x3f000000,0x44(%esi)')
    assert V.consistency('float', 4, 0x200, a)[0] == 'ok'


def test_r2_wider_than_member_is_suspicious_only():
    """R2：宽度 > 注解尺寸 ⇒ 只判 suspicious ✓（合并字节写的可能 ✗ 不能断死）"""
    a = V.access_of('  444f95:\t89 7e 50             \tmov    %edi,0x50(%esi)')
    v, why = V.consistency('BYTE', 1, 0x200, a)
    assert v == 'suspicious', (v, why)


def test_normal_access_is_ok():
    a = V.access_of('  444f95:\t89 7e 50             \tmov    %edi,0x50(%esi)')
    assert V.consistency('int', 4, 0x200, a)[0] == 'ok'


# ---------------- 弱来源标注（纯函数 ✓）----------------

def test_source_strength_labels_weak_sources():
    assert V.source_strength('pdb_merge') == 'weak'
    assert V.source_strength('gen_headers_9.2') == 'weak'
    assert V.source_strength('annotation') == 'weak'
    assert V.source_strength('binary:disasm@0x444F60') == 'binary'
    assert V.source_strength('binary layout: after m_ScriptRoleBuf') == 'binary'


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