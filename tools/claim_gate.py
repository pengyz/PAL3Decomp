"""R1 产生端闸（2026-10-29·复核 8c777315）——证据纪律机制化：
「补信息工程的任何推断必须挂 A 级证据，否则只是质疑」⇒ 产生端两条棘轮：
  ①未验认领禁增长（unverified_count ≤ baseline）②新多认领必入裁定台账
（存量多认领 grandfather 进 baseline 集）。check_annotations 消费；不阻断存量。
"""
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / 'data/status/claim_gate_baseline.json'
LEDGER = ROOT / 'data/status/pending/multi_claim_ledger.json'


def evaluate_claim_gate(unverified_count, unverified_baseline, multi_claims,
                        multi_baseline, ledger, gap_fill_unadjudicated=None,
                        red_flags=None):
    """双轨闸（P2）：(errors=硬红棘轮, warns=黄牌质疑)。
    硬红：未验增长/新多认领无台账；黄牌：gap_fill 无裁定/成员反证（索引不全禁硬判）。"""
    errs, warns = [], []
    if unverified_count > unverified_baseline:
        errs.append('CLAIM_GATE:unverified_growth %d>%d' % (unverified_count, unverified_baseline))
    for addr, clss in sorted((multi_claims or {}).items()):
        if addr in set(multi_baseline) or addr in set(ledger):
            continue
        errs.append('CLAIM_GATE:multi_claim_unadjudicated:%s' % addr)
    for a in (gap_fill_unadjudicated or []):
        warns.append('CLAIM_GATE:gap_fill_unadjudicated:%s' % a)
    for a in (red_flags or []):
        warns.append('CLAIM_GATE:member_counter_evidence:%s' % a)
    return errs, warns


def load_state():
    b = json.load(open(BASELINE)) if BASELINE.exists() else {}
    led = set()
    if LEDGER.exists():
        led = {c['addr'] for c in json.load(open(LEDGER)).get('adjudicated', [])}
    return b, led


def save_baseline(unverified_count, multi_addrs):
    BASELINE.write_text(json.dumps(
        {'unverified_baseline': unverified_count,
         'multi_baseline': sorted(multi_addrs)}, ensure_ascii=False, indent=2))


def main():
    """状态收集（多认领=地址被≥2 类 methods 认领；未验=evidence_level∉{A,B,verified}）。"""
    import glob
    unv = 0
    claims = {}
    for f in glob.glob(str(ROOT / 'data/annotations/structs/*.json')):
        d = json.load(open(f))
        nm = d.get('name')
        for k, v in (d.get('methods') or {}).items():
            if not isinstance(v, dict):
                continue
            if v.get('evidence_level') not in ('A', 'B', 'verified'):
                unv += 1
            claims.setdefault(k, []).append(nm)
    multi = {a: cs for a, cs in claims.items() if len(set(cs)) > 1}
    gap_un = []
    for f in glob.glob(str(ROOT / 'data/annotations/structs/*.json')):
        d = json.load(open(f))
        for k, v in (d.get('methods') or {}).items():
            if isinstance(v, dict) and 'gap_fill' in json.dumps(v) and not v.get('adjudication'):
                gap_un.append(k)
    red = []
    gc = ROOT / 'data/status/attribution_guard_census.json'
    if gc.exists():
        red = [x['addr'] for x in json.load(open(gc)).get('red', [])]
    b, led = load_state()
    errs, warns = evaluate_claim_gate(
        unv, b.get('unverified_baseline', unv), multi,
        set(b.get('multi_baseline', [])) | set(multi) if not b else set(b.get('multi_baseline', [])), led,
        gap_fill_unadjudicated=gap_un, red_flags=red)
    return errs, warns, unv, multi


if __name__ == '__main__':
    errs, warns, unv, multi = main()
    print('unverified=%d multi=%d errs=%d warns=%d' % (unv, len(multi), len(errs), len(warns)))
    for e in errs[:10]:
        print(' ', e)
    for w in warns[:5]:
        print('  warn:', w)
