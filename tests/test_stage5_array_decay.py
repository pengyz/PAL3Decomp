#!/usr/bin/env python3
"""[#6 B 变体] stage5 `_path_is_pointer` 数组→指针退化分类单测（R15）。

病灶：`m_bRtVisible = this->m_bRtVisible;`（成员声明 `unsigned char[8]`）
      ⇒ `_path_is_pointer` 只判 `'*' in mt` ⇒ False ⇒ Family2 不补 cast
      ⇒ C2440 `char[8]` → `unsigned long *`（RoleStatePanel.cpp:777）。
修：末段成员为数组且调用点确认无下标 ⇒ True（C++ 数组→指针退化）。

运行：`python3 -m pytest tests/test_stage5_array_decay.py -q`。

"""
import importlib.util
import os
import sys
from pathlib import Path
from types import SimpleNamespace

REPO = Path(os.environ.get('PAL3_REPO', str(Path(__file__).resolve().parent.parent)))
S5_FILE = os.environ.get('S5_FILE', str(REPO / 'pipeline' / 'gen' / 'stages' / 'stage5_fixup.py'))
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))

_spec = importlib.util.spec_from_file_location('stage5_under_test', S5_FILE)
s5 = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(s5)

_TYPES = {
    ('RoleStatePanel', 'm_bRtVisible'): 'unsigned char [8]',
    ('RoleStatePanel', 'm_pPtr'): 'unsigned long *',
    ('RoleStatePanel', 'm_iFlag'): 'int',
}


def _ctx():
    return SimpleNamespace(cls_name='RoleStatePanel', method_name='OnMessage',
                           is_free_function=False)


def _vt():
    # LHS 本地变量声明：`unsigned long *m_bRtVisible;`
    return {'m_bRtVisible': {'kind': 'ptr', 'base': 'unsigned long', 'stars': 1}}


def _patch_member_type(monkeypatch):
    monkeypatch.setattr(s5, '_member_type', lambda c, m: _TYPES.get((c, m)))


def test_array_member_without_subscript_is_pointer(monkeypatch):
    _patch_member_type(monkeypatch)
    assert s5._path_is_pointer('this->m_bRtVisible', _vt(), _ctx(),
                               array_decays=True) is True


def test_array_member_with_subscript_is_element(monkeypatch):
    _patch_member_type(monkeypatch)
    assert s5._path_is_pointer('this->m_bRtVisible[2]', _vt(), _ctx(),
                               array_decays=False) is False


def test_pointer_member_unchanged(monkeypatch):
    _patch_member_type(monkeypatch)
    assert s5._path_is_pointer('this->m_pPtr', _vt(), _ctx(),
                               array_decays=True) is True


def test_scalar_member_unchanged(monkeypatch):
    _patch_member_type(monkeypatch)
    assert s5._path_is_pointer('this->m_iFlag', _vt(), _ctx(),
                               array_decays=True) is False


def test_family2_emits_cast_for_array_member(monkeypatch):
    _patch_member_type(monkeypatch)
    out = s5._fix_line_plain_var_assign(
        '    m_bRtVisible = this->m_bRtVisible;', _vt(), _ctx())
    assert out == '    m_bRtVisible = (unsigned long *)this->m_bRtVisible;', out


def test_family2_keeps_subscript_rhs(monkeypatch):
    _patch_member_type(monkeypatch)
    line = '    m_bRtVisible = this->m_bRtVisible[2];'
    assert s5._fix_line_plain_var_assign(line, _vt(), _ctx()) == line
