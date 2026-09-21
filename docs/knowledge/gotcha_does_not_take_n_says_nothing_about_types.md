---
name: gotcha-does-not-take-n-says-nothing-about-types
description: MSVC 的 "function does not take N parameters" 只说明实参数目，不含类型信息——据此推断该补什么重载会连续失败；必须自己取实参的声明类型
type: gotcha
created: 2026-09-21
updated: 2026-09-21
status: active
sources: [session-2026-09-21]
---

# gotcha：`does not take N parameters` **不含类型信息**

## 现象

看到 7 条 `'CreateFromMemory' : function does not take 1 parameters` 与 5 条 `... 2 parameters`，
我推断"缺一个 1 参重载" ✓ 并加了 `void CreateFromMemory(gbImage2D* img)` ✗ —— **零效果** ✓；
再推断"实参是整数" ✓ 并改成 `void CreateFromMemory(int nFlag)` ✗ —— **仍零效果** ✓。

**原因** ✓✓：`does not take N parameters` **只报告实参数目** ✓；
那 7 条 1 参调用的**实参类型可能彼此不同** ✗（`unsigned __int8` ✓ / `gbImage2D*` ✗ / `void*` ✗）
⇒ **一个重载无法同时覆盖** ✓ ⇒ 必须**逐站点取实参的声明类型** ✓（读调用点所在函数的签名 ✓）：

```bash
grep -n "pData" pal3/src/Misc/MainEquipUI.cpp | head
#  1286: unsigned __int8 MainEquipUI::SetAdornVisible(unsigned __int8 pData)   ← 类型在这里 ✓
grep -n "nValue" pal3/src/Misc/SaleUI.cpp | head
#  2737: int SaleUI::SetValue(unsigned __int8 nValue)                           ← 同上 ✓
```

## 规则

- **报错只给"数目"时，不要推断类型** ✗：
 先 `grep` 出**调用点所在函数的签名**（实参由此而来 ✓），或直接读生成代码里该表达式的声明类型 ✓。
- 若**多个站点类型不一致** ⇒ 这不是"补一个重载"能解的 ✓ ⇒ 属于**发射侧的统一**（见
  [[page:gotcha-verify-the-layer-before-patching]] ✓ 与 [[page:gotcha-interlocking-invariants-block-local-fixes]] ✓）。
- 同族纪律：**"零效果"要先证伪"改动是否参与编译"，再怀疑机制** ✓。
