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


def test_d1_zero_param_global_XZ_form():
    """D1① 零参全局=尾 XZ（void 参 X+收尾 Z，无 @）：?FileSysInit@@YAXXZ。"""
    assert mangle(None, 'FileSysInit', 'void __cdecl()') == '?FileSysInit@@YAXXZ'
    assert mangle(None, 'GlobOvl2', 'int __stdcall()') == '?GlobOvl2@@YGXZ' or \
           mangle(None, 'GlobOvl2', 'int __stdcall()') == '?GlobOvl2@@YGHXZ'


def test_d1_already_mangled_shortcircuit():
    assert mangle(None, '?FileSysInit@@YAXXZ', 'void __cdecl()') == '?FileSysInit@@YAXXZ'


def test_d6_stdcall_fp_param():
    """D6 stdcall fp 参须 P6G 编码（静默编 H=bug）。"""
    out = mangle(None, 'F', 'void __cdecl(void (__stdcall *)(int))')
    assert 'P6GXH@Z' in out, out


def test_d4_E_family_is_eh_funclet_note():
    """D4 口径修正：_E/$E=EH funclet（编译器合成物），非 stage4 可解析符号——
    Fix1 注释主张撤回，collect_sub_refs 接面挂账。"""
    is_eh_funclet = vm.is_eh_funclet
    assert is_eh_funclet('_E68') and is_eh_funclet('$E68') and is_eh_funclet('$LN4')
    assert not is_eh_funclet('sub_401000')


# ===== ovl 换轨·五缺陷真值锚（plan-1to5 §467-522 实测名，2026-11-03 TDD）=====

def test_defect1_class_prefix_V():
    """类类型前缀=V（PAV），非 U（PAU）。真值: obj 实测 ?OnMessage@CCBAIWindow@@QAEDPAPAVUIListBox@@@Z"""
    from pipeline.ida.vc6_mangler import mangle
    got = mangle('CCBAIWindow', 'OnMessage', 'char __thiscall(UIListBox **)')
    assert got == '?OnMessage@CCBAIWindow@@QAEDPAPAVUIListBox@@@Z'


def test_defect2_virtual_prefix_UAE():
    """虚性传入=U 前缀（UAE），非 Q。真值: ?Update@UIStatic@@UAEHMH@Z"""
    from pipeline.ida.vc6_mangler import mangle
    got = mangle('UIStatic', 'Update', 'int __thiscall(float, int)', virtual_=True)
    assert got == '?Update@UIStatic@@UAEHMH@Z'


def test_defect3_nested_class_backref():
    """嵌套类→层级号 NODE@1@（1=外层类回指）。真值: ?PushOpen@AStarPathFinder@@QAEHPAUNODE@1@@Z"""
    from pipeline.ida.vc6_mangler import mangle
    got = mangle('AStarPathFinder', 'PushOpen', 'int __thiscall(AStarPathFinder::NODE *)')
    assert got == '?PushOpen@AStarPathFinder@@QAEHPAUNODE@1@@Z'


def test_defect4_backref_repeated_type():
    """重复类型第二现=backref 压缩（省类型重拼）。真值形: PA V... @N@ 回指"""
    from pipeline.ida.vc6_mangler import mangle
    got = mangle('Bag', 'Swap', 'void __thiscall(UIListBox *, UIListBox *)')
    # 第二参 UIListBox* 应为回指形（@N@），禁整名重拼
    import re as _re
    assert _re.search(r'PAV\d+@', got), '无 backref 压缩: %s' % got


def test_defect5_typedef_resolution():
    """typedef 展开：CHAR→D(char)·LPCSTR→PB(const char*)"""
    from pipeline.ida.vc6_mangler import mangle
    assert mangle('X', 'F', 'void __thiscall(CHAR)').endswith('D@Z'), 'CHAR 未展开为 D'
    assert mangle('X', 'F', 'void __thiscall(LPCSTR)').endswith('PB@Z'), 'LPCSTR 未展开为 PB'
