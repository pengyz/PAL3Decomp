#!/usr/bin/env python3
"""[外部 vtable 槽名表 2026-10-15] external 条目链恢复单测（R15，_VTBL_INDEX 注入夹具）。

病灶（L1 回退 1，实测 PalScriptWaitObj::ReleaseObject@0x4A68D0 尾部 gfxMgr 虚调用区
23 字节差）：_resolve_vtbl_name_chain 链首=注解 vtables[0].addr ⇒ 0032f2e35 移除
gbGfxManager 编造 vtable 址（0x10000）后链走 no_vtables_declaration ⇒ dispatch 从
具名成员调用（thiscall）降级原始 fn-ptr（cdecl）。
修法：槽序/槽名是真数据（methods[槽址].name，与 gbGfxManager.h:146 slot2=NewTexture
逐位一致）⇒ external 标记入索引 + idb_members 按槽序合成 ⇒ 链恢复具名渲染。
⚠️ vtable **地址**仍不认领（不回填 0x10000 族）。
"""
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen' / 'stages'))

from data import store  # noqa: E402,F401
import stage3_cleanup as s3  # noqa: E402


def _inject(index):
    saved = s3._VTBL_INDEX
    s3._VTBL_INDEX = index
    return saved


def test_external_slot_resolves_to_method_name():
    # gbGfxManager 形：external 键 + 槽序合成 + methods 名
    idx = {
        'class_addr': {'gbGfxManager': 'external:gbgfxmanager'},
        'by_addr': {'external:gbgfxmanager': {1: 'MsgProc', 2: 'NewTexture'}},
        'idb_members': {'external:gbgfxmanager': ['', 'MsgProc', 'NewTexture']},
        'class_slot_addrs': {'gbGfxManager': {1: '0x00010001', 2: '0x00010002'}},
        'class_decl': {'gbGfxManager': {'MsgProc': {'0x00010001'},
                                        'NewTexture': {'0x00010002'}}},
    }
    saved = _inject(idx)
    try:
        # 消费者实证形：byte_off=8 ⇒ slot2 ⇒ NewTexture（thiscall(gbGfxManager*,char*)）
        name, why = s3._resolve_vtbl_name_chain('gbGfxManager', 8)
        assert why is None, why
        assert name == 'NewTexture'
    finally:
        s3._VTBL_INDEX = saved


def test_external_no_declared_name_fail_closed():
    idx = {
        'class_addr': {'gbGfxManager': 'external:gbgfxmanager'},
        'by_addr': {'external:gbgfxmanager': {2: 'NewTexture'}},
        'idb_members': {'external:gbgfxmanager': ['', '', 'NewTexture']},
        'class_slot_addrs': {'gbGfxManager': {2: '0x00010002'}},
        'class_decl': {'gbGfxManager': {}},   # 名字未在本类声明 ⇒ 护栏必须拒
    }
    saved = _inject(idx)
    try:
        name, why = s3._resolve_vtbl_name_chain('gbGfxManager', 8)
        assert name is None and why == 'name_not_declared_for_class'
    finally:
        s3._VTBL_INDEX = saved


def test_external_marker_synthesis_in_loader():
    # 真 loader 路径：external 标记 ⇒ 唯一键 + idb_members 合成
    idx = s3._load_vtbl_index()
    ext = {k: v for k, v in idx['class_addr'].items() if str(v).startswith('external:')}
    assert 'gbGfxManager' in ext, ext
    key = ext['gbGfxManager']
    assert key in idx['idb_members'], 'external 条目须合成 idb_members'
    assert idx['idb_members'][key], '合成表非空'
    # ⚠️ 治理正确性：vtable 址仍不认领（合成键是索引键，非地址）
    assert key == 'external:gbgfxmanager'


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))
