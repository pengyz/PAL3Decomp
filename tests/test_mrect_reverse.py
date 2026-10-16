#!/usr/bin/env python3
"""[型名替换缺陷签名逆转 2026-10-16] reverse_mrect_typelie 单测（R15）。

机制：IDB m_rect@16 全库唯一属 UIWnd ⇒ Hex-Rays 型名替换把 `*((T**)X+4)`（X+16
指针槽读）渲染成 `X->m_rect.left`（N×4==16 数字巧合）⇒ 位等价但型谎言。
只动签名命中形（铸包裹/算术位）；真成员访问零触碰（禁全量逆转）。
"""
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO))
sys.path.insert(0, str(REPO / 'pipeline' / 'gen'))

from data import store  # noqa: E402,F401
import ast_transform as at  # noqa: E402


# ── 签名 1：指针铸包裹（值即刻指针化）──────────────────────────────
def test_sig1_simple_pointer_cast():
    out = at.reverse_mrect_typelie('v = (RoleSystem *)X->m_rect.left;')
    assert out == 'v = *((RoleSystem **)X + 4);', out


def test_sig1_field_n_mapping():
    assert at.reverse_mrect_typelie('p = (T *)X->m_rect.top;') == 'p = *((T **)X + 5);'
    assert at.reverse_mrect_typelie('p = (T *)X->m_rect.right;') == 'p = *((T **)X + 6);'
    assert at.reverse_mrect_typelie('p = (T *)X->m_rect.bottom;') == 'p = *((T **)X + 7);'


def test_sig1_fnptr_cast_access_only():
    # CGameData:266 病灶形：fnptr 铸包裹 ⇒ 访问本身逆转为整数槽读（外铸重解释）
    src = '((void ( *)(UIScene **, _DWORD, tagRECT *, CGameData *))(*p)->m_rect.left)(a, b);'
    out = at.reverse_mrect_typelie(src)
    assert '*((_DWORD *)(*p) + 4)' in out, out
    assert 'm_rect' not in out


# ── 签名 2：下标/乘除/地址算术位（无浮点铸前缀）────────────────────
def test_sig2_subscript_arithmetic():
    src = 'x = arr[9344 * this[28].E.m_rect.right + 148 + 584 * i];'
    out = at.reverse_mrect_typelie(src)
    assert 'this[28].E.m_rect.right' not in out, out
    assert '*((_DWORD *)this[28].E + 6)' in out, out


def test_sig2_address_of_in_arithmetic():
    # `&` 取址形进算术 ⇒ 槽址逆转；裸加的第二操作数**非签名形**不入（精确判据）
    src = 'b = *((_BYTE *)&X.m_rect.left + X.m_rect.right);'
    out = at.reverse_mrect_typelie(src)
    assert '&X.m_rect.left' not in out, out
    assert '((_DWORD *)X + 4)' in out, out
    assert 'X.m_rect.right' in out, out   # 裸加形不入签名（乘/除/下标才算）


# ── 真成员访问零触碰（禁全量逆转的关键负向锁）──────────────────────
def test_real_member_accesses_untouched():
    for src in ('top = (double)this->m_rect.top;',                        # 浮点铸
                'v = (float)this->m_rect.bottom - f;',                    # 浮点铸
                'this->m_rect.left = 0;',                                 # 赋值
                'if ( this->m_rect.right > 10 )',                         # 比较
                'SetRect(&this->m_rect);',                                # 传参
                'a = this->m_rect.left + this->m_rect.right;',            # 普通整数加（非签名形）
                'Flags, &i->m_rect.top);'):                               # 取址传参
        assert at.reverse_mrect_typelie(src) == src, src


if __name__ == '__main__':
    import pytest
    raise SystemExit(pytest.main([__file__, '-v']))


# ── [28 条定向应用] allowlist 逐站回归 ─────────────────────────────
def _load_allowlist():
    import json
    return json.load(open(REPO / 'data' / 'annotations' / 'mrect_allowlist.json'))['sites']


def test_allowlist_28_sites_each_applies():
    """28 条逐条：构造行锚定场景 ⇒ current→target 精确生效（定向应用回归锁）。"""
    sites = _load_allowlist()
    assert len(sites) == 28
    for e in sites:
        code = '// pad\n' * (e['line'] - 1) + '  ' + e['current'] + ';\n'
        out, applied, skipped = at.apply_mrect_allowlist(code, [e], unit_name=None)
        assert len(applied) == 1 and not skipped, (e['file'], e['line'])
        assert e['target'] in out and e['current'] not in out, e


def test_allowlist_line_anchor_and_dup_consume():
    # current 重复形（6 条）：行锚定各自命中、互不抢
    code = '  A = (T *)X->m_rect.left;\n  B = (T *)X->m_rect.left;\n'
    ents = [
        {'file': 'pal3/src/Foo.cpp', 'line': 1, 'current': '(T *)X->m_rect.left',
         'target': '*((T **)X + 4)'},
        {'file': 'pal3/src/Foo.cpp', 'line': 2, 'current': '(T *)X->m_rect.left',
         'target': '*((T **)X + 4)'},
    ]
    out, applied, skipped = at.apply_mrect_allowlist(code, ents)
    assert len(applied) == 2 and not skipped
    assert out.count('*((T **)X + 4)') == 2


