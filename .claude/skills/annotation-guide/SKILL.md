---
name: annotation-guide
description: "PAL3 annotations 标注规范与验证流程指南"
tags: [reverse-engineering, annotations, validation]
when_to_use: "当用户要求修改 annotations、添加函数/结构体定义、或进行反编译标注时加载"
---

# PAL3 Annotations 标注规范

## 数据格式

### functions.json — 仅全局函数

```json
{
  "0x004014F0": {
    "name": "ArraySort",
    "signature": "int __stdcall(int base, int count, int elemSize, int compareFunc)"
  }
}
```
- Key: `0x` + 8 位大写十六进制地址
- `name`: 非空，**仅限全局函数名**（不包含 `::`）
- `signature`: IDA 风格函数签名
- ⚠️ **不再存储类成员函数** — 所有类方法（含虚函数）归属到 `structs/*.json` 的 `methods` 字段

### structs/*.json — 类定义（含虚函数表和方法）

```json
{
  "name": "UIWnd",
  "binary_size": 68,
  "base_class": null,
  "known_members": {
    "0": { "name": "vfptr", "type": "void *", "source": "gap_fill:type_fix(vtable pointer)" },
    "20": { "name": "m_name", "type": "char[260]", "source": "binary:raw_InitComponents" }
  },
  "methods": {
    "0x00445E70": {
      "name": "UIWnd::ShowWindow",
      "signature": "int __thiscall(UIWnd *this, int nFlags)",
      "source": "vtable_migrated",
      "ordinal": 0
    }
  },
  "vtables": [
    {
      "addr": "0x0056AE2C",
      "base": "UIFrameWnd",
      "slots": [
        { "addr": "0x00445E70", "from": null },
        { "addr": "0x00443200", "from": "UIFrameWnd" }
      ]
    }
  ]
}
```

#### 字段说明
- `known_members`: key 是**十进制字节偏移**，`source` 标注数据来源
- `methods`: address-keyed dict，每个条目描述一个类方法
  - **`ordinal` 存在** = 虚函数（ordinal 值在主虚表中的 slot 下标）
  - **`ordinal` 缺失** = 非虚函数
  - `name` 格式为 `ClassName::MethodName`
- `vtables`: 该类的虚函数表列表（一个类可能有多张表，多继承时）
  - `addr`: 虚表在二进制中的 .rdata 地址
  - `base`: 该虚表对应的基类名（多继承时区分）
  - `slots`: 有序列表，按虚表 slot 顺序排列
    - `addr`: 该 slot 指向的函数地址
    - `from`: `null` = 本类实现，`"BaseClass"` = 继承自基类

#### 虚函数判定规则
- **`ordinal in methods[addr]`** = 该函数是虚函数
- 继承链一致性：同一 slot ordinal 在基类和派生类中应有相同的函数名
- 虚函数表 slot 顺序即 vtable 布局顺序，codegen 按此顺序输出 `virtual` 声明

### globals.json
```json
{
  "0x0056A634": { "name": "g_bActorFlag", "type": "unsigned char" }
}
```

### vtables.json — 已废弃

`vtables.json` 已被删除。所有虚函数表数据已迁移至各 `structs/*.json` 文件的 `vtables` 字段。

## 验证流程

**每次修改 annotations 前后必须运行：**
```bash
cd /home/peng/workspace/PAL3Decomp && python3 pipeline/check_annotations.py
```

验证项目：
1. JSON 格式正确性
2. 地址格式 `0x[0-9A-F]{8}`
3. 必填字段（name、signature、type）
4. 结构体成员无重名，offset 递增
5. base_class 引用存在
6. vtable 地址/slot 地址格式正确
7. own slot（from=null）对应的 method 有 ordinal

## 关键约束

1. **二进制证据优先** — 结构体偏移必须有 `binary:xxx` 或 `pdb_verified` 来源
2. **禁止 Hex-Rays 推断** — Hex-Rays 反编译的偏移可能不准确，必须用二进制验证
3. **不降级信息** — 已知类型不改为 `void*`/`int`
4. **gen_cpp 等价变换** — 代码生成只做等价转换，不编造信息
5. **类方法不进入 functions.json** — `functions.json` 只存全局函数，类方法（含虚函数）归属各自的 `structs/*.json`
6. **虚表数据内聚在类定义内** — 每张虚表属于且仅属于一个类，记录在类的 `vtables` 字段中
