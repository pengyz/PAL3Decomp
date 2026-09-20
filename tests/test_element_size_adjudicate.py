# tests/test_element_size_adjudicate.py
"""任务4 测试：两层裁定器（raw_site 只含字面量 / ownership_candidate 只含 lowered 候选）。

覆盖三件事：
1. 计划任务 4 的两个 fixture 语义（Role 的 size 由字面量 evidenced；BINK 错锚不得被 verified）；
2. **真实产物形态**（`data/status/element_size_sites.json`）：寄存器 `ptr`、改编符号 `dtor`
   （`??1stdiobuf@@UAE@XZ_2`）、`count` 为字符串等 —— 裁定器不得对它们做 `int()` 假设，
   且 `raw_site` / `size_state` 字段完整；
3. 真实注解里的 `0x411CA0` **双源矛盾**必须被暴露（PalScript 活动主张 + ScriptObj 已撤回主张）。

护栏：`-` 开头未知开关 ⇒ 返回 0 且不执行；缺站点文件 ⇒ 返回 2。

注：本机 pytest 不可用（collect 阶段崩）⇒ 自带走 `__main__` runner 与 `_MiniPatch` 替身。
"""
import json
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'tools'))
import element_size_adjudicate as a                    # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SITES_JSON = os.path.join(ROOT, 'data', 'status', 'element_size_sites.json')

# raw 层唯一允许出现的键：地址/字节/字面量（不含任何注解派生信息）
RAW_KEYS = {'site', 'line', 'kind', 'ptr', 'size', 'count', 'ctor', 'dtor'}


def _site(**kw):
    s = {'site': 'sub_0', 'kind': 'ehl', 'ptr': 'eax', 'size': 16, 'count': 1,
         'ctor': None, 'dtor': None, 'line': 1}
    s.update(kw)
    return s


def _struct(name, size, methods=None):
    d = {'name': name, 'binary_size': size, 'known_members': {}}
    if methods:
        d['methods'] = {addr: {'name': nm} for addr, nm in methods.items()}
    return d


# ---------------------------------------------------------------- 计划 fixture 1
def test_role_size_evidenced_from_literal_and_raw_layer_stays_pure():
    """`size=0x2200` 站点：size 来自指令字面量 ⇒ evidenced；raw 层不掺注解。"""
    sites = [_site(site='sub_408740', ptr='0xC05F60', size=0x2200, count=5,
                   ctor='0x411900', dtor='0x411CA0', line=11962)]
    structs = {'Role': _struct('Role', 8704, {'0x00411900': 'Role'}),
               'RoleSystem': _struct('RoleSystem', 4868)}
    rows = a.adjudicate(sites, structs)
    assert len(rows) == 1
    row = rows[0]
    # raw 层：只含字面量，且逐字段等于输入
    assert set(row['raw_site']) == RAW_KEYS
    assert row['raw_site'] == {'site': 'sub_408740', 'line': 11962, 'kind': 'ehl',
                               'ptr': '0xC05F60', 'size': 0x2200, 'count': 5,
                               'ctor': '0x411900', 'dtor': '0x411CA0'}
    assert row['size_state'] == 'evidenced'
    # size 维度：8704 不唯一 ⇒ 两个类都在候选里
    assert row['size_matches_classes'] == ['Role']
    assert row['size_unique'] is True
    oc = row['ownership_candidate']
    assert 'Role' in oc['candidate_classes']
    # 2026-09-20 P0 契约变更：verified 是循环论证 ⇒ 降级为 annotation_self_consistent
    # 且不得再产出 verified_class（翻转旧断言，而非保留'现状'）
    assert oc['verified_class'] is None
    assert oc['state'] == 'annotation_self_consistent'
    assert row['requires_second_criterion'] is True
    # 本用例的 ctor/dtor 主张与 size **自洽** ⇒ contradiction 必须为 False
    assert row['contradiction'] is False
    # 归属层整体是 lowered（注解派生）证据，永不冒充 class 级 A 证据
    assert oc['evidence_layer'] == 'lowered'
    assert oc['a_evidence'] is False
    assert all(c['evidence'] == 'annotation(lowered)'
               for c in oc['candidates'] if c['role'] in ('ctor', 'dtor'))


