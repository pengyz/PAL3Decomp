---
type: pattern
date: 2026-09-18
---

# 定归属、定函数名要**看函数逻辑**（最准），不要靠名字投票

## 结论

判断"这个函数属于哪个类、该叫什么名"，**依据顺序**应是：

1. **寄存器来源** —— 最硬的一条：MSVC `__thiscall` 把 `this` 放在 **`ecx`**。
   若 decomp 的第一个局部是 `X *v1; // ecx`，**那就是 `this`**，函数属于 `X`
   （哪怕 Hex-Rays 通篇没写 `this`、`this->` 计数为 0）。
2. **它调用的具名方法** —— 在 `this` 上调用了 `X::SomeMethod` ⇒ 至少属于 `X` 或其派生。
3. **它访问的成员** —— 但**只认经 `this`（或来自 `ecx` 的那个局部）的访问**；
   经其它指针访问的成员**不算**（见 `gotcha_member_name_voting_is_confounded_by_transitive_access.md`）。
4. **算法语义** —— 它在干什么（构造/析构/释放/查找/渲染/存档…）⇒ 决定**名字**。
   例如"释放 `m_pDialogData`/`m_RoleArray` 缓冲区 + `operator delete` + 调 `X::DestroyScript`"
   ⇒ 是**析构/资源释放**语义，名字应是 `~X`（或 `X::Release`），不是 `X::X`。

## 反例（本仓库真实发生）

`0x00411CA0` 曾被注解为 `ScriptObj::~ScriptObj`，decomp 为
`int __cdecl ScriptObj__ScriptObj(int nVal)`、`this->` 出现 0 次。
按"名字投票"会得到一堆假阳性；**按逻辑**一眼定案：

```c
PalScript *v1; // ecx                       // ← this！
PalScript::DestroyScript(v1);               // ← 具名方法
... v2->m_pDialogData / m_RoleArray / m_bCreated ...   // ← 全是 PalScript 成员
... operator delete(...) ; NPC::FreeBuffer(...) ...    // ← 释放语义
```

⇒ 属于 **`PalScript`**，名字 **`~PalScript`** ✓

## 可机械化的部分

* **`// ecx` 的首个局部 ⇒ `this`**：可以自动筛出大量"Hex-Rays 没写 `this` 但其实是成员函数"的条目；
* **调用的具名方法**（`X::Y(` 形态）是第二强信号；
* **算法语义 ⇒ 名字**：这一步需要读代码，难自动化，但**可以按行为族归类**
  （释放/构造/查找/绘制/序列化），再给名字或 `_todo_` 占位。

## 纪律

* 名字**给不出语义就写 `_todo_` 风格占位名**，并在 `name_evidence` 里写明"含义未定"；
  **禁止**为"看起来有语义"而造名（`pattern_annotation_batch_rename_no_evidence.md`）。
* 定案后把**逻辑依据**（ecx 来源 / 调用的具名方法 / 语义判断）写进注解的
  `evidence` / `name_evidence`，供后续复核。
