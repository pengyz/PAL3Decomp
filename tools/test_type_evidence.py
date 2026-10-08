#!/usr/bin/env python3
"""tools/type_evidence.py + tools/apply_annotation_batch.py(type_change) 的契约测试
（自带 __main__ runner，不依赖 pytest——gotcha_local_pytest_collect_crashes_use_self_runner）。

断言**契约**而非现状（gotcha_tests_must_assert_contract_not_status_quo），
且契约必须穿过**集成缝**（2026-09-27 复核 D12/F12 教训：16 条单测全绿但 scan_t1
偏移基错位 100% 假阴性——单缓冲自洽 fixture 恰好掩盖了 blob/file 基错位）：
- classify_insn：fi*=整型内存操作数（D3）、lea/imm=addr（F6）、setcc 不证符号（F10）、
  op_size=0 ⇒ unknown（F15）。
- decode_refs_at：偏移基同源（D1）、错位解码不作证据（D2）、[reg+disp] 不作绝对证据（F4）、
  mem 优先于巧合 imm（F5）、歧义不作证据。
- propose：D4 浮点证据优先（mov 触碰兼容、整型运算冲突）、double 禁填、unknown 混入冲突、
  WIDTH-4-MATCHED（D10）。
- 守卫 type_change：evidence 硬约束、防陈旧批次、**原字节风格保持**（F8）。
"""
import json
import os
import shutil
import struct
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools.type_evidence import (  # noqa: E402
    FILLABLE, Ref, classify_insn, decode_refs_at, emit_batch, load_candidates,
    parse_member_key, propose, scan_t2,
)

VA = 0x00C05B10


def _ref(kind, size, sign=None, mnem='mov'):
    return Ref(0x1000, 0x401000, mnem, 'x', size, kind, sign)


def _decode(machine_code, target_va, hit_off=0, boundaries=None):
    import capstone
    from capstone import x86 as cs_x86
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    text_va = 0x401000
    return decode_refs_at(machine_code, text_va, hit_off, target_va, md,
                          (cs_x86.X86_OP_MEM, cs_x86.X86_OP_IMM), boundaries=boundaries)


# ---------------------------------------------------------------- classify_insn

def test_classify_insn():
    assert classify_insn('fld', 4) == ('float', None)
    assert classify_insn('fstp', 4) == ('float', None)
    assert classify_insn('fld', 8) == ('double', None)
    assert classify_insn('fild', 4) == ('int', None)          # int32 入 x87
    assert classify_insn('movss', 4) == ('float', None)
    assert classify_insn('movsd', 8) == ('double', None)
    assert classify_insn('mov', 4) == ('int', None)
    assert classify_insn('movzx', 1, is_imm=False) == ('int', 'unsigned')
    assert classify_insn('movsx', 1, is_imm=False) == ('int', 'signed')
    assert classify_insn('mov', 4, is_imm=True) == ('addr', None)   # 地址物化不参与定型
    assert classify_insn('fld', 10) == ('unknown', None)      # tbyte 不证
    assert classify_insn('fadd', 4) == ('float', None)


def test_classify_fi_is_int():
    # D3：fi* 读**整型**内存（曾给 gbGfxDriverInfo.width 造出 16 个假 float 站点）
    assert classify_insn('fiadd', 4) == ('int', None)
    assert classify_insn('fidiv', 4) == ('int', None)
    assert classify_insn('fimul', 8) == ('int', None)
    assert classify_insn('ficom', 2) == ('int', None)
    assert classify_insn('fisub', 4) == ('int', None)


def test_classify_cvt_and_setcc():
    # F10：cvtt* 读浮点内存；cvtsi2* 读整型内存；setcc 不证符号位（只证 1 字节写）
    assert classify_insn('cvttss2si', 4) == ('float', None)
    assert classify_insn('cvttsd2si', 8) == ('double', None)
    assert classify_insn('cvtsi2ss', 4) == ('int', None)
    assert classify_insn('sete', 1) == ('int', None)
    assert classify_insn('setne', 1) == ('int', None)


def test_classify_lea_is_addr_and_size0_unknown():
    assert classify_insn('lea', 4) == ('addr', None)          # F6：lea 是地址物化
    assert classify_insn('mov', 0) == ('unknown', None)       # F15：宽度未知不冒充 4B


# ---------------------------------------------------------------- decode_refs_at

def test_decode_disp_operand():
    # mov eax, [0xC05B10]  = A1 10 5B C0 00（disp 就是操作数本身）
    code = b'\xA1' + struct.pack('<I', VA)
    ref, n = _decode(code + b'\x90' * 8, VA, hit_off=1)
    assert ref is not None, 'disp 命中必须解出承载指令'
    assert ref.note == 'disp' and ref.kind == 'int' and ref.op_size == 4
    assert ref.insn_va == 0x401000
    assert n == 1, '边界内承载必须唯一（n 要如实上报）'


def test_decode_imm_materialization_is_addr():
    # push 0xC05B10 = 68 10 5B C0 00 ⇒ 地址物化，kind='addr'
    code = b'\x68' + struct.pack('<I', VA)
    ref, n = _decode(code + b'\x90' * 8, VA, hit_off=1)
    assert ref is not None and ref.kind == 'addr', 'imm 物化必须标 addr'


def test_decode_byte_store_width():
    # mov byte ptr [0xC05B10], 1 = C6 05 10 5B C0 00 01 ⇒ 宽度 1
    # （start=1 另有 add eax,imm32 同覆盖 ⇒ 必须给真实指令边界，D2）
    code = b'\xC6\x05' + struct.pack('<I', VA) + b'\x01'
    ref, n = _decode(code + b'\x90' * 8, VA, hit_off=2, boundaries={0x401000})
    assert ref is not None and ref.op_size == 1, 'byte ptr 必须证出宽度 1'


def test_decode_coincidental_bytes_rejected():
    # 巧合字节：10 5B C0 00 跨越 push 0x10 / pop ebx / rol byte ptr [eax],0
    # 三条指令的边界 ⇒ 不存在覆盖 [h,h+4) 且操作数 == 目标值的承载指令
    code = b'\x6A\x10\x5B\xC0\x00\x00' + b'\x90' * 16
    ref, n = _decode(code, VA, hit_off=1)
    assert ref is None, '巧合字节不得成为证据'