def test_role_size_not_unique_yields_ambiguous_and_shared_dtor_claim():
    """8704 的**真实**不唯一性（Role + ScriptSystem）+ dtor 指向另一个类 ⇒ 不得 verified。"""
    sites = [_site(site='sub_408740', ptr='0xC05F60', size=0x2200, count=5,
                   ctor='0x411900', dtor='0x411CA0', line=11962)]
    structs = {'Role': _struct('Role', 8704, {'0x00411900': 'Role'}),
               'ScriptSystem': _struct('ScriptSystem', 8704),
               'PalScript': _struct('PalScript', 2176, {'0x00411CA0': '~PalScript'})}
    row = a.adjudicate(sites, structs)[0]
    assert row['size_state'] == 'evidenced'
    assert row['size_matches_classes'] == ['Role', 'ScriptSystem']
    assert row['size_unique'] is False
    oc = row['ownership_candidate']
    assert oc['candidate_classes'] == ['PalScript', 'Role', 'ScriptSystem']
    assert oc['verified_class'] is None                     # 已无 verified 概念（M1：循环论证）
    # 2026-09-20 P0 契约变更（M1/M2）：dtor 的 PalScript(2176) 主张与 8704 字面量**不自洽**
    # ⇒ 现在**直接判 conflict**（旧契约把它降级为 ambiguous ⇒ 属漏报 ✗，已修）
    assert oc['state'] == 'conflict'
    assert oc['state'] != 'ambiguous'  # 旧契约值，明确排除
    assert row['contradiction'] is True
    # dtor 的 PalScript 主张与 8704 字面量不自洽 ⇒ 必须留下显式痕迹
    dtor = [c for c in oc['candidates'] if c['role'] == 'dtor'][0]
    assert dtor['class'] == 'PalScript' and dtor['size_consistent'] is False


# ---------------------------------------------------------------- 计划 fixture 2
def test_bink_wrong_anchor_is_conflict_not_verified():
    """`size=896` 站点：ctor 被注成 BINK(932) ⇒ 与字面量 896 冲突，绝不能 verified。"""
    sites = [_site(site='sub_41F6F0', ptr='ecx', size=896, count=64,
                   ctor='0x4236D0', dtor='0x423880', line=47092)]
    structs = {'BINK': _struct('BINK', 932, {'0x004236D0': 'Reset'}),
               'ScriptVM': _struct('ScriptVM', 888, {'0x00423880': 'ProcessFrame'}),
               'tagRoleSlot': _struct('tagRoleSlot', 896)}
    row = a.adjudicate(sites, structs)[0]
    assert row['size_state'] == 'evidenced'
    assert row['size_matches_classes'] == ['tagRoleSlot']
    oc = row['ownership_candidate']
    assert oc['verified_class'] != 'BINK'
    assert oc['verified_class'] is None
    assert oc['state'] in ('ambiguous', 'conflict')
    assert 'tagRoleSlot' in oc['candidate_classes']          # 896 的唯一匹配类仍是候选
    bink = [c for c in oc['candidates'] if c['class'] == 'BINK'][0]
    assert bink['size_consistent'] is False
    assert bink['evidence'] == 'annotation(lowered)'


# ---------------------------------------------------------------- 真实产物形态
def test_real_artifact_rows_complete_with_registers_and_mangled_symbols():
    """裁定器必须吃下**真实产物**：466 站点、寄存器 ptr、改编符号 dtor、count 为 int|None。"""
    with open(SITES_JSON, encoding='utf-8') as fh:
        payload = json.load(fh)
    sites = payload['sites']
    assert len(sites) == 466
    structs, retracted = a.load_annotations()
    assert len(structs) > 800
    rows = a.adjudicate(sites, structs, retracted)
    assert len(rows) == len(sites)

    for r in rows:
        assert set(r['raw_site']) == RAW_KEYS
        assert r['size_state'] in ('evidenced', 'unestablished')
        oc = r['ownership_candidate']
        assert oc['state'] in ('annotation_self_consistent', 'ambiguous', 'conflict', 'candidate', 'unestablished')
        assert oc['evidence_layer'] == 'lowered' and oc['a_evidence'] is False
        assert isinstance(oc['candidates'], list)
        assert isinstance(oc['unresolved_operands'], dict)
        # 可审计性：conflict 裁定必须带可复算理由；size 不自洽的主张必须留痕
        if oc['state'] == 'conflict':
            assert oc['conflict_reasons'], r['raw_site']
        if any(c['size_consistent'] is False for c in oc['candidates']):
            assert oc['conflict_reasons'], r['raw_site']
        if '0x411ca0' in oc['address_refs']:
            assert any('多源' in x for x in oc['conflict_reasons'])

    # 寄存器 ptr 原样保留（真实产物 462/466 是寄存器）
    reg = [r for r in rows if r['raw_site']['ptr'] in ('eax', 'ecx', 'edx', 'esi')]
    assert len(reg) > 400
    assert all(r['raw_site']['size'] is not None for r in reg)

    # 改编符号 dtor：不得被 int()/地址化，且不得产生 verified
    mangled = [r for r in rows if r['raw_site']['dtor'] == '??1stdiobuf@@UAE@XZ_2']
    assert mangled, '真实产物应含改编符号 dtor'
    for r in mangled:
        assert r['ownership_candidate']['unresolved_operands'].get('dtor') == \
            '??1stdiobuf@@UAE@XZ_2'
        assert r['ownership_candidate']['state'] != 'verified'
        assert r['ownership_candidate']['verified_class'] is None

    # 契约（2026-09-20 T2 评审条件②）：count 恒为 int|None —— 原先有 2 条是 str
    # （asm 行 300295 `push ecx`、300859 `push ebx`），现已归一化为 None ⇒ 正向验证：
    bad = [r for r in rows if not (r['raw_site']['count'] is None or isinstance(r['raw_site']['count'], int))]
    assert not bad, 'count 必须为 int|None，实得 %r' % [r['raw_site']['count'] for r in bad[:3]]
    nones = [r for r in rows if r['raw_site']['count'] is None]
    assert nones, '寄存器操作数的 count 应归一化为 None（真实产物应有 2 条）'
    assert all(r['size_state'] == 'evidenced' for r in nones)


