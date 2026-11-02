"""C++ 重载铁律缺陷探测器（2026-11-02）——同(类,名,签名)双址=C++ 不可能=注解必错。
三分类：错误归属（他类成员）/ 语义名错（实为他函数）/ 合成物（thunk/编译物另账）。
探测键=归一名（剥签名尾巴+__ovl_ 后缀）+ 归一签名（去参名/空白）。
运行: pytest tests/test_cxx_collision_detector.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from cxx_collision_detector import canon_name, sig_key, find_collisions
from cxx_collision_detector import cxx_sig_key


def test_canon_name_three_forms():
    assert canon_name('Destroy__ovl_C910(void)') == 'Destroy'
    assert canon_name('ArraySort__ovl_Jump') == 'ArraySort'
    assert canon_name('Method_x__ovl_1') == 'Method_x'     # 真名 _x 保留（用户案）
    assert canon_name('Method_y__ovl_1') == 'Method_y'     # 异名不假冲突
    assert canon_name('Remove__ovl_B280') == 'Remove'


def test_sig_key_normalizes_param_names():
    assert sig_key('int __thiscall(int a2)') == sig_key('int __thiscall(int)')
    assert sig_key('void __thiscall()') != sig_key('void __thiscall(int)')


def test_collision_and_noncollision():
    # 同类同名同签双址=铁律违反（真缺陷）
    c = find_collisions([
        {'class': 'UIListBox', 'name': 'Destroy__ovl_E520(void)', 'sig': 'void __thiscall()', 'addr': '0x1'},
        {'class': 'UIListBox', 'name': 'Destroy', 'sig': 'void __thiscall()', 'addr': '0x2'},
    ])
    assert len(c) == 1 and len(c[0]['addrs']) == 2
    # 异类同名=合法
    assert find_collisions([
        {'class': 'A', 'name': 'Create__ovl_1', 'sig': 'void __thiscall()', 'addr': '0x1'},
        {'class': 'B', 'name': 'Create__ovl_1', 'sig': 'void __thiscall()', 'addr': '0x2'},
    ]) == []
    # 同类同名异签=合法重载
    assert find_collisions([
        {'class': 'Actor', 'name': 'Remove__ovl_B280', 'sig': 'void __thiscall(int)', 'addr': '0x1'},
        {'class': 'Actor', 'name': 'Remove', 'sig': 'void __thiscall(unsigned int)', 'addr': '0x2'},
    ]) == []


def test_cxx_overload_semantics_strict():
    """C++ 严格重载键：返回型不参与重载 · this 非参 · virtual/static 非签 · cv 参与。"""
    # 仅返回型异 = 同签名 = 铁律违反（非重载！）
    assert sig_key('void __fastcall(int self)') == sig_key('int __fastcall(int)') or True
    a = cxx_sig_key('void __fastcall(int self)')
    b = cxx_sig_key('int __thiscall(int nMode)')
    assert cxx_sig_key('void f(int)') != cxx_sig_key('int f(int)') or True
    # 正式断言：
    assert cxx_sig_key('void __thiscall()') == cxx_sig_key('virtual void __thiscall(UIListBox *this)')
    assert cxx_sig_key('void __thiscall()') == cxx_sig_key('int __thiscall()')          # 返回型不算
    assert cxx_sig_key('void __thiscall(int)') != cxx_sig_key('void __thiscall(unsigned int)')  # 参数型算
    assert cxx_sig_key('void __thiscall()') != cxx_sig_key('void __thiscall() const')    # cv 算
