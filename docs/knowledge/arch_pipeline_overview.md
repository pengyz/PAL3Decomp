# PAL3 反编译管线架构总览

**created**: 2026-10-22（知识库重构·补 arch）

## 目标

**字节匹配反编译**：MSVC 6.0 SP0 编译的 `PAL3.exe` → 生成字节一致的 C++ 源码。

**字节匹配 > 代码优雅 > 工具链便利 > 个人偏好**（CLAUDE.md 核心原则）。

## 两阶段管线

```
Phase 1（自动化）：
  annotations → apply_annotations → IDB → Hex-Rays → decomp JSON → codegen → C++
      ↑__________________________ Phase 1 ____________________________↑
                                                        ↕ 字节比对
Phase 2（手工）：
  字节比对定位不匹配 → 手工 fix → phase2/overlay → apply
```

## Phase 1 各层职责（红线）

| 层 | 职责 | 红线 |
|---|---|---|
| **annotation** | 为 IDA 提供类型信息（结构体/签名/全局）| 不能直接改 codegen 产物 |
| **apply_annotations** | 将 annotation 写入 IDB | 不能编造信息 |
| **Hex-Rays** | 基于 IDB 类型生成伪代码 | 能力有限（无引用/模板）|
| **codegen** | 伪代码 → 可编译 C++ | 只能等价变换 |
| **check_annotations** | 验证 annotation 一致性 | 不查 codegen 风格 |

## 数据流

```
data/annotations/
  ├── structs/*.json       ← 类布局（成员/偏移/类型/vtable）
  ├── functions.json       ← 函数签名（自由函数 + 方法）
  ├── globals.json         ← 全局变量
  └── skip_functions.json  ← 跳过的 CRT/库函数
        ↓
  pipeline/ida/apply_annotations.py  → work IDB
        ↓
  pipeline/ida/export_full.py        → asm/pal3/decomp/*.json（Hex-Rays 伪代码）
        ↓
  pipeline/gen/codegen.py
    ├── stages/emit_headers.py       → pal3/src/**/*.h（类声明）
    ├── stages/emit_cpp.py           → pal3/src/**/*.cpp（函数实现）
    ├── stages/stage1-5*.py          → 后处理（类型传播/清理/替换/修复）
    └── stages/collect.py            → 聚合（free_functions.h）
        ↓
  pipeline/cli.py probe s2           → S2 编译普查
  pipeline/cli.py match              → L1 字节比对
```

## 阶段耗时（实测）

| 阶段 | 耗时 | 瓶颈 |
|---|---|---|
| `check` | 2.3s | 秒级闸（不进 IDB）|
| `apply` | 11.3s | — |
| **`export`** | **150.9s** | **Hex-Rays 反编译**（3038 函数 ≈ 50ms/函数）|
| **`codegen`** | **199.5s** | **emit_headers 78s + emit_cpp 45s + ast_transform 60s** |
| `probe` | varies | 编译普查 |
| `match` | varies | L1 字节比对 |
| **总** | **~360s** | |

## 核心类型（data/annotations/structs/*.json）

```json
{
  "name": "ClassName",
  "binary_size": 820,
  "bases": [{"name": "BaseClass", "offset": 0}],
  "known_members": {
    "0": {"name": "m_field", "type": "int", "source": "...", "evidence_level": "A"},
    ...
  },
  "methods": {
    "0x401000": {"name": "MethodName", "signature": "int __thiscall(Cls *this, int a)", "source": "..."}
  },
  "vtables": ["0x56AAC4"]
}
```

## 关键机制

### 1. vptr 处理（F59/F62/F63 演化）

**问题**：注解在 +0 标「真实成员」，但 MSVC 为虚函数类隐式加 vptr ⇒ 成员被推到 +4，下游全偏。

**F59 解法**：把 +0 成员改成 `static`（不占字节）⇒ 编译器隐式 vptr 独占 +0 ⇒ 偏移归位。

**F63 修法**：改写 static 后删冗余 gap（`_gap_001[3]`）⇒ `sizeof` 从 824 归 820。

### 2. gap 记账（单一记账 + 补白提顶）

循环顶部统一补白（任何分支前）⇒ 三类分支不绕过 ✓
不丢成员（`off < start_off` 只告警）✓

### 3. union/struct 内联（位面复用）

```json
"offset": {
  "name": "field_name",
  "type": {"union": [
    {"type": "int", "name": "variant1"},
    {"type": "float", "name": "variant2"}
  ]}
}
```
**union 本身即 overlap 声明**（CLAUDE.md 三判据：值位面/取址/重解释）。

## 证据模型（2026-10-21 定谳）

**A 级（非循环·指令字节）**：`ret N` · 调用点 `push` · `fld/fstp/mov` opcode · 访问形 · 值位型常量 · vtable 槽 · IDA 函数边界/xref

**B 级（循环·我们写入）**：IDA 修饰名 · IDA `stack_frame` 参数名/型 · IDA/decomp 反编译

**⚠️ IDA 签名是循环论证**（`apply_annotations set_name+SetType` 写进 IDB）

## 度量指标

| 指标 | 公式 | 当前值 |
|---|---|---|
| **字节覆盖** | 已标注字节 / binary_size | **87.50%** |
| **签名覆盖** | 两注册表并集 / decomp 全量 | **94.37%** |
| **弱型率** | 数值基元成员 / 总成员 | 57.37% |
| **S2** | 编译通过单元 | **120/214** |
| **L1** | 字节全同函数数（三限定）| **110/640 = 17.2%** |

## 关联文档

- **改型纪律**：[method_function_signature_inference.md](method_function_signature_inference.md)
- **证据分级**：[rule_evidence_tiering_no_unobtainable_gate.md](rule_evidence_tiering_no_unobtainable_gate.md)
- **落盘前 checklist**：[rule_pre_commit_evidence_checklist.md](rule_pre_commit_evidence_checklist.md)
- **设计意图**：[gotcha_read_design_intent_before_patching.md](gotcha_read_design_intent_before_patching.md)
