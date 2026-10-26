# PAL3 Decompilation Project

**仙剑奇侠传 3 匹配反编译项目** —— 生成与原始二进制字节相同的 C/C++ 源码。

> **字节匹配 > 代码优雅 > 工具链便利 > 个人偏好**（核心原则）

## 项目目标

**字节一致反编译** MSVC 6.0 SP0 编译的 `PAL3.exe`：

```
annotations → apply → IDB → Hex-Rays → decomp JSON → codegen → C++ → 字节比对
↑________________________ Phase 1（自动化）________________________↑
                                                    ↕ 字节比对
                                    Phase 2（手工 fix）
```

**L1（字节全同）** 是唯一真相源（三限定：截断 + 长度相等 + 重定位 4 字节 don't-care）

## 当前状态（2026-10-26）

| 指标 | 值 | 判 |
|---|---|---|
| **check** | **0 errors** | 🟢 PASS |
| **S2**（编译通过）| **123/214**（57%）| 🟡 |
| **L1**（字节全同）| **17.2%**（三限定）| 🔴 |
| **字节覆盖** | **87.50%** | 🟢 |
| **签名覆盖** | **94.37%** | 🟢 |
| **测试** | 865 passed · 1 failed | 🟡 |

## 项目结构

```
PAL3Decomp/
├── data/
│   ├── annotations/        # 类布局/函数签名/全局变量（真相源）
│   │   ├── structs/*.json  # 类定义（成员/偏移/类型/vtable）
│   │   ├── functions.json  # 函数签名
│   │   └── globals.json    # 全局变量
│   └── status/             # 状态/基线/报告
├── pipeline/
│   ├── cli.py              # 管线入口（check/apply/export/codegen/probe/match）
│   ├── ida/                # IDA 层（apply_annotations/export_full）
│   ├── gen/                # codegen 层（emit_headers/emit_cpp/ast_transform）
│   └── compare_pal3.py     # L1 字节比对
├── pal3/src/               # 生成的 C++ 源码（214 .cpp）
├── asm/pal3/               # IDA 导出（ida_structs.json/decomp/*.json）
├── tools/                  # 工具集（109 个）
├── tests/                  # 测试（865 passed）
├── docs/
│   ├── knowledge/          # 知识库（109 个：gotcha/arch/debug/rule）
│   └── specs/              # 规格文档
└── original/               # 原始二进制（PAL3.exe）
```

## 管线架构

### 阶段 + 耗时

| 阶段 | 命令 | 耗时 | 说明 |
|---|---|---|---|
| **check** | `python pipeline/cli.py check` | 2.3s | 秒级闸（不进 IDB）|
| **apply** | `python pipeline/cli.py apply` | 11.3s | annotations → IDB |
| **export** | `python pipeline/cli.py export` | 150.9s | IDB → decomp JSON |
| **codegen** | `python pipeline/cli.py codegen all` | 199.5s | decomp → C++ |
| **probe** | `python pipeline/cli.py probe s2` | varies | 编译普查 |
| **match** | `python pipeline/cli.py match` | varies | L1 字节比对 |

### 数据流（红线）

```
annotation → apply → IDB → export → ida_structs.json → codegen → C++
                                          ↑
                                    唯一数据源（codegen 只读这里）
```

**禁止跨层读取**：
- ✅ codegen 只读 `ida_structs.json`（IDB 导出）
- ❌ codegen **不能读 annotation**（跨层）
- ❌ export **不能读 annotation**（跨层）

## 快速开始

### 环境要求

- Python 3.10+
- MSVC 6.0 SP0（`tools/compilers/msvc6.0/`）
- wine（Linux 上跑 MSVC 6.0）
- IDA Pro（`original/PAL3.exe.i64`）

### 一键循环

```bash
# 完整迭代（含基线断言）
python pipeline/cli.py loop --expect-s2 123/214 --expect-errors 1273 --expect-l1 184

# 分阶段
python pipeline/cli.py check      # 秒级闸
python pipeline/cli.py apply      # 注解 → IDB
python pipeline/cli.py export     # IDB → decomp
python pipeline/cli.py codegen all # decomp → C++
python pipeline/cli.py probe s2   # 编译普查
python pipeline/cli.py match      # L1 字节比对
```

