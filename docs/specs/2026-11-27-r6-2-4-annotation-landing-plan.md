# R6②④ 注解落地施工图：C2DSpark 22,640/44 与 PropUI 差 164

日期：2026-11-27　卡：#47（tsk_01M8CNM0YZ9YDZBH65YHBD）　性质：只读施工图（不改仓库）

R6 六项里，①③⑤#37 已给施工图、⑥ #18 已给，② 与 ④ 只有取证。本文件只回答：**改哪个 JSON 的哪个字段、删/移哪些成员、怎么验、风险在哪、先做哪件**。

**本卡未改任何注解/代码/基线**；唯一新增是本文件。

---

## 0. 摘要（先看这一节）

| 项 | 真值（等级） | 当前注解（工作树） | 差距 | 本施工图动作 |
|---|---|---|---|---|
| ② C2DSpark | **22,640 / 0x5870**（A，#29） | 24,688 / 20 员 / 末员末端 0x6070 | 尺寸 +2,048；`m_Spark` 元素 48（真值 44） | 改 `C2DSpark.json`、`C2DSpark_tagSpark.json` 两个文件：尺寸、19 个尾员 −0x800、元素尺寸 48→44 并删 1 个越界成员 |
| ② tagSpark | **44 / 0x2C**（A，#29） | 48 / 12 员 / `pRenderEffect@0x2C` 末端 0x30 | 尺寸 +4；末员越界 | 删 `0x2C pRenderEffect`，尺寸 44 |
| ④ PropUI | **28,892 / 0x70DC**（A，#31） | **28,892 / 47 员**（工作树已改，`M`，mtime 03:28:43） | 已一致 | **不重复改**：本文件给「核对 + 验收 + 提交边界」；HEAD 仍是 29,056/95 |

推荐顺序：**④ 先验收（改动已在工作树）→ ② 在独占管线窗口落地**。② 与 ④ 无相互依赖，但都必须避开 #45 正在占的管线通道（apply/export/codegen/probe/match）。

必须 Human/PMO 决定的点（§6）：② 是否同意「先改尺寸与成员偏移、元素成员的语义名另卡」；④ 是否接受当前 `m_unk_0x70B4[28]` 的留白式表达（不先做 11 个标量的语义化）。

---

## 1. 输入与当前状态

### 1.1 引用的既有产物（逐条 `test -f` 通过）

| 文件 | 用途 | 存在 |
|---|---|---|
| `docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md` | ② 证据（#29，418 行） | ✅ |
| `docs/specs/2026-11-27-propui-size-164-evidence.md` | ④ 证据（#31，333 行） | ✅ |
| `docs/audit/2026-11-26-r6-decision-brief.md` | R6 终态表（#35，`②` 在 `:58-80`、`④` 在 `:112-129`） | ✅ |
| `docs/specs/2026-11-27-r6-annotation-landing-plan.md` | ①③⑤ 施工图格式（#37） | ✅ |
| `docs/specs/2026-11-27-r4-screenfade-landing-plan.md` | R4 fade 落地施工图（#39，384 行） | ✅ |

**与 #39 的对账**：无文件、无类重叠——#39 改的是 `PalScriptWaitObj`/`ScreenEffect`/四个 `ScreenFade*`/`ScreenEffectMgr`（`data/annotations/structs/` 下 6 个 JSON），②④ 改的是 `C2DSpark`/`C2DSpark_tagSpark`/`PropUI`（3 个 JSON），交集为空；唯一耦合是**管线通道**（都要跑 apply/export/codegen/probe/match），必须与 #45/#39 串行（见 §4）。#39 的三条断言（PSWO 8、ScreenEffect 24 且 m_nType@8、Mgr 152）与本文件无引用关系，故不重复、不借其数字。

### 1.2 当前注解实况（本卡现读）

| 类 | 工作树 | HEAD | 文件状态 |
|---|---|---|---|
| `C2DSpark` | binary_size **24688**、20 员 | 24688、20 员 | 未改（mtime 11-18 18:41） |
| `C2DSpark_tagSpark` | binary_size **48**、12 员 | 48、12 员 | 未改（mtime 11-16 21:22） |
| `PropUI` | binary_size **28892**、**47 员** | 29056、95 员 | **`M`（已改未提交，mtime 03:28:43）** |

