"""注册表（spec #7）——D9 加固版：计数/内容/公式三锁（篡改实验实证旧版 2/2 静默绿）。"""
import json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
NINE = {'game','engine_static','lib_crt','lib_stl','lib_thirdparty','compiler_synthesized',
        'import_thunk','linker_artifact','unknown'}
CONF = {'high','medium','low'}
SUPPLY = {'exact','skewed','missing'}


def _load(name):
    return json.load(open(ROOT / 'data/annotations' / name, encoding='utf-8'))


def test_thunk_registry_schema_and_count():
    d = _load('thunk_registry.json')
    meta = {k for k in d if k.startswith('_')}
    assert meta == {'_schema'}, meta                          # 元键白名单（D9）
    assert len(d) - len(meta) == 29, len(d)                   # 计数锁（防静默丢条目）：17+12（R2a 第 9 形）
    for a, e in d.items():
        if a.startswith('_'): continue
        assert e.get('boundary') in NINE, (a, e)
        assert e.get('confidence') in CONF, (a, e)
        assert e.get('evidence'), (a, e)


def test_static_obj_ctor_thunk_form_12():
    """R2a 第 9 形 static_obj_ctor_thunk_to_import（B9 imm32 FF 25 [IAT]）12 件锁。
    6 个 gbengine 导入类静态对象 ×(ctor+dtor)（gbVFileSystem×3/gbVolModNode/gbImage2D/CPK），
    2026-10-31 PE 字节形 + 导入表 IAT 名双证（review_thunk_mechanism D5 定谳收编）。"""
    d = _load('thunk_registry.json')
    form = {a for a, e in d.items()
            if not a.startswith('_') and e.get('form') == 'static_obj_ctor_thunk_to_import'}
    expect = {'0x00401BC0', '0x00401BE0', '0x00401C00', '0x00401C20', '0x00401C40',
              '0x00401C60', '0x00404530', '0x00404550', '0x00404670', '0x004046A4',
              '0x004CE0D0', '0x004CE0F0'}
    assert form == expect, form
    for a in expect:
        assert d[a]['boundary'] == 'compiler_synthesized', (a, d[a])
    # 内容锁（篡改实验靶点）：首件 IAT 目标 = gbVFileSystem ctor
    assert '??0gbVFileSystem' in d['0x00401BC0']['note'], d['0x00401BC0']


def test_73_slot_pairing_and_content():
    d = _load('system_lib_statics.json')
    slots = d.get('d3dx9_psgp_slots') or []
    assert len(slots) == 73, len(slots)
    named = paired = unknown = 0
    for s in slots:
        i = s['slot']
        assert s['slot_va'] == hex(0x6090A8 + 4*i), s         # 公式断言
        assert s.get('status') in ('named','paired','unknown'), s
        for f in ('live_init','default_impl'):
            v = s.get(f)
            assert v is None or (v.startswith('0x') and 3 <= len(v) <= 10), (s, f)
        if s['status']=='named': named += 1
        elif s['status']=='paired': paired += 1
        else: unknown += 1
    assert (named, paired, unknown) == (6, 63, 4), (named, paired, unknown)   # 计数锁
    # 内容锁（篡改实验靶点）：槽#7/#35 地址↔名钉死
    s7 = slots[7]; s35 = slots[35]
    assert s7['name'] == 'c_D3DXVec3Normalize' and s7['default_impl'] == '0x5450b5', s7
    assert s35['name'] == 'c_D3DXQuaternionSlerp' and s35['default_impl'] == '0x544777', s35
    assert s7['live_init'] != s7['default_impl']              # D2 双字段区分（init 桩≠impl）


def test_supply_enum_valid():
    d = _load('system_lib_statics.json')
    for e in d.get('libs') or []:
        assert e.get('boundary') in NINE, e
        assert e.get('supply') in SUPPLY, e


def test_spec4_schema_closure():
    """spec §4 契约闭合（review_plan_T6 §4 缺口清偿）：逐槽 verify + 命名更正 +
    地址区间 + flags + disposition。verify 三态=review_dx §3.4 全量配对定谳。"""
    d = _load('system_lib_statics.json')
    VERIFY = {'byte-match', 'partial', 'unmatched'}
    dist = {'byte-match': 0, 'partial': 0, 'unmatched': 0}
    for s in d['d3dx9_psgp_slots']:
        assert s.get('verify') in VERIFY, s
        assert s.get('verify_note'), s
        dist[s['verify']] += 1
    assert dist == {'byte-match': 2, 'partial': 67, 'unmatched': 4}, dist   # 69 可复现/4 残差
    by_slot = {s['slot']: s for s in d['d3dx9_psgp_slots']}
    assert by_slot[7]['verify'] == 'byte-match' and by_slot[35]['verify'] == 'byte-match'
    assert by_slot[39]['verify'] == 'unmatched'
    # 命名更正三条（spec §7.2，dx §2.2 字节证据）
    nc = d.get('naming_corrections') or []
    assert len(nc) == 3, nc
    fixes = {e['addr']: e['to'] for e in nc}
    assert fixes['0x00542533'] == '_D3DXVec3Normalize@8', fixes
    assert fixes['0x00544771'] == '_D3DXQuaternionSlerp@16', fixes
    assert 'RandLerpF' in fixes['0x004B8200'], fixes
    # 地址区间（review_dx 数字审计实测）+ libs flags/disposition
    r = d['d3dx9_psgp_table'].get('exe_ranges') or {}
    assert r.get('live_table') == '0x6090A8-0x6091CB' and r.get('template_table') == '0x6091D0-0x6092F3', r
    for e in d.get('libs') or []:
        assert e.get('flags'), e
        assert e.get('disposition'), e
