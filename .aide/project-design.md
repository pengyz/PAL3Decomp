# PAL3 反编译管线 — aide 项目设计文档

## 概述

将 PAL3Decomp 项目从 Claude Code 迁移到 aide 平台，构建一个迭代式反编译工作台。

- **项目名称**: `pal3-decompilation`
- **项目路径**: `/home/peng/workspace/PAL3Decomp`
- **模式**: Chat（非 Flow）
- **状态**: ✅ 已创建成功

---

## 架构设计

### 为什么选 Chat 模式

| 维度 | Flow 模式 | Chat 模式 ✅ |
|------|----------|-------------|
| 迭代方式 | DAG 固定路径 | 用户随时切换方向 |
| 控制粒度 | 节点级 | 自然语言指令级 |
| 适配性 | 适合线性管线 | 适合探索式工作 |
| 原项目对标 | — | Claude Code 交互方式 |

反编译工作的核心特征：**每次迭代的目标函数不同、分析路径不确定、需要频繁人工决策**。这决定了 Chat 模式是唯一合理选择。

### UI 面板布局

```
┌─────────────────────────────────┬─────────────────────┐
│                                 │   管线状态           │
│        工作台 (chat)             │   (markdown)        │
│                                 ├─────────────────────┤
│        60%                      │   迭代日志           │
│                                 │   (markdown)        │
│                                 │      40%            │
└─────────────────────────────────┴─────────────────────┘
```

- **工作台**: 主交互区，用户下达指令、查看分析结果
- **管线状态**: 当前 IDB/annotations/编译状态实时展示
- **迭代日志**: 每次迭代的类型推断、BFS 更新、字节匹配记录

---

## 数据槽

| 槽名 | 类型 | 持久化 | 用途 |
|------|------|--------|------|
| `pipeline_status` | text | ✅ | 管线状态面板内容 |
| `iteration_log` | text | ✅ | 迭代日志面板内容 |

---

## Agent 定义

### engineer (反编译工程师)

```yaml
fallback_soul: |
  你是 PAL3 反编译工程师。你的核心工作循环：
  1. 从 annotations 和 decomp 数据中选择下一个目标函数
  2. 分析反编译输出，识别类名、方法名、类型信息
  3. 更新 annotations（运行 check_annotations.py 验证）
  4. 运行 IDA 应用标注 → 导出 → gen_cpp → 编译 → 对比
  5. 记录进展到迭代日志
```

---

## 门禁系统 (Hooks)

### 从 Claude Code 迁移的门禁

原项目通过 `.claude/settings.json` 的 `PreToolUse` hook 实现了三层门禁：

| 原 Hook | 触发工具 | 验证逻辑 |
|---------|---------|---------|
| validate-annotations.py | Edit/Write/Bash | JSON 格式、结构体重叠、地址格式、git commit 拦截 |
| pre-commit (git hook) | git commit | check_annotations.py + 增量对齐检测 |
| commit-msg (git hook) | git commit | Evidence + Confidence 格式检查 |

### aide Hook 接口设计

```yaml
hooks:
  pre_tool_use:
    # 门禁 1: Annotations 写入验证
    - matcher:
        tools: [Write, Edit]
        path_pattern: "pipeline/data/annotations/**"
      action:
        run: "cd $param.project_root && python3 pipeline/check_annotations.py --staged"
        on_fail: block
        message: "Annotations 验证失败，请修正后重试"

    # 门禁 2: Git commit 前验证
    - matcher:
        tools: [Bash]
        command_pattern: "git commit"
      action:
        run: "cd $param.project_root && python3 pipeline/check_annotations.py"
        on_fail: block
        message: "Commit 门禁：annotations 验证未通过"

    # 门禁 3: Commit message 格式
    - matcher:
        tools: [Bash]
        command_pattern: "git commit"
      action:
        validate_message:
          pattern: "^\\[(annotate|pipeline|codegen|build|docs|fix|refactor|test)\\] .+"
          message: "Commit message 必须为 [category] description 格式"

  post_tool_use:
    # 门禁 4: 结构体偏移校验（警告不阻断）
    - matcher:
        tools: [Write, Edit]
        path_pattern: "pipeline/data/annotations/structs/*.json"
      action:
        run: "cd $param.project_root && python3 pipeline/verify_offset.py --file $tool.file_path"
        on_fail: warn
        message: "结构体偏移校验警告"
```

### Hook 变量替换

