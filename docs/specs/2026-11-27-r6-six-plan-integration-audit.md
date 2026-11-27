# R6 六项施工图集成复核：冲突、写域、实施顺序与一次拍板清单

日期：2026-11-27　卡：#48（tsk_01M8CPQS2G32Q1JA0PKE2V）　性质：只读

R6 六项的施工图分散在三处：#37（①③⑤）、#47（②④）、#18（⑥）。本文件只做**跨图集成**：同一类/同一成员有没有被两张图重复改、写域会不会撞、顺序怎么排、哪些必须 Human 一次拍板。

**本卡未改任何注解/代码/基线**；唯一新增是本文件。

---

## 0. 结论摘要

1. **六项目标 JSON 两两不相交**（8 个文件，见 §3.3）——没有任何一个类/成员被两张图同时改；不存在"谁为准"的裁决问题。
2. **有两组"组内强耦合"必须原子改**：② 的 `C2DSpark_tagSpark`(44B) 与 `C2DSpark`(22,640B) 是一对（元素尺寸变则宿主数组末端变）；⑥ 的 `CCCTData`(430,000) 与 `CCBCamControl`(430,256) 是一对（`m_CCT` 的类型就是前者）。
3. **基类投影无交叉**：六项目标的基类分别是 UIFrameWnd / UIListBox / (无) / UIFrameWnd / (无)；R4 正在改的 `PalScriptWaitObj` 不是它们任何一项的基类 ⇒ **R4 落地不会移动 R6 目标的布局**，两者只需在管线通道上串行。
4. **唯一的硬前置是 Human 裁决 ⑥**（D-1：PDB 说 `CCCTData` 是 430,000 池 union，twin 裁决说 402,824 类是 CCCTData）。这一项不裁，⑥ 不能开工；其余五项可动。
5. **四处现场漂移必须先重取，不能照旧数字验收**：
   - ④ PropUI 工作树已从 #47 记录的 **47 员变成 50 员**（末 4 员为 `m_titleBar@0x701C` / `m_unk_0x70B4[28]` / `m_bInitFlag@0x70D8`，另有两员新增），census 还停在 47 员/308B；
   - ① `s4_baseline` 的 L1 记录已从 189 变 **192**（sha `66c193fe…`），凡写「L1≥189」的验收都要改成「不低于落地当日实测」；
   - `struct_holes` 与 `s4_baseline` 当前均为 `M`（并发管线写），引用前必须重读；
   - #37 的 ③ 预期洞（670,520B）与 #27 原文（16B）矛盾——**以 #37 为准**（删 `m_TaskGroups` 后必然出现 670,504B 未解析区），本文件不另造数。
6. **推荐顺序（4 批）**：批 1 只读验收 ①+④ → 批 2 尺寸自闭合 ②+③ → 批 3 删成员收洞 ⑤ → 批 4 身份重铸 ⑥（等 Human）。

---

## 1. 输入与现状（本卡现读）

### 1.1 引用产物存在性（C1 全 OK）

| 文件 | 用途 |
|---|---|
| `docs/audit/2026-11-26-r6-decision-brief.md` | R6 六项终态与问题（#35，62,950B） |
| `docs/specs/2026-11-27-r6-annotation-landing-plan.md` | ①③⑤ 施工图（#37） |
| `docs/specs/2026-11-27-r6-2-4-annotation-landing-plan.md` | ②④ 施工图（#47） |
| `docs/specs/2026-11-26-ccctdata-recast-plan.md` | ⑥ 施工图/身份反证（#18） |
| `docs/specs/2026-11-27-ccbstage-size-three-numbers-evidence.md` | ③ 证据（#27） |
| `docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md` | ⑤ 证据（#24） |
| `docs/specs/2026-11-26-uititle-noteitem-layout-evidence.md` | ① 证据（#22） |
| `docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md` | ② 证据（#29） |
| `docs/specs/2026-11-27-propui-size-164-evidence.md` | ④ 证据（#31） |

### 1.2 六项目标的当前注解快照（C2）

