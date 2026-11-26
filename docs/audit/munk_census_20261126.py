#!/usr/bin/env python3
"""m_unk_<offset> 留白名普查（只读）。

用途：为 docs/audit/2026-11-26-munk-batch-decision-packet.md 提供可复现真值。
只读 data/annotations/structs/*.json，不写任何 annotation / 基线 / 生成树。

用法：
  python3 docs/audit/munk_census_20261126.py            # 打印汇总
  python3 docs/audit/munk_census_20261126.py --json out.json  # 另存逐条清单

口径：
  exact  = 名字严格匹配 ^m_unk_(0x)?<hex>$（本卡要求的「m_unk_<offset> 形态」）
  recursive = 除 known_members 顶层成员外，也遍历 type={struct:[...]}/{union:[...]} 的内联成员
  跨度 span = 同类下一顶层成员的偏移差；末员用该类 binary_size 收尾（若可算）
"""
import argparse
import collections
import glob
import hashlib
import json
import os
import re
import sys

STRUCT_DIR = "data/annotations/structs"
PAT_EXACT = re.compile(r"^m_unk_(?:0x)?[0-9A-Fa-f]+$")
PAT_ANY = re.compile(r"m_unk_")
PAT_TODO = re.compile(r"_todo_", re.I)
PAT_NUM = re.compile(r"^m_[A-Za-z]+_[0-9A-Fa-f]{2,}$")
LEDGER = "data/annotations/archive/pseudo_semantic_names_20261118.json"


def parse_off(s):
    try:
        return int(s, 0)
    except (TypeError, ValueError):
        return None


def walk_members(km, nested=False):
    """yield (offset, member, is_nested)。km 为 known_members 字典。"""
    if not isinstance(km, dict):
        return
    for off, m in km.items():
        if not isinstance(m, dict):
            continue
        yield off, m, False
        t = m.get("type")
        if isinstance(t, dict):
            for key in ("struct", "union"):
                for sub in t.get(key, []) or []:
                    if isinstance(sub, dict) and "offset" in sub and "name" in sub:
                        yield sub["offset"], sub, True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--json", help="把逐条清单写到该路径")
    args = ap.parse_args()

    files = sorted(glob.glob(os.path.join(STRUCT_DIR, "*.json")))
    ledger = json.load(open(LEDGER, encoding="utf-8")).get("names", {})
    ledger_pairs = {(cl, it["name"]) for cl, items in ledger.items() for it in items}

    rows = []
    per_class = collections.OrderedDict()
    variants = collections.Counter()
    variant_pairs = {k: set() for k in ("unk", "any", "todo", "num", "ledger")}
    ev_dist = collections.Counter()
    file_hashes = {}

    for f in files:
        raw = open(f, "rb").read()
        file_hashes[os.path.basename(f)] = hashlib.sha256(raw).hexdigest()
        d = json.loads(raw)
        cl = d.get("name") or os.path.basename(f)[:-5]
        size = d.get("binary_size")
        km = d.get("known_members") or {}
        top_offs = sorted(x for x in (parse_off(o) for o in km) if x is not None)

        for off, m, nested in walk_members(km):
            name = m.get("name", "")
            o = parse_off(off)
            key = (cl, off, name)
            if PAT_EXACT.match(name):
                variants["unk"] += 1
                variant_pairs["unk"].add(key)
                span = None
                if not nested and o is not None and o in top_offs:
                    i = top_offs.index(o)
                    nxt = top_offs[i + 1] if i + 1 < len(top_offs) else size
                    if isinstance(nxt, int) and nxt >= o:
                        span = nxt - o
                rows.append({
                    "class": cl, "offset": off, "name": name,
                    "type": m.get("type"), "evidence_level": m.get("evidence_level"),
                    "source": m.get("source"), "file": f, "nested": nested, "span": span,
                })
                ev_dist[str(m.get("evidence_level"))] += 1
                pc = per_class.setdefault(cl, {"count": 0, "span": 0, "no_span": 0,
                                               "evidence": collections.Counter(), "file": f})
                pc["count"] += 1
                pc["span"] += span or 0
                pc["no_span"] += 1 if span is None else 0
                pc["evidence"][str(m.get("evidence_level"))] += 1
            if PAT_ANY.search(name):
                variants["any"] += 1
                variant_pairs["any"].add(key)
            if PAT_TODO.search(name):
                variants["todo"] += 1
                variant_pairs["todo"].add(key)
            if PAT_NUM.match(name):
                variants["num"] += 1
                variant_pairs["num"].add(key)
            if (cl, name) in ledger_pairs:
                variants["ledger"] += 1
                variant_pairs["ledger"].add(key)

    union = set().union(*variant_pairs.values())
    print(f"扫描文件: {len(files)} 个 ({STRUCT_DIR}/*.json)")
    print(f"\n[exact] m_unk_<offset> 成员: {len(rows)} 条 / {len(per_class)} 类")
    for cl, pc in per_class.items():
        ev = dict(pc["evidence"])
        extra = f" no_span={pc['no_span']}" if pc["no_span"] else ""
        print(f"  {cl:20s} {pc['count']:3d} 条  跨度合计 {pc['span']:6d} B  ev={ev}{extra}")
    print(f"  跨度合计: {sum(r['span'] or 0 for r in rows)} B（无跨度 {sum(1 for r in rows if r['span'] is None)} 条）")
    print(f"\n[口径变体] " + "  ".join(f"{k}={v}" for k, v in variants.items()))
    print(f"  五种口径并集(按 类+偏移+名 去重): {len(union)} 条 / {len({k[0] for k in union})} 类")
    for k in ("unk", "any", "todo", "num", "ledger"):
        print(f"  仅 {k}: {len(variant_pairs[k])}")

    if args.json:
        payload = {
            "generated_at": __import__("datetime").datetime.now().isoformat(timespec="seconds"),
            "scanned_files": len(files),
            "exact_count": len(rows),
            "exact_classes": len(per_class),
            "span_total": sum(r["span"] or 0 for r in rows),
            "per_class": {cl: {"count": pc["count"], "span": pc["span"],
                               "evidence": dict(pc["evidence"]), "file": pc["file"]}
                          for cl, pc in per_class.items()},
            "variants": dict(variants),
            "union": len(union),
            "file_sha256": file_hashes,
            "rows": rows,
        }
        json.dump(payload, open(args.json, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
        print(f"\n逐条清单已写: {args.json}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
