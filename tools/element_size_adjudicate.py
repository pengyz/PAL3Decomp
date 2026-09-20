#!/usr/bin/env python3
"""只读：把 element-size 站点裁成 raw_site + ownership_candidate 两层（Spike D1-T4）。

**分层纪律（三路复核要求）**：
- `raw_site` 只含 **地址/字节/字面量**（`site/line/kind/ptr/size/count/ctor/dtor`）✓，
  逐字段原样回填、不做任何推断；
- 注解派生的 ctor/dtor 归属**只能进 `ownership_candidate`**，且每条都标
  `evidence='annotation(lowered)'`；该层带 `evidence_layer='lowered'` 与 `a_evidence=False`
  ⇒ **永不直接产生 class 级 A 证据**（A 级证据必须来自指令里的 reg+disp32/绝对地址）✓。

**与计划任务 4 代码的差异（在真实产物上验证后修正，见 docs/specs 计划与提交说明）**：
1. `_ctor_to_class` 的键必须**归一化**：注解键是 `0x00411900`（8 位带前导零），站点值是
   `0x411900` ⇒ 直接 `lower()` 匹配会把 466 站点里的全部归属候选丢光。这里按
   `'0x'+hex.lower().lstrip('0')` 归一化（大小写不敏感 + 去前导零）。
2. `ctor`/`dtor`/`ptr` 可能是**寄存器**（`ecx`）、**内存操作数**、**名字改编符号**
   （`??1stdiobuf@@UAE@XZ_2`）或局部符号（`nullsub_1`）⇒ 只对 `0x…` 形态尝试解析地址；
   非地址操作数原样记入 `unresolved_operands`（**已知漏采**），绝不 `int()`。
3. 真实的 `ptr` 几乎全是寄存器（466 里仅 4 个绝对地址）⇒ **归属判定只用 size + ctor/dtor**，
   绝不假设 `ptr` 可用 ✓。
4. `size` 是 `int`（来自 `push 2200h` 字面量），与注解 `binary_size` 直接比较 ✓；
   `count` 在 2 条真实站点里是字符串 ⇒ raw 层原样保留。

状态机（`ownership_candidate.state`，判据写在 `conflict_reasons`/`notes` 里可复算）：
- `unestablished`：站点没有 size 字面量；
- `conflict`：(a) 站点引用的某个地址被 **≥2 个活动注解来源**主张归属；或
  (b) 地址派生的类集合与 size 派生的类集合**都非空且不相交**（锚点全被字面量否定）；
- `ambiguous`：size 不唯一（多类同 `binary_size`）或地址派生多类但至少一类与 size 自洽；
- `verified`：地址派生**唯一**一类、size 派生**唯一**且相同、且没有未解析操作数；
  注意这是**候选层**的一致性判定，不是 A 证据（`a_evidence=False`）；
- `candidate`：证据不足以支撑上述任何一种。

**除显式 `--json <path>` 外本工具不写任何文件**；注解目录**只读**。
护栏：任何 `-` 开头且非已知开关的参数 ⇒ 打印提示、返回 0、不执行任何操作；
缺站点文件 ⇒ 返回 2。
"""
import argparse
import datetime
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ANN_DIR = os.path.join(ROOT, 'data', 'annotations')
SITES_DEFAULT = os.path.join(ROOT, 'data', 'status', 'element_size_sites.json')

TOOL_VERSION = 1

# raw 层唯一允许的键：地址/字节/字面量
RAW_SITE_KEYS = ('site', 'line', 'kind', 'ptr', 'size', 'count', 'ctor', 'dtor')

_HEX = re.compile(r'^0x[0-9a-fA-F]+$')
# 散文里的符号引用（本仓约定的地址写法）：sub_411CA0 / unk_C05F60
_PROSE_ADDR = re.compile(r'\b(sub|unk)_([0-9A-Fa-f]{4,8})\b')


