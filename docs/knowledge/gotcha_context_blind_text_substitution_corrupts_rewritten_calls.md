---
name: gotcha-context-blind-text-substitution-corrupts-rewritten-calls
description: 用一个上下文无关的正则做后处理替换，会命中**已经被上游改写过的**调用尾部，拼出 `obj->Cls::this->Method()` 这种畸形代码；实测既有 15 处，且被 C1003 截断掩盖住
type: gotcha
created: 2026-09-18
updated: 2026-09-18
status: active
sources: [session-2026-09-18]
---

**现象**：`pipeline/gen/stages/stage5_fixup.py` 里把 Hex-Rays 的 `(int)this` 工件
转成成员自调用：

```python
code = re.sub(r'\b(\w+)\(\(int\)this\)', r'this->\1()', code)
```

意图是对的（`Method((int)this)` → `this->Method()`），但 `\b(\w+)\(` 也会命中
**已经被上游（`ast_transform` 的显式-this 分支）改写好的**调用尾部：

| 上游已正确产出 | 被这行替换后 |
|---|---|
| `obj->Cls::Method((int)this)` | `obj->Cls::**this->Method()**` ← 畸形，且实参丢失 |
| `::ShowWindow((int)this)` | `::**this->ShowWindow()**` ← 畸形 |

**实测**：改前生成树里这类畸形共 **15 处**（`::this->Xxx`、`->this->ShowWindow`），
分布在 7 个文件（`CScreenMode`、`EquipUI`、`CUtil`、`CCBSystem`、`CCBStageScene`、
`RoleSystem`、`UIScenePanel`）。**没有任何门禁能看见它们**：

- 这些文件都在 **C1003 截断**名单里（恰好 102 条错误），畸形行产生的错误
  **落在报告窗口之外** ⇒ 普查显示"新增错误 0 / 净增错误码 无"；
- `compile_regression` 只比 ok/fail 与文件级计数 ⇒ 也看不见；
- 只有在 `ast_transform` 的显式-this 证据门被打开、新的同形态位点出现后，
  我才在**内容 diff** 里看到第 16 处，才反查到这条 15 处的既有缺陷。

**修法**：给替换加负向后顾，排除 `\w` `:` `.` `>` —— 该替换只适用**未限定**的自调用：

```python
code = re.sub(r'(?<![\w:.>])(\w+)\(\(int\)this\)', r'this->\1()', code)
```

限定形态交给上游的显式-this 分支（它会产出 `(obj)->Cls::Method(rest)` 或保留静态调用，
两种都比畸形文本可读、报错也更准确）。

**效果**（实测）：畸形 15 → **0**；总错误 **3497 → 3305（−192）**，主要来自那 7 个文件的
级联错误消失（`UIScenePanel` 102→48、`CCBSystem`/`CCBStageScene` 102→45、`CScreenMode` 102→86）；
**C1003 截断文件 15 → 11**（4 个降到上限以下，重新变得可测）。

**可复用的教训**：
1. **后处理替换必须限定上下文**。"看到 `Name((int)this)` 就改成 `this->Name()`" 在
   *未限定* 时对，在 *已限定/已成员化* 时错——而后者恰好是上游刚产出的正确结果。
   同一个文本在管线不同阶段含义不同，替换必须知道自己处在哪一阶段。
2. **同一条正则的"良性"与"有害"取决于上游是否已经改写**。上游修好一处、打开一扇门，
   就可能让下游一个长期沉默的缺陷显形。**每打开一个门都要重做内容 diff**。
3. **畸形代码可能完全被门禁漏掉**：C1003 截断把错误移出窗口、ok/fail 与文件计数
   看不见文本形态。这类缺陷只能靠**内容 diff / 结构不变量**发现——
   本轮的做法是给"畸形形态"写一条可 grep 的不变量（`(::|\.|->)this->\w+` 必须为 0）。
4. **把不变量固化成检查**：比"再看一眼 diff"可靠。见
   `gotcha_error_census_not_a_pure_function_of_the_tree.md`（同一族：门禁看不见的形态）。
