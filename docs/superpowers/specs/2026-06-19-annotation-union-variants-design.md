# Annotation Union Variants — 设计文档

## 问题

当前 annotation 的 `known_members` 是扁平 offset→value 映射，每个偏移只能有一个名字。但游戏二进制中存在大量内存复用模式——同一块内存在不同上下文中以不同类型访问。

典型场景：`PalScript` 的 `m_RoleSlotArray @ +0x18C`：
- 作为 `char[896]`（SetAction 中按 role ID 遍历）
- 作为几十个具名字段的集合（`m_pTexture @ +0x196`、`m_nRoleCount @ +0x220`...）

开发者原始的 C++ 代码用了匿名 union + 匿名 struct：
```cpp
union {
    unsigned char m_RoleSlotArray[896];
    struct {
        gbTexture *m_pTexture;
        int m_nRoleCount;
        // ...
    };
};
```

当前 codegen 只支持"同偏移多类型"的 union（多个名字共享同一个 offset），不支持"大数组 vs 内部有不同偏移的 struct"的 union。

## 目标

扩展 annotation JSON 格式和 codegen，使 struct annotation 中的字段可以表达 union 语义——一个字段有多个 variant，其中 variant 可以是：
- A. 引用已知 struct 类型（`data/annotations/structs/` 中定义）
- B. 内联子字段列表（`_members` 中的绝对偏移）

## 格式

### 引用已知类型

```json
{
  "name": "m_RoleSlotData",
  "type": "unsigned char[896]",
  "_variants": [
    {"type": "tagRoleSlot"}
  ]
}
```

- `tagRoleSlot` 来自 `data/annotations/structs/tagRoleSlot.json`
- 其 `known_members` 中的偏移是**相对于 `tagRoleSlot` 基址**的
- codegen 在嵌入 union 时自动加上外层字段的偏移（union 基址）

### 内联子字段

```json
{
  "name": "m_RoleSlotData",
  "type": "unsigned char[896]",
  "_variants": [
    {
      "type": "struct",
      "_members": [
        {"offset": "0x0A", "name": "m_pTexture", "type": "gbTexture *"},
        {"offset": "0x14", "name": "m_pTextureInfo", "type": "_PlugInfo *"}
      ]
    }
  ]
}
```

- `_members` 中的 offset 是**父结构体的绝对偏移**（与 `known_members` 一致）
- 不与引用类型混用（要么引用类型，要么内联，不能同时）

### 同偏移简写（已有兼容）

```json
{
  "0": {
    "name": "as_int",
    "type": "char *",
    "_variants": [
      {"name": "as_float", "type": "float"}
    ]
  }
}
```

- 简写形式：省略 `type`/`_members`，只给 `name` + `type`→ 同偏移多类型
- 已有 codegen 支持（`len(group) > 1` 时的 union 块），保留兼容

## codegen 实现（`emit_headers.py`）

### 核心修改位置

`generate_header()` 中成员循环（当前 ~line 1300-1350）：

```python
for off_str in sorted_offsets:
    m = group[0]
    variants = m.get("_variants", [])
    
    if variants:
        # 插 gap padding
        if off > start_off:
            gap = off - start_off
            lines.append("    char _gap_%03X[%d]; // +0x%X" % (start_off, gap, start_off))
        
        lines.append("    union { // +0x%X" % off)
        
        # Variant 0: 主字段本身
        _emit_member_line(lines, m, off)
        
        for v in variants:
            ref_type = v.get("type", "")
            if ref_type == "struct":
                # 内联 struct
                lines.append("        struct {")
                inner_start = off
                _prev = inner_start
                for mem in sorted(v.get("_members", []), key=lambda x: int(x["offset"], 16)):
                    abs_off = int(mem["offset"], 16)
                    if abs_off > _prev:
                        gap = abs_off - _prev
                        lines.append("            char _gap_%03X[%d];" % (_prev, gap))
                    _emit_member_line(lines, mem, abs_off, indent=12)
                    _prev = abs_off + _estimate_member_size(mem.get("type", "int"))
                lines.append("        };")
            else:
                # 引用已知 struct 类型
                ref_data = _load_struct(ref_type)
                lines.append("        struct {")
                ref_members = ref_data.get("known_members", {})
                inner_start = off
                _prev = inner_start
                for ref_off_str, ref_info in sorted(ref_members.items(), key=lambda x: int(x[0], 16)):
                    rel_off = int(ref_off_str, 16)
                    abs_off = off + rel_off
                    if abs_off > _prev:
                        gap = abs_off - _prev
                        lines.append("            char _gap_%03X[%d];" % (_prev, gap))
                    _emit_member_line(lines, ref_info, abs_off, indent=12)
                    _prev = abs_off + _estimate_member_size(ref_info.get("type", "int"))
                lines.append("        };")
        
        lines.append("    };")
        member_size = max(...)
        start_off = off + member_size
        continue
```

