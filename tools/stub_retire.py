#!/usr/bin/env python3
"""tools/stub_retire.py — stub↔S2 退役对账（方案 v2 §2，M3）。

盘点口径表（方案 v2 §2，先钉死）：
  phase2/stubs/*_stub.cpp（平层）      unit   计入 S3 存量（主口径）· 退役=删文件
  phase2/stubs/_slots/**               slots  计入 S3 符号口径 · 退役=剔条目
  phase2/stubs/_supply/**              supply 计入 S3 符号口径 · 退役=ledger retired+重生成
  phase2/stubs/_eh_metadata_stub.cpp   glue   不计（恒存）
  phase2/stubs/_real/**                real   不计（真函数回填面）
  **/*.obj                             排除（编译产物，禁入源码树）

规则（S1–S4，消 v1 的 Rn 双义）：
  S1 催删：S2-ok 单元仍有 unit stub ⇒ WARN+retire_due；--strict ⇒ exit 1
  S2 催建：S2-fail 单元缺 unit stub ⇒ FAIL-LOUD
  S3 双口径棘轮：单元数+全 stub 面符号总数 非增；增长须归因
     （enum: retire/new_unit/regression/census_refresh/rebaseline）
  S4 读数：覆盖率（census 四元组口径）+ 存量 + retire_due 只读展示

台账（m4_ratchet.json，append-only 哈希链——改写历史可检出）：
  写者=本工具 record；执行者=M4 轮次流程（方案 v2 §2）。
用法:
  python tools/stub_retire.py check [--strict]
  python tools/stub_retire.py plan
  python tools/stub_retire.py record --reason <enum> [--evidence <str>]
"""
import argparse
import hashlib
import json
import re
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
CENSUS = PROJECT_ROOT / 'data' / 'status' / 'probe_census.json'
STUB_ROOT = PROJECT_ROOT / 'phase2' / 'stubs'
RATCHET = PROJECT_ROOT / 'data' / 'status' / 'm4_ratchet.json'
DEBT = PROJECT_ROOT / 'data' / 'status' / 'pruned_debt.json'

GROWTH_REASONS = {'new_unit', 'regression', 'census_refresh', 'rebaseline'}
REASONS = GROWTH_REASONS | {'retire', 'prune', 'supply_regen', 'initial'}

_UNIT_HDR_RE = re.compile(r'^// Stub for S2-fail unit: (.+)$', re.M)


# ── 盘点（口径表的机械化）─────────────────────────────────────────
def classify_stubs():
    """→ {'unit': {unit: path}, 'slots_files': n, 'supply_files': n, 'glue': n,
         'real_files': n, 'obj_excluded': n}"""
    out = {'unit': {}, 'slots_files': 0, 'supply_files': 0, 'glue': 0,
           'real_files': 0, 'obj_excluded': 0}
    for f in sorted(STUB_ROOT.rglob('*')):
        if f.suffix == '.obj':
            out['obj_excluded'] += 1
            continue
        if f.suffix != '.cpp':
            continue
        rel = f.relative_to(STUB_ROOT).as_posix()
        if rel.startswith('_slots/'):
            out['slots_files'] += 1
        elif rel.startswith('_supply/'):
            out['supply_files'] += 1
        elif rel.startswith('_real/'):
            out['real_files'] += 1
        elif f.name == '_eh_metadata_stub.cpp':
            out['glue'] += 1
        else:
            m = _UNIT_HDR_RE.search(f.read_text(encoding='utf-8', errors='replace'))
            unit = m.group(1).strip() if m else rel.replace('_stub.cpp', '.cpp')
            out['unit'][unit] = f
    return out


def stub_symbol_count():
    """全 stub 面符号总数（S3 符号口径；复用 stub_gen.span 机制）。"""
    sys.path.insert(0, str(PROJECT_ROOT / 'tools'))
    from stub_gen import stub_function_spans
    n = 0
    for f in STUB_ROOT.rglob('*.cpp'):
        n += len(stub_function_spans(f.read_text(encoding='utf-8', errors='replace')))
    return n


def census_reading():
    """census 四元组（方案 v2 F4 修：generated_at+unit-set hash+ok+分母）。"""
    if not CENSUS.exists():
        return None
    c = json.loads(CENSUS.read_text(encoding='utf-8'))
    s2 = c['s2']
    units = sorted(x['unit'] for x in s2['results'])
    return {
        'generated_at': c.get('generated_at'),
        'total': s2['total'], 'ok': s2['ok'],
        'unit_set_hash': hashlib.sha256('\n'.join(units).encode()).hexdigest()[:16],
        'errors_total': sum(len(x.get('errors', [])) for x in s2['results']),
    }


# ── 台账（append-only 哈希链）─────────────────────────────────────
def load_ratchet():
    if not RATCHET.exists():
        return []
    d = json.loads(RATCHET.read_text(encoding='utf-8'))
    chain = d.get('snapshots', [])
    # 改写历史检出：逐环重算
    prev = 'genesis'
    for s in chain:
        want = hashlib.sha256((prev + json.dumps({k: v for k, v in s.items()
                                                  if k != 'hash'}, sort_keys=True)
                               ).encode()).hexdigest()
        if s.get('hash') != want:
            return ('TAMPERED', chain)
        prev = s['hash']
    return chain


