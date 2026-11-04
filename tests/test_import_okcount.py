"""import_standard changeset ok 计数（终审修——T10 dryRun 实锤：
apply_changeset 的 ok:false 在 text 内（isError=None）——工具级信号误读=假成功）。"""
from ghidra_track.import_standard import batch_ok


def test_batch_ok_true_when_text_ok():
    assert batch_ok({'content': [{'text': 'ok: true\napplied: [x]'}]}) is True


def test_batch_ok_false_inside_text():
    # T10 实锤形：isError=None 但 text 内 ok:false + errors[]
    r = {'isError': None, 'content': [{'text':
         'ok: false\ndryRun: true\nerrors[1]:\n  - index: 0'}]}
    assert batch_ok(r) is False, 'text 内 ok:false 必须判失败（禁假成功）'


def test_batch_ok_error_flag():
    assert batch_ok({'isError': True, 'content': [{'text': 'x'}]}) is False