def test_decode_base_register_rejected():
    # F4：mov ecx, [ecx+0xC05B10] = 8B 81 <disp> ⇒ [reg+disp] 不是绝对地址证据
    code = b'\x8B\x81' + struct.pack('<I', VA) + b'\x90' * 8
    ref, n = _decode(code, VA, hit_off=2)
    assert ref is None, '[reg+disp] 的 disp==VA 不构成绝对地址证据'


def test_decode_lea_is_addr():
    code = b'\x8D\x05' + struct.pack('<I', VA) + b'\x90' * 8
    ref, n = _decode(code, VA, hit_off=2, boundaries={0x401000})
    assert ref is not None and ref.kind == 'addr', 'lea 只证地址'


def test_decode_mem_wins_over_coincident_imm():
    # F5：mov dword ptr [VA], VA = C7 05 <disp32> <imm32> —— mem 侧才是宽度证据
    code = b'\xC7\x05' + struct.pack('<I', VA) * 2 + b'\x90' * 8
    ref, n = _decode(code, VA, hit_off=2, boundaries={0x401000})
    assert ref is not None and ref.kind != 'addr' and ref.op_size == 4, \
        'mem 命中必须压过巧合 imm（否则宽度证据被 addr 覆盖）'


def test_decode_ambiguous_and_boundary():
    # D2/F5：8B 05 <VA>（mov eax,[VA]，起点 0）与 05 <VA>（add eax,VA，起点 1）
    # 都覆盖 [2,5)：无边界 = 歧义 ⇒ 不作证据；有边界 ⇒ 只认边界上的解码
    code = b'\x8B\x05' + struct.pack('<I', VA) + b'\x90' * 8
    ref, n = _decode(code, VA, hit_off=2)
    assert ref is None and n >= 2, '多解码歧义不得作证据（曾被"最早者优先"伪解码抢占）'
    ref, n = _decode(code, VA, hit_off=2, boundaries={0x401000})
    assert ref is not None and ref.insn_va == 0x401000 and ref.op_size == 4, \
        '边界过滤后必须取边界上的真承载'
    ref, n = _decode(code, VA, hit_off=2, boundaries={0x401001})
    assert ref is not None and ref.insn_va == 0x401001 and ref.kind == 'addr'


def test_chain_movzx_byte_to_unsigned_char():
    # 端到端证据链（SIGN 正则 → decode → propose 联调，D12 缺口）
    code = b'\x0F\xB6\x05' + struct.pack('<I', VA) + b'\x90' * 8   # movzx eax, byte ptr [VA]
    ref, n = _decode(code, VA, hit_off=3, boundaries={0x401000})
    assert (ref.kind, ref.op_size, ref.sign) == ('int', 1, 'unsigned')
    assert propose([ref, ref])[0:2] == ('unsigned char', 'A')


# ---------------------------------------------------------------- propose 分级

def test_propose_float():
    refs = [_ref('float', 4, mnem='fld'), _ref('float', 4, mnem='fstp')]
    p, g, _ = propose(refs)
    assert (p, g) == ('float', 'A')


def test_propose_float_single_site_is_B():
    p, g, _ = propose([_ref('float', 4, mnem='fld')])
    assert (p, g) == ('float', 'B'), '单站点只报不落盘'


def test_propose_float_plus_int_move_compatible():
    # D4 裁决（推翻旧契约"float+int 混用一律 C"——实测该规则误杀 3 个已确证 float）：
    # mov/清零/比较的 dword **触碰**与浮点族兼容
    refs = [_ref('float', 4, mnem='fld'), _ref('float', 4, mnem='fstp'),
            _ref('int', 4, mnem='mov')]
    p, g, _ = propose(refs)
    assert (p, g) == ('float', 'A'), 'float 成员几乎总被 mov 触碰，不得误判冲突'


def test_propose_float_plus_int_op_conflict():
    # 真冲突 = 整型运算（fild/fi*/算术）与浮点族同槽（fild/fist vs fld/fstp）
    refs = [_ref('float', 4, mnem='fld'), _ref('float', 4, mnem='fstp'),
            _ref('int', 4, mnem='fild')]
    p, g, _ = propose(refs)
    assert p is None and g == 'C'


def test_propose_float_double_mixed_conflict():
    p, g, _ = propose([_ref('float', 4, mnem='fld'), _ref('double', 8, mnem='fstp')])
    assert p is None and g == 'C', 'float 与 double 同槽必须冲突'


def test_propose_double_never_filled():
    # A-D4/A 疑点 5：double 提案只报告（布局高危 4→8），emit 层禁落盘
    refs = [_ref('double', 8, mnem='fstp'), _ref('double', 8, mnem='fld'),
            _ref('int', 4, mnem='mov')]
    p, g, _ = propose(refs)
    assert (p, g) == ('double', 'A'), 'mov 触碰与 double 兼容，提案照出'
    assert 'double' not in FILLABLE, 'double v1 禁填（emit_batch/守卫双重拦截）'


def test_propose_unknown_counts_in_conflict():
    # F11：kind=unknown 站点混入 ⇒ 未理解的证据不落盘
    refs = [_ref('float', 4, mnem='fld'), _ref('float', 4, mnem='fld'),
            _ref('unknown', 10, mnem='fld')]
    p, g, _ = propose(refs)
    assert p is None and g == 'C'


def test_propose_int_matched_label():
    # D10：4B 只证宽度不证 int（实测 SSD.m_pCurrentBlock 是 char* 却曾被标 INT-MATCHED）
    refs = [_ref('int', 4), _ref('int', 4)]
    p, g, notes = propose(refs)
    assert p is None and g == 'A' and notes[-1] == 'WIDTH-4-MATCHED', \
        '4B 整型 = 宽度已正确，不得产生填充，也不得自称"int 已正确"'


