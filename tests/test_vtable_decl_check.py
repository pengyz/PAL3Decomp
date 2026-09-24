"""`tools/vtable_decl_check.py` 的测试 —— **先写测试**（TDD，红→绿）。

被测对象：**声明校验（棘轮制）**。校验三类项，并把结果折算成**只升不降**的棘轮指标：

  1. **槽数数** —— 声明数量 vs `vtables[].slots` 数量（按 view 对，MI 多表各自校验）
  2. **槽序**   —— 用 Task 1（`vtable_slot_order`）的**正向规则**从声明生成预期槽序，逐槽对比
  3. **签名**   —— Task 3（`vtable_sig_infer`）`methods_pending` 候选 vs 声明（**等价类**维度）

棘轮三态：上升 ⇒ 放行 + 更新基线；不变 ⇒ 放行；下降 ⇒ **阻塞**（回归检测）。
**禁止硬门禁**（v1/v2 两次死锁证明此路不通）⇒ 本文件有专门一条测试钉死"0 已验证不阻塞"。

## 控制器裁定（Ruling 1–5）在本文件中的对应测试

| Ruling | 内容 | 测试 |
|---|---|---|
| 1 | 棘轮必须接受 **B/C 带证据**（A 级占比下降，按"必须 A"会首日死锁） | `test_ruling1_*` ×3 |
| 2 | 必须读 `features` 区分 `sret_ambiguous` vs `hidden_param_suspicion`（不能只看 grade） | `test_ruling2_*` ×4 |
| 3 | 键归一（3398 methods 键中 32 个小写 ⇒ 消费时必须归一小写） | `test_ruling3_*` ×2 |
| 4 | 词面统一（Task 1 `'func'` vs Task 2 `'fn'`）必须经 `slot_order_kind()` 适配 | `test_ruling4_*` ×2 |
| 5 | 校验基准是**编译产物**（独立于 methods 表），不是同源自比 | `test_ruling5_*` ×2 |

## 判别力（负向/变异测试）

`test_mutation_*` 故意改**槽序 / 槽数 / 签名**，断言校验必须报警且棘轮必须阻塞
（否则门禁无判别力）。另有真实数据锚点：`CEffectSystem` 的 `0x4C6260` 在生成头里排在第 2 位、
二进制却排在最后 —— 实测真差异，必须被报为 `order_mismatch`。

运行：`python3 tests/test_vtable_decl_check.py` 或 `pytest tests/test_vtable_decl_check.py`
（本机 pytest 恒崩 —— `_pytest/assertion/rewrite.py` 的 `TypeError: required field "lineno"
missing from alias`，与 Task 1/2/3/4 记录一致 ⇒ 用文件内独立运行器。）
"""
import json
import os
import shutil
import sys
import tempfile
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PROJECT_ROOT / 'tools'))

from vtable_decl_check import (  # noqa: E402
    KIND_FN,
    MODEL_CHAIN,
    MODEL_FLAT,
    ORDER_ALIAS,
    ORDER_MISMATCH,
    ORDER_OK,
    ORDER_UNDECLARED,
    ORDER_VIEW_UNMATCHED,
    RATCHET_BLOCKED,
    RATCHET_IMPROVED,
    RATCHET_PASS,
    SIG_CONTRADICTION,
    SIG_OK,
    SIG_SYNTHETIC_OK,
    SIG_UNCHECKED,
    SIG_WEAK,
    BinaryView,
    CheckResult,
    ClassDecls,
    ClassHealth,
    DeclSpec,
    RatchetDecision,
    SigVerdict,
    SlotResult,
    ViewCheck,
    build_baseline,
    build_hierarchy,
    check_all,
    check_class,
    cpp_return_kind,
    cpp_type_param_class,
    decl_arity,
    load_decl_dir,
    load_pending,
    load_structs_dir,
    main,
    norm_addr_key,
    parse_decl_text,
    ratchet_decide,
    render_report,
    signature_verdict,
)

REAL_DECLS = PROJECT_ROOT / 'pal3' / 'src'
REAL_STRUCTS = PROJECT_ROOT / 'data' / 'annotations' / 'structs'


# ---------------- 夹具小工具 ----------------

def _decl_line(ret, name, params='', addr=None, cv='', pure=False, inline=False):
    """造一行生成头里的 virtual 声明（`// 0xADDR` 尾注释可选）。"""
    head = ('virtual %s ' % ret).strip() + ' ' if ret else 'virtual '
    body = '%s(%s)%s' % (name, params, (' ' + cv) if cv else '')
    tail = ' = 0' if pure else ''
    end = '{}' if inline else ';'
    cmt = (' // 0x%08X' % addr) if addr is not None else ''
    return '    %s%s%s%s%s' % (head, body, tail, end, cmt)


def _header(cls, lines, bases=()):
    """造一个 codegen 生成头（class 块 + 声明行）。"""
    inh = ''
    if bases:
        inh = ' : ' + ', '.join('public %s' % b for b in bases) + ' '
    out = ['#pragma once', '// Auto-generated: %s' % cls, '', 'class %s%s{' % (cls, inh), 'public:']
    out.extend(lines)
    out.append('};')
    return '\n'.join(out) + '\n'


def _struct_json(cls, views):
    """views: [(vtable_addr, base_label_or_None, [slot_addr...]), ...]"""
    return {
        'name': cls,
        'vtables': [{
            'addr': '0x%08X' % va,
            'base': base,
            'slots': [{'addr': '0x%08X' % sa, 'from': None} for sa in slots],
        } for va, base, slots in views],
    }


def _cand(signature='int()', arity=0, ret='i32', params=(), grade='A',
          features=(), convention='__thiscall', lower_bound=False, variadic=False,
          cc_provisional=False):
    return {
        'signature': signature, 'convention': convention, 'arity': arity,
        'arity_is_lower_bound': lower_bound, 'return_kind': ret,
        'params': list(params), 'variadic': variadic, 'grade': grade,
        'features': list(features), 'notes': [],
    }


def _p(slots=1, classes=('i32', 'ptr', 'f32', 'bool', 'i8', 'i16')):
    return {'slots': slots, 'class_candidates': list(classes), 'determined': len(classes) == 1}


def _pending(entries):
    """entries: {addr(int or str): record dict}"""
    return {norm_addr_key(a): r for a, r in entries.items()}


def _cd(cls, decls, bases=()):
    return ClassDecls(cls=cls, bases=tuple(bases), decls=tuple(decls))


def _d(name, params='', addr=None, ret='void', kind=KIND_FN, cv='', variadic=False, pure=False):
    return DeclSpec(name=name, params=params, cv=cv, ret=ret, kind=kind, addr=addr,
                    variadic=variadic, pure=pure)


class _Tmp(unittest.TestCase):
    """给需要落盘的用例提供 tmp 目录。"""

    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp(prefix='t5decl_'))

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def write(self, rel, text):
        p = self.tmp / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(text, encoding='utf-8')
        return p


# ================= 1. 声明解析 =================

