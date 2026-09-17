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

---

## 7. A 路线取证结果：**拿到 A 级证据，但暴露一个必须解决的矛盾**

### 7.1 ✅ A 级证据（字节级）：槽 4 = `0x00445B90`，UI 族共享

```
0x00445B90 出现在【4 个类】vtable 的【同一个偏移 16（槽 4）】:
   UIStatic  [4] 0x00445B90  IDB槽名=Create
   UIFrameWnd[4] 0x00445B90  IDB槽名=Create
   CCBItemWindow[4] 0x00445B90 IDB槽名=Create
   UIWnd     [4] 0x00445B90  IDB槽名=Create
```
⇒ **`vftable->Create` = 槽 4 = `0x00445B90`**（**字节级证据，非猜测**）。

### 7.2 ✅ 反汇编证据：真实签名是**2 个有效参数**

```
00445b90: mov 0x4(%esp),%eax     ← 读 [esp+4]（arg1）
00445b95: mov %ecx,%esi          ← esi = this
00445b9c: lea 0x10(%esi),%edi    ← 目标 = this+0x10
   ...   拷贝 16 字节（= tagRECT 大小！）到 this+0x10
00445bba: mov 0x14(%esp),%ecx    ← 读 [esp+0x14]（arg3）
00445bc0: mov %ecx,0x20(%esi)    ← 写入 this+0x20
```
⇒ 形态为 `Create(tagRECT *pRect, int parent)`（**2 个有效参数**），
与 **IDB 槽签名 `int (__thiscall *)(int, int)` 一致**。

**⚠️ 间接支持**：它把 **16 字节**拷贝到 `this+0x10` —— 与标注的 `CCBItemWindow::Create(int id, tagRECT *pRect, int parent)` 里 `tagRECT` 有关；
但 `[esp+4]` 被当作**源指针**使用（`mov (%ecx),%eax` 等 4 次 4 字节读），说明 arg1 是**指针**，不是 `int id`。

### 7.3 ❌ 暴露的矛盾：**调用点传 4 个参数，实现只读 2 个**

```c
// decomp（UIGameOver::Create:19-23）
((void (__thiscall *)(UIStatic *, _DWORD, int *, UIGameOver *))vftable->Create)(
   &this->m_Blood,   // 对象
   0,                // ?
   &v3,              // ?
   this);            // ?
```
若实现是 `Create(pRect, parent)`（this 由 `%ecx` 传入），则**其余实参应为 2 个**；
而 decomp 给了 **3 个**（`0`, `&v3`, `this`）⇒ **多传一个 ⇒ stdcall 下 `%esp` 会错位 4 字节**。

**⇒ 该处【不能】简单改成 `(&this->m_Blood)->Create(0, &v3)`** —— 必须先把
**"调用点参数个数 / 类型" 与 "实现" 对齐**，而那需要判断"哪个实参是多余的"。

### 7.4 ⇒ A 路线的真实形状（比"补一条注解"复杂）

A 路线**拿得到 A 级证据**（§7.1 槽位、§7.2 签名），但**要落成 `methods` 注解还缺一步**：

| 缺口 | 内容 |
|---|---|
| **多传参矛盾** | 调用点 4 参 vs 实现 2 参 ⇒ 需判定多余实参（可能 `/O2` 下寄存器传参未体现在 `%esp` 偏移里）|
| **类归属** | `0x00445B90` 现记为 `CCBItemWindow::Create`，但它在 4 个类的槽 4 共享 ⇒ 需判断它是"UI 族共享实现"还是"某类的实现被折叠" |
| **空槽** | `UIStatic` 的 `UIInfo` 空槽（byte 0x56A600）里槽 4 无对应函数名 ⇒ 佐证 `UIStatic` 未实现自己的 `Create` |

**⇒ 结论：A 路线可行但**单点成本高**（需逐槽对齐调用点与实现），
**不适合按"补 26 个类"的粒度批量推进**；应按**单类单槽**粒度做，且每步验证。**
