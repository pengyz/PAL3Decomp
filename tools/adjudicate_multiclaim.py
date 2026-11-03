#!/usr/bin/env python3
"""多注组成员实访裁决引擎（A 案·2026-11-03）。
判据（CLAUDE.md 归属红线）：函数内 this->member 引用的成员在目标类存在且在他候选类不存在。
纯函数 score_candidates 先行（R15）。"""
import json, glob, re, os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def score_candidates(accessed, class_members):
    """accessed: set[str] 函数实访成员；class_members: {cls: set[str]}。
    返回 [(cls, hit_count, unique_hits)] 降序。unique_hits=只在该类存在的实访成员。"""
    out = []
    for cls, mem in class_members.items():
        hits = accessed & mem
        if not hits:
            continue
        others = set().union(*[v for k, v in class_members.items() if k != cls]) if len(class_members) > 1 else set()
        uniq = hits - others
        out.append((cls, len(hits), len(uniq), sorted(hits)[:5]))
    out.sort(key=lambda x: (-x[2], -x[1]))
    return out


def extract_accessed(decomp_text):
    """decomp 渲染文本 → 实访成员名集（this->X / this.field 形）。"""
    return set(re.findall(r'this->(\w+)', decomp_text)) | set(re.findall(r'this\.(\w+)', decomp_text))


def main():
    remain = json.load(open('/tmp/remain_conflicts.json'))
    raw, bases = {}, {}
    for f in glob.glob(os.path.join(ROOT, 'data/annotations/structs/*.json')):
        d = json.load(open(f))
        km = d.get('known_members')
        items = km.values() if isinstance(km, dict) else (km or [])   # dict 形=偏移键（曾误迭代键致 no-hits）
        names = set()
        for m in items:
            if isinstance(m, dict):
                names.add(m.get('name') or '')
            elif isinstance(m, str) and not m.isdigit():
                names.add(m)
        raw[d.get('name')] = names
        bases[d.get('name')] = [b.get('name') for b in (d.get('bases') or []) if isinstance(b, dict)]
    def closure(cls, seen=None):
        seen = seen or set()
        if cls in seen or cls not in raw:
            return set()
        seen.add(cls)
        out = set(raw[cls])
        for b in bases.get(cls, []):
            out |= closure(b, seen)
        return out
    members = {c: closure(c) for c in raw}
    verdicts, unclear = [], []
    for addr, cands in remain.items():
        a = addr.lower()
        a = a[2:] if a.startswith('0x') else a   # lstrip 陷阱禁用（剥光前导零）
        df = glob.glob(os.path.join(ROOT, 'asm/pal3/decomp/*_%s.json' % a))
        if not df:
            unclear.append((addr, [c['class'] for c in cands], 'no-decomp'))
            continue
        text = json.dumps(json.load(open(df[0])))
        accessed = extract_accessed(text)
        cm = {c['class']: members.get(c['class'], set()) for c in cands}
        ranking = score_candidates(accessed, cm)
        if ranking and ranking[0][2] >= 2 and (len(ranking) == 1 or ranking[0][2] > ranking[1][2]):
            verdicts.append({'addr': addr, 'winner': ranking[0][0], 'unique_hits': ranking[0][2],
                             'evidence': ranking[0][3], 'candidates': [c['class'] for c in cands]})
        else:
            unclear.append((addr, [c['class'] for c in cands], ranking[:2] if ranking else 'no-hits'))
    json.dump({'verdicts': verdicts, 'unclear': [{'addr': a, 'cands': c, 'why': str(w)[:120]} for a, c, w in unclear]},
              open('data/status/multiclaim_adjudication_20261103.json', 'w'), indent=1, ensure_ascii=False)
    print('机械可裁: %d | 人裁余: %d' % (len(verdicts), len(unclear)))
    for v in verdicts[:5]:
        print(' ', v['addr'], '→', v['winner'], 'uniq=%d' % v['unique_hits'], v['evidence'])


if __name__ == '__main__':
    main()