| 项 | 类 | binary_size | 成员数 | bases | 状态 |
|---|---|---|---|---|---|
| ① | `UITitle_JDHY` | **290,488** | 43 | UIFrameWnd@0 | 工作树 `M`（已落地未提交） |
| ③ | `CCBStage` | 673,988 | 20 | UIListBox@0 | 未改 |
| ⑤ | `CCBRoleState` | 22,224 | 89 | UIListBox@0 | 未改 |
| ② | `C2DSpark` / `C2DSpark_tagSpark` | 24,688 / 48 | 20 / 12 | 无 | 未改 |
| ④ | `PropUI` | **28,892** | **50**（#47 记 47） | UIFrameWnd@0 | 工作树 `M`（已落地未提交） |
| ⑥ | `CCCTData` / `CCBCamControl` | 430,256 / 430,256 | 0 / 28 | 无 | 未改（chimera） |

### 1.3 census 与基线（C3/C4）

- `struct_holes_20261125.json`：`classes_with_holes=199`、`total_holes=1040`、`total_hole_bytes=801,950`。六项中 4 项在册：UITitle_JDHY 8B / CCBStage 36B / CCBRoleState 6,483B / PropUI **47 员/308B**（与工作树 50 员不一致）/ CCCTData 430,256B / CCBCamControl 12B；C2DSpark 与 tagSpark **不在册**（零洞类不入表，见 #47 C9）。
- `probe_census.json`（`generated_at 2026-11-27T03:49:00`）：S2 **159/230**。
- `s4_baseline.json`：`match_L1=192`、matched 1,154、symbols 1,265、sha `66c193fe51cd…`，当前 `M`。
- 两者都属派生物，**本文件引用的是 03:49 的快照**；落地卡必须当场重取。

---

## 2. 六项逐项表

| 项 | 目标 JSON | 改动类型 | size 断言（before→after） | 证据等级 | 依赖 codegen？ | 建议 writeScopes | 依赖卡 |
|---|---|---|---|---|---|---|---|
| ① | `structs/UITitle_JDHY.json` | **无成员改动**（只验收+提交） | 290,488→290,488；`m_NoteItem@0x262C8 [36]`、`m_isItemShow@0x262A4 [36]` | A（#22） | 否 | 无（只读核对）+ 提交权在 PMO | 无 |
| ③ | `structs/CCBStage.json` | 改 `binary_size`；删 `m_TaskGroups[256]@0xA8`、`m_nTodo_A48A8@0xA48A8`、`m_dwAniFlagOver@0xA48C0`；加 `m_unk_0xA3BD0 UIRoleDialog` | 673,988→672,040；成员 20→18；洞 36B→**670,520B** | A（#27） | 否（注解层；但产物重生成需跑链） | `structs/CCBStage.json` + `tests/` | 无（但需 Human 认可大洞，见 §5） |
| ⑤ | `structs/CCBRoleState.json` | 改 `binary_size`；删 23 员（15 属无名 20,644B 类、4 幻影、3 属 CCBUIPanel、1 属 PropUI） | 22,224→20,568；成员 89→66；洞 6,483→4,915B | A（#24） | 否 | `structs/CCBRoleState.json` + `tests/` | 无 |
| ② | `structs/C2DSpark.json` + `structs/C2DSpark_tagSpark.json` | 改两个 `binary_size`；tagSpark 48→44 删 `0x2C pRenderEffect`；C2DSpark 19 个尾员统一 −0x800 | 24,688→22,640；48→44；`512×44=0x5800`+`0x70`=0x5870 | A（#29） | 否 | 两个 JSON + `tests/` | 无（但需 Human 认可语义后置，见 §5） |
| ④ | `structs/PropUI.json` | **已落地**（HEAD 95 员/29,056 → 工作树 50 员/28,892） | 29,056→28,892；164=52+16+96 已消 | A（#31） | 否 | 无（验收+提交） | 无（但需按 50 员重验） |
| ⑥ | `structs/CCCTData.json` + `structs/CCBCamControl.json` | **待 Human 裁决**：P-1＝CCCTData 430,256→430,000（3 员：池 2000×204 + 位图 + 索引）、CCBCamControl 去池三员加 `m_CCT: CCCTData@0`；P-2＝CCCTData→402,824 类 Y | P-1：430,000 + 430,256 不变；P-2：402,824 | PDB A（#18），twin 裁决冲突（D-1） | P-1 否；P-2 需新建类+15 方法迁移（仍注解层） | P-1：两个 JSON + `functions.json`（15 条方法归属）；P-2：另加新建 `CCCTData.json` 类名与类 Y 类文件 | Human 裁决 D-1 |