- `C2DSpark` 在 `data/annotations/structs/CCBSystem.json:0x34` 只以 **指针** `C2DSpark * m_p2DSpark` 出现 ⇒ 尺寸变化**不级联**任何其他类的 sizeof。
- `C2DSpark` / `C2DSpark_tagSpark` 都不在 census 类列表里（当前 `struct_holes` 的 `classes_with_holes=199`、`total_hole_bytes=801,950`）。注意 census **只登记有洞的类**：`classes` 是长度为 199 的列表、`classes_with_holes` 同为 199，两者相等即为证据（C9 实测）。⇒ 落地后二者洞为 0，**不会**新增条目，`classes_with_holes` 保持 199、`total_hole_bytes` 不变；若按「新增两个 0 洞条目」验收会误判失败。

---

## 2. ② C2DSpark / tagSpark 施工图

### 2.1 目标与证据链（A 级，三条独立闭合）

| 证据 | 内容 | 位置 |
|---|---|---|
| 唯一分配 | `push 0x5870`(=22,640) → `call 0x55353B`(operator new) → `mov ecx,eax` → `call 0x4D5AB0`(ctor) → `mov [esi+0x34],eax` | `data/status/_disasm_cache.txt`：`0x512AE1` / `0x512AF0` / `0x512B1B` / `0x512B30` |
| ctor 清零常量 | `mov ecx,0x161C` + `rep stos` = 0x161C×4 = **22,640** | ctor `0x4D5AB0` |
| ctor 最大写界 | 最远写 `mov [esi+0x586C]`（两处 `0xFFFFFFFF`），终点 `0x5870` | `0x4D5ACB` / `0x4D5D77` |
| 元素步长 ×3 | `add ecx/edi,0x2C`（44），计数 `0x200`（512），`mov ecx,0xB; rep movs`(44B 整元素拷贝) | `0x4D5ECE` / `0x4D61AB` / `0x4D6350` |
| 全库否证 | `push 0x6070`、`push 0x6000` 均 **0 命中**（不存在 24,688 的分配） | 整份 `_disasm_cache.txt` |

闭合：**512 × 44 = 22,528 = 0x5800**；`0x5800 + 0x70(112B 尾员) = 0x5870 = 22,640`。

### 2.2 改动表

**文件 A：`data/annotations/structs/C2DSpark_tagSpark.json`**

| 动作 | 字段/成员 | before | after | 证据 |
|---|---|---|---|---|
| 改 | `binary_size` | 48 | **44（0x2C）** | 步长 0x2C ×3 处、44B 整元素拷贝（A） |
| 删 | `"0x2c"` `pRenderEffect` (int) | 存在（末端 0x30） | 删除 | 它是「假设 48B」产生的伪成员：实为**下一个元素的 0x00 字段**，`0x2C ≥ 44` 本身就越界（A） |
| 留 | `0x0..0x28` 共 11 员 | — | 不动 | 尺寸闭合已够；语义名另卡（见 §2.5） |

**文件 B：`data/annotations/structs/C2DSpark.json`**

| 动作 | 字段/成员 | before | after | 证据 |
|---|---|---|---|---|
| 改 | `binary_size` | 24,688 | **22,640（0x5870）** | 分配立即数 + 清零常量 + 最大写界（A） |
| 改 | `"0x0"` `m_Spark` 类型 | `C2DSpark_tagSpark[512]` | **不变**（元素变 44 后自动 22,528） | 元素数 0x200 来自三处循环（A） |
| 移 | `0x6000 m_fDisplayWidth` | 0x6000 | **0x5800** | ctor 写 `[esi+0x5800]`（A） |
| 移 | `0x6004 m_fDisplayHeight` | 0x6004 | **0x5804** | 同上 |
| 移 | `0x6008 m_nCurrentSpark` | 0x6008 | **0x5808** | `CreateSingle`/`CreateStars` 读 `[ebx+0x5808]`（A） |
| 移 | `0x600C m_fBigLum` | 0x600C | **0x580C** | ctor 写（A） |
| 移 | `0x6010 m_nBigLumX` / `0x6014 m_nBigLumY` | 0x6010/0x6014 | **0x5810/0x5814** | ctor 写（A） |
| 移 | `0x6018 m_bMouseTrack` | 0x6018 | **0x5818** | `SetEnableMouseTrack` 写 `[ecx+0x5818]=al`（A） |
| 移 | `0x601C m_pAdditiveBlend` | 0x601C | **0x581C** | ctor 存 68B 子对象（B） |
| 移 | `0x6020..0x6044` 十员（红/蓝/绿/红16/黄16 各一对） | 0x6020..0x6044 | **0x5820..0x5844** | ctor 六个 `push 0x44` 分配 + 存点（B，偏移 A） |
| 移 | `0x6048 m_Quad` (gbUIQuad 40B) | 0x6048 | **0x5848** | 0x5848+0x28=**0x5870**（A：闭合点） |

