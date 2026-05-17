# Codegen AST Migration Spec

## Problem

当前 26 个 transform 通过 `@register(order=N)` 编排，但它们不是独立纯函数——上游 transform 的输出格式决定下游 regex 是否匹配。这导致：
- order 依赖隐式脆弱（vftable 注释必须在 OOP 之后）
- 80+ 文件与旧 pipeline 输出不一致
- 新增 fix 容易破坏已有 transform 的 regex 匹配前提

## Solution: 两步迁移

### Step 1: 聚合为 4 个确定性 Stage

消除 order 编排，把 26 个 transform 合并为 4 个 stage function。每个 stage 是一个文件、一个 `run(code, ctx)` 入口。Stage 内部逻辑顺序在代码中线性排列。

```
Stage 1 - structural    函数签名修改（不看 body）
Stage 2 - semantic      OOP 调用变换（tree-sitter AST，已有）
Stage 3 - cleanup       删除/注释 IDA 无效代码（依赖 Stage 2 输出）
Stage 4 - substitution  纯文本替换（无上下文依赖）
```

Pipeline runner:
```python
def run_transforms(code, ctx):
    code = stage1_structural.run(code, ctx)
    code = stage2_semantic.run(code, ctx)
    code = stage3_cleanup.run(code, ctx)
    code = stage4_substitution.run(code, ctx)
    return code
```

### Step 2: 逐 Stage 迁移到 tree-sitter AST

每个 stage 内部从 regex 切换到 AST visitor，接口 `run(code, ctx) -> str` 不变。

迁移顺序（按 ROI）：
1. Stage 3 (cleanup) — 最大收益：ctor/vftable 检测从 regex 提升到 AST node type
2. Stage 1 (structural) — 函数签名在 AST 中是确定性 node
3. Stage 4 (substitution) — 在 tree token 层做 identifier 替换
4. Stage 2 — 已是 AST，不动

## 文件结构

```
pipeline/gen/
  codegen.py
  data.py
  stages/
    transform.py            4 行 pipeline runner
    stage1_structural.py    签名修改
    stage2_semantic.py      OOP 变换（= 现有 ast_transform.py）
    stage3_cleanup.py       IDA 无效代码清理
    stage4_substitution.py  文本替换
    collect.py              函数收集
    emit_cpp.py             .cpp 文件生成
    emit_headers.py         .h 文件生成
```

删除：
- `transforms/` 目录（26 个文件）→ 合并入 4 个 stage
- 旧 `gen_cpp.py` → codegen.py 完全替代
- `@register` / auto-discovery 机制 → 不再需要

## Stage 详细设计

### stage1_structural.run(code, ctx)

操作：只修改函数定义行（第一行），不动 body。
```
1. 过滤 IDA 头部注释 (// between_std_methods)
2. 找到函数定义行
3. sub_XXXXX → ClassName::Method
4. 去除 calling convention
5. 移除 this 参数
6. ctor/dtor: 去除返回类型
7. ctor/dtor: body 中 return expr → expr (无返回值)
```

Step 2 AST 迁移：parse tree → 找 `function_definition` node → 修改 `declarator` 子树。

### stage2_semantic.run(code, ctx)

操作：OOP 调用转换 `Class::Method(obj, ...)` → `obj->Method(...)`。
已实现：`ast_transform.py`（tree-sitter）。直接复用。

### stage3_cleanup.run(code, ctx)

操作：删除/注释 Stage 2 产生的 IDA 无效代码。
```
1. 删除 backtick compiler calls（多行跳过）
2. 删除 __vftable = N 赋值
3. 注释 ->__vftable-> 虚调用
4. 注释/删除 ((Type*)expr)->Type() 显式 ctor 调用
5. 处理 return ctor → return expr
6. COERCE_FLOAT(literal) → inline float
```

Step 2 AST 迁移：parse tree → visitor 标记 ctor_call/vftable_access 节点 → 批量 edit。

### stage4_substitution.run(code, ctx)

操作：纯文本替换，无上下文依赖。
```
1. thunk 名替换
2. .rdata literal 内联
3. struct member 解析 (dword_XXX → g_Instance.member)
4. global name 替换
5. vtable type → void
6. __int8/__int16 → char/short
7. LL → i64
8. _ThrowInfo → _s__ThrowInfo
9. operator new 修复
10. LODWORD/HIDWORD address cast
11. (*)var → (*var)
12. ctor return → this
13. stdiobuf → UIWnd (free funcs)
14. this → _this (free funcs)
```

Step 2 AST 迁移：parse tree → 遍历 identifier/type node → 替换 text。

## 验证标准

- Step 1 完成后：新旧 pipeline 0 diff（MD5 逐文件对比）
- Step 2 每个 stage 迁移后：仍保持 0 diff
- 编译通过数不回归

## 约束

- tree-sitter-cpp 已集成（`import tree_sitter_cpp`）
- Hex-Rays 输出 0 parse error（已验证）
- 接口统一：`run(code: str, ctx: TransformContext) -> str`
- DataStore 单例提供全局数据
