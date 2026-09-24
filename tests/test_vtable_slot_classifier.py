"""`tools/vtable_slot_classifier.py` 的测试 —— **先写测试**（TDD，红→绿）。

本文件是 vtable **合成槽分类器**（槽内容 → kind）的金样本回归集。所有 expected 均为
真机 MSVC 6.0 SP0（cl 12.00.8168，`tools/wine_cl.sh`）编译 + **原始指令字节**反汇编
（objdump/ndisasm，**禁止 decomp JSON**）实测，逐条对齐两个金样本 README：

* `_vtable_abi_probe_20260925/README.md`
  #2 覆写次基本体（fn）· #4 本体内 vbtable 读（fn，反例）· #3 静态 adjustor thunk
  （`?ff@D3@@W7AEHXZ`）· #5 动态 vbase adjustor（`?o@D@@$4...` 形态）·
  #6 纯虚（`__purecall` 外部符号）· #7 虚析构（`??_G` + `??_E` 弱别名同址，签名 `void*(unsigned)`）
* `_vtable_attack_cases_20260925/README.md`
  B-1 混合槽 `??_ED@@$4PPPPPPPM@BA@AEPAXI@Z`（composite 金样本）——
  `sub ecx,[ecx-4]; sub ecx,0x10; jmp` = 动态 vbase 调整 × 常量 delta × deleting dtor

夹具全部为**反汇编工具的逐字输出**（空白规整），复现命令见各夹具注释；本任务用同样命令
在真机重新编译 vt2.cpp / vt3.cpp / q2a.cpp / c2.cpp 并重新提取，逐字与 README 一致。

运行：`python3 tests/test_vtable_slot_classifier.py` 或 `pytest tests/test_vtable_slot_classifier.py`
"""
import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))

from vtable_slot_classifier import (  # noqa: E402
    ALL_KINDS,
    KIND_ADJUSTOR_STATIC,
    KIND_ADJUSTOR_VBASE,
    KIND_COMPOSITE,
    KIND_DELETING_DTOR,
    KIND_FN,
    KIND_PURECALL,
    FEATURE_ADJUSTOR_STATIC,
    FEATURE_ADJUSTOR_VBASE,
    FEATURE_DELETING_DTOR,
    FEATURE_PURECALL,
    SlotEvidence,
    classify_slot,
    is_deleting_dtor_signature,
    normalize_kind,
    normalize_signature,
    parse_disasm,
    slot_order_kind,
)


# ================= 金样本夹具（真机实测反汇编，逐字） =================

# abi README #2 —— `?h@D@@UAEHXZ` 本体（vt2.obj: objdump -d）：
# 覆写次基虚函数**不生成 thunk**，本体按 D 布局直接取成员 ⇒ 普通函数
FN_H_AT_D = """
  0:  8b 41 08              mov    0x8(%ecx),%eax
  3:  c3                    ret
"""

# abi README #4 —— `?v@DV@@UAEHXZ` 本体（vt2.obj: objdump -d）：
# 本体内读 vbtable 相对成员（`mov -0x4(%ecx),%eax`），但**没有尾 jmp** ⇒ 不是 adjustor
FN_V_AT_DV = """
  0:  8b 41 fc              mov    -0x4(%ecx),%eax
  3:  c3                    ret
"""

# abi README #7 —— scalar deleting dtor `??_GV@@UAEPAXI@Z`（c2.obj 同族，46 字节全本体，
# 从 COMDAT 原始字节 `55 8b ec 51 89 4d fc ...` objdump -D -b binary -m i386）：
# 与 `??_EV@@UAEPAXI@Z`（`??_E` vector deleting，弱别名）**共享地址**
DTOR_GV = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  51                    push   %ecx
  4:  89 4d fc              mov    %ecx,-0x4(%ebp)
  7:  8b 4d fc              mov    -0x4(%ebp),%ecx
  a:  e8 00 00 00 00        call   0xf
  f:  8b 45 08              mov    0x8(%ebp),%eax
 12:  83 e0 01              and    $0x1,%eax
 15:  85 c0                 test   %eax,%eax
 17:  74 0c                 je     0x25
 19:  8b 4d fc              mov    -0x4(%ebp),%ecx
 1c:  51                    push   %ecx
 1d:  e8 00 00 00 00        call   0x22
 22:  83 c4 04              add    $0x4,%esp
 25:  8b 45 fc              mov    -0x4(%ebp),%eax
 28:  8b e5                 mov    %ebp,%esp
 2a:  5d                    pop    %ebp
 2b:  c2 04 00              ret    $0x4
