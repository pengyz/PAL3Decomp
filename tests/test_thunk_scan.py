"""thunk_scan 字节形判据（research_thunk §4.2 #7 / R2a 勘误后 9 形齐）。
fixture 全部取自已验证真实字节（PE 直读/research 摘录），R15：改工具必须跑其测试。
运行: python3 tests/test_thunk_scan.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from thunk_scan import classify_shape  # noqa: E402


def test_import_thunk_and_psgp_dispatch():
    assert classify_shape(bytes.fromhex('ff2518a55600')) == 'import_thunk'          # 0x542072
    assert classify_shape(bytes.fromhex('ff251ca05600')) == 'import_thunk'          # 0x55EF80 DInput8
    assert classify_shape(bytes.fromhex('ff25c4906000')) == 'psgp_dispatch'         # 0x542533 槽#7
    assert classify_shape(bytes.fromhex('ff2534916000')) == 'psgp_dispatch'         # 0x544771 槽#35
    # 目标非 IAT/PSGP ⇒ 不判定入人工桶
    assert classify_shape(bytes.fromhex('ff2500104000')) == 'jmp_indirect_other'


def test_psgp_lazy_init_A_and_C_form():
    # 0x542526: 6A 01 E8 <rel32> FF 25 C4 90 60 00（A 形）
    a = bytes.fromhex('6a01') + b'\xe8' + (0x546F41 - (0x542526 + 7)).to_bytes(4, 'little', signed=True) + bytes.fromhex('ff25c4906000')
    assert classify_shape(a) == 'psgp_lazy_init'
    # C 形: 55 8B EC 6A 01 E8 rel32 5D FF 25 ...
    c = bytes.fromhex('558bec6a01') + b'\xe8' + (0x1234).to_bytes(4, 'little', signed=True) + bytes.fromhex('5dff25c4906000')
    assert classify_shape(c) == 'psgp_lazy_init'


def test_form9_and_singleton():
    # 0x401BC0 真实字节（2026-10-31 PE 直证）：mov ecx,0x7CC178; jmp [IAT 0x56A568]
    assert classify_shape(bytes.fromhex('b978c17c00ff2568a55600')) == 'static_obj_ctor_thunk_to_import'
    # T5 单例：B9 imm32 E9 rel32（0x53C890 形）
    t5 = bytes.fromhex('b9c01e7b01') + b'\xe9' + (0x1234).to_bytes(4, 'little', signed=True)
    assert classify_shape(t5) == 'singleton_thunk'
    # B9 变体不误收
    assert classify_shape(bytes.fromhex('b9c01e7b0190')) == 'mov_ecx_imm_other'


def test_adjustor_glue_alias_real():
    # T6：83 E9 imm8 E9 rel32（0x41BE20 sub 0x38）
    t6 = bytes.fromhex('83e938') + b'\xe9' + (0x1234).to_bytes(4, 'little', signed=True)
    assert classify_shape(t6) == 'this_adjustor'
    # T8：0x401BB0 真实字节 E8 0B 00 00 00 E9 16 00 00 00
    assert classify_shape(bytes.fromhex('e80b000000e916000000')) == 'static_init_glue'
    # T7：5B 直跳
    assert classify_shape(b'\xe9' + (0x1234).to_bytes(4, 'little', signed=True)) == 'tail_alias'
    # 真身：标准 prologue
    assert classify_shape(bytes.fromhex('558bec83ec0c56')) == 'real_body'
    assert classify_shape(b'') == 'unknown'


def test_unknown_libname_census_consistent_with_f3_bins():
    """分流 census 与 F3 名号区间桶的对账锁：装桩区(287-524/528) 与真 CRT 区(529-552)
    的字节形分布必须可解释（装桩区=glue/thunk 簇，真 CRT 区=real_body 簇）。
    篡改实验靶点：分布快照锁定。"""
    import json
    import subprocess
    out = Path(__file__).resolve().parents[1] / 'data/status/unknown_libname_shape_census_20261031.json'
    if not out.exists():
        subprocess.run([sys.executable, str(ROOT / 'tools/thunk_scan.py'),
                        '--skip-unknown-libname', '-o', str(out)], check=True,
                       capture_output=True)
    d = json.loads(out.read_text(encoding='utf-8'))
    assert d['count'] == 210, d['count']
    rows = {r['addr']: r for r in d['rows']}
    # 三形锚点（fixture 级）：装桩区首件、真 CRT 区首件
    assert rows['0x004017D0']['family'] in ('static_init_glue', 'singleton_thunk',
                                           'tail_alias', 'real_body'), rows['0x004017D0']
    dist = d['family_dist']
    assert sum(dist.values()) == 210
    assert 'real_body' in dist and dist['real_body'] >= 24, dist   # 真 CRT 24 条下限
