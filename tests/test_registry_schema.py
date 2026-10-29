"""注册表落地（spec #7）——thunk_registry + system_lib_statics（73 槽 PSGP 全量对账）。
运行: pytest tests/test_registry_schema.py -q"""
import json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
NINE = {'game','engine_static','lib_crt','lib_stl','lib_thirdparty','compiler_synthesized',
        'import_thunk','linker_artifact','unknown'}
CONF = {'high','medium','low'}


def _load(name):
    return json.load(open(ROOT / 'data/annotations' / name))


def test_thunk_registry_schema():
    d = _load('thunk_registry.json')
    assert d, '空注册表'
    for a, e in d.items():
        if a.startswith('_'):
            continue
        assert e.get('boundary') in NINE, (a, e)
        assert e.get('confidence') in CONF, (a, e)
        assert e.get('evidence'), (a, e)


def test_73_slot_pairing_accounted():
    d = _load('system_lib_statics.json')
    slots = d.get('d3dx9_psgp_slots') or []
    assert len(slots) == 73, len(slots)
    for s in slots:
        assert s.get('slot') is not None and s.get('slot_va'), s
        assert s.get('status') in ('named', 'paired', 'unknown'), s


def test_enum_valid():
    d = _load('system_lib_statics.json')
    for e in (d.get('libs') or []):
        assert e.get('boundary') in NINE, e
