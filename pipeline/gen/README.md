# Codegen Pipeline

从 IDA Hex-Rays 反编译 JSON 生成 MSVC 6.0 兼容的 C++ 源码。

## 架构

```
codegen.py                入口（子命令: headers / cpp / all）
data.py                   DataStore 单例（一次性加载 annotations + binary）
ast_transform.py          tree-sitter OOP 调用变换（Stage 2 核心）
stages/
  transform.py            4-stage pipeline runner
  stage1_structural.py    函数签名修改（AST: function_definition 节点）
  stage2_semantic.py      OOP 调用变换（AST: call_expression 遍历）
  stage3_cleanup.py       IDA 无效代码清理（AST: vftable/ctor 节点检测）
  stage4_substitution.py  token 替换（AST: identifier/type_identifier 遍历）
  collect.py              从 decomp JSON 收集函数，按类分组
  emit_cpp.py             生成 src/pal3/**/*.cpp
  emit_headers.py         生成 include/pal3/gen/*.h
```

## 用法

```bash
python pipeline/gen/codegen.py all              # headers + cpp
python pipeline/gen/codegen.py headers          # 只生成 .h
python pipeline/gen/codegen.py cpp              # 只生成 .cpp
python pipeline/gen/codegen.py cpp ClassName    # 只生成特定类
```

## 4-Stage Transform Pipeline

代码变换分为 4 个确定性阶段，依次执行：

```
decomp JSON 原始代码
  │
  ├─ Stage 1 (structural)    函数签名修改，不看 body
  │   AST: function_definition → 删除 ms_call_modifier, this 参数
  │
  ├─ Stage 2 (semantic)      OOP 调用重写（唯一产生新模式的阶段）
  │   AST: Class::Method(obj,...) → obj->Method(...)
  │
  ├─ Stage 3 (cleanup)       清理 Stage 2 产生的 IDA 残留
  │   AST: vftable 赋值/调用、显式 ctor/dtor 检测
  │
  └─ Stage 4 (substitution)  token 级替换，无上下文依赖
      AST: identifier → 名称解析, type_identifier → 类型修复
```

**关键约束**：Stage 2 产生新的 `->ClassName()` 和 `->__vftable->` 模式，Stage 3 必须在 Stage 2 之后才能处理它们。Stage 4 与前 3 个 stage 无交互。

## tree-sitter 集成

所有结构判断通过 AST node type 完成，不依赖 regex pattern matching：

- `_is_vftable_field(node)` — `field_expression.field == "__vftable"`
- `_is_vftable_call(node)` — call 函数子树含 __vftable
- `_get_ctor_call_info(node)` — cast_type == method_name 判定 ctor
- `_extract_cast_type(node)` — 穿透 parenthesized/binary/cast 层
- `_collect_token_edits(tree)` — 单次遍历收集 identifier 替换

## 添加新的 Hex-Rays 修复

1. **确定属于哪个 Stage**：
   - 改函数签名 → Stage 1
   - 需要 OOP 变换后的模式 → Stage 3
   - 纯 token 替换 → Stage 4

2. **在对应 stage 文件中添加逻辑**：
   - 优先用 AST node type 检测（`node.type == 'call_expression'`）
   - 简单文本替换（`code.replace('A', 'B')`）可直接使用

3. **验证**：编译结果不回归

## DataStore

`data.py` 在 codegen 启动时一次性加载所有资源：

- `store.literals` — .rdata float/string 常量
- `store.thunks` — thunk 函数名映射
- `store.globals_map` — IDA 默认名 → 标注名
- `store.struct_instances` — 全局结构体实例范围
- `store.struct_members` — 结构体成员偏移 → (名称, 类型)
- `store.game_classes` — 有 .h 文件的类名集合
- `store.static_methods` — __cdecl 类方法集合

Transform 通过 `from data import store` 访问，不传 ctx。
