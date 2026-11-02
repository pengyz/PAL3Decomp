"""annotation_import 转换层（双轨 spec §4）——注解 JSON → Ghidra 导入计划（纯函数层）。
铁律：载体诚实化（IDA hack 不入验证轨）· 已 mangled 名直通 · 占位名过。
运行: pytest ghidra_track/tests/test_annotation_import.py -q"""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'ghidra_track'))
from import_annotation import build_import_plan, honest_signature


def test_mangled_name_passthrough():
    plan = build_import_plan(
        functions={'0x00401C70': {'name': '?FileSysInit@@YAXXZ', 'signature': 'void __cdecl()'}},
        structs={}, globals={})
    names = [op for op in plan if op['kind'] == 'set_name']
    assert names and names[0]['name'] == '?FileSysInit@@YAXXZ'   # 禁重绞


def test_carrier_honesty():
    """IDA 载体 __fastcall(int self) → thiscall 本体（self 消隐）。"""
    assert honest_signature('void __fastcall(int self)', cls='NPC') == {
        'conv': '__thiscall', 'ret': 'void', 'params': [], 'cls': 'NPC'}
    assert honest_signature('int __cdecl(const char*, const char*, char*)', cls=None) == {
        'conv': '__cdecl', 'ret': 'int',
        'params': ['const char*', 'const char*', 'char*'], 'cls': None}


def test_struct_offset_mapping():
    plan = build_import_plan(functions={}, globals={},
        structs={'UIListBox': {'size': 1208,
            'known_members': {'68': {'name': 'm_selcolor', 'type': 'gbColorQuad'},
                              '80': {'name': 'm_scrollbar', 'type': 'UIScrollBar'}}}})
    ds = [op for op in plan if op['kind'] == 'define_struct']
    assert ds and ds[0]['size'] == 1208
    assert {m['offset'] for m in ds[0]['members']} == {68, 80}


def test_placeholder_names_pass():
    plan = build_import_plan(
        functions={'0x004074C0': {'name': 'todo_ctor', 'signature': 'void __cdecl()'}},
        structs={}, globals={})
    assert any(op['kind'] == 'set_name' and op['name'] == 'todo_ctor' for op in plan)