> 19 个尾员统一 **−0x800**（因为 512 × (48−44) = 2,048 = 0x800），不是逐个猜的。

### 2.3 闭合算式

```
元素：  512 × 44            = 22,528 = 0x5800
尾员：  0x5800 .. 0x5848(Quad 起点) + 0x28 = 0x5870
总计：  0x5870              = 22,640            ✅ 与 push 0x5870 相等
```

### 2.4 24,688 / 48 是怎么来的、为什么错

- 注解的 `48 = 24,576 / 512`，而 24,576 来自**错误的尾部起点 0x6000**（`0x6000 = 512 × 48`）。
- 换句话：48 不是观测值，是「为了让尾员从 0x6000 开始」反解出来的；真值尾部起点是 0x5800。
- 差额：2,048 = 512 × 4（每元素多算 4B）——与「PDB 48 / 24,688」的 PAL3A 旧构建值一致，属参考级、不能压过本 exe 的 A 级证据。

### 2.5 验证与已知缺口

**验证（优先静态断言，其次全链）**

```bash
# 1) 编译器裁判
python3 tools/audit_type_layout.py --only C2DSpark,C2DSpark_tagSpark
# 2) 注解一致性
python3 pipeline/cli.py check
# 3) 静态断言（/tmp 独立 TU，不污染仓库）
#    sizeof(C2DSpark)==22640  sizeof(C2DSpark_tagSpark)==44
#    offsetof(C2DSpark,m_fDisplayWidth)==0x5800  offsetof(C2DSpark,m_Quad)==0x5848
# 4) 全链（独占窗口）
python3 pipeline/cli.py loop --expect-s2 ... --expect-errors ... --expect-l1 ...
```

**已知缺口（不在本卡修）**

| 缺口 | 内容 | 建议 |
|---|---|---|
| G-②-1 | `tagSpark` 的 11 个成员**语义全错**：注解写 5 组 texture/wrap 指针，实测元素是 float/int（0x00/0x04 x/y、0x18 颜色源、0x20 尺寸、0x28 类型、0x29 可见位） | 另开「tagSpark 成员重建」卡；本卡只保证 sizeof/偏移闭合 |
| G-②-2 | `0x4D61C0` 现名 `DestroyAll` 但体内是渲染循环，`0x4D6380` 又标 `Render` | 另开命名/边界卡 |
| G-②-3 | 改后 `C2DSpark` 的 512 元素成员访问会整体位移，若 decomp 里有按旧名生成的访问，codegen 产物会变 | 落地卡必须跑全链并逐单元看 S2，不要只看总错误 |

---

## 3. ④ PropUI 施工图（改动已落地，本卡核对 + 验收）

### 3.1 目标与证据（A 级，两条独立）

| 证据 | 内容 |
|---|---|
| 两处分配 | `0x45974F push 0x70DC` → `0x45975E call 0x55353B` → `0x459779 call 0x46D140`（ctor）→ `[esi+0xCC0]`；`0x523422 push 0x70DC` → `0x523431` → `0x52344B call 0x46D140` → `[esi+0x6D4]`（`push 0x70DC` 全库仅 2 命中） |
| ctor 最大写 | `0x46D49F mov BYTE [esi+0x70D8],1` → 终点 `0x70D9`，4 对齐 = **0x70DC** |
| 类身份 | `0x46D444 mov [esi],0x56B688`（vptr 与注解一致） |
| 子对象闭合 | ctor 于 `0x46D3F7` 构造 `UIFrameContainer@0x701C`（152B）→ 止于 `0x70B4`，随后写标量 0x70B4..0x70D8 |

### 3.2 工作树已落地的改动（HEAD → worktree）