def test_parse_header_basic_decls_with_addr():
    txt = _header('B', [_decl_line('void', 'f', '', 0x401000),
                        _decl_line('int', 'g', 'int a', 0x401010)])
    got = parse_decl_text(txt)
    assert set(got) == {'B'}, got
    cd = got['B']
    assert [d.name for d in cd.decls] == ['f', 'g']
    assert [d.addr for d in cd.decls] == [0x401000, 0x401010]
    assert cd.decls[1].ret == 'int'
    assert cd.decls[1].params == '(int)'


def test_parse_header_records_bases():
    txt = _header('D', [_decl_line('void', 'f', '', 0x401000)],
                  bases=('A', 'CTaskTpl_D'))
    got = parse_decl_text(txt)
    assert got['D'].bases == ('A', 'CTaskTpl_D')


def test_parse_header_skips_nonvirtual_and_members():
    txt = _header('B', [
        _decl_line('void', 'f', '', 0x401000),
        '    int m_nX; // +0x4',
        '    int Init(int a); // 0x00401020',
        '    static void S(); // 0x00401030',
    ])
    cd = parse_decl_text(txt)['B']
    assert [d.name for d in cd.decls] == ['f']


def test_parse_header_addrless_virtual_dtor_recorded():
    """生成头把注入的虚析构写成 `virtual ~C() {}`（无地址注释）⇒ 必须记账，不得静默丢。"""
    txt = _header('C', [_decl_line('', '~C', '', None, inline=True),
                        _decl_line('void', 'f', '', 0x401000)])
    cd = parse_decl_text(txt)['C']
    assert [d.name for d in cd.decls] == ['~C', 'f']
    assert cd.decls[0].addr is None
    assert cd.decls[0].kind == 'deleting_dtor'
    assert cd.decls[0].inline is True


def test_parse_header_pure_virtual_kind():
    txt = _header('C', [_decl_line('void', 'f', '', 0x401000, pure=True)])
    d = parse_decl_text(txt)['C'].decls[0]
    assert d.pure is True
    assert d.kind == 'purecall'


def test_parse_header_const_and_variadic():
    txt = _header('C', [_decl_line('int', 'f', 'char * format', 0x401000, cv='const'),
                        _decl_line('void', 'g', 'int a, ...', 0x401010, inline=False)])
    cd = parse_decl_text(txt)['C']
    assert cd.decls[0].cv == 'const'
    assert cd.decls[0].kind == KIND_FN
    assert cd.decls[1].variadic is True
    # 变参声明级 sig = 参数表 + cv（Task 1 口径）
    assert cd.decls[1].sig == '(int,...)'


def test_parse_header_missing_addr_comment_tolerated():
    txt = _header('C', ['    virtual void f();'])
    d = parse_decl_text(txt)['C'].decls[0]
    assert d.addr is None and d.name == 'f'


def test_parse_header_param_names_stripped_for_matching():
    """派生头覆写基类时参数名常常不同（nVal vs a）⇒ 声明级 sig 必须剥参数名，
    否则 Task 1 的 match_key 认不出覆写（会当成新增槽 ⇒ 槽序假失败）。"""
    base = parse_decl_text(_header('A', [_decl_line('int', 'g', 'int a', 0x401000)]))['A']
    der = parse_decl_text(_header('D', [_decl_line('int', 'g', 'int nVal', 0x402000)],
                                  bases=('A',)))['D']
    assert base.decls[0].sig == der.decls[0].sig == '(int)'


def test_parse_header_braces_inside_inline_body_do_not_break_class_scan():
    txt = ('class C {\npublic:\n'
           '    virtual void f() { if (1) { } }\n'
           '    virtual void g(); // 0x00401000\n'
           '};\n')
    cd = parse_decl_text(txt)['C']
    assert [d.name for d in cd.decls] == ['f', 'g']


def test_load_decl_dir_reads_headers_and_dedups_by_richest_body():
    txt1 = _header('A', [_decl_line('void', 'f', '', 0x401000)])
    txt2 = _header('A', [_decl_line('void', 'f', '', 0x401000),
                         _decl_line('void', 'g', '', 0x401010)])
    with tempfile.TemporaryDirectory() as td:
        p = Path(td)
        (p / 'a.h').write_text(txt1, encoding='utf-8')
        (p / 'sub').mkdir()
        (p / 'sub' / 'a.h').write_text(txt2, encoding='utf-8')
        got = load_decl_dir(p)
    assert [d.name for d in got['A'].decls] == ['f', 'g']


def test_norm_addr_key_unifies_case_and_width():
    assert norm_addr_key(0x45AE60) == '0x0045ae60'
    assert norm_addr_key('0x0045AE60') == '0x0045ae60'
    assert norm_addr_key('0x45ae60') == '0x0045ae60'
    assert norm_addr_key('45ae60h') == '0x0045ae60'


def test_load_pending_accepts_bypass_file_and_normalizes_keys():
    raw = {'methods_pending': {'0x0045AE60': {'candidates': []}}}
    got = load_pending(raw)
    assert list(got) == ['0x0045ae60']
    assert load_pending({'0x0045AE60': {'candidates': []}}) == got


# ================= 2. Ruling 3：键归一 =================

def test_ruling3_lowercase_pending_key_is_found():
    """Ruling 3 正例：真实注解里有 32/3398 个小写地址键（如 SaleUI 0x0045ae60）⇒
    归一后必须命中签名证据。"""
    decls = {'C': _cd('C', [_d('f', '', 0x45AE60, ret='int')])}
    views = {'C': [BinaryView(0x56AAAA, None, (0x45AE60,))]}
    pend = _pending({'0x0045ae60': {'candidates': [_cand('int()', 0, 'i32')]}})
    _views, health = check_class('C', decls['C'], views['C'], pack_pending(pend))
    assert health.sig_checked == 1, health
    assert health.sig_ok == 1, health


def test_ruling3_naive_uppercase_lookup_would_miss():
    """Ruling 3 反例（判别力）：不归一（直接大写查表）时同一份证据查不到 ⇒ 0.94% 键对不上。"""
    pending_upper = {'0x0045AE60': {'candidates': [_cand('int()', 0, 'i32')]}}
    assert norm_addr_key('0x0045ae60') not in pending_upper      # 未归一 ⇒ 漏
    assert norm_addr_key('0x0045ae60') in {norm_addr_key(k) for k in pending_upper}   # 归一 ⇒ 中


def pack_pending(pending):
    """把 {key: record} 包成 load_pending 口径的 dict（测试内部小工具）。"""
    return pending


# ================= 3. Ruling 4：词面适配器 =================