"""

# abi README #3 —— 静态 adjustor thunk `?ff@D3@@W7AEHXZ`（vt3.obj: objdump -D）：
# `add/sub imm; jmp` 且**仅 ecx 操作数**（实测字节 `83 e9 08 e9 00 00 00 00`）
ADJ_STATIC_FF = """
  0:  83 e9 08              sub    $0x8,%ecx
  3:  e9 00 00 00 00        jmp    0x8
"""

# abi README #5 —— 动态 vbase adjustor `?o@D@@$4PPPPPPPM@A@AEXXZ`（c2.obj: objdump -D）：
# `sub -N(%ecx),%ecx; jmp`（delta 运行期取自 vbtable 相对位置）
ADJ_VBASE_O = """
  0:  2b 49 fc              sub    -0x4(%ecx),%ecx
  3:  e9 00 00 00 00        jmp    0x8
"""

# 同上 thunk 的 ndisasm（Intel 语法）逐字输出 —— 钉死"两种反汇编语法同结论"
ADJ_VBASE_O_NDISASM = """
00000000  2B49FC            sub ecx,[ecx-0x4]
00000003  E900000000        jmp 0x8
"""

# 同上 thunk 的 IDA 语法逐字形态（attack README B-1 即以 Intel 形态记录 `sub ecx, [ecx-4]`）
ADJ_VBASE_O_IDA = """
sub     ecx, [ecx-4]
jmp     loc_body
"""

# attack B-1 —— 混合槽 `??_ED@@$4PPPPPPPM@BA@AEPAXI@Z`（c2.obj: objdump -D，11 字节全本体）：
# `sub ecx,[ecx-4]`（动态 vbase）+ `sub ecx,0x10`（常量 delta）+ 尾 jmp
COMPOSITE_ED = """
  0:  2b 49 fc              sub    -0x4(%ecx),%ecx
  3:  83 e9 10              sub    $0x10,%ecx
  6:  e9 00 00 00 00        jmp    0xb
"""

# abi README #6 —— q2a.obj vtable 实测（tools/coff_vtable.py）：
#   ??_7Q2@@6B@  [0] __purecall  [1] ?r@Q2@@UAEHXZ
# 纯虚槽指向 **__purecall 外部符号**（CRT stub），无本体可反汇编
PURECALL_EXTERNAL = '__purecall'


def E(symbols=(), signature='', instructions=(), is_external=False, external_symbol='', addr=''):
    return SlotEvidence(symbols=tuple(symbols), signature=signature,
                        instructions=instructions, is_external=is_external,
                        external_symbol=external_symbol, addr=addr)


# ================= 1. fn（默认：普通函数） =================

def test_fn_plain_virtual_body_is_default_kind():
    """abi #2 `?h@D@@UAEHXZ`（vt2 实测）：普通本体 ⇒ kind=fn，零特征"""
    res = classify_slot(E(instructions=FN_H_AT_D))
    assert res.kind == KIND_FN, res
    assert res.features == frozenset(), res.features


def test_fn_vbtable_read_in_body_is_not_an_adjustor():
    """abi #4 `?v@DV@@UAEHXZ`：本体内 `mov -0x4(%ecx),%eax`（vbtable 相对读）**不是**
    adjustor —— adjustor 判据必须是"调整链 + 尾 jmp"整形态，不能只看内存操作数形态"""
    res = classify_slot(E(instructions=FN_V_AT_DV))
    assert res.kind == KIND_FN, res
    assert res.features == frozenset(), res.features


# ================= 2. deleting_dtor（与 ??_G 共享地址 + 签名 void*(unsigned)） =================

