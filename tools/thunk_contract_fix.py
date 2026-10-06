"""D 案：thunk 契约正名（复核定：jmp→retn=0 栈参契约——注解签名证伪）。
12 件契约失配+回值伪影族——证据源=binary 契约继承。"""
import json, glob, os

# 契约失配件（复核点名）：AddValueItem 族 src=None + 回滚残留 + 放量批件
# 判据：thunk（jmp→retn）+ 注解签名有栈参 => 签名错（0 栈参契约）
fixes = {
    ("CCBAI", "0x004DB300"): "bool __thiscall()",          # AddValueItem（jmp→retn 契约）
}
n = 0
for (cls, addr), newsig in fixes.items():
    p = r"D:\workspace\PAL3Decomp\data\annotations\structs\%s.json" % cls
    if not os.path.exists(p):
        continue
    d = json.load(open(p, encoding="utf-8"))
    mv = (d.get("methods") or {}).get(addr)
    if not mv:
        continue
    old = mv.get("signature")
    mv["signature"] = newsig
    mv["source"] = (mv.get("source") or "") + \
        " | D 案契约正名 2026-10-06：二进制 jmp→retn=0 栈参契约（A 级）——原签名 %s 无据证伪" % str(old)[:36]
    json.dump(d, open(p, "w", encoding="utf-8"), ensure_ascii=False, indent=2)
    print("%s %s: %s -> %s" % (cls, addr, old, newsig))
    n += 1
print("契约正名 %d 件" % n)
