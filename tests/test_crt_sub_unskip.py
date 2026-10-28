"""三 G 冤户 unskip（spec #3；0x541490 裁决改判 linker_artifact 留 skip）。

证据（research_crt_boundary §普查）：
  0x5414A0 = UICursor 装载（235B SEH + "ui\cursor\jt.tga" + OpenBaseFile，thiscall）
  0x541860 = CD 盘扫描（118B sprintf "%c:\" + GetDriveTypeA==5）
  0x00541C40 = 注册表读（114B RegOpenKeyExA HKLM + RegQueryValueEx）→ PAL3_ReadRegistryStr
  0x541490 = 5B jmp crt_sub_005415C0 别名（K 类/linker_artifact）⇒ 留 skip
运行: python3 tests/test_crt_sub_unskip.py
"""
import json
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
SK = json.load(open(ROOT / 'data/annotations/skip_functions.json'))
FN = json.load(open(ROOT / 'data/annotations/functions.json'))

THREE = ('0x005414A0', '0x00541860', '0x00541C40')


def test_three_g_wenhu_unskipped_and_declared():
    for a in THREE:
        assert a not in SK, a                       # 冤户出 skip
        e = FN.get(a)
        assert e and e.get('signature'), a          # 有 decl 形
        assert 'crt_runtime' not in (e.get('source') or '')


def test_registry_reader_named():
    assert FN['0x00541C40']['name'] == 'PAL3_ReadRegistryStr'   # 草稿钉名（行为证据）


def test_541490_alias_retained_linker_artifact():
    """Ruling: A 级 5B jmp 别名=linker_artifact，留 skip（定义体免源）。"""
    assert '0x00541490' in SK