def test_deleting_dtor_shared_addr_and_signature():
    """abi #7 `??_GV@@UAEPAXI@Z`：同址 `??_G`/`??_E` 弱别名 + 签名 `void*(unsigned)` ⇒ deleting_dtor"""
    ev = E(symbols=('??_GV@@UAEPAXI@Z', '??_EV@@UAEPAXI@Z'),
           signature='void*(unsigned)', instructions=DTOR_GV)
    res = classify_slot(ev)
    assert res.kind == KIND_DELETING_DTOR, res
    assert res.features == frozenset({FEATURE_DELETING_DTOR}), res.features


def test_deleting_dtor_signature_text_variants_all_match():
    """签名文本形式（IDA/声明写法，含**显式 this** 形）归一后都判 `void*(unsigned)`；
    形近的非删除器签名必须判否"""
    for sig in ('void*(unsigned)', 'void * (unsigned int)', 'void * __thiscall(unsigned)',
                'void*(unsigned int __formal)', 'void * (__thiscall D::*)(unsigned int)',
                'void *(__thiscall void *this, unsigned int flags)'):
        assert is_deleting_dtor_signature(sig) is True, (sig, normalize_signature(sig))
    assert normalize_signature('void * (__thiscall D::*)(unsigned int)') == 'void*(unsigned)'
    assert normalize_signature('void *(__thiscall void *this, unsigned int flags)') == \
        'void*(void*,unsigned)'
    for sig in ('void()', 'void*(int)', 'int*(unsigned)', 'void*(void*)', ''):
        assert is_deleting_dtor_signature(sig) is False, (sig, normalize_signature(sig))


def test_deleting_dtor_symbol_without_signature_is_unconfirmed_but_hit():
    """`??_G` 共享地址但签名证据缺失 ⇒ 仍判 deleting_dtor（符号即删除器本体），但**必须**留
    "未确认"痕迹——真实二进制里 IDA 类型常缺失，签名缺失时不能回落成 fn（静默误判）"""
    ev = E(symbols=('??_GV@@UAEPAXI@Z', '??_EV@@UAEPAXI@Z'), instructions=DTOR_GV)
    res = classify_slot(ev)
    assert res.kind == KIND_DELETING_DTOR, res
    assert any('未确认' in n for n in res.notes), res.notes


def test_deleting_dtor_symbol_with_contradicting_signature_is_rejected():
    """同址 `??_E` 但签名 `void()` ⇒ **矛盾**，不得判 deleting_dtor（默认 fn + 矛盾痕迹）"""
    ev = E(symbols=('??_EV@@UAEPAXI@Z',), signature='void()', instructions=DTOR_GV)
    res = classify_slot(ev)
    assert res.kind == KIND_FN, res
    assert any('矛盾' in n for n in res.notes), res.notes


def test_deleting_dtor_shape_inferred_without_symbols():
    """**扩展判据（需上层认可）**：真实二进制 531 名仅 4 条 mangled ⇒ `??_G`/`??_E` 名可能不在；
    此时以二进制形态（`and r,1` + `test` + 条件跳过释放块 + 2 个 call）+ 签名 `void*(unsigned)`
    推断 deleting_dtor，并留"形态推断"痕迹（不能回落成 fn）"""
    ev = E(signature='void*(unsigned)', instructions=DTOR_GV)
    res = classify_slot(ev)
    assert res.kind == KIND_DELETING_DTOR, res
    assert any('形态推断' in n for n in res.notes), res.notes


def test_shape_inference_requires_deleting_dtor_skeleton():
    """反例：签名 `void*(unsigned)` 但本体没有 `flags&1` 释放骨架（只有 1 个 call）⇒ 不得形态推断"""
    body = """
  0:  55                    push   %ebp
  1:  8b ec                 mov    %esp,%ebp
  3:  8b 45 08              mov    0x8(%ebp),%eax
  6:  83 e0 01              and    $0x1,%eax
  9:  e8 00 00 00 00        call   0xe
  e:  8b e5                 mov    %ebp,%esp
 10:  5d                    pop    %ebp
 11:  c2 04 00              ret    $0x4
"""
    res = classify_slot(E(signature='void*(unsigned)', instructions=body))
    assert res.kind == KIND_FN, res
    assert res.features == frozenset(), res.features