| 字段 | HEAD | 工作树 | 判定 |
|---|---|---|---|
| `binary_size` | 29,056 | **28,892（0x70DC）** | ✅ 与 A 级证据一致 |
| 成员数 | 95 | **47** | ✅ 删掉了越界/幻影段 |
| 末段成员 | `mb_OK@0x6FB8` UIButton(344) + `mb_OKRc@0x7110` tagRECT(16) | `m_titleBar@0x701C` UIFrameContainer(152) → `m_unk_0x70B4` uchar[28] → `m_bInitFlag@0x70D8` uchar | ✅ 与 ctor 写界一致；`mb_OK` 在整份反汇编里**零引用**（`[esi+0x6FB8]` 0 命中），属模型错误"

> 该改动是他人/并发在工作树落下的（`M`，mtime 03:28:43），**不是本卡产物**；本卡只核对正确性并给验收步骤，不重复改。
> 48 个被删成员的逐条依据见 #31 报告 `docs/specs/2026-11-27-propui-size-164-evidence.md` §3.2（157–169 行，尾部真实结构）与 §4（170–195 行，164 归因）；本文件只保留 4 行差异，不重复列 48 行。

### 3.3 164 的构成与消除

```
0x7180(29,056) − 0x70DC(28,892) = 164
  = 52  (0x70DC..0x7110，无成员空档，由 mb_OK 344B 模型跨过)
  + 16  (mb_OKRc tagRECT)
  + 96  (0x7120..0x7180 尾垫)
```

工作树改动把三块同时消掉：`binary_size` 改 0x70DC、`mb_OK` 与其后的 `mb_OKRc` 删除、尾垫消失 ⇒ **164 归零**。

### 3.4 验证与剩余缺口

```bash
python3 tools/audit_type_layout.py --only PropUI
python3 pipeline/cli.py check
# 静态断言：sizeof(PropUI)==28892；offsetof(m_titleBar)==0x701C；
#           offsetof(m_unk_0x70B4)==0x70B4；offsetof(m_bInitFlag)==0x70D8
```

| 缺口 | 内容 | 建议 |
|---|---|---|
| G-④-1 | `0x70B4..0x70D0` 现在被压成 `unsigned char[28]`，丢了 ctor 逐个写的标量（0x70B4/0x70B8/0x70BC/0x70C0/0x70C1/0x70C4/0x70C8/0x70CC/0x70D8 共 9 个写点；读点在 `0x46DE69`/`0x46DE79`/`0x46DE8A`/`0x46DFD5` 等） | 另开「PropUI 尾部标量语义化」卡（B 级证据已够给类型，名字需按使用点取证） |
| G-④-2 | `0x70D0`/`0x70D4` 有引用（3 次 / 2 次）但未建模，落地后 census 会出现约 8B 洞 | 与 G-④-1 同卡处理；本卡不新增成员 |
| G-④-3 | `0x46D140` 现名 `InitUI`，实为 ctor | 另开命名卡 |

---

## 4. 实施顺序与依赖

| 步 | 动作 | 依赖 | 说明 |
|---|---|---|---|
| 1 | 验收 ④（工作树 28,892/47） | 无（改动已在工作树） | 只需跑 §3.4 三条命令 + 提交边界确认；**不要再改一遍** |
| 2 | 落地 ②（两个 JSON） | 独占管线窗口 | 与 #45 冲突：`#45` 正在改 ScreenFade*/Mgr 并会跑 apply/export/codegen/probe/match，必须**串行** |
| 3 | ② 全链读数对比 | 步骤 2 后 | 记录 S2/总错误/L1/check；`C2DSpark` 不进 census，新增 0 洞条目属预期 |
| 4 | G-②-1 / G-④-1 语义化 | Human 拍板 | 两张独立小卡，可与 ②④ 并行（不同文件） |

**为什么 ④ 先、② 后**：④ 的改动已在工作树，验收成本最低、风险为零改动；② 会改变 `C2DSpark` 的 512 个元素偏移，codegen 产物面较大，需要独占窗口观察 S2 逐单元变化。

---

## 5. 风险与回退

