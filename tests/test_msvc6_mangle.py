"""apply 期 mangled name 转换基建（TDD）——复用 vc6_mangler 单源（TOS 纪律：禁重建轮）；
缺口三件：全局形/apply 接线/冲突规则 mangled 化。注解保持可读名单源。
真值锚：IDA 实验实证（?Remove@Actor@@QAEXH@Z/I@Z demangle 核对）。
冲突裁定升级：mangled 形相等=冲突；int A::method(int) vs int A::method() 不冲突；
int A::method() vs int B::method() 不冲突。
运行: pytest tests/test_msvc6_mangle.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import importlib.util
_spec = importlib.util.spec_from_file_location('vc6_mangler', str(ROOT / 'pipeline/ida/vc6_mangler.py'))
vm = importlib.util.module_from_spec(_spec); _spec.loader.exec_module(vm)
mangle, parse_signature, mangled_conflict = vm.mangle, vm.parse_signature, vm.mangled_conflict


def test_member_thiscall_groundtruth():
    # IDA 实验真值（2026-11-02）
    assert mangle('Actor', 'Remove', 'void __thiscall(int)') == '?Remove@Actor@@QAEXH@Z'
    assert mangle('Actor', 'Remove', 'void __thiscall(unsigned int)') == '?Remove@Actor@@QAEXI@Z'


def test_global_cdecl_groundtruth():
    assert mangle(None, 'GlobOvl', 'void __cdecl(int)') == '?GlobOvl@@YAXH@Z'
    assert mangle(None, 'GlobOvl', 'void __cdecl(float)') == '?GlobOvl@@YAXM@Z'
    assert mangle(None, 'ArraySort', 'int __cdecl(int,int,int,int (*)(int,int))') == '?ArraySort@@YAHHHHP6AHHH@Z@Z'


def test_parse_signature():
    conv, ret, params = parse_signature('int __cdecl(const char *,const char *,char *)')
    assert conv == '__cdecl' and ret == 'int' and params == ['const char *', 'const char *', 'char *']


def test_conflict_by_mangled_not_name():
    a = mangle('A', 'method', 'int __thiscall(int)')
    b = mangle('A', 'method', 'int __thiscall()')
    c = mangle('B', 'method', 'int __thiscall()')
    assert mangled_conflict([a, b]) is False   # 同类同名异签名=重载不冲突
    assert mangled_conflict([b, c]) is False   # 异类同名不冲突
    assert mangled_conflict([b, b]) is True    # 同 mangled 双址=真冲突


def test_conflict_normalizes_ovl_suffix():
    """冲突裁定按清扫后名（__ovl_ 归一）：Destroy vs Destroy__ovl_E520 同签名=真冲突。"""
    a = mangle('UIListBox', 'Destroy', 'void __thiscall()')
    b = mangle('UIListBox', 'Destroy__ovl_E520', 'void __thiscall()')
    import re as _re
    strip = lambda n: _re.sub(r'__ovl_[0-9a-fA-F]+$', '', n)
    a2 = mangle('UIListBox', strip('Destroy'), 'void __thiscall()')
    b2 = mangle('UIListBox', strip('Destroy__ovl_E520'), 'void __thiscall()')
    assert mangled_conflict([a, b]) is False   # 现名不撞（后缀未清）
    assert mangled_conflict([a2, b2]) is True  # 清扫后名=真冲突必报
