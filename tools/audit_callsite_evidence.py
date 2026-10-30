"""P3 调用面证据（2026-10-30）——调用形三分类作归属第三证据源。
调用形语义：member（接收者调用=成员性强）· qualified（类限定=类作用域形）·
bare（裸调=自由形反信号）。均为质疑级增强（不判定），佐人裁。
用法: python3 tools/audit_callsite_evidence.py
"""
import glob
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def classify_call_form(line, name):
    """单行调用形分类：member/qualified/bare；非调用→None。"""
    esc = re.escape(name)
    if re.search(r'(->|\.)\s*(?:\w+::)?' + esc + r'\b\s*\(', line):
        return 'member'
    if re.search(r'\b\w+::' + esc + r'\b\s*\(', line):
        return 'qualified'
    if re.search(r'(?<![\w:.>:])' + esc + r'\b\s*\(', line):
        return 'bare'
    return None


def summarize_callsites(texts, name):
    s = {'member': 0, 'qualified': 0, 'bare': 0}
    for t in texts:
        for line in t.splitlines():
            k = classify_call_form(line, name)
            if k:
                s[k] += 1
    return s


def main():
    corpus = []
    for f in glob.glob(str(ROOT / 'asm/pal3/decomp/*.json')):
        try:
            d = json.load(open(f))
            c = d.get('decompiled_c')
            if c:
                corpus.append(c)
        except Exception:
            pass
    for f in glob.glob(str(ROOT / 'pal3/src/**/*.cpp'), recursive=True):
        corpus.append(open(f, errors='replace').read())
    print('语料 %d 件' % len(corpus))
    out = {}
    for qf in ('gap_fill_adjudication_20261029.json', 'attribution_questions_20261029.json'):
        p = ROOT / 'data/status/pending' / qf
        if not p.exists():
            continue
        q = json.load(open(p))
        cardsets = [q.get('cards') or []]
        if q.get('rowtable_batch'):
            cardsets.append(q['rowtable_batch'].get('cards') or [])
        for cs in cardsets:
            for c in cs:
                nm = c.get('claim') or ''
                if not nm or c.get('callsite_evidence'):
                    continue
                s = summarize_callsites(corpus, nm)
                if s['member'] or s['qualified'] or s['bare']:
                    c['callsite_evidence'] = s
                    c['question'] = (c.get('question') or '') + \
                        '【调用面：member=%d qualified=%d bare=%d】' % (s['member'], s['qualified'], s['bare'])
        json.dump(q, open(p, 'w'), ensure_ascii=False, indent=2)
        out[qf] = sum(1 for cs in cardsets for c in cs if c.get('callsite_evidence'))
    print('证据包充实:', out)


if __name__ == '__main__':
    main()
