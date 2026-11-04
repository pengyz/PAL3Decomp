"""verify_b_import — B 面回读壳 + proof CLI（spec v2 §2）。

project_b_facts(tool, S)：经 ghidra-mcp 标准工具面回读 B 程序 → canonical facts
（回读面正名 spec §2：list_functions/get_function_info/list_data_types/
get_data_type/get_global_variables——传输层复用 import_via_daemon 的 tool 分发=标准通路）。
verdict：PROVEN=diff 全净且 unverifiable 全带理由；BROKEN=任一 missing/changed/
extra 或无理由 unverifiable（R4 禁把不可验当已验）。
unverifiable 二分（R4）：'no carrier in B'=B 侧无字段承载（载体注释或 dropped+理由
的处置在矩阵 T5 裁）；'field absent in B readback'=回读缺席。
"""
import argparse
import datetime
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from verify_core import diff_facts, norm_addr, project_ann_facts  # noqa: E402


def _call(tool, name, args, S):
    """daemon 调用 → 解析 JSON 文本；失败返回 None（缺席语义，不崩）。"""
    r = tool(name, dict(S, **args), 1)
    if not isinstance(r, dict):
        return None
    if r.get('isError'):
        return None
    try:
        return json.loads(str((r.get('content') or [{}])[0].get('text', '')))
    except (ValueError, IndexError, KeyError):
        return None


def project_b_facts(tool, S):
    """B 程序回读 → canonical facts（键形与 verify_core.project_ann_facts 对齐）。"""
    funcs = {}
    lst = _call(tool, 'list_functions', {}, S)
    for item in (lst or []):
        addr = item.get('address') or item.get('addr')
        if addr is None:
            continue
        info = _call(tool, 'get_function_info', {'functionAddress': addr}, S) or {}
        entry = {'name': info.get('name') or item.get('name')}
        if info.get('signature'):
            entry['signature'] = info['signature']
        if info.get('className') or info.get('class'):
            entry['class'] = info.get('className') or info.get('class')
        funcs[norm_addr(addr)] = entry
    structs = {}
    dtypes = _call(tool, 'list_data_types', {'kind': 'struct'}, S)
    for item in (dtypes or []):
        nm = item.get('name')
        if not nm:
            continue
        d = _call(tool, 'get_data_type', {'name': nm}, S) or {}
        members = {}
        for fld in (d.get('fields') or []):
            off = fld.get('offset')
            if off is None:
                continue
            members[int(off)] = {'name': fld.get('name'),
                                 'type': fld.get('type') or 'undefined'}
        structs[nm] = {'size': d.get('size'), 'members': members}
    globals_ = {}
    gvars = _call(tool, 'get_global_variables', {}, S)
    for item in (gvars or []):
        addr = item.get('address') or item.get('addr')
        if addr is None or not item.get('name'):
            continue
        globals_[norm_addr(addr)] = {'name': item['name'], 'type': item.get('type')}
    return {'functions': funcs, 'structs': structs, 'globals': globals_, 'skips': {}}


def compute_verdict(diffs):
    """PROVEN=缺/变/多 任一 或 无理由 unverifiable ⇒ BROKEN（R4 fail-loud）。"""
    if diffs.get('missing') or diffs.get('changed') or diffs.get('extra'):
        return 'BROKEN'
    for u in (diffs.get('unverifiable') or []):
        if not u.get('reason'):
            return 'BROKEN'
    return 'PROVEN'


def _coverage(expected, actual, diffs):
    cov = {}
    for domain in ('functions', 'structs', 'globals', 'skips'):
        e = (expected or {}).get(domain) or {}
        a = (actual or {}).get(domain) or {}
        cov[domain] = {'expected': len(e), 'actual': len(a)}
    cov['diff_counts'] = {k: len(v) for k, v in (diffs or {}).items()}
    return cov


def main():
    ap = argparse.ArgumentParser(description='B 面导入 proof（回读对账）')
    ap.add_argument('--ann', required=True, help='annotation 目录')
    ap.add_argument('--gpr', required=True, help='Ghidra 项目路径（.gpr）')
    ap.add_argument('--program', default='PAL3.exe')
    ap.add_argument('--out', default=None, help='报告输出路径（默认 data/status/）')
    a = ap.parse_args()
    from import_via_daemon import notify, rpc, tool  # 传输层=标准通路
    rpc('initialize', {'protocolVersion': '2025-03-26', 'capabilities': {},
                       'clientInfo': {'name': 'proof', 'version': '1'}})
    notify('notifications/initialized')
    r = tool('create_session', {'binaryPath': a.gpr, 'programPath': a.program}, 2)
    txt = str((r.get('content') or [{}])[0].get('text', ''))
    assert 'id:' in txt, '会话创建失败=禁静默（2026-11-03 污染教训）: %s' % txt[:120]
    sid = txt.split('id:')[1].split()[0].strip('"')
    S = {'sessionId': sid}
    expected = project_ann_facts(a.ann)
    actual = project_b_facts(tool, S)
    diffs = diff_facts(expected, actual)
    verdict = compute_verdict(diffs)
    report = {'date': datetime.date.today().isoformat(), 'ann': a.ann, 'gpr': a.gpr,
              'session': sid, 'coverage': _coverage(expected, actual, diffs),
              'diffs': diffs, 'verdict': verdict}
    out = a.out or os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                                'data', 'status',
                                'b_import_proof_%s.json' % report['date'])
    os.makedirs(os.path.dirname(out), exist_ok=True)
    json.dump(report, open(out, 'w'), indent=1, ensure_ascii=False, default=str)
    print('verdict: %s | coverage: %s -> %s' % (
        verdict, {k: v['expected'] for k, v in report['coverage'].items() if isinstance(v, dict) and 'expected' in v}, out))
    return 0 if verdict == 'PROVEN' else 1


if __name__ == '__main__':
    sys.exit(main())
