"""dual_source_diff.py 单测（TDD 夹具）。

## 为什么（2026-10-23 step0 Task 1）

双源 diff 报表是**只读**降摩擦工具（`docs/specs/2026-10-23-step0-plan.md` Task 1）：
对比 `asm/pal3/ida_structs.json` 与 `data/annotations/structs/*.json`，
产出 `data/status/dual_source_report.md`。本夹具锁三件对抗复核约束：

1. **口径 = 往返保真**（非「IDA vs 注解」）：`ida_structs.json` 是
   `annotation → apply → IDB → export` 的下游产物，差异读作「往返保真缺口」；
2. **陈旧拒报**：记录 export 时间戳，export 早于注解最新改动 ⇒ 拒报（不写报表）；
3. **dict 形态识别**：`known_members` 的 inline union/struct（dict `type`）、
   `source:overlap`、同偏移 `_N` 变体键都是**位面复用**声明（同一存储的多解释视图），
   **不是偏移冲突**，不得计入缺失/冲突。

## 覆盖

| 场景 | 测试 |
|---|---|
| 报表生成 + 口径声明 + 时间戳 + 可复现 | test_dual_source_diff_generates |
| 陈旧数据 ⇒ 拒报（记录时间戳） | test_diff_stale_reject |
| dict/overlap/同偏移变体 ⇒ 位面复用（非冲突） | test_diff_dict_form_bitplane_not_conflict |
| 真实成员缺失 ⇒ 必须被检出（防真空报表） | test_diff_detects_member_loss |
"""
import json
import os
import re
import subprocess
import sys

import pytest

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOOL = os.path.join(ROOT, 'tools', 'dual_source_diff.py')
REPORT = os.path.join(ROOT, 'data', 'status', 'dual_source_report.md')


def _run(args, timeout=60):
    """从仓库根跑工具（子进程端到端，含 CLI 解析）。"""
    return subprocess.run([sys.executable, TOOL] + list(args),
                          capture_output=True, text=True, timeout=timeout,
                          cwd=ROOT)


def _metrics(out):
    """解析 `[dual_source_diff] key=value ...` 行 ⇒ dict。"""
    got = {}
    for line in out.splitlines():
        m = re.match(r'^\[dual_source_diff\]\s+(.*)$', line.strip())
        if not m:
            continue
        for tok in m.group(1).split():
            if '=' in tok:
                k, v = tok.split('=', 1)
                got[k] = v
    return got


def _section(text, title):
    """抽取 `## <含 title 的节名>` 正文（到下一个 `## ` 为止；`###` 子节不截断）。"""
    m = re.search(r'^##\s[^\n]*' + re.escape(title) + r'[^\n]*\n(.*?)(?=^##\s|\Z)',
                  text, re.M | re.S)
    assert m, f'报表缺少章节: {title}'
    return m.group(1)


def _mk_fixture(tmp_path, ida_structs, ann_structs, stale=False):
    """写合成夹具（ida_structs.json + ann-dir），可选拍旧 export 时间戳。"""
    ida_path = tmp_path / 'ida_structs.json'
    ida_path.write_text(json.dumps(ida_structs), encoding='utf-8')
    ann_dir = tmp_path / 'ann'
    ann_dir.mkdir(exist_ok=True)
    for s in ann_structs:
        (ann_dir / (s['name'] + '.json')).write_text(
            json.dumps(s), encoding='utf-8')
    if stale:
        # export 早于注解最新改动 ⇒ 陈旧
        ann_ts = max(os.path.getmtime(str(p)) for p in ann_dir.glob('*.json'))
        os.utime(str(ida_path), (ann_ts - 100, ann_ts - 100))
    else:
        ann_ts = max(os.path.getmtime(str(p)) for p in ann_dir.glob('*.json'))
        os.utime(str(ida_path), (ann_ts + 100, ann_ts + 100))
    return ida_path, ann_dir


def test_dual_source_diff_generates():
    """双源 diff 报表生成（只读）。

    计划原样断言（`docs/specs/2026-10-23-step0-plan.md` Task 1 Step 1）：
    退出码 0 且报表落盘。另锁三件对抗复核约束：
      * 报表含**往返保真**口径声明（非「IDA vs 注解」措辞）；
      * 报表记录 **export 时间戳** 且陈旧判定 = FRESH；
      * 同输入 ⇒ 同输出（字节级可复现）。

    ⚠️ 本测试跑真实数据：若注解已改而未重跑 export，工具按设计**拒报**（rc=2）
    —— 那是门禁在报警（CLAUDE.md「验证前强制全链检查」），不是测试缺陷。
    """
    r = _run([])
    assert r.returncode == 0, f'rc={r.returncode}\n{r.stdout}\n{r.stderr}'
    assert 'dual_source_report' in r.stdout or os.path.exists(REPORT)
    assert os.path.exists(REPORT), '报表未落盘'

    text = open(REPORT, encoding='utf-8').read()
    assert '往返保真' in text, '报表必须声明「往返保真」口径'
    assert 'export 时间戳' in text, '报表必须记录 export 时间戳'
    m = _metrics(r.stdout)
    assert m.get('stale') == '0', f'实数据应 FRESH，实得 {m}'
    assert m.get('export_ts') and m.get('ann_ts'), f'必须记录双侧时间戳: {m}'

    # 同输入 ⇒ 同输出（报表字节 + stdout 度量行均须可复现）
    r2 = _run([])
    assert r2.returncode == 0
    assert r2.stdout == r.stdout, '同输入须同输出（stdout 可复现）'
    assert open(REPORT, encoding='utf-8').read() == text, '报表须字节可复现'


