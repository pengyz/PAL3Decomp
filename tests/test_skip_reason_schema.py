"""skip_functions reason 枚举化（spec #4）——三轴 schema 的 skip 轴。

枚举（spec §三轴）：lib_relink_ok / compiler_regenerated / linker_generated /
dual_def_workaround / dup_decl_elsewhere / awaiting_signature
规则来源：crt_skip_census_20261028.md §分类（0x55xxxx 真 CRT/静态簇/微跳板/unknown_libname）
运行: python3 tests/test_skip_reason_schema.py
"""
import json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
SK = json.load(open(ROOT / 'data/annotations/skip_functions.json'))
ENUM = {'lib_relink_ok', 'compiler_regenerated', 'linker_generated',
        'dual_def_workaround', 'dup_decl_elsewhere', 'awaiting_signature'}


def test_all_entries_have_skip_reason_in_enum():
    missing = [a for a, e in SK.items() if e.get('skip_reason') not in ENUM]
    assert not missing, '缺 skip_reason 或越枚举: %d 条 如 %s' % (len(missing), missing[:3])


def test_total_unchanged_and_reason_mirror_intact():
    assert len(SK) == 1927, len(SK)   # 平账推导：1910(T2 前) -3(T2 unskip) +20(T4 registry: 18+0x43BE10+0x55434F)
    assert all(e.get('reason') for e in SK.values())         # reason 镜像在（6 消费点向后兼容）


def test_rules_from_census_applied():
    """Ruling：名形证据 > 段启发（0x55xxxx 段内藏 unknown_libname/_static_ 簇，
    同件双规则互斥时名形桶优先）。"""
    for a, e in SK.items():
        sr, nm = e['skip_reason'], e.get('name') or ''
        if 'SingletonThunk' in nm or nm.startswith('compiler_init_'):
            assert sr == 'compiler_regenerated', (a, sr)
        elif nm.startswith('crt_sub_'):
            assert sr == 'awaiting_signature', (a, sr)  # I-1：G 冤户候选前置（防 _sub_ 截胡）
        elif '_static_' in nm or '_sub_' in nm:
            assert sr == 'lib_relink_ok', (a, sr)      # F2 PSGP 供源（非再生）
        elif a in ('0x0041CA30', '0x0041D590', '0x00485DC0', '0x005044F0'):
            assert sr == 'awaiting_signature', (a, sr) # F1 真代码字节形证伪跳板
        elif nm.startswith('unknown_libname_'):
            n = int(nm.split('_')[-1]) if nm.split('_')[-1].isdigit() else -1
            if 287 <= n <= 524 or n == 528:
                assert sr == 'compiler_regenerated', (a, sr)   # F3 群 A C 静态初始化桩
            elif 529 <= n <= 552:
                assert sr == 'lib_relink_ok', (a, sr)          # F3 真 CRT 24 条
            else:
                assert sr == 'awaiting_signature', (a, sr)
        elif 0x00550000 <= int(a, 16) <= 0x0055FFFF:
            assert sr == 'lib_relink_ok', (a, sr)


def test_i1_crt_sub_binned_awaiting():
    """I-1：crt_sub_* = G 冤户候选（禁猜测）⇒ awaiting_signature；
    `_sub_` 截胡致 52 条误桶 lib_relink_ok = 数据 bug（终审 f78e97a9）。"""
    wrong = [(a, e['skip_reason']) for a, e in SK.items()
             if (e.get('name') or '').startswith('crt_sub_') and e['skip_reason'] != 'awaiting_signature']
    assert not wrong, wrong[:5]


def test_i2_six_consumers_schema_compatible():
    """I-2：6 消费点零 skip_reason 依赖（reason 镜像向后兼容契约=计划承诺对账测试）。"""
    import re as _re
    consumers = ['pipeline/ida/export_full.py', 'pipeline/gen/stages/collect.py',
                 'pipeline/gen/data.py', 'pipeline/ida/apply_annotations.py',
                 'pipeline/check_annotations.py', 'pipeline/gen/annotation_view.py']
    for f in consumers:
        lines = [l for l in open(str(ROOT / f)).read().splitlines()
                 if 'skip_reason' in l
                 and not any(k in l for k in ('_globals', 'rdata', '_info'))]   # globals 域同名字段白名单
        assert not lines, (f, lines[:2])    # 消费点禁读 skip_functions 新轴（向后兼容锁）


def test_i3_census_pure_state_asserted():
    """I-3：读数漂移防呆——census overlay 标签=pure 硬断言。"""
    c = json.load(open(ROOT / 'data/status/probe_census.json'))
    ov = c.get('overlay', {})
    assert ov.get('applied') in ([], None), ov.get('applied')
