# 标注审计 Schema v1 (2026-11-12)

## 定义

一条标注声称"系统性审计过"必须满足四条件：
1. **枚举完备**：该数据的全部使用点已枚举（非采样）
2. **逐点对拍**：每个使用点的实际类型/约定与标注声明一致
3. **矛盾处置**：发现矛盾时已修正标注或已证明矛盾是渲染惯例
4. **审计记录**：每条证据带 file:line + 使用点原文 + 对拍结论

## Schema

### 结构成员 (known_members[].audit)

```json
{
  "audit": {
    "level": "audited|contradicted|insufficient",
    "method": "use_site_enumeration",
    "sites_checked": 19,
    "sites_consistent": 19,
    "sites_contradicted": 0,
    "contradictions": [
      {"file": "X.cpp", "line": 123, "expected": "int", "actual": "float *", "detail": "..."}
    ],
    "timestamp": "2026-11-12"
  }
}
```

- `audited`: 全部使用点类型一致
- `contradicted`: 存在使用点与标注不一致（需人工裁决）
- `insufficient`: 使用点过少或歧义（无法定谳）

### 方法签名 (methods[].audit)

```json
{
  "audit": {
    "level": "audited",
    "method": "calling_convention_and_slot_accounting",
    "cc": "__thiscall",
    "param_count": 2,
    "evidence": [
      "entry: mov esi,ecx + ret 4 = thiscall(1) + 槽位",
      "caller: push 0 = 单实参"
    ],
    "timestamp": "2026-11-12"
  }
}
```

### 全局变量 (globals[].audit)

```json
{
  "audit": {
    "level": "audited",
    "method": "use_site_enumeration",
    "sites_checked": 5,
    "sites_consistent": 5,
    "byte_evidence": "b'Basedata system init failed.'",
    "timestamp": "2026-11-12"
  }
}
```

## 门控

- `evidence_level: "audited"` 仅在 `audit.level == "audited"` 时合法
- `check_annotations` 验证: audit 字段存在 + level 匹配 + contradictions 非空时警告
- 无 audit 字段 = unverified（不可用于门控放行）
