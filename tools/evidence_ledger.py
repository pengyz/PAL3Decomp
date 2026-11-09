#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Evidence ledger：统一登记二进制裁决/审计结论，形成可引用的 ev id 账本。

借鉴 REA「Evidence 账本」思想（2026-11-09 引入），对齐本仓两条既有纪律：
  - 每条结论 = {id, subject, claim, evidence_refs, authority, status, created, resolved}
  - evidence_refs 只存**指针**（文件:行 / 工具命令 / ida 地址），不复制证据内容
    —— 防「双副本分叉」（docs/knowledge/gotcha_dual_copy_table_divergence.md 同理）。
  - authority 对齐 pal3-pipeline SKILL.md「证据等级（提交阈值）」节（**以该节为准**，
    本文件只做提示，不另立规则副本）：
      A 级 = 二进制指令 reg+disp32（偏移修改≥85）
      B 级 = 3+ 条 A 级交叉确认（≥80）
      C 级 = Hex-Rays 文本推断（仅标注参考，不可单独用于偏移修改）
      D 级 = 语义推断（命名≥60，不可用于偏移/类型修改）
  - status 生命周期：open → resolved | contradicted（仅 open 态可裁决，不可回退）。
  - summary-first：query 默认只回 id+等级+状态+一句话结论；--full 才展开证据指针。

Usage:
  evidence_ledger.py add --subject S --claim C --ref R [--ref R ...]
                         --authority A|B|C|D [--status open|resolved|contradicted] [--note N]
  evidence_ledger.py resolve <id> --verdict resolved|contradicted --note N
  evidence_ledger.py query [--id ID] [--status open|resolved|contradicted]
                           [--authority A|B|C|D] [--subject SUB] [--claim C] [--full]
  evidence_ledger.py stats
  evidence_ledger.py --self-test     # 在临时目录自测，不触碰真实台账

无参数 = 打印 stats + 用法提示（不写盘）。未知开关一律拒绝（exit 2）——
教训 P2-4：静默忽略未知开关曾导致默认动作误写台账。

账本文件：data/status/evidence_ledger.json（git 跟踪，原子写 tmp+os.replace）。
三条台账纪律（详见 CLAUDE.md「任务路由表」节）：
  1. 引用结论必须带 ev id（commit message / 代码注释 / 报告）；
  2. 复用优先：二进制裁决前先 query，已有结论不重复考古；
  3. summary-first：query 默认只回摘要。