def test_real_dual_source_address_0x411ca0_is_exposed():
    """0x411CA0 在注解里有 ≥2 个来源（PalScript 活动 / ScriptObj 已撤回）⇒ 必须暴露。"""
    structs, retracted = a.load_annotations()
    conf = a.address_conflicts(structs, retracted)
    by_addr = {c['addr']: c for c in conf}
    assert '0x411ca0' in by_addr, '双源地址必须出现在 address_conflicts 里'
    c = by_addr['0x411ca0']
    claimants = {x['class'] for x in c['active']} | {x.get('class') for x in c['retracted']}
    assert 'PalScript' in {x['class'] for x in c['active']}
    assert len(claimants) >= 2, claimants
    # 大小写/前导零归一化：注解键是 '0x00411CA0'，站点是 '0x411CA0'
    assert c['addr'] == '0x411ca0'
    # 「0x411CA0 是 Role 数组 dtor」这一主张**只存在于散文**（Role.json 的 methods 里没有它）
    # ⇒ 必须作为 structured=False 的线索暴露，且不得冒充结构化归属主张
    prose = [p for p in c['prose_mentions'] if p['class'] == 'Scene']
    assert prose, 'Scene.json 的散文主张必须被暴露'
    assert all(p['structured'] is False for p in c['prose_mentions'])
    assert any('sub_411CA0' in p['excerpt'] for p in prose)
    # 该散文把 0x2200/size 与 Role（=sub_411900）绑在一起 ⇒ 正是"Role 数组 dtor"这一读法的来源
    assert any('0x2200' in p['excerpt'] and 'Role' in p['excerpt'] for p in prose)
    assert any(p['field'].startswith('Scene.known_members') for p in prose)

    with open(SITES_JSON, encoding='utf-8') as fh:
        sites = json.load(fh)['sites']
    rows = a.adjudicate(sites, structs, retracted)
    refd = [r for r in rows
            if '0x411ca0' in r['ownership_candidate']['address_refs']]
    assert refd, '引用 0x411CA0 的站点行必须带 address_refs 痕迹'
    # 这些行里 ctor/dtor 指向不同类 ⇒ 候选 ≥2 且不得 verified
    multi = [r for r in refd if len(r['ownership_candidate']['candidate_classes']) >= 2]
    assert multi
    assert all(r['ownership_candidate']['verified_class'] is None for r in refd
               if len(r['ownership_candidate']['candidate_classes']) >= 2)


