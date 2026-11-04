"""B 转换证明 Task 4：verify_b_import 回读壳（真形版——T10 实探 daemon 表形修正）。

历史（记账）：首版 mock 假设 daemon 出 JSON=错假设——实测 daemon 出 YAML-ish
三态表形（list 项/平铺 kv/fields CSV 行）且无 get_global_variables（真名
list_data_symbols）。本测试以**实探原文**为 canned，钉解析器与投影形。
verdict：PROVEN=全净+unverifiable 全带理由；BROKEN=缺/变/多或无理由（R4）。
"""
import json

from ghidra_track.verify_b_import import (
    _parse_dtype,
    _parse_kv,
    _parse_list,
    compute_verdict,
    project_b_facts,
)

_LIST_FN = """functions[2]:
  - name: Foo
    address: "00401000"
    entryPoint: "00401000"
    signature: undefined Foo(void)
    namespace: null"""

_KV_FN = """name: Foo
address: "00401000"
signature: undefined void __thiscall()
namespace: null
size: 39"""

_LIST_DT = """dataTypes[1]:
  - name: S"""

_DTYPE = """name: S
category: /
size: 8
type: structure
fields[2]{name,dataType,offset,size,comment,bitOffset,bitSize}:
  m_b,int,4,4,null,null,null
  null,undefined,7,1,null,null,null"""

_LIST_SYM = """globals[1]:
  - name: g_X
    address: "00500000"
    dataType: int"""


def _mk_tool(canned):
    """canned: {tool_name: 原文 str 或 {'error': ...}} → 假 daemon（真表形原文）。"""
    def tool(name, args, rid=1):
        if name not in canned:
            return {'isError': True, 'content': [{'text': 'unknown tool %s' % name}]}
        payload = canned[name]
        if isinstance(payload, dict) and 'error' in payload:
            return {'isError': True, 'content': [{'text': payload['error']}]}
        return {'content': [{'text': payload}]}
    return tool


def test_parser_handles_real_shapes():
    assert _parse_list(_LIST_FN)[0]['address'] == '00401000'
    assert _parse_kv(_KV_FN)['size'] == '39'
    d = _parse_dtype(_DTYPE)
    assert d['size'] == 8 and len(d['fields']) == 2, 'size 数值强转（契约）'
    assert d['fields'][0]['name'] == 'm_b'
    assert d['fields'][1].get('name') in (None, 'null'), '未名字节行 name=null'


def test_project_b_facts_canonical_shape():
    canned = {
        'list_functions': _LIST_FN,
        'get_function_info': _KV_FN,
        'list_data_types': _LIST_DT,
        'get_data_type': _DTYPE,
        'list_data_symbols': _LIST_SYM,
    }
    f = project_b_facts(_mk_tool(canned), {})
    assert 0x401000 in f['functions']
    assert f['functions'][0x401000]['name'] == 'Foo'
    assert f['functions'][0x401000]['signature'] == 'void __thiscall()', \
        'undefined 前缀须剥'
    assert f['structs']['S']['size'] == 8
    assert f['structs']['S']['members'][4] == {'name': 'm_b', 'type': 'int'}
    assert 7 not in f['structs']['S']['members'], '未名字节行禁入成员'
    assert f['globals'][0x500000] == {'name': 'g_X', 'type': 'int'}


def test_project_b_facts_tool_error_degrades_not_crash():
    canned = {'list_functions': _LIST_FN, 'get_function_info': {'error': 'boom'}}
    f = project_b_facts(_mk_tool(canned), {})
    assert 0x401000 in f['functions'], '坏 get_function_info 不得整崩'
    assert f['functions'][0x401000].get('signature'), 'list 行 signature 兜底'


def test_project_b_facts_skips_external_globals():
    sym = """globals[1]:
  - name: DirectInput8Create
    address: "EXTERNAL:00000007"
    dataType: undefined"""
    f = project_b_facts(_mk_tool({'list_data_symbols': sym}), {})
    assert f['globals'] == {}, 'EXTERNAL: 前缀=导入面禁入（注解全局=内部址）'


def test_verdict_proven_when_clean():
    assert compute_verdict({'missing': [], 'changed': [], 'extra': [],
                            'unverifiable': [{'path': 'x', 'reason': 'no carrier in B'}],
                            'match': [1]}) == 'PROVEN'


def test_verdict_broken_on_any_diff():
    assert compute_verdict({'missing': [{'path': 'a', 'reason': None}], 'changed': [],
                            'extra': [], 'unverifiable': [], 'match': []}) == 'BROKEN'
    assert compute_verdict({'missing': [], 'changed': [{'path': 'b', 'reason': None}],
                            'extra': [], 'unverifiable': [], 'match': []}) == 'BROKEN'
    assert compute_verdict({'missing': [], 'changed': [], 'extra': [{'path': 'c'}],
                            'unverifiable': [], 'match': []}) == 'BROKEN'


def test_verdict_broken_on_reasonless_unverifiable():
    assert compute_verdict({'missing': [], 'changed': [], 'extra': [],
                            'unverifiable': [{'path': 'p', 'reason': None}],
                            'match': []}) == 'BROKEN'
