# 可行性验证：把 `vftable->Method` 分派解析成具名方法调用（A′）

> 用户质疑（正确）：**"vtbl 是编译器内部机制，在反编译代码里不应该可见"**
> ⇒ 不应发 `vtbl_defs.h` 暴露它，而应**把分派解析回源码级方法调用**。

## 1. 项目既有机制（我先前忽略了 —— 它就在同一个文件里）

```
pipeline/gen/stages/stage3_cleanup.py:431  _decode_vtbl_call(call_node)
    """Decode a vtable dispatch call_expression.
       Returns dict(obj, method, offset, cls_hint, ret, params) or None."""
    · 识别形态：`<obj-chain>->__vftable-><Method>` 与 `<obj-chain>->__vftable+N`
    · 从 cast 里取 ret/params ⇒ cls_hint = 首个参数的类型

pipeline/gen/stages/stage3_cleanup.py:487  _resolve_vtbl_method(d)
    · 用 store.struct_vtables 把 (cls_hint, method/offset) 映射成方法名

pipeline/gen/stages/stage3_cleanup.py:505  _vtbl_stub_names(ret, params, idx)
    · 解析不出时生成 `static ... pal3_vtbl_unk_N(...)` 存根
```
产物中 `pal3_vtbl_unk_` 出现 **927 次** ⇒ 项目**本就在消除 vtable 机制**。

## 2. 本目标形态（`UIGameOver::Create`，实测 decomp）

```c
void __thiscall UIGameOver::Create(UIGameOver *this)
{
  vtbl_0056AE2C *vftable;                              // ① 局部变量（Hex-Rays 给出真实类型）
  ...
  vftable = this->m_Blood.__vftable;                   // ② 从对象取 vptr
  ...
  ((void (__thiscall *)(UIStatic *, _DWORD, int *, UIGameOver *))vftable->Create)(
    &this->m_Blood, 0, &v3, this);                     // ③ 首参 = 对象本身
}
```

⚠️ **现有 `_decode_vtbl_call` 覆盖不到它**：它只认 `obj->__vftable->Method`（inline 形态），
而这里是 **"先存局部变量、再 `local->Method`"** 形态。

## 3. 等价变换（目标输出）

```cpp
(&this->m_Blood)->UIStatic::Create(0, &v3, this);
```
依据：C++ 里 `obj->VirtualMethod(args)` 编译结果**就是** vtable 分派
（`call [vptr+4*slot]`，首参 this）⇒ 与原二进制**等价**，且**vtable 机制完全不可见**。

## 4. 可行性逐项核对（**实测**）

| # | 需要的信息 | 是否可得 | 来源 |
|---|---|---|---|
| ① | 局部变量声明 `vtbl_X *vftable;` | ✅ | decomp/AST |
| ② | 赋值 `vftable = <obj>.__vftable` ⇒ 对象表达式 | ✅ | decomp/AST |
| ③ | `vftable->Create` 的**槽名与偏移** | ✅ | **`ida_structs['vtbl_0056AE2C'].data_members`**（`Create` → offset 16 = 槽 4）|
| ④ | 对象类型 | ✅ | 生成头（`m_Blood: UIStatic`，`UIGameOver.h:13`）|
| ⑤ | **槽 4 对应"哪个具名方法"** | ❌ **数据缺口** | `UIStatic` 的注解 `methods` 里**没有 `Create`**（只有 `Destroy/Render/OnMessage/Update/CreateWithTextures/…`）|

**⇒ 结论：变换的"机制"可行（①②③④ 齐备），但"方法名解析"（⑤）存在数据缺口。**
无法解析时应**退回既有 stub 行为**（`pal3_vtbl_unk_N`）——**不编造方法名**（CLAUDE.md 禁止猜测性修改）。

## 5. ⇒ 修正后的实施路径

| 序 | 动作 | 说明 |
|---|---|---|
| **1** | 在 stage3 新增解码分支：识别"**局部 vftable 变量**"形态（②+③），解析出 `(对象表达式, 槽名/偏移, cls_hint)` | 复用 `_decode_vtbl_call` 的返回结构 |
| **2** | 方法名解析**优先用** `vtbl_X.data_members[slot].name`（**来自 IDB，非编造**）；再用 `_resolve_vtbl_method` 的既有路径 | ⑤ 的缺口因此**部分可补**（`Create` 这个名字 IDB 有） |
| **3** | 解析成功 ⇒ 生成 `(<obj>)-><Cls>::<Method>(<其余实参>)`；失败 ⇒ **保留 stub** | 不编造 |
| **4** | **最小验证**：`UIGameOver` 的错误 1→0；再跑 `codegen → probe → match`，**必须验证 `L1` 不回退**（基线 `L1=16`）| 纪律要求 |

**⚠️ 预期待确认**：若 Step 2 用 IDB 的槽名 `Create`，则产物是
`(&this->m_Blood)->Create(0, &v3, this)` —— 但生成头里 `UIStatic` **没有 `Create` 声明**
⇒ 仍会 C2039。**⇒ 必须先确认"用 IDB 槽名"能否落到一个已声明的方法**，
否则需**同时补注解**（`UIStatic::Create` 的槽位与签名）——那属 annotation 工作，需 A 级证据。

## 6. 我的错误记录（本会话第 N 次同类）

自造 `vtbl_defs.h` 之前**未查项目既有机制**，而该机制**就在同一个文件里**（早先 grep 过其名字）。
⇒ 与之前"先动手后查约定"同型。**规程：动手前先 grep 目标关键词，列出既有机制。**
