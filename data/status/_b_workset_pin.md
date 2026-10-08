# B 批工作集钉死（Step 2 产物，2026-09-27）

对象：`data/status/type_evidence_report.json`（type_evidence v2 全量 dry-run，W=715）。
本文件钉死工作集口径、对账"211"俗数、给出分级全貌与产出解释。
（数字待 ff86c62f 修复轮对抗复核收敛后终稿；如有修订在文末追加修订记录。）

## 1. 工作集 W 口径（写死，来自两轮复核裁定）
```
W = { (cls, off) |
      cls ∈ globals_partition.top_levels 的容器类（type ≠ unknown）；
      off ∈ structs/cls.json known_members 键（'0x' 前缀按 16 进制，否则 10 进制）；
      成员当前 type ∈ {int, unsigned int, _DWORD, __int32, unsigned __int32} }
```
- **W = 715 个 / 26 类**（ScriptSystemData 119 · tagEffMgrData 93 · CGameData 65 ·
  RoleSystem 64 · PAL3 49 · tagCombatTaskData 48 · CScreenMode 42 · Actor 37 · 其余 18 类 238）。
- B2 census 行**不进 W**（与 known_member 是同一批字节的两种视图）；仅作旁证列（b2_ref）。
- 多实例类按**全部实例 VA** 取证（RoleSystem×5 / PAL3×2 / Array×4 …；PAL3 21 个成员
  曾因单实例取证误判，已修复）。
- 同偏移多键显式报 dup，不静默覆盖（实测 0 处 in W）。

## 2. "211"俗数对账（delta 说明）
- **211 不可复现**。可复现的近似口径：B2 行 type=int = **226**；B2 行 type∈占位集 = **231**。
  "211"应是早期某次 census 快照的口径漂移数，无当前定义与之对应。
- 注：本次 dry-run 的 grade-0（零证据）计数恰为 211，纯撞数，非该俗数出处。
- 与 W=715 的关系：715 是**容器 known_members 占位成员**（可被 T1/T2 取证的最小可写单元）；
  226/231 是 **B2 census 行**（容器外/无 known_member 的 extern 视角，属 **C 批**成员化对象）。
  两者分属 B/C 两批，不可混算。

## 3. 分级全貌（W=715）
| 级 | 计数 | 含义 | 动作 |
|---|---|---|---|
| A | 203 | 多站点一致证据 | 其中 196 = WIDTH-4-MATCHED（宽度已正确，无动作）；**7 = 可落盘 float** |
| B | 298 | 单站点/符号不可证/仅 T2/double | 只报告（含 4 条 float 人工裁定池） |
| C | 3 | 真冲突 | 报告不落盘（3 条全是整型多宽度混用） |
| 0 | 211 | 无证据 | 不动 |

按类（总/A/B/C/0/W4M/提案）：ScriptSystemData 119/25/3/2/89/25/0 · tagEffMgrData 93/0/93/0/0/0/0 ·
CGameData 65/10/29/0/26/10/0 · RoleSystem 64/3/44/0/17/3/0 · PAL3 49/15/10/0/24/8/9 ·
tagCombatTaskData 48/48/0/0/0/48/0 · CScreenMode 42/0/36/0/6/0/0 · Actor 37/0/30/0/7/0/0 ·
SceneMgr 20/6/2/1/11/6/0 · tagEffSParticleSys 16/14/2/0/0/14/2 · 其余 16 类见报告。

## 4. 产出解释（为什么不是"211 个填充"）
- **可落盘 7 条**（全 PAL3 +0x1358..+0x1380 连续 float 数组块 + m_nEffObjCount，
  fadd/fmul/fld/fstp 数理运算证据，双实例 VA 取证）。
- **196 条 WIDTH-4-MATCHED**：4B 整型触碰 ⇒ 占位 int 的**宽度**已正确；int/float/指针
  不可分（仓规：类型最多证到宽度+int/float/指针+符号）⇒ 无动作，不是漏做。
- **298 条 B**：主因 (a) 单站点不落盘（多站点规则）；(b) 1/2B 字节缺 movzx/movsx 符号证据；
  (c) tagEffMgrData 93 全 B——实测其 T1 站点 **225/225 全为地址物化**（mov ecx,offset /
  push 形态，0 个宽度证据），93/93 另有 T2 渲染佐证但 T2 不单独定型——是"经指针访问"
  形态（T1 单源实测覆盖 25-30%，与信号地图一致）；
  (d) double 提案 v1 禁填（布局高危 4→8）。
- **解锁路径**：T1b（this+disp32）补方法类盲区；符号位证据（movzx/movsx 流）解锁 1/2B 填充；
  人工裁定池 4 条 float（tagEffSParticleSys 2 条带 imm 位型旁证 0xc2480000=-50.0f）。
- **批量定型的真实主场在 C 批**：392 个缺口成员（CEffMgr 263/SceneMgr 129）新增时
  按 T1 证据直接定型（预实测可及率 75%/93%，见 _c_batch_t1_premeasure.md）。

## 5. 门禁与后续
- Step 3 落盘链（每类一批）：emit_batch 产守卫批次 → `apply_annotation_batch --dry-run` →
  落盘 → annotation_diff → **apply→export（不回灌不进生成头！）** → codegen →
  `audit_type_layout --only <Cls>` → `verify_fix --class <Cls>` → 四道门。
- 逐步对抗复核（用户纪律）：修复轮复核（ff86c62f）→ Step 3 实现 → 复核 → Step 4 收官 → 复核。

## 修订记录
- （待 ff86c62f 收敛后填写）
