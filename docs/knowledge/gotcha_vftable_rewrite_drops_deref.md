---
name: gotcha-vftable-rewrite-drops-deref-and-needs-member-decl
description: vtable 派发改写 `(*ptr)->__vftable->M(*ptr,args)` 必须保留 `(*ptr)`；但只改这一行必被门禁拦下——还要求"方法确是该类成员"（实测 L1 35→34、S2 ok 75→74）
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：vtable 派发改写丢解引用，且"改对接收者"不等于"能编译"

## 现象

`pipeline/gen/stages/stage3_cleanup.py` 的 `run()` 里有一段注释自述为

    # Pattern 2: (*ptr)->__vftable->Method(*ptr, extra_args) → ptr->Method(extra_args)

repl 是 `\1->\2(\3)` —— **把 `(*...)` 的解引用层级丢掉了**。实测：

```
Hex-Rays 原始输出（对的）:
  ((void (__thiscall *)(UIStatic *, int))(*p_m_pBack)->__vftable->ShowWindow)(*p_m_pBack, 1);
生成的 C++（错的）:
  p_m_pBack->ShowWindow(1);
```

`ptr` 在此形态里**必然是多级指针或数组**（否则 Hex-Rays 不会写 `(*ptr)->`）：
实测 `UIStatic **p_m_pBack`（局部，取自 `&this->m_pBack`）、`UIListBox *m_pMagicList[6]`（数组成员）。
丢掉 `*` 后接收者是 `T**`/数组，不是类类型 ⇒ MSVC `C2227`
`left of '->ShowWindow' must point to class/struct/union`。

规模（decomp 语料全量实测）：**76 站点 / 29 文件** —— `ShowWindow` 53、`Create` 16、`_sdtor_call_dtor` 7。

## **为什么**：只修接收者会被门禁拦下（单变量 A/B 实测）

改成 `(*\1)->\2(\3);` 后：

| 指标 | 变化 |
|---|---|
| `C2227` | **−41** ✓ 意图中的收益 |
| `C2039` | **+22** ✗ |
| S2 ok | **75 → 74** ✗（`Combat/CCBProtectWindow.cpp` ok→fail）|
| L1 | **35 → 34** ✗（matched 265/319 → 256/309）|

`C2039 +22` 与 decomp 计数**完全吻合**，两个独立机制：

1. **`Create` 16 站点**：`(*p)->Create(1)` 要求 `Create` 是该类成员。
   `(*p)->ShowWindow(1)` 能编译只是因为 `class UIStatic : public UIWnd` 继承到了
   `virtual int ShowWindow(int)`；`Create` 没有在 UIStatic/UIPushButton/UIListBox/UIScene 里声明。
   ⚠️ **不能靠恢复注解来修**：UIStatic 的 `methods`/`vtables` 是上一会话因真实 vtable(`0x56B018`)
   未定而**刻意剥离**的（`data/annotations/structs/UIStatic.json` 的 `_strip_note`），
   恢复即违反"禁止猜测性修改"。
2. **`_sdtor_call_dtor` 7 站点**：它依赖 `stage5_fixup.py:892-898` 的 `delete \1` 规则，
   而该规则只接受**裸标识符**接收者 ⇒ `(*ptr)->_sdtor_call_dtor(1)` 不再被转成 `delete`。
   **这就是那唯一一个 ok→fail 单元**（基线该行是 `delete p_m_pWHFace;`）。

## **何时使用**

动 vtable 派发解析（`stage3_cleanup.py` 的 Pattern 1/2、`_decode_vtbl_call`、
`_resolve_vftable_calls_ast`）或 `stage5_fixup.py` 的 dtor→delete 规则时：

* 完整批次 = ①保留 `(*ptr)` 解引用 **+** ②`stage5_fixup` 接受 `(*ident)` 形态
  **+** ③目标类对槽位方法名的声明，或"目标类没有该方法时回退到既有 stub 路径"
  （后者即 `docs/specs/2026-09-21-vtable-resolver-refactor-design.md` 的 S2/S3）。
* 验收测试（**自门控**：批次未落地 ⇒ SKIP，落地即生效；只落一半 ⇒ FAIL）：
  `tests/test_vftable_deref_preserved.py`。
* 就地警告注释已写在 `stage3_cleanup.py` 该 `re.sub` 上方，含上述全部实测数字。