> 「依赖 codegen」一列：六项都**不需要改 `pipeline/gen`**；但都要重新生成产物（apply→export→codegen），因此都需要管线通道。

---

## 3. 交叉检查

### 3.1 同一类 / 同一成员是否被两张图重复改

**没有。** 六项落在 8 个互不相同的 JSON 上（§3.3），成员级也无交集：

- ① 的 `m_NoteItem`/`m_isItemShow` 只在 UITitle_JDHY；
- ③ 的 `m_TaskGroups`/`m_nTodo_A48A8`/`m_dwAniFlagOver` 只在 CCBStage；
- ⑤ 被删的 23 员只在 CCBRoleState（其中 1 员 `0x56CC m_BattleFlags` 属 PropUI，是**跨类误挂**，不是与 ④ 的改动冲突——④ 改的是 PropUI 尾部 0x6FB8 之后，0x56CC 在中间，不受影响）；
- ② 的 tagSpark 元素成员与 ④ 的 PropUI 尾部无关；
- ⑥ 的 CCCTData/CCBCamControl 与其他五项无交集。

⇒ 不存在「谁为准」，只需处理**组内**耦合（②的两文件、⑥的两文件）。

### 3.2 同一基类投影是否被不同项同时改

| 基类 | 被哪些项影响 | 结论 |
|---|---|---|
| `UIFrameWnd`（72B） | ①、④ | 两项都只改**自身** `binary_size`/尾部成员，不改基类；UIFrameWnd 大小不变 |
| `UIListBox`（72B） | ③、⑤ | 同上，不改基类 |
| 无基类 | ②、⑥ | — |
| `PalScriptWaitObj`（R4/#45 正在改） | 六项**都不继承**它 | R4 只影响 ScreenEffect 族（ScreenEffect/四个 Fade/ScreenEffectMgr/Role），与 R6 目标布局无交集 |

⇒ **无基类投影冲突**。R4 的 `Role 8708→8704`（#43 实测）也不落在六项目标内。

### 3.3 写域矩阵

六项目标文件（8 个）：`UITitle_JDHY.json`、`CCBStage.json`、`CCBRoleState.json`、`C2DSpark.json`、`C2DSpark_tagSpark.json`、`PropUI.json`、`CCCTData.json`、`CCBCamControl.json` —— 两两不相交，且都落在 `data/annotations/structs/` 下**具体文件**。

风险面：
- 若某张卡把 writeScopes 写成整个 `data/annotations/structs/` 目录，就会与其余五个批次全部重叠 ⇒ **开卡时必须写具体文件名**。
- `tests/` 是公共写域：②③⑤ 都要加断言，建议**各自新建独立测试文件**（如 `tests/test_r6_c2dspark_sizes.py`），避免同时改同一个 test 文件。
- ⑥ P-1 还要动 `data/annotations/functions.json`（15 条方法归属）——该文件其他卡也可能碰，需在卡面注明「只改这 15 个地址的 owner 字段」。

### 3.4 管线通道（与 #45/R4 的串行）

- `#45`（R4 fade 落地，玄策）当前 **in_progress**，writeScopes 是五个 fade/Mgr JSON + `tests/`。
- R6 任一项落地都要跑 `apply→export→codegen→probe→match`；`apply` 会写 IDB、`export` 会重写 `asm/pal3/decomp`/`ida_structs.json`、`codegen` 会重写 `pal3/src`、`probe`/`match` 会重写 census/基线 ⇒ **同一时刻只能有一个卡在跑**。
- 顺序建议：**先让 #45 收口并验收**（它还在 in_progress），再开 R6 批 2/3；否则 R4 的 PSWO 改动与 R6 的注解改动会混在同一轮读数里，退化无法归因。

---

## 4. 统一实施顺序（4 批）

### 批 1：只读验收 ① + ④（可并行，不占管线）

