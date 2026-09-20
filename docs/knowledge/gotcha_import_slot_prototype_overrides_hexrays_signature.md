---
name: gotcha-import-slot-prototype-overrides-hexrays-demangled-signature
description: 导入槽（IAT）上残留的"退化原型"会**盖掉** Hex-Rays 从修饰名解出的签名，导致调用点实参被整段吞掉（伪代码 `gbVFileSystem::Read(g_pVFileSys);`）。改槽只能用 ida_nalt.set_tinfo（idc.SetType 失败），且必须 clear_cached_cfuncs 才看得到效果。32 处 C2660 的根因
type: gotcha
created: 2026-09-20
updated: 2026-09-20
status: active
sources: [session-2026-09-20 round-133]
---

**现象**：`asm/pal3/decomp/` 里 15 个函数的伪代码是 `gbVFileSystem::Read(g_pVFileSys);` ——
三个实参凭空消失，生成 C++ 报 `C2660: 'Read' : function does not take 0 parameters`（33 条）。

**二进制里参数是好的**（0x004BB050 `RenderTarget::ReadVFile`）：
`push edi(pFile) / push 40h(size) / push esi(buf) / mov ecx,[eax] / call ebx`，
而且 IDA 反汇编注释就写着 `gbVFileSystem::Read(void *,uint,gbVFile *)`。**丢的是反编译侧。**

**机制**：Hex-Rays 对 `call ds:<slot>` 的处理是
"槽上有类型就用槽上的；槽上没有类型才回退到修饰名"。
实测同一个类里 `Seek/TellPos/Write/OpenFile` 的槽类型是 `<none>` ⇒ 参数完整；
唯独 `?Read@gbVFileSystem@@QAEXPAXIPAVgbVFile@@@Z` 的槽被写成了
`void __thiscall(gbVFileSystem *__hidden this)`（**零栈参**）⇒ 实参被吞。
同类退化槽还有 `?TransformPlane@gbMatrix4@@`、`?Transform@gbMatrix4@@QBEX…`，
以及"参数个数够但约定写成 `__stdcall`"的 `?RenderGeomQuad@gbDynVertBuf@@` /
`?RenderGeomQuadViaStrip@…`（this 直接从参数表里消失）。

**两个坑（都实测过）**：
1. `idc.SetType(ea, "void __thiscall(gbVFileSystem *, void *, unsigned int, gbVFile *)")`
   **对导入槽返回失败**（`ok=None`），槽类型不变。必须走
   `ida_typeinf.parse_decl` + `tinfo_t.create_ptr` + **`ida_nalt.set_tinfo(ea, ptr)`**
   （注意要的是**函数指针**类型，不是函数类型）。
2. 改完立刻 `ida_hexrays.decompile()` **看不到变化** —— Hex-Rays 有反编译缓存，
   必须 `ida_hexrays.clear_cached_cfuncs()`（`export_full.py` 每次跑的是全新进程/新缓存，
   所以流水线里不需要这一步，只有"就地验证"时才需要）。

**修法（已落地，第 133 轮 F73）**：`pipeline/ida/apply_annotations.py::_fix_gbengine_import_slots()`，
放在 `apply` 的**最后**（`save_database` 之前）。签名**完全取自修饰名**（VC6 mangling 自带参数表 +
调用约定），判据只有两条：显式栈参个数 < 修饰名参数个数，或约定不是 `__thiscall`。
实测 249 个导入名 → 233 个 `__thiscall` 成员 → 232 个可解析 → 修正 **5 个槽**，failed=0；
两栏错误数 **2339 → 2286（−53）**，`Read −33`、`RenderGeomQuad −17`，S2 ok 74→75，L1 38（不回退）。

**排查提示**：`?Read@…` 这类名字在 `ida_nalt.enum_import_names` 回调里拿到的是**修饰名**，
**不含括号**；用 `'(' in name` 之类条件做过滤会把 249 个全部滤掉（本 pass 第一版就是这么写错的，
日志只显示 `names=0`）。所以这类 pass 必须把每一级过滤的计数都打出来，
否则"0 个候选"无法区分"真的没有"和"条件写错"。