"""

import json
import os
import sys
import tempfile
from collections import Counter
from contextlib import redirect_stdout
from datetime import date
from io import StringIO
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
LEDGER = REPO / 'data' / 'status' / 'evidence_ledger.json'

AUTHORITIES = ('A', 'B', 'C', 'D')
STATUSES = ('open', 'resolved', 'contradicted')

AUTH_HINT = {
    'A': '二进制指令 reg+disp32（≥85）',
    'B': '3+ 条 A 级交叉确认（≥80）',
    'C': 'Hex-Rays 文本推断（不可单独用于偏移修改）',
    'D': '语义推断（不可用于偏移/类型修改）',
}


def _die(msg, code=2):
    print('[evidence_ledger] ' + msg, file=sys.stderr)
    sys.exit(code)


def _get1(opts, key):
    vals = opts.get(key)
    return vals[-1] if vals else None


def _parse(argv, known_values, known_flags):
    """严格解析：未知开关一律拒绝（教训 P2-4，不得静默忽略）。"""
    opts = {}
    positional = []
    i = 0
    while i < len(argv):
        tok = argv[i]
        if tok.startswith('-'):
            if tok in known_flags:
                opts[tok] = True
                i += 1
                continue
            if tok in known_values:
                if i + 1 >= len(argv):
                    _die('开关 %s 缺少取值' % tok)
                opts.setdefault(tok, []).append(argv[i + 1])
                i += 2
                continue
            _die('未知开关 %r；已知开关: %s'
                 % (tok, sorted(set(known_values) | set(known_flags))))
        positional.append(tok)
        i += 1
    return opts, positional


def _load(path):
    if not path.exists():
        return []
    try:
        entries = json.loads(path.read_text(encoding='utf-8'))
    except (OSError, ValueError) as exc:
        _die('台账文件损坏，拒绝操作 %s: %s' % (path, exc))
    if not isinstance(entries, list):
        _die('台账格式异常（顶层应为数组）: %s' % path)
    return entries


def _save(path, entries):
    entries.sort(key=lambda e: e['id'])
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix('.json.tmp')
    tmp.write_text(json.dumps(entries, ensure_ascii=False, indent=2) + '\n',
                   encoding='utf-8')
    os.replace(str(tmp), str(path))


def _next_id(entries):
    nums = []
    for e in entries:
        try:
            nums.append(int(e['id'].split('_')[1]))
        except (KeyError, IndexError, ValueError):
            _die('台账中存在非法 id: %r' % e.get('id'))
    return 'ev_%04d' % (1 + max(nums or [0]))


def _cmd_add(path, argv):
    opts, _pos = _parse(argv, {'--subject', '--claim', '--ref',
                               '--authority', '--status', '--note'}, set())
    subject = _get1(opts, '--subject')
    claim = _get1(opts, '--claim')
    refs = opts.get('--ref', [])
    authority = _get1(opts, '--authority')
    status = _get1(opts, '--status') or 'open'
    note = _get1(opts, '--note')
    if not subject or not claim:
        _die('add 需要 --subject 与 --claim')
    if not refs:
        _die('add 至少需要一个 --ref（台账只存指针，禁止无指针条目）')
    if authority not in AUTHORITIES:
        _die('--authority 必须是 %s（以 pal3-pipeline SKILL.md 证据等级节为准）'
             % '/'.join(AUTHORITIES))
    if status not in STATUSES:
        _die('--status 必须是 %s' % '/'.join(STATUSES))
    if status != 'open' and not note:
        _die('登记非 open 状态必须给 --note（写明裁决出处：工具输出/commit/文件:行）')
    entries = _load(path)
    for e in entries:
        if e.get('subject') == subject and e.get('claim') == claim:
            _die('重复条目：同 subject+claim 已存在为 %s（如需更新请 resolve 或登记更精确的 claim）'
                 % e['id'])
    today = date.today().isoformat()
    entry = {
        'id': _next_id(entries),
        'subject': subject,
        'claim': claim,
        'evidence_refs': refs,
        'authority': authority,
        'status': status,
        'created': today,
        'resolved': None,
    }
    if status != 'open':
        entry['resolved'] = {'date': today, 'verdict': status, 'note': note}
    entries.append(entry)
    _save(path, entries)
    print('已登记 %s [%s/%s] %s :: %s' % (entry['id'], authority, status, subject, claim))
    return 0


def _cmd_resolve(path, argv):
    opts, positional = _parse(argv, {'--verdict', '--note'}, set())
    if len(positional) != 1:
        _die('resolve 需要且仅需要一个 <id> 位置参数')
    eid = positional[0]
    verdict = _get1(opts, '--verdict')
    note = _get1(opts, '--note')
    if verdict not in ('resolved', 'contradicted'):
        _die('--verdict 必须是 resolved|contradicted')
    if not note:
        _die('resolve 必须 --note 写明裁决依据（工具输出/commit/ev id）')
    entries = _load(path)
    for e in entries:
        if e.get('id') == eid:
            if e.get('status') != 'open':
                _die('%s 当前状态为 %s（非 open），拒绝重复裁决（生命周期不可回退）'
                     % (eid, e.get('status')))
            e['status'] = verdict
            e['resolved'] = {'date': date.today().isoformat(),
                             'verdict': verdict, 'note': note}
            _save(path, entries)
            print('已裁决 %s -> %s :: %s' % (eid, verdict, note))
            return 0
    _die('未找到 %s' % eid)


def _cmd_query(path, argv):
    opts, _pos = _parse(argv, {'--id', '--status', '--authority',
                               '--subject', '--claim'}, {'--full'})
    entries = _load(path)
    f_id = _get1(opts, '--id')
    f_status = _get1(opts, '--status')
    f_auth = _get1(opts, '--authority')
    f_subject = _get1(opts, '--subject')
    f_claim = _get1(opts, '--claim')
    hits = [e for e in entries
            if (not f_id or e.get('id') == f_id)
            and (not f_status or e.get('status') == f_status)
            and (not f_auth or e.get('authority') == f_auth)
            and (not f_subject or f_subject in e.get('subject', ''))
            and (not f_claim or f_claim in e.get('claim', ''))]
    for e in hits:
        print('[%s] %s/%s %s :: %s'
              % (e['id'], e['authority'], e['status'], e['subject'], e['claim']))
        if opts.get('--full'):
            for r in e.get('evidence_refs', []):
                print('    ref: ' + r)
            r = e.get('resolved')
            if r:
                print('    resolved: %s %s %s'
                      % (r.get('date'), r.get('verdict'), r.get('note')))
    print('共 %d 条命中' % len(hits))
    return 0


def _cmd_stats(path):
    entries = _load(path)
    by_status = Counter(e.get('status', '?') for e in entries)
    by_auth = Counter(e.get('authority', '?') for e in entries)
    print('台账: %s' % path)
    print('总数: %d | 状态: %s | 等级: %s | 下一 id: %s'
          % (len(entries),
             ' '.join('%s=%d' % (s, by_status.get(s, 0)) for s in STATUSES),
             ' '.join('%s=%d' % (a, by_auth.get(a, 0)) for a in AUTHORITIES),
             _next_id(entries)))
    return 0


def _dispatch(path, argv):
    if not argv:
        _cmd_stats(path)
        print('\n用法: add | resolve <id> | query | stats | --self-test'
              '（详见文件头 docstring）')
        return 0
    cmd = argv[0]
    if cmd == 'add':
        return _cmd_add(path, argv[1:])
    if cmd == 'resolve':
        return _cmd_resolve(path, argv[1:])
    if cmd == 'query':
        return _cmd_query(path, argv[1:])
    if cmd == 'stats':
        return _cmd_stats(path)
    _die('未知子命令 %r' % cmd)


def _self_test():
    """在临时目录自测全部校验分支与生命周期，不触碰真实台账。"""
    tmp = Path(tempfile.mkdtemp(prefix='evledger_selftest_'))
    path = tmp / 'ledger.json'
    failures = []

    def run(argv):
        buf = StringIO()
        try:
            with redirect_stdout(buf):
                code = _dispatch(path, argv)
        except SystemExit as exc:
            code = exc.code if isinstance(exc.code, int) else 1
        return code, buf.getvalue()

    def expect(name, cond):
        print(('PASS ' if cond else 'FAIL ') + name)
        if not cond:
            failures.append(name)

    code, out = run(['add', '--subject', 'S1', '--claim', 'C1',
                     '--ref', 'f.md:1', '--authority', 'B'])
    expect('add 基本登记（自动 id=ev_0001）', code == 0 and 'ev_0001' in out)
    code, out = run(['add', '--subject', 'S1', '--claim', 'C1',
                     '--ref', 'f.md:1', '--authority', 'B'])
    expect('同 subject+claim 拒重', code == 2)
    code, out = run(['add', '--subject', 'S2', '--claim', 'C2'])
    expect('缺 ref / authority 拒绝', code == 2)
    code, out = run(['add', '--subject', 'S3', '--claim', 'C3',
                     '--ref', 'x:1', '--authority', 'E'])
    expect('非法 authority 拒绝', code == 2)
    code, out = run(['add', '--subject', 'S4', '--claim', 'C4',
                     '--ref', 'g.md:2', '--authority', 'C', '--status', 'resolved'])
    expect('非 open 状态缺 --note 拒绝', code == 2)
    code, out = run(['resolve', 'ev_9999', '--verdict', 'resolved', '--note', 'n'])
    expect('resolve 不存在 id 拒绝', code == 2)
    code, out = run(['resolve', 'ev_0001', '--verdict', 'resolved', '--note', '编译器裁判定谳'])
    expect('resolve open 条目', code == 0)
    code, out = run(['resolve', 'ev_0001', '--verdict', 'contradicted', '--note', 'x'])
    expect('重复裁决拒绝（不可回退）', code == 2)
    code, out = run(['query', '--status', 'open'])
    expect('query --status open 0 命中', code == 0 and '共 0 条命中' in out)
    code, out = run(['query', '--id', 'ev_0001', '--full'])
    expect('query --full 含 refs 与裁决记录', code == 0 and 'f.md:1' in out and '编译器裁判定谳' in out)
    code, out = run(['query', '--bogus'])
    expect('未知开关拒绝（P2-4）', code == 2)
    code, out = run([])
    expect('无参数 = stats + 用法，不写盘', code == 0 and '用法' in out)
    code, out = run(['add', '--subject', 'S5', '--claim', 'C5',
                     '--ref', 'h.md:3', '--authority', 'A'])
    expect('第二条登记 id 递增（ev_0002）', code == 0 and 'ev_0002' in out)
    code, out = run(['resolve', 'ev_0002', '--verdict', 'contradicted', '--note', '反证'])
    expect('contradicted 流转', code == 0)
    code, out = run(['stats'])
    expect('stats 汇总', code == 0 and '总数: 2' in out and '下一 id: ev_0003' in out)
    raw = json.loads(path.read_text(encoding='utf-8'))
    expect('落盘结构含全部字段',
           set(raw[0]) == {'id', 'subject', 'claim', 'evidence_refs',
                           'authority', 'status', 'created', 'resolved'})
    print('SELF-TEST: %s' % ('PASS' if not failures else 'FAIL(%d)' % len(failures)))
    return 0 if not failures else 1


def main():
    argv = sys.argv[1:]
    if '--self-test' in argv:
        sys.exit(_self_test())
    sys.exit(_dispatch(LEDGER, argv))


if __name__ == '__main__':
    main()