def test_ruling4_fn_word_survives_adapter_and_is_not_synthetic():
    """Ruling 4 正例：Task 2 词面 `'fn'` 经 `slot_order_kind()` 变成 `'func'` 才喂 Task 1；
    否则 Task 1 会把 `'fn'` 当**合成槽**（单槽组）⇒ 槽序错。"""
    from vtable_slot_order import KIND_FUNC
    from vtable_slot_classifier import slot_order_kind
    assert KIND_FN == 'fn'
    assert slot_order_kind(KIND_FN) == KIND_FUNC

    # 同名组逆序：经适配器后 o()/o(int) 成组逆序 ⇒ [o(int), o()]
    decls = [_d('o', '', 0x1000, ret='void'), _d('o', '(int)', 0x2000, ret='void')]
    cd = _cd('C', decls)
    views = [BinaryView(0x56A000, None, (0x2000, 0x1000))]
    vc, health = check_class('C', cd, views, model=MODEL_FLAT)
    assert vc[0].slots[0].addr == 0x2000
    assert [s.order for s in vc[0].slots] == [ORDER_OK, ORDER_OK], vc[0].slots
    assert health.slot_health == 1.0


def test_ruling4_naive_pass_through_would_misorder():
    """Ruling 4 反例（判别力）：把 `'fn'` 直接当 kind 传给 Task 1 ⇒ 每个声明都成**单槽组**
    ⇒ 同名组逆序消失 ⇒ 预期槽序变成声明序，与二进制实测相反。"""
    from vtable_slot_order import VirtualDecl, compute_slot_order
    naive = compute_slot_order([], [VirtualDecl('o', '()', 'fn'), VirtualDecl('o', '(int)', 'fn')])
    assert [e.decl.sig for e in naive] == ['()', '(int)']       # 未逆序（错）
    good = compute_slot_order([], [VirtualDecl('o', '()', 'func'),
                                   VirtualDecl('o', '(int)', 'func')])
    assert [e.decl.sig for e in good] == ['(int)', '()']        # 逆序（对）


# ================= 4. §1 槽数数 =================

def test_count_check_ok_single_view():
    cd = _cd('C', [_d('f', '', 0x1000), _d('g', '(int)', 0x2000, ret='int')])
    views = [BinaryView(0x56A000, None, (0x1000, 0x2000))]
    vc, health = check_class('C', cd, views)
    assert vc[0].count_ok is True
    assert vc[0].n_slots == 2 and vc[0].n_decl_addr == 2 and vc[0].n_decl_addrless == 0
    assert health.count_ok is True and health.count_health == 1.0


def test_count_check_extra_decl_reported():
    """变异：多声明一个虚函数（二进制表里没有对应槽）⇒ 槽数项必须报警。"""
    cd = _cd('C', [_d('f', '', 0x1000), _d('g', '(int)', 0x2000, ret='int'),
                   _d('bogus', '', 0x3000)])
    views = [BinaryView(0x56A000, None, (0x1000, 0x2000))]
    vc, health = check_class('C', cd, views)
    assert vc[0].count_ok is False
    assert vc[0].n_decl_addr == 3 and vc[0].n_slots == 2
    assert health.count_health < 1.0
    assert any('槽数' in f for f in health.findings), health.findings


def test_count_check_missing_decl_reported():
    """变异：少声明一个 ⇒ 槽数项报警 + 该槽 undeclared。"""
    cd = _cd('C', [_d('f', '', 0x1000)])
    views = [BinaryView(0x56A000, None, (0x1000, 0x2000))]
    vc, health = check_class('C', cd, views)
    assert vc[0].count_ok is False
    assert [s.order for s in vc[0].slots] == [ORDER_OK, ORDER_UNDECLARED]
    assert health.slot_health == 0.5


def test_count_check_addrless_decl_counted_but_not_positioned():
    """位置不可判的声明（`virtual ~C() {}`）：计入槽数项与 finding，但不参与逐槽序对比
    （否则会凭空平移对齐 ⇒ 正确声明被误判）。"""
    cd = _cd('C', [_d('~C', '', None, ret='', kind='deleting_dtor'),
                   _d('f', '', 0x1000)])
    views = [BinaryView(0x56A000, None, (0x1000,))]
    vc, health = check_class('C', cd, views)
    assert vc[0].n_decl_addrless == 1
    assert vc[0].count_ok is False                     # 2 声明（含 1 无地址）vs 1 槽
    assert [s.order for s in vc[0].slots] == [ORDER_OK]
    assert health.slot_health == 1.0
    assert health.count_health < 1.0                   # 无地址声明压低计数棘轮


# ================= 5. §2 槽序 =================

def test_order_exact_sequence_verifies_all():
    cd = _cd('C', [_d('f', '', 0x1000), _d('g', '(int)', 0x2000, ret='int')])
    views = [BinaryView(0x56A000, None, (0x1000, 0x2000))]
    vc, health = check_class('C', cd, views)
    assert [s.order for s in vc[0].slots] == [ORDER_OK, ORDER_OK]
    assert health.slot_health == 1.0 and health.n_order_ok == 2


def test_order_uses_task1_group_reversal_for_overloads():
    """§2 必须真的用 Task 1 正向规则：同名重载组内逆序 ⇒ 声明 [o(),o(int)] 的**预期**槽序
    是 [o(int), o()]；二进制若给出 [o(),o(int)] 则是 order_mismatch。"""
    cd = _cd('C', [_d('o', '', 0x1000), _d('o', '(int)', 0x2000)])
    swapped = [BinaryView(0x56A000, None, (0x1000, 0x2000))]
    vc, health = check_class('C', cd, swapped)
    assert [s.order for s in vc[0].slots] == [ORDER_MISMATCH, ORDER_MISMATCH]
    assert health.slot_health == 0.0


def test_order_mutation_swap_decl_addresses_is_reported():
    """变异：把两个声明的地址对调 ⇒ 预期槽序与二进制不符 ⇒ 必须报警。"""
    good = _cd('C', [_d('f', '', 0x1000), _d('g', '(int)', 0x2000, ret='int')])
    bad = _cd('C', [_d('f', '', 0x2000), _d('g', '(int)', 0x1000, ret='int')])
    views = [BinaryView(0x56A000, None, (0x1000, 0x2000))]
    assert [s.order for s in check_class('C', good, views)[0][0].slots] == [ORDER_OK, ORDER_OK]
    vc, health = check_class('C', bad, views)
    assert all(s.order == ORDER_MISMATCH for s in vc[0].slots)
    assert health.slot_health == 0.0


def test_order_undeclared_slot_has_no_decl():
    cd = _cd('C', [_d('f', '', 0x1000)])
    views = [BinaryView(0x56A000, None, (0x9999,))]
    vc, _h = check_class('C', cd, views)
    assert vc[0].slots[0].order == ORDER_UNDECLARED
    assert vc[0].slots[0].decl_index is None


def test_order_alias_duplicate_slot_addr_verified_with_note():
    """二进制表同一函数占两槽（MSVC 会把同一指针写进多个槽）⇒ 声明按唯一地址去重时，
    重复槽记 `alias` 并**算已验证**（该地址确实被声明），但必须留痕。"""
    cd = _cd('C', [_d('f', '', 0x1000), _d('g', '(int)', 0x2000, ret='int')])
    views = [BinaryView(0x56A000, None, (0x1000, 0x1000, 0x2000))]
    vc, health = check_class('C', cd, views)
    assert [s.order for s in vc[0].slots] == [ORDER_OK, ORDER_ALIAS, ORDER_OK]
    assert health.slot_health == 1.0
    assert any('别名' in n for n in vc[0].slots[1].notes)