def test_propose_byte_sign_required():
    signed = [_ref('int', 1, 'signed', 'movsx'), _ref('int', 1, 'signed', 'movsx')]
    assert propose(signed)[0:2] == ('char', 'A')
    unsigned = [_ref('int', 1, 'unsigned', 'movzx'), _ref('int', 1, 'unsigned', 'movzx')]
    assert propose(unsigned)[0:2] == ('unsigned char', 'A')
    nosign = [_ref('int', 1), _ref('int', 1)]
    p, g, _ = propose(nosign)
    assert p is None and g == 'B', '符号位不可证不得填 byte 类型'


def test_propose_word():
    assert propose([_ref('int', 2, 'signed', 'movsx'), _ref('int', 2, 'signed', 'movsx')])[0:2] \
        == ('short', 'A')
    assert propose([_ref('int', 2, 'unsigned', 'movzx'), _ref('int', 2, 'unsigned', 'movzx')])[0:2] \
        == ('unsigned short', 'A')


def test_propose_multiwidth_conflict():
    p, g, _ = propose([_ref('int', 4), _ref('int', 1)])
    assert p is None and g == 'C'


def test_propose_addr_only_needs_t2():
    refs = [_ref('addr', 4, mnem='mov')]
    p, g, _ = propose(refs, {'sites': 3, 'hints': {}})
    assert p is None and g == 'B', '地址物化不构成宽度证据'
    p, g, _ = propose(refs)
    assert p is None and g == '0'


def test_propose_empty():
    assert propose([])[0:2] == (None, '0')


# ---------------------------------------------------------------- 键解析（D7）

def test_parse_member_key():
    assert parse_member_key('50814') == 50814
    assert parse_member_key('0x68C') == 0x68C
    assert parse_member_key('0x4C') == 0x4C
    assert parse_member_key('188_2') == 188
    assert parse_member_key('0x8') == 8


# ---------------------------------------------------------------- T2 佐证扫描

def test_scan_t2_combined_regex(tmpdir=None):
    d = tempfile.mkdtemp()
    try:
        body = 'v = aShock; *(float *)&aShock = f; q = *(_BYTE *)&aShock;'
        json.dump({'decompiled_c': body},
                  open(os.path.join(d, 'f.json'), 'w', encoding='utf-8'))
        out = scan_t2({0x1000: 'aShock', 0x2000: 'aBink'}, decomp_dir=d)
        assert out[0x1000]['sites'] == 3
        assert out[0x1000]['hints']['float'] >= 1 and out[0x1000]['hints']['byte'] >= 1
        assert 0x2000 not in out, '无渲染点的成员不得有 T2 槽'
    finally:
        shutil.rmtree(d)


def test_scan_t2_word_boundary():
    # D11：'m_nEff' 不得在 'm_nEffObjCount' 内计数（短名串扰 = 虚高投票）
    d = tempfile.mkdtemp()
    try:
        body = 'v = m_nEffObjCount; w = m_nEff; x = m_nEffObjCount;'
        json.dump({'decompiled_c': body},
                  open(os.path.join(d, 'f.json'), 'w', encoding='utf-8'))
        out = scan_t2({0x1000: 'm_nEff'}, decomp_dir=d)
        assert out.get(0x1000, {}).get('sites', 0) == 1, '词边界：只算独立渲染点'
    finally:
        shutil.rmtree(d)


# ---------------------------------------------------------------- 批次产出 + 守卫

def test_emit_batch_only_fillable_A():
    d = tempfile.mkdtemp()
    try:
        results = [
            {'cls': 'Foo', 'key': '16', 'offset': 16, 'cur_type': 'int', 'grade': 'A',
             'proposal': 'float', 't1': [{'insn_va': '0x00401234', 'op_str': 'fld dword ptr [x]'}]},
            {'cls': 'Foo', 'key': '20', 'offset': 20, 'cur_type': 'int', 'grade': 'A',
             'proposal': 'double', 't1': [{'insn_va': '0x00401240', 'op_str': 'fstp qword ptr [x]'}]},
            {'cls': 'Foo', 'key': '24', 'offset': 24, 'cur_type': 'int', 'grade': 'B',
             'proposal': 'float', 't1': [{'insn_va': '0x00401250', 'op_str': 'fld dword ptr [x]'}]},
        ]
        out = os.path.join(d, 'batch.json')
        n, _ = emit_batch(results, out)
        items = json.load(open(out, encoding='utf-8'))
        assert n == 1 and len(items) == 1, 'double 禁填 + B 级不落，只留 A 级可落盘提案'
        assert items[0]['new_type'] == 'float' and items[0]['kind'] == 'type_change'
        assert items[0]['evidence'].strip(), 'evidence 硬约束（守卫会拒空证据）'
    finally:
        shutil.rmtree(d)


def _run_guard(batch, ann_dir):
    import tools.apply_annotation_batch as gab
    old_argv, old_ann = sys.argv, gab.ANN
    old_call = gab.subprocess.call
    sys.argv = ['apply_annotation_batch.py', '--batch', batch]
    gab.ANN = ann_dir
    gab._STYLE = {}
    gab.subprocess.call = lambda *a, **k: 0   # 隔离内嵌 check 闸（HEAD 存量红与本测试无关）
    try:
        return gab.main()
    finally:
        sys.argv, gab.ANN, gab.subprocess.call = old_argv, old_ann, old_call


def test_guard_type_change_applies_and_preserves_style():
    # F8/D6：落盘走守卫、**原字节风格保持**（CRLF/indent2/无尾换行除 type/source 外全字节不变）
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {'16': {'name': 'm_a', 'type': 'int', 'source': 'x'}}}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2)
        text = text.replace('\n', '\r\n')            # CRLF、无尾换行（仓内多数派风格）
        open(p, 'w', encoding='utf-8', newline='').write(text)
        batch = [{'kind': 'type_change', 'class': 'Foo', 'key': '16', 'new_type': 'float',
                  'evidence': 'T1: 0x00401234 fld dword ptr [0x00C05B10]'}]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, d)
        assert rc == 0
        raw = open(p, 'rb').read()
        assert b'\r\n' in raw, 'CRLF 必须保持'
        assert not raw.endswith(b'\r\n') and not raw.endswith(b'\n'), '尾换行状态必须保持'
        got = json.loads(raw.decode('utf-8'))
        m = got['known_members']['16']
        assert m['type'] == 'float'
        assert 'type_change' in m['source'], 'source 必须留证据凭据'
    finally:
        shutil.rmtree(d)


