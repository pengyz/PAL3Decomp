# 前向声明机制分析

## free_functions.h 生成逻辑

生成点在 `pipeline/gen/stages/emit_cpp.py` 的 `run_cpp_generation`，**同一文件有双写点**（dual-copy 分叉风险）：

1. **预生成**（`emit_cpp.py:779-796`）：写 `#pragma once` + `free_func_sigs` 声明，**无任何前向声明**（供 .cpp include 检查用；射程模式 `EXPORT_FUNC` 等跳过重写，保留全量版）。
2. **全量生成**（`emit_cpp.py:825-855`）：在声明前补类型前向声明——正则 `\b(\w+)\s*\*` 扫签名里的指针类型，剔 `_SYSTEM_TYPES` 后逐个发射 **`struct %s;`**（`emit_cpp.py:848`，硬编码 `struct` 关键字）。`struct CCBStage;` 即此产出：签名 `InitRound(CCBStage *_this, ...)` 命中正则。

## CCBStage.h 生成逻辑

`pipeline/gen/stages/emit_headers.py` 生成类头。顶层游戏类型定义**一律硬编码 `class`**（`emit_headers.py:2143-2155`：`lines.append('class %s%s {' % ...)`，无任何数据驱动的 class/struct 分派）⇒ 产出 `class CCBStage {`。全树 776 个头是 `^class` 定义；仅 `_inline_*` overlay 员用 `struct`（`_ns_udts.h`，是内联 UDT 块，与本议题无关）。

## class/struct 决定源头

**无规则、无随机——是两处硬编码关键字不一致**。全管线 9 处前向声明发射点：

| 位置 | 关键字 |
|---|---|
| `emit_cpp.py:267` · `emit_headers.py:128/1812/1996/2122/3540/4101` | `class %s;` |
| **`emit_cpp.py:848`（free_functions.h）** | **`struct %s;`** ← 唯一异类 |

定义侧恒 `class` + 8 处前向声明恒 `class` ⇒ 一致解就是全用 `class`；`struct` 是 free_functions.h 发射点的历史笔误级分叉。IDA 侧无 class_key 信息（IDB 全是 struct），annotation 也无此字段 ⇒ struct 无任何数据来源。

**危害面**：`free_functions.cpp:23` 同 TU include `Combat/CCBStage.h` ⇒ `struct CCBStage;` 与 `class CCBStage {` 类键冲突。MSVC6 对 class/struct 键不一致敏感（本仓自证：`emit_headers.py:1807` 注释"MSVC6 不允许同名 class/struct 前向声明与嵌套定义混用 ⇒ C2143 ×213 文件"，2026-10-19 C2143 修实证）。

## 修复方案

**最小修（1 行）**：`pipeline/gen/stages/emit_cpp.py:848`

```python
-            h_lines.append('struct %s;' % t)
+            h_lines.append('class %s;' % t)   # 与定义侧 class 及其余 8 处发射点一致
```

**结构修（推荐，防复发）**：
1. 收敛为单一发射函数 `fwd_decl(name) -> 'class %s;' % name`（放 `pipeline/gen/annotation_view.py` 或新 `pipeline/gen/class_key.py`），替换全部 9 处调用点——同型双副本分叉坑见 `docs/knowledge/gotcha_dual_copy_table_divergence.md`。
2. 合并 free_functions.h 双写点为一个 `_emit_free_functions_header()`，预生成/全量共用（现状：中断于两写点之间会留下**缺前向声明**的版本）。
3. 回归验证：`codegen all` 后 diff 产物应仅 `free_functions.h` 的 `struct→class` 变化；跑 `probe` + `match` 确认 L1 不降、`free_functions.cpp` 错误不增。
