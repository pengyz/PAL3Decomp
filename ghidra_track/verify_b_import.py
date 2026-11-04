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
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from verify_core import diff_facts, norm_addr, project_ann_facts  # noqa: E402


def _call(tool, name, args, S):
    """daemon 调用 → 返回**原文**（daemon 出 YAML-ish 表形非 JSON——T10 实测；
    解析器接管）。失败返回 None（通道缺席语义，不崩）。"""
    r = tool(name, dict(S, **args), 1)
    if not isinstance(r, dict) or r.get('isError'):
        return None
    try:
        return str((r.get('content') or [{}])[0].get('text', ''))
    except (IndexError, KeyError):
        return None


def _parse_list(text):
    """daemon 列表态（'key:\n  - k: v' 列表项）→ [dict]。"""
    if not text:
        return []
    entries, cur = [], None
    for line in text.splitlines():
        s = line.strip()
        if s.startswith('- '):
            if cur:
                entries.append(cur)
            cur = {}
            s = s[2:]
        m = re.match(r'^(\w+):\s*(.*)$', s)
        if m and cur is not None:
            v = m.group(2).strip().strip('"')
            cur[m.group(1)] = None if v in ('', 'undefined', 'null') else v
    if cur:
        entries.append(cur)
    return entries


def _parse_kv(text):
    """daemon 平铺 kv 态（get_function_info）→ dict。"""
    out = {}
    if not text:
        return out
    for line in text.splitlines():
        m = re.match(r'^(\w+):\s*(.*)$', line.strip())
        if m:
            v = m.group(2).strip().strip('"')
            out[m.group(1)] = None if v in ('', 'undefined', 'null') else v
    return out


def _parse_table(text):
    """daemon 表态（'X[N]{cols}:' + CSV 行）→ [dict]（list_data_types 实形 T10 探）。"""
    out, cols = [], None
    for line in (text or '').splitlines():
        s = line.strip()
        m = re.match(r'\w+\[\d+\]\{(.+)\}:', s)
        if m:
            cols = [c.strip() for c in m.group(1).split(',')]
            continue
        if cols and s and ',' in s and not re.match(r'^\w+: ', s):
            vals = [v.strip().strip('"') for v in s.split(',')]
            out.append(dict(zip(cols, vals + [None] * (len(cols) - len(vals)))))
    return out


def _parse_dtype(text):
    """get_data_type 表态（kv + fields[N]{cols}: + CSV 行）→ dict{name,size,fields}。"""
    out = {'fields': []}
    if not text:
        return out
    cols = None
    for line in text.splitlines():
        s = line.strip()
        m = re.match(r'fields\[\d+\]\{(.+)\}:', s)
        if m:
            cols = [c.strip() for c in m.group(1).split(',')]
            continue
        m = re.match(r'^(\w+):\s*(.*)$', s)
        if m and cols is None:
            v = m.group(2).strip().strip('"')
            if v in ('', 'undefined', 'null'):
                out[m.group(1)] = None
            elif m.group(1) in ('size', 'alignment') and v.isdigit():
                out[m.group(1)] = int(v)   # 数值强转（str '8' vs int 8=diff 假红）
            elif m.group(1) != 'fields':
                out[m.group(1)] = v
            continue
        if cols and (',' in s) and not s.startswith('-'):
            vals = [v.strip().strip('"') for v in s.split(',')]
            row = dict(zip(cols, vals + [None] * (len(cols) - len(vals))))
            out['fields'].append({k: (None if v in ('', 'undefined', 'null') else v)
                                 for k, v in row.items()})
    return out


def project_b_facts(tool, S, page=500):
    """B 程序回读 → canonical facts（真形解析：list/kv/fields 三态+分页）。"""
    funcs = {}
    offset = 0
    while True:
        txt = _call(tool, 'list_functions', {'offset': offset, 'limit': page}, S)
        items = _parse_list(txt)
        if not items:
            break
        for item in items:
            addr = item.get('address') or item.get('entryPoint')
            if not addr or ':' in str(addr):
                continue
            info = _parse_kv(_call(tool, 'get_function_info', {'address': addr}, S) or '')
            entry = {'name': item.get('name') or info.get('name')}
            sig = info.get('signature') or item.get('signature')
            if sig:
                # daemon 形 'undefined NAME(void)' → 去类型前缀保留形
                entry['signature'] = re.sub(r'^undefined\s+', '', str(sig))
            funcs[norm_addr(addr)] = entry
        if len(items) < page:
            break
        offset += page
    structs = {}
    offset = 0
    while True:
        txt = _call(tool, 'list_data_types', {'offset': offset, 'limit': page}, S)
        items = _parse_table(txt) or _parse_list(txt)
        if not items:
            break
        for item in items:
            nm = item.get('name')
            if not nm:
                continue
            d = _parse_dtype(_call(tool, 'get_data_type', {'name': nm}, S) or '')
            members = {}
            for fld in (d.get('fields') or []):
                if not isinstance(fld, dict):
                    continue  # 行形不齐防御（T10 崩溃钉：某型无表头形）
                off = fld.get('offset')
                nm2 = fld.get('name')
                if off is None or nm2 in (None, 'null'):
                    continue  # 未名字节=非 annotation 面（不计）
                members[int(off)] = {'name': nm2,
                                     'type': fld.get('dataType') or 'undefined'}
            structs[nm] = {'size': d.get('size'), 'members': members}
        if len(items) < page:
            break
        offset += page
    globals_ = {}
    offset = 0
    while True:
        txt = _call(tool, 'list_data_symbols', {'offset': offset, 'limit': page}, S)
        items = _parse_list(txt)
        if not items:
            break
        for item in items:
            addr = item.get('address')
            if not addr or ':' in str(addr) or not item.get('name'):
                continue  # EXTERNAL:/段前缀=导入面非注解全局
            globals_[norm_addr(addr)] = {'name': item['name'],
                                         'type': item.get('dataType')}
        if len(items) < page:
            break
        offset += page
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