| 项 | 前置 | 验收命令/读数 | 风险 | 回退 |
|---|---|---|---|---|
| ① UITitle_JDHY | 无 | `audit_type_layout.py --only UITitle_JDHY`；`cli.py check`；确认 43 员/290,488、`m_NoteItem@0x262C8` | 工作树 `M` 是他人改动，别 `git checkout`（会退回 377,700 旧布局） | 不适用（只读） |
| ④ PropUI | **先重取当前成员快照**（47→50 员） | `audit_type_layout.py --only PropUI`；`check`；确认 28,892 且末员 `m_bInitFlag@0x70D8` | census 仍是 47 员，按 census 验会误判 | 不适用（只读） |

### 批 2：尺寸自闭合 ② + ③（写域不重叠，但共用管线 ⇒ 分两轮或一轮同跑）

| 项 | 前置 | 验收命令/读数 | 风险 | 回退 |
|---|---|---|---|---|
| ② C2DSpark/tagSpark | Human 认可「语义后置」 | `audit_type_layout --only C2DSpark,C2DSpark_tagSpark`；静态断言 22,640/44、0x5800/0x5848；`check` 无新错 | 改后 512 元素访问整体位移，S2 可能按单元变化 | 两 JSON 一起 `git checkout`（不可只回一个） |
| ③ CCBStage | Human 认可「670,520B 洞」 | 同上 --only CCBStage；断言 672,040/18 员/末员 `m_unk_0xA3BD0` | 删 `m_TaskGroups` 后 670KB 未解析；`check` 不会报错但 census 会显著变大 | 单 JSON checkout |

### 批 3：删成员收洞 ⑤

| 项 | 前置 | 验收 | 风险 | 回退 |
|---|---|---|---|---|
| ⑤ CCBRoleState | 批 2 收口（读数归因清晰） | `audit_type_layout --only CCBRoleState`；断言 20,568/66 员/洞 4,915B；全链读数不低于批 2 后值 | 删 15 员会丢 20,644B 类的唯一线索（仅存于 #24 报告） | 单 JSON checkout |

### 批 4：身份重铸 ⑥（等 Human）

| 项 | 前置 | 验收 | 风险 | 回退 |
|---|---|---|---|---|
| ⑥ P-1（推荐） | Human 改 R6⑥ 身份句 | CCCTData→430,000/3 员；CCBCamControl→26 员含 `m_CCT`；`check`；census 洞 430,256→0 | 两 JSON 必须同批；15 条方法 owner 迁移 | 两 JSON + `functions.json` 一起回退 |
| ⑥ P-2（若坚持 twin） | Human 重写卡面 | 需新建 402,824 类并迁 15 方法；与 PDB 冲突需在卡面注明 | 与 PDB 直接冲突，验收无法自洽 | 不建议 |

---

## 5. Human 一次拍板清单（5 问）

| # | 问题 | 选项 | 影响 |
|---|---|---|---|
| 1 | **⑥ 的身份句**：采信 PDB（`CCCTData`=430,000 池 union，402,824 类是未名 UIListBox 派生类）还是维持 twin 裁决（402,824 类=CCCTData）？ | A=P-1（推荐，PDB 三重证据）；B=P-2（重写卡面，补类 Y 成员/方法/dtor） | A：⑥ 可开工，另开「402,824 类命名」卡；B：⑥ 需先推翻 PDB 或承认注解/PDB 分叉，工期显著变长 |
| 2 | **③ 是否接受先改尺寸、留 670,520B 洞**？ | A=先尺寸后成员（本图方案）；B=先开 B 的正名卡+成员重建卡，再改尺寸 | A：一轮落地、洞变大；B：多两轮、但洞可解释 |
| 3 | **⑤ 是否接受先删 15 员**、把 20,644B 类留成无名洞？ | A=先删（洞 6,483→4,915）；B=先给 20,644B 类命名再删 | A：快、但丢失该类的唯一线索；B：稳、多一轮 |
| 4 | **② 是否接受先尺寸/偏移、tagSpark 元素语义另卡**？ | A=先尺寸；B=先重建 tagSpark 成员语义再改尺寸 | A：尺寸立刻闭合，但元素名仍全是伪语义；B：更彻底、但②的 A 级证据只覆盖尺寸 |
| 5 | **①④ 是否现在验收并提交**（两份都是他人留在工作树的 `M`）？ | A=现在验收+提交；B=等各自 owner 提交；C=继续留在工作树 | A：证据已齐、风险低；但提交权在 PMO，且 ④ 已从 47 变 50 员，需按 50 重验 |