def test_allowlist_unit_filter_and_real_untouched():
    # unit 过滤：他单元条目不入；真访问串零触碰
    ents = [{'file': 'pal3/src/UI/UIScene.cpp', 'line': 1,
             'current': '(T *)X->m_rect.left', 'target': '*((T **)X + 4)'}]
    code = '  a = this->m_rect.left;\n  b = (T *)X->m_rect.left;\n'
    out, applied, skipped = at.apply_mrect_allowlist(code, ents, unit_name='Other')
    assert not applied and code == out                      # 他单元不动
    out, applied, skipped = at.apply_mrect_allowlist(code, ents, unit_name='UIScene')
    assert len(applied) == 1 and 'this->m_rect.left' in out  # 真访问保持


# ── [F-CG 尾 5 项] 7 站 allowlist 回归 ─────────────────────────────
def test_fcg_tail_allowlist_7_sites():
    """7 站逐条（组 3/18/17/8/6）：行锚定 current→target 精确生效。"""
    import json
    sites = json.load(open(REPO / 'data' / 'annotations' /
                           'fcg_tail_allowlist.json'))['sites']
    assert len(sites) == 7
    for e in sites:
        code = '// pad\n' * (e['line'] - 1) + e['current'] + '\n'
        out, applied, skipped = at.apply_mrect_allowlist(code, [e])
        assert len(applied) == 1 and not skipped, (e['file'], e['line'])
        assert e['target'] in out and e['current'] not in out, e


def test_fcg_tail_entries_wellformed():
    """R13 预检（树无关化 2026-10-16）：7 站 entry 良构——生成树行锚定检查
    属 verify 步（树随 codegen 重生成漂移 ⇒ 单测保持树无关）。"""
    import json
    sites = json.load(open(REPO / 'data' / 'annotations' /
                           'fcg_tail_allowlist.json'))['sites']
    assert len(sites) == 7
    for e in sites:
        assert e['file'] and e['line'] > 0 and e['current'] and e['target'], e
        assert e['current'] != e['target']


# ── [sig-3 第三形 119 站] 定向应用回归 ─────────────────────────────
def test_sig3_allowlist_119_sites_each_applies():
    """119 站逐条：整行锚定 current→target 精确生效（G1 112 + G2 2 + G3 2 + G4 3）。"""
    import json
    sites = json.load(open(REPO / 'data' / 'annotations' / 'sig3_allowlist.json'))['sites']
    assert len(sites) == 119
    for e in sites:
        code = '// pad\n' * (e['line'] - 1) + e['current'] + '\n'
        out, applied, skipped = at.apply_mrect_allowlist(code, [e])
        assert len(applied) == 1 and not skipped, (e['file'], e['line'])
        assert e['target'] in out and e['current'] not in out, e


def test_sig3_embedded_receivers_keep_ampersand():
    """G3/G4 嵌入接收者 target 必带 &（防基址换成员值回归形）。"""
    import json
    sites = json.load(open(REPO / 'data' / 'annotations' / 'sig3_allowlist.json'))['sites']
    emb = [e for e in sites if 'm_3DObj' in e['base'] or 'm_ListGrid' in e['base']]
    assert len(emb) == 5   # G3 2 + G4 3
    for e in emb:
        assert '(&' in e['target'], e
        assert e['base'] not in e['target']


def test_sig3_pointer_receivers_no_ampersand_and_arith_untouched():
    """G1/G2 指针接收者不带 &；行内算术（+1116/4*i）保持不动。"""
    import json
    sites = json.load(open(REPO / 'data' / 'annotations' / 'sig3_allowlist.json'))['sites']
    ptr = [e for e in sites if e['base'] in ('this->m_rect.left',
                                             'this->m_pSkillWindow->m_rect.left')]
    assert len(ptr) == 114  # G1 112 + G2 2
    for e in ptr:
        assert '(&' not in e['target'].replace('(*(_DWORD *)', ''), e
        # 算术片段保持
        for frag in ('1116', '4 * ', '+ 112', '= BufferAt'):
            if frag in e['current']:
                assert frag in e['target'], (e['line'], frag)


# ── [A/C 族强转] 24 站回归 ─────────────────────────────────────────
def test_ac_family_allowlist_sites_apply():
    """24 站逐条：整行锚定 current→target 精确生效（C2679 消除形）。"""
    import json
    sites = json.load(open(REPO / 'data' / 'annotations' /
                           'ac_family_cast_allowlist.json'))['sites']
    assert len(sites) == 25  # 24 + verifier 补录 PAL3 L3195（31站修法余1站）
    for e in sites:
        code = '// pad\n' * (e['line'] - 1) + e['current'] + '\n'
        out, applied, skipped = at.apply_mrect_allowlist(code, [e])
        assert len(applied) == 1 and not skipped, (e['file'], e['line'])
        assert e['target'] in out and e['current'] not in out, e


def test_ac_family_bit_equivalence_forms():
    """强转形锁：((int *)X)[i] / *(_DWORD *)&X / (int)RHS —— 4B 位槽等价制式。"""
    import json
    sites = json.load(open(REPO / 'data' / 'annotations' /
                           'ac_family_cast_allowlist.json'))['sites']
    for e in sites:
        t = e['target']
        assert ('((int *)' in t or '*(_DWORD *)' in t or '(int)' in t), e
