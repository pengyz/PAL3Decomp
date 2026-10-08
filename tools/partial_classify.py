"""partial diff 根因分类：size 失配（布局族）vs 内容 diff（指令选择族）——注解可修子集筛。"""
import json

d = json.load(open(r"D:\workspace\PAL3Decomp\data\status\s4_diff_detail.json", encoding="utf-8"))
u = d.get("units") or {}
kinds = {"size_mismatch": [], "content_diff": [], "tiny": []}
for f, lst in u.items():
    for fn in lst or []:
        sz = fn.get("size") or 0
        cl = fn.get("compiled_len") or 0
        nd = fn.get("n_diff") or 0
        if sz == 0:
            continue
        if cl != sz:
            kinds["size_mismatch"].append((f.split("/")[-1], fn.get("name"), sz, cl, nd))
        elif nd <= 4:
            kinds["tiny"].append((f.split("/")[-1], fn.get("name"), sz, nd))
        else:
            kinds["content_diff"].append((f.split("/")[-1], fn.get("name"), sz, nd))

print("partial 根因分类：")
for k, v in kinds.items():
    print("  %-16s %d 件" % (k, len(v)))
print("\nsize 失配 top 8（注解布局族候选）:")
for n, nm, sz, cl, nd in sorted(kinds["size_mismatch"], key=lambda x: -abs(x[2] - x[3]))[:8]:
    print("  %-22s %s size=%d compiled=%d Δ=%+d" % (n[:22], str(nm)[:28], sz, cl, cl - sz))
print("\ntiny（≤4 diff·快赢候选）:")
for n, nm, sz, nd in kinds["tiny"][:8]:
    print("  %-22s %s size=%d diff=%d" % (n[:22], str(nm)[:28], sz, nd))
