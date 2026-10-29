"""归属守卫（B1，2026-10-29）——CLAUDE.md 归属规则工具化：
「禁止仅凭 signature this 修正函数归属——必须有 decomp member access evidence
（this->member 在目标类存在且不在原类存在）」⇒ 机械化为红/黄牌信号。

红牌 RED:member_in_other_class —— 体访问 this->X 且 X∉声明类成员而∈他类成员（反证）
黄牌 YELLOW:unverified+crosscast —— 认领未验 且 体含异类 this 转换
绿 —— 无信号（不等于已验，只等于无反证）

用法: python3 tools/audit_attribution_guard.py > census 输出 data/status/
"""
import glob
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
THIS_REF = re.compile(r'(?:this->|&this->)(\w+)')
CAST = re.compile(r'\(\((\w+) \*\)this\)')


def build_member_index(ida_structs, structs_jsons):
    """B2b：成员索引双源合并——ida_structs.data_members ∪ structs.known_members。"""
    idx = {}
    for nm, d in (ida_structs or {}).items():
        s = set(idx.setdefault(nm, set()))
        for m in (d or {}).get('data_members') or []:
            if isinstance(m, dict) and m.get('name'):
                s.add(m['name'])
        idx[nm] = s
    for nm, d in (structs_jsons or {}).items():
        s = set(idx.setdefault(nm, set()))
        for m in (d or {}).get('known_members') or []:
            if isinstance(m, dict) and m.get('name'):
                s.add(m['name'])
        idx[nm] = s
    return idx


def extract_this_member_refs(body):
    """体中 this->成员 引用名集合。"""
    return set(THIS_REF.findall(body))


def classify_claim(body, claimed, claimed_members, other_classes,
                   evidence_level, cross_casts):
    """单条认领判牌。claimed_members/other_classes={cls:set(members)}。"""
    flags = []
    refs = extract_this_member_refs(body)
    missing = set()
    for m in refs:
        if m in claimed_members:
            continue
        for cls, mems in other_classes.items():
            if m in mems and cls != claimed:
                missing.add(m)
                break
    if missing:
        flags.append('RED:member_in_other_class')
    elif (evidence_level in (None, 'unverified')) and cross_casts:
        flags.append('YELLOW:unverified+crosscast')
    return {'flags': flags, 'refs': sorted(refs), 'missing': sorted(missing)}


def main():
    structs = {}
    for f in glob.glob(str(ROOT / 'data/annotations/structs/*.json')):
        d = json.load(open(f))
        if d.get('name'):
            structs[d['name']] = d
    ida_s = json.load(open(ROOT / 'asm/pal3/ida_structs.json'))
    members = build_member_index(ida_s, structs)
    out = []
    for nm, d in structs.items():
        for addr, info in (d.get('methods') or {}).items():
            if not isinstance(info, dict):
                continue
            body = ''
            for f in glob.glob(str(ROOT / ('asm/pal3/decomp/*%s*.json' % addr[-6:].lower()))):
                try:
                    body = json.load(open(f)).get('decompiled_c', '') or ''
                except Exception:
                    pass
                if body:
                    break
            sig = classify_claim(
                body=body, claimed=nm,
                claimed_members=members.get(nm, set()),
                other_classes={c: members[c] for c in members if c != nm},
                evidence_level=info.get('evidence_level'),
                cross_casts=set(CAST.findall(body)))
            if sig['flags']:
                out.append({'class': nm, 'addr': addr,
                            'name': info.get('name'), 'flags': sig['flags'],
                            'missing': sig['missing'][:5]})
    red = [o for o in out if o['flags'][0].startswith('RED')]
    yel = [o for o in out if o['flags'][0].startswith('YELLOW')]
    res = {'red_count': len(red), 'yellow_count': len(yel),
           'red': red[:200], 'yellow_sample': yel[:50]}
    Path(ROOT / 'data/status/attribution_guard_census.json').write_text(
        json.dumps(res, ensure_ascii=False, indent=2))
    print('RED %d · YELLOW %d → data/status/attribution_guard_census.json' % (len(red), len(yel)))


if __name__ == '__main__':
    main()