# ================= 3. adjustor_static（add/sub imm; jmp，仅 ecx 操作数） =================

def test_adjustor_static_sub_imm_jmp_thunk():
    """abi #3 `?ff@D3@@W7AEHXZ`（vt3 实测 `83 e9 08 e9 ...`）：`sub imm,%ecx; jmp` ⇒ adjustor_static"""
    res = classify_slot(E(instructions=ADJ_STATIC_FF))
    assert res.kind == KIND_ADJUSTOR_STATIC, res
    assert res.features == frozenset({FEATURE_ADJUSTOR_STATIC}), res.features


def test_adjustor_static_add_imm_jmp_form():
    """同形态的 `add imm,%ecx; jmp`（MSVC 负 delta 亦发射 `add $0xfffffffX,%ecx`）⇒ adjustor_static"""
    body = """
  0:  83 c1 f8              add    $0xfffffff8,%ecx
  3:  e9 00 00 00 00        jmp    0x8
"""
    res = classify_slot(E(instructions=body))
    assert res.kind == KIND_ADJUSTOR_STATIC, res
    assert FEATURE_ADJUSTOR_STATIC in res.features


# ================= 4. adjustor_vbase（动态 delta：sub -N(%ecx),%ecx 或 vbtable 间接） =================

def test_adjustor_vbase_dynamic_delta_jmp():
    """abi #5 `?o@D@@$4PPPPPPPM@A@AEXXZ`（c2 实测）：`sub -0x4(%ecx),%ecx; jmp` ⇒ adjustor_vbase"""
    res = classify_slot(E(instructions=ADJ_VBASE_O))
    assert res.kind == KIND_ADJUSTOR_VBASE, res
    assert res.features == frozenset({FEATURE_ADJUSTOR_VBASE}), res.features


def test_adjustor_vbase_same_conclusion_under_intel_syntax():
    """ndisasm（Intel）与 IDA 语法（attack B-1 记录形态 `sub ecx, [ecx-4]`）必须同结论：
    证据来自原始指令字节，不因反汇编器语法而变"""
    for body in (ADJ_VBASE_O_NDISASM, ADJ_VBASE_O_IDA):
        res = classify_slot(E(instructions=body))
        assert res.kind == KIND_ADJUSTOR_VBASE, (body, res)


def test_adjustor_vbase_vbtable_indirect_delta():
    """vbtable 间接调整（`mov r,-0x4(%ecx)` → `sub 0x4(%r),%ecx`; jmp）⇒ 动态 delta ⇒ adjustor_vbase"""
    body = """
  0:  8b 41 fc              mov    -0x4(%ecx),%eax
  3:  2b 48 04              sub    0x4(%eax),%ecx
  6:  e9 00 00 00 00        jmp    0xb
"""
    res = classify_slot(E(instructions=body))
    assert res.kind == KIND_ADJUSTOR_VBASE, res
    assert res.features == frozenset({FEATURE_ADJUSTOR_VBASE}), res.features


# ================= 5. purecall（CRT stub / 外部符号） =================

def test_purecall_external_crt_stub():
    """abi #6（q2a 实测 `??_7Q2@@6B@[0] = __purecall`）：槽指向 CRT stub 外部符号 ⇒ purecall"""
    res = classify_slot(E(symbols=(PURECALL_EXTERNAL,), is_external=True,
                          external_symbol=PURECALL_EXTERNAL))
    assert res.kind == KIND_PURECALL, res
    assert res.features == frozenset({FEATURE_PURECALL}), res.features


def test_purecall_name_variants_recognised():
    """链接后符号写法 `__purecall` / `_purecall` / `purecall` 同结论（只认名字，不解析 mangling）"""
    for name in ('__purecall', '_purecall', 'purecall'):
        res = classify_slot(E(external_symbol=name, is_external=True))
        assert res.kind == KIND_PURECALL, (name, res)


