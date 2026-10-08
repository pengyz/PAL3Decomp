"""T1b 状态机契约测试（复核 1239c52d C7：3 反面 + 核心语义）。python tools/test_t1b.py"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tools.t1b import collect_t1b_for_method, method_seed_map, this_track_step  # noqa: E402


def _insns(machine_code, va=0x401000):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return list(md.disasm(machine_code, va))


def test_basic_this_disp_carrier():
    # mov eax, [ecx+0x10] => 载体 this+0x10
    ins = _insns(bytes.fromhex('8B 41 10'))          # mov eax,[ecx+0x10]
    hits, _ = collect_t1b_for_method(ins)
    assert 0x10 in hits, hits


def test_index_form_excluded():
    # mov eax,[ecx+edx*4+0x10] => **不得**入证据（复核 R5：57 站点误归属实证）
    ins = _insns(bytes.fromhex('8B 44 91 10'))       # mov eax,[ecx+edx*4+0x10]
    hits, _ = collect_t1b_for_method(ins)
    assert hits == {}, 'index 形态不得入证据：%s' % hits


def test_negative_disp_rejected():
    # mov eax,[ecx-0x8] => 负 disp 拒（R6 MI 防线）
    ins = _insns(bytes.fromhex('8B 41 F8'))          # mov eax,[ecx-8]
    hits, _ = collect_t1b_for_method(ins)
    assert hits == {}, '负 disp 不得入证据'


def test_call_kills_ecx():
    # mov esi,ecx ; call ; mov [esi+0x10],eax => call 后 esi 不失效但 ecx 失效；
    # 若 esi 未复制则 [esi] 不入——复制传播后 esi 继承 this+0 应入（call 只杀 eax/ecx/edx）
    ins = _insns(bytes.fromhex('89 CE E8 00 00 00 00 89 46 10'))  # mov esi,ecx;call $;mov [esi+0x10],eax
    hits, _ = collect_t1b_for_method(ins)
    assert 0x10 in hits, 'esi 复制传播应在 call 后存活：%s' % hits
    ins2 = _insns(bytes.fromhex('E8 00 00 00 00 8B 41 10'))        # call $; mov eax,[ecx+0x10]
    hits2, _ = collect_t1b_for_method(ins2)
    assert 0x10 not in hits2, 'call 后 ecx 失效不得再作证据'


def test_pop_and_partial_write_invalidate():
    # mov esi,ecx ; pop esi ; mov [esi+0x10],eax => pop 写 esi ⇒ 失效（复核 C1 反面③）
    ins = _insns(bytes.fromhex('89 CE 5E 89 46 10'))
    hits, _ = collect_t1b_for_method(ins)
    assert hits == {}, 'pop 后旧值不得再作证据：%s' % hits
    # mov esi,ecx ; mov si,ax ; mov eax,[esi+0x10] => 部分寄存器写整族失效
    # （32 位模式无 sil——0x88C6 是 mov dh,al；部分写 ESI 族须用 16 位 `mov si,ax`）
    ins2 = _insns(bytes.fromhex('89 CE 66 89 C6 8B 46 10'))
    hits2, _ = collect_t1b_for_method(ins2)
    assert 0x10 not in hits2, '部分寄存器写须整族失效：%s' % hits2


def test_derived_pointer_lea():
    # lea esi,[ecx+0x20] ; mov eax,[esi+0x4] => this+0x24
    ins = _insns(bytes.fromhex('8D 71 20 8B 46 04'))
    hits, _ = collect_t1b_for_method(ins)
    assert 0x24 in hits, '派生指针归并：%s' % hits


def test_non_thiscall_not_seeded():
    # 播种门：无 __thiscall ⇒ 空映射 ⇒ 零载体
    ins = _insns(bytes.fromhex('8B 41 10'))
    hits, _ = collect_t1b_for_method(ins, seed_this=False)
    assert hits == {}, '非 thiscall 不得播种'


def test_inc_dec_imul_kill():
    # mov esi,ecx ; inc esi ; mov eax,[esi+0x10] => inc 写 ⇒ 失效
    ins = _insns(bytes.fromhex('89 CE 46 8B 46 10'))
    hits, _ = collect_t1b_for_method(ins)
    assert hits == {}, 'inc 写点须失效'
    # 单操作数 imul 杀 eax/edx
    ins2 = _insns(bytes.fromhex('89 CE F7 E6 8B 46 10'))           # mov esi,ecx; imul esi; mov eax,[esi+0x10]
    hits2, _ = collect_t1b_for_method(ins2)
    assert 0x10 in hits2, 'imul 不杀 esi（只杀 eax/edx 族）：%s' % hits2


def test_seed_map_thiscall_gate():
    # 真实仓库输入面：RoleSystem 方法中非 thiscall 存在（复核实测 8 static）
    sm = method_seed_map()
    assert sm, '播种图非空'
    n_seed = sum(1 for v in sm.values() if v)
    n_no = sum(1 for v in sm.values() if not v)
    assert n_seed > 100 and n_no > 10, '播种门应两向都有（thiscall %d / 非 %d）' % (n_seed, n_no)


def test_propose_v3_merge_semantics():
    # 设计 §2.3：T1 addr-only + T1b float×2 ⇒ float/A + 溯源注；单 float ⇒ B；double 禁填分支
    from tools.t1b import propose_v3, to_refs
    from tools.type_evidence import Ref
    t1_addr = [Ref(0x100, 0x401000, 'push', '0xADDR', 4, 'addr', None, note='imm')]
    f2 = [Ref(0x100, 0x402000, 'fadd', 'x', 4, 'float', None, note='this+disp'),
          Ref(0x100, 0x402010, 'fstp', 'x', 4, 'float', None, note='this+disp')]
    p, g, notes = propose_v3(t1_addr, f2)
    assert p == 'float' and g == 'A', (p, g)
    assert any('T1:1 T1b:2' in n for n in notes), notes
    assert not any('cross-source-width' in n for n in notes), '同宽不误报'
    f1 = [Ref(0x100, 0x402000, 'fadd', 'x', 4, 'float', None, note='this+disp')]
    p2, g2, _ = propose_v3([], f1)
    assert g2 == 'B', '单 float 站点必须 B（不落盘）：%s' % g2
    t1_i4 = [Ref(0x100, 0x401000, 'mov', 'x', 4, 'int', None, note='disp')]
    t1b_i1 = [Ref(0x100, 0x402000, 'movzx', 'x', 1, 'int', 'unsigned', note='this+disp')]
    p3, g3, notes3 = propose_v3(t1_i4, t1b_i1)
    assert g3 == 'C' and any('cross-source-width' in n for n in notes3), (g3, notes3)
    dbl = [Ref(0x100, 0x402000, 'fld', 'x', 8, 'double', None, note='this+disp'),
           Ref(0x100, 0x402100, 'fstp', 'x', 8, 'double', None, note='this+disp')]
    p4, g4, _ = propose_v3(t1_addr, dbl)
    assert p4 == 'double', 'double 提案保留（emit 禁填）：%s' % p4


def test_to_refs_shapes():
    from tools.t1b import to_refs
    hits = [(0x402000, 'fadd', 4, 'load'), (0x402010, 'mov', 4, 'store')]
    refs = to_refs(0x100, hits)
    assert len(refs) == 2
    assert refs[0].kind == 'float' and refs[1].kind == 'int'
    assert all(r.note == 'this+disp' for r in refs)


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