# ---------------------------------------------------------------- 缺陷修正点（计划代码 #1/#2）
def test_addr_normalization_and_non_address_operands():
    """注解键带前导零（`0x00411900`）、站点值不带（`0x411900`）⇒ 必须归一到同一键。

    同时：寄存器/改编符号/局部符号**不是地址** ⇒ 不解析、不 `int()`、不抛异常。
    """
    assert a._norm_addr('0x00411900') == a._norm_addr('0x411900') == '0x411900'
    assert a._norm_addr('0x00411CA0') == '0x411ca0'
    assert a._norm_addr('0x00000000') == '0x0'
    assert a._norm_addr('ecx') is None
    assert a._norm_addr('??1stdiobuf@@UAE@XZ_2') is None
    assert a._norm_addr('nullsub_1') is None
    assert a._norm_addr(None) is None
    # `int` 形态（T2 的 `_val()` 会把 `push 401190h` 转成 int；独立复核列为会崩 T4 的 major）
    assert a._norm_addr(0x411900) == '0x411900'
    assert a._norm_addr(4198800) == '0x401190'
    assert a._norm_addr(True) is None

    structs = {'Role': _struct('Role', 16, {'0x00411900': 'Role'})}
    oc = a.adjudicate([_site(ctor='0x411900')], structs)[0]['ownership_candidate']
    assert [c['class'] for c in oc['candidates'] if c['role'] == 'ctor'] == ['Role']

    # int 形态同样要解析出归属，且 raw 层**原样**保留 int（不改写）
    ri = a.adjudicate([_site(ctor=0x411900)], structs)[0]
    assert ri['raw_site']['ctor'] == 0x411900
    assert [c['class'] for c in ri['ownership_candidate']['candidates']
            if c['role'] == 'ctor'] == ['Role']
    assert ri['ownership_candidate']['unresolved_operands'] == {}

    oc2 = a.adjudicate([_site(ctor='ecx', dtor='nullsub_1')], structs)[0]['ownership_candidate']
    assert oc2['unresolved_operands'] == {'ctor': 'ecx', 'dtor': 'nullsub_1'}
    assert oc2['candidates'] == [{'addr': None, 'class': 'Role', 'name': None, 'role': 'size',
                                  'evidence': 'annotation(size)', 'size_consistent': True}]


# ---------------------------------------------------------------- 加载健壮性
def test_load_annotations_skips_broken_json(tmp_path, monkeypatch):
    """单个坏 JSON 不得中断整体加载（902 个注解文件的现实风险）。"""
    sd = tmp_path / 'structs'
    sd.mkdir()
    (sd / 'Good.json').write_text('{"name":"Good","binary_size":8}', encoding='utf-8')
    (sd / 'Broken.json').write_text('{not json', encoding='utf-8')
    (sd / 'NotADict.json').write_text('[1,2,3]', encoding='utf-8')
    monkeypatch.setattr(a, 'ANN_DIR', str(tmp_path))
    structs, retracted = a.load_annotations()
    assert structs == {'Good': {'name': 'Good', 'binary_size': 8}}
    assert retracted == []


# ---------------------------------------------------------------- 护栏
def test_missing_sites_file_returns_2(tmp_path):
    assert a.main(['--sites', str(tmp_path / 'nope.json')]) == 2


def test_unknown_flag_is_rejected_and_writes_nothing(tmp_path):
    out = tmp_path / 'out.json'
    rc = a.main(['--help', '--json', str(out)])
    assert rc == 0                                  # 护栏：拒绝执行而非跑全流程
    assert not out.exists()


def test_json_written_only_to_given_path(tmp_path):
    out = tmp_path / 'adj.json'
    assert a.main(['--sites', SITES_JSON, '--json', str(out)]) == 0
    with open(out, encoding='utf-8') as fh:
        payload = json.load(fh)
    assert payload['sites'] == SITES_JSON
    assert payload['generated_at'].endswith('Z')
    assert len(payload['rows']) == 466
    assert payload['summary']['rows'] == 466
    assert payload['summary']['evidenced'] == 466


if __name__ == '__main__':
    import inspect
    import shutil
    import tempfile
    import pathlib

    class _MiniPatch:
        """够用的 monkeypatch 替身（本机 pytest 不可用时的兜底 runner）。"""

        def __init__(self):
            self._undo = []

        def setattr(self, obj, name, value):
            self._undo.append((obj, name, getattr(obj, name)))
            setattr(obj, name, value)

        def undo(self):
            for obj, name, old in reversed(self._undo):
                setattr(obj, name, old)
            self._undo = []

    ok = fail = 0
    for name, fn in sorted(globals().items()):
        if name.startswith('test_') and callable(fn):
            params = inspect.signature(fn).parameters
            kwargs, tmpdir, mp = {}, None, _MiniPatch()
            if 'tmp_path' in params:
                tmpdir = tempfile.mkdtemp(prefix='esa_test_')
                kwargs['tmp_path'] = pathlib.Path(tmpdir)
            if 'monkeypatch' in params:
                kwargs['monkeypatch'] = mp
            try:
                fn(**kwargs)
                print('  PASS %s' % name)
                ok += 1
            except Exception as e:                   # noqa: BLE001 - runner 需报告一切异常
                print('  FAIL %s: %s: %s' % (name, type(e).__name__, e))
                fail += 1
            finally:
                mp.undo()
                if tmpdir:
                    shutil.rmtree(tmpdir, ignore_errors=True)
    print('Results: %d passed, %d failed' % (ok, fail))
    sys.exit(1 if fail else 0)