---
name: annotation-guide
description: "PAL3 annotations 标注规范与验证流程指南"
tags: [reverse-engineering, annotations, validation]
when_to_use: "当用户要求修改 annotations、添加函数/结构体定义、或进行反编译标注时加载"
---

# PAL3 Annotations 标注规范

## 数据格式

### functions.json
```json
{
  "0x004014F0": {
    "name": "CCBAI::Thunk_GetValue",
    "signature": "char __stdcall(int a1, int a2)"
  }
}
```
- Key: `0x` + 8 位大写十六进制地址
- `name`: 非空，格式 `ClassName::MethodName` 或 `FreeFunction`
- `signature`: IDA 风格函数签名

### structs/*.json
```json
{
  "name": "Actor",
  "pdb_size": 596,
  "binary_size": null,
  "gen_size": 596,
  "base_class": null,
  "known_members": {
    "0": { "name": "m_actarray", "type": "...", "source": "pdb_verified_by_old_ida" },
    "20": { "name": "m_name", "type": "char[260]", "source": "binary:raw_InitComponents" }
  }
}
```
- `known_members` 的 key 是**十进制字节偏移**
- `source` 标注数据来源（`pdb_verified`、`binary:函数名`、`ida_decomp:函数名`）
- **禁止**无来源的偏移推断

### globals.json
```json
{
  "0x0056A634": { "name": "g_bActorFlag", "type": "unsigned char" }
}
```

## 验证流程

**每次修改 annotations 前后必须运行：**
```bash
python3 pipeline/check_annotations.py
```

## 关键约束

1. **二进制证据优先** — 结构体偏移必须有 `binary:xxx` 或 `pdb_verified` 来源
2. **禁止 Hex-Rays 推断** — Hex-Rays 反编译的偏移可能不准确，必须用二进制验证
3. **不降级信息** — 已知类型不改为 `void*`/`int`
4. **gen_cpp 等价变换** — 代码生成只做等价转换，不编造信息
