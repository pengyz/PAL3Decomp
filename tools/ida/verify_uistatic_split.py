"""V5：用**复核者指定的 A 级锚**在 IDB 内复核 `UIStatic`/`UIPushButton` 拆分（只读 ✓）。

A 级锚三要素（**不用** `??0<Cls>@@` ✗，它来自 PAL3A PDB）：
  ① **vtable 地址**（`off_56AD88` / `off_56ADD0`）与其**装载者**（`mov dword ptr [reg], offset off_XX` ✓）
  ② **分配点 `push N`**（紧邻 `call ??2@YAPAXI@Z` ✓）
  ③ **ctor 写域**（`rep stosd` 的起点与长度 ✓、关键字段写宽度 ✓）
运行：/home/peng/ida-pro-9.1/idat -A -S"tools/ida/verify_uistatic_split.py" original/PAL3.exe.i64
输出：pipeline/ida/_logs/_verify_uistatic_split.txt
"""
import re
import idaapi, idautils, idc, ida_funcs, ida_nalt

idaapi.auto_wait()
OUT = r"/home/peng/workspace/PAL3Decomp/pipeline/ida/_logs/_verify_uistatic_split.txt"
CTORS = {"0x440740": "A", "0x4422E0": "B"}
VT = {"0x56AD88": "A", "0x56ADD0": "B"}

f = open(OUT, "w", encoding="utf-8")
f.write("=== V5：A 级锚复核 UIStatic/UIPushButton 拆分 ===\n")
f.write("IDB=%s imagebase=0x%X\n\n" % (ida_nalt.get_input_file_path(), idaapi.get_imagebase()))

def body(ea, limit=400):
    out, cur = [], ea
    for _ in range(limit):
        if idc.get_func_attr(cur, idc.FUNCATTR_START) != ea: break
        out.append((cur, idc.generate_disasm_line(cur, 0) or ""))
        cur = idc.next_head(cur, ea + 0x2000)
        if cur == idc.BADADDR: break
    return out

# ① vtable 装载者
f.write("【① vtable 装载者】\n")
for vt, tag in VT.items():
    ea = int(vt, 16)
    n = 0
    for xr in idautils.XrefsTo(ea, 0):
        fn = ida_funcs.get_func(xr.frm)
        f.write("  %s %s ← 0x%06X  %s  in %s\n" % (tag, vt, xr.frm,
                (idc.generate_disasm_line(xr.frm, 0) or "")[:56], (idc.get_func_name(fn.start_ea) if fn else "?")[:34]))
        n += 1
    f.write("  ⇒ %s 引用 %d 处\n" % (tag, n))

# ② 分配点 push N（紧邻 operator new 且随后 call A/B 的 ctor）
f.write("\n【② 分配点 push N ⇒ 整对象尺寸】\n")
new_ea = idc.get_name_ea_simple("??2@YAPAXI@Z")
found = {}
for ea in idautils.Functions():
    b = body(ea)
    for i, (a2, t) in enumerate(b):
        if "??2@YAPAXI@Z" not in t and "operator new" not in t: continue
        N = None
        for j in range(max(0, i - 12), i):
            m = re.search(r'\bpush\s+([0-9A-Fa-f]+)h\b', b[j][1])
            if m: N = int(m.group(1), 16)
        for k in range(i + 1, min(len(b), i + 18)):
            m = re.search(r'\bcall\s+sub_([0-9A-Fa-f]+)', b[k][1])
            if m:
                key = "0x%s" % m.group(1)
                if key in CTORS:
                    found.setdefault(CTORS[key], set()).add(N)
                break
for tag, ns in sorted(found.items()):
    f.write("  %s（ctor %s）的 new 尺寸集合 = %s\n" % (tag, [k for k, v in CTORS.items() if v == tag][0],
            sorted(x for x in ns if x is not None)))

# ③ ctor 写域（rep stosd 起点/长度 + 末写位移）
f.write("\n【③ ctor 写域（末写位移 = 尺寸上界）】\n")
for ctor, tag in CTORS.items():
    ea = int(ctor, 16)
    b = body(ea)
    mx, stosd = 0, None
    for a2, t in b:
        for m in re.finditer(r'\[[a-z]{2,3}\+([0-9A-Fa-f]+)h\]', t):
            mx = max(mx, int(m.group(1), 16))
        if "rep stosd" in t:
            stosd = t
    f.write("  %s ctor %s：末写位移 = 0x%X (%d) ｜ rep stosd 行 = %s\n"
            % (tag, ctor, mx, mx, (stosd or "-")[:52]))
f.write("\n判读：① 谁装载该 vtable ⇒ 谁的方法；② new 尺寸 ⇒ 整对象；③ 末写+4 ⇒ 尺寸上界。三者互证 ✓\n")
f.close()
print("v5 written:", OUT)
idc.qexit(0)