def test_diff_stale_reject(tmp_path):
    """陈旧数据 ⇒ 拒报（记录时间戳）。

    export 时间戳早于注解最新改动 ⇒ 数据陈旧，报表是过期读数 ⇒ **拒报**：
    非零退出 + 不写报表 + 记录双侧时间戳（供人工判断陈旧多久）。
    """
    ida_path, ann_dir = _mk_fixture(
        tmp_path,
        {'Foo': {'size': 8, 'kind': 'struct', 'data_members': [
            {'name': 'a', 'type': 'int', 'offset': 0}]}},
        [{'name': 'Foo', 'binary_size': 8, 'known_members': {
            '0': {'name': 'a', 'type': 'int'}}}],
        stale=True)
    out = tmp_path / 'report.md'
    r = _run(['--ida-structs', str(ida_path), '--ann-dir', str(ann_dir),
              '--out', str(out)])
    assert r.returncode != 0, f'陈旧须拒报，实得 rc=0\n{r.stdout}'
    assert not out.exists(), '陈旧时不得写报表（拒报）'
    combined = r.stdout + r.stderr
    assert 'stale=1' in combined, f'须标记陈旧: {combined}'
    m = _metrics(combined)
    assert m.get('export_ts') and m.get('ann_ts'), f'须记录双侧时间戳: {m}'


def test_diff_dict_form_bitplane_not_conflict(tmp_path):
    """dict 形态 / overlap / 同偏移变体 = 位面复用（非偏移冲突）。

    `known_members` 的三形态都是**位面复用声明**（同一存储的多解释视图）：
      * `type` 为 dict（`{"union": [...]}` / `{"struct": [...]}`）；
      * `source` 带 `overlap`；
      * 同偏移 `_N` 变体键（`0` + `0_1`）。
    三者都**不得**计入「成员缺失 / 偏移冲突 / 类型差异」，只进位面复用账。
    """
    ida_path, ann_dir = _mk_fixture(
        tmp_path,
        {'Foo': {'size': 16, 'kind': 'struct', 'data_members': [
            # dict 形态成员的往返形：合成名 _inline_<类>_<成员>
            {'name': 'ov', 'type': '_inline_Foo_ov', 'offset': 0},
            # 同偏移多视图（变体键 0_1）在 IDB 侧是两个重叠成员
            {'name': 'as_int', 'type': 'int', 'offset': 8},
            {'name': 'as_float', 'type': 'float', 'offset': 8},
            # source:overlap 的成员
            {'name': 'buf', 'type': 'int', 'offset': 12}]}},
        [{'name': 'Foo', 'binary_size': 16, 'known_members': {
            '0': {'name': 'ov', 'type': {'union': [
                    {'type': 'int', 'name': 'v_int'},
                    {'type': 'float', 'name': 'v_float'}]},
                 'source': 'overlay:test'},
            '8': {'name': 'as_int', 'type': 'int'},
            '8_1': {'name': 'as_float', 'type': 'float'},
            '12': {'name': 'buf', 'type': 'int',
                   'source': '位面复用 overlap:buf-as-bytes'}}}],
        stale=False)
    out = tmp_path / 'report.md'
    r = _run(['--ida-structs', str(ida_path), '--ann-dir', str(ann_dir),
              '--out', str(out)])
    assert r.returncode == 0, f'rc={r.returncode}\n{r.stdout}\n{r.stderr}'
    m = _metrics(r.stdout)
    assert m.get('bitplane_dict') == '1', f'dict 形态 1 个: {m}'
    assert m.get('bitplane_suffix') == '1', f'同偏移变体 1 个: {m}'
    assert m.get('bitplane_overlap') == '1', f'overlap 声明 1 个: {m}'
    # 位面复用不得被计为缺失/新增
    assert m.get('ann_missing') == '0', f'位面复用非缺失: {m}'
    assert m.get('ida_extra') == '0', f'位面复用非新增: {m}'
    assert m.get('divergent') == '0', f'位面复用非类型差异: {m}'

    text = out.read_text(encoding='utf-8')
    body = _section(text, '位面复用')
    for name in ('ov', 'as_float', 'buf'):
        assert name in body, f'{name} 须记入位面复用账: {body}'
    for title in ('成员缺失', '类型差异'):
        assert 'ov' not in _section(text, title), \
            f'位面复用不得进「{title}」'


def test_diff_detects_member_loss(tmp_path):
    """真实成员缺失必须被检出（防真空报表）。"""
    ida_path, ann_dir = _mk_fixture(
        tmp_path,
        {'Foo': {'size': 16, 'kind': 'struct', 'data_members': [
            {'name': 'a', 'type': 'int', 'offset': 0}]}},
        [{'name': 'Foo', 'binary_size': 16, 'known_members': {
            '0': {'name': 'a', 'type': 'int'},
            '8': {'name': 'lost_member', 'type': 'float'}}}],
        stale=False)
    out = tmp_path / 'report.md'
    r = _run(['--ida-structs', str(ida_path), '--ann-dir', str(ann_dir),
              '--out', str(out)])
    assert r.returncode == 0, f'rc={r.returncode}\n{r.stdout}\n{r.stderr}'
    m = _metrics(r.stdout)
    assert m.get('ann_missing') == '1', f'须检出 1 个往返丢失成员: {m}'
    text = out.read_text(encoding='utf-8')
    assert 'lost_member' in _section(text, '成员缺失')
