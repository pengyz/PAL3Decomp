"""D7 戳剥离单源（review_mangled_migration_20261102）：4 处分叉正则收敛 strip_stamp()。"""

from pipeline.ida.vc6_mangler import strip_stamp


def test_hex_tail_stamp():
    assert strip_stamp('Destroy__ovl_03') == 'Destroy'
    assert strip_stamp('Destroy__ovl_ABCDEF12') == 'Destroy'


def test_g1_no_hex_form():
    assert strip_stamp('OnMessage_ovl') == 'OnMessage'


def test_bare_hex_tail():
    assert strip_stamp('Foo_ABC', mode='all') == 'Foo'


def test_inner_underscore_preserved():
    assert strip_stamp('Method_x__ovl_1') == 'Method_x'


def test_clean_name_untouched():
    assert strip_stamp('Update') == 'Update'
    assert strip_stamp('') == ''


def test_address_suffixed_names_kept_in_ovl_mode():
    """回归钉（2026-11-03）：地址戳名=身份，ovl 模式禁剥（曾致 18 假碰撞）。"""
    assert strip_stamp('crt_sub_00540D20') == 'crt_sub_00540D20'
    assert strip_stamp('SingletonThunk_00431DB0') == 'SingletonThunk_00431DB0'
    assert strip_stamp('Foo_ABC', mode='all') == 'Foo'
