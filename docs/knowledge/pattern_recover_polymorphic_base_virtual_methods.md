---
name: pattern-recover-polymorphic-base-virtual-methods
description: 从二进制取证"多态基类的虚方法集合"的完整方法链——含 MSVC6 vtable 发射条件、表边界判定、槽位函数识别
type: pattern
created: 2026-09-15
updated: 2026-09-15
status: active
sources: [session-2026-09-15]
---

**规则**：当一个类的注解是 `+0 = __vftable` 但 `methods` 为空（"F2 缺口"）时，
它的 vptr 无法由 codegen 复现——因为 `virtual` 只能声明**新槽**，不能凭空造出 vptr。
**恢复该类虚方法集合的可靠路径如下**（本会话实测走通，产出了 `??_7CEffCylinder@@6B@` 的 13 槽合成表）。

## 方法链（按顺序）

1. **界定表的边界——不要用"遇到非 `.text` 指针即停"**
   `tools/vtable_scanner.py` 的这个判据在本项目**失效**：实测 `CEffAction` 表 `0x56F5E4`
   读出了 **96 槽**，因为该地址之后**所有 DWORD 都落在 `.text`**（多张相邻表连续排布）。
   **正确做法**：用 **ctor 实写的 vptr 地址**作边界——
   `original/PAL3.exe` 里有 **467 个** `movl $0x5xxxxx,(%reg)` 形式的 vptr 存储，
   其目标即各表**起始地址**；相邻起始之差 = 前一张表的长度。工具：`tools/vtable_compare.py`。
   ⚠️ 对**多继承的连续子表**此法仍不完美（`0x56F7C8` 读到 65 槽，真实表在 `0x56F804`
   之后接的是**别的类** `RenderTarget2::*`）⇒ 需结合"槽位函数归属"人工核对。

2. **识别槽位函数**：把槽位地址反查 `decomp`/`annotations` 的 VA → 名字。
   无名槽往往是**编译器生成的桩或删除析构函数**，用反汇编特征识别：
   - **deleting destructor**：`test $0x1,%al`（或 `testb $0x1,0x8(%esp)`）+ **恢复 vptr**
     （`movl $0x<表地址>,(%esi)`）+ 条件 `call <operator delete>`
   - **返回 0 的桩**：`xor %al,%al; ret $0x4`
   - **空槽桩**：`ret $0x10`（参数 4 个 DWORD）/ `ret`（无参）

3. **用受控最小件验证合成机制**（不要直接改仓库头文件再猜）：
   构造与目标类**同形**的最小类（多态基类 + 非多态第二基类 + 按声明序的虚方法），
   编译后用 `tools/coff_vtable.py --obj` 读 `??_7<Cls>@@6B@`，确认**槽序 = 源码声明序**。
   本会话实测的三条语义：
   ```
   [0]          = deleting destructor（虚析构时占槽）
   [1..]        = 直接基类的槽（原地继承，未 override 的指基类实现）
   其后的新虚方法 = **按源码声明顺序追加**
   ```

4. **补注解后再比对**：给多态基类的 `.h` 补上取证到的 `virtual` 声明，
   编译目标类，用 `tools/coff_vtable.py` 与 `tools/vtable_compare.py` **逐槽比对**。

## ⚠️ MSVC6 的 vtable 发射条件（本会话新发现，是"编不出表"的第二个原因）

**MSVC6 只在"定义了该类的虚函数"时才发射它的 vtable**（key-function 语义）。
实测同一 TU 的 5 个变体：

| 变体 | 内容 | 产出 vtable |
|---|---|---|
| A | 仅实例化 `Cls g;` | **0** |
| B | 取虚成员指针 `&Cls::Method` | **0** |
| C | **定义全部 10 个虚函数** | **0** |
| **D** | **定义任一虚函数 + 定义虚析构 `Cls::~Cls(){}`** | **1** ✓ |

⇒ 若某类"编不出 vtable"，先查**它的虚析构是否被定义**——
生成头里常见 `~Cls();`（**非虚声明**）且 `.cpp` 因错误不产出 `.obj`，
则该表**永远不会被发射**，与基类是否多态无关。

## ️ `??_E` 与 `??_G` 是**同一个函数**（不要当成两个）

`??_E<Cls>@@UAEPAXI@Z`（vector deleting dtor）在 `.obj` 符号表里的
**storage class = 105 = `IMAGE_SYM_CLASS_WEAK_EXTERNAL`（别名）**，
而 `??_G<Cls>@@UAEPAXI@Z`（scalar）持有**实际定义** ⇒ 链接器做 COMDAT 解析，
**两者最终同地址**。⇒ 不要用"vtable 引用 `??_E`、二进制用 `??_G`"作为不可复现的理由。

## 何时使用

- 修 `C2039 "'__vftable' : is not a member"` 族（本项目 **718 条 / 38 文件**）时——
  这类报错说明生成头缺 vptr，**根因是多态基类的虚方法未标注**，不是名字问题。
- 判定"C-V：把 vtable 表示收口到 C++ `virtual`"是否可行时（本会话结论：**机制可行**，
  剩余是**数据供给**）。
- 任何"某类 `sizeof` 与二进制不符"的排查——先确认它**有没有** vtable，再谈布局。

## 工具

| 工具 | 职责 |
|---|---|
| `tools/vtable_scanner.py` | 读**二进制**侧槽位（⚠️ 边界判据会吞并相邻表）|
| `tools/coff_vtable.py` | 读**编译产物**侧 `??_7` 表（`--selfcheck` 自检 PASS）|
| `tools/vtable_compare.py` | 按 **ctor 实写地址**界定二进制表边界 |