# ================= 6. §2 MI（多视图各自校验） =================

def _mi_fixture():
    """vt2 形状：D : A, B；f/h 覆写，m 新增（只进主视图）。"""
    txt = (_header('A', [_decl_line('void', 'f', '', 0x1000),
                         _decl_line('void', 'g', 'int a', 0x1010, inline=False)])
           + _header('B', [_decl_line('void', 'h', '', 0x2000),
                           _decl_line('void', 'k', 'double a', 0x2010, inline=False)])
           + _header('D', [_decl_line('void', 'f', '', 0x3000),
                           _decl_line('void', 'h', '', 0x3010),
                           _decl_line('void', 'm', '', 0x3020)], bases=('A', 'B')))
    return parse_decl_text(txt)


def test_order_mi_views_checked_independently():
    decls = _mi_fixture()
    views = [BinaryView(0x56A000, 'A', (0x3000, 0x1010, 0x3020)),
             BinaryView(0x56A020, 'B', (0x3010, 0x2010))]
    vcs, health = check_class('D', decls['D'], views, hierarchy=build_hierarchy(decls),
                              model=MODEL_CHAIN, decls_by_cls=decls)
    assert len(vcs) == 2
    assert [v.label for v in vcs] == ['A', 'B']
    assert all(s.order == ORDER_OK for v in vcs for s in v.slots)
    assert health.slot_health == 1.0 and health.n_slots == 5


def test_order_mi_secondary_view_mutation_blocks_that_view_only():
    """变异：只改次视图槽序 ⇒ 次视图 2 槽全 mismatch，主视图 3 槽仍 verified。"""
    decls = _mi_fixture()
    views = [BinaryView(0x56A000, 'A', (0x3000, 0x1010, 0x3020)),
             BinaryView(0x56A020, 'B', (0x2010, 0x3010))]
    vcs, health = check_class('D', decls['D'], views, hierarchy=build_hierarchy(decls),
                              model=MODEL_CHAIN, decls_by_cls=decls)
    assert [s.order for s in vcs[0].slots] == [ORDER_OK, ORDER_OK, ORDER_OK]
    assert [s.order for s in vcs[1].slots] == [ORDER_MISMATCH, ORDER_MISMATCH]
    assert health.n_slots == 5 and health.n_order_ok == 3


def test_order_flat_model_marks_extra_binary_views_unmatched():
    """flat 模型（默认）只校验主表；其余二进制表记 `view_unmatched`（未验证，0 分），
    并应提示改用 MODEL_CHAIN —— 这是有意的保守口径，不是静默放过。
    注意 flat 模型对 MI 是**有限**的：D 的头只声明自己的槽（不含继承槽 g）⇒ 主表也会报错位，
    这正是 MI 必须走 chain 的原因（chain 用例见上）。"""
    decls = _mi_fixture()
    views = [BinaryView(0x56A000, 'A', (0x3000, 0x1010, 0x3020)),
             BinaryView(0x56A020, 'B', (0x3010, 0x2010))]
    vcs, health = check_class('D', decls['D'], views, hierarchy=build_hierarchy(decls),
                              model=MODEL_FLAT, decls_by_cls=decls)
    assert len(vcs) == 2
    assert all(s.order == ORDER_VIEW_UNMATCHED for s in vcs[1].slots)
    assert health.n_slots == 5
    assert 1 <= health.n_order_ok < 5          # flat 对 MI 只能部分命中 ⇒ 必须走 chain
    assert health.slot_health < 1.0
    assert any('view_unmatched' in f or 'chain' in f for f in health.findings), health.findings


# ================= 7. §3 签名（等价类维度） =================

def test_cpp_type_param_class_mapping():
    assert cpp_type_param_class('int') == 'i32'
    assert cpp_type_param_class('unsigned int') == 'i32'
    assert cpp_type_param_class('char *') == 'ptr'
    assert cpp_type_param_class('const char *') == 'ptr'
    assert cpp_type_param_class('BYTE') == 'i8'
    assert cpp_type_param_class('WORD') == 'i16'
    assert cpp_type_param_class('bool') == 'bool'
    assert cpp_type_param_class('BOOL') == 'i32'      # Windows BOOL = int（物化不同）
    assert cpp_type_param_class('float') == 'f32'
    assert cpp_type_param_class('double') == 'f64'
    assert cpp_type_param_class('__int64') == 'i64'
    assert cpp_type_param_class('tagRECT') == 'struct'
    assert cpp_type_param_class('void') == 'void'


def test_cpp_return_kind_mapping():
    assert cpp_return_kind('void') == 'void'
    assert cpp_return_kind('int') == 'i32'
    assert cpp_return_kind('CUtil *') == 'i32'        # 4 字节寄存器返回（Task 3 词面 i32）
    assert cpp_return_kind('bool') == 'bool'
    assert cpp_return_kind('char') == 'i8'


def test_decl_arity_counts_params_excluding_this():
    assert decl_arity(_d('f', '')) == 0
    assert decl_arity(_d('f', '(int,char*)')) == 2
    assert decl_arity(_d('f', '(int,...)', variadic=True)) == 1


def test_signature_grade_a_compatible():
    d = _d('g', '(int)', 0x2000, ret='int')
    v = signature_verdict(d, [_cand('int(int)', 1, 'i32', [_p(1, ('i32', 'ptr', 'f32'))])])
    assert v.status == SIG_OK, v
    assert v.detail == 'ok'


def test_signature_mutation_extra_param_is_contradiction():
    """变异：声明多一个参数（A 级候选 arity 确定）⇒ 必须判矛盾。"""
    d = _d('g', '(int,char*)', 0x2000, ret='int')
    v = signature_verdict(d, [_cand('int(int)', 1, 'i32', [_p(1, ('i32', 'ptr'))])])
    assert v.status == SIG_CONTRADICTION
    assert v.detail == 'arity_mismatch'


def test_signature_param_class_contradiction():
    d = _d('g', '(double)', 0x2000, ret='void')
    v = signature_verdict(d, [_cand('void(double)', 1, 'void', [_p(2, ('f64', 'i64'))])])
    assert v.status == SIG_OK
    bad = signature_verdict(_d('g', '(int)', 0x2000, ret='void'),
                            [_cand('void(float)', 1, 'void', [_p(1, ('f32',))])])
    assert bad.status == SIG_CONTRADICTION
    assert bad.detail == 'param_class_mismatch'


def test_signature_return_contradiction():
    d = _d('g', '()', 0x2000, ret='void')
    v = signature_verdict(d, [_cand('int()', 0, 'i32')])
    assert v.status == SIG_CONTRADICTION and v.detail == 'return_mismatch'


def test_signature_variadic_contradiction():
    d = _d('g', '(int)', 0x2000, ret='void', variadic=False)
    v = signature_verdict(d, [_cand('void(int,...)', 1, 'void', [_p(1, ('i32',))], variadic=True)])
    assert v.status == SIG_CONTRADICTION and v.detail == 'variadic_mismatch'


