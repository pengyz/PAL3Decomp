---
name: gotcha-variadic-prototype-parens-is-not-one-param
description: C++ 里 `int f(...)` 是**合法的可变参原型**（任意个数实参都合法），不是"1 参"——把它当 1 参使 codegen_invariants 报出 56 处假阳性，并曾被断言为 C2660 成因
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：`f(...)` 不是"1 参"，是"元数不限"

## 现象

`tools/codegen_invariants.py` 的 **check B** 会统计"声明形参数 vs 调用实参数"是否一致。
生成代码里对未解析的 `sub_XXXX` 会发射**省略号占位原型**：

```c
int sub_401070(...);            // free_functions.cpp / RoleSystem.cpp / … 共 106 个符号
...
sub_401070((AStarPathFinder *)this, v24, nVal2, a7, v27);   // 5 个实参
```

判据把 `...` 当作 **1 参** ⇒ 报出 **56 处**"声明 1 参 vs 调用 N 实参"，
且工具 docstring 断言这是 **`C2660/C2664` 的直接成因**。

## **为什么**：这个断言是错的（真实编译器实测）

```
$ wine tools/compilers/msvc6.0/Bin/CL.EXE /nologo /TP /c t.cpp
   int sub_401070(...);
   int user_a(void) { return sub_401070(1, 2, 3, 4, 5); }
   int user_c(void) { return sub_401070(1); }
⇒ 0 错误 ✓
```

C++ 里 **`(...)` 是合法的可变参声明**（MSVC6 接受），任意个数/类型实参都合法
⇒ 它**永远不可能**与调用点数不符 ⇒ 那 56 处**全部是假阳性** ✗。

旁证（同一次普查）：**202 条 `C2660` 里，指名叫省略号声明符号的 0 条** ✓。
⇒ 交叉核对"某条错误是否真的来自某类声明"时，**报文里的符号名就是一票否决的证据** ——
若错误族里一个符号都没出现，那它就不是这个族的原因 ✗。

## 另一个**已被真实编译器证实**的同名机制（对照）

同一个"参数个数不符"错误码，**真正**的成因之一是**名字遮蔽**：

```cpp
struct W { int ShowWindow(int nFlags); };
struct D : W { int g(void *hWnd) { return ShowWindow(hWnd, 4); } };
// ^ C2660: 'ShowWindow' : function does not take 2 parameters   ← 命中继承来的 W::ShowWindow(int)
int g2(void *h) { return ShowWindow(h, 4); }   // 全局作用域: C2065（含 windows.h 时绑定 Win32 ::ShowWindow）
```

⇒ 生成代码里 `ShowWindow(g_hMainWnd, 4)` 落在 `CCBUI::DlgProcEditorMain` 之类的成员函数内，
被继承来的 `UIWnd::ShowWindow(int)` 遮蔽（`class UIStatic : public UIWnd`）。
这是**基线里 14 条 C2660** 的成因，修法是发射 `::ShowWindow(...)`。

## **何时使用**

* 读 `codegen_invariants` 的 [B] 报告时：先问"这些符号是省略号原型吗" ⇒ 是则**不是问题**；
* 写任何"声明/调用一致性"判据时：**可变参/默认参数/`(void)`** 都必须单独归类，
  不能一律用"逗号数 + 1"；
* 看到 `C2660 'X' : does not take N parameters` 时：**首选怀疑名字遮蔽**
  （在该作用域可见的成员 `X` 参数个数 ≠ N），而不是签名注解写错；
* 引用 `docs/specs/2026-09-20-evidence-layer-design.md` 的 "A132/B56/C27/D10" 时：
  **B 已更正为 B1** ✓（该文件已就地标注更正）。