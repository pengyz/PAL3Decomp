---
name: codegen-multi-inheritance-anon-member
description: 多重继承基类被渲染成无名成员导致 C2208 级联 — 根因是 apply/export 两层自造限制（非 IDA 限制），2026-08-29 已修复
type: gotcha
created: 2026-08-29
updated: 2026-08-29
status: fixed
sources: [session-2026-08-29]
---

**现象**：编译出现大量 `C2208: no members defined using this type`，类型名形如 `CTaskTpl_..._CEffCylinder`（无变量名字段），命中 ~38 个多继承类（CEff 任务模板类、Role/UICaption/MUIDialog/SceneObj 等），经 globals.h include 链级联炸穿全部 205 个 .cpp。

**根因（已验证修正）**：annotation 数据本身没错。最初判断"IDA struct 模型只支持单继承"是**错的**——IDA 9.x 的 UDT 模型原生支持任意数量基类（`udm_t.is_baseclass()/set_baseclass()`，且 `parse_decls` 能直接解析标准 C++ 多继承语法）。真正的根因是两层自造限制：

1. **写入侧** `apply_annotations.py:create_fixed_struct()`：构造匿名基类成员时从不调用 `mb.set_baseclass()`，IDA 把基类 2+ 当普通无名数据成员（引入于 commit 236a324c0 附近，注释写死了"IDA's struct model limitation"的错误假设）。
2. **读取侧** `export_full.py`：用 `umoffset == 0` 猜"是不是基类"，而不是问官方 `um.is_baseclass()`。offset 0 的第一基类碰巧判对，非零偏移的第二+基类被误分类为匿名 inline 成员流入 `data_members`，最终被 `emit_headers.py` 渲染成非法 C++。

**修复（2026-08-29）**：写入侧补 `mb.set_baseclass()`；读取侧改用 `is_baseclass()`，判定逻辑抽成无 IDA 依赖的纯函数 `pipeline/ida/udt_classify.py:classify_bases_and_members()`。`emit_headers.py` 的 class 声明行本来就遍历完整 `bases` 列表，上游喂对数据后无需改动。

**固化守卫**：
- `tests/test_udt_classify.py` — 纯逻辑单测（含"第二基类在非零偏移必须进 bases"的核心回归用例）
- `pipeline/ida/test_multi_inheritance_regression.py` — 真实 IDB 集成回归（`idat -A -S` 或 MCP py_eval 运行），端到端断言 create_fixed_struct → classify 的产出

**何时使用**：再遇到"IDB 里 `name=''` 且 offset 非 0 的成员"时，先查 `is_baseclass()` 再决定它是基类还是 inline union/struct；不要用偏移或命名约定猜。对 IDA 能力下结论前先用 `parse_decls`/官方 API 实测——本项目已两次因"想当然的 IDA 限制"引入 bug（另见 template_bases.json 桥接的由来）。

**遗留跟进**：管线修复 ≠ 错误清零。需重跑 `codegen all + compile` 产出新快照，确认 C2208/C2440/C2664 级联消除幅度（历史峰值 48/185 pass，见 docs/knowledge 里 6-27 快照记录）。