# ================= 6. composite（多种特征同时命中 ⇒ 需 IDA 人工定性） =================

def test_composite_b1_mixed_slot_needs_manual_adjudication():
    """attack B-1 `??_ED@@$4PPPPPPPM@BA@AEPAXI@Z`（c2 实测 11 字节）：
    deleting dtor（`??_E` 同址 + 签名）× 动态 vbase 调整 × 常量 delta ⇒ 三特征 ⇒ composite"""
    ev = E(symbols=('??_ED@@$4PPPPPPPM@BA@AEPAXI@Z', '??_GD@@$4PPPPPPPM@BA@AEPAXI@Z'),
           signature='void*(unsigned)', instructions=COMPOSITE_ED)
    res = classify_slot(ev)
    assert res.kind == KIND_COMPOSITE, res
    assert res.features == frozenset({FEATURE_DELETING_DTOR, FEATURE_ADJUSTOR_STATIC,
                                      FEATURE_ADJUSTOR_VBASE}), res.features
    assert res.needs_manual_review is True, res


def test_composite_mixed_thunk_without_dtor_symbol():
    """混合调整链（动态 delta + 常量 delta）而**无** deleting dtor 证据 ⇒ 仍 composite
   （attack B-1 指出"序言也不是两指令形态"的混合槽无 kind 可归）"""
    ev = E(symbols=('?w@DV2@@$4PPPPPPPM@A@AEXXZ',), instructions=COMPOSITE_ED)
    res = classify_slot(ev)
    assert res.kind == KIND_COMPOSITE, res
    assert res.features == frozenset({FEATURE_ADJUSTOR_STATIC, FEATURE_ADJUSTOR_VBASE}), \
        res.features


# ================= 7. adjustor_static 判据的排除项（简报明列） =================

def test_import_thunk_symbol_family_excluded_from_adjustor_static():
    """import thunk（`j_*` 家族）**不得**判 adjustor_static —— 即使其形态恰好是 `add imm,%ecx; jmp`"""
    body = """
  0:  83 c1 04              add    $0x4,%ecx
  3:  e9 00 00 00 00        jmp    0x8
"""
    res = classify_slot(E(symbols=('j_MessageBoxA', '__imp__MessageBoxA@16'), instructions=body))
    assert res.kind == KIND_FN, res
    assert not (res.features & {FEATURE_ADJUSTOR_STATIC, FEATURE_ADJUSTOR_VBASE}), res.features
    assert any('import' in n.lower() for n in res.notes), res.notes


def test_indirect_jmp_import_thunk_excluded():
    """尾部**间接** jmp（`jmp *addr`，import thunk 体）⇒ 不是 adjustor"""
    body = """
  0:  83 c1 04              add    $0x4,%ecx
  3:  ff 25 00 00 00 00     jmp    *0x0
"""
    res = classify_slot(E(instructions=body))
    assert res.kind == KIND_FN, res
    assert any('import' in n.lower() for n in res.notes), res.notes


def test_incremental_linking_thunk_excluded():
    """增量链接 thunk 体（`mov %edi,%edi; push $target; jmp`）⇒ 不是 adjustor"""
    body = """
  0:  8b ff                 mov    %edi,%edi
  2:  68 00 00 00 00        push   $0x0
  7:  e9 00 00 00 00        jmp    0xc
"""
    res = classify_slot(E(instructions=body))
    assert res.kind == KIND_FN, res
    assert res.features == frozenset(), res.features


def test_parameter_forwarding_wrapper_excluded():
    """参数转发包装器（跳转前动栈/非 ecx 操作数）⇒ 不是 adjustor_static（"仅 ecx 操作数"）"""
    body = """
  0:  8b 44 24 08           mov    0x8(%esp),%eax
  4:  89 44 24 04           mov    %eax,0x4(%esp)
  8:  83 c1 04              add    $0x4,%ecx
  b:  e9 00 00 00 00        jmp    0x10
"""
    res = classify_slot(E(instructions=body))
    assert res.kind == KIND_FN, res
    assert res.features == frozenset(), res.features


# ================= 8. 词表 / Task 1 对接 / 证据痕迹 =================