def test_signature_unknown_lower_bound_arity_accepted():
    """arity_is_lower_bound（cdecl 读集下界）⇒ 声明参数更多不算矛盾（B/C 带证据）。"""
    d = _d('g', '(int,char*,double)', 0x2000, ret='void')
    v = signature_verdict(d, [_cand('void(int)', 1, 'unknown', [_p(1, ('i32',))],
                                    grade='B', lower_bound=True,
                                    features=('arity_is_lower_bound',))])
    assert v.status in (SIG_OK,), v


def test_signature_one_of_many_candidates_compatible():
    """一地址多候选（ICF/多重声明）⇒ 任一候选无矛盾即通过。"""
    d = _d('g', '(int)', 0x2000, ret='int')
    v = signature_verdict(d, [
        _cand('int(char)', 1, 'i32', [_p(1, ('i8',))], grade='B'),
        _cand('int(int)', 1, 'i32', [_p(1, ('i32', 'ptr'))], grade='B'),
    ])
    assert v.status == SIG_OK


def test_signature_unchecked_without_evidence():
    v = signature_verdict(_d('g', '(int)', 0x2000, ret='int'), [])
    assert v.status == SIG_UNCHECKED
    assert v.detail == 'unchecked'


def test_signature_synthetic_decl_without_candidate_is_ok():
    """合成槽（Task 3 跳过签名推断）⇒ 槽型声明本身即证据，记 synthetic。"""
    v = signature_verdict(_d('~C', '', None, ret='', kind='deleting_dtor'), [])
    assert v.status == SIG_SYNTHETIC_OK


def test_signature_weak_when_candidate_determines_nothing():
    d = _d('g', '(int)', 0x2000, ret='int')
    v = signature_verdict(d, [_cand('?()', None, 'unknown', [], grade='C')])
    assert v.status == SIG_WEAK


def test_signature_convention_contradiction_only_for_grade_a():
    """调用约定矛盾只在 A 级（且无 this_on_stack）时算硬矛盾；B/C 只留痕。"""
    d = _d('g', '(int)', 0x2000, ret='int')
    a = signature_verdict(d, [_cand('int(int)', 1, 'i32', [_p(1, ('i32',))],
                                    convention='__cdecl', grade='A')])
    assert a.status == SIG_CONTRADICTION and a.detail == 'convention_mismatch'
    b = signature_verdict(d, [_cand('int(int)', 1, 'i32', [_p(1, ('i32',))],
                                    convention='__cdecl', grade='B',
                                    features=('this_on_stack',))])
    assert b.status == SIG_OK


# ================= 8. Ruling 1：接受 B/C 带证据 =================

def test_ruling1_grade_a_accepted():
    d = _d('g', '(int)', 0x2000, ret='int')
    assert signature_verdict(d, [_cand('int(int)', 1, 'i32', [_p(1, ('i32',))],
                                       grade='A')]).status == SIG_OK


def test_ruling1_grade_b_with_evidence_accepted():
    """B 级（缺返回宽度/cc_provisional）带证据 ⇒ 必须放行，不能要求 A 才通过。"""
    d = _d('g', '(int)', 0x2000, ret='int')
    v = signature_verdict(d, [_cand('?()', 1, 'unknown', [_p(1, ('i32', 'ptr'))],
                                    grade='B', cc_provisional=True)])
    assert v.status == SIG_OK, v


def test_ruling1_grade_c_with_evidence_accepted():
    d = _d('g', '(int)', 0x2000, ret='int')
    v = signature_verdict(d, [_cand('?()', None, 'unknown', [_p(1, ('i32',))], grade='C')])
    assert v.status == SIG_OK, v


# ================= 9. Ruling 2：features 区分 sret_ambiguous / hidden_param_suspicion =================

def test_ruling2_sret_ambiguous_waives_return_dimension():
    """B + sret_ambiguous = "判不出"（返回结构体 >8B ⇒ 首参 sret，整体可能错位一位）
    ⇒ 返回宽度不符**不得**判矛盾，且必须留痕 `waived=('return',...)`。"""
    d = _d('g', '()', 0x2000, ret='void')
    v = signature_verdict(d, [_cand('void()', 0, 'sret(>8B)', [],
                                    grade='B', features=('sret_ambiguous',))])
    assert v.status == SIG_OK, v
    assert 'return' in v.waived
    assert 'sret_ambiguous' in v.notes


def test_ruling2_hidden_param_suspicion_waives_exact_arity():
    """B + hidden_param_suspicion = "有隐藏参数嫌疑" ⇒ arity 只是下界（+1 合法），
    waived 里记 `arity`（与 sret_ambiguous 的语义不同 ⇒ 判定也不同）。"""
    d = _d('g', '(int,char*)', 0x2000, ret='int')
    v = signature_verdict(d, [_cand('int(int)', 1, 'i32', [_p(1, ('i32',))],
                                    grade='B', features=('hidden_param_suspicion',),
                                    lower_bound=True)])
    assert v.status == SIG_OK, v
    assert 'arity' in v.waived
    assert 'hidden_param_suspicion' in v.notes


def test_ruling2_two_features_are_distinguishable_not_grade_only():
    """Ruling 2 核心：同 grade=B 的两个候选，因 features 不同 ⇒ waived 不同
    （只看 grade 无法区分 ⇒ 这是"必须读 features"的可检查形式）。"""
    d = _d('g', '(int)', 0x2000, ret='void')
    sret = signature_verdict(d, [_cand('void()', 1, 'sret(>8B)', [], grade='B',
                                       features=('sret_ambiguous',))])
    hid = signature_verdict(d, [_cand('void(int)', 1, 'void', [], grade='B',
                                      features=('hidden_param_suspicion',),
                                      lower_bound=True)])
    assert sret.status == hid.status == SIG_OK, (sret, hid)
    assert sret.waived != hid.waived
    assert sret.grade == hid.grade == 'B'


def test_ruling2_hidden_param_suspicion_does_not_accept_arity_below():
    """负例：hidden_param_suspicion 只允许**更多**参数；声明比下界还少 ⇒ 仍是矛盾。"""
    d = _d('g', '()', 0x2000, ret='void')
    v = signature_verdict(d, [_cand('void(int,int)', 2, 'void', [], grade='B',
                                    features=('hidden_param_suspicion',), lower_bound=True)])
    assert v.status == SIG_CONTRADICTION and v.detail == 'arity_below_lower_bound'


def test_ruling2_sret_ambiguous_keeps_param_class_checks_off():
    """sret_ambiguous 时参数整体可能错位一位 ⇒ 参数类检查也必须放宽（否则假矛盾）。"""
    d = _d('g', '(double)', 0x2000, ret='void')
    v = signature_verdict(d, [_cand('void(int)', 1, 'void', [_p(1, ('f32',))],
                                    grade='B', features=('sret_ambiguous',))])
    assert v.status == SIG_OK, v