def _norm_addr(tok):
    """把 `0x…` 形态归一到 `'0x' + 去前导零 + 小写`；非地址操作数返回 None。

    `0x00411900`（注解键）与 `0x411900`（站点值）必须归一到同一个键。
    寄存器（`ecx`）/改编符号（`??1stdiobuf@@UAE@XZ_2`）/局部符号（`nullsub_1`）
    不是地址 ⇒ 返回 None（调用方记入 `unresolved_operands`，已知漏采）。

    `int` 也接受（`audit_element_sizes._val()` 会把 `push 401190h` 之类的**数字字面量**
    直接转成 `int`）——独立复核已把"`ptr`/`ctor`/`dtor` 可为 `int`"列为会崩 T4 的 major
    ⇒ 这里按 `'0x%x'` 归一，raw 层仍**原样**回填 `int`（不做任何改写）。
    """
    if isinstance(tok, bool) or tok is None:
        return None
    if isinstance(tok, int):
        return '0x%x' % tok if tok >= 0 else None
    if not isinstance(tok, str):
        return None
    t = tok.strip()
    if not _HEX.match(t):
        return None
    digits = t[2:].lower().lstrip('0')
    return '0x' + (digits or '0')


def _load_structs(ann_dir):
    """只读 `structs/*.json` ⇒ {name: data}；坏 JSON / 非 dict 跳过（902 文件的现实风险）。"""
    out = {}
    sd = os.path.join(ann_dir, 'structs')
    for f in sorted(os.listdir(sd)) if os.path.isdir(sd) else []:
        if not f.endswith('.json'):
            continue
        try:
            with open(os.path.join(sd, f), encoding='utf-8') as fh:
                d = json.load(fh)
        except Exception:                            # noqa: BLE001 - 单个坏文件不得中断整体
            continue
        if not isinstance(d, dict):
            continue
        out[d.get('name') or f[:-5]] = d
    return out


def _load_retracted(ann_dir):
    """只读 `functions.json` 里 **已撤回** 的归属主张（`type='skip'`）。

    真实例：`0x00411CA0` 的 `ScriptObj_~ScriptObj`（reason: "misattributed in struct,
    removed"）——它与 `PalScript.json` 的 `~PalScript` 构成同一地址的**双源矛盾**。
    撤回主张只用于**暴露矛盾**（`address_conflicts`），**不参与**行级 state 判定，
    否则一条早已撤回的记录会把大量行误判为 conflict。
    """
    fp = os.path.join(ann_dir, 'functions.json')
    out = []
    if not os.path.isfile(fp):
        return out
    try:
        with open(fp, encoding='utf-8') as fh:
            data = json.load(fh)
    except Exception:                                # noqa: BLE001
        return out
    if not isinstance(data, dict):
        return out
    for addr, v in data.items():
        if not isinstance(v, dict) or v.get('type') != 'skip':
            continue
        na = _norm_addr(addr)
        if na is None:
            continue
        nm = v.get('name') or ''
        out.append({'addr': na, 'class': nm.split('_', 1)[0] or None, 'name': nm,
                    'source': 'functions.json(type=skip)', 'reason': v.get('reason')})
    return out


def load_annotations(ann_dir=None):
    """读注解（只读）⇒ (structs, retracted)。`ann_dir` 缺省取模块级 `ANN_DIR`（便于测试替换）。"""
    ann_dir = ann_dir or ANN_DIR
    return _load_structs(ann_dir), _load_retracted(ann_dir)


def _prose_mentions(structs):
    """机械扫描注解 JSON 里的**文本字段**，收集 `sub_XXXX`/`unk_XXXX` 引用 ⇒ {addr: [mention]}。

    用途：把"**未结构化**的散文主张"也暴露出来（断言性最低，故标 `structured: false`，
    **不参与** `address_conflicts` 的 ≥2 门槛、也不参与行级 state）。
    真实例：`Scene.json` 的 `known_members.57572.source` 写
    `??_L(esi+0E0E4h, 0x2200, 0x32, sub_411900=Role, sub_411CA0)` —— 这正是
    "`0x411CA0` 是 Role 数组的 dtor" 这一主张的唯一书面来源（Role.json 的 methods 里**没有**它），
    与 `PalScript` 的 `~PalScript` 主张构成需要人看的两义。
    """
    def walk(o, path):
        if isinstance(o, dict):
            for k, v in o.items():
                yield from walk(v, '%s.%s' % (path, k))
        elif isinstance(o, list):
            for i, v in enumerate(o):
                yield from walk(v, '%s[%d]' % (path, i))
        elif isinstance(o, str):
            yield path, o

    out = {}
    for cls, d in structs.items():
        for path, text in walk(d, cls):
            for m in _PROSE_ADDR.finditer(text):
                na = _norm_addr('0x' + m.group(2))
                if na is None:
                    continue
                out.setdefault(na, []).append(
                    {'class': cls, 'field': path, 'structured': False,
                     'excerpt': text[:160]})
    return out


