"""注册表（spec #7）——D9 加固版：计数/内容/公式三锁（篡改实验实证旧版 2/2 静默绿）。"""
import json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
NINE = {'game','engine_static','lib_crt','lib_stl','lib_thirdparty','compiler_synthesized',
        'import_thunk','linker_artifact','unknown'}
CONF = {'high','medium','low'}
SUPPLY = {'exact','skewed','missing'}


def _load(name):
    return json.load(open(ROOT / 'data/annotations' / name))


def test_thunk_registry_schema_and_count():
    d = _load('thunk_registry.json')
    meta = {k for k in d if k.startswith('_')}
    assert meta == {'_schema'}, meta                          # 元键白名单（D9）
    assert len(d) - len(meta) == 17, len(d)                   # 计数锁（防静默丢条目）
    for a, e in d.items():
        if a.startswith('_'): continue
        assert e.get('boundary') in NINE, (a, e)
        assert e.get('confidence') in CONF, (a, e)
        assert e.get('evidence'), (a, e)


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