def test_kind_vocabulary_and_task1_slot_order_alias():
    """kind 词表 = 简报 6 种；Task 1 `vtable_slot_order` 的 KIND_FUNC 词面是 'func' ⇒
    `slot_order_kind('fn') == 'func'` 供对接，其余 kind 原样通过"""
    assert set(ALL_KINDS) == {KIND_FN, KIND_DELETING_DTOR, KIND_ADJUSTOR_STATIC,
                              KIND_ADJUSTOR_VBASE, KIND_PURECALL, KIND_COMPOSITE}
    assert normalize_kind('func') == KIND_FN          # Task 1 词面 → 本模块词面
    assert slot_order_kind(KIND_FN) == 'func'         # 本模块词面 → Task 1 词面
    for k in (KIND_DELETING_DTOR, KIND_ADJUSTOR_STATIC, KIND_ADJUSTOR_VBASE,
              KIND_PURECALL, KIND_COMPOSITE):
        assert slot_order_kind(k) == k
        assert normalize_kind(k) == k


def test_unknown_kind_rejected():
    try:
        normalize_kind('vbase_adjustor_dyn')
    except ValueError:
        return
    raise AssertionError('unknown kind 未被拒绝')


def test_notes_record_which_evidence_matched():
    """每条命中的特征都要留证据痕迹（Task 5 诊断/审计用），composite 还要写明需人工定性"""
    ev = E(symbols=('??_ED@@$4PPPPPPPM@BA@AEPAXI@Z',), signature='void*(unsigned)',
           instructions=COMPOSITE_ED)
    res = classify_slot(ev)
    joined = ' | '.join(res.notes)
    assert 'deleting_dtor' in joined and '??_E' in joined, res.notes
    assert 'adjustor_vbase' in joined and 'adjustor_static' in joined, res.notes
    assert 'composite' in joined and '人工' in joined, res.notes


def test_golden_matrix_all_six_kinds():
    """金样本总表：6 种 kind 各 ≥1 实测例，逐条对齐两个 README（回归总控）"""
    cases = [
        (E(instructions=FN_H_AT_D), KIND_FN),
        (E(symbols=('??_GV@@UAEPAXI@Z', '??_EV@@UAEPAXI@Z'), signature='void*(unsigned)',
           instructions=DTOR_GV), KIND_DELETING_DTOR),
        (E(instructions=ADJ_STATIC_FF), KIND_ADJUSTOR_STATIC),
        (E(instructions=ADJ_VBASE_O), KIND_ADJUSTOR_VBASE),
        (E(symbols=(PURECALL_EXTERNAL,), is_external=True, external_symbol=PURECALL_EXTERNAL),
         KIND_PURECALL),
        (E(symbols=('??_ED@@$4PPPPPPPM@BA@AEPAXI@Z',), signature='void*(unsigned)',
           instructions=COMPOSITE_ED), KIND_COMPOSITE),
    ]
    got = [classify_slot(ev).kind for ev, _ in cases]
    assert got == [k for _, k in cases], got


def test_parse_disasm_accepts_objdump_and_bare_text():
    """夹具输入解析：objdump 带偏移/字节列与裸指令文本都要能解析成同一规范形态"""
    a = parse_disasm(ADJ_VBASE_O)
    b = parse_disasm('sub -0x4(%ecx),%ecx\njmp 0x8')
    assert [(i.mnem, i.ops) for i in a] == [(i.mnem, i.ops) for i in b], (a, b)
    assert [i.mnem for i in a] == ['sub', 'jmp']


def test_parse_disasm_skips_listing_headers():
    """objdump -D 完整输出含横幅/节头/符号头行 ⇒ 必须**跳过**，不得当指令解析
    （端到端核对真机 .obj 时发现：节头被解析成伪指令会打断调整链 ⇒ thunk 误判 fn）"""
    listing = """
/tmp/x.bin：     文件格式 binary


Disassembly of section .data:

00000000 <.data>:
   0:	83 e9 08             	sub    $0x8,%ecx
   3:	e9 00 00 00 00       	jmp    0x8
"""
    assert [i.mnem for i in parse_disasm(listing)] == ['sub', 'jmp']
    assert classify_slot(E(instructions=listing)).kind == KIND_ADJUSTOR_STATIC