def test_ruling2_determined_sret_return_is_checked_not_waived():
    """`sret`（**已判定** >8B 结构返回，非 ambiguous）只豁免 arity/params，**return 仍校验**：
    声明 `void` 与 sret 是实打实的矛盾；声明按值结构体则宽度不可判（不作判据）。"""
    cand = _cand('void(int)', 1, 'sret(>8B)', [], grade='B', features=('sret',))
    bad = signature_verdict(_d('g', '(int)', 0x2000, ret='void'), [cand])
    assert bad.status == SIG_CONTRADICTION and bad.detail == 'return_mismatch', bad
    ok = signature_verdict(_d('g', '(int)', 0x2000, ret='tagRECT'), [cand])
    assert ok.status == SIG_OK, ok


def test_signature_weak_and_contradiction_mixed_candidates_pick_contradiction():
    """回归守卫：弱候选在前、矛盾候选在后时，必须给出**矛盾**（旧实现此处索引越界）。"""
    d = _d('g', '()', 0x2000, ret='int')
    v = signature_verdict(d, [
        _cand('?()', None, 'unknown', [], grade='C'),          # 什么都没判定
        _cand('int(int)', 1, 'i32', [_p(1, ('i32',))], grade='A'),   # arity 矛盾
    ])
    assert v.status == SIG_CONTRADICTION and v.detail == 'arity_mismatch', v


# ================= 10. Ruling 5：基准独立于 methods 表 =================

def test_ruling5_methods_table_not_consulted():
    """Ruling 5：校验基准是编译产物（`vtables[].slots` + 生成头），不是 methods 表。
    把 methods 表改成与 vtable 完全矛盾，判定必须逐字不变。"""
    decls = {'C': _cd('C', [_d('f', '', 0x1000)])}
    plain = _struct_json('C', [(0x56A000, None, [0x1000])])
    poisoned = dict(plain)
    poisoned['methods'] = {'0x001000': {'name': 'NOT_f', 'signature': 'void __cdecl()'},
                           '0x009999': {'name': 'ghost', 'signature': 'int()'}}
    r1 = check_all(decls, _views_of(plain))
    r2 = check_all(decls, _views_of(poisoned))
    assert r1.classes['C'].slot_health == r2.classes['C'].slot_health == 1.0
    assert build_baseline(r1)['classes']['C'] == build_baseline(r2)['classes']['C']


def test_ruling5_checker_never_reads_struct_methods_key():
    """静态守卫：本工具的 JSON 读取器不得触碰 `methods` 键（同源自比的入口）。"""
    import vtable_decl_check as m
    src = Path(m.__file__).read_text(encoding='utf-8')
    assert "['methods']" not in src and '["methods"]' not in src
    assert 'methods_pending' in src          # Task 3 旁路是**唯一**签名证据入口


def _views_of(struct):
    """struct dict → {cls: [BinaryView...]}（复用装载器的解析口径）。"""
    from vtable_decl_check import struct_to_views
    return {struct['name']: struct_to_views(struct)}


# ================= 11. 棘轮三态 =================

def _grow_fixture():
    """一个声明齐全的类（health 1.0）与一个缺声明的类（health 0.5）。"""
    decls = {'Good': _cd('Good', [_d('f', '', 0x1000)]),
             'Bad': _cd('Bad', [_d('f', '', 0x4000)])}
    structs = {'Good': [BinaryView(0x56A000, None, (0x1000,))],
               'Bad': [BinaryView(0x56B000, None, (0x4000, 0x4010))]}
    return decls, structs


def test_ratchet_improved_passes_and_updates_baseline():
    decls, structs = _grow_fixture()
    base = build_baseline(check_all(decls, structs))
    assert base['classes']['Bad']['slot_health'] == 0.5
    fixed = dict(decls)
    fixed['Bad'] = _cd('Bad', [_d('f', '', 0x4000), _d('g', '', 0x4010)])
    cur = build_baseline(check_all(fixed, structs))
    d = ratchet_decide(base, cur)
    assert d.passed is True and d.improved is True and d.blocked is False
    assert d.updated is not None
    assert d.updated['classes']['Bad']['slot_health'] == 1.0
    assert d.updated != base


def test_ratchet_same_passes_without_update():
    decls, structs = _grow_fixture()
    base = build_baseline(check_all(decls, structs))
    cur = build_baseline(check_all(decls, structs))
    d = ratchet_decide(base, cur)
    assert d.passed is True and d.improved is False and d.updated is None
    assert all(c.status == 'same' for c in d.components), d.components


def test_ratchet_decrease_blocks():
    """变异：删掉一个声明 ⇒ health 1.0 → 0.5 ⇒ 必须阻塞。"""
    decls, structs = _grow_fixture()
    base = build_baseline(check_all(decls, structs))
    broken = {'Good': _cd('Good', []), 'Bad': decls['Bad']}
    cur = build_baseline(check_all(broken, structs))
    d = ratchet_decide(base, cur)
    assert d.passed is False and d.blocked is True and d.updated is None
    bad = [c for c in d.components if c.status == 'down']
    assert any(c.klass == 'Good' and c.metric == 'slot_health' for c in bad), d.components


def test_ratchet_per_class_decrease_blocks_even_if_overall_improves():
    """整体上升不能掩盖单类下降（health 是**按类**定义的）。"""
    decls = {'A': _cd('A', [_d('f', '', 0x1000)]), 'B': _cd('B', [])}
    structs = {'A': [BinaryView(0x56A000, None, (0x1000,))],
               'B': [BinaryView(0x56B000, None, (0x5000, 0x5010, 0x5020))]}
    base = build_baseline(check_all(decls, structs))
    assert base['classes']['A']['slot_health'] == 1.0
    assert base['classes']['B']['slot_health'] == 0.0
    # B 大改善（0→1），A 下降（1.0→1/3：二进制多出两个未声明槽）⇒ 整体上升但必须阻塞
    structs2 = {'A': [BinaryView(0x56A000, None, (0x1000, 0x1010, 0x1020))],
                'B': structs['B']}
    fixed = {'A': decls['A'],
             'B': _cd('B', [_d('f', '', 0x5000), _d('g', '', 0x5010), _d('h', '', 0x5020)])}
    cur = build_baseline(check_all(fixed, structs2))
    assert cur['classes']['B']['slot_health'] == 1.0
    assert cur['classes']['A']['slot_health'] < 1.0
    assert cur['overall']['slot_health'] > base['overall']['slot_health']
    d = ratchet_decide(base, cur)
    assert d.blocked is True
    assert any(c.klass == 'A' and c.status == 'down' for c in d.components)


def test_ratchet_missing_class_blocks():
    decls, structs = _grow_fixture()
    base = build_baseline(check_all(decls, structs))
    cur = build_baseline(check_all({'Good': decls['Good']},
                                   {'Good': structs['Good']}))
    d = ratchet_decide(base, cur)
    assert d.blocked is True
    assert any(c.status == 'missing' and c.klass == 'Bad' for c in d.components)


