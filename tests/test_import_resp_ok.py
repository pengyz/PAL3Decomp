"""create_* 响应真判（P0 假成功修·2026-11-05 病灶 929→77 实证）。

import 时 worker 病态返回 JSON-RPC error 对象/空文本 → 旧判
`isError or t.startswith('Error')` 不中 → **852 缺型全计 ok**。
新判：create_* 必须文本含 `success: true`（与 changeset batch_ok 同族纪律）。
"""
from ghidra_track.import_standard import resp_ok


def test_success_true_ok():
    r = {'content': [{'text': 'success: true\nname: UIWnd\ncategory: /\nsize: 65'}]}
    assert resp_ok(r) is True


def test_error_object_bad():
    r = {'error': {'code': -32603, 'message': 'worker busy'}}
    assert resp_ok(r) is False, 'JSON-RPC error 对象必须判败（t='' 假成功）'


def test_empty_text_bad():
    assert resp_ok({'content': [{'text': ''}]}) is False
    assert resp_ok({'content': []}) is False
    assert resp_ok(None) is False


def test_success_false_bad():
    r = {'content': [{'text': 'success: false\nreason: already exists'}]}
    assert resp_ok(r) is False


def test_error_text_bad():
    assert resp_ok({'content': [{'text': 'Error: boom'}]}) is False
    assert resp_ok({'isError': True, 'content': [{'text': 'success: true'}]}) is False
