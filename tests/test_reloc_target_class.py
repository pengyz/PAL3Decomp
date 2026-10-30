"""PlanB-T2a 重定位目标类别一致判定（纯计量新桶 class_ok）。
exp 缺名时双证分类：地址段语义 × 我方符号形 ⇒ 类别一致=class_ok（非 ok 非 mismatch）。
运行: pytest tests/test_reloc_target_class.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from gbengine_compare import classify_reloc_target, class_agree_bucket


def test_classify_crt_data_iat():
    assert classify_reloc_target(0x00541D10, '??3@YAXPAX@Z') == 'crt'
    assert classify_reloc_target(0x00BFC6F4, '?g_Input@@3VGRPinput@@A') == 'storage'
    assert classify_reloc_target(0x0056A1C0, '__imp__timeGetTime@0') == 'storage'
    assert classify_reloc_target(0x00450650, '_strncpy') == 'crt'


def test_imp_mangled_real_const_forms():
    """R2a-2 三形补判（28/60 假阳根因）：__imp_? mangled 导入 / __real@ 常量池。"""
    assert classify_reloc_target(0x0056A58C, '__imp_?Release@gbRefObject@@QAEXXZ') == 'storage'
    assert classify_reloc_target(0x0056AFA0, '__real@4@40008000000000000000') == 'storage'
    assert classify_reloc_target(0x00570110, '?g_nSkillItemIDTable@@3PAHA') == 'storage'


def test_class_agree_class_ok_and_mismatch():
    assert class_agree_bucket(0x005540F0, '_strncpy') == 'class_ok'
    assert class_agree_bucket(0x005540F0, '?g_Input@@3VGRPinput@@A') == 'class_mismatch'   # CRT 址+数据符
    assert class_agree_bucket(0x00450650, '?Fn@Cls@@AAEXXZ') == 'unresolved'          # 代码形不可判类
    # 大类格：storage 三形（iat/data/const）互认；rdata 含 IAT+常量池+const 全局（段界实测）
    assert class_agree_bucket(0x0056A58C, '__imp_?Release@gbRefObject@@QAEXXZ') == 'class_ok'
    assert class_agree_bucket(0x00570110, '?g_nSkillItemIDTable@@3PAHA') == 'class_ok'
    assert class_agree_bucket(0x0056AFA0, '__real@4@40008000000000000000') == 'class_ok' 


def test_self_local_and_autoname_fallback():
    """R2a-3：$L 局部标签自指向=独立桶；sub_ 自动名兜底（va_idx 缺自动名）。"""
    from gbengine_compare import is_self_local, fallback_autoname
    assert is_self_local(0x004CA9A0, 0x200, 0x004CAA5C) is True     # 函数界内目标
    assert is_self_local(0x004CA9A0, 0x200, 0x00519180) is False
    assert fallback_autoname(0x00519180) == 'sub_519180'


def test_dollar_L_prefix_is_self_local():
    """$L=MSVC 静态局部标签（工具链语义自证自局部，A 级）。"""
    from gbengine_compare import is_self_local_sym
    assert is_self_local_sym('$L81517') is True
    assert is_self_local_sym('?sub_519180@@YAHZZ') is False