def test_guard_rejects_empty_evidence():
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {'16': {'name': 'm_a', 'type': 'int', 'source': 'x'}}}
        p = os.path.join(d, 'Foo.json')
        json.dump(ann, open(p, 'w', encoding='utf-8'))
        before = open(p, 'rb').read()
        batch = [{'kind': 'type_change', 'class': 'Foo', 'key': '16', 'new_type': 'float',
                  'evidence': '   '}]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, d)
        assert rc == 1, '空 evidence 必须整批拒绝（硬约束 1）'
        assert open(p, 'rb').read() == before, '被拒批次不得落任何盘'
    finally:
        shutil.rmtree(d)


def test_guard_rejects_nonplaceholder_and_double():
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {
            '16': {'name': 'm_a', 'type': 'float', 'source': 'x'},   # 非占位
            '20': {'name': 'm_b', 'type': 'int', 'source': 'y'},
        }}
        p = os.path.join(d, 'Foo.json')
        json.dump(ann, open(p, 'w', encoding='utf-8'))
        before = open(p, 'rb').read()
        batch = [
            {'kind': 'type_change', 'class': 'Foo', 'key': '16', 'new_type': 'char',
             'evidence': 'T1: x'},                                    # 防覆盖已验证类型
            {'kind': 'type_change', 'class': 'Foo', 'key': '20', 'new_type': 'double',
             'evidence': 'T1: x'},                                    # double 禁填
        ]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, d)
        assert rc == 1
        assert open(p, 'rb').read() == before, '非占位覆盖/double 必须被拒且整批不写'
    finally:
        shutil.rmtree(d)


def test_decode_imm_float_bits_corroboration():
    # P1-4（复核 ff86c62f）：**任意** imm 操作数的 float 位型旁证必须真可产出。
    # 旧版只在 imm==目标地址时才看 ⇒ 全报告 0 行，验收表引用的是不存在的证据。
    code = bytes.fromhex('C7 05 10 5B C0 00 00 00 48 C2')   # mov d[0x00C05B10], 0xC2480000 (=-50.0f)
    ref, n = _decode(code, VA)
    assert ref is not None and n == 1
    assert 'float-bits' in (ref.note or ''), 'mov [mem], imm(-50.0f) 必须记浮点位型旁证'
    _, grade, notes = propose([ref], None)
    assert any('imm 位型像 float' in x for x in notes), '旁证必须表面化到 notes（P1-4）'
    code0 = bytes.fromhex('C7 05 10 5B C0 00 00 00 00 00')  # mov d[0x00C05B10], 0
    ref0, _ = _decode(code0, VA)
    assert ref0 is not None and 'float-bits' not in (ref0.note or ''), 'imm=0 不是浮点位型（反面）'


# ------------------------------------------------- P1-2/P1-3（复核 ff86c62f 2026-09-27）

def test_guard_write_phase_skip_rejects_whole_batch():
    # P1-2：写入阶段"静默跳过"必须计拒绝 ⇒ 整批不写（此前 [跳过]…continue 不计数 ⇒
    # 一条坏 rename 被丢、其余照常 flush、exit 0 = 部分落盘却报成功）。
    # 复核 5560c6c5 Q6①：fixture 必须用**可 round-trip 风格**（CRLF+indent2），
    # 否则被 P1-3 探测兜底拒 = 因错误原因通过（掩盖 P1-2 契约）。
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {'16': {'name': 'm_a', 'type': 'int', 'source': 'x'}},
               'methods': {'0x00401000': {'name': 'Ok', 'signature': 'void __thiscall Foo::Ok(Foo *this)'}}}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        before = open(p, 'rb').read()
        batch = [
            {'kind': 'type_change', 'class': 'Foo', 'key': '16', 'new_type': 'float',
             'evidence': 'T1: 0x00401234 fld dword ptr [0x00C05B10]'},       # 有效条目
            {'kind': 'rename', 'class': 'Foo', 'addr': '0x00409999',
             'new_name': 'Renamed', 'evidence': 'T1: x', 'name_evidence': 'PDB'},
                                                                       # 写入期才发现不存在
        ]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, d)
        assert rc == 1, '写入期跳过必须整批拒绝（P1-2 原子性）'
        assert open(p, 'rb').read() == before, '有效条目也不得落盘（全或无）'
    finally:
        shutil.rmtree(d)


def test_guard_same_file_multi_entry_chained():
    # P0（复核 5560c6c5）：同文件多条目必须**链式施加** —— 第 2 条 load 缓冲版。
    # 旧实现重读原盘覆盖缓冲 ⇒ 第 1 条静默丢失 + rc=0（B 批天然同文件多条目，致命）。
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {
            '16': {'name': 'm_a', 'type': 'int', 'source': 'x'},
            '20': {'name': 'm_b', 'type': 'int', 'source': 'y'},
            '24': {'name': 'm_c', 'type': 'int', 'source': 'z'},
        }}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        batch = [
            {'kind': 'type_change', 'class': 'Foo', 'key': '16', 'new_type': 'float',
             'evidence': 'T1: 0x00401234 fld dword ptr [0x00C05B10]'},
            {'kind': 'type_change', 'class': 'Foo', 'key': '20', 'new_type': 'char',
             'evidence': 'T1: 0x00401256 movzx byte ptr [0x00C05B14]'},
            {'kind': 'rename', 'class': 'Foo', 'addr': '0x00401000', 'new_name': 'Renamed',
             'evidence': 'T1: x', 'name_evidence': 'PDB',
             '_note': 'methods 为空时写入期拒绝——本条不入本契约'},
        ]
        # 本契约只验 type_change×2 同文件链式（rename 条目去掉，另测）
        batch = batch[:2]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, d)
        assert rc == 0
        got = json.loads(open(p, encoding='utf-8').read())
        assert got['known_members']['16']['type'] == 'float', '第 1 条不得被第 2 条覆盖（P0）'
        assert got['known_members']['20']['type'] == 'char', '第 2 条必须生效'
        assert got['known_members']['24']['type'] == 'int', '未触碰键不得变化'
    finally:
        shutil.rmtree(d)


