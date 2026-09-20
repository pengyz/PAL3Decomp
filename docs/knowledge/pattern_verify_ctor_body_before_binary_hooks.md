---
name: pattern-verify-ctor-body-before-binary-hooks
description: 用某个"ctor 地址"做二进制挂钩（分配点/尺寸/归属）之前，先在 asm 里看它本体——注解里的 ctor 可能是静态初始化 thunk；真 ctor 的判据是"写自己类的 vtable"
type: pattern
created: 2026-09-19
updated: 2026-09-19
status: active
sources: [session-2026-09-19]
---

**规则**：任何"用 ctor 当锚点"的取证（分配点尺寸、构造链、归属），先花一次 grep 验证该 ctor 的**本体**；
真 ctor 的可靠判据是 **`mov dword ptr [this], offset <vtable>`**（自己类的 vtable），
而不是注解里写着 `name: <类名>`。

**为什么**：注解里的 ctor 可能根本不是 ctor。实测（2026-09-19）：
`CCBProtectWindow.json` 把 `0x0051D6E0` 标成 ctor、`0x0051D6F0` 标成 dtor，而 asm 里它们是

```
sub_51D6E0:  mov eax, ds:dword_5705B0 ; mov dword_17AD59C, eax ; retn     ; 静态初始化
sub_51D6F0:  jmp sub_51D700
sub_51D700:  fld ds:dword_5705B0 ; fadd st, st ; fstp flt_17AD598 ; retn  ; 算一个全局
```

—— 一个不碰 `this`、只写全局的**编译器生成静态初始化簇**（`.data` 初始化表引用）。
真正的 ctor 是 `0x005160A0`（它写 `off_5704A8`），而它**不在**注解方法表里。
若直接拿 0x51D6E0 当锚点，分配点分析会得"0 个分配点"并让人误判"这个类不分配"。

**何时使用**：
* 做分配点/尺寸取证时：`push N; call ??2@YAPAXI@Z; …; mov ecx, eax; call <ctor>` 里的 `<ctor>`
  必须是真 ctor，否则 N 挂错了类（这正是 §49.1 那次失败的形态）。
* 找真 ctor 的配方：在 `data/annotations/structs/*.json` 里搜 `vtables[].addr` 确认表的归属 →
  在 asm 数据区找该表（`off_XXXX dd offset ...`）→ 看它的 **DATA XREF** 落在哪个函数 →
  那个函数里的 `mov [reg], offset <表>` 就是 ctor。
* 顺带判据：注解方法表里出现"无 `this`、只碰全局、长度 < 10 行、或被 `.data` 初始化表引用"的条目，
  多半是 thunk，应标 `skip` 而不是当方法。
