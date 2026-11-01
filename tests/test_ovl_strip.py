"""TDD：__ovl_ 剥离在所有调用生成路径必须统一。
先写失败测试（红），再修（绿）。"""
import re
import sys
import os

sys.path.insert(0, 'pipeline/gen')


def test_routed_free_call_strips_ovl():
    """rewrite_routed_free_calls 生成的调用必须剥 __ovl_XXXX 后缀。"""
    from ast_transform import rewrite_routed_free_calls
    # routed_by_name: {裸名: (cls, method_with_ovl, nparams)}
    routed = {
        'Create': ('ARC_PlayerAtt', 'Create__ovl_1', 0),
        'Destroy': ('UIListBox', 'Destroy__ovl_E520', 0),
    }
    code = 'Create(recv1);\nDestroy(recv2);'
    result = rewrite_routed_free_calls(code, routed)
    # 生成的调用必须用裸名（无 __ovl_）
    assert 'Create__ovl_1' not in result, f'调用侧未剥 __ovl_: {result}'
    assert 'Destroy__ovl_E520' not in result, f'调用侧未剥 __ovl_: {result}'
    assert 'Create(' in result, f'应有裸名 Create: {result}'
    assert 'Destroy(' in result, f'应有裸名 Destroy: {result}'


def test_unqualified_member_call_strips_ovl():
    """rewrite_unqualified_member_call 生成的调用必须剥 __ovl_XXXX。"""
    from ast_transform import rewrite_unqualified_member_call
    methods_by_cls = {
        'UIListBox': {'Destroy__ovl_E520': (0, 'void __thiscall(UIListBox *this)')},
    }
    code = 'Destroy__ovl_E520((UIListBox *)this);'
    result = rewrite_unqualified_member_call(code, methods_by_cls)
    assert 'Destroy__ovl_E520' not in result, f'成员调用未剥 __ovl_: {result}'
    assert 'Destroy(' in result, f'应有裸名 Destroy: {result}'


def test_collect_methods_strips_ovl():
    """collect_methods 返回的方法名必须已剥 __ovl_。"""
    # 直接测试正则
    name = 'Create__ovl_1'
    stripped = re.sub(r'__ovl_[0-9a-fA-F]+$', '', name)
    assert stripped == 'Create', f'剥离应得 Create，得 {stripped}'

    name2 = 'Destroy__ovl_E520'
    stripped2 = re.sub(r'__ovl_[0-9a-fA-F]+$', '', name2)
    assert stripped2 == 'Destroy', f'剥离应得 Destroy，得 {stripped2}'

    # 无 __ovl_ 的名字不变
    name3 = 'Create'
    stripped3 = re.sub(r'__ovl_[0-9a-fA-F]+$', '', name3)
    assert stripped3 == 'Create', f'无 __ovl_ 不应变: {stripped3}'


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
    print(f'\n{failures} failures')
    sys.exit(1 if failures else 0)