def test_guard_add_method_existing_rejects():
    # P1-2 变体：add_method 撞既有 addr = 批次意图未达成 ⇒ 拒（不得静默当成功）。
    d = tempfile.mkdtemp()
    try:
        ann = {'methods': {'0x00401000': {'name': 'Old', 'signature': 'void Foo::Old()'}}}
        p = os.path.join(d, 'Foo.json')
        json.dump(ann, open(p, 'w', encoding='utf-8'))
        before = open(p, 'rb').read()
        batch = [{'kind': 'add_method', 'class': 'Foo', 'addr': '0x00401000',
                  'new_name': 'New', 'signature': 'void __thiscall Foo::New(Foo *this)',
                  'evidence': 'T1: 0x00401234 call'}]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, d)
        assert rc == 1, '已存在 ⇒ 拒'
        assert open(p, 'rb').read() == before
    finally:
        shutil.rmtree(d)


def test_guard_style_probe_rejects_unpreservable_style():
    # P1-3：原文件风格保不住（\uXXXX 转义谱系，Logger.json 同病）⇒ 整批不写，
    # 否则落盘=整文件重排版淹没 annotation_diff。
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {'16': {'name': 'm_\u2014x', 'type': 'int', 'source': 'x'}}}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=True, indent=2)   # \uXXXX 转义风格
        open(p, 'w', encoding='utf-8', newline='').write(text)
        before = open(p, 'rb').read()
        batch = [{'kind': 'type_change', 'class': 'Foo', 'key': '16', 'new_type': 'float',
                  'evidence': 'T1: 0x00401234 fld dword ptr [0x00C05B10]'}]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, d)
        assert rc == 1, '重序列化不等价必须整批拒（P1-3）'
        assert open(p, 'rb').read() == before
    finally:
        shutil.rmtree(d)


def test_guard_style_probe_rejects_inline_object_style():
    # P1-3 变体：inline 对象单行谱系（tagCam/tagCmdData/tagRoleTask 同病）。
    d = tempfile.mkdtemp()
    try:
        p = os.path.join(d, 'Foo.json')
        text = ('{\n "known_members": {\n'
                '  "16": { "type": "int", "name": "m_a", "source": "x" }\n }\n}')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        before = open(p, 'rb').read()
        batch = [{'kind': 'type_change', 'class': 'Foo', 'key': '16', 'new_type': 'float',
                  'evidence': 'T1: 0x00401234 fld dword ptr [0x00C05B10]'}]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, d)
        assert rc == 1, 'inline 对象风格保不住必须整批拒'
        assert open(p, 'rb').read() == before
    finally:
        shutil.rmtree(d)


def test_guard_style_probe_passes_indent1_crlf():
    # 测试盲区③：indent=1（PAL3.json 真实待写风格）+ CRLF + 无尾换行必须通过并落盘。
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {'16': {'name': 'm_a', 'type': 'int', 'source': 'x'}}}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=1).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        batch = [{'kind': 'type_change', 'class': 'Foo', 'key': '16', 'new_type': 'float',
                  'evidence': 'T1: 0x00401234 fld dword ptr [0x00C05B10]'}]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, d)
        assert rc == 0
        raw = open(p, 'rb').read()
        assert b'\r\n' in raw and not raw.endswith(b'\n'), 'indent1/CRLF/无尾必须保持'
        assert b'"type": "float"' in raw or b'"type":"float"' in raw.replace(b' ', b'') or b'float' in raw
    finally:
        shutil.rmtree(d)


def test_guard_type_change_key_format():
    # 复核 5560c6c5 Q4 纠向：key 允许**全部真实键形态**（dec/hex/N_N；实测 dec 9745/hex 51/N_N 4）。
    # 旧测试的 hex 负面是假契约（被"无成员键"兜底掩盖）——hex 负面/正面都用**真实存在的键**。
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {'50814_0': {'name': 'm_arr', 'type': 'int', 'source': 'x'}}}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        bp = os.path.join(d, 'batch.json')
        json.dump([{'kind': 'type_change', 'class': 'Foo', 'key': '50814_0', 'new_type': 'float',
                    'evidence': 'T1: 0x00401234 fld dword ptr [0x00C05B10]'}],
                  open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, d) == 0, 'N_N 数组后缀键必须接受'
        # hex 键正面：键真实存在于注解 ⇒ 必须接受（旧规则误拒 hex 会整批卡死 B 批）
        ann2 = {'known_members': {'0x10': {'name': 'm_h', 'type': 'int', 'source': 'x'}}}
        p2 = os.path.join(d, 'Bar.json')
        text2 = json.dumps(ann2, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p2, 'w', encoding='utf-8', newline='').write(text2)
        bp2 = os.path.join(d, 'batch2.json')
        json.dump([{'kind': 'type_change', 'class': 'Bar', 'key': '0x10', 'new_type': 'float',
                    'evidence': 'T1: 0x00401234 fld dword ptr [0x00C05B10]'}],
                  open(bp2, 'w', encoding='utf-8'))
        assert _run_guard(bp2, d) == 0, 'hex 键必须接受（真实键形态）'
        # 非法键形态负面：'16 20' 之类必须在**校验期**整批拒（不能靠写入期兜底）
        ann3 = {'known_members': {'16 20': {'name': 'm_bad', 'type': 'int', 'source': 'x'}}}
        p3 = os.path.join(d, 'Baz.json')
        text3 = json.dumps(ann3, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p3, 'w', encoding='utf-8', newline='').write(text3)
        before = open(p3, 'rb').read()
        bp3 = os.path.join(d, 'batch3.json')
        json.dump([{'kind': 'type_change', 'class': 'Baz', 'key': '16 20', 'new_type': 'float',
                    'evidence': 'T1: 0x00401234 fld dword ptr [0x00C05B10]'}],
                  open(bp3, 'w', encoding='utf-8'))
        assert _run_guard(bp3, d) == 1, '非法键形态必须整批拒'
        assert open(p3, 'rb').read() == before
    finally:
        shutil.rmtree(d)


