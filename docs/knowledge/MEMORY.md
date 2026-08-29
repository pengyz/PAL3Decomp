# 项目共享知识库索引

规则见 [README.md](README.md)。每次写入新条目后在对应 type 段追加一行。

## Architecture

## Gotchas

- [多重继承匿名成员渲染 bug](gotcha_codegen_multi_inheritance_anon_member.md) — 根因是 apply/export 两层自造限制（IDA 原生支持多基类），已修复并有单测+IDB 回归守卫；待重跑 codegen+compile 收口
- [annotation hook 从未生效](gotcha_annotation_hook_never_wired.md) — validate-annotations.py 路径过期 + 未接入 settings.json，双重失效

## Patterns

- [无证据批量重命名](pattern_annotation_batch_rename_no_evidence.md) — A:cascade_sync 标记的伪语义重命名事故，check_annotations 通过 ≠ 标注质量真实提升

## Debugging

## Decisions

## References

- [IDA MCP 本机搭建](reference_ida_mcp_setup.md) — headless ida-pro-mcp 独立 venv，启动/打开 IDB 命令
