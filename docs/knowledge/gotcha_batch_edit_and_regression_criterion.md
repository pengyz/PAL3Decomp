# 批量代码改动的静默失败 + 回归判据须 diff 生成物（2026-10-20）

**created**: 2026-10-20（真相源迁移实证，两条同源教训）

---

## 教训一：批量插入 import 会静默失败（放进了 docstring）

**实证**：真相源迁移时用脚本给 5 个文件插
`from annotation_view import base_names as _base_names`：
```python
s.replace('\n', '\n' + IMP + '\n', 1)   # ← 插在"第一个换行后"
```
结果插进了 **`data.py` 的模块 docstring 内部**（`"""Global data store...\nfrom annotation_view ...\n"""`）
⇒ import 成了字符串字面量、**从不执行** ⇒ 运行时 `NameError: name '_base_names' is not defined`。

**关键特征：静默** —— `py_compile` 全过、语法合法、只是名字未绑定。
要不是全链跑出 NameError，这会以"改了但没生效"的形式潜伏。

**防复发**：
1. 批量插 import **必须锚定在首个顶层 `import `/`from ` 行前**，或 docstring **配对结束之后**
2. 插入后必须**实测绑定**：`python3 -c "import <module>; hasattr(mod,'<name>')"`
3. `py_compile` 通过 ≠ 名字可用（它只查语法，不查绑定）

---

## 教训二：回归判据必须 **diff 生成物**，不能只看错误计数

**实证**：真相源迁移后编译错误 **1289 → 1314（+25）**，正式回归工具判"真新增 29 条"。
逐改动隔离、可重复性测试都做了，仍未定谳 —— 直到做了**生成源 A/B diff**：

```bash
cp pal3/src/Misc/CCBUIPanel.cpp /tmp/after_...
git stash push -- pipeline/gen/ data/annotations/ ...   # A 侧
... codegen ...
cp pal3/src/Misc/CCBUIPanel.cpp /tmp/before_...
diff /tmp/before_... /tmp/after_...
# ⇒ **空**（完全一致）
```

**生成物完全相同** ⇒ +25 不是"数据回退"，而是**头文件/继承修正后同一 .cpp 的
编译报告变化**（更好类型信息 ⇒ 原被遮蔽的错误浮出，C1003 型遮蔽释放）。

**为什么错误计数不可靠**：编译错误受**遮蔽**影响（早错挡住后错）。修掉早错、
或改进类型信息，都会让原本不报的错误冒出来 —— 计数涨 ≠ 数据劣化。

**「数据不回退」的正确判据**（优先级从高到低）：
1. **生成物 diff**（.h/.cpp 逐字节比对）—— 最直接
2. **指标**（annotation_completeness / codegen_invariant_lint）
3. **S2 不降**（单元数）
4. **编译错误计数** —— 最弱，须结合遮蔽分析

⇒ 判据选择：**度量「产物」而非度量「症状」**。

---

## 关联

- 双副本分叉（本迁移消除 `base_class`/`bases`）：
  [gotcha_dual_copy_table_divergence.md](gotcha_dual_copy_table_divergence.md) 实例三
- 产出集/清理判据：[gotcha_codegen_output_set_derivation.md](gotcha_codegen_output_set_derivation.md)
- C1003 遮蔽现象：CLAUDE.md「度量盲区：C1003 截断单元」
