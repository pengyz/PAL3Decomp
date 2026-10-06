"""签名缺参族批量补参（ret N/4 > 签名参——GetTargetRole 型）。int 占位+序号名（nVal 惯例）。"""
import json

p = r"D:\workspace\PAL3Decomp\data\status\sig_missing_params.json"
rows = json.load(open(p, encoding="utf-8"))["rows"]

import glob, os
by_cls = {}
for r in rows:
    by_cls.setdefault(r["cls"], []).append(r)

n_fixed = 0
for cls, lst in by_cls.items():
    mp = r"D:\workspace\PAL3Decomp\data\annotations\structs\%s.json" % cls
    if not os.path.exists(mp):
        continue
    d = json.load(open(mp, encoding="utf-8"))
    ch = False
    for r in lst:
        mv = (d.get("methods") or {}).get(r["addr"])
        if not mv:
            continue
        sig = str(mv.get("signature") or "")
        need = r["ret_p"] - r["sig_p"]
        if need <= 0 or '(' not in sig:
            continue
        # 补参：int 占位+序号名（nVal 惯例——既有签名形）
        add = "".join(", int nVal%d" % (r["sig_p"] + i + 1) for i in range(need))
        j = sig.rfind(')')
        if j < 0:
            continue
        inner_end = sig.rfind('(', 0, j)
        if inner_end < 0:
            continue
        head = sig[:inner_end + 1]
        inner = sig[inner_end + 1:j]
        if inner.strip() in ('', 'void'):
            new_inner = add.lstrip(', ')
        else:
            new_inner = inner + add
        mv["signature"] = head + new_inner + sig[j:]
        mv["source"] = (mv.get("source") or "") + \
            " | 签名缺参批量 2026-10-06：ret %d/4=%d 参 vs 签名 %d——补 %d 参（int 占位·nVal 序号惯例）" % (
                r["ret_p"] * 4, r["ret_p"], r["sig_p"], need)
        ch = True
        n_fixed += 1
    if ch:
        json.dump(d, open(mp, "w", encoding="utf-8"), ensure_ascii=False, indent=2)
print("批量补参 %d 件" % n_fixed)