def test_ratchet_model_switch_is_incomparable_not_a_verdict():
    """模型切换（flat ↔ chain）会让全部分量不可比 ⇒ 必须显式说"没做对比"，
    既不得假装放行（假绿），也不得误报阻塞（假红）。"""
    decls = _mi_fixture()
    views = [BinaryView(0x56A000, 'A', (0x3000, 0x1010, 0x3020)),
             BinaryView(0x56A020, 'B', (0x3010, 0x2010))]
    flat = build_baseline(check_all(decls, {'D': views}, model=MODEL_FLAT))
    chain = build_baseline(check_all(decls, {'D': views}, model=MODEL_CHAIN))
    assert flat['overall']['model'] == 'flat' and chain['overall']['model'] == 'chain'
    d = ratchet_decide(flat, chain)
    assert d.comparison == 'model_changed'
    assert d.blocked is False and d.components == ()
    assert any('模型不一致' in n for n in d.notes), d.notes


def test_ratchet_new_class_is_not_a_regression():
    decls, structs = _grow_fixture()
    base = build_baseline(check_all({'Good': decls['Good']}, {'Good': structs['Good']}))
    cur = build_baseline(check_all(decls, structs))
    d = ratchet_decide(base, cur)
    assert d.passed is True
    assert any(c.status == 'new' and c.klass == 'Bad' for c in d.components)


def test_ratchet_signature_health_decrease_blocks_without_slot_change():
    """签名棘轮单独有牙：槽序/槽数不变，只把 A 级证据改成矛盾 ⇒ sig_health 下降 ⇒ 阻塞。"""
    cd = _cd('C', [_d('g', '(int)', 0x2000, ret='int')])
    views = [BinaryView(0x56A000, None, (0x2000,))]
    ok = _pending({'0x2000': {'candidates': [_cand('int(int)', 1, 'i32', [_p(1, ('i32',))])]}})
    bad = _pending({'0x2000': {'candidates': [_cand('int()', 0, 'i32', [])]}})
    base = build_baseline(check_all({'C': cd}, {'C': views}, pending=ok))
    cur = build_baseline(check_all({'C': cd}, {'C': views}, pending=bad))
    assert base['classes']['C']['slot_health'] == cur['classes']['C']['slot_health'] == 1.0
    assert base['classes']['C']['sig_health'] == 1.0
    assert cur['classes']['C']['sig_health'] == 0.0
    d = ratchet_decide(base, cur)
    assert d.blocked is True
    assert any(c.metric == 'sig_health' and c.status == 'down' for c in d.components)


def test_ratchet_zero_verified_does_not_block_no_hard_gate():
    """**禁止硬门禁**（v1/v2 死锁根因）：0 已验证 / 未解析槽多，**不**阻塞 ——
    v2 规格曾把不等号写反（"未解析 < 阈值 ⇒ 阻塞"）⇒ 0 未解析反而阻塞。
    本测试钉死：health=0 的类只要不**下降**就放行。"""
    decls = {'C': _cd('C', [])}
    structs = {'C': [BinaryView(0x56A000, None, (0x1000, 0x1010))]}
    base = build_baseline(check_all(decls, structs))
    assert base['classes']['C']['slot_health'] == 0.0
    d = ratchet_decide(base, build_baseline(check_all(decls, structs)))
    assert d.passed is True and d.blocked is False
    # 也不存在"未解析比例阈值"这类参数
    import inspect
    assert 'threshold' not in inspect.signature(ratchet_decide).parameters


def test_ratchet_baseline_roundtrips_json():
    decls, structs = _grow_fixture()
    base = build_baseline(check_all(decls, structs))
    again = json.loads(json.dumps(base))
    assert again == base
    d = ratchet_decide(again, again)
    assert d.passed is True


# ================= 12. 报告与确定性 =================

def test_render_report_mentions_three_check_items_and_health():
    decls, structs = _grow_fixture()
    res = check_all(decls, structs)
    txt = render_report(res)
    assert '槽数' in txt and '槽序' in txt and '签名' in txt
    assert 'health' in txt
    assert 'Bad' in txt


def test_check_all_is_deterministic():
    decls, structs = _grow_fixture()
    a = json.dumps(build_baseline(check_all(decls, structs)), sort_keys=True)
    b = json.dumps(build_baseline(check_all(decls, structs)), sort_keys=True)
    assert a == b


def test_check_result_shape():
    decls, structs = _grow_fixture()
    res = check_all(decls, structs)
    assert isinstance(res, CheckResult)
    assert set(res.classes) == {'Good', 'Bad'}
    assert set(res.views) == {'Good', 'Bad'}
    assert isinstance(res.classes['Good'], ClassHealth)
    assert isinstance(res.views['Good'][0], ViewCheck)
    assert isinstance(res.views['Good'][0].slots[0], SlotResult)
    assert res.stats['slots_total'] == 3
    assert res.stats['classes'] == 2


# ================= 13. CLI =================

class TestCli(_Tmp):

    def _fixture(self):
        self.write('decls/C.h', _header('C', [_decl_line('void', 'f', '', 0x1000)]))
        self.write('structs/C.json', json.dumps(_struct_json('C', [(0x56A000, None, [0x1000])])))
        return ('--decls', str(self.tmp / 'decls'), '--structs', str(self.tmp / 'structs'))

    def test_cli_first_run_reports_health(self):
        args = self._fixture()
        rc = main(list(args) + ['--json', str(self.tmp / 'r.json')])
        assert rc == 0
        rep = json.loads((self.tmp / 'r.json').read_text(encoding='utf-8'))
        assert rep['overall']['slot_health'] == 1.0

    def test_cli_writes_baseline_only_with_flag(self):
        args = self._fixture()
        bl = self.tmp / 'base.json'
        assert main(list(args) + ['--baseline', str(bl)]) == 0
        assert not bl.exists()                       # 未给 --write-baseline ⇒ 不落盘
        assert main(list(args) + ['--baseline', str(bl), '--write-baseline']) == 0
        assert bl.exists()

    def test_cli_blocks_on_regression_exit_1(self):
        args = self._fixture()
        bl = self.tmp / 'base.json'
        assert main(list(args) + ['--baseline', str(bl), '--write-baseline']) == 0
        # 删掉声明 ⇒ health 1.0 → 0.0
        self.write('decls/C.h', _header('C', []))
        rc = main(list(args) + ['--baseline', str(bl)])
        assert rc == 1

    def test_cli_refuses_to_write_inside_annotations(self):
        args = self._fixture()
        rc = main(list(args) + ['--baseline', 'data/annotations/structs/_nope.json',
                                '--write-baseline'])
        assert rc == 2

    def test_cli_usage_error_on_missing_inputs(self):
        assert main(['--decls', str(self.tmp / 'nope'), '--structs', str(self.tmp / 'nope2')]) == 2


# ================= 14. 真实数据锚点 =================

