# PAL3 Decompilation Project

**仙剑奇侠传 3 匹配反编译项目** —— 生成与原始二进制字节相同的 C/C++ 源码。

> **字节匹配 > 代码优雅 > 工具链便利 > 个人偏好**（核心原则）

---

## 项目概览

本项目对 **仙剑奇侠传 3（PAL3）** 进行**字节匹配反编译**，目标是生成能编译出**与原始二进制字节完全相同**的 C/C++ 源码。

### 两个核心目标

| 目标 | 二进制 | 方法 | 状态 |
|---|---|---|---|
| **PAL3.exe** | 游戏主程序 | **反编译管线**（自动化）| 🟡 进行中（L1 17.2%）|
| **gbengine.dll** | 游戏引擎 | **手写匹配**（人工）| 🟡 进行中（不完整）|

### 项目性质

**不是「还原源码」**，而是**「再创作」**：
- C++ 编译成二进制是**不可逆的信息丢失**过程
- 类型、类层次、继承、模板实例化全部坍缩为指令和数据
- 我们做的是**再创作一个能输出完全相同二进制的 C++ 程序**

---

## PAL3.exe（核心目标）

**MSVC 6.0 SP0 编译**（`/O2 /Ob2 /Oi /Ot /Oy`）的游戏主程序。

### 反编译管线

```
annotations → apply → IDB → Hex-Rays → decomp JSON → codegen → C++ → 字节比对
↑________________________ Phase 1（自动化）________________________↑
                                                    ↕ 字节比对
                                    Phase 2（手工 fix）
```

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

### 当前状态（2026-10-26）

| 指标 | 值 | 判 |
|---|---|---|
| **check** | **0 errors** | 🟢 PASS |
| **S2**（编译通过）| **123/214**（57%）| 🟡 |
| **L1**（字节全同）| **17.2%**（三限定）| 🔴 |
| **字节覆盖** | **87.50%** | 🟢 |
| **签名覆盖** | **94.37%** | 🟢 |
| **测试** | 865 passed · 1 failed | 🟡 |

---

## gbengine.dll（手写匹配）

**MSVC 6.0 SP5 编译**的游戏引擎核心（数学库/渲染/音频/脚本）。

### 方法：手写匹配

**不走反编译管线**，而是**人工逐函数匹配**：
1. IDA 反汇编获取函数
2. 人工理解语义
3. 手写 C++ 实现
4. 编译 + 字节比对验证

### 当前状态（不完整）

| 项 | 状态 |
|---|---|
| **函数数** | ~1020 导出 |
| **已实现** | 部分（56 .cpp，17553 行）|
| **匹配率** | 27%（topo.dll）|
| **编译** | ✅ 全部编译通过 |

### 数学库（topo.dll）

**VC6 SP5 编译**（~414 函数）：
- `gbVec3D` / `gbMatrix4` / `gbQuaternion` / `gbPlane` 等
- 7 文件，2885 行
- 27% 匹配

---

## 项目结构

```
PAL3Decomp/
├── data/
│   ├── annotations/          # 类布局/函数签名/全局变量（真相源）
│   │   ├── structs/*.json    # 类定义（成员/偏移/类型/vtable）
│   │   ├── functions.json    # 函数签名
│   │   └── globals.json      # 全局变量
│   └── status/               # 状态/基线/报告
│
├── pipeline/                 # PAL3.exe 反编译管线
│   ├── cli.py                # 管线入口（check/apply/export/codegen/probe/match）
│   ├── check_annotations.py  # 注解一致性检查
│   ├── compare_pal3.py       # L1 字节比对
│   ├── ida/                  # IDA 层（apply_annotations/export_full）
│   └── gen/                  # codegen 层（emit_headers/emit_cpp/ast_transform）
│
├── pal3/                     # PAL3.exe 生成的 C++ 源码
│   ├── src/                  # 212 .cpp + 头文件
│   └── CMakeLists.txt        # 构建配置
│
├── gbengine/                 # gbengine.dll 手写匹配
│   ├── src/                  # 手写 C++ 实现
│   ├── gbengine.def          # 导出定义
│   └── CMakeLists.txt        # 构建配置
│
├── asm/
│   └── pal3/                 # IDA 导出（ida_structs.json/decomp/*.json）
│
├── tools/                    # 工具集（109 个）
│   ├── compilers/msvc6.0/    # MSVC 6.0 SP0 工具链
│   ├── check_*.py            # 检查工具
│   ├── audit_*.py            # 审计工具
│   └── analyze_*.py          # 分析工具
│
├── tests/                    # 测试（865 passed）
├── docs/
│   ├── knowledge/            # 知识库（109 个：gotcha/arch/debug/rule）
│   └── specs/                # 规格文档
│
├── cmake/                    # CMake 构建配置（VC6 toolchain）
├── original/                 # 原始二进制（PAL3.exe + IDB）
├── phase2/                   # Phase 2 手工 fix 留存
└── extra/PAL3patch/          # 社区补丁（submodule）
```

