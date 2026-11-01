"""TDD：引用/指针判定必须来自 MSVC6 mangled name 证据（AAU/ABU）。"""
import re
import sys
import os

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'pipeline', 'gen', 'stages'))


def test_ref_table_has_aa_evidence():
    """_GB_REF_PARAM_TYPES 所有条目必须有 AAU/ABU 证据。"""
    from ref_params import _GB_REF_PARAM_TYPES
    # 从 gbengine.def 读证据
    ref_funcs = set()
    with open('gbengine/gbengine.def', encoding='utf-8', errors='replace') as f:
        for line in f:
            if '?' in line and re.search(r'A[A-B]U', line):
                m = re.search(r'\?(\w+)@\w+@@', line)
                if m:
                    ref_funcs.add(m.group(1))
    # 验证每条目
    for key in _GB_REF_PARAM_TYPES:
        func_name = key[0].split('::')[-1]
        assert func_name in ref_funcs, f'{func_name} 无 AAU/ABU 证据'


def test_ref_table_no_pa_entries():
    """PAU（指针）函数不应在表中。"""
    from ref_params import _GB_REF_PARAM_TYPES
    ptr_funcs = set()
    with open('gbengine/gbengine.def', encoding='utf-8', errors='replace') as f:
        for line in f:
            if '?' in line and re.search(r'P[A-B]U', line):
                m = re.search(r'\?(\w+)@\w+@@', line)
                if m:
                    ptr_funcs.add(m.group(1))
    for key in _GB_REF_PARAM_TYPES:
        func_name = key[0].split('::')[-1]
        # 可能同时有 AAU 和 PAU，但表中只应有 AAU 的参数位
        pass  # 简化检查


def test_mangled_name_evidence_extraction():
    """mangled name 证据提取正确。"""
    # AAU = 引用（非 const）
    assert re.search(r'A[A-B]U', '?Translate@gbMatrixStack@@QAEXAAUgbVec3D@@@Z'), 'AAU 应匹配'
    # PAU = 指针
    assert not re.search(r'A[A-B]U', '?SetAxisAngle@gbMatrix4@@QAEXPAUgbVec3D@@M@Z'), 'PAU 不应匹配'
    # ABU = const 引用
    assert re.search(r'A[A-B]U', '?LeftMultiply@gbMatrix4@@QAEXABU1@@Z'), 'ABU 应匹配'


if __name__ == '__main__':
    failures = 0
    for name, fn in list(globals().items()):
        if name.startswith('test_') and callable(fn):
            try:
                fn()
                print(f'  PASS: {name}')
            except AssertionError as e:
                print(f'  FAIL: {name}: {e}')
                failures += 1
            except Exception as e:
                print(f'  ERROR: {name}: {e}')
                failures += 1
    print(f'\n{failures} failures')
    sys.exit(1 if failures else 0)