---

## 6. PMO 开卡建议（不实际开卡）

| 卡 | 主题 | owner 角色 | writeScopes | blockedBy | 验收要点 |
|---|---|---|---|---|---|
| R6-a | ② C2DSpark/tagSpark 落地 | coder | `data/annotations/structs/C2DSpark.json`、`C2DSpark_tagSpark.json`、`tests/test_r6_c2dspark_sizes.py` | Human 批 §5-4（A） | sizeof 22,640/44；尾员 0x5800/0x5848；全链不退化 |
| R6-b | ③ CCBStage 落地 | coder | `data/annotations/structs/CCBStage.json`、`tests/test_r6_ccbstage_size.py` | Human 批 §5-2 | 672,040/18 员；洞 670,520B 记录在案 |
| R6-c | ⑤ CCBRoleState 落地 | coder | `data/annotations/structs/CCBRoleState.json`、`tests/test_r6_ccbrolestate_size.py` | Human 批 §5-3；R6-a/b 收口 | 20,568/66 员；洞 4,915B |
| R6-d | ⑥ CCCTData/CCBCamControl 重铸（P-1） | coder | `data/annotations/structs/CCCTData.json`、`CCBCamControl.json`、`data/annotations/functions.json`、`tests/test_r6_ccctdata_pool.py` | Human 批 §5-1（A） | 430,000/3 员；430,256/26 员含 m_CCT；洞归零 |
| R6-e | tagSpark / PropUI 尾部语义化 | researcher | 两个 JSON（各自另卡） | 无 | 逐成员使用点证据；禁用 slot_N/伪语义 |

**不建议**把 ②③⑤ 合成一张大卡：写域虽不重叠，但读数无法归因，回退会连带。

---

## 7. 复现命令与原样输出

### C1 九份输入产物存在性

```bash
for f in docs/audit/2026-11-26-r6-decision-brief.md \
  docs/specs/2026-11-27-r6-annotation-landing-plan.md \
  docs/specs/2026-11-27-r6-2-4-annotation-landing-plan.md \
  docs/specs/2026-11-26-ccctdata-recast-plan.md \
  docs/specs/2026-11-27-ccbstage-size-three-numbers-evidence.md \
  docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md \
  docs/specs/2026-11-26-uititle-noteitem-layout-evidence.md \
  docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md \
  docs/specs/2026-11-27-propui-size-164-evidence.md; do
  test -f "$f" && echo "OK $f" || echo "MISSING $f"
done
```

```text
OK docs/audit/2026-11-26-r6-decision-brief.md
OK docs/specs/2026-11-27-r6-annotation-landing-plan.md
OK docs/specs/2026-11-27-r6-2-4-annotation-landing-plan.md
OK docs/specs/2026-11-26-ccctdata-recast-plan.md
OK docs/specs/2026-11-27-ccbstage-size-three-numbers-evidence.md
OK docs/specs/2026-11-26-ccbrolestate-ctor-boundary-evidence.md
OK docs/specs/2026-11-26-uititle-noteitem-layout-evidence.md
OK docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md
OK docs/specs/2026-11-27-propui-size-164-evidence.md
```

### C2 六项目标注解快照

```bash
python3 - <<'PY'
import json
for c in ['UITitle_JDHY','CCBStage','CCBRoleState','C2DSpark','C2DSpark_tagSpark','PropUI','CCCTData','CCBCamControl']:
    d=json.load(open('data/annotations/structs/%s.json'%c))
    print('%-18s size=%-7s members=%-3s bases=%s' % (c, d.get('binary_size'), len(d.get('known_members',{})), d.get('bases')))
PY
```

```text
UITitle_JDHY       size=290488  members=43  bases=[{'name': 'UIFrameWnd', 'offset': 0}]
CCBStage           size=673988  members=20  bases=[{'name': 'UIListBox', 'offset': 0}]
CCBRoleState       size=22224   members=89  bases=[{'name': 'UIListBox', 'offset': 0}]
C2DSpark           size=24688   members=20  bases=None
C2DSpark_tagSpark  size=48      members=12  bases=None
PropUI             size=28892   members=50  bases=[{'name': 'UIFrameWnd', 'offset': 0}]
CCCTData           size=430256  members=0   bases=None
CCBCamControl      size=430256  members=28  bases=None
```