def _address_claims(structs):
    """活动归属索引：{归一化地址: [{class, name, source}…]}（`methods` + `vtables` + `known_methods`）。"""
    idx = {}
    for cls, d in structs.items():
        for addr, v in (d.get('methods') or {}).items():
            na = _norm_addr(addr)
            if na is None:
                continue
            idx.setdefault(na, []).append(
                {'class': cls, 'name': (v or {}).get('name'), 'source': 'methods'})
        for vt in (d.get('vtables') or []):
            for slot in ((vt or {}).get('slots') or []):
                na = _norm_addr((slot or {}).get('addr'))
                if na is None:
                    continue
                idx.setdefault(na, []).append(
                    {'class': cls, 'name': None, 'source': 'vtables'})
        km = d.get('known_methods')
        if isinstance(km, dict):
            for addr, v in km.items():
                na = _norm_addr(addr)
                if na is None:
                    continue
                idx.setdefault(na, []).append(
                    {'class': cls, 'name': (v or {}).get('name') if isinstance(v, dict) else None,
                     'source': 'known_methods'})
    return idx


def address_conflicts(structs, retracted=None, active_index=None, prose=None):
    """暴露**同一地址的多源主张**（活动来源 ≥2 类，或活动 + 已撤回来源）。

    返回按地址排序的列表，每条含 `active`/`retracted`/`claimants`/`prose_mentions`。
    用于成功判据 ② 的"`0x411CA0` 双源矛盾暴露"（PalScript `~PalScript` vs
    functions.json 里已撤回的 ScriptObj `~ScriptObj`；外加 Scene.json 的散文主张）。

    门槛只看 **active ∪ retracted** 的**类**是否 ≥2；`prose_mentions` 是附加信息
    （未结构化、`structured: false`），**不参与**门槛。
    """
    idx = active_index if active_index is not None else _address_claims(structs)
    pro = _prose_mentions(structs) if prose is None else prose
    ret = {}
    for r in (retracted or []):
        ret.setdefault(r['addr'], []).append(r)
    out = []
    for addr in sorted(set(idx) | set(ret)):
        act = idx.get(addr, [])
        rtd = ret.get(addr, [])
        claimants = sorted({c['class'] for c in act if c.get('class')} |
                           {c['class'] for c in rtd if c.get('class')})
        if len(claimants) < 2:
            continue
        out.append({'addr': addr, 'active': act, 'retracted': rtd, 'claimants': claimants,
                    'sources': sorted({c['source'] for c in act} | {c['source'] for c in rtd}),
                    'prose_mentions': pro.get(addr, [])})
    return out