| 风险 | 触发信号 | 回退 |
|---|---|---|
| ② 改后 `C2DSpark` 相关单元 S2 退化 | `probe` 中 `pal3/src/Effect/C2DSpark.cpp` 由 ok 转 fail，或总错误上升 | 两个 JSON `git checkout`，重跑 codegen/probe；不要只回滚一个（尺寸与偏移必须成对） |
| ② 尺寸改了但 `tagSpark` 仍 48 | `check` 报 `m_Spark` 末端 0x6000 越界 / audit 报 sizeof 24,688 | 确认两个文件都改；`binary_size` 与成员偏移必须同批 |
| ④ 被误当成「待改」重做 | 有人再次把 PropUI 改回 29,056 | 以工作树 28,892/47 为准；重做前先 `git diff data/annotations/structs/PropUI.json` 看是否已有他人在改 |
| 管线并发 | 与 #45 同窗口跑 apply/export | 串行；谁先谁后由 PMO 指定，禁止并发 |

---

## 6. 已确定 / 推断 / 未解（三档）

**已确定（A 级，可直接照做）**
- ② `sizeof(C2DSpark)=22,640`、`sizeof(tagSpark)=44`、元素 512、尾员起点 0x5800、`m_Quad` 止于 0x5870。
- ④ `sizeof(PropUI)=28,892`、ctor 最大写 0x70D8、两处分配 0x70DC、164 = 52+16+96。

**推断（B 级，落地不依赖但需在卡里标注）**
- ② 尾员 0x581C..0x5844 的 6 个 68B 子对象是 `gbTextureArray`/`gbRenderEffect`（尺寸吻合，类型名未逐点取证）。
- ④ `0x70B4..0x70D8` 的 9 个写点是「显示/状态开关」族（由读点上下文推），名字未取证。

**未解（缺口，单列）**
- ② `tagSpark` 成员语义全错（G-②-1）；`DestroyAll`/`Render` 名与边界错位（G-②-2）。
- ④ `0x70D0/0x70D4` 未建模（G-④-2）；`InitUI` 实为 ctor（G-④-3）。

---

## 7. 复现命令与原样输出

### C1 引用的既有产物存在

```bash
for f in docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md \
         docs/specs/2026-11-27-propui-size-164-evidence.md \
         docs/audit/2026-11-26-r6-decision-brief.md \
         docs/specs/2026-11-27-r6-annotation-landing-plan.md; do
  test -f "$f" && echo "OK $f" || echo "MISSING $f"
done
```

```text
OK docs/specs/2026-11-27-c2dspark-tagspark-48b-evidence.md
OK docs/specs/2026-11-27-propui-size-164-evidence.md
OK docs/audit/2026-11-26-r6-decision-brief.md
OK docs/specs/2026-11-27-r6-annotation-landing-plan.md
```

### C2 当前注解三方对账（工作树 / HEAD）

```bash
python3 - <<'PY'
import json, subprocess
for cls in ['C2DSpark','C2DSpark_tagSpark','PropUI']:
    cur=json.load(open('data/annotations/structs/%s.json'%cls))
    head=json.loads(subprocess.run(['git','show','HEAD:data/annotations/structs/%s.json'%cls],
                                   capture_output=True,text=True).stdout)
    print(cls,'worktree',cur['binary_size'],len(cur['known_members']),
          '| HEAD',head['binary_size'],len(head['known_members']))
PY
```

```text
C2DSpark worktree 24688 20 | HEAD 24688 20
C2DSpark_tagSpark worktree 48 12 | HEAD 48 12
PropUI worktree 28892 47 | HEAD 29056 95
```

### C3 ② 分配链与写界（反汇编原样）

```bash
grep -nE "^ *(512ae1|512af0|512b1b|512b30):" data/status/_disasm_cache.txt
```

```text
355455:  512ae1:	68 70 58 00 00       	push   0x5870
355458:  512af0:	e8 46 0a 04 00       	call   0x55353b
355470:  512b1b:	e8 90 2f fc ff       	call   0x4d5ab0
355475:  512b30:	89 46 34             	mov    DWORD PTR [esi+0x34],eax
```

### C4 ② 步长 0x2C（三处）

```bash
grep -nE "^ *(4d5ece|4d61ab|4d6350):" data/status/_disasm_cache.txt
```

```text
273619:  4d5ece:	83 c1 2c             	add    ecx,0x2c
273850:  4d61ab:	83 c0 2c             	add    eax,0x2c
273969:  4d6350:	83 c7 2c             	add    edi,0x2c
```

