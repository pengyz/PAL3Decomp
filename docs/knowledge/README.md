# 项目共享知识库 — 提取规则

面向所有 AI 实例（Claude Code / Codex / 其他协作工具）：会话中遇到下面时刻之一，按本规则写入本目录。

移植自 osbot 项目的 `docs/knowledge/` 机制，适配 PAL3Decomp 的反编译管线场景。

## 写入时机

1. **commit 后** — 用户主动提及刚 commit 的内容
2. **用户纠正方法** — "别这样做"、"这不对" → 多为 `pattern` / `gotcha`
3. **用户确认非显然方法有效** — 接受了非常规选择 → `decision`，正反馈也写，避免知识库只剩避雷
4. **遇到平台坑/反直觉行为** — IDA/Hex-Rays/MSVC6/codegen 管线的坑 → `gotcha` / `debug`
5. **发现门禁失效或流程漏洞** — hook 未生效、校验有盲区 → `gotcha`（这类往往最贵，一旦漏掉会重复踩）

判断标准：另一个 AI 实例接手这个项目时，这条知识能帮它少走弯路吗？不能 → 不写。

## 类型

<types>
<type>
    <name>architecture</name>
    <description>管线设计决策、annotation/export/codegen 层职责边界、为什么选 A 不选 B。</description>
    <when_to_save>方案被确认采纳、用户解释了非显然的取舍、读代码看不出"为什么"时</when_to_save>
    <body_structure>事实陈述（一句），然后 **为什么：**（机制/约束/被否决的备选）和 **何时使用：**（做什么相关改动时该回想此条）。</body_structure>
</type>
<type>
    <name>gotcha</name>
    <description>IDA/Hex-Rays/MSVC6 编译器/codegen 管线的坑、反直觉行为、门禁失效。</description>
    <when_to_save>触碰某工具/管线阶段导致非预期结果、找到 workaround、发现校验盲区时</when_to_save>
    <body_structure>现象陈述，然后 **为什么：**（底层机制）和 **何时使用：**（什么场景下要警惕此坑）。</body_structure>
</type>
<type>
    <name>pattern</name>
    <description>annotation 标注约定、codegen 开发模式、证据分级的最佳实践/反模式。</description>
    <when_to_save>同类问题第二次出现、确立项目约定、发现标注反模式时</when_to_save>
    <body_structure>规则陈述，然后 **为什么：**（避免什么）和 **何时使用：**（做什么类型标注/代码时套用）。</body_structure>
</type>
<type>
    <name>debug</name>
    <description>调试方法、IDA 查询路径、关键工具用法、排查路径。</description>
    <when_to_save>排查中发现高效诊断手段、定位到关键工具/命令时</when_to_save>
    <body_structure>排查动作（命令/路径），然后 **为什么：**（症状映射到此动作的逻辑）和 **何时使用：**（出现什么症状时启用）。</body_structure>
</type>
<type>
    <name>decision</name>
    <description>已验证的取舍。包括正反馈：用户确认非常规选择有效。</description>
    <when_to_save>用户接受了非显而易见的方案选择且未推翻、做完后回头确认走对了路时</when_to_save>
    <body_structure>选择陈述，然后 **为什么：**（为什么这个选项胜出）和 **何时使用：**（什么场景下重复此选择）。</body_structure>
</type>
<type>
    <name>reference</name>
    <description>外部资源指针：工具安装位置、关键脚本、本机环境配置。</description>
    <when_to_save>用户提到一个外部资源及其用途、或搭建了可复用的工具链时</when_to_save>
    <body_structure>资源位置 + 一句用途说明。无需 Why/When。</body_structure>
</type>
</types>

## 不写入

- 代码/annotation 本身能表达的 → 读代码/JSON
- `git log` / `CHANGE_LOG.md` 能查到的具体证据条目 → 那里是权威（单字段的证据记录仍归 `CHANGE_LOG.md`，不进这里）
- `CLAUDE.md` / skill 文档已有的规则 → 不重复
- 仅对当前用户有用的偏好 → 写个人 memory
- 临时调试状态、进行中的工作 → 不持久化
- 修复某个具体 annotation 字段的过程 → 证据在 `CHANGE_LOG.md`，这里只写"发现的通用规律"

即使用户明确要求保存上述内容，也要先反问"其中有什么*非显然*的部分？" — 那部分才值得记。

## 文件结构

每条知识 1 个文件：`docs/knowledge/<type>_<slug>.md`。

frontmatter：

```markdown
---
name: <kebab-case-slug>
description: <一行钩子，决定未来召回相关性>
type: architecture | gotcha | pattern | debug | decision | reference
created: YYYY-MM-DD
sources: [<commit-hash 或 session 描述>]
---

<事实陈述，一句>

**为什么：** ...
**何时使用：** ...
```

`reference` 类型可省 Why/When。其他五类必填。

## 写入流程

1. Read `docs/knowledge/MEMORY.md` 与本文件
2. 用 description 和现有条目对照 → 已有相似条目则**更新**，不新建
3. 写入 `docs/knowledge/<type>_<slug>.md`
4. 在 `docs/knowledge/MEMORY.md` 对应 type 段落追加一行索引
5. 同步追加一行到 `docs/knowledge/kairos/YYYY/MM/YYYY-MM-DD.md`

## Kairos 日志（事件流）

`docs/knowledge/kairos/YYYY/MM/YYYY-MM-DD.md` 是 commit/会话级事件流，作为未来蒸馏的增量素材。

写入时机：
- 每次写入 knowledge 条目 → 同步追加一行
- 没产生条目但发生了"项目级动作"（annotation 大批量变更、pipeline 阶段性结论）→ 仅追加一行 kairos

格式：`- HH:MM — <动作>：<一句话>`，单文件 ≤ 100KB。

## 引用前的验证（防 stale）

引用 docs/knowledge/ 中提到的具体文件 / 函数 / 命令前，必须：

- 文件路径 → Read 或 ls 验证存在
- 函数 / 结构体名 → grep annotation JSON 或 IDA MCP 查询验证未被重命名
- 命令 / flag → 在脚本 `--help` 或本文验证

"docs/knowledge/ 说 X 存在" ≠ "X 现在存在"。验证失败 → 不引用 + 标记为失效候选。

## 约束

- 单条目正文 ≤ 30 行；接近上限时拆分或精简
- `MEMORY.md` ≤ 200 行；接近上限删最旧/最不引用的条目
- 写入前先查重；更新优先于新增
- `decision` / `pattern` 类条目正反并存，不要让知识库只剩"避雷指南"

## 与 CHANGE_LOG.md / CLAUDE.md 的边界

| 内容 | 去处 |
|------|------|
| 单个字段/偏移的证据记录（哪个函数、哪条指令） | `data/annotations/CHANGE_LOG.md` |
| annotation 标注的强约束规则（证据分级、禁止事项） | `CLAUDE.md` + pal3-pipeline skill |
| 管线各阶段的通用坑/规律（如"codegen 对多继承的处理缺口"） | `docs/knowledge/gotcha_*.md` |
| 本机工具链搭建（IDA MCP、pipeline 环境配置） | `docs/knowledge/reference_*.md` |
| 一次性 annotation 事故的教训（如无证据批量重命名） | `docs/knowledge/pattern_*.md`（教训抽象后的规律，不是事故本身的流水账） |
