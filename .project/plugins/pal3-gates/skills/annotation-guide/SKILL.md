---
name: annotation-guide
description: "PAL3 annotations 标注规范。当用户要修改函数/结构体/全局变量标注时加载。"
tags: [reverse-engineering, annotations, pal3]
when_to_use: "当用户要求修改 annotations、添加函数签名、更新结构体成员时"
---

# PAL3 Annotations 标注规范

## 数据格式

### functions.json
```json
{"0x004014F0": {"name": "CCBAI::Thunk_GetValue", "signature": "char __stdcall(int a1, int a2)"}}
```
- Key: `0x` + 8 位大写十六进制
- name: 非空，格式 `ClassName::MethodName` 或 `FreeFunction`
- signature: IDA 风格

### structs/*.json
```json
{
  "name": "Actor",
  "binary_size": 596,
  "pack": null,
  "base_class": null,
  "known_members": {
    "0": {"name": "m_actarray", "type": "...", "source": "pdb_verified"},
    "20": {"name": "m_name", "type": "char[260]", "source": "binary:raw_InitComponents"}
  }
}
```
- known_members key: 十进制字节偏移
- source 标注数据来源

## 置信度规则

| 证据 | 置信度 | 可用于 |
|------|--------|--------|
| 绝对地址指令 | 90 | offset/type 修改 |
| reg+disp32 + this-source 证明 | 85 | type 修改 |
| IDA apply_annotations + Hex-Rays | 85 | 语义命名 |
| 3+ 交叉 A 级证据 | 80+ | offset 修改 |
| Hex-Rays 文本（无 apply） | 50 | **禁止用于 offset/type** |
| 语义推断 | 30 | 仅命名 |

## 验证流程

修改 annotations 前后必须：
```bash
python pipeline/cli.py check
```

## 禁止行为

1. 从反编译文本推断偏移（可能使用错误结构体布局）
2. 批量修改未验证字段
3. 假设对齐方向（必须确认实际值）
4. 使用非语义命名（保持 `_todo_`）
5. 提交缺少 A 级证据的 offset/type 修改