def adjudicate(sites, structs, retracted=None):
    """把站点裁成两层。返回 list[dict]，每条含 raw_site / size_state / ownership_candidate。

    `retracted` 只影响 `address_refs`（矛盾暴露），**不影响** `state`（见 `_load_retracted`）。
    """
    idx = _address_claims(structs)
    conf_list = address_conflicts(structs, retracted, active_index=idx)
    conf_addrs = {c['addr'] for c in conf_list}
    dual_active = {c['addr'] for c in conf_list
                   if len({x['class'] for x in c['active'] if x.get('class')}) >= 2}
    sizes = {}
    for cls, d in structs.items():
        b = d.get('binary_size')
        if isinstance(b, int):
            sizes.setdefault(b, []).append(cls)

    rows = []
    for s in sites:
        raw = {k: s.get(k) for k in RAW_SITE_KEYS}       # 逐字段原样回填，不做推断
        size = s.get('size')
        size_classes = sorted(sizes.get(size, [])) if isinstance(size, int) else []

        cands, unresolved, claimed = [], {}, []
        for role in ('ctor', 'dtor'):
            tok = s.get(role)
            if tok is None:
                continue
            na = _norm_addr(tok)
            if na is None:                                # 寄存器/改编符号/局部符号 ⇒ 已知漏采
                unresolved[role] = tok
                continue
            for claim in idx.get(na, []):
                bsz = structs.get(claim['class'], {}).get('binary_size')
                cands.append({'addr': na, 'class': claim['class'], 'name': claim['name'],
                              'role': role, 'evidence': 'annotation(lowered)',
                              'size_consistent': (bsz == size) if isinstance(size, int)
                              and isinstance(bsz, int) else None})
                claimed.append(claim['class'])
        for cls in size_classes:                          # size 派生也是注解派生（binary_size）
            cands.append({'addr': None, 'class': cls, 'name': None, 'role': 'size',
                          'evidence': 'annotation(size)', 'size_consistent': True})

        claimed_classes = sorted(set(claimed))
        candidate_classes = sorted(set(claimed_classes) | set(size_classes))
        site_addrs = {_norm_addr(s.get(r)) for r in ('ctor', 'dtor')} - {None}
        addr_refs = sorted(site_addrs & conf_addrs)
        dual_refs = sorted(site_addrs & dual_active)
        notes, reasons = [], []
        if size_classes and not claimed_classes:
            notes.append('无 ctor/dtor 归属主张，size 派生类仅供参考')
        inconsistent = [c for c in cands
                        if c['role'] in ('ctor', 'dtor') and c['size_consistent'] is False]
        if inconsistent:
            reasons.append('归属主张与 size 字面量不自洽: ' + ', '.join(
                '%s:%s(%s≠%d)' % (c['role'], c['addr'], c['class'], size)
                for c in inconsistent))
        if addr_refs:
            reasons.append('引用地址存在多源注解主张: ' + ', '.join(addr_refs))
        if dual_refs:
            reasons.append('引用地址被 ≥2 个活动注解来源主张归属: ' + ', '.join(dual_refs))
        if len(size_classes) > 1:
            notes.append('size %s 非唯一（%d 个类同 binary_size）⇒ 只能作候选'
                         % ('0x%X' % size if isinstance(size, int) else size, len(size_classes)))
        if len(claimed_classes) > 1:
            notes.append('ctor/dtor 指向 %d 个不同类（%s）⇒ 归属只能作候选'
                         % (len(claimed_classes), ', '.join(claimed_classes)))

        if not isinstance(size, int):
            state, verified = 'unestablished', None
        elif dual_refs:
            state, verified = 'conflict', None
        elif inconsistent:
            # M2（2026-09-20 P0）：最直接的自相矛盾（注解主张的类 size 与元素字面量不符）
            # 原先要求 size_classes 非空才判 conflict，导致 26 行漏报（19 candidate + 7 ambiguous）。
            # 现改为：只要 ctor/dtor 主张与 size 字面量不自洽即为 conflict（reasons 已含明细）。
            state, verified = 'conflict', None
        elif claimed_classes and size_classes and not (set(claimed_classes) & set(size_classes)):
            state, verified = 'conflict', None
        elif len(size_classes) > 1 or len(claimed_classes) > 1:
            state, verified = 'ambiguous', None
        elif (len(claimed_classes) == 1 and size_classes == claimed_classes
              and not unresolved):
            # M1（2026-09-20 P0）：原 verified 是循环论证（比较的两边都来自注解）⇒ 降级为
            # annotation_self_consistent，且不再产出 verified_class（消费前须取第二判据）。
            state, verified = 'annotation_self_consistent', None
            notes.append('仅注解内部自洽（非独立证据）——不得据此认定尺寸正确；'
                         '消费前必须取得第二判据（requires_second_criterion）')
        else:
            state, verified = 'candidate', None
        assert state != 'conflict' or reasons, 'conflict 必须给出可复算的理由（可审计性）'

        rows.append({
            'raw_site': raw,
            'size_state': 'evidenced' if isinstance(size, int) else 'unestablished',
            'size_matches_classes': size_classes,
            'size_unique': len(size_classes) == 1,
            'requires_second_criterion': state in ('annotation_self_consistent', 'candidate', 'ambiguous'),
            'contradiction': bool(inconsistent),
            'ownership_candidate': {
                'state': state,
                'verified_class': verified,
                'candidates': cands,
                'candidate_classes': candidate_classes,
                'unresolved_operands': unresolved,
                'address_refs': addr_refs,
                'conflict_reasons': reasons,
                'notes': notes,
                'evidence_layer': 'lowered',
                'a_evidence': False,
            },
        })
    return rows