def test_guard_rename_requires_nonempty_new_name():
    # 复核 5560c6c5 Q7a/b：写盘字段是 new_name —— 空串绕硬约束 3 落空名、缺失写入期 KeyError。
    # 校验与写盘必须同源（按"将被写的字段"查）。
    d = tempfile.mkdtemp()
    try:
        ann = {'methods': {'0x00401000': {'name': 'Old', 'signature': 'void Foo::Old()'}}}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        before = open(p, 'rb').read()
        bp = os.path.join(d, 'batch.json')
        json.dump([
            {'kind': 'rename', 'class': 'Foo', 'addr': '0x00401000', 'new_name': '',
             'evidence': 'T1: x', 'name_evidence': 'PDB'},              # 空名
        ], open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, d) == 1, '空 new_name 必须整批拒'
        bp2 = os.path.join(d, 'batch2.json')
        json.dump([
            {'kind': 'rename', 'class': 'Foo', 'addr': '0x00401000',
             'evidence': 'T1: x', 'name_evidence': 'PDB'},              # 缺 new_name（旧会 KeyError）
        ], open(bp2, 'w', encoding='utf-8'))
        assert _run_guard(bp2, d) == 1, '缺 new_name 必须校验期整批拒（不得写入期崩溃）'
        assert open(p, 'rb').read() == before
    finally:
        shutil.rmtree(d)


def test_float_bits_tightened_and_target_excluded():
    # C1（复核 75f6709b）：_float_bits 收紧（exp∈[0x20,0xEF]，旧 0<exp<0xFF 随机通过率 99.2%）
    # 与 imm==target 排除（地址物化位型不算旁证）各锁一判别。
    code_addr = bytes.fromhex('C7 05 10 5B C0 00 14 5B C0 00')  # mov d[0x00C05B10], 0x00C05B14(地址位型)
    ref, _ = _decode(code_addr, VA)
    assert ref is not None
    assert 'float-bits' not in (ref.note or ''), '地址位型 imm（exp=1）不得造浮点旁证（收紧）'
    code_self = bytes.fromhex('68 10 5B C0 00')                  # push 0x00C05B10（imm==目标）
    ref2, _ = _decode(code_self, VA)
    assert ref2 is not None
    assert 'float-bits' not in (ref2.note or ''), 'imm==目标=地址物化，位型不算旁证（排除）'


def test_guard_shift_offset_miss_rejects():
    # C1（复核 75f6709b M8）：shift_offset 的 from 不命中任何成员键 = 意图未达成 ⇒ 整批拒。
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {'16': {'name': 'm_a', 'type': 'int', 'source': 'x'}}}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        before = open(p, 'rb').read()
        bp = os.path.join(d, 'batch.json')
        json.dump([{'kind': 'shift_offset', 'class': 'Foo', 'from': 99, 'to': 100,
                    'evidence': 'T1: x'}], open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, d) == 1, 'from 不命中必须整批拒（不得空转报成功）'
        assert open(p, 'rb').read() == before
    finally:
        shutil.rmtree(d)


def test_guard_delete_member_applies_and_chains():
    # W2 幻影清理（c34f38aa A7）：delete_member 施加 + 与 type_change 同文件链式（P0 链）。
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {
            '4952': {'name': 'm_nRT2Buf0', 'type': 'int', 'source': 'auto:overlap_g_PAL3_at_+0x1358'},
            '4956': {'name': 'm_nRT2Buf1', 'type': 'int', 'source': 'x'},
            '20': {'name': 'm_keep', 'type': 'int', 'source': 'y'},
        }}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        batch = [
            {'kind': 'delete_member', 'class': 'Foo', 'key': '4952',
             'evidence': 'W1: phantom(static-block) 0x4C0F6C guard+atexit 三元组'},
            {'kind': 'type_change', 'class': 'Foo', 'key': '4956', 'new_type': 'float',
             'evidence': 'T1: 0x00401234 fld dword ptr [0x00C05B10]'},
        ]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, d)
        assert rc == 0
        got = json.loads(open(p, encoding='utf-8').read())
        assert '4952' not in got['known_members'], '幻影成员必须被删'
        assert got['known_members']['4956']['type'] == 'float', '同文件链式：第 2 条生效'
        assert got['known_members']['20']['type'] == 'int', '未触碰键不变'
        raw = open(p, 'rb').read()
        assert b'\r\n' in raw and not raw.endswith(b'\n'), 'CRLF/无尾风格保持'
    finally:
        shutil.rmtree(d)


def test_guard_delete_member_stale_rejects():
    # A7：防陈旧失败 ⇒ 整批拒（不存在的 key 不得静默跳过）。
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {'20': {'name': 'm_keep', 'type': 'int', 'source': 'y'}}}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        before = open(p, 'rb').read()
        batch = [{'kind': 'delete_member', 'class': 'Foo', 'key': '9999',
                  'evidence': 'W1: x'}]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, d) == 1, '无成员键必须整批拒'
        assert open(p, 'rb').read() == before
    finally:
        shutil.rmtree(d)


def test_guard_global_add_registers_and_dedups():
    # W2-④ 独立全局正名（globals.json 在注解根目录——实测踩点：structs/ 下无此文件）。
    d = tempfile.mkdtemp()
    try:
        ann_dir = os.path.join(d, 'structs')
        os.makedirs(ann_dir)
        g = {'0x00C10968': {'name': 'g_palScript', 'type': 'PalScript'}}
        gp = os.path.join(d, 'globals.json')
        text = json.dumps(g, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(gp, 'w', encoding='utf-8', newline='').write(text)
        batch = [{'kind': 'global_add', 'addr': '0x00DE90B0', 'name': 'g_nFoo', 'type': 'int',
                  'evidence': 'W1: exists(12 站点数据活动)'}]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        rc = _run_guard(bp, ann_dir)
        assert rc == 0
        got = json.loads(open(gp, encoding='utf-8').read())
        assert got['0x00DE90B0']['name'] == 'g_nFoo' and got['0x00DE90B0']['type'] == 'int'
        assert '0x00C10968' in got, '既有条目不变'
        # 防重：同址再加 ⇒ 整批拒
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, ann_dir) == 1, '同址 global_add 必须拒（防重）'
    finally:
        shutil.rmtree(d)


