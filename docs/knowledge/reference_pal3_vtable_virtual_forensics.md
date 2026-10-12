# reference · PAL3 `virtual` 注入 / vtable 映射 / 偏移基准 法证（captain 5 轮独立复核）

**type**: reference
**created**: 2026-10-10（Goal Round 15-19）
**status**: 病灶链已定位，T2 实施前必读
**related**: `decision_byte_match_is_goal_judges_may_improve.md` · `reference_p0_p1_p2_prep_analysis.md`

## 病灶链（自下游到上游，5 轮逐步上溯）

```
[下游] PAL3.h:113 出现 `virtual int SceneUpdate(int, int); // 0x0044F4C0`
   ↑ emit_headers.py:2466 标 virtual（vtable 映射驱动）
   ↑ emit_headers.py:2490「vtable 映射完整性：每个 vtable 槽位都要有 virtual 声明」
   ↑ emit_headers.py:2481-2486  `_all_vtable_slots` 来源：
        优先 _read_vtable_from_binary(_get_vtable_addr(cls))   ← 二进制
        fallback class_vtable_slots(cls_name)                   ← annotation/IDB
   ↑ emit_headers.py:451-468 `_get_vtable_addr` 来源：
        ① _get_ida_structs()[cls].vtables[0].addr              ← IDB 导出（真源）
        ② data/annotations/structs/<Cls>.json 的 vtables        ← fallback
[上游] 病灶源：_get_ida_structs() 里 PAL3 的 vtables 映射
```

## 五轮复核抓到的问题（每条附证据）

| # | 发现 | 证据 |
|---|---|---|
| 1 | **病灶层定位错误**：`virtual` 是 codegen 注入，**非 annotation** | `structs/PAL3.json` 里 `virtual` 出现 **0 次** |
| 2 | **量化数字不一致**：T1 说「87/87」，实测 **58/57** | `audit_type_layout.py --only PAL3` 输出 |
| 3 | **假阳性混入**：「冲突 58 > 成员 57」 | `audit_type_layout.py:52-57` docstring：「对嵌套成员做 `offsetof` **本就不合法** ⇒ 假冲突」 |
| 4 | **`virtual` 判定机制**：vtable 映射驱动 | `emit_headers.py:2490` |
| 5 | **病灶再上溯**：源在 IDB 导出，非 annotation 文件 | `data/annotations/structs/PAL3.json` **无 `vtables` 字段** |
| 6 | **🔴 `known_members` 越界 3 倍** | 最大偏移 `0x3996 = 14,742` vs `binary_size = 4936` |

## 可信结论分级（T2 实施前按此裁决）

| 结论 | 可信度 | 说明 |
|---|---|---|
| `virtual SceneUpdate` ⇒ vptr ⇒ 全员偏移 +8 | ✅ **高** | 因果链双侧独立确认 |
| 57 methods 受阻 | ✅ **高** | `structs/PAL3.json` 的 `methods` 字段是实的 |
| 「修一处解锁 57 方法」 | ⚠️ **待重估** | 受假阳性影响 |
| 逐成员冲突计数（58/87） | ⚠️ **含假阳性** | **不可作量化依据** |
| 「87 成员偏移错 = virtual 单一因」 | 🔴 **存疑** | `known_members` 越界 3 倍 ⇒ 可能另有成员归属错误 |

## T2 实施前必答（第 6 项，决定性）

1. `_get_ida_structs()` 从哪个文件/哪次导出读？（疑 `asm/pal3/ida_structs.json`）
2. 里面 PAL3 的 `vtables` 是否含 `SceneUpdate @ 0x44F4C0`？**谁写进去的**？
3. **`known_members` 越界 3 倍**是什么？（疑部分成员是**别的类/继承链**被误塞进 PAL3）

**⚠️ 若第 3 项成立**，则 T2 不是「去 virtual / 改偏移基准」二选一，而是**三处都要修**：
`vtables` 映射（去 SceneUpdate）· `known_members`（剔除越界成员）· codegen（可选，加防御）。

## 方法论注

**「每步对抗复核」的直接收益**：5 轮复核抓到 6 个问题，其中 2 个是**会让 T2 全白做**的（病灶层错 / 越界 3 倍）。
`diagnoser` 在查 objdump（二进制侧），captain 在查 annotation/生成头（注解侧）—— **两侧交叉**才抓到病灶层错位。
