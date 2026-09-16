#!/usr/bin/env python3
"""0b 的离线测量台：用缓存的 `.obj` 复测 mangler 命中率。

为什么需要它：`pipeline/cli.py match` 要占 IDB 窗口且每次重编 56 个单元（约 1 分钟）。
`unmatched` 的归因与修复是**纯 Python 的名字编码问题**，可以完全离线验证
——`/tmp/ua/*.obj` 是同一批 56 个 S2-passing 单元的编译产物，本工具直接复用。

基准（2026-09-15，HEAD ac6d67374）：
    symbols=189  mangler 命中=129  unmatched=60

用法：
    python3 tools/mangler_bench.py            # 现状
    python3 tools/mangler_bench.py --verbose   # 附未命中清单
    python3 tools/mangler_bench.py --regen     # 重新编译 56 个单元（需 wine_cl，不碰 IDB）

判据（每改一处后必须）：
    unmatched 下降 · symbols 不缩水 · 若命中数上升需人工确认不是"错配"
"""
import argparse
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "pipeline"))
sys.path.insert(0, os.path.join(ROOT, "pipeline", "ida"))
sys.path.insert(0, os.path.join(ROOT, "tools"))

OBJ_GLOB = "/tmp/ua/*.obj"
BASELINE = {"symbols": 189, "matched": 129, "unmatched": 60}


def load_decomp_idx():
    idx = {}
    for p in glob.glob(os.path.join(ROOT, "asm", "pal3", "decomp", "*.json")):
        try:
            with open(p, encoding="utf-8") as f:
                d = json.load(f)
        except (OSError, json.JSONDecodeError):
            continue
        if d.get("name") and d.get("address") and d.get("size_bytes"):
            idx[d["name"]] = d
    return idx


def build_map(idx, import_vm):
    """与 compare_pal3.build_mangled_map 同口径（含探测变体）。"""
    m2e = {}
    for name, e in idx.items():
        if "::" not in name:
            continue
        base = name.split("(")[0]
        if "::" not in base:
            continue
        cls, method = base.rsplit("::", 1)
        sig = e.get("signature") or ""
        try:
            m = import_vm.mangle(cls, method, sig)
            m2e.setdefault(m, e)
            for kw in ({"virtual_": True}, {"static_": True}):
                mv = import_vm.mangle(cls, method, sig, **kw)
                if mv != m:
                    m2e.setdefault(mv, e)
        except Exception:
            pass
    return m2e


def collect_obj_symbols():
    import gbengine_compare as gc
    funcs = []
    for o in sorted(glob.glob(OBJ_GLOB)):
        try:
            funcs += list(gc.parse_coff_obj(o))
        except Exception:
            pass
    return funcs


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--verbose", action="store_true", help="列出未命中符号")
    ap.add_argument("--group", action="store_true", help="按形态分组统计未命中")
    args = ap.parse_args()

    import vc6_mangler as vm
    idx = load_decomp_idx()
    m2e = build_map(idx, vm)
    funcs = collect_obj_symbols()
    hit = [s for s in funcs if s in m2e]
    miss = [s for s in funcs if s not in m2e]

    print("mangled_map=%d" % len(m2e))
    print("symbols=%d  matched=%d  unmatched=%d" % (len(funcs), len(hit), len(miss)))
    d_s = len(funcs) - BASELINE["symbols"]
    d_m = len(hit) - BASELINE["matched"]
    d_u = len(miss) - BASELINE["unmatched"]
    print("vs 基准: symbols %+d  matched %+d  unmatched %+d" % (d_s, d_m, d_u))
    if d_u > 0 or d_m < 0:
        print("  ⚠️ 退化")

    if args.group:
        c = {}
        for s in miss:
            t = []
            if s.startswith("??_G") or s.startswith("??_E"):
                t.append("scalar-dtor")
            elif s.startswith("??1"):
                t.append("dtor")
            elif s.startswith("??0"):
                t.append("ctor")
            if "@@SA" in s or "@@YA" in s:
                t.append("static")
            if "PAV" in s:
                t.append("ptr-class")
            if re.search(r"@\d@", s):
                t.append("nested")
            if "PAD" in s or "PBD" in s:
                t.append("char*")
            for x in (t or ["other"]):
                c[x] = c.get(x, 0) + 1
        for k, n in sorted(c.items(), key=lambda x: -x[1]):
            print("   %-14s %d" % (k, n))

    if args.verbose:
        print("\n未命中 %d 条:" % len(miss))
        for s in miss:
            print("   %s" % s[:92])
    return 0


if __name__ == "__main__":
    sys.exit(main())