### C5 ② 全库否证

```bash
grep -cE "push +0x6070" data/status/_disasm_cache.txt
grep -cE "push +0x6000" data/status/_disasm_cache.txt
```

```text
0
0
```

### C6 ④ 两处分配

```bash
grep -nE "^ *(45974f|45975e|523422|523431):" data/status/_disasm_cache.txt
```

```text
119071:  45974f:	68 dc 70 00 00       	push   0x70dc
119074:  45975e:	e8 d8 9d 0f 00       	call   0x55353b
377289:  523422:	68 dc 70 00 00       	push   0x70dc
377292:  523431:	e8 05 01 03 00       	call   0x55353b
```

### C7 ④ 尾部引用（0x70D0/0x70D4/0x70B4..0x70D8）

```bash
grep -cE "\+0x70d0\]" data/status/_disasm_cache.txt
grep -cE "\+0x70d4\]" data/status/_disasm_cache.txt
grep -nE "\+0x70d8\]" data/status/_disasm_cache.txt | wc -l
```

```text
3
2
25
```

> 25 = 1 处写（ctor `0x46D49F`）+ 24 处读；与 #31 报告的「6 处读」是不同口径（那只统计 PropUI 方法域内的单基址读），本卡按全库计数。

### C8 ④ 当前 worktree 尾部成员

```bash
python3 - <<'PY'
import json
d=json.load(open('data/annotations/structs/PropUI.json'))
for k in sorted(d['known_members'], key=lambda x:int(x,0))[-4:]:
    m=d['known_members'][k]; print(k, m['name'], json.dumps(m.get('type'))[:40])
print('binary_size', d['binary_size'])
PY
```

```text
0x6ea4 m_noBtn "unsigned char[344]"
0x701c m_titleBar "UIFrameContainer"
0x70b4 m_unk_0x70B4 "unsigned char[28]"
0x70d8 m_bInitFlag "unsigned char"
binary_size 28892 members 47
```

### C9 census 只登记有洞类 + 0x6FB8 零引用

```bash
grep -cE "\\+0x6fb8\\]" data/status/_disasm_cache.txt || true
```

```text
0
```

> census 形状用下面这段（与工具等价，只读）证明：`classes` 与 `classes_with_holes` 长度相等（199），且 C2DSpark/tagSpark 不在其中；因此落地后零洞的它们不会入表。

```bash
python3 -c "import json;d=json.load(open('data/status/struct_holes_20261125.json'));cl=d['classes'];print('classes_len',len(cl),'meta',d['_meta']['classes_with_holes']);print('C2DSpark in',any(c.get('cls')=='C2DSpark' for c in cl),'tagSpark in',any(c.get('cls')=='C2DSpark_tagSpark' for c in cl))"
```

```text
classes_len 199 meta 199
C2DSpark in False tagSpark in False
```

---

## 8. 给 PMO 的开卡条件与建议 writeScopes

**可开实现卡（②）的条件**：本文件与 #29 证据已齐；④ 先验收；等 #45 释放管线通道；Human 认可「先尺寸、后语义」的两步走。

| 卡 | 建议 writeScopes | 验收 |
|---|---|---|
| ② 落地 | `data/annotations/structs/C2DSpark.json`、`data/annotations/structs/C2DSpark_tagSpark.json` | `audit_type_layout --only C2DSpark,C2DSpark_tagSpark` 通过；`check` 无新错；静态断言 sizeof 22,640/44、尾员 0x5800/0x5848；全链 S2/总错误/L1 不退化；census **不新增条目**（零洞类不入 `classes`，`classes_with_holes` 保持 199，见 C9） |
| ④ 验收 | 无（只读核对） | §3.4 三条命令通过；确认工作树 28,892/47 与 #31 证据一致；提交时与 HEAD 差异一并说明 |
| G-②-1 tagSpark 语义 | `data/annotations/structs/C2DSpark_tagSpark.json` | 逐成员给出使用点证据；命名禁用 `slot_N`/伪语义 |
| G-④-1 PropUI 尾部标量 | `data/annotations/structs/PropUI.json` | 0x70B4..0x70D8 逐字段类型/名字证据；census 洞归零 |

**不替 Human 拍板**：② 是否接受「语义后置」、④ 是否接受 `m_unk_0x70B4[28]` 留白、两卡先后顺序。
