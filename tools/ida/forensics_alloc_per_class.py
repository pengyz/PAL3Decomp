"""IDB 取证 V3：把 `operator new(N)` 的 N **归到具体的类**（headless ✓ 查 IDB ✓）。

判据（A 级 ✓）：MSVC 的 `new Cls(...)` 惯用法是
    push N ; call ??2@YAPAXI@Z ; <push args> ; call <Cls 的 ctor>
⇒ 从每个 `operator new` 调用点**向后 ≤16 条指令**找**第一个 call**，
  若该 call 的目标是某个**目标类的 ctor** ⇒ 该 `push N` 就是**该类的整对象尺寸** ✓✓。
这同时解决两件事：**尺寸**（N ✓）与**ctor 身份**（被调的那个 ✓）。

运行：/home/peng/ida-pro-9.1/idat -A -S"tools/ida/forensics_alloc_per_class.py" original/PAL3.exe.i64
输出：pipeline/ida/_logs/_forensics_alloc_per_class.txt
"""
import re
import idaapi, idautils, idc, ida_funcs, ida_nalt

idaapi.auto_wait()
OUT = r"/home/peng/workspace/PAL3Decomp/pipeline/ida/_logs/_forensics_alloc_per_class.txt"
TARGETS = ["UITitle_ArcSave", "ScreenEffectNode", "CCBUI", "CScreenMode", "JusticeBookUI",
           "UIRoleSelectDialog", "UIListBox", "CCBUIPanel", "UIScenePanel", "CCBRoleState",
           "UISceneFrm", "CCBStageScene", "UICoverFrm", "UISceneMap"]
RE_PUSH = re.compile(r'\bpush\s+(?:offset\s+)?([0-9A-Fa-f]+)h?\b')
RE_CALL = re.compile(r'\bcall\s+(\S+)')

f = open(OUT, "w", encoding="utf-8")
f.write("=== IDB 取证 V3：operator new(N) 归属到类 ===\n")
f.write("IDB=%s\n\n" % ida_nalt.get_input_file_path())

# 先建"ctor 地址 ⇒ 类名"表
ctor_of = {}
for cls in TARGETS:
    for ea in idautils.Functions():
        n = idc.get_func_name(ea) or ""
        if cls in n and (n.startswith("??0") or "_%s" % cls in n or "ctor" in n.lower()):
            ctor_of[ea] = (cls, n)
f.write("候选 ctor 数：%d\n\n" % len(ctor_of))

res = {}
for ea in idautils.Functions():
    fnm = idc.get_func_name(ea) or ""
    body, cur = [], ea
    for _ in range(2000):
        if idc.get_func_attr(cur, idc.FUNCATTR_START) != ea: break
        body.append((cur, idc.generate_disasm_line(cur, 0) or ""))
        cur = idc.next_head(cur, ea + 0x8000)
        if cur == idc.BADADDR: break
    for i, (ea2, t) in enumerate(body):
        if not ("??2@YAPAXI@Z" in t or "operator new" in t):
            continue
        N = None
        for j in range(max(0, i - 10), i):
            m = RE_PUSH.search(body[j][1])
            if m: N = m.group(1)
        # 向后 ≤16 条找第一个 call，看是否指向某个候选 ctor ✓
        callee = None
        for k in range(i + 1, min(len(body), i + 17)):
            m = RE_CALL.search(body[k][1])
            if not m: continue
            tgt = idc.get_name_ea_simple(m.group(1))
            if tgt != idc.BADADDR and tgt in ctor_of:
                callee = ctor_of[tgt]; break
            tgt2 = idc.get_operand_value(body[k][0], 0)
            if tgt2 in ctor_of:
                callee = ctor_of[tgt2]; break
        if callee:
            cls = callee[0]
            res.setdefault(cls, {})
            res[cls].setdefault(N, []).append((ea2, fnm, callee[1]))

for cls in TARGETS:
    f.write("########## %s ##########\n" % cls)
    d = res.get(cls) or {}
    if not d:
        f.write("  ✗ 未找到 `push N → new → 本类 ctor` 的惯用法（⇒ 该类可能不经 operator new，或 ctor 名未被识别 ✓）\n\n")
        continue
    for N, lst in sorted(d.items(), key=lambda x: -len(x[1])):
        f.write("  push N = %-8s (%d 次)  ctor=%s\n" % (N, len(lst), lst[0][2][:44]))
        for ea2, fnm, _ in lst[:3]:
            f.write("      0x%06X  in %s\n" % (ea2, fnm[:60]))
    f.write("\n")

f.write("=== 判读 ===\n")
f.write("push N + 紧随其后的 `call <本类 ctor>` ⇒ N = 该类整对象尺寸（A 级 ✓）\n")
f.write("同一类出现多个 N ⇒ 该类有多个 ctor/尺寸（或存在别的类实例化 ✓）⇒ 需按 ctor 分别定 ✓\n")
f.close()
print("v3 written:", OUT)
idc.qexit(0)
