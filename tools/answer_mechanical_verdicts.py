"""R7×P 档机械裁定（2026-10-30）——字节真值可判定面自动裁断（合用户铁律：
准确=判定，不准确=不判定）。裁定单源=structs methods.adjudication（claim_gate 消费），
卡面 answer 同步镜像。用法: python3 tools/answer_mechanical_verdicts.py
"""
import glob
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def _norm(a):
    try:
        return int(str(a), 16)
    except ValueError:
        return None


def verdict_for(card, p_index):
    """P 档字节真值→裁定 (value, evidence)；无可判证据→None（留人裁）。"""
    key = (card.get('class'), _norm(card.get('addr')))
    hit = p_index.get(key)
    if not hit:
        return None
    kind, extra = hit
    if kind == 'P:vtable_confirmed':
        return 'confirmed', 'vtable 槽字节真值（B2a located 表实含）'
    if kind == 'P:misowned':
        return 'rejected', '正向反证：认领类表已定位且不含，他表实含（%s）' % (extra or '?')
    if kind == 'P:multi_owned':
        return 'shared_impl', '多表实含（合成物/共享实现形，Destroy__ovl_03 同款）'
    return None


def main():
    cen = json.load(open(ROOT / 'data/status/vtable_ownership_census.json'))
    p_index = {}
    owner_by_addr = {}
    for kind, key in (('P:vtable_confirmed', 'vtable_confirmed'),
                      ('P:misowned', 'misowned'), ('P:multi_owned', 'multi_owned')):
        for nm, addr, name in cen.get(key, []):
            n = _norm(addr)
            p_index[(nm, n)] = (kind, None)
            owner_by_addr.setdefault(n, set()).add(nm)
    for (nm, n), (kind, _) in list(p_index.items()):
        if kind == 'P:misowned':
            others = owner_by_addr.get(n, set()) - {nm}
            p_index[(nm, n)] = (kind, '/'.join(sorted(others)))
    # 交叉卡池
    cards = json.load(open(ROOT / 'data/status/pending/gap_fill_adjudication_20261029.json'))
    answered = 0
    touched = {}
    for c in cards['cards']:
        if c.get('answer'):
            continue
        v = verdict_for(c, p_index)
        if not v:
            continue
        val, ev = v
        c['answer'] = val
        c['evidence'] = ev
        c['adjudicator'] = 'mechanical:P-tier'
        answered += 1
        touched.setdefault(c['class'], set()).add((c['addr'], val))
    # 单源回写：structs methods.adjudication（claim_gate 合法裁定集内）
    for f in glob.glob(str(ROOT / 'data/annotations/structs/*.json')):
        d = json.load(open(f))
        nm = d.get('name')
        ch = False
        for addr, val in touched.get(nm, ()):
            m = (d.get('methods') or {}).get(addr)
            if isinstance(m, dict) and not m.get('adjudication'):
                m['adjudication'] = val
                ch = True
        if ch:
            json.dump(d, open(f, 'w'), ensure_ascii=False, indent=2)
    json.dump(cards, open(ROOT / 'data/status/pending/gap_fill_adjudication_20261029.json', 'w'),
              ensure_ascii=False, indent=2)
    remain = sum(1 for c in cards['cards'] if not c.get('answer'))
    print('机械裁定 %d | 余留人裁 %d' % (answered, remain))


if __name__ == '__main__':
    main()
