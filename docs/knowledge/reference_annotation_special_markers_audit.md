# annotation 层特殊标记扫描报告

**type**: reference
**created**: 2026-10-15
**来源**: 用户第一性洞察「类型衰退本身无法被 S2/L1 度量」+ 全库扫描

## 核心洞察
> **不报错 + 字节一致 ≠ 代码还原度到位**
> 类型衰退是「静默劣化」—— 代码能编、字节能对，但**还原度低**

## 标记总览（分母 ~6080 条 known_members）

| 类别 | 数量 | 占比 | 优先级 |
|---|---|---|---|
| **PDB 来源** | **~330** | 5.5% | 🔴 高 |
| **伪语义命名** | **257** | 4.2% | 🔴 高 |
| **待办标记** | **30** | 0.5% | 🟡 中 |
| **overlap（真/自动/修正）** | **15** | 0.2% | 🟡 中 |
| **`void *` 类型衰退** | **50** | 0.8% | 🟡 中 |
| **总计问题标记** | **~682** | **11.2%** | — |

## 🔴 PDB 来源标记（~330 条，CLAUDE.md 明令仅参考级）

| 标记 | 数量 | 风险 |
|---|---|---|
| `pdb_merge` | 73 | ⚠️ PDB 合并 |
| `pdb_verified_by_old_ida` | 65 | ⚠️ 旧 IDA 验证 |
| `PDB_batch_import(size_match)` | **59** | ⚠️ **PDB 批量导入**（最危险）|
| `pdb_fill_incomplete` | **43** | ⚠️ **PDB 填充不完整** |
| `PDB_verified` | 23 | ⚠️ PDB 验证 |
| `PDB+PAL3_offset_adjusted` | 20 | ⚠️ PDB + 偏移调整 |
| `PDB_PAL3_adjusted(-16_after_172)` | 14 | ⚠️ PDB + 偏移调整 |
| `(PDB-derived` / `PDB-derived` | 14 | ⚠️ PDB 派生 |
| `pdb` / `PDB` | 11 | ⚠️ PDB |
| `pdb+asm*` | 10 | ⚠️ PDB + asm 混合 |

**问题面**：PDB 来自 **PAL3A**（偏移可能与 PAL3 不同）· **不能单独作为证据**（CLAUDE.md 明令）

## 🟡 伪语义命名（257 条，T74 族，CLAUDE.md 禁止）

**形态**：地址后缀（`m_D8BEEC` · `m_nField_1080` · `_method_532710` · `_nearby_417420`）
**分布**：`ScriptSystemData` 为主（`m_nField_*` 系列）

## 🟡 待办标记（30 条）
- `annotate_todo` 29 条
- `TODO` 1 条

## 🟢 overlap 标记（15 条）

| 类型 | 数量 | 详情 | 治理 |
|---|---|---|---|
| `overlap: 4-byte workspace` | 1 | `Actor.m_InnerActor`（**真重叠**）| 保留（union 语法更优）|
| `auto:extern_overlap_*` | 2 | `ScriptSystemData.m_fTimerA/B` | 核实 |
| `codegen:global_overlap_detection` | 1 | `ScriptSystemData.g_vRotateAxis` | 核实 |
| `auto:overlap_*` | 6 | `ScriptSystemData` 全局重叠 | 核实 |
| `+fix:overlap_correct_count` | 3 | `CCBAI.m_EnemyDemand` / `m_FriendDemand` / `CCBStage.m_fDamageNumPosY` | 核实 |
| `pdb_merge+fix:overlap_correct_count` | 1 | `LineupComp.m_ObjPos` | 核实 |
| `A:LEA_*_no_overlap` | 1 | `CCBVolModNode`（**no_overlap**）| 保留 |
| `A+:decomp_*_no_overlap` | 1 | `RoleSystem._embed_UIWnd_624`（**no_overlap**）| 保留 |

## 🟢 type 衰退（50 条 `void *`）
**应语义化**（`RoleSystem *` 等）—— 质量专项阶段 2

## ✅ type: skip（0 条，已清）

## 治理建议（按 ROI）

| 序 | 治理 | 理由 | 成本 |
|---|---|---|---|
| **🥇** | **PDB 批量导入 59 条逐条 A 级验证** | CLAUDE.md 明令，最危险 | 中 |
| **🥈** | **`void *` 50 条语义化** | 类型衰退（质量专项阶段 2）| 中 |
| **🥉** | **伪语义命名 257 条语义化** | CLAUDE.md 禁止（独立大型工作流）| 高 |
| **P4** | **`auto:overlap_*` 9 条核实** | 真重叠还是误报？| 低 |
| **P5** | **`annotate_todo` 30 条判定** | 保留 `_todo_` 或语义化 | 低 |
| **P6** | **`pdb_fill_incomplete` 43 条补全/去除** | 自认不完整 | 中 |

## 扫描命令（可复现）
```bash
# PDB 来源标记
python3 -c "
import json, glob, collections, re
markers = collections.Counter()
for f in glob.glob('data/annotations/**/*.json', recursive=True):
    try: d = json.load(open(f))
    except: continue
    if not isinstance(d, dict): continue
    km = d.get('known_members')
    if not isinstance(km, dict): continue
    for k, v in km.items():
        if not isinstance(v, dict): continue
        src = v.get('source', '')
        if not src or not isinstance(src, str): continue
        for token in re.split(r'[|\\s]+', src):
            if not token: continue
            base = token.split(':')[0] if ':' in token else token
            if 'pdb' in base.lower(): markers[base] += 1
print(markers.most_common(20))
"

# 伪语义命名
python3 -c "
import json, glob, re
count = 0
for f in glob.glob('data/annotations/**/*.json', recursive=True):
    try: d = json.load(open(f))
    except: continue
    if not isinstance(d, dict): continue
    km = d.get('known_members')
    if not isinstance(km, dict): continue
    for k, v in km.items():
        if not isinstance(v, dict): continue
        name = v.get('name', '')
        if re.search(r'_[0-9A-Fa-f]{4,}$', name): count += 1
print(f'伪语义命名总数: {count}')
"
```
