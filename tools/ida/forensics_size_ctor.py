"""IDB 取证 V2（headless ✓，查 IDB ✓，非离线 ✓）。

运行：/home/peng/ida-pro-9.1/idat -A -S"tools/ida/forensics_size_ctor.py" original/PAL3.exe.i64
输出：pipeline/ida/_logs/_forensics_size_ctor.txt

V2 修 V1 三处不足（V1 已实测 ✗）：
 ① vtable 命名不匹配 ⇒ 改为**从 ctor 首条对 [reg] 的存储直接取**（`mov dword ptr [reg], offset X` ✓）
    —— 不依赖 IDB 的符号命名 ✓（这才是"ctor 归属"的直接证据 ✓）
 ② 只报了 operator new 调用点、无立即数 ⇒ 从调用点**向前反扫 `push imm`**（≤10 条 ✓）取 N ✓
 ③ [reg+imm] 上界不再依赖 vtable ⇒ **整函数体**扫描取最大位移 ✓
"""
import re
import idaapi, idautils, idc, ida_funcs, ida_nalt

idaapi.auto_wait()
OUT = r"/home/peng/workspace/PAL3Decomp/pipeline/ida/_logs/_forensics_size_ctor.txt"
TARGETS = ["UITitle_ArcSave", "ScreenEffectNode", "CCBUI", "CScreenMode", "JusticeBookUI",
           "UIRoleSelectDialog", "UIListBox", "CCBUIPanel", "UIScenePanel", "CCBRoleState",
           "UISceneFrm", "CCBStageScene", "UICoverFrm", "UISceneMap"]
RE_IMM = re.compile(r'\[[a-z]{2,3}\+([0-9A-Fa-f]+)h?\]')
RE_PUSH = re.compile(r'\bpush\s+(?:offset\s+)?([0-9A-Fa-f]+)h?\b')
RE_STORE_VT = re.compile(r'mov\s+dword ptr \[[a-z]{2,3}\],\s*offset\s+(\S+)')

def func_body(start, limit=800):
    """返回 (ea, text) 列表（同一函数内 ✓）。"""
    out = []
    ea = start
    for _ in range(limit):
        if idc.get_func_attr(ea, idc.FUNCATTR_START) != start:
            break
        out.append((ea, idc.generate_disasm_line(ea, 0) or ""))
        ea = idc.next_head(ea, start + 0x4000)
        if ea == idc.BADADDR:
            break
    return out

def max_disp(body):
    mx = 0
    for _ea, t in body:
        for m in RE_IMM.finditer(t):
            try: mx = max(mx, int(m.group(1), 16))
            except Exception: pass
    return mx

f = open(OUT, "w", encoding="utf-8")
f.write("=== IDB 取证 V2（ctor 身份 / operator new 立即数 / 整体上界）===\n")
f.write("IDB=%s imagebase=0x%X\n\n" % (ida_nalt.get_input_file_path(), idaapi.get_imagebase()))
new_ea = idc.get_name_ea_simple("??2@YAPAXI@Z")

for cls in TARGETS:
    f.write("########## %s ##########\n" % cls)
    # 候选函数（名字含类 ✓）
    cand = []
    for ea in idautils.Functions():
        n = idc.get_func_name(ea) or ""
        if cls in n:
            cand.append((ea, n))
    ctors = [(ea, n) for ea, n in cand if n.startswith("??0") or "ctor" in n.lower() or n.endswith("_%s" % cls)]
    f.write("  候选函数 %d 个；其中疑似 ctor %d 个\n" % (len(cand), len(ctors)))
    for ea, n in ctors[:6]:
        body = func_body(ea)
        # ① ctor 首条对 [reg] 的存储 ⇒ 真 vtable（归属证据 ✓）
        vt = None
        for _ea2, t in body[:12]:
            m = RE_STORE_VT.search(t)
            if m:
                vt = m.group(1); break
        # ③ 整体上界
        mx = max_disp(body)
        f.write("    ctor 0x%06X %-46s | ①首条 vtable 存储 = %-28s | ③[reg+imm] 上界 = 0x%X (%d)\n"
                % (ea, n[:46], vt or "(无 ⇒ 非多态或未识别 ✗)", mx, mx))
    # ② operator new 立即数（在名字含本类的函数体内 ✓）
    allocs = []
    if new_ea and new_ea != idc.BADADDR:
        for ea, n in cand:
            body = func_body(ea)
            for i, (ea2, t) in enumerate(body):
                if "??2@YAPAXI@Z" in t or "operator new" in t:
                    N = None
                    for j in range(max(0, i - 10), i):      # 向前反扫 push imm ✓
                        m = RE_PUSH.search(body[j][1])
                        if m:
                            N = m.group(1)
                    allocs.append((ea2, n, N))
    f.write("  ② 名字含本类的函数体内 operator new 调用 %d 处（含向前反扫的 push 立即数 ✓）:\n" % len(allocs))
    seenN = {}
    for ea2, n, N in allocs:
        seenN.setdefault(N, 0)
        seenN[N] += 1
        if len([1 for x in allocs if x[0] == ea2]) <= 4:
            f.write("    0x%06X  %-40s  push N = %s\n" % (ea2, n[:40], N))
    f.write("    ⇒ 立即数分布（尺寸候选 ✓）: %s\n\n" % sorted(seenN.items(), key=lambda x: -x[1])[:6])

f.write("=== 判读 ===\n")
f.write("① 首条 [reg] 存储的 vtable 目标 = 该 ctor 归属的类 ⇒ dual-ctor 身份定谳 ✓\n")
f.write("② push N（反扫）= operator new(N) ⇒ 整对象尺寸 A 级 ✓\n")
f.write("③ [reg+imm] 上界 = 独立于 ①② 的整体尺寸上界 ✓\n")
f.close()
print("forensics v2 written:", OUT)
idc.qexit(0)