| 变量 | 来源 | 示例 |
|------|------|------|
| `$param.project_root` | 项目参数 | `/home/peng/workspace/PAL3Decomp` |
| `$param.ida_path` | 项目参数 | `/opt/ida/idat64` |
| `$tool.file_path` | 当前操作文件 | `pipeline/data/annotations/structs/CRole.json` |
| `$tool.command` | Bash 命令内容 | `git commit -m "[annotate] ..."` |

### 当前状态

> ⚠️ **Hook runtime 尚未实现**。YAML 中的 `hooks` 段已定义完整接口，待 aide 支持后自动生效。
> 当前通过 `directives` 中的门禁规则做**软约束**（依赖 Agent 自觉遵守）。

---

## Hook 功能需求（提交给 aide 开发）

### 需求 1: PreToolUse Hook

**触发时机**: Agent 调用工具前，拦截检查。

```
matcher:
  tools: [工具名列表]           # 精确匹配工具名
  path_pattern: "glob"         # 文件路径 glob（Write/Edit/Delete）
  command_pattern: "regex"     # 命令正则（Bash 专用）
action:
  run: "shell_command"         # 执行外部脚本
  on_fail: block | warn        # block=阻止执行, warn=警告但允许
  message: "错误提示"          # 展示给 Agent 的提示
```

### 需求 2: PostToolUse Hook

**触发时机**: 工具执行成功后，做后置检查。

接口同 PreToolUse，但 `on_fail: block` 时回滚本次写入。

### 需求 3: validate_message

**特殊 action**: 用正则验证 git commit message 格式。

```
action:
  validate_message:
    pattern: "regex"
    message: "格式不合规提示"
```

### 需求 4: 变量系统

- `$param.*` — 项目创建时传入的参数
- `$tool.file_path` — 当前工具操作的文件路径
- `$tool.command` — Bash 工具的完整命令字符串
- `$tool.args` — 工具的 JSON 参数（高级用例）

---

## Directives 全文（软门禁）

directives 段包含了完整的门禁规则文字描述，即使 Hook 未实现，Agent 也会遵循：

- **Annotations 写入**：修改前必须运行 `check_annotations.py`
- **Git Commit**：提交前验证 + message 格式 `[category] description`
- **IDA 脚本**：使用 `$param.ida_path -A -S"script.py" ...` 格式
- **代码质量**：禁止从反编译推断偏移、必须有二进制证据、不降级类型

---

## 工作流循环

```
┌─────────────────────────────────────────────────────────┐
│  阶段 0: apply_annotations                               │
│  python3 pipeline/ida/apply_annotations.py               │
│  → 将 annotations/ 数据注入 IDB (函数名+类型+全局变量)    │
├─────────────────────────────────────────────────────────┤
│  阶段 1: IDA 导出                                        │
│  idat64 -A -S"export_all.py" PAL3.exe.i64               │
│  → 生成 asm/pal3/decomp/*.json                          │
├─────────────────────────────────────────────────────────┤
│  阶段 2: gen_cpp                                         │
│  python3 pipeline/gen/gen_cpp.py                         │
│  → 后处理生成 src/pal3/*.cpp, include/pal3/*.h           │
├─────────────────────────────────────────────────────────┤
│  阶段 3: 编译                                            │
│  cmake --build build --config Release                    │
│  → MSVC6 编译，输出 PAL3.exe                             │
├─────────────────────────────────────────────────────────┤
│  阶段 4: 字节对比                                        │
│  python3 pipeline/compare.py                             │
│  → 对比编译产物 vs 原始二进制                              │
├─────────────────────────────────────────────────────────┤
│  阶段 5: 标注                                            │
│  分析结果 → 更新 annotations/ → 回到阶段 0               │
│  (此处触发 PreToolUse hook 验证)                         │
└─────────────────────────────────────────────────────────┘
```

---

## 路径约定

| 用途 | 路径 |
|------|------|
| 标注数据 | `pipeline/data/annotations/` |
| IDA 脚本 | `pipeline/ida/` |
| 反编译 JSON | `asm/pal3/decomp/` |
| 源码生成 | `src/pal3/` |
| PDB 参考 | `pipeline/data/pdb/` |
| 原始二进制 | `original/PAL3.exe` |
| IDA 数据库 | `original/PAL3.exe.i64` |
| 编译工具链 | `tools/compilers/msvc6.0/` |

---

## 下一步

1. ~~创建 aide 项目~~ ✅
2. **等待 aide 实现 Hook runtime** → `hooks` 段自动生效
3. 通过 `project_open("pal3-decompilation")` 进入工作台开始迭代
4. 首次运行时验证 IDA 路径和工具链可用性
