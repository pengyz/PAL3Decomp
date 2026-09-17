# 缺陷定位：codegen 丢失 `UIStatic::UIStatic()` 的**函数头** ⇒ `UIStatic.cpp` 编译失败

> 这是"5 个近失文件"（`UICamera` 7 错、`UIStatic` 6 错…）的第一个**具体根因**，
> 且它是**产物缺陷**，不是注解缺陷。

## 1. 缺陷现场（`pal3/src/Misc/UIStatic.cpp`，逐行）

```cpp
 100|   ...（前一个函数的结尾）
 105| // 0x00440740
 106| UIStatic::UIStatic()          ← 函数头（正常）
 107| {
 108|   Parent_Data **p_m_fonttype; // eax
 ...
 130|   *(_DWORD *)&this->m_text[8] = 0;
 131|   *(_DWORD *)&this->m_text[12] = 0;
 132| }                              ← 构造函数体结束
 133|
 134| // 0x004407A0
 135|   return (int)this;            ← **孤立语句（无函数头、无 `{`）**
 136| }
 137|
 138| // 0x004407C0
 139| UIStatic::~UIStatic()
 140| {
```

**编译错误**（实测 6 个）：
```
UIStatic.cpp(135) : C2143 syntax error : missing ';' before 'return'
UIStatic.cpp(136) : C2143 ×3
UIStatic.cpp(140) : C2143 + C2447 missing function header (old-style formal list?)
```

## 2. 精确归因：**`0x00440740`（构造函数）的函数头丢失**

- `105` 行的 `// 0x00440740` 注释**在**，说明 codegen **知道**有这个函数；
- **但它的函数头（`UIStatic::UIStatic()` + `{`）被丢掉了** ⇒ 其后所有内容都被解析为顶层语句 ⇒ 从 `135` 起语法崩。
- **⇒ 缺陷是"地址注释后的函数头缺失"，不是 `_scalar_dtor` 的问题。**

**`_scalar_dtor` 是第二层现象**：`0x004407A0` 的 decomp 名是
`` UIStatic::`scalar deleting destructor'(uint) ``、注解 `methods` 记为 `_scalar_dtor`
（`signature: "int __thiscall(void *Block, char)"`、`source: vtable_migrated`）。
codegen 把它的**声明**发进了头（`UIStatic.h:40` 有 `int _scalar_dtor(void *Block, char);`），
**但 `.cpp` 里把函数头去掉了、只留 `return (int)this;` + `}`**（带 `// 0x004407A0` 注释）。

**并与既有跳过逻辑不一致**：
```
pipeline/gen/stages/collect.py:193-198
    # Skip compiler-generated _scalar_dtor functions.
    # These are vtable wrappers around virtual destructors; the compiler
    # generates them automatically from 'virtual ~ClassName()' declarations.
    if '_scalar_dtor' in method or method.startswith('_sdtor'):
        store.scalar_dtor_classes.add(cls)
        continue
```
⇒ **`collect.py` 明确"跳过"它**，但 `.cpp` 产物里**仍有它的体** ⇒ **跳过逻辑与 `.cpp` 生成不一致**。

**对照**：`CEffShock.cpp` 里**完全没有** `_scalar_dtor`（`grep` 计数 0）⇒ 该类没有此问题
⇒ **同一缺陷在不同类上表现不同**（有的残留体、有的不残留）。

## 3. ⇒ 这意味着什么

| 项 | 判定 |
|---|---|
| **性质** | **codegen 产物缺陷**（丢失函数头 + 跳过逻辑不一致） |
| **不是** | 注解问题（注解记录完整：`_scalar_dtor` 有名有签名） |
| **影响** | 使文件**必然编译失败**（语法崩在 `135` 行，后续全部连带错误） |
| **修复收益** | 修好 ⇒ `UIStatic.cpp` 很可能 **passing ⇒ `ok` +1**；同类文件（`UICamera`/`JusticeBookUI`/`UITitle_BBTY`/`scScriptInstance`）**若同因，则 +5** |
| **修复位置** | codegen 的"函数定义发射"处（**尚未定位到确切函数**） |

## 4. ⚠️ 诚实标注

1. **我未定位到"函数头发射"的确切代码位置**（`grep "// 0x"` 只找到 `stage3_cleanup.py` 的
   单行注释替换，不是函数定义拼接处）；**修复前必须找到它**。
2. **我未验证**另外 4 个文件是否**同因**（只确认 `UIStatic` 与 `CEffShock` 的表现不同）。
3. **我未验证该缺陷是何时引入的**（可能是本会话某次 codegen 改动，也可能是既有的）。
   ⇒ 若要闭合"`ok` 56→51"的因果，**需先查这 5 个文件是否同因**，再查引入时点。

## 5. ⇒ 下一步（据本发现，顺序明确）

| 序 | 动作 | 判据 |
|---|---|---|
| **1** | 定位"函数定义发射"代码（从 `.cpp` 里 `// 0x…` 注释的来源反查） | 找到拼接函数头的函数 |
| **2** | 查为什么 `0x00440740` 的头被丢（是否与 `_scalar_dtor` 跳过、或与签名/重载有关）| 复现最小案例 |
| **3** | 验证另 4 个文件是否同因 | 各自的首个语法错误行是否也在"缺失函数头"处 |
| **4** | 修 + 跑管线 | `ok` 应 +1～+5；`L1` 不得回退 |