def append_snapshot(reason, evidence):
    chain = load_ratchet()
    if isinstance(chain, tuple):
        return None, '台账被改写（哈希链断），拒绝 record'
    if reason not in REASONS:
        return None, '归因越枚举: %s（%s）' % (reason, '/'.join(sorted(REASONS)))
    cls = classify_stubs()
    snap = {
        'seq': len(chain),
        'reason': reason,
        'evidence': evidence or '',
        'unit_stubs': len(cls['unit']),
        'stub_symbols': stub_symbol_count(),
        'coverage': census_reading(),
    }
    prev = chain[-1]['hash'] if chain else 'genesis'
    snap['hash'] = hashlib.sha256((prev + json.dumps(snap, sort_keys=True)).encode()).hexdigest()
    chain.append(snap)
    RATCHET.write_text(json.dumps({'snapshots': chain}, ensure_ascii=False, indent=2) + '\n',
                       encoding='utf-8')
    return snap, None


# ── S1/S2 对账 ───────────────────────────────────────────────────
def reconcile():
    c = json.loads(CENSUS.read_text(encoding='utf-8'))
    cls = classify_stubs()
    s2 = {x['unit']: x.get('status') for x in c['s2']['results']}
    retire_due, missing = [], []
    for unit, st in s2.items():
        has_stub = unit in cls['unit']
        if st == 'ok' and has_stub:
            retire_due.append(unit)
        if st != 'ok' and not has_stub:
            missing.append(unit)
    # 反向面：stub 存在但 census 无此单元（new_unit/陈旧）
    orphan = [u for u in cls['unit'] if u not in s2]
    return cls, retire_due, missing, orphan


def cmd_check(args):
    cls, retire_due, missing, orphan = reconcile()
    cov = census_reading()
    print('[stub_retire] census %s | 单元 ok %d/%d | 错误 %d'
          % (cov['generated_at'], cov['ok'], cov['total'], cov['errors_total']))
    print('[stub_retire] 存量: unit %d | slots %d 文件 | supply %d 文件 | real %d 文件'
          ' | glue %d | obj 排除 %d | 符号 %d'
          % (len(cls['unit']), cls['slots_files'], cls['supply_files'],
             cls['real_files'], cls['glue'], cls['obj_excluded'], stub_symbol_count()))
    rc = 0
    # S2（催建）先判
    if missing:
        print('[S2] FAIL-LOUD: %d 个 S2-fail 单元缺 stub:' % len(missing))
        for u in missing[:10]:
            print('   %s' % u)
        rc = 2
    # S1（催删）
    if retire_due:
        print('[S1] retire_due %d 个 S2-ok 单元仍有 stub（plan 出清单）:' % len(retire_due))
        for u in retire_due[:10]:
            print('   %s' % u)
        if args.strict or (DEBT.exists() and len(retire_due) > 30):
            print('[S1] --strict/阈值触发 ⇒ exit 1')
            rc = rc or 1
    if orphan:
        print('[S1] 反向面: %d 个 stub 无 census 单元对应（陈旧/new_unit）: %s'
              % (len(orphan), orphan[:5]))
    # S3（双口径棘轮）
    chain = load_ratchet()
    if isinstance(chain, tuple):
        print('[S3] 台账哈希链断（改写历史）⇒ exit 1')
        return 1
    if chain:
        last = chain[-1]
        nu, ns = len(cls['unit']), stub_symbol_count()
        if (nu > last['unit_stubs'] or ns > last['stub_symbols']) \
                and last['reason'] not in GROWTH_REASONS:
            print('[S3] 存量增长无归因放行（上次归因=%s）: unit %d>%d sym %d>%d'
                  % (last['reason'], nu, last['unit_stubs'], ns, last['stub_symbols']))
            rc = rc or 1
        else:
            print('[S3] 对上快照 seq=%d（reason=%s）: unit %d vs %d | sym %d vs %d'
                  % (last['seq'], last['reason'], nu, last['unit_stubs'],
                     ns, last['stub_symbols']))
    else:
        print('[S3] 无台账快照——先 record（initial）')
    print('[S4] 覆盖率 %d/%d = %.0f%%（unit_set %s）'
          % (cov['ok'], cov['total'], 100.0 * cov['ok'] / max(cov['total'], 1),
             cov['unit_set_hash']))
    return rc


def cmd_plan(args):
    _, retire_due, _, _ = reconcile()
    print('退役建议清单（v1 只打印——实删=人工+mock_link 闭合回归+git 面确认）:')
    for u in retire_due:
        print('  del %s' % u)
    print('共 %d' % len(retire_due))
    return 0


def cmd_record(args):
    snap, err = append_snapshot(args.reason, args.evidence)
    if err:
        print('record FAIL: %s' % err)
        return 1
    print('record ok: seq=%d unit=%d sym=%d reason=%s'
          % (snap['seq'], snap['unit_stubs'], snap['stub_symbols'], snap['reason']))
    return 0


def main():
    ap = argparse.ArgumentParser(description='stub↔S2 退役对账（方案 v2 §2）')
    sub = ap.add_subparsers(dest='cmd', required=True)
    p = sub.add_parser('check')
    p.add_argument('--strict', action='store_true')
    sub.add_parser('plan')
    p = sub.add_parser('record')
    p.add_argument('--reason', required=True, choices=sorted(REASONS))
    p.add_argument('--evidence', default='')
    args = ap.parse_args()
    return {'check': cmd_check, 'plan': cmd_plan, 'record': cmd_record}[args.cmd](args)


if __name__ == '__main__':
    sys.exit(main())