def build_payload(sites_path, structs, retracted, rows, ann_dir=None, conflicts=None):
    by_state = {}
    for r in rows:
        st = r['ownership_candidate']['state']
        by_state[st] = by_state.get(st, 0) + 1
    if conflicts is None:
        conflicts = address_conflicts(structs, retracted)
    return {
        'tool_version': TOOL_VERSION,
        'sites': sites_path,
        'annotations_dir': ann_dir or ANN_DIR,
        'generated_at': datetime.datetime.now(datetime.timezone.utc)
                                       .strftime('%Y-%m-%dT%H:%M:%SZ'),
        'summary': {
            'rows': len(rows),
            'evidenced': sum(1 for r in rows if r['size_state'] == 'evidenced'),
            'by_state': by_state,
            'size_unique_rows': sum(1 for r in rows if r['size_unique']),
            'address_conflicts': len(conflicts),
        },
        'address_conflicts': conflicts,
        'rows': rows,
    }


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    # 护栏（防重演已发生 2 起的 `--help` 覆盖产物事故）：任何 `-` 开头且非已知开关的参数
    # ⇒ 打印提示、返回 0、**不执行任何操作**。
    known = {'--sites', '--annotations', '--json'}
    unknown = [x for x in argv if x.startswith('-') and x.split('=')[0] not in known]
    if unknown:
        print('[element_size_adjudicate] 未知开关 %r ⇒ 不执行任何操作' % unknown)
        print('用法: [--sites <path>] [--annotations <dir>] [--json <path>]')
        return 0
    ap = argparse.ArgumentParser()
    ap.add_argument('--sites', default=SITES_DEFAULT)
    ap.add_argument('--annotations', default=ANN_DIR)
    ap.add_argument('--json', default=None)
    args = ap.parse_args(argv)
    if not os.path.exists(args.sites):
        print('[ERROR] 缺站点文件: %s（先跑 tools/audit_element_sizes.py）' % args.sites,
              file=sys.stderr)
        return 2
    with open(args.sites, encoding='utf-8') as fh:
        sites = json.load(fh).get('sites', [])
    structs, retracted = load_annotations(args.annotations)
    rows = adjudicate(sites, structs, retracted)
    conflicts = address_conflicts(structs, retracted)
    ev = sum(1 for r in rows if r['size_state'] == 'evidenced')
    by_state = {}
    for r in rows:
        st = r['ownership_candidate']['state']
        by_state[st] = by_state.get(st, 0) + 1
    print('裁定 %d 条：evidenced=%d' % (len(rows), ev))
    print('归属态分布: %s' % ', '.join('%s=%d' % kv for kv in sorted(by_state.items())))
    print('多源地址矛盾: %d 条' % len(conflicts))
    if args.json:
        payload = build_payload(args.sites, structs, retracted, rows,
                                ann_dir=args.annotations, conflicts=conflicts)
        with open(args.json, 'w', encoding='utf-8') as fh:
            json.dump(payload, fh, indent=1, ensure_ascii=False)
        print('-> %s' % args.json)
    return 0


if __name__ == '__main__':
    sys.exit(main())