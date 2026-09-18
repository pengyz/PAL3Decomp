---
name: gotcha-set-key-shape-must-match-consumers
description: 同一个构建集合时，相邻两行一处 split 了参数表、另一处没 split，而所有消费方都用裸名比较 ⇒ 那条守卫"恒为假"从未生效；实测 104 条里 96 条形态不符
type: gotcha
created: 2026-09-18
updated: 2026-09-18
status: active
sources: [session-2026-09-18]
---

**现象**：`pipeline/gen/data.py` 构建 `store.static_methods`（`__cdecl` 静态方法集合）时：

```python
# decomp `name` 是**带参数表**的（"Cls::M(int)"）
self.method_sigs.setdefault(_name.split('(')[0], _sig)   # ← 归一化了
if '__cdecl' in _sig and '__thiscall' not in _sig:
    self.static_methods.add(_name)                       # ← 漏了，存的是 "Cls::M(int)"
```

而**所有**消费方都用裸名比：

| 位置 | 比较式 |
|---|---|
| `ast_transform.py:529` | `qualified = '%s::%s' % (class_name, method_name)` |
| `ast_transform.py:702` | `_qualified = '%s::%s' % (class_name, method_name)` |
| `stage4_substitution.py:721` | `('%s::%s' % (cls, meth)) in store.static_methods` |

⇒ 只要那条名字带参数表，`in static_methods` 就**恒为假**。**实测 104 条里 96 条带参数表**，
即这条守卫**从未生效**。

**为什么这条最危险**：它不报错、不抛异常、没有日志。守卫失效的后果是
**`__cdecl` 静态成员的第一个实参被当成 `this`**，于是被吞掉或用于构造成员调用：

```
(((Array *)j))->Array::Copy();                        ← 实参 j 被当成 this，Array::Copy() 少传一个参数
(((UIScene *)"M22"))->UIScene::ProcessInput(0)        ← 把字符串字面量当 this
```
注意**旧形态在 MSVC 下能编译**（静态成员可以经实例调用，对象被忽略），
所以它同时骗过了编译门禁 —— 这是**静默的语义错误**，不是编译错误。

**强信号（找这类 bug 的最快办法）**：**同一段代码里相邻两行用了不同的归一化**。
`method_sigs` 与 `static_methods` 出自同一循环、同一变量，一行 split 一行没 split ——
这本身就是最强的 bug 指示。凡是"建集合"与"用集合"分离的地方，都应核对**键形态**。

**修法**：`self.static_methods.add(_name.split('(')[0])`。**先写用例确认它是红的**：

```
tests/test_static_methods_guard.py
  test_static_methods_entries_are_bare_qualified_names   # 修前：96/104 带参数表 → 失败
  test_method_sigs_and_static_methods_use_the_same_key_shape  # 修前：失败
  test_static_guard_fires_for_every_stored_entry          # 行为侧
```
（补这条用例是必须的：**既有的 `test_pipeline.py:76` 传的是裸名 `{'Foo::StaticMethod'}`，
覆盖不到真实形态** —— 改前改后都过，等于没有护栏。）

**效果（实测）**：S2 66 → **67**（`Scene.cpp` 转 ok）；总错误 3305 → **3205（−100）**；
大降 `C2660 −65`、`C2227 −10`、`C2653 −10`、`C2671 −5`；`L1 17` 且**多重集恒等**；
生成文本变化 23 个文件 / 191 hunk，全部是"静态成员首参被还原为真实实参"。

**一处需要归因的假回归（已查清）**：`CCBStage.cpp` 真新增 5 条 C2440
（`v8 = CCBStage::ProcTurnToRole` 把成员函数指针赋给 `void *`），但该文件**只有 6 行变化**
（227/487/490/494/531/12618），**这 5 条错误所在行（3540/3543/3560/3569）逐字未变**，
且同缺陷的 3512/3524 改前就已报出 ⇒ 是**错误恢复位移**（同 TU 里修掉早期错误后，
MSVC6 把此前被抑制的错误报了出来），不是引入的缺陷。见
`gotcha_error_census_not_a_pure_function_of_the_tree.md`。

**流程副作用（记录）**：因为 `tools/regression_detector.py` 现在会因"净增错误码 / 真新增错误"
而拒刷基线并 exit 1，**任何修掉早期错误的改动都会触发它**（churn 使它报警）。
这是**保守设计的正确行为**，但流程必须是：**逐条归因 → 确认是位移 → 刻意刷新**
（`python3 tools/regression_detector.py --save-baseline`），而不是绕过它。
