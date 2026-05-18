---
name: pal3-pipeline
description: "PAL3 反编译管线完整工作流。当用户要求修改 annotations、运行管线、执行 IDA 操作、进行字节对齐时加载。"
tags: [reverse-engineering, annotations, pipeline, ida, pal3]
when_to_use: "当用户提到反编译、标注、annotations、IDA、compile、byte-match、对齐时"
---

# PAL3 反编译管线

## 核心原则

- **二进制是权威**：PAL3.exe 指令优先于 PDB 和 Hex-Rays 推断
- **单字段验证**：每个偏移/类型修改必须有独立的 A 级二进制证据
- **置信度 ≥ 80**：offset/type 修改需要 80+ 置信度
- **不降级信息**：已知类型不改为 void*/int

## 管线 CLI

```bash
python pipeline/cli.py check        # 验证 annotations 格式
python pipeline/cli.py apply        # 应用标注到 IDB
python pipeline/cli.py export       # 从 IDB 导出 decomp JSON
python pipeline/cli.py codegen all  # 生成 headers + cpp
python pipeline/cli.py compile      # MSVC6 编译验证
```

完整流程：check → apply → export → codegen → compile → byte-compare

## IDA 脚本执行

```bash
$param.ida_path -A -S"pipeline/ida/script.py" "$param.project_root/original/PAL3.exe.i64"
```

关键脚本：
- `apply_annotations.py` — 应用 annotations 到 IDB
- `export_full.py` — 导出全量 decomp JSON
- `query_todo_fields.py` — 全局扫描 _todo_ 字段
- `query_class_full.py ClassName` — 特定类全方法扫描
- `verify_offset.py` — 验证全局实例字段偏移

## 路径约定

| 路径 | 用途 |
|------|------|
| `pipeline/data/annotations/` | 标注数据（唯一可编辑的数据源） |
| `pipeline/data/annotations/structs/` | 结构体 JSON（每类一文件） |
| `pipeline/ida/` | IDA 脚本（只读） |
| `asm/pal3/decomp/` | Hex-Rays 导出 JSON（自动生成） |
| `src/pal3/` | 生成的 C++ 源码 |
| `include/pal3/gen/` | 生成的头文件 |
| `tools/gbengine_compare.py` | gbengine 字节对比工具 |
| `.claude/pal3_cursor.json` | 工作游标（当前 BFS 位置） |
| `.claude/pal3_iterations/` | 迭代记录 |

## 数据格式

### functions.json
```json
{"0x004014F0": {"name": "ClassName::Method", "signature": "ret __conv(params)"}}
```

### structs/*.json
```json
{
  "name": "Actor",
  "binary_size": 596,
  "base_class": null,
  "known_members": {
    "0": {"name": "m_field", "type": "int", "source": "binary:func_name"}
  }
}
```
- key: 十进制字节偏移
- source: `pdb_verified` | `binary:函数名` | `ida_decomp:函数名`

## 置信度规则

| 证据 | 置信度 | 可用于 |
|------|--------|--------|
| 绝对地址指令 (VA + opcode) | 90 | offset/type |
| reg+disp32 + this-source | 85 | type |
| apply_annotations + Hex-Rays | 85 | 命名 |
| 3+ A 级交叉证据 | 80+ | offset |
| Hex-Rays 文本（无 apply） | 50 | **禁止 offset/type** |
| 语义推断 | 30 | 仅命名 |

## 禁止行为

1. ❌ 从反编译文本推断偏移（可能使用错误结构体布局）
2. ❌ 批量修改未验证字段
3. ❌ 假设对齐方向（必须确认实际值）
4. ❌ 非语义命名（保持 `_todo_` 如果不确定）
5. ❌ 提交缺少 A 级证据的 offset/type 修改
6. ❌ 修改 pipeline/*.py 脚本（由 plugin gate 强制）

## 工作游标

查看 `.claude/pal3_cursor.json` 获取：
- 当前目标函数
- BFS frontier（待处理队列）
- 上次完成的函数列表

查看 `.claude/pal3_iterations/NNNN.json` 获取迭代历史记录。

## gbengine 字节对齐

```bash
python tools/gbengine_compare.py --compile src/gbengine/XXX.cpp --all
```

匹配分类：
- `exact` — 100% 字节匹配
- `equiv` — 逻辑等价（寄存器/栈偏移差异可接受）
- `partial` — 部分正确
- `wrong` — 需要修复

Size MISMATCH 必须修复。寄存器选择差异可接受。
