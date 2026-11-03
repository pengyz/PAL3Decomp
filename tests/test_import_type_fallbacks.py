"""B 导入修缮（2026-11-03）：型解析回退链 type_candidates 纯函数（R15 先行）。
真值=import_failures 实测残余形（gbVFileSystem*/__int64/_BYTE*/A::B*）。"""

from ghidra_track.import_via_daemon import type_candidates


def test_ptr_to_plain_fallback():
    assert type_candidates('gbVFileSystem *') == ['gbVFileSystem *', 'gbVFileSystem']


def test_nested_ptr_strips_outer():
    got = type_candidates('AStarPathFinder::NODE *')
    assert 'NODE *' in got and 'NODE' in got and got[0] == 'AStarPathFinder::NODE *'


def test_int64_alias():
    assert '__int64' in type_candidates('__int64') and 'longlong' in type_candidates('__int64')


def test_ghidra_byte_alias():
    got = type_candidates('_BYTE *')
    assert 'byte *' in got and 'byte' in got


def test_plain_type_single():
    assert type_candidates('int') == ['int']
