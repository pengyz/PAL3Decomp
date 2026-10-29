"""free_functions.cpp 聚合守卫（A 定谳 2026-10-29）：零带返回型限定定义（成员定义归类文件）。
白名单：0x4074C0 PAL3::StartCombat（行表处理器渲染噪声，B 行表专项处置前挂账）。
运行: pytest tests/test_free_functions_routing.py -q"""
import re
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
DEF = re.compile(r'(?m)^\s*(?:[\w:~*&<> ]+\s+)?\b(\w+)::(\w+)\s*\([^;{]*\)\s*(?:const\s*)?\{')
ALLOWED = {('PAL3', 'StartCombat')}   # B 专项前挂账（行表处理器渲染噪声）


def test_no_member_definitions_in_free_functions():
    t = open(ROOT / 'pal3/src/free_functions.cpp').read()
    hits = {(m.group(1), m.group(2)) for m in DEF.finditer(t)}
    assert hits <= ALLOWED, hits - ALLOWED
