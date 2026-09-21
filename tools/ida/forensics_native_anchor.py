"""⚠️ **已弃用（2026-09-21，独立复核 f2225846 证伪）** ✗ —— 请勿据此下结论。

弃用理由（两条，均已抽验 ✓）：
1. **`??0<Cls>@@` 不是 PAL3.exe 的原生名** ✗：`original/PAL3.exe.asm` 里这些 ctor 是
   `sub_440740` 之类；`??0…` 来自 `data/pdb/pdb_export.json`（**PAL3A** PDB，地址常常与 PAL3 不同，
   例 `??0UIStatic@@QAE@XZ` addr=0x004CBB04 ≠ 0x440740）⇒ **它仍是"我们挂上去的名字"** ✓，属循环锚 ✗。
2. **本脚本把 `??_L`（eh vector constructor iterator）的 size 实参误当分配尺寸** ✗：
   `push offset ctor; push count; push size; call ??_L@…` 里的 `size` 会与 `new` 的 `push N` 混淆
   （真 `new` 形态是 `push N; call ??2@YAPAXI@Z; …; call <ctor>`）⇒ 本脚本给出**假配对** ✗。

⇒ **A 级锚应改为**：**vtable 地址** + **分配点 `push N`（紧邻 `operator new`）** + **ctor 写域**（末写位移）三者互证 ✓。

原说明（仅供追溯）——
原说明（仅供追溯）：IDB 取证 V4：用**编译器原生锚**（`??0<Cls>@@` 重整名）定"尺寸归属"，破循环依赖 ✓。

原理：`??0<Cls>@@QAE@XZ` 是**编译器生成的 ctor 符号**（非注解派生 ✓，除非注解故意覆盖 ✓）。
对每个该类 ctor 的**每个调用点**，向前反扫最近的 `push imm` ⇒ 该 `new Cls` 的**整对象尺寸** ✓。
输出每个 (调用点, push N, 调用者函数) 三元组 ⇒ 同一类的所有真实分配尺寸 ✓。

运行：/home/peng/ida-pro-9.1/idat -A -S"tools/ida/forensics_native_anchor.py" original/PAL3.exe.i64
"""
import re
import idaapi, idautils, idc, ida_funcs, ida_nalt

idaapi.auto_wait()
OUT = r"/home/peng/workspace/PAL3Decomp/pipeline/ida/_logs/_forensics_native_anchor.txt"
CLASSES = ["UITitle_ArcSave", "UIRoleSelectDialog", "CScreenMode", "JusticeBookUI",
           "CCBUIPanel", "CCBUI", "UIListBox", "ScreenEffectNode", "UISceneMap", "UIStatic"]
RE_PUSH = re.compile(r'\bpush\s+([0-9A-Fa-f]+)h\b')     # 只认 hex 字面量 ✓（IDA 用 `424h`）

f = open(OUT, "w", encoding="utf-8")
f.write("=== V4：以编译器原生 `??0<Cls>@@` 为锚的尺寸归属 ===\n\n")
for cls in CLASSES:
    f.write("########## %s ##########\n" % cls)
    # 找原生 ctor 符号（??0 开头 ✓）
    ctors = []
    for ea, nm in idautils.Names():
        if nm.startswith("??0") and cls in nm and "@@QAE@XZ" in nm:
            ctors.append((ea, nm))
    if not ctors:
        f.write("  ✗ 无原生 `??0%s@@QAE@XZ` 符号（⇒ 该类可能无默认 ctor，或名字被注解覆盖 ✓）\n\n" % cls)
        continue
    for cea, cnm in ctors:
        f.write("  ctor %-42s @0x%06X，调用点：\n" % (cnm[:42], cea))
        n = 0
        for xr in idautils.XrefsTo(cea, 0):
            fn = ida_funcs.get_func(xr.frm)
            fnm = idc.get_func_name(fn.start_ea) if fn else "?"
            # 向前反扫 ≤12 条找最近的 push imm ✓
            N, found = None, 0
            ea = xr.frm
            for _ in range(12):
                ea = idc.prev_head(ea)
                if ea == idc.BADADDR: break
                t = idc.generate_disasm_line(ea, 0) or ""
                m = RE_PUSH.search(t)
                if m:
                    N = int(m.group(1), 16); found += 1
                    break
            f.write("    0x%06X  push N = %-8s = %-7s  in %s\n"
                    % (xr.frm, ("0x%X" % N) if N is not None else "(无)", N if N is not None else "-", fnm[:52]))
            n += 1
        f.write("    ⇒ 调用点 %d 个\n\n" % n)
f.write("判读：同一 ctor 的多个调用点若给出**同一个 N** ⇒ 该 N 就是该类的整对象尺寸（原生锚 ✓ 非循环 ✓）\n")
f.close()
print("v4 written:", OUT)
idc.qexit(0)