---

## 构建

### PAL3.exe（MSVC 6.0 SP0）

```bash
# 完整迭代（含基线断言）
python pipeline/cli.py loop --expect-s2 123/214 --expect-errors 1273 --expect-l1 184

# 分阶段
python pipeline/cli.py check      # 秒级闸（2.3s）
python pipeline/cli.py apply      # 注解 → IDB（11.3s）
python pipeline/cli.py export     # IDB → decomp（150.9s）
python pipeline/cli.py codegen all # decomp → C++（199.5s）
python pipeline/cli.py probe s2   # 编译普查
python pipeline/cli.py match      # L1 字节比对
```

### gbengine.dll（MSVC 6.0 SP5）

```bash
# 单文件编译验证
python tools/gbengine_compare.py --compile gbengine/src/gbCamera.cpp

# 字节比对
python tools/gbengine_compare.py --func gbCamera::SetLookAt
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

---

## AI First 开发模式

本项目采用 **AI First** 开发模式：AI 是主要开发者，人类负责协调、审查、决策。

### 多级闸门（Gates）

| 闸门 | 时机 | 工具 | 失败处理 |
|---|---|---|---|
| **L1 门禁** | 提交前 | `pipeline/cli.py check` | 0 errors 才可提交 |
| **L2 秒级闸** | 动手前 | `check_annotation_preflight.py` | 0.108s 快速失败 |
| **L3 编译闸** | codegen 后 | `compile_regression.py` | 发现退化立即报警 |
| **L4 错误分类** | probe 后 | `error_classifier.py` | 指导修复方向 |
| **L5 字节匹配** | match 后 | `pipeline/cli.py match` | L1 不得回退 |
| **L6 布局验证** | 改 struct 后 | `audit_type_layout.py` | 编译器裁判 |
| **L7 证物报告** | 修复提交前 | `verify_fix.py` | 有问题不提交 |

### 提示词系统（Prompts）

**分层提示词**：
- **CLAUDE.md**：项目强约束（红线/纪律/检查点）
- **docs/knowledge/**：知识库（109 个：gotcha/arch/debug/rule）
- **docs/specs/**：规格文档（设计/方案/计划）
- **skills/**：技能路由（pal3-pipeline/annotation-audit）

**提示词优先级**：
```
用户直接指令 > CLAUDE.md 约束 > skill 指引 > 通用规则
```

### 对抗性复核（Adversarial Review）

**每步修复必须过对抗复核**：
1. **出方案**（修复方案）
2. **对抗复核**（子 agent 独立验证）
3. **修复**（按方案）
4. **再复核**（验证效果）
5. **提交**（commit + push）

**复核要求**：
- **独立验证**（非自我确认）
- **A 级证据**（指令字节，非 IDA 签名）
- **同树 A/B**（非跨树对比）
- **当场读输出**（非事后查基线）

### TDD 纪律

**测试先行**：
```python
# 1. 写失败测试
def test_xxx():
    assert function(input) == expected

# 2. 跑失败
pytest tests/test_xxx.py -v  # FAIL

# 3. 实现
def function(input): ...

# 4. 跑通过
pytest tests/test_xxx.py -v  # PASS

# 5. 提交
git commit -m "feat: add xxx"
```

**测试要求**：
- **判别力**（M2/M3 变异体须 FAIL）
- **真实测试**（非 stub `assert True`）
- **UT 接近 0 成本**（禁 sleep/编译/I/O）

---

## 如何贡献

### 贡献流程

```
1. 理解约束（读 CLAUDE.md + docs/knowledge/）
2. 选任务（P0 阻塞 > bug 修复 > 新功能）
3. 出方案（修复方案 + 影响面）
4. 对抗复核（子 agent 独立验证）
5. TDD 实现（测试先行）
6. 过闸门（L1-L7）
7. 提交（commit + push）
```

### 贡献类型

| 类型 | 要求 | 优先 |
|---|---|---|
| **annotation 修正** | A 级证据（objdump 指令字节）| 高 |
| **bug 修复** | TDD + 对抗复核 | 高 |
| **新功能** | 设计文档 + 测试 | 中 |
| **文档更新** | 反映当前状态 | 中 |
| **工具改进** | TDD + 判别力 | 中 |

### 贡献红线（必须遵守）

| 红线 | 说明 |
|---|---|
| **A 级证据** | 每处 annotation 修改必须有二进制直接证据 |
| **禁猜测** | 无证据不改偏移/类型/签名 |
| **禁批量** | 禁止批量修改未验证字段 |
| **禁伪语义命名** | `m_nState_4968` 类名字 |
| **禁跨层读取** | codegen 不能读 annotation |
| **禁 IDB 手改** | 必须走 annotation apply 流 |

### 提交规范

```bash
# commit message 格式
<type>(<scope>): <subject>