# ================= 9. 解析器健壮性（静默失败缺陷修复，先红后绿） =================
#
# 三条实测缺陷（均为"解析器静默丢弃 ⇒ 真 adjustor thunk 误判成静默 fn（零 notes）"）：
#   例 1 `objdump -dr` 的**重定位注释行**被当成指令 ⇒ 尾 jmp 不在末位 ⇒ fn
#   例 2 IDA 粘贴的**地址列前缀**（`CODE:00401000` / `00401000`）⇒ 整段丢弃或伪指令 ⇒ fn
#   例 3 IDA 文本的 `;` 注释未剥离 ⇒ 操作数解析成 `other` ⇒ 调整链断裂 ⇒ fn
# 另加"非空输入但解析不出指令时必须留痕"（不得静默回落 fn）。

# 例 1 —— `objdump -dr` 逐字形态：指令行 + 紧随其后的重定位注释行
# （`?o@D@@$4PPPPPPPM@A@AEXXZ` 即 abi README #5 动态 vbase adjustor）
OBJDUMP_DR_VBASE_WITH_RELOC = """
  0:  2b 49 fc              sub    -0x4(%ecx),%ecx
  3:  e9 00 00 00 00        jmp    0x8
  3: R_386_PC32  ?o@D@@$4PPPPPPPM@A@AEXXZ
"""

# 同上形态的 `R_IA64_*` 家族（判据必须按 `R_<ARCH>_<TYPE>` 通用匹配，不写死 x86）
OBJDUMP_DR_STATIC_WITH_RELOC_IA64 = """
  0:  83 e9 08              sub    $0x8,%ecx
  3:  e9 00 00 00 00        jmp    0x8
  4: R_IA64_PCREL21B  ?ff@D3@@W7AEHXZ
"""

# 例 2 —— IDA 粘贴的地址列前缀三形态（同一 thunk 的逐字形态）
IDA_ADDR_COLUMN_CODE = """
CODE:00401000 sub ecx,[ecx-4]
CODE:00401003 jmp loc_body
"""
IDA_ADDR_COLUMN_BARE = """
00401000  sub ecx,[ecx-4]
00401003  jmp loc_body
"""
IDA_ADDR_COLUMN_TEXT_SEG = """
.text:00401000  sub ecx,[ecx-4]
.text:00401003  jmp loc_body
"""

# 例 3 —— IDA 文本带 `;` 行尾注释
IDA_SEMICOLON_COMMENT = """
sub ecx,[ecx-4]  ; adjust this
jmp loc_body    ; tail
"""

# 非空但**完全无法解析**的本体（既非指令，也无地址列/字节列）
UNPARSEABLE_BODY = """
@@@ not an instruction
=== still not one ===
"""


def test_objdump_reloc_annotation_lines_are_skipped():
    """缺陷例 1：`objdump -dr` 的重定位注释行（`R_386_*` / `R_IA64_*` 家族）**不是指令** ⇒
    必须跳过；否则它抢占末位、尾 jmp 不再在末位 ⇒ 真 adjustor thunk 静默判成 fn"""
    for text, kind, feats in (
            (OBJDUMP_DR_VBASE_WITH_RELOC, KIND_ADJUSTOR_VBASE, {FEATURE_ADJUSTOR_VBASE}),
            (OBJDUMP_DR_STATIC_WITH_RELOC_IA64, KIND_ADJUSTOR_STATIC, {FEATURE_ADJUSTOR_STATIC})):
        assert [i.mnem for i in parse_disasm(text)] == ['sub', 'jmp'], parse_disasm(text)
        res = classify_slot(E(instructions=text))
        assert res.kind == kind, (text, res)
        assert res.features == frozenset(feats), res.features


