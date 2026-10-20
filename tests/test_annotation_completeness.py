"""R15 单测：tools/annotation_completeness.py（annotation 完整度/准确度指标）。

背景（2026-10-20 用户第一性论点）：**cast 是现象，不是原因**——应建
「数据标注完整度 + 准确率」指标，直接根治 annotation，cast 自然减少。
本工具度量「因」（annotation 质量）；编译错误数度量「果」。
"""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'tools'))

import annotation_completeness as A  # noqa: E402


# ---------------------------------------------------------------- 判据

def test_weak_type_covers_placeholders():
    for t in ('void *', '_BYTE', '_BYTE[16]', '_DWORD', 'unsigned long',
              'unsigned long *', 'int', 'int *', 'float *', 'char *',
              'char[8]', 'HWND', 'unsigned char'):
        assert A.is_weak_type(t), t


def test_strong_type_not_weak():
    for t in ('RoleAtt *', 'gbVec3D', 'UIWnd *', 'CCBStage',
              'tagRECT', 'unsigned long (__cdecl ***)(unsigned int)',
              'int (__stdcall *)(struct HWND__ *,unsigned int)'):
        assert not A.is_weak_type(t), t


def test_placeholder_name_detection():
    for n in ('_todo_074', 'm_nTodo_704', '_tail_25F', '_gap_000',
              '_unk_0004', '_field_0CE', 'byte_D8EBBC', 'dword_DD4E3C',
              'flt_D90060', 'off_56C548'):
        assert A.is_placeholder_name(n), n


def test_normal_name_not_placeholder():
    for n in ('m_pRoleState', 'g_RoleSlotBuf', 'MoveToAbsolute',
              'm_teamSlots', 'pDebugTex'):
        assert not A.is_placeholder_name(n), n


# ---------------------------------------------------------------- verdict 判定

def test_final_misattached_only():
    assert A.is_final_misattached('误挂（变量名）')
    assert not A.is_final_misattached('误挂待终审（mangled 零命中）')
    assert not A.is_final_misattached('认领（真类名）')


def test_pending_verdict():
    assert A.is_pending_verdict('误挂待终审（mangled 零命中）')
    assert not A.is_pending_verdict('误挂（变量名）')


def test_none_safe():
    assert not A.is_weak_type(None)
    assert not A.is_placeholder_name(None)
    assert not A.is_final_misattached(None)


# ---------------------------------------------------------------- 聚合

def test_collect_shape():
    res = A.collect()
    c = res['completeness']
    for k in ('weak_type_rate', 'placeholder_name_rate', 'signature_coverage',
              'weak_signature_rate', 'shell_class_rate', 'pending_verdict_rate'):
        assert k in c, k
        assert 0.0 <= c[k] <= 1.0, k


def test_collect_counts_consistent():
    res = A.collect()
    n = res['counts']
    assert n['weak_members'] <= n['members']
    assert n['shells'] <= n['classes']
    assert n['weak_signed'] <= n['signed']
    assert n['members'] > 1000, '应扫到上千成员（实测 9615）'


def test_ratchet_direction_semantics():
    """棘轮方向：弱型率越高越差；签名覆盖率越低越差。"""
    assert 'weak_type_rate' in A._HIGHER_IS_WORSE
    assert 'signature_coverage' in A._LOWER_IS_WORSE