### 偏移约定

| 场景 | _members/known_members 偏移 | codegen 处理 |
|------|---------------------------|-------------|
| 引用类型 | 相对于被引用类型基址 | 加 union 基址：`abs = union_base + rel` |
| 内联 _members | 父结构体绝对偏移 | 直接使用：`abs = int(mem["offset"], 16)` |

### _load_struct 辅助函数

```python
def _load_struct(name):
    """从 annotation structs 目录加载 struct 定义，缓存结果。"""
    if name in _struct_cache:
        return _struct_cache[name]
    path = ANNOTATIONS_DIR / "structs" / f"{name}.json"
    if not path.exists():
        return {}
    data = json.load(open(path))
    _struct_cache[name] = data
    return data
```

## check_annotations 校验

在 `check_annotations.py` 的 struct 校验段新增 `_variants` 检查：

```python
for addr_s, info in members.items():
    variants = info.get("_variants", [])
    if not variants:
        continue
    
    base_off = int(addr_s.split("_")[0], 0)
    main_type = info.get("type", "int")
    main_size = _estimate_member_size(main_type, structs)
    
    for v in variants:
        ref_type = v.get("type", "")
        
        # 1. 引用类型必须存在
        if ref_type and ref_type != "struct":
            if ref_type not in all_struct_names:
                errors.append(f"structs[{sname}]: _variants ref to unknown type '{ref_type}'")
                continue
            ref_data = structs.get(ref_type, {})
            ref_size = ref_data.get("binary_size", 0)
        elif ref_type == "struct":
            # 内联 struct：计算最大范围
            ref_size = 0
            for mem in v.get("_members", []):
                mem_end = int(mem["offset"], 16) + _estimate_member_size(mem.get("type", "int"), structs)
                ref_size = max(ref_size, mem_end - base_off)
        else:
            continue
        
        # 2. variant 大小不能超过主字段
        if ref_size > main_size:
            errors.append(
                f"structs[{sname}]: _variants '{ref_type}' size {ref_size} > "
                f"main field '{info.get('name')}' size {main_size}")
        
        # 3. 引用类型不能是 union（禁止嵌套）
        if ref_type in structs and structs[ref_type].get("is_union"):
            errors.append(f"structs[{sname}]: _variants cannot reference a union type")
        
        # 4. 引用类型不能有 base_class（内嵌 struct 无需继承）
        if ref_type in structs and structs[ref_type].get("base_class"):
            warnings.append(f"structs[{sname}]: _variants ref '{ref_type}' has base_class")
```

## 测试用例

1. `PalScript.m_RoleSlotArray`: `unsigned char[896]` + `_variants: [{type: "tagRoleSlot"}]`
2. `scVARIANT_data`: 已有 `is_union: true`，无需改动
3. 同偏移简写兼容：已有用法不受影响

## 实施顺序

1. `check_annotations.py` 先合入 `_variants` 校验
2. `emit_headers.py` 合入 union 生成逻辑
3. 验证 PalScript 生成代码（`union { char[896]; struct { ... }; };`）
4. 扩展其他已知复用场景

## 不做的

- 不修改 DataStore（`_variants` 只影响 header 生成）
- 不修改 stage3_cleanup / ast_transform（只影响类型布局，不影响 OOP 转换）
- 不支持嵌套 union（union 内不能再引用 union 类型）
- 不支持引用类型自身有 `_variants`
