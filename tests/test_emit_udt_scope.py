# R15：emit 命名 UDT 作用域提升——纯函数单测先行（2026-10-16 verifier）
# 病灶：tagCam.h `union _inline_tagCam_yaw {...} yaw;` 类内嵌套 ⇒ CCCTData.cpp
# 局部声明 `union _inline_tagCam_yaw *p_yaw`（TU 全局作用域）解析失败 ⇒ C2228×15。
# 修法：命名 UDT 定义提升到命名空间作用域（布局不变等价变换）。
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))

from data import store  # noqa: E402,F401
from stages.emit_headers import named_udt_scope_form  # noqa: E402


def test_hoist_tagcam_yaw_union():
    ns, member = named_udt_scope_form(
        type_name='_inline_tagCam_yaw', kind='union', member_name='yaw',
        body_lines=['    float f; // +0xC', '    CEffMgr * p; // +0xC'])
    assert ns[0] == 'union _inline_tagCam_yaw {'
    assert ns[-1] == '};'
    assert 'float f;' in ns[1]
    assert member == 'union _inline_tagCam_yaw yaw;'


def test_hoist_nested_struct_muidialog():
    ns, member = named_udt_scope_form(
        type_name='_inline_MUIDialog_m_btRc', kind='struct', member_name='m_btRc',
        body_lines=['    tagRECT rc;'])
    assert ns[0] == 'struct _inline_MUIDialog_m_btRc {'
    assert member == 'struct _inline_MUIDialog_m_btRc m_btRc;'


def test_unnamed_stays_none():
    ns, member = named_udt_scope_form(
        type_name='MUIDialog::$123', kind='struct', member_name='x', body_lines=['    int a;'])
    assert ns is None and member is None


def test_non_inline_name_rejected():
    ns, member = named_udt_scope_form(
        type_name='gbChain1D', kind='struct', member_name='children', body_lines=['    int a;'])
    assert ns is None and member is None


def test_hoist_udt_block_glue():
    """胶合：类内命名 UDT 块文本 ⇒ (命名空间 decl, 成员行)（布局不变等价变换）。"""
    from stages.emit_headers import hoist_udt_block
    block = [
        '    union _inline_tagCam_yaw { // +0xC',
        '        float f; // +0xC',
        '        CEffMgr * p; // +0xC',
        '    } yaw;',
    ]
    ns, member = hoist_udt_block(block, 'yaw')
    assert ns[0] == '#pragma pack(push,1)'
    assert ns[1] == 'union _inline_tagCam_yaw {'
    assert '    float f; // +0xC' in ns[2]
    assert ns[-1] == '#pragma pack(pop)'
    assert member == '    union _inline_tagCam_yaw yaw;'


def test_hoist_udt_block_unnamed_passthrough():
    from stages.emit_headers import hoist_udt_block
    block = ['    union { // +0x0', '        int a;', '    } x;']
    ns, member = hoist_udt_block(block, 'x')
    assert ns is None and member is None


def test_hoist_self_ref_needs_forward_decl():
    """自引用 body（成员含本类指针）⇒ ns decl 前出 `class <cls>;` 前向声明。"""
    from stages.emit_headers import hoist_udt_block
    block = [
        '    union _inline_PalScript_m_RoleSlotArray { // +0x18C',
        '        PalScript * m_pCurrentScript; // +0x354',
        '    } m_RoleSlotArray;',
    ]
    ns, member = hoist_udt_block(block, 'm_RoleSlotArray', cls_name='PalScript')
    assert ns[0] == '#pragma pack(push,1)'
    assert ns[1] == 'class PalScript;'
    assert ns[2] == 'union _inline_PalScript_m_RoleSlotArray {'
    assert member == '    union _inline_PalScript_m_RoleSlotArray m_RoleSlotArray;'