### C3 census 条目（六项中在册者）

```bash
python3 - <<'PY'
import json
h=json.load(open('data/status/struct_holes_20261125.json'))
m={c['cls']:c for c in h['classes']}
for k in ['UITitle_JDHY','CCBStage','CCBRoleState','C2DSpark','C2DSpark_tagSpark','PropUI','CCCTData','CCBCamControl']:
    c=m.get(k)
    print(k, (c['size'], c['members'], c['hole_bytes'], len(c['holes'])) if c else 'ABSENT')
print('meta', h['_meta'].get('classes_with_holes'), h['_meta'].get('total_holes'), h['_meta'].get('total_hole_bytes'))
PY
```

```text
UITitle_JDHY (290488, 43, 8, 1)
CCBStage (673988, 20, 36, 2)
CCBRoleState (22224, 89, 6483, 27)
C2DSpark ABSENT
C2DSpark_tagSpark ABSENT
PropUI (28892, 47, 308, 13)
CCCTData (430256, 0, 430256, 1)
CCBCamControl (430256, 28, 12, 1)
meta 199 1040 801950
```

### C4 基线读数（同一快照）

```bash
python3 - <<'PY'
import json,hashlib
b=open('data/status/s4_baseline.json','rb').read(); d=json.loads(b)
print('L1',d['stats']['match_L1'],'matched',d['stats']['matched'],'symbols',d['stats']['symbols'],'sha',hashlib.sha256(b).hexdigest()[:12])
pc=json.load(open('data/status/probe_census.json'))
print('s2',pc['s2']['ok'],'/',pc['s2']['total'],'generated_at',pc['generated_at'])
PY
```

```text
L1 192 matched 1154 symbols 1265 sha 66c193fe51cd
s2 159 / 230 generated_at 2026-11-27T03:49:00
```

### C5 写域交集（应为空）

```bash
python3 - <<'PY'
sets={
 '①UITitle':{'UITitle_JDHY.json'},
 '③CCBStage':{'CCBStage.json'},
 '⑤CCBRoleState':{'CCBRoleState.json'},
 '②C2DSpark':{'C2DSpark.json','C2DSpark_tagSpark.json'},
 '④PropUI':{'PropUI.json'},
 '⑥CCCTData':{'CCCTData.json','CCBCamControl.json'},
}
ks=list(sets)
for i in range(len(ks)):
    for j in range(i+1,len(ks)):
        inter=sets[ks[i]] & sets[ks[j]]
        if inter: print('OVERLAP',ks[i],ks[j],inter)
print('pairs_checked', len(ks)*(len(ks)-1)//2)
PY
```

```text
pairs_checked 15
```

### C6 与 R4 的基类交集（应为空）

```bash
python3 - <<'PY'
import json
r6=['UITitle_JDHY','CCBStage','CCBRoleState','C2DSpark','PropUI','CCCTData','CCBCamControl']
for c in r6:
    d=json.load(open('data/annotations/structs/%s.json'%c))
    bn=[b['name'] for b in (d.get('bases') or [])]
    print(c, bn, 'PSWO' if 'PalScriptWaitObj' in bn else '')
PY
```

```text
UITitle_JDHY ['UIFrameWnd']
CCBStage ['UIListBox']
CCBRoleState ['UIListBox']
C2DSpark []
PropUI ['UIFrameWnd']
CCCTData []
CCBCamControl []
```

---

## 8. 边界与未覆盖

- 本卡只读：未改任何注解/代码/基线；唯一新增是本文件（`git status` 见 §7 外单独核验）。
- **未做的事**：没有重跑 apply/export/codegen/probe/match；没有替 Human 裁决 ⑥；没有给出 ③ 的成员重建方案（属另卡）。
- **被本卡挂起的已知问题**：④ 的 47→50 员漂移（需 #31 owner 或 PMO 确认哪版为准）；census 的 PropUI 47 员为过期数据；`s4_baseline` L1=192 与 #37/#39/#43 文中 189 的历史值不一致（以 192 为准）。
- 若后续任一批次落地，验收读数必须以**当轮** `probe_census`/`s4_baseline` 为准，不得复用本文件的 03:49 快照。