def test_guard_global_retype_redirects_and_dedups():
    # B 批填充重定向机制件：globals.json 类型修正（9 行 float 弹药落点）。
    d = tempfile.mkdtemp()
    try:
        ann_dir = os.path.join(d, 'structs')
        os.makedirs(ann_dir)
        g = {'0x00DE8DF8': {'name': 'g_nRenderTarget2_DE8DF8', 'type': 'int',
                            'source': 'auto:overlap_g_PAL3_at_+0x1358'},
             '0x00DE8DFC': {'name': 'g_nRenderTarget2_DE8DFC', 'type': 'int',
                            'source': 'auto:overlap_g_PAL3_at_+0x135C'}}
        gp = os.path.join(d, 'globals.json')
        text = json.dumps(g, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(gp, 'w', encoding='utf-8', newline='').write(text)
        batch = [{'kind': 'global_retype', 'addr': '0x00DE8DF8', 'new_type': 'float',
                  'evidence': 'T1: 0x004C1020 fstp dword ptr [0x00DE8DF8]'}]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, ann_dir) == 0
        got = json.loads(open(gp, encoding='utf-8').read())
        assert got['0x00DE8DF8']['type'] == 'float', '重定向定型必须生效'
        assert 'global_retype' in got['0x00DE8DF8']['source'], 'source 留证据凭据'
        assert got['0x00DE8DFC']['type'] == 'int', '未触碰条目不变'
        # 幂等：同型重跑 = no-op 成功
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, ann_dir) == 0, '同型重跑必须 no-op 成功'
        # 防陈旧：未注册地址 ⇒ 整批拒
        json.dump([{'kind': 'global_retype', 'addr': '0x00DEAD00', 'new_type': 'float',
                    'evidence': 'T1: x'}], open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, ann_dir) == 1, '未注册地址必须整批拒'
    finally:
        shutil.rmtree(d)


def test_guard_normalize_key_moves_and_dedups():
    # W5 键纪律：hex/N_N 键归一到纯十进制；防陈旧（旧键缺）/防撞（新键占）双查。
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {
            '0x6C': {'name': 'm_h', 'type': 'int', 'source': 'x'},
            '50814_0': {'name': 'm_arr', 'type': 'int', 'source': 'y'},
            '108': {'name': 'm_keep', 'type': 'int', 'source': 'z'},
        }}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        bp = os.path.join(d, 'batch.json')
        json.dump([{'kind': 'normalize_key', 'class': 'Foo', 'from_key': '50814_0', 'to_key': '50814_0',
                    'evidence': 'W5: N_N 同形幂等键（规范化 source 记账）'}],
                  open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, d) == 0, '同形 to==from 应可（幂等记账）'
        # hex→dec 撞键必须拒（0x6C=108 已存在）
        json.dump([{'kind': 'normalize_key', 'class': 'Foo', 'from_key': '0x6C', 'to_key': '108',
                    'evidence': 'W5: x'}], open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, d) == 1, '新键已存在必须整批拒'
        # 防陈旧：旧键缺
        json.dump([{'kind': 'normalize_key', 'class': 'Foo', 'from_key': '0x99', 'to_key': '153',
                    'evidence': 'W5: x'}], open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, d) == 1, '旧键缺必须整批拒'
    finally:
        shutil.rmtree(d)


