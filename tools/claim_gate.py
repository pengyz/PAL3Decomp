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


VALID_ADJ = {'confirmed', 'rejected', 'shared_impl', 'transplant_valid'}


def evaluate_claim_gate(unverified_count, unverified_baseline, multi_claims,
                        multi_baseline, ledger, gap_fill_unadjudicated=None,
                        red_flags=None, level_a_no_evidence_count=0,
                        ledger_entries=None, gap_fill_adjudged=None,
                        p_count=None, p_baseline=None):
    """双轨闸（P2）：(errors=硬红棘轮, warns=黄牌质疑)。
    硬红：未验增长/新多认领无台账；黄牌：gap_fill 无裁定/成员反证（索引不全禁硬判）。"""
    errs, warns = [], []
    # R1-a：证据伴随校验——level∈{A,B} 但无证据指针仍计未验（堵洗绿）
    _eff_unv = unverified_count + (level_a_no_evidence_count or 0)
    if _eff_unv > unverified_baseline:
        errs.append('CLAIM_GATE:unverified_growth %d>%d' % (_eff_unv, unverified_baseline))
    _le = ledger_entries or {}
    for addr, clss in sorted((multi_claims or {}).items()):
        if addr in set(multi_baseline):
            continue
        if addr in set(ledger) and (_le.get(addr) or {}).get('answer'):
            continue          # F3：台账准入须有裁定内容（空裁定不消）
        errs.append('CLAIM_GATE:multi_claim_unadjudicated:%s' % addr)
    for a in (gap_fill_unadjudicated or []):
        warns.append('CLAIM_GATE:gap_fill_unadjudicated:%s' % a)
    # F4：adjudication 须落合法裁定集（任意真值消音=洗白路径堵死）
    for a, v in sorted((gap_fill_adjudged or {}).items()):
        if v not in VALID_ADJ:
            errs.append('CLAIM_GATE:gap_fill_invalid_adjudication:%s:%s' % (a, v))
    # F5：P 档回退=硬红（字节真值判定数禁降）
    if p_count is not None and p_baseline is not None and p_count < p_baseline:
        errs.append('CLAIM_GATE:p_verdict_regression %d<%d' % (p_count, p_baseline))
    for a in (red_flags or []):
        warns.append('CLAIM_GATE:member_counter_evidence:%s' % a)
    return errs, warns


def load_state():
    """R1-b：基线缺失=fail-loud（禁自动重自举洗白）。"""
    if not BASELINE.exists() or json.load(open(BASELINE)) == {}:
        return {'ERROR': 'baseline_missing'}, set()
    b = json.load(open(BASELINE))
    led, le = set(), {}
    if LEDGER.exists():
        for c in json.load(open(LEDGER)).get('adjudicated', []):
            le[c['addr']] = c
            led.add(c['addr'])
    return b, led, le


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
    la_no_ev = 0
    adjudged = {}
    for f in glob.glob(str(ROOT / 'data/annotations/structs/*.json')):
        d = json.load(open(f))
        for k, v in (d.get('methods') or {}).items():
            if not isinstance(v, dict):
                continue
            if v.get('evidence_level') in ('A', 'B') and not (v.get('source') or v.get('evidence')):
                la_no_ev += 1
            if v.get('adjudication') is not None:
                adjudged[k] = v['adjudication']
    pc = ROOT / 'data/status/vtable_ownership_census.json'
    if not pc.exists():
        return ['CLAIM_GATE:census_missing (vtable_ownership_census.json 删除即洗牌=堵死)'], [], unv, multi
    p_count = sum(json.load(open(pc)).get('verdict_counts', {}).get(k, 0)
                  for k in ('P:vtable_confirmed', 'P:multi_owned', 'P:misowned'))
    b, led, le = load_state()
    if 'ERROR' in b:
        return ['CLAIM_GATE:baseline_missing (fail-loud 禁自举)'], [], unv, multi
    errs, warns = evaluate_claim_gate(
        unv, b.get('unverified_baseline', unv), multi,
        set(b.get('multi_baseline', [])) | set(multi) if not b else set(b.get('multi_baseline', [])), led,
        gap_fill_unadjudicated=gap_un, red_flags=red,
        level_a_no_evidence_count=la_no_ev, ledger_entries=le,
        gap_fill_adjudged=adjudged, p_count=p_count,
        p_baseline=b.get('p_baseline', p_count))
    return errs, warns, unv, multi


if __name__ == '__main__':
    errs, warns, unv, multi = main()
    print('unverified=%d multi=%d errs=%d warns=%d' % (unv, len(multi), len(errs), len(warns)))
    for e in errs[:10]:
        print(' ', e)
    for w in warns[:5]:
        print('  warn:', w)
