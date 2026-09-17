# 更正 + 最终定位：`UIStatic.cpp` 的孤立 `return (int)this;`（codegen 缺陷，非注解）

> **本文件更正我上一版** `_cleanup_finding_codegen_missing_func_header.md` 的**标题与归因**。

## 1. 更正：**函数头没有丢失**（我看错了行）

上一版称"`UIStatic::UIStatic()` 的函数头丢失"——**错误**。逐行核实：

```
107| // 0x00440740
108| UIStatic::UIStatic()     ← **函数头在**
109| {
 ...  构造函数体
132| }                         ← 正常结束
134| // 0x004407A0
135|   return (int)this;       ← **唯一的异常**
136| }
138| // 0x004407C0
139| UIStatic::~UIStatic()    ← 正常
```
⇒ **缺陷是 `0x004407A0`（`_scalar_dtor`）只有函数体、没有函数头。**

## 2. 归因链（逐条实测）

| 假设 | 检验 | 结论 |
|---|---|---|
| 函数头丢失 | 逐行核实 | ❌ **推翻**（头在 108 行）|
| transform 阶段剥掉 | 离线跑 5 个 stage | ❌ 排除（头在全部阶段存活：`void UIStatic::UIStatic()`）|
| **注解 `_scalar_dtor` 条目造成** | ① 移除 `UIStatic.json` 的 `0x004407A0` 条目 → 重跑 codegen ⇒ **产物不变**<br>② 再**重跑 export** → codegen ⇒ **产物仍不变**（仍 6 错）| ❌ **排除** |
| **`collect.py` 的跳过逻辑** | `collect.py:193-198` 明确 `# Skip compiler-generated _scalar_dtor functions` 且 `continue` | ⚠️ **但 `.cpp` 里仍有它的体** ⇒ **跳过逻辑与 `.cpp` 产物不一致** |

**⇒ 缺陷在 codegen 层（从 `decomp` 生成），不是注解层。**
**⇒ 对照**：`CEffShock.cpp` 里完全没有 `_scalar_dtor`（`grep` 计数 0）⇒ **同一缺陷在不同类上表现不同**
（可能与该类的 `_scalar_dtor` 是否被 `collect` 之外的通路选中有关）。

## 3. ⇒ 修复方向（下一步）

| 序 | 动作 |
|---|---|
| **1** | 在 `emit_cpp.py` 的**函数发射**处（`:409-411` 的 `for addr, code in transformed`；`transformed` 由 `:349-355` 从 `methods` 构建）查：为什么 `_scalar_dtor` 的 `code` **只有体**（说明它在进入 `transformed` 前已被某处剥离了头）|
| **2** | 或在 `collect.py` 的跳过处**同时从 `.cpp` 输入中移除**（当前只 `continue`，不进 `store`，但 `.cpp` 用别的来源）|
| **3** | 确认 `CEffShock` 为何不受影响（找出那个"别的来源"的差别）|

## 4. 诚实标注

- 我**未**定位到"剥离函数头"的确切代码行（但已缩小到 `emit_cpp.py:349-411` 区间与 `collect.py:193-198` 的不一致）。
- 我**未**验证另 4 个文件（`UICamera`/`JusticeBookUI`/`UITitle_BBTY`/`scScriptInstance`）是否同因。
- 本轮**两次自我更正**（先说"头丢失"、再说"注解造成"）——两次都被自己的实测推翻。

## 5. 本轮仍然获得的**可靠结论**

| 结论 | 证据 |
|---|---|
| `UIStatic.cpp` 因 `_scalar_dtor` 的孤立体而编译失败（6 错） | 逐行 + 编译实测 |
| **不是**函数头丢失 | 逐行核实 |
| **不是** transform 造成 | 5 阶段离线复现（头存活）|
| **不是**注解造成 | 移除注解 + 重跑 export + codegen ⇒ 产物不变 |
| 与 `collect.py:193-198` 的"跳过"意图**不一致** | 源码 + 产物对照 |
| `CEffShock` 不受影响 | `grep -c _scalar_dtor CEffShock.cpp` = 0 |