def test_guard_global_categorize_and_delete():
    # 全局实况清理 G1 机制件：分类标注（非破坏）+ 删条（防陈旧+处置闭合必填）。
    d = tempfile.mkdtemp()
    try:
        ann_dir = os.path.join(d, 'structs')
        os.makedirs(ann_dir)
        g = {'0x00C043A0': {'name': 'g_RoleSlotBuf', 'type': 'RoleSystem', 'source': 'x'},
             '0x00C109F0': {'name': 'dword_C109F0', 'type': 'skip', 'source': 'y'}}
        gp = os.path.join(d, 'globals.json')
        text = json.dumps(g, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(gp, 'w', encoding='utf-8', newline='').write(text)
        bp = os.path.join(d, 'batch.json')
        json.dump([{'kind': 'global_categorize', 'addr': '0x00C043A0', 'category': 'anchor_object',
                    'evidence': 'G6: 锚对象本体（严格内部判定修正后单列）'}],
                  open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, ann_dir) == 0
        got = json.loads(open(gp, encoding='utf-8').read())
        assert got['0x00C043A0']['category'] == 'anchor_object'
        json.dump([{'kind': 'global_categorize', 'addr': '0x00C043A0', 'category': 'anchor_object',
                    'evidence': 'x'}], open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, ann_dir) == 0, '同分类重跑须 no-op 成功'
        json.dump([{'kind': 'delete_global', 'addr': '0x00C109F0', 'evidence': 'x'}],
                  open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, ann_dir) == 1, '缺 disposal 必须拒'
        json.dump([{'kind': 'delete_global', 'addr': '0x00C109F0',
                    'disposal': 'g_palScript 内部+零引用双证', 'evidence': 'x'}],
                  open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, ann_dir) == 0
        got = json.loads(open(gp, encoding='utf-8').read())
        assert '0x00C109F0' not in got, '删条须生效'
        assert '0x00C043A0' in got, '未触碰条目不变'
    finally:
        shutil.rmtree(d)


def test_guard_global_tombstone_suppresses_emission():
    # C2（75e5af3b 硬条件）：删除=墓碑化——type=skip 墓碑保留抑制载体；幂等 no-op。
    d = tempfile.mkdtemp()
    try:
        ann_dir = os.path.join(d, 'structs')
        os.makedirs(ann_dir)
        g = {'0x00C109F0': {'name': 'dword_C109F0', 'type': 'int', 'source': 'x'}}
        gp = os.path.join(d, 'globals.json')
        text = json.dumps(g, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(gp, 'w', encoding='utf-8', newline='').write(text)
        bp = os.path.join(d, 'batch.json')
        json.dump([{'kind': 'global_tombstone', 'addr': '0x00C109F0',
                    'disposal': 'g_palScript 内部承接', 'evidence': 'G6 复归墓碑'}],
                  open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, ann_dir) == 0
        got = json.loads(open(gp, encoding='utf-8').read())
        ent = got['0x00C109F0']
        assert ent['type'] == 'skip' and ent.get('deleted'), '须成 skip 墓碑（抑制载体）'
        json.dump([{'kind': 'global_tombstone', 'addr': '0x00C109F0',
                    'disposal': 'x', 'evidence': 'x'}], open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, ann_dir) == 0, '重跑须 no-op 成功'
    finally:
        shutil.rmtree(d)


def test_guard_delete_method_removes_and_dedups():
    # C-② 方法误归属清理机制件：methods 删条 + 防陈旧（无此方法 ⇒ 整批拒）。
    d = tempfile.mkdtemp()
    try:
        ann = {'known_members': {}, 'methods': {
            '0x00493E40': {'name': 'FormatStatusCaption', 'signature': 'int __thiscall X(Y *this)'},
            '0x00401000': {'name': 'Keep', 'signature': 'void __thiscall X(Y *this)'}}}
        p = os.path.join(d, 'SceneMgr.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        bp = os.path.join(d, 'batch.json')
        json.dump([{'kind': 'delete_method', 'class': 'SceneMgr', 'key': '0x00493E40',
                    'evidence': 'decomp 实为 __cdecl SceneMgr_FormatStatusCaption(int nVal) 自由函数'}],
                  open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, d) == 0
        got = json.loads(open(p, encoding='utf-8').read())
        assert '0x00493E40' not in got['methods'], '误归属方法必须删'
        assert '0x00401000' in got['methods'], '未触碰方法不变'
        json.dump([{'kind': 'delete_method', 'class': 'SceneMgr', 'key': '0x00DEAD00',
                    'evidence': 'x'}], open(bp, 'w', encoding='utf-8'))
        assert _run_guard(bp, d) == 1, '无此方法必须整批拒'
    finally:
        shutil.rmtree(d)


def test_guard_add_method_idempotent_noop():
    # 复核 5560c6c5 Q3 / 75f6709b C2：内容完全一致的重跑 = no-op 成功（幂等）；
    # 断言输出含 [no-op] 以**判别 HEAD 静默跳过**（HEAD 也 rc=0 但打 [跳过]）。
    import contextlib
    import io
    d = tempfile.mkdtemp()
    try:
        ent = {'name': 'New', 'signature': 'void __thiscall Foo::New(Foo *this)'}
        ann = {'methods': {'0x00401000': dict(ent)}}
        p = os.path.join(d, 'Foo.json')
        text = json.dumps(ann, ensure_ascii=False, indent=2).replace('\n', '\r\n')
        open(p, 'w', encoding='utf-8', newline='').write(text)
        batch = [{'kind': 'add_method', 'class': 'Foo', 'addr': '0x00401000',
                  'new_name': 'New', 'signature': 'void __thiscall Foo::New(Foo *this)',
                  'evidence': 'T1: 0x00401234 call'}]
        bp = os.path.join(d, 'batch.json')
        json.dump(batch, open(bp, 'w', encoding='utf-8'))
        buf = io.StringIO()
        with contextlib.redirect_stdout(buf):
            rc = _run_guard(bp, d)
        assert rc == 0, '内容一致的重跑必须 no-op 成功（幂等）'
        assert '[no-op]' in buf.getvalue(), '必须打 [no-op]（判别 HEAD 静默跳过 [跳过]）'
    finally:
        shutil.rmtree(d)


# ---------------------------------------------------------------- 集成缝（真实仓库）

def test_load_candidates_smoke_real_repo():
    # F2/D7/D9 端到端缝：hex 键不崩、多实例展开、工作集 W 口径
    cands, diags = load_candidates()
    assert len(cands) > 100, '工作集 W 应有数百条容器占位成员'
    assert all(c['vas'] and all(isinstance(v, int) and v > 0x400000 for _, v in c['vas'])
               for c in cands), 'vas 必须是全实例 VA 集合（D9）'
    assert all(c['src'] == 'member-placeholder' for c in cands), \
        'B2 行不进工作集（复核裁定：同一批字节的两种视图）'
    multi = diags.get('multi_instance') or {}
    if multi:
        cls = sorted(multi)[0]
        rows = [c for c in cands if c['cls'] == cls]
        if rows:
            assert len(rows[0]['vas']) == len(multi[cls]), '多实例类必须逐实例取证'


def test_scan_t1_offset_basis_real_pe():
    # D1 端到端缝（真实 PE + 真实候选）：偏移基同源后解码率必须达到可证伪下界。
    # 历史缺陷：blob 相对 h 当文件偏移 ⇒ 93/93 假阴性（100%）。
    from tools.type_evidence import build_boundaries, exe_text_image, load_func_ranges, scan_t1
    cands, _ = load_candidates(only_cls='tagEffMgrData')
    assert cands, 'tagEffMgrData 应在工作集内'
    data, va2off, sections = exe_text_image()
    boundaries = build_boundaries(data, va2off, load_func_ranges())
    refs, raw = scan_t1(data, sections, [c['vas'][0][1] for c in cands],
                        boundaries=boundaries)
    decoded = sum(1 for c in cands if refs.get(c['vas'][0][1]))
    total = sum(len(v) for v in refs.values()) + sum(len(v) for v in raw.values())
    assert total > 0, '该类成员必须有 LE4 命中（探针实测 225 处）'
    assert decoded >= len(cands) * 0.5, \
        '解码率下界 50%%（实际 %d/%d）——偏移基回归哨兵' % (decoded, len(cands))


ALL = [v for k, v in sorted(globals().items()) if k.startswith('test_')]


def main():
    failed = 0
    for fn in ALL:
        try:
            fn()
            print('PASS %s' % fn.__name__)
        except AssertionError as e:
            failed += 1
            print('FAIL %s: %s' % (fn.__name__, e))
        except Exception as e:  # noqa: BLE001
            failed += 1
            print('ERROR %s: %r' % (fn.__name__, e))
    print('%d/%d passed' % (len(ALL) - failed, len(ALL)))
    return 1 if failed else 0


if __name__ == '__main__':
    sys.exit(main())
