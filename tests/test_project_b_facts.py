"""B 转换证明 Task 4：verify_b_import 回读壳（task-4-brief Step 1，TDD 红→绿）。

mock daemon 层：project_b_facts(tool, S) 的 tool=注入式假 daemon（import_via_daemon
的 tool 分发同签名）——断言 canonical facts 投影形+verdict 计算。
verdict（spec v2 §1/§7）：diff 缺/变/多 任一 或 无理由 unverifiable ⇒ BROKEN；
全净+unverifiable 全带理由 ⇒ PROVEN。
"""
import json

from ghidra_track.verify_b_import import compute_verdict, project_b_facts


def _mk_tool(canned):
    """canned: {tool_name: payload_dict_or_list} → 假 daemon tool 分发。"""
    def tool(name, args, rid=1):
        if name not in canned:
            return {'isError': True, 'content': [{'text': 'unknown tool %s' % name}]}
        payload = canned[name]
        if isinstance(payload, dict) and 'error' in payload:
            return {'isError': True, 'content': [{'text': payload['error']}]}
        return {'content': [{'text': json.dumps(payload)}]}
    return tool


def test_project_b_facts_canonical_shape():
    canned = {
        'list_functions': [{'address': '0x401000', 'name': 'Foo'}],
        'get_function_info': {'address': '0x401000', 'name': 'Foo',
                              'signature': 'void __thiscall()'},
        'list_data_types': [{'name': 'S'}],
        'get_data_type': {'name': 'S', 'size': 8,
                          'fields': [{'name': 'm_b', 'offset': 4, 'type': 'int'}]},
        'get_global_variables': [{'address': '0x500000', 'name': 'g_X', 'type': 'int'}],
    }
    f = project_b_facts(_mk_tool(canned), {})
    assert 0x401000 in f['functions']
    assert f['functions'][0x401000]['name'] == 'Foo'
    assert 'signature' in f['functions'][0x401000]
    assert f['structs']['S']['size'] == 8
    assert f['structs']['S']['members'][4] == {'name': 'm_b', 'type': 'int'}
    assert f['globals'][0x500000] == {'name': 'g_X', 'type': 'int'}


def test_project_b_facts_tool_error_degrades_not_crash():
    # 回读面缺口=可验性问题不许崩（unverifiable 语义的底座）
    canned = {'list_functions': [{'address': '0x401000', 'name': 'Foo'}],
              'get_function_info': {'error': 'boom'}}
    f = project_b_facts(_mk_tool(canned), {})
    assert 0x401000 in f['functions'], '坏 get_function_info 不得整崩（缺字段=缺席）'
    assert 'signature' not in f['functions'][0x401000] or \
        f['functions'][0x401000].get('signature') in (None, '')


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
    # 无理由 unverifiable=红（R4 禁把不可验当已验）
    assert compute_verdict({'missing': [], 'changed': [], 'extra': [],
                            'unverifiable': [{'path': 'p', 'reason': None}],
                            'match': []}) == 'BROKEN'