def test_reloc_and_structural_lines_are_not_counted_as_dropped():
    """重定位行/节头/**纯数据字节行**是**有意跳过**的结构行，不属"丢弃" ⇒ 不得因此触发
    partially_parsed（否则正常 `objdump -dr` 清单、数据密集的 COMDAT 切片会被误标解析不完整）"""
    data_run = OBJDUMP_DR_VBASE_WITH_RELOC + "  6:\t00 00 00 00\n  10:\t00\n"
    res = classify_slot(E(instructions=data_run))
    assert res.kind == KIND_ADJUSTOR_VBASE, res
    joined = ' | '.join(res.notes)
    assert 'partially_parsed' not in joined, res.notes
    assert 'insufficient_evidence' not in joined, res.notes


def test_ida_address_column_prefix_is_stripped():
    """缺陷例 2：IDA 粘贴形态 `CODE:00401000 instr` / `00401000  instr` / `.text:00401000 instr`
    的地址列前缀必须剥掉 ⇒ 与裸指令文本同结论（原实现整段丢弃 ⇒ insns 为空 ⇒ fn）"""
    for text in (IDA_ADDR_COLUMN_CODE, IDA_ADDR_COLUMN_BARE, IDA_ADDR_COLUMN_TEXT_SEG):
        assert [i.mnem for i in parse_disasm(text)] == ['sub', 'jmp'], (text, parse_disasm(text))
        res = classify_slot(E(instructions=text))
        assert res.kind == KIND_ADJUSTOR_VBASE, (text, res)
        assert res.features == frozenset({FEATURE_ADJUSTOR_VBASE}), res.features


def test_ida_semicolon_comment_is_stripped_before_operand_parse():
    """缺陷例 3：`;` 行尾注释必须剥离 ⇒ 操作数仍解析成 `mem`（base=ecx, disp=-4）而非 `other`，
    调整链不断 ⇒ adjustor_vbase"""
    ins = parse_disasm(IDA_SEMICOLON_COMMENT)
    assert [i.mnem for i in ins] == ['sub', 'jmp'], ins
    src = ins[0].ops[1]
    assert (src.kind, src.base, src.disp) == ('mem', 'ecx', -4), src
    assert not any(o.kind == 'other' for i in ins for o in i.ops), ins
    res = classify_slot(E(instructions=IDA_SEMICOLON_COMMENT))
    assert res.kind == KIND_ADJUSTOR_VBASE, res


def test_unparseable_body_leaves_insufficient_evidence_trace():
    """非空输入但解析出 0 条指令 ⇒ **必须**在 notes 里留 `insufficient_evidence` 痕迹
    （原实现静默返回零 notes 的 fn —— 真 thunk 就这样消失）"""
    res = classify_slot(E(instructions=UNPARSEABLE_BODY))
    assert res.kind == KIND_FN, res
    assert res.notes, '非空输入零解析不得静默返回空 notes'
    assert any('insufficient_evidence' in n for n in res.notes), res.notes


def test_mostly_dropped_body_leaves_partially_parsed_trace():
    """丢弃行占比 > 50% ⇒ 留 `partially_parsed` 痕迹（解析不完整时 fn 结论不可信）"""
    text = '\n'.join(['sub ecx,[ecx-4]', '@@@ junk 1', '=== junk 2 ===', '%%% junk 3 %%%'])
    res = classify_slot(E(instructions=text))
    assert res.kind == KIND_FN, res
    assert any('partially_parsed' in n for n in res.notes), res.notes


def test_empty_input_has_no_evidence_trace():
    """空输入（无任何非空行）不属"证据不足"——不得凭空产生痕迹"""
    for text in ('', '\n\n   \n'):
        res = classify_slot(E(instructions=text))
        assert res.notes == (), (text, res.notes)
        assert res.kind == KIND_FN, (text, res)


if __name__ == '__main__':
    ok = fail = skip = 0
    for nm, fn in sorted(list(globals().items())):
        if nm.startswith('test_') and callable(fn):
            try:
                fn(); print('  PASS %s' % nm); ok += 1
            except unittest.SkipTest as e:
                print('  SKIP %s: %s' % (nm, e)); skip += 1
            except Exception as e:
                print('  FAIL %s: %s: %s' % (nm, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)