# type: feat/fix/docs/test/refactor
# scope: annotations/pipeline/tools/tests/docs
# subject: 简短描述

# 例
fix(annotations): CCBStage 数组 size 修正（IDA 驱动）
test(incremental): 增量正确性 golden hash
docs(readme): 完全重构 README
```

### 提交前检查

```bash
# 1. 过闸门
python pipeline/cli.py check        # L1 门禁
python tools/compile_regression.py  # L3 编译闸
python pipeline/cli.py match        # L5 字节匹配

# 2. 跑测试
python -m pytest tests/ -q

# 3. 证物报告
python tools/verify_fix.py --class <Cls>

# 4. 提交
git add .
git commit -m "fix(annotations): xxx"
git push origin master
```

### 代码风格

- **Python 3.10+**（类型注解）
- **C++ MSVC 6.0 兼容**（禁现代语法）
- **注释解释「为什么」**（非「做什么」）
- **实测数字写进注释**（例：`C2227 −41 / C2039 +22`）

---

---

## ⚠️ IDA Pro 依赖说明

**IDA Pro 是商业反编译器**，开发者须**自行获取 license** 才能跑完整流程。

**本项目高度依赖 IDA 的 Hex-Rays 插件**生成 C++ 伪代码（`asm/pal3/decomp/*.json`）。

| 项 | 要求 |
|---|---|
| **软件** | IDA Pro（商业，需 license）|
| **插件** | **Hex-Rays**（必需，生成 C++ 伪代码）|
| **版本** | **9.x**（推荐，已测试）|
| **其他版本** | ⚠️ **未测试**（可能不兼容）|

### 为什么高度依赖 Hex-Rays

- `export_full.py` 从 IDB 导出 `ida_structs.json`（结构体/签名/全局）
- `asm/pal3/decomp/*.json` 是 Hex-Rays 生成的 C++ 伪代码（3038 函数）
- **codegen 层**将伪代码转换为可编译 C++（修补 Hex-Rays 不支持的语法）

### 无 IDA 时的替代

- 降级用 objdump 自建索引（同源同效）
- 但**丢失 Hex-Rays 伪代码**（codegen 无法工作）
- **恢复后须用 IDA 交叉复核关键结论**

### 版本兼容性

- ✅ **9.x**（已测试，推荐）
- ⚠️ **其他版本**（未测试，可能不兼容）
- **建议**：开发者使用 9.x 以确保一致性

### 获取 IDA

- 官方：https://hex-rays.com/ida-pro/
- 教育/商业 license 请自行申请
- **本项目不提供 IDA 或 license**

---

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

**度量盲区**：L1 182 例里 179 例编译字节长于原函数（合计 1903 尾字节 NOP）
**隐藏差异**：L1 字节的 19.24% / 重定位字节的 69.6%

### 度量指标

| 指标 | 公式 | 当前值 |
|---|---|---|
| **字节覆盖** | 已标注字节 / binary_size | 87.50% |
| **签名覆盖** | 两注册表并集 / decomp 全量 | 94.37% |
| **S2** | 编译通过单元 | 123/214 |
| **L1** | 字节全同函数数（三限定）| 17.2% |

---

## 知识库

`docs/knowledge/`（109 个）：
- **gotcha**（77 个）：教训沉淀
- **arch**（2 个）：架构理解
- **debug**（2 个）：调试方法
- **rule**（2 个）：规则纪律

**引用前必须验证文件/字段仍存在**（见该目录 README）

---

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

---

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

---

## 核心困难

1. **CRT 边界**：哪些函数是 CRT 的、哪些是游戏自带的？
2. **vtable 布局**：虚函数声明顺序、COMDAT 折叠、调整 thunk
3. **模板特化**：Hex-Rays 不支持模板，`template_bases.json` 做桥接
4. **优化反编译产物**：Hex-Rays 反编译「看起来对但字节不对」
5. **L1 三限定**：字节全同 ≠ 全字节相同（度量盲区）

---

## 项目约束

- **每一处 annotation 修改必须有二进制直接证据**（A 级）
- **禁止猜测性修改**（无证据不改偏移/类型/签名）
- **禁止批量修改未验证字段**（逐一验证）
- **禁止伪语义命名**（`m_nState_4968` 类）
- **禁止仅凭 Hex-Rays 反编译推断偏移**
- **禁止仅凭 signature-this 判归属**

---

## 相关文档

- **架构**：`docs/knowledge/arch_pipeline_overview.md`
- **调试**：`docs/knowledge/debug_common_diagnosis.md`
- **改型纪律**：`docs/knowledge/method_function_signature_inference.md`
- **证据分级**：`docs/knowledge/rule_evidence_tiering_no_unobtainable_gate.md`
- **度量盲区**：`CLAUDE.md`「字节全同 ≠ 全字节相同」
