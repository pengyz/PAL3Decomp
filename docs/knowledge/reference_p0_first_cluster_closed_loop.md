# reference · P0 首个冲突簇闭环（PAL3：误归属 → uniform +8 平移）

**type**: reference
**created**: 2026-10-12（Goal Round 22-39）
**status**: 已闭环，P0 可复制此模式到其他冲突簇
**related**: `reference_pal3_vtable_virtual_forensics.md` · `decision_byte_match_is_goal_judges_may_improve.md`

## 一句话
**1 个 decomp JSON 的 1 个字段**（`name`）修复了 PAL3 类 **57/57 成员偏移错 + 57 个方法受阻**。

## 病灶链（最终版）
```
asm/pal3/decomp/PAL3_SceneUpdateint_int_0044f4c0.json
  name: 'PAL3::SceneUpdate(int,int)'      ← 误归属（真身 CGameData）
  signature: 'virtual int __thiscall(PAL3 *this, ...)'  ← 症状（virtual 从 name 归属推）
        ↓ emit_headers 按 name 聚合方法到 PAL3
        ↓ virtual ⇒ vptr@0 ⇒ MSVC6 对 double 对齐插 4B padding
        ↓ 全员偏移 +8（uniform shift）
        ↓ 57/57 成员偏移错 + sizeof(PAL3) 4944 vs binary_size 4936
```

## A 级证据（objdump + decomp 自证）
| # | |
|---|---|
| **E1** | `0x405649 mov ecx,0xdb9fd0` + `0x40564e call 0x44f4c0` ⇒ `this = g_gamefrm`（非 PAL3 实例 `0x8acbf0`）|
| **E2** | `0x44f51d mov ecx,[esi+0x6e10]`，`0x6e10=28176 > 4936=PAL3.size` |
| **E3** | 函数体 `CGameData::Load((CGameData*)this, ...)` 显式 cast |
| **E4** | `CGameData.json` 有 `0x0044F4C0 SceneUpdate`（`source:'vtable_migrated'`, `ordinal:2`）· `CGameData.binary_size=28268 > 28176` ✓ |

## 修法（B：改归属，爆炸半径 1 字段）
```python
# 唯一改动
asm/pal3/decomp/PAL3_SceneUpdateint_int_0044f4c0.json
  name: 'PAL3::SceneUpdate(int,int)'  →  'CGameData::SceneUpdate(int,int)'
# + 2 处 decompiled_c 的名字重写（调用点旧名残留）
asm/pal3/decomp/PAL3_Updatefloat_004055d0.json
asm/pal3/decomp/PAL3_SceneUpdateint_int_0044f4c0.json
# PAL3::SceneUpdate → CGameData::SceneUpdate（只替换完整限定名，UISceneUpdate 未动）
```

## 四层检查点（P0 闭环的验收判据）
| 层 | 检查 | 结果 |
|---|---|---|
| **L1 数据层** | decomp JSON `name` = `CGameData::SceneUpdate(int,int)` | ✅ |
| **L2.5 调用点层** | `PAL3.cpp` 无 `PAL3::SceneUpdate`（codegen 后）| ✅ 0 |
| **L2 生成层** | `PAL3.h` 0 · `Data/CGameData.h` 1（⚠️ 路径是 `Data/` 不是 `GameBase/`）| ✅ |
| **L3 门禁层** | `audit_type_layout --only PAL3` | ✅ **58/57 → 1/57**（仅 `__tail_drift__` 伪成员）|

## P0 效果实测
| | 前 | 后 |
|---|---|---|
| 真布局冲突 | **57/57（100%）** | ✅ **0/57** |
| uniform +8 平移 | 全员偏移错 | ✅ 完全消失 |
| `sizeof(PAL3)` | 4944 | ✅ **4936**（= `binary_size`）|
| 可解锁方法 | — | **57 个** |

## 🎯 复制此模式到其他冲突簇（P0 的扩展路径）
1. **找误归属**：`E3` 模式扫 decomp JSON（`X::Y((X*)this)` 且 X ≠ name 类）
   —— 实测 569 候选（太宽，含正常基类/成员 cast）
2. **严过滤**：name 类 `binary_size` < cast 类的 ⇒ **253 候选**（top：`CCBRoleState→PAL_GDB` 12 个）
3. **逐个 A 级取证**（objdump 调用点 this 来源 + 函数体 cast + 目标类 methods/size）
4. **走 B 修法**（改 `name`）+ **同步 `decompiled_c` 调用点旧名**
5. **四层检查点**验收

## ⚠️ 已知坑（本闭环踩过）
| 坑 | 教训 |
|---|---|
| **修法 A（剥 `virtual`）会破坏 451 个真虚方法** | 452 个 decomp JSON 的 signature 带 `virtual`，绝大多数是正常的 |
| **检查点路径写错**（`GameBase/` 应为 `Data/`）| **检查点本身要验对对象** |
| **检查点没说须 codegen 后验** | 改 decomp JSON 后生成头不会自动更新 |
| **调用点旧名残留** | 改 `name` 不影响 `decompiled_c` ⇒ 会编译失败 |
| **并发 codegen 互删 `pal3/src`** | R1：编排者不得在子代理 running 期间动同一写入面 |
