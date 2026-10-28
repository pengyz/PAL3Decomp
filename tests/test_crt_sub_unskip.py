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


def test_registry_reader_named_and_arity():
    e = FN['0x00541C40']
    assert e['name'] == 'PAL3_ReadRegistryStr'        # 草稿钉名（行为证据）
    assert e['signature'].count(',') == 2             # P1 三参形（WinMain 三 push+add esp,0xC 铁证）


def test_uicursor_fastcall_abi_carrier():
    assert '__fastcall' in FN['0x005414A0']['signature']   # P2 ABI 载体（T1 同法 ecx 传 this）


def test_541490_alias_retained_linker_artifact():
    """Ruling（理由降级 P3）：留 skip——唯一消费方=编译器合成 atexit 桩（C 类永不源码重建）
    无源码消费面；5B jmp 仅证纯转发（linker_artifact 过度定级，ILT/ICF 三假说未定谳）。"""
    assert '0x00541490' in SK


def test_p4_correctness_locks():
    """P4 补锁：双源零命中 + 名字唯一 + 0x541490 不入 functions（防双注/重名）。"""
    import glob as _g
    for a in ('0x005414A0', '0x00541860', '0x00541C40'):
        assert not any(a in open(f).read() for f in _g.glob(str(ROOT / 'data/annotations/structs/*.json'))), a
    assert '0x00541490' not in FN
    names = [v.get('name') for v in FN.values()]
    for n in ('PAL3_LoadUICursor', 'PAL3_FindCDRomDrive', 'PAL3_ReadRegistryStr'):
        assert names.count(n) == 1, n