def test_real_headers_parse():
    decls = load_decl_dir(REAL_DECLS)
    assert len(decls) >= 60, len(decls)
    # 生成头里的地址注释形如 `// 0x445e70`；CUtil 是 7 槽单继承样本
    assert 'CUtil' in decls
    assert len(decls['CUtil'].decls) == 7
    assert decls['CUtil'].decls[0].addr == 0x445E70


def test_real_structs_load_all_slots():
    structs = load_structs_dir(REAL_STRUCTS)
    assert len(structs) >= 70, len(structs)
    total = sum(len(v.slot_addrs) for vs in structs.values() for v in vs)
    assert total == 841, total          # 与 data/status/vtable_baseline.json 的 total_slots 一致


def test_real_data_check_runs_and_reports_nonvacuous_health():
    decls = load_decl_dir(REAL_DECLS)
    structs = load_structs_dir(REAL_STRUCTS)
    res = check_all(decls, structs)
    hs = [h.slot_health for h in res.classes.values()]
    assert len(hs) >= 50, len(hs)
    mean = sum(hs) / len(hs)
    # 判别力下界/上界：不能恒 1（无判别力）也不能恒 0（度量已死）
    assert 0.4 <= mean <= 0.95, mean
    assert sum(1 for h in hs if h == 1.0) >= 10
    assert sum(1 for h in hs if h == 0.0) >= 1


def test_real_data_ceffectsystem_known_order_mismatch_is_reported():
    """实测真差异：CEffectSystem 生成头把 `0x4C6260` 排在槽 1，二进制排在最后 ⇒
    必须报 order_mismatch（若这条不报，说明 §2 槽序校验对真实数据失效）。"""
    decls = load_decl_dir(REAL_DECLS)
    structs = load_structs_dir(REAL_STRUCTS)
    res = check_all(decls, structs)
    assert 'CEffectSystem' in res.views
    slots = [s for v in res.views['CEffectSystem'] for s in v.slots]
    assert any(s.order == ORDER_MISMATCH for s in slots), slots
    assert all(s.order != ORDER_UNDECLARED for s in slots)
    assert res.classes['CEffectSystem'].slot_health < 1.0


def test_real_data_deterministic_output():
    decls = load_decl_dir(REAL_DECLS)
    structs = load_structs_dir(REAL_STRUCTS)
    a = json.dumps(build_baseline(check_all(decls, structs)), sort_keys=True)
    b = json.dumps(build_baseline(check_all(decls, structs)), sort_keys=True)
    assert a == b


def test_ruling3_end_to_end_mixed_case_pending_keys():
    """Ruling 3 端到端：同一份 `methods_pending` 里大写键（Task 3 产出）与小写键
    （真实注解形态）混用时，两侧都必须命中签名证据。"""
    decls = {'C': _cd('C', [_d('f', '', 0x1000, ret='int'),
                            _d('g', '(int)', 0x2000, ret='int')])}
    structs = {'C': [BinaryView(0x56A000, None, (0x1000, 0x2000))]}
    pending = {
        '0x00001000': {'candidates': [_cand('int()', 0, 'i32')]},                 # 小写
        '0x00002000': {'candidates': [_cand('int(int)', 1, 'i32', [_p(1, ('i32',))])]},  # 小写
    }
    res = check_all(decls, structs, pending=load_pending(pending))
    assert res.classes['C'].sig_checked == 2, res.classes['C']
    assert res.classes['C'].sig_ok == 2
    assert res.classes['C'].sig_health == 1.0


class TestRealDataMutation(_Tmp):
    """**真实数据变异测试**：拿真实生成头（CUtil.h）与真实二进制表做基线，
    再对真实声明做极小变异 ⇒ 断言必须报警 + 棘轮必须阻塞（合成夹具之外的判别力证据）。"""

    def _real_header_and_views(self, cls='CUtil'):
        src = next(iter(sorted(REAL_DECLS.rglob('%s.h' % cls))))
        target = self.tmp / ('%s.h' % cls)
        target.write_text(src.read_text(encoding='utf-8', errors='replace'), encoding='utf-8')
        views = load_structs_dir(REAL_STRUCTS)[cls]
        return target, views

    def test_real_header_baseline_is_full_health(self):
        _p, views = self._real_header_and_views()
        res = check_all(load_decl_dir(self.tmp), {'CUtil': views})
        assert res.classes['CUtil'].slot_health == 1.0, res.classes['CUtil']
        assert res.classes['CUtil'].count_ok is True
        assert res.classes['CUtil'].n_slots == 7

    def test_mutation_swap_two_real_decl_addresses_blocks_ratchet(self):
        target, views = self._real_header_and_views()
        base = build_baseline(check_all(load_decl_dir(self.tmp), {'CUtil': views}))
        txt = target.read_text(encoding='utf-8')
        # 交换前两条 virtual 声明的地址注释（0x445e70 ↔ 0x00523670）
        assert '0x445e70' in txt and '0x00523670' in txt
        txt = txt.replace('0x445e70', '0xTMP').replace('0x00523670', '0x445e70')
        target.write_text(txt.replace('0xTMP', '0x00523670'), encoding='utf-8')
        res = check_all(load_decl_dir(self.tmp), {'CUtil': views})
        assert res.classes['CUtil'].slot_health < 1.0        # 交换只损伤这两个位置（局部化）
        assert res.classes['CUtil'].n_order_ok == 5          # 7 槽中 2 个错位
        d = ratchet_decide(base, build_baseline(res))
        assert d.blocked is True
        assert any(c.metric == 'slot_health' and c.status == 'down' for c in d.components)

    def test_mutation_delete_one_real_decl_blocks_ratchet(self):
        target, views = self._real_header_and_views()
        base = build_baseline(check_all(load_decl_dir(self.tmp), {'CUtil': views}))
        txt = target.read_text(encoding='utf-8')
        line = [l for l in txt.splitlines() if 'WriteLog' in l][0]
        target.write_text('\n'.join(l for l in txt.splitlines() if l != line) + '\n',
                          encoding='utf-8')
        res = check_all(load_decl_dir(self.tmp), {'CUtil': views})
        assert res.classes['CUtil'].slot_health < 1.0
        assert any('无声明' in f for f in res.classes['CUtil'].findings), res.classes['CUtil'].findings
        assert ratchet_decide(base, build_baseline(res)).blocked is True


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
    for nm, cls in sorted(list(globals().items())):
        if nm.startswith('Test') and isinstance(cls, type) and issubclass(cls, unittest.TestCase):
            for mn in sorted(dir(cls)):
                if mn.startswith('test_'):
                    inst = cls(mn)
                    try:
                        inst.setUp(); getattr(inst, mn)()
                        inst.tearDown(); print('  PASS %s.%s' % (nm, mn)); ok += 1
                    except unittest.SkipTest as e:
                        print('  SKIP %s.%s: %s' % (nm, mn, e)); skip += 1
                    except Exception as e:
                        print('  FAIL %s.%s: %s: %s' % (nm, mn, type(e).__name__, e)); fail += 1
    print('Results: %d passed, %d failed, %d skipped' % (ok, fail, skip))
    sys.exit(1 if fail else 0)