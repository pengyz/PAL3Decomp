---
name: pal3-pipeline
description: "PAL3 标注迭代管线 — IDA 标注→导出→codegen→编译→对比的完整工作流"
tags: [reverse-engineering, pal3, annotations, pipeline]
when_to_use: "当需要执行 PAL3 反编译管线流程时加载"
---

# PAL3 标注迭代管线

## Pipeline CLI

```bash
# 完整重建
python pipeline/cli.py init --force   # raw→PDB→FLIRT→annotations→IDB
python pipeline/cli.py export         # IDB→decomp JSONs
python pipeline/cli.py codegen all    # JSONs→.h+.cpp
python pipeline/cli.py compile        # VC6 编译

# 日常迭代（只改 annotation）
python pipeline/cli.py init           # 只 apply（不重建 raw）
python pipeline/cli.py export
python pipeline/cli.py codegen all
python pipeline/cli.py compile

# 只改 codegen（annotation 未变）
python pipeline/cli.py codegen all
python pipeline/cli.py compile
```

## IDA 查询工具

```bash
python pipeline/cli.py tool query_todo_fields       # 全局 _todo_ 扫描
python pipeline/cli.py tool query_class_full Name   # 指定类全量扫描
python pipeline/cli.py tool query_highref_fields    # 补充上下文
python pipeline/cli.py tool find_strides            # stride 分析
```

输出在 `pipeline/ida/_logs/*.json`。IDA 脚本的 print() 不显示在终端。

## data/annotations/ 文件格式

```
functions.json     {addr: {name, signature}}
globals.json       {addr: {name, type, overlaps_with, decomp_name}}
skip_functions.json {addr: {name, reason, target_name}}
structs/*.json     {name, binary_size, known_members: {offset: {name, type}}}
```

`globals.json` 中标记 `overlaps_with` 的变量是伪全局（地址落在父结构体内），
在 `globals.json` 中标记 `"type": "skip"`，并在父 struct 的 known_members 中
补对应偏移的字段。codegen 通过 struct_instances 自动解析为 `g_Parent.field`。

## Phantom Global 处理

1. 确认全局变量地址落在某 `struct_instance` 范围内
2. 在父结构体的 `known_members` 中添加对应偏移的字段定义
3. 在 `globals.json` 中将该全局标记为 `"type": "skip"`，`reason` 注明父结构体
4. 重新 export + codegen

## 字段验证

1. 定位二进制证据（query_todo_fields / verify_offset.py）
2. 确认 reg 来源（函数头部 ecx 赋值：`mov esi, ecx` / `lea esi, [ecx+X]`）
3. 确认访问宽度（指令前缀：8B=4B, C6=1B, 66 8B=2B, D9=float, DD=double）
4. 记录证据到 `CHANGE_LOG.md`
5. 修改 annotation → `check_annotations.py` 验证 → 提交