### 测试

```bash
# 全量测试
python -m pytest tests/ -q

# 增量检查（hash+timestamp）
python3 tools/check_incremental.py

# 双源 diff 报表
python3 tools/dual_source_diff.py
```

## 核心概念

### 证据模型（A 级 vs B 级）

| 级 | 证据 | 判 |
|---|---|---|
| **A 级** | 指令字节（`ret N` / `push` / `mov` opcode）| ✅ 非循环 |
| **B 级** | IDA 修饰名 / stack_frame / decomp | ❌ **循环论证**（我们注入的）|

**⚠️ IDA 签名是循环论证**（`apply_annotations set_name+SetType` 写进 IDB）

### L1 三限定

```
① 截断：编译产物先截到原函数长度再比
② 长度相等：截断后两侧长度必须相等
③ 重定位 4 字节 don't-care：覆盖的字节即使不同也计 match
```

### 度量指标

| 指标 | 公式 | 当前值 |
|---|---|---|
| **字节覆盖** | 已标注字节 / binary_size | 87.50% |
| **签名覆盖** | 两注册表并集 / decomp 全量 | 94.37% |
| **S2** | 编译通过单元 | 123/214 |
| **L1** | 字节全同函数数（三限定）| 17.2% |

## 知识库

`docs/knowledge/`（109 个）：
- **gotcha**（77 个）：教训沉淀
- **arch**（2 个）：架构理解
- **debug**（2 个）：调试方法
- **rule**（2 个）：规则纪律

**引用前必须验证文件/字段仍存在**（见该目录 README）

## 工具集

| 工具 | 用途 |
|---|---|
| `check_annotations` | 注解一致性 |
| `error_classifier` | 错误分类 |
| `audit_type_layout` | 布局审计（编译器裁判）|
| `member_usage_scan` | 成员全用法形 |
| `check_incremental` | 增量检查 |
| `dual_source_diff` | 双源 diff 报表 |
| `run_pipeline_incremental` | 增量管线执行 |

## 强制检查点

| 时机 | 工具 | 命令 |
|---|---|---|
| **动手改任何东西之前** | 病灶层检查 | 见 CLAUDE.md |
| **一轮完整迭代** | 一键循环 + 基线断言 | `python pipeline/cli.py loop` |
| **codegen all 后** | 编译回归检测 | `python tools/compile_regression.py` |
| **probe 后** | 错误分类 | `python tools/error_classifier.py --summary` |
| **probe 后** | 字节匹配裁判 | `python pipeline/cli.py match` |
| **修改 struct 后** | 布局验证 | `python tools/audit_type_layout.py` |
| **任何修复提交前** | 证物报告 | `python tools/verify_fix.py` |

## 核心困难

1. **CRT 边界**：哪些函数是 CRT 的、哪些是游戏自带的？
2. **vtable 布局**：虚函数声明顺序、COMDAT 折叠、调整 thunk
3. **模板特化**：Hex-Rays 不支持模板，`template_bases.json` 做桥接
4. **优化反编译产物**：Hex-Rays 反编译「看起来对但字节不对」
5. **L1 三限定**：字节全同 ≠ 全字节相同（度量盲区）

## 项目约束

- **每一处 annotation 修改必须有二进制直接证据**（A 级）
- **禁止猜测性修改**（无证据不改偏移/类型/签名）
- **禁止批量修改未验证字段**（逐一验证）
- **禁止伪语义命名**（`m_nState_4968` 类）
- **禁止仅凭 Hex-Rays 反编译推断偏移**
- **禁止仅凭 signature-this 判归属**

## 相关文档

- **架构**：`docs/knowledge/arch_pipeline_overview.md`
- **调试**：`docs/knowledge/debug_common_diagnosis.md`
- **改型纪律**：`docs/knowledge/method_function_signature_inference.md`
- **证据分级**：`docs/knowledge/rule_evidence_tiering_no_unobtainable_gate.md`
- **度量盲区**：`CLAUDE.md`「字节全同 ≠ 全字节相